/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_fmc_core.h
  * @brief   Header file of FMC HAL module.
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
#ifndef STM32H7PXX_FMC_CORE_H
#define STM32H7PXX_FMC_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @defgroup FMC_Core FMC Core
  * @{
  */

#if defined (FMC_BASE)
/** @defgroup FMC_Core_Private_Constants FMC Core Private Constants
  * @{
  */
/* Number of nanoseconds in one second */
#define FMC_NANOSECONDS_PER_SECOND  (1000000000UL) /*!< Number of nanoseconds in one second  */
#define FMC_MILLISECONDS_PER_SECOND (1000U)        /*!< Number of milliseconds in one second */
#define FMC_MICROSECONDS_PER_SECOND (1000000U)     /*!< Number of microseconds in one second */
/**
  * @}
  */

/** @defgroup FMC_Core_Private_Macros FMC Core Private Macros
  * @{
  */
#if defined (FMC_NORSRAM_BK1)
#define IS_FMC_ADDR_SETUP_TIME(time) ((time) <= 15U)
#define IS_FMC_ADDR_HOLD_TIME(time) (((time) > 0U) && ((time) <= 15U))
#define IS_FMC_DATASETUP_TIME(time) (((time) > 0U) && ((time) <= 255U))
#define IS_FMC_TURNAROUND_TIME(time) (((time) > 0U) && ((time) <= 16U))
#define IS_FMC_CLK_DIV(div) (((div) > 0U) && ((div) <= 16U))
#define IS_FMC_DATA_LATENCY(latency) (((latency) > 1U) && ((latency) <= 17U))
#endif /* FMC_NORSRAM_BK1 */
#define FMC_READ_FIELD(value, msk, pos) (((uint32_t)(value) & msk) >> pos)
#define FMC_WRITE_FIELD(value, msk, pos) (((uint32_t)(value) << pos) & msk)
#if defined (FMC_SDRAM_BK5)
#define IS_FMC_LOAD_TO_ACTIVE_DELAY(delay) (((delay) > 0U) && ((delay) <= 16U))
#define IS_FMC_EXIT_SELFREFRESH_DELAY(delay) (((delay) > 0U) && ((delay) <= 16U))
#define IS_FMC_SELFREFRESH_TIME(time) (((time) > 0U) && ((time) <= 16U))
#define IS_FMC_ROW_CYCLE_DELAY(delay) (((delay) > 0U) && ((delay) <= 16U))
#define IS_FMC_WRITE_RECOVERY_TIME(time) (((time) > 0U) && ((time) <= 16U))
#define IS_FMC_ROW_PRECHARGE_DELAY(delay) (((delay) > 0U) && ((delay) <= 16U))
#define IS_FMC_ROW_TO_COLUMN_DELAY(delay) (((delay) > 0U) && ((delay) <= 16U))
#endif /* FMC_SDRAM_BK5 */
#if defined (FMC_NAND_BK)
#define IS_FMC_TCLR_TIME(time) (((time) > 0U) && ((time) <= 16U))
#define IS_FMC_TAR_TIME(time) (((time) > 0U) && ((time) <= 16U))
#define IS_FMC_SETUP_TIME(time) (((time) > 0U) && ((time) <= 255U))
#define IS_FMC_WAIT_TIME(time) (((time) > 0U) && ((time) <= 255U))
#define IS_FMC_HOLD_TIME(time) (((time) > 0U) && ((time) <= 254U))
#define IS_FMC_HIZ_COMMON_TIME(time) (((time) > 0U) && ((time) <= 255U))
#endif /* FMC_NAND_BK */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup FMC_Core_Exported_Constants FMC Core Exported Constants
  * @{
  */

/** @defgroup FMC_Write_Timing FMC Write Timing
  * @{
  */
#if defined (FMC_NORSRAM_BK1)
#define FMC_WR_TIMING_VALUE (0x0FFFFFFFU)
/**
  * @}
  */

/** @defgroup FMC_Memory_Type FMC Memory Type
  * @{
  */
#define FMC_MEMORY_TYPE_SRAM  (0x00000000U)
#define FMC_MEMORY_TYPE_PSRAM FMC_BCRx_MTYP_0
#define FMC_MEMORY_TYPE_NOR   FMC_BCRx_MTYP_1
/**
  * @}
  */

/** @defgroup FMC_Data_Address_Bus_Multiplexing FMC Data Address Bus Multiplexing
  * @{
  */
#define FMC_MUX_DATA_ADDR_DISABLE (0x00000000U)
#define FMC_MUX_DATA_ADDR_ENABLE  FMC_BCRx_MUXEN
/**
  * @}
  */

/** @defgroup FMC_Data_Bus_Width FMC Data Bus Width
  * @{
  */
#define FMC_DATA_BUS_WIDTH_8_BIT  (0x00000000U)
#define FMC_DATA_BUS_WIDTH_16_BIT FMC_BCRx_MWID_0
/**
  * @}
  */

/** @defgroup FMC_Write_FIFO FMC Write FIFO
  * @{
  */
#define FMC_WRITE_FIFO_ENABLE  (0x00000000U)
#define FMC_WRITE_FIFO_DISABLE FMC_BCR1_WFDIS
/**
  * @}
  */

/** @defgroup FMC_Wait_Signal_Polarity FMC Wait Signal Polarity
  * @{
  */
#define FMC_WAIT_SIGNAL_POLARITY_LOW  (0x00000000U)
#define FMC_WAIT_SIGNAL_POLARITY_HIGH FMC_BCRx_WAITPOL
/**
  * @}
  */

/** @defgroup FMC_Wait_Timing_Configuration FMC Wait Timing Configuration
  * @{
  */
#define FMC_WAIT_TIMING_CONFIG_BEFORE_WAITSTAT (0x00000000U)
#define FMC_WAIT_TIMING_CONFIG_DURING_WAITSTAT FMC_BCRx_WAITCFG
/**
  * @}
  */

/** @defgroup FMC_Synchonous_Wait_Signal_State FMC Synchronous Wait Signal State
  * @{
  */
#define FMC_SYNC_WAIT_SIGNAL_DISABLE (0x00000000U)
#define FMC_SYNC_WAIT_SIGNAL_ENABLE  FMC_BCRx_WAITEN
/**
  * @}
  */

/** @defgroup FMC_Asynchronous_Wait_Signal_State FMC Asynchronous Wait Signal State
  * @{
  */
#define FMC_ASYNC_WAIT_SIGNAL_DISABLE (0x00000000U)
#define FMC_ASYNC_WAIT_SIGNAL_ENABLE  FMC_BCRx_ASYNCWAIT
/**
  * @}
  */

/** @defgroup FMC_Continous_Clock FMC Continuous Clock
  * @{
  */
#define FMC_CONTINUOUS_CLOCK_SYNC_ONLY  (0x00000000U)
#define FMC_CONTINUOUS_CLOCK_SYNC_ASYNC FMC_BCR1_CCLKEN
/**
  * @}
  */

/** @defgroup FMC_Page_Size FMC Page Size
  * @{
  */
#define FMC_PAGE_SIZE_NONE      (0x00000000U)
#define FMC_PAGE_SIZE_128_BYTE  FMC_BCRx_CPSIZE_0
#define FMC_PAGE_SIZE_256_BYTE  FMC_BCRx_CPSIZE_1
#define FMC_PAGE_SIZE_512_BYTE  (FMC_BCRx_CPSIZE_0 | FMC_BCRx_CPSIZE_1)
#define FMC_PAGE_SIZE_1024_BYTE FMC_BCRx_CPSIZE_2
/**
  * @}
  */

/** @defgroup FMC_Access_Mode FMC Access Mode
  * @{
  */
#define FMC_ACCESS_MODE_A (0x00000000U)
#define FMC_ACCESS_MODE_B FMC_BTRx_ACCMOD_0
#define FMC_ACCESS_MODE_C FMC_BTRx_ACCMOD_1
#define FMC_ACCESS_MODE_D FMC_BTRx_ACCMOD_2
/**
  * @}
  */
#endif /* FMC_NORSRAM_BK1 */

#if defined (FMC_SDRAM_BK5)
/** @defgroup FMC_SDRAM_Max_Refresh_Rate_Value FMC SDRAM Max Refresh Rate Value
  * @{
  */
#define FMC_SDRAM_MAX_REFRESH_RATE_VALUE (4095U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Max_Load_Mode_Value FMC SDRAM Max Load Mode Value
  * @{
  */
#define FMC_SDRAM_MAX_LOAD_MODE_VALUE (16383U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Refresh_Rate_Safe_Margin_Value FMC SDRAM Refresh Rate Safe Margin Value
  * @{
  */
#define FMC_SDRAM_REFRESH_RATE_SAFE_MARGIN_CYCLE (20U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Column_Bits_number FMC SDRAM Column Address Width
  * @{
  */
#define FMC_SDRAM_COLUMN_ADDR_WIDTH_8_BIT  (0x00000000U)
#define FMC_SDRAM_COLUMN_ADDR_WIDTH_9_BIT  FMC_SDCR_NC_0
#define FMC_SDRAM_COLUMN_ADDR_WIDTH_10_BIT FMC_SDCR_NC_1
#define FMC_SDRAM_COLUMN_ADDR_WIDTH_11_BIT FMC_SDCR_NC_Msk
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Row_Bits_number FMC SDRAM Row Address Width
  * @{
  */
#define FMC_SDRAM_ROW_ADDR_WIDTH_11_BIT (0x00000000U)
#define FMC_SDRAM_ROW_ADDR_WIDTH_12_BIT FMC_SDCR_NR_0
#define FMC_SDRAM_ROW_ADDR_WIDTH_13_BIT FMC_SDCR_NR_1
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Memory_Bus_Width FMC SDRAM Memory Bus Width
  * @{
  */
#define FMC_SDRAM_MEM_BUS_WIDTH_8_BIT  (0x00000000U)
#define FMC_SDRAM_MEM_BUS_WIDTH_16_BIT FMC_SDCR_MWID_0
#define FMC_SDRAM_MEM_BUS_WIDTH_32_BIT FMC_SDCR_MWID_1
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Internal_Banks_Number FMC SDRAM Internal Banks Number
  * @{
  */
#define FMC_SDRAM_INTERN_BANKS_NUMBER_2 (0x00000000U)
#define FMC_SDRAM_INTERN_BANKS_NUMBER_4 (0x00000040U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Read_Burst FMC SDRAM Read Burst
  * @{
  */
#define FMC_SDRAM_READ_BURST_DISABLE (0x00000000U)
#define FMC_SDRAM_READ_BURST_ENABLE  FMC_SDCR_RBURST
/**
  * @}
  */

/** @defgroup FMC_SDRAM_CAS_Latency FMC SDRAM CAS Latency
  * @{
  */
#define FMC_SDRAM_CAS_LATENCY_1_CYCLE  FMC_SDCR_CAS_0
#define FMC_SDRAM_CAS_LATENCY_2_CYCLE  FMC_SDCR_CAS_1
#define FMC_SDRAM_CAS_LATENCY_3_CYCLE  FMC_SDCR_CAS
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Write_Protection FMC SDRAM Write Protection
  * @{
  */
#define FMC_SDRAM_WRITE_PROTECTION_DISABLE (0x00000000U)
#define FMC_SDRAM_WRITE_PROTECTION_ENABLE  FMC_SDCR_WP
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Read_Pipe_Delay FMC SDRAM Read Pipe Delay
  * @{
  */
#define FMC_SDRAM_READ_PIPE_DELAY_0_CYCLE (0x00000000U)
#define FMC_SDRAM_READ_PIPE_DELAY_1_CYCLE FMC_SDCR_RPIPE_0
#define FMC_SDRAM_READ_PIPE_DELAY_2_CYCLE FMC_SDCR_RPIPE_1
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Kernel_Clock_Multiplier FMC SDRAM Kernel Clock Multiplier
  * @{
  */
#define FMC_SDRAM_CLOCK_PERIOD_MULT_2 (0x00000002U)
#define FMC_SDRAM_CLOCK_PERIOD_MULT_3 (0x00000003U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Command_Mode FMC SDRAM Command Mode
  * @{
  */
#define FMC_SDRAM_COMMAND_NORMAL      (0x00000000U)
#define FMC_SDRAM_COMMAND_CLK_ENABLE  FMC_SDCMR_MODE_0
#define FMC_SDRAM_COMMAND_PALL        FMC_SDCMR_MODE_1
#define FMC_SDRAM_COMMAND_AUTOREFRESH (FMC_SDCMR_MODE_0 | FMC_SDCMR_MODE_1)
#define FMC_SDRAM_COMMAND_LOAD        FMC_SDCMR_MODE_2
#define FMC_SDRAM_COMMAND_SELFREFRESH (FMC_SDCMR_MODE_0 | FMC_SDCMR_MODE_2)
#define FMC_SDRAM_COMMAND_POWERDOWN   (FMC_SDCMR_MODE_1 | FMC_SDCMR_MODE_2)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Remap_Config FMC SDRAM Remap Config
  * @{
  */
#define FMC_SDRAM_DEVICE1_REGION5_NOR_SRAM_REGION1 (0x00000000U)
#define FMC_SDRAM_DEVICE1_REGION1_NOR_SRAM_REGION5 FMC_BCR1_BMAP_0
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Devices FMC SDRAM Devices
  * @{
  */
#define FMC_SDRAM_DEVICE1 (0U)
#define FMC_SDRAM_DEVICE2 (1U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Mode_Status FMC SDRAM Mode Status
  * @{
  */
#define FMC_SDRAM_DEVICE_NORMAL_MODE  (0x00000000U)
#define FMC_SDRAM_DEVICE_SELF_REFRESH FMC_SDSR_MODES1_0
#define FMC_SDRAM_DEVICE_POWER_DOWN   FMC_SDSR_MODES1_1
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Interrupt_Definition FMC SDRAM Low Layer Interrupt definition
  * @{
  */
#define FMC_SDRAM_IT_REFRESH_ERROR FMC_SDRTR_REIE
/**
  * @}
  */

/** @defgroup FMC_Flag_definition FMC SDRAM Flag definition
  * @{
  */
#define FMC_SDRAM_FLAG_CLEAR_REFRESH_ERROR FMC_SDRTR_CRE
#define FMC_SDRAM_FLAG_REFRESH_ERROR       FMC_SDSR_RE
/**
  * @}
  */
#endif /* FMC_SDRAM_BK5 */

#if defined (FMC_NAND_BK)
#define FMC_NAND_DEVICE_MANUFACTURER_LEN         (12U)
#define FMC_NAND_DEVICE_MODEL_LEN                (20U)
#define FMC_NAND_PAGE_SIZE_512                   (512U)
#define FMC_NAND_ECC_HAMMING_SIZE_BYTE           (4U)
#define FMC_NAND_MAX_PAGES_FOR_16BIT_ADDRESS     (65535U)
#define FMC_NAND_ADDR_1ST_CYCLE(addr)            (uint8_t)(addr)
#define FMC_NAND_ADDR_2ND_CYCLE(addr)            (uint8_t)((addr) >> 8U)
#define FMC_NAND_ADDR_3RD_CYCLE(addr)            (uint8_t)((addr) >> 16U)
#define FMC_NAND_ADDR_4TH_CYCLE(addr)            (uint8_t)((addr) >> 24U)
#define FMC_NAND_COLUMN_1ST_CYCLE(addr)          (uint8_t)((addr) & 0xFFU)
#define FMC_NAND_COLUMN_2ND_CYCLE(addr)          (uint8_t)((addr) >> 8U)
#define FMC_NAND_ADDR_AREA                       (0x00020000U)
#define FMC_NAND_ADDR_AREA_A                     (0x00000000U)
/* Constants to define commands for NAND Memory */
#define FMC_NAND_CMD_AREA                        (0x00010000U)
#define FMC_NAND_CMD_RESET                       ((uint8_t)0xFFU)
#define FMC_NAND_CMD_READ_ID                     ((uint8_t)0x90U)
#define FMC_NAND_CMD_ERASE0                      ((uint8_t)0x60U)
#define FMC_NAND_CMD_ERASE1                      ((uint8_t)0xD0U)
#define FMC_NAND_CMD_AREA_A                      ((uint8_t)0x00U)
#define FMC_NAND_CMD_AREA_B                      ((uint8_t)0x01U)
#define FMC_NAND_CMD_AREA_C                      ((uint8_t)0x50U)
#define FMC_NAND_CMD_AREA_TRUE1                  ((uint8_t)0x30U)
#define FMC_NAND_CMD_RANDOM_OUTPUT_0             ((uint8_t)0x05U)
#define FMC_NAND_CMD_RANDOM_OUTPUT_1             ((uint8_t)0xE0U)
#define FMC_NAND_CMD_WRITE0                      ((uint8_t)0x80U)
#define FMC_NAND_CMD_WRITE_TRUE1                 ((uint8_t)0x10U)
#define FMC_NAND_CMD_RANDOM_INPUT                ((uint8_t)0x85U)
#define FMC_NAND_CMD_STATUS                      ((uint8_t)0x70U)
#define FMC_NAND_CMD_READ_PARAMETER_PAGE         ((uint8_t)0xECU)
#define FMC_NAND_CMD_READ_COPY_BACK              ((uint8_t)0x35U)


/** @defgroup NAND_Flag Flags
  * @{
  */
#define FMC_NAND_FLAG_FIFO_EMPTY   FMC_SR_FEMPT
/**
  * @}
  */

/** @defgroup FMC_NAND_Wait_feature FMC NAND Wait feature
  * @{
  */
#define FMC_NAND_WAIT_FEATURE_DISABLED (0x00000000U)
#define FMC_NAND_WAIT_FEATURE_ENABLED  (FMC_PCR_PWAITEN)
/**
  * @}
  */

/** @defgroup FMC_NAND_Data_Width FMC NAND Data Width
  * @{
  */
#define FMC_NAND_DATA_BUS_WIDTH_8_BIT  (0x00000000U)
#define FMC_NAND_DATA_BUS_WIDTH_16_BIT (FMC_PCR_PWID_0)
/**
  * @}
  */

/** @defgroup FMC_ECC_Algorithm FMC ECC algorithm
  * @{
  */
#define FMC_NAND_ECC_ALGO_NONE     (0xFFFFFFFFU)
#define FMC_NAND_ECC_ALGO_HAMMING  (0x00000000U)
/**
  * @}
  */

/** @defgroup FMC_NAND_ECC_Access_Mode FMC NAND Sequencer and BCH access mode
  * @{
  */
#define FMC_NAND_ACCESS_MODE_IGNORE  (0xFFFFFFFFU)

/** @defgroup FMC_NAND_Chunk_Size FMC NAND chunk Size
  * @{
  */
#define FMC_NAND_CHUNK_SIZE_256_BYTE  (0U << FMC_PCR_ECCPS_Pos)
#define FMC_NAND_CHUNK_SIZE_512_BYTE  (1U << FMC_PCR_ECCPS_Pos)
#define FMC_NAND_CHUNK_SIZE_1024_BYTE (2U << FMC_PCR_ECCPS_Pos)
#define FMC_NAND_CHUNK_SIZE_2048_BYTE (3U << FMC_PCR_ECCPS_Pos)
#define FMC_NAND_CHUNK_SIZE_4096_BYTE (4U << FMC_PCR_ECCPS_Pos)
#define FMC_NAND_CHUNK_SIZE_8192_BYTE (5U << FMC_PCR_ECCPS_Pos)
#endif /* FMC_NAND_BK */

/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup FMC_Core_Exported_Macros FMC Core Exported Macros
  * @{
This subsection provides a macro allowing to check the current handle state and move it to a new state
in an atomic way.
  */
#if defined(USE_HAL_CHECK_PROCESS_STATE) && (USE_HAL_CHECK_PROCESS_STATE == 1U)
#define FMC_CHECK_UPDATE_STATE(handle, state_field, fmc_conditional_state, fmc_new_state, previous_state)       \
  do {                                                                                                              \
    do {                                                                                                            \
      /* Return HAL_BUSY if the status is not ready */                                                              \
      if ((__LDREXW((volatile uint32_t *)((uint32_t)&(handle)->state_field))                                        \
           & (uint32_t)(fmc_conditional_state)) == 0U)                                                              \
      {                                                                                                             \
        return HAL_BUSY;                                                                                            \
      }                                                                                                             \
      (previous_state) = (handle)->state_field;                                                                     \
      /* If state is ready then attempt to change the state to the new one */                                       \
    } while (__STREXW((uint32_t)(fmc_new_state), (volatile uint32_t *)((uint32_t)&((handle)->state_field))) != 0U); \
    /* Do not start any other memory access until memory barrier is complete */                                     \
    __DMB();                                                                                                        \
  } while (0)
#else
#define FMC_CHECK_UPDATE_STATE(handle, state_field, fmc_conditional_state, fmc_new_state, previous_state)       \
  do {                                                                                                              \
    (previous_state)       = (handle)->state_field;                                                                 \
    (handle)->state_field = (fmc_new_state);                                                                        \
  } while(0)
#endif /* USE_HAL_CHECK_PROCESS_STATE == 1U */
/**
  * @}
  */

/* Private Functions -------------------------------------------------------------------------------------------------*/
/** @defgroup FMC_Core_Private_Functions FMC Core Private Functions
  * @{
This subsection provides a set of functions allowing to :
- Enable and disable the FMC.
- Set the FMC regions remap.
- Get the FMC region remap.
- Enable and disable the NORSRAM device.
- Enable and disable the NORSRAM device write protection.
- Get the corresponding NORSRAM device write protection status.
- Enable and disable the FMC SDRAM device write protection.
- Get the corresponding FMC SDRAM device write protection status.
- Check whether the specified FMC SDRAM flag is set.
- Clear the specified FMC SDRAM flag.
- Enable the specified FMC SDRAM interrupt.
- Disable the specified FMC SDRAM interrupt.
- Check whether the specified FMC SDRAM interrupt is set.
- Enable and disable the NAND device.
- Get the corresponding NAND device status.
- Enable and disable the NAND ECC.
- Get the corresponding NAND ECC status.
- Get the corresponding NAND ECC results.
  */
#if defined (FMC_NORSRAM_BK1)
/**
  * @brief Enable the FMC peripheral.
  */
__STATIC_INLINE void FMC_Enable(void)
{
  STM32_SET_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_FMCEN);
}

/**
  * @brief Disable the FMC peripheral.
  */
__STATIC_INLINE void FMC_Disable(void)
{
  STM32_CLEAR_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_FMCEN);
}

/**
  * @brief Set the FMC region remap.
  * @param remap_value Specifies the remap value to be set.
  *                    This parameter must be one of the following values:
  *                    @arg @ref FMC_SDRAM_REMAP_DEVICE1_REGION5
  *                    @arg @ref FMC_SDRAM_REMAP_DEVICE1_REGION1
  */
__STATIC_INLINE void FMC_SetRegionRemap(uint32_t remap_value)
{
  STM32_MODIFY_REG(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_BMAP, remap_value);
}

/**
  * @brief  Get the FMC region remap value.
  * @return uint32_t The current remap value.
  */
__STATIC_INLINE uint32_t FMC_GetRegionRemap(void)
{
  return (STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_BMAP));
}

/**
  * @brief Enable the NORSRAM device.
  * @param p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NOR_SRAM_Enable(FMC_NORSRAM_SUBBANK_TypeDef *p_instance)
{
  STM32_SET_BIT(p_instance->BCR, FMC_BCRx_MBKEN);
}

/**
  * @brief Disable the NORSRAM device.
  * @param p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NOR_SRAM_Disable(FMC_NORSRAM_SUBBANK_TypeDef *p_instance)
{
  STM32_CLEAR_BIT(p_instance->BCR, FMC_BCRx_MBKEN);
}

/**
  * @brief Enable the NORSRAM device write protection.
  * @param p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NOR_SRAM_EnableWriteProtection(FMC_NORSRAM_SUBBANK_TypeDef *p_instance)
{
  STM32_CLEAR_BIT(p_instance->BCR, FMC_BCRx_WREN_Msk);
}

/**
  * @brief Disable the NORSRAM device write protection.
  * @param p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NOR_SRAM_DisableWriteProtection(FMC_NORSRAM_SUBBANK_TypeDef *p_instance)
{
  STM32_SET_BIT(p_instance->BCR, FMC_BCRx_WREN_Msk);
}

/**
  * @brief  Get the corresponding NORSRAM device write protection status.
  * @param  p_instance Pointer to the device instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FMC_NOR_SRAM_IsEnabledWriteProtection(const FMC_NORSRAM_SUBBANK_TypeDef *p_instance)
{
  return (((STM32_READ_BIT(p_instance->BCR, FMC_BCRx_WREN_Msk) == FMC_BCRx_WREN_Msk) ? 0UL : 1UL));
}

/**
  * @brief  Calculate the NOR device address.
  * @param  instance Pointer to the device instance.
  * @param  offset   NOR memory offset address
  * @retval NOR address value.
  */
__STATIC_INLINE uint32_t FMC_NOR_CalculateMemoryAddress(uint32_t instance, uint16_t offset)
{
  uint32_t FMC_REGION = (STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_BMAP) == FMC_BCR1_BMAP_0) ?
                        FMC_SDRAM_BK5 : FMC_BASE;

  return ((uint32_t)((((((uint32_t)instance - (uint32_t)FMC_NORSRAM1_SUBBANK1) / 8UL) * 0x04000000UL) + FMC_REGION) +
                     (2U * (uint32_t)(offset))));
}

/**
  * @brief  Read a single byte (8 bits) from NOR memory at a specified offset.
  * @param  instance Pointer to the device instance.
  * @param  offset   Offset within the NOR memory to read from.
  * @retval The 8-bit value read from the NOR memory.
  */
__STATIC_INLINE uint8_t FMC_NOR_ReadMemory8(uint32_t instance, uint16_t offset)
{
  return *(volatile uint8_t *)FMC_NOR_CalculateMemoryAddress(instance, offset);
}

/**
  * @brief  Read a 16-bit half-word from NOR memory at a specified offset.
  * @param  instance Pointer to the device instance.
  * @param  offset   Offset within the NOR memory to read from.
  * @retval The 16-bit half-word value read from the NOR memory.
  */
__STATIC_INLINE uint16_t FMC_NOR_ReadMemory16(uint32_t instance, uint16_t offset)
{
  return *(volatile uint16_t *)FMC_NOR_CalculateMemoryAddress(instance, offset);
}

/**
  * @brief Write the NOR memory data to specified address.
  * @param address NOR memory address.
  * @param data    Data to write.
  */
__STATIC_INLINE void FMC_NOR_Write(uint32_t address, uint16_t data)
{
  *(volatile uint16_t *)address = data;
  __DSB();
}

/**
  * @brief Write multiple bytes to NOR memory starting at a specified address.
  * @param device_addr Starting NOR memory address to write.
  * @param p_data_addr Pointer to the source data buffer.
  * @param size_byte   Number of bytes to write.
  */
__STATIC_INLINE void FMC_NOR_WriteBuffer(uint32_t device_addr, const void *p_data_addr, uint32_t size_byte)
{
  uint16_t *p_current_address   = (uint16_t *)device_addr;
  const uint16_t *p_end_address = (uint16_t *)(device_addr + (size_byte - 1U));
  const uint16_t *p_src_data    = (const uint16_t *)p_data_addr;

  while (p_current_address <= p_end_address)
  {
    *p_current_address = *p_src_data;
    __DSB();
    ++p_current_address;
    ++p_src_data;
  }
}

/**
  * @brief Read multiple bytes from NOR memory starting at a specified address.
  * @param device_addr Starting NOR memory address to read.
  * @param p_data      Pointer to the destination buffer where data is stored.
  * @param size_byte   Number of bytes to read.
  */
__STATIC_INLINE void FMC_NOR_ReadBuffer(uint32_t device_addr, void *p_data, uint32_t size_byte)
{
  uint8_t *p_dest_data = (uint8_t *)p_data;
  uint32_t size = size_byte;
  uint32_t addr = device_addr;

  while (size > 0U)
  {
    *p_dest_data = *(volatile uint8_t *)addr;
    ++p_dest_data;
    ++addr;
    --size;
  }
}

/**
  * @brief  Convert the voltage supply value from CFI format to millivolts.
  * @param  voltage_cfi_value The voltage value obtained from the device info in CFI format.
  * @retval The resulting voltage value in millivolts.
  */
__STATIC_INLINE uint32_t FMC_NOR_ConvertVoltage(uint16_t voltage_cfi_value)
{
  return ((uint32_t)(((voltage_cfi_value & 0x0FUL) * 100UL) + (((voltage_cfi_value & 0xF0UL) >> 4U) * 1000UL)));
}
#endif /* defined(FMC_NORSRAM_BK1) */

/**
  * @brief  Compute the ceiling of an unsigned 64-bit division.
  * @param  dividend Unsigned 64-bit dividend.
  * @param  divisor  Unsigned 64-bit divisor.
  * @retval Returns 0 if divisor is 0.
  */
__STATIC_INLINE uint64_t FMC_CeilDivU64(uint64_t dividend, uint64_t divisor)
{
  return ((divisor != 0U) ? ((dividend + divisor - 1UL) / divisor) : 0UL);
}

/**
  * @brief  Convert the timing parameters from nanoseconds to source clock cycle number.
  * @param  timing_nsec        The timing parameter in nanoseconds.
  * @param  source_clk_freq_hz The source clock frequency in Hz.
  * @retval timing parameter in source clock cycle number.
  */
__STATIC_INLINE uint32_t FMC_ConvertNanosecondsToClockCycle(uint32_t timing_nsec, uint32_t source_clk_freq_hz)
{
  /* Convert timing from nanoseconds to the number of source clock cycles, rounding up to the nearest whole cycle */
  return ((uint32_t)FMC_CeilDivU64(((uint64_t)timing_nsec * (uint64_t)source_clk_freq_hz),
                                   (uint64_t)FMC_NANOSECONDS_PER_SECOND));
}

/**
  * @brief  Convert the timing parameters from source clock cycle number to nanoseconds.
  * @param  timing_cycle       The timing parameter in source clock cycle number.
  * @param  source_clk_freq_hz The source clock frequency in Hz.
  * @retval timing parameter in nanoseconds.
  */
__STATIC_INLINE uint32_t FMC_ConvertClockCycleToNanoseconds(uint32_t timing_cycle, uint32_t source_clk_freq_hz)
{
  return ((source_clk_freq_hz != 0U) ?
          ((uint32_t)(((uint64_t)timing_cycle * FMC_NANOSECONDS_PER_SECOND) / source_clk_freq_hz)) : 0UL);
}

#if defined (FMC_SDRAM_BK5)

/**
  * @brief Enable the FMC SDRAM device write protection.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param device     Specifies the selected device.
  *                   This parameter must be one of the following values:
  *                    @arg @ref FMC_SDRAM_DEVICE1
  *                    @arg @ref FMC_SDRAM_DEVICE2
  */
__STATIC_INLINE void FMC_SDRAM_EnableWriteProtection(FMC_SDRAM_TypeDef *p_instance, uint32_t device)
{
  STM32_SET_BIT(p_instance->SDCR[device], FMC_SDCR_WP_Msk);
}

/**
  * @brief Disable the FMC SDRAM device write protection.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param device     Specifies the selected device.
  *                   This parameter must be one of the following values:
  *                    @arg @ref FMC_SDRAM_DEVICE1
  *                    @arg @ref FMC_SDRAM_DEVICE2
  */
__STATIC_INLINE void FMC_SDRAM_DisableWriteProtection(FMC_SDRAM_TypeDef *p_instance, uint32_t device)
{
  STM32_CLEAR_BIT(p_instance->SDCR[device], FMC_SDCR_WP_Msk);
}

/**
  * @brief Get the corresponding FMC SDRAM device write protection status.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param device     Specifies the selected device.
  *                   This parameter must be one of the following values:
  *                    @arg @ref FMC_SDRAM_DEVICE1
  *                    @arg @ref FMC_SDRAM_DEVICE2
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FMC_SDRAM_IsEnabledWriteProtection(const FMC_SDRAM_TypeDef *p_instance, uint32_t device)
{
  return (((STM32_READ_BIT(p_instance->SDCR[device], FMC_SDCR_WP_Msk) == FMC_SDCR_WP_Msk) ? 1UL : 0UL));
}

/**
  * @brief  Adjust the timing parameters from kernel clock cycle number to nanoseconds.
  * @param  timing             The timing parameter in source clock cycle number.
  * @param  source_clk_freq_hz The clock frequency in Hz.
  * @param  row_nb             The rows number.
  * @return timing parameter in nanoseconds.
  */
__STATIC_INLINE uint32_t FMC_SDRAM_AdjustRefreshPeriodNanoseconds(uint32_t timing, uint32_t source_clk_freq_hz,
                                                                  uint32_t row_nb)
{
  return ((source_clk_freq_hz != 0U) ? (uint32_t)((((uint64_t)timing +
                                                    (uint64_t)FMC_SDRAM_REFRESH_RATE_SAFE_MARGIN_CYCLE) *
                                                   ((uint64_t)row_nb * 1000UL)) / source_clk_freq_hz) : 0UL);
}

/**
  * @brief  Set the SDRAM clock (SDCLK) in the SDRAM controller.
  * @param  p_instance Pointer to the FMC SDRAM instance.
  * @param  multiplier SDRAM clock period multiplier value:
  *                    This parameter must be one of the following values:
  *                    @arg @ref FMC_SDRAM_CLOCK_PERIOD_MULT_2
  *                    @arg @ref FMC_SDRAM_CLOCK_PERIOD_MULT_3
  */
__STATIC_INLINE void FMC_SDRAM_SetClockDivider(FMC_SDRAM_TypeDef *p_instance, uint32_t multiplier)
{
  STM32_MODIFY_REG(p_instance->SDCR[FMC_SDRAM_DEVICE1], FMC_SDCR_SDCLK, (multiplier << FMC_SDCR_SDCLK_Pos));
}

/**
  * @brief  Get the SDRAM clock (SDCLK) in the SDRAM controller.
  * @param  p_instance Pointer to the FMC SDRAM instance.
  * @return SDRAM clock multiplier.
  */
__STATIC_INLINE uint32_t FMC_SDRAM_GetClockDivider(const FMC_SDRAM_TypeDef *p_instance)
{
  return (STM32_READ_BIT(p_instance->SDCR[FMC_SDRAM_DEVICE1], FMC_SDCR_SDCLK) >> FMC_SDCR_SDCLK_Pos);
}

/**
  * @brief  Disable the SDRAM clock (SDCLK) in the SDRAM controller.
  * @param  p_instance Pointer to the FMC SDRAM instance.
  */
__STATIC_INLINE void FMC_SDRAM_DisableSDCLK(FMC_SDRAM_TypeDef *p_instance)
{
  STM32_CLEAR_BIT(p_instance->SDCR[FMC_SDRAM_DEVICE1], FMC_SDCR_SDCLK_Msk);
}

/**
  * @brief  Check if SDRAM clock is enabled or not.
  * @param  p_instance Pointer to the FMC SDRAM instance.
  * @return SDRAM clock status
  */
__STATIC_INLINE uint32_t FMC_SDRAM_IsEnabledSDCLK(const FMC_SDRAM_TypeDef *p_instance)
{
  return ((STM32_READ_BIT(p_instance->SDCR[FMC_SDRAM_DEVICE1], FMC_SDCR_SDCLK_Msk) != 0U) ? 1U : 0U);
}

/**
  * @brief  Calculate the SDRAM clock frequency in Hz.
  * @param  source_clk_freq_hz The source clock frequency in Hz.
  * @param  clk_div            The SDRAM clock divider.
  * @return uint32_t           SDRAM clock frequency in Hz.
  */
__STATIC_INLINE uint32_t FMC_SDRAM_CalculateClockFrequency(uint32_t source_clk_freq_hz, uint32_t clk_div)
{
  return ((clk_div != 0U) ? ((uint32_t)(source_clk_freq_hz / clk_div)) : 0UL);
}

/**
  * @brief Check whether or not the specified FMC SDRAM flag is set.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param flag       Specify the SDRAM flag to check.
  *                   This parameter must be one of the following values:
  *                     @arg @ref FMC_SDRAM_FLAG_CLEAR_REFRESH_ERROR : Refresh error clear interruption flag
  *                     @arg @ref FMC_SDRAM_FLAG_REFRESH_ERROR : Refresh error flag
  * @retval The state of SDRAM flag (0 or 1)
  */
__STATIC_INLINE uint32_t FMC_SDRAM_IsActiveFlag(const FMC_SDRAM_TypeDef *p_instance, uint32_t flag)
{
  return (uint32_t)((STM32_READ_BIT(p_instance->SDSR, flag) == flag) ? 1UL : 0UL);
}

/**
  * @brief Clear the specified FMC SDRAM flags.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param flag       Specify the SDRAM flag to check.
  *                   This parameter must be one of the following values:
  *                     @arg @ref FMC_SDRAM_FLAG_CLEAR_REFRESH_ERROR : Refresh error clear interruption flag
  */
__STATIC_INLINE void FMC_SDRAM_ClearFlag(FMC_SDRAM_TypeDef *p_instance, uint32_t flag)
{
  STM32_SET_BIT(p_instance->SDRTR, flag);
}

/**
  * @brief Enable the refresh error FMC SDRAM interrupt.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param it_source  Specify the SDRAM interrupt to enable.
  *                   This parameter can be the following value:
  *                   @arg @ref FMC_SDRAM_IT_REFRESH_ERROR : Interrupt enable for refresh error
  */
__STATIC_INLINE void FMC_SDRAM_EnableIT(FMC_SDRAM_TypeDef *p_instance, uint32_t it_source)
{
  STM32_SET_BIT(p_instance->SDRTR, it_source);
}

/**
  * @brief Disable the refresh error FMC SDRAM interrupt.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param it_source  Specify the SDRAM interrupt to enable.
  *                   This parameter can be the following value:
  *                   @arg @ref FMC_SDRAM_IT_REFRESH_ERROR : Interrupt enable for refresh error
  */
__STATIC_INLINE void FMC_SDRAM_DisableIT(FMC_SDRAM_TypeDef *p_instance, uint32_t it_source)
{
  STM32_CLEAR_BIT(p_instance->SDRTR, it_source);
}

/**
  * @brief Check whether or not the specified SDRAM interrupt is enabled.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param it_source  Specify the SDRAM interrupt to enable.
  *                   This parameter can be the following value:
  *                   @arg @ref FMC_SDRAM_IT_REFRESH_ERROR : Interrupt enable for refresh error
  * @retval The state of SDRAM interrupt (0 or 1)
  */
__STATIC_INLINE uint32_t FMC_SDRAM_IsEnabledIT(const FMC_SDRAM_TypeDef *p_instance, uint32_t it_source)
{
  return (uint32_t)((STM32_READ_BIT(p_instance->SDRTR, it_source) == it_source) ? 1UL : 0UL);
}
#endif /* FMC_SDRAM_BK5 */

#if defined (FMC_NAND_BK)
/**
  * @brief  Enable the NAND device.
  * @param  p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NAND_Enable(FMC_NAND_TypeDef *p_instance)
{
  STM32_SET_BIT(p_instance->PCR, FMC_PCR_PBKEN);
}

/**
  * @brief  Disable the NAND device.
  * @param  p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NAND_Disable(FMC_NAND_TypeDef *p_instance)
{
  STM32_CLEAR_BIT(p_instance->PCR, FMC_PCR_PBKEN);
}

/**
  * @brief  Get the NAND device status.
  * @param  p_instance Pointer to the device instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FMC_NAND_IsEnabled(const FMC_NAND_TypeDef *p_instance)
{
  return ((STM32_READ_BIT(p_instance->PCR, FMC_PCR_PBKEN) == FMC_PCR_PBKEN) ? 1UL : 0UL);
}

#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC== 1U)
/**
  * @brief  Enable the NAND ECC feature.
  * @param  p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NAND_ECC_Enable(FMC_NAND_TypeDef *p_instance)
{
  STM32_SET_BIT(p_instance->PCR, FMC_PCR_ECCEN);
}

/**
  * @brief  Disable the NAND ECC feature.
  * @param  p_instance Pointer to the device instance.
  */
__STATIC_INLINE void FMC_NAND_ECC_Disable(FMC_NAND_TypeDef *p_instance)
{
  STM32_CLEAR_BIT(p_instance->PCR, FMC_PCR_ECCEN);
}

/**
  * @brief  Get the NAND ECC feature status.
  * @param  p_instance Pointer to the device instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FMC_NAND_ECC_IsEnabled(const FMC_NAND_TypeDef *p_instance)
{
  return ((STM32_READ_BIT(p_instance->PCR, FMC_PCR_ECCEN) == FMC_PCR_ECCEN) ? 1UL : 0UL);
}
#endif /* USE_HAL_NAND_ECC */

/**
  * @brief Calculate Chunk size for the NAND.
  * @param  chunk_size Chunk size.
  * @return The calculated chunk size.
  */
__STATIC_INLINE uint16_t FMC_NAND_CalculateChunkSize(uint32_t chunk_size)
{
  return (uint16_t)((uint16_t)1U << (uint16_t)(8U + (uint16_t)((chunk_size >> FMC_PCR_ECCPS_Pos) & 0x7U)));
}

/**
  * @brief  Check whether the selected NAND device flag is set or not.
  * @param  p_instance Pointer to NAND instance.
  * @param  flag       Specifies the NAND device flag to check.
  *                    This parameter must be set to any combination of the following values:
  *                    @arg FMC_NAND_FLAG_FIFO_EMPTY : FIFO empty flag.
  * @retval The state of flag (SET or RESET).
  */
__STATIC_INLINE uint32_t FMC_NAND_IsActiveFlag(const FMC_NAND_TypeDef *p_instance, uint32_t flag)
{
  return ((STM32_READ_BIT(p_instance->SR, flag) == flag) ? 1U : 0U);
}

/**
  * @brief  Check if Hamming ECC is ready.
  * @param  p_instance Pointer to the device instance.
  * @retval The state of FMC_FLAG_FIFO_EMPTY flag.
  */
__STATIC_INLINE uint32_t FMC_NAND_IsECCHammingReady(const FMC_NAND_TypeDef *p_instance)
{
  return (((p_instance->SR & FMC_SR_FEMPT) == FMC_SR_FEMPT) ? 1U : 0U);
}

/**
  * @brief  Read and reconstruct the Hamming ECC value from a raw byte buffer.
  * @param  p_ecc     Pointer to the buffer containing the ECC bytes as stored in OOB.
  * @return uint32_t  Reconstructed 32-bit Hamming ECC value.
  */
__STATIC_INLINE uint32_t FMC_NAND_ECC_ReadHamming(const uint8_t *p_ecc)
{
  uint32_t ecc = 0U;

  for (uint32_t i = 0U; i < FMC_NAND_ECC_HAMMING_SIZE_BYTE; i++)
  {
    /* Pack each ECC byte into its corresponding position in the 32-bit value */
    ecc |= ((uint32_t)p_ecc[i] << (8U * i));
  }

  return ecc;
}


/**
  * @brief  Get the NAND ECC computation value.
  * @param  p_instance Pointer to the device instance.
  * @retval ECC computed value.
  */
__STATIC_INLINE uint32_t FMC_NAND_ECC_GetHammingValue(const FMC_NAND_TypeDef *p_instance)
{
  return (STM32_READ_REG(p_instance->ECCR));
}


/**
  * @brief  Send an address byte to the NAND device.
  * @param  p_instance Pointer to the device instance.
  * @param  addr       Address byte to be sent.
  */
__STATIC_INLINE void FMC_NAND_WriteAddress(const FMC_NAND_TypeDef *p_instance, uint8_t addr)
{
  uint32_t device_addr = (uint32_t)FMC_NAND_DEVICE_ADDRESS(p_instance);
  volatile uint8_t *p_addr = (volatile uint8_t *)(device_addr | (uint32_t)FMC_NAND_ADDR_AREA);

  *p_addr = addr;
  __DSB();
}

/**
  * @brief  Send a command to the NAND memory's common command space.
  * @param  p_instance Pointer to the device instance.
  * @param  cmd        NAND command to be sent.
  */
__STATIC_INLINE void FMC_NAND_SendCommonCommand(const FMC_NAND_TypeDef *p_instance, uint8_t cmd)
{
  uint32_t device_addr = (uint32_t)FMC_NAND_DEVICE_ADDRESS(p_instance);
  volatile uint8_t *p_cmd = (volatile uint8_t *)(device_addr | (uint32_t)FMC_NAND_CMD_AREA);

  *p_cmd = cmd;
  __DSB();
}

/**
  * @brief  Perform dummy reads from the NAND device buffer.
  * @param  p_instance Pointer to the device instance.
  * @param  length     Number of bytes to read and discard.
  */
__STATIC_INLINE void FMC_NAND_DummyRead(const FMC_NAND_TypeDef *p_instance, uint16_t length)
{
  const volatile uint8_t *const p_data = (const volatile uint8_t *)((uint32_t)(FMC_NAND_DEVICE_ADDRESS(p_instance)));

  for (uint16_t i = 0U; i < length; i++)
  {
    (void)*p_data;
  }
}
#endif /* FMC_NAND_BK */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup FMC_Core_Exported_Functions FMC Core Exported Functions
  *  @{
  */
#if defined (FMC_NORSRAM_BK1)
void FMC_NOR_SRAM_SetConfig(FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t config);
void FMC_NOR_SRAM_GetConfig(const FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t *p_config);
void FMC_NOR_SRAM_SetConfigMemory(FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t control_cfg, uint32_t timing_cfg);
void FMC_NOR_SRAM_GetConfigMemory(const FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t *p_control_cfg,
                                  uint32_t *p_timing_cfg);
void FMC_NOR_SRAM_SetClock(uint32_t clock_cfg, uint32_t clock_div_cfg);
void FMC_NOR_SRAM_SetWrTiming(FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t rd_access_mode, uint32_t wr_timing_cfg);
void FMC_NOR_SRAM_GetWrTiming(const FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t *p_rd_access_mode,
                              uint32_t *p_wr_timing_cfg);
uint32_t FMC_NOR_SRAM_GetRegionBaseAddress(void);
#endif /* defined(FMC_NORSRAM_BK1) */
#if defined (FMC_SDRAM_BK5)
void FMC_SDRAM_SetConfig(FMC_SDRAM_TypeDef *p_instance, uint32_t control_cfg, uint32_t timing_cfg);
void FMC_SDRAM_GetConfig(const FMC_SDRAM_TypeDef *p_instance, uint32_t *p_control_cfg, uint32_t *p_timing_cfg);
void FMC_SDRAM_SetConfigMemory(FMC_SDRAM_TypeDef *p_instance, uint32_t device, uint32_t memory_cfg,
                               uint32_t timing_cfg);
void FMC_SDRAM_GetConfigMemory(const FMC_SDRAM_TypeDef *p_instance, uint32_t device, uint32_t *p_memory_cfg,
                               uint32_t *p_timing_cfg);
void FMC_SDRAM_SendCommand(FMC_SDRAM_TypeDef *p_instance, uint32_t command_cfg);
uint32_t FMC_SDRAM_AdjustRefreshPeriodCycle(uint32_t refresh_period_ms, uint32_t source_clk_freq_hz, uint32_t row_nb);
void FMC_SDRAM_SetRefreshRate(FMC_SDRAM_TypeDef *p_instance, uint32_t refresh_rate_cycle);
uint32_t FMC_SDRAM_GetRefreshRate(const FMC_SDRAM_TypeDef *p_instance);
uint32_t FMC_SDRAM_GetDeviceMode(const FMC_SDRAM_TypeDef *p_instance, uint32_t device);
uint32_t FMC_SDRAM_GetDeviceBaseAddress(uint32_t device);
#endif /* FMC_SDRAM_BK5 */
#if defined (FMC_NAND_BK)
void FMC_NAND_SetConfig(FMC_NAND_TypeDef *p_instance, uint32_t config);
void FMC_NAND_GetConfig(const FMC_NAND_TypeDef *p_instance, uint32_t *p_config);
void FMC_NAND_SetConfigMemory(FMC_NAND_TypeDef *p_instance, uint32_t memory_cfg, uint32_t timing_cfg);
void FMC_NAND_GetConfigMemory(const FMC_NAND_TypeDef *p_instance, uint32_t *p_memory_cfg, uint32_t *p_timing_cfg);
void FMC_NAND_SetLastWriteAccessTiming(FMC_NAND_TypeDef *p_instance, uint32_t attribute_timing_cfg);
void FMC_NAND_GetLastWriteAccessTiming(const FMC_NAND_TypeDef *p_instance, uint32_t *p_attribute_timing_cfg);
void FMC_NAND_ReadFromDevice(FMC_NAND_TypeDef *p_instance, void *p_data, uint32_t size_byte);
void FMC_NAND_WriteToDevice(FMC_NAND_TypeDef *p_instance, const void *p_data, uint32_t size_byte);
void FMC_NAND_ECC_ChunkRead(FMC_NAND_TypeDef *p_instance, uint32_t chunk_offset, void *p_data,
                            uint32_t chunk_size);
void FMC_NAND_ECC_ChunkProgram(FMC_NAND_TypeDef *p_instance, uint32_t chunk_offset,
                               const void *p_data, uint32_t chunk_size);
#endif /* FMC_NAND_BK */
/**
  * @}
  */

/**
  * @}
  */
#endif /* FMC_BASE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_FMC_CORE_H */
