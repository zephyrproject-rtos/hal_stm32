/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_sdio.c
  * @brief   SDIO HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Secure Digital Input Output (SDIO) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
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

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @addtogroup SDIO
  * @{
  */
/** @defgroup SDIO_Introduction SDIO Introduction
  * @{

  - The SDIO Hardware Abstraction Layer provides a high-level interface to the STM32 SDMMC peripheral for
    communicating with Secure Digital Input Output (SDIO) cards.

  - This HAL driver is built on top of the SDMMC core layer and simplifies peripheral initialization, device
    identification, configuration, and transition to the transfer state.

  - It supports the main data operations required by I/O applications, including direct and extended
    read/write transfers, function control, I/O interrupt management, and access to device status,
    configuration, and common or function-specific register information.

  - The driver supports polling and DMA transfer modes for data exchanges, allowing the application to balance
    CPU load, throughput, and responsiveness.

  - It also provides services to manage device insertion and removal events, configure transfer timing and,
    when available, FIFO threshold parameters.

  - This abstraction layer improves portability across STM32 devices embedding the SDMMC peripheral and eases
    the integration of SDIO-based peripherals into embedded applications.

  */
/**
  * @}
  */

/** @defgroup SDIO_How_To_Use SDIO How To Use
  * @{
# How to use this driver

## The HAL SDIO driver can be used as follows:

SDIO card system specifications are available through the SD card association website at www.sdcard.org
This driver is compliant with SDIO card specification version 4.0 and fully compliant with previous version.

This HAL SDIO driver is a layered driver on top of the SDMMC core driver (allowing to handle SD,MMC memories and SDIO
cards).
The HAL SDIO driver allows to interface with SDIO cards.

This driver implements a high level communication layer for read and write from/to this SDIO card.

This driver provides 8 different sets of APIs that allows to:

1. Initialize and de-initialize the logical SDIO object :
   - To initialize the SDIO Card, use the HAL_SDIO_Init() function
     - to associate physical instance to logical object.
     - Enable the SDMMC peripheral clock either by :
       - Calling the appropriate HAL RCC function  HAL_RCC_SDMMCx_EnableClock
       - Setting the USE_HAL_SDIO_CLK_ENABLE_MODEL to HAL_CLK_ENABLE_PERIPH_ONLY through stm32tnxx_hal_conf.h
         module, in this case the SDMMC peripheral clock must be automatically enabled by the HAL_SDIO_Init().
   - To de-initialize the SDIO card, use the HAL_SDIO_DeInit() function that must turn off the SDIO Card and set
     the HAL SDIO handle state to RESET.

2. Set and Get SDIO configuration:
   - Configures the SDIO card. The clock frequency must be less than 400 kHz. This phase allows the card identification
     to ensure that the card has been correctly identified. After identification, apply the user parameters.
     During this stage, the SDIO card moves from the IDENTIFICATION STATE to the TRANSFER STATE and sets the global
     state to the IDLE state.
   - To retrieve the current SDIO card configuration, use the HAL_SDIO_GetConfig().
   - When the GPIO Pin detects a removal of the SDIO card from the bus, use the HAL_SDIO_NotifyCardRemoval() to apply
     the SDMMC default configuration and wait for an insertion of the SDIO card.
   - When the GPIO Pin detects an insertion of the SDIO card, use the HAL_SDIO_NotifyCardInsertion() to
     re-apply the user configuration.
   - To change the SDIO data bus width, use the HAL_SDIO_SetDataBusWidth().
   - To get the SDIO data bus width, use the HAL_SDIO_GetDataBusWidth().
   - To set a new transfer clock frequency, use the HAL_SDIO_SetTransferClockFreq().
   - To get the current transfer clock frequency, use the  HAL_SDIO_GetTransferClockFreq().
   - To update the SDIO block size, use the HAL_SDIO_SetBlockSize().
   - To configure the speed mode on the SDIO card, use HAL_SDIO_SetSpeedMode().
   - To reset the SDIO card, use the HAL_SDIO_ResetCard().
   - To retrieve the peripheral clock frequency for SDIO card, use the HAL_SDIO_GetClockFreq().
   - According to the SDIO card specification, the timeout values available through define can be used also
     by user to fill the configuration structure at the SetConfig call:
     - HAL_SDIO_DATA_MAX_TIMEOUT (0xFFFFFFFFU) : Max data timeout
     - For the data_timeout_cycle : Use HAL_SDIO_SetDataTimeout() to update it with the user definition

3. Input and Output operations:
  - Direct Read/Write Operations:
    - To read data directly from an SDIO card, use the HAL_SDIO_ReadDirect() function.
    - To write data directly to an SDIO card, use the HAL_SDIO_WriteDirect() function.
  - Extended Read/Write Operations:
    - Blocking mode: Polling
      - To read data in an extended manner from an SDIO card, use the HAL_SDIO_ReadExtended() function.
      - To write data in an extended manner to an SDIO card, use the HAL_SDIO_WriteExtended() function.
    - Non-Blocking mode: DMA in normal mode
      - To read data in an extended manner with DMA, use the HAL_SDIO_ReadExtended_DMA() function.
      - To write data in an extended manner with DMA, use the HAL_SDIO_WriteExtended_DMA() function.

4. IRQHandler and Callbacks Functions:
   - All SDIO card interrupt requests are handled by the HAL_SDIO_IRQHandler function.
   - By default, after the HAL_SDIO_Init, all callbacks are reset to the corresponding legacy weak (overridden)
     functions:
      - HAL_SDIO_XferCpltCallback()               : A Callback when an Xfer transfer is completed.
      - HAL_SDIO_ErrorCallback()                  : A Callback when an error has occurred.
      - HAL_SDIO_IOFunctionCallback()             : A Callback when an IO function is completed.
      - HAL_SDIO_DriveTransceiver_1_8V_Callback() : A Callback when the switch to 1.8 v is completed.

   - To use the callback registration feature, Set the USE_HAL_SDIO_REGISTER_CALLBACKS to 1U the compilation flag
     through stm32tnxx_hal_conf.h module to allow the user to configure dynamically the driver register callbacks.

   - Use Functions to register a user callback, it allows to register following callbacks:
     - HAL_SDIO_RegisterXferCpltCallback()    : To register an xfer callback function.
     - HAL_SDIO_RegisterErrorCallback()   : To register an error callback function.
     - HAL_SDIO_RegisterIOFunctionCallback()  : To register an IO function callback function.
     - HAL_SDIO_RegisterTransceiverCallback() : To register a transceiver callback function.
       When The compilation define USE_HAL_SDIO_REGISTER_CALLBACKS is set to 0 or not defined, the callback registering
       feature is not available and weak (overridden) callbacks are used.

5. SDIO Card related information functions:
  - To get the global_state, use the HAL_SDIO_GetState().
  - To get SDIO card common control register information, use the function HAL_SDIO_GetCardCommonControlRegister().
  - To get SDIO card function basic register information, use the function HAL_SDIO_GetCardFunctionBasicRegister().
  - To retrieve the last error code detected by the SDIO card, Set the USE_HAL_SDIO_GET_LAST_ERRORS to 1U
    the compilation flag through stm32tnxx_hal_conf.h module to allow the user to get the last error code by calling
    HAL_SDIO_GetLastErrorCodes().
  - To store the user data into the SDIO handle, set the USE_HAL_SDIO_USER_DATA to 1U
    the compilation flag through stm32tnxx_hal_conf.h module and use the function HAL_SDIO_SetUserData().
  - To get the user data, use the function HAL_SDIO_GetUserData().

6. SDIO card IO interrupt:
  - To enable an interrupt for function X, use the function HAL_SDIO_EnableIOFunctionInterrupt().
  - To disable an interrupt for function x, use the function HAL_SDIO_DisableIOFunctionInterrupt().
  - To enable an IO function x, use the function HAL_SDIO_EnableIOFunction().
  - To disable an IO function x, use the function HAL_SDIO_DisableIOFunction().
  - To select an IO function x, use the function HAL_SDIO_SelectIOFunction().
  - To abort an IO read/write operations for function x, use the function HAL_SDIO_AbortIOFunction().
  - to enable the asynchronous interrupt, use the function HAL_SDIO_EnableIOAsynInterrupt().
  - to disable the asynchronous interrupt, use the function HAL_SDIO_DisableIOAsynInterrupt().

7. SDIO Delay Block functions:
The delay block (DLYB) is used to generate an output clock that is phased from the input clock.
  - Use HAL_SDIO_SetConfigDlybDelay() to set the SDIO delay block configuration.
  - Use HAL_SDIO_GetDlybOutputClockPhase() to get the SDIO delay block output clock phase.
  - Use HAL_SDIO_CalculateDlybMaxClockPhase() to calculate the SDIO delay block maximum output clock phase.
  - Use HAL_SDIO_EnableDlyb() to enable the SDIO delay block.
  - Use HAL_SDIO_DisableDlyb() to disable the SDIO delay block.
  - Use HAL_SDIO_IsEnabledDlyb() to check if the delay block peripheral is enabled or not.

8. SDIO Card Interrupt and flags Inline functions:
  - HAL_SDIO_EnableIT()     : Enable the SDIO card interrupt to generate an interrupt request.
  - HAL_SDIO_DisableIT()    : Disable the SDIO card interrupt to clear an interrupt request.
  - HAL_SDIO_IsEnabledIT()  : Check whether or not the specified SDIO interrupt is set.
  - HAL_SDIO_IsActiveFlag() : Check whether the specified SDIO flag is set or not.
  - HAL_SDIO_ClearFlag()    : Clear the SDIO's pending flags.
  */
/**
  * @}
  */

/** @defgroup SDIO_Configuration_Table SDIO Configuration Table
  * @{
## Configuration inside the SDIO driver

Config defines                  |  Description    |  Default value    | Note
--------------------------------|-----------------|-------------------|-------------------------------------------------
USE_ASSERT_DBG_PARAM            | from the IDE    |      NONE         | Allows to use the assert checks parameters.
USE_ASSERT_DBG_STATE            | from the IDE    |      NONE         | Allows to use the assert checks states.
USE_HAL_CHECK_PARAM             | from hal_conf.h |       0           | Allows to use the run-time checks parameters.
USE_HAL_SDIO_REGISTER_CALLBACKS | from hal_conf.h |       0           | Allows to provide specific callback functions.
USE_HAL_SDIO_GET_LAST_ERRORS    | from hal_conf.h |       0           | Allows to get last errors codes.
USE_HAL_SDIO_USER_DATA          | from hal_conf.h |       0           | Allows to enable/disable user data.
USE_HAL_SDIO_CLK_ENABLE_MODEL   | from hal_conf.h | HAL_CLK_ENABLE_NO | Allows to enable the clock model for the SDIO.
  */
/**
  * @}
  */
#if defined(SDMMC1)
#if defined (USE_HAL_SDIO_MODULE) && (USE_HAL_SDIO_MODULE == 1)

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Private_Constants SDIO Private Constants
  * @{
  */
#define SDIO_INIT_FREQ                    400000U      /*!< Initialization phase : 400 kHz max                  */
#define SDIO_TIMEOUT_MS                   1000U        /*!< SDIO timeout millisecond                            */

#define SDIO_READ_FLAG                    0x0UL        /*!< SDIO Read flag for CMD52 and CMD53                  */
#define SDIO_WRITE_FLAG                   0x1UL        /*!< SDIO Write flag for CMD52 and CMD53                 */

#define SDIO_CCCR_REG_NUMBER              22U          /*!< SDIO card cccr register number                      */
#define SDIO_OCR_SDIO_S18R_POS            (1UL << 24U) /*!< SDIO OCR bit position for switching to 1.8V         */

#define SDIO_FBR_SIZE_REG                 256U         /*!< SDIO Function basic register 256 byte area          */

#define SDIO_FBR_SUPPORT_CSA              1U           /*!< SDIO function support Code Storage Area             */
#define SDIO_FBR_SUPPORT_POWER_SELECTION  1U           /*!< SDIO function support power selection               */

#define SDIO_FRB_BLOCK_SIZE_BYTE          0x10U        /*!< SDIO FBR block size in byte (2 bytes)               */

#define SDIO_RESET_DATA                   0U           /*!< SDIO data to be written to the specified CCCR byte,
                                                            indicating the reset operation                      */

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Private_Macros SDIO Private Macros
  * @{
  */
/*! Macro to get the handle instance */
#define SDIO_GET_INSTANCE(handle) ((SDMMC_TypeDef *)((uint32_t)(handle)->instance))

/*! SDIO RAW mode supported */
#define IS_SDIO_RAW(read_after_write) (((read_after_write) == HAL_SDIO_WRITE_ONLY) \
                                       || ((read_after_write) == HAL_SDIO_READ_AFTER_WRITE))

/*! SDIO Block mode supported */
#define IS_SDIO_BLOCK_MODE(block_mode) (((block_mode) == HAL_SDIO_BLOCK_MODE_BYTE) \
                                        || ((block_mode) == HAL_SDIO_BLOCK_MODE_BLOCK))

/*! SDIO Operation Code supported */
#define IS_SDIO_OP_CODE(op_code) (((op_code) == HAL_SDIO_OP_CODE_INC_NO) || ((op_code) == HAL_SDIO_OP_CODE_INC_AUTO))

/*! SDIO Function number supported */
#define IS_SDIO_FUNCTION(function_nbr) (((function_nbr) == HAL_SDIO_FUNCTION_0)     \
                                        || ((function_nbr) == HAL_SDIO_FUNCTION_1)  \
                                        || ((function_nbr) == HAL_SDIO_FUNCTION_2)  \
                                        || ((function_nbr) == HAL_SDIO_FUNCTION_3)  \
                                        || ((function_nbr) == HAL_SDIO_FUNCTION_4)  \
                                        || ((function_nbr) == HAL_SDIO_FUNCTION_5)  \
                                        || ((function_nbr) == HAL_SDIO_FUNCTION_6)  \
                                        || ((function_nbr) == HAL_SDIO_FUNCTION_7))

/*! SDIO Block data size supported */
#define IS_SDIO_SUPPORTED_DATA_BLOCK_SIZE(block_size) (((block_size) == HAL_SDIO_BLOCK_SIZE_1BYTE)       \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_2BYTE)    \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_4BYTE)    \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_8BYTE)    \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_16BYTE)   \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_32BYTE)   \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_64BYTE)   \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_128BYTE)  \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_256BYTE)  \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_512BYTE)  \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_1024BYTE) \
                                                       || ((block_size) == HAL_SDIO_BLOCK_SIZE_2048BYTE))

/*! SDIO base of function f's FBRs */
#define IS_SDIO_FBR_BASE(FUNCTION)  ((FUNCTION) * 0x100UL)

/*! SDIO set bits at a specific position */
#define SDIO_SET_BITS(value, pos)       ((value) << (pos))
/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Private_Functions SDIO Private Functions
  * @{
  */
static void SDIO_SetDefaultConfig(const hal_sdio_handle_t *hsdio);
static hal_status_t SDIO_SetConfig(hal_sdio_handle_t *hsdio, const hal_sdio_config_t *p_config);

static hal_status_t SDIO_Card_Identify(hal_sdio_handle_t *hsdio);
static hal_status_t SDIO_Card_IdentifyVoltageRange(const hal_sdio_handle_t *hsdio);
static hal_status_t SDIO_Card_IdentifyRelativeAddress(const hal_sdio_handle_t *hsdio);

static hal_status_t SDIO_ReadDirect(hal_sdio_handle_t *hsdio, uint32_t addr, hal_sdio_raw_t raw,
                                    hal_sdio_function_t function_nbr, uint8_t *p_data);
static hal_status_t SDIO_WriteDirect(hal_sdio_handle_t *hsdio, uint32_t addr, hal_sdio_raw_t raw,
                                     hal_sdio_function_t function_nbr, uint8_t data);
static hal_status_t SDIO_WriteExtended(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                       const uint8_t *p_data, uint16_t size_byte, uint32_t timeout_ms);
static hal_status_t SDIO_ReadExtended_DMA(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                          uint8_t *p_data, uint32_t size_byte);
static hal_status_t SDIO_WriteExtended_DMA(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                           uint8_t *p_data, uint32_t size_byte);
static uint8_t SDIO_Convert_Block_Size(const hal_sdio_handle_t *hsdio, uint32_t block_size);
static hal_status_t SDIO_IOFunction_IRQHandler(hal_sdio_handle_t *hsdio);
static void SDIO_ReadFullFIFO(hal_sdio_handle_t *hsdio, uint8_t *p_buff, uint32_t *data_remaining);
static void SDIO_ReadPartialFIFO(const hal_sdio_handle_t *hsdio, uint8_t *p_buff, uint32_t data_remaining);
static void SDIO_WriteToFullFIFO(hal_sdio_handle_t *hsdio, uint32_t *p_buff, uint32_t *data_remaining);
static void SDIO_WriteToPartialFIFO(const hal_sdio_handle_t *hsdio, const uint8_t *p_buff, uint32_t data_remaining);
static uint32_t SDIO_ComputeNbrOfBlocks(const hal_sdio_handle_t *hsdio, uint32_t size_byte, uint32_t block_size);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup SDIO_Exported_Functions HAL SDIO Functions
  * @{
  */
/** @addtogroup SDIO_Exported_Functions_Group1
  * @{
This section provides functions allowing to initialize and de-initialize the SDIO card :
- Call the function HAL_SDIO_Init() to initialize the selected HAL SDIO handle and associate an SDIO peripheral
  instance.
- Call the function HAL_SDIO_DeInit() to de-initialize the SDIO card.
  */
/**
  * @brief  Initialize the selected  HAL SDIO handle and associate an SDIO peripheral instance.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  * @param  instance HAL SDIO instance.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            SDIO handle has been correctly Initialized.
  */
hal_status_t HAL_SDIO_Init(hal_sdio_handle_t *hsdio, hal_sdio_t instance)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_ALL_INSTANCE((SDMMC_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hsdio == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Associate physical instance to logical object */
  hsdio->instance = instance;

#if defined (USE_HAL_SDIO_CLK_ENABLE_MODEL) && (USE_HAL_SDIO_CLK_ENABLE_MODEL == HAL_CLK_ENABLE_PERIPH_ONLY)
  if (hsdio->instance == HAL_SDIO_CARD_1)
  {
    HAL_RCC_SDMMC1_EnableClock();
  }
#if defined (SDMMC2)
  else if (hsdio->instance == HAL_SDIO_CARD_2)
  {
    HAL_RCC_SDMMC2_EnableClock();
  }
#endif /* SDMMC2 */
  else
  {
    /* Nothing to do */
  }
#endif /* USE_HAL_SDIO_CLK_ENABLE_MODEL */

#if defined (USE_HAL_SDIO_REGISTER_CALLBACKS) && (USE_HAL_SDIO_REGISTER_CALLBACKS == 1U)
  hsdio->p_xfer_cplt_callback = HAL_SDIO_XferCpltCallback;
  hsdio->p_error_callback = HAL_SDIO_ErrorCallback;
#endif /* USE_HAL_SDIO_REGISTER_CALLBACKS */

  hsdio->p_io_function_cplt_callback[HAL_SDIO_MAX_IO_NUMBER - 1U] = HAL_SDIO_IOFunctionCallback;

#if defined (USE_HAL_SDIO_USER_DATA) && (USE_HAL_SDIO_USER_DATA == 1)
  hsdio->p_user_data = NULL;
#endif /* USE_HAL_SDIO_USER_DATA */

#if defined (USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
  hsdio->last_error_codes = HAL_SDIO_ERROR_NONE;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

  hsdio->context = SDMMC_CONTEXT_NONE;
  hsdio->global_state = HAL_SDIO_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  De-Initializes the SDIO card.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  */
void HAL_SDIO_DeInit(hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_ALL_INSTANCE(SDIO_GET_INSTANCE(hsdio)));

  (void)SDMMC_SET_PWR_STATE(SDIO_GET_INSTANCE(hsdio), SDMMC_PWR_OFF);
  hsdio->global_state = HAL_SDIO_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup SDIO_Exported_Functions_Group2 Set and Get configurations functions
  * @{
This subsection provides a set of functions allowing to configure the SDIO peripheral:

- Global configuration APIs:
  - HAL_SDIO_SetConfig()           : Allowing to set the HAL peripheral instance into a ready to use state (idle)
                                     according to the user parameters.
  - HAL_SDIO_GetConfig()           : Allowing to retrieve the HAL peripheral configuration.
  - HAL_SDIO_NotifyCardInsertion() : Allowing to set the user parameters after detection the insertion of SDIO card.
  - HAL_SDIO_NotifyCardRemoval()   : Allowing to set the default SDMMC config after the removal of the SDIO card.

- Unitary configuration APIs:
  - HAL_SDIO_SetDataBusWidth()      : Allowing to set wide bus operation.
  - HAL_SDIO_GetDataBusWidth()      : Allowing to get wide bus operation.
  - HAL_SDIO_SetTransferClockFreq() : Allowing to set the SDIO Clock.
  - HAL_SDIO_GetTransferClockFreq() : Allowing to get the SDIO Clock.
  - HAL_SDIO_SetBlockSize()         : Allowing to set the SDIO block size.
  - HAL_SDIO_SetSpeedMode()         : Allowing to configure the speed mode on the SDIO card.
  - HAL_SDIO_ResetCard()            : Allowing to reset SDIO Card.
  - HAL_SDIO_SetDataTimeout()       : Allowing to modify the data timeout value according to the SDIO card type.
  - HAL_SDIO_GetDataTimeout()       : Allowing to retrieve the data timeout value.
  - HAL_SDIO_GetClockFreq()         : Allowing to retrieve the peripheral clock frequency for SDIO card.
These APIs are intended to dynamically modify/Retrieve a unitary item meaning that a global config has been already
applied.
  */
/**
  * @brief  Configure the SDIO according to the user parameters.
  * @param  hsdio              Pointer to a hal_sdio_handle_t structure.
  * @param  p_config           Pointer to a hal_sdio_config_t structure that contains the SDIO configuration.
  * @param  sdio_identify_card Pointer to the identification callback function.
  * @note   If the param sdio_identify_card is passed as NULL parameter, the SDIO module will be identified using the
  *         identification card function defined in the SDIO source file.
  * @note   If sdio_identify_card is passed as not null, the user utilizes a custom function to perform the
  *         identification phase for the SDIO module. This function must be properly registered and implemented by the
  *         user to handle the specific identification sequence of the SDIO card.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         SDIO instance is already configured and cannot be modified.
  * @retval HAL_OK            SDIO instance has been correctly configured.
  */
hal_status_t HAL_SDIO_SetConfig(hal_sdio_handle_t *hsdio, const hal_sdio_config_t *p_config,
                                hal_sdio_identify_card_t sdio_identify_card)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_EDGE(((uint32_t)p_config->clk_cfg.clk_edge)));
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_POWER_SAVE(((uint32_t)p_config->clk_cfg.clk_power_save)));
  ASSERT_DBG_PARAM(IS_SDMMC_BUS_WIDE(((uint32_t)p_config->bus_wide)));
  ASSERT_DBG_PARAM(IS_SDMMC_HARDWARE_FLOW_CONTROL(((uint32_t)p_config->hw_flow_ctrl)));
  ASSERT_DBG_PARAM(p_config->clk_cfg.clk_hz != 0U);
  ASSERT_DBG_PARAM(IS_SDMMC_TRANSCEIVER(((uint8_t)p_config->transceiver)));

  ASSERT_DBG_STATE(hsdio->global_state, ((uint32_t)HAL_SDIO_STATE_INIT) | (uint32_t)HAL_SDIO_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsdio->data_timeout_cycle = p_config->data_timeout_cycle;
  hsdio->sdio_transceiver   = p_config->transceiver;

  SDIO_SetDefaultConfig(hsdio);

  /* SDIO enumeration sequence */
  hsdio->p_sdio_card_identification_callback = (sdio_identify_card == NULL) ? SDIO_Card_Identify : sdio_identify_card;
  if (hsdio->p_sdio_card_identification_callback(hsdio) != HAL_OK)
  {
    hsdio->global_state = HAL_SDIO_STATE_CARD_REMOVED;
    return HAL_ERROR;
  }

  if (SDIO_SetConfig(hsdio, p_config) != HAL_OK)
  {
    hsdio->global_state = HAL_SDIO_STATE_CARD_REMOVED;
    return HAL_ERROR;
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get the SDIO configuration.
  * @param  hsdio    Pointer to a hal_sdio_handle_t structure.
  * @param  p_config Pointer to a hal_sdio_config_t structure that contains the SDIO configuration.
  */
void HAL_SDIO_GetConfig(const hal_sdio_handle_t *hsdio, hal_sdio_config_t *p_config)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_config_t sdmmc_cfg = {0};

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE | (uint32_t)HAL_SDIO_STATE_ACTIVE |
                   (uint32_t)HAL_SDIO_STATE_CARD_REMOVED);

  p_config->transceiver = hsdio->sdio_transceiver;

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  SDMMC_GetConfig(p_instance, &sdmmc_cfg);
  p_config->bus_wide               = (hal_sdio_bus_wide_t)(sdmmc_cfg.bus_wide);
  p_config->hw_flow_ctrl           = (hal_sdio_hardware_flow_control_t)(sdmmc_cfg.hardware_flow_control);
  p_config->clk_cfg.clk_edge       = (hal_sdio_clock_edge_t)sdmmc_cfg.clk.clock_edge;
  p_config->clk_cfg.clk_power_save = (hal_sdio_clock_power_save_t)sdmmc_cfg.clk.clock_power_save;
  p_config->clk_cfg.clk_hz = HAL_RCC_SDMMC_GetKernelClkFreq(p_instance);
  if (sdmmc_cfg.clk.clock_div != 0U)
  {
    p_config->clk_cfg.clk_hz /= (2U * sdmmc_cfg.clk.clock_div);
  }
}

/**
  * @brief  Notify SDIO card after insertion.
  * @param  hsdio    Pointer to a hal_sdio_handle_t structure.
  * @param  p_config Pointer to a hal_sdio_config_t structure that contains the SDIO configuration.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            SDIO instance has been correctly configured after detection.
  */
hal_status_t HAL_SDIO_NotifyCardInsertion(hal_sdio_handle_t *hsdio, const hal_sdio_config_t *p_config)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_EDGE(((uint32_t)p_config->clk_cfg.clk_edge)));
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_POWER_SAVE(((uint32_t)p_config->clk_cfg.clk_power_save)));
  ASSERT_DBG_PARAM(IS_SDMMC_BUS_WIDE(((uint32_t)p_config->bus_wide)));
  ASSERT_DBG_PARAM(IS_SDMMC_HARDWARE_FLOW_CONTROL(((uint32_t)p_config->hw_flow_ctrl)));
  ASSERT_DBG_PARAM(p_config->clk_cfg.clk_hz != 0U);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_CARD_REMOVED);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* SDIO enumeration sequence */
  if (hsdio->p_sdio_card_identification_callback == NULL)
  {
    hsdio->p_sdio_card_identification_callback = SDIO_Card_Identify;
  }

  if (hsdio->p_sdio_card_identification_callback(hsdio) != HAL_OK)
  {
    hsdio->global_state = HAL_SDIO_STATE_CARD_REMOVED;
    return HAL_ERROR;
  }

  if (SDIO_SetConfig(hsdio, p_config) != HAL_OK)
  {
    hsdio->global_state = HAL_SDIO_STATE_CARD_REMOVED;
    return HAL_ERROR;
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Notify SDIO card after removal.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  * @retval HAL_OK SDIO card has been correctly re-configured with its default configuration.
  */
hal_status_t HAL_SDIO_NotifyCardRemoval(hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE | (uint32_t)HAL_SDIO_STATE_ACTIVE);

  SDIO_SetDefaultConfig(hsdio);

  hsdio->global_state = HAL_SDIO_STATE_CARD_REMOVED;

  return HAL_OK;
}

/**
  * @brief  Set SDIO wide bus.
  * @param  hsdio     Pointer to a hal_sdio_handle_t structure.
  * @param  bus_wide  Specifies the SDIO card wide bus mode.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
hal_status_t HAL_SDIO_SetDataBusWidth(hal_sdio_handle_t *hsdio, hal_sdio_bus_wide_t bus_wide)
{
  SDMMC_TypeDef *p_instance;
  hal_status_t status = HAL_OK;
  uint8_t data;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_BUS_WIDE(((uint32_t)bus_wide)));

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  switch (bus_wide)
  {
    case HAL_SDIO_BUS_WIDE_4BIT:
      data = 2U;
      break;
    case HAL_SDIO_BUS_WIDE_8BIT:
      data = 3U;
      break;
    default: /* HAL_SDIO_BUS_WIDE_1BIT */
      data = 0U;
      break;
  }

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  SDMMC_MODIFY_CLKCR(p_instance, SDMMC_CLKCR_WIDBUS, (uint32_t)bus_wide);

  if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR4_BYTE3, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0, data) != HAL_OK)
  {
    status = HAL_ERROR;
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}

/**
  * @brief  Get SDIO wide bus.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  * @retval hal_sdio_bus_wide_t sdio wide bus.
  */
hal_sdio_bus_wide_t HAL_SDIO_GetDataBusWidth(const hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE | (uint32_t)HAL_SDIO_STATE_ACTIVE);

  return (hal_sdio_bus_wide_t)(uint32_t)STM32_READ_BIT(SDIO_GET_INSTANCE(hsdio)->CLKCR, SDMMC_CLKCR_WIDBUS);
}


/**
  * @brief  Set the SDIO transfer clock frequency.
  * @param  hsdio                  Pointer to a hal_sdio_handle_t structure.
  * @param  transfer_clock_freq_hz SDIO Clock frequency in Hz.
  * @retval HAL_OK                 Operation completed.
  */
hal_status_t HAL_SDIO_SetTransferClockFreq(const hal_sdio_handle_t *hsdio, const uint32_t transfer_clock_freq_hz)
{
  SDMMC_TypeDef *p_instance;
  uint32_t clock_div;
  uint32_t sdmmc_clk;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(transfer_clock_freq_hz != 0U);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq(p_instance);
  if (sdmmc_clk == 0U)
  {
    return HAL_ERROR;
  }

  clock_div = (sdmmc_clk) / (2U * transfer_clock_freq_hz);
  SDMMC_MODIFY_CLKCR(p_instance, SDMMC_CLKCR_CLKDIV, clock_div);

  return HAL_OK;
}

/**
  * @brief  Get the SDIO transfer clock frequency.
  * @param  hsdio    Pointer to a hal_sdio_handle_t structure.
  * @retval uint32_t transfer clock frequency value in Hz.
  */
uint32_t HAL_SDIO_GetTransferClockFreq(const hal_sdio_handle_t *hsdio)
{
  SDMMC_TypeDef *p_instance;
  uint32_t transfer_clock_freq;
  uint32_t clk_div;

  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE | (uint32_t)HAL_SDIO_STATE_ACTIVE);

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  clk_div = STM32_READ_BIT(p_instance->CLKCR, SDMMC_CLKCR_CLKDIV);

  transfer_clock_freq = HAL_RCC_SDMMC_GetKernelClkFreq(p_instance);

  if (clk_div != 0U)
  {
    transfer_clock_freq /= (2U * clk_div);
  }

  return transfer_clock_freq;
}

/**
  * @brief  Set the SDIO block size.
  * @param  hsdio        Pointer to a hal_sdio_handle_t structure.
  * @param  function_nbr Specifies the SDIO function number.
  * @param  block_size   Specifies the SDIO Block size to set.
  * @retval HAL_ERROR    An error has occurred.
  * @retval HAL_OK       Operation completed.
  */
hal_status_t HAL_SDIO_SetBlockSize(hal_sdio_handle_t *hsdio, hal_sdio_function_t function_nbr,
                                   hal_sdio_block_size_t block_size)
{
  hal_sdio_extended_cmd_t cmd53;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_FUNCTION(function_nbr));
  ASSERT_DBG_PARAM(IS_SDIO_SUPPORTED_DATA_BLOCK_SIZE(block_size));

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  cmd53.io_function_nbr = HAL_SDIO_FUNCTION_0;
  cmd53.operation_code  = HAL_SDIO_OP_CODE_INC_AUTO;
  cmd53.block_mode      = HAL_SDIO_BLOCK_MODE_BYTE;
  cmd53.reg_addr        = (uint32_t)IS_SDIO_FBR_BASE((uint16_t)function_nbr) + SDIO_FRB_BLOCK_SIZE_BYTE;
  if (SDIO_WriteExtended(hsdio, &cmd53, (uint8_t *)(&block_size), SDIO_FRB_BLOCK_SIZE_BYTE,
                         SDMMC_CMD_TIMEOUT) != HAL_OK)
  {
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }

  hsdio->block_size = block_size;
  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Configure the data rate.
  * @param  hsdio      Pointer to a hal_sdio_handle_t structure.
  * @param  speed_mode Specifies the SDIO speed mode to set.
  * @retval HAL_ERROR  An error has occurred.
  * @retval HAL_OK     Operation completed.
  */
hal_status_t HAL_SDIO_SetSpeedMode(hal_sdio_handle_t *hsdio, const hal_sdio_speed_mode_t speed_mode)
{
  SDMMC_TypeDef *p_instance;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  switch (speed_mode)
  {
    case HAL_SDIO_SPEED_MODE_SDR25:
      break;

    case HAL_SDIO_SPEED_MODE_SDR50:
      SDMMC_MODIFY_CLKCR(p_instance, SDMMC_CLKCR_BUSSPEED, SDMMC_CLKCR_BUSSPEED);
      break;

    case HAL_SDIO_SPEED_MODE_DDR50:
      SDMMC_MODIFY_CLKCR(p_instance, SDMMC_CLKCR_DDR | SDMMC_CLKCR_BUSSPEED,
                         SDMMC_CLKCR_DDR | SDMMC_CLKCR_BUSSPEED);
      break;

    case HAL_SDIO_SPEED_MODE_SDR104:
      SDMMC_MODIFY_CLKCR(p_instance, SDMMC_CLKCR_BUSSPEED, SDMMC_CLKCR_BUSSPEED);
      break;

    default: /* SDR12 */
      break;
  }

  if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR16_BYTE3, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                       (uint8_t)speed_mode) != HAL_OK)
  {
    status = HAL_ERROR;
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}

/**
  * @brief  Reset SDIO Card.
  * @param  hsdio     Pointer to a hal_sdio_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
hal_status_t HAL_SDIO_ResetCard(hal_sdio_handle_t *hsdio)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  /** To reset the SDIO module by CMD52 with writing to RES in CCCR.
    * In order to reset an I/O card or the I/O portion of a combo card, Use CMD52 to write 1 to the RES bit in
    * the CCCR(bit3 of register 6).
    * Setting the RES bit to 1 does not affect the current card protocol selection.
    */
  if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR4_BYTE2, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                       SDIO_RESET_DATA) != HAL_OK)
  {
    status = HAL_ERROR;
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}

/**
  * @brief  Set SDIO data timeout.
  * @param  hsdio              Pointer to a hal_sdio_handle_t structure.
  * @param  data_timeout_cycle SDIO data timeout cycle.
  * @retval HAL_OK SDIO card has been correctly set the data timeout cycle value.
  */
hal_status_t HAL_SDIO_SetDataTimeout(hal_sdio_handle_t *hsdio, uint32_t data_timeout_cycle)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  hsdio->data_timeout_cycle = data_timeout_cycle;

  return HAL_OK;
}

/**
  * @brief  Get SDIO data timeout.
  * @param  hsdio    Pointer to a hal_sdio_handle_t structure.
  * @retval uint32_t data_timeout_cycle value in millisecond.
  */
uint32_t HAL_SDIO_GetDataTimeout(const hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE  | (uint32_t)HAL_SDIO_STATE_ACTIVE);

  return hsdio->data_timeout_cycle;
}

/** @brief  Return the peripheral clock frequency for SDIO.
  * @param  hsdio    Pointer to a hal_sdio_handle_t structure
  * @retval uint32_t Frequency in Hz
  * @retval 0 source clock of the SDIO not configured or not ready.
  */
uint32_t HAL_SDIO_GetClockFreq(const hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_STATE(hsdio->global_state, ((uint32_t)HAL_SDIO_STATE_IDLE | (uint32_t)HAL_SDIO_STATE_ACTIVE));

  return HAL_RCC_SDMMC_GetKernelClkFreq(SDIO_GET_INSTANCE(hsdio));
}

/**
  * @}
  */

/** @addtogroup SDIO_Exported_Functions_Group3 Process functions
  * @{
This subsection provides a set of functions allowing to manage the data transfer from/to SDIO card.

There are 2 categories of HAL functions APIs to manage the data transfer:
- Blocking mode: Polling
  - HAL_SDIO_ReadExtended().
  - HAL_SDIO_WriteExtended().
- Non-Blocking mode: DMA
 - HAL_SDIO_ReadExtended_DMA().
 - HAL_SDIO_WriteExtended_DMA().

There are 2 categories of HAL functions APIs to manage data register from/to SDIO card:
- HAL_SDIO_ReadDirect().
- HAL_SDIO_WriteDirect().
  */
/**
  * @brief  Read data from a specified address using the direct mode through cmd52.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  p_argument        Pointer to cmd52 argument structure.
  * @param  p_data            Pointer to the buffer that will contain the received data.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SDIO_ReadDirect(hal_sdio_handle_t *hsdio, const hal_sdio_direct_cmd_t *p_argument, uint8_t *p_data)
{
  SDMMC_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_argument != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_RAW(p_argument->read_after_write));
  ASSERT_DBG_PARAM(IS_SDIO_FUNCTION(p_argument->io_function_nbr));
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_argument == NULL) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
  hsdio->last_error_codes = HAL_SDIO_ERROR_NONE;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  if (SDIO_ReadDirect(hsdio,                        \
                      p_argument->reg_addr,         \
                      p_argument->read_after_write, \
                      p_argument->io_function_nbr,  \
                      p_data) != HAL_OK)
  {
    hsdio->context = SDMMC_CONTEXT_NONE;
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return HAL_OK;
}


/**
  * @brief  Write data to a specified address using the direct mode through cmd52.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  p_argument        Pointer to cmd52 argument structure.
  * @param  data              Data to write.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SDIO_WriteDirect(hal_sdio_handle_t *hsdio, const hal_sdio_direct_cmd_t *p_argument, uint8_t data)
{
  SDMMC_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_argument != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_RAW(p_argument->read_after_write));
  ASSERT_DBG_PARAM(IS_SDIO_FUNCTION(p_argument->io_function_nbr));

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_argument == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
  hsdio->last_error_codes = HAL_SDIO_ERROR_NONE;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  if (SDIO_WriteDirect(hsdio,                        \
                       p_argument->reg_addr,         \
                       p_argument->read_after_write, \
                       p_argument->io_function_nbr,  \
                       data) != HAL_OK)
  {
    hsdio->context = SDMMC_CONTEXT_NONE;
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Read data from a specified address using extended mode through cmd53.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  p_argument        Pointer to cmd53 argument structure.
  * @param  p_data            Pointer to the buffer that will contain the data to read.
  * @param  size_byte         Size to read.
  * @param  timeout_ms        Specify timeout value in millisecond.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SDIO_ReadExtended(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument, uint8_t *p_data,
                                   uint32_t size_byte, uint32_t timeout_ms)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t cmd;
  uint32_t error_state;
  uint32_t tick_start = HAL_GetTick();
  uint32_t data_remaining;
  uint32_t nbr_of_block;
  uint8_t *p_tmp_buff = p_data;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_argument != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_BLOCK_MODE(p_argument->block_mode));
  ASSERT_DBG_PARAM(IS_SDIO_OP_CODE(p_argument->operation_code));
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_argument == NULL) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
  hsdio->last_error_codes = HAL_SDIO_ERROR_NONE;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

  p_instance  = SDIO_GET_INSTANCE(hsdio);
  nbr_of_block = SDIO_ComputeNbrOfBlocks(hsdio, size_byte, (uint32_t)hsdio->block_size);

  /* Initialize data control register */
  if ((p_instance->DCTRL & SDMMC_DCTRL_SDIOEN) != 0U)
  {
    p_instance->DCTRL = SDMMC_DCTRL_SDIOEN;
  }
  else
  {
    p_instance->DCTRL = 0U;
  }

  /* Configure the SDIO dpsm (Data Path State Machine) */
  data_ctrl.data_timeout = hsdio->data_timeout_cycle;
  if (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK)
  {
    data_ctrl.data_length = (uint32_t)(nbr_of_block * (uint32_t)hsdio->block_size);
    data_ctrl.data_block_size = SDIO_Convert_Block_Size(hsdio, (uint32_t)hsdio->block_size);
  }
  else
  {
    data_ctrl.data_length = (size_byte > 0U) ? size_byte : (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE;
    data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_1B;
  }

  data_ctrl.transfer_dir = SDMMC_TRANSFER_DIR_TO_SDMMC ;
  data_ctrl.transfer_mode = (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK) ? SDMMC_TRANSFER_MODE_BLOCK :
                            SDMMC_TRANSFER_MODE_SDIO;
  data_ctrl.dpsm = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  hsdio->context = (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK) ? SDMMC_CONTEXT_READ_MULTIPLE_BLOCK :
                   SDMMC_CONTEXT_READ_SINGLE_BLOCK;
  cmd = SDIO_SET_BITS(SDIO_READ_FLAG, 31U);
  cmd |= SDIO_SET_BITS((uint32_t)p_argument->io_function_nbr, 28U);
  cmd |= SDIO_SET_BITS(((uint32_t)p_argument->block_mode), 27U);
  cmd |= SDIO_SET_BITS(((uint32_t)p_argument->operation_code), 26U);
  cmd |= SDIO_SET_BITS((p_argument->reg_addr & 0x1FFFFU), 9U);
  if (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BYTE)
  {
    cmd |= (((uint32_t)size_byte) & 0x1FFU);
  }
  else /* HAL_SDIO_BLOCK_MODE_BLOCK */
  {
    cmd |= nbr_of_block & 0x1FFU;
  }
  error_state = SDMMC_SDIO_SendReadWriteExtendedCmd(p_instance, cmd);
  if (error_state != HAL_SDIO_ERROR_NONE)
  {
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= error_state;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
    hsdio->context = SDMMC_CONTEXT_NONE;
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }

  data_remaining = data_ctrl.data_length;
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL \
                              | SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_DATAEND) == 0U)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXFIFOHF) == 0U) && (data_remaining >= 32U))
    {
      SDIO_ReadFullFIFO(hsdio, p_tmp_buff, &data_remaining);
    }
    else if (data_remaining < 32U)
    {
      SDIO_ReadPartialFIFO(hsdio, p_tmp_buff, data_remaining);
    }
    else
    {
      /* Nothing to do */
    }

    if ((HAL_GetTick() - tick_start) >=  timeout_ms)
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
      hsdio->context = SDMMC_CONTEXT_NONE;
      hsdio->global_state = HAL_SDIO_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }
  SDMMC_CMDTRANS_DISABLE(p_instance);
  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT) != 0U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= HAL_SDIO_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    hsdio->context = SDMMC_CONTEXT_NONE;
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL) != 0U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= HAL_SDIO_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    hsdio->context = SDMMC_CONTEXT_NONE;
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR) != 0U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= HAL_SDIO_ERROR_RX_OVERRUN;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    hsdio->context = SDMMC_CONTEXT_NONE;
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }
  else
  {
    /* Nothing to do */
  }

  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Write data from a specified address using extended mode through cmd53.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  p_argument        Pointer to cmd53 argument structure.
  * @param  p_data            Pointer to the buffer that will contain the data to transmit.
  * @param  size_byte         Block size to write.
  * @param  timeout_ms        Specify timeout value in millisecond.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SDIO_WriteExtended(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                    const uint8_t *p_data, uint32_t size_byte, uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_argument != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_BLOCK_MODE(p_argument->block_mode));
  ASSERT_DBG_PARAM(IS_SDIO_OP_CODE(p_argument->operation_code));
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_argument == NULL) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
  hsdio->last_error_codes = HAL_SDIO_ERROR_NONE;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

  if (SDIO_WriteExtended(hsdio, p_argument, p_data, (uint16_t)size_byte, timeout_ms) != HAL_OK)
  {
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CLEAR_FLAG(SDIO_GET_INSTANCE(hsdio), SDMMC_STATIC_DATA_FLAGS);
  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Read data from a specified address using extended mode through cmd53 in DMA mode.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  p_argument        Pointer to cmd53 argument structure.
  * @param  p_data            Pointer to the buffer that will contain the data to transmit.
  * @param  size_byte         Block size to write.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SDIO_ReadExtended_DMA(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                       uint8_t *p_data, uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_argument != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_BLOCK_MODE(p_argument->block_mode));
  ASSERT_DBG_PARAM(IS_SDIO_OP_CODE(p_argument->operation_code));
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_argument == NULL) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
  hsdio->last_error_codes = HAL_SDIO_ERROR_NONE;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

  if (SDIO_ReadExtended_DMA(hsdio, p_argument, p_data, size_byte) != HAL_OK)
  {
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Write data from a specified address using extended mode through cmd53 in DMA mode.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  p_argument        Pointer to cmd53 argument structure.
  * @param  p_data            Pointer to the buffer that will contain the data to transmit.
  * @param  size_byte         Block size to write.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SDIO_WriteExtended_DMA(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                        uint8_t *p_data, uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_argument != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_BLOCK_MODE(p_argument->block_mode));
  ASSERT_DBG_PARAM(IS_SDIO_OP_CODE(p_argument->operation_code));
  ASSERT_DBG_PARAM(p_data != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_argument == NULL) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
  hsdio->last_error_codes = HAL_SDIO_ERROR_NONE;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

  if (SDIO_WriteExtended_DMA(hsdio, p_argument, p_data, size_byte) != HAL_OK)
  {
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup SDIO_Exported_Functions_Group4
  * @{
    This subsection provides a set of callback functions allowing to manage the data transfer from/to SDIO card.
  */

/**
  * @brief  This function handles SDIO card interrupt request.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  */
void HAL_SDIO_IRQHandler(hal_sdio_handle_t *hsdio)
{
  SDMMC_TypeDef *p_instance;
  hal_status_t error_state;
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
  uint32_t error_code;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
  hal_sdio_extended_cmd_t cmd53;
  uint32_t context;
  uint32_t flags;

  ASSERT_DBG_PARAM(hsdio != NULL);

  p_instance  = SDIO_GET_INSTANCE(hsdio);
  context = hsdio->context;
  flags = STM32_READ_REG(p_instance->STAR);

  if (STM32_READ_BIT(flags, SDMMC_FLAG_SDIOIT) != 0U)
  {
    (void)SDIO_IOFunction_IRQHandler(hsdio);
  }

  if (STM32_READ_BIT(flags, SDMMC_FLAG_DATAEND) != 0U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_FLAG_DATAEND);

    hsdio->global_state = HAL_SDIO_STATE_IDLE;

    SDMMC_DISABLE_IT(p_instance, SDMMC_IT_DATAEND  | SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR \
                     | SDMMC_IT_RXOVERR  | SDMMC_IT_TXFIFOHE | SDMMC_IT_RXFIFOHF);

    SDMMC_DISABLE_IT(p_instance, SDMMC_IT_IDMABTC);
    SDMMC_CMDTRANS_DISABLE(p_instance);

    if ((context & SDMMC_CONTEXT_DMA) != 0U)
    {
      p_instance->DLENR = 0;
      p_instance->IDMACTRLR = SDMMC_DISABLE_IDMA;
      if ((p_instance->DCTRL & SDMMC_DCTRL_SDIOEN) != 0U)
      {
        p_instance->DCTRL = SDMMC_DCTRL_SDIOEN;
      }
      else
      {
        p_instance->DCTRL = 0U;
      }
    }

    if (hsdio->remaining_data != 0U)
    {
      cmd53.block_mode      = HAL_SDIO_BLOCK_MODE_BYTE;
      cmd53.reg_addr        = hsdio->next_reg_addr;
      cmd53.io_function_nbr = HAL_SDIO_FUNCTION_1;
      cmd53.operation_code  = HAL_SDIO_OP_CODE_INC_AUTO;
      if (((context & SDMMC_CONTEXT_READ_SINGLE_BLOCK) != 0U) || ((context & SDMMC_CONTEXT_READ_MULTIPLE_BLOCK) != 0U))
      {
        hsdio->p_xfer_buff = (uint8_t *)hsdio->next_data_addr;
        error_state =  SDIO_ReadExtended_DMA(hsdio, &cmd53, hsdio->p_xfer_buff, hsdio->remaining_data);
      }
      else
      {
        hsdio->p_xfer_buff = (uint8_t *)hsdio->next_data_addr;
        error_state =  SDIO_WriteExtended_DMA(hsdio, &cmd53, hsdio->p_xfer_buff, hsdio->remaining_data);
      }
      if (error_state != HAL_OK)
      {
        hsdio->global_state = HAL_SDIO_STATE_IDLE;
#if defined (USE_HAL_SDIO_REGISTER_CALLBACKS) && (USE_HAL_SDIO_REGISTER_CALLBACKS == 1)
        hsdio->p_error_callback(hsdio);
#else
        HAL_SDIO_ErrorCallback(hsdio);
#endif /* USE_HAL_SDIO_REGISTER_CALLBACKS */
      }
    }
    else if (((context & SDMMC_CONTEXT_WRITE_SINGLE_BLOCK) != 0U)
             || ((context & SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK) != 0U))
    {
      hsdio->context = SDMMC_CONTEXT_NONE;
      hsdio->global_state = HAL_SDIO_STATE_IDLE;
#if defined (USE_HAL_SDIO_REGISTER_CALLBACKS) && (USE_HAL_SDIO_REGISTER_CALLBACKS == 1)
      hsdio->p_xfer_cplt_callback(hsdio, HAL_SDIO_EVENT_CB_TX_CPLT);
#else
      HAL_SDIO_XferCpltCallback(hsdio, HAL_SDIO_EVENT_CB_TX_CPLT);
#endif /* USE_HAL_SDIO_REGISTER_CALLBACKS */
    }
    else
    {
      hsdio->context = SDMMC_CONTEXT_NONE;
      hsdio->global_state = HAL_SDIO_STATE_IDLE;
#if defined (USE_HAL_SDIO_REGISTER_CALLBACKS) && (USE_HAL_SDIO_REGISTER_CALLBACKS == 1)
      hsdio->p_xfer_cplt_callback(hsdio, HAL_SDIO_EVENT_CB_RX_CPLT);
#else
      HAL_SDIO_XferCpltCallback(hsdio, HAL_SDIO_EVENT_CB_RX_CPLT);
#endif /* USE_HAL_SDIO_REGISTER_CALLBACKS */
    }
  }

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_RXOVERR \
                           | SDMMC_FLAG_TXUNDERR) != 0U)
  {
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    error_code = SDMMC_READ_REG(p_instance, STAR);

    if ((error_code & SDMMC_IT_DCRCFAIL) != 0U)
    {
      hsdio->last_error_codes |= HAL_SDIO_ERROR_DATA_CRC_FAIL;
    }
    if ((error_code & SDMMC_IT_DTIMEOUT) != 0U)
    {
      hsdio->last_error_codes |= HAL_SDIO_ERROR_DATA_TIMEOUT;
    }
    if ((error_code & SDMMC_IT_RXOVERR) != 0U)
    {
      hsdio->last_error_codes |= HAL_SDIO_ERROR_RX_OVERRUN;
    }
    if ((error_code & SDMMC_IT_TXUNDERR) != 0U)
    {
      hsdio->last_error_codes |= HAL_SDIO_ERROR_TX_UNDERRUN;
    }
    hsdio->context = SDMMC_CONTEXT_NONE;
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

#if defined (USE_HAL_SDIO_REGISTER_CALLBACKS) && (USE_HAL_SDIO_REGISTER_CALLBACKS == 1)
    hsdio->p_error_callback(hsdio);
#else
    HAL_SDIO_ErrorCallback(hsdio);
#endif /* USE_HAL_SDIO_REGISTER_CALLBACKS */
  }
}

/**
  * @brief Transfer completed callbacks.
  * @param hsdio    Pointer to a hal_sdio_handle_t structure.
  * @param cb_event Xfer callback event in hal_sdio_event_cb_t structure.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_SDIO_XferCpltCallback(hal_sdio_handle_t *hsdio, hal_sdio_event_cb_t cb_event)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hsdio);
  STM32_UNUSED(cb_event);
}

/**
  * @brief  SDIO error callbacks.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_SDIO_ErrorCallback(hal_sdio_handle_t *hsdio)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hsdio);
}

/**
  * @brief  SDIO IO Function complete callback.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  * @param  func  SDIO IO Function.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_SDIO_IOFunctionCallback(hal_sdio_handle_t *hsdio, uint32_t func)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hsdio);
  STM32_UNUSED(func);
}

/**
  * @brief  Enable/Disable the SDIO Transceiver 1.8V Mode callback.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  * @param  state Voltage Switch State.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_SDIO_DriveTransceiver_1_8V_Callback(hal_sdio_handle_t *hsdio, hal_sdio_transceiver_state_t state)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hsdio);
  STM32_UNUSED(state);
}

#if defined (USE_HAL_SDIO_REGISTER_CALLBACKS) && (USE_HAL_SDIO_REGISTER_CALLBACKS == 1U)
/**
  * @brief Register the SDIO Xfer callback to be used instead of the weak HAL_SDIO_XferCpltCallback predefined callback.
  * @param hsdio              Pointer to a hal_sdio_handle_t structure.
  * @param callback           Pointer to the Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_SDIO_RegisterXferCpltCallback(hal_sdio_handle_t *hsdio, hal_sdio_xfer_cb_t callback)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsdio->p_xfer_cplt_callback = callback;

  return HAL_OK;
}

/**
  * @brief  Register the SDIO Error callback to be used instead of the weak HAL_SDIO_ErrorCallback predefined callback.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  callback          Pointer to the callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_SDIO_RegisterErrorCallback(hal_sdio_handle_t *hsdio, hal_sdio_cb_t callback)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsdio->p_error_callback = callback;

  return HAL_OK;
}

/**
  * @brief  Register a User SDIO Transceiver callback to be used instead of the weak (overridden) predefined callback.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  callback          Pointer to the callback function
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_SDIO_RegisterTransceiverCallback(hal_sdio_handle_t *hsdio, hal_sdio_transceiver_cb_t callback)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsdio->p_transceiver_1_8V_callback = callback;

  return HAL_OK;
}

#endif /* USE_HAL_SDIO_REGISTER_CALLBACKS */

/**
  * @brief  Register an IO function callback.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  io_function       IO function number.
  * @param  callback          IO IRQ handler.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_SDIO_RegisterIOFunctionCallback(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function,
                                                 hal_sdio_io_function_cb_t callback)
{
  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_FUNCTION(io_function));
  ASSERT_DBG_PARAM(callback != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsdio->p_io_function_cplt_callback[(uint32_t)io_function] = callback;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup SDIO_Exported_Functions_Group5 SDIO card related functions
  * @{
    This subsection provides a set of functions allowing to control the SDIO card operations.
  */
/**
  * @brief  Get the SDIO state.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  * @retval hal_sdio_handle_t Current SDIO state.
  */
hal_sdio_state_t HAL_SDIO_GetState(const hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  return hsdio->global_state;
}

/**
  * @brief  Get Card Common Control register information (CCCR).
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  p_cccr            Pointer to Card common control register.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SDIO_GetCardCommonControlRegister(hal_sdio_handle_t *hsdio, hal_sdio_cccr_t *p_cccr)
{
  uint8_t tmp_buffer[SDIO_CCCR_REG_NUMBER] = {0U};

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_cccr != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_cccr == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  for (uint32_t count = 0U; count <= SDIO_CCCR_REG_NUMBER; count++)
  {
    if (SDIO_ReadDirect(hsdio, SDMMC_SDIO_CCCR0 + count, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                        &tmp_buffer[count]) != HAL_OK)
    {
      hsdio->global_state = HAL_SDIO_STATE_IDLE;
      return HAL_ERROR;
    }
  }

  p_cccr->cccr_revision = tmp_buffer[0] & 0x0FU;
  p_cccr->sdio_revision = (tmp_buffer[0] & 0xF0U) >> 4U;
  p_cccr->sd_spec_revision = tmp_buffer[0x01U] & 0x0FU;
  p_cccr->bus_width_8Bit = ((tmp_buffer[0x07U] & 0x04U) != 0U) ? HAL_SDIO_BUS_WIDTH_8BIT_SUPPORTED :
                           HAL_SDIO_BUS_WIDTH_8BIT_NOT_SUPPORTED;
  p_cccr->card_capability = (tmp_buffer[0x08U] & 0xDFUL);
  p_cccr->common_cis_pointer = tmp_buffer[0x09U] | ((uint32_t)tmp_buffer[(uint32_t)0x09U + 1U] << 8U) |
                               ((uint32_t)tmp_buffer[(uint32_t)0x09U + 2U] << 16U);

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get Card Function Basic register information (FBR).
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  p_fbr             Pointer to Function Basic register.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_SDIO_GetCardFunctionBasicRegister(hal_sdio_handle_t *hsdio, hal_sdio_fbr_t *p_fbr)
{
  uint8_t tmp_buffer[SDIO_FBR_SIZE_REG] = {0U};

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_fbr != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_fbr == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  for (uint8_t func_idx = 2U; func_idx <= HAL_SDIO_MAX_IO_NUMBER; func_idx++)
  {
    for (uint32_t count = 0U; count <= SDIO_CCCR_REG_NUMBER; count++)
    {
      if (SDIO_ReadDirect(hsdio, (((uint32_t)SDMMC_SDIO_F1BR0 * (uint32_t)func_idx) + count),
                          HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0, &tmp_buffer[count]) != HAL_OK)
      {
        hsdio->global_state = HAL_SDIO_STATE_IDLE;
        return HAL_ERROR;
      }
    }
    p_fbr[(uint32_t)func_idx - 1U].io_std_function_code = tmp_buffer[0U] & 0x0FU;
    p_fbr[(uint32_t)func_idx - 1U].io_ext_function_code = tmp_buffer[1U];
    p_fbr[(uint32_t)func_idx - 1U].io_pointer_to_cis = tmp_buffer[9U] | ((uint32_t)tmp_buffer[10U] << 8U) \
                                                       | ((uint32_t)tmp_buffer[11U] << 16U);
    p_fbr[(uint32_t)func_idx - 1U].io_pointer_to_csa = tmp_buffer[12U] | ((uint32_t)tmp_buffer[13U] << 8U) \
                                                       | ((uint32_t)tmp_buffer[14U] << 16U);
    if ((tmp_buffer[2U] & 0x01U) != 0U)
    {
      p_fbr[(uint32_t)func_idx - 1U].flags |= (uint8_t)SDIO_FBR_SUPPORT_POWER_SELECTION;
    }
    if ((tmp_buffer[0U] & 0x40U) != 0U)
    {
      p_fbr[(uint32_t)func_idx - 1U].flags |= (uint8_t)SDIO_FBR_SUPPORT_CSA;
    }
  } /* End for (uint8_t func_idx = 2U; func_idx <= HAL_SDIO_MAX_IO_NUMBER; func_idx++)  */

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return HAL_OK;
}

#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
/**
  * @brief  Get last errors codes.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  * @retval uint32_t Last errors codes which can be a combination of @ref SDIO_Error_Status.
  */
uint32_t HAL_SDIO_GetLastErrorCodes(const hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  return hsdio->last_error_codes;
}
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

#if defined (USE_HAL_SDIO_USER_DATA) && (USE_HAL_SDIO_USER_DATA == 1)
/**
  * @brief  Store the user data into the SDIO handle.
  * @param  hsdio       Pointer to a hal_sdio_handle_t structure.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_SDIO_SetUserData(hal_sdio_handle_t *hsdio, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  hsdio->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the SDIO handle.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  * @retval Pointer to the user data.
  */
const void *HAL_SDIO_GetUserData(const hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  return (hsdio->p_user_data);
}
#endif /* USE_HAL_SDIO_USER_DATA */
/**
  * @}
  */

/** @addtogroup SDIO_Exported_Functions_Group6 Peripheral IO interrupt
  * @{
    This subsection provides a set of functions allowing to enable/disable IO functions interrupt features
    on the SDIO card.
  */
/**
  * @brief  Enable SDIO IO interrupt.
  * @param  hsdio       Pointer to a hal_sdio_handle_t structure.
  * @param  io_function Specifies the SDIO IO function.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_SDIO_EnableIOFunctionInterrupt(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function)
{
  SDMMC_TypeDef *p_instance;
  uint8_t io_interrupt_enabled = 0U;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_FUNCTION(io_function));

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  if (SDIO_ReadDirect(hsdio, SDMMC_SDIO_CCCR4, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                      &io_interrupt_enabled) != HAL_OK)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* if already enable, do not need enable again */
    if ((((io_interrupt_enabled >> (uint8_t)io_function) & 0x01U) != 0x01U) && ((io_interrupt_enabled & 0x01U) == 0U))
    {
      io_interrupt_enabled |= (1U << (uint8_t)io_function) | 0x01U;
      hsdio->io_interrupt_nbr++;
      hsdio->io_function_enabled_mask |= (1U << (uint8_t)io_function);
      if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR4, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                           io_interrupt_enabled) != HAL_OK)
      {
        status = HAL_ERROR;
      }
      else
      {
        SDMMC_ENABLE_IT(p_instance, SDMMC_IT_SDIOIT);

        /* Enable host SDIO interrupt operations */
        SDMMC_OPERATION_ENABLE(p_instance);
      }
    }
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}

/**
  * @brief  Disable SDIO IO interrupt.
  * @param  hsdio       Pointer to a hal_sdio_handle_t structure.
  * @param  io_function Specifies the SDIO IO function.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_SDIO_DisableIOFunctionInterrupt(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function)
{
  uint8_t io_interrupt_enabled = 0U;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_FUNCTION(io_function));

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  if (SDIO_ReadDirect(hsdio, SDMMC_SDIO_CCCR4, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                      &io_interrupt_enabled) != HAL_OK)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* if already disable, do not need disable again */
    if (((io_interrupt_enabled >> (uint32_t)io_function) & 0x01U) != 0x00U)
    {
      /* disable the interrupt, don't disable the interrupt master here */
      io_interrupt_enabled &= ~(1U << (uint8_t)io_function);
      if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR4, HAL_SDIO_READ_AFTER_WRITE, HAL_SDIO_FUNCTION_0,
                           io_interrupt_enabled) != HAL_OK)
      {
        status = HAL_ERROR;
      }
      else
      {
        if (hsdio->io_interrupt_nbr > 1U)
        {
          hsdio->io_interrupt_nbr--;
        }
        else
        {
          hsdio->io_interrupt_nbr = 0U;
          SDMMC_DISABLE_IT(SDIO_GET_INSTANCE(hsdio), SDMMC_IT_SDIOIT);
        }
      }
    }
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}

/**
  * @brief  Enable SDIO Function.
  * @param  hsdio       Pointer to a hal_sdio_handle_t structure.
  * @param  io_function Specifies the IO function to enable.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_SDIO_EnableIOFunction(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function)
{
  uint8_t io_enabled = 0U;
  uint8_t io_ready = 0U;
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_FUNCTION(io_function));
  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  if (SDIO_ReadDirect(hsdio, SDMMC_SDIO_CCCR0_BYTE2, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0, &io_enabled) == HAL_OK)
  {
    if (((io_enabled >> (uint32_t)io_function) & 0x01U) == 0U)
    {
      io_enabled |= (1U << (uint8_t)io_function);

      if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR0_BYTE2, HAL_SDIO_READ_AFTER_WRITE, HAL_SDIO_FUNCTION_0,
                           io_enabled) == HAL_OK)
      {
        if (SDIO_ReadDirect(hsdio, SDMMC_SDIO_CCCR0_BYTE3, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                            &io_ready) == HAL_OK)
        {
          /* check if IO ready */
          if ((io_ready & (1UL << (uint32_t)io_function)) != 0U)
          {
            status = HAL_OK;
          }
        }
      }
    }
    else /* if already enable, do not need to enable again */
    {
      status = HAL_OK;
    }
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;
  return status;
}

/**
  * @brief  Disable SDIO IO function.
  * @param  hsdio       Pointer to a hal_sdio_handle_t structure.
  * @param  io_function Specifies the IO function to disable.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_SDIO_DisableIOFunction(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function)
{
  uint8_t io_enabled = 0U;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_FUNCTION(io_function));

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  if (SDIO_ReadDirect(hsdio, SDMMC_SDIO_CCCR0_BYTE2, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                      &io_enabled) != HAL_OK)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* if already enable, do not need disable again */
    if (((io_enabled >> (uint32_t)io_function) & 0x01U) != 0x00U)
    {
      io_enabled &= ~(1U << (uint8_t)io_function);
      if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR0_BYTE2, HAL_SDIO_READ_AFTER_WRITE, HAL_SDIO_FUNCTION_0,
                           io_enabled) != HAL_OK)
      {
        status = HAL_ERROR;
      }
    }
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}

/**
  * @brief  Select SDIO IO function.
  * @param  hsdio       Pointer to a hal_sdio_handle_t structure.
  * @param  io_function Specifies the IO function to select.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_SDIO_SelectIOFunction(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_FUNCTION(io_function));

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR12_BYTE1, HAL_SDIO_READ_AFTER_WRITE, HAL_SDIO_FUNCTION_0,
                       (uint8_t)io_function) != HAL_OK)
  {
    status = HAL_ERROR;
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}

/**
  * @brief  Abort an IO transfer function.
  * @param  hsdio       Pointer to a hal_sdio_handle_t structure.
  * @param  io_function Specify the IO function to abort
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_SDIO_AbortIOFunction(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(IS_SDIO_FUNCTION(io_function));

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR4_BYTE2, HAL_SDIO_READ_AFTER_WRITE, HAL_SDIO_FUNCTION_0,
                       (uint8_t)io_function) != HAL_OK)
  {
    status = HAL_ERROR;
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}

/**
  * @brief  Enable asynchronous IO interrupt.
  * @param  hsdio     Pointer to a hal_sdio_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
hal_status_t HAL_SDIO_EnableIOAsynInterrupt(hal_sdio_handle_t *hsdio)
{
  uint8_t enable_asyn_it = 0U;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  if (SDIO_ReadDirect(hsdio, SDMMC_SDIO_CCCR20_BYTE2, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                      &enable_asyn_it) != HAL_OK)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* if already enable, do not need enable again */
    if ((enable_asyn_it & 0x02U) != 0x02U)
    {
      enable_asyn_it |= 0x02U;
      if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR20_BYTE2, HAL_SDIO_READ_AFTER_WRITE, HAL_SDIO_FUNCTION_0,
                           enable_asyn_it) != HAL_OK)
      {
        status =  HAL_ERROR;
      }
    }
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}

/**
  * @brief  Disable asynchronous IO interrupt.
  * @param  hsdio     Pointer to a hal_sdio_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
hal_status_t HAL_SDIO_DisableIOAsynInterrupt(hal_sdio_handle_t *hsdio)
{
  uint8_t enable_asyn_it = 0U;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  if (SDIO_ReadDirect(hsdio, SDMMC_SDIO_CCCR20_BYTE2, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                      &enable_asyn_it) != HAL_OK)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* if already disable, do not need disable again */
    if ((enable_asyn_it & 0x02U) != 0x00U)
    {
      enable_asyn_it &= (uint8_t) ~(0x02U);
      if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR20_BYTE2, HAL_SDIO_READ_AFTER_WRITE, HAL_SDIO_FUNCTION_0,
                           enable_asyn_it) != HAL_OK)
      {
        status = HAL_ERROR;
      }
    }
  }

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}
/**
  * @}
  */

/** @addtogroup SDIO_Exported_Functions_Group7 SDIO Delay Block functions
  * @{
This subsection provides a set of functions allowing to configure the delay block:
- Call HAL_SDIO_SetConfigDlybDelay() to set the SDIO delay block configuration.
- Call HAL_SDIO_GetDlybOutputClockPhase() to get the SDIO delay block output clock phase.
- Call HAL_SDIO_CalculateDlybMaxClockPhase() to calculate the SDIO delay block maximum output clock phase.
- Call HAL_SDIO_EnableDlyb() to enable the SDIO delay block peripheral.
- Call HAL_SDIO_DisableDlyb() to disable SDIO the delay clock peripheral.
- Call HAL_SDIO_IsEnabledDlyb() to check whether the delay block peripheral is enabled or not.
  */
/**
  * @brief Set the SDIO delay block configuration.
  * @param hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param clock_phase_value The selected output clock phase value will be stored.
  * @retval HAL_ERROR        An error has been occurred.
  * @retval HAL_OK           The delay is correctly set.
  */
hal_status_t HAL_SDIO_SetConfigDlybDelay(const hal_sdio_handle_t *hsdio, uint32_t clock_phase_value)
{
  DLYB_TypeDef *instance;
  dlyb_state_t state;

  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, HAL_SDIO_STATE_IDLE);

  instance = SDMMC_GET_DLYB_INSTANCE(SDIO_GET_INSTANCE(hsdio));

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
  * @brief Get the SDIO delay block output clock phase.
  * @param hsdio Pointer to a hal_sdio_handle_t structure.
  * @retval uint32_t output clock phase value.
  */
uint32_t HAL_SDIO_GetDlybOutputClockPhase(const hal_sdio_handle_t *hsdio)
{

  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, (uint32_t)HAL_SDIO_STATE_IDLE | (uint32_t)HAL_SDIO_STATE_ACTIVE);

  return (DLYB_GetOutputClockPhase(SDMMC_GET_DLYB_INSTANCE(SDIO_GET_INSTANCE(hsdio))));
}

/**
  * @brief Calculate the SDIO delay block maximum output clock phase.
  * @param hsdio Pointer to a hal_sdio_handle_t structure.
  * @param p_max_clock_phase  Pointer to the variable where the maximum clock phase value to be stored.
  * @retval HAL_INVALID_PARAM Invalid p_max_clock_phase parameter.
  * @retval HAL_ERROR         The max clock phase is not correctly calculated.
  * @retval HAL_OK            The max clock phase is correctly calculated.
  */
hal_status_t HAL_SDIO_CalculateDlybMaxClockPhase(hal_sdio_handle_t *hsdio, uint32_t *p_max_clock_phase)
{
  hal_status_t status = HAL_ERROR;
  DLYB_TypeDef *instance;
  uint32_t sel;
  uint32_t unit;
  dlyb_state_t state;

  ASSERT_DBG_PARAM(hsdio != NULL);
  ASSERT_DBG_PARAM(p_max_clock_phase != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, HAL_SDIO_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_max_clock_phase == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hsdio, global_state, HAL_SDIO_STATE_IDLE, HAL_SDIO_STATE_ACTIVE);

  instance = SDMMC_GET_DLYB_INSTANCE(SDIO_GET_INSTANCE(hsdio));
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

  hsdio->global_state = HAL_SDIO_STATE_IDLE;

  return status;
}

/**
  * @brief Enable the SDIO delay block.
  * @param hsdio   Pointer to a hal_mm_handle_t structure.
  * @retval HAL_OK The delay block is enabled.
  */
hal_status_t HAL_SDIO_EnableDlyb(hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, HAL_SDIO_STATE_IDLE);

  DLYB_Enable(SDMMC_GET_DLYB_INSTANCE(SDIO_GET_INSTANCE(hsdio)));

  return HAL_OK;
}

/**
  * @brief Disable the SDIO delay block.
  * @param hsdio   Pointer to a hal_sdio_handle_t structure.
  * @retval HAL_OK The delay block is disabled.
  */
hal_status_t HAL_SDIO_DisableDlyb(hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  ASSERT_DBG_STATE(hsdio->global_state, HAL_SDIO_STATE_IDLE);

  DLYB_Disable(SDMMC_GET_DLYB_INSTANCE(SDIO_GET_INSTANCE(hsdio)));

  return HAL_OK;
}

/**
  * @brief Check if the delay block peripheral is enabled or not.
  * @param hsdio                   Pointer to a hal_sdio_handle_t structure.
  * @retval HAL_SDIO_DLYB_DISABLED Delay block is disabled.
  * @retval HAL_SDIO_DLYB_ENABLED  Delay block is enabled.
  */
hal_sdio_dlyb_state_t HAL_SDIO_IsEnabledDlyb(const hal_sdio_handle_t *hsdio)
{
  ASSERT_DBG_PARAM(hsdio != NULL);

  return (hal_sdio_dlyb_state_t)DLYB_IsEnabled(SDMMC_GET_DLYB_INSTANCE(SDIO_GET_INSTANCE(hsdio)));
}
/**
  * @}
  */

/**
  * @}
  */

/* Private functions--------------------------------------------------------------------------------------------------*/
/** @addtogroup SDIO_Private_Functions
  * @{
  */
/**
  * @brief  Configure the SDIO according to the default parameters.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  */
static void SDIO_SetDefaultConfig(const hal_sdio_handle_t *hsdio)
{
  SDMMC_TypeDef *p_instance;
  uint32_t sdmmc_clk;
  sdmmc_config_t sdmmc_cfg = {0U};

  p_instance  = SDIO_GET_INSTANCE(hsdio);
  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq(p_instance);

  sdmmc_cfg.clk.clock_edge        = SDMMC_CLOCK_EDGE_RISING;
  sdmmc_cfg.clk.clock_power_save  = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  sdmmc_cfg.bus_wide              = SDMMC_BUS_WIDE_1BIT;
  sdmmc_cfg.hardware_flow_control = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  sdmmc_cfg.clk.clock_div         = (sdmmc_clk + (2U * SDIO_INIT_FREQ) - 1U) / (2U * SDIO_INIT_FREQ);

  /* Initialize SDMMC peripheral interface with default configuration */
  (void)SDMMC_SetConfig(p_instance, &sdmmc_cfg);
}

/**
  * @brief  Configure the SDIO according to the user parameters.
  * @param  hsdio     Pointer to a hal_sdio_handle_t structure.
  * @param  p_config  Pointer to a hal_sdio_config_t structure that contains the SDIO configuration.
  * @retval HAL_ERROR SDIO instance is already configured and cannot be modified.
  * @retval HAL_OK    SDIO instance has been correctly configured.
  */
static hal_status_t SDIO_SetConfig(hal_sdio_handle_t *hsdio, const hal_sdio_config_t *p_config)
{
  SDMMC_TypeDef *p_instance;
  hal_status_t status = HAL_OK;
  sdmmc_config_t cfg = {0};
  uint32_t sdmmc_clk;
  uint8_t tmp_data;

  p_instance  = SDIO_GET_INSTANCE(hsdio);
  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq(p_instance);

  /* Set user SDMMC peripheral configuration for SDIO card initialization */
  cfg.clk.clock_edge        = (uint32_t)p_config->clk_cfg.clk_edge;
  cfg.clk.clock_power_save  = (uint32_t)p_config->clk_cfg.clk_power_save;
  cfg.bus_wide              = (uint32_t)p_config->bus_wide;
  cfg.hardware_flow_control = (uint32_t)p_config->hw_flow_ctrl;
  cfg.clk.clock_div         = (sdmmc_clk / (2U * (uint32_t)p_config->clk_cfg.clk_hz));
  SDMMC_SetConfig(p_instance, &cfg);

  tmp_data = (p_config->bus_wide == HAL_SDIO_BUS_WIDE_4BIT) ? 2U : 0U;

  if (SDIO_WriteDirect(hsdio, SDMMC_SDIO_CCCR4_BYTE3, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0, tmp_data) != HAL_OK)
  {
    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Start the identification mode.
  * @param  hsdio     Pointer to a hal_sdio_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SDIO_Card_Identify(hal_sdio_handle_t *hsdio)
{
  hal_status_t status = HAL_OK;

  if (SDIO_Card_IdentifyVoltageRange(hsdio) != HAL_OK)
  {
    status = HAL_ERROR;
  }
  else
  {
    if (SDIO_Card_IdentifyRelativeAddress(hsdio) != HAL_OK)
    {
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Validates the operation voltage range, identifies cards.
  * @param  hsdio     Pointer to a hal_sdio_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SDIO_Card_IdentifyVoltageRange(const hal_sdio_handle_t *hsdio)
{
  SDMMC_TypeDef *p_instance;
  uint32_t sdmmc_clk;
  uint32_t init_clock_div;
  uint32_t init_clock_hz;
  uint32_t error_state;
  uint32_t resp4;
  uint32_t nbr_of_func;

  p_instance  = SDIO_GET_INSTANCE(hsdio);
  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq(p_instance);

  (void)SDMMC_SET_PWR_STATE(p_instance, SDMMC_PWR_ON);

  if (sdmmc_clk == 0U)
  {
    return HAL_ERROR;
  }

  /* Wait for 1ms + 74 more cycles: required power up waiting time before starting the SDIO initialization sequence */
  init_clock_div = STM32_READ_BIT(p_instance->CLKCR, SDMMC_CLKCR_CLKDIV);
  init_clock_hz = sdmmc_clk;

  if (init_clock_div != 0U)
  {
    init_clock_hz /= (2U * init_clock_div);
  }

  if (init_clock_hz == 0U)
  {
    return HAL_ERROR;
  }

  SDMMC_DelayMs(p_instance, 1U + (((74U * 1000U) + init_clock_hz - 1U) / init_clock_hz));

  /* Identify card operating voltage */
  error_state = SDMMC_SendGoIdleStateCmd(p_instance);
  if (error_state != HAL_SDIO_ERROR_NONE)
  {
    return HAL_ERROR;
  }

  /* Send CMD5 */
  error_state = SDMMC_SDIO_SendOperationconditionCmd(p_instance, 0U, &resp4);
  if (error_state != HAL_SDIO_ERROR_NONE)
  {
    return HAL_ERROR;
  }
  nbr_of_func = ((resp4 & 0x70000000U) >> 28U);
  /* Check if Nbr of function > 0 and OCR valid */
  if (nbr_of_func > 0U)
  {
    /* Send CMD5 with arg= S18R */
    if (SDMMC_SDIO_SendOperationconditionCmd(p_instance,
                                             (SDIO_OCR_SDIO_S18R_POS),
                                             &resp4) != HAL_SDIO_ERROR_NONE)
    {
      return HAL_ERROR;
    }

    /* Check if IORDY = 1 and S18A = 1 */
    if ((((resp4 & 0x80000000U) >> 31U) != 0U) && (((resp4 & 0x1000000U) >> 24U) != 0U))
    {
      /* Send CMD11 to switch 1.8V mode */
      error_state = SDMMC_SendVoltageSwitchCmd(p_instance);
      if (error_state != HAL_SDIO_ERROR_NONE)
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* S18A is not supported */
    }
  }

  return HAL_OK;
}

/**
  * @brief  Ask SDIO card to publish a new relative address (RCA).
  * @param  hsdio     Pointer to a hal_sdio_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t SDIO_Card_IdentifyRelativeAddress(const hal_sdio_handle_t *hsdio)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_state;
  uint32_t timeout_ms = 0U;
  uint16_t sdio_rca = 1U;

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  /** Cmd3 is sent while response is SDMMC_ERROR_ILLEGAL_CMD, due to the partial init test done before
    * (sending cmd0 after the sequence cmd0/cmd3 is sent is considered illegal).
    */
  do
  {
    error_state = SDMMC_SD_SendRelativeAddrCmd(p_instance, &sdio_rca);
    timeout_ms++;
    HAL_Delay(1);
  } while ((error_state == SDMMC_ERROR_ILLEGAL_CMD) && (timeout_ms != SDIO_TIMEOUT_MS));

  if ((timeout_ms == SDIO_TIMEOUT_MS) || (error_state != HAL_SDIO_ERROR_NONE))
  {
    return HAL_ERROR;
  }

  /* Select the Card (Sending CMD7) */
  error_state = SDMMC_SendSelDeselCmd(p_instance, (uint32_t)(((uint32_t)sdio_rca) << 16U));
  if (error_state != HAL_SDIO_ERROR_NONE)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Read one byte data.
  * @param  hsdio        Pointer to a hal_sdio_handle_t structure.
  * @param  addr         Specify the read address.
  * @param  raw          Specify the read after write mode.
  * @param  function_nbr IO function number.
  * @param  p_data       Pointer to write or read data.
  * @retval HAL_ERROR    An error has occurred.
  * @retval HAL_OK       Operation completed.
  */
static hal_status_t SDIO_ReadDirect(hal_sdio_handle_t *hsdio, uint32_t addr, hal_sdio_raw_t raw,
                                    hal_sdio_function_t function_nbr, uint8_t *p_data)
{
  SDMMC_TypeDef *p_instance;
  hal_status_t status = HAL_OK;
  uint32_t error_state;
  uint32_t cmd;

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  cmd = SDIO_SET_BITS(SDIO_READ_FLAG, 31U);
  cmd |= SDIO_SET_BITS((uint32_t)function_nbr, 28U);
  cmd |= SDIO_SET_BITS((uint32_t)raw, 27U);
  cmd |= SDIO_SET_BITS((addr & 0x1FFFFU), 9U);
  error_state = SDMMC_SDIO_SendReadWriteDirectCmd(p_instance, cmd, p_data);

  if (error_state != HAL_SDIO_ERROR_NONE)
  {
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= error_state;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    status = HAL_ERROR;
  }

  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);

  return status;
}

/**
  * @brief  Write one byte data.
  * @param  hsdio        Pointer to a hal_sdio_handle_t structure.
  * @param  addr         Specify the write address.
  * @param  raw          Specify the Read after write mode.
  * @param  function_nbr IO function number.
  * @param  data         Data to write.
  * @retval HAL_ERROR    An error has occurred.
  * @retval HAL_OK       Operation completed.
  */
static hal_status_t SDIO_WriteDirect(hal_sdio_handle_t *hsdio, uint32_t addr, hal_sdio_raw_t raw,
                                     hal_sdio_function_t function_nbr, uint8_t data)
{
  SDMMC_TypeDef *p_instance;
  hal_status_t status = HAL_OK;
  uint32_t error_state;
  uint32_t cmd;
  uint8_t response;

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  cmd = SDIO_SET_BITS(SDIO_WRITE_FLAG, 31U);
  cmd |= SDIO_SET_BITS((uint32_t)function_nbr, 28U);
  cmd |= SDIO_SET_BITS((uint32_t)raw, 27U);
  cmd |= SDIO_SET_BITS((addr & 0x1FFFFU), 9U);
  cmd |= data;
  error_state = SDMMC_SDIO_SendReadWriteDirectCmd(p_instance, cmd, &response);
  if (error_state != HAL_SDIO_ERROR_NONE)
  {
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= error_state;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    status = HAL_ERROR;
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);

  return status;
}

/**
  * @brief  Write multiple data with a single command.
  * @param  hsdio      Pointer to a hal_sdio_handle_t structure.
  * @param  p_argument Pointer to cmd53 argument structure.
  * @param  size_byte  Block size if CMD53 defined in HAL_SDIO_BLOCK_MODE_BLOCK.
  * @param  p_data     Pointer to write or read data.
  * @param  timeout_ms Specify timeout value in millisecond.
  * @retval HAL_ERROR  An error has occurred.
  * @retval HAL_OK     Operation completed.
  */
static hal_status_t SDIO_WriteExtended(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                       const uint8_t *p_data, uint16_t size_byte, uint32_t timeout_ms)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t error_state;
  uint32_t tick_start = HAL_GetTick();
  uint32_t data_remaining;
  uint32_t *p_tmp_buff = (uint32_t *)(uint32_t)p_data;
  uint32_t cmd;
  uint32_t nbr_of_block;

  p_instance  = SDIO_GET_INSTANCE(hsdio);
  nbr_of_block = SDIO_ComputeNbrOfBlocks(hsdio, size_byte, (uint32_t)hsdio->block_size);

  /* Initialize data control register */
  if ((p_instance->DCTRL & SDMMC_DCTRL_SDIOEN) != 0U)
  {
    p_instance->DCTRL = SDMMC_DCTRL_SDIOEN;
  }
  else
  {
    p_instance->DCTRL = 0U;
  }

  /* Configure the SDIO dpsm (Data Path State Machine) */
  data_ctrl.data_timeout = hsdio->data_timeout_cycle;
  if (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK)
  {
    data_ctrl.data_length = (uint32_t)(nbr_of_block * (uint32_t)hsdio->block_size);
    data_ctrl.data_block_size = SDIO_Convert_Block_Size(hsdio, (uint32_t)hsdio->block_size);
  }
  else
  {
    data_ctrl.data_length = size_byte;
    data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_1B;
  }

  data_ctrl.transfer_dir = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode = (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK) ? SDMMC_TRANSFER_MODE_BLOCK :
                            SDMMC_TRANSFER_MODE_SDIO;
  data_ctrl.dpsm = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  hsdio->context = (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK) ? SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK :
                   SDMMC_CONTEXT_WRITE_SINGLE_BLOCK;
  cmd = SDIO_SET_BITS(SDIO_WRITE_FLAG, 31U);
  cmd |= SDIO_SET_BITS((uint32_t)p_argument->io_function_nbr, 28U);
  cmd |= SDIO_SET_BITS(((uint32_t)p_argument->block_mode), 27U);
  cmd |= SDIO_SET_BITS(((uint32_t)p_argument->operation_code), 26U);
  cmd |= SDIO_SET_BITS((p_argument->reg_addr & 0x1FFFFU), 9U);
  if (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BYTE)
  {
    cmd |= (((uint32_t)size_byte) & 0x1FFU);
  }
  else /* HAL_SDIO_BLOCK_MODE_BLOCK */
  {
    cmd |= nbr_of_block & 0x1FFU;
  }
  error_state = SDMMC_SDIO_SendReadWriteExtendedCmd(p_instance, cmd);
  if (error_state != HAL_SDIO_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= error_state;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    hsdio->context = SDMMC_CONTEXT_NONE;
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }

  data_remaining = data_ctrl.data_length;
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXUNDERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0U)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXFIFOHE) != 0U) && (data_remaining >= 32U))
    {
      SDIO_WriteToFullFIFO(hsdio, p_tmp_buff, &data_remaining);
    }
    else if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXFIFOHE | SDMMC_FLAG_TXFIFOE) != 0U) \
             && (data_remaining < 32U))
    {
      SDIO_WriteToPartialFIFO(hsdio, (uint8_t *)p_tmp_buff, data_remaining);
    }
    else
    {
      /* Nothing to do */
    }

    if ((HAL_GetTick() - tick_start) >= timeout_ms)
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
      hsdio->global_state = HAL_SDIO_STATE_IDLE;
      hsdio->context = SDMMC_CONTEXT_NONE;
      return HAL_ERROR;
    }
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);
  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT) != 0U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= HAL_SDIO_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    hsdio->context = SDMMC_CONTEXT_NONE;
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL) != 0U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= HAL_SDIO_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    hsdio->context = SDMMC_CONTEXT_NONE;
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXUNDERR) != 0U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= HAL_SDIO_ERROR_TX_UNDERRUN;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    hsdio->context = SDMMC_CONTEXT_NONE;
    return HAL_ERROR;
  }
  else
  {
    /* Nothing to do */
  }

  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);

  return HAL_OK;
}

/**
  * @brief  Read data from a specified address using extended mode through cmd53 in DMA mode.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  p_argument        Pointer to cmd53 argument structure.
  * @param  p_data            Pointer to the buffer that will contain the data to transmit.
  * @param  size_byte         Block size to read
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed.
  */
static hal_status_t SDIO_ReadExtended_DMA(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                          uint8_t *p_data, uint32_t size_byte)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t error_state;
  uint32_t cmd;
  uint32_t nbr_of_block;
  uint8_t *p_dma_buffer;

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  /* Initialize data control register */
  if ((p_instance->DCTRL & SDMMC_DCTRL_SDIOEN) != 0U)
  {
    p_instance->DCTRL = SDMMC_DCTRL_SDIOEN;
  }
  else
  {
    p_instance->DCTRL = 0U;
  }

  p_dma_buffer = p_data;
  hsdio->p_xfer_buff = p_data;
  hsdio->xfer_size_byte = size_byte;
  hsdio->next_data_addr = (uint32_t)p_data;

  nbr_of_block = SDIO_ComputeNbrOfBlocks(hsdio, size_byte, (uint32_t)hsdio->block_size);

  if (nbr_of_block != 0U)
  {
    hsdio->remaining_data = (size_byte - ((uint32_t)hsdio->block_size * nbr_of_block));
    hsdio->next_reg_addr = (p_argument->reg_addr) |
                           ((((nbr_of_block * (uint32_t)hsdio->block_size) >> 1UL) & 0x3FFFU) << 1UL);

    hsdio->next_reg_addr |= ((hsdio->remaining_data <= (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE) ? 1U : 0U);

    hsdio->next_data_addr += (nbr_of_block * (uint32_t)hsdio->block_size);
  }
  else
  {
    if (size_byte < (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE)
    {
      hsdio->next_data_addr += size_byte;
    }
    else
    {
      hsdio->next_data_addr += (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE;
    }

    if (hsdio->remaining_data != 0U)
    {
      if (size_byte >= (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE)
      {
        hsdio->remaining_data = (size_byte - (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE);
        hsdio->next_reg_addr += ((uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE + 1U);
      }
      else
      {
        hsdio->remaining_data = (size_byte - hsdio->remaining_data);
        hsdio->next_reg_addr += (size_byte + 1U);
      }
    }
  }

  /* DMA configuration (use single buffer) */
  p_instance->IDMACTRLR = SDMMC_ENABLE_IDMA_SINGLE_BUFF;
  p_instance->IDMABASER = (uint32_t)p_dma_buffer;

  data_ctrl.data_timeout = hsdio->data_timeout_cycle;
  if (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK)
  {
    data_ctrl.data_length = (uint32_t)(nbr_of_block * (uint32_t)hsdio->block_size);
    data_ctrl.data_block_size = SDIO_Convert_Block_Size(hsdio, (uint32_t)hsdio->block_size);
  }
  else
  {
    data_ctrl.data_length = (size_byte > 0U) ? size_byte : (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE;
    data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_1B;
  }

  data_ctrl.transfer_dir = SDMMC_TRANSFER_DIR_TO_SDMMC ;
  data_ctrl.transfer_mode = (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK) ? SDMMC_TRANSFER_MODE_BLOCK :
                            SDMMC_TRANSFER_MODE_SDIO;
  data_ctrl.dpsm = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);
  hsdio->context = ((p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK) ? SDMMC_CONTEXT_READ_MULTIPLE_BLOCK :
                    SDMMC_CONTEXT_READ_SINGLE_BLOCK) | SDMMC_CONTEXT_DMA;

  cmd = SDIO_SET_BITS(SDIO_READ_FLAG, 31U);
  cmd |= SDIO_SET_BITS((uint32_t)p_argument->io_function_nbr, 28U);
  cmd |= SDIO_SET_BITS(((uint32_t)p_argument->block_mode), 27U);
  cmd |= SDIO_SET_BITS(((uint32_t)p_argument->operation_code), 26U);
  cmd |= SDIO_SET_BITS((p_argument->reg_addr & 0x1FFFFU), 9U);
  if (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BYTE)
  {
    cmd |= (((uint32_t)size_byte) & 0x1FFU);
  }
  else /* HAL_SDIO_BLOCK_MODE_BLOCK */
  {
    cmd |= nbr_of_block & 0x1FFU;
  }

  error_state = SDMMC_SDIO_SendReadWriteExtendedCmd(p_instance, cmd);
  if (error_state != HAL_SDIO_ERROR_NONE)
  {
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= error_state;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
    hsdio->context = SDMMC_CONTEXT_NONE;
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_ENABLE_IT(p_instance, (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_RXOVERR | SDMMC_IT_DATAEND));

  return HAL_OK;
}

/**
  * @brief  Write data from a specified address using extended mode through cmd53 in DMA mode.
  * @param  hsdio             Pointer to a hal_sdio_handle_t structure.
  * @param  p_argument        Pointer to cmd53 argument structure.
  * @param  p_data            Pointer to the buffer that will contain the data to transmit
  * @param  size_byte         Block size to write
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed.
  */
static hal_status_t SDIO_WriteExtended_DMA(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                           uint8_t *p_data, uint32_t size_byte)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t cmd;
  uint32_t error_state;
  uint32_t nbr_of_block;
  const uint8_t *p_dma_buffer;

  p_instance  = SDIO_GET_INSTANCE(hsdio);

  /* Initialize data control register */
  if ((p_instance->DCTRL & SDMMC_DCTRL_SDIOEN) != 0U)
  {
    p_instance->DCTRL = SDMMC_DCTRL_SDIOEN;
  }
  else
  {
    p_instance->DCTRL = 0U;
  }

  p_dma_buffer = p_data;
  hsdio->p_xfer_buff = (uint8_t *)p_data;
  hsdio->xfer_size_byte = size_byte;
  hsdio->next_data_addr = (uint32_t)p_data;

  nbr_of_block = SDIO_ComputeNbrOfBlocks(hsdio, size_byte, (uint32_t)hsdio->block_size);

  if (nbr_of_block != 0U)
  {
    hsdio->remaining_data = (size_byte - ((uint32_t)hsdio->block_size * nbr_of_block));
    if ((uint32_t)hsdio->block_size <= 128U)
    {
      hsdio->next_reg_addr = (p_argument->reg_addr) |
                             ((((nbr_of_block * (uint32_t)hsdio->block_size) >> 1UL) & 0x3FFFU) << 1UL);

      hsdio->next_reg_addr |= ((hsdio->remaining_data <= (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE) ? 1U : 0U);
    }
    else
    {
      hsdio->next_reg_addr = (nbr_of_block * (uint32_t)hsdio->block_size) >> 1UL;
    }
    hsdio->next_data_addr += (nbr_of_block * (uint32_t)hsdio->block_size);
  }
  else
  {
    if (size_byte >= (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE)
    {
      hsdio->remaining_data = (size_byte - (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE);
      hsdio->next_data_addr += (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE;
    }
    else
    {
      hsdio->remaining_data = (size_byte - hsdio->remaining_data);
      hsdio->next_data_addr += size_byte;
    }

    if (hsdio->remaining_data != 0U)
    {
      if (size_byte >= (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE)
      {
        hsdio->next_reg_addr += (512UL >> 1UL);
        hsdio->remaining_data = (size_byte - (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE);
      }
      else
      {
        hsdio->next_reg_addr += (size_byte >> 1UL) | 1U;
        hsdio->remaining_data = (size_byte - hsdio->remaining_data);
      }
    }
  }

  /* DMA configuration (use single buffer) */
  p_instance->IDMACTRLR = SDMMC_ENABLE_IDMA_SINGLE_BUFF;
  p_instance->IDMABASER = (uint32_t)p_dma_buffer;

  data_ctrl.data_timeout = hsdio->data_timeout_cycle;
  if (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK)
  {
    data_ctrl.data_length = (uint32_t)(nbr_of_block * (uint32_t)hsdio->block_size);
    data_ctrl.data_block_size = SDIO_Convert_Block_Size(hsdio, (uint32_t)hsdio->block_size);
  }
  else
  {
    data_ctrl.data_length = (size_byte > (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE) ?
                            (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE : size_byte;
    data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_1B;
  }

  data_ctrl.transfer_dir = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode = (p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK) ? SDMMC_TRANSFER_MODE_BLOCK
                            : SDMMC_TRANSFER_MODE_SDIO;
  data_ctrl.dpsm = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);

  SDMMC_CMDTRANS_ENABLE(p_instance);

  hsdio->context = ((p_argument->block_mode == HAL_SDIO_BLOCK_MODE_BLOCK) ? SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK :
                    SDMMC_CONTEXT_WRITE_SINGLE_BLOCK) | SDMMC_CONTEXT_DMA;
  cmd = SDIO_SET_BITS(SDIO_WRITE_FLAG, 31U);
  cmd |= SDIO_SET_BITS((uint32_t)p_argument->io_function_nbr, 28U);
  cmd |= SDIO_SET_BITS(((uint32_t)p_argument->block_mode), 27U);
  cmd |= SDIO_SET_BITS(((uint32_t)p_argument->operation_code), 26U);
  cmd |= SDIO_SET_BITS((p_argument->reg_addr & 0x1FFFFU), 9U);

  if (nbr_of_block == 0U)
  {
    if (size_byte <= (uint32_t)HAL_SDIO_BLOCK_SIZE_512BYTE)
    {
      cmd |= size_byte & 0x1FFU;
    }
  }
  else
  {
    cmd |= nbr_of_block & 0x1FFU;
  }

  error_state = SDMMC_SDIO_SendReadWriteExtendedCmd(p_instance, cmd);
  if (error_state != HAL_SDIO_ERROR_NONE)
  {
#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
    hsdio->last_error_codes |= error_state;
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
    hsdio->context = SDMMC_CONTEXT_NONE;
    hsdio->global_state = HAL_SDIO_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_ENABLE_IT(p_instance, (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR | SDMMC_IT_DATAEND));

  return HAL_OK;
}

/**
  * @brief  Converts a block size in bytes to the corresponding SDMMC value for configuring the SDMMC.
  * @param  hsdio      Pointer to a hal_sdio_handle_t structure.
  * @param  block_size Block size in bytes.
  * @note   The function calculates the most significant bit position of the block size.
  *         If the block size is not a power of two, it returns the value for 4 bytes.
  *         Otherwise, it returns the position of the most significant bit shifted to the correct position.
  * @retval Block size as DBLOCKSIZE[3:0] bits format.
  */
static uint8_t SDIO_Convert_Block_Size(const hal_sdio_handle_t *hsdio, uint32_t block_size)
{
  STM32_UNUSED(hsdio);

  uint8_t most_significant_bit = (uint8_t)__CLZ(__RBIT(block_size));
  /* (1 << most_significant_bit) - 1 is the mask used for block size */
  if ((block_size & ((1UL << most_significant_bit) - 1U)) != 0U)
  {
    return (uint8_t)SDMMC_DATABLOCK_SIZE_4B;
  }

  return most_significant_bit << SDMMC_DCTRL_DBLOCKSIZE_Pos;
}

/**
  * @brief  SDIO card io pending interrupt handle function.
  * @param  hsdio Pointer to a hal_sdio_handle_t structure.
  * @note   This function is used to handle the pending io interrupt.
  *         To register a IO IRQ handler, Use HAL_SDIO_EnableIOInterrupt() and HAL_SDIO_RegisterIOFunctionCallback().
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
 */
static hal_status_t SDIO_IOFunction_IRQHandler(hal_sdio_handle_t *hsdio)
{
  uint32_t position;
  uint32_t iocurrent;
  uint8_t pending_interrupt;

  if (hsdio->io_interrupt_nbr == 1U)
  {
    (hsdio->p_io_function_cplt_callback[STM32_POSITION_VAL(hsdio->io_function_enabled_mask)])
    (hsdio, STM32_POSITION_VAL(hsdio->io_function_enabled_mask));
  }
  else if (hsdio->io_interrupt_nbr > 1U)
  {
    /* Get pending IT firstly */
    if (SDIO_ReadDirect(hsdio, SDMMC_SDIO_CCCR4_BYTE1, HAL_SDIO_WRITE_ONLY, HAL_SDIO_FUNCTION_0,
                        &pending_interrupt) != HAL_OK)
    {
      return HAL_ERROR;
    }

    pending_interrupt &= 0xFEU;                       /* clearing bi [0] that is not part of the IO functions */
    position = STM32_POSITION_VAL(pending_interrupt); /* Get the first pin position from the pins mask        */
    iocurrent = (1UL << position);                    /* Get the first pin from the pins mask                 */

    /* Treat the IO functions pending interrupts (max 7) */
    while (pending_interrupt != 0U)
    {
      (hsdio->p_io_function_cplt_callback[position])(hsdio, position);
      pending_interrupt &= (uint8_t)(~iocurrent);       /* Clear the current pin from the pins mask      */
      position = STM32_POSITION_VAL(pending_interrupt); /* Get the next pin position from the pins mask  */
      iocurrent = (1UL << position);                    /* Get the pin from the pins mask                */
    }
  }
  else
  {
    /* Nothing to do */
  }

  return HAL_OK;
}

/**
  * @brief  Handles data for reading from the FIFO when data_remaining is greater than or equal to 32 bytes.
  * @param  hsdio          Pointer to a hal_sdio_handle_t structure.
  * @param  p_buff         Pointer to a buffer where the read data will be stored.
  * @param  data_remaining the remaining data size to be read.
 */
static void SDIO_ReadFullFIFO(hal_sdio_handle_t *hsdio, uint8_t *p_buff, uint32_t *data_remaining)
{
  uint32_t data;
  uint8_t *p_tmp_buff = p_buff;

  for (uint32_t reg_count = 0U; reg_count < 8U; reg_count++)
  {
    data = SDMMC_ReadFIFO(SDIO_GET_INSTANCE(hsdio));
    *p_tmp_buff = (uint8_t)(data & 0xFFU);
    p_tmp_buff++;
    *p_tmp_buff = (uint8_t)((data >> 8U) & 0xFFU);
    p_tmp_buff++;
    *p_tmp_buff = (uint8_t)((data >> 16U) & 0xFFU);
    p_tmp_buff++;
    *p_tmp_buff = (uint8_t)((data >> 24U) & 0xFFU);
    p_tmp_buff++;
  }
  *data_remaining -= 32U;
}

/**
  * @brief  Handles data for reading from the FIFO when data_remaining is less than 32 bytes.
  * @param  hsdio          Pointer to a hal_sdio_handle_t structure.
  * @param  p_buff         Pointer to a buffer where the read data will be stored.
  * @param  data_remaining the remaining data size to be read.
 */
static void SDIO_ReadPartialFIFO(const hal_sdio_handle_t *hsdio, uint8_t *p_buff, uint32_t data_remaining)
{
  SDMMC_TypeDef *p_instance;
  uint32_t tmp_data_remaining;
  uint32_t data;
  uint8_t *p_tmp_buff = p_buff;

  p_instance  = SDIO_GET_INSTANCE(hsdio);
  tmp_data_remaining = data_remaining;

  while ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXFIFOE) == 0U) && (tmp_data_remaining > 0U))
  {
    data = SDMMC_ReadFIFO(p_instance);
    for (uint32_t byte_count = 0U; byte_count < 4U; byte_count++)
    {
      if (tmp_data_remaining > 0U)
      {
        *p_tmp_buff = (uint8_t)((data >> (byte_count * 8U)) & 0xFFU);
        p_tmp_buff++;
        tmp_data_remaining--;
      }
    }
  }
}

/**
  * @brief  Handles data for writing to the FIFO when data_remaining is greater than or equal to 32 bytes.
  * @param  hsdio          Pointer to a hal_sdio_handle_t structure.
  * @param  p_buff         Pointer to a buffer where the read data will be stored.
  * @param  data_remaining the remaining data size to be read.
 */
static void SDIO_WriteToFullFIFO(hal_sdio_handle_t *hsdio, uint32_t *p_buff, uint32_t *data_remaining)
{
  for (uint32_t reg_count = 8U; reg_count > 0U; reg_count--)
  {
    SDMMC_WriteFIFO(SDIO_GET_INSTANCE(hsdio), *p_buff);
    (*p_buff)++;
  }
  *data_remaining -= 32U;
}

/**
  * @brief  Handles data for writing to the FIFO when data_remaining is less than 32 bytes.
  * @param  hsdio          Pointer to a hal_sdio_handle_t structure.
  * @param  p_buff         Pointer to a buffer where the read data will be stored.
  * @param  data_remaining the remaining data size to be read.
 */
static void SDIO_WriteToPartialFIFO(const hal_sdio_handle_t *hsdio, const uint8_t *p_buff, uint32_t data_remaining)
{
  uint32_t tmp_data_remaining;
  uint32_t data;
  const uint8_t *p_u8buff = p_buff;

  tmp_data_remaining = data_remaining;

  while (tmp_data_remaining > 0U)
  {
    data = 0U;
    for (uint32_t byte_count = 0U; (byte_count < 4U) && (tmp_data_remaining > 0U); byte_count++)
    {
      data |= ((uint32_t)(*p_u8buff) << (byte_count << 3U));
      p_u8buff++;
      tmp_data_remaining--;
    }
    SDMMC_WriteFIFO(SDIO_GET_INSTANCE(hsdio), data);
  }
}

/**
  * @brief  Compute the number of blocks to be read/write for a given data size.
  * @param  hsdio       Pointer to a hal_sdio_handle_t structure.
  * @param  size_byte   Size of the data in bytes.
  * @param  block_size  Block size in bytes (must be a power of 2).
  * @retval Number of blocks.
  */
static uint32_t SDIO_ComputeNbrOfBlocks(const hal_sdio_handle_t *hsdio, uint32_t size_byte, uint32_t block_size)
{
  STM32_UNUSED(hsdio);

  /* Ensure block_size is a power of 2 */
  if ((block_size & (block_size - 1U)) != 0U)
  {
    /* Invalid block size, return 0 */
    return 0U;
  }

  uint32_t nbr_of_block = size_byte / block_size;

  return nbr_of_block;
}
/**
  * @}
  */
#endif /* USE_HAL_SDIO_MODULE */
#endif /* SDMMC1 */

/**
  * @}
  */

/**
  * @}
  */
