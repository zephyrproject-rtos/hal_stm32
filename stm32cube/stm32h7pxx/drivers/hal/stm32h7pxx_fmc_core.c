/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_fmc_core.c
  * @brief   FMC Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following functionalities of the Flexible Memory
  *          Controller (FMC):
  *           - Set the FMC registers configuration functions
  *           - Retrieve the FMC registers configuration functions
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
#include "stm32h7pxx_fmc_core.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

#if defined (FMC_BASE)

/** @defgroup FMC_Core_Private_Constants FMC Core Private Constants
  * @{
  */
#if defined (FMC_NORSRAM_BK1)
/* BCR register configuration mask for static config */
#define BCR_CFG_MSK (FMC_BCRx_MBKEN   | FMC_BCRx_MUXEN     | FMC_BCRx_MTYP    | FMC_BCRx_MWID     | FMC_BCRx_FACCEN  \
                     | FMC_BCRx_BURSTEN | FMC_BCRx_WAITPOL   | FMC_BCRx_WAITCFG | FMC_BCRx_WREN     | FMC_BCRx_WAITEN  \
                     | FMC_BCRx_EXTMOD  | FMC_BCRx_ASYNCWAIT | FMC_BCRx_CPSIZE  | FMC_BCRx_CBURSTRW | FMC_BCR1_CCLKEN  \
                     | FMC_BCR1_WFDIS)

/* BCR register configuration mask for memory config*/
#define MEM_CFG_MSK (FMC_BCRx_MWID    | FMC_BCRx_CPSIZE | FMC_BCRx_MUXEN   | FMC_BCRx_ASYNCWAIT | FMC_BCRx_WAITEN  \
                     | FMC_BCRx_WAITCFG | FMC_BCR1_CCLKEN | FMC_BCRx_BURSTEN | FMC_BCRx_CBURSTRW)

/* BWTR register configuration mask */
#define BWTR_CFG_MASK (FMC_BWTRx_ADDSET | FMC_BWTRx_ADDHLD | FMC_BWTRx_DATAST | FMC_BWTRx_BUSTURN | FMC_BWTRx_ACCMOD)
#endif /* defined(FMC_NORSRAM_BK1) */

/* Clock div bitfield shift */
#define FMC_CLKDIV_SHIFT (4U)

#if defined (FMC_SDRAM_BK5)
/* SDTR register configuration mask */
#define SDTR_CFG_MASK (FMC_SDTR_TMRD | FMC_SDTR_TXSR | FMC_SDTR_TRAS | FMC_SDTR_TWR | FMC_SDTR_TRCD)

/* SDCMR register command configuration mask */
#define SDCMR_CFG_MASK  (FMC_SDCMR_MODE | FMC_SDCMR_CTB2 | FMC_SDCMR_CTB1 | FMC_SDCMR_NRFS | FMC_SDCMR_MRD)

/* SDCR register memory configuration mask */
#define SDCR_CFG_MASK   (FMC_SDCR_NC | FMC_SDCR_NR | FMC_SDCR_MWID | FMC_SDCR_NB | FMC_SDCR_CAS | FMC_SDCR_WP)

/* SDRAM minimum refresh rate in clock cycles */
#define FMC_SDRAM_REFRESH_RATE_MIN_CYCLE (41U)
#endif /* FMC_SDRAM_BK5 */

#if defined (FMC_NAND_BK)
/* PCR register configuration mask */
#define PCR_CFG_MASK (FMC_PCR_PWAITEN | FMC_PCR_ECCEN  | FMC_PCR_ECCPS)
/* PCR register configuration mask for memory config */
#define MEM_PCR_CFG_MASK (FMC_PCR_PWID | FMC_PCR_TCLR | FMC_PCR_TAR)
#endif /* FMC_NAND_BK */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup FMC_Core_Exported_Functions
  * @{
This driver contains a set of APIs to interface with the FMC banks in order to run the external devices.
This section provides functions allowing to:
  - Configure the FMC NORSRAM interface
  - Get the FMC NORSRAM interface configuration
  - Configure the FMC SDRAM interface.
  - Get the FMC SDRAM interface configuration.
  - Set the memory configuration per devices.
  - Get the memory configuration per devices.
  - Send command to the FMC SDRAM device.
  - Adjust the timing parameters from nanoseconds to kernel clock cycle number.
  - Set the FMC SDRAM memory refresh rate.
  - Get the FMC SDRAM Memory refresh rate.
  - Get the indicated FMC SDRAM device mode.
  - Configure the FMC NAND interface
  - Get the FMC NAND interface configuration
  */
#if defined (FMC_NORSRAM_BK1)
/**
  * @brief Set the FMC NORSRAM device according to the specified static FMC parameters.
  * @param p_instance Pointer to NORSRAM device instance.
  * @param config     Contains the static FMC configuration information.
  */
void FMC_NOR_SRAM_SetConfig(FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t config)
{
  STM32_MODIFY_REG(p_instance->BCR, BCR_CFG_MSK, (config | FMC_BCRx_WREN));

  /* Configure Write FIFO mode when Write Fifo is enabled for bank2..4 */
  if ((p_instance != FMC_NORSRAM1_SUBBANK1) && ((config & FMC_BCR1_WFDIS) == FMC_WRITE_FIFO_ENABLE))
  {
    STM32_CLEAR_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_WFDIS);
  }
}

/**
  * @brief Retrieve the FMC NORSRAM device static FMC parameters.
  * @param p_instance Pointer to NORSRAM device instance.
  * @param p_config   Contains the static FMC configuration information.
  */
void FMC_NOR_SRAM_GetConfig(const FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t *p_config)
{
  /* Read control register */
  *p_config = STM32_READ_REG(p_instance->BCR);

  /* Check FIFO configuration */
  if (STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_WFDIS) == 0U)
  {
    STM32_CLEAR_BIT(*p_config, FMC_BCR1_WFDIS);
  }
}

/**
  * @brief Set the FMC NORSRAM device according to the specified memory parameters.
  * @param p_instance  Pointer to NORSRAM device instance.
  * @param control_cfg Contains the control configuration information.
  * @param timing_cfg  Contains the timing configuration information.
  */
void FMC_NOR_SRAM_SetConfigMemory(FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t control_cfg, uint32_t timing_cfg)
{
  /* Set configuration mask value */
  STM32_MODIFY_REG(p_instance->BCR, MEM_CFG_MSK, control_cfg);
  STM32_WRITE_REG(p_instance->BTR, timing_cfg);
  STM32_WRITE_REG(p_instance->BWTR, FMC_WR_TIMING_VALUE);
}

/**
  * @brief Retrieve the FMC NORSRAM device memory parameters.
  * @param p_instance    Pointer to NORSRAM device instance.
  * @param p_control_cfg Contains the control configuration information.
  * @param p_timing_cfg  Contains the timing configuration information.
  */
void FMC_NOR_SRAM_GetConfigMemory(const FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t *p_control_cfg,
                                  uint32_t *p_timing_cfg)
{
  /* Read control register */
  *p_control_cfg = STM32_READ_REG(p_instance->BCR);

  /* Check FIFO configuration */
  if (STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_WFDIS) == 0U)
  {
    STM32_CLEAR_BIT(*p_control_cfg, FMC_BCR1_WFDIS);
  }

  /* Read timing register */
  *p_timing_cfg = STM32_READ_REG(p_instance->BTR);

  /* Check continuous clock and clock div configuration */
  if (STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_CCLKEN) == FMC_BCR1_CCLKEN)
  {
    STM32_SET_BIT(*p_control_cfg, FMC_BCR1_CCLKEN);
    STM32_MODIFY_REG(*p_timing_cfg, FMC_BTRx_CLKDIV, STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BTR, FMC_BTRx_CLKDIV));
  }
}

/**
  * @brief Set the FMC NORSRAM device clock configuration.
  * @param clock_cfg     Contains the clock configuration information.
  * @param clock_div_cfg Contains the clock division configuration information.
  */
void FMC_NOR_SRAM_SetClock(uint32_t clock_cfg, uint32_t clock_div_cfg)
{
  /* Configure the continuous clock when Continuous clock is enabled for bank2..4 */
  STM32_SET_BIT(FMC_NORSRAM1_SUBBANK1->BCR, clock_cfg | FMC_BCR1_CCLKEN);

  /* Align the clock div to the lowest frequency when the continuous clock is enabled */
  if (clock_cfg != 0U)
  {
    if (clock_div_cfg > STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BTR, FMC_BTRx_CLKDIV))
    {
      STM32_MODIFY_REG(FMC_NORSRAM1_SUBBANK1->BTR, FMC_BTRx_CLKDIV, clock_div_cfg);
    }
  }
}

/**
  * @brief Set the FMC NORSRAM device according to the specified write timing parameters.
  * @param p_instance     Pointer to NORSRAM device instance.
  * @param rd_access_mode Contains the read access mode information.
  * @param wr_timing_cfg  Contains the write timing configuration information.
  */
void FMC_NOR_SRAM_SetWrTiming(FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t rd_access_mode, uint32_t wr_timing_cfg)
{
  /* Set timing value */
  STM32_SET_BIT(p_instance->BCR, FMC_BCRx_EXTMOD);
  STM32_MODIFY_REG(p_instance->BTR, FMC_BTRx_ACCMOD, rd_access_mode);
  STM32_MODIFY_REG(p_instance->BWTR, BWTR_CFG_MASK, wr_timing_cfg);
}

/**
  * @brief Retrieve the FMC NORSRAM device write timing parameters.
  * @param p_instance       Pointer to NORSRAM device instance.
  * @param p_rd_access_mode Contains the read access mode information.
  * @param p_wr_timing_cfg  Contains the write timing configuration information.
  */
void FMC_NOR_SRAM_GetWrTiming(const FMC_NORSRAM_SUBBANK_TypeDef *p_instance, uint32_t *p_rd_access_mode,
                              uint32_t *p_wr_timing_cfg)
{
  *p_rd_access_mode = STM32_READ_BIT(p_instance->BTR, FMC_BTRx_ACCMOD);
  /* Read write timing register */
  *p_wr_timing_cfg = STM32_READ_REG(p_instance->BWTR);
}

/**
  * @brief Get the NOR SRAM device base address.
  * @return uint32_t NOR SRAM device base address.
  */
uint32_t FMC_NOR_SRAM_GetRegionBaseAddress(void)
{
  uint32_t remap_region = FMC_GetRegionRemap();

  if (remap_region == FMC_SDRAM_DEVICE1_REGION5_NOR_SRAM_REGION1)
  {
    return (FMC_NORSRAM_BK1);
  }
  else
  {
    return (FMC_SDRAM_BK5);
  }
}

#endif /* defined(FMC_NORSRAM_BK1) */

#if defined (FMC_SDRAM_BK5)

/**
  * @brief Set the FMC SDRAM common configuration according to the specified memory parameters.
  * @param p_instance  Pointer to the FMC SDRAM instance.
  * @param control_cfg Contains the common configuration information.
  * @param timing_cfg  Contains the timing configuration information.
  */
void FMC_SDRAM_SetConfig(FMC_SDRAM_TypeDef *p_instance, uint32_t control_cfg, uint32_t timing_cfg)
{
  STM32_MODIFY_REG(p_instance->SDCR[FMC_SDRAM_DEVICE1], (FMC_SDCR_SDCLK_Msk | FMC_SDCR_RPIPE_Msk |
                                                         FMC_SDCR_RBURST_Msk), control_cfg);
  STM32_MODIFY_REG(p_instance->SDTR[FMC_SDRAM_DEVICE1], (FMC_SDTR_TRP | FMC_SDTR_TRC), timing_cfg);
}

/**
  * @brief Retrieve the FMC SDRAM device memory parameters.
  * @param p_instance    Pointer to the FMC SDRAM instance.
  * @param p_control_cfg Contains the common memory configuration information.
  * @param p_timing_cfg  Contains the common timing configuration information.
  */
void FMC_SDRAM_GetConfig(const FMC_SDRAM_TypeDef *p_instance, uint32_t *p_control_cfg, uint32_t *p_timing_cfg)
{
  *p_control_cfg = STM32_READ_REG(p_instance->SDCR[FMC_SDRAM_DEVICE1]);
  *p_timing_cfg  = STM32_READ_REG(p_instance->SDTR[FMC_SDRAM_DEVICE1]);
}

/**
  * @brief Set the FMC SDRAM device according to the specified memory parameters.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param device Specifies the selected device.
  *               This parameter can be only one of the following values:
  *               @arg @ref FMC_SDRAM_DEVICE1
  *               @arg @ref FMC_SDRAM_DEVICE2
  * @param memory_cfg Contains the memory configuration information.
  * @param timing_cfg  Contains the timing configuration information.
  */
void FMC_SDRAM_SetConfigMemory(FMC_SDRAM_TypeDef *p_instance, uint32_t device, uint32_t memory_cfg, uint32_t timing_cfg)
{
  STM32_MODIFY_REG(p_instance->SDCR[device], SDCR_CFG_MASK, memory_cfg);
  STM32_MODIFY_REG(p_instance->SDTR[device], SDTR_CFG_MASK, timing_cfg);
}

/**
  * @brief Retrieve the FMC SDRAM device memory parameters.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param device Specifies the selected device.
  *                This parameter can be only one of the following values:
  *                @arg @ref FMC_SDRAM_DEVICE1
  *                @arg @ref FMC_SDRAM_DEVICE2
  * @param p_memory_cfg Contains the memory configuration information.
  * @param p_timing_cfg  Contains the common timing configuration information.
  */
void FMC_SDRAM_GetConfigMemory(const FMC_SDRAM_TypeDef *p_instance, uint32_t device, uint32_t *p_memory_cfg,
                               uint32_t *p_timing_cfg)
{
  *p_memory_cfg = STM32_READ_REG(p_instance->SDCR[device]);
  *p_timing_cfg = STM32_READ_REG(p_instance->SDTR[device]);
}


/**
  * @brief Send command to the FMC SDRAM device.
  * @param p_instance  Pointer to the FMC SDRAM instance.
  * @param command_cfg Contains the command configuration information.
  */
void FMC_SDRAM_SendCommand(FMC_SDRAM_TypeDef *p_instance, uint32_t command_cfg)
{
  STM32_MODIFY_REG(p_instance->SDCMR, SDCMR_CFG_MASK, command_cfg);
}

/**
  * @brief  Adjust the timing parameters from milliseconds to kernel clock cycle number.
  * @param  refresh_period_ms  The timing parameter in milliseconds.
  * @param  source_clk_freq_hz The clock frequency in Hz.
  * @param  row_nb             The rows number.
  * @return timing parameter in kernel clock cycle number.
  */
uint32_t FMC_SDRAM_AdjustRefreshPeriodCycle(uint32_t refresh_period_ms, uint32_t source_clk_freq_hz, uint32_t row_nb)
{
  uint32_t sdram_refresh_period_cycle;

  sdram_refresh_period_cycle = (uint32_t)FMC_CeilDivU64(((uint64_t)refresh_period_ms * (uint64_t)source_clk_freq_hz),
                                                        ((uint64_t)row_nb * 1000UL));

  /* Check if the SDRAM refresh period is below the minimum allowed refresh cycle count and adjust if necessary */
  if (sdram_refresh_period_cycle < FMC_SDRAM_REFRESH_RATE_MIN_CYCLE)
  {
    sdram_refresh_period_cycle = FMC_SDRAM_REFRESH_RATE_MIN_CYCLE;
  }

  return (sdram_refresh_period_cycle - FMC_SDRAM_REFRESH_RATE_SAFE_MARGIN_CYCLE);
}

/**
  * @brief Set the SDRAM Memory Refresh rate.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param refresh_rate_cycle SDRAM refresh rate value.
  */
void FMC_SDRAM_SetRefreshRate(FMC_SDRAM_TypeDef *p_instance, uint32_t refresh_rate_cycle)
{
  STM32_MODIFY_REG(p_instance->SDRTR, FMC_SDRTR_COUNT, (refresh_rate_cycle << FMC_SDRTR_COUNT_Pos));
}

/**
  * @brief  Get the FMC SDRAM Memory Refresh rate.
  * @param  p_instance Pointer to the FMC SDRAM instance.
  * @return Value of the refresh rate.
  */
uint32_t FMC_SDRAM_GetRefreshRate(const FMC_SDRAM_TypeDef *p_instance)
{
  return (STM32_READ_BIT(p_instance->SDRTR, FMC_SDRTR_COUNT) >> FMC_SDRTR_COUNT_Pos);
}

/**
  * @brief Get the indicated FMC SDRAM device mode.
  * @param p_instance Pointer to the FMC SDRAM instance.
  * @param device Specifies the selected device.
  *                This parameter can be only one of the following values:
  *                @arg @ref FMC_SDRAM_DEVICE1
  *                @arg @ref FMC_SDRAM_DEVICE2
  * @retval The FMC SDRAM device mode, could be one of the following values:
  *         @arg @ref FMC_SDRAM_NORMAL_MODE
  *         @arg @ref FMC_SDRAM_SELF_REFRESH_MODE
  *         @arg @ref FMC_SDRAM_POWER_DOWN_MODE
  */
uint32_t FMC_SDRAM_GetDeviceMode(const FMC_SDRAM_TypeDef *p_instance, uint32_t device)
{
  return ((device == FMC_SDRAM_DEVICE1) ? STM32_READ_BIT(p_instance->SDSR, FMC_SDSR_MODES1) :
          (STM32_READ_BIT(p_instance->SDSR, FMC_SDSR_MODES2) >> 2U));
}

/**
  * @brief Get the SDRAM device base address.
  * @param device    Specifies the selected device.
  *                  This parameter must be one of the following values:
  *                  @arg @ref FMC_SDRAM_DEVICE1
  *                  @arg @ref FMC_SDRAM_DEVICE2
  * @return uint32_t SDRAM device base address.
  */
uint32_t FMC_SDRAM_GetDeviceBaseAddress(uint32_t device)
{
  uint32_t remap_region = FMC_GetRegionRemap();

  if (device == FMC_SDRAM_DEVICE1)
  {
    if (remap_region == FMC_SDRAM_DEVICE1_REGION1_NOR_SRAM_REGION5)
    {
      return (FMC_NORSRAM_BK1);
    }
    return (FMC_SDRAM_BK5);
  }
  else
  {
    return (FMC_SDRAM_BK6);
  }
}
#endif /* FMC_SDRAM_BK5 */

#if defined (FMC_NAND_BK)
/**
  * @brief  Set the FMC NAND according to the specified  FMC parameters.
  * @param  p_instance Pointer to NAND instance.
  * @param  config     Contains the FMC configuration information.
  */
void FMC_NAND_SetConfig(FMC_NAND_TypeDef *p_instance, uint32_t config)
{
  STM32_MODIFY_REG(p_instance->PCR, PCR_CFG_MASK, config);
}

/**
  * @brief  Retrieve the FMC NAND configuration.
  * @param  p_instance  Pointer to NAND instance.
  * @param  p_config    Contains the FMC configuration information.
  */
void FMC_NAND_GetConfig(const FMC_NAND_TypeDef *p_instance, uint32_t *p_config)
{
  *p_config = STM32_READ_REG(p_instance->PCR);
}

/**
  * @brief  Set the FMC NAND according to the specified memory parameters.
  * @param  p_instance Pointer to NAND instance.
  * @param  memory_cfg Contains the memory configuration information.
  * @param  timing_cfg Contains the timing configuration information.
  */
void FMC_NAND_SetConfigMemory(FMC_NAND_TypeDef *p_instance, uint32_t memory_cfg, uint32_t timing_cfg)
{
  /* Set configuration mask value */
  STM32_MODIFY_REG(p_instance->PCR, MEM_PCR_CFG_MASK, memory_cfg);
  STM32_WRITE_REG(p_instance->PMEM, timing_cfg);
  STM32_WRITE_REG(p_instance->PATT, timing_cfg);
}

/**
  * @brief  Retrieve the FMC NAND device memory parameters.
  * @param  p_instance   Pointer to NAND device instance.
  * @param  p_memory_cfg Contains the memory configuration information.
  * @param  p_timing_cfg Contains the timing configuration information.
  */
void FMC_NAND_GetConfigMemory(const FMC_NAND_TypeDef *p_instance, uint32_t *p_memory_cfg, uint32_t *p_timing_cfg)
{
  *p_memory_cfg = STM32_READ_REG(p_instance->PCR);
  *p_timing_cfg = STM32_READ_REG(p_instance->PMEM);
}

/**
  * @brief  Set the FMC NAND device according to the specified timing parameters.
  * @param  p_instance           Pointer to NAND device instance.
  * @param  attribute_timing_cfg Contains the attribute timing configuration information.
  */

void FMC_NAND_SetLastWriteAccessTiming(FMC_NAND_TypeDef *p_instance, uint32_t attribute_timing_cfg)
{
  STM32_WRITE_REG(p_instance->PATT, attribute_timing_cfg);
}

/**
  * @brief  Get the FMC NAND device according to the specified timing parameters.
  * @param  p_instance             Pointer to NAND device instance.
  * @param  p_attribute_timing_cfg Contains the attribute timing configuration information.
  */
void FMC_NAND_GetLastWriteAccessTiming(const FMC_NAND_TypeDef *p_instance, uint32_t *p_attribute_timing_cfg)
{
  *p_attribute_timing_cfg = STM32_READ_REG(p_instance->PATT);
}

/**
  * @brief  Write data to the NAND device buffer.
  * @param  p_instance Pointer to NAND instance.
  * @param  p_data    Pointer to the data buffer to be written to the NAND device.
  * @param  size_byte Number of bytes to write.
  */
void FMC_NAND_WriteToDevice(FMC_NAND_TypeDef *p_instance, const void *p_data, uint32_t size_byte)
{
  const uint8_t *p_tmp_data = (const uint8_t *)p_data;
  volatile uint16_t data16;
  uint32_t index = 0U;
  uint32_t remaining_bytes = size_byte;

  if (remaining_bytes >= 4U)
  {
    uint32_t remaining_bytes32 = (remaining_bytes >> 2U);
    for (index = 0U; index < remaining_bytes32; index++)
    {
      *(volatile uint32_t *)FMC_NAND_DEVICE_ADDRESS(p_instance) = *(const volatile uint32_t *)(p_tmp_data);
      __DSB();
      p_tmp_data += 4U;
      remaining_bytes -= 4U;
    }
  }

  if (remaining_bytes >= 2U)
  {
    uint32_t remaining_bytes16 = (remaining_bytes >> 1U);
    for (index = 0U; index < remaining_bytes16; index++)
    {
      *(volatile uint16_t *)FMC_NAND_DEVICE_ADDRESS(p_instance) = *(const volatile uint16_t *)(p_tmp_data);
      __DSB();
      p_tmp_data += 2U;
      remaining_bytes -= 2U;
    }
  }

  if (remaining_bytes == 1U)
  {
    data16 = (uint16_t)(*(const volatile uint8_t *)(p_tmp_data)) | ((uint16_t)0xFFU << 8U);
    *(volatile uint16_t *)FMC_NAND_DEVICE_ADDRESS(p_instance) = data16;
    __DSB();
  }
}

/**
  * @brief  Read data from the NAND device buffer.
  * @param  p_instance Pointer to NAND instance.
  * @param  p_data    Pointer to the buffer where read data are stored.
  * @param  size_byte Number of bytes to read.
  */
void FMC_NAND_ReadFromDevice(FMC_NAND_TypeDef *p_instance, void *p_data, uint32_t size_byte)
{
  uint8_t *p_tmp_data = (uint8_t *)p_data;
  uint32_t index = 0U;
  uint32_t remaining_bytes = size_byte;
  if (remaining_bytes >= 4U)
  {
    uint32_t remaining_bytes32 = (remaining_bytes >> 2U);
    for (index = 0U; index < remaining_bytes32; index++)
    {
      *(volatile uint32_t *)p_tmp_data = *(volatile uint32_t *)FMC_NAND_DEVICE_ADDRESS(p_instance);
      __DSB();
      p_tmp_data += 4U;
      remaining_bytes -= 4U;
    }
  }

  if (remaining_bytes >= 2U)
  {
    uint32_t remaining_bytes16 = (remaining_bytes >> 1U);
    for (index = 0U; index < remaining_bytes16; index++)
    {
      *(volatile uint16_t *)p_tmp_data = *(volatile uint16_t *)FMC_NAND_DEVICE_ADDRESS(p_instance);
      __DSB();
      p_tmp_data += 2U;
      remaining_bytes -= 2U;
    }
  }

  if (remaining_bytes == 1U)
  {
    *(volatile uint8_t *)p_tmp_data = *(volatile uint8_t *)FMC_NAND_DEVICE_ADDRESS(p_instance);
    __DSB();
  }
}

/**
  * @brief  Read data chunk from the NAND device.
  * @param  p_instance   Pointer to NAND instance.
  * @param  chunk_offset The offset in bytes within the page to start reading from.
  * @param  p_data       Pointer to the buffer where read data are stored.
  * @param  chunk_size   Number of bytes to read.
  */
void FMC_NAND_ECC_ChunkRead(FMC_NAND_TypeDef *p_instance, uint32_t chunk_offset, void *p_data,
                            uint32_t chunk_size)
{
  FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_RANDOM_OUTPUT_0);
  FMC_NAND_WriteAddress(p_instance, FMC_NAND_COLUMN_1ST_CYCLE(chunk_offset));
  FMC_NAND_WriteAddress(p_instance, FMC_NAND_COLUMN_2ND_CYCLE(chunk_offset));
  FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_RANDOM_OUTPUT_1);
  FMC_NAND_ReadFromDevice(p_instance, p_data, chunk_size);
}

/**
  * @brief  Program data chunk to the NAND device.
  * @param  p_instance   Pointer to NAND instance.
  * @param  chunk_offset The offset in bytes within the page to start writing to.
  * @param  p_data       Pointer to the buffer where data to be written is stored.
  * @param  chunk_size   Number of bytes to write.
  */
void FMC_NAND_ECC_ChunkProgram(FMC_NAND_TypeDef *p_instance, uint32_t chunk_offset,
                               const void *p_data, uint32_t chunk_size)
{
  FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_RANDOM_INPUT);
  FMC_NAND_WriteAddress(p_instance, FMC_NAND_COLUMN_1ST_CYCLE(chunk_offset));
  FMC_NAND_WriteAddress(p_instance, FMC_NAND_COLUMN_2ND_CYCLE(chunk_offset));
  FMC_NAND_WriteToDevice(p_instance, p_data, chunk_size);
}

#endif /* FMC_NAND_BK */
/**
  * @}
  */
#endif /* FMC_BASE */

/**
  * @}
  */
