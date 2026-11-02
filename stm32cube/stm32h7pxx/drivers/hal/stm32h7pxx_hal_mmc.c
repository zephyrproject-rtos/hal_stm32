/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_mmc.c
  * @brief   MMC card HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Secure Digital (MMC) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + MMC card Control functions
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

/** @addtogroup MMC
  * @{
  */
/** @defgroup MMC_Introduction MMC Introduction
  * @{

  - The MMC Hardware Abstraction Layer provides a high-level interface to the STM32 SDMMC peripheral for
    communicating with MMC cards and embedded MMC (eMMC) devices.

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
    the integration of MMC and eMMC storage into embedded applications.

  */
/**
  * @}
  */

/** @defgroup MMC_How_To_Use MMC How To Use
  * @{

# How to use this driver #####
This HAL MMC driver is a layered driver on top of the SDMMC core driver (allowing to handle SD and MMC memories).
The HAL MMC driver allows to interface with MMC cards and Embedded MMC (e-mmc) devices.

This driver implements a high level communication layer for read and write from/to this memory.

This driver provides 10 different set of APIs that allows to :

1. Initialize and de-initialize the logical MMC object :
  - To initialize the MMC Card, use the HAL_MMC_Init() function to
    - to associate physical instance to logical object.
    - Enable the SDMMC peripheral Clock:
      - Either by calling the appropriate HAL RCC function  HAL_RCC_SDMMCx_EnableClock
      - Either by Setting the USE_HAL_MMC_CLK_ENABLE_MODEL to HAL_CLK_ENABLE_PERIPH_ONLY through stm32tnxx_hal_conf.h
        module, in this case the SDMMC peripheral clock must be automatically enabled by the HAL_MMC_Init().
  - To de-initiliaze the MMC card, use the HAL_MMC_DeInit() function that must turn off the MMC Card and set
    the HAL MMC handle state to RESET

2. Set and Get MMC configuration:
  - Configure the MMC card, use the HAL_MMC_SetConfig() to apply the MMC card configuration process, the clock
    frequency must be less than 400Khz. then, this phase allows the card identification and Get all card information
    (CSD, EXT CSD, CID, Card Status Register) to ensure that the card has been correctly identified and
    then, Apply the user parameters.
    In this stage, the MMC card moved from the IDENTIFICATION STATE to TRANSFER STATE and put the globale state
    at the IDLE state. In this case, we can perform any MMC card Erase, read and write operation.
  - To get the MMC card configuration, use the HAL_MMC_GetConfig() to retrieve the current MMC configuration.
  - When the GPIO Pin detects a removal of the MMC card from the bus, use the HAL_MMC_NotifyCardRemoval() to apply
    the SDMMC default configuration and wait for an insertion of the MMC card.
  - When the GPIO Pin detects an insertion of the MMC card, use the HAL_MMC_NotifyCardInsertion() to
    re-apply the user configuration.
  - According to the MMC card specification (speed, size and class), the timeout values available through define
    can be used also by user to fill the configuration structure at the SetConfig call:
     - HAL_MMC_DATA_MAX_TIMEOUT      (0xFFFFFFFFU) : Max data timeout
     - HAL_MMC_STOP_XFER_MAX_TIMEOUT (500U)        : Max stop transfer timeout 500 ms
     - HAL_MMC_ERASE_MAX_TIMEOUT     (63000U)      : Max erase Timeout 63 seconds
    It can modify the timeout process values:
     - For the data_timeout_cycle    : Use HAL_MMC_SetDataTimeout() to update it with the user definition
     - For the stopxfer_timeout_ms   : Use HAL_MMC_SetStopXferTimeout() to update it with the user definition
     - for the erase_timeout_ms      : Use HAL_MMC_SetEraseTimeout() to update it with the user definition

3. Input and Output operations:
  - Blocking mode: Polling
    - Read from MMC card in polling mode by using function HAL_MMC_ReadBlocks().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr
      After this, ensure that the transfer is done correctly.
      The check is done through HAL_MMC_GetCardState() function of MMC card state.
    - Write to MMC card in polling mode by using function HAL_MMC_WriteBlocks().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr
      After this, ensure that the transfer is done correctly.
      The check is done through HAL_MMC_GetCardState() function of the MMC card state.

  - Non-Blocking mode: IT
    - Read from the MMC card in Interrupt mode by using function HAL_MMC_ReadBlocks_IT().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr
      After this, ensure that the transfer is done correctly by using the Xfer complete callbacks to check
      the end of the process.
    - Write to MMC card in Interrupt mode by using function HAL_MMC_WriteBlocks_IT().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr
      After this, ensure that the transfer is done correctly by using the Xfer complete callbacks to check
      the end of the process.

  - Non-Blocking mode: DMA in normal mode
    - Read from the MMC card in DMA mode by using function HAL_MMC_ReadBlocks_DMA().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr
      After this, ensure that the transfer is done correctly by checking the IT transfer process
      through the MMC xfer interrupt event.
    - Write to MMC card in DMA mode by using function HAL_MMC_WriteBlocks_DMA().
      This function supports only 512-bytes block length (the block size must be chosen as 512 bytes).
      Choose either one block read operation or multiple block read operation by adjusting blocks_nbr
      After this, ensure that the transfer is done correctly by using the Xfer complete callbacks to check
      the end of the process.

  - Non-Blocking mode: DMA in linked-list mode
      Use the Linked list fueature by enabling the USE_HAL_MMC_LINKEDLIST compilation flag through
      stm32tnxx_hal_conf.h module.
      At this stage, Build a linked-list Q using the module Q.
      - Read from the MMC card in linked-list mode by using the function HAL_MMC_ReadBlocks_LinkedList().
        This functions supports only 512-bytes block length (the block size must be chosen as 512 bytes).
        After this, ensure that the transfer is done correctly by using the Xfer complete callbacks to check
        the end of the process.
      - Write to the MMC card in linked-list mode by using the function HAL_MMC_WriteBlocks_LinkedList().
        This functions supports only 512-bytes block length (the block size must be chosen as 512 bytes).
        After this, ensure that the transfer is done correctly by using the Xfer complete callbacks to check
        the end of the process.

  - Abort operation
     - Abort any transfer to/from the MMC card by using the HAL_MMC_Abort() to stop the transfer in polling mode
     - Abort any transfer to/from the MMC card by using the HAL_MMC_Abort_IT() to stop the transfer in IT mode

4. IRQHandler and Callbacks Functions:
  - All MMC card interrupts requests are handled by the HAL_MMC_IRQHandler function.
  - By default, after the HAL_MMC_Init, all callbacks are reset to the corresponding legacy weak (surcharged) functions:
     - HAL_MMC_XferCpltCallback() : A Callback when an Xfer transfer is completed.
     - HAL_MMC_ErrorCallback()    : A Callback when an error has occurred.
     - HAL_MMC_AbortCallback()    : A Callback when an abort is completed.

  - To use the callback registration feature, Set the USE_HAL_MMC_REGISTER_CALLBACKS to 1U the compilation flag
     through stm32tnxx_hal_conf.h module to allow the user to configure dynamically the driver register callbacks.

  - Use Functions to register a user callback, it allows to register following callbacks:
     - HAL_MMC_RegisterXferCpltCallback()  : To register an xfer callback function.
     - HAL_MMC_RegisterErrorCallback() : To register an error callback function.
     - HAL_MMC_RegisterAbortCallback() : To register an abort callback function.
       When The compilation define USE_HAL_MMC_REGISTER_CALLBACKS is set to 0 or not defined, the callback registering
       feature is not available and weak (surcharged) callbacks are used.

5. MMC Card related information functions:
  - To get the global state, use the HAL_MMC_GetState().
  - To get the internal state of the MMC card, use the HAL_MMC_GetCardState().
  - To get MMC card information, use the function HAL_MMC_GetCardInfo().
    It returns useful information about the MMC card such as block number, block size type, logical block number,
    logical block size and the relative card address.
  - To get the MMC Card Identification Data, Set the USE_HAL_MMC_GET_CID to 1U the compilation flag through
    stm32tnxx_hal_conf.h module and use the function HAL_MMC_GetCardCID().
  - To retrieve the MMC/EMMC card specification version, use the HAL_MMC_GetCardSpecVersion().
  - To retrieve the last error code detecting by the MMC card, Set the USE_HAL_MMC_GET_LAST_ERRORS to 1U
    the compilation flag through stm32tnxx_hal_conf.h module to allow the user to get the last error code.
  - To store the user data into the MMC handle, Set the USE_HAL_MMC_USER_DATA to 1U
    the compilation flag through stm32tnxx_hal_conf.h module and use the function HAL_MMC_SetUserData().
  - To get the user data, use the function HAL_MMC_GetUserData().

6. MMC Card Peripheral Erase management
  - To perform specific commands sequence for the different type of erase, use the function HAL_MMC_EraseSequence().
  - To perform sanitize operation on the device, use the function HAL_MMC_Sanitize().
  - To configure the Secure Removal Type in the Extended CSD register, use the function HAL_MMC_SetSecureRemovalType().
  - To get the supported type of the Secure Removal, use the function HAL_MMC_GetSecureRemovalType().

7. MMC Card Peripheral low power management
  - To switch the device from Standby State to Sleep State, use the function HAL_MMC_EnterCardSleepMode().
  - To switch the device from Sleep State to Standby State, use the function HAL_MMC_ExitCardSleepMode().

8. MMC card linked-list queue functions:
This subsection provides a set of functions allowing to manage the MMC linked-list node and queue:
  - To build an SDMMC node, use the HAL_MMC_FillNodeConfig() according to configured parameters within
    hal_mmc_node_config_t structure.
  - To get the current SDMMC node configuration, use the HAL_MMC_GetNodeConfig().
  - To set the MMC linked list node data buffer state, use the HAL_MMC_SetNodeDataBufferState().
  - To get the MMC linked list node data buffer state, use the HAL_MMC_GetNodeDataBufferState().
  - To get the MMC linked list node information, use the HAL_MMC_GetNodeInfo().
  - To set the MMC linked list node address, use the HAL_MMC_SetNodeAddress().
  - To get the MMC linked list node address, use the HAL_MMC_GetNodeAddress().

9. MMC Delay Block functions:
This subsection provides a set of functions allowing to generate an output clock that is dephased from the input clock.
  - Use HAL_MMC_SetConfigDlybDelay() to set the MMC delay block configuration.
  - Use HAL_MMC_GetDlybOutputClockPhase() to get the MMC delay block output clock phase.
  - Use HAL_MMC_EnableDlyb() to enable the MMC delay block.
  - Use HAL_MMC_DisableDlyb() to disable the MMC delay block.
  - Use HAL_MMC_IsEnabledDlyb() to check if the delay block peripheral is enabled or not.

10. MMC Card Interrupt and flags Inline functions:
  - HAL_MMC_EnableIT()     : Enable the MMC device interrupt to generate an interrupt request.
  - HAL_MMC_DisableIT()    : Disable the MMC device interrupt to clear an interrupt request.
  - HAL_MMC_IsActiveFlag() : Check whether the specified MMC flag is set or not.
  - HAL_MMC_ClearFlag()    : Clear the MMC's pending flags.

11. MMC Card Replay Protected Memory Block Management (RPMB):
This subsection provides a set of functions for managing the Replay Protected Memory Block (RPMB).
  - Before RPMB key programming, read/write data from/to the RPMB area, you need to switch to the RPMB partition area
    using the API HAL_MMC_SelectPartitionArea().
  - If the authentication key is not yet programmed, you need to program the RPMB authentication key by calling the API
    HAL_MMC_ProgramRPMBAuthenticationKey().
  - Retrieve the current write counter value using the API HAL_MMC_GetRPMBWriteCounter(). This counter is used to
    prevent replay attacks by ensuring that each write operation has a unique counter value.
  - Generate the MAC for the data to be written. The MAC ensures the integrity and authenticity of the data.
  - Write the authenticated data to the RPMB using the API HAL_MMC_WriteRPMBBlocks().
  - Read the authenticated data back from the RPMB using the API HAL_MMC_ReadRPMBBlocks() and verify its integrity.
  - Get the RPMB error codes using the API HAL_MMC_GetRPMBErrorCodes().
  - Get the RPMB partition size area using API HAL_MMC_GetRPMBSize().
  */
/**
  * @}
  */

/** @defgroup MMC_Configuration_Table MMC Configuration Table
  * @{
## Configuration inside the MMC driver

Config defines                      | Description     | Default value   | Note
------------------------------------| --------------- | ----------------| ---------------------------------------------
USE_ASSERT_DBG_PARAM                | from the IDE    |     NONE        | Allows to use the assert checks parameters.
USE_ASSERT_DBG_STATE                | from the IDE    |     NONE        | Allows to use the assert checks states.
USE_HAL_CHECK_PARAM                 | from hal_conf.h |      0          | Allows to use the runtime checks parameters.
USE_HAL_MMC_AUTO_DETECTION_FREQUENCY| from hal_conf.h |      0          | Allows to Enable/Disable MMC Custom Frequency.
USE_HAL_MMC_REGISTER_CALLBACKS      | from hal_conf.h |      0          | Allows to provide specific callback functions.
USE_HAL_MMC_LINKEDLIST              | from hal_conf.h |      1          | Allows to use the MMC in linked-list mode.
USE_HAL_MMC_GET_CID                 | from hal_conf.h |      1          | Allows to get MMC Card identification.
USE_HAL_MMC_GET_SPEC_VERSION        | from hal_conf.h |      1          | Allows to get the MMC Card version.
USE_HAL_MMC_GET_LAST_ERRORS         | from hal_conf.h |      1          | Allows to get last errors codes.
USE_HAL_MMC_USER_DATA               | from hal_conf.h |      0          | Allows to enable/disable user data.
USE_HAL_MMC_CLK_ENABLE_MODEL        | from hal_conf.h |HAL_CLK_ENABLE_NO| Allows to enable the clock model for the MMC.
USE_HAL_MMC_RPMB_FEATURE            | from hal_conf.h |      0          | Allows to enable the RPMB feature for the MMC.
  */
/**
  * @}
  */
#if defined(SDMMC1)
#if defined (USE_HAL_MMC_MODULE) && (USE_HAL_MMC_MODULE == 1)

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup MMC_Private_Functions MMC Private Functions
  * @{
  */
static void         MMC_SetDefaultConfig(const hal_mmc_handle_t *hmmc);
static hal_status_t MMC_SetConfig(hal_mmc_handle_t *hmmc, const hal_mmc_config_t *p_config);
static hal_status_t MMC_NotifyCardInsertion(hal_mmc_handle_t *hmmc, const hal_mmc_config_t *p_config);
static hal_status_t MMC_SetWideBus(hal_mmc_handle_t *hmmc, hal_mmc_bus_wide_t wide_bus);
static void         MMC_Write_IT(hal_mmc_handle_t *hmmc);
static void         MMC_Read_IT(hal_mmc_handle_t *hmmc);

static hal_status_t MMC_Card_Identify(hal_mmc_handle_t *hmmc);
static hal_status_t MMC_Card_IdentifyVoltageRange(hal_mmc_handle_t *hmmc);
static hal_status_t MMC_Card_IdentifyCID(hal_mmc_handle_t *hmmc);
static hal_status_t MMC_Card_IdentifyRelativeAddress(hal_mmc_handle_t *hmmc);
static hal_status_t MMC_Card_EnterDataTransferMode(hal_mmc_handle_t *hmmc);
static hal_status_t MMC_Card_GetCSD(hal_mmc_handle_t *hmmc);
static hal_status_t MMC_Card_SetHighSpeedMode(hal_mmc_handle_t *hmmc, uint32_t speed_mode_state);
static hal_status_t MMC_Card_SetDDRSpeedMode(hal_mmc_handle_t *hmmc, uint32_t speed_mode_state);
static hal_status_t MMC_Card_SetBlockSize(hal_mmc_handle_t *hmmc, uint32_t blk_size);
static hal_status_t MMC_Card_UpdatePwrClass(hal_mmc_handle_t *hmmc, uint32_t wide, uint32_t speed);
static hal_status_t MMC_Card_GetExtCSD(hal_mmc_handle_t *hmmc, uint32_t timeout_ms);
static hal_status_t MMC_Card_Erase(hal_mmc_handle_t *hmmc, hal_mmc_erase_type_t erase_type, uint32_t start_block_addr,
                                   uint32_t end_block_addr);
static uint32_t MMC_Card_CalculateClockDiv(const hal_mmc_handle_t *hmmc, uint32_t sdmmc_clk, uint32_t user_freq);
static hal_status_t MMC_Card_GetClockDiv(hal_mmc_handle_t *hmmc, uint32_t sdmmc_clk, uint32_t user_freq,
                                         uint32_t *p_clk_div);
static uint32_t     MMC_GetCardState(hal_mmc_handle_t *hmmc);

#if defined (USE_HAL_MMC_RPMB_FEATURE) && (USE_HAL_MMC_RPMB_FEATURE == 1)
static uint16_t MMC_Card_RPMBResultToErrorMask(uint16_t rpmb_result);
static hal_status_t MMC_Card_SetRPMBReliableWriteBlockCount(hal_mmc_handle_t *hmmc, uint32_t block_count);
static hal_status_t MMC_Card_ProgramRPMBPacket(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr,
                                               uint32_t blocks_nbr, uint8_t *p_mac, uint32_t timeout_ms);
static hal_status_t MMC_Card_GetRPMBWriteResponse(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t timeout_ms);

static hal_status_t MMC_Card_GetRPMBReadResponse(hal_mmc_handle_t *hmmc, uint8_t *p_data, const uint8_t *p_nonce,
                                                 uint8_t *p_mac, uint8_t *p_resp_req, uint32_t timeout_ms);

static void MMC_Card_ProgramRPMBStuff(hal_mmc_handle_t *hmmc);
static void MMC_Card_ProgramRPMBMac(hal_mmc_handle_t *hmmc);
static void MMC_Card_ProgramRPMBData(hal_mmc_handle_t *hmmc);
static void MMC_Card_ProgramRPMBTail(hal_mmc_handle_t *hmmc);
#endif /* USE_HAL_MMC_RPMB_FEATURE */
/**
  * @}
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup MMC_Private_Constants MMC Private Constants
  * @{
  */
#define MMC_CARD_SPEED_MODE_DISABLE               0U          /*!< MMC Card speed mode state disable                       */
#define MMC_CARD_SPEED_MODE_ENABLE                1U          /*!< MMC Card speed mode state enable                        */

#define MMC_CARD_BUFFER_EMPTY                     0x100U      /*!< MMC Card buffer empty ready for data                    */

#if defined (USE_HAL_MMC_RPMB_FEATURE) && (USE_HAL_MMC_RPMB_FEATURE == 1)
#define MMC_CARD_RPMB_KEY_MAC_POSITION            196U        /*!< MMC Card rpmb key mac position                          */
#define MMC_CARD_RPMB_DATA_POSITION               228U        /*!< MMC Card rpmb data position                             */
#define MMC_CARD_RPMB_NONCE_POSITION              484U        /*!< MMC Card rpmb nonce position                            */
#define MMC_CARD_RPMB_WRITE_COUNTER_POSITION      500U        /*!< MMC Card rpmb write counter position                    */
#define MMC_CARD_RPMB_RESULT_POSITION             508U        /*!< MMC Card rpmb request response position                 */
#define MMC_CARD_RPMB_REQ_RESP_POSITION           510U        /*!< MMC Card rpmb request response position                 */

#define MMC_CARD_RPMB_AUTHENTICATION_KEY_RESPONSE 0x0100U     /*!< MMC Card RPMB authentication key response               */
#define MMC_CARD_RPMB_COUNTER_VALUE_RESPONSE      0x0200U     /*!< MMC Card RPMB read counter value response               */
#define MMC_CARD_RPMB_WRITE_DATA_RESPONSE         0x0300U     /*!< MMC Card RPMB write data response                       */
#define MMC_CARD_RPMB_READ_DATA_RESPONSE          0x0400U     /*!< MMC Card RPMB read data response                        */

#define MMC_CARD_RPMB_STUFF_SIZE_BYTE             196U        /*!< MMC Card RPMB stuff size in byte                        */
#define MMC_CARD_RPMB_KEY_MAC_SIZE_BYTE           32U         /*!< MMC Card RPMB mac size in byte                          */
#define MMC_CARD_RPMB_DATA_SIZE_BYTE              256U        /*!< MMC Card RPMB data size in byte                         */
#define MMC_CARD_RPMB_NONCE_SIZE_BYTE             16U         /*!< MMC Card RPMB nonce size in byte                        */
#define MMC_CARD_RPMB_WRITE_COUNTER_SIZE_BYTE     4U          /*!< MMC Card RPMB write counter size in byte                */
#define MMC_CARD_RPMB_TAIL_SIZE_BYTE              28U         /*!< MMC Card RPMB write tail size in byte                   */

#define MMC_CARD_READ_WRITE_COUNTER_REQ           0x02U       /*!< MMC Card Reading of the Write Counter value request     */
#define MMC_CARD_AUTHENTICATED_DATA_WRITE_REQ     0x03U       /*!< MMC Card Authenticated data write request               */
#define MMC_CARD_AUTHENTICATED_DATA_READ_REQ      0x04U       /*!< MMC Card Authenticated data read request                */
#define MMC_CARD_RESULT_READ_REQ                  0x05U       /*!< MMC Card Result read request                            */

#define MMC_CARD_RPMB_PROGRAM_STUFF_BYTES_STEP1   0x01U       /*!< MMC Card RPMB program stuff bytes                       */
#define MMC_CARD_RPMB_PROGRAM_KEY_MAC_STEP2       0x02U       /*!< MMC Card RPMB program key mac                           */
#define MMC_CARD_RPMB_PROGRAM_DATA_STEP3          0x03U       /*!< MMC Card RPMB program RPMB data                         */
#define MMC_CARD_RPMB_PROGRAM_TAIL_STEP4          0x04U       /*!< MMC Card RPMB program tail pack                         */

#define MMC_CARD_RPMB_BLOCK_COUNT                 0x01U       /*!< MMC Card RPMB block count                               */
#define MMC_CARD_RPMB_RELIABLE_WRITE_TYPE         0x80000000U /*!< MMC Card RPMB Reliable write type of programming access */

/* RPMB raw result codes (received from card) */
#define MMC_CARD_RPMB_RESULT_OPERATION_OK                        0x0000U /*!< MMC Card Rpmb operation OK                          */
#define MMC_CARD_RPMB_RESULT_GENERAL_FAILURE                     0x0001U /*!< MMC Card Rpmb general failure                       */
#define MMC_CARD_RPMB_RESULT_AUTHENTICATION_FAILURE              0x0002U /*!< MMC Card Rpmb authentication failure                */
#define MMC_CARD_RPMB_RESULT_COUNTER_FAILURE                     0x0003U /*!< MMC Card Rpmb counter failure                       */
#define MMC_CARD_RPMB_RESULT_ADDRESS_FAILURE                     0x0004U /*!< MMC Card Rpmb address failure                       */
#define MMC_CARD_RPMB_RESULT_WRITE_FAILURE                       0x0005U /*!< MMC Card Rpmb write failure                         */
#define MMC_CARD_RPMB_RESULT_READ_FAILURE                        0x0006U /*!< MMC Card Rpmb read failure                          */
#define MMC_CARD_RPMB_RESULT_AUTHENTICATION_KEY_NOT_PROGRAMMED   0x0007U /*!< MMC Card Rpmb authentication key not yet programmed */
#define MMC_CARD_RPMB_RESULT_WRITE_COUNTER_EXPIRED               0x0080U /*!< MMC Card Rpmb write counter has expired             */
#endif /* USE_HAL_MMC_RPMB_FEATURE */

#define MMC_EXT_CSD_PWR_CLASS_DDR_52_FIFO_POS          (SDMMC_MMC_EXT_CSD_PWR_CL_DDR_52_IDX     >> 2U) /*!< MMC Card  ext csd pwr class ddr 52 position                 */
#define MMC_EXT_CSD_SUPPORT_PWR_CLASS_52_26_FIFO_POS   (SDMMC_MMC_EXT_CSD_PWR_CL_52_IDX         >> 2U) /*!< MMC Card  ext csd supported pwr class 52 | 26 position      */
#define MMC_EXT_CSD_DEV_TYPE_SWITCH_TIME_FIFO_POS      (SDMMC_MMC_EXT_CSD_DEVICE_TYPE_IDX       >> 2U) /*!< MMC Card  ext csd device type and switching timing position */
#define MMC_EXT_CSD_SECURE_REMOVAL_FIFO_POS            (SDMMC_MMC_EXT_CSD_SECURE_REMOVAL_IDX    >> 2U) /*!< MMC Card  ext csd secure removal position                   */
#define MMC_EXT_CSD_DATA_SECTOR_SIZE_FIFO_POS          (SDMMC_MMC_EXT_CSD_DATA_SECTOR_SIZE_IDX  >> 2U) /*!< MMC Card  ext csd data sector size position                 */
#define MMC_EXT_CSD_SLEEP_NOTIF_AWAKE_TIME_FIFO_POS    (SDMMC_MMC_EXT_CSD_SLEEP_NOTIF_TIME_IDX  >> 2U) /*!< MMC Card  ext csd sleep notification awak timing position   */
#define MMC_EXT_CSD_SECTOR_COUNT_SIZE_FIFO_POS         (SDMMC_MMC_EXT_CSD_SECTOR_COUNT_SIZE_IDX >> 2U) /*!< MMC Card  ext csd sector count size position                */
#define MMC_EXT_CSD_PWR_CLASS_SIZE_FIFO_POS            (SDMMC_MMC_EXT_CSD_PWR_CLASS_SIZE_IDX    >> 2U) /*!< MMC Card  ext csd pwr class size position                   */
#define MMC_EXT_CSD_RPMB_SIZE_MULT_FIFO_POS            (SDMMC_MMC_EXT_CSD_RPMB_SIZE_MULT_IDX    >> 2U) /*!< MMC Card  ext csd rpmb size mult position                   */


/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup MMC_Private_Macros MMC Private Macros
  * @{
  */
/*! Check secure removal type */
#define IS_MMC_SRT_TYPE(type) (((type) == HAL_MMC_SRT_ERASE) || ((type) == HAL_MMC_SRT_WRITE_CHAR_ERASE) \
                               || ((type) == HAL_MMC_SRT_WRITE_CHAR_COMPL_RANDOM)                        \
                               || ((type) == HAL_MMC_SRT_VENDOR_DEFINED))

/*! Check the erase type */
#define IS_MMC_ERASE_TYPE(type) (((type) == HAL_MMC_ERASE_DEFAULT) || ((type) == HAL_MMC_ERASE_TRIM)                 \
                                 || ((type) == HAL_MMC_ERASE_DISCARD) || ((type) == HAL_MMC_ERASE_SECURE_TRIM_STEP1) \
                                 || ((type) == HAL_MMC_ERASE_SECURE) || ((type) == HAL_MMC_ERASE_SECURE_TRIM_STEP2))

/*! Check if the address is aligned to 8 */
#define IS_MMC_ADDR_ALIGNED_TO_8(addr)    (((addr) % 8U) == 0U)

/*! Check the case of blocks sector size field != 0 */
#define IS_MMC_DATA_SECTOR_SIZE(sector_size, start_addr, end_addr)  (((sector_size) == 0U) ? (1U == 1U) :    \
                                                                     (IS_MMC_ADDR_ALIGNED_TO_8((start_addr)) \
                                                                      && IS_MMC_ADDR_ALIGNED_TO_8((end_addr))))

/*! Macro to get the handle instance */
#define MMC_GET_INSTANCE(handle) ((SDMMC_TypeDef *)((uint32_t)(handle)->instance))

/*! Check the partition type */
#define IS_MMC_PARTITION_TYPE(partition)  (((partition) == HAL_MMC_AREA_PARTITION_USER)       \
                                           || ((partition) == HAL_MMC_AREA_PARTITION_BOOT_1 ) \
                                           || ((partition) == HAL_MMC_AREA_PARTITION_BOOT_2 ) \
                                           || ((partition) == HAL_MMC_AREA_PARTITION_RPMB   ))
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup MMC_Exported_Functions HAL MMC Functions
  * @{
  */

/** @addtogroup MMC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
This section provides functions allowing to initialize/de-initialize the MMC card device :
- Call the function HAL_MMC_Init() to initialize the selected  HAL MMC handle and associate an MMC peripheral instance.
- Call the function HAL_MMC_DeInit() to de-initialize the MMC card device.
  */
/**
  * @brief Initialize the selected  HAL MMC handle and associate an MMC peripheral instance.
  * @param hmmc     Pointer to a hal_mmc_handle_t structure.
  * @param instance HAL MMC instance.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            MMC handle has been correctly Initialized.
  */
hal_status_t HAL_MMC_Init(hal_mmc_handle_t *hmmc, hal_mmc_t instance)
{
  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_ALL_INSTANCE((SDMMC_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hmmc == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmmc->instance = instance;

#if defined (USE_HAL_MMC_CLK_ENABLE_MODEL) && (USE_HAL_MMC_CLK_ENABLE_MODEL == HAL_CLK_ENABLE_PERIPH_ONLY)
  if (hmmc->instance == HAL_MMC_CARD_1)
  {
    LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_SDMMC1);
  }
#if defined (SDMMC2)
  else if (hmmc->instance == HAL_MMC_CARD_2)
  {
    LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_SDMMC2);
  }
#endif /* SDMMC2 */
  else
  {
    /* Nothing to do */
  }
#endif /* USE_HAL_MMC_CLK_ENABLE_MODEL */

#if defined (USE_HAL_MMC_REGISTER_CALLBACKS) && (USE_HAL_MMC_REGISTER_CALLBACKS == 1)
  hmmc->p_xfer_cplt_callback = HAL_MMC_XferCpltCallback;
  hmmc->p_error_callback     = HAL_MMC_ErrorCallback;
  hmmc->p_abort_callback     = HAL_MMC_AbortCallback;
#endif /* USE_HAL_MMC_REGISTER_CALLBACKS */

#if defined (USE_HAL_MMC_USER_DATA) && (USE_HAL_MMC_USER_DATA == 1)
  hmmc->p_user_data = NULL;
#endif /* USE_HAL_MMC_USER_DATA */

#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
  hmmc->last_error_codes = HAL_MMC_ERROR_NONE;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
#if defined (USE_HAL_MMC_RPMB_FEATURE) && (USE_HAL_MMC_RPMB_FEATURE == 1)
  hmmc->rpmb_error_codes = HAL_MMC_RPMB_OPERATION_OK;
#endif /* USE_HAL_MMC_RPMB_FEATURE */
  hmmc->context = SDMMC_CONTEXT_NONE;
  hmmc->global_state = HAL_MMC_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief De-Initialize the MMC card.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  */
void HAL_MMC_DeInit(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_ALL_INSTANCE(MMC_GET_INSTANCE(hmmc)));

  p_instance  = MMC_GET_INSTANCE(hmmc);

  SDMMC_DISABLE_IT(p_instance, SDMMC_IT_DATAEND | SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR \
                   | SDMMC_IT_RXOVERR);

  SDMMC_CMDTRANS_DISABLE(p_instance);

  (void)SDMMC_SendStopTransferCmd(p_instance, hmmc->stop_xfer_timeout_ms);

  SDMMC_SET_PWR_STATE(p_instance, SDMMC_PWR_OFF);

  hmmc->global_state = HAL_MMC_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup MMC_Exported_Functions_Group2 Set and Get configurations functions
  * @{
This subsection provides a set of functions allowing to configure the MMC peripheral:

There are 2 categories of HAL configuration APIs:

- Global configuration APIs:
  - HAL_MMC_SetConfig()           : Allowing to set the HAL peripheral instance into a ready to use state (idle)
                                    according to the user parameters.
  - HAL_MMC_GetConfig()           : Allowing to retrieve the HAL peripheral configuration.
  - HAL_MMC_NotifyCardInsertion() : Allowing to set the user parameters after detection the insertion of MMC card.
  - HAL_MMC_NotifyCardRemoval()   : Allowing to set the default SDMMC config after the removal of the MMC card.
  - HAL_MMC_SwitchSpeedMode()     : Allowing to switch to the speed bus mode desired.
- Unitary configuration APIs:
  - HAL_MMC_SetDataTimeout()      : Allowing to modify the data timeout value according to the MMC card type.
  - HAL_MMC_GetDataTimeout()      : Allowing to retrieve the data timeout value.
  - HAL_MMC_SetStopXferTimeout()  : Allowing to modify the stop transfer timeout value according to MMC card type.
  - HAL_MMC_GetStopXferTimeout()  : Allowing to retrieve the stop transfer timeout value.
  - HAL_MMC_SetEraseTimeout()     : Allowing to modify the erase timeout value according to MMC card type.
  - HAL_MMC_GetEraseTimeout()     : Allowing to retrieve the ererase timeout value.
  - HAL_MMC_GetClockFreq()        : Allowing to retrieve the MMC peripheral kernel clock frequency.
These APIs are intended to dynamically modify/Retrieve a unitary item meaning that a global config has been already
applied.
  */
/**
  * @brief Configure the MMC according to the user parameters.
  * @param hmmc     Pointer to a hal_mmc_handle_t structure.
  * @param p_config Pointer to a hal_mmc_config_t structure that contains the MMC configuration.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         MMC instance is already configured and cannot be modified.
  * @retval HAL_OK            MMC instance has been correctly configured.
  */
hal_status_t HAL_MMC_SetConfig(hal_mmc_handle_t *hmmc, const hal_mmc_config_t *p_config)
{
  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_EDGE(((uint32_t)p_config->clk_cfg.clk_edge)));
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_POWER_SAVE(((uint32_t)p_config->clk_cfg.clk_power_save)));
  ASSERT_DBG_PARAM(IS_SDMMC_BUS_WIDE(((uint32_t)p_config->bus_wide)));
  ASSERT_DBG_PARAM(IS_SDMMC_HARDWARE_FLOW_CONTROL(((uint32_t)p_config->hw_flow_ctrl)));
#if defined (USE_HAL_MMC_AUTO_DETECTION_FREQUENCY) && (USE_HAL_MMC_AUTO_DETECTION_FREQUENCY == 0)
  ASSERT_DBG_PARAM(p_config->clk_cfg.clk_hz != 0U);
#endif /* USE_HAL_MMC_AUTO_DETECTION_FREQUENCY */

  ASSERT_DBG_STATE(hmmc->global_state, ((uint32_t)HAL_MMC_STATE_INIT) | (uint32_t)HAL_MMC_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmmc->data_timeout_cycle   = p_config->data_timeout_cycle;
  hmmc->stop_xfer_timeout_ms = p_config->stop_xfer_timeout_ms;
  hmmc->erase_timeout_ms     = p_config->erase_timeout_ms;

  MMC_SetDefaultConfig(hmmc);

  if (MMC_NotifyCardInsertion(hmmc, p_config) != HAL_OK)
  {
    hmmc->global_state = HAL_MMC_STATE_CARD_REMOVED;
    return HAL_ERROR;
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the MMC configuration.
  * @param hmmc     Pointer to a hal_mmc_handle_t structure.
  * @param p_config Pointer to a hal_mmc_config_t structure that contains the MMC configuration.
  */
void HAL_MMC_GetConfig(const hal_mmc_handle_t *hmmc, hal_mmc_config_t *p_config)
{
  sdmmc_config_t sdmmc_cfg = {0};

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  SDMMC_GetConfig(MMC_GET_INSTANCE(hmmc), &sdmmc_cfg);
  p_config->bus_wide               = (hal_mmc_bus_wide_t)(sdmmc_cfg.bus_wide);
  p_config->hw_flow_ctrl           = (hal_mmc_hardware_flow_control_t)(sdmmc_cfg.hardware_flow_control);
  p_config->clk_cfg.clk_edge       = (hal_mmc_clock_edge_t)sdmmc_cfg.clk.clock_edge;
  p_config->clk_cfg.clk_power_save = (hal_mmc_clock_power_save_t)sdmmc_cfg.clk.clock_power_save;
#if defined (USE_HAL_MMC_AUTO_DETECTION_FREQUENCY) && (USE_HAL_MMC_AUTO_DETECTION_FREQUENCY == 0)
  p_config->clk_cfg.clk_hz = HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)(hmmc)->instance));
  if (sdmmc_cfg.clk.clock_div != 0U)
  {
    p_config->clk_cfg.clk_hz /= (2U * sdmmc_cfg.clk.clock_div);
  }
#endif /* USE_HAL_MMC_AUTO_DETECTION_FREQUENCY */

  p_config->data_timeout_cycle   = hmmc->data_timeout_cycle;
  p_config->erase_timeout_ms     = hmmc->erase_timeout_ms;
  p_config->stop_xfer_timeout_ms = hmmc->stop_xfer_timeout_ms;
}

/**
  * @brief Notify MMC card after insertion.
  * @param hmmc     Pointer to a hal_mmc_handle_t structure.
  * @param p_config Pointer to a hal_mmc_config_t structure that contains the MMC configuration.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    MMC instance has been correctly configured after detection.
  */
hal_status_t HAL_MMC_NotifyCardInsertion(hal_mmc_handle_t *hmmc, const hal_mmc_config_t *p_config)
{
  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_EDGE(((uint32_t)p_config->clk_cfg.clk_edge)));
  ASSERT_DBG_PARAM(IS_SDMMC_CLOCK_POWER_SAVE(((uint32_t)p_config->clk_cfg.clk_power_save)));
  ASSERT_DBG_PARAM(IS_SDMMC_BUS_WIDE(((uint32_t)p_config->bus_wide)));
  ASSERT_DBG_PARAM(IS_SDMMC_HARDWARE_FLOW_CONTROL(((uint32_t)p_config->hw_flow_ctrl)));
#if defined (USE_HAL_MMC_AUTO_DETECTION_FREQUENCY) && (USE_HAL_MMC_AUTO_DETECTION_FREQUENCY == 0)
  ASSERT_DBG_PARAM(p_config->clk_cfg.clk_hz != 0U);
#endif /* USE_HAL_MMC_AUTO_DETECTION_FREQUENCY */

  ASSERT_DBG_STATE(hmmc->global_state, ((uint32_t)HAL_MMC_STATE_CARD_REMOVED) | (uint32_t)HAL_MMC_STATE_IDLE);

  if (MMC_NotifyCardInsertion(hmmc, p_config) != HAL_OK)
  {
    hmmc->global_state = HAL_MMC_STATE_CARD_REMOVED;
    return HAL_ERROR;
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Notify MMC card after removal.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_OK MMC card has been correctly re-configured with its default configuration.
  */
hal_status_t HAL_MMC_NotifyCardRemoval(hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  MMC_SetDefaultConfig(hmmc);

  hmmc->global_state = HAL_MMC_STATE_CARD_REMOVED;

  return HAL_OK;
}

/**
  * @brief Configure the speed bus mode.
  * @param hmmc       Pointer to a hal_mmc_handle_t structure.
  * @param speed_mode Specifies the MMC card speed bus mode.
  *        This parameter can be one of the following values @ref hal_mmc_speed_mode_t group.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_BUSY    Concurrent process ongoing.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_MMC_SwitchSpeedMode(hal_mmc_handle_t *hmmc, hal_mmc_speed_mode_t speed_mode)
{
  const SDMMC_TypeDef *p_instance;
  uint32_t tickstart;
  hal_status_t status = HAL_OK;
  uint32_t device_type;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(IS_SDMMC_SPEED_MODE(((uint32_t)speed_mode)));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

  p_instance  = MMC_GET_INSTANCE(hmmc);

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  /* Field device_type extracted from Extended CSD register = [196 = 49*4] */
  device_type = hmmc->device_type;

  switch (speed_mode)
  {
    case HAL_MMC_SPEED_MODE_AUTO:
    {
      if (((p_instance->CLKCR & SDMMC_CLKCR_WIDBUS) != 0U) && ((device_type & 0x04U) != 0U))
      {
        if (MMC_Card_SetHighSpeedMode(hmmc, MMC_CARD_SPEED_MODE_ENABLE) != HAL_OK)
        {
          status = HAL_ERROR;
        }
        else
        {
          if ((p_instance->CLKCR & SDMMC_CLKCR_CLKDIV) != 0U)
          {
            /* DDR mode not supported with CLKDIV = 0 */
            if (MMC_Card_SetDDRSpeedMode(hmmc, MMC_CARD_SPEED_MODE_ENABLE) != HAL_OK)
            {
              status = HAL_ERROR;
            }
          }
        }
      }
      else if ((device_type & 0x02U) != 0U)
      {
        if (MMC_Card_SetHighSpeedMode(hmmc, MMC_CARD_SPEED_MODE_ENABLE) != HAL_OK)
        {
          status = HAL_ERROR;
        }
      }
      else
      {
        /* Nothing to do : keep current speed */
      }
      break;
    }
    case HAL_MMC_SPEED_MODE_DDR:
    {
      if (((p_instance->CLKCR & SDMMC_CLKCR_WIDBUS) != 0U) && ((device_type & 0x04U) != 0U))
      {
        if (MMC_Card_SetHighSpeedMode(hmmc, MMC_CARD_SPEED_MODE_ENABLE) != HAL_OK)
        {
          status = HAL_ERROR;
        }
        else
        {
          if ((p_instance->CLKCR & SDMMC_CLKCR_CLKDIV) != 0U)
          {
            /* DDR mode not supported with CLKDIV = 0 */
            if (MMC_Card_SetDDRSpeedMode(hmmc, MMC_CARD_SPEED_MODE_ENABLE) != HAL_OK)
            {
              status = HAL_ERROR;
            }
          }
        }
      }
      else
      {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
        hmmc->last_error_codes |= HAL_MMC_ERROR_UNSUPPORTED_FEATURE;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
        status = HAL_ERROR;
      }
      break;
    }
    case HAL_MMC_SPEED_MODE_HIGH:
    {
      if ((device_type & 0x02U) != 0U)
      {
        if (MMC_Card_SetHighSpeedMode(hmmc, MMC_CARD_SPEED_MODE_ENABLE) != HAL_OK)
        {
          status = HAL_ERROR;
        }
      }
      else
      {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
        hmmc->last_error_codes |= HAL_MMC_ERROR_UNSUPPORTED_FEATURE;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
        status = HAL_ERROR;
      }
      break;
    }
    case HAL_MMC_SPEED_MODE_DEFAULT:
    {
      if ((p_instance->CLKCR & SDMMC_CLKCR_DDR) != 0U)
      {
        if (MMC_Card_SetDDRSpeedMode(hmmc, MMC_CARD_SPEED_MODE_DISABLE) != HAL_OK)
        {
          status = HAL_ERROR;
        }
      }
      if ((p_instance->CLKCR & SDMMC_CLKCR_BUSSPEED) != 0U)
      {
        if (MMC_Card_SetHighSpeedMode(hmmc, MMC_CARD_SPEED_MODE_DISABLE) != HAL_OK)
        {
          status = HAL_ERROR;
        }
      }
      break;
    }
    default:
      status = HAL_ERROR;
      break;
  }

  /* Verify that MMC card is ready to use after Speed mode switch*/
  tickstart = HAL_GetTick();
  while ((MMC_GetCardState(hmmc) != (uint32_t)HAL_MMC_CARD_TRANSFER))
  {
    if ((HAL_GetTick() - tickstart) >= hmmc->data_timeout_cycle)
    {
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return status;
}

/**
  * @brief Set MMC data timeout.
  * @param hmmc               Pointer to a hal_mmc_handle_t structure.
  * @param data_timeout_cycle MMC data timeout cycle.
  * @retval HAL_OK            MMC card has been correctly set the data timeout cycle value in millisecond.
  */
hal_status_t HAL_MMC_SetDataTimeout(hal_mmc_handle_t *hmmc, uint32_t data_timeout_cycle)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

  hmmc->data_timeout_cycle = data_timeout_cycle;

  return HAL_OK;
}

/**
  * @brief Get MMC data timeout.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval uint32_t data_timeout_cycle value in millisecond.
  */
uint32_t HAL_MMC_GetDataTimeout(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  return hmmc->data_timeout_cycle;
}

/**
  * @brief Set MMC stop transfer timeout.
  * @param hmmc                Pointer to a hal_mmc_handle_t structure.
  * @param stopxfer_timeout_ms MMC stop xfer timeout in millisecond.
  * @retval HAL_OK             When the MMC card correctly sets the stop xfer timeout in millisecond.
  */
hal_status_t HAL_MMC_SetStopXferTimeout(hal_mmc_handle_t *hmmc, uint32_t stopxfer_timeout_ms)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

  hmmc->stop_xfer_timeout_ms = stopxfer_timeout_ms;

  return HAL_OK;
}

/**
  * @brief Get MMC stop transfer timeout.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval uint32_t stop_xfer_timeout_ms Stop xfer timeout value in millisecond.
  */
uint32_t HAL_MMC_GetStopXferTimeout(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  return hmmc->stop_xfer_timeout_ms;
}

/**
  * @brief Set MMC erase timeout.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param erase_timeout_ms MMC erase timeout in millisecond.
  * @retval HAL_OK          When the MMC card correctly sets the erase timeout value in millisecond.
  */
hal_status_t HAL_MMC_SetEraseTimeout(hal_mmc_handle_t *hmmc, uint32_t erase_timeout_ms)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

  hmmc->erase_timeout_ms = erase_timeout_ms;

  return HAL_OK;
}

/**
  * @brief Get MMC erase timeout.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval uint32_t erase_timeout_ms Erase timeout value in millisecond.
  */
uint32_t HAL_MMC_GetEraseTimeout(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  return hmmc->erase_timeout_ms;
}

/** @brief  Return the peripheral clock frequency for MMC card.
  * @param  hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval uint32_t Frequency in Hz.
  *         0 if the source clock of the MMC is not configured or not ready.
  */
uint32_t HAL_MMC_GetClockFreq(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM((hmmc != NULL));
  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT | (uint32_t)HAL_MMC_STATE_CARD_REMOVED);

  return HAL_RCC_SDMMC_GetKernelClkFreq(MMC_GET_INSTANCE(hmmc));
}

/**
  * @}
  */

/** @addtogroup MMC_Exported_Functions_Group3 Input and Output operation functions
  * @{
This subsection provides a set of functions allowing to manage the data transfer from/to MMC card.

There are 4 categories of HAL functions APIs to manage the data transfer:
- Blocking mode: Polling
  - HAL_MMC_ReadBlocks()
  - HAL_MMC_WriteBlocks()
- Non-Blocking mode: IT
 - HAL_MMC_ReadBlocks_IT()
 - HAL_MMC_WriteBlocks_IT()
- Non-Blocking mode: DMA
 - HAL_MMC_ReadBlocks_DMA()
 - HAL_MMC_WriteBlocks_DMA()
- Non-Blocking mode: DMA in linked list mode
 - HAL_MMC_ReadBlocks_LinkedList()
 - HAL_MMC_WriteBlocks_LinkedList()
- Function to Erases the specified memory area of the given MMC card.

There are 2 categories of HAL functions APIs to abort transfer data:
- Abort the current transfer in polling mode with HAL_MMC_Abort().
- Abort the current transfer in IT/DMA mode with HAL_MMC_Abort_IT().
  */
/**
  * @brief Erase the specified memory area of the given MMC card.
  * @param hmmc             Pointer to a hal_mmc_handle_t structure.
  * @param start_block_addr Start Block address.
  * @param end_block_addr   End Block address.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_Erase(hal_mmc_handle_t *hmmc, uint32_t start_block_addr, uint32_t end_block_addr)
{
  uint32_t start_addr = start_block_addr;
  uint32_t end_addr   = end_block_addr;
  uint32_t tick_start;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(end_addr >= start_addr);
  ASSERT_DBG_PARAM(end_addr <= hmmc->mmc_card_info.logical_block_nbr);
  ASSERT_DBG_PARAM(IS_MMC_DATA_SECTOR_SIZE(hmmc->data_sector_size, start_addr, end_addr));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((end_addr < start_addr) || (end_addr > hmmc->mmc_card_info.logical_block_nbr))
  {
    return HAL_INVALID_PARAM;
  }

  if ((hmmc->data_sector_size != 0x0U) && (((start_addr % 8U) != 0U) || ((end_addr % 8U) != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  if ((hmmc->mmc_card_type) != SDMMC_MMC_CARD_HC)
  {
    start_addr *= SDMMC_BLOCK_SIZE_BYTE;
    end_addr   *= SDMMC_BLOCK_SIZE_BYTE;
  }

  if (MMC_GetCardState(hmmc) != (uint32_t)HAL_MMC_CARD_TRANSFER)
  {
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  if (MMC_Card_Erase(hmmc, HAL_MMC_ERASE_DEFAULT, start_addr, end_addr) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tick_start = HAL_GetTick();
  while (MMC_GetCardState(hmmc) != (uint32_t)HAL_MMC_CARD_TRANSFER)
  {
    if ((HAL_GetTick() - tick_start) >= SDMMC_CMD_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Read block(s) from a specified address in a card. The Data transfer is managed by polling mode.
  * @param hmmc          Pointer to a hal_mmc_handle_t structure.
  * @param p_data        Pointer to the buffer that must contain the received data.
  * @param block_addr    Block Address from where data is to be read.
  * @param blocks_nbr    Number of MMC blocks to read.
  * @param timeout_ms    Timeout value in millisecond.
  * @warning This API must be followed by a check on the card state through HAL_MMC_GetCardState().
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_ReadBlocks(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr,
                                uint32_t timeout_ms)
{
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t error_code;
  uint32_t tickstart = HAL_GetTick();
  uint32_t remaining_data;
  uint32_t addr = block_addr;
  uint32_t *p_tmp_data;
  uint32_t cmd_type;
  SDMMC_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hmmc->mmc_card_info.logical_block_nbr);
  ASSERT_DBG_PARAM(IS_MMC_DATA_SECTOR_SIZE(hmmc->data_sector_size, addr, blocks_nbr));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || ((addr + blocks_nbr) > hmmc->mmc_card_info.logical_block_nbr))
  {
    return HAL_INVALID_PARAM;
  }

  if ((hmmc->data_sector_size != 0x0U) && (((addr % 8U) != 0U) || ((blocks_nbr % 8U) != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  p_tmp_data = (uint32_t *)(uint32_t)p_data;
  SDMMC_CLEAR_DCTRL(p_instance);

  if ((hmmc->mmc_card_type) != SDMMC_MMC_CARD_HC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = blocks_nbr * SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (blocks_nbr > 1U)
  {
    hmmc->context = SDMMC_CONTEXT_READ_MULTIPLE_BLOCK;
    cmd_type = SDMMC_CMD_READ_MULT_BLOCK;
  }
  else
  {
    hmmc->context = SDMMC_CONTEXT_READ_SINGLE_BLOCK;
    cmd_type = SDMMC_CMD_READ_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendReadBlocksCmd(p_instance, addr, cmd_type);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  remaining_data = data_ctrl.data_length;
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0UL)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXFIFOHF) != 0UL) && (remaining_data >= 32U))
    {
      for (uint32_t count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
      {
        *p_tmp_data = SDMMC_ReadFIFO(p_instance);
        p_tmp_data++;
      }
      remaining_data -= SDMMC_FIFO_SIZE;
    }

    if (((HAL_GetTick() - tickstart) >= timeout_ms) || (timeout_ms == 0U))
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);

  if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DATAEND) != 0UL) && (blocks_nbr > 1U))
  {
    error_code = SDMMC_SendStopTransferCmd(p_instance, hmmc->stop_xfer_timeout_ms);
    if (error_code != HAL_MMC_ERROR_NONE)
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_ERROR;
    }
  }

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_RXOVERR) != 0U)
  {
    error_code = SDMMC_READ_REG(p_instance, STAR);
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    if ((error_code & SDMMC_FLAG_DTIMEOUT) != 0UL)
    {
      hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
    }

    if ((error_code & SDMMC_FLAG_DCRCFAIL) != 0UL)
    {
      hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_CRC_FAIL;
    }

    if ((error_code & SDMMC_FLAG_RXOVERR) != 0UL)
    {
      hmmc->last_error_codes |= HAL_MMC_ERROR_RX_OVERRUN;
    }
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */

    hmmc->context = SDMMC_CONTEXT_NONE;
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Write block(s) to a specified address in a card. The Data transfer is managed by polling mode.
  * @param hmmc       Pointer to a hal_mmc_handle_t structure.
  * @param p_data     Pointer to the buffer that must contain the data to transmit.
  * @param block_addr Block Address where data must be written.
  * @param blocks_nbr Number of MMC blocks to write.
  * @param timeout_ms Timeout value in millisecond.
  * @warning This API must be followed by a check on the card state through HAL_MMC_GetCardState().
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       A timeout has occurred.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_WriteBlocks(hal_mmc_handle_t *hmmc, const uint8_t *p_data, uint32_t block_addr,
                                 uint32_t blocks_nbr, uint32_t timeout_ms)
{
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t error_code;
  uint32_t tickstart = HAL_GetTick();
  uint32_t remaining_data;
  uint32_t addr = block_addr;
  const uint32_t *p_tmp_data;
  uint32_t cmd_type;
  SDMMC_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hmmc->mmc_card_info.logical_block_nbr);
  ASSERT_DBG_PARAM(IS_MMC_DATA_SECTOR_SIZE(hmmc->data_sector_size, addr, blocks_nbr));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || ((addr + blocks_nbr) > hmmc->mmc_card_info.logical_block_nbr))
  {
    return HAL_INVALID_PARAM;
  }

  if ((hmmc->data_sector_size != 0x0U) && (((addr % 8U) != 0U) || ((blocks_nbr % 8U) != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_tmp_data = (const uint32_t *)(uint32_t)p_data;
  p_instance  = MMC_GET_INSTANCE(hmmc);
  SDMMC_CLEAR_DCTRL(p_instance);

  if ((hmmc->mmc_card_type) != SDMMC_MMC_CARD_HC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = blocks_nbr * SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (blocks_nbr > 1U)
  {
    hmmc->context = SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK;
    cmd_type = SDMMC_CMD_WRITE_MULT_BLOCK;
  }
  else
  {
    hmmc->context = SDMMC_CONTEXT_WRITE_SINGLE_BLOCK;
    cmd_type = SDMMC_CMD_WRITE_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendWriteBlocksCmd(p_instance, addr, cmd_type);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  remaining_data = data_ctrl.data_length;
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXUNDERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0UL)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXFIFOHE) == 1UL) && (remaining_data >= 32U))
    {
      for (uint32_t count = 0U; count < 8U; count++)
      {
        SDMMC_WriteFIFO(p_instance, *p_tmp_data);
        p_tmp_data++;
      }
      remaining_data -= 32U;
    }

    if (((HAL_GetTick() - tickstart) >= timeout_ms) || (timeout_ms == 0U))
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);

  if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DATAEND) != 0UL) && (blocks_nbr > 1U))
  {
    error_code = SDMMC_SendStopTransferCmd(p_instance, hmmc->stop_xfer_timeout_ms);
    if (error_code != HAL_MMC_ERROR_NONE)
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_ERROR;
    }
  }

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_TXUNDERR) != 0U)
  {
    error_code = SDMMC_READ_REG(p_instance, STAR);
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
    if ((error_code & SDMMC_FLAG_DTIMEOUT) != 0UL)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    }

    if ((error_code & SDMMC_FLAG_DCRCFAIL) != 0UL)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    }

    if ((error_code & SDMMC_FLAG_TXUNDERR) != 0UL)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= HAL_MMC_ERROR_TX_UNDERRUN;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    }
    hmmc->context = SDMMC_CONTEXT_NONE;
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
  hmmc->context = SDMMC_CONTEXT_NONE;
  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Read block(s) from a specified address in a card. The Data transfer is managed in interrupt mode.
  * @param hmmc       Pointer to a hal_mmc_handle_t structure.
  * @param p_data     Pointer to the buffer that must contain the received data.
  * @param block_addr Block Address from where data is to be read.
  * @param blocks_nbr Number of blocks to read.
  * @warning This API must be followed by a check on the card state through HAL_MMC_GetCardState().
  * @warning It could also check the IT transfer process through the MMC Rx interrupt event.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_ReadBlocks_IT(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr)
{
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t addr = block_addr;
  uint32_t error_code;
  uint32_t cmd_type;
  SDMMC_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hmmc->mmc_card_info.logical_block_nbr);
  ASSERT_DBG_PARAM(IS_MMC_DATA_SECTOR_SIZE(hmmc->data_sector_size, addr, blocks_nbr));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || ((addr + blocks_nbr) > hmmc->mmc_card_info.logical_block_nbr))
  {
    return HAL_INVALID_PARAM;
  }

  if ((hmmc->data_sector_size != 0x0U) && (((addr % 8U) != 0U) || ((blocks_nbr % 8U) != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);

  SDMMC_CLEAR_DCTRL(p_instance);

  hmmc->p_xfer_buff = (uint32_t *)(uint32_t)p_data;
  hmmc->xfer_size_byte = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;

  if ((hmmc->mmc_card_type) != SDMMC_MMC_CARD_HC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (blocks_nbr > 1U)
  {
    hmmc->context = (SDMMC_CONTEXT_READ_MULTIPLE_BLOCK | SDMMC_CONTEXT_IT);
    cmd_type = SDMMC_CMD_READ_MULT_BLOCK;
  }
  else
  {
    hmmc->context = (SDMMC_CONTEXT_READ_SINGLE_BLOCK | SDMMC_CONTEXT_IT);
    cmd_type = SDMMC_CMD_READ_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendReadBlocksCmd(p_instance, addr, cmd_type);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_ENABLE_IT(p_instance, (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_RXOVERR | SDMMC_IT_DATAEND \
                               | SDMMC_FLAG_RXFIFOHF));

  return HAL_OK;
}

/**
  * @brief Write block(s) to a specified address in a card. The Data transfer is managed in interrupt mode.
  * @param hmmc       Pointer to a hal_mmc_handle_t structure.
  * @param p_data     Pointer to the buffer that must contain the data to transmit.
  * @param block_addr Block Address where data must be written.
  * @param blocks_nbr Number of blocks to write.
  * @warning This API must be followed by a check on the card state through HAL_MMC_GetCardState().
  * @warning It could also check the IT transfer process through the MMC Tx interrupt event.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_WriteBlocks_IT(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr)
{
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t addr = block_addr;
  uint32_t error_code;
  uint32_t cmd_type;
  SDMMC_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hmmc->mmc_card_info.logical_block_nbr);
  ASSERT_DBG_PARAM(IS_MMC_DATA_SECTOR_SIZE(hmmc->data_sector_size, addr, blocks_nbr));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || ((addr + blocks_nbr) > hmmc->mmc_card_info.logical_block_nbr))
  {
    return HAL_INVALID_PARAM;
  }

  if ((hmmc->data_sector_size != 0x0U) && (((addr % 8U) != 0U) || ((blocks_nbr % 8U) != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  SDMMC_CLEAR_DCTRL(p_instance);

  hmmc->p_xfer_buff = (uint32_t *)(uint32_t)p_data;
  hmmc->xfer_size_byte = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;

  if ((hmmc->mmc_card_type) != SDMMC_MMC_CARD_HC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);

  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (blocks_nbr > 1U)
  {
    hmmc->context = (SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK | SDMMC_CONTEXT_IT);
    cmd_type = SDMMC_CMD_WRITE_MULT_BLOCK;
  }
  else
  {
    hmmc->context = (SDMMC_CONTEXT_WRITE_SINGLE_BLOCK | SDMMC_CONTEXT_IT);
    cmd_type = SDMMC_CMD_WRITE_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendWriteBlocksCmd(p_instance, addr, cmd_type);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_ENABLE_IT(p_instance, (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR | SDMMC_IT_DATAEND \
                               | SDMMC_FLAG_TXFIFOHE));

  return HAL_OK;
}

/**
  * @brief Read block(s) from a specified address in a card. The Data transfer is managed by DMA mode.
  * @param hmmc       Pointer to a hal_mmc_handle_t structure.
  * @param p_data     Pointer to the buffer that must contain the received data.
  * @param block_addr Block Address from where data is to be read.
  * @param blocks_nbr Number of blocks to read.
  * @warning This API must be followed by a check on the card state through HAL_MMC_GetCardState().
  * @warning It could also check the DMA transfer process through the MMC Rx interrupt event.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_ReadBlocks_DMA(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr)
{
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t addr = block_addr;
  uint32_t error_code;
  uint32_t cmd_type;
  SDMMC_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hmmc->mmc_card_info.logical_block_nbr);
  ASSERT_DBG_PARAM(IS_MMC_DATA_SECTOR_SIZE(hmmc->data_sector_size, addr, blocks_nbr));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || ((addr + blocks_nbr) > hmmc->mmc_card_info.logical_block_nbr))
  {
    return HAL_INVALID_PARAM;
  }

  if ((hmmc->data_sector_size != 0x0U) && (((addr % 8U) != 0U) || ((blocks_nbr % 8U) != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  SDMMC_CLEAR_DCTRL(p_instance);

  hmmc->p_xfer_buff = (uint32_t *)(uint32_t)p_data;
  hmmc->xfer_size_byte = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;

  if ((hmmc->mmc_card_type) != SDMMC_MMC_CARD_HC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);

  SDMMC_CMDTRANS_ENABLE(MMC_GET_INSTANCE(hmmc));
  MMC_GET_INSTANCE(hmmc)->IDMABASER = (uint32_t)p_data;
  SDMMC_SET_IDMACTRL(p_instance, SDMMC_ENABLE_IDMA_SINGLE_BUFF);

  if (blocks_nbr > 1U)
  {
    hmmc->context = (SDMMC_CONTEXT_READ_MULTIPLE_BLOCK | SDMMC_CONTEXT_DMA);
    cmd_type = SDMMC_CMD_READ_MULT_BLOCK;
  }
  else
  {
    hmmc->context = (SDMMC_CONTEXT_READ_SINGLE_BLOCK | SDMMC_CONTEXT_DMA);
    cmd_type = SDMMC_CMD_READ_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendReadBlocksCmd(p_instance, addr, cmd_type);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes = error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_ENABLE_IT(p_instance, (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_RXOVERR | SDMMC_IT_DATAEND));

  return HAL_OK;
}

/**
  * @brief Write block(s) to a specified address in a card. The Data transfer is managed by DMA mode.
  * @param hmmc       Pointer to a hal_mmc_handle_t structure.
  * @param p_data     Pointer to the buffer that must contain the data to transmit.
  * @param block_addr Block Address where data must be written.
  * @param blocks_nbr Number of blocks to write.
  * @warning This API must be followed by a check on the card state through HAL_MMC_GetCardState().
  * @warning It could also check the DMA transfer process through the MMC Tx interrupt event.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_WriteBlocks_DMA(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr)
{
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t error_code;
  uint32_t addr = block_addr;
  uint32_t cmd_type;
  SDMMC_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hmmc->mmc_card_info.logical_block_nbr);
  ASSERT_DBG_PARAM(IS_MMC_DATA_SECTOR_SIZE(hmmc->data_sector_size, addr, blocks_nbr));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || ((addr + blocks_nbr) > hmmc->mmc_card_info.logical_block_nbr))
  {
    return HAL_INVALID_PARAM;
  }

  if ((hmmc->data_sector_size != 0x0U) && (((addr % 8U) != 0U) || ((blocks_nbr % 8U) != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  SDMMC_CLEAR_DCTRL(p_instance);

  hmmc->p_xfer_buff = (uint32_t *)(uint32_t)p_data;
  hmmc->xfer_size_byte = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;

  if ((hmmc->mmc_card_type) != SDMMC_MMC_CARD_HC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);
  MMC_GET_INSTANCE(hmmc)->IDMABASER = (uint32_t)p_data;
  SDMMC_SET_IDMACTRL(p_instance, SDMMC_ENABLE_IDMA_SINGLE_BUFF);

  if (blocks_nbr > 1U)
  {
    hmmc->context = (SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK | SDMMC_CONTEXT_DMA);
    cmd_type = SDMMC_CMD_WRITE_MULT_BLOCK;
  }
  else
  {
    hmmc->context = (SDMMC_CONTEXT_WRITE_SINGLE_BLOCK | SDMMC_CONTEXT_DMA);
    cmd_type = SDMMC_CMD_WRITE_SINGLE_BLOCK;
  }

  error_code = SDMMC_SendWriteBlocksCmd(p_instance, addr, cmd_type);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_ENABLE_IT(p_instance, (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR | SDMMC_IT_DATAEND));

  return HAL_OK;
}

#if defined (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1)
/**
  * @brief Read block(s) from a specified address in a card. The received Data must be stored in linked list buffers.
  * @param hmmc          Pointer to a hal_mmc_handle_t structure.
  * @param block_addr    Block Address from where data is to be read.
  * @param blocks_nbr    Total number of blocks to read.
  * @param p_q           Pointer to a hal_q_t structure that contains the configuration information for the Q.
  * @note  linked list must be prepared before calling this function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_ReadBlocks_LinkedList(hal_mmc_handle_t *hmmc, uint32_t block_addr, uint32_t blocks_nbr,
                                           const hal_q_t *p_q)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t dma_base0_reg;
  uint32_t dma_base1_reg;
  uint32_t error_code;
  uint32_t addr = block_addr;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hmmc->mmc_card_info.logical_block_nbr);
  ASSERT_DBG_PARAM(IS_MMC_DATA_SECTOR_SIZE(hmmc->data_sector_size, addr, blocks_nbr));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_q == NULL) || ((addr + blocks_nbr) > hmmc->mmc_card_info.logical_block_nbr))
  {
    return HAL_INVALID_PARAM;
  }

  if ((hmmc->data_sector_size != 0x0U) && (((addr % 8U) != 0U) || ((blocks_nbr % 8U) != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_instance = MMC_GET_INSTANCE(hmmc);

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance->IDMABASER = ((hal_mmc_node_t *)p_q->p_head_node)->idma_buffer_base_addr;
  p_instance->IDMABSIZER = ((hal_mmc_node_t *)p_q->p_head_node)->idma_buffer_size;
  p_instance->IDMABAR   = (uint32_t)p_q->p_head_node;
  p_instance->IDMALAR   = ((hal_mmc_node_t *)p_q->p_head_node)->idma_node_offset;

  dma_base0_reg = p_instance->IDMABASER;
  dma_base1_reg = p_instance->IDMABAR;

  if ((p_instance->IDMABSIZER == 0U) || (dma_base0_reg == 0U) || (dma_base1_reg == 0U))
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes = HAL_MMC_ERROR_ADDR_OUT_OF_RANGE;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  SDMMC_CLEAR_DCTRL(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);

#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
  hmmc->last_error_codes = HAL_MMC_ERROR_NONE;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
  hmmc->global_state = HAL_MMC_STATE_ACTIVE;

  if ((hmmc->mmc_card_type) != SDMMC_MMC_CARD_HC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);

  SDMMC_FIFORST_ENABLE(MMC_GET_INSTANCE(hmmc));
  SDMMC_CMDTRANS_ENABLE(MMC_GET_INSTANCE(hmmc));
  SDMMC_SET_IDMACTRL(MMC_GET_INSTANCE(hmmc), SDMMC_ENABLE_IDMA_DOUBLE_BUFF0);

  hmmc->context = (SDMMC_CONTEXT_READ_MULTIPLE_BLOCK | SDMMC_CONTEXT_DMA);

  error_code = SDMMC_SendReadBlocksCmd(p_instance, addr, SDMMC_CMD_READ_MULT_BLOCK);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    hmmc->global_state = HAL_MMC_STATE_IDLE;
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  SDMMC_ENABLE_IT(MMC_GET_INSTANCE(hmmc), (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_RXOVERR | SDMMC_IT_DATAEND \
                                           | SDMMC_IT_IDMABTC));

  return HAL_OK;
}

/**
  * @brief Write block(s) to a specified address in a card. The transferred Data are stored linked list nodes buffers.
  * @param hmmc       Pointer to a hal_mmc_handle_t structure.
  * @param block_addr Block Address from where data is to be read.
  * @param blocks_nbr Total number of blocks to read.
  * @param p_q        Pointer to a hal_q_t structure that contains the configuration information for the Q.
  * @note  Linked list must be prepared before calling this function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_WriteBlocks_LinkedList(hal_mmc_handle_t *hmmc, uint32_t block_addr, uint32_t blocks_nbr,
                                            const hal_q_t *p_q)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t addr = block_addr;
  uint32_t error_code;
  uint32_t dma_base0_reg;
  uint32_t dma_base1_reg;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(blocks_nbr != 0U);
  ASSERT_DBG_PARAM((addr + blocks_nbr) <= hmmc->mmc_card_info.logical_block_nbr);
  ASSERT_DBG_PARAM(IS_MMC_DATA_SECTOR_SIZE(hmmc->data_sector_size, addr, blocks_nbr));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_q == NULL) || ((addr + blocks_nbr) > hmmc->mmc_card_info.logical_block_nbr))
  {
    return HAL_INVALID_PARAM;
  }

  if ((hmmc->data_sector_size != 0x0U) && (((addr % 8U) != 0U) || ((blocks_nbr % 8U) != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_instance = MMC_GET_INSTANCE(hmmc);

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance->IDMABASER = ((hal_mmc_node_t *)p_q->p_head_node)->idma_buffer_base_addr;
  p_instance->IDMABSIZER = ((hal_mmc_node_t *)p_q->p_head_node)->idma_buffer_size;
  p_instance->IDMABAR   = (uint32_t)p_q->p_head_node;
  p_instance->IDMALAR   = ((hal_mmc_node_t *)p_q->p_head_node)->idma_node_offset;

  dma_base0_reg = p_instance->IDMABASER;
  dma_base1_reg = p_instance->IDMABAR;

  if ((p_instance->IDMABSIZER == 0U) || (dma_base0_reg == 0U) || (dma_base1_reg == 0U))
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes = HAL_MMC_ERROR_ADDR_OUT_OF_RANGE;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CLEAR_DCTRL(p_instance);

  if ((hmmc->mmc_card_type) != SDMMC_MMC_CARD_HC)
  {
    addr *= SDMMC_BLOCK_SIZE_BYTE;
  }

  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE * blocks_nbr;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);

  SDMMC_CMDTRANS_ENABLE(MMC_GET_INSTANCE(hmmc));
  SDMMC_SET_IDMACTRL(p_instance, SDMMC_ENABLE_IDMA_DOUBLE_BUFF0);

  hmmc->context = (SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK | SDMMC_CONTEXT_DMA);

  error_code = SDMMC_SendWriteBlocksCmd(p_instance, addr, SDMMC_CMD_WRITE_MULT_BLOCK);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    hmmc->global_state = HAL_MMC_STATE_IDLE;
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  SDMMC_ENABLE_IT(MMC_GET_INSTANCE(hmmc), (SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR \
                                           | SDMMC_IT_DATAEND | SDMMC_IT_IDMABTC));

  return HAL_OK;
}
#endif /* USE_HAL_MMC_LINKEDLIST */

/**
  * @brief Abort the current transfer and disable the MMC.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_BUSY    Concurrent process ongoing.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_MMC_Abort(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_ACTIVE);

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_ACTIVE, HAL_MMC_STATE_ABORT);

  p_instance  = MMC_GET_INSTANCE(hmmc);

  SDMMC_DISABLE_IT(p_instance, SDMMC_IT_DATAEND | SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR \
                   | SDMMC_IT_RXOVERR);
  SDMMC_CMDTRANS_DISABLE(p_instance);

  /** We must send the CMD12 in all cases in order to stop the data transfers.
    * In case the data transfer just finished , the external memory must not respond and must return
    * HAL_MMC_ERROR_CMD_RSP_TIMEOUT.
    * In case the data transfer aborted, the external memory must respond and must return HAL_MMC_ERROR_NONE
    * Other scenario must return HAL_ERROR.
    */
  error_code = SDMMC_SendStopTransferCmd(p_instance, hmmc->stop_xfer_timeout_ms);
  if ((error_code != HAL_MMC_ERROR_NONE) && (error_code != HAL_MMC_ERROR_CMD_RSP_TIMEOUT))
  {
#if defined (USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();
  if ((p_instance->DCTRL & SDMMC_DCTRL_DTDIR) == SDMMC_TRANSFER_DIR_TO_CARD)
  {
    if (error_code == HAL_MMC_ERROR_NONE)
    {
      while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DABORT | SDMMC_FLAG_BUSYD0END) == 0UL)
      {
        if ((HAL_GetTick() - tickstart) >= hmmc->data_timeout_cycle)
        {
          hmmc->global_state = HAL_MMC_STATE_IDLE;
          return HAL_ERROR;
        }
      }
    }
    if (error_code == HAL_MMC_ERROR_CMD_RSP_TIMEOUT)
    {
      while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DATAEND) == 0UL)
      {
        if ((HAL_GetTick() - tickstart) >= hmmc->data_timeout_cycle)
        {
          hmmc->global_state = HAL_MMC_STATE_IDLE;
          return HAL_ERROR;
        }
      }
    }
  }
  else if ((p_instance->DCTRL & SDMMC_DCTRL_DTDIR) == SDMMC_TRANSFER_DIR_TO_SDMMC)
  {
    while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DABORT | SDMMC_FLAG_DATAEND) == 0UL)
    {
      if ((HAL_GetTick() - tickstart) >= hmmc->data_timeout_cycle)
      {
        hmmc->global_state = HAL_MMC_STATE_IDLE;
        return HAL_ERROR;
      }
    }
  }
  else
  {
    /* Nothing to do */
  }

  /** The reason of all these while conditions previously is that we need to wait the SDMMC and clear the appropriate
    *  flags that must be set depending of the abort/non abort of the memory.
    *  Not waiting for the SDMMC flags must cause the next SDMMC_DISABLE_IDMA to not get cleared and must result in next
    *  SDMMC read/write operation to fail.
    */
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_FLAG_BUSYD0END);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  SDMMC_CLEAR_IDMACTRL(p_instance);

  hmmc->context = SDMMC_CONTEXT_NONE;
  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Abort the current transfer and disable the MMC (IT mode).
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_BUSY  Concurrent process ongoing.
  * @retval HAL_OK    Operation completed.
  */
hal_status_t HAL_MMC_Abort_IT(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code = HAL_MMC_ERROR_NONE;
  hal_mmc_card_state_t card_state;

  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_ACTIVE);

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_ACTIVE, HAL_MMC_STATE_ABORT);

  p_instance  = MMC_GET_INSTANCE(hmmc);

  SDMMC_DISABLE_IT(p_instance, SDMMC_IT_DATAEND | SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR \
                   | SDMMC_IT_RXOVERR);
  SDMMC_CLEAR_IDMACTRL(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);

  card_state = (hal_mmc_card_state_t)MMC_GetCardState(hmmc);

  if ((card_state == HAL_MMC_CARD_RECEIVING) || (card_state == HAL_MMC_CARD_SENDING))
  {
    error_code = SDMMC_SendStopTransferCmd(p_instance, hmmc->stop_xfer_timeout_ms);
  }
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else
  {
#if defined (USE_HAL_MMC_REGISTER_CALLBACKS) && (USE_HAL_MMC_REGISTER_CALLBACKS == 1)
    hmmc->p_abort_callback(hmmc);
#else
    HAL_MMC_AbortCallback(hmmc);
#endif /* USE_HAL_MMC_REGISTER_CALLBACKS */
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup MMC_Exported_Functions_Group4 IRQHandler and Callbacks Functions
  * @{
    This subsection provides a set of callback functions allowing to manage the data transfer from/to MMC card.
  */
/**
  * @brief This function handles MMC card interrupt request.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  */
void HAL_MMC_IRQHandler(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code;
  uint32_t context;
  hal_mmc_event_cb_t cb_event;
  uint32_t its;
  uint32_t flags;

  ASSERT_DBG_PARAM(hmmc != NULL);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  its     = SDMMC_READ_REG(p_instance, MASKR);
  flags   = SDMMC_READ_REG(p_instance, STAR);
  context = hmmc->context;

  if ((STM32_READ_BIT((flags & its), SDMMC_FLAG_RXFIFOHF) != 0U) && ((context & SDMMC_CONTEXT_IT) != 0U))
  {
    MMC_Read_IT(hmmc);
    return;
  }

  if ((STM32_READ_BIT((flags & its), SDMMC_FLAG_TXFIFOHE) != 0UL) && ((context & SDMMC_CONTEXT_IT) != 0U))
  {
    MMC_Write_IT(hmmc);
    return;
  }

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DATAEND) != 0U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_FLAG_DATAEND);
    SDMMC_DISABLE_IT(p_instance, SDMMC_IT_DATAEND | SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR \
                     | SDMMC_IT_RXOVERR | SDMMC_IT_TXFIFOHE | SDMMC_IT_RXFIFOHF);

    SDMMC_DISABLE_IT(p_instance, SDMMC_IT_IDMABTC);
    SDMMC_CMDTRANS_DISABLE(p_instance);

    if ((context & SDMMC_CONTEXT_DMA) != 0U)
    {
      SDMMC_CLEAR_DLEN(p_instance);
      SDMMC_CLEAR_DCTRL(p_instance);
      SDMMC_SET_IDMACTRL(p_instance, SDMMC_DISABLE_IDMA);
    }

    if (((context & SDMMC_CONTEXT_READ_MULTIPLE_BLOCK) != 0U) || ((context & SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK) != 0U))
    {
      error_code = SDMMC_SendStopTransferCmd(p_instance, hmmc->stop_xfer_timeout_ms);
      if (error_code != HAL_MMC_ERROR_NONE)
      {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
        hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */

#if defined (USE_HAL_MMC_REGISTER_CALLBACKS) && (USE_HAL_MMC_REGISTER_CALLBACKS == 1)
        hmmc->p_error_callback(hmmc);
#else
        HAL_MMC_ErrorCallback(hmmc);
#endif /* USE_HAL_MMC_REGISTER_CALLBACKS */
      }
    }

    if ((context & SDMMC_CONTEXT_IT) != 0U)
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    }

    if (((context & SDMMC_CONTEXT_WRITE_SINGLE_BLOCK) != 0U) || ((context & SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK) != 0U))
    {
      cb_event = HAL_MMC_EVENT_CB_TX_CPLT;
    }
    else
    {
      cb_event = HAL_MMC_EVENT_CB_RX_CPLT;
    }
    hmmc->global_state = HAL_MMC_STATE_IDLE;
#if defined (USE_HAL_MMC_REGISTER_CALLBACKS) && (USE_HAL_MMC_REGISTER_CALLBACKS == 1)
    hmmc->p_xfer_cplt_callback(hmmc, cb_event);
#else
    HAL_MMC_XferCpltCallback(hmmc, cb_event);
#endif /* USE_HAL_MMC_REGISTER_CALLBACKS */
  }

  else
  {
#if defined (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1)
    /* Handle linked-list interrupts */
    if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_IDMABTC) != 0UL)
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_IT_IDMABTC);
      if ((context & SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK) != 0U)
      {
        cb_event = HAL_MMC_EVENT_CB_TX_NODE_CPLT;
      }
      else /* SDMMC_CONTEXT_READ_MULTIPLE_BLOCK */
      {
        cb_event = HAL_MMC_EVENT_CB_RX_NODE_CPLT;
      }

#if defined (USE_HAL_MMC_REGISTER_CALLBACKS) && (USE_HAL_MMC_REGISTER_CALLBACKS == 1)
      hmmc->p_xfer_cplt_callback(hmmc, cb_event);
#else
      HAL_MMC_XferCpltCallback(hmmc, cb_event);
#endif /* USE_HAL_MMC_REGISTER_CALLBACKS */
    }
#endif /* USE_HAL_MMC_LINKEDLIST */
  }
  /* Handle Error interrupts */
  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_RXOVERR \
                           | SDMMC_FLAG_TXUNDERR) != 0U)
  {
    error_code = SDMMC_READ_REG(p_instance, STAR);
    if ((error_code & SDMMC_IT_DCRCFAIL) != 0UL)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes = HAL_MMC_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    }
    if ((error_code & SDMMC_IT_DTIMEOUT) != 0UL)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes = HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    }
    if ((error_code & SDMMC_IT_RXOVERR) != 0UL)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes = HAL_MMC_ERROR_RX_OVERRUN;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    }
    if ((error_code & SDMMC_IT_TXUNDERR) != 0UL)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes = HAL_MMC_ERROR_TX_UNDERRUN;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    }

    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    SDMMC_DISABLE_IT(p_instance, SDMMC_IT_DATAEND | SDMMC_IT_DCRCFAIL | SDMMC_IT_DTIMEOUT | SDMMC_IT_TXUNDERR \
                     | SDMMC_IT_RXOVERR);

    SDMMC_CMDTRANS_DISABLE(p_instance);
    SDMMC_FIFORST_ENABLE(p_instance);
    SDMMC_CMDSTOP_ENABLE(p_instance);
    error_code = SDMMC_SendStopTransferCmd(p_instance, hmmc->stop_xfer_timeout_ms);
    SDMMC_CMDSTOP_DISABLE(p_instance);
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_FLAG_DABORT);

    if ((context & SDMMC_CONTEXT_IT) != 0U)
    {
      hmmc->context = SDMMC_CONTEXT_NONE;
    }
    else if ((context & SDMMC_CONTEXT_DMA) != 0U)
    {
      hmmc->context = SDMMC_CONTEXT_NONE;
      /* Disable Internal DMA */
      SDMMC_DISABLE_IT(p_instance, SDMMC_IT_IDMABTC);
      SDMMC_SET_IDMACTRL(p_instance, SDMMC_DISABLE_IDMA);
      if (error_code != SDMMC_ERROR_NONE)
      {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
        hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      }
    }
    else
    {
      /* Nothing to do */
    }
    hmmc->global_state = HAL_MMC_STATE_IDLE;
#if defined (USE_HAL_MMC_REGISTER_CALLBACKS) && (USE_HAL_MMC_REGISTER_CALLBACKS == 1)
    hmmc->p_error_callback(hmmc);
#else
    HAL_MMC_ErrorCallback(hmmc);
#endif /* USE_HAL_MMC_REGISTER_CALLBACKS */
  }
}

/**
  * @brief Xfer Transfer completed callbacks.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param cb_event Xfer callback event in hal_mmc_event_cb_t structure.
  */
__weak void HAL_MMC_XferCpltCallback(hal_mmc_handle_t *hmmc, hal_mmc_event_cb_t cb_event)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hmmc);
  STM32_UNUSED(cb_event);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_MMC_XferCpltCallback can be implemented in the user file
   */
}

/**
  * @brief MMC error callbacks.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  */
__weak void HAL_MMC_ErrorCallback(hal_mmc_handle_t *hmmc)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hmmc);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_MMC_ErrorCallback can be implemented in the user file
   */
}

/**
  * @brief MMC Abort callbacks.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  */
__weak void HAL_MMC_AbortCallback(hal_mmc_handle_t *hmmc)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hmmc);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_MMC_AbortCallback can be implemented in the user file
   */
}

#if defined (USE_HAL_MMC_REGISTER_CALLBACKS) && (USE_HAL_MMC_REGISTER_CALLBACKS == 1)
/**
  * @brief Register the MMC Xfer Callback to be used instead of the weak HAL_MMC_XferCpltCallback predefined callback.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param callback Pointer to the Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_MMC_RegisterXferCpltCallback(hal_mmc_handle_t *hmmc, hal_mmc_xfer_cb_t callback)
{
  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmmc->p_xfer_cplt_callback = callback;

  return HAL_OK;
}

/**
  * @brief Register the MMC Error Callback to be used instead of the weak HAL_MMC_ErrorCallback predefined callback.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param callback Pointer to the Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_MMC_RegisterErrorCallback(hal_mmc_handle_t *hmmc, hal_mmc_cb_t callback)
{
  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmmc->p_error_callback = callback;

  return HAL_OK;
}

/**
  * @brief Register the MMC Abort Callback to be used instead of the weak HAL_MMC_AbortCallback predefined callback.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param callback Pointer to the Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_MMC_RegisterAbortCallback(hal_mmc_handle_t *hmmc, hal_mmc_cb_t callback)
{
  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmmc->p_abort_callback = callback;

  return HAL_OK;
}
#endif /* USE_HAL_MMC_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup MMC_Exported_Functions_Group5 MMC State, Error related functions
  * @{
This subsection provides a set of functions allowing to control the MMC card operations and get the related information.
  */
/**
  * @brief Get the MMC state.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval hal_mmc_state_t  Current MMC state.
  */
hal_mmc_state_t HAL_MMC_GetState(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  return hmmc->global_state;
}

#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
/**
  * @brief Return the MMC error code.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval MMC Error Code.
  */
uint32_t HAL_MMC_GetLastErrorCodes(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  return hmmc->last_error_codes;
}
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
/**
  * @}
  */

/** @addtogroup MMC_Exported_Functions_Group6 MMC User data related functions
  * @{
This subsection provides a set of functions allowing to set and get the user data.
  */
#if defined (USE_HAL_MMC_USER_DATA) && (USE_HAL_MMC_USER_DATA == 1)
/**
  * @brief Store the user data into the MMC handle.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param p_user_data Pointer to the user data.
  */
void HAL_MMC_SetUserData(hal_mmc_handle_t *hmmc, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  hmmc->p_user_data = p_user_data;
}

/**
  * @brief Retrieve the user data from the MMC handle.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval Pointer to the user data.
  */
const void *HAL_MMC_GetUserData(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  return (hmmc->p_user_data);
}
#endif /* USE_HAL_MMC_USER_DATA */
/**
  * @}
  */

/** @addtogroup MMC_Exported_Functions_Group7 MMC Card related functions
  * @{
This subsection provides a set of functions allowing to get card information.
  */
/**
  * @brief Get the current MMC card data state.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval hal_mmc_card_state_t MMC card State.
  */
hal_mmc_card_state_t HAL_MMC_GetCardState(hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  return (hal_mmc_card_state_t)(MMC_GetCardState(hmmc));
}

/**
  * @brief Get the MMC card info.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param p_card_info Pointer to the hal_mmc_card_info_t structure that must contain the MMC card status information.
  */
void HAL_MMC_GetCardInfo(const hal_mmc_handle_t *hmmc, hal_mmc_card_info_t *p_card_info)
{
  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_card_info != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  p_card_info->relative_addr           = (uint32_t)(hmmc->mmc_card_info.relative_addr);
  p_card_info->block_nbr               = (uint32_t)(hmmc->mmc_card_info.block_nbr);
  p_card_info->block_size_byte         = (uint32_t)(hmmc->mmc_card_info.block_size_byte);
  p_card_info->logical_block_nbr       = (uint32_t)(hmmc->mmc_card_info.logical_block_nbr);
  p_card_info->logical_block_size_byte = (uint32_t)(hmmc->mmc_card_info.logical_block_size_byte);
}

#if defined (USE_HAL_MMC_GET_CID) && (USE_HAL_MMC_GET_CID == 1)
/**
  * @brief Get information of the card which are stored on the CID register.
  * @param hmmc  Pointer to a hal_mmc_handle_t structure.
  * @param p_cid Pointer to a hal_mmc_card_cid_t structure that contains all CID register parameters.
  */
void HAL_MMC_GetCardCID(const hal_mmc_handle_t *hmmc, hal_mmc_card_cid_t *p_cid)
{
  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_cid != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  p_cid->manufacturer_id    = hmmc->cid.manufacturer_id;
  p_cid->oem_app_id         = hmmc->cid.oem_app_id;
  p_cid->product_name_part1 = hmmc->cid.product_name_part1;
  p_cid->product_name_part2 = hmmc->cid.product_name_part2;
  p_cid->product_rev        = hmmc->cid.product_rev;
  p_cid->product_serial_nbr = hmmc->cid.product_serial_nbr;
  p_cid->reserved1          = hmmc->cid.reserved1;
  p_cid->manufacturer_date  = hmmc->cid.manufacturer_date;
  p_cid->cid_crc            = hmmc->cid.cid_crc;
  p_cid->reserved2          = hmmc->cid.reserved2;
}
#endif /* USE_HAL_MMC_GET_CID */

#if defined (USE_HAL_MMC_GET_SPEC_VERSION) && (USE_HAL_MMC_GET_SPEC_VERSION == 1)
/**
  * @brief Get the supported specification version supported by the MMC card.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval hal_mmc_specification_version_t MMC specification version.
  */
hal_mmc_specification_version_t HAL_MMC_GetCardSpecVersion(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  return hmmc->version;
}
#endif /* USE_HAL_MMC_GET_SPEC_VERSION */
/**
  * @}
  */

/** @addtogroup MMC_Exported_Functions_Group8 Peripheral Erase management
  * @{
    This subsection provides a set of functions allowing the peripheral erase management.
  */
/**
  * @brief Perform specific commands sequence for the different type of erase.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param erase_type Specifies the type of erase to be performed.
  *                   This parameter can be one of @ref hal_mmc_erase_type_t group.
  * @param start_block_addr Start Block address.
  * @param end_block_addr End Block address.
  * @warning This API must be followed by a check on the card state through HAL_MMC_GetCardState().
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_EraseSequence(hal_mmc_handle_t *hmmc, hal_mmc_erase_type_t erase_type, uint32_t start_block_addr,
                                   uint32_t end_block_addr)
{
  uint32_t start_addr = start_block_addr;
  uint32_t end_addr   = end_block_addr;
  uint32_t tick_start;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(IS_MMC_ERASE_TYPE(erase_type));
  ASSERT_DBG_PARAM(IS_MMC_DATA_SECTOR_SIZE(hmmc->data_sector_size, start_addr, end_addr));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((end_addr < start_addr) || (end_addr > hmmc->mmc_card_info.logical_block_nbr))
  {
    return HAL_INVALID_PARAM;
  }

  if ((hmmc->data_sector_size != 0x0U) && (((start_addr % 8U) != 0U) || ((end_addr % 8U) != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  if ((hmmc->mmc_card_type) != SDMMC_MMC_CARD_HC)
  {
    start_addr *= SDMMC_BLOCK_SIZE_BYTE;
    end_addr   *= SDMMC_BLOCK_SIZE_BYTE;
  }

  if (MMC_Card_Erase(hmmc, erase_type, start_addr, end_addr) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tick_start = HAL_GetTick();
  while (MMC_GetCardState(hmmc) != (uint32_t)HAL_MMC_CARD_TRANSFER)
  {
    if ((HAL_GetTick() - tick_start) >= SDMMC_CMD_TIMEOUT)
    {
      return HAL_ERROR;
    }
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Perform sanitize operation on the device.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @warning This API must be followed by a check on the card state through HAL_MMC_GetCardState().
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_BUSY    Concurrent process ongoing.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_MMC_Sanitize(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code;
  uint32_t response = 0U;
  uint32_t count;
  uint32_t tickstart = HAL_GetTick();

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  error_code = SDMMC_SendSwitchCmd(p_instance, SDMMC_MMC_START_SANITIZE_OPERATION);
  if (error_code == HAL_MMC_ERROR_NONE)
  {
    /* Wait that the device is ready by checking the D0 line */
    while ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_BUSYD0END) == 0UL) && (error_code == HAL_MMC_ERROR_NONE))
    {
      if ((HAL_GetTick() - tickstart) >= hmmc->erase_timeout_ms)
      {
        SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
        hmmc->global_state = HAL_MMC_STATE_IDLE;
        return HAL_TIMEOUT;
      }
    }

    SDMMC_CLEAR_FLAG(p_instance, SDMMC_FLAG_BUSYD0END);
    /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
    count = SDMMC_MAX_TRIAL;
    do
    {
      error_code = SDMMC_SendStatusCmd(p_instance, (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
      if (error_code != HAL_MMC_ERROR_NONE)
      {
        break;
      }

      response = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
      count--;
    } while (((response & MMC_CARD_BUFFER_EMPTY) == 0U) && (count != 0U));

    if ((count != 0U) && (error_code == HAL_MMC_ERROR_NONE))
    {
      if ((response & 0x80U) != 0U)
      {
        error_code = HAL_MMC_ERROR_REQUEST_NOT_APPLICABLE;
      }
    }
    else if (count == 0U)
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_TIMEOUT;
    }
    else
    {
      /* Nothing to do */
    }
  }

  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;

    return HAL_ERROR;
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Configure the Secure Removal Type (SRT) in the Extended CSD register.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param sec_removal_type Specifies the type of erase to be performed.
  *                         This parameter can be one of @ref hal_mmc_secure_removal_type_t group.
  * @warning This API must be followed by a check on the card state through HAL_MMC_GetCardState().
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_BUSY    Concurrent process ongoing.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_MMC_SetSecureRemovalType(hal_mmc_handle_t *hmmc, hal_mmc_secure_removal_type_t sec_removal_type)
{
  SDMMC_TypeDef *p_instance;
  hal_mmc_secure_removal_type_t srt;
  uint32_t error_code;
  uint32_t response = 0U;
  uint32_t count;
  uint32_t tmp;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(IS_MMC_SRT_TYPE(sec_removal_type));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  srt = HAL_MMC_GetSecureRemovalType(hmmc);
  /* Check the value passed as parameter is supported by the device */
  if (((uint32_t)sec_removal_type & (uint32_t)srt) != 0U)
  {
    /* Index : 16 - Value : secure_removal_type */
    tmp = ((uint32_t)srt) | (((STM32_POSITION_VAL((uint32_t)sec_removal_type)) << 4U));
    error_code = SDMMC_SendSwitchCmd(p_instance, (0x03100000U | ((uint32_t)tmp << 8U)));
    if (error_code == HAL_MMC_ERROR_NONE)
    {
      /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
      count = SDMMC_MAX_TRIAL;
      do
      {
        error_code = SDMMC_SendStatusCmd(p_instance, (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
        if (error_code != HAL_MMC_ERROR_NONE)
        {
          break;
        }

        response = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
        count--;
      } while (((response & MMC_CARD_BUFFER_EMPTY) == 0U) && (count != 0U));

      if ((count != 0U) && (error_code == HAL_MMC_ERROR_NONE))
      {
        if ((response & 0x80U) != 0U)
        {
          error_code = HAL_MMC_ERROR_REQUEST_NOT_APPLICABLE;
        }
      }
      else if (count == 0U)
      {
        SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
        hmmc->global_state = HAL_MMC_STATE_IDLE;
        return  HAL_TIMEOUT;
      }
      else
      {
        /* Nothing to do */
      }
    }
  }
  else
  {
    error_code = HAL_MMC_ERROR_UNSUPPORTED_FEATURE;
  }

  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return  HAL_ERROR;
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the supported values of the Secure Removal Type (SRT).
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL mmc secure removal type.
  */
hal_mmc_secure_removal_type_t HAL_MMC_GetSecureRemovalType(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  return (hal_mmc_secure_removal_type_t)hmmc->secure_removal_type;
}
/**
  * @}
  */

/** @addtogroup MMC_Exported_Functions_Group9 Peripheral low power management
  * @{
    This subsection provides a set of functions allowing the control the sleep management.
  */
/**
  * @brief Switch the device from Standby State to Sleep State.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_BUSY    Concurrent process ongoing.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_MMC_EnterCardSleepMode(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code;
  uint32_t sleep_timeout;
  uint32_t timeout;
  uint32_t count;
  uint32_t response = 0U;
  uint32_t tickstart = HAL_GetTick();

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  /* Set the power-off notification to powered-on : ext_csd[34] = 1. Host must notify before powering off the device. */
  error_code = SDMMC_SendSwitchCmd(p_instance, SDMMC_MMC_SET_PWR_OFF_NOTIF_TO_PWR_ON);
  if (error_code == HAL_MMC_ERROR_NONE)
  {
    /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
    count = SDMMC_MAX_TRIAL;
    do
    {
      error_code = SDMMC_SendStatusCmd(p_instance, (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16));
      if (error_code != HAL_MMC_ERROR_NONE)
      {
        break;
      }

      response = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
      count--;
    } while (((response & MMC_CARD_BUFFER_EMPTY) == 0U) && (count != 0U));

    if (count == 0U)
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_ERROR;
    }
    else if (error_code == HAL_MMC_ERROR_NONE)
    {
      if ((response & 0x80U) != 0U)
      {
        error_code = HAL_MMC_ERROR_UNSUPPORTED_FEATURE;
      }
      else
      {
        /* Set the power-off notification to sleep notification : ext_csd[34] = 4 */
        error_code = SDMMC_SendSwitchCmd(p_instance, SDMMC_MMC_SET_PWR_OFF_NOTIF_TO_SLEEP_NOTIF);
        if (error_code == HAL_MMC_ERROR_NONE)
        {
          /* Field SLEEP_NOTIFICATION_TIME [216] */
          sleep_timeout = hmmc->sleep_notification_timeout_ms;

          if ((sleep_timeout == 0U) || (sleep_timeout > SDMMC_MMC_S_A_TIMEOUT))
          {
            /* Max register value defined is 0x17 */
            sleep_timeout = SDMMC_MMC_S_A_TIMEOUT;
          }
          timeout = (((1UL << sleep_timeout) / 100U) + 1U);

          /* Wait that the device is ready by checking the D0 line */
          while ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_BUSYD0END) == 0UL) && (error_code == HAL_MMC_ERROR_NONE))
          {
            if ((HAL_GetTick() - tickstart) >= timeout)
            {
              SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
              hmmc->global_state = HAL_MMC_STATE_IDLE;
              return HAL_ERROR;
            }
          }

          SDMMC_CLEAR_FLAG(p_instance, SDMMC_FLAG_BUSYD0END);
          /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
          count = SDMMC_MAX_TRIAL;
          do
          {
            error_code = SDMMC_SendStatusCmd(p_instance, \
                                             (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
            if (error_code != HAL_MMC_ERROR_NONE)
            {
              break;
            }

            response = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
            count--;
          } while (((response & MMC_CARD_BUFFER_EMPTY) == 0U) && (count != 0U));

          if (count == 0U)
          {
            SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
            hmmc->global_state = HAL_MMC_STATE_IDLE;
            return HAL_ERROR;
          }
          else if (error_code == HAL_MMC_ERROR_NONE)
          {
            if ((response & 0x80U) != 0U)
            {
              error_code = HAL_MMC_ERROR_UNSUPPORTED_FEATURE;
            }
            else
            {
              /* Switch the device in stand-by mode */
              (void)SDMMC_SendSelDeselCmd(p_instance, 0U);

              /* Field S_A_TIEMOUT bit number = 217 from EXT_CSD register */
              sleep_timeout = hmmc->sleep_awake_timeout_ms;

              /* Sleep/Awake timeout_ms = 100ns * 2^S_A_TIMEOUT */
              if ((sleep_timeout == 0U) || (sleep_timeout > SDMMC_MMC_S_A_TIMEOUT))
              {
                /* Max register value defined is 0x17 which equals 838.86ms timeout */
                sleep_timeout = SDMMC_MMC_S_A_TIMEOUT;
              }
              timeout = (((1UL << sleep_timeout) / 10000U) + 1U);

              if (MMC_GetCardState(hmmc) == (uint32_t)HAL_MMC_CARD_STANDBY)
              {
                tickstart = HAL_GetTick();
                /* Send CMD5 CMD_MMC_SLEEP_AWAKE with RCA and SLEEP as argument. The bit 15 is set to 1. */
                error_code = SDMMC_MMC_SendSleepCmd(p_instance,                                                       \
                                                    (uint32_t)((((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U) \
                                                               | (0x1UL << 15U)));
                if (error_code == HAL_MMC_ERROR_NONE)
                {
                  /* Wait that the device is ready by checking the D0 line */
                  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_BUSYD0END) == 0UL)
                  {
                    if ((HAL_GetTick() - tickstart) >= timeout)
                    {
                      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
                      hmmc->global_state = HAL_MMC_STATE_IDLE;
                      return HAL_ERROR;
                    }
                  }
                  SDMMC_CLEAR_FLAG(p_instance, SDMMC_FLAG_BUSYD0END);
                }
              }
              else
              {
                error_code = HAL_MMC_ERROR_REQUEST_NOT_APPLICABLE;
              }
            }
          }
          else
          {
            /* Nothing to do */
          }
        }
      }
    }
    else
    {
      /* Nothing to do */
    }
  }

  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Exit the device from Sleep State to Standby State.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_BUSY    Concurrent process ongoing.
  * @retval HAL_OK      Operation completed.
  */
hal_status_t HAL_MMC_ExitCardSleepMode(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code;
  uint32_t sleep_timeout;
  uint32_t timeout;
  uint32_t count;
  uint32_t response = 0U;
  uint32_t tickstart = HAL_GetTick();

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  /* Field S_A_TIEMOUT [217] */
  sleep_timeout = hmmc->sleep_awake_timeout_ms;

  /* Sleep/Awake timeout_ms = 100ns * 2^S_A_TIMEOUT */
  if ((sleep_timeout == 0U) || (sleep_timeout > SDMMC_MMC_S_A_TIMEOUT))
  {
    /* Max register value defined is 0x17 */
    sleep_timeout = SDMMC_MMC_S_A_TIMEOUT;
  }
  timeout = (((1UL << sleep_timeout) / 10000U) + 1U);

  /* Send CMD5 CMD_MMC_SLEEP_AWAKE with RCA and SLEEP as argument. The bit 15 is set to 0. */
  error_code = SDMMC_MMC_SendSleepCmd(p_instance, (hmmc->mmc_card_info.relative_addr << 16U));
  if (error_code == HAL_MMC_ERROR_NONE)
  {
    /* Wait that the device is ready by checking the D0 line */
    while ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_BUSYD0END) == 0U) && (error_code == HAL_MMC_ERROR_NONE))
    {
      if ((HAL_GetTick() - tickstart) >= timeout)
      {
        SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
        hmmc->global_state = HAL_MMC_STATE_IDLE;
        return HAL_ERROR;
      }
    }

    SDMMC_CLEAR_FLAG(p_instance, SDMMC_FLAG_BUSYD0END);

    if (MMC_GetCardState(hmmc) == (uint32_t)HAL_MMC_CARD_STANDBY)
    {
      /* Switch the device in transfer mode */
      error_code = SDMMC_SendSelDeselCmd(p_instance, (hmmc->mmc_card_info.relative_addr << 16U));
      if (error_code == HAL_MMC_ERROR_NONE)
      {
        if (MMC_GetCardState(hmmc) == (uint32_t)HAL_MMC_CARD_TRANSFER)
        {
          /* Set the power-off notification to powered-on : ext_csd[34] = 1 */
          error_code = SDMMC_SendSwitchCmd(p_instance, SDMMC_MMC_SET_PWR_OFF_NOTIF_TO_PWR_ON);
          if (error_code == HAL_MMC_ERROR_NONE)
          {
            /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
            count = SDMMC_MAX_TRIAL;
            do
            {
              error_code = SDMMC_SendStatusCmd(p_instance,
                                               (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
              if (error_code != HAL_MMC_ERROR_NONE)
              {
                break;
              }

              response = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
              count--;
            } while (((response & MMC_CARD_BUFFER_EMPTY) == 0U) && (count != 0U));

            if (count == 0U)
            {
              SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
              hmmc->global_state = HAL_MMC_STATE_IDLE;
              return HAL_ERROR;
            }
            else if (error_code == HAL_MMC_ERROR_NONE)
            {
              if ((response & 0x80U) != 0U)
              {
                error_code = HAL_MMC_ERROR_UNSUPPORTED_FEATURE;
              }
            }
            else
            {
              /* Nothing to do */
            }
          }
        }
        else
        {
          error_code = HAL_MMC_ERROR_REQUEST_NOT_APPLICABLE;
        }
      }
    }
    else
    {
      error_code = HAL_MMC_ERROR_REQUEST_NOT_APPLICABLE;
    }
  }

  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup MMC_Exported_Functions_Group10 Linked-List Queue functions
  * @{
This subsection provides a set of functions allowing to manage the MMC linked-list node and queue:
- Call the function HAL_MMC_FillNodeConfig() to fill the node according to configured parameter
  within hal_mmc_node_config_t structure.
- Call the function HAL_MMC_GetNodeConfig() to get the MMC linked-list node.
- Call the function HAL_MMC_SetNodeDataBufferState() to set the MMC linked list node data buffer state.
- Call the function HAL_MMC_GetNodeDataBufferState() to get the MMC linked list node data buffer state.
  */
#if defined (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1)
/**
  * @brief Build Linked List node.
  * @param p_node     Pointer to new node to build.
  * @param p_buffer   Pointer to buffer node.
  * @param size_byte  size of the node in byte.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_FillNodeConfig(hal_mmc_node_t *p_node, void *p_buffer, uint32_t size_byte)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_buffer != NULL);
  ASSERT_DBG_PARAM(size_byte != 0U);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_buffer == NULL) || (p_node == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Configure the Link Node registers*/
  p_node->idma_buffer_base_addr = (uint32_t)p_buffer;
  p_node->idma_buffer_size      = size_byte;
  p_node->idma_node_offset      = SDMMC_IDMALAR_ULS | SDMMC_IDMALAR_ABR | SDMMC_IDMALAR_ULA;

  return HAL_OK;
}

/**
  * @brief Get the MMC node configuration.
  * @param p_node      Pointer to hal_mmc_node_t node structure.
  * @param p_buffer    Pointer to buffer node.
  * @param p_size_byte Pointer to the size of the node in byte.
  */
void HAL_MMC_GetNodeConfig(const hal_mmc_node_t *p_node, uint32_t *p_buffer, uint32_t *p_size_byte)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_buffer != NULL);
  ASSERT_DBG_PARAM(p_size_byte != NULL);

  *p_buffer = p_node->idma_buffer_base_addr;
  *p_size_byte = p_node->idma_buffer_size;
}

/**
  * @brief Set MMC linked list node data buffer state.
  * @param p_node Pointer to node.
  * @param state  Node state.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_MMC_SetNodeDataBufferState(const hal_mmc_node_t *p_node, hal_mmc_node_state_t state)
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
  * @brief Get MMC linked list node data buffer state.
  * @param p_node Pointer to node.
  * @retval HAL_MMC_DATA_BUFFER_NOT_READY MMC Data buffer node is not ready.
  * @retval HAL_MMC_DATA_BUFFER_READY     MMC Data buffer node is ready.
  */
hal_mmc_node_state_t HAL_MMC_GetNodeDataBufferState(const hal_mmc_node_t *p_node)
{
  ASSERT_DBG_PARAM(p_node != NULL);

  return (hal_mmc_node_state_t)(uint32_t)(STM32_READ_BIT(p_node->idma_node_offset, SDMMC_IDMALAR_ABR));
}
#endif /* USE_HAL_MMC_LINKEDLIST */
/**
  * @}
  */

/** @addtogroup MMC_Exported_Functions_Group11 MMC Delay Block functions
  * @{
This subsection provides a set of functions allowing to configure the delay block:
- Call HAL_MMC_SetConfigDlybDelay() to set the MMC delay block configuration.
- Call HAL_MMC_GetDlybOutputClockPhase() to get the MMC delay block output clock phase.
- Call HAL_MMC_EnableDlyb() to enable the MMC delay block peripheral.
- Call HAL_MMC_DisableDlyb() to disable MMC the delay clock peripheral.
- Call HAL_MMC_IsEnabledDlyb() to check whether the delay block peripheral is enabled or not.
  */
/**
  * @brief Set the MMC delay block configuration.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param clock_phase_value The selected output clock phase value to be stored.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    The delay is correctly set.
  */
hal_status_t HAL_MMC_SetConfigDlybDelay(const hal_mmc_handle_t *hmmc, uint32_t clock_phase_value)
{
  DLYB_TypeDef *instance;
  dlyb_state_t state;

  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, HAL_MMC_STATE_IDLE);

  instance = SDMMC_GET_DLYB_INSTANCE(MMC_GET_INSTANCE(hmmc));

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
  * @brief Get the MMC delay block output clock phase.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval uint32_t output clock phase value.
  */
uint32_t HAL_MMC_GetDlybOutputClockPhase(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  return (DLYB_GetOutputClockPhase(SDMMC_GET_DLYB_INSTANCE(MMC_GET_INSTANCE(hmmc))));
}

/**
  * @brief Calculate the MMC delay block maximum output clock phase.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param p_max_clock_phase Pointer to the variable where the maximum clock phase value to be stored.
  * @retval HAL_INVALID_PARAM Invalid p_max_clock_phase parameter.
  * @retval HAL_ERROR         The max clock phase is not correctly calculated.
  * @retval HAL_BUSY          Concurrent process ongoing.
  * @retval HAL_OK            The max clock phase is correctly calculated.
  */
hal_status_t HAL_MMC_CalculateDlybMaxClockPhase(hal_mmc_handle_t *hmmc, uint32_t *p_max_clock_phase)
{
  hal_status_t status = HAL_ERROR;
  DLYB_TypeDef *instance;
  uint32_t sel;
  uint32_t unit;
  dlyb_state_t state;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_max_clock_phase != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, HAL_MMC_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_max_clock_phase == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  instance = SDMMC_GET_DLYB_INSTANCE(MMC_GET_INSTANCE(hmmc));

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

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return status;
}

/**
  * @brief Enable the MMC delay block.
  * @param hmmc Pointer to a hal_mm_handle_t structure.
  * @retval HAL_OK The delay block is enabled.
  */
hal_status_t HAL_MMC_EnableDlyb(hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, ((uint32_t)HAL_MMC_STATE_IDLE  | (uint32_t)HAL_MMC_STATE_ACTIVE |
                                        (uint32_t)HAL_MMC_STATE_ABORT));

  DLYB_Enable(SDMMC_GET_DLYB_INSTANCE(MMC_GET_INSTANCE(hmmc)));

  return HAL_OK;
}

/**
  * @brief Disable the MMC delay block.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            The delay block is disabled.
  */
hal_status_t HAL_MMC_DisableDlyb(hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

  DLYB_Disable(SDMMC_GET_DLYB_INSTANCE(MMC_GET_INSTANCE(hmmc)));

  return HAL_OK;
}

/**
  * @brief Check if the delay block peripheral is enabled or not.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_MMC_DLYB_DISABLED Delay block is disabled.
  * @retval HAL_MMC_DLYB_ENABLED  Delay block is enabled.
  */
hal_mmc_dlyb_state_t HAL_MMC_IsEnabledDlyb(hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE \
                   | (uint32_t)HAL_MMC_STATE_ABORT);

  return (hal_mmc_dlyb_state_t)DLYB_IsEnabled(SDMMC_GET_DLYB_INSTANCE(MMC_GET_INSTANCE(hmmc)));
}
/**
  * @}
  */

#if defined (USE_HAL_MMC_RPMB_FEATURE) && (USE_HAL_MMC_RPMB_FEATURE == 1)
/** @addtogroup MMC_Exported_Functions_Group13 MMC Replay Protected Memory Block management (RPMB)
  * @{
This subsection provides a set of functions for managing the Replay Protected Memory Block (RPMB).
- Call HAL_MMC_SelectPartitionArea() to switch between area partitions.
- Call HAL_MMC_ProgramRPMBAuthenticationKey() to program the authentication keys. This is typically a one-time operation
  and must be done securely.
- Call HAL_MMC_GetRPMBWriteCounter() to retrieve the write counter value. This counter is used to prevent replay attacks
  by ensuring that each write operation has a unique counter value.
- Call HAL_MMC_ReadRPMBBlocks() to perform a read operation from RPMB area.
- Call HAL_MMC_WriteRPMBBlocks() to perform a write operation to RPMB area.
- Call HAL_MMC_GetRPMBErrorCodes() to get the RPMB error codes.
- Call HAL_MMC_GetRPMBSize() to get the RPMB partition area size in byte.
  */
/**
  * @brief Switch to the selected MMC partition.
  * @param hmmc           Pointer to a hal_mmc_handle_t structure.
  * @param area_partition The MMC partition area to be selected.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    The partition area was selected successfully.
  */
hal_status_t HAL_MMC_SelectPartitionArea(hal_mmc_handle_t *hmmc, hal_mmc_area_partition_t area_partition)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code;
  uint32_t tick_start;
  __IO uint32_t count = 0U;
  uint32_t response = 0U;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(IS_MMC_PARTITION_TYPE(area_partition));

  ASSERT_DBG_STATE(hmmc->global_state, HAL_MMC_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  error_code = SDMMC_SendSwitchCmd(p_instance, (uint32_t)area_partition);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Wait that the device is ready by checking the D0 line */
  tick_start = HAL_GetTick();
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_BUSYD0END) == 0UL)
  {
    if ((HAL_GetTick() - tick_start) >= (uint32_t)hmmc->partition_switching_timing_ms)
    {
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_ERROR;
    }
  }
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_FLAG_BUSYD0END);

  /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
  do
  {
    if (count >= SDMMC_MAX_TRIAL)
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_ERROR;
    }
    error_code = SDMMC_SendStatusCmd(p_instance, (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
    if (error_code != HAL_MMC_ERROR_NONE)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_ERROR;
    }

    response = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
    count++;
  } while ((count < SDMMC_MAX_TRIAL) && ((response & MMC_CARD_BUFFER_EMPTY) == 0U));

  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Program the authentication key within the RPMB partition.
  * @param hmmc       Pointer to a hal_mmc_handle_t structure
  * @param p_key      Pointer to the authentication key (32 bytes)
  * @param timeout_ms Timeout value in millisecond
  * @note  JEDEC RPMB key programming sequence is performed in 3 phases:
  *        Phase 1: Program one authentication key write request frame with reliable write enabled.
  *        Phase 2: Program one Result Read Request frame.
  *        Phase 3: Read one Result Read Response frame and verify result/request-response fields.
  *        The API returns HAL_ERROR if any phase fails or if the RPMB result is not operation successful.
  * @retval HAL_INVALID_PARAM Invalid p_key parameter.
  * @retval HAL_TIMEOUT       A timeout has occurred.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_MMC_ProgramRPMBAuthenticationKey(hal_mmc_handle_t *hmmc, const uint8_t *p_key, uint32_t timeout_ms)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t errorstate;
  uint32_t tickstart = HAL_GetTick();
  uint32_t count;
  uint32_t byte_count = 0;
  uint32_t data;
  uint32_t remaining_data;
  uint8_t tail_pack[12] = {0};
  const uint8_t zero_pack[4] = {0};
  const uint8_t *tempbuff;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_key != NULL);
  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_key == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);
  tail_pack[11] = 0x01;

  SDMMC_CLEAR_DCTRL(MMC_GET_INSTANCE(hmmc));

  /* Phase 1 (JEDEC RPMB): send one authentication key write request frame with reliable write. */
  /* Configure the MMC DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (MMC_Card_SetRPMBReliableWriteBlockCount(hmmc, MMC_CARD_RPMB_RELIABLE_WRITE_TYPE
                                              | MMC_CARD_RPMB_BLOCK_COUNT) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  hmmc->context = SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK;
  errorstate = SDMMC_SendWriteBlocksCmd(p_instance, 0, SDMMC_CMD_WRITE_MULT_BLOCK);
  if (errorstate != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= errorstate;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  tempbuff = zero_pack;
  remaining_data = data_ctrl.data_length;
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXUNDERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0U)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXFIFOHE) != 0U) && (remaining_data >= SDMMC_FIFO_SIZE))
    {
      for (count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
      {
        data = (uint32_t)(*tempbuff);
        tempbuff++;
        byte_count++;
        data |= ((uint32_t)(*tempbuff) << 8U);
        tempbuff++;
        byte_count++;
        data |= ((uint32_t)(*tempbuff) << 16U);
        tempbuff++;
        byte_count++;
        data |= ((uint32_t)(*tempbuff) << 24U);
        tempbuff++;
        byte_count++;
        (void)SDMMC_WriteFIFO(p_instance, data);
        if ((byte_count < MMC_CARD_RPMB_KEY_MAC_POSITION) \
            || ((byte_count < MMC_CARD_RPMB_WRITE_COUNTER_POSITION) && (byte_count >= MMC_CARD_RPMB_DATA_POSITION)))
        {
          tempbuff = zero_pack;
        }
        else if (byte_count == MMC_CARD_RPMB_KEY_MAC_POSITION)
        {
          tempbuff = p_key;
        }
        else if (byte_count == MMC_CARD_RPMB_WRITE_COUNTER_POSITION)
        {
          tempbuff = tail_pack;
        }
        else
        {
          /* Nothing to do */
        }

      }
      remaining_data -= SDMMC_FIFO_SIZE;
    }

    if (((HAL_GetTick() - tickstart) >= timeout_ms) || (timeout_ms == 0U))
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT) == 1U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL) == 1U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXUNDERR) == 1U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_TX_UNDERRUN;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else
  {
    /* Nothing to do */
  }
  SDMMC_CMDTRANS_DISABLE(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
  SDMMC_CLEAR_DCTRL(p_instance);

  /* Phase 2 (JEDEC RPMB): send one Result Read Request frame. */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (MMC_Card_SetRPMBReliableWriteBlockCount(hmmc, MMC_CARD_RPMB_BLOCK_COUNT) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  hmmc->rpmb_req = MMC_CARD_RESULT_READ_REQ;
  hmmc->remaining_data = SDMMC_BLOCK_SIZE_BYTE;

  if (MMC_Card_ProgramRPMBPacket(hmmc, NULL, 0U, 1U, NULL, timeout_ms) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  SDMMC_CMDTRANS_DISABLE(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  SDMMC_CLEAR_DCTRL(p_instance);

  /* Phase 3 (JEDEC RPMB): read one Result Read Response frame and decode operation status. */
  if (MMC_Card_SetRPMBReliableWriteBlockCount(hmmc, MMC_CARD_RPMB_BLOCK_COUNT) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Configure the MMC DPSM (Data Path State Machine) */
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  hmmc->context = SDMMC_CONTEXT_READ_MULTIPLE_BLOCK;
  errorstate = SDMMC_SendReadBlocksCmd(p_instance, 0, SDMMC_CMD_READ_MULT_BLOCK);
  if (errorstate != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= errorstate;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  byte_count = 0;
  remaining_data = data_ctrl.data_length;
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0U)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXFIFOHF) != 0U) && (remaining_data >= SDMMC_FIFO_SIZE))
    {
      for (count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
      {
        data = SDMMC_ReadFIFO(p_instance);
        if (byte_count == MMC_CARD_RPMB_RESULT_POSITION)
        {
          /* Capture tail bytes [508..511]: [8..9]=>Result, [10..11]=>Req/Resp */
          tail_pack[8] = (uint8_t)(data & 0xFFU);
          tail_pack[9] = (uint8_t)((data >> 8U) & 0xFFU);
          tail_pack[10] = (uint8_t)((data >> 16U) & 0xFFU);
          tail_pack[11] = (uint8_t)((data >> 24U) & 0xFFU);
        }
        byte_count += 4U;
      }
      remaining_data -= SDMMC_FIFO_SIZE;
    }

    if (((HAL_GetTick() - tickstart) >= timeout_ms) || (timeout_ms == 0U))
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }
  SDMMC_CMDTRANS_DISABLE(p_instance);

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT) == 1U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL) == 1U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR) == 1U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_RX_OVERRUN;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else
  {
    /* Nothing to do */
  }
  uint16_t result = (((uint16_t)tail_pack[8] << 8U) | ((uint16_t)tail_pack[9]));
  uint16_t req_resp = (((uint16_t)tail_pack[10] << 8U) | ((uint16_t)tail_pack[11]));
  /* Check result of operation */
  if ((req_resp != MMC_CARD_RPMB_AUTHENTICATION_KEY_RESPONSE) || (result != MMC_CARD_RPMB_RESULT_OPERATION_OK))
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->rpmb_error_codes |= MMC_Card_RPMBResultToErrorMask(result);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  hmmc->global_state = HAL_MMC_STATE_IDLE;
  return HAL_OK;
}

/**
  * @brief  Get the value of write counter within the RPMB partition.
  * @param  hmmc              Pointer to a hal_mmc_handle_t structure.
  * @param  p_nonce           Pointer to the value of nonce (16 bytes)
  * @param  p_write_counter   Pointer to the write counter to read (4 bytes)
  * @param  timeout_ms        Timeout value in millisecond.
  * @note   JEDEC RPMB write-counter read sequence is performed in 2 phases:
  *         Phase 1: Program one Write Counter Read Request frame (with caller nonce).
  *         Phase 2: Read one Counter Value Response frame, then verify result/request-response fields
  *                  and nonce echo before returning the counter value.
  *         The API returns HAL_ERROR if any phase fails or if response integrity checks fail.
  * @retval HAL_INVALID_PARAM Invalid p_write_counter parameter.
  * @retval HAL_TIMEOUT       A timeout has occurred.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_MMC_GetRPMBWriteCounter(hal_mmc_handle_t *hmmc, uint8_t *p_nonce, uint32_t *p_write_counter,
                                         uint32_t timeout_ms)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t errorstate;
  uint32_t tickstart = HAL_GetTick();
  uint32_t count;
  uint32_t byte_count = 0;
  uint32_t data;
  uint32_t remaining_data;
  uint16_t result;
  uint16_t req_resp;
  uint8_t tail_pack[12] = {0};
  uint8_t zero_pack[4] = {0};
  uint8_t echo_nonce[16] = {0};
  uint8_t *tempbuff;

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_nonce != NULL);
  ASSERT_DBG_PARAM(p_write_counter != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_write_counter == NULL) || (p_nonce == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  p_instance  = MMC_GET_INSTANCE(hmmc);

  SDMMC_CLEAR_DCTRL(p_instance);
  /* Phase 1 (JEDEC RPMB): send one Write Counter Read Request frame including nonce. */
  hmmc->rpmb_req = MMC_CARD_READ_WRITE_COUNTER_REQ;
  hmmc->p_nonce = p_nonce;
  hmmc->remaining_data = SDMMC_BLOCK_SIZE_BYTE;

  if (MMC_Card_SetRPMBReliableWriteBlockCount(hmmc, MMC_CARD_RPMB_BLOCK_COUNT) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Configure the MMC DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (MMC_Card_ProgramRPMBPacket(hmmc, NULL, 0U, 0U, NULL, timeout_ms) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  SDMMC_CLEAR_DCTRL(p_instance);

  /* Phase 2 (JEDEC RPMB): read one Counter Value Response frame. */
  if (MMC_Card_SetRPMBReliableWriteBlockCount(hmmc, MMC_CARD_RPMB_BLOCK_COUNT) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Configure the MMC DPSM (Data Path State Machine) */
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  hmmc->context = SDMMC_CONTEXT_READ_MULTIPLE_BLOCK;
  errorstate = SDMMC_SendReadBlocksCmd(p_instance, 0, SDMMC_CMD_READ_MULT_BLOCK);
  if (errorstate != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= errorstate;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  tempbuff = zero_pack;
  byte_count = 0;
  remaining_data = data_ctrl.data_length;
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0U)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXFIFOHF) != 0U) && (remaining_data >= SDMMC_FIFO_SIZE))
    {
      for (count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
      {
        data = SDMMC_ReadFIFO(p_instance);
        *tempbuff = (uint8_t)(data & 0xFFU);
        tempbuff++;
        byte_count++;
        *tempbuff = (uint8_t)((data >> 8U) & 0xFFU);
        tempbuff++;
        byte_count++;
        *tempbuff = (uint8_t)((data >> 16U) & 0xFFU);
        tempbuff++;
        byte_count++;
        *tempbuff = (uint8_t)((data >> 24U) & 0xFFU);
        tempbuff++;
        byte_count++;
        if (byte_count < MMC_CARD_RPMB_NONCE_POSITION)
        {
          tempbuff = zero_pack;
        }
        else if (byte_count == MMC_CARD_RPMB_NONCE_POSITION)
        {
          tempbuff = echo_nonce;
        }
        else if (byte_count == MMC_CARD_RPMB_WRITE_COUNTER_POSITION)
        {
          tempbuff = tail_pack;
        }
        else
        {
          /* Nothing to do */
        }
      }
      remaining_data -= SDMMC_FIFO_SIZE;
    }

    if (((HAL_GetTick() - tickstart) >= timeout_ms) || (timeout_ms == 0U))
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT) == 1U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL) == 1U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR) == 1U)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_RX_OVERRUN;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else
  {
    /* Nothing to do */
  }

  /* Read the RPMB operation status and response type from the received frame trailer. */
  result = (((uint16_t)tail_pack[8] << 8U) | ((uint16_t)tail_pack[9]));
  req_resp = (((uint16_t)tail_pack[10] << 8U) | ((uint16_t)tail_pack[11]));
  /* Verify response type and operation result before exposing write counter. */
  if ((req_resp != MMC_CARD_RPMB_COUNTER_VALUE_RESPONSE) || (result != MMC_CARD_RPMB_RESULT_OPERATION_OK))
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->rpmb_error_codes |= MMC_Card_RPMBResultToErrorMask(result);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Verify Nonce echo */
  for (count = 0; count < 16U; count++)
  {
    if (p_nonce[count] != echo_nonce[count])
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
      hmmc->global_state = HAL_MMC_STATE_IDLE;
      return HAL_ERROR;
    }
  }

  *p_write_counter = ((uint32_t)tail_pack[3] | ((uint32_t)tail_pack[2] << 8) | ((uint32_t)tail_pack[1] << 16) \
                      | ((uint32_t)tail_pack[0] << 24));

  /* Store the write counter in the MMC handle for use during RPMB write and read operations. */
  hmmc->counter_value = *p_write_counter;

  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Write block(s) to a specified address in the RPMB partition in polling mode.
  * @param hmmc               Pointer to a hal_mmc_handle_t structure.
  * @param p_data             Pointer to the buffer containing the data to transmit.
  * @param block_addr         Block Address where data will be written.
  * @param blocks_nbr         Number of blocks to write.
  * @param p_mac              Pointer to the authentication MAC buffer.
  * @param timeout_ms         Timeout value in millisecond.
  * @note  JEDEC RPMB authenticated write sequence is performed in 3 phases:
  *        Phase 1: Program authenticated data write request frame(s) with reliable write enabled.
  *        Phase 2: Program one Result Read Request frame.
  *        Phase 3: Read one Result Read Response frame and verify result/request-response fields.
  *        The API returns HAL_ERROR if any phase fails or if the RPMB result is not operation successful.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       A timeout has occurred.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_MMC_WriteRPMBBlocks(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr,
                                     uint32_t blocks_nbr, uint8_t *p_mac, uint32_t timeout_ms)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint16_t result;
  uint16_t req_resp;
  static uint8_t tail_response[12U];

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(p_mac != NULL);
  ASSERT_DBG_PARAM((block_addr + blocks_nbr) <= (hmmc->rpmb_partition_size_byte / SDMMC_BLOCK_SIZE_BYTE));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (p_mac == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  /* Phase 1 (JEDEC RPMB): send authenticated data write request frame(s) with reliable write. */
  hmmc->rpmb_req = MMC_CARD_AUTHENTICATED_DATA_WRITE_REQ;
  hmmc->p_nonce = 0U;
  hmmc->remaining_data = blocks_nbr * SDMMC_BLOCK_SIZE_BYTE;

  p_instance  = MMC_GET_INSTANCE(hmmc);
  SDMMC_CLEAR_DCTRL(p_instance);

  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = blocks_nbr * SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (MMC_Card_SetRPMBReliableWriteBlockCount(hmmc, (MMC_CARD_RPMB_RELIABLE_WRITE_TYPE | blocks_nbr)) != HAL_OK)
  {
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  if (MMC_Card_ProgramRPMBPacket(hmmc, p_data, block_addr, blocks_nbr, p_mac, timeout_ms) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
  SDMMC_CLEAR_DCTRL(p_instance);

  /* Phase 2 (JEDEC RPMB): send one Result Read Request frame. */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (MMC_Card_SetRPMBReliableWriteBlockCount(hmmc, MMC_CARD_RPMB_BLOCK_COUNT) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  hmmc->rpmb_req = MMC_CARD_RESULT_READ_REQ;
  hmmc->remaining_data = SDMMC_BLOCK_SIZE_BYTE;

  if (MMC_Card_ProgramRPMBPacket(hmmc, NULL, 0U, 0U, NULL, timeout_ms) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
  SDMMC_CLEAR_DCTRL(p_instance);

  /* Phase 3 (JEDEC RPMB): read one Result Read Response frame and decode operation status. */
  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (MMC_Card_SetRPMBReliableWriteBlockCount(hmmc, MMC_CARD_RPMB_BLOCK_COUNT) != HAL_OK)
  {
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  if (MMC_Card_GetRPMBWriteResponse(hmmc, tail_response, timeout_ms) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Read the RPMB operation status and response type from the received frame trailer. */
  result = (((uint16_t)tail_response[8] << 8U) | ((uint16_t)tail_response[9]));
  req_resp = (((uint16_t)tail_response[10] << 8U) | ((uint16_t)tail_response[11]));
  /* Verify response type and operation result before exposing write counter. */
  if ((req_resp != MMC_CARD_RPMB_WRITE_DATA_RESPONSE) || (result != MMC_CARD_RPMB_RESULT_OPERATION_OK))
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->rpmb_error_codes |= MMC_Card_RPMBResultToErrorMask(result);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Read block(s) from a specified address in the RPMB partition in polling mode.
  * @param hmmc               Pointer to a hal_mmc_handle_t structure.
  * @param p_data             Pointer to the buffer that will contain the data to receive.
  * @param block_addr         Block address where data will be read.
  * @param blocks_nbr         Number of blocks to read.
  * @param p_nonce            Pointer to the nonce buffer.
  * @param p_mac              Pointer to the authentication MAC buffer.
  * @param timeout_ms         Timeout value in millisecond.
  * @note  JEDEC RPMB authenticated read sequence is performed in 2 phases:
  *        Phase 1: Program one authenticated data read request frame.
  *        Phase 2: Read authenticated data response frame(s) and verify result/request-response fields.
  *        The API returns HAL_ERROR if any phase fails or if the RPMB result is not operation successful.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       A timeout has occurred.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_MMC_ReadRPMBBlocks(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr,
                                    uint8_t *p_nonce, uint8_t *p_mac, uint32_t timeout_ms)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint16_t result;
  uint16_t req_resp;
  static uint8_t tail_response[12U];

  ASSERT_DBG_PARAM(hmmc != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(p_nonce != NULL);
  ASSERT_DBG_PARAM(p_mac != NULL);
  ASSERT_DBG_PARAM((block_addr + blocks_nbr) <= (hmmc->rpmb_partition_size_byte / SDMMC_BLOCK_SIZE_BYTE));

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (p_nonce == NULL) || (p_mac == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hmmc, global_state, HAL_MMC_STATE_IDLE, HAL_MMC_STATE_ACTIVE);

  /* Phase 1 (JEDEC RPMB): send one authenticated data read request frame. */
  hmmc->rpmb_req = MMC_CARD_AUTHENTICATED_DATA_READ_REQ;
  hmmc->p_nonce = p_nonce;
  hmmc->remaining_data = SDMMC_BLOCK_SIZE_BYTE;
  p_instance  = MMC_GET_INSTANCE(hmmc);

  SDMMC_CLEAR_DCTRL(p_instance);

  /* Configure the MMC DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_CARD;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (MMC_Card_SetRPMBReliableWriteBlockCount(hmmc, MMC_CARD_RPMB_BLOCK_COUNT) != HAL_OK)
  {
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  if (MMC_Card_ProgramRPMBPacket(hmmc, NULL, block_addr, 0U, p_mac, timeout_ms) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);
  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  SDMMC_CLEAR_DCTRL(p_instance);

  /* Phase 2 (JEDEC RPMB): read authenticated data response frame(s) and decode operation status. */
  hmmc->remaining_data = blocks_nbr * SDMMC_BLOCK_SIZE_BYTE;
  /* Configure the MMC DPSM (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = blocks_nbr * SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  if (MMC_Card_SetRPMBReliableWriteBlockCount(hmmc, blocks_nbr) != HAL_OK)
  {
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  if (MMC_Card_GetRPMBReadResponse(hmmc, p_data, p_nonce, p_mac, tail_response, timeout_ms) != HAL_OK)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Check result of operation */
  result = (((uint16_t)tail_response[8] << 8U) | ((uint16_t)tail_response[9]));
  req_resp = (((uint16_t)tail_response[10] << 8U) | ((uint16_t)tail_response[11]));
  /* Check result of operation */
  if ((req_resp != MMC_CARD_RPMB_READ_DATA_RESPONSE) || (result != MMC_CARD_RPMB_RESULT_OPERATION_OK))
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
    hmmc->rpmb_error_codes |= MMC_Card_RPMBResultToErrorMask(result);
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_DATA_FLAGS);
  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Return the MMC RPMB error code.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval uint32_t MMC RPMB error code.
  */
uint32_t HAL_MMC_GetRPMBErrorCodes(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE |
                   (uint32_t)HAL_MMC_STATE_ABORT);

  return hmmc->rpmb_error_codes;
}

/**
  * @brief Return the MMC RPMB size in bytes.
  * @param hmmc             Pointer to a hal_mmc_handle_t structure.
  * @retval uint32_t MMC RPMB size.
  */
uint32_t HAL_MMC_GetRPMBSize(const hal_mmc_handle_t *hmmc)
{
  ASSERT_DBG_PARAM(hmmc != NULL);

  ASSERT_DBG_STATE(hmmc->global_state, (uint32_t)HAL_MMC_STATE_IDLE | (uint32_t)HAL_MMC_STATE_ACTIVE |
                   (uint32_t)HAL_MMC_STATE_ABORT);

  return (hmmc->rpmb_partition_size_byte);
}
/**
  * @}
  */

#endif /* USE_HAL_MMC_RPMB_FEATURE */

/**
  * @}
  */

/* Private function --------------------------------------------------------------------------------------------------*/
/** @addtogroup MMC_Private_Functions MMC Private Functions
  * @{
  */
/**
  * @brief Configure the MMC according to the default parameters.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  */
static void MMC_SetDefaultConfig(const hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  uint32_t sdmmc_clk;
  sdmmc_config_t cfg = {0U};

  p_instance  = MMC_GET_INSTANCE(hmmc);
  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq(p_instance);

  cfg.clk.clock_edge        = SDMMC_CLOCK_EDGE_RISING;
  cfg.clk.clock_power_save  = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  cfg.bus_wide              = SDMMC_BUS_WIDE_1BIT;
  cfg.hardware_flow_control = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  cfg.clk.clock_div         = (sdmmc_clk + (2U * SDMMC_MMC_INIT_FREQ) - 1U) / (2U * SDMMC_MMC_INIT_FREQ);

  SDMMC_SetConfig(p_instance, &cfg);
}

/**
  * @brief Notify MMC card after insertion.
  * @param hmmc     Pointer to a hal_mmc_handle_t structure.
  * @param p_config Pointer to a hal_mmc_config_t structure that contains the MMC configuration.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    MMC instance has been correctly configured after detection.
  */
static hal_status_t MMC_NotifyCardInsertion(hal_mmc_handle_t *hmmc, const hal_mmc_config_t *p_config)
{
  if (MMC_Card_Identify(hmmc) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (MMC_Card_EnterDataTransferMode(hmmc) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (MMC_SetConfig(hmmc, p_config) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (MMC_Card_SetBlockSize(hmmc, SDMMC_BLOCK_SIZE_BYTE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Configure the MMC according to the user parameters.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param p_config Pointer to a hal_mmc_config_t structure that contains the MMC configuration.
  * @retval HAL_ERROR MMC instance is already configured and cannot be modified.
  * @retval HAL_OK    MMC instance has been correctly configured.
  */
static hal_status_t MMC_SetConfig(hal_mmc_handle_t *hmmc, const hal_mmc_config_t *p_config)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_config_t cfg = {0};
  uint32_t response  = 0U;
  uint32_t sdmmc_clk;
  uint32_t error_code;
  hal_status_t status;
  uint32_t count;

  p_instance  = MMC_GET_INSTANCE(hmmc);
  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq(p_instance);

  if (sdmmc_clk == 0U)
  {
    return HAL_ERROR;
  }

  /*---------------------------------------------------------------------- Check and update the power class if needed */
  if ((p_instance->CLKCR & SDMMC_CLKCR_BUSSPEED) != 0U)
  {
    status = ((p_instance->CLKCR & SDMMC_CLKCR_DDR) != 0U) ?
             MMC_Card_UpdatePwrClass(hmmc, (uint32_t)p_config->bus_wide, SDMMC_SPEED_MODE_DDR) :
             MMC_Card_UpdatePwrClass(hmmc, (uint32_t)p_config->bus_wide, SDMMC_SPEED_MODE_HIGH);
  }
  else
  {
    status = MMC_Card_UpdatePwrClass(hmmc, (uint32_t)p_config->bus_wide, SDMMC_SPEED_MODE_DEFAULT);
  }

  if (status != HAL_OK)
  {
    return HAL_ERROR;
  }
  else
  {
    if (MMC_SetWideBus(hmmc, p_config->bus_wide) != HAL_OK)
    {
      return HAL_ERROR;
    }
    /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
    count = SDMMC_MAX_TRIAL;
    do
    {
      error_code = SDMMC_SendStatusCmd(p_instance, (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
      if (error_code != HAL_MMC_ERROR_NONE)
      {
        break;
      }

      response = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
      count--;
    } while (((response & MMC_CARD_BUFFER_EMPTY) == 0U) && (count != 0U));

    if ((count != 0U) && (error_code == HAL_MMC_ERROR_NONE))
    {
      if ((response & 0x80U) == 0U)
      {
        cfg.bus_wide              = (uint32_t)p_config->bus_wide;
        cfg.hardware_flow_control = (uint32_t)p_config->hw_flow_ctrl;
        cfg.clk.clock_edge        = (uint32_t)p_config->clk_cfg.clk_edge;
        cfg.clk.clock_power_save  = (uint32_t)p_config->clk_cfg.clk_power_save;
#if defined(USE_HAL_MMC_AUTO_DETECTION_FREQUENCY) && (USE_HAL_MMC_AUTO_DETECTION_FREQUENCY == 0)
        if (MMC_Card_GetClockDiv(hmmc, sdmmc_clk, p_config->clk_cfg.clk_hz, &cfg.clk.clock_div) != HAL_OK)
        {
          return HAL_ERROR;
        }

#else
        (void) MMC_Card_GetClockDiv(hmmc, sdmmc_clk, 0U, &cfg.clk.clock_div);

#endif /* USE_HAL_MMC_AUTO_DETECTION_FREQUENCY */

        /* Set MMC user configuration */
        SDMMC_SetConfig(p_instance, &cfg);
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Enables the SDMMC wide bus mode.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param wide_bus Pointer to the hal_mmc_bus_wide_t.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t MMC_SetWideBus(hal_mmc_handle_t *hmmc, hal_mmc_bus_wide_t wide_bus)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code;

  p_instance  = MMC_GET_INSTANCE(hmmc);

  if (wide_bus == HAL_MMC_BUS_WIDE_8BIT)
  {
    error_code = SDMMC_SendSwitchCmd(p_instance, SDMMC_MMC_BUS_WIDTH_8_HS);
  }
  else if (wide_bus == HAL_MMC_BUS_WIDE_4BIT)
  {
    error_code = SDMMC_SendSwitchCmd(p_instance, SDMMC_MMC_BUS_WIDTH_4_HS);
  }
  else
  {
    error_code = SDMMC_SendSwitchCmd(p_instance, SDMMC_MMC_BUS_WIDTH_1_DEFAULT_SPEED);
  }

  if (error_code != 0U)
  {
#if defined (USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Set the Block size of the MMC card.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param blk_size The block size to be set.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    MMC card has correctly set the block size.
  */
static hal_status_t MMC_Card_SetBlockSize(hal_mmc_handle_t *hmmc, uint32_t blk_size)
{
  uint32_t error_code;

  error_code = SDMMC_SendBlockLengthCmd(MMC_GET_INSTANCE(hmmc), blk_size);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(MMC_GET_INSTANCE(hmmc), SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Start the transfer mode for the MMC card.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t MMC_Card_EnterDataTransferMode(hal_mmc_handle_t *hmmc)
{
  uint32_t error_code;

  if (MMC_Card_GetCSD(hmmc) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /*----------------------------------------------------------------------------------------------- CMD13 SEND_STATUS */
  /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
  error_code = SDMMC_SendStatusCmd(MMC_GET_INSTANCE(hmmc),
                                   (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
  if (error_code != HAL_MMC_ERROR_NONE)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /*-------------------------------------------------------------------------------------------- CMD8 HS_SEND_EXT_CSD */
  if (MMC_Card_GetExtCSD(hmmc, hmmc->data_timeout_cycle) != HAL_OK)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /*----------------------------------------------------------------------------------------------- CMD13 SEND_STATUS */
  /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
  error_code = SDMMC_SendStatusCmd(MMC_GET_INSTANCE(hmmc),
                                   (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
  if (error_code != HAL_MMC_ERROR_NONE)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  if (hmmc->mmc_card_type == SDMMC_MMC_CARD_HC)
  {
    hmmc->mmc_card_info.block_nbr               = hmmc->sector_count;
    hmmc->mmc_card_info.logical_block_nbr       = hmmc->mmc_card_info.block_nbr;
    hmmc->mmc_card_info.block_size_byte         = SDMMC_BLOCK_SIZE_BYTE;
    hmmc->mmc_card_info.logical_block_size_byte = hmmc->mmc_card_info.block_size_byte;
  }

  return HAL_OK;
}

/**
  * @brief Get MMC unique card identification (CID) number.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t MMC_Card_IdentifyCID(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  p_instance  = MMC_GET_INSTANCE(hmmc);

  /*----------------------------------------------------------------------------------------------- CMD2 ALL_SEND_CID */
  if (SDMMC_SendCIDCmd(p_instance) == HAL_MMC_ERROR_NONE)
  {
    uint32_t cid[4U];

    /* Get Card identification number data */
    cid[0U] = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
    cid[1U] = SDMMC_GetResponse(p_instance, SDMMC_RESP2);
    cid[2U] = SDMMC_GetResponse(p_instance, SDMMC_RESP3);
    cid[3U] = SDMMC_GetResponse(p_instance, SDMMC_RESP4);

#if defined (USE_HAL_MMC_GET_CID) && (USE_HAL_MMC_GET_CID == 1)
    /* Store all information of the card which are stored on the CID register */
    hmmc->cid.manufacturer_id = (uint8_t)SDMMC_READ_FIELD(cid[0], SDMMC_MANUFACTURE_ID_MSK,
                                                          SDMMC_MANUFACTURE_ID_POS);

    hmmc->cid.oem_app_id = (uint16_t)SDMMC_READ_FIELD(cid[0], SDMMC_OEM_APP_ID_MSK, SDMMC_OEM_APP_ID_POS);

    hmmc->cid.product_name_part1 = SDMMC_READ_FIELD(cid[0], SDMMC_PRODUCT_NAME_PART1_MSK,
                                                    SDMMC_PRODUCT_NAME_PART1_POS);

    hmmc->cid.product_name_part2 = (uint8_t)SDMMC_READ_FIELD(cid[1], SDMMC_PRODUCT_NAME_PART2_MSK,
                                                             SDMMC_PRODUCT_NAME_PART2_POS);

    hmmc->cid.product_rev = (uint8_t)SDMMC_READ_FIELD(cid[2], SDMMC_PRODUCT_REVISION_MSK,
                                                      SDMMC_PRODUCT_REVISION_POS);

    hmmc->cid.product_serial_nbr = ((SDMMC_READ_FIELD(cid[2], SDMMC_PRODUCT_SERIAL_NBR2_MSK,
                                                      SDMMC_PRODUCT_SERIAL_NBR2_POS)) << 8U) | \
                                   (SDMMC_READ_FIELD(cid[3], SDMMC_PRODUCT_SERIAL_NBR1_MSK,
                                                     SDMMC_PRODUCT_SERIAL_NBR1_POS));

    hmmc->cid.reserved1 = (uint8_t)SDMMC_READ_FIELD(cid[3], SDMMC_RESERVED_MSK, SDMMC_RESERVED_POS);

    hmmc->cid.manufacturer_date = (uint16_t)SDMMC_READ_FIELD(cid[3], SDMMC_MANUFACTURE_DATE_MSK,
                                                             SDMMC_MANUFACTURE_DATE_POS);

    hmmc->cid.cid_crc = (uint8_t)SDMMC_READ_FIELD(cid[3], SDMMC_CID_CRC_MSK, SDMMC_CID_CRC_POS);

    hmmc->cid.reserved2 = 1U;
#else
    STM32_UNUSED(cid[1U]);
#endif /* USE_HAL_MMC_GET_CID */

  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Ask MMC card to publish a new relative address (RCA).
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t MMC_Card_IdentifyRelativeAddress(hal_mmc_handle_t *hmmc)
{
  uint16_t relative_addr = 2U;

  /* Send CMD3 SET_REL_ADDR with RCA = 2 (must be greater than 1) */
  if (SDMMC_MMC_SendRelativeAddrCmd(MMC_GET_INSTANCE(hmmc), relative_addr) != HAL_MMC_ERROR_NONE)
  {
    return HAL_ERROR;
  }

  hmmc->mmc_card_info.relative_addr = relative_addr;

  return HAL_OK;
}

/**
  * @brief Get MMC card specific data register (CSD).
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t MMC_Card_GetCSD(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code;
  uint32_t csd[4U];

  p_instance  = MMC_GET_INSTANCE(hmmc);
  /* Send CMD9 SEND_CSD with argument as card's RCA */
  error_code = SDMMC_SendCSDCmd(p_instance, (uint32_t)(hmmc->mmc_card_info.relative_addr << 16U));
  if (error_code != HAL_MMC_ERROR_NONE)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else
  {
    csd[0U] = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
    csd[1U] = SDMMC_GetResponse(p_instance, SDMMC_RESP2);
    csd[2U] = SDMMC_GetResponse(p_instance, SDMMC_RESP3);
    csd[3U] = SDMMC_GetResponse(p_instance, SDMMC_RESP4);
  }

#if defined (USE_HAL_MMC_GET_SPEC_VERSION) && (USE_HAL_MMC_GET_SPEC_VERSION == 1)
  hmmc->version = (hal_mmc_specification_version_t)(uint32_t)(SDMMC_READ_FIELD(csd[0],
                                                                               SDMMC_MMC_CARD_SYSTEM_SPEC_VERSION_MSK,
                                                                               SDMMC_MMC_CARD_SYSTEM_SPEC_VERSION_POS));
#endif /* USE_HAL_MMC_GET_SPEC_VERSION */

  error_code = SDMMC_SendSelDeselCmd(p_instance, (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
  if (error_code != HAL_MMC_ERROR_NONE)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  if (hmmc->mmc_card_type == SDMMC_MMC_CARD_LC)
  {
    hmmc->mmc_card_info.block_nbr = ((((SDMMC_READ_FIELD(csd[1], SDMMC_MMC_CARD_DEVICE_SIZE1_MSK,
                                                         SDMMC_MMC_CARD_DEVICE_SIZE1_POS)) << 2U) | \
                                      SDMMC_READ_FIELD(csd[2], SDMMC_MMC_CARD_DEVICE_SIZE2_MSK,
                                                       SDMMC_MMC_CARD_DEVICE_SIZE2_POS)) + 1U);
    hmmc->mmc_card_info.block_nbr *= (1UL << \
                                      ((((uint8_t)SDMMC_READ_FIELD(csd[2], SDMMC_MMC_CARD_DEVICE_SIZE_MUL_MSK,
                                                                   SDMMC_MMC_CARD_DEVICE_SIZE_MUL_POS)) & 0x07U) + 2U));

    hmmc->mmc_card_info.block_size_byte = (1UL << \
                                           (((uint8_t)SDMMC_READ_FIELD(csd[1], SDMMC_MMC_CARD_READ_BLOCK_LEN_MSK,
                                                                       SDMMC_MMC_CARD_READ_BLOCK_LEN_POS)) & 0x0FU));

    hmmc->mmc_card_info.logical_block_nbr = (hmmc->mmc_card_info.block_nbr) *
                                            ((hmmc->mmc_card_info.block_size_byte) / SDMMC_BLOCK_SIZE_BYTE);

    hmmc->mmc_card_info.logical_block_size_byte = SDMMC_BLOCK_SIZE_BYTE;
  }

  return HAL_OK;
}

/**
  * @brief Start the identification mode.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t MMC_Card_Identify(hal_mmc_handle_t *hmmc)
{
  if (MMC_Card_IdentifyVoltageRange(hmmc) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (MMC_Card_IdentifyCID(hmmc) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (MMC_Card_IdentifyRelativeAddress(hmmc) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Enquires cards about their operating voltage and configures clock controls and stores MMC information
  *        that must be needed in future in the MMC handle.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t MMC_Card_IdentifyVoltageRange(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code;
  uint32_t sdmmc_clk;
  uint32_t init_clock_div;
  uint32_t init_clock_hz;
  __IO uint32_t count   = 0U;
  uint32_t response     = 0U;
  uint32_t validvoltage = 0U;

  p_instance  = MMC_GET_INSTANCE(hmmc);
  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq(p_instance);

  (void)SDMMC_SET_PWR_STATE(p_instance, SDMMC_PWR_ON);

  if (sdmmc_clk == 0U)
  {
    return HAL_ERROR;
  }

  /* Wait for 1ms + 74 more cycles: required power up waiting time before starting the MMC initialization sequence */
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

  /*---------------------------------------------------------------------------------------------- CMD0 GO_IDLE_STATE */
  error_code = SDMMC_SendGoIdleStateCmd(p_instance);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /*----------------------------------------------------------------------------------------------- CMD1 SEND_OP_COND */
  while (validvoltage == 0U)
  {
    count++;
    if (count == SDMMC_MAX_VOLT_TRIAL)
    {
      return HAL_ERROR;
    }

    /* SEND CMD1 APP_CMD with voltage range as argument */
    error_code = SDMMC_SendOpConditionCmd(p_instance, MMC_VOLTAGE_RANGE);
    if (error_code != HAL_MMC_ERROR_NONE)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= HAL_MMC_ERROR_INVALID_VOLTRANGE;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      return HAL_ERROR;
    }

    response = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
    validvoltage = (((response >> 31U) == 1U) ? 1U : 0U);
  }

  /* Determine capacity using MMC access mode bits (OCR[29:30]) */
  if (((response & SDMMC_MMC_ACCESS_MODE_MSK) >> SDMMC_MMC_ACCESS_MODE_POS) == SDMMC_MMC_SECTOR_MODE)
  {
    hmmc->mmc_card_type = SDMMC_MMC_CARD_HC;
  }
  else
  {
    hmmc->mmc_card_type = SDMMC_MMC_CARD_LC;
  }

  return HAL_OK;
}

/**
  * @brief Wrap up reading in non-blocking mode.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  */
static void MMC_Read_IT(hal_mmc_handle_t *hmmc)
{
  uint32_t *p_tmp;

  p_tmp = hmmc->p_xfer_buff;
  if (hmmc->xfer_size_byte >= SDMMC_FIFO_SIZE)
  {
    for (uint32_t count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
    {
      *p_tmp = SDMMC_ReadFIFO(MMC_GET_INSTANCE(hmmc));
      p_tmp++;
    }

    hmmc->p_xfer_buff = p_tmp;
    hmmc->xfer_size_byte -= SDMMC_FIFO_SIZE;
  }
}

/**
  * @brief Wrap up writing in non-blocking mode.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  */
static void MMC_Write_IT(hal_mmc_handle_t *hmmc)
{
  uint32_t *p_tmp;

  p_tmp = hmmc->p_xfer_buff;
  if (hmmc->xfer_size_byte >= SDMMC_FIFO_SIZE)
  {
    for (uint32_t count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
    {
      (void)SDMMC_WriteFIFO(MMC_GET_INSTANCE(hmmc), *p_tmp);
      p_tmp++;
    }

    hmmc->p_xfer_buff = p_tmp;
    hmmc->xfer_size_byte -= SDMMC_FIFO_SIZE;
  }
}

/**
  * @brief Switches the MMC card to high speed mode.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param speed_mode_state Speed mode state.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t MMC_Card_SetHighSpeedMode(hal_mmc_handle_t *hmmc, uint32_t speed_mode_state)
{
  SDMMC_TypeDef *instance = MMC_GET_INSTANCE(hmmc);
  uint32_t error_code = HAL_MMC_ERROR_NONE;
  hal_status_t status;
  uint32_t response;
  uint32_t count;
  uint32_t sdmmc_clk;
  sdmmc_config_t cfg = {0};

  sdmmc_clk = HAL_RCC_SDMMC_GetKernelClkFreq((SDMMC_TypeDef *)((uint32_t)(hmmc)->instance));

  if (((instance->CLKCR & SDMMC_CLKCR_BUSSPEED) != 0U) && (speed_mode_state == MMC_CARD_SPEED_MODE_DISABLE))
  {
    status = MMC_Card_UpdatePwrClass(hmmc, (instance->CLKCR & SDMMC_CLKCR_WIDBUS), SDMMC_SPEED_MODE_DEFAULT);
    if (status == HAL_OK)
    {
      /* Index : 185 - Value : 0 */
      error_code = SDMMC_SendSwitchCmd(instance, SDMMC_MMC_TIMMING_INTERFACE_DEFAULT);
    }
  }

  if (((instance->CLKCR & SDMMC_CLKCR_BUSSPEED) == 0U) && (speed_mode_state != MMC_CARD_SPEED_MODE_DISABLE))
  {
    status = MMC_Card_UpdatePwrClass(hmmc, (instance->CLKCR & SDMMC_CLKCR_WIDBUS), SDMMC_SPEED_MODE_HIGH);
    if (status == HAL_OK)
    {
      /* Index : 185 - Value : 1 */
      error_code = SDMMC_SendSwitchCmd(instance, SDMMC_MMC_TIMMING_INTERFACE_HS);
    }
  }

  if (error_code == HAL_MMC_ERROR_NONE)
  {
    /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
    count = SDMMC_MAX_TRIAL;
    do
    {
      error_code = SDMMC_SendStatusCmd(instance, (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
      if (error_code != HAL_MMC_ERROR_NONE)
      {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
        hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
        return HAL_ERROR;
      }

      response = SDMMC_GetResponse(instance, SDMMC_RESP1);
      count--;
    } while (((response & MMC_CARD_BUFFER_EMPTY) == 0U) && (count != 0U));

    if ((count != 0U) && (error_code == HAL_MMC_ERROR_NONE))
    {
      if ((response & 0x80U) != 0U)
      {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
        hmmc->last_error_codes |= SDMMC_ERROR_UNSUPPORTED_FEATURE;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
        return HAL_ERROR;
      }
      else
      {
        SDMMC_GetConfig(instance, &cfg);
        if (speed_mode_state == MMC_CARD_SPEED_MODE_DISABLE)
        {
          STM32_CLEAR_BIT(instance->CLKCR, SDMMC_CLKCR_BUSSPEED);
        }
        else
        {
          /* High Speed Clock must be less or equal to 52MHz*/
          if (sdmmc_clk == 0U)
          {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
            hmmc->last_error_codes |= SDMMC_ERROR_INVALID_PARAMETER;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
            return HAL_ERROR;
          }
          else
          {
            if (sdmmc_clk <= SDMMC_MMC_HIGH_SPEED_FREQ)
            {
              cfg.clk.clock_div = 2;
            }
            else
            {
              cfg.clk.clock_div = (sdmmc_clk / (2U * SDMMC_MMC_HIGH_SPEED_FREQ)) + 1U;
            }
            SDMMC_SetConfig(instance, &cfg);
            STM32_SET_BIT(instance->CLKCR, SDMMC_CLKCR_BUSSPEED);
          }
        }
      }
    }
    else if (count == 0U)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= SDMMC_ERROR_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      return HAL_ERROR;
    }
    else
    {
      /* Nothing to do */
    }
  }

  return HAL_OK;
}

/**
  * @brief Switches the MMC card to Double Data Rate (DDR) mode.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param speed_mode_state Speed mode state.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t MMC_Card_SetDDRSpeedMode(hal_mmc_handle_t *hmmc, uint32_t speed_mode_state)
{
  SDMMC_TypeDef *instance = MMC_GET_INSTANCE(hmmc);
  uint32_t error_code = HAL_MMC_ERROR_NONE;
  uint32_t response;
  uint32_t count;

  if (((instance->CLKCR & SDMMC_CLKCR_DDR) != 0U) && (speed_mode_state == MMC_CARD_SPEED_MODE_DISABLE))
  {
    if ((instance->CLKCR & SDMMC_CLKCR_WIDBUS_0) != 0U)
    {
      if (MMC_Card_UpdatePwrClass(hmmc, SDMMC_BUS_WIDE_4BIT, SDMMC_SPEED_MODE_HIGH) == HAL_OK)
      {
        /* Index : 183 - Value : 1 */
        error_code = SDMMC_SendSwitchCmd(instance, SDMMC_MMC_BUS_WIDTH_4_HS);
      }
    }
    else
    {
      if (MMC_Card_UpdatePwrClass(hmmc, SDMMC_BUS_WIDE_8BIT, SDMMC_SPEED_MODE_HIGH) == HAL_OK)
      {
        /* Index : 183 - Value : 2 */
        error_code = SDMMC_SendSwitchCmd(instance, SDMMC_MMC_BUS_WIDTH_8_HS);
      }
    }
  }

  if (((instance->CLKCR & SDMMC_CLKCR_DDR) == 0U) && (speed_mode_state != MMC_CARD_SPEED_MODE_DISABLE))
  {
    if ((instance->CLKCR & SDMMC_CLKCR_WIDBUS_0) != 0U)
    {
      if (MMC_Card_UpdatePwrClass(hmmc, SDMMC_BUS_WIDE_4BIT, SDMMC_SPEED_MODE_DDR) == HAL_OK)
      {
        /* Index : 183 - Value : 5 */
        error_code = SDMMC_SendSwitchCmd(instance, SDMMC_MMC_BUS_WIDTH_4_DDR);
      }
    }
    else
    {
      if (MMC_Card_UpdatePwrClass(hmmc, SDMMC_BUS_WIDE_8BIT, SDMMC_SPEED_MODE_DDR) == HAL_OK)
      {
        /* Index : 183 - Value : 6 */
        error_code = SDMMC_SendSwitchCmd(instance, SDMMC_MMC_BUS_WIDTH_8_DDR);
      }
    }
  }

  if (error_code == HAL_MMC_ERROR_NONE)
  {
    /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
    count = SDMMC_MAX_TRIAL;
    do
    {
      error_code = SDMMC_SendStatusCmd(instance, (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
      if (error_code != HAL_MMC_ERROR_NONE)
      {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
        hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
        return HAL_ERROR;
      }

      response = SDMMC_GetResponse(instance, SDMMC_RESP1);
      count--;
    } while (((response & MMC_CARD_BUFFER_EMPTY) == 0U) && (count != 0U));

    if ((count != 0U) && (error_code == HAL_MMC_ERROR_NONE))
    {
      if ((response & 0x80U) != 0U)
      {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
        hmmc->last_error_codes |= SDMMC_ERROR_UNSUPPORTED_FEATURE;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
        return HAL_ERROR;
      }
      else
      {
        if (speed_mode_state == MMC_CARD_SPEED_MODE_DISABLE)
        {
          STM32_CLEAR_BIT(instance->CLKCR, SDMMC_CLKCR_DDR);
        }
        else
        {
          STM32_SET_BIT(instance->CLKCR, SDMMC_CLKCR_DDR);
        }
      }
    }
    else if (count == 0U)
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= SDMMC_ERROR_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      return HAL_ERROR;
    }
    else
    {
      /* Nothing to do */
    }
  }

  return HAL_OK;
}

/**
  * @brief Update the power class of the device.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param wide Wide of MMC bus.
  * @param speed Speed of the MMC bus.
  * @retval HAL_ERROR An error has occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t MMC_Card_UpdatePwrClass(hal_mmc_handle_t *hmmc, uint32_t wide, uint32_t speed)
{
  SDMMC_TypeDef *p_instance;
  uint32_t count;
  uint32_t response;
  uint32_t error_code;
  uint32_t supported_pwr_class;

  p_instance  = MMC_GET_INSTANCE(hmmc);

  if ((wide == SDMMC_BUS_WIDE_8BIT) || (wide == SDMMC_BUS_WIDE_4BIT))
  {
    /* Get the supported PowerClass field from the Extended CSD register */
    if (speed == SDMMC_SPEED_MODE_DDR)
    {
      /* Field PWR_CL_DDR_52_xxx [238 or 239] */
      supported_pwr_class = hmmc->supported_pwr_class_ddr_52;
    }
    else if (speed == SDMMC_SPEED_MODE_HIGH)
    {
      /* Field PWR_CL_52_xxx [200 or 202] */
      supported_pwr_class = hmmc->supported_pwr_class_cl_52;
    }
    else
    {
      /* Field PWR_CL_26_xxx [201 or 203] */
      supported_pwr_class = hmmc->supported_pwr_class_cl_26;
    }

    if (wide == SDMMC_BUS_WIDE_8BIT)
    {
      /* Bit [7:4]: power class for 8-bits bus configuration - Bit [3:0]: power class for 4-bits bus configuration */
      supported_pwr_class = (supported_pwr_class >> 4U);
    }

    if ((hmmc->pwr_class & 0x0FU) != ((uint8_t)supported_pwr_class & 0x0FU))
    {
      /* Need to change current power class */
      error_code = SDMMC_SendSwitchCmd(p_instance, (0x03BB0000U | ((supported_pwr_class & 0x0FU) << 8U)));

      if (error_code == HAL_MMC_ERROR_NONE)
      {
        /* While card is not ready for data and trial number for sending CMD13 is not exceeded */
        count = SDMMC_MAX_TRIAL;
        do
        {
          error_code = SDMMC_SendStatusCmd(p_instance,
                                           (uint32_t)(((uint32_t)hmmc->mmc_card_info.relative_addr) << 16U));
          if (error_code != HAL_MMC_ERROR_NONE)
          {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
            hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
            return HAL_ERROR;
          }

          response = SDMMC_GetResponse(p_instance, SDMMC_RESP1);
          count--;
        } while (((response & MMC_CARD_BUFFER_EMPTY) == 0U) && (count != 0U));

        if ((count != 0U) && (error_code == HAL_MMC_ERROR_NONE))
        {
          if ((response & 0x80U) != 0U)
          {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
            hmmc->last_error_codes |= SDMMC_ERROR_UNSUPPORTED_FEATURE;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
            return HAL_ERROR;
          }
        }
        else if (count == 0U)
        {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
          hmmc->last_error_codes |= SDMMC_ERROR_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
          return HAL_ERROR;
        }
        else
        {
          /* Nothing to do */
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Updates the handle with card information stored on the Extended CSD register.
  * @param hmmc         Pointer to a hal_mmc_handle_t structure.
  * @param timeout_ms   Timeout value in millisecond.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_OK      Operation completed.
  */
static hal_status_t MMC_Card_GetExtCSD(hal_mmc_handle_t *hmmc, uint32_t timeout_ms)
{
  SDMMC_TypeDef *p_instance;
  sdmmc_data_ctrl_t data_ctrl;
  uint32_t error_code;
  uint32_t tickstart = HAL_GetTick();
  uint32_t data;
  uint8_t idx = 0U;

  p_instance  = MMC_GET_INSTANCE(hmmc);
  SDMMC_CLEAR_DCTRL(p_instance);

  /* Configure the MMC dpsm (Data Path State Machine) */
  data_ctrl.data_timeout    = hmmc->data_timeout_cycle;
  data_ctrl.data_length     = SDMMC_BLOCK_SIZE_BYTE;
  data_ctrl.data_block_size = SDMMC_DATABLOCK_SIZE_512B;
  data_ctrl.transfer_dir    = SDMMC_TRANSFER_DIR_TO_SDMMC;
  data_ctrl.transfer_mode   = SDMMC_TRANSFER_MODE_BLOCK;
  data_ctrl.dpsm            = SDMMC_DPSM_DISABLE;
  (void)SDMMC_ConfigData(p_instance, &data_ctrl);
  SDMMC_CMDTRANS_ENABLE(p_instance);

  error_code = SDMMC_MMC_SendEXTCSDCmd(p_instance, 0);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0UL)
  {
    if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXFIFOHF) == 1UL)

    {
      for (uint32_t count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
      {
        data = SDMMC_ReadFIFO(p_instance);
        switch (idx)
        {
          case MMC_EXT_CSD_PWR_CLASS_DDR_52_FIFO_POS:
            hmmc->supported_pwr_class_ddr_52 = (uint8_t)SDMMC_READ_FIELD(data,
                                                                         SDMMC_MMC_EXT_CSD_PWR_CL_DDR_52_MSK,
                                                                         SDMMC_MMC_EXT_CSD_PWR_CL_DDR_52_POS);
            break;

          case MMC_EXT_CSD_SUPPORT_PWR_CLASS_52_26_FIFO_POS:
            hmmc->supported_pwr_class_cl_52 = (uint8_t)SDMMC_READ_FIELD(data,
                                                                        SDMMC_MMC_EXT_CSD_PWR_CL_52_MSK,
                                                                        SDMMC_MMC_EXT_CSD_PWR_CL_52_POS);
            hmmc->supported_pwr_class_cl_26 = (uint8_t)SDMMC_READ_FIELD(data,
                                                                        SDMMC_MMC_EXT_CSD_PWR_CL_26_MSK,
                                                                        SDMMC_MMC_EXT_CSD_PWR_CL_26_POS);
            break;

          case MMC_EXT_CSD_DEV_TYPE_SWITCH_TIME_FIFO_POS:
            hmmc->device_type = (uint8_t)SDMMC_READ_FIELD(data,
                                                          SDMMC_MMC_EXT_CSD_DEVICE_TYPE_MSK,
                                                          SDMMC_MMC_EXT_CSD_DEVICE_TYPE_POS);
            /* This field indicates the maximum timeout for the SWITCH command (CMD6) when switching partitions by
             * changing PARTITION_ACCESS bits in PARTITION_CONFIG field (EXT_CSD byte [179]).
             * Time is expressed in units of 10-milliseconds
             */
            hmmc->partition_switching_timing_ms = (uint16_t) \
                                                  SDMMC_READ_FIELD(data,
                                                                   SDMMC_MMC_EXT_CSD_PARTITION_SWITCH_TIME_MSK,
                                                                   SDMMC_MMC_EXT_CSD_PARTITION_SWITCH_TIME_POS) * 10U;
            break;

          case MMC_EXT_CSD_DATA_SECTOR_SIZE_FIFO_POS:
            hmmc->data_sector_size = (uint8_t)SDMMC_READ_FIELD(data,
                                                               SDMMC_MMC_EXT_CSD_DATA_SECTOR_SIZE_MSK,
                                                               SDMMC_MMC_EXT_CSD_DATA_SECTOR_SIZE_POS);
            break;

          case MMC_EXT_CSD_SECURE_REMOVAL_FIFO_POS:
            hmmc->secure_removal_type = (uint8_t)SDMMC_READ_FIELD(data,
                                                                  SDMMC_MMC_EXT_CSD_SECURE_REMOVAL_MSK,
                                                                  SDMMC_MMC_EXT_CSD_SECURE_REMOVAL_POS);
            break;

          case MMC_EXT_CSD_SLEEP_NOTIF_AWAKE_TIME_FIFO_POS:

            hmmc->sleep_notification_timeout_ms = (uint8_t)SDMMC_READ_FIELD(data,
                                                                            SDMMC_MMC_EXT_CSD_SLEEP_NOTIF_TIME_MSK,
                                                                            SDMMC_MMC_EXT_CSD_SLEEP_NOTIF_TIME_POS);
            hmmc->sleep_awake_timeout_ms = (uint8_t)SDMMC_READ_FIELD(data,
                                                                     SDMMC_MMC_EXT_CSD_S_A_TIMEOUT_MSK,
                                                                     SDMMC_MMC_EXT_CSD_S_A_TIMEOUT_POS);
            break;

          case MMC_EXT_CSD_SECTOR_COUNT_SIZE_FIFO_POS:
            hmmc->sector_count = SDMMC_READ_FIELD(data,
                                                  SDMMC_MMC_EXT_CSD_SECTOR_COUNT_SIZE_MSK,
                                                  SDMMC_MMC_EXT_CSD_SECTOR_COUNT_SIZE_POS);
            break;

          case MMC_EXT_CSD_PWR_CLASS_SIZE_FIFO_POS:
            hmmc->pwr_class = (uint8_t)SDMMC_READ_FIELD(data,
                                                        SDMMC_MMC_EXT_CSD_PWR_CLASS_SIZE_MSK,
                                                        SDMMC_MMC_EXT_CSD_PWR_CLASS_SIZE_POS);
            break;

#if defined (USE_HAL_MMC_RPMB_FEATURE) && (USE_HAL_MMC_RPMB_FEATURE == 1)
          /* The RPMB partition size is calculated from the register by using the following equation:
           *  RPMB partition size = 128kB x RPMB_SIZE_MULT
           * RPMB_SIZE_MULT bits in EXT_CSD byte [168]).
           */
          case MMC_EXT_CSD_RPMB_SIZE_MULT_FIFO_POS:
            hmmc->rpmb_partition_size_byte = (uint32_t)SDMMC_READ_FIELD(data,
                                                                        SDMMC_MMC_EXT_CSD_RPMB_SIZE_MULT_MSK,
                                                                        SDMMC_MMC_EXT_CSD_RPMB_SIZE_MULT_POS) \
                                             * 128U * 1024U;
            break;
#endif /* USE_HAL_MMC_RPMB_FEATURE */
          default:
            break;
        }
        idx++;
      }
    }

    if (((HAL_GetTick() - tickstart) >= timeout_ms) || (timeout_ms == 0U))
    {
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
      return HAL_TIMEOUT;
    }
  }

  SDMMC_CMDTRANS_DISABLE(p_instance);

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT) == 1UL)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL) == 1UL)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR) == 1UL)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_RX_OVERRUN;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
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
  * @brief Erases the specified memory area of the given MMC card.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param erase_type erase operation type.
  * @param start_block_addr Start Block address.
  * @param end_block_addr End Block address.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_OK      Operation completed.
  */
static hal_status_t MMC_Card_Erase(hal_mmc_handle_t *hmmc, hal_mmc_erase_type_t erase_type, uint32_t start_block_addr,
                                   uint32_t end_block_addr)
{
  SDMMC_TypeDef *p_instance;
  uint32_t error_code;
  uint32_t tickstart;

  p_instance  = MMC_GET_INSTANCE(hmmc);
  /* Send CMD35 MMC_ERASE_GRP_START with start address as argument */
  error_code = SDMMC_SendEraseCmd(p_instance, start_block_addr, SDMMC_CMD_ERASE_GRP_START, SDMMC_CMD_TIMEOUT);

  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Send CMD36 MMC_ERASE_GRP_END with end address as argument */
  error_code = SDMMC_SendEraseCmd(p_instance, end_block_addr, SDMMC_CMD_ERASE_GRP_END, SDMMC_CMD_TIMEOUT);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }

  /* Send CMD38 ERASE with erase type as argument */
  error_code = SDMMC_SendEraseCmd(p_instance, (uint32_t)erase_type, SDMMC_CMD_ERASE, hmmc->erase_timeout_ms);
  if (error_code != HAL_MMC_ERROR_NONE)
  {
    SDMMC_CLEAR_FLAG(p_instance, SDMMC_STATIC_FLAGS);
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= error_code;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->global_state = HAL_MMC_STATE_IDLE;
    return HAL_ERROR;
  }
  else
  {
    if ((erase_type == HAL_MMC_ERASE_SECURE) || (erase_type == HAL_MMC_ERASE_SECURE_TRIM_STEP2))
    {
      /* Wait that the device is ready by checking the D0 line */
      tickstart = HAL_GetTick();
      while ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_BUSYD0END) == 0UL) && (error_code == HAL_MMC_ERROR_NONE))
      {
        if ((HAL_GetTick() - tickstart) >= hmmc->erase_timeout_ms)
        {
          hmmc->global_state = HAL_MMC_STATE_IDLE;
          return HAL_TIMEOUT;
        }
      }
      SDMMC_CLEAR_FLAG(p_instance, SDMMC_FLAG_BUSYD0END);
    }
  }

  hmmc->global_state = HAL_MMC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Calculate the clock divide factor regarding the kernel clock and the user clock.
  * @param hmmc      Pointer to a hal_mmc_handle_t structure.
  * @param sdmmc_clk kernel clock Frequency in Hz
  * @param user_freq user frequency in Hz
  * @retval uint32_t clock factor divide.
  */
static uint32_t MMC_Card_CalculateClockDiv(const hal_mmc_handle_t *hmmc, uint32_t sdmmc_clk, uint32_t user_freq)
{
  STM32_UNUSED(hmmc);
  return ((sdmmc_clk + (2U * user_freq)  - 1U) / (2U * user_freq));
}

/**
  * @brief Get the MMC clock divide factor.
  * @param hmmc        Pointer to a hal_mmc_handle_t structure.
  * @param sdmmc_clk   kernel clock Frequency in Hz
  * @param user_freq   user frequency in Hz
  * @param p_clk_div   Pointer to clock divide factor
  * @retval HAL_ERROR  in case of an error has occurred
  * @retval HAL_OK     in case of no error has occurred.
  */
static hal_status_t MMC_Card_GetClockDiv(hal_mmc_handle_t *hmmc, uint32_t sdmmc_clk, uint32_t user_freq,
                                         uint32_t *p_clk_div)
{
#if defined(USE_HAL_MMC_AUTO_DETECTION_FREQUENCY) && (USE_HAL_MMC_AUTO_DETECTION_FREQUENCY == 1)
  STM32_UNUSED(user_freq);
  uint32_t target_freq = SDMMC_MMC_HIGH_SPEED_FREQ;
  if ((2U * SDMMC_MMC_HIGH_SPEED_FREQ) <= sdmmc_clk)
  {
    *p_clk_div = MMC_Card_CalculateClockDiv(hmmc, sdmmc_clk, target_freq);
  }
  else
  {
    *p_clk_div = 0U;
  }
#else
  if (user_freq <= SDMMC_MMC_HIGH_SPEED_FREQ)
  {
    if ((2U * user_freq) <= sdmmc_clk)
    {
      *p_clk_div = MMC_Card_CalculateClockDiv(hmmc, sdmmc_clk, user_freq);
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
#endif /* USE_HAL_MMC_AUTO_DETECTION_FREQUENCY */

  return HAL_OK;
}

/**
  * @brief Get the MMC state information.
  * @param  hmmc     Pointer to a hal_sd_handle_t structure.
  * @retval uint32_t MMC card state value.
  */
static uint32_t MMC_GetCardState(hal_mmc_handle_t *hmmc)
{
  SDMMC_TypeDef *p_instance;
  uint32_t card_state;

  p_instance  = MMC_GET_INSTANCE(hmmc);
  card_state = SDMMC_SendStatusCmd(p_instance, (uint32_t)(hmmc->mmc_card_info.relative_addr << 16U));

  if (card_state != SDMMC_ERROR_NONE)
  {
    return card_state;
  }

  card_state = SDMMC_GetResponse(p_instance, SDMMC_RESP1);

  card_state = ((card_state >> 9U) & 0x0FU);

  return card_state;
}

#if defined (USE_HAL_MMC_RPMB_FEATURE) && (USE_HAL_MMC_RPMB_FEATURE == 1)
/**
  * @brief  Helper to convert raw RPMB result to a value to be ORed into the handle rpmb_error_codes.
  * @param  rpmb_result  Raw RPMB error code from card.
  * @retval error_mask   Converted error to be stored within handle.
  */
static uint16_t MMC_Card_RPMBResultToErrorMask(uint16_t rpmb_result)
{
  uint16_t error_mask = HAL_MMC_RPMB_OPERATION_OK;
  uint16_t base_result = (rpmb_result & (uint16_t)(~MMC_CARD_RPMB_RESULT_WRITE_COUNTER_EXPIRED));

  if ((rpmb_result & MMC_CARD_RPMB_RESULT_WRITE_COUNTER_EXPIRED) != 0U)
  {
    error_mask |= HAL_MMC_RPMB_WRITE_COUNTER_EXPIRED;
  }

  switch (base_result)
  {
    case MMC_CARD_RPMB_RESULT_OPERATION_OK:
      break;

    case MMC_CARD_RPMB_RESULT_GENERAL_FAILURE:
      error_mask |= HAL_MMC_RPMB_GENERAL_FAILURE;
      break;

    case MMC_CARD_RPMB_RESULT_AUTHENTICATION_FAILURE:
      error_mask |= HAL_MMC_RPMB_AUTHENTICATION_FAILURE;
      break;

    case MMC_CARD_RPMB_RESULT_COUNTER_FAILURE:
      error_mask |= HAL_MMC_RPMB_COUNTER_FAILURE;
      break;

    case MMC_CARD_RPMB_RESULT_ADDRESS_FAILURE:
      error_mask |= HAL_MMC_RPMB_ADDRESS_FAILURE;
      break;

    case MMC_CARD_RPMB_RESULT_WRITE_FAILURE:
      error_mask |= HAL_MMC_RPMB_WRITE_FAILURE;
      break;

    case MMC_CARD_RPMB_RESULT_READ_FAILURE:
      error_mask |= HAL_MMC_RPMB_READ_FAILURE;
      break;

    case MMC_CARD_RPMB_RESULT_AUTHENTICATION_KEY_NOT_PROGRAMMED:
      error_mask |= HAL_MMC_RPMB_AUTHENTICATION_KEY_NOT_PROGRAMMED;
      break;

    default:
      error_mask |= HAL_MMC_RPMB_GENERAL_FAILURE;
      break;
  }

  return error_mask;
}

/**
  * @brief Set the reliable write type of programming access in bit[31] and/or the block count value in bit [0-15].
  * @param hmmc        Pointer to a hal_mmc_handle_t structure.
  * @param block_count block count value.
  * @retval HAL_ERROR  in case of an error has occurred
  * @retval HAL_OK     in case of no error has occurred.
  */
static hal_status_t MMC_Card_SetRPMBReliableWriteBlockCount(hal_mmc_handle_t *hmmc, uint32_t block_count)
{
  uint32_t errorstate;

  errorstate = SDMMC_SendBlockCountCmd(MMC_GET_INSTANCE(hmmc), block_count);
  if (errorstate != HAL_MMC_ERROR_NONE)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= errorstate;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    hmmc->rpmb_error_codes |= HAL_MMC_RPMB_GENERAL_FAILURE;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief Program the packet data to a specified address in the RPMB area in polling mode.
  * @param hmmc         Pointer to a hal_mmc_handle_t structure.
  * @param p_data       Pointer to the buffer containing the data to transmit.
  * @param block_addr   Block Address where data will be written.
  * @param blocks_nbr   Number of blocks to write.
  * @param p_mac        Pointer to the authentication MAC buffer.
  * @param timeout_ms   Timeout value in millisecond.
  * @note  JEDEC frame-programming helper for request packets (key program, counter read,
  *        authenticated read request, authenticated write request, and result-read request).
  *        One 512-byte frame is assembled through 4 ordered sub-steps:
  *        Step 1: Stuff bytes [0..195], Step 2: Key/MAC [196..227],
  *        Step 3: Data [228..483], Step 4: Tail [484..511].
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_OK      Operation completed successfully.
  */
static hal_status_t MMC_Card_ProgramRPMBPacket(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr,
                                               uint32_t blocks_nbr, uint8_t *p_mac, uint32_t timeout_ms)
{
  SDMMC_TypeDef *p_instance;
  uint32_t errorstate;
  uint32_t count;
  uint32_t tickstart = HAL_GetTick();
  uint32_t data;
  uint32_t byte_count;
  const uint32_t *p_tmp_wbuff;

  p_instance  = MMC_GET_INSTANCE(hmmc);

  hmmc->p_rpmb_data = p_data;
  hmmc->blocks_nbr = blocks_nbr;
  hmmc->block_addr = block_addr;
  hmmc->p_mac = p_mac;
  hmmc->offset = 0U;

  MMC_Card_ProgramRPMBStuff(hmmc);
  p_tmp_wbuff = hmmc->p_xfer_buff;
  hmmc->context = SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK;
  errorstate = SDMMC_SendWriteBlocksCmd(p_instance, 0, SDMMC_CMD_WRITE_MULT_BLOCK);
  if (errorstate != HAL_MMC_ERROR_NONE)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= errorstate;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  byte_count = 0U;
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXUNDERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT
                              | SDMMC_FLAG_DATAEND) == 0U)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXFIFOHE) != 0U) && (hmmc->remaining_data != 0U))
    {
      for (count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
      {
        data = (uint32_t)(*p_tmp_wbuff);
        p_tmp_wbuff++;
        byte_count += 4U;
        (void)SDMMC_WriteFIFO(p_instance, data);
        if ((byte_count == SDMMC_BLOCK_SIZE_BYTE) && (hmmc->rpmb_next_step == MMC_CARD_RPMB_PROGRAM_STUFF_BYTES_STEP1))
        {
          byte_count = 0U;
          MMC_Card_ProgramRPMBStuff(hmmc);
          p_tmp_wbuff = hmmc->p_xfer_buff;
        }
        if ((byte_count == MMC_CARD_RPMB_KEY_MAC_POSITION)
            && (hmmc->rpmb_next_step == MMC_CARD_RPMB_PROGRAM_KEY_MAC_STEP2))
        {
          MMC_Card_ProgramRPMBMac(hmmc);
          p_tmp_wbuff = hmmc->p_xfer_buff;
        }
        if ((byte_count == MMC_CARD_RPMB_DATA_POSITION) && (hmmc->rpmb_next_step == MMC_CARD_RPMB_PROGRAM_DATA_STEP3))
        {
          MMC_Card_ProgramRPMBData(hmmc);
          p_tmp_wbuff = hmmc->p_xfer_buff;
        }
        if ((byte_count == MMC_CARD_RPMB_NONCE_POSITION) && (hmmc->rpmb_next_step == MMC_CARD_RPMB_PROGRAM_TAIL_STEP4))
        {
          MMC_Card_ProgramRPMBTail(hmmc);
          p_tmp_wbuff = hmmc->p_xfer_buff;
        }
        else
        {
          /* Nothing to do */
        }
      }
    }
    if (((HAL_GetTick() - tickstart) >= timeout_ms) || (timeout_ms == 0U))
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= errorstate;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      return HAL_TIMEOUT;
    }
  }

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT) == 1U)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL) == 1U)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_TXUNDERR) == 1U)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_TX_UNDERRUN;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else
  {
    /* Nothing to do */
  }

  return HAL_OK;
}

/**
  * @brief Get the RPMB write response.
  * @param hmmc         Pointer to a hal_mmc_handle_t structure.
  * @param p_data       Pointer to the buffer containing the data response of the programming packet.
  * @param timeout_ms   Timeout value in millisecond.
  * @note  JEDEC response helper used after a Result Read Request to fetch one
  *        Result Read Response frame and extract tail bytes [500..511]
  *        (write counter + result + request/response fields).
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_OK      Operation completed successfully.
  */
static hal_status_t MMC_Card_GetRPMBWriteResponse(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t timeout_ms)
{
  SDMMC_TypeDef *p_instance;
  uint32_t errorstate;
  uint32_t tickstart = HAL_GetTick();
  uint32_t count;
  uint32_t byte_count = 0;
  uint32_t data;
  uint32_t remaining_data;
  uint8_t zero_pack[4] = {0};
  uint8_t *p_tmp_data;

  hmmc->context = SDMMC_CONTEXT_READ_MULTIPLE_BLOCK;
  p_instance  = MMC_GET_INSTANCE(hmmc);
  errorstate = SDMMC_SendReadBlocksCmd(p_instance, 0, SDMMC_CMD_READ_MULT_BLOCK);
  if (errorstate != HAL_MMC_ERROR_NONE)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= errorstate;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  p_tmp_data = zero_pack;
  byte_count = 0;
  remaining_data = SDMMC_BLOCK_SIZE_BYTE;
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0U)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXFIFOHF) != 0U) && (remaining_data >= SDMMC_FIFO_SIZE))
    {
      for (count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
      {
        data = SDMMC_ReadFIFO(p_instance);
        *p_tmp_data = (uint8_t)(data & 0xFFU);
        p_tmp_data++;
        byte_count++;
        *p_tmp_data = (uint8_t)((data >> 8U) & 0xFFU);
        p_tmp_data++;
        byte_count++;
        *p_tmp_data = (uint8_t)((data >> 16U) & 0xFFU);
        p_tmp_data++;
        byte_count++;
        *p_tmp_data = (uint8_t)((data >> 24U) & 0xFFU);
        p_tmp_data++;
        byte_count++;
        if (byte_count < MMC_CARD_RPMB_WRITE_COUNTER_POSITION)
        {
          p_tmp_data = zero_pack;
        }
        else if (byte_count == MMC_CARD_RPMB_WRITE_COUNTER_POSITION)
        {
          p_tmp_data = p_data;
        }
        else
        {
          /* Nothing to do */
        }
      }
      remaining_data -= SDMMC_FIFO_SIZE;
    }

    if (((HAL_GetTick() - tickstart) >= timeout_ms) || (timeout_ms == 0U))
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      return HAL_TIMEOUT;
    }
  }
  SDMMC_CMDTRANS_DISABLE(p_instance);

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT) == 1U)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL) == 1U)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR) == 1U)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_RX_OVERRUN;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else
  {
    /* Nothing to do */
  }

  return HAL_OK;
}

/**
  * @brief Get the RPMB read response.
  * @param hmmc         Pointer to a hal_mmc_handle_t structure.
  * @param p_data       Pointer to the buffer that will contain the data to receive.
  * @param p_nonce      Pointer to the nonce buffer.
  * @param p_mac        Pointer to the authentication MAC buffer.
  * @param p_resp_req   Pointer to the response/request buffer.
  * @param timeout_ms   Timeout value in millisecond.
  * @note  JEDEC authenticated-read response helper.
  *        For each response frame, extracts MAC, data payload, nonce echo, and tail fields,
  *        then validates nonce echo integrity before returning HAL_OK.
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_ERROR   An error has occurred.
  * @retval HAL_OK      Operation completed successfully.
  */
static hal_status_t MMC_Card_GetRPMBReadResponse(hal_mmc_handle_t *hmmc, uint8_t *p_data, const uint8_t *p_nonce,
                                                 uint8_t *p_mac, uint8_t *p_resp_req, uint32_t timeout_ms)
{
  SDMMC_TypeDef *p_instance;
  uint32_t errorstate;
  uint32_t count;
  uint32_t byte_count;
  uint32_t data;
  uint32_t remaining_data;
  uint32_t offset = 0;
  uint32_t tickstart = HAL_GetTick();
  uint8_t zero_pack[4] = {0};
  uint8_t echo_nonce[16] = {0};
  uint8_t  *tempbuff;

  hmmc->context = SDMMC_CONTEXT_READ_MULTIPLE_BLOCK;
  p_instance  = MMC_GET_INSTANCE(hmmc);
  errorstate = SDMMC_SendReadBlocksCmd(p_instance, 0, SDMMC_CMD_READ_MULT_BLOCK);
  if (errorstate != HAL_MMC_ERROR_NONE)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= errorstate;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  tempbuff = zero_pack;
  byte_count = 0;
  remaining_data = hmmc->remaining_data;
  while (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT \
                              | SDMMC_FLAG_DATAEND) == 0U)
  {
    if ((SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXFIFOHF) != 0U) && (remaining_data >= SDMMC_FIFO_SIZE))
    {
      for (count = 0U; count < (SDMMC_FIFO_SIZE / 4U); count++)
      {
        data = SDMMC_ReadFIFO(p_instance);
        *tempbuff = (uint8_t)(data & 0xFFU);
        tempbuff++;
        byte_count++;
        *tempbuff = (uint8_t)((data >> 8U) & 0xFFU);
        tempbuff++;
        byte_count++;
        *tempbuff = (uint8_t)((data >> 16U) & 0xFFU);
        tempbuff++;
        byte_count++;
        *tempbuff = (uint8_t)((data >> 24U) & 0xFFU);
        tempbuff++;
        byte_count++;
        if (byte_count < MMC_CARD_RPMB_KEY_MAC_POSITION)
        {
          tempbuff = zero_pack;
        }
        else if (byte_count == MMC_CARD_RPMB_KEY_MAC_POSITION)
        {
          tempbuff = (uint8_t *)p_mac;
        }
        else if (byte_count == MMC_CARD_RPMB_DATA_POSITION)
        {
          tempbuff = &p_data[offset];
        }
        else if (byte_count == MMC_CARD_RPMB_NONCE_POSITION)
        {
          tempbuff = echo_nonce;
        }
        else if (byte_count == MMC_CARD_RPMB_WRITE_COUNTER_POSITION)
        {
          tempbuff = (uint8_t *)p_resp_req;
        }
        else if (byte_count == SDMMC_BLOCK_SIZE_BYTE)
        {
          byte_count = 0;
          offset += (uint32_t)256U;
        }
        else
        {
          /* Nothing to do */
        }
      }
      remaining_data -= SDMMC_FIFO_SIZE;
    }

    if (((HAL_GetTick() - tickstart) >= timeout_ms) || (timeout_ms == 0U))
    {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
      hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
      return HAL_TIMEOUT;
    }
  }
  SDMMC_CMDTRANS_DISABLE(p_instance);

  if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DTIMEOUT) == 1U)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_TIMEOUT;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_DCRCFAIL) == 1U)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_DATA_CRC_FAIL;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else if (SDMMC_IS_ACTIVE_FLAG(p_instance, SDMMC_FLAG_RXOVERR) == 1U)
  {
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
    hmmc->last_error_codes |= HAL_MMC_ERROR_RX_OVERRUN;
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
    return HAL_ERROR;
  }
  else
  {
    /* Nothing to do */
  }

  for (uint8_t i = 0; i < 16U; i++)
  {
    if (p_nonce[i] != echo_nonce[i])
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief Program the RPMB stuff.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @note  Internal packet builder Step 1: initialize Stuff bytes [0..195] to zero.
  */
static void MMC_Card_ProgramRPMBStuff(hal_mmc_handle_t *hmmc)
{
  static uint32_t tmp_data[MMC_CARD_RPMB_STUFF_SIZE_BYTE / 4U] = {0U};

  hmmc->rpmb_next_step = MMC_CARD_RPMB_PROGRAM_KEY_MAC_STEP2;
  hmmc->p_xfer_buff = tmp_data;
  hmmc->xfer_size_byte = MMC_CARD_RPMB_STUFF_SIZE_BYTE;
}

/**
  * @brief Program the RPMB Mac.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @note  Internal packet builder Step 2: place Key/MAC field [196..227]
  *        according to request type.
  */
static void MMC_Card_ProgramRPMBMac(hal_mmc_handle_t *hmmc)
{
  static uint32_t tmp_data[MMC_CARD_RPMB_KEY_MAC_SIZE_BYTE / 4U] = {0U};

  if (hmmc->rpmb_req == MMC_CARD_AUTHENTICATED_DATA_WRITE_REQ)
  {
    hmmc->p_xfer_buff = (uint32_t *)(uint32_t)hmmc->p_mac;
  }
  else /* MMC_CARD_READ_READ_COUNTER_REQ */
  {
    hmmc->p_xfer_buff = tmp_data;
  }
  hmmc->xfer_size_byte = MMC_CARD_RPMB_KEY_MAC_SIZE_BYTE;
  hmmc->rpmb_next_step = MMC_CARD_RPMB_PROGRAM_DATA_STEP3;
}

/**
  * @brief Program the RPMB data.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @note  Internal packet builder Step 3: place Data field [228..483]
  *        according to request type.
  */
static void MMC_Card_ProgramRPMBData(hal_mmc_handle_t *hmmc)
{
  static uint32_t tmp_data[MMC_CARD_RPMB_DATA_SIZE_BYTE / 4U] = {0U};

  if (hmmc->rpmb_req == MMC_CARD_AUTHENTICATED_DATA_WRITE_REQ)
  {
    hmmc->p_xfer_buff = (uint32_t *)(uint32_t)&hmmc->p_rpmb_data[hmmc->offset];
  }
  else /* MMC_CARD_READ_READ_COUNTER_REQ */
  {
    hmmc->p_xfer_buff = tmp_data;
  }
  hmmc->xfer_size_byte = MMC_CARD_RPMB_DATA_SIZE_BYTE;
  hmmc->rpmb_next_step = MMC_CARD_RPMB_PROGRAM_TAIL_STEP4;
}

/**
  * @brief Program the RPMB tail.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @note  Internal packet builder Step 4: place Tail field [484..511]
  *        (nonce/write-counter/address/block-count/result-request).
  */
static void MMC_Card_ProgramRPMBTail(hal_mmc_handle_t *hmmc)
{
  static uint32_t tmp_data[7U] = {0U};

  if (hmmc->rpmb_req == MMC_CARD_AUTHENTICATED_DATA_WRITE_REQ)
  {
    /* tmp_data[0..3]: Nonce field not used for authenticated write request. */
    tmp_data[0] = 0U;
    tmp_data[1] = 0U;
    tmp_data[2] = 0U;
    tmp_data[3] = 0U;

    /* tmp_data[4]: Write counter field. */
    tmp_data[4] = (uint32_t)((hmmc->counter_value) & 0xFFU) << 24U;
    tmp_data[4] |= ((uint32_t)(hmmc->counter_value >> 8) & 0xFFU) << 16U;
    tmp_data[4] |= ((uint32_t)(hmmc->counter_value >> 16) & 0xFFU) << 8U;
    tmp_data[4] |= ((uint32_t)(hmmc->counter_value >> 24) & 0xFFU);

    /* tmp_data[5]: Address field in low 16 bits and block count field in high 16 bits. */
    tmp_data[5] = (((uint32_t)hmmc->block_addr >> 8U) & 0xFFU);
    tmp_data[5] |= (((uint32_t)hmmc->block_addr & 0xFFU) << 8U);
    tmp_data[5] |= ((((uint32_t)hmmc->blocks_nbr >> 8U) & 0xFFU) << 16U);
    tmp_data[5] |= (((uint32_t)hmmc->blocks_nbr & 0xFFU) << 24U);
  }
  else if (hmmc->rpmb_req == MMC_CARD_AUTHENTICATED_DATA_READ_REQ)
  {
    /* tmp_data[0..3]: Nonce field echoed back in authenticated read request. */
    for (uint8_t count = 0; count < 4U; count++)
    {
      tmp_data[count] = ((uint32_t)hmmc->p_nonce[(count * 4U)] << 24U)      |
                        ((uint32_t)hmmc->p_nonce[(count * 4U) + 1U] << 16U) |
                        ((uint32_t)hmmc->p_nonce[(count * 4U) + 2U] << 8U)  |
                        ((uint32_t)hmmc->p_nonce[(count * 4U) + 3U]);
    }

    /* tmp_data[4]: Write counter field not used for authenticated read request. */
    tmp_data[4] = 0U;
    /* tmp_data[5]: Address field in low 16 bits; block count field left cleared. */
    tmp_data[5] = (((uint32_t)hmmc->block_addr >> 8U) & 0xFFU);
    tmp_data[5] |= (((uint32_t)hmmc->block_addr & 0xFFU) << 8U);
  }
  else if (hmmc->rpmb_req == MMC_CARD_RESULT_READ_REQ)
  {
    /* tmp_data[0..3]: Nonce field not used for result read request. */
    tmp_data[0] = 0U;
    tmp_data[1] = 0U;
    tmp_data[2] = 0U;
    tmp_data[3] = 0U;
    /* tmp_data[4]: Write counter field not used for result read request. */
    tmp_data[4] = 0U;
    /* tmp_data[5]: Address and block count fields not used for result read request. */
    tmp_data[5] = 0U;
  }
  else /* MMC_CARD_READ_WRITE_COUNTER_REQ */
  {
    for (uint8_t count = 0; count < 4U; count++)
    {
      /* tmp_data[0..3]: Nonce field used to authenticate the counter read request. */
      tmp_data[count] = ((uint32_t)hmmc->p_nonce[(count * 4U)] << 24U)      |
                        ((uint32_t)hmmc->p_nonce[(count * 4U) + 1U] << 16U) |
                        ((uint32_t)hmmc->p_nonce[(count * 4U) + 2U] << 8U)  |
                        ((uint32_t)hmmc->p_nonce[(count * 4U) + 3U]);
    }

    /* tmp_data[4]: Write counter field cleared in the counter read request frame. */
    tmp_data[4] = 0U;
    /* tmp_data[5]: Address and block count fields not used for counter read request. */
    tmp_data[5] = 0U;
  }

  /* tmp_data[6]: Result field cleared and request/response field set in the last byte. */
  tmp_data[6] = ((uint32_t)hmmc->rpmb_req << 24U);

  hmmc->p_xfer_buff = tmp_data;
  hmmc->xfer_size_byte = MMC_CARD_RPMB_TAIL_SIZE_BYTE;

  if (hmmc->remaining_data != 0U)
  {
    hmmc->rpmb_next_step = MMC_CARD_RPMB_PROGRAM_STUFF_BYTES_STEP1;
    hmmc->offset += MMC_CARD_RPMB_DATA_SIZE_BYTE;
    hmmc->remaining_data -= SDMMC_BLOCK_SIZE_BYTE;
  }
}
#endif /* USE_HAL_MMC_RPMB_FEATURE */
/**
  * @}
  */

#endif /* USE_HAL_MMC_MODULE */
#endif /* SDMMC1 */

/**
  * @}
  */

/**
  * @}
  */
