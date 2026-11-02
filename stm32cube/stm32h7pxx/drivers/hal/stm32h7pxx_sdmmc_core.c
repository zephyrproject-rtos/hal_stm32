/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_sdmmc_core.c
  * @brief   SDMMC core driver module.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the SDMMC peripheral:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
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

/** @addtogroup SDMMC_CORE
  * @{
# SDMMC peripheral features :
The SD/MMC card host interface (SDMMC) provides an interface between the AHB peripheral bus and MultiMedia
cards (MMCs), SD memory cards, SDMMC cards and CE-ATA devices.

# The SDMMC features include the following :
- Full compliance with MultiMediaCard System Specification Version 4.51. Card support for three different
  databus modes: 1-bit (default), 4-bit and 8-bit.
- Full compatibility with previous versions of MultiMediaCards (backward compatibility).
- Full compliance with SD memory card specifications version 4.1. (SDR104 SDMMC_CK speed limited to maximum allowed
  IO speed, SPI mode and UHS-II mode not supported).
- Full compliance with SDIO card specification version 4.0. Card support for two different databus modes:
  1-bit (default) and 4-bit. (SDR104 SDMMC_CK speed limited to maximum allowed IO speed,
  SPI mode and UHS-II mode not supported).
- Data transfer up to 208 Mbyte/s for the 8 bit mode (depending maximum allowed IO speed).
- Data and command output enable signals to control external bidirectional drivers

# How to use this driver :

## This driver is a considered as a driver of service for external devices drivers that interfaces with the SDMMC
peripheral. According to the device used (SD card/ MMC card / SDMMC card ...), a set of APIs is used in the device's
driver to perform SDMMC operations and functionalities.

This driver is almost transparent for the final user, it is only used to implement other functionalities of the external
device.

The SDMMC clock is coming from output of PLL1_Q or PLL2_R.
Before start working with SDMMC peripheral make sure that the PLL is well configured.
The SDMMC peripheral uses two clock signals:
- PLL1_Q bus clock (default after reset)
- PLL2_R bus clock

Enable/Disable peripheral clock using RCC peripheral macros related to SDMMC peripheral.

- Enable the Power ON State using the SDMMC_PowerState_ON(sdmmcx) function and disable it using the function
  SDMMC_PowerState_OFF(sdmmcx).

- Enable/Disable the peripheral interrupts using the macros SDMMC_ENABLE_IT(hSDMMC, IT) and
  SDMMC_DISABLE_IT(hSDMMC, IT) if you need to use interrupt mode.

- When using the DMA mode
    - Configure the IDMA mode (Single buffer or double)
    - Configure the buffer address
    - Configure Data Path State Machine

- To control the CPSM (Command Path State Machine) and send
    commands to the card use the SDMMC_SendCommand(sdmmcx),
    SDMMC_GetCommandResponse() and SDMMC_GetResponse() functions. First, user has
    to fill the command structure (pointer to sdmmc_cmd_init_t) according
    to the selected command to be sent.
    The parameters that must be filled are:
     - Command argument
     - Command Index
     - Command Response type
     - Command Wait
     - CPSM Status (Enable or Disable).

    To check if the command is well received, read the SDMMC_CMDRESP register using the SDMMC_GetCommandResponse().
      The SDMMC responses registers (SDMMC_RESP1 to SDMMC_RESP2), use the SDMMC_GetResponse() function.

- To control the DPSM (Data Path State Machine) and send/receive data to/from the card use the SDMMC_DataConfig(),
  SDMMC_GetDataCounter(), SDMMC_ReadFIFO(), SDMMC_WriteFIFO() and SDMMC_GetFIFOCount() functions.

- Read Operations :
   - First, user has to fill the data structure (pointer to sdmmc_data_init_t) according
     to the selected data type to be received.
     The parameters that must be filled are:
        - Data TimeOut
        - Data Length
        - Data Block size
        - Data Transfer direction: must be from card (To SDMMC)
        - Data Transfer mode
        - DPSM Status (Enable or Disable)
   - Configure the SDMMC resources to receive the data from the card according to selected transfer mode.
   - Send the selected Read command.
   - Use the SDMMC flags/interrupts to check the transfer status.

- Write Operations :
     - First, user has to fill the data structure (pointer to sdmmc_data_init_t) according to the selected data type
       to be received.
       The parameters that must be filled are:
          - Data TimeOut
          - Data Length
          - Data Block size
          - Data Transfer direction:  must be to card (To CARD)
          - Data Transfer mode
          - DPSM Status (Enable or Disable)
     - Configure the SDMMC resources to send the data to the card according to selected transfer mode.
     - Send the selected Write command.
     - Use the SDMMC flags/interrupts to check the transfer status.

- Command management operations :
     - The commands used for Read/Write/Erase operations are managed in separate functions.
         Each function allows to send the needed command with the related argument, then check the response.
         By the same approach, you could implement a command and check the response.
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_sdmmc_core.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @addtogroup SDMMC_CORE SDMMC Core
  * @{
  */
#if defined(SDMMC1)

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------------------------------------------*/
#ifndef NULL
#define NULL ((void *)0U)
#endif /* NULL */
/* Private macro -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** @defgroup SDMMC_CORE_Private_Functions SDMMC CORE Private Functions
  * @{
  */
static uint32_t SDMMC_WaitFlagUntilTimeout(const SDMMC_TypeDef *sdmmcx, uint32_t flag_mask, uint32_t timeout_ms);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup SDMMC_CORE_Exported_Functions SDMMC Core Exported Functions
  * @{
  */

/** @addtogroup SDMMC_CORE_Group1 Set and Get Configurations functions
  * @{
This section provides functions allowing to Get and Set the SDMMC configuration:
- Call the function SDMMC_GetConfig() to get the sdmmc configuration.
- Call the function SDMMC_SetConfig() to set the sdmmc configuration.
  */
/**
  * @brief Get the SDMMC config according to the specified parameters.
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param p_config Pointer to SDMMC configuration.
  */
void SDMMC_GetConfig(const SDMMC_TypeDef *sdmmcx, sdmmc_config_t *p_config)
{
  p_config->clk.clock_div         = (sdmmcx->CLKCR & SDMMC_CLKCR_CLKDIV);
  p_config->clk.clock_edge        = (sdmmcx->CLKCR & SDMMC_CLKCR_NEGEDGE);
  p_config->clk.clock_power_save  = (sdmmcx->CLKCR & SDMMC_CLKCR_PWRSAV);
  p_config->bus_wide              = (sdmmcx->CLKCR & SDMMC_CLKCR_WIDBUS);
  p_config->hardware_flow_control = (sdmmcx->CLKCR & SDMMC_CLKCR_HWFC_EN);
}

/**
  * @brief Set the SDMMC config according to the specified parameters in the sdmmc_config_t.
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param p_config Pointer to SDMMC configuration structure.
  */
void SDMMC_SetConfig(SDMMC_TypeDef *sdmmcx, const sdmmc_config_t *p_config)
{
  if (p_config->tranceiver_present == SDMMC_TRANSCEIVER_PRESENT)
  {
    /* Set transceiver polarity */
    sdmmcx->POWER |= SDMMC_POWER_DIRPOL;
  }

  STM32_MODIFY_REG(sdmmcx->CLKCR, CLKCR_CLEAR_MASK, (p_config->clk.clock_edge | p_config->clk.clock_power_save \
                                                     | p_config->bus_wide | p_config->hardware_flow_control    \
                                                     | p_config->clk.clock_div));
}
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Group2 Peripheral Control functions
  * @{
    This subsection provides a set of functions allowing to control the SDMMC data transfers.
  */
/**
  * @brief Configure the SDMMC command path according to the specified parameters in sdmmc_cmd_init_t structure
  *        and send the command.
  * @param sdmmcx    Pointer to SDMMC register base.
  * @param p_command Pointer to a sdmmc_cmd_init_t structure.
  */
void SDMMC_SendCommand(SDMMC_TypeDef *sdmmcx, const sdmmc_cmd_init_t *p_command)
{
  sdmmcx->ARGR = p_command->argument;
  STM32_MODIFY_REG(sdmmcx->CMDR, CMD_CLEAR_MASK,
                   (p_command->cmd_index | p_command->response | p_command->wait_for_interrupt \
                    | p_command->cpsm));
}

/**
  * @brief Configure the SDMMC data path according to the specified parameters in the sdmmc_data_ctrl_t.
  * @param sdmmcx      Pointer to SDMMC register base.
  * @param p_data_ctrl Pointer to a sdmmc_data_ctrl_t structure that contains the configuration information
  *                    for the SDMMC data.
  */
void SDMMC_ConfigData(SDMMC_TypeDef *sdmmcx, const sdmmc_data_ctrl_t *p_data_ctrl)
{
  sdmmcx->DTIMER = p_data_ctrl->data_timeout;
  sdmmcx->DLENR = p_data_ctrl->data_length;
  STM32_MODIFY_REG(sdmmcx->DCTRL, DCTRL_CLEAR_MASK, (p_data_ctrl->data_block_size | p_data_ctrl->transfer_dir \
                                                     | p_data_ctrl->transfer_mode | p_data_ctrl->dpsm));
}
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Group3 SDMMC Commands management and Data transfers functions
  * @{
This subsection provides a set of functions allowing to manage the needed commands.
  */
/**
  * @brief Send the Data Block Length command and check the response.
  * @param sdmmcx     Pointer to SDMMC register base.
  * @param block_size Block size to configure.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendBlockLengthCmd(SDMMC_TypeDef *sdmmcx, uint32_t block_size)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = block_size;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SET_BLOCKLEN;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_SET_BLOCKLEN, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the Block count command and check the response.
  * @param SDMMCx      Pointer to SDMMC register base.
  * @param block_count Block count.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendBlockCountCmd(SDMMC_TypeDef *SDMMCx, uint32_t block_count)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t errorstate;

  /* Set Block Size for Card */
  sdmmc_cmdinit.argument           = (uint32_t)block_count;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SET_BLOCK_COUNT;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(SDMMCx, &sdmmc_cmdinit);

  /* Check for error conditions */
  errorstate = SDMMC_GetCmdResp1(SDMMCx, SDMMC_CMD_SET_BLOCK_COUNT, SDMMC_CMD_TIMEOUT);

  return errorstate;
}

/**
  * @brief Send the Read Single/Multi Block command and check the response.
  * @param sdmmcx        Pointer to SDMMC register base.
  * @param read_addr     Address from where data is to be read.
  * @param read_blk_type Type of read iteration (Single or Multiple type).
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendReadBlocksCmd(SDMMC_TypeDef *sdmmcx, uint32_t read_addr, uint32_t read_blk_type)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = read_addr;
  sdmmc_cmdinit.cmd_index          = read_blk_type;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, (uint8_t)read_blk_type, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the Write Single/Multi Block command and check the response.
  * @param sdmmcx         Pointer to SDMMC register base.
  * @param write_addr     Address from where data is to be written.
  * @param write_blk_type Type of write iteration (Single or Multiple type).
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendWriteBlocksCmd(SDMMC_TypeDef *sdmmcx, uint32_t write_addr, uint32_t write_blk_type)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = write_addr;
  sdmmc_cmdinit.cmd_index          = write_blk_type;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, (uint8_t)write_blk_type, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the Start Address Erase command and check the response.
  * @param sdmmcx           Pointer to SDMMC register base.
  * @param start_addr       Start Block address.
  * @param cmd_erase        Command of erase type.
  * @param erase_timeout_ms Erase timeout value.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendEraseCmd(SDMMC_TypeDef *sdmmcx, uint32_t start_addr, uint32_t cmd_erase, uint32_t erase_timeout_ms)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = start_addr;
  sdmmc_cmdinit.cmd_index          = cmd_erase;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, (uint8_t)cmd_erase, erase_timeout_ms);

  return error_code;
}

/**
  * @brief Send the Stop Transfer command and check the response.
  * @param sdmmcx                   Pointer to SDMMC register base.
  * @param stop_transfer_timeout_ms Stop transfer timeout duration.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendStopTransferCmd(SDMMC_TypeDef *sdmmcx, uint32_t stop_transfer_timeout_ms)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = 0U;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_STOP_TRANSMISSION;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;

  SDMMC_CMDSTOP_ENABLE(sdmmcx);
  SDMMC_CMDTRANS_DISABLE(sdmmcx);
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);
  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_STOP_TRANSMISSION, stop_transfer_timeout_ms);
  SDMMC_CMDSTOP_DISABLE(sdmmcx);

  /* Ignore Address Out Of Range Error, not relevant at end of memory */
  if (error_code == SDMMC_ERROR_ADDR_OUT_OF_RANGE)
  {
    error_code = SDMMC_ERROR_NONE;
  }

  return error_code;
}

/**
  * @brief Send the Select Deselect command and check the response.
  * @param sdmmcx Pointer to SDMMC register base.
  * @param addr   Address of the card to be selected.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendSelDeselCmd(SDMMC_TypeDef *sdmmcx, uint32_t addr)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = addr;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SEL_DESEL_CARD;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_SEL_DESEL_CARD, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the Go Idle State command and check the response.
  * @param sdmmcx Pointer to SDMMC register base.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendGoIdleStateCmd(SDMMC_TypeDef *sdmmcx)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;

  sdmmc_cmdinit.argument           = 0U;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_GO_IDLE_STATE;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_NO;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  /** 8 is the number of required instructions cycles for the below loop statement.
    * The SDMMC_CMD_TIMEOUT is expressed in ms.
    */
  uint32_t count = SDMMC_CMD_TIMEOUT * (SystemCoreClock / 22U / 1000U);

  do
  {
    count--;
    if (count == 0U)
    {
      return SDMMC_ERROR_TIMEOUT;
    }

  } while (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CMDSENT) == 0U);

  SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_STATIC_CMD_FLAGS);

  return SDMMC_ERROR_NONE;
}

/**
  * @brief  Send the Operating Condition command and check the response.
  * @param  sdmmcx Pointer to SDMMC register base.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendOperCondCmd(SDMMC_TypeDef *sdmmcx)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  /** Send CMD8 to verify SD card interface operating condition.
    *  argument: - [31:12]: Reserved (must be set to '0')
    *  - [11:8]: Supply Voltage (VHS) 0x1 (Range: 2.7-3.6 V)
    *  - [7:0]: Check Pattern (recommended 0xAA)
    */
  sdmmc_cmdinit.argument           = SDMMC_CHECK_PATTERN;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_HS_SEND_EXT_CSD;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp7(sdmmcx);

  return error_code;
}

/**
  * @brief Send the Application command to verify that that the next command is an application specific command
  *        rather than a standard command and check the response.
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param argument Command argument.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendAppCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_APP_CMD;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_APP_CMD, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the command asking the accessed card to send its operating condition register (OCR).
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param argument Command argument.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendAppOperCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SD_APP_OP_COND;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp3(sdmmcx);

  return error_code;
}

/**
  * @brief Send the Bus Width command and check the response.
  * @param sdmmcx    Pointer to SDMMC register base.
  * @param bus_width Bus width.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendBusWidthCmd(SDMMC_TypeDef *sdmmcx, uint32_t bus_width)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = bus_width;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_APP_SD_SET_BUSWIDTH;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_APP_SD_SET_BUSWIDTH, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the Send SCR command and check the response.
  * @param sdmmcx Pointer to SDMMC register base.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendSCRCmd(SDMMC_TypeDef *sdmmcx)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = 0U;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SD_APP_SEND_SCR;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_SD_APP_SEND_SCR, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the Send CID command and check the response.
  * @param sdmmcx Pointer to SDMMC register base.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendCIDCmd(SDMMC_TypeDef *sdmmcx)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = 0U;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_ALL_SEND_CID;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_LONG;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp2(sdmmcx);

  return error_code;
}

/**
  * @brief Send the Send CSD command and check the response.
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param argument Command argument.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendCSDCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SEND_CSD;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_LONG;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp2(sdmmcx);

  return error_code;
}

/**
  * @brief Send the Send CSD command and check the response.
  * @param sdmmcx Pointer to SDMMC register base.
  * @param p_rca  Card relative address (RCA).
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SD_SendRelativeAddrCmd(SDMMC_TypeDef *sdmmcx, uint16_t *p_rca)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = 0U;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SET_REL_ADDR;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp6(sdmmcx, SDMMC_CMD_SET_REL_ADDR, p_rca);

  return error_code;
}

/**
  * @brief Send command to Set Relative Address MMC card (not SD card).
  * @param sdmmcx Pointer to SDMMC register base.
  * @param rca Card relative address (RCA).
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_MMC_SendRelativeAddrCmd(SDMMC_TypeDef *sdmmcx, uint16_t rca)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = ((uint32_t)rca << 16U);
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SET_REL_ADDR;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_SET_REL_ADDR, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the Sleep command to MMC card (not SD card).
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param argument argument of the command (RCA and Sleep/Awake).
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_MMC_SendSleepCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_MMC_SLEEP_AWAKE;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_MMC_SLEEP_AWAKE, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the Status command and check the response.
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param argument Command argument.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendStatusCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SEND_STATUS;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_SEND_STATUS, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the Status register command and check the response.
  * @param sdmmcx Pointer to SDMMC register base.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendStatusRegisterCmd(SDMMC_TypeDef *sdmmcx)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = 0U;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SD_APP_STATUS;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_SD_APP_STATUS, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send host capacity support information and activates the card's initialization process.
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param argument argument used for the command.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendOpConditionCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SEND_OP_COND;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp3(sdmmcx);

  return error_code;
}

/**
  * @brief Checks switchable function and switch card function.
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param argument argument used for the command.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendSwitchCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  /* Send CMD6 to activate SDR50 Mode and Power Limit 1.44W */
  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_HS_SWITCH;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_HS_SWITCH, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the command asking the accessed card to send its operating condition register (OCR).
  * @param sdmmcx   Pointer to SDMMC register base.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_SendVoltageSwitchCmd(SDMMC_TypeDef *sdmmcx)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = 0x00000000;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_VOLTAGE_SWITCH;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_VOLTAGE_SWITCH, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief Send the Send EXT_CSD command and check the response.
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param argument Command argument.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_MMC_SendEXTCSDCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_HS_SEND_EXT_CSD;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp1(sdmmcx, SDMMC_CMD_HS_SEND_EXT_CSD, SDMMC_CMD_TIMEOUT);

  return error_code;
}

/**
  * @brief  Execute a cmd52 to write single byte data and read single byte data if needed.
  * @param  sdmmcx: Pointer to SDMMC register base.
  * @param  argument:  SDMMC command argument which is sent to a card as part of a command message.
  * @param  p_response: pointer to response if needed.
  * @retval SDIO Card error state.
  */
uint32_t SDMMC_SDIO_SendReadWriteDirectCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument, uint8_t *p_response)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SDMMC_RW_DIRECT;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp5(sdmmcx, SDMMC_CMD_SDMMC_RW_DIRECT, p_response);

  return error_code;
}

/**
  * @brief  Execute a cmd53 to write or read multiple data with a single command.
  * @param  sdmmcx: Pointer to SDMMC register base.
  * @param  argument: SDMMC command argument which is sent to a card as part of a command message.
  * @retval SDIO Card error state.
  */
uint32_t SDMMC_SDIO_SendReadWriteExtendedCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SDMMC_RW_EXTENDED;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp5(sdmmcx, SDMMC_CMD_SDMMC_RW_EXTENDED, (uint8_t *) NULL);

  return error_code;
}

/**
  * @brief  Execute a cmd5 to write or read multiple data with a single command.
  * @param  sdmmcx: Pointer to SDMMC register base.
  * @param  argument: SDMMC command argument which is sent to a card as part of a command message.
  * @param  p_response: pointer to response if needed.
  * @retval SDIO Card error state.
  */
uint32_t SDMMC_SDIO_SendOperationconditionCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument, uint32_t *p_response)
{
  sdmmc_cmd_init_t sdmmc_cmdinit;
  uint32_t error_code;

  sdmmc_cmdinit.argument           = argument;
  sdmmc_cmdinit.cmd_index          = SDMMC_CMD_SDMMC_SEN_OP_COND;
  sdmmc_cmdinit.response           = SDMMC_RESPONSE_SHORT;
  sdmmc_cmdinit.wait_for_interrupt = SDMMC_WAIT_NO;
  sdmmc_cmdinit.cpsm               = SDMMC_CPSM_ENABLE;
  SDMMC_SendCommand(sdmmcx, &sdmmc_cmdinit);

  error_code = SDMMC_GetCmdResp4(sdmmcx, p_response);

  return error_code;
}
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Group4 SDMMC Responses management functions
  * @{
This subsection provides a set of functions allowing to manage the needed responses.
  */

/**
  * @brief Checks for error conditions for R1 response.
  * @param sdmmcx       Pointer to SDMMC register base.
  * @param cmd          Command index.
  * @param timeout_ms   Timeout duration.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_GetCmdResp1(SDMMC_TypeDef *sdmmcx, uint8_t cmd, uint32_t timeout_ms)
{
  uint32_t response_r1;
  uint32_t error_code = SDMMC_ERROR_NONE;

  /* Polling for flags until timeout */
  (void)SDMMC_WaitFlagUntilTimeout(sdmmcx, (SDMMC_FLAG_CMDREND | SDMMC_FLAG_BUSYD0END), timeout_ms);

  if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT);
    error_code = SDMMC_ERROR_CMD_RSP_TIMEOUT;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CCRCFAIL))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CCRCFAIL);
    error_code = SDMMC_ERROR_CMD_CRC_FAIL;
  }
  else
  {
    /* Nothing to do */
  }

  if (error_code != SDMMC_ERROR_NONE)
  {
    return error_code;
  }

  SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_STATIC_CMD_FLAGS);

  if (SDMMC_GetCommandResponse(sdmmcx) != cmd)
  {
    return SDMMC_ERROR_CMD_CRC_FAIL;
  }

  response_r1 = SDMMC_GetResponse(sdmmcx, SDMMC_RESP1);

  if ((response_r1 & SDMMC_OCR_ERRORBITS) == SDMMC_ALLZERO)
  {
    error_code = SDMMC_ERROR_NONE;
  }
  else if ((response_r1 & SDMMC_OCR_ADDR_OUT_OF_RANGE) == SDMMC_OCR_ADDR_OUT_OF_RANGE)
  {
    error_code = SDMMC_ERROR_ADDR_OUT_OF_RANGE;
  }
  else if ((response_r1 & SDMMC_OCR_ADDR_MISALIGNED) == SDMMC_OCR_ADDR_MISALIGNED)
  {
    error_code = SDMMC_ERROR_ADDR_MISALIGNED;
  }
  else if ((response_r1 & SDMMC_OCR_BLOCK_LEN_ERR) == SDMMC_OCR_BLOCK_LEN_ERR)
  {
    error_code = SDMMC_ERROR_BLOCK_LEN_ERR;
  }
  else if ((response_r1 & SDMMC_OCR_ERASE_SEQ_ERR) == SDMMC_OCR_ERASE_SEQ_ERR)
  {
    error_code = SDMMC_ERROR_ERASE_SEQ_ERR;
  }
  else if ((response_r1 & SDMMC_OCR_BAD_ERASE_PARAM) == SDMMC_OCR_BAD_ERASE_PARAM)
  {
    error_code = SDMMC_ERROR_BAD_ERASE_PARAM;
  }
  else if ((response_r1 & SDMMC_OCR_WRITE_PROT_VIOLATION) == SDMMC_OCR_WRITE_PROT_VIOLATION)
  {
    error_code = SDMMC_ERROR_WRITE_PROT_VIOLATION;
  }
  else if ((response_r1 & SDMMC_OCR_LOCK_UNLOCK_FAILED) == SDMMC_OCR_LOCK_UNLOCK_FAILED)
  {
    error_code = SDMMC_ERROR_LOCK_UNLOCK_FAILED;
  }
  else if ((response_r1 & SDMMC_OCR_COM_CRC_FAILED) == SDMMC_OCR_COM_CRC_FAILED)
  {
    error_code = SDMMC_ERROR_COM_CRC_FAILED;
  }
  else if ((response_r1 & SDMMC_OCR_ILLEGAL_CMD) == SDMMC_OCR_ILLEGAL_CMD)
  {
    error_code = SDMMC_ERROR_ILLEGAL_CMD;
  }
  else if ((response_r1 & SDMMC_OCR_CARD_ECC_FAILED) == SDMMC_OCR_CARD_ECC_FAILED)
  {
    error_code = SDMMC_ERROR_CARD_ECC_FAILED;
  }
  else if ((response_r1 & SDMMC_OCR_CC_ERROR) == SDMMC_OCR_CC_ERROR)
  {
    error_code = SDMMC_ERROR_CC_ERR;
  }
  else if ((response_r1 & SDMMC_OCR_STREAM_READ_UNDERRUN) == SDMMC_OCR_STREAM_READ_UNDERRUN)
  {
    error_code = SDMMC_ERROR_STREAM_READ_UNDERRUN;
  }
  else if ((response_r1 & SDMMC_OCR_STREAM_WRITE_OVERRUN) == SDMMC_OCR_STREAM_WRITE_OVERRUN)
  {
    error_code = SDMMC_ERROR_STREAM_WRITE_OVERRUN;
  }
  else if ((response_r1 & SDMMC_OCR_CID_CSD_OVERWRITE) == SDMMC_OCR_CID_CSD_OVERWRITE)
  {
    error_code = SDMMC_ERROR_CID_CSD_OVERWRITE;
  }
  else if ((response_r1 & SDMMC_OCR_WP_ERASE_SKIP) == SDMMC_OCR_WP_ERASE_SKIP)
  {
    error_code = SDMMC_ERROR_WP_ERASE_SKIP;
  }
  else if ((response_r1 & SDMMC_OCR_CARD_ECC_DISABLED) == SDMMC_OCR_CARD_ECC_DISABLED)
  {
    error_code = SDMMC_ERROR_CARD_ECC_DISABLED;
  }
  else if ((response_r1 & SDMMC_OCR_ERASE_RESET) == SDMMC_OCR_ERASE_RESET)
  {
    error_code = SDMMC_ERROR_ERASE_RESET;
  }
  else if ((response_r1 & SDMMC_OCR_AKE_SEQ_ERROR) == SDMMC_OCR_AKE_SEQ_ERROR)
  {
    error_code = SDMMC_ERROR_AKE_SEQ_ERR;
  }
  else
  {
    error_code = SDMMC_ERROR_GENERAL_UNKNOWN_ERR;
  }

  return error_code;
}

/**
  * @brief Checks for error conditions for R2 (CID or CSD) response.
  * @param sdmmcx Pointer to SDMMC register base.
  * @retval Card error code.
  */
uint32_t SDMMC_GetCmdResp2(SDMMC_TypeDef *sdmmcx)
{
  uint32_t error_code = SDMMC_ERROR_NONE;

  /* Polling for flags until timeout */
  (void)SDMMC_WaitFlagUntilTimeout(sdmmcx, (SDMMC_FLAG_CCRCFAIL | SDMMC_FLAG_CMDREND), SDMMC_CMD_TIMEOUT);

  if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT);
    error_code = SDMMC_ERROR_CMD_RSP_TIMEOUT;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CCRCFAIL))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CCRCFAIL);
    error_code =  SDMMC_ERROR_CMD_CRC_FAIL;
  }
  else
  {
    /* No error flag set */
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_STATIC_CMD_FLAGS);
  }

  return error_code;
}

/**
  * @brief Checks for error conditions for R3 (OCR) response.
  * @param sdmmcx Pointer to SDMMC register base.
  * @retval Card error code.
  */
uint32_t SDMMC_GetCmdResp3(SDMMC_TypeDef *sdmmcx)
{
  uint32_t error_code = SDMMC_ERROR_NONE;

  /* Polling for flags until timeout */
  (void)SDMMC_WaitFlagUntilTimeout(sdmmcx, (SDMMC_FLAG_CCRCFAIL | SDMMC_FLAG_CMDREND), SDMMC_CMD_TIMEOUT);

  if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT);
    error_code = SDMMC_ERROR_CMD_RSP_TIMEOUT;
  }
  else
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_STATIC_CMD_FLAGS);
  }

  return error_code;
}

/**
  * @brief  Checks for error conditions for R4 response.
  * @param  sdmmcx Pointer to SDMMC register base.
  * @param  p_resp Pointer to response.
  * @retval Card error state.
  */
uint32_t SDMMC_GetCmdResp4(SDMMC_TypeDef *sdmmcx, uint32_t *p_resp)
{
  uint32_t sta_reg;

  /* 8 is the number of required instructions cycles for the below loop statement.
  The SDMMC_CMD_TIMEOUT is expressed in ms */
  uint32_t count = SDMMC_CMD_TIMEOUT * (SystemCoreClock / 8U / 1000U);

  do
  {
    if (count-- == 0U)
    {
      return SDMMC_ERROR_TIMEOUT;
    }
    sta_reg = sdmmcx->STAR;
  } while (((sta_reg & (SDMMC_FLAG_CCRCFAIL | SDMMC_FLAG_CMDREND | SDMMC_FLAG_CTIMEOUT)) == 0U) \
           || ((sta_reg & SDMMC_FLAG_CMDACT) != 0U));

  if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT);

    return SDMMC_ERROR_CMD_RSP_TIMEOUT;
  }
  else
  {
    /* Clear all the static flags */
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_STATIC_CMD_FLAGS);
  }

  /* Clear all the static flags */
  SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_STATIC_CMD_FLAGS);

  /* We have received response, retrieve it.  */
  *p_resp = SDMMC_GetResponse(sdmmcx, SDMMC_RESP1);

  return SDMMC_ERROR_NONE;
}

/**
  * @brief  Checks for error conditions for R5 (cmd52/cmd53) response.
  * @param  sdmmcx: Pointer to SDMMC register base.
  * @param  sdio_cmd: The sent command index.
  * @param  p_data: pointer to the read/write buffer needed for cmd52.
  * @retval Card error state.
  */
uint32_t SDMMC_GetCmdResp5(SDMMC_TypeDef *sdmmcx, uint8_t sdio_cmd, uint8_t *p_data)
{
  uint32_t response_r5;
  uint32_t sta_reg;

  /* 8 is the number of required instructions cycles for the below loop statement.
  The SDMMC_CMD_TIMEOUT is expressed in ms */
  uint32_t count = SDMMC_CMD_TIMEOUT * (SystemCoreClock / 8U / 1000U);

  do
  {
    if (count-- == 0U)
    {
      return SDMMC_ERROR_TIMEOUT;
    }
    sta_reg = sdmmcx->STAR;
  } while (((sta_reg & (SDMMC_FLAG_CCRCFAIL | SDMMC_FLAG_CMDREND | SDMMC_FLAG_CTIMEOUT)) == 0U) \
           || ((sta_reg & SDMMC_FLAG_CMDACT) != 0U));

  if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT);

    return SDMMC_ERROR_CMD_RSP_TIMEOUT;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CCRCFAIL))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CCRCFAIL);

    return SDMMC_ERROR_CMD_CRC_FAIL;
  }
  else
  {
    /* Nothing to do */
  }

  /* Check response received is of desired command */
  if (SDMMC_GetCommandResponse(sdmmcx) != sdio_cmd)
  {
    return SDMMC_ERROR_CMD_CRC_FAIL;
  }

  /* Clear all the static flags */
  SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_STATIC_CMD_FLAGS);

  /* We have received response, retrieve it.  */
  response_r5 = SDMMC_GetResponse(sdmmcx, SDMMC_RESP1);

  if ((response_r5 & SDMMC_SDIO_R5_ERRORBITS) == SDMMC_ALLZERO)
  {
    /* we only want 8 bit read or write data and the 8 bit response flags are masked in the data pointer */
    if (p_data != NULL)
    {
      *p_data = (uint8_t)(response_r5 & 0xFFU);
    }

    return SDMMC_ERROR_NONE;
  }
  else if ((response_r5 & SDMMC_SDIO_R5_OUT_OF_RANGE) == SDMMC_SDIO_R5_OUT_OF_RANGE)
  {
    return SDMMC_ERROR_ADDR_OUT_OF_RANGE;
  }
  else if ((response_r5 & SDMMC_SDIO_R5_INVALID_FUNCTION_NUMBER) == SDMMC_SDIO_R5_INVALID_FUNCTION_NUMBER)
  {
    return SDMMC_ERROR_INVALID_PARAMETER;
  }
  else if ((response_r5 & SDMMC_SDIO_R5_ILLEGAL_CMD) == SDMMC_SDIO_R5_ILLEGAL_CMD)
  {
    return SDMMC_ERROR_ILLEGAL_CMD;
  }
  else if ((response_r5 & SDMMC_SDIO_R5_COM_CRC_FAILED) == SDMMC_SDIO_R5_COM_CRC_FAILED)
  {
    return SDMMC_ERROR_COM_CRC_FAILED;
  }
  else
  {
    return SDMMC_ERROR_GENERAL_UNKNOWN_ERR;
  }
}

/**
  * @brief Checks for error conditions for R6 (RCA) response.
  * @param sdmmcx Pointer to SDMMC register base.
  * @param cmd    Command index.
  * @param p_rca  Pointer to the variable that contain the SD card relative address RCA.
  * @retval Card error code.
  */
uint32_t SDMMC_GetCmdResp6(SDMMC_TypeDef *sdmmcx, uint8_t cmd, uint16_t *p_rca)
{
  uint32_t response_r1;
  uint32_t error_code = SDMMC_ERROR_NONE;

  /* Polling for flags until timeout */
  (void)SDMMC_WaitFlagUntilTimeout(sdmmcx, (SDMMC_FLAG_CCRCFAIL | SDMMC_FLAG_CMDREND), SDMMC_CMD_TIMEOUT);

  if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT);

    error_code = SDMMC_ERROR_CMD_RSP_TIMEOUT;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CCRCFAIL))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CCRCFAIL);

    error_code = SDMMC_ERROR_CMD_CRC_FAIL;
  }
  else
  {
    /* Nothing to do */
  }

  if (error_code != SDMMC_ERROR_NONE)
  {
    return error_code;
  }

  if (SDMMC_GetCommandResponse(sdmmcx) != cmd)
  {
    return SDMMC_ERROR_CMD_CRC_FAIL;
  }

  SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_STATIC_CMD_FLAGS);

  response_r1 = SDMMC_GetResponse(sdmmcx, SDMMC_RESP1);

  if ((response_r1 & (SDMMC_R6_GENERAL_UNKNOWN_ERROR | SDMMC_R6_ILLEGAL_CMD \
                      | SDMMC_R6_COM_CRC_FAILED)) == SDMMC_ALLZERO)
  {
    *p_rca = (uint16_t)(response_r1 >> 16);
  }
  else if ((response_r1 & SDMMC_R6_ILLEGAL_CMD) == SDMMC_R6_ILLEGAL_CMD)
  {
    error_code = SDMMC_ERROR_ILLEGAL_CMD;
  }
  else if ((response_r1 & SDMMC_R6_COM_CRC_FAILED) == SDMMC_R6_COM_CRC_FAILED)
  {
    error_code = SDMMC_ERROR_COM_CRC_FAILED;
  }
  else
  {
    error_code = SDMMC_ERROR_GENERAL_UNKNOWN_ERR;
  }

  return error_code;
}

/**
  * @brief Checks for error conditions for R7 response.
  * @param sdmmcx Pointer to SDMMC register base.
  * @retval Error code can be one of @ref SDMMC_error_types.
  */
uint32_t SDMMC_GetCmdResp7(SDMMC_TypeDef *sdmmcx)
{
  uint32_t error_code = SDMMC_ERROR_NONE;

  /* Polling for flags until timeout */
  (void)SDMMC_WaitFlagUntilTimeout(sdmmcx, (SDMMC_FLAG_CCRCFAIL | SDMMC_FLAG_CMDREND), SDMMC_CMD_TIMEOUT);

  if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CTIMEOUT);

    error_code = SDMMC_ERROR_CMD_RSP_TIMEOUT;
  }

  else if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CCRCFAIL))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CCRCFAIL);

    error_code = SDMMC_ERROR_CMD_CRC_FAIL;
  }
  else
  {
    /* Nothing to do */
  }

  if (SDMMC_IS_ACTIVE_FLAG(sdmmcx, SDMMC_FLAG_CMDREND))
  {
    SDMMC_CLEAR_FLAG(sdmmcx, SDMMC_FLAG_CMDREND);
  }

  return error_code;
}

/**
  * @}
  */

/** @defgroup SDMMC_CORE_Group5 SDMMC time calculation functions
  * @{
This subsection provides a function for SDMMC time calculation.
  */
/**
  * @brief Delay in milli-second.
  * @param sdmmcx   Pointer to SDMMC register base.
  * @param delay_ms Delay in ms value.
  */
void SDMMC_DelayMs(const SDMMC_TypeDef *sdmmcx, uint32_t delay_ms)
{
  __IO uint32_t count = delay_ms * (SystemCoreClock / 22U / 1000U);

  STM32_UNUSED(sdmmcx);

  while (count != 0U)
  {
    count--;
  }
}
/**
  * @}
  */

/**
  * @}
  */

/* Private function --------------------------------------------------------------------------------------------------*/
/** @defgroup SDMMC_CORE_Private_Functions SDMMC CORE Private Functions
  * @{
  */
/**
  * @brief Wait for a flag state until timeout.
  * @param sdmmcx     Pointer to SDMMC register base.
  * @param flag_mask  Value of the flag expected.
  * @param timeout_ms Timeout duration.
  * @retval SDMMC_ERROR_TIMEOUT in case of timeout has occurred.
  * @retval SDMMC_ERROR_NONE    in case of no error has occurred.
  */
static uint32_t SDMMC_WaitFlagUntilTimeout(const SDMMC_TypeDef *sdmmcx, uint32_t flag_mask, uint32_t timeout_ms)
{
  uint32_t timeout = timeout_ms * (SystemCoreClock / 22U / 1000U);
  uint32_t status_reg;

  status_reg = STM32_READ_REG(sdmmcx->STAR);
  /* Repeat while timeout != 0U */
  while (((((status_reg & flag_mask) == 0U) || ((status_reg & SDMMC_FLAG_CMDACT) != 0U))) && (timeout > 0U))
  {
    timeout--;
    status_reg = STM32_READ_REG(sdmmcx->STAR);
  }

  if (timeout == 0U)
  {
    return SDMMC_ERROR_TIMEOUT;
  }

  return SDMMC_ERROR_NONE;
}
/**
  * @}
  */
#endif /* SDMMC1 */

/**
  * @}
  */

/**
  * @}
  */
