/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_sd.c
  * @brief   SD card HAL module driver.
  *          This file provides firmware functions to manage the following functionalities of the Secure Digital (SD)
  *          peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral control functions
  *           + Peripheral state functions
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

/** @addtogroup SD
  * @{
  */
/** @defgroup SD_Introduction SD Introduction
  * @{

  - The SD Hardware Abstraction Layer provides a high-level interface to the STM32 SDMMC peripheral for
    communicating with Secure Digital (SD) and microSD memory cards.

  - This HAL driver is built on top of the SDMMC core layer and simplifies peripheral initialization, device
    identification, configuration, and transition to the transfer state.

  - It supports the main data operations required by storage applications, including single-block and
    multi-block read/write transfers, erase control, transfer abort management, and access to device status and
    configuration information.

  - The driver supports polling, interrupt, DMA, and, when enabled, linked-list or double-buffer DMA transfer modes,
    allowing the application to balance CPU load, throughput, and responsiveness.

  - It also provides services to manage device insertion and removal events, configure transfer timing and,
    when available, FIFO threshold parameters.

  - This abstraction layer improves portability across STM32 devices embedding the SDMMC peripheral and eases
    the integration of SD storage into embedded applications.

  */
/**
  * @}
  */

/** @defgroup SD_How_To_Use SD How To Use
  * @{
# How to use this driver

## The HAL SD driver can be used as follows:

SD memory card system Specifications are available through the SD card association website at www.sdcard.org
This driver is compliant with SD memory card specification version 6.0 and full compliant with previous version.

This HAL SD driver is a layered driver on top of the SDMMC core driver (allowing to handle SD and MMC memories).
The HAL SD driver allows to interface with SD and uSD cards devices.

This driver implements a high level communication layer for read and write from/to this memory.

This driver provides different set of APIs that allows to :

1. Initialize and de-initialize the logical SD object :
   - To initialize the SD Card, use the HAL_SD_Init() function to
     - to associate physical instance to logical object.
     - Enable the SDMMC peripheral Clock:
       - Either by calling the appropriate HAL RCC function  HAL_RCC_SDMMCx_EnableClock
       - Either by Setting the USE_HAL_SD_CLK_ENABLE_MODEL to HAL_CLK_ENABLE_PERIPH_ONLY through stm32tnxx_hal_conf.h
         module, in this case the SDMMC peripheral clock must be automatically enabled by the HAL_SD_Init().
   - To de-initiliaze the SD card, use the HAL_SD_DeInit() function that must turn off the SD Card and set
     the HAL SD handle state to RESET
2. Set and Get SD configuration:
   - Configure the SD card, use the HAL_SD_SetConfig() to apply the SD card configuration process, the clock frequency
     must be less than 400Khz. then, this phase allows the card identification and Get all card information
     (CSD, CID, Card Status Register) to ensure that the card has been correctly identified and
     then, Apply the user parameters.
     In this stage, the SD card moved from the IDENTIFICATION STATE to TRANSFER STATE and put the globale state
     at the IDLE state. In this case, we can perform any SD card Erase, read and write operation.
   - To get the SD card configuration, use the HAL_SD_GetConfig() to retrieve the current SD configuration.
   - When the GPIO Pin detects a removal of the SD card from the bus, use the HAL_SD_NotifyCardRemoval() to apply
     the SDMMC default configuration and wait for an insertion of the SD card.
   - When the GPIO Pin detects an insertion of the SD card, use the HAL_SD_NotifyCardInsertion() to
     re-apply the user configuration.
   - According to the SD card specification (speed, size and class), the timeout values available through define
     can be used also by user to fill the configuration structure at the SetConfig call:
      - HAL_SD_DATA_MAX_TIMEOUT      (0xFFFFFFFFU) : Max data timeout
      - HAL_SD_STOP_XFER_MAX_TIMEOUT (500U)        : Max stop transfer timeout 500 ms
      - HAL_SD_ERASE_MAX_TIMEOUT     (63000U)      : Max erase Timeout 63 seconds
     It can modify the timeout process values:
      - For the data_timeout_cycle    : Use HAL_SD_SetDataTimeout() to update it with the user definition
      - For the stopxfer_timeout_ms   : Use HAL_SD_SetStopXferTimeout() to update it with the user definition
      - for the erase_timeout_ms      : Use HAL_SD_SetEraseTimeout() to update it with the user definition

3. Input and Output operations:
  - Blocking mode: Polling
    - Read from SD card in polling mode by using function HAL_SD_ReadBlocks().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr.
      After this, ensure that the transfer is done correctly.
      The check is done through HAL_SD_GetCardState() function of SD card state.
    - Write to SD card in polling mode by using function HAL_SD_WriteBlocks().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr.
      After this, ensure that the transfer is done correctly.
      The check is done through HAL_SD_GetCardState() function of the SD card state.

  - Non-Blocking mode: IT
    - Read from the SD card in Interrupt mode by using function HAL_SD_ReadBlocks_IT().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr.
      After this, ensure that the transfer is done correctly by using the Xfer complete callbacks to check
      the end of the process.
    - Write to SD card in Interrupt mode by using function HAL_SD_WriteBlocks_IT().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr.
      After this, ensure that the transfer is done correctly by using the Xfer complete callbacks to check
      the end of the process.

  - Non-Blocking mode: DMA in normal mode
    - Read from the SD card in DMA mode by using function HAL_SD_ReadBlocks_DMA().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr.
      After this, ensure that the transfer is done correctly by checking the IT transfer process
      through the SD xfer interrupt event.
    - Write to SD card in DMA mode by using function HAL_SD_WriteBlocks_DMA().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr.
      After this, ensure that the transfer is done correctly by using the Xfer complete callbacks to check
      the end of the process.

  - Non-Blocking mode: DMA in linked-list mode
      Use the Linked list feature by enabling the USE_HAL_SD_LINKEDLIST compilation flag through stm32tnxx_hal_conf.h
      module.
      At this stage, Build a linked-list Q using the module Q.
      - Read from the SD card in linked-list mode by using the function HAL_SD_ReadBlocks_LinkedList().
        This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
        After this, ensure that the transfer is done correctly by using the Xfer complete callbacks to check
        the end of the process.
      - Write to the SD card in linked-list mode by using the function HAL_SD_WriteBlocks_LinkedList().
        This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
        After this, ensure that the transfer is done correctly by using the Xfer complete callbacks to check
        the end of the process.

  - Abort operation
     - Abort any transfer to/from the SD card by using the HAL_SD_Abort() to stop the transfer in polling mode
     - Abort any transfer to/from the SD card by using the HAL_SD_Abort_IT() to stop the transfer in IT mode

4. IRQHandler and Callbacks Functions:
   - All SD card interrupt requests are handled by the HAL_SD_IRQHandler function.
   - By default, after the HAL_SD_Init, all callbacks are reset to the corresponding legacy weak (surcharged) functions:
      - HAL_SD_XferCpltCallback()               : A Callback when an Xfer transfer is completed.
      - HAL_SD_ErrorCallback()                  : A Callback when an error has occurred.
      - HAL_SD_AbortCallback()                  : A Callback when an abort is completed.
      - HAL_SD_DriveTransceiver_1_8V_Callback() : A Callback when the switch to 1.8 v is completed.

   - To use the callback registration feature, Set the USE_HAL_SD_REGISTER_CALLBACKS to 1U the compilation flag
     through stm32tnxx_hal_conf.h module to allow the user to configure dynamically the driver register callbacks.

   - Use Functions to register a user callback, it allows to register following callbacks:
     - HAL_SD_RegisterXferCpltCallback()    : To register an xfer callback function.
     - HAL_SD_RegisterErrorCallback()   : To register an error callback function.
     - HAL_SD_RegisterAbortCallback()   : To register an abort callback function.
     - HAL_SD_RegisterTransceiverCallback() : To register a transceiver callback function.
       When The compilation define USE_HAL_SD_REGISTER_CALLBACKS is set to 0 or not defined, the callback registering
       feature is not available and weak (surcharged) callbacks are used.

5. SD Card related information functions:
  - To get the globale global_state, use the HAL_SD_GetState().
  - To get the internal state of the SD card, use the HAL_SD_GetCardState().
  - To get SD card status use the function HAL_SD_GetCardStatus() to retrieve the status bits that are related to the SD
    memory card proprietary features.
  - To get SD card information, use the function HAL_SD_GetCardInfo().
    It returns useful information about the SD card such as block number, block size type, logical block number,
    logical block size and the relative card address.
  - To switch the speed mode of the SD card, use the HAL_SD_SwitchSpeedMode().
  - To retrieve the SD card specification version, use the HAL_SD_GetCardSpecVersion().
  - To get the SD card identification register value, use the HAL_SD_GetCardCID() function.
  - To retrieve the last error code detecting by the SD card, Set the USE_HAL_SD_GET_LAST_ERRORS to 1U
    the compilation flag through stm32tnxx_hal_conf.h module to allow the user to get the last error code.

6. SD Card Interrupt and flags Inline functions:
  - HAL_SD_EnableIT()     : Enable the SD device interrupt to generate an interrupt request.
  - HAL_SD_DisableIT()    : Disable the SD device interrupt to clear an interrupt request.
  - HAL_SD_IsActiveFlag() : Check whether the specified SD flag is set or not.
  - HAL_SD_ClearFlag()    : Clear the SD's pending flags.

7. SD card linked-list queue functions:
This subsection provides a set of functions allowing to manage the SD linked-list node and queue:
  - To build an SDMMC node, use the HAL_SD_FillNodeConfig() according to configured parameters within
    hal_sd_node_config_t structure.
  - To get the current SDMMC node configuration,  use the HAL_SD_GetNodeConfig().
  - To set the SD linked list node data buffer state, use the HAL_SD_SetNodeDataBufferState().
  - To get the SD linked list node data buffer state, use the HAL_SD_GetNodeDataBufferState().
  - To get the SD linked list node information, use the HAL_SD_GetNodeInfo().
  - To set the SD linked list node address, use the HAL_SD_SetNodeAddress().
  - To get the SD linked list node address, use the HAL_SD_GetNodeAddress().

8. SD Delay Block functions:
The delay block (DLYB) is used to generate an output clock that is dephased from the input clock.
  - Use HAL_SD_SetConfigDlybDelay() to set the SD delay block configuration.
  - Use HAL_SD_GetDlybOutputClockPhase() to get the SD delay block output clock phase.
  - Use HAL_SD_CalculateDlybMaxClockPhase() to calculate the SD delay block maximum output clock phase.
  - Use HAL_SD_EnableDlyb() to enable the SD delay block.
  - Use HAL_SD_DisableDlyb() to disable the SD delay block.
  - Use HAL_SD_IsEnabledDlyb() to check if the delay block peripheral is enabled or not.
  */
/**
  * @}
  */

/** @defgroup SD_Configuration_Table SD Configuration Table
  * @{
## Configuration inside the SD driver

Config defines                      | Description     | Default value   | Note
------------------------------------| --------------- | ----------------| ----------------------------------------------
USE_ASSERT_DBG_PARAM                | from the IDE    |     NONE        | Allows to use the assert checks parameters.
USE_ASSERT_DBG_STATE                | from the IDE    |     NONE        | Allows to use the assert checks states.
USE_HAL_CHECK_PARAM                 | from hal_conf.h |      0          | Allows to use the run-time checks parameters.
USE_HAL_SD_AUTO_DETECTION_FREQUENCY | from hal_conf.h |      0          | Allows to Enable/Disable SD Custom Frequency.
USE_HAL_SD_REGISTER_CALLBACKS       | from hal_conf.h |      0          | Allows to provide specific callback functions.
USE_HAL_SD_LINKEDLIST               | from hal_conf.h |      1          | Allows to use the SD in linked-list mode.
USE_HAL_SD_GET_CID                  | from hal_conf.h |      1          | Allows to get card identification information.
USE_HAL_SD_GET_LAST_ERRORS          | from hal_conf.h |      1          | Allows to get last errors codes.
USE_HAL_SD_USER_DATA                | from hal_conf.h |      0          | Allows to Enable/Disable user data.
USE_HAL_SD_CLK_ENABLE_MODEL         | from hal_conf.h |HAL_CLK_ENABLE_NO| Allows to enable the clock model for the SD.
USE_HAL_SD_GET_SPEC_VERSION         | from hal_conf.h |      1          | Allows to get the SD Card version.
  */
/**
  * @}
  */
#if defined(SDMMC1)
#if defined (USE_HAL_SD_MODULE) && (USE_HAL_SD_MODULE == 1)

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup SD_Private_Functions SD Private Functions
  * @{
  */
static void         SD_SetDefaultConfig(hal_sd_handle_t *hsd);
static hal_status_t SD_SetConfig(hal_sd_handle_t *hsd, const hal_sd_config_t *p_config);
static hal_status_t SD_NotifyCardInsertion(hal_sd_handle_t *hsd, const hal_sd_config_t *p_config);
static void         SD_SetSCRConfig(hal_sd_handle_t *hsd);
static hal_status_t SD_SetSpeedMode(hal_sd_handle_t *hsd, uint32_t speed_pattern);
static hal_status_t SD_GetSpeedMode(hal_sd_handle_t *hsd, hal_sd_speed_mode_t speed_mode, uint32_t *p_switch_speed);
static hal_status_t SD_SetWideBus(hal_sd_handle_t *hsd, hal_sd_bus_wide_t wide_bus);
static void         SD_Write_IT(hal_sd_handle_t *hsd);
static void         SD_Read_IT(hal_sd_handle_t *hsd);
static hal_status_t SD_GetCardStatusData(hal_sd_handle_t *hsd, uint32_t *p_sd_data);
static hal_status_t SD_GetCardSCRData(hal_sd_handle_t *hsd, uint32_t *p_sd_scr);
static hal_status_t SD_StartVoltageSwitchSequence(hal_sd_handle_t *hsd);
static hal_status_t SD_CheckVoltageSwitch(hal_sd_handle_t *hsd);

static hal_status_t SD_Card_Identify(hal_sd_handle_t *hsd);
static hal_status_t SD_Card_IdentifyVoltageRange(hal_sd_handle_t *hsd);
static hal_status_t SD_Card_IdentifyCID(hal_sd_handle_t *hsd);
static hal_status_t SD_Card_IdentifyRelativeAddress(hal_sd_handle_t *hsd);
static hal_status_t SD_Card_EnterDataTransferMode(hal_sd_handle_t *hsd);
static hal_status_t SD_Card_GetRelativeAddr(hal_sd_handle_t *hsd, uint16_t *p_sd_relative_addr);
static hal_status_t SD_Card_GetCSD(hal_sd_handle_t *hsd);
static hal_status_t SD_Card_GetSCR(hal_sd_handle_t *hsd, uint32_t *p_scr);
#if defined (USE_HAL_SD_GET_SPEC_VERSION) && (USE_HAL_SD_GET_SPEC_VERSION == 1)
static hal_sd_specification_version_t SD_Card_GetVersion(hal_sd_handle_t *hsd);
#endif /* USE_HAL_SD_GET_SPEC_VERSION */
static hal_status_t SD_Card_SetBlockSize(hal_sd_handle_t *hsd, uint32_t blk_size);
static hal_status_t SD_Card_SendStatus(hal_sd_handle_t *hsd, uint32_t *p_sd_status);
static uint32_t     SD_Card_CalculateClockDiv(uint32_t sdmmc_clk, uint32_t user_freq);
static hal_status_t SD_Card_GetClockDiv(const hal_sd_handle_t *hsd, uint32_t sdmmc_clk, uint32_t user_freq,
                                        uint32_t *p_clk_div);
static hal_status_t SD_GetCardStatus(hal_sd_handle_t *hsd, hal_sd_card_status_t *p_status);
static uint32_t     SD_GetCardState(const hal_sd_handle_t *hsd);
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup SD_Private_Macros SD Private Macros
  * @{
  */
/*! SD Get operating voltage */
#define SD_GET_OPERATING_VOLTAGE_STATE(response) ((((response) >> 31U) == 1U) ? 1U : 0U)

/*! Macro to get the handle instance */
#define SD_GET_INSTANCE(handle) ((SDMMC_TypeDef *)((uint32_t)(handle)->instance))

/**
  * @}
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
#if defined (USE_HAL_SD_GET_SPEC_VERSION) && (USE_HAL_SD_GET_SPEC_VERSION == 1)
/** @defgroup SD_Private_Types SD Private Types
  * @{
  */
/*! SD Card spec version values */
typedef struct
{
  uint8_t sd_spec;   /*!< Spec version 1.x or 2.x */
  uint8_t sd_spec_3; /*!< Spec version 3.x        */
  uint8_t sd_spec_4; /*!< Spec version 4.x        */
  uint8_t sd_spec_x; /*!< Spec version 5.x or 6.x */
} sd_spec_values_t;

/*! SD Card spec information */
typedef struct
{
  sd_spec_values_t field_value;           /*!< Spec version value */
  hal_sd_specification_version_t version; /*!< SD card version    */
} sd_spec_info_t;
/**
  * @}
  */
#endif /* USE_HAL_SD_GET_SPEC_VERSION */
/* Private constants -------------------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup SD_Exported_Functions HAL SD Functions
  * @{
  */
/** @addtogroup SD_Exported_Functions_Group1
  * @{
This section provides functions allowing to initialize and de-initialize the SD card device :
- Call the function HAL_SD_Init() to initialize the selected  HAL SD handle and associate an SD peripheral instance.
- Call the function HAL_SD_DeInit() to de-initialize the SD card device.
  */
/**
  * @brief Initialize the selected  HAL SD handle and associate an SD peripheral instance.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param instance HAL SD instance.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            SD handle has been correctly Initialized.
  */
hal_status_t HAL_SD_Init(hal_sd_handle_t *hsd, hal_sd_t instance)
{
  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_ALL_INSTANCE((SDMMC_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hsd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Associate physical instance to logical object */
  hsd->instance = instance;

#if defined (USE_HAL_SD_CLK_ENABLE_MODEL) && (USE_HAL_SD_CLK_ENABLE_MODEL == HAL_CLK_ENABLE_PERIPH_ONLY)
  if (hsd->instance == HAL_SD_CARD_1)
  {
    LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_SDMMC1);
  }
#if defined (SDMMC2)
  else if (hsd->instance == HAL_SD_CARD_2)
  {
    LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_SDMMC2);
  }
#endif /* SDMMC2 */
  else
  {
    /* Nothing to do */
  }
#endif /* USE_HAL_SD_CLK_ENABLE_MODEL */

#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
  hsd->p_xfer_cplt_callback        = HAL_SD_XferCpltCallback;
  hsd->p_error_callback            = HAL_SD_ErrorCallback;
  hsd->p_abort_callback            = HAL_SD_AbortCallback;
  hsd->p_transceiver_1_8V_callback = HAL_SD_DriveTransceiver_1_8V_Callback;
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */

#if defined (USE_HAL_SD_USER_DATA) && (USE_HAL_SD_USER_DATA == 1)
  hsd->p_user_data = NULL;
#endif /* USE_HAL_SD_USER_DATA */

#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
  hsd->last_error_codes = HAL_SD_ERROR_NONE;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */

  hsd->context = SDMMC_CONTEXT_NONE;
  hsd->global_state = HAL_SD_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief De-Initialize the SD card.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  */
void HAL_SD_DeInit(hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_ALL_INSTANCE(SD_GET_INSTANCE(hsd)));

  SDMMC_SET_PWR_STATE(SD_GET_INSTANCE(hsd), SDMMC_PWR_OFF);

  hsd->global_state = HAL_SD_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup SD_Exported_Functions_Group2 Set and Get configurations functions
  * @{
This subsection provides a set of functions allowing to configure the SD peripheral:

There are 2 categories of HAL configuration APIs

- Global configuration APIs:
  - HAL_SD_SetConfig()           : Allowing to set the HAL peripheral instance into a ready to use state (idle)
                                   according to the user parameters.
  - HAL_SD_GetConfig()           : Allowing to retrieve the HAL peripheral configuration.
  - HAL_SD_NotifyCardInsertion() : Allowing to set the user parameters after detection the insertion of SD card.
  - HAL_SD_NotifyCardRemoval()   : Allowing to set the default SDMMC config after the removal of the SD card.

- Unitary configuration APIs:
  - HAL_SD_SetDataTimeout()      : Allowing to modify the data timeout value according to the SD card type.
  - HAL_SD_GetDataTimeout()      : Allowing to retrieve the data timeout value.
  - HAL_SD_SetStopXferTimeout()  : Allowing to modify the stop transfer timeout value according to SD card type.
  - HAL_SD_GetStopXferTimeout()  : Allowing to retrieve the stop transfer timeout value.
  - HAL_SD_SetEraseTimeout()     : Allowing to modify the erase timeout value according to SD card type.
  - HAL_SD_GetEraseTimeout()     : Allowing to retrieve the ererase timeout value.
These APIs are intended to dynamically modify/Retrieve a unitary item meaning that a global config has been already
applied.
  */
/**
  * @brief Configure the SD according to the user parameters.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param p_config Pointer to a hal_sd_config_t structure that contains the SD configuration.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         SD instance is already configured and cannot be modified.
  * @retval HAL_OK            SD instance has been correctly configured.
  */
hal_status_t HAL_SD_SetConfig(hal_sd_handle_t *hsd, const hal_sd_config_t *p_config)
{
  ASSERT_DBG_PARAM(hsd      != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_EDGE(((uint32_t)p_config->clk_cfg.clk_edge)));
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_POWER_SAVE(((uint32_t)p_config->clk_cfg.clk_power_save)));
  ASSERT_DBG_PARAM(IS_SDMMC_BUS_WIDE(((uint32_t)p_config->bus_wide)));
  ASSERT_DBG_PARAM(IS_SDMMC_HARDWARE_FLOW_CONTROL(((uint32_t)p_config->hw_flow_ctrl)));
#if defined (USE_HAL_SD_AUTO_DETECTION_FREQUENCY) && (USE_HAL_SD_AUTO_DETECTION_FREQUENCY == 0U)
  ASSERT_DBG_PARAM(p_config->clk_cfg.clk_hz != 0U);
#endif /* USE_HAL_SD_AUTO_DETECTION_FREQUENCY */

  ASSERT_DBG_STATE(hsd->global_state, ((uint32_t)HAL_SD_STATE_INIT) | (uint32_t)HAL_SD_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsd->data_timeout_cycle   = p_config->data_timeout_cycle;
  hsd->stop_xfer_timeout_ms = p_config->stop_xfer_timeout_ms;
  hsd->erase_timeout_ms     = p_config->erase_timeout_ms;
  hsd->sd_transceiver       = p_config->transceiver;

  SD_SetDefaultConfig(hsd);

  if (SD_NotifyCardInsertion(hsd, p_config) != HAL_OK)
  {
    hsd->global_state = HAL_SD_STATE_CARD_REMOVED;
    return HAL_ERROR;
  }

  hsd->global_state = HAL_SD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the SD configuration.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param p_config Pointer to a hal_sd_config_t structure that contains the SD configuration.
  */
void HAL_SD_GetConfig(const hal_sd_handle_t *hsd, hal_sd_config_t *p_config)
{
  sdmmc_config_t sdmmc_cfg = {0};

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  SDMMC_GetConfig(SD_GET_INSTANCE(hsd), &sdmmc_cfg);

  p_config->bus_wide               = (hal_sd_bus_wide_t)(sdmmc_cfg.bus_wide);
  p_config->hw_flow_ctrl           = (hal_sd_hardware_flow_control_t)(sdmmc_cfg.hardware_flow_control);
  p_config->clk_cfg.clk_edge       = (hal_sd_clock_edge_t)sdmmc_cfg.clk.clock_edge;
  p_config->clk_cfg.clk_power_save = (hal_sd_clock_power_save_t)sdmmc_cfg.clk.clock_power_save;
#if defined (USE_HAL_SD_AUTO_DETECTION_FREQUENCY) && (USE_HAL_SD_AUTO_DETECTION_FREQUENCY == 0U)
  p_config->clk_cfg.clk_hz =  HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)hsd->instance));
  if (sdmmc_cfg.clk.clock_div != 0U)
  {
    p_config->clk_cfg.clk_hz /= (2U * sdmmc_cfg.clk.clock_div);
  }
#endif /* USE_HAL_SD_AUTO_DETECTION_FREQUENCY */
  p_config->transceiver            = hsd->sd_transceiver;

  /* Retrieve SDMMC timeout values */
  p_config->data_timeout_cycle     = hsd->data_timeout_cycle;
  p_config->erase_timeout_ms       = hsd->erase_timeout_ms;
  p_config->stop_xfer_timeout_ms   = hsd->stop_xfer_timeout_ms;
}

/**
  * @brief Notify SD card after insertion.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param p_config Pointer to a hal_sd_config_t structure that contains the SD configuration.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    SD instance has been correctly configured after detection.
  */
hal_status_t HAL_SD_NotifyCardInsertion(hal_sd_handle_t *hsd, const hal_sd_config_t *p_config)
{
  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_EDGE(((uint32_t)p_config->clk_cfg.clk_edge)));
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_POWER_SAVE(((uint32_t)p_config->clk_cfg.clk_power_save)));
  ASSERT_DBG_PARAM(IS_SDMMC_BUS_WIDE(((uint32_t)p_config->bus_wide)));
  ASSERT_DBG_PARAM(IS_SDMMC_HARDWARE_FLOW_CONTROL(((uint32_t)p_config->hw_flow_ctrl)));
#if defined (USE_HAL_SD_AUTO_DETECTION_FREQUENCY) && (USE_HAL_SD_AUTO_DETECTION_FREQUENCY == 0U)
  ASSERT_DBG_PARAM(p_config->clk_cfg.clk_hz != 0U);
#endif /* USE_HAL_SD_AUTO_DETECTION_FREQUENCY */

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_CARD_REMOVED | (uint32_t)HAL_SD_STATE_IDLE);

  if (SD_NotifyCardInsertion(hsd, p_config) != HAL_OK)
  {
    hsd->global_state = HAL_SD_STATE_CARD_REMOVED;
    return HAL_ERROR;
  }

  hsd->global_state = HAL_SD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Notify SD card after removal.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval HAL_OK SD card has been correctly re-configured with its default configuration.
  */
hal_status_t HAL_SD_NotifyCardRemoval(hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  SD_SetDefaultConfig(hsd);

  hsd->global_state = HAL_SD_STATE_CARD_REMOVED;

  return HAL_OK;
}

/**
  * @brief Set SD data timeout.
  * @param  hsd                Pointer to a hal_sd_handle_t structure.
  * @param  data_timeout_cycle SD data timeout cycle.
  * @retval HAL_OK             SD card has been correctly set the data timeout cycle value.
  */
hal_status_t HAL_SD_SetDataTimeout(hal_sd_handle_t *hsd, uint32_t data_timeout_cycle)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

  hsd->data_timeout_cycle = data_timeout_cycle;

  return HAL_OK;
}

/**
  * @brief Get SD data timeout.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval uint32_t data_timeout_cycle value in millisecond.
  */
uint32_t HAL_SD_GetDataTimeout(const hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  return hsd->data_timeout_cycle;
}

/**
  * @brief Set SD stop transfer timeout.
  * @param  hsd                 Pointer to a hal_sd_handle_t structure.
  * @param  stopxfer_timeout_ms SD stop xfer timeout.
  * @retval HAL_OK              When SD card sets correctly the stop xfer timeout in millisecond.
  */
hal_status_t HAL_SD_SetStopXferTimeout(hal_sd_handle_t *hsd, uint32_t stopxfer_timeout_ms)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

  hsd->stop_xfer_timeout_ms = stopxfer_timeout_ms;

  return HAL_OK;
}

/**
  * @brief Get SD stop transfer timeout.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval uint32_t stop_xfer_timeout_ms value in millisecond.
  */
uint32_t HAL_SD_GetStopXferTimeout(const hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  return hsd->stop_xfer_timeout_ms;
}

/**
  * @brief Set SD erase timeout.
  * @param  hsd              Pointer to a hal_sd_handle_t structure.
  * @param  erase_timeout_ms SD erase timeout.
  * @retval HAL_OK           When SD card sets correctly the erase timeout value in millisecond.
  */
hal_status_t HAL_SD_SetEraseTimeout(hal_sd_handle_t *hsd, uint32_t erase_timeout_ms)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

  hsd->erase_timeout_ms = erase_timeout_ms;

  return HAL_OK;
}

/**
  * @brief Get SD erase timeout.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval uint32_t erase_timeout_ms value in millisecond.
  */
uint32_t HAL_SD_GetEraseTimeout(const hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  return hsd->erase_timeout_ms;
}
/**
  * @}
  */

/** @addtogroup SD_Exported_Functions_Group3 Input and Output operation functions
  * @{
This subsection provides a set of functions allowing to manage the data transfer from/to SD card.

There are 3 categories of HAL functions APIs to manage the data transfer:
- Blocking mode: Polling
  - HAL_SD_ReadBlocks().
  - HAL_SD_WriteBlocks().
- Non-Blocking mode: IT
 - HAL_SD_ReadBlocks_IT().
 - HAL_SD_WriteBlocks_IT().
- Non-Blocking mode: DMA
 - HAL_SD_ReadBlocks_DMA().
 - HAL_SD_WriteBlocks_DMA().
- Non-Blocking mode: DMA in linked list mode
 - HAL_SD_ReadBlocks_LinkedList().
 - HAL_SD_WriteBlocks_LinkedList().
- Function to Erases the specified memory area of the given SD card.

There are 2 categories of HAL functions APIs to abort transfer data:
- Abort the current transfer in polling mode with HAL_SD_Abort().
- Abort the current transfer in IT/DMA mode with HAL_SD_Abort_IT().
  */

/**
  * @brief Erases the specified memory area of the given SD card.
  * @param hsd              Pointer to hal_sd_handle_t structure.
  * @param start_block_addr Start Block address.
  * @param end_block_addr   End of Block address.
  * @warning This API must be followed by a check on the card state through HAL_SD_GetCardState().
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_Erase(hal_sd_handle_t *hsd, uint32_t start_block_addr, uint32_t end_block_addr)
{
  uint32_t error_code;
  uint32_t start_addr = start_block_addr;
  uint32_t end_addr   = end_block_addr;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(end_addr >= start_addr);
  ASSERT_DBG_PARAM(end_addr <= hsd->sd_card.logical_blk_nbr);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((end_addr < start_addr) || (end_addr > hsd->sd_card.logical_blk_nbr))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_IDLE, HAL_SD_STATE_ACTIVE);

  /* Get start and end block for high capacity cards */
  if (hsd->type != SDMMC_SD_CARD_SDHC_SDXC)
  {
    start_addr *= SDMMC_BLOCK_SIZE_BYTE;
    end_addr   *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Wait for the Card Transfer status */
  if (SD_GetCardState(hsd) != (uint32_t)HAL_SD_CARD_TRANSFER)
  {
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Send CMD32 SD_ERASE_GRP_START with argument as start_addr */
  error_code = SDMMC_SendEraseCmd(SD_GET_INSTANCE(hsd), start_addr, SDMMC_CMD_SD_ERASE_GRP_START, SDMMC_CMD_TIMEOUT);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Send CMD33 SD_ERASE_GRP_END with argument as end_addr */
  error_code = SDMMC_SendEraseCmd(SD_GET_INSTANCE(hsd), end_addr, SDMMC_CMD_SD_ERASE_GRP_END, SDMMC_CMD_TIMEOUT);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Send CMD38 ERASE */
  error_code = SDMMC_SendEraseCmd(SD_GET_INSTANCE(hsd), 0UL, SDMMC_CMD_ERASE, hsd->erase_timeout_ms);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  hsd->global_state = HAL_SD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Reads block(s) from a specified address in a card. The Data transfer is managed by polling mode.
  * @param hsd          Pointer to a hal_sd_handle_t structure.
  * @param p_data       Pointer to the buffer that contain the received data.
  * @param block_addr   Block Address from where the data is to be read.
  * @param blocks_nbr   Number of SD blocks to read.
  * @param timeout_ms   Specify timeout value.
  * @warning This API must be followed by a check on the card state through HAL_SD_GetCardState().
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_ReadBlocks(hal_sd_handle_t *hsd, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr,
                               uint32_t timeout_ms)
{
  uint32_t error_code;
  uint32_t cmd_type;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t tick_start = HAL_GetTick();
  uint32_t remaining_data;
  uint32_t addr = block_addr;
  uint32_t *p_tmp_data;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hsd->sd_card.logical_blk_nbr);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (blocks_nbr == 0U) || ((addr + blocks_nbr) > hsd->sd_card.logical_blk_nbr))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_IDLE, HAL_SD_STATE_ACTIVE);

  p_tmp_data = (uint32_t *)(uint32_t)p_data;

  /* Initialize data control register */
  SDMMC_CLEAR_DCTRL(SD_GET_INSTANCE(hsd));

  if (hsd->type != SDMMC_SD_CARD_SDHC_SDXC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the SD DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hsd->data_timeout_cycle;
  data_ctrl.data_length     = blocks_nbr * SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &data_ctrl);

  SDMMC_CMDTRANS_ENABLE(SD_GET_INSTANCE(hsd));

  /* Read block(s) in polling mode */
  if (blocks_nbr > 1U)
  {
    hsd->context = SDMMC_CONTEXT_READ_MULTIPLE_BLOCK;
    cmd_type = SDMMC_CMD_READ_MULT_BLOCK;
  }
  else
  {
    hsd->context = SDMMC_CONTEXT_READ_SINGLE_BLOCK;
    cmd_type = SDMMC_CMD_READ_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendReadBlocksCmd(SD_GET_INSTANCE(hsd), addr, cmd_type);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->context = SDMMC_CONTEXT_NONE;
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Poll on SDMMC flags */
  remaining_data = data_ctrl.data_length;
  while (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0UL)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_RXFIFOHF) != 0UL) && (remaining_data >= 32U))
    {
      /* Read data from SDMMC Rx FIFO */
      for (uint32_t count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
      {
        *p_tmp_data = SDMMC_ReadFIFO(SD_GET_INSTANCE(hsd));
        p_tmp_data++;
      }
      remaining_data -= SDMMC_FIFO_SIZE;
    }

    if (((HAL_GetTick() - tick_start) >= timeout_ms) || (timeout_ms == 0U))
    {
      SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
      hsd->context = SDMMC_CONTEXT_NONE;
      hsd->global_state = HAL_SD_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }

  SDMMC_CMDTRANS_DISABLE(SD_GET_INSTANCE(hsd));

  if ((SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DATAEND) != 0UL) && (blocks_nbr > 1U))
  {
    if (hsd->type != SDMMC_SD_CARD_SECURED)
    {
      /* Send stop transmission command */
      error_code = SDMMC_SendStopTransferCmd(SD_GET_INSTANCE(hsd), hsd->stop_xfer_timeout_ms);
      if (error_code != HAL_SD_ERROR_NONE)
      {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
        hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
        SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
        hsd->context = SDMMC_CONTEXT_NONE;
        hsd->global_state = HAL_SD_STATE_IDLE;
        return HAL_ERROR;
      }
    }
  }

  if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_RXOVERR) != 0U)
  {
    error_code = SDMMC_READ_REG(SD_GET_INSTANCE(hsd), STAR);
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    if ((error_code & SDMMC_FLAG_DTIMEOUT) != 0UL)
    {
      hsd->last_error_codes |= HAL_SD_ERROR_TIMEOUT;
    }

    if ((error_code & SDMMC_FLAG_DCRCFAIL) != 0UL)
    {
      hsd->last_error_codes |= HAL_SD_ERROR_DATA_CRC_FAIL;
    }

    if ((error_code & SDMMC_FLAG_RXOVERR) != 0UL)
    {
      hsd->last_error_codes |= HAL_SD_ERROR_RX_OVERRUN;
    }
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    hsd->context = SDMMC_CONTEXT_NONE;
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
  hsd->global_state = HAL_SD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Allows to write block(s) to a specified address in a card. The Data transfer is managed by polling mode.
  * @param hsd          Pointer to a hal_sd_handle_t structure.
  * @param p_data       pointer to the buffer that contain the data to transmit.
  * @param block_addr   Block Address where the data is written.
  * @param blocks_nbr   Number of SD blocks to write.
  * @param timeout_ms   Specify timeout value.
  * @warning This API must be followed by a check on the card state through HAL_SD_GetCardState().
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_WriteBlocks(hal_sd_handle_t *hsd, const uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr,
                                uint32_t timeout_ms)
{
  uint32_t error_code;
  uint32_t cmd_type;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t tick_start = HAL_GetTick();
  uint32_t remaining_data;
  uint32_t addr = block_addr;
  const uint32_t *p_tmp_data;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hsd->sd_card.logical_blk_nbr);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (blocks_nbr == 0U) || ((addr + blocks_nbr) > hsd->sd_card.logical_blk_nbr))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_IDLE, HAL_SD_STATE_ACTIVE);

  p_tmp_data = (const uint32_t *)(uint32_t)p_data;

  /* Initialize data control register */
  SDMMC_CLEAR_DCTRL(SD_GET_INSTANCE(hsd));

  if (hsd->type != SDMMC_SD_CARD_SDHC_SDXC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the SD DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hsd->data_timeout_cycle;
  data_ctrl.data_length     = blocks_nbr * SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(SD_GET_INSTANCE(hsd));

  /* Write Blocks in Polling mode */
  if (blocks_nbr > 1U)
  {
    hsd->context = SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK;
    cmd_type = SDMMC_CMD_WRITE_MULT_BLOCK;
  }
  else
  {
    hsd->context = SDMMC_CONTEXT_WRITE_SINGLE_BLOCK;
    cmd_type = SDMMC_CMD_WRITE_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendWriteBlocksCmd(SD_GET_INSTANCE(hsd), addr, cmd_type);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->context = SDMMC_CONTEXT_NONE;
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Write block(s) in polling mode */
  remaining_data = data_ctrl.data_length;
  while (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_TXUNDERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0UL)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_TXFIFOHE) != 0UL) && (remaining_data >= 32U))
    {
      /* Write data to SDMMC Tx FIFO */
      for (uint32_t count = 0U; count < 8U; count++)
      {
        SDMMC_WriteFIFO(SD_GET_INSTANCE(hsd), *p_tmp_data);
        p_tmp_data++;
      }
      remaining_data -= 32U;
    }

    if (((HAL_GetTick() - tick_start) >= timeout_ms) || (timeout_ms == 0U))
    {
      SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
      hsd->context = SDMMC_CONTEXT_NONE;
      hsd->global_state = HAL_SD_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }

  SDMMC_CMDTRANS_DISABLE(SD_GET_INSTANCE(hsd));

  if ((SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DATAEND) != 0UL) && (blocks_nbr > 1U))
  {
    if (hsd->type != SDMMC_SD_CARD_SECURED)
    {
      error_code = SDMMC_SendStopTransferCmd(SD_GET_INSTANCE(hsd), hsd->stop_xfer_timeout_ms);
      if (error_code != HAL_SD_ERROR_NONE)
      {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
        hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
        SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
        hsd->context = SDMMC_CONTEXT_NONE;
        hsd->global_state = HAL_SD_STATE_IDLE;
        return HAL_ERROR;
      }
    }
  }

  if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_TXUNDERR) != 0U)
  {
    error_code = SDMMC_READ_REG(SD_GET_INSTANCE(hsd), STAR);
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    if ((error_code & SDMMC_FLAG_DTIMEOUT) != 0UL)
    {
      hsd->last_error_codes |= HAL_SD_ERROR_DATA_TIMEOUT;
    }

    if ((error_code & SDMMC_FLAG_DCRCFAIL) != 0UL)
    {
      hsd->last_error_codes |= HAL_SD_ERROR_DATA_CRC_FAIL;
    }

    if ((error_code & SDMMC_FLAG_TXUNDERR) != 0UL)
    {
      hsd->last_error_codes |= HAL_SD_ERROR_TX_UNDERRUN;
    }
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    hsd->context = SDMMC_CONTEXT_NONE;
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
  hsd->global_state = HAL_SD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Reads block(s) from a specified address in a card. The Data transfer is managed in interrupt mode.
  * @param hsd        Pointer to a hal_sd_handle_t structure.
  * @param p_data     Pointer to the buffer that contain the received data.
  * @param block_addr Block Address from where the data is to be read.
  * @param blocks_nbr Number of blocks to read.
  * @warning This API must be followed by a check on the card state through HAL_SD_GetCardState().
  * @warning It could also check the IT transfer process through the SD Rx interrupt event.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_ReadBlocks_IT(hal_sd_handle_t *hsd, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr)
{
  uint32_t error_code;
  uint32_t cmd_type;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t addr = block_addr;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hsd->sd_card.logical_blk_nbr);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (blocks_nbr == 0U) || ((addr + blocks_nbr) > hsd->sd_card.logical_blk_nbr))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_IDLE, HAL_SD_STATE_ACTIVE);

  SDMMC_CLEAR_DCTRL(SD_GET_INSTANCE(hsd));

  hsd->p_xfer_buff = (uint32_t *)(uint32_t)p_data;
  hsd->xfer_size_byte = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;

  if (hsd->type != SDMMC_SD_CARD_SDHC_SDXC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  data_ctrl.data_timeout    = hsd->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(SD_GET_INSTANCE(hsd));

  /* Read Blocks in IT mode */
  if (blocks_nbr > 1U)
  {
    hsd->context = (SDMMC_CONTEXT_READ_MULTIPLE_BLOCK | SDMMC_CONTEXT_IT);
    cmd_type = SDMMC_CMD_READ_MULT_BLOCK;
  }
  else
  {
    hsd->context = (SDMMC_CONTEXT_READ_SINGLE_BLOCK | SDMMC_CONTEXT_IT);
    cmd_type = SDMMC_CMD_READ_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendReadBlocksCmd(SD_GET_INSTANCE(hsd), addr, cmd_type);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->context = SDMMC_CONTEXT_NONE;
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_ENABLE_IT(SD_GET_INSTANCE(hsd), (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_RXOVERR | SDMMC_IT_DATAEND \
                                         | SDMMC_FLAG_RXFIFOHF));

  return HAL_OK;
}

/**
  * @brief Writes block(s) to a specified address in a card. The Data transfer is managed in interrupt mode.
  * @param hsd        Pointer to a hal_sd_handle_t structure.
  * @param p_data     Pointer to the buffer that contain the data to transmit.
  * @param block_addr Block Address where data is written.
  * @param blocks_nbr Number of blocks to write.
  * @warning This API must be followed by a check on the card state through HAL_SD_GetCardState().
  * @warning It could also check the IT transfer process through the SD Tx interrupt event.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_WriteBlocks_IT(hal_sd_handle_t *hsd, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr)
{
  uint32_t error_code;
  uint32_t cmd_type;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t addr = block_addr;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hsd->sd_card.logical_blk_nbr);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (blocks_nbr == 0U) || ((addr + blocks_nbr) > hsd->sd_card.logical_blk_nbr))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_IDLE, HAL_SD_STATE_ACTIVE);

  /* Initialize data control register */
  SDMMC_CLEAR_DCTRL(SD_GET_INSTANCE(hsd));
  hsd->p_xfer_buff = (uint32_t *)(uint32_t)p_data;
  hsd->xfer_size_byte = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;

  if (hsd->type != SDMMC_SD_CARD_SDHC_SDXC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the SD DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hsd->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(SD_GET_INSTANCE(hsd));

  /* Write Blocks in Polling mode */
  if (blocks_nbr > 1U)
  {
    hsd->context = (SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK | SDMMC_CONTEXT_IT);
    cmd_type = SDMMC_CMD_WRITE_MULT_BLOCK;
  }
  else
  {
    hsd->context = (SDMMC_CONTEXT_WRITE_SINGLE_BLOCK | SDMMC_CONTEXT_IT);
    cmd_type = SDMMC_CMD_WRITE_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendWriteBlocksCmd(SD_GET_INSTANCE(hsd), addr, cmd_type);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->context = SDMMC_CONTEXT_NONE;
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Enable transfer interrupts */
  SDMMC_ENABLE_IT(SD_GET_INSTANCE(hsd), (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR | SDMMC_IT_DATAEND \
                                         | SDMMC_FLAG_TXFIFOHE));

  return HAL_OK;
}

/**
  * @brief Reads block(s) from a specified address in a card. The Data transfer is managed by DMA mode.
  * @param hsd        Pointer to a hal_sd_handle_t structure.
  * @param p_data     Pointer to the buffer that contain the received data.
  * @param block_addr Block Address from where the data is to be read.
  * @param blocks_nbr Number of SD blocks to read.
  * @warning This API must be followed by a check on the card state through HAL_SD_GetCardState().
  * @warning It could also check the DMA transfer process through the SD Rx interrupt event.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_ReadBlocks_DMA(hal_sd_handle_t *hsd, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr)
{
  uint32_t error_code;
  uint32_t cmd_type;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t addr = block_addr;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hsd->sd_card.logical_blk_nbr);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (blocks_nbr == 0U) || ((addr + blocks_nbr) > hsd->sd_card.logical_blk_nbr))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_IDLE, HAL_SD_STATE_ACTIVE);

  /* Initialize data control register */
  SDMMC_CLEAR_DCTRL(SD_GET_INSTANCE(hsd));

  /* Set address for SD card normal capacity */
  if (hsd->type != SDMMC_SD_CARD_SDHC_SDXC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the SD DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hsd->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(SD_GET_INSTANCE(hsd));

  SD_GET_INSTANCE(hsd)->IDMABASER = (uint32_t)p_data;
  SDMMC_SET_IDMACTRL(SD_GET_INSTANCE(hsd), SDMMC_IDMA_NORMAL_MODE | SDMMC_IDMACTRLR_IDMAEN);

  /* Read Blocks in DMA mode */
  if ((data_ctrl.data_length / SDMMC_BLOCK_SIZE_BYTE) > 1U)
  {
    hsd->context = (SDMMC_CONTEXT_READ_MULTIPLE_BLOCK | SDMMC_CONTEXT_DMA);
    cmd_type = SDMMC_CMD_READ_MULT_BLOCK;
  }
  else
  {
    hsd->context = (SDMMC_CONTEXT_READ_SINGLE_BLOCK | SDMMC_CONTEXT_DMA);
    cmd_type = SDMMC_CMD_READ_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendReadBlocksCmd(SD_GET_INSTANCE(hsd), addr, cmd_type);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->context = SDMMC_CONTEXT_NONE;
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Enable transfer interrupts */
  SDMMC_ENABLE_IT(SD_GET_INSTANCE(hsd), (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_RXOVERR | SDMMC_IT_DATAEND \
                                         | SDMMC_IT_IDMABTC));

  return HAL_OK;
}

/**
  * @brief Writes block(s) to a specified address in a card. The Data transfer is managed by DMA mode.
  * @param hsd        Pointer to a hal_sd_handle_t structure.
  * @param p_data     Pointer to the buffer that contain the data to transmit.
  * @param block_addr Block Address where data is written.
  * @param blocks_nbr Number of SD blocks to write.
  * @warning This API must be followed by a check on the card state through HAL_SD_GetCardState().
  * @warning It could also check the DMA transfer process through the SD Tx interrupt event.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_WriteBlocks_DMA(hal_sd_handle_t *hsd, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr)
{
  uint32_t error_code;
  uint32_t cmd_type;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t addr = block_addr;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hsd->sd_card.logical_blk_nbr);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (blocks_nbr == 0U) || ((addr + blocks_nbr) > hsd->sd_card.logical_blk_nbr))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_IDLE, HAL_SD_STATE_ACTIVE);

  /* Initialize data control register */
  SDMMC_CLEAR_DCTRL(SD_GET_INSTANCE(hsd));

  /* Set address for SD card normal capacity */
  if (hsd->type != SDMMC_SD_CARD_SDHC_SDXC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the SD DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hsd->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(SD_GET_INSTANCE(hsd));

  SD_GET_INSTANCE(hsd)->IDMABASER = (uint32_t)p_data;
  SDMMC_SET_IDMACTRL(SD_GET_INSTANCE(hsd), SDMMC_IDMA_NORMAL_MODE | SDMMC_IDMACTRLR_IDMAEN);

  /* Write Blocks in Polling mode */
  if ((data_ctrl.data_length / SDMMC_BLOCK_SIZE_BYTE) > 1U)
  {
    hsd->context = (SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK | SDMMC_CONTEXT_DMA);
    cmd_type = SDMMC_CMD_WRITE_MULT_BLOCK;
  }
  else
  {
    hsd->context = (SDMMC_CONTEXT_WRITE_SINGLE_BLOCK | SDMMC_CONTEXT_DMA);
    cmd_type = SDMMC_CMD_WRITE_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendWriteBlocksCmd(SD_GET_INSTANCE(hsd), addr, cmd_type);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->context = SDMMC_CONTEXT_NONE;
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Enable transfer interrupts */
  SDMMC_ENABLE_IT(SD_GET_INSTANCE(hsd), (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR | SDMMC_IT_DATAEND \
                                         | SDMMC_IT_IDMABTC));

  return HAL_OK;
}

#if defined (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1)
/**
  * @brief Reads block(s) from a specified address in a card. The Data transfer is managed by DMA mode.
  * @param hsd        Pointer to a hal_sd_handle_t structure.
  * @param block_addr Block Address from where data is to be read.
  * @param blocks_nbr Number of SD blocks to read.
  * @param p_q        Pointer to a hal_q_t structure that contains the configuration information for the Q.
  * @warning This API must be followed by a check on the card state through HAL_SD_GetCardState().
  * @warning It could also check the DMA transfer process through the SD Rx interrupt event.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_ReadBlocks_LinkedList(hal_sd_handle_t *hsd, uint32_t block_addr, uint32_t blocks_nbr,
                                          const hal_q_t *p_q)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t addr = block_addr;
  uint32_t error_code;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hsd->sd_card.logical_blk_nbr);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* check p_q pointer */
  if ((p_q == NULL) || (blocks_nbr == 0U) || ((addr + blocks_nbr) > hsd->sd_card.logical_blk_nbr))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_instance = SD_GET_INSTANCE(hsd);

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_IDLE, HAL_SD_STATE_ACTIVE);

  /* Set buffer address and buffer size in SDMMC peripheral */
  p_instance->IDMABASER = ((hal_sd_node_t *)p_q->p_head_node)->idma_buffer_base_addr;
  p_instance->IDMABSIZER = ((hal_sd_node_t *)p_q->p_head_node)->idma_buffer_size;
  /* Set linked-list base address and linked-list configuration */
  p_instance->IDMABAR = (uint32_t)p_q->p_head_node;
  p_instance->IDMALAR = ((hal_sd_node_t *)p_q->p_head_node)->idma_node_offset;

  /* Initialize data control register */
  SDMMC_CLEAR_DCTRL(SD_GET_INSTANCE(hsd));

  /* Set address for SD card normal capacity */
  if (hsd->type != SDMMC_SD_CARD_SDHC_SDXC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the SD DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hsd->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &data_ctrl);

  SDMMC_FIFORST_ENABLE(SD_GET_INSTANCE(hsd));
  SDMMC_CMDTRANS_ENABLE(SD_GET_INSTANCE(hsd));

  /* Enable IDMA and linked list mode */
  SDMMC_SET_IDMACTRL(SD_GET_INSTANCE(hsd), SDMMC_IDMA_LINKEDLIST_MODE | SDMMC_IDMACTRLR_IDMAEN);
  hsd->context = (SDMMC_CONTEXT_READ_MULTIPLE_BLOCK | SDMMC_CONTEXT_DMA);

  /* Read Multi Block command */
  error_code = SDMMC_SendReadBlocksCmd(SD_GET_INSTANCE(hsd), addr, SDMMC_CMD_READ_MULT_BLOCK);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->context = SDMMC_CONTEXT_NONE;
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Enable transfer interrupts */
  SDMMC_ENABLE_IT(SD_GET_INSTANCE(hsd), (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_RXOVERR | SDMMC_IT_DATAEND \
                                         | SDMMC_IT_IDMABTC));

  return HAL_OK;
}

/**
  * @brief Writes block(s) to a specified address in a card. The Data transfer is managed by DMA mode.
  * @param hsd        Pointer to a hal_sd_handle_t structure.
  * @param block_addr Block Address where the data is written.
  * @param blocks_nbr Number of SD blocks to write.
  * @param p_q        Pointer to a hal_q_t structure that contains the configuration information for the Q.
  * @warning This API must be followed by a check on the card state through HAL_SD_GetCardState().
  * @warning It could also check the DMA transfer process through the SD Tx interrupt event.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_WriteBlocks_LinkedList(hal_sd_handle_t *hsd, uint32_t block_addr, uint32_t blocks_nbr,
                                           const hal_q_t *p_q)
{
  uint32_t error_code;
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t addr = block_addr;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hsd->sd_card.logical_blk_nbr);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_q == NULL) || (blocks_nbr == 0U) || ((addr + blocks_nbr) > hsd->sd_card.logical_blk_nbr))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_instance = SD_GET_INSTANCE(hsd);

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_IDLE, HAL_SD_STATE_ACTIVE);

  /* Set buffrer address and buffer size in SDMMC peripheral */
  p_instance->IDMABASER = ((hal_sd_node_t *)p_q->p_head_node)->idma_buffer_base_addr;
  p_instance->IDMABSIZER = ((hal_sd_node_t *)p_q->p_head_node)->idma_buffer_size;
  /* Set linked-list base address and linked-list configuration */
  p_instance->IDMABAR = (uint32_t)p_q->p_head_node;
  p_instance->IDMALAR = ((hal_sd_node_t *)p_q->p_head_node)->idma_node_offset;

  /* Initialize data control register */
  SDMMC_CLEAR_DCTRL(SD_GET_INSTANCE(hsd));

  /* Set address for SD card normal capacity */
  if (hsd->type != SDMMC_SD_CARD_SDHC_SDXC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the SD DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hsd->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &data_ctrl);

  SDMMC_CMDTRANS_ENABLE(SD_GET_INSTANCE(hsd));
  SDMMC_SET_IDMACTRL(SD_GET_INSTANCE(hsd), SDMMC_IDMA_LINKEDLIST_MODE | SDMMC_IDMACTRLR_IDMAEN);

  /* Write Blocks in Polling mode */
  hsd->context = (SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK | SDMMC_CONTEXT_DMA);

  /* Write Multiple Block command */
  error_code = SDMMC_SendWriteBlocksCmd(SD_GET_INSTANCE(hsd), addr, SDMMC_CMD_WRITE_MULT_BLOCK);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->context = SDMMC_CONTEXT_NONE;
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Enable transfer interrupts */
  SDMMC_ENABLE_IT(SD_GET_INSTANCE(hsd), (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR | SDMMC_IT_DATAEND \
                                         | SDMMC_IT_IDMABTC));

  return HAL_OK;
}
#endif /* USE_HAL_SD_LINKEDLIST */

/**
  * @brief Abort the current transfer.
  * @param  hsd Pointer to a hal_sd_handle_t structure.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_BUSY  Concurrent process ongoing.
  * @retval HAL_ERROR Operation completed with error.
  */
hal_status_t HAL_SD_Abort(hal_sd_handle_t *hsd)
{
  uint32_t error_code;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_ACTIVE);

  HAL_CHECK_UPDATE_STATE(hsd, global_state, (uint32_t)HAL_SD_STATE_ACTIVE, HAL_SD_STATE_ABORT);

  SDMMC_DISABLE_IT(SD_GET_INSTANCE(hsd), SDMMC_IT_DATAEND | SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR \
                   | SDMMC_IT_RXOVERR);
  SDMMC_CMDTRANS_DISABLE(SD_GET_INSTANCE(hsd));

  /* Send the CMD12 in all cases in order to stop the data transfers.
   * In case the data transfer just finished, the external memory is not responding and returns
   * HAL_SD_ERROR_CMD_RSP_TIMEOUT.
   * In case the data transfer aborted, the external memory responds and returns HAL_SD_ERROR_NONE.
   * Another scenario returns HAL_ERROR.
   */
  error_code = SDMMC_SendStopTransferCmd(SD_GET_INSTANCE(hsd), hsd->stop_xfer_timeout_ms);
  if ((error_code != HAL_SD_ERROR_NONE) && (error_code != HAL_SD_ERROR_CMD_RSP_TIMEOUT))
  {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */

    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();
  if ((SD_GET_INSTANCE(hsd)->DCTRL & SDMMC_DCTRL_DTDIR) == SDMMC_TRANSFER_DIR_TO_CARD)
  {
    if (error_code == HAL_SD_ERROR_NONE)
    {
      while (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DABORT | SDMMC_FLAG_BUSYD0END) != 0U)
      {
        if ((HAL_GetTick() - tickstart) >=  hsd->data_timeout_cycle)
        {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
          hsd->last_error_codes |= HAL_SD_ERROR_TIMEOUT;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
          hsd->global_state = HAL_SD_STATE_IDLE;
          return HAL_ERROR;
        }
      }
    }

    if (error_code == HAL_SD_ERROR_CMD_RSP_TIMEOUT)
    {
      while (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DATAEND) != 0U)
      {
        if ((HAL_GetTick() - tickstart) >=  hsd->data_timeout_cycle)
        {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
          hsd->last_error_codes = HAL_SD_ERROR_TIMEOUT;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */

          hsd->global_state = HAL_SD_STATE_IDLE;
          return HAL_ERROR;
        }
      }
    }
  }
  else if ((SD_GET_INSTANCE(hsd)->DCTRL & SDMMC_DCTRL_DTDIR) == SDMMC_TRANSFER_DIR_TO_SDMMC)
  {
    while (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DABORT | SDMMC_FLAG_DATAEND) != 0U)
    {
      if ((HAL_GetTick() - tickstart) >=  hsd->data_timeout_cycle)
      {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
        hsd->last_error_codes = HAL_SD_ERROR_TIMEOUT;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */

        hsd->global_state = HAL_SD_STATE_IDLE;
        return HAL_ERROR;
      }
    }
  }
  else
  {
    /* Nothing to do */
  }

  /* The reason of all these while conditions previously is that we need to wait the SDMMC and clear the appropriate
   *  flags that will be set depending of the abort/non abort of the memory.
   *  Not waiting for the SDMMC flags will cause the next SDMMC_DISABLE_IDMA to not get cleared and will result in next
   *  SDMMC read/write operation to fail.
   */
  SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_BUSYD0END);
  SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_DATA_FLAGS);
  SDMMC_CLEAR_IDMACTRL(SD_GET_INSTANCE(hsd));

  hsd->context = SDMMC_CONTEXT_NONE;
  hsd->global_state = HAL_SD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Abort the current transfer in IT mode.
  * @param  hsd        Pointer to a hal_sd_handle_t structure.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_BUSY  Concurrent process ongoing.
  * @retval HAL_ERROR Operation completed with error.
  */
hal_status_t HAL_SD_Abort_IT(hal_sd_handle_t *hsd)
{
  hal_sd_card_state_t card_state;
  uint32_t error_code = HAL_SD_ERROR_NONE;

  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_ACTIVE);

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_ACTIVE, HAL_SD_STATE_ABORT);

  /* Disable All interrupts */
  SDMMC_DISABLE_IT(SD_GET_INSTANCE(hsd), SDMMC_IT_DATAEND | SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR \
                   | SDMMC_IT_RXOVERR);

  /* If IDMA Context, disable Internal DMA */
  SDMMC_CLEAR_IDMACTRL(SD_GET_INSTANCE(hsd));
  SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_DATA_FLAGS);

  card_state = (hal_sd_card_state_t)SD_GetCardState(hsd);

  if ((card_state == HAL_SD_CARD_RECEIVING) || (card_state == HAL_SD_CARD_SENDING))
  {
    error_code = SDMMC_SendStopTransferCmd(SD_GET_INSTANCE(hsd), hsd->stop_xfer_timeout_ms);
  }
  if (error_code != HAL_SD_ERROR_NONE)
  {
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }
  else
  {
#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
    hsd->p_abort_callback(hsd);
#else
    HAL_SD_AbortCallback(hsd);
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */
  }

  /* Set the new state */
  hsd->global_state = HAL_SD_STATE_IDLE;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup SD_Exported_Functions_Group4 IRQHandler and Callbacks Functions
  * @{
    This subsection provides a set of callback functions allowing to manage the data transfer from/to SD card.
  */
/**
  * @brief This function handles SD card interrupt request.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  */
void HAL_SD_IRQHandler(hal_sd_handle_t *hsd)
{
  uint32_t error_code;
  uint32_t context;
  hal_sd_event_cb_t cb_event;
  uint32_t its;
  uint32_t flags;

  ASSERT_DBG_PARAM(hsd != NULL);

  its     = SDMMC_READ_REG(SD_GET_INSTANCE(hsd), MASKR);
  flags   = SDMMC_READ_REG(SD_GET_INSTANCE(hsd), STAR);
  context = hsd->context;

  /* Handle RX FIFO interrupts */
  if ((STM32_READ_BIT((flags & its), SDMMC_FLAG_RXFIFOHF) != 0U) && ((context & SDMMC_CONTEXT_IT) != 0U))
  {
    SD_Read_IT(hsd);
    return;
  }

  /* Handle TX FIFO interrupts */
  if ((STM32_READ_BIT((flags & its), SDMMC_FLAG_TXFIFOHE) != 0U) && ((context & SDMMC_CONTEXT_IT) != 0U))
  {
    SD_Write_IT(hsd);
    return;
  }

  /* Handle Data End interrupts */
  if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DATAEND) != 0U)
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DATAEND);
    SDMMC_DISABLE_IT(SD_GET_INSTANCE(hsd), SDMMC_IT_DATAEND  | SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT  \
                     | SDMMC_IT_TXUNDERR | SDMMC_IT_RXOVERR  | SDMMC_IT_TXFIFOHE | SDMMC_IT_RXFIFOHF  \
                     | SDMMC_IT_IDMABTC);
    SDMMC_CMDTRANS_DISABLE(SD_GET_INSTANCE(hsd));
    if ((context & SDMMC_CONTEXT_DMA) != 0U)
    {
      SDMMC_CLEAR_DLEN(SD_GET_INSTANCE(hsd));
      SDMMC_CLEAR_DCTRL(SD_GET_INSTANCE(hsd));
      SDMMC_CLEAR_IDMACTRL(SD_GET_INSTANCE(hsd));
    }

    if (((context & SDMMC_CONTEXT_READ_MULTIPLE_BLOCK) != 0U) || ((context & SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK) != 0U))
    {
      error_code = SDMMC_SendStopTransferCmd(SD_GET_INSTANCE(hsd), hsd->stop_xfer_timeout_ms);
      if (error_code != HAL_SD_ERROR_NONE)
      {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
        hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
        hsd->p_error_callback(hsd);
#else
        HAL_SD_ErrorCallback(hsd);
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */
      }
    }

    if ((context & SDMMC_CONTEXT_IT) != 0U)
    {
      SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_DATA_FLAGS);
    }

    hsd->context = SDMMC_CONTEXT_NONE;
    if (((context & SDMMC_CONTEXT_WRITE_SINGLE_BLOCK) != 0U) || ((context & SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK) != 0U))
    {
      cb_event = HAL_SD_EVENT_CB_TX_CPLT;
    }
    else
    {
      cb_event = HAL_SD_EVENT_CB_RX_CPLT;
    }
    hsd->global_state = HAL_SD_STATE_IDLE;
#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
    hsd->p_xfer_cplt_callback(hsd, cb_event);
#else
    HAL_SD_XferCpltCallback(hsd, cb_event);
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */
  }

#if defined (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1)
  /* Handle linked-list interrupts */
  if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_IDMABTC) != 0U)
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_IDMABTC);

    if ((context & SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK) != 0U)
    {
      cb_event = HAL_SD_EVENT_CB_TX_NODE_CPLT;
    }
    else
    {
      cb_event = HAL_SD_EVENT_CB_RX_NODE_CPLT;
    }
#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
    hsd->p_xfer_cplt_callback(hsd, cb_event);
#else
    HAL_SD_XferCpltCallback(hsd, cb_event);
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */
  }
#endif /* (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1) */

  /* Handle Error interrupts */
  if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_RXOVERR \
                           | SDMMC_FLAG_TXUNDERR) != 0U)
  {
    error_code = SDMMC_READ_REG(SD_GET_INSTANCE(hsd), STAR);
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    if ((error_code & SDMMC_IT_DCRCFAIL) != 0U)
    {
      hsd->last_error_codes |= HAL_SD_ERROR_DATA_CRC_FAIL;
    }
    if ((error_code & SDMMC_IT_DTIMEOUT) != 0U)
    {
      hsd->last_error_codes |= HAL_SD_ERROR_DATA_TIMEOUT;
    }
    if ((error_code & SDMMC_IT_RXOVERR) != 0U)
    {
      hsd->last_error_codes |= HAL_SD_ERROR_RX_OVERRUN;
    }
    if ((error_code & SDMMC_IT_TXUNDERR) != 0U)
    {
      hsd->last_error_codes |= HAL_SD_ERROR_TX_UNDERRUN;
    }
#endif /* USE_HAL_SD_GET_LAST_ERRORS */

    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_DATA_FLAGS);

    /* Disable all interrupts */
    SDMMC_DISABLE_IT(SD_GET_INSTANCE(hsd), SDMMC_IT_DATAEND | SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT \
                     | SDMMC_IT_TXUNDERR | SDMMC_IT_RXOVERR);

    SDMMC_CMDTRANS_DISABLE(SD_GET_INSTANCE(hsd));
    SDMMC_FIFORST_ENABLE(SD_GET_INSTANCE(hsd));
    SDMMC_CMDSTOP_ENABLE(SD_GET_INSTANCE(hsd));
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= SDMMC_SendStopTransferCmd(SD_GET_INSTANCE(hsd), hsd->stop_xfer_timeout_ms);
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    SDMMC_CMDSTOP_DISABLE(SD_GET_INSTANCE(hsd));
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DABORT);
    hsd->context      = SDMMC_CONTEXT_NONE;

    if ((context & SDMMC_CONTEXT_DMA) != 0U)
    {
      SDMMC_DISABLE_IT(SD_GET_INSTANCE(hsd), SDMMC_IT_IDMABTC);
      SD_GET_INSTANCE(hsd)->IDMACTRLR = SDMMC_DISABLE_IDMA;
    }
    hsd->global_state = HAL_SD_STATE_IDLE;
#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
    hsd->p_error_callback(hsd);
#else
    HAL_SD_ErrorCallback(hsd);
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */
  }
}

/**
  * @brief Xfer Transfer completed callbacks.
  * @param hsd        Pointer to a hal_sd_handle_t structure.
  * @param cb_event   Xfer callback event in hal_sd_event_cb_t structure.
  */
__WEAK void HAL_SD_XferCpltCallback(hal_sd_handle_t *hsd, hal_sd_event_cb_t cb_event)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hsd);
  STM32_UNUSED(cb_event);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_SD_TxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief error callbacks.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  */
__WEAK void HAL_SD_ErrorCallback(hal_sd_handle_t *hsd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hsd);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_SD_ErrorCallback can be implemented in the user file
   */
}

/**
  * @brief Abort callbacks.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  */
__WEAK void HAL_SD_AbortCallback(hal_sd_handle_t *hsd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hsd);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_SD_AbortCallback can be implemented in the user file
   */
}

/**
  * @brief Enable/Disable the SD Transceiver 1.8V Mode Callback.
  * @param hsd   Pointer to a hal_sd_handle_t structure.
  * @param state Voltage Switch State.
  */
__WEAK  void HAL_SD_DriveTransceiver_1_8V_Callback(hal_sd_handle_t *hsd, hal_sd_transceiver_state_t state)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hsd);
  STM32_UNUSED(state);
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_SD_DriveTransceiver_1_8V_Callback could be implemented in the user file
   */
}

#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
/**
  * @brief Register the SD Xfer Callback to be used instead of the weak HAL_SD_XferCpltCallback predefined callback.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param callback pointer to the Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_SD_RegisterXferCpltCallback(hal_sd_handle_t *hsd, hal_sd_xfer_cb_t callback)
{
  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsd->p_xfer_cplt_callback = callback;

  return HAL_OK;
}

/**
  * @brief Register the SD Error Callback to be used instead of the weak HAL_SD_ErrorCallback predefined callback.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param callback Pointer to the Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_SD_RegisterErrorCallback(hal_sd_handle_t *hsd, hal_sd_cb_t callback)
{
  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsd->p_error_callback = callback;

  return HAL_OK;
}

/**
  * @brief Register the SD Abort Callback to be used instead of the weak HAL_SD_AbortCallback predefined callback.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param callback Pointer to the Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_SD_RegisterAbortCallback(hal_sd_handle_t *hsd, hal_sd_cb_t callback)
{
  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsd->p_abort_callback = callback;

  return HAL_OK;
}

/**
  * @brief Register a User SD Transceiver Callback to be used instead of the weak HAL_SD_DriveTransceiver_1_8V_Callback
  *        predefined callback.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param callback Pointer to the Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_SD_RegisterTransceiverCallback(hal_sd_handle_t *hsd, hal_sd_transceiver_cb_t callback)
{
  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsd->p_transceiver_1_8V_callback = callback;

  return HAL_OK;
}
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup SD_Exported_Functions_Group5 SD card related functions
  * @{
    This subsection provides a set of functions allowing to control the SD card operations.
  */

/**
  * @brief Get the SD state.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval hal_sd_state_t  Current SD state.
  */
hal_sd_state_t HAL_SD_GetState(const hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  return hsd->global_state;
}

/**
  * @brief Get the current SD card data state.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval hal_sd_card_state_t SD card State.
  */
hal_sd_card_state_t HAL_SD_GetCardState(const hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, ((uint32_t)HAL_SD_STATE_IDLE) | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  return (hal_sd_card_state_t)(SD_GetCardState(hsd));
}

/**
  * @brief Get the SD status information.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param p_status Pointer to the hal_sd_card_status_t structure that must contain the SD card status information.
  * @note this must be called if there is no SD transaction ongoing.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Completed successfully.
  */
hal_status_t HAL_SD_GetCardStatus(hal_sd_handle_t *hsd, hal_sd_card_status_t *p_status)
{
  uint32_t sd_status[16];
  uint32_t *p_sd_card_status = sd_status;
  uint32_t speed_grade;
  uint32_t unit_size;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_status != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_status == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (SD_Card_SendStatus(hsd, sd_status) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }
  else
  {
    *p_sd_card_status = (((sd_status[0] & SDMMC_0TO7BITS) << 24)  | ((sd_status[0] & SDMMC_8TO15BITS) << 8) | \
                         ((sd_status[0] & SDMMC_16TO23BITS) >> 8) | ((sd_status[0] & SDMMC_24TO31BITS) >> 24));
    p_sd_card_status++;
    *p_sd_card_status = (((sd_status[1] & SDMMC_0TO7BITS) << 24)  | ((sd_status[1] & SDMMC_8TO15BITS) << 8) | \
                         ((sd_status[1] & SDMMC_16TO23BITS) >> 8) | ((sd_status[1] & SDMMC_24TO31BITS) >> 24));
    p_sd_card_status++;
    *p_sd_card_status = (((sd_status[2] & SDMMC_0TO7BITS) << 24)  | ((sd_status[2] & SDMMC_8TO15BITS) << 8) | \
                         ((sd_status[2] & SDMMC_16TO23BITS) >> 8) | ((sd_status[2] & SDMMC_24TO31BITS) >> 24));
    p_sd_card_status++;
    *p_sd_card_status = (((sd_status[3] & SDMMC_0TO7BITS) << 24)  | ((sd_status[3] & SDMMC_8TO15BITS) << 8) | \
                         ((sd_status[3] & SDMMC_16TO23BITS) >> 8) | ((sd_status[3] & SDMMC_24TO31BITS) >> 24));
    p_sd_card_status++;
    *p_sd_card_status = (((sd_status[4] & SDMMC_0TO7BITS) << 24)  | ((sd_status[4] & SDMMC_8TO15BITS) << 8) | \
                         ((sd_status[4] & SDMMC_16TO23BITS) >> 8) | ((sd_status[4] & SDMMC_24TO31BITS) >> 24));

    p_status->data_bus_width           = (uint8_t)SDMMC_READ_FIELD(sd_status[0], SDMMC_SD_CARD_DATA_BUS_WIDTH_MSK,
                                                                   SDMMC_SD_CARD_DATA_BUS_WIDTH_POS);
    p_status->secured_mode             = (uint8_t)SDMMC_READ_FIELD(sd_status[0], SDMMC_SD_CARD_SECURED_MODE_MSK,
                                                                   SDMMC_SD_CARD_SECURED_MODE_POS);
    p_status->card_type                = (uint16_t)SDMMC_READ_FIELD(sd_status[0], SDMMC_SD_CARD_TYPE_MSK,
                                                                    SDMMC_SD_CARD_TYPE_POS);
    p_status->protected_area_size_byte = SDMMC_READ_FIELD(sd_status[1], SDMMC_SD_CARD_SIZE_OF_PROTECTED_AREA_MSK,
                                                          SDMMC_SD_CARD_SIZE_OF_PROTECTED_AREA_POS);
    p_status->speed_class              = (uint8_t)SDMMC_READ_FIELD(sd_status[2], SDMMC_SD_CARD_SPEED_CLASS_MSK,
                                                                   SDMMC_SD_CARD_SPEED_CLASS_POS);
    p_status->performance_move         = (uint8_t)SDMMC_READ_FIELD(sd_status[2], SDMMC_SD_CARD_PERFORMANCE_MOVE_MSK,
                                                                   SDMMC_SD_CARD_PERFORMANCE_MOVE_POS);
    p_status->allocation_unit_size     = (uint8_t)SDMMC_READ_FIELD(sd_status[2], SDMMC_SD_CARD_AU_SIZE_MSK,
                                                                   SDMMC_SD_CARD_AU_SIZE_POS);
    p_status->erase_size               = (uint16_t)SDMMC_READ_FIELD(sd_status[2], SDMMC_SD_CARD_ERASE_SIZE1_MSK,
                                                                    SDMMC_SD_CARD_ERASE_SIZE1_POS) | \
                                         (uint16_t)SDMMC_READ_FIELD(sd_status[3], SDMMC_SD_CARD_ERASE_SIZE2_MSK,
                                                                    SDMMC_SD_CARD_ERASE_SIZE2_POS);
    p_status->erase_timeout            = (uint8_t)SDMMC_READ_FIELD(sd_status[3], SDMMC_SD_CARD_ERASE_TIMEOUT_MSK,
                                                                   SDMMC_SD_CARD_ERASE_TIMEOUT_POS);
    p_status->erase_offset             = (uint8_t)SDMMC_READ_FIELD(sd_status[3], SDMMC_SD_CARD_ERASE_OFFSET_MSK,
                                                                   SDMMC_SD_CARD_ERASE_OFFSET_POS);
    p_status->uhs_speed_grade          = (uint8_t)SDMMC_READ_FIELD(sd_status[3], SDMMC_SD_CARD_UHS_SPEED_GRADE_MSK,
                                                                   SDMMC_SD_CARD_UHS_SPEED_GRADE_POS);
    p_status->uhs_allocation_unit_size = (uint8_t)SDMMC_READ_FIELD(sd_status[3], SDMMC_SD_CARD_UHS_AU_SIZE_MSK,
                                                                   SDMMC_SD_CARD_UHS_AU_SIZE_POS);
    p_status->video_speed_class        = (uint8_t)SDMMC_READ_FIELD(sd_status[4], SDMMC_SD_CARD_VIDEO_SPEED_CLASS_MSK,
                                                                   SDMMC_SD_CARD_VIDEO_SPEED_CLASS_POS);
  }

  if (SD_Card_SetBlockSize(hsd, SDMMC_BLOCK_SIZE_BYTE) != HAL_OK)
  {
    hsd->global_state = HAL_SD_STATE_IDLE;
    return HAL_ERROR;
  }

  speed_grade = p_status->uhs_speed_grade;
  unit_size = p_status->uhs_allocation_unit_size;
  /* Set SD card speed */
  if ((hsd->type == SDMMC_SD_CARD_SDHC_SDXC) && ((speed_grade != 0U) || (unit_size != 0U)))
  {
    hsd->speed = SDMMC_SD_CARD_ULTRA_HIGH_SPEED;
  }
  else if (hsd->type == SDMMC_SD_CARD_SDHC_SDXC)
  {
    hsd->speed = SDMMC_SD_CARD_HIGH_SPEED;
  }
  else
  {
    hsd->speed = SDMMC_SD_CARD_NORMAL_SPEED;
  }

  return HAL_OK;
}

/**
  * @brief Get the SD card info.
  * @param hsd         Pointer to a hal_sd_handle_t structure.
  * @param p_card_info Pointer to the hal_sd_card_info_t structure that must contain the SD card status information.
  */
void HAL_SD_GetCardInfo(const hal_sd_handle_t *hsd, hal_sd_card_info_t *p_card_info)
{
  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_card_info != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  p_card_info->relative_addr         = (uint32_t)(hsd->sd_card.relative_addr);
  p_card_info->blk_nbr               = (uint32_t)(hsd->sd_card.blk_nbr);
  p_card_info->blk_size_byte         = (uint32_t)(hsd->sd_card.blk_size_byte);
  p_card_info->logical_blk_nbr       = (uint32_t)(hsd->sd_card.logical_blk_nbr);
  p_card_info->logical_blk_size_byte = (uint32_t)(hsd->sd_card.logical_blk_size_byte);
}

#if defined (USE_HAL_SD_GET_CID) && (USE_HAL_SD_GET_CID == 1)
/**
  * @brief Get information of the card which are stored on the CID register.
  * @param hsd  Pointer to a hal_sd_handle_t structure.
  * @param p_cid Pointer to a hal_sd_card_cid_t structure that contains all CID register parameters.
  */
void HAL_SD_GetCardCID(const hal_sd_handle_t *hsd, hal_sd_card_cid_t *p_cid)
{
  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_cid != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  p_cid->manufacturer_id    = hsd->cid.manufacturer_id;
  p_cid->oem_app_id         = hsd->cid.oem_app_id;
  p_cid->product_name_part1 = hsd->cid.product_name_part1;
  p_cid->product_name_part2 = hsd->cid.product_name_part2;
  p_cid->product_rev        = hsd->cid.product_rev;
  p_cid->product_serial_nbr = hsd->cid.product_serial_nbr;
  p_cid->reserved1          = hsd->cid.reserved1;
  p_cid->manufacturer_date  = hsd->cid.manufacturer_date;
  p_cid->cid_crc            = hsd->cid.cid_crc;
  p_cid->reserved2          = hsd->cid.reserved2;
}
#endif /* USE_HAL_SD_GET_CID */

/**
  * @brief Configure the speed bus mode.
  * @param hsd        Pointer to a hal_sd_handle_t structure.
  * @param speed_mode Specifies the SD card speed bus mode.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
hal_status_t HAL_SD_SwitchSpeedMode(hal_sd_handle_t *hsd, hal_sd_speed_mode_t speed_mode)
{
  uint32_t switch_speed_mode;
  uint32_t tick_start;
  sdmmc_config_t sd_config;

  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE);

  if (hsd->speed == SDMMC_SD_CARD_ULTRA_HIGH_SPEED)
  {
    SDMMC_GetConfig(SD_GET_INSTANCE(hsd), &sd_config);
    if (sd_config.bus_wide != SDMMC_BUS_WIDE_4BIT)
    {
      /* Use 4 parallel data lines to change the bus speed mode */
      if (SD_SetWideBus(hsd, HAL_SD_BUS_WIDE_4BIT) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
  }

  if (SD_GetSpeedMode(hsd, speed_mode, &switch_speed_mode) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (SD_SetSpeedMode(hsd, switch_speed_mode) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Verify that SD card is ready to use after Speed mode switch */
  tick_start = HAL_GetTick();
  while (SD_GetCardState(hsd) != (uint32_t)HAL_SD_CARD_TRANSFER)
  {
    if ((HAL_GetTick() - tick_start) >=  SDMMC_CMD_TIMEOUT)
    {
      return HAL_ERROR;
    }
  }

  if (SD_Card_SetBlockSize(hsd, SDMMC_BLOCK_SIZE_BYTE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

#if defined (USE_HAL_SD_GET_SPEC_VERSION) && (USE_HAL_SD_GET_SPEC_VERSION == 1)
/**
  * @brief Get the supported specification version supported by the SD card.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval hal_sd_specification_version_t SD specification version.
  */
hal_sd_specification_version_t HAL_SD_GetCardSpecVersion(const hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  return hsd->version;
}
#endif /* USE_HAL_SD_GET_SPEC_VERSION */

#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
/**
  * @brief Get last errors codes.
  * @param hsd Pointer to SD handle.
  * @retval uint32_t Last errors codes which can be a combination of @ref SD_Error_Status.
  */
uint32_t HAL_SD_GetLastErrorCodes(const hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  return (hsd->last_error_codes);
}
#endif /* USE_HAL_SD_GET_LAST_ERRORS */

#if defined (USE_HAL_SD_USER_DATA) && (USE_HAL_SD_USER_DATA == 1)
/**
  * @brief Store the user data into the SD handle.
  * @param hsd         Pointer to SD handle.
  * @param p_user_data Pointer to the user data.
  */
void HAL_SD_SetUserData(hal_sd_handle_t *hsd, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  hsd->p_user_data = p_user_data;
}

/**
  * @brief Retrieve the user data from the SD handle.
  * @param hsd Pointer to SD channel handle.
  * @retval Pointer to the user data.
  */
const void *HAL_SD_GetUserData(const hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  return (hsd->p_user_data);
}
#endif /* USE_HAL_SD_USER_DATA */

/** @brief  Return the peripheral clock frequency for SD card.
  * @param  hsd Pointer to a hal_sd_handle_t structure.
  * @retval uint32_t Frequency in Hz.
  *         0 if the source clock of the SD is not configured or not ready.
  */
uint32_t HAL_SD_GetClockFreq(const hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM((hsd != NULL));
  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT | (uint32_t)HAL_SD_STATE_CARD_REMOVED);

  return HAL_RCC_SDMMC_GetKernelClkFreq(SD_GET_INSTANCE(hsd));
}
/**
  * @}
  */

/** @addtogroup SD_Exported_Functions_Group7 linked-list queue functions
  * @{
This subsection provides a set of functions allowing to manage the SD linked-list node and queue:
- Call the function HAL_SD_FillNodeConfig() to fill the node according to configured parameter
  within hal_sd_node_config_t structure.
- Call the function HAL_SD_GetNodeConfig() to get the SD linked-list node.
- Call the function HAL_SD_SetNodeDataBufferState() to set the SD linked list node data buffer state.
- Call the function HAL_SD_GetNodeDataBufferState() to get the SD linked list node data buffer state.
- Call the function HAL_SD_GetNodeInfo() to get the SD linked list node information.
- Call the function HAL_SD_SetNodeAddress() to set the SD linked list node address.
- Call the function HAL_SD_GetNodeAddress() to get the SD linked list node address.
  */
#if defined (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1)
/**
  * @brief Build the SD linked-list node.
  * @param p_node     Pointer to new node to build.
  * @param p_buffer   Pointer to buffer node.
  * @param size_byte  size of the node in byte.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_FillNodeConfig(hal_sd_node_t *p_node, void *p_buffer, uint32_t size_byte)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_buffer != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_node == NULL) || (p_buffer == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Configure the Link Node registers */
  p_node->idma_buffer_base_addr = (uint32_t)p_buffer;
  p_node->idma_buffer_size      = size_byte;
  p_node->idma_node_offset      = SDMMC_IDMALAR_ULS | SDMMC_IDMALAR_ABR | SDMMC_IDMALAR_ULA;

  return HAL_OK;
}

/**
  * @brief Get the SD node configuration.
  * @param p_node      Pointer to hal_sd_node_t node structure.
  * @param p_buffer    Pointer to buffer node.
  * @param p_size_byte Pointer to the size of the node in byte.
  */
void HAL_SD_GetNodeConfig(const hal_sd_node_t *p_node, uint32_t *p_buffer, uint32_t *p_size_byte)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_buffer != NULL);
  ASSERT_DBG_PARAM(p_size_byte != NULL);

  /* Get SDMMC node Configuration */
  *p_buffer = p_node->idma_buffer_base_addr;
  *p_size_byte = p_node->idma_buffer_size;
}

/**
  * @brief Set SD linked list node data buffer state.
  * @param p_node Pointer to node.
  * @param state  Node state.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SD_SetNodeDataBufferState(const hal_sd_node_t *p_node, hal_sd_node_state_t state)
{
  ASSERT_DBG_PARAM(p_node != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  SDMMC_SetNodeDataBufferState(p_node->idma_node_offset, (uint32_t) state);

  return HAL_OK;
}

/**
  * @brief Get SD linked list node data buffer state.
  * @param p_node Pointer to node.
  * @retval HAL_SD_DATA_BUFFER_NOT_READY SD Data buffer node is not ready.
  * @retval HAL_SD_DATA_BUFFER_READY     SD Data buffer node is ready.
  */
hal_sd_node_state_t HAL_SD_GetNodeDataBufferState(const hal_sd_node_t *p_node)
{
  ASSERT_DBG_PARAM(p_node != NULL);

  return (hal_sd_node_state_t)(uint32_t)(STM32_READ_BIT(p_node->idma_node_offset, SDMMC_IDMALAR_ABR));
}
#endif /* (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1) */
/**
  * @}
  */

/** @addtogroup SD_Exported_Functions_Group8 SD Delay Block functions
  * @{
This subsection provides a set of functions allowing to configure the delay block:
- Call HAL_SD_SetConfigDlybDelay() to set the SD delay block configuration.
- Call HAL_SD_GetDlybOutputClockPhase() to get the SD delay block output clock phase.
- Call HAL_SD_CalculateDlybMaxClockPhase() to calculate the SD delay block maximum output clock phase.
- Call HAL_SD_EnableDlyb() to enable the SD delay block peripheral.
- Call HAL_SD_DisableDlyb() to disable SD the delay clock peripheral.
- Call HAL_SD_IsEnabledDlyb() to check whether the delay block peripheral is enabled or not.
  */
/**
  * @brief Set the SD delay block configuration.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @param clock_phase_value The selected output clock phase value will be stored.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    The delay is correctly set.
  */
hal_status_t HAL_SD_SetConfigDlybDelay(const hal_sd_handle_t *hsd, uint32_t clock_phase_value)
{
  DLYB_TypeDef *instance;
  dlyb_state_t state;

  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, HAL_SD_STATE_IDLE);

  instance = SDMMC_GET_DLYB_INSTANCE(SD_GET_INSTANCE(hsd));

  state = DLYB_IsEnabled(instance);
  DLYB_Enable(instance);
  if (DLYB_ConfigureUnitDelay(instance) != DLYB_CORE_OK)
  {
    return HAL_ERROR;
  }
  DLYB_SetOutputClockPhase(instance, clock_phase_value);

  if (state == DLYB_DISABLED)
  {
    DLYB_Disable(instance);
  }

  return HAL_OK;
}

/**
  * @brief Get the SD delay block output clock phase.
  * @param  hsd Pointer to a hal_sd_handle_t structure.
  * @retval uint32_t output clock phase value.
  */
uint32_t HAL_SD_GetDlybOutputClockPhase(const hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  return (DLYB_GetOutputClockPhase(SDMMC_GET_DLYB_INSTANCE(SD_GET_INSTANCE(hsd))));
}

/**
  * @brief Calculate the SD delay block maximum output clock phase.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @param p_max_clock_phase Pointer to the variable where the maximum clock phase value to be stored.
  * @retval HAL_INVALID_PARAM Invalid p_max_clock_phase parameter.
  * @retval HAL_ERROR         The max clock phase is not correctly calculated.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            The max clock phase is correctly calculated.
  */
hal_status_t HAL_SD_CalculateDlybMaxClockPhase(hal_sd_handle_t *hsd, uint32_t *p_max_clock_phase)
{
  hal_status_t status = HAL_ERROR;
  DLYB_TypeDef *instance;
  uint32_t sel;
  uint32_t unit;
  dlyb_state_t state;

  ASSERT_DBG_PARAM(hsd != NULL);
  ASSERT_DBG_PARAM(p_max_clock_phase != NULL);

  ASSERT_DBG_STATE(hsd->global_state, HAL_SD_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_max_clock_phase == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsd, global_state, HAL_SD_STATE_IDLE, HAL_SD_STATE_ACTIVE);

  instance = SDMMC_GET_DLYB_INSTANCE(SD_GET_INSTANCE(hsd));
  state = DLYB_IsEnabled(instance);
  DLYB_Enable(instance);
  DLYB_GetConfig(instance, &unit, &sel);

  if (DLYB_ConfigureUnitDelay(instance) == DLYB_CORE_OK)
  {
    *p_max_clock_phase = DLYB_CalculateMaxOutputClockPhase(instance);
    status = HAL_OK;
  }

  DLYB_SetConfig(instance, unit, sel);
  if (state == DLYB_DISABLED)
  {
    DLYB_Disable(instance);
  }

  hsd->global_state = HAL_SD_STATE_IDLE;

  return status;
}

/**
  * @brief Enable the SD delay block.
  * @param hsd Pointer to a hal_mm_handle_t structure.
  * @retval HAL_OK The delay block is enabled.
  */
hal_status_t HAL_SD_EnableDlyb(hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, HAL_SD_STATE_IDLE);

  DLYB_Enable(SDMMC_GET_DLYB_INSTANCE(SD_GET_INSTANCE(hsd)));

  return HAL_OK;
}

/**
  * @brief Disable the SD delay block.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval HAL_OK The delay block is disabled.
  */
hal_status_t HAL_SD_DisableDlyb(hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, HAL_SD_STATE_IDLE);

  DLYB_Disable(SDMMC_GET_DLYB_INSTANCE(SD_GET_INSTANCE(hsd)));

  return HAL_OK;
}

/**
  * @brief Check if the delay block peripheral is enabled or not.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval HAL_SD_DLYB_DISABLED Delay block is disabled.
  * @retval HAL_SD_DLYB_ENABLED  Delay block is enabled.
  */
hal_sd_dlyb_state_t HAL_SD_IsEnabledDlyb(hal_sd_handle_t *hsd)
{
  ASSERT_DBG_PARAM(hsd != NULL);

  ASSERT_DBG_STATE(hsd->global_state, (uint32_t)HAL_SD_STATE_IDLE | (uint32_t)HAL_SD_STATE_ACTIVE \
                   | (uint32_t)HAL_SD_STATE_ABORT);

  return (hal_sd_dlyb_state_t)DLYB_IsEnabled(SDMMC_GET_DLYB_INSTANCE(SD_GET_INSTANCE(hsd)));
}
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup SD_Private_Functions
  * @{
  */
/**
  * @brief Configure the SD according to the default parameters.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  */
static void SD_SetDefaultConfig(hal_sd_handle_t *hsd)
{
  uint32_t sdmmc_clk;
  sdmmc_config_t cfg = {0U};

  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)hsd->instance));

  /* Set the default SDMMC peripheral configuration */
  cfg.clk.clock_edge        = (uint32_t)HAL_SD_CLOCK_EDGE_RISING;
  cfg.clk.clock_power_save  = (uint32_t)HAL_SD_CLOCK_POWER_SAVE_DISABLE;
  cfg.bus_wide              = (uint32_t)HAL_SD_BUS_WIDE_1BIT;
  cfg.hardware_flow_control = (uint32_t)HAL_SD_HARDWARE_FLOW_CONTROL_DISABLE;
  cfg.clk.clock_div         = (sdmmc_clk + (2U * SDMMC_SD_CARD_INIT_FREQ) - 1U) / (2U * SDMMC_SD_CARD_INIT_FREQ);

  SDMMC_SetConfig(SD_GET_INSTANCE(hsd), &cfg);
}

/**
  * @brief Configure the SD according to the user parameters.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param p_config Pointer to a hal_sd_config_t structure that contains the SD configuration.
  * @retval HAL_ERROR SD instance is already configured and cannot be modified.
  * @retval HAL_OK    SD instance has been correctly configured.
  */
static hal_status_t SD_SetConfig(hal_sd_handle_t *hsd, const hal_sd_config_t *p_config)
{
  sdmmc_config_t cfg = {0};
  uint32_t sdmmc_clk;

  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)hsd->instance));

  if (SD_SetWideBus(hsd, p_config->bus_wide) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Set user SDMMC peripheral configuration for SD card initialization */
  cfg.clk.clock_edge        = (uint32_t)p_config->clk_cfg.clk_edge;
  cfg.clk.clock_power_save  = (uint32_t)p_config->clk_cfg.clk_power_save;
  cfg.bus_wide              = (uint32_t)p_config->bus_wide;
  cfg.hardware_flow_control = (uint32_t)p_config->hw_flow_ctrl;
#if defined(USE_HAL_SD_AUTO_DETECTION_FREQUENCY) && (USE_HAL_SD_AUTO_DETECTION_FREQUENCY == 0)
  if (SD_Card_GetClockDiv(hsd, sdmmc_clk, p_config->clk_cfg.clk_hz, &cfg.clk.clock_div) != HAL_OK)
  {
    return HAL_ERROR;
  }
#else
  (void) SD_Card_GetClockDiv(hsd, sdmmc_clk, 0U, &cfg.clk.clock_div);
#endif /* USE_HAL_SD_AUTO_DETECTION_FREQUENCY */

  /* Set SD user configuration */
  SDMMC_SetConfig(SD_GET_INSTANCE(hsd), &cfg);

  return HAL_OK;
}

/**
  * @brief Notify SD card after insertion.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param p_config Pointer to a hal_sd_config_t structure that contains the SD configuration.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    SD instance has been correctly configured after detection.
  */
static hal_status_t SD_NotifyCardInsertion(hal_sd_handle_t *hsd, const hal_sd_config_t *p_config)
{
  hal_sd_card_status_t card_status = {0};

  /* SD card identification sequence */
  if (SD_Card_Identify(hsd) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* SD card transfer sequence */
  if (SD_Card_EnterDataTransferMode(hsd) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (SD_GetCardStatus(hsd, &card_status) != HAL_OK)
  {
    return HAL_ERROR;
  }

#if defined (USE_HAL_SD_GET_SPEC_VERSION) && (USE_HAL_SD_GET_SPEC_VERSION == 1)
  hsd->version = SD_Card_GetVersion(hsd);
#endif /* USE_HAL_SD_GET_SPEC_VERSION */

  if (SD_SetConfig(hsd, p_config) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (SD_Card_SetBlockSize(hsd, SDMMC_BLOCK_SIZE_BYTE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Enables the SDMMC wide bus mode.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param wide_bus Pointer to the hal_sd_bus_wide_t.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SD_SetWideBus(hal_sd_handle_t *hsd, hal_sd_bus_wide_t wide_bus)
{
  uint32_t scr[2U] = {0UL, 0UL};
  uint32_t wide = SDMMC_SINGLE_BUS_SUPPORT;

  if (wide_bus == HAL_SD_BUS_WIDE_4BIT)
  {
    wide = SDMMC_WIDE_BUS_SUPPORT;

    if (SD_Card_GetSCR(hsd, scr) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* If requested card supports wide bus operation */
    if ((scr[1U] & SDMMC_WIDE_BUS_SUPPORT) == 0U)
    {
      /* Error request not applicable */
      return HAL_ERROR;
    }
  }

  /* Send CMD55 application specific command  */
  if (SDMMC_SendAppCmd(SD_GET_INSTANCE(hsd), (uint32_t)(hsd->sd_card.relative_addr)) != HAL_SD_ERROR_NONE)
  {
    return HAL_ERROR;
  }

  /* Send ACMD6 to set the bus width */
  if (SDMMC_SendBusWidthCmd(SD_GET_INSTANCE(hsd), (wide >> 17U)) != HAL_SD_ERROR_NONE)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Start the identification mode.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SD_Card_Identify(hal_sd_handle_t *hsd)
{
  /* SD card power identification sequence */
  if (SD_Card_IdentifyVoltageRange(hsd) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* SD card unique card identification sequence */
  if (SD_Card_IdentifyCID(hsd) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* SD card relative address identification sequence */
  if (SD_Card_IdentifyRelativeAddress(hsd) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Validates the operation voltage range, identifies cards.
  * @param  hsd Pointer to a hal_sd_handle_t structure.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Operation completed with error.
  */
static hal_status_t SD_Card_IdentifyVoltageRange(hal_sd_handle_t *hsd)
{
  uint32_t sdmmc_clk;
  uint32_t init_clock_div;
  uint32_t init_clock_hz;
  __IO uint32_t count = 0U;
  uint32_t response;
  uint32_t error_code;

  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)hsd->instance));
  SDMMC_SET_PWR_STATE(SD_GET_INSTANCE(hsd), SDMMC_PWR_ON);

  if (sdmmc_clk == 0U)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= HAL_SD_ERROR_INVALID_PARAM;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /* Wait for 1ms + 74 more cycles: required power up waiting time before starting the SD initialization sequence */
  init_clock_div = STM32_READ_BIT(SD_GET_INSTANCE(hsd)->CLKCR, SDMMC_CLKCR_CLKDIV);
  init_clock_hz = sdmmc_clk;

  if (init_clock_div != 0U)
  {
    init_clock_hz /= (2U * init_clock_div);
  }

  if (init_clock_hz == 0U)
  {
    return HAL_ERROR;
  }

  SDMMC_DelayMs(SD_GET_INSTANCE(hsd), 1U + (((74U * 1000U) + init_clock_hz - 1U) / init_clock_hz));

  /*---------------------------------------------------------------------------------------------- CMD0 GO_IDLE_STATE */
  error_code = SDMMC_SendGoIdleStateCmd(SD_GET_INSTANCE(hsd));
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /*----------------------------------------------------------------------------------------------- CMD8 SEND_IF_COND */
  error_code = SDMMC_SendOperCondCmd(SD_GET_INSTANCE(hsd));
  if (error_code == HAL_SD_ERROR_CMD_RSP_TIMEOUT)
  {
    /* Return to idle state in case of SDMMC_CARD_V1_X */
    error_code = SDMMC_SendGoIdleStateCmd(SD_GET_INSTANCE(hsd));
    if (error_code != HAL_SD_ERROR_NONE)
    {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
      hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }
  }
  /*------------------------------------------------------------------------------------------- ACMD41 SD_APP_OP_COND */
  do
  {
    if (count >= SDMMC_MAX_TRIAL)
    {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
      hsd->last_error_codes |= HAL_SD_ERROR_INVALID_VOLTRANGE;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }

    /*------------------------------------------------------------------------------------------------- CMD55 APP_CMD */
    error_code = SDMMC_SendAppCmd(SD_GET_INSTANCE(hsd), 0U);
    if (error_code != HAL_SD_ERROR_NONE)
    {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
      hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }

    error_code = SDMMC_SendAppOperCmd(SD_GET_INSTANCE(hsd),
                                      (SDMMC_VOLTAGE_WINDOW_SD | SDMMC_HIGH_CAPACITY | SDMMC_SD_SWITCH_1_8V_CAPACITY));
    if (error_code != HAL_SD_ERROR_NONE)
    {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
      hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }

    response = SDMMC_GetResponse(SD_GET_INSTANCE(hsd), SDMMC_RESP1);

    count++;
  } while ((count < SDMMC_MAX_TRIAL) && (SD_GET_OPERATING_VOLTAGE_STATE(response) == 0U));

  /* Check SD card capacity */
  if ((response & SDMMC_HIGH_CAPACITY) == SDMMC_HIGH_CAPACITY)
  {
    /* Set SD high capacity type */
    hsd->type = SDMMC_SD_CARD_SDHC_SDXC;
    if (hsd->sd_transceiver == HAL_SD_TRANSCEIVER_PRESENT)
    {
      if ((response & SDMMC_SD_SWITCH_1_8V_CAPACITY) == SDMMC_SD_SWITCH_1_8V_CAPACITY)
      {
        /* Start switching procedue */
        SDMMC_ENABLE_VOLTAGE_SWITCH(SD_GET_INSTANCE(hsd));
        /* Start the voltage switch sequence to switch to 1.8V mode */
        if (SD_StartVoltageSwitchSequence(hsd) != HAL_OK)
        {
          return HAL_ERROR;
        }
        SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_CKSTOP);
        if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_BUSYD0) == 0U)
        {
          /* Error when activate Voltage Switch in SDMMC Peripheral */
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
          hsd->last_error_codes |= HAL_SD_ERROR_UNSUPPORTED_FEATURE;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
          return HAL_ERROR;
        }
        else
        {
          /* Enable Transceiver Switch PIN */
#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
          hsd->p_transceiver_1_8V_callback(hsd, HAL_SD_TRANSCEIVER_ENABLE);
#else
          HAL_SD_DriveTransceiver_1_8V_Callback(hsd, HAL_SD_TRANSCEIVER_ENABLE);
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */
          if (SD_CheckVoltageSwitch(hsd) != HAL_OK)
          {
            return HAL_ERROR;
          }
        }
      }
    }
  }
  else
  {
    /* Set SD standard capacity type */
    hsd->type = SDMMC_SD_CARD_SDSC;
  }

  return HAL_OK;
}

/**
  * @brief Get SD unique card identification (CID) number.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SD_Card_IdentifyCID(hal_sd_handle_t *hsd)
{
  uint32_t cid[4U];

  /*----------------------------------------------------------------------------------------------- CMD2 ALL_SEND_CID */
  if (SDMMC_SendCIDCmd(SD_GET_INSTANCE(hsd)) == HAL_SD_ERROR_NONE)
  {
    cid[0U] = SDMMC_GetResponse(SD_GET_INSTANCE(hsd), SDMMC_RESP1);
    cid[1U] = SDMMC_GetResponse(SD_GET_INSTANCE(hsd), SDMMC_RESP2);
    cid[2U] = SDMMC_GetResponse(SD_GET_INSTANCE(hsd), SDMMC_RESP3);
    cid[3U] = SDMMC_GetResponse(SD_GET_INSTANCE(hsd), SDMMC_RESP4);

#if defined (USE_HAL_SD_GET_CID) && (USE_HAL_SD_GET_CID == 1)
    /* Store all information of the card which are stored on the CID register */
    hsd->cid.manufacturer_id    = (uint8_t)SDMMC_READ_FIELD(cid[0], SDMMC_MANUFACTURE_ID_MSK, SDMMC_MANUFACTURE_ID_POS);
    hsd->cid.oem_app_id         = (uint16_t)SDMMC_READ_FIELD(cid[0], SDMMC_OEM_APP_ID_MSK, SDMMC_OEM_APP_ID_POS);
    hsd->cid.product_name_part1 = SDMMC_READ_FIELD(cid[0], SDMMC_PRODUCT_NAME_PART1_MSK, SDMMC_PRODUCT_NAME_PART1_POS);
    hsd->cid.product_name_part2 = (uint8_t)SDMMC_READ_FIELD(cid[1], SDMMC_PRODUCT_NAME_PART2_MSK,
                                                            SDMMC_PRODUCT_NAME_PART2_POS);
    hsd->cid.product_rev        = (uint8_t)SDMMC_READ_FIELD(cid[2], SDMMC_PRODUCT_REVISION_MSK,
                                                            SDMMC_PRODUCT_REVISION_POS);
    hsd->cid.product_serial_nbr = ((SDMMC_READ_FIELD(cid[2], SDMMC_PRODUCT_SERIAL_NBR2_MSK,
                                                     SDMMC_PRODUCT_SERIAL_NBR2_POS)) << 8U) | \
                                  (SDMMC_READ_FIELD(cid[3], SDMMC_PRODUCT_SERIAL_NBR1_MSK,
                                                    SDMMC_PRODUCT_SERIAL_NBR1_POS));
    hsd->cid.reserved1          = (uint8_t)SDMMC_READ_FIELD(cid[3], SDMMC_RESERVED_MSK, SDMMC_RESERVED_POS);
    hsd->cid.manufacturer_date  = (uint16_t)SDMMC_READ_FIELD(cid[3], SDMMC_MANUFACTURE_DATE_MSK,
                                                             SDMMC_MANUFACTURE_DATE_POS);
    hsd->cid.cid_crc            = (uint8_t)SDMMC_READ_FIELD(cid[3], SDMMC_CID_CRC_MSK, SDMMC_CID_CRC_POS);
    hsd->cid.reserved2          = (uint8_t)SDMMC_READ_FIELD(cid[3], SDMMC_NOT_USED_MSK, SDMMC_NOT_USED_POS);
#else
    STM32_UNUSED(cid[0U]);
#endif /* USE_HAL_SD_GET_CID */
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Ask SD card to publish a new relative address (RCA).
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SD_Card_IdentifyRelativeAddress(hal_sd_handle_t *hsd)
{
  uint16_t sd_rca = 0U;

  /*----------------------------------------------------------------------------------------------- CMD3 SET_REL_ADDR */
  if (SD_Card_GetRelativeAddr(hsd, &sd_rca) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Get the relative SD card address (RCA) */
  hsd->sd_card.relative_addr = (((uint32_t)sd_rca) << 16U);

  return HAL_OK;
}

/**
  * @brief Start the transfer mode for the SD card.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SD_Card_EnterDataTransferMode(hal_sd_handle_t *hsd)
{
  /* Get SD card specific data */
  if (SD_Card_GetCSD(hsd) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Select the Card */
  if (SDMMC_SendSelDeselCmd(SD_GET_INSTANCE(hsd), (uint32_t)hsd->sd_card.relative_addr) != HAL_SD_ERROR_NONE)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Get SD card specific data register (CSD).
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SD_Card_GetCSD(hal_sd_handle_t *hsd)
{
  uint32_t csd[4U];

  /* Send CMD9 SEND_CSD with argument as card's RCA */
  if (SDMMC_SendCSDCmd(SD_GET_INSTANCE(hsd), (uint32_t)(hsd->sd_card.relative_addr)) == HAL_SD_ERROR_NONE)
  {
    csd[0U] = SDMMC_GetResponse(SD_GET_INSTANCE(hsd), SDMMC_RESP1);
    csd[1U] = SDMMC_GetResponse(SD_GET_INSTANCE(hsd), SDMMC_RESP2);
    csd[2U] = SDMMC_GetResponse(SD_GET_INSTANCE(hsd), SDMMC_RESP3);
    csd[3U] = SDMMC_GetResponse(SD_GET_INSTANCE(hsd), SDMMC_RESP4);
  }
  else
  {
    return HAL_ERROR;
  }

  if (hsd->type == SDMMC_SD_CARD_SDSC)
  {
    /* Physical Layer Simplified Specification Version 6.00:
       blk_nbr = (device_size + 1) * multiple  which multiple = 2^(device_size_mulyiple + 2) */
    hsd->sd_card.blk_nbr  = (((SDMMC_READ_FIELD(csd[1], SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE2_MSK,
                                                SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE2_POS) << 2U) |
                              SDMMC_READ_FIELD(csd[2], SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE1_MSK,
                                               SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE1_POS)) + 1U) *
                            (1UL << (((SDMMC_READ_FIELD(csd[2], SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE_MULTIPLE_MSK,
                                                        SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE_MULTIPLE_POS)) & 0x07U)
                                     + 2U));

    /* blk_size_byte = 2^N : Which N is the read block len readen from CSD register */
    hsd->sd_card.blk_size_byte = (1UL << SDMMC_READ_FIELD(csd[1], SDMMC_SD_CARD_SDSC_CSD_READ_BL_LEN_MSK,
                                                          SDMMC_SD_CARD_SDSC_CSD_READ_BL_LEN_POS));
    hsd->sd_card.logical_blk_nbr = (hsd->sd_card.blk_nbr) * ((hsd->sd_card.blk_size_byte) / SDMMC_BLOCK_SIZE_BYTE);
    hsd->sd_card.logical_blk_size_byte = SDMMC_BLOCK_SIZE_BYTE;
  }
  else if (hsd->type == SDMMC_SD_CARD_SDHC_SDXC)
  {
    /** SDMMC_RESP1 : Bits 127 - 96 du CSD --> csd[0U]
      * SDMMC_RESP2 : Bits 95 - 64 du CSD  --> csd[1U]
      * SDMMC_RESP3 : Bits 63 - 32 du CSD  --> csd[2U]
      * SDMMC_RESP4 : Bits 31 - 0 du CSD   --> csd[3U]
      */
    hsd->sd_card.blk_nbr = (SDMMC_READ_FIELD(csd[1], SDMMC_SD_CARD_SDHC_SDXC_CSD_DEVICE_SIZE2_MSK,
                                             SDMMC_SD_CARD_SDHC_SDXC_CSD_DEVICE_SIZE2_POS)) << 26U;
    hsd->sd_card.blk_nbr |= (((SDMMC_READ_FIELD(csd[2], SDMMC_SD_CARD_SDHC_SDXC_CSD_DEVICE_SIZE1_MSK,
                                                SDMMC_SD_CARD_SDHC_SDXC_CSD_DEVICE_SIZE1_POS)) + 1U)) * 1024U;
    hsd->sd_card.logical_blk_nbr = hsd->sd_card.blk_nbr;
    hsd->sd_card.blk_size_byte = SDMMC_BLOCK_SIZE_BYTE;
    hsd->sd_card.logical_blk_size_byte = hsd->sd_card.blk_size_byte;
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Finds the SD card SCR register value.
  * @param hsd   Pointer to a hal_sd_handle_t structure.
  * @param p_scr Pointer to the buffer that must contain the SCR value.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SD_Card_GetSCR(hal_sd_handle_t *hsd, uint32_t *p_scr)
{
  uint32_t error_code;
  uint32_t temp_scr[2U] = {0UL, 0UL};
  uint32_t *scr = p_scr;

  /* Set block size to 8 bytes */
  if (SD_Card_SetBlockSize(hsd, SDMMC_SD_CARD_SCR_DATA_SIZE_BYTE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Send CMD55 APP_CMD with argument as card's RCA */
  error_code = SDMMC_SendAppCmd(SD_GET_INSTANCE(hsd), (uint32_t)(hsd->sd_card.relative_addr));
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  SD_SetSCRConfig(hsd);

  /* Send ACMD51 SD_APP_SEND_SCR with argument as 0 */
  error_code = SDMMC_SendSCRCmd(SD_GET_INSTANCE(hsd));
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /* Get SCD block response */
  if (SD_GetCardSCRData(hsd, temp_scr) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Check SDMMC error flags */
  if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_RXOVERR) != 0U)
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_DATA_FLAGS);

    return HAL_ERROR;
  }
  else
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_DATA_FLAGS);

    *scr = (((temp_scr[1] & SDMMC_0TO7BITS) << 24)  | ((temp_scr[1] & SDMMC_8TO15BITS) << 8) | \
            ((temp_scr[1] & SDMMC_16TO23BITS) >> 8) | ((temp_scr[1] & SDMMC_24TO31BITS) >> 24));
    scr++;
    *scr = (((temp_scr[0] & SDMMC_0TO7BITS) << 24)  | ((temp_scr[0] & SDMMC_8TO15BITS) << 8) | \
            ((temp_scr[0] & SDMMC_16TO23BITS) >> 8) | ((temp_scr[0] & SDMMC_24TO31BITS) >> 24));
  }

  return HAL_OK;
}

/**
  * @brief Configure the SCR SDMMC peripheral.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  */
static void SD_SetSCRConfig(hal_sd_handle_t *hsd)
{
  sdmmc_data_ctrl_t data = {0U};

  /* Set SCR SDMMC peripheral configuration */
  data.data_timeout    = hsd->data_timeout_cycle;
  data.data_length     = SDMMC_SD_CARD_SCR_DATA_SIZE_BYTE;
  data.data_block_size = SDMMC_DATABLOCK_SIZE_8B;
  data.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data.dpsm            = SDMMC_DPSM_ENABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &data);
}

/**
  * @brief Switches the SD card to the Speed mode.
  * @param hsd           Pointer to a hal_sd_handle_t structure.
  * @param speed_pattern Speed mode to set.
  *        This parameter can be one of the following values:
  *          @arg SDMMC_DDR50_SWITCH_PATTERN  : High speed DDR50.
  *          @arg SDMMC_SDR104_SWITCH_PATTERN : High Speed SDR104.
  *          @arg SDMMC_SDR50_SWITCH_PATTERN  : High Speed SDR50.
  *          @arg SDMMC_SDR25_SWITCH_PATTERN  : high speed SDR25.
  *          @arg SDMMC_SDR12_SWITCH_PATTERN  : high speed SDR12.
  * @warning This operation must be followed by the configuration of PLL to have SDMMCCK clock between 50 and 120 MHz.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SD_SetSpeedMode(hal_sd_handle_t *hsd, uint32_t speed_pattern)
{
  sdmmc_data_ctrl_t sdmmc_datactrl;
  uint32_t sd_hs[16] = {0};
  uint32_t loop = 0 ;
  uint32_t timeout = HAL_GetTick();

  /* Initialize the Data control register */
  SDMMC_CLEAR_DCTRL(SD_GET_INSTANCE(hsd));
  if (SD_Card_SetBlockSize(hsd, 64U) != HAL_OK)
  {
    return HAL_ERROR;
  }
  /* Configure the SD DPSM (Data Path State Machine) */
  sdmmc_datactrl.data_timeout    = hsd->data_timeout_cycle;
  sdmmc_datactrl.data_length     = 64U;
  sdmmc_datactrl.data_block_size = SDMMC_DATABLOCK_SIZE_64B ;
  sdmmc_datactrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  sdmmc_datactrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  sdmmc_datactrl.dpsm            = SDMMC_DPSM_ENABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &sdmmc_datactrl);

  /* Send CMD6 to switch to the speed pattern */
  if (SDMMC_SendSwitchCmd(SD_GET_INSTANCE(hsd), speed_pattern) != HAL_SD_ERROR_NONE)
  {
    return HAL_ERROR;
  }
  while (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DBCKEND | SDMMC_FLAG_DATAEND) == 0UL)
  {
    if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_RXFIFOHF) == 1UL)
    {
      for (uint32_t count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
      {
        sd_hs[(8U * loop) + count]  = SDMMC_ReadFIFO(SD_GET_INSTANCE(hsd));
      }
      loop ++;
    }

    if ((HAL_GetTick() - timeout) >=  SDMMC_CMD_TIMEOUT)
    {
      return HAL_ERROR;
    }
  }

  if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DTIMEOUT) == 1UL)
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DTIMEOUT);
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DCRCFAIL) == 1UL)
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DCRCFAIL);
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_RXOVERR) == 1UL)
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_RXOVERR);
    return HAL_ERROR;
  }
  else
  {
    /* No error flag set */
  }
  /* Check if the switch mode HS is ok */
  if ((((uint8_t *)sd_hs)[13] & 2U) != 2U)
  {
    /* Unsupported feature */
    return HAL_ERROR;
  }
  else
  {
    if (hsd->sd_transceiver == HAL_SD_TRANSCEIVER_PRESENT)
    {
      if (hsd->speed == SDMMC_SD_CARD_ULTRA_HIGH_SPEED)
      {
#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
        hsd->p_transceiver_1_8V_callback(hsd, HAL_SD_TRANSCEIVER_ENABLE);
#else
        HAL_SD_DriveTransceiver_1_8V_Callback(hsd, HAL_SD_TRANSCEIVER_ENABLE);
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */
#if defined (DLYB_SDMMC1) || defined (DLYB_SDMMC2)
        /* SDMMC_FB_CLK tuned feedback clock selected as receive clock, for SDR104 */
        if ((speed_pattern == SDMMC_SDR104_SWITCH_PATTERN) || (speed_pattern == SDMMC_SDR50_SWITCH_PATTERN))
        {
          STM32_MODIFY_REG(SD_GET_INSTANCE(hsd)->CLKCR, SDMMC_CLKCR_SELCLKRX, SDMMC_CLKCR_SELCLKRX_1);
        }
        /* SDMMC_CKin feedback clock selected as receive clock, for DDR50 */
        else if (speed_pattern == SDMMC_DDR50_SWITCH_PATTERN)
        {
          STM32_MODIFY_REG(SD_GET_INSTANCE(hsd)->CLKCR, SDMMC_CLKCR_SELCLKRX, SDMMC_CLKCR_SELCLKRX_0);
        }
        else
        {
          /* Nothing to do */
        }
        /* Enable DelayBlock Peripheral */
        DLYB_Enable(SDMMC_GET_DLYB_INSTANCE(SD_GET_INSTANCE(hsd)));
#endif /* (DLYB_SDMMC1) || (DLYB_SDMMC2) */
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Get the switch speed mode argument.
  * @param hsd            Pointer to a hal_sd_handle_t structure.
  * @param speed_mode     Specifies the SD card speed bus mode.
  * @param p_switch_speed Pointer to the switch speed.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SD_GetSpeedMode(hal_sd_handle_t *hsd, hal_sd_speed_mode_t speed_mode, uint32_t *p_switch_speed)
{
  if (((hsd->speed == SDMMC_SD_CARD_ULTRA_HIGH_SPEED) || (hsd->type == SDMMC_SD_CARD_SDHC_SDXC))
      && (hsd->sd_transceiver == HAL_SD_TRANSCEIVER_PRESENT) && (speed_mode == HAL_SD_SPEED_MODE_DDR50))
  {
    /* Switch to DDR50 mode up to 50MHz 1.8V signaling */
    *p_switch_speed = SDMMC_DDR50_SWITCH_PATTERN;
    SDMMC_SET_CLKCR(SD_GET_INSTANCE(hsd), SDMMC_CLKCR_BUSSPEED | SDMMC_CLKCR_DDR);
  }

  else if (((hsd->speed == SDMMC_SD_CARD_ULTRA_HIGH_SPEED) || (hsd->type == SDMMC_SD_CARD_SDHC_SDXC))
           && (hsd->sd_transceiver == HAL_SD_TRANSCEIVER_PRESENT) && (speed_mode == HAL_SD_SPEED_MODE_SDR104))
  {
    /* Switch to SDR104 mode up to 208MHz 1.8V signaling */
    *p_switch_speed = SDMMC_SDR104_SWITCH_PATTERN;
    SDMMC_SET_CLKCR(SD_GET_INSTANCE(hsd), SDMMC_CLKCR_BUSSPEED);
  }

  else if (((hsd->speed == SDMMC_SD_CARD_ULTRA_HIGH_SPEED) || (hsd->type == SDMMC_SD_CARD_SDHC_SDXC))
           && (hsd->sd_transceiver == HAL_SD_TRANSCEIVER_PRESENT) && (speed_mode == HAL_SD_SPEED_MODE_SDR50))
  {
    /* Switch to SDR50 mode up to 100MHz 1.8V signaling */
    *p_switch_speed = SDMMC_SDR50_SWITCH_PATTERN;
    SDMMC_SET_CLKCR(SD_GET_INSTANCE(hsd), SDMMC_CLKCR_BUSSPEED);
  }

  else if (((hsd->speed == SDMMC_SD_CARD_NORMAL_SPEED) || (hsd->speed == SDMMC_SD_CARD_HIGH_SPEED)
            || (hsd->speed == SDMMC_SD_CARD_ULTRA_HIGH_SPEED))
           && ((hsd->type == SDMMC_SD_CARD_SDSC) || (hsd->type == SDMMC_SD_CARD_SDHC_SDXC))
           && (speed_mode == HAL_SD_SPEED_MODE_HIGH))
  {
    /* Switch to HS mode up to 50MHz in 3.3V signaling */
    *p_switch_speed = SDMMC_SDR25_SWITCH_PATTERN;
  }

  else if (((hsd->speed == SDMMC_SD_CARD_NORMAL_SPEED) || (hsd->speed == SDMMC_SD_CARD_HIGH_SPEED)
            || (hsd->speed == SDMMC_SD_CARD_ULTRA_HIGH_SPEED))
           && ((hsd->type == SDMMC_SD_CARD_SDSC) || (hsd->type == SDMMC_SD_CARD_SDHC_SDXC))
           && (speed_mode == HAL_SD_SPEED_MODE_DEFAULT))
  {
    /* Switch to DS mode up to 25MHz in 3.3V signaling */
    *p_switch_speed = SDMMC_SDR12_SWITCH_PATTERN;
  }

  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

#if defined (USE_HAL_SD_GET_SPEC_VERSION) && (USE_HAL_SD_GET_SPEC_VERSION == 1)
/**
  * @brief Get the SD specification version.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval SD spec version refer to hal_sd_specification_version_t.
  */
static hal_sd_specification_version_t SD_Card_GetVersion(hal_sd_handle_t *hsd)
{
  uint32_t scr[2U] = {0UL, 0UL};
  sd_spec_values_t spec, spec_info;
  static const sd_spec_info_t sd_spec_info[9] =
  {
    {{0, 0, 0, 0}, HAL_SD_SPECIFICATION_VERSION_1_00_OR_1_01},
    {{1, 0, 0, 0}, HAL_SD_SPECIFICATION_VERSION_1_10},
    {{2, 0, 0, 0}, HAL_SD_SPECIFICATION_VERSION_2_00},
    {{2, 1, 0, 0}, HAL_SD_SPECIFICATION_VERSION_3_0X},
    {{2, 1, 1, 0}, HAL_SD_SPECIFICATION_VERSION_4_XX},
    {{2, 1, 1, 1}, HAL_SD_SPECIFICATION_VERSION_5_XX},
    {{2, 1, 0, 1}, HAL_SD_SPECIFICATION_VERSION_5_XX},
    {{2, 1, 1, 2}, HAL_SD_SPECIFICATION_VERSION_6_XX},
    {{2, 1, 0, 2}, HAL_SD_SPECIFICATION_VERSION_6_XX},
  };

  if (SD_Card_GetSCR(hsd, scr) == HAL_OK)
  {
    spec.sd_spec   = (uint8_t)SDMMC_READ_FIELD(scr[1], SDMMC_SD_CARD_SPEC_MSK, SDMMC_SD_CARD_SPEC_POS);
    spec.sd_spec_3 = (uint8_t)SDMMC_READ_FIELD(scr[1], SDMMC_SD_CARD_SPEC_3_MSK, SDMMC_SD_CARD_SPEC_3_POS);
    spec.sd_spec_4 = (uint8_t)SDMMC_READ_FIELD(scr[1], SDMMC_SD_CARD_SPEC_4_MSK, SDMMC_SD_CARD_SPEC_4_POS);
    spec.sd_spec_x = (uint8_t)SDMMC_READ_FIELD(scr[1], SDMMC_SD_CARD_SPEC_5_MSK, SDMMC_SD_CARD_SPEC_5_POS);

    for (size_t i = 0; i < (sizeof(sd_spec_info) / sizeof(sd_spec_info[0])); i++)
    {
      spec_info = sd_spec_info[i].field_value;
      if ((spec_info.sd_spec      == spec.sd_spec)   \
          && (spec_info.sd_spec_3 == spec.sd_spec_3) \
          && (spec_info.sd_spec_4 == spec.sd_spec_4) \
          && (spec_info.sd_spec_x == spec.sd_spec_x))
      {
        return sd_spec_info[i].version;
      }
    }
  }

  return HAL_SD_SPECIFICATION_VESION_UNSUPPORTED;
}
#endif /* USE_HAL_SD_GET_SPEC_VERSION */

/**
  * @brief Set the Block size of the SD card.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param blk_size The block size to be set.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    SD card has correctly set the block size.
  */
static hal_status_t SD_Card_SetBlockSize(hal_sd_handle_t *hsd, uint32_t blk_size)
{
  /* Set Block Size for SD Card */
  if (SDMMC_SendBlockLengthCmd(SD_GET_INSTANCE(hsd), blk_size) != HAL_SD_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Send Status info command.
  * @param hsd         Pointer to a hal_sd_handle_t structure.
  * @param p_sd_status Pointer to the buffer that must contain the SD card status.
  * @retval HAL_OK     SD card state returned successfully.
  * @retval HAL_ERROR  SD card state returned with error.
  */
static hal_status_t SD_Card_SendStatus(hal_sd_handle_t *hsd, uint32_t *p_sd_status)
{
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t error_code;
  uint32_t *p_data = p_sd_status;

  error_code = SDMMC_SendBlockLengthCmd(SD_GET_INSTANCE(hsd), 64U);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes = error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  error_code = SDMMC_SendAppCmd(SD_GET_INSTANCE(hsd), hsd->sd_card.relative_addr);
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes = error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /* Configure the SD DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hsd->data_timeout_cycle;
  data_ctrl.data_length     = 64U;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_64B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_ENABLE;
  SDMMC_ConfigData(SD_GET_INSTANCE(hsd), &data_ctrl);

  error_code = SDMMC_SendStatusRegisterCmd(SD_GET_INSTANCE(hsd));
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    hsd->last_error_codes = error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  if (SD_GetCardStatusData(hsd, p_data) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_RXOVERR) != 0U)
  {
    error_code = SDMMC_READ_REG(SD_GET_INSTANCE(hsd), STAR);
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_DATA_FLAGS);
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
    if ((error_code & SDMMC_FLAG_DTIMEOUT) != 0UL)
    {
      hsd->last_error_codes = HAL_SD_ERROR_DATA_TIMEOUT;
    }

    if ((error_code & SDMMC_FLAG_DCRCFAIL) != 0UL)
    {
      hsd->last_error_codes = HAL_SD_ERROR_DATA_CRC_FAIL;
    }

    if ((error_code & SDMMC_FLAG_RXOVERR) != 0UL)
    {
      hsd->last_error_codes = HAL_SD_ERROR_RX_OVERRUN;
    }
#endif /* USE_HAL_SD_GET_LAST_ERRORS */

    return HAL_ERROR;
  }

  SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_DATA_FLAGS);

  return HAL_OK;
}

/**
  * @brief Wrap up reading in non-blocking mode.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  */
static void SD_Read_IT(hal_sd_handle_t *hsd)
{
  uint32_t *p_tmp;

  p_tmp = hsd->p_xfer_buff;
  if (hsd->xfer_size_byte >= SDMMC_FIFO_SIZE)
  {
    /* Read data from SDMMC Rx FIFO */
    for (uint32_t count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
    {
      *p_tmp = SDMMC_ReadFIFO(SD_GET_INSTANCE(hsd));
      p_tmp++;
    }
    hsd->p_xfer_buff = p_tmp;
    hsd->xfer_size_byte -= SDMMC_FIFO_SIZE;
  }
}

/**
  * @brief Wrap up writing in non-blocking mode.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  */
static void SD_Write_IT(hal_sd_handle_t *hsd)
{
  uint32_t *p_tmp;

  p_tmp = hsd->p_xfer_buff;

  if (hsd->xfer_size_byte >= SDMMC_FIFO_SIZE)
  {
    /* Write data to SDMMC Tx FIFO */
    for (uint32_t count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
    {
      SDMMC_WriteFIFO(SD_GET_INSTANCE(hsd), *p_tmp);
      p_tmp++;
    }
    hsd->p_xfer_buff = p_tmp;
    hsd->xfer_size_byte -= SDMMC_FIFO_SIZE;
  }
}

/**
  * @brief Wait for a SD status data to be ready.
  * @param hsd       Pointer to a hal_sd_handle_t structure.
  * @param p_sd_data Pointer to SD status data.
  * @retval HAL_ERROR in case of timeout has occurred.
  * @retval HAL_OK    in case of no error has occurred.
  */
static hal_status_t SD_GetCardStatusData(hal_sd_handle_t *hsd, uint32_t *p_sd_data)
{
  __IO uint32_t timeout_ms;
  uint32_t *p_sd_status_data = p_sd_data;

  timeout_ms =
    SDMMC_CMD_TIMEOUT * (HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)hsd->instance)) / 22U / 1000U);

  /* Repeat while timeout != 0U */
  do
  {
    if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_RXFIFOHF) == 1UL)
    {
      for (uint32_t idx = 0U; idx < (SDMMC_FIFO_SIZE / 4U); idx++)
      {
        *p_sd_status_data = SDMMC_ReadFIFO(SD_GET_INSTANCE(hsd));
        p_sd_status_data++;
      }
    }

    if (timeout_ms == 0U)
    {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1U)
      hsd->last_error_codes |= HAL_SD_ERROR_TIMEOUT;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }
    timeout_ms--;

  } while (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                                | SDMMC_FLAG_DATAEND) == 0UL);

  return HAL_OK;
}

/**
  * @brief Wait for a SD scr data to be ready.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @param p_sd_scr Pointer to SD scr data.
  * @retval HAL_ERROR in case of timeout has occurred.
  * @retval HAL_OK    in case of no error has occurred.
  */
static hal_status_t SD_GetCardSCRData(hal_sd_handle_t *hsd, uint32_t *p_sd_scr)
{
  __IO uint32_t timeout_ms;
  uint32_t idx;

  timeout_ms = SDMMC_CMD_TIMEOUT *
               (HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)hsd->instance)) / 22U / 1000U);
  /* Repeat while timeout != 0U */
  do
  {
    idx = SDMMC_GetDataCounter(SD_GET_INSTANCE(hsd));

    if ((SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_RXFIFOE) == 0UL) && (idx != 0U))
    {
      p_sd_scr[0] = SDMMC_ReadFIFO(SD_GET_INSTANCE(hsd));
      p_sd_scr[1] = SDMMC_ReadFIFO(SD_GET_INSTANCE(hsd));
    }

    if (timeout_ms == 0U)
    {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1U)
      hsd->last_error_codes |= HAL_SD_ERROR_TIMEOUT;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }
    timeout_ms--;

  } while (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                                | SDMMC_FLAG_DATAEND) == 0UL);

  return HAL_OK;
}

/**
  * @brief Wait for a SD relative card address to be ready.
  * @param hsd       Pointer to a hal_sd_handle_t structure.
  * @param p_sd_rca  pointer to SD relative card address.
  * @retval HAL_ERROR in case of an error has occurred.
  * @retval HAL_OK    in case of no error has occurred.
  */
static hal_status_t SD_Card_GetRelativeAddr(hal_sd_handle_t *hsd, uint16_t *p_sd_rca)
{
  __IO uint32_t timeout_ms ;
  uint32_t error_code;

  timeout_ms = SDMMC_CMD_TIMEOUT *
               (HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)hsd->instance)) / 22U / 1000U);

  /* Repeat while timeout != 0U */
  do
  {
    error_code = SDMMC_SD_SendRelativeAddrCmd(SD_GET_INSTANCE(hsd), p_sd_rca);
    if (error_code != HAL_SD_ERROR_NONE)
    {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1U)
      hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }

    if (timeout_ms == 0U)
    {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1U)
      hsd->last_error_codes |= HAL_SD_ERROR_TIMEOUT;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }
    timeout_ms--;

  } while (*p_sd_rca == 0U);

  return HAL_OK;
}

/**
  * @brief Start the Switch voltage sequence to 1.8V.
  * @param hsd      Pointer to a hal_sd_handle_t structure.
  * @retval HAL_ERROR   in case of other error has occurred.
  * @retval HAL_OK      in case of no error has occurred.
  */
static hal_status_t SD_StartVoltageSwitchSequence(hal_sd_handle_t *hsd)
{
  __IO uint32_t timeout_ms;
  uint32_t error_code;

  timeout_ms = SDMMC_CMD_TIMEOUT *
               (HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)hsd->instance)) / 22U / 1000U);

  /* Send CMD11 to switch 1.8V mode */
  error_code = SDMMC_SendVoltageSwitchCmd(SD_GET_INSTANCE(hsd));
  if (error_code != HAL_SD_ERROR_NONE)
  {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1U)
    hsd->last_error_codes |= error_code;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /* Repeat while timeout != 0U */
  do
  {
    if (timeout_ms == 0U)
    {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1U)
      hsd->last_error_codes |= HAL_SD_ERROR_TIMEOUT;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }
    timeout_ms--;

  } while (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_CKSTOP) == 0U);

  return HAL_OK;
}

/**
  * @brief Check for SD Switch voltage is Done.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval HAL_ERROR   in case of an error has occurred when enabling 1.8V mode.
  * @retval HAL_OK      in case of no error has occurred.
  */
static hal_status_t SD_CheckVoltageSwitch(hal_sd_handle_t *hsd)
{
  __IO uint32_t timeout_ms;

  SDMMC_START_VOLTAGE_SWITCH(SD_GET_INSTANCE(hsd));

  timeout_ms = SDMMC_CMD_TIMEOUT *
               (HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)hsd->instance)) / 22U / 1000U);

  /* Repeat while timeout != 0U */
  do
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_VSWEND);
    if (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_BUSYD0) != 0U)
    {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1U)
      /* Error when enabling 1.8V mode */
      hsd->last_error_codes |= HAL_SD_ERROR_INVALID_VOLTRANGE;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;

    }
    /* Switch to 1.8V OK */

    /* Disable VSWITCH FLAG from SDMMC Peripheral */
    SDMMC_DISABLE_VOLTAGE_SWITCH(SD_GET_INSTANCE(hsd));

    /* Clean Status flags */
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);

    if (timeout_ms == 0U)
    {
#if defined (USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1U)
      /* Error when enabling 1.8V mode */
      hsd->last_error_codes |= HAL_SD_ERROR_TIMEOUT;
#endif /* USE_HAL_SD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }
    timeout_ms--;

  } while (SDMMC_IS_ACTIVE_FLAG(SD_GET_INSTANCE(hsd), SDMMC_FLAG_VSWEND) != 0U);

  return HAL_OK;
}

/**
  * @brief Calculate the clock divide factor regarding the kernel clock and the user clock.
  * @param sdmmc_clk kernel clock Frequency in Hz
  * @param user_freq user frequency in Hz
  * @retval uint32_t clock factor divide.
  */
static uint32_t SD_Card_CalculateClockDiv(uint32_t sdmmc_clk, uint32_t user_freq)
{
  return ((sdmmc_clk + (2U * user_freq)  - 1U) / (2U * user_freq));
}

/**
  * @brief Get the SD clock divide factor.
  * @param hsd         Pointer to a hal_sd_handle_t structure.
  * @param sdmmc_clk   kernel clock Frequency in Hz
  * @param user_freq   user frequency in Hz
  * @param p_clk_div   Pointer to clock divide factor
  * @retval HAL_ERROR  in case of an error has occurred
  * @retval HAL_OK     in case of no error has occurred.
  */
static hal_status_t SD_Card_GetClockDiv(const hal_sd_handle_t *hsd, uint32_t sdmmc_clk, uint32_t user_freq,
                                        uint32_t *p_clk_div)
{
  uint32_t target_freq = 0U;

  switch (hsd->speed)
  {
    case SDMMC_SD_CARD_ULTRA_HIGH_SPEED:
      target_freq = SDMMC_SD_CARD_UHS_SPEED_FREQ;
      break;
    case SDMMC_SD_CARD_HIGH_SPEED:
      target_freq = SDMMC_SD_CARD_HS_SPEED_FREQ;
      break;
    default:
      target_freq = SDMMC_SD_CARD_NS_SPEED_FREQ;
      break;
  }

#if defined(USE_HAL_SD_AUTO_DETECTION_FREQUENCY) && (USE_HAL_SD_AUTO_DETECTION_FREQUENCY == 1)
  STM32_UNUSED(user_freq);
  if ((2U * target_freq) <= sdmmc_clk)
  {
    *p_clk_div = SD_Card_CalculateClockDiv(sdmmc_clk, target_freq);
  }
  else
  {
    *p_clk_div = 0U;
  }
#else
  if ((user_freq > 0) && (user_freq <= target_freq))
  {
    if ((2U * user_freq) <= sdmmc_clk)
    {
      *p_clk_div = SD_Card_CalculateClockDiv(sdmmc_clk, user_freq);
    }
    else
    {
      *p_clk_div = 0U;
    }
  }
  else
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_SD_AUTO_DETECTION_FREQUENCY */

  return HAL_OK;
}

/**
  * @brief Get the SD status information.
  * @param hsd        Pointer to a hal_sd_handle_t structure.
  * @param p_status   Pointer to the hal_sd_card_status_t structure that must contain the SD card status information.
  * @note this must be called if there is no SD transaction ongoing.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Completed successfully.
  */
static hal_status_t SD_GetCardStatus(hal_sd_handle_t *hsd, hal_sd_card_status_t *p_status)
{
  uint32_t sd_status[16];
  uint8_t speed_grade;
  uint8_t unit_size;

  if (SD_Card_SendStatus(hsd, sd_status) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(SD_GET_INSTANCE(hsd), SDMMC_STATIC_FLAGS);
    hsd->global_state = HAL_SD_STATE_INIT;
    return HAL_ERROR;
  }
  else
  {
    p_status->uhs_allocation_unit_size = (uint8_t)SDMMC_READ_FIELD(sd_status[3], SDMMC_SD_CARD_UHS_AU_SIZE_MSK,
                                                                   SDMMC_SD_CARD_UHS_AU_SIZE_POS);
    p_status->video_speed_class        = (uint8_t)SDMMC_READ_FIELD(sd_status[4], SDMMC_SD_CARD_VIDEO_SPEED_CLASS_MSK,
                                                                   SDMMC_SD_CARD_VIDEO_SPEED_CLASS_POS);
  }

  if (SD_Card_SetBlockSize(hsd, SDMMC_BLOCK_SIZE_BYTE) != HAL_OK)
  {
    hsd->global_state = HAL_SD_STATE_INIT;
    return HAL_ERROR;
  }

  speed_grade = p_status->uhs_speed_grade;
  unit_size = p_status->uhs_allocation_unit_size;
  /* Set SD card speed */
  if ((hsd->type == SDMMC_SD_CARD_SDHC_SDXC) && ((speed_grade != 0U) || (unit_size != 0U)))
  {
    hsd->speed = SDMMC_SD_CARD_ULTRA_HIGH_SPEED;
  }
  else if (hsd->type == SDMMC_SD_CARD_SDHC_SDXC)
  {
    hsd->speed = SDMMC_SD_CARD_HIGH_SPEED;
  }
  else
  {
    hsd->speed = SDMMC_SD_CARD_NORMAL_SPEED;
  }

  return HAL_OK;
}

/**
  * @brief Get the SD state information.
  * @param hsd Pointer to a hal_sd_handle_t structure.
  * @retval uint32_t SD card state value.
  */
static uint32_t SD_GetCardState(const hal_sd_handle_t *hsd)
{
  uint32_t card_state;

  card_state = SDMMC_SendStatusCmd(SD_GET_INSTANCE(hsd), hsd->sd_card.relative_addr);

  if (card_state != 0U)
  {
    return card_state;
  }

  card_state = SDMMC_GetResponse(SD_GET_INSTANCE(hsd), SDMMC_RESP1);

  card_state = (card_state >> 9U) & 0x0FU;

  return card_state;
}
/**
  * @}
  */
#endif /* USE_HAL_SD_MODULE */
#endif /* SDMMC1 */

/**
  * @}
  */

/**
  * @}
  */
