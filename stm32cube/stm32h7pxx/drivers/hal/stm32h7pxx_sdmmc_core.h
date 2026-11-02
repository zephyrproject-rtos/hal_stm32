/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_sdmmc_core.h
  * @brief   Header file of SDMMC core driver module.
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
#ifndef STM32H7PXX_SDMMC_CORE_H
#define STM32H7PXX_SDMMC_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */
#if defined(SDMMC1)

/** @defgroup SDMMC_CORE SDMMC Core
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup SDMMC_CORE_Exported_Types SDMMC_CORE Exported Types
  * @{
  */

/*! SDMMC Configuration Structure definition */
typedef struct
{
  uint32_t clock_edge;            /*!< Specifies the SDMMC_CCK clock transition on which Data and Command change.
                                      This parameter can be a value of @ref SDMMC_CORE_Clock_Edge                 */
  uint32_t clock_power_save;      /*!< Specifies whether SDMMC Clock output is enabled or
                                      disabled when the bus is idle.
                                      This parameter can be a value of @ref SDMMC_CORE_Clock_Power_Save           */
  uint32_t clock_div;             /*!< Specifies the clock frequency of the SDMMC controller.
                                      This parameter can be a value between Min_Data = 0 and Max_Data = 1023      */
} sdmmc_clk_config_t;

/*! SDMMC Configuration Structure definition */
typedef struct
{
  sdmmc_clk_config_t clk;         /*!< Specifies the SDMMC clock config.                                        */
  uint32_t bus_wide;              /*!< Specifies the SDMMC bus width.
                                      This parameter can be a value of @ref SDMMC_CORE_Bus_Wide                 */
  uint32_t hardware_flow_control; /*!< Specifies whether the SDMMC hardware flow control is enabled or disabled.
                                      This parameter can be a value of @ref SDMMC_CORE_Hardware_Flow_Control    */
  uint32_t tranceiver_present;    /*!< Specifies if there is a 1V8 Transceiver/Switcher.
                                      This parameter can be a value of @ref SDMMC_CORE_TRANSCEIVER_PRESENT      */
} sdmmc_config_t;

/*! SDMMC Command Control structure */
typedef struct
{
  uint32_t argument;           /*!< Specifies the SDMMC command argument which is sent to a card as part of a command
                                    message. If a command contains an argument, it must be loaded into this register
                                    before writing the command to the command register.                               */
  uint32_t cmd_index;          /*!< Specifies the SDMMC command index. It must be Min_Data = 0 and Max_Data = 64      */
  uint32_t response;           /*!< Specifies the SDMMC response type.
                                    This parameter can be a value of @ref SDMMC_CORE_Response_Type                    */
  uint32_t wait_for_interrupt; /*!< Specifies whether SDMMC wait for interrupt request is enabled or disabled.
                                    This parameter can be a value of @ref SDMMC_CORE_Wait_Interrupt_State             */
  uint32_t cpsm;               /*!< Specifies whether SDMMC Command path state machine (CPSM) is enabled or disabled.
                                    This parameter can be a value of @ref SDMMC_CORE_CPSM_State                       */
} sdmmc_cmd_init_t;

/*! SDMMC Data Control structure */
typedef struct
{
  uint32_t data_timeout;    /*!< Specifies the data timeout period in card bus clock periods.                    */
  uint32_t data_length;     /*!< Specifies the number of data bytes to be transferred.                           */
  uint32_t data_block_size; /*!< Specifies the data block size for block transfer.
                                 This parameter can be a value of @ref SDMMC_CORE_Data_Block_Size                */
  uint32_t transfer_dir;    /*!< Specifies the data transfer direction, whether the transfer
                                 is a read or write.
                                 This parameter can be a value of @ref SDMMC_CORE_Transfer_Direction             */
  uint32_t transfer_mode;   /*!< Specifies whether data transfer is in stream or block mode.
                                 This parameter can be a value of @ref SDMMC_CORE_Transfer_Type                  */
  uint32_t dpsm;            /*!< Specifies whether SDMMC Data path state machine (DPSM) is enabled or disabled.
                                 This parameter can be a value of @ref SDMMC_CORE_DPSM_State                     */
} sdmmc_data_ctrl_t;

/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup SDMMC_CORE_Exported_Constants SDMMC CORE Exported Constants
  * @{
  */
/** @defgroup SDMMC_Block_Size_byte SDMMC Block Size byte
  * @{
  */
#define SDMMC_BLOCK_SIZE_BYTE   512U
/**
  * @}
  */

/** @defgroup SDMMC_Transceiver_state SDMMC Transceiver state
  * @{
  */
#define SDMMC_TRANSCEIVER_DISABLE  0x00 /*!< Transceiver disable */
#define SDMMC_TRANSCEIVER_ENABLE   0x01 /*!< Transceiver enable  */
#define IS_SDMMC_TRANSCEIVER(TRANSCEIVER) ((TRANSCEIVER == SDMMC_TRANSCEIVER_DISABLE) \
                                           || (TRANSCEIVER == SDMMC_TRANSCEIVER_ENABLE))
/**
  * @}
  */

/** @defgroup SDMMC_error_types SDMMC error types
  * @{
  */
#define SDMMC_ERROR_NONE                   0x00000000U /*!< No error                                                      */
#define SDMMC_ERROR_CMD_CRC_FAIL           0x00000001U /*!< Command response received (but CRC check failed)              */
#define SDMMC_ERROR_DATA_CRC_FAIL          0x00000002U /*!< Data block sent/received (CRC check failed)                   */
#define SDMMC_ERROR_CMD_RSP_TIMEOUT        0x00000004U /*!< Command response timeout                                      */
#define SDMMC_ERROR_DATA_TIMEOUT           0x00000008U /*!< Data timeout                                                  */
#define SDMMC_ERROR_TX_UNDERRUN            0x00000010U /*!< Transmit FIFO underrun                                        */
#define SDMMC_ERROR_RX_OVERRUN             0x00000020U /*!< Receive FIFO overrun                                          */
#define SDMMC_ERROR_ADDR_MISALIGNED        0x00000040U /*!< Misaligned address                                            */
#define SDMMC_ERROR_BLOCK_LEN_ERR          0x00000080U /*!< Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length   */
#define SDMMC_ERROR_ERASE_SEQ_ERR          0x00000100U /*!< An error in the sequence of erase command occurs              */
#define SDMMC_ERROR_BAD_ERASE_PARAM        0x00000200U /*!< An invalid selection for erase groups                         */
#define SDMMC_ERROR_WRITE_PROT_VIOLATION   0x00000400U /*!< Attempt to program a write protect block                      */
#define SDMMC_ERROR_LOCK_UNLOCK_FAILED     0x00000800U /*!< Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card    */
#define SDMMC_ERROR_COM_CRC_FAILED         0x00001000U /*!< CRC check of the previous command failed                      */
#define SDMMC_ERROR_ILLEGAL_CMD            0x00002000U /*!< Command is not legal for the card state                       */
#define SDMMC_ERROR_CARD_ECC_FAILED        0x00004000U /*!< Card internal ECC was applied but failed to correct the data  */
#define SDMMC_ERROR_CC_ERR                 0x00008000U /*!< Internal card controller error                                */
#define SDMMC_ERROR_GENERAL_UNKNOWN_ERR    0x00010000U /*!< General or unknown error                                      */
#define SDMMC_ERROR_STREAM_READ_UNDERRUN   0x00020000U /*!< The card could not sustain data reading in stream mode        */
#define SDMMC_ERROR_STREAM_WRITE_OVERRUN   0x00040000U /*!< The card could not sustain data programming in stream mode    */
#define SDMMC_ERROR_CID_CSD_OVERWRITE      0x00080000U /*!< CID/CSD overwrite error                                       */
#define SDMMC_ERROR_WP_ERASE_SKIP          0x00100000U /*!< Only partial address space was erased                         */
#define SDMMC_ERROR_CARD_ECC_DISABLED      0x00200000U /*!< Command has been executed without using internal ECC          */
#define SDMMC_ERROR_ERASE_RESET            0x00400000U /*!< Erase sequence was cleared before executing because an out of erase sequence command was received                        */
#define SDMMC_ERROR_AKE_SEQ_ERR            0x00800000U /*!< Error in sequence of authentication                           */
#define SDMMC_ERROR_INVALID_VOLTRANGE      0x01000000U /*!< Error in case of invalid voltage range                        */
#define SDMMC_ERROR_ADDR_OUT_OF_RANGE      0x02000000U /*!< Error when addressed block is out of range                    */
#define SDMMC_ERROR_REQUEST_NOT_APPLICABLE 0x04000000U /*!< Error when command request is not applicable                  */
#define SDMMC_ERROR_INVALID_PARAMETER      0x08000000U /*!< the used parameter is not valid                               */
#define SDMMC_ERROR_UNSUPPORTED_FEATURE    0x10000000U /*!< Error when feature is not supported                           */
#define SDMMC_ERROR_BUSY                   0x20000000U /*!< Error when transfer process is busy                           */
#define SDMMC_ERROR_DMA                    0x40000000U /*!< Error while DMA transfer                                      */
#define SDMMC_ERROR_TIMEOUT                0x80000000U /*!< Timeout error                                                 */
/**
  * @}
  */

/** @defgroup SDMMC_SDIO_Commands_Index SDMMC Commands Index
  * @{
  */
/**
  * @brief  Masks for R5 Response
  */
/** this is the reserved for future use in spec RFU */
#define SDMMC_SDIO_R5_ERROR                          ((uint32_t)0x00000400U)
/** Out of range error */
#define SDMMC_SDIO_R5_OUT_OF_RANGE                   ((uint32_t)0x00000100U)
/** Invalid function number */
#define SDMMC_SDIO_R5_INVALID_FUNCTION_NUMBER        ((uint32_t)0x00000200U)
/** General or an unknown error */
#define SDMMC_SDIO_R5_GENERAL_UNKNOWN_ERROR          ((uint32_t)0x00000800U)
/** SDIO Card current state
  * 00=DIS (card not selected)
  * 01=CMD (data line free)
  * 10=TRN (transfer on data lines) */
#define SDMMC_SDIO_R5_IO_CURRENT_STATE               ((uint32_t)0x00003000U)
/** Illegal command error */
#define SDMMC_SDIO_R5_ILLEGAL_CMD                    ((uint32_t)0x00004000U)
/** CRC check of previous cmd failed */
#define SDMMC_SDIO_R5_COM_CRC_FAILED                 ((uint32_t)0x00008000U)

#define SDMMC_SDIO_R5_ERRORBITS                      (SDMMC_SDIO_R5_COM_CRC_FAILED            \
                                                      | SDMMC_SDIO_R5_ILLEGAL_CMD             \
                                                      | SDMMC_SDIO_R5_GENERAL_UNKNOWN_ERROR   \
                                                      | SDMMC_SDIO_R5_INVALID_FUNCTION_NUMBER \
                                                      | SDMMC_SDIO_R5_OUT_OF_RANGE)
/**
  * @brief SDIO_CMD53_MODE
  */
#define SDMMC_SDIO_MODE_BYTE                         0x00U  /*!< Byte Mode  */
#define SDMMC_SDIO_MODE_BLOCK                        0x01U  /*!< Block Mode */

/**
  * @brief SDIO_CMD53_OP_CODE
  */
#define SDMMC_SDIO_NO_INC                            0x00U  /*!< No auto indentation */
#define SDMMC_SDIO_AUTO_INC                          0x01U  /*!< Auto indentation    */

/**
  * @brief SDIO_CMD53_RAW
  */
#define SDMMC_SDIO_WO                                0x00U  /*!< Write only Flag       */
#define SDMMC_SDIO_RAW                               0x01U  /*!< Read after write Flag */
/**
  * @}
  */

/** @defgroup SDMMC_Commands_Index SDMMC Commands Index
  * @{
  */
#define SDMMC_CMD_GO_IDLE_STATE        0U   /*!< Resets the SD memory card.                                                               */
#define SDMMC_CMD_SEND_OP_COND         1U   /*!< Send host capacity support information and activates the card's initialization process.  */
#define SDMMC_CMD_ALL_SEND_CID         2U   /*!< Asks any card connected to the host to send the CID numbers on the CMD line.             */
#define SDMMC_CMD_SET_REL_ADDR         3U   /*!< Asks the card to publish a new relative address (RCA).                                   */
#define SDMMC_CMD_SET_DSR              4U   /*!< Programs the DSR of all cards.                                                           */
#define SDMMC_CMD_SDMMC_SEN_OP_COND    5U   /*!< Send host capacity support information (HCS) and asks the accessed card to send its operating condition register (OCR) content in the response on the CMD line.*/
#define SDMMC_CMD_HS_SWITCH            6U   /*!< Checks switchable function (mode 0) and switch card function (mode 1).                   */
#define SDMMC_CMD_SEL_DESEL_CARD       7U   /*!< Selects the card by its own relative address and gets deselected by any other address    */
#define SDMMC_CMD_HS_SEND_EXT_CSD      8U   /*!< Send SD Memory Card interface condition, which includes host supply voltage information  and asks the card whether card supports voltage.                      */
#define SDMMC_CMD_SEND_CSD             9U   /*!< Addressed card sends its card specific data (CSD) on the CMD line.                       */
#define SDMMC_CMD_SEND_CID             10U  /*!< Addressed card sends its card identification (CID) on the CMD line.                      */
#define SDMMC_CMD_VOLTAGE_SWITCH       11U  /*!< SD card Voltage switch to 1.8V mode.                                                     */
#define SDMMC_CMD_STOP_TRANSMISSION    12U  /*!< Forces the card to stop transmission.                                                    */
#define SDMMC_CMD_SEND_STATUS          13U  /*!< Addressed card sends its status register.                                                */
#define SDMMC_CMD_HS_BUSTEST_READ      14U  /*!< Reserved                                                                                 */
#define SDMMC_CMD_GO_INACTIVE_STATE    15U  /*!< Send an addressed card into the inactive state.                                          */
#define SDMMC_CMD_SET_BLOCKLEN         16U  /*!< Sets the block length (in bytes for SDSC) for all following block commands (read, write, lock). Default block length is fixed to 512 Bytes. Not effective        */
/*!< for SDHS and SDXC.                                                                       */
#define SDMMC_CMD_READ_SINGLE_BLOCK    17U  /*!< Reads single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of fixed 512 bytes in case of SDHC and SDXC.                                    */
#define SDMMC_CMD_READ_MULT_BLOCK      18U  /*!< Continuously transfers data blocks from card to host until interrupted by  STOP_TRANSMISSION command.                                                            */
#define SDMMC_CMD_HS_BUSTEST_WRITE     19U  /*!< 64 bytes tuning pattern is sent for SDR50 and SDR104.                                    */
#define SDMMC_CMD_WRITE_DAT_UNTIL_STOP 20U  /*!< Speed class control command.                                                             */
#define SDMMC_CMD_SET_BLOCK_COUNT      23U  /*!< Specify block count for CMD18 and CMD25.                                                 */
#define SDMMC_CMD_WRITE_SINGLE_BLOCK   24U  /*!< Writes single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of fixed 512 bytes in case of SDHC and SDXC.                                   */
#define SDMMC_CMD_WRITE_MULT_BLOCK     25U  /*!< Continuously writes blocks of data until a STOP_TRANSMISSION follows.                    */
#define SDMMC_CMD_PROG_CID             26U  /*!< Reserved for manufacturers.                                                              */
#define SDMMC_CMD_PROG_CSD             27U  /*!< Programming of the programmable bits of the CSD.                                         */
#define SDMMC_CMD_SET_WRITE_PROT       28U  /*!< Sets the write protection bit of the addressed group.                                    */
#define SDMMC_CMD_CLR_WRITE_PROT       29U  /*!< Clears the write protection bit of the addressed group.                                  */
#define SDMMC_CMD_SEND_WRITE_PROT      30U  /*!< Asks the card to send the status of the write protection bits.                           */
#define SDMMC_CMD_SD_ERASE_GRP_START   32U  /*!< Sets the address of the first write block to be erased. (For SD card only).              */
#define SDMMC_CMD_SD_ERASE_GRP_END     33U  /*!< Sets the address of the last write block of the continuous range to be erased.           */
#define SDMMC_CMD_ERASE_GRP_START      35U  /*!< Sets the address of the first write block to be erased. Reserved for each command system set by switch function command (CMD6).                                  */
#define SDMMC_CMD_ERASE_GRP_END        36U  /*!< Sets the address of the last write block of the continuous range to be erased. Reserved for each command system set by switch function command (CMD6).           */
#define SDMMC_CMD_ERASE                38U  /*!< Reserved for SD security applications.                                                   */
#define SDMMC_CMD_FAST_IO              39U  /*!< SD card doesn't support it (Reserved).                                                   */
#define SDMMC_CMD_GO_IRQ_STATE         40U  /*!< SD card doesn't support it (Reserved).                                                   */
#define SDMMC_CMD_LOCK_UNLOCK          42U  /*!< Sets/resets the password or lock/unlock the card. The size of the data block is set by the SET_BLOCK_LEN command.                                                */
#define SDMMC_CMD_APP_CMD              55U  /*!< Indicates to the card that the next command is an application specific command rather than a standard command.                                                   */
#define SDMMC_CMD_GEN_CMD              56U  /*!< Used either to transfer a data block to the card or to get a data block from the card for general purpose/application specific commands.                         */
#define SDMMC_CMD_NO_CMD               64U  /*!< No command                                                                               */
/**
  * @}
  */

/** @defgroup SDMMC_SD_Card_Specific_commands SDMMC SD Card Specific commands
  * @{
  */
#define SDMMC_CMD_APP_SD_SET_BUSWIDTH          6U   /*!< (ACMD6) Defines the data bus width to be used for data transfer. The allowed data bus widths are given in SCR register.                                                   */
#define SDMMC_CMD_SD_APP_STATUS                13U  /*!< (ACMD13) Send the SD status.                                                             */
#define SDMMC_CMD_SD_APP_SEND_NUM_WRITE_BLOCKS 22U  /*!< (ACMD22) Send the number of the written (without errors) write blocks. Responds with 32bit+CRC data block.                                                                */
#define SDMMC_CMD_SD_APP_OP_COND               41U  /*!< (ACMD41) Send host capacity support information (HCS) and asks the accessed card to send its operating condition register (OCR) content in the response on the CMD line.  */
#define SDMMC_CMD_SD_APP_SET_CLR_CARD_DETECT   42U  /*!< (ACMD42) Connect/Disconnect the 50 KOhm pull-up resistor on CD/DAT3 (pin 1) of the card  */
#define SDMMC_CMD_SD_APP_SEND_SCR              51U  /*!< Reads the SD Configuration Register (SCR).                                               */
#define SDMMC_CMD_SDMMC_RW_DIRECT              52U  /*!< For SD I/O card only, reserved for security specification.                               */
#define SDMMC_CMD_SDMMC_RW_EXTENDED            53U  /*!< For SD I/O card only, reserved for security specification.                               */
/**
  * @}
  */

/** @defgroup SDMMC_MMC_Specific_commands SDMMC MMC Specific commands
  * @{
  */
#define SDMMC_CMD_MMC_SLEEP_AWAKE 5 /*!< Toggle the device between Sleep state and Standby state */
/**
  * @}
  */

/** @defgroup SDMMC_SD_Card_Specific_security_commands SDMMC SD Card Specific security commands
  * @{
  */
#define SDMMC_CMD_SD_APP_GET_MKB                     43U
#define SDMMC_CMD_SD_APP_GET_MID                     44U
#define SDMMC_CMD_SD_APP_SET_CER_RN1                 45U
#define SDMMC_CMD_SD_APP_GET_CER_RN2                 46U
#define SDMMC_CMD_SD_APP_SET_CER_RES2                47U
#define SDMMC_CMD_SD_APP_GET_CER_RES1                48U
#define SDMMC_CMD_SD_APP_SECURE_READ_MULTIPLE_BLOCK  18U
#define SDMMC_CMD_SD_APP_SECURE_WRITE_MULTIPLE_BLOCK 25U
#define SDMMC_CMD_SD_APP_SECURE_ERASE                38U
#define SDMMC_CMD_SD_APP_CHANGE_SECURE_AREA          49U
#define SDMMC_CMD_SD_APP_SECURE_WRITE_MKB            48U
/**
  * @}
  */

/** @defgroup SDMMC_Masks_for_errors_Card_Status_R1 SDMMC Masks for errors Card Status R1 (OCR Register)
  * @{
  */
#define SDMMC_OCR_ADDR_OUT_OF_RANGE     0x80000000U
#define SDMMC_OCR_ADDR_MISALIGNED       0x40000000U
#define SDMMC_OCR_BLOCK_LEN_ERR         0x20000000U
#define SDMMC_OCR_ERASE_SEQ_ERR         0x10000000U
#define SDMMC_OCR_BAD_ERASE_PARAM       0x08000000U
#define SDMMC_OCR_WRITE_PROT_VIOLATION  0x04000000U
#define SDMMC_OCR_LOCK_UNLOCK_FAILED    0x01000000U
#define SDMMC_OCR_COM_CRC_FAILED        0x00800000U
#define SDMMC_OCR_ILLEGAL_CMD           0x00400000U
#define SDMMC_OCR_CARD_ECC_FAILED       0x00200000U
#define SDMMC_OCR_CC_ERROR              0x00100000U
#define SDMMC_OCR_GENERAL_UNKNOWN_ERROR 0x00080000U
#define SDMMC_OCR_STREAM_READ_UNDERRUN  0x00040000U
#define SDMMC_OCR_STREAM_WRITE_OVERRUN  0x00020000U
#define SDMMC_OCR_CID_CSD_OVERWRITE     0x00010000U
#define SDMMC_OCR_WP_ERASE_SKIP         0x00008000U
#define SDMMC_OCR_CARD_ECC_DISABLED     0x00004000U
#define SDMMC_OCR_ERASE_RESET           0x00002000U
#define SDMMC_OCR_AKE_SEQ_ERROR         0x00000008U
#define SDMMC_OCR_ERRORBITS             0xFDFFE008U
/**
  * @}
  */

/** @defgroup SDMMC_Masks_for_R6_Response SDMMC Masks for R6 Response
  * @{
  */
#define SDMMC_R6_GENERAL_UNKNOWN_ERROR 0x00002000U
#define SDMMC_R6_ILLEGAL_CMD           0x00004000U
#define SDMMC_R6_COM_CRC_FAILED        0x00008000U
/**
  * @}
  */

/** @defgroup SDMMC_Speed_Switch_Pattern SDMMC Speed Switch Pattern
  * @{
  */
#define SDMMC_VOLTAGE_WINDOW_SD       0x80100000U
#define SDMMC_HIGH_CAPACITY           0x40000000U
#define SDMMC_STD_CAPACITY            0x00000000U
#define SDMMC_CHECK_PATTERN           0x000001AAU
#define SDMMC_SD_SWITCH_1_8V_CAPACITY 0x01000000U
#define SDMMC_DDR50_SWITCH_PATTERN    0x80FFFF04U
#define SDMMC_SDR104_SWITCH_PATTERN   0x80FF1F03U
#define SDMMC_SDR50_SWITCH_PATTERN    0x80FF1F02U
#define SDMMC_SDR25_SWITCH_PATTERN    0x80FFFF01U
#define SDMMC_SDR12_SWITCH_PATTERN    0x80FFFF00U
/**
  * @}
  */

/** @defgroup SDMMC_Trial_Times SDMMC trial times
  * @{
  */
#define SDMMC_MAX_VOLT_TRIAL  0x0000FFFFU
#define SDMMC_MAX_TRIAL       0x0000FFFFU
#define SDMMC_ALLZERO         0x00000000U
#define SDMMC_MAX_DATA_LENGTH 0x01FFFFFFU
/**
  * @}
  */

/** @defgroup SDMMC_Fifo_Size SDMMC Fifo size
  * @{
  */
#define SDMMC_FIFO_SIZE 32U /*!< Half full FIFO data size in byte */
/**
  * @}
  */

/** @defgroup SDMMC_Wide_Bus_Supported SDMMC Wide bus supported
  * @{
  */
#define SDMMC_WIDE_BUS_SUPPORT    0x00040000U
#define SDMMC_SINGLE_BUS_SUPPORT  0x00010000U
/**
  * @}
  */

/** @defgroup SDMMC_Bit_numbering SDMMC Bit numbering
  * @{
  */
#define SDMMC_0TO7BITS    0x000000FFU
#define SDMMC_8TO15BITS   0x0000FF00U
#define SDMMC_16TO23BITS  0x00FF0000U
#define SDMMC_24TO31BITS  0xFF000000U
/**
  * @}
  */

/** @defgroup SDMMC_Command_Class_supported SDMMC Command Class supported
  * @{
  */
#define SDMMC_CCCC_ERASE 0x00000020U
/**
  * @}
  */

/** @defgroup SDMMC_Cmd_Tiemout SDMMC Cmd Timeout
  * @{
  */
#define SDMMC_CMD_TIMEOUT  100U  /*!< 100ms are required for an command response timeout */
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Clock_Edge Clock Edge
  * @{
  */
#define SDMMC_CLOCK_EDGE_RISING  0x00000000U
#define SDMMC_CLOCK_EDGE_FALLING SDMMC_CLKCR_NEGEDGE
#define IS_SDMMC_CLOCK_EDGE(EDGE) ((EDGE == SDMMC_CLOCK_EDGE_RISING) || (EDGE == SDMMC_CLOCK_EDGE_FALLING))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Clock_Power_Save Clock Power Saving
  * @{
  */
#define SDMMC_CLOCK_POWER_SAVE_DISABLE   0x00000000U
#define SDMMC_CLOCK_POWER_SAVE_ENABLE    SDMMC_CLKCR_PWRSAV
#define IS_SDMMC_CLOCK_POWER_SAVE(SAVE)  ((SAVE == SDMMC_CLOCK_POWER_SAVE_DISABLE) \
                                          || (SAVE == SDMMC_CLOCK_POWER_SAVE_ENABLE))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Bus_Wide Bus Width
  * @{
  */
#define SDMMC_BUS_WIDE_1BIT     0x00000000U
#define SDMMC_BUS_WIDE_4BIT     SDMMC_CLKCR_WIDBUS_0
#define SDMMC_BUS_WIDE_8BIT     SDMMC_CLKCR_WIDBUS_1
#define IS_SDMMC_BUS_WIDE(WIDE) ((WIDE == SDMMC_BUS_WIDE_1BIT) || (WIDE == SDMMC_BUS_WIDE_4BIT) \
                                 || (WIDE == SDMMC_BUS_WIDE_8BIT))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Hardware_Flow_Control Hardware Flow Control
  * @{
  */
#define SDMMC_HARDWARE_FLOW_CONTROL_DISABLE      0x00000000U
#define SDMMC_HARDWARE_FLOW_CONTROL_ENABLE       SDMMC_CLKCR_HWFC_EN
#define IS_SDMMC_HARDWARE_FLOW_CONTROL(CONTROL)  ((CONTROL == SDMMC_HARDWARE_FLOW_CONTROL_DISABLE) \
                                                  || (CONTROL == SDMMC_HARDWARE_FLOW_CONTROL_ENABLE))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Speed_Mode SDMMC Speed Mode
  * @{
  */
#define SDMMC_SPEED_MODE_AUTO         0x00000000U
#define SDMMC_SPEED_MODE_DEFAULT      0x00000001U
#define SDMMC_SPEED_MODE_HIGH         0x00000002U
#define SDMMC_SPEED_MODE_ULTRA        0x00000003U
#define SDMMC_SPEED_MODE_ULTRA_SDR104 SDMMC_SPEED_MODE_ULTRA
#define SDMMC_SPEED_MODE_DDR          0x00000004U
#define SDMMC_SPEED_MODE_ULTRA_SDR50  0x00000005U

#define IS_SDMMC_SPEED_MODE(MODE) ((MODE == SDMMC_SPEED_MODE_AUTO) || (MODE == SDMMC_SPEED_MODE_DEFAULT)  \
                                   || (MODE == SDMMC_SPEED_MODE_HIGH) || (MODE == SDMMC_SPEED_MODE_ULTRA) \
                                   || (MODE == SDMMC_SPEED_MODE_ULTRA_SDR50) || (MODE == SDMMC_SPEED_MODE_DDR))

/**
  * @}
  */

/** @defgroup SDMMC_CORE_TRANSCEIVER_PRESENT Transceiver Present
  * @{
  */
#define SDMMC_TRANSCEIVER_UNKNOWN     0x00000000U
#define SDMMC_TRANSCEIVER_NOT_PRESENT 0x00000001U
#define SDMMC_TRANSCEIVER_PRESENT     0x00000002U
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Command_Index Command Index
  * @{
  */
#define IS_SDMMC_CMD_INDEX(INDEX) ((INDEX) < 0x40U)
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Response_Type Response Type
  * @{
  */
#define SDMMC_RESPONSE_NO           0x00000000U
#define SDMMC_RESPONSE_SHORT        SDMMC_CMDR_WAITRESP_0
#define SDMMC_RESPONSE_LONG         SDMMC_CMDR_WAITRESP
#define IS_SDMMC_RESPONSE(RESPONSE) ((RESPONSE == SDMMC_RESPONSE_NO) || (RESPONSE == SDMMC_RESPONSE_SHORT) \
                                     || (RESPONSE == SDMMC_RESPONSE_LONG))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Wait_Interrupt_State Wait Interrupt
  * @{
  */
#define SDMMC_WAIT_NO       0x00000000U
#define SDMMC_WAIT_IT       SDMMC_CMDR_WAITINT
#define SDMMC_WAIT_PEND     SDMMC_CMDR_WAITPEND
#define IS_SDMMC_WAIT(WAIT) ((WAIT == SDMMC_WAIT_NO) || (WAIT == SDMMC_WAIT_IT) || (WAIT == SDMMC_WAIT_PEND))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_CPSM_State CPSM State
  * @{
  */
#define SDMMC_CPSM_DISABLE   0x00000000U
#define SDMMC_CPSM_ENABLE    SDMMC_CMDR_CPSMEN
#define IS_SDMMC_CPSM(CPSM)  ((CPSM == SDMMC_CPSM_DISABLE) || (CPSM == SDMMC_CPSM_ENABLE))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Response_Registers Response Register
  * @{
  */
#define SDMMC_RESP1          0x00000000U
#define SDMMC_RESP2          0x00000004U
#define SDMMC_RESP3          0x00000008U
#define SDMMC_RESP4          0x0000000CU
#define IS_SDMMC_RESP(RESP)  ((RESP == SDMMC_RESP1) || (RESP == SDMMC_RESP2) || (RESP == SDMMC_RESP3) \
                              || (RESP == SDMMC_RESP4))
/**
  * @}
  */

/** @defgroup SDMMC_Internal_DMA_Mode  SDMMC Internal DMA Mode
  * @{
  */
#define SDMMC_DISABLE_IDMA             0x00000000U
#define SDMMC_ENABLE_IDMA_SINGLE_BUFF  SDMMC_IDMACTRLR_IDMAEN
#define SDMMC_ENABLE_IDMA_DOUBLE_BUFF0 (SDMMC_IDMACTRLR_IDMAEN | SDMMC_IDMACTRLR_IDMABMODE)
#define SDMMC_ENABLE_IDMA_DOUBLE_BUFF1 (SDMMC_IDMACTRLR_IDMAEN | SDMMC_IDMACTRLR_IDMABMODE | SDMMC_IDMA_IDMABACT)
#define SDMMC_IDMA_NORMAL_MODE         0U
#define SDMMC_IDMA_LINKEDLIST_MODE     SDMMC_IDMACTRLR_IDMABMODE
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Data_Block_Size  Data Block Size
  * @{
  */
#define SDMMC_DATABLOCK_SIZE_1B     0x00000000U
#define SDMMC_DATABLOCK_SIZE_2B     SDMMC_DCTRL_DBLOCKSIZE_0
#define SDMMC_DATABLOCK_SIZE_4B     SDMMC_DCTRL_DBLOCKSIZE_1
#define SDMMC_DATABLOCK_SIZE_8B     (SDMMC_DCTRL_DBLOCKSIZE_0 | SDMMC_DCTRL_DBLOCKSIZE_1)
#define SDMMC_DATABLOCK_SIZE_16B    SDMMC_DCTRL_DBLOCKSIZE_2
#define SDMMC_DATABLOCK_SIZE_32B    (SDMMC_DCTRL_DBLOCKSIZE_0 | SDMMC_DCTRL_DBLOCKSIZE_2)
#define SDMMC_DATABLOCK_SIZE_64B    (SDMMC_DCTRL_DBLOCKSIZE_1 | SDMMC_DCTRL_DBLOCKSIZE_2)
#define SDMMC_DATABLOCK_SIZE_128B   (SDMMC_DCTRL_DBLOCKSIZE_0 | SDMMC_DCTRL_DBLOCKSIZE_1|SDMMC_DCTRL_DBLOCKSIZE_2)
#define SDMMC_DATABLOCK_SIZE_256B   SDMMC_DCTRL_DBLOCKSIZE_3
#define SDMMC_DATABLOCK_SIZE_512B   (SDMMC_DCTRL_DBLOCKSIZE_0 | SDMMC_DCTRL_DBLOCKSIZE_3)
#define SDMMC_DATABLOCK_SIZE_1024B  (SDMMC_DCTRL_DBLOCKSIZE_1 | SDMMC_DCTRL_DBLOCKSIZE_3)
#define SDMMC_DATABLOCK_SIZE_2048B  (SDMMC_DCTRL_DBLOCKSIZE_0 | SDMMC_DCTRL_DBLOCKSIZE_1|SDMMC_DCTRL_DBLOCKSIZE_3)
#define SDMMC_DATABLOCK_SIZE_4096B  (SDMMC_DCTRL_DBLOCKSIZE_2 | SDMMC_DCTRL_DBLOCKSIZE_3)
#define SDMMC_DATABLOCK_SIZE_8192B  (SDMMC_DCTRL_DBLOCKSIZE_0 | SDMMC_DCTRL_DBLOCKSIZE_2 | SDMMC_DCTRL_DBLOCKSIZE_3)
#define SDMMC_DATABLOCK_SIZE_16384B (SDMMC_DCTRL_DBLOCKSIZE_1 | SDMMC_DCTRL_DBLOCKSIZE_2 | SDMMC_DCTRL_DBLOCKSIZE_3)

#define IS_SDMMC_BLOCK_SIZE(SIZE) ((SIZE == SDMMC_DATABLOCK_SIZE_1B)       || (SIZE == SDMMC_DATABLOCK_SIZE_2B)    \
                                   || (SIZE == SDMMC_DATABLOCK_SIZE_4B)    || (SIZE == SDMMC_DATABLOCK_SIZE_8B)    \
                                   || (SIZE == SDMMC_DATABLOCK_SIZE_16B)   || (SIZE == SDMMC_DATABLOCK_SIZE_32B)   \
                                   || (SIZE == SDMMC_DATABLOCK_SIZE_64B)   || (SIZE == SDMMC_DATABLOCK_SIZE_128B)  \
                                   || (SIZE == SDMMC_DATABLOCK_SIZE_256B)  || (SIZE == SDMMC_DATABLOCK_SIZE_512B)  \
                                   || (SIZE == SDMMC_DATABLOCK_SIZE_1024B) || (SIZE == SDMMC_DATABLOCK_SIZE_2048B) \
                                   || (SIZE == SDMMC_DATABLOCK_SIZE_4096B) || (SIZE == SDMMC_DATABLOCK_SIZE_8192B) \
                                   || (SIZE == SDMMC_DATABLOCK_SIZE_16384B))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Transfer_Direction Transfer Direction
  * @{
  */
#define SDMMC_TRANSFER_DIR_TO_CARD   0x00000000U
#define SDMMC_TRANSFER_DIR_TO_SDMMC  SDMMC_DCTRL_DTDIR
#define IS_SDMMC_TRANSFER_DIR(DIR)   ((DIR == SDMMC_TRANSFER_DIR_TO_CARD) || (DIR == SDMMC_TRANSFER_DIR_TO_SDMMC))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Transfer_Type Transfer Type
  * @{
  */
#define SDMMC_TRANSFER_MODE_BLOCK    0x00U
#define SDMMC_TRANSFER_MODE_SDIO     SDMMC_DCTRL_DTMODE_0
#define SDMMC_TRANSFER_MODE_STREAM   SDMMC_DCTRL_DTMODE_1
#define IS_SDMMC_TRANSFER_MODE(MODE) ((MODE == SDMMC_TRANSFER_MODE_BLOCK)     \
                                      || ((MODE) == SDMMC_TRANSFER_MODE_SDIO) \
                                      || (MODE == SDMMC_TRANSFER_MODE_STREAM))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_DPSM_State DPSM State
  * @{
  */
#define SDMMC_DPSM_DISABLE   0x00U
#define SDMMC_DPSM_ENABLE    SDMMC_DCTRL_DTEN
#define IS_SDMMC_DPSM(DPSM)  ((DPSM == SDMMC_DPSM_DISABLE) || (DPSM == SDMMC_DPSM_ENABLE))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Read_Wait_Mode Read Wait Mode
  * @{
  */
#define SDMMC_READ_WAIT_MODE_DATA2    0x00
#define SDMMC_READ_WAIT_MODE_CLK      SDMMC_DCTRL_RWMOD
#define IS_SDMMC_READWAIT_MODE(MODE)  ((MODE == SDMMC_READ_WAIT_MODE_CLK) || (MODE == SDMMC_READ_WAIT_MODE_DATA2))
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Interrupt_sources Interrupt Sources
  * @{
  */
#define SDMMC_IT_CCRCFAIL   SDMMC_MASKR_CCRCFAILIE
#define SDMMC_IT_DCRCFAIL   SDMMC_MASKR_DCRCFAILIE
#define SDMMC_IT_CTIMEOUT   SDMMC_MASKR_CTIMEOUTIE
#define SDMMC_IT_DTIMEOUT   SDMMC_MASKR_DTIMEOUTIE
#define SDMMC_IT_TXUNDERR   SDMMC_MASKR_TXUNDERRIE
#define SDMMC_IT_RXOVERR    SDMMC_MASKR_RXOVERRIE
#define SDMMC_IT_CMDREND    SDMMC_MASKR_CMDRENDIE
#define SDMMC_IT_CMDSENT    SDMMC_MASKR_CMDSENTIE
#define SDMMC_IT_DATAEND    SDMMC_MASKR_DATAENDIE
#define SDMMC_IT_DHOLD      SDMMC_MASKR_DHOLDIE
#define SDMMC_IT_DBCKEND    SDMMC_MASKR_DBCKENDIE
#define SDMMC_IT_DABORT     SDMMC_MASKR_DABORTIE
#define SDMMC_IT_TXFIFOHE   SDMMC_MASKR_TXFIFOHEIE
#define SDMMC_IT_RXFIFOHF   SDMMC_MASKR_RXFIFOHFIE
#define SDMMC_IT_RXFIFOF    SDMMC_MASKR_RXFIFOFIE
#define SDMMC_IT_TXFIFOE    SDMMC_MASKR_TXFIFOEIE
#define SDMMC_IT_BUSYD0END  SDMMC_MASKR_BUSYD0ENDIE
#define SDMMC_IT_SDIOIT     SDMMC_MASKR_SDIOITIE
#define SDMMC_IT_ACKFAIL    SDMMC_MASKR_ACKFAILIE
#define SDMMC_IT_ACKTIMEOUT SDMMC_MASKR_ACKTIMEOUTIE
#define SDMMC_IT_VSWEND     SDMMC_MASKR_VSWENDIE
#define SDMMC_IT_CKSTOP     SDMMC_MASKR_CKSTOPIE
#define SDMMC_IT_IDMABTC    SDMMC_MASKR_IDMABTCIE
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Flags_sources Flags Sources
  * @{
  */
#define SDMMC_FLAG_CCRCFAIL   SDMMC_STAR_CCRCFAIL
#define SDMMC_FLAG_DCRCFAIL   SDMMC_STAR_DCRCFAIL
#define SDMMC_FLAG_CTIMEOUT   SDMMC_STAR_CTIMEOUT
#define SDMMC_FLAG_DTIMEOUT   SDMMC_STAR_DTIMEOUT
#define SDMMC_FLAG_TXUNDERR   SDMMC_STAR_TXUNDERR
#define SDMMC_FLAG_RXOVERR    SDMMC_STAR_RXOVERR
#define SDMMC_FLAG_CMDREND    SDMMC_STAR_CMDREND
#define SDMMC_FLAG_CMDSENT    SDMMC_STAR_CMDSENT
#define SDMMC_FLAG_DATAEND    SDMMC_STAR_DATAEND
#define SDMMC_FLAG_DHOLD      SDMMC_STAR_DHOLD
#define SDMMC_FLAG_DBCKEND    SDMMC_STAR_DBCKEND
#define SDMMC_FLAG_DABORT     SDMMC_STAR_DABORT
#define SDMMC_FLAG_DPSMACT    SDMMC_STAR_DPSMACT
#define SDMMC_FLAG_CMDACT     SDMMC_STAR_CPSMACT
#define SDMMC_FLAG_TXFIFOHE   SDMMC_STAR_TXFIFOHE
#define SDMMC_FLAG_RXFIFOHF   SDMMC_STAR_RXFIFOHF
#define SDMMC_FLAG_TXFIFOF    SDMMC_STAR_TXFIFOF
#define SDMMC_FLAG_RXFIFOF    SDMMC_STAR_RXFIFOF
#define SDMMC_FLAG_TXFIFOE    SDMMC_STAR_TXFIFOE
#define SDMMC_FLAG_RXFIFOE    SDMMC_STAR_RXFIFOE
#define SDMMC_FLAG_BUSYD0     SDMMC_STAR_BUSYD0
#define SDMMC_FLAG_BUSYD0END  SDMMC_STAR_BUSYD0END
#define SDMMC_FLAG_SDIOIT     SDMMC_STAR_SDIOIT
#define SDMMC_FLAG_ACKFAIL    SDMMC_STAR_ACKFAIL
#define SDMMC_FLAG_ACKTIMEOUT SDMMC_STAR_ACKTIMEOUT
#define SDMMC_FLAG_VSWEND     SDMMC_STAR_VSWEND
#define SDMMC_FLAG_CKSTOP     SDMMC_STAR_CKSTOP
#define SDMMC_FLAG_IDMATE     SDMMC_STAR_IDMATE
#define SDMMC_FLAG_IDMABTC    SDMMC_STAR_IDMABTC

#define SDMMC_STATIC_FLAGS (SDMMC_FLAG_CCRCFAIL  | SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_CTIMEOUT | SDMMC_FLAG_DTIMEOUT  \
                            | SDMMC_FLAG_TXUNDERR  | SDMMC_FLAG_RXOVERR  | SDMMC_FLAG_CMDREND  | SDMMC_FLAG_CMDSENT \
                            | SDMMC_FLAG_DATAEND   | SDMMC_FLAG_DHOLD    | SDMMC_FLAG_DBCKEND  | SDMMC_FLAG_DABORT  \
                            | SDMMC_FLAG_BUSYD0END | SDMMC_FLAG_SDIOIT   | SDMMC_FLAG_ACKFAIL  | SDMMC_FLAG_IDMABTC \
                            | SDMMC_FLAG_VSWEND    | SDMMC_FLAG_CKSTOP   | SDMMC_FLAG_IDMATE   | SDMMC_FLAG_ACKTIMEOUT)

#define SDMMC_STATIC_CMD_FLAGS (SDMMC_FLAG_CCRCFAIL | SDMMC_FLAG_CTIMEOUT  | SDMMC_FLAG_CMDREND | SDMMC_FLAG_CMDSENT \
                                | SDMMC_FLAG_BUSYD0END)

#define SDMMC_STATIC_DATA_FLAGS (SDMMC_FLAG_DCRCFAIL | SDMMC_FLAG_DTIMEOUT | SDMMC_FLAG_TXUNDERR | SDMMC_FLAG_DHOLD    \
                                 | SDMMC_FLAG_RXOVERR  | SDMMC_FLAG_DATAEND  | SDMMC_FLAG_DBCKEND  | SDMMC_FLAG_IDMATE \
                                 | SDMMC_FLAG_DABORT   | SDMMC_FLAG_IDMABTC)
/**
  * @}
  */

/** @defgroup SDMMC_SDIO_CCCR_Registers SDMMC SDIO CCCR Registers
  * @{
  */
/*-------------------------------- CCCR0 ----------------------------------*/
#define SDMMC_SDIO_CCCR0                  0x000U  /*!< SDIOS Card Common Control Register 0        */
#define SDMMC_SDIO_CCCR0_BYTE0            0x000U  /*!< SDIOS Card Common Control Register 0 Byte 0 */
#define SDMMC_SDIO_CCCR0_BYTE1            0x001U  /*!< SDIOS Card Common Control Register 0 Byte 1 */
#define SDMMC_SDIO_CCCR0_BYTE2            0x002U  /*!< SDIOS Card Common Control Register 0 Byte 2 */
#define SDMMC_SDIO_CCCR0_BYTE3            0x003U  /*!< SDIOS Card Common Control Register 0 Byte 3 */

/*-------------------------------- CCCR4 ----------------------------------*/
#define SDMMC_SDIO_CCCR4                  0x004U  /*!< SDIOS Card Common Control Register 4        */
#define SDMMC_SDIO_CCCR4_BYTE0            0x004U  /*!< SDIOS Card Common Control Register 4 Byte 0 */
#define SDMMC_SDIO_CCCR4_BYTE1            0x005U  /*!< SDIOS Card Common Control Register 4 Byte 1 */
#define SDMMC_SDIO_CCCR4_BYTE2            0x006U  /*!< SDIOS Card Common Control Register 4 Byte 2 */
#define SDMMC_SDIO_CCCR4_BYTE3            0x007U  /*!< SDIOS Card Common Control Register 4 Byte 3 */

/*-------------------------------- CCCR8 ----------------------------------*/
#define SDMMC_SDIO_CCCR8                  0x008U  /*!< SDIOS Card Common Control Register 8        */
#define SDMMC_SDIO_CCCR8_BYTE0            0x008U  /*!< SDIOS Card Common Control Register 8 Byte 0 */
#define SDMMC_SDIO_CCCR8_BYTE1            0x009U  /*!< SDIOS Card Common Control Register 8 Byte 1 */
#define SDMMC_SDIO_CCCR8_BYTE2            0x00AU  /*!< SDIOS Card Common Control Register 8 Byte 2 */
#define SDMMC_SDIO_CCCR8_BYTE3            0x00BU  /*!< SDIOS Card Common Control Register 8 Byte 3 */

/*-------------------------------- CCCR12 ---------------------------------*/
#define SDMMC_SDIO_CCCR12                 0x00CU  /*!< SDIOS Card Common Control Register 12        */
#define SDMMC_SDIO_CCCR12_BYTE0           0x00CU  /*!< SDIOS Card Common Control Register 12 Byte 0 */
#define SDMMC_SDIO_CCCR12_BYTE1           0x00DU  /*!< SDIOS Card Common Control Register 12 Byte 1 */
#define SDMMC_SDIO_CCCR12_BYTE2           0x00EU  /*!< SDIOS Card Common Control Register 12 Byte 2 */
#define SDMMC_SDIO_CCCR12_BYTE3           0x00FU  /*!< SDIOS Card Common Control Register 12 Byte 3 */

/*-------------------------------- CCCR16 ---------------------------------*/
#define SDMMC_SDIO_CCCR16                 0x010U  /*!< SDIOS Card Common Control Register 16        */
#define SDMMC_SDIO_CCCR16_BYTE0           0x010U  /*!< SDIOS Card Common Control Register 16 Byte 0 */
#define SDMMC_SDIO_CCCR16_BYTE1           0x011U  /*!< SDIOS Card Common Control Register 16 Byte 1 */
#define SDMMC_SDIO_CCCR16_BYTE2           0x012U  /*!< SDIOS Card Common Control Register 16 Byte 2 */
#define SDMMC_SDIO_CCCR16_BYTE3           0x013U  /*!< SDIOS Card Common Control Register 16 Byte 3 */

/*-------------------------------- CCCR20 ---------------------------------*/
#define SDMMC_SDIO_CCCR20                 0x014U  /*!< SDIOS Card Common Control Register 20        */
#define SDMMC_SDIO_CCCR20_BYTE0           0x014U  /*!< SDIOS Card Common Control Register 20 Byte 0 */
#define SDMMC_SDIO_CCCR20_BYTE1           0x015U  /*!< SDIOS Card Common Control Register 20 Byte 1 */
#define SDMMC_SDIO_CCCR20_BYTE2           0x016U  /*!< SDIOS Card Common Control Register 20 Byte 2 */
#define SDMMC_SDIO_CCCR20_BYTE3           0x017U  /*!< SDIOS Card Common Control Register 20 Byte 3 */

/*-------------------------------- F1BR0 ----------------------------------*/
#define SDMMC_SDIO_F1BR0                  0x100U  /*!< SDIOS Function 1 Basic Register 0        */
#define SDMMC_SDIO_F1BR0_BYTE0            0x100U  /*!< SDIOS Function 1 Basic Register 0 Byte 0 */
#define SDMMC_SDIO_F1BR0_BYTE1            0x101U  /*!< SDIOS Function 1 Basic Register 0 Byte 1 */
#define SDMMC_SDIO_F1BR0_BYTE2            0x102U  /*!< SDIOS Function 1 Basic Register 0 Byte 2 */
#define SDMMC_SDIO_F1BR0_BYTE3            0x103U  /*!< SDIOS Function 1 Basic Register 0 Byte 3 */

/*-------------------------------- F1BR8 ----------------------------------*/
#define SDMMC_SDIO_F1BR8                  0x108U  /*!< SDIOS Function 1 Basic Register 8        */
#define SDMMC_SDIO_F1BR8_BYTE0            0x108U  /*!< SDIOS Function 1 Basic Register 8 Byte 0 */
#define SDMMC_SDIO_F1BR8_BYTE1            0x109U  /*!< SDIOS Function 1 Basic Register 8 Byte 1 */
#define SDMMC_SDIO_F1BR8_BYTE2            0x10AU  /*!< SDIOS Function 1 Basic Register 8 Byte 2 */
#define SDMMC_SDIO_F1BR8_BYTE3            0x10BU  /*!< SDIOS Function 1 Basic Register 8 Byte 3 */

/*-------------------------------- F1BR12 ---------------------------------*/
#define SDMMC_SDIO_F1BR12                 0x10CU  /*!< SDIOS Function 1 Basic Register 12        */
#define SDMMC_SDIO_F1BR12_BYTE0           0x10CU  /*!< SDIOS Function 1 Basic Register 12 Byte 0 */
#define SDMMC_SDIO_F1BR12_BYTE1           0x10DU  /*!< SDIOS Function 1 Basic Register 12 Byte 1 */
#define SDMMC_SDIO_F1BR12_BYTE2           0x10EU  /*!< SDIOS Function 1 Basic Register 12 Byte 2 */
#define SDMMC_SDIO_F1BR12_BYTE3           0x10FU  /*!< SDIOS Function 1 Basic Register 12 Byte 3 */

/*-------------------------------- F1BR16 ---------------------------------*/
#define SDMMC_SDIO_F1BR16                 0x110U  /*!< SDIOS Function 1 Basic Register 16        */
#define SDMMC_SDIO_F1BR16_BYTE0           0x110U  /*!< SDIOS Function 1 Basic Register 16 Byte 0 */
#define SDMMC_SDIO_F1BR16_BYTE1           0x111U  /*!< SDIOS Function 1 Basic Register 16 Byte 1 */
#define SDMMC_SDIO_F1BR16_BYTE2           0x112U  /*!< SDIOS Function 1 Basic Register 16 Byte 2 */
#define SDMMC_SDIO_F1BR16_BYTE3           0x113U  /*!< SDIOS Function 1 Basic Register 16 Byte 3 */
/**
  * @}
  */

/** @defgroup SDMMC_CORE_SDIO_BUS_SPEED SDMMC CORE SDIO Bus Speed Definitions
  * @{
  */
#define SDMMC_SDIO_BUS_SPEED_SDR12        0x00U /*!< SDMMC SDIO bus speed mode SDR12  */
#define SDMMC_SDIO_BUS_SPEED_SDR25        0x02U /*!< SDMMC SDIO bus speed mode SDR25  */
#define SDMMC_SDIO_BUS_SPEED_SDR50        0x04U /*!< SDMMC SDIO bus speed mode SDR50  */
#define SDMMC_SDIO_BUS_SPEED_SDR104       0x06U /*!< SDMMC SDIO bus speed mode SDR104 */
#define SDMMC_SDIO_BUS_SPEED_DDR50        0x08U /*!< SDMMC SDIO bus speed mode DDR50  */
/**
  * @}
  */

/** @defgroup SDMMC_CORE_SDIO_BLOCK_SIZE SDMMC CORE SDIO Block Size Definitions
  * @{
  */
#define SDMMC_SDIO_BLOCK_SIZE_1BYTE        1U    /*!< SDIO block size 1 byte    */
#define SDMMC_SDIO_BLOCK_SIZE_2BYTE        2U    /*!< SDIO block size 2 byte    */
#define SDMMC_SDIO_BLOCK_SIZE_4BYTE        4U    /*!< SDIO block size 4 byte    */
#define SDMMC_SDIO_BLOCK_SIZE_8BYTE        8U    /*!< SDIO block size 8 byte    */
#define SDMMC_SDIO_BLOCK_SIZE_16BYTE       16U   /*!< SDIO block size 16 byte   */
#define SDMMC_SDIO_BLOCK_SIZE_32BYTE       32U   /*!< SDIO block size 32 byte   */
#define SDMMC_SDIO_BLOCK_SIZE_64BYTE       64U   /*!< SDIO block size 64 byte   */
#define SDMMC_SDIO_BLOCK_SIZE_128BYTE      128U  /*!< SDIO block size 128 byte  */
#define SDMMC_SDIO_BLOCK_SIZE_256BYTE      256U  /*!< SDIO block size 256 byte  */
#define SDMMC_SDIO_BLOCK_SIZE_512BYTE      512U  /*!< SDIO block size 512 byte  */
#define SDMMC_SDIO_BLOCK_SIZE_1024BYTE     1024U /*!< SDIO block size 1024 byte */
#define SDMMC_SDIO_BLOCK_SIZE_2048BYTE     2048U /*!< SDIO block size 2048 byte */
/**
  * @}
  */

/** @defgroup SDMMC_CORE_registers_bits_and_address SDMMC registers bits and address in the alias region
  * @{
  */
/*!< CLKCR register clear mask */
#define CLKCR_CLEAR_MASK (SDMMC_CLKCR_CLKDIV  | SDMMC_CLKCR_PWRSAV | SDMMC_CLKCR_WIDBUS   | SDMMC_CLKCR_NEGEDGE \
                          | SDMMC_CLKCR_HWFC_EN | SDMMC_CLKCR_DDR    | SDMMC_CLKCR_BUSSPEED | SDMMC_CLKCR_SELCLKRX)

/*!< SDMMC DCTRL Clear Mask */
#define DCTRL_CLEAR_MASK  (SDMMC_DCTRL_DTEN | SDMMC_DCTRL_DTDIR | SDMMC_DCTRL_DTMODE | SDMMC_DCTRL_DBLOCKSIZE)

/*!< CMD Register clear mask */
#define CMD_CLEAR_MASK (SDMMC_CMDR_CMDINDEX | SDMMC_CMDR_WAITRESP | SDMMC_CMDR_WAITINT | SDMMC_CMDR_WAITPEND \
                        | SDMMC_CMDR_CPSMEN   | SDMMC_CMDR_CMDSUSPEND)
/**
  * @}
  */

/** @defgroup SDMMC_Power SDMMC Power Definitions
  * @{
  */
#define SDMMC_PWR_OFF 0U                    /*!< SDMMC power off */
#define SDMMC_PWR_ON  SDMMC_POWER_PWRCTRL   /*!< SDMMC power on  */
#define SDMMC_PWR_UP  SDMMC_POWER_PWRCTRL_1 /*!< SDMMC power up  */
/**
  * @}
  */

/**
  * @}
  */
/* Private Constants -------------------------------------------------------------------------------------------------*/
/** @defgroup SDMMC_SD_Private_Constants SDMMC SD Private Constants
  * @{
  */

/** @defgroup SDMMC_SD_Frequency SDMMC SD frequency types structure definition
  * @{
  */
#define SDMMC_SD_CARD_INIT_FREQ       400000U    /*!< Initialization phase   : 400 kHz max */
#define SDMMC_SD_CARD_NS_SPEED_FREQ   25000000U  /*!< Normal speed phase     : 25 MHz max  */
#define SDMMC_SD_CARD_HS_SPEED_FREQ   50000000U  /*!< High speed phase       : 50 MHz max  */
#define SDMMC_SD_CARD_UHS_SPEED_FREQ  100000000U /*!< Ultra High speed phase : 100 MHz max */
/**
  * @}
  */

/** @defgroup SDMMC_SD_Memory_Types SDMMC SD memory types structure definition
  * @{
  */
#define SDMMC_SD_CARD_SDSC      0x00UL /*!< SD Standard Capacity < 2Go                          */
#define SDMMC_SD_CARD_SDHC_SDXC 0x01UL /*!< SD High Capacity < 32Go, SD Extended Capacity < 2To */
#define SDMMC_SD_CARD_SECURED   0x03UL /*!< SD Card secured type                                */
/**
  * @}
  */

/** @defgroup SDMMC_MMC_Frequency SDMMC MMC frequency types structure definition
  * @{
  */
#define SDMMC_MMC_INIT_FREQ           (400000U)   /*!< Initialization phase : 400 kHz max */
#define SDMMC_MMC_HIGH_SPEED_FREQ     (52000000U) /*!< High speed phase   : 52 MHz max    */
/**
  * @}
  */

/** @defgroup SDMMC_MMC_Memory_Types SDMMC MMC memory types structure definition
  * @{
  */
#define SDMMC_MMC_CARD_LC  (0x00U) /*!< MMC Card Low Capacity <=2Gbytes              */
#define SDMMC_MMC_CARD_HC  (0x01U) /*!< MMC Card High Capacity >2Gbytes and <2Tbytes */
/**
  * @}
  */

/** @defgroup SDMMC_SD_supported_version SDMMC SD supported version structure definition
  * @{
  */
#define SDMMC_SD_CARD_V1_X 0x00UL /*!< Supported card version 1.x */
#define SDMMC_SD_CARD_V2_X 0x01UL /*!< Supported card version 2.x */
/**
  * @}
  */

/** @defgroup SDMMC_SD_speed_types SDMMC SD speed types structure definition
  * @{
  */
#define SDMMC_SD_CARD_NORMAL_SPEED     0x0000U /*!< Normal Speed Card < 12.5Mo/s : Spec Version 1.01                                          */
#define SDMMC_SD_CARD_HIGH_SPEED       0x0100U /*!< High Speed Card < 25Mo/s : Spec version 2.00                                              */
#define SDMMC_SD_CARD_ULTRA_HIGH_SPEED 0x0200U /*!< UHS-I SD Card < 50Mo/s for SDR50, DDR5 Cards and < 104Mo/s for SDR104 : Spec version 3.01 */
/**
  * @}
  */

/** @defgroup SDMMC_transfer_context SDMMC transfer context structure definition
  * @{
  */
#define SDMMC_CONTEXT_NONE                 0x00UL /*!< None                            */
#define SDMMC_CONTEXT_READ_SINGLE_BLOCK    0x01UL /*!< Read single block operation     */
#define SDMMC_CONTEXT_READ_MULTIPLE_BLOCK  0x02UL /*!< Read multiple blocks operation  */
#define SDMMC_CONTEXT_WRITE_SINGLE_BLOCK   0x10UL /*!< Write single block operation    */
#define SDMMC_CONTEXT_WRITE_MULTIPLE_BLOCK 0x20UL /*!< Write multiple blocks operation */
#define SDMMC_CONTEXT_IT                   0x08UL /*!< Process in Interrupt mode       */
#define SDMMC_CONTEXT_DMA                  0x80UL /*!< Process in DMA mode             */
/**
  * @}
  */

/** @defgroup SDMMC_SD_Card_SCR_Data_Size_Byte SDMMC SD Card SCR Data Size Byte definition
  * @{
  */
#define SDMMC_SD_CARD_SCR_DATA_SIZE_BYTE    8U  /*!< SD SCR Data size byte */
/**
  * @}
  */

/** @defgroup SDMMC_MMC_BUS_WIDTH_SELECTION SDMMC MMC Bus Width Selection definition
  * @{
  */
#define SDMMC_MMC_BUS_WIDTH_1_DEFAULT_SPEED 0x03B70000U /*!< MMC argument to set a 1-bit for default speed mode */
#define SDMMC_MMC_BUS_WIDTH_4_HS            0x03B70100U /*!< MMC argument to set a 4-bit for High speed mode    */
#define SDMMC_MMC_BUS_WIDTH_8_HS            0x03B70200U /*!< MMC argument to set a 8-bit for High speed mode    */
#define SDMMC_MMC_BUS_WIDTH_4_DDR           0x03B70500U /*!< MMC argument to set a 4-bit for DDR mode           */
#define SDMMC_MMC_BUS_WIDTH_8_DDR           0x03B70600U /*!< MMC argument to set a 8-bit for DDR mode           */
/**
  * @}
  */

/** @defgroup SDMMC_MMC_ARG_FOR_SANITIZE_OPERATIOn SDMMC MMC argument to start the sanitize operation definition
  * @{
  */
#define SDMMC_MMC_START_SANITIZE_OPERATION  0x03A50100U /*!< MMC argument to start the sanitize operation */
/**
  * @}
  */

/** @defgroup SDMMC_MMC_SLEEP_AWAKE_TIMEOUT SDMMC MMC sleep/awake timeout definition
  * @{
  */
#define SDMMC_MMC_S_A_TIMEOUT  0x17U /*!< Max Sleep-Awake timeout value (Bit[217] of ext_csd register)  */
/**
  * @}
  */

/** @defgroup SDMMC_MMC_POWER_OFF_NOTIFICATION SDMMC MMC Power Off Notification definition
  * @{
  */
#define SDMMC_MMC_SET_PWR_OFF_NOTIF_TO_PWR_ON       0x03220100U /*!< Set the power-off notification to powered-on : ext_csd[34] = 1         */
#define SDMMC_MMC_SET_PWR_OFF_NOTIF_TO_SLEEP_NOTIF  0x03220400U /*!< Set the power-off notification to sleep notification : ext_csd[34] = 4 */
/**
  * @}
  */

/** @defgroup SDMMC_MMCHIGH_SPEED_TIMMING SDMMC MMC High Speed Timing definition
  * @{
  */
#define SDMMC_MMC_TIMMING_INTERFACE_DEFAULT  0x03B90000U /*!< Selecting backwards compatibility interface timing ext_csd[185] = 0 */
#define SDMMC_MMC_TIMMING_INTERFACE_HS       0x03B90100U /*!< interface timing for HS ext_csd[185] = 1                            */
/**
  * @}
  */

/** @defgroup SDMMC_SD_Card_Specification_Version SDMMC SD Card Specification Version definition
  * @{
  */
#define SDMMC_SD_CARD_SPEC_POS    24U          /*!< SDMMC SD card spec position  */
#define SDMMC_SD_CARD_SPEC_MSK    0x0F000000UL /*!< 0x0F000000UL                 */
#define SDMMC_SD_CARD_SPEC_3_POS  15U          /*!< SDMMC SD card spec3 position */
#define SDMMC_SD_CARD_SPEC_3_MSK  0x00008000UL /*!< 0x00008000UL                 */
#define SDMMC_SD_CARD_SPEC_4_POS  10U          /*!< SDMMC SD card spec4 position */
#define SDMMC_SD_CARD_SPEC_4_MSK  0x00000400UL /*!< 0x00000400UL                 */
#define SDMMC_SD_CARD_SPEC_5_POS  6U           /*!< SDMMC SD card spec5 position */
#define SDMMC_SD_CARD_SPEC_5_MSK  0x000003C0UL /*!< 0x000003C0UL                 */
/**
  * @}
  */

/** @defgroup SDMMC_Card_Identification_Data SDMMC Card Identification Data definition
  * @{
  */
#define SDMMC_MANUFACTURE_ID_POS       24U          /*!< SD/MMC card manufacture ID position        */
#define SDMMC_MANUFACTURE_ID_MSK       0xFF000000U  /*!< 0xFF000000U                                */
#define SDMMC_OEM_APP_ID_POS           8U           /*!< SD/MMC card OEM Application ID position    */
#define SDMMC_OEM_APP_ID_MSK           0x00FFFF00U  /*!< 0x00FFFF00U                                */
#define SDMMC_PRODUCT_NAME_PART1_POS   0U           /*!< SD/MMC card product name1 position         */
#define SDMMC_PRODUCT_NAME_PART1_MSK   0x000000FFU  /*!< 0x000000FFU                                */
#define SDMMC_PRODUCT_NAME_PART2_POS   0U           /*!< SD/MMC card product name2 position         */
#define SDMMC_PRODUCT_NAME_PART2_MSK   0xFFFFFFFFU  /*!< 0xFFFFFFFFU                                */
#define SDMMC_PRODUCT_REVISION_POS     24U          /*!< SD/MMC card product revision position      */
#define SDMMC_PRODUCT_REVISION_MSK     0xFF000000U  /*!< 0xFF000000U                                */
#define SDMMC_PRODUCT_SERIAL_NBR2_POS  0U           /*!< SD/MMC card product serial number position */
#define SDMMC_PRODUCT_SERIAL_NBR2_MSK  0x00FFFFFFU  /*!< 0x00FFFFFFU                                */
#define SDMMC_PRODUCT_SERIAL_NBR1_POS  24U          /*!< SD/MMC card serial number1 position        */
#define SDMMC_PRODUCT_SERIAL_NBR1_MSK  0xFF000000U  /*!< 0xFF000000U                                */
#define SDMMC_RESERVED_POS             20U          /*!< SD/MMC card reserved position              */
#define SDMMC_RESERVED_MSK             0x00F00000U  /*!< 0x00F00000U                                */
#define SDMMC_MANUFACTURE_DATE_POS     8U           /*!< SD/MMC card manufacture date position      */
#define SDMMC_MANUFACTURE_DATE_MSK     0x000FFF00U  /*!< 0x000FFF00U                                */
#define SDMMC_CID_CRC_POS              1U           /*!< SD/MMC card CID crc position               */
#define SDMMC_CID_CRC_MSK              0x000000FEU  /*!< 0x000000FEU                                */
#define SDMMC_NOT_USED_POS             0U           /*!< SD/MMC card Not used                       */
#define SDMMC_NOT_USED_MSK             0x00000001U  /*!< 0x00000001                                 */
/**
  * @}
  */

/** @defgroup MMC_Card_Specific_Data MMC Card Specific Data definition
  * @{
  */
#define SDMMC_MMC_CARD_DEVICE_SIZE1_POS      0U           /*!< MMC Card Device size 1 position              */
#define SDMMC_MMC_CARD_DEVICE_SIZE1_MSK      0x000003FFU  /*!< 0x000003FFU                                  */
#define SDMMC_MMC_CARD_DEVICE_SIZE2_POS      30U          /*!< MMC Card Ddevice size 2 position             */
#define SDMMC_MMC_CARD_DEVICE_SIZE2_MSK      0xC0000000U  /*!< 0xC0000000U                                  */
#define SDMMC_MMC_CARD_DEVICE_SIZE_MUL_POS   15U          /*!< MMC Card Device size Mul position            */
#define SDMMC_MMC_CARD_DEVICE_SIZE_MUL_MSK   0x00038000U  /*!< 0x00038000U                                  */
#define SDMMC_MMC_CARD_READ_BLOCK_LEN_POS    16U          /*!< MMC Card read block len position             */
#define SDMMC_MMC_CARD_READ_BLOCK_LEN_MSK    0x000F0000U  /*!< 0x000F0000U                                  */
/**
  * @}
  */
/** @defgroup SDMMC_MMC_Card_Voltage_Range MMC Card Voltage Range definition
  * @{
  */
#define SDMMC_MMC_HIGH_VOLTAGE_RANGE                    0x80FF8000U  /*!< High voltage in byte mode   */
#define SDMMC_MMC_DUAL_VOLTAGE_RANGE                    0x80FF8080U  /*!< Dual voltage in byte mode   */
#define SDMMC_MMC_LOW_VOLTAGE_RANGE                     0x80000080U  /*!< Low voltage in byte mode    */
#define SDMMC_EMMC_HIGH_VOLTAGE_RANGE                   0xC0FF8000U  /*!< High voltage in sector mode */
#define SDMMC_EMMC_DUAL_VOLTAGE_RANGE                   0xC0FF8080U  /*!< Dual voltage in sector mode */
#define SDMMC_EMMC_LOW_VOLTAGE_RANGE                    0xC0000080U  /*!< Low voltage in sector mode  */
#define SDMMC_MMC_INVALID_VOLTAGE_RANGE                 0x0001FF01U  /*!< Invalid voltage Range       */
/**
  * @}
  */

/** @defgroup MMC_Card_Extended_Specific_Data MMC Card Extended Specific Data definition
  * @{
  */
/*------------------------------------  Bit definition for MMC CARD EXT CSD register ---------------------------------*/
#define SDMMC_MMC_EXT_CSD_SECURE_REMOVAL_IDX      16U          /*!< Secure Removal type index           */
#define SDMMC_MMC_EXT_CSD_SECURE_REMOVAL_POS      0U           /*!< Secure Removal type position        */
#define SDMMC_MMC_EXT_CSD_SECURE_REMOVAL_MSK      0x000000FFU  /*!< Secure Removal type msk             */

#define SDMMC_MMC_EXT_CSD_DEVICE_TYPE_IDX         196U         /*!< Device Type index                   */
#define SDMMC_MMC_EXT_CSD_DEVICE_TYPE_POS         8U           /*!< Device Type position                */
#define SDMMC_MMC_EXT_CSD_DEVICE_TYPE_MSK         0x0000FF00U  /*!< Device Type msk                     */

#define SDMMC_MMC_EXT_CSD_DATA_SECTOR_SIZE_IDX    61U          /*!< Data Sector size index              */
#define SDMMC_MMC_EXT_CSD_DATA_SECTOR_SIZE_POS    8U           /*!< Data Sector size position           */
#define SDMMC_MMC_EXT_CSD_DATA_SECTOR_SIZE_MSK    0x0000FF00U  /*!< Data Sector Size msk                */

#define SDMMC_MMC_EXT_CSD_PWR_CLASS_SIZE_IDX      187U         /*!< Power Class index                   */
#define SDMMC_MMC_EXT_CSD_PWR_CLASS_SIZE_POS      24U          /*!< Power Class position                */
#define SDMMC_MMC_EXT_CSD_PWR_CLASS_SIZE_MSK      0xFF000000U  /*!< Power Class msk                     */

#define SDMMC_MMC_EXT_CSD_SECTOR_COUNT_SIZE_IDX   212U         /*!< Sector Count index                  */
#define SDMMC_MMC_EXT_CSD_SECTOR_COUNT_SIZE_POS   0U           /*!< Sector Count position               */
#define SDMMC_MMC_EXT_CSD_SECTOR_COUNT_SIZE_MSK   0xFFFFFFFFU  /*!< Sector Count msk                    */

#define SDMMC_MMC_EXT_CSD_SLEEP_NOTIF_TIME_IDX    216U         /*!< Sleep Notification timeout index    */
#define SDMMC_MMC_EXT_CSD_SLEEP_NOTIF_TIME_POS    0U           /*!< Sleep Notification timeout position */
#define SDMMC_MMC_EXT_CSD_SLEEP_NOTIF_TIME_MSK    0xFFU        /*!< Sleep Notification timeout msk      */

#define SDMMC_MMC_EXT_CSD_S_A_TIMEOUT_IDX         217U         /*!< Sleep Awake timeout index           */
#define SDMMC_MMC_EXT_CSD_S_A_TIMEOUT_POS         8U           /*!< Sleep Awake timeout position        */
#define SDMMC_MMC_EXT_CSD_S_A_TIMEOUT_MSK         0x0000FF00U  /*!< Sleep Awake timeout msk             */

#define SDMMC_MMC_EXT_CSD_PARTITION_SWITCH_TIME_IDX     199U         /*!< Partition switching timing index    */
#define SDMMC_MMC_EXT_CSD_PARTITION_SWITCH_TIME_POS     24U          /*!< Partition switching timing position */
#define SDMMC_MMC_EXT_CSD_PARTITION_SWITCH_TIME_MSK     0xFF000000U  /*!< Partition switching timing msk      */

#define SDMMC_MMC_EXT_CSD_RPMB_SIZE_MULT_IDX            168U         /*!< RPMB Partition size index           */
#define SDMMC_MMC_EXT_CSD_RPMB_SIZE_MULT_POS            0U           /*!< RPMB Partition size position        */
#define SDMMC_MMC_EXT_CSD_RPMB_SIZE_MULT_MSK            0x000000FFU  /*!< RPMB Partition size msk             */

#if defined (VDD_VALUE) && (VDD_VALUE <= 1950U)
#define MMC_VOLTAGE_RANGE                         SDMMC_EMMC_LOW_VOLTAGE_RANGE /*!< EMMC voltage range */
#define SDMMC_MMC_EXT_CSD_PWR_CL_26_IDX           201U        /*!< Power class for 26 MHz at 1.95 V 1 R index    */
#define SDMMC_MMC_EXT_CSD_PWR_CL_26_POS           8U          /*!< Power class for 26 MHz at 1.95 V 1 R position */
#define SDMMC_MMC_EXT_CSD_PWR_CL_26_MSK           0x0000FF00U /*!< 0x0000FF00U                                   */

#define SDMMC_MMC_EXT_CSD_PWR_CL_52_IDX           200U        /*!< Power class for 52 MHz at 1.95 V 1 R index    */
#define SDMMC_MMC_EXT_CSD_PWR_CL_52_POS           0U          /*!< Power class for 52 MHz at 1.95 V 1 R position */
#define SDMMC_MMC_EXT_CSD_PWR_CL_52_MSK           0x000000FFU /*!< 0x000000FFU                                   */

#define SDMMC_MMC_EXT_CSD_PWR_CL_DDR_52_IDX       238U        /*!< Power class for 52MHz, DDR at VCC = 1.95V index    */
#define SDMMC_MMC_EXT_CSD_PWR_CL_DDR_52_POS       16U         /*!< Power class for 52MHz, DDR at VCC = 1.95V position */
#define SDMMC_MMC_EXT_CSD_PWR_CL_DDR_52_MSK       0x00FF0000U /*!< 0x00FF0000U                                        */

#else
#define MMC_VOLTAGE_RANGE                         SDMMC_MMC_HIGH_VOLTAGE_RANGE /*!< MMC voltage range */
#define SDMMC_MMC_EXT_CSD_PWR_CL_26_IDX           203U        /*!< Power class for 26 MHz at 3.6 V 1 R index         */
#define SDMMC_MMC_EXT_CSD_PWR_CL_26_POS           24U         /*!< Power class for 26 MHz at 3.6 V 1 R position      */
#define SDMMC_MMC_EXT_CSD_PWR_CL_26_MSK           0xFF000000U /*!< 0xFF000000U                                       */

#define SDMMC_MMC_EXT_CSD_PWR_CL_52_IDX           202U        /*!< Power class for 52 MHz at 3.6 V 1 R index         */
#define SDMMC_MMC_EXT_CSD_PWR_CL_52_POS           16U         /*!< Power class for 52 MHz at 3.6 V 1 R position      */
#define SDMMC_MMC_EXT_CSD_PWR_CL_52_MSK           0x00FF0000U /*!< 0x00FF0000U                                       */

#define SDMMC_MMC_EXT_CSD_PWR_CL_DDR_52_IDX       239U        /*!< Power class for 52MHz, DDR at VCC = 3.6V index    */
#define SDMMC_MMC_EXT_CSD_PWR_CL_DDR_52_POS       24U         /*!< Power class for 52MHz, DDR at VCC = 3.6V position */
#define SDMMC_MMC_EXT_CSD_PWR_CL_DDR_52_MSK       0xFF000000U /*!< 0xFF000000U                                       */
#endif /* (VDD_VALUE) && (VDD_VALUE <= 1950U)*/

#define SDMMC_MMC_ACCESS_MODE_MSK                 0x60000000U /*!< 0x60000000U MMC access mode mask in OCR register  */
#define SDMMC_MMC_ACCESS_MODE_POS                 29U         /*!< MMC access mode position in OCR register          */
#define SDMMC_MMC_SECTOR_MODE                     0x2U        /*!< MMC sector mode                                   */

/**
  * @}
  */

/** @defgroup MMC_Card_System_Specification_Version MMC Card System specification version definition
  * @{
  */
#define SDMMC_MMC_CARD_SYSTEM_SPEC_VERSION_POS           26U          /*!< MMC Card system spec version position */
#define SDMMC_MMC_CARD_SYSTEM_SPEC_VERSION_MSK           0x3C000000U  /*!< 0x3C000000U                           */
/**
  * @}
  */

/** @defgroup SDMMC_SD_CARD_STATUS_register SDMMC SD Card Status register definition
  * @{
  */
#define SDMMC_SD_CARD_DATA_BUS_WIDTH_POS         30U          /*!< SD card data bus width position              */
#define SDMMC_SD_CARD_DATA_BUS_WIDTH_MSK         0xC0000000U  /*!< 0xC0000000U                                  */
#define SDMMC_SD_CARD_SECURED_MODE_POS           29U          /*!< SD card secured mode position                */
#define SDMMC_SD_CARD_SECURED_MODE_MSK           0x20000000U  /*!< 0x20000000U                                  */
#define SDMMC_SD_CARD_TYPE_POS                   0U           /*!< SD card type position                        */
#define SDMMC_SD_CARD_TYPE_MSK                   0x0000FFFFU  /*!< 0x0000FFFFU                                  */
#define SDMMC_SD_CARD_SIZE_OF_PROTECTED_AREA_POS 0U           /*!< SD card size of protected area position      */
#define SDMMC_SD_CARD_SIZE_OF_PROTECTED_AREA_MSK 0xFFFFFFFFU  /*!< 0xFFFFFFFFU                                  */
#define SDMMC_SD_CARD_SPEED_CLASS_POS            24U          /*!< SD card speed class position                 */
#define SDMMC_SD_CARD_SPEED_CLASS_MSK            0xFF000000U  /*!< 0xFF000000U                                  */
#define SDMMC_SD_CARD_PERFORMANCE_MOVE_POS       16U          /*!< SD card performance of move position         */
#define SDMMC_SD_CARD_PERFORMANCE_MOVE_MSK       0x00FF0000U  /*!< 0x00FF0000U                                  */
#define SDMMC_SD_CARD_AU_SIZE_POS                12U          /*!< SD card allocation unit size position        */
#define SDMMC_SD_CARD_AU_SIZE_MSK                0x0000F000U  /*!< 0x0000F000U                                  */
#define SDMMC_SD_CARD_ERASE_SIZE1_POS            0U           /*!< SD card erase size 1 position                */
#define SDMMC_SD_CARD_ERASE_SIZE1_MSK            0x000000FFU  /*!< 0x000000FFU                                  */
#define SDMMC_SD_CARD_ERASE_SIZE2_POS            24U          /*!< SD card erase size 2 position                */
#define SDMMC_SD_CARD_ERASE_SIZE2_MSK            0xFF000000U  /*!< 0xFF000000U                                  */
#define SDMMC_SD_CARD_ERASE_TIMEOUT_POS          18U          /*!< SD card erase timeout position               */
#define SDMMC_SD_CARD_ERASE_TIMEOUT_MSK          0x00FC0000U  /*!< 0x00FC0000U                                  */
#define SDMMC_SD_CARD_ERASE_OFFSET_POS           16U          /*!< SD card erase offset position                */
#define SDMMC_SD_CARD_ERASE_OFFSET_MSK           0x00030000U  /*!< 0x00030000U                                  */
#define SDMMC_SD_CARD_UHS_SPEED_GRADE_POS        12U          /*!< SD card speed grade of UHS mode position     */
#define SDMMC_SD_CARD_UHS_SPEED_GRADE_MSK        0x0000F000U  /*!< 0x0000F000U                                  */
#define SDMMC_SD_CARD_UHS_AU_SIZE_POS            8U           /*!< SD card size of unit allocation UHS position */
#define SDMMC_SD_CARD_UHS_AU_SIZE_MSK            0x00000F00U  /*!< 0x00000F00U                                  */
#define SDMMC_SD_CARD_VIDEO_SPEED_CLASS_POS      0U           /*!< SD card video speed class value position     */
#define SDMMC_SD_CARD_VIDEO_SPEED_CLASS_MSK      0x000000FFU  /*!< 0x000000FFU                                  */
/**
  * @}
  */

/** @defgroup SDMMC_SD_CARD_SPECIFIC_DATA SDMMC SDMMC SD Card Specific datat definition
  * @{
  */
#define SDMMC_SD_CARD_SDHC_SDXC_CSD_DEVICE_SIZE1_POS    16U          /*!< SD card SDHC SDXC CSD device size position  */
#define SDMMC_SD_CARD_SDHC_SDXC_CSD_DEVICE_SIZE1_MSK    0xFFFF0000U  /*!< 0xFFFF0000U                                 */
#define SDMMC_SD_CARD_SDHC_SDXC_CSD_DEVICE_SIZE2_POS    0U           /*!< SD card CSD device size position            */
#define SDMMC_SD_CARD_SDHC_SDXC_CSD_DEVICE_SIZE2_MSK    0x0000003FU  /*!< 0x0000003FU                                 */
#define SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE1_POS         30U          /*!< SD card SDSC CSD device size position       */
#define SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE1_MSK         0xC0000000U  /*!< 0xC0000000U                                 */
#define SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE2_POS         0U           /*!< SD card SDSC CSD device size position       */
#define SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE2_MSK         0x000003FFU  /*!< 0x000003FFU                                 */
#define SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE_MULTIPLE_POS 15U          /*!< SD card SDSC CSD device multiple position   */
#define SDMMC_SD_CARD_SDSC_CSD_DEVICE_SIZE_MULTIPLE_MSK 0x00038000U  /*!< 0x00038000U                                 */
#define SDMMC_SD_CARD_SDSC_CSD_READ_BL_LEN_POS          16U          /*!< SD card SDSC CSD read block length position */
#define SDMMC_SD_CARD_SDSC_CSD_READ_BL_LEN_MSK          0x000F0000U  /*!< 0x000F0000U                                 */
/**
  * @}
  */

/** @defgroup SDMMC_DATA_BUFFER_STATE SDMMC Data Buffer State definition
  * @{
  */
#define SDMMC_DATA_BUFFER_STATE_NOT_READY    0U  /*!< SDMMC Data Buffer State Not Ready */
#define SDMMC_DATA_BUFFER_STATE_READY        1U  /*!< SDMMC Data Buffer State Ready     */
/**
  * @}
  */

/**
  * @}
  */
/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup SDMMC_Private_Macros SDMMC Private Macros
  * @{
  */
/*! Get SDMMC instance macros */
#if defined (SDMMC2)
#define SDMMC_GET_DLYB_INSTANCE(instance) ((instance == SDMMC1) ? DLYB_SDMMC1 : DLYB_SDMMC2)
#else
#define SDMMC_GET_DLYB_INSTANCE(instance) \
  ({                                      \
    STM32_UNUSED(instance);               \
    DLYB_SDMMC1;                          \
  })
#endif /* SDMMC2 */
/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup SDMMC_CORE_Exported_macros SDMMC_CORE Exported Macros
  * @{
  */
#define SDMMC_READ_REG(instance, reg)               STM32_READ_REG((instance)->reg)
#define SDMMC_SET_PWR_STATE(instance, state)        STM32_MODIFY_REG((instance)->POWER, SDMMC_POWER_PWRCTRL, (state))
#define SDMMC_GET_PWR_STATE(instance)               STM32_READ_BIT((instance)->POWER, SDMMC_POWER_PWRCTRL)
#define SDMMC_ENABLE_VOLTAGE_SWITCH(instance)       STM32_SET_BIT((instance)->POWER, SDMMC_POWER_VSWITCHEN)
#define SDMMC_START_VOLTAGE_SWITCH(instance)        STM32_SET_BIT((instance)->POWER, SDMMC_POWER_VSWITCH)
#define SDMMC_DISABLE_VOLTAGE_SWITCH(instance)      STM32_CLEAR_BIT((instance)->POWER, SDMMC_POWER_VSWITCH \
                                                                    | SDMMC_POWER_VSWITCHEN)
#define SDMMC_SET_DIRECTION_LOW_POLARITY(instance)  STM32_CLEAR_BIT((instance)->POWER, SDMMC_POWER_DIRPOL)
#define SDMMC_SET_DIRECTION_HIGH_POLARITY(instance) STM32_SET_BIT((instance)->POWER, SDMMC_POWER_DIRPOL)
#define SDMMC_READ_FIELD(val, msk, pos)             (((uint32_t)(val) & (msk)) >> (pos))

/**
  * @brief  Enable the SDMMC device interrupt.
  * @param  instance Pointer to SDMMC register base.
  * @param  interrupt specifies the SDMMC interrupt sources to be enabled.
  *         This parameter can be one or a combination of the following values:
  *            @arg SDMMC_IT_CCRCFAIL:   Command response received (CRC check failed) interrupt.
  *            @arg SDMMC_IT_DCRCFAIL:   Data block sent/received (CRC check failed) interrupt.
  *            @arg SDMMC_IT_CTIMEOUT:   Command response timeout interrupt.
  *            @arg SDMMC_IT_DTIMEOUT:   Data timeout interrupt.
  *            @arg SDMMC_IT_TXUNDERR:   Transmit FIFO underrun error interrupt.
  *            @arg SDMMC_IT_RXOVERR:    Received FIFO overrun error interrupt.
  *            @arg SDMMC_IT_CMDREND:    Command response received (CRC check passed) interrupt.
  *            @arg SDMMC_IT_CMDSENT:    Command sent (no response required) interrupt.
  *            @arg SDMMC_IT_DATAEND:    Data end (data counter, DATACOUNT, is zero) interrupt.
  *            @arg SDMMC_IT_DHOLD:      Data transfer Hold interrupt.
  *            @arg SDMMC_IT_DBCKEND:    Data block sent/received (CRC check passed) interrupt.
  *            @arg SDMMC_IT_DABORT:     Data transfer aborted by CMD12 interrupt.
  *            @arg SDMMC_IT_TXFIFOHE:   Transmit FIFO Half Empty interrupt.
  *            @arg SDMMC_IT_RXFIFOHF:   Receive FIFO Half Full interrupt.
  *            @arg SDMMC_IT_RXFIFOF:    Receive FIFO full interrupt.
  *            @arg SDMMC_IT_TXFIFOE:    Transmit FIFO empty interrupt.
  *            @arg SDMMC_IT_BUSYD0END:  End of SDMMC_D0 Busy following a CMD response detected interrupt.
  *            @arg SDMMC_IT_SDIOIT:     SDIO interrupt received interrupt.
  *            @arg SDMMC_IT_ACKFAIL:    Boot Acknowledgment received interrupt.
  *            @arg SDMMC_IT_ACKTIMEOUT: Boot Acknowledgment timeout interrupt.
  *            @arg SDMMC_IT_VSWEND:     Voltage switch critical timing section completion interrupt.
  *            @arg SDMMC_IT_CKSTOP:     SDMMC_CK stopped in Voltage switch procedure interrupt.
  *            @arg SDMMC_IT_IDMABTC:    IDMA buffer transfer complete interrupt.
  */
#define SDMMC_ENABLE_IT(instance, interrupt) ((instance)->MASKR |= (interrupt))

/**
  * @brief  Disable the SDMMC device interrupt.
  * @param  instance Pointer to SDMMC register base.
  * @param  interrupt specifies the SDMMC interrupt sources to be disabled.
  *          This parameter can be one or a combination of the following values:
  *            @arg SDMMC_IT_CCRCFAIL:   Command response received (CRC check failed) interrupt.
  *            @arg SDMMC_IT_DCRCFAIL:   Data block sent/received (CRC check failed) interrupt.
  *            @arg SDMMC_IT_CTIMEOUT:   Command response timeout interrupt.
  *            @arg SDMMC_IT_DTIMEOUT:   Data timeout interrupt.
  *            @arg SDMMC_IT_TXUNDERR:   Transmit FIFO underrun error interrupt.
  *            @arg SDMMC_IT_RXOVERR:    Received FIFO overrun error interrupt.
  *            @arg SDMMC_IT_CMDREND:    Command response received (CRC check passed) interrupt.
  *            @arg SDMMC_IT_CMDSENT:    Command sent (no response required) interrupt.
  *            @arg SDMMC_IT_DATAEND:    Data end (data counter, DATACOUNT, is zero) interrupt.
  *            @arg SDMMC_IT_DHOLD:      Data transfer Hold interrupt.
  *            @arg SDMMC_IT_DBCKEND:    Data block sent/received (CRC check passed) interrupt.
  *            @arg SDMMC_IT_DABORT:     Data transfer aborted by CMD12 interrupt.
  *            @arg SDMMC_IT_TXFIFOHE:   Transmit FIFO Half Empty interrupt.
  *            @arg SDMMC_IT_RXFIFOHF:   Receive FIFO Half Full interrupt.
  *            @arg SDMMC_IT_RXFIFOF:    Receive FIFO full interrupt.
  *            @arg SDMMC_IT_TXFIFOE:    Transmit FIFO empty interrupt.
  *            @arg SDMMC_IT_BUSYD0END:  End of SDMMC_D0 Busy following a CMD response detected interrupt.
  *            @arg SDMMC_IT_SDIOIT:     SDIO interrupt received interrupt.
  *            @arg SDMMC_IT_ACKFAIL:    Boot Acknowledgment received interrupt.
  *            @arg SDMMC_IT_ACKTIMEOUT: Boot Acknowledgment timeout interrupt.
  *            @arg SDMMC_IT_VSWEND:     Voltage switch critical timing section completion interrupt.
  *            @arg SDMMC_IT_CKSTOP:     SDMMC_CK stopped in Voltage switch procedure interrupt.
  *            @arg SDMMC_IT_IDMABTC:    IDMA buffer transfer complete interrupt.
  */
#define SDMMC_DISABLE_IT(instance, interrupt) ((instance)->MASKR &= ~(interrupt))

/**
  * @brief  Checks whether the specified SDMMC flag is set or not.
  * @param  instance Pointer to SDMMC register base.
  * @param  flag specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg SDMMC_FLAG_CCRCFAIL:   Command response received (CRC check failed).
  *            @arg SDMMC_FLAG_DCRCFAIL:   Data block sent/received (CRC check failed).
  *            @arg SDMMC_FLAG_CTIMEOUT:   Command response timeout.
  *            @arg SDMMC_FLAG_DTIMEOUT:   Data timeout.
  *            @arg SDMMC_FLAG_TXUNDERR:   Transmit FIFO underrun error.
  *            @arg SDMMC_FLAG_RXOVERR:    Received FIFO overrun error.
  *            @arg SDMMC_FLAG_CMDREND:    Command response received (CRC check passed).
  *            @arg SDMMC_FLAG_CMDSENT:    Command sent (no response required).
  *            @arg SDMMC_FLAG_DATAEND:    Data end (data counter, DATACOUNT, is zero).
  *            @arg SDMMC_FLAG_DHOLD:      Data transfer Hold.
  *            @arg SDMMC_FLAG_DBCKEND:    Data block sent/received (CRC check passed).
  *            @arg SDMMC_FLAG_DABORT:     Data transfer aborted by CMD12.
  *            @arg SDMMC_FLAG_DPSMACT:    Data path state machine active.
  *            @arg SDMMC_FLAG_CPSMACT:    Command path state machine active.
  *            @arg SDMMC_FLAG_TXFIFOHE:   Transmit FIFO Half Empty.
  *            @arg SDMMC_FLAG_RXFIFOHF:   Receive FIFO Half Full.
  *            @arg SDMMC_FLAG_TXFIFOF:    Transmit FIFO full.
  *            @arg SDMMC_FLAG_RXFIFOF:    Receive FIFO full.
  *            @arg SDMMC_FLAG_TXFIFOE:    Transmit FIFO empty.
  *            @arg SDMMC_FLAG_RXFIFOE:    Receive FIFO empty.
  *            @arg SDMMC_FLAG_BUSYD0:     Inverted value of SDMMC_D0 line (Busy).
  *            @arg SDMMC_FLAG_BUSYD0END:  End of SDMMC_D0 Busy following a CMD response detected.
  *            @arg SDMMC_FLAG_SDIOIT:     SDIO interrupt received.
  *            @arg SDMMC_FLAG_ACKFAIL:    Boot Acknowledgment received.
  *            @arg SDMMC_FLAG_ACKTIMEOUT: Boot Acknowledgment timeout.
  *            @arg SDMMC_FLAG_VSWEND:     Voltage switch critical timing section completion.
  *            @arg SDMMC_FLAG_CKSTOP:     SDMMC_CK stopped in Voltage switch procedure.
  *            @arg SDMMC_FLAG_IDMATE:     IDMA transfer error.
  *            @arg SDMMC_FLAG_IDMABTC:    IDMA buffer transfer complete.
  * @retval The new state of SDMMC_FLAG (SET or RESET).
  */
#define SDMMC_IS_ACTIVE_FLAG(instance, flag) (((instance)->STAR & (flag)) != 0U)

/**
  * @brief  Clears the SDMMC pending flags.
  * @param  instance Pointer to SDMMC register base.
  * @param  flag specifies the flag to clear.
  *          This parameter can be one or a combination of the following values:
  *            @arg SDMMC_FLAG_CCRCFAIL:   Command response received (CRC check failed).
  *            @arg SDMMC_FLAG_DCRCFAIL:   Data block sent/received (CRC check failed).
  *            @arg SDMMC_FLAG_CTIMEOUT:   Command response timeout.
  *            @arg SDMMC_FLAG_DTIMEOUT:   Data timeout.
  *            @arg SDMMC_FLAG_TXUNDERR:   Transmit FIFO underrun error.
  *            @arg SDMMC_FLAG_RXOVERR:    Received FIFO overrun error.
  *            @arg SDMMC_FLAG_CMDREND:    Command response received (CRC check passed).
  *            @arg SDMMC_FLAG_CMDSENT:    Command sent (no response required).
  *            @arg SDMMC_FLAG_DATAEND:    Data end (data counter, DATACOUNT, is zero).
  *            @arg SDMMC_FLAG_DHOLD:      Data transfer Hold.
  *            @arg SDMMC_FLAG_DBCKEND:    Data block sent/received (CRC check passed).
  *            @arg SDMMC_FLAG_DABORT:     Data transfer aborted by CMD12.
  *            @arg SDMMC_FLAG_BUSYD0END:  End of SDMMC_D0 Busy following a CMD response detected.
  *            @arg SDMMC_FLAG_SDIOIT:     SDIO interrupt received.
  *            @arg SDMMC_FLAG_ACKFAIL:    Boot Acknowledgment received.
  *            @arg SDMMC_FLAG_ACKTIMEOUT: Boot Acknowledgment timeout.
  *            @arg SDMMC_FLAG_VSWEND:     Voltage switch critical timing section completion.
  *            @arg SDMMC_FLAG_CKSTOP:     SDMMC_CK stopped in Voltage switch procedure.
  *            @arg SDMMC_FLAG_IDMATE:     IDMA transfer error.
  *            @arg SDMMC_FLAG_IDMABTC:    IDMA buffer transfer complete.
  */
#define SDMMC_CLEAR_FLAG(instance, flag) ((instance)->ICR = (flag))

/**
  * @brief  Checks whether the specified SDMMC interrupt has occurred or not.
  * @param  instance Pointer to SDMMC register base.
  * @param  interrupt specifies the SDMMC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg SDMMC_IT_CCRCFAIL:   Command response received (CRC check failed) interrupt.
  *            @arg SDMMC_IT_DCRCFAIL:   Data block sent/received (CRC check failed) interrupt.
  *            @arg SDMMC_IT_CTIMEOUT:   Command response timeout interrupt.
  *            @arg SDMMC_IT_DTIMEOUT:   Data timeout interrupt.
  *            @arg SDMMC_IT_TXUNDERR:   Transmit FIFO underrun error interrupt.
  *            @arg SDMMC_IT_RXOVERR:    Received FIFO overrun error interrupt.
  *            @arg SDMMC_IT_CMDREND:    Command response received (CRC check passed) interrupt.
  *            @arg SDMMC_IT_CMDSENT:    Command sent (no response required) interrupt.
  *            @arg SDMMC_IT_DATAEND:    Data end (data counter, DATACOUNT, is zero) interrupt.
  *            @arg SDMMC_IT_DHOLD:      Data transfer Hold interrupt.
  *            @arg SDMMC_IT_DBCKEND:    Data block sent/received (CRC check passed) interrupt.
  *            @arg SDMMC_IT_DABORT:     Data transfer aborted by CMD12 interrupt.
  *            @arg SDMMC_IT_TXFIFOHE:   Transmit FIFO Half Empty interrupt.
  *            @arg SDMMC_IT_RXFIFOHF:   Receive FIFO Half Full interrupt.
  *            @arg SDMMC_IT_RXFIFOF:    Receive FIFO full interrupt.
  *            @arg SDMMC_IT_TXFIFOE:    Transmit FIFO empty interrupt.
  *            @arg SDMMC_IT_BUSYD0END:  End of SDMMC_D0 Busy following a CMD response detected interrupt.
  *            @arg SDMMC_IT_SDIOIT:     SDIO interrupt received interrupt.
  *            @arg SDMMC_IT_ACKFAIL:    Boot Acknowledgment received interrupt.
  *            @arg SDMMC_IT_ACKTIMEOUT: Boot Acknowledgment timeout interrupt.
  *            @arg SDMMC_IT_VSWEND:     Voltage switch critical timing section completion interrupt.
  *            @arg SDMMC_IT_CKSTOP:     SDMMC_CK stopped in Voltage switch procedure interrupt.
  *            @arg SDMMC_IT_IDMABTC:    IDMA buffer transfer complete interrupt.
  * @retval The new state of SDMMC_IT (SET or RESET).
  */
#define SDMMC_GET_IT(instance, interrupt) (((instance)->STAR &(interrupt)) == (interrupt))

/**
  * @brief  Clears the SDMMC's interrupt pending bits.
  * @param  instance Pointer to SDMMC register base.
  * @param  interrupt specifies the interrupt pending bit to clear.
  *          This parameter can be one or a combination of the following values:
  *            @arg SDMMC_IT_CCRCFAIL:   Command response received (CRC check failed) interrupt.
  *            @arg SDMMC_IT_DCRCFAIL:   Data block sent/received (CRC check failed) interrupt.
  *            @arg SDMMC_IT_CTIMEOUT:   Command response timeout interrupt.
  *            @arg SDMMC_IT_DTIMEOUT:   Data timeout interrupt.
  *            @arg SDMMC_IT_TXUNDERR:   Transmit FIFO underrun error interrupt.
  *            @arg SDMMC_IT_RXOVERR:    Received FIFO overrun error interrupt.
  *            @arg SDMMC_IT_CMDREND:    Command response received (CRC check passed) interrupt.
  *            @arg SDMMC_IT_CMDSENT:    Command sent (no response required) interrupt.
  *            @arg SDMMC_IT_DATAEND:    Data end (data counter, DATACOUNT, is zero) interrupt.
  *            @arg SDMMC_IT_DHOLD:      Data transfer Hold interrupt.
  *            @arg SDMMC_IT_DBCKEND:    Data block sent/received (CRC check passed) interrupt.
  *            @arg SDMMC_IT_DABORT:     Data transfer aborted by CMD12 interrupt.
  *            @arg SDMMC_IT_BUSYD0END:  End of SDMMC_D0 Busy following a CMD response detected interrupt.
  *            @arg SDMMC_IT_SDIOIT:     SDIO interrupt received interrupt.
  *            @arg SDMMC_IT_ACKFAIL:    Boot Acknowledgment received interrupt.
  *            @arg SDMMC_IT_ACKTIMEOUT: Boot Acknowledgment timeout interrupt.
  *            @arg SDMMC_IT_VSWEND:     Voltage switch critical timing section completion interrupt.
  *            @arg SDMMC_IT_CKSTOP:     SDMMC_CK stopped in Voltage switch procedure interrupt.
  *            @arg SDMMC_IT_IDMABTC:    IDMA buffer transfer complete interrupt.
  */
#define SDMMC_CLEAR_IT(instance, interrupt) ((instance)->ICR = (interrupt))

/**
  * @brief  Enable Start the SD I/O Read Wait operation.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_START_READWAIT_ENABLE(instance) ((instance)->DCTRL |= SDMMC_DCTRL_RWSTART)

/**
  * @brief  Disable Start the SD I/O Read Wait operations.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_START_READWAIT_DISABLE(instance) ((instance)->DCTRL &= ~SDMMC_DCTRL_RWSTART)

/**
  * @brief  Enable Start the SD I/O Read Wait operation.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_STOP_READWAIT_ENABLE(instance) ((instance)->DCTRL |= SDMMC_DCTRL_RWSTOP)

/**
  * @brief  Disable Stop the SD I/O Read Wait operations.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_STOP_READWAIT_DISABLE(instance) ((instance)->DCTRL &= ~SDMMC_DCTRL_RWSTOP)

/**
  * @brief  Enable the SD I/O Mode Operation.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_OPERATION_ENABLE(instance) ((instance)->DCTRL |= SDMMC_DCTRL_SDIOEN)

/**
  * @brief  Disable the SD I/O Mode Operation.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_OPERATION_DISABLE(instance) ((instance)->DCTRL &= ~SDMMC_DCTRL_SDIOEN)

/**
  * @brief  Disable FIFO reset Operation.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_FIFORST_DISABLE(instance) ((instance)->DCTRL &= ~SDMMC_DCTRL_FIFORST)

/**
  * @brief  Enable FIFO reset Operation.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_FIFORST_ENABLE(instance)  ((instance)->DCTRL |= SDMMC_DCTRL_FIFORST)

/**
  * @brief  Clear SDMMC data control register.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_CLEAR_DCTRL(instance) STM32_CLEAR_REG((instance)->DCTRL)

/**
  * @brief  Enable the SD I/O Suspend command sending.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_SUSPEND_CMD_ENABLE(instance) ((instance)->CMDR |= SDMMC_CMDR_CMDSUSPEND)

/**
  * @brief  Disable the SD I/O Suspend command sending.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_SUSPEND_CMD_DISABLE(instance) ((instance)->CMDR &= ~SDMMC_CMDR_CMDSUSPEND)

/**
  * @brief  Enable the CMDTRANS mode.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_CMDTRANS_ENABLE(instance) ((instance)->CMDR |= SDMMC_CMDR_CMDTRANS)

/**
  * @brief  Disable the CMDTRANS mode.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_CMDTRANS_DISABLE(instance) ((instance)->CMDR &= ~SDMMC_CMDR_CMDTRANS)

/**
  * @brief  Enable the CMDSTOP mode.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_CMDSTOP_ENABLE(instance) ((instance)->CMDR |= SDMMC_CMDR_CMDSTOP)

/**
  * @brief  Disable the CMDSTOP mode.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_CMDSTOP_DISABLE(instance) ((instance)->CMDR &= ~SDMMC_CMDR_CMDSTOP)

/**
  * @brief  Clear SDMMC  data length register.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_CLEAR_DLEN(instance) STM32_CLEAR_REG((instance)->DLENR)

/**
  * @brief  Set SDMMC clock control register.
  * @param  instance Pointer to SDMMC register base.
  * @param  flag Specifies the flag to clear.
  *          This parameter can be one or a combination of the following @ref SDMMC_CORE_Flags_sources.
  */
#define SDMMC_SET_CLKCR(instance, flag) STM32_SET_BIT(((instance)->CLKCR), flag)

/**
  * @brief  Set SDMMC DMA control register.
  * @param  instance Pointer to SDMMC register base.
  * @param  flag Specifies the flag to clear.
  *          This parameter can be one or a combination of @ref SDMMC_Internal_DMA_Mode.
  */
#define SDMMC_SET_IDMACTRL(instance, flag) STM32_SET_BIT(((instance)->IDMACTRLR), flag)

/**
  * @brief  Clear SDMMC DMA control register.
  * @param  instance Pointer to SDMMC register base.
  */
#define SDMMC_CLEAR_IDMACTRL(instance) STM32_CLEAR_REG(((instance)->IDMACTRLR))

/**
  * @brief  Modify SDMMC clock control register.
  * @param  instance Pointer to SDMMC register base.
  * @param  clear_mask Specifies the bits to clear.
  * @param  set_mask Specifies the bits to set.
  */
#define SDMMC_MODIFY_CLKCR(instance, clear_mask, set_mask) STM32_MODIFY_REG((instance)->CLKCR, clear_mask, set_mask)
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup SDMMC_CORE_Exported_Functions SDMMC Core Exported Functions
  * @{
  */
/** @defgroup SDMMC_CORE_Group1 Set and Get configurations functions
  * @{
  */
void SDMMC_SetConfig(SDMMC_TypeDef *sdmmcx, const sdmmc_config_t *p_config);
void SDMMC_GetConfig(const SDMMC_TypeDef *sdmmcx, sdmmc_config_t *p_config);
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Group2 Peripheral Control functions
  * @{
  */
/* Command path state machine (CPSM) management functions */
void SDMMC_SendCommand(SDMMC_TypeDef *sdmmcx, const sdmmc_cmd_init_t *p_command);

/* Data path state machine (DPSM) management functions */
void SDMMC_ConfigData(SDMMC_TypeDef *sdmmcx, const sdmmc_data_ctrl_t *p_data_ctrl);
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Group3 SDMMC Commands management and Data transfers functions
  * @{
  */
uint32_t SDMMC_SendBlockLengthCmd(SDMMC_TypeDef *sdmmcx, uint32_t block_size);
uint32_t SDMMC_SendBlockCountCmd(SDMMC_TypeDef *SDMMCx, uint32_t block_count);
uint32_t SDMMC_SendReadBlocksCmd(SDMMC_TypeDef *sdmmcx, uint32_t read_addr, uint32_t read_blk_type);
uint32_t SDMMC_SendWriteBlocksCmd(SDMMC_TypeDef *sdmmcx, uint32_t write_addr, uint32_t write_blk_type);
uint32_t SDMMC_SendEraseCmd(SDMMC_TypeDef *sdmmcx, uint32_t start_addr, uint32_t cmd_erase, uint32_t erase_timeout_ms);
uint32_t SDMMC_SendStopTransferCmd(SDMMC_TypeDef *sdmmcx, uint32_t stop_transfer_timeout_ms);
uint32_t SDMMC_SendSelDeselCmd(SDMMC_TypeDef *sdmmcx, uint32_t addr);
uint32_t SDMMC_SendGoIdleStateCmd(SDMMC_TypeDef *sdmmcx);
uint32_t SDMMC_SendOperCondCmd(SDMMC_TypeDef *sdmmcx);
uint32_t SDMMC_SendAppCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument);
uint32_t SDMMC_SendAppOperCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument);
uint32_t SDMMC_SendBusWidthCmd(SDMMC_TypeDef *sdmmcx, uint32_t bus_width);
uint32_t SDMMC_SendSCRCmd(SDMMC_TypeDef *sdmmcx);
uint32_t SDMMC_SendCIDCmd(SDMMC_TypeDef *sdmmcx);
uint32_t SDMMC_SendCSDCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument);
uint32_t SDMMC_SD_SendRelativeAddrCmd(SDMMC_TypeDef *sdmmcx, uint16_t *p_rca);
uint32_t SDMMC_SendStatusCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument);
uint32_t SDMMC_SendStatusRegisterCmd(SDMMC_TypeDef *sdmmcx);
uint32_t SDMMC_SendSwitchCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument);
uint32_t SDMMC_MMC_SendSleepCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument);
uint32_t SDMMC_SendVoltageSwitchCmd(SDMMC_TypeDef *sdmmcx);
uint32_t SDMMC_SendOpConditionCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument);
uint32_t SDMMC_MMC_SendRelativeAddrCmd(SDMMC_TypeDef *sdmmcx, uint16_t rca);
uint32_t SDMMC_MMC_SendEXTCSDCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument);

uint32_t SDMMC_SDIO_SendReadWriteDirectCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument, uint8_t *p_response);
uint32_t SDMMC_SDIO_SendReadWriteExtendedCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument);
uint32_t SDMMC_SDIO_SendOperationconditionCmd(SDMMC_TypeDef *sdmmcx, uint32_t argument, uint32_t *p_response);
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Group4 SDMMC Responses management functions
  * @{
  */
uint32_t SDMMC_GetCmdResp1(SDMMC_TypeDef *sdmmcx, uint8_t cmd, uint32_t timeout_ms);
uint32_t SDMMC_GetCmdResp2(SDMMC_TypeDef *sdmmcx);
uint32_t SDMMC_GetCmdResp3(SDMMC_TypeDef *sdmmcx);
uint32_t SDMMC_GetCmdResp4(SDMMC_TypeDef *sdmmcx, uint32_t *p_resp);
uint32_t SDMMC_GetCmdResp5(SDMMC_TypeDef *sdmmcx, uint8_t sdio_cmd, uint8_t *p_data);
uint32_t SDMMC_GetCmdResp6(SDMMC_TypeDef *sdmmcx, uint8_t cmd, uint16_t *p_rca);
uint32_t SDMMC_GetCmdResp7(SDMMC_TypeDef *sdmmcx);
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Group5 SDMMC time calculation functions
  * @{
  */
void SDMMC_DelayMs(const SDMMC_TypeDef *sdmmcx, uint32_t delay_ms);
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Group6 Read, Write and Get command response functions.
  * @{
  */
/**
  * @brief  Read data (word) from Rx FIFO in blocking mode (polling).
  * @param  sdmmcx Pointer to SDMMC register base.
  * @retval uint32_t data.
  */
__STATIC_INLINE uint32_t SDMMC_ReadFIFO(const SDMMC_TypeDef *sdmmcx)
{
  return (sdmmcx->FIFOR[0]);
}

/**
  * @brief Write data (word) to Tx FIFO in blocking mode (polling).
  * @param sdmmcx Pointer to SDMMC register base.
  * @param data   Specifies the data to put in FIFO.
  */
__STATIC_INLINE void SDMMC_WriteFIFO(SDMMC_TypeDef *sdmmcx, uint32_t data)
{
  sdmmcx->FIFOR[0] = data;
}

/**
  * @brief Return the command index of last command for which response received.
  * @param sdmmcx Pointer to SDMMC register base.
  * @retval Command Index of the last command response received.
  */
__STATIC_INLINE uint8_t SDMMC_GetCommandResponse(const SDMMC_TypeDef *sdmmcx)
{
  return (uint8_t)(sdmmcx->RESPCMDR);
}

/**
  * @brief Return the response received from the card for the last command.
  * @param sdmmcx       Pointer to SDMMC register base.
  * @param response_reg Specifies the SDMMC response register.
  *         This parameter can be one of the following values:
  *           @arg SDMMC_RESP1: Response Register 1.
  *           @arg SDMMC_RESP2: Response Register 2.
  *           @arg SDMMC_RESP3: Response Register 3.
  *           @arg SDMMC_RESP4: Response Register 4.
  * @retval The Corresponding response register value.
  */
__STATIC_INLINE uint32_t SDMMC_GetResponse(const SDMMC_TypeDef *sdmmcx, uint32_t response_reg)
{
  return (*(__IO uint32_t *)((uint32_t)(&(sdmmcx->RESP1R)) + response_reg));
}

/**
  * @brief Returns number of remaining data bytes to be transferred.
  * @param sdmmcx Pointer to SDMMC register base.
  * @retval Number of remaining data bytes to be transferred.
  */
__STATIC_INLINE uint32_t SDMMC_GetDataCounter(const SDMMC_TypeDef *sdmmcx)
{
  return (sdmmcx->DCNTR);
}

/**
  * @brief Sets one of the two options of inserting read wait interval.
  * @param sdmmcx               Pointer to SDMMC register base.
  * @param sdmmc_read_wait_mode SDMMC Read Wait operation mode.
  *         This parameter can be:
  *           @arg SDMMC_READ_WAIT_MODE_CLK: Read Wait control by stopping SDMMCCLK.
  *           @arg SDMMC_READ_WAIT_MODE_DATA2: Read Wait control using SDMMC_DATA2.
  */
__STATIC_INLINE void SDMMC_SetSDMMCReadWaitMode(SDMMC_TypeDef *sdmmcx, uint32_t sdmmc_read_wait_mode)
{
  /* Set SDMMC read wait mode */
  STM32_MODIFY_REG(sdmmcx->DCTRL, SDMMC_DCTRL_RWMOD, sdmmc_read_wait_mode);
}
/**
  * @}
  */

/** @defgroup SDMMC_CORE_Group7 SDMMC Linked-List functions
  * @{
  */
/**
  * @brief Set SDMMC linked list node data buffer state.
  * @param node_offset node offset value.
  * @param state       data buffer state.
  */
__STATIC_INLINE void SDMMC_SetNodeDataBufferState(uint32_t node_offset, uint32_t state)
{
  STM32_MODIFY_REG((*(uint32_t *) node_offset), SDMMC_IDMALAR_ABR, state << SDMMC_IDMALAR_ABR_Pos);
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
#endif /* SDMMC1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif
#endif /* STM32H7PXX_SDMMC_CORE_H */
