/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_mmc.h
  * @brief   Header file of MMC HAL module.
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
#ifndef STM32H7PXX_HAL_MMC_H
#define STM32H7PXX_HAL_MMC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#if defined (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1)
/* Include Q module for linked-list management with associated features */
#ifndef USE_HAL_Q_BASE_OFFSET_ADDR_MODE
#define USE_HAL_Q_BASE_OFFSET_ADDR_MODE (1U)
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

#ifndef USE_HAL_Q_CIRCULAR_LINK
#define USE_HAL_Q_CIRCULAR_LINK    (1U)
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#include "stm32h7pxx_hal_q.h"
#endif /* (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1) */

#include "stm32h7pxx_sdmmc_core.h"
#include "stm32h7pxx_dlyb_core.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */
#if defined(SDMMC1)

/** @defgroup MMC MMC
  * @{
  */
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup MMC_Exported_Constants HAL MMC Constants
  * @{
  */
/** @defgroup MMC_Transfer_Timeout MMC Transfer Timeout definition
  * @{
  */
#define HAL_MMC_DATA_MAX_TIMEOUT      0xFFFFFFFFU /*!< MMC data timeout          */
#define HAL_MMC_STOP_XFER_MAX_TIMEOUT 500U        /*!< MMC erase timeout 500ms   */
#define HAL_MMC_ERASE_MAX_TIMEOUT     63000U      /*!< MMC max erase timeout 63s */
/**
  * @}
  */

/** @defgroup MMC_Error_Codes MMC Error Codes definition
  * @{
  */
#define HAL_MMC_ERROR_NONE                     SDMMC_ERROR_NONE                   /*!< No error                                                     */
#define HAL_MMC_ERROR_CMD_CRC_FAIL             SDMMC_ERROR_CMD_CRC_FAIL           /*!< Command response received (but CRC check failed)             */
#define HAL_MMC_ERROR_DATA_CRC_FAIL            SDMMC_ERROR_DATA_CRC_FAIL          /*!< Data block sent/received (CRC check failed)                  */
#define HAL_MMC_ERROR_CMD_RSP_TIMEOUT          SDMMC_ERROR_CMD_RSP_TIMEOUT        /*!< Command response timeout                                     */
#define HAL_MMC_ERROR_DATA_TIMEOUT             SDMMC_ERROR_DATA_TIMEOUT           /*!< Data timeout                                                 */
#define HAL_MMC_ERROR_TX_UNDERRUN              SDMMC_ERROR_TX_UNDERRUN            /*!< Transmit FIFO underrun                                       */
#define HAL_MMC_ERROR_RX_OVERRUN               SDMMC_ERROR_RX_OVERRUN             /*!< Receive FIFO overrun                                         */
#define HAL_MMC_ERROR_ADDR_MISALIGNED          SDMMC_ERROR_ADDR_MISALIGNED        /*!< Misaligned address                                           */
#define HAL_MMC_ERROR_BLOCK_LEN_ERR            SDMMC_ERROR_BLOCK_LEN_ERR          /*!< Transferred block length is not allowed for the card or the
                                               number of transferred bytes does not match the block length  */
#define HAL_MMC_ERROR_ERASE_SEQ_ERR            SDMMC_ERROR_ERASE_SEQ_ERR          /*!< An error in the sequence of erase command occurs             */
#define HAL_MMC_ERROR_BAD_ERASE_PARAM          SDMMC_ERROR_BAD_ERASE_PARAM        /*!< An invalid selection for erase groups                        */
#define HAL_MMC_ERROR_WRITE_PROT_VIOLATION     SDMMC_ERROR_WRITE_PROT_VIOLATION   /*!< Attempt to program a write protect block                     */
#define HAL_MMC_ERROR_LOCK_UNLOCK_FAILED       SDMMC_ERROR_LOCK_UNLOCK_FAILED     /*!< Sequence or password error has been detected in unlock
                                               command or if there was an attempt to access a locked card   */
#define HAL_MMC_ERROR_COM_CRC_FAILED           SDMMC_ERROR_COM_CRC_FAILED         /*!< CRC check of the previous command failed                     */
#define HAL_MMC_ERROR_ILLEGAL_CMD              SDMMC_ERROR_ILLEGAL_CMD            /*!< Command is not legal for the card state                      */
#define HAL_MMC_ERROR_CARD_ECC_FAILED          SDMMC_ERROR_CARD_ECC_FAILED        /*!< Card internal ECC was applied but failed to correct the data */
#define HAL_MMC_ERROR_CC_ERR                   SDMMC_ERROR_CC_ERR                 /*!< Internal card controller error                               */
#define HAL_MMC_ERROR_GENERAL_UNKNOWN_ERR      SDMMC_ERROR_GENERAL_UNKNOWN_ERR    /*!< General or unknown error                                     */
#define HAL_MMC_ERROR_STREAM_READ_UNDERRUN     SDMMC_ERROR_STREAM_READ_UNDERRUN   /*!< The card could not sustain data reading in stream mode       */
#define HAL_MMC_ERROR_STREAM_WRITE_OVERRUN     SDMMC_ERROR_STREAM_WRITE_OVERRUN   /*!< The card could not sustain data programming in stream mode   */
#define HAL_MMC_ERROR_CID_CSD_OVERWRITE        SDMMC_ERROR_CID_CSD_OVERWRITE      /*!< CID/CSD overwrite error                                      */
#define HAL_MMC_ERROR_WP_ERASE_SKIP            SDMMC_ERROR_WP_ERASE_SKIP          /*!< Only partial address space was erased                        */
#define HAL_MMC_ERROR_CARD_ECC_DISABLED        SDMMC_ERROR_CARD_ECC_DISABLED      /*!< Command has been executed without using internal ECC         */
#define HAL_MMC_ERROR_ERASE_RESET              SDMMC_ERROR_ERASE_RESET            /*!< Erase sequence was cleared before executing because an out
                                               of erase sequence command was received                       */
#define HAL_MMC_ERROR_AKE_SEQ_ERR              SDMMC_ERROR_AKE_SEQ_ERR            /*!< Error in sequence of authentication                          */
#define HAL_MMC_ERROR_INVALID_VOLTRANGE        SDMMC_ERROR_INVALID_VOLTRANGE      /*!< Error in case of invalid voltage range                       */
#define HAL_MMC_ERROR_ADDR_OUT_OF_RANGE        SDMMC_ERROR_ADDR_OUT_OF_RANGE      /*!< Error when addressed block is out of range                   */
#define HAL_MMC_ERROR_REQUEST_NOT_APPLICABLE   SDMMC_ERROR_REQUEST_NOT_APPLICABLE /*!< Error when command request is not applicable                 */
#define HAL_MMC_ERROR_INVALID_PARAM            SDMMC_ERROR_INVALID_PARAMETER      /*!< the used parameter is not valid                              */
#define HAL_MMC_ERROR_UNSUPPORTED_FEATURE      SDMMC_ERROR_UNSUPPORTED_FEATURE    /*!< Error when feature is not supported                          */
#define HAL_MMC_ERROR_BUSY                     SDMMC_ERROR_BUSY                   /*!< Error when transfer process is busy                          */
#define HAL_MMC_ERROR_DMA                      SDMMC_ERROR_DMA                    /*!< Error while DMA transfer                                     */
#define HAL_MMC_ERROR_TIMEOUT                  SDMMC_ERROR_TIMEOUT                /*!< Timeout error                                                */

#define HAL_MMC_RPMB_OPERATION_OK                      ((uint16_t)0x0000U)          /*!< MMC Card Rpmb operation OK                                                                        */
#define HAL_MMC_RPMB_GENERAL_FAILURE                   ((uint16_t)(1UL << 0x0000U)) /*!< MMC Card Rpmb general failure                                                                     */
#define HAL_MMC_RPMB_AUTHENTICATION_FAILURE            ((uint16_t)(1UL << 0x0001U)) /*!< MMC Card Rpmb authentication failure (MAC comparison not matching, MAC calculation failure)       */
#define HAL_MMC_RPMB_COUNTER_FAILURE                   ((uint16_t)(1UL << 0x0002U)) /*!< MMC Card Rpmb counter failure (Counter not matching in comparison, counter incrementing failure)  */
#define HAL_MMC_RPMB_ADDRESS_FAILURE                   ((uint16_t)(1UL << 0x0003U)) /*!< MMC Card Rpmb address failure (Address out of range, wrong address alignment)                     */
#define HAL_MMC_RPMB_WRITE_FAILURE                     ((uint16_t)(1UL << 0x0004U)) /*!< MMC Card Rpmb write failure (data/counter/result failure)                                         */
#define HAL_MMC_RPMB_READ_FAILURE                      ((uint16_t)(1UL << 0x0005U)) /*!< MMC Card Rpmb read failure (data/counter/result failure)                                          */
#define HAL_MMC_RPMB_AUTHENTICATION_KEY_NOT_PROGRAMMED ((uint16_t)(1UL << 0x0006U)) /*!< MMC Card Rpmb authentication key not yet programmed                                               */
#define HAL_MMC_RPMB_WRITE_COUNTER_EXPIRED             ((uint16_t)(1UL << 0x0007U)) /*!< MMC Card Rpmb write counter has expired                                                           */
/**
  * @}
  */

/**
  * @}
  */
/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup MMC_Exported_Types HAL MMC Types
  * @{
  */

/*! MMC Card instance */
typedef enum
{
  HAL_MMC_CARD_1 = SDMMC1_BASE, /*!< HAL MMC card instance 1 */
#if defined (SDMMC2)
  HAL_MMC_CARD_2 = SDMMC2_BASE  /*!< HAL MMC card instance 2 */
#endif /* SDMMC2 */
} hal_mmc_t;

/*! MMC Card global state */
typedef enum
{
  HAL_MMC_STATE_RESET        = (0U),         /*!< MMC card not yet initialized or disabled */
  HAL_MMC_STATE_INIT         = (1UL << 31U), /*!< MMC card initialized but not configured  */
  HAL_MMC_STATE_CARD_REMOVED = (1UL << 30U), /*!< MMC card removed                         */
  HAL_MMC_STATE_IDLE         = (1UL << 29U), /*!< MMC card configured and ready for use    */
  HAL_MMC_STATE_ACTIVE       = (1UL << 28U), /*!< MMC card operation IO ongoing            */
  HAL_MMC_STATE_ABORT        = (1UL << 27U)  /*!< MMC card is aborting the current process */
} hal_mmc_state_t;

/*! MMC Card internal State */
typedef enum
{
  HAL_MMC_CARD_IDLE           = 0x00U, /*!< MMC card is in idle state (can't be checked by CMD13)           */
  HAL_MMC_CARD_READY          = 0x01U, /*!< MMC card state is ready (can't be checked by CMD13)             */
  HAL_MMC_CARD_IDENTIFICATION = 0x02U, /*!< MMC card is in identification state (can't be checked by CMD13) */
  HAL_MMC_CARD_STANDBY        = 0x03U, /*!< MMC card is in standby state                                    */
  HAL_MMC_CARD_TRANSFER       = 0x04U, /*!< MMC card is in transfer state                                   */
  HAL_MMC_CARD_SENDING        = 0x05U, /*!< MMC card is sending an operation                                */
  HAL_MMC_CARD_RECEIVING      = 0x06U, /*!< MMC card is receiving operation information                     */
  HAL_MMC_CARD_PROGRAMMING    = 0x07U, /*!< MMC card is in programming state                                */
  HAL_MMC_CARD_DISCONNECTED   = 0x08U, /*!< MMC card is disconnected                                        */
  HAL_MMC_CARD_BUSTEST        = 0x09U, /*!< MMC card is in bus test state                                   */
  HAL_MMC_CARD_SLEEP          = 0x0AU, /*!< MMC card is in sleep state (can't be checked by CMD13)          */
  HAL_MMC_CARD_ERROR          = 0xFFU  /*!< MMC card response Error (can't be checked by CMD13)             */
} hal_mmc_card_state_t;

/*!  MMC secure removal type */
typedef enum
{
  HAL_MMC_SRT_ERASE                   = 0x01U, /*!< Information removed by an erase                                                                */
  HAL_MMC_SRT_WRITE_CHAR_ERASE        = 0x02U, /*!< Information removed by an overwriting with a character followed by an erase                    */
  HAL_MMC_SRT_WRITE_CHAR_COMPL_RANDOM = 0x04U, /*!< Information removed by an overwriting with a character, its complement then a random character */
  HAL_MMC_SRT_VENDOR_DEFINED          = 0x08U  /*!< Information removed using a vendor defined                                                     */
} hal_mmc_secure_removal_type_t;

/*! MMC erase type */
typedef enum
{
  HAL_MMC_ERASE_DEFAULT           = 0x00000000U, /*!< Erase the erase groups identified by CMD35 & 36                                   */
  HAL_MMC_ERASE_TRIM              = 0x00000001U, /*!< Erase the write blocks identified by CMD35 & 36                                   */
  HAL_MMC_ERASE_DISCARD           = 0x00000003U, /*!< Discard the write blocks identified by CMD35 & 36                                 */
  HAL_MMC_ERASE_SECURE            = 0x80000000U, /*!< Perform a secure purge according SRT on the erase groups identified by CMD35 & 36 */
  HAL_MMC_ERASE_SECURE_TRIM_STEP1 = 0x80000001U, /*!< Mark the write blocks identified by CMD35 & 36 for secure erase                   */
  HAL_MMC_ERASE_SECURE_TRIM_STEP2 = 0x80008000U  /*!< Perform a secure purge according SRT on the write blocks previously identified    */
} hal_mmc_erase_type_t;

/*! MMC Card Speed mode */
typedef enum
{
  HAL_MMC_SPEED_MODE_AUTO    = SDMMC_SPEED_MODE_AUTO,    /*!< Max speed mode supported by the card */
  HAL_MMC_SPEED_MODE_DEFAULT = SDMMC_SPEED_MODE_DEFAULT, /*!< Default Speed (MMC @ 26MHz)          */
  HAL_MMC_SPEED_MODE_HIGH    = SDMMC_SPEED_MODE_HIGH,    /*!< High Speed (MMC @ 52 MHz)            */
  HAL_MMC_SPEED_MODE_DDR     = SDMMC_SPEED_MODE_DDR      /*!< High Speed DDR (MMC DDR @ 52 MHz)    */
} hal_mmc_speed_mode_t;

#if defined (USE_HAL_MMC_GET_SPEC_VERSION) && (USE_HAL_MMC_GET_SPEC_VERSION == 1)
/*! MMC Card Specification version */
typedef enum
{
  HAL_MMC_SPECIFICATION_VERSION_1_2     = 0x00U, /*!< MMC Card spec version 1.2 */
  HAL_MMC_SPECIFICATION_VERSION_1_4     = 0x01U, /*!< MMC Card spec version 1.4 */
  HAL_MMC_SPECIFICATION_VERSION_2_2     = 0x02U, /*!< MMC Card spec version 2.2 */
  HAL_MMC_SPECIFICATION_VERSION_3_0     = 0x03U, /*!< MMC Card spec version 3.0 */
  HAL_MMC_SPECIFICATION_VERSION_4_0     = 0x04U, /*!< MMC Card spec version 4.0 */
  HAL_MMC_SPECIFICATION_VERSION_UNKNOWN = 0x05U  /*!< MMC Card Unknown version  */
} hal_mmc_specification_version_t;
#endif /* USE_HAL_MMC_GET_SPEC_VERSION */

/*! MMC Card Event Callback */
typedef enum
{
  HAL_MMC_EVENT_CB_TX_CPLT      = 0x01U, /*!< MMC Tx complete callback      */
  HAL_MMC_EVENT_CB_RX_CPLT      = 0x02U, /*!< MMC Rx complete callback      */
  HAL_MMC_EVENT_CB_TX_NODE_CPLT = 0x03U, /*!< MMC Tx NODE complete callback */
  HAL_MMC_EVENT_CB_RX_NODE_CPLT = 0x04U  /*!< MMC Rx NODE complete callback */
} hal_mmc_event_cb_t;

/*! MMC Card Clock Edge */
typedef enum
{
  HAL_MMC_CLOCK_EDGE_RISING  = SDMMC_CLOCK_EDGE_RISING, /*!< Clock edge is in rising mode  */
  HAL_MMC_CLOCK_EDGE_FALLING = SDMMC_CLOCK_EDGE_FALLING /*!< Clock edge is in falling mode */
} hal_mmc_clock_edge_t;

/*! MMC Card Clock Power Saving */
typedef enum
{
  HAL_MMC_CLOCK_POWER_SAVE_DISABLE = SDMMC_CLOCK_POWER_SAVE_DISABLE, /*!< Clock is always Disabled                     */
  HAL_MMC_CLOCK_POWER_SAVE_ENABLE  = SDMMC_CLOCK_POWER_SAVE_ENABLE   /*!< Clock is only enabled when the bus is active */
} hal_mmc_clock_power_save_t;

/*! MMC Card Bus Width */
typedef enum
{
  HAL_MMC_BUS_WIDE_1BIT = SDMMC_BUS_WIDE_1BIT, /*!< Default 1-bit wide bus mode */
  HAL_MMC_BUS_WIDE_4BIT = SDMMC_BUS_WIDE_4BIT, /*!< 4-bit wide bus mode         */
  HAL_MMC_BUS_WIDE_8BIT = SDMMC_BUS_WIDE_8BIT  /*!< 8-bit wide bus mode         */
} hal_mmc_bus_wide_t;

/*! MMC Card Hardware Flow Control */
typedef enum
{
  HAL_MMC_HARDWARE_FLOW_CONTROL_DISABLE = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE, /*!< Hardware flow control is disabled */
  HAL_MMC_HARDWARE_FLOW_CONTROL_ENABLE  = SDMMC_HARDWARE_FLOW_CONTROL_ENABLE   /*!< Hardware flow control is enabled  */
} hal_mmc_hardware_flow_control_t;

#if defined (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1)
/*! MMC Card Node State */
typedef enum
{
  HAL_MMC_DATA_BUFFER_NOT_READY = 0U, /*!< MMC Data Buffer Not Ready */
  HAL_MMC_DATA_BUFFER_READY     = 1U  /*!< MMC Data Buffer Ready     */
} hal_mmc_node_state_t;
#endif /* USE_HAL_MMC_LINKEDLIST */

/*! MMC Card DLYB State */
typedef enum
{
  HAL_MMC_DLYB_DISABLED = DLYB_DISABLED, /*!< MMC DLYB disabled */
  HAL_MMC_DLYB_ENABLED  = DLYB_ENABLED   /*!< MMC DLYB enabled  */
} hal_mmc_dlyb_state_t;

/*! MMC Card Area Partitions */
typedef enum
{
  HAL_MMC_AREA_PARTITION_USER   = 0x03B30000U, /*!< MMC card User area partition   */
  HAL_MMC_AREA_PARTITION_BOOT_1 = 0x03B30100U, /*!< MMC card Boot area partition 1 */
  HAL_MMC_AREA_PARTITION_BOOT_2 = 0x03B30200U, /*!< MMC card Boot area partition 2 */
  HAL_MMC_AREA_PARTITION_RPMB   = 0x03B30300U  /*!< MMC card RPMB area partition   */
} hal_mmc_area_partition_t;

/*! MMC Card Information */
typedef struct
{
  uint32_t relative_addr;           /*!< Specifies the Relative Card Address           */
  uint32_t block_nbr;               /*!< Specifies the Card Capacity in blocks         */
  uint32_t block_size_byte;         /*!< Specifies one block size in bytes             */
  uint32_t logical_block_nbr;       /*!< Specifies the Card logical Capacity in blocks */
  uint32_t logical_block_size_byte; /*!< Specifies logical block size in bytes         */
} hal_mmc_card_info_t;

#if defined (USE_HAL_MMC_GET_CID) && (USE_HAL_MMC_GET_CID == 1)
/*! MMC Card Identification Data */
typedef struct
{
  uint32_t product_name_part1; /*!< Product Name part1    */
  uint32_t product_serial_nbr; /*!< Product Serial Number */
  uint16_t oem_app_id;         /*!< OEM/Application ID    */
  uint16_t manufacturer_date;  /*!< Manufacturing Date    */
  uint8_t  manufacturer_id;    /*!< Manufacturer ID       */
  uint8_t  cid_crc;            /*!< CID CRC               */
  uint8_t  reserved2;          /*!< Always 1              */
  uint8_t  product_name_part2; /*!< Product Name part2    */
  uint8_t  product_rev;        /*!< Product Revision      */
  uint8_t  reserved1;          /*!< Reserved1             */
} hal_mmc_card_cid_t;
#endif /* USE_HAL_MMC_GET_CID */

/*! MMC Card Clock configuration */
typedef struct
{
  hal_mmc_clock_edge_t       clk_edge;       /*!< MMC clock edge       */
  hal_mmc_clock_power_save_t clk_power_save; /*!< MMC clock power save */

#if defined (USE_HAL_MMC_AUTO_DETECTION_FREQUENCY) && (USE_HAL_MMC_AUTO_DETECTION_FREQUENCY == 0)
  uint32_t                   clk_hz;         /*!< MMC clock frequency  */
#endif /* USE_HAL_MMC_AUTO_DETECTION_FREQUENCY */
} hal_mmc_clock_config_t;

/*! MMC Card globale configuration */
typedef struct
{
  hal_mmc_clock_config_t          clk_cfg;              /*!< MMC clock configuration              */
  hal_mmc_bus_wide_t              bus_wide;             /*!< MMC bus wide                         */
  hal_mmc_hardware_flow_control_t hw_flow_ctrl;         /*!< MMC hardware flow control            */
  uint32_t                        data_timeout_cycle;   /*!< MMC data timeout                     */
  uint32_t                        stop_xfer_timeout_ms; /*!< MMC stop xfer timeout in millisecond */
  uint32_t                        erase_timeout_ms;     /*!< MMC erase timeout in millisecond     */
} hal_mmc_config_t;

#if defined (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1)
/*! MMC Card Data Control structure */
typedef struct
{
  uint32_t idma_node_offset;      /*!< MMC Card DMA linked list configuration register */
  uint32_t idma_buffer_base_addr; /*!< MMC Card DMA buffer base address register       */
  uint32_t idma_buffer_size;      /*!< MMC Card DMA buffer size register               */
} hal_mmc_node_t;
#endif /* USE_HAL_MMC_LINKEDLIST */

typedef struct hal_mmc_handle_s hal_mmc_handle_t; /*!< MMC handle Structure type */

#if defined (USE_HAL_MMC_REGISTER_CALLBACKS) && (USE_HAL_MMC_REGISTER_CALLBACKS == 1)
typedef void (*hal_mmc_cb_t)(hal_mmc_handle_t *hmmc);                                   /*!< HAL MMC Error/Abort Callback pointer definition */
typedef void (*hal_mmc_xfer_cb_t)(hal_mmc_handle_t *hmmc, hal_mmc_event_cb_t cb_event); /*!< HAL MMC Process Callback pointer definition     */
#endif /* USE_HAL_MMC_REGISTER_CALLBACKS */

/*! MMC handle Structure definition */
struct hal_mmc_handle_s
{
  hal_mmc_t                       instance;                      /*!< MMC registers base address                                                        */
  uint32_t                        *p_xfer_buff;                  /*!< Pointer to MMC Xfer Buffer                                                        */
  uint32_t                        xfer_size_byte;                /*!< MMC Xfer size                                                                     */
  volatile uint32_t               context;                       /*!< MMC transfer context                                                              */
  volatile hal_mmc_state_t        global_state;                  /*!< MMC card State                                                                    */
  hal_mmc_card_info_t             mmc_card_info;                 /*!< MMC Card information                                                              */
  uint32_t                        mmc_card_type;                 /*!< MMC card Type                                                                     */
  uint32_t                        data_timeout_cycle;            /*!< MMC Card data timeout                                                             */
  uint32_t                        stop_xfer_timeout_ms;          /*!< MMC Card stop transfer timeout in millisecond                                     */
  uint32_t                        erase_timeout_ms;              /*!< MMC Card erase timeout in millisecond                                             */
  uint32_t                        sector_count;                  /*!< MMC Card sector count                                                             */
  uint8_t                         supported_pwr_class_ddr_52;    /*!< MMC Card Power class for 52MHz DDR at vcc = 3.6V                                  */
  uint8_t                         supported_pwr_class_cl_52;     /*!< MMC Card Power class for 52 MHz at 1.95 V 1 R                                     */
  uint8_t                         supported_pwr_class_cl_26;     /*!< MMC Card Power class for 26 MHz at 1.95 V 1 R                                     */
  uint8_t                         device_type;                   /*!< MMC Card Device type                                                              */
  uint8_t                         data_sector_size;              /*!< MMC Card Sector size                                                              */
  uint8_t                         secure_removal_type;           /*!< MMC Card supported secure removal type                                            */
  uint8_t                         sleep_notification_timeout_ms; /*!< MMC Card sleep notification timeout in millisecond                                */
  uint8_t                         sleep_awake_timeout_ms;        /*!< MMC Card Sleep/Awake timeout in millisecond                                       */
  uint8_t                         pwr_class;                     /*!< MMC Card power class                                                              */
  uint16_t                        partition_switching_timing_ms; /*!< MMC Card partition switch timing in millisecond, with a maximum value is 2550ms   */
#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
  volatile uint32_t               last_error_codes;              /*!< MMC Card Error codes                                                              */
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */

#if defined (USE_HAL_MMC_USER_DATA) && (USE_HAL_MMC_USER_DATA == 1)
  const void                      *p_user_data;                 /*!< MMC user data                                                                      */
#endif /* USE_HAL_MMC_USER_DATA */

#if defined (USE_HAL_MMC_GET_SPEC_VERSION) && (USE_HAL_MMC_GET_SPEC_VERSION == 1)
  hal_mmc_specification_version_t version;                      /*!< MMC card version                                                                   */
#endif /* USE_HAL_MMC_GET_SPEC_VERSION */

#if defined (USE_HAL_MMC_GET_CID) && (USE_HAL_MMC_GET_CID == 1)
  hal_mmc_card_cid_t              cid;                          /*!< MMC card identification                                                            */
#endif /* USE_HAL_MMC_GET_CID */
#if defined (USE_HAL_MMC_REGISTER_CALLBACKS) && (USE_HAL_MMC_REGISTER_CALLBACKS == 1)
  hal_mmc_xfer_cb_t               p_xfer_cplt_callback;         /*!< MMC Xfer callback function                                                         */
  hal_mmc_cb_t                    p_error_callback;             /*!< MMC Error callback function                                                        */
  hal_mmc_cb_t                    p_abort_callback;             /*!< MMC Abort callback function                                                        */
#endif /* USE_HAL_MMC_REGISTER_CALLBACKS */
#if defined (USE_HAL_MMC_RPMB_FEATURE) && (USE_HAL_MMC_RPMB_FEATURE == 1)
  uint32_t                        offset;                       /*!< MMC Card Data offset for RPMB data programming                                     */
  uint32_t                        remaining_data;               /*!< MMC Card data remaining to be read or write to RPMB area                           */
  uint32_t                        block_addr;                   /*!< MMC Card block addr for RPMB operation                                             */
  uint32_t                        blocks_nbr;                   /*!< MMC Card block number to be programmed into RPMB area                              */
  uint32_t                        counter_value;                /*!< MMC Card counter value                                                             */
  uint32_t                        rpmb_partition_size_byte;     /*!< MMC Card RPMB partition size in bytes                                              */
  uint16_t                        rpmb_error_codes;             /*!< MMC Card RPMB Error codes                                                          */
  uint8_t                         *p_mac;                       /*!< Pointer to the authentication MAC buffer                                           */
  uint8_t                         *p_nonce;                     /*!< Pointer to the nonce buffer                                                        */
  uint8_t                         *p_rpmb_data;                 /*!< Pointer to the buffer containing data to transmit                                  */
  uint8_t                         rpmb_next_step;               /*!< MMC RPMB  next step operation                                                      */
  uint8_t                         rpmb_req;                     /*!< MMC RPMB request type                                                              */
#endif /* USE_HAL_MMC_RPMB_FEATURE */
};
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup MMC_Exported_Functions HAL MMC Functions
  * @{
  */

/** @defgroup MMC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_MMC_Init(hal_mmc_handle_t *hmmc, hal_mmc_t instance);
void HAL_MMC_DeInit(hal_mmc_handle_t *hmmc);
/**
  * @}
  */

/** @defgroup MMC_Exported_Functions_Group2 Set and Get configurations functions
  * @{
  */
hal_status_t HAL_MMC_SetConfig(hal_mmc_handle_t *hmmc, const hal_mmc_config_t *p_config);
void         HAL_MMC_GetConfig(const hal_mmc_handle_t *hmmc, hal_mmc_config_t *p_config);
hal_status_t HAL_MMC_NotifyCardInsertion(hal_mmc_handle_t *hmmc, const hal_mmc_config_t *p_config);
hal_status_t HAL_MMC_NotifyCardRemoval(hal_mmc_handle_t *hmmc);
hal_status_t HAL_MMC_SwitchSpeedMode(hal_mmc_handle_t *hmmc, hal_mmc_speed_mode_t speed_mode);
hal_status_t HAL_MMC_SetDataTimeout(hal_mmc_handle_t *hmmc, uint32_t data_timeout_cycle);
uint32_t     HAL_MMC_GetDataTimeout(const hal_mmc_handle_t *hmmc);
hal_status_t HAL_MMC_SetStopXferTimeout(hal_mmc_handle_t *hmmc, uint32_t stopxfer_timeout_ms);
uint32_t     HAL_MMC_GetStopXferTimeout(const hal_mmc_handle_t *hmmc);
hal_status_t HAL_MMC_SetEraseTimeout(hal_mmc_handle_t *hmmc, uint32_t erase_timeout_ms);
uint32_t     HAL_MMC_GetEraseTimeout(const hal_mmc_handle_t *hmmc);
uint32_t     HAL_MMC_GetClockFreq(const hal_mmc_handle_t *hmmc);
/**
  * @}
  */

/** @defgroup MMC_Exported_Functions_Group3 Input and Output operation functions
  * @{
  */
hal_status_t HAL_MMC_Erase(hal_mmc_handle_t *hmmc, uint32_t start_block_addr, uint32_t end_block_addr);
hal_status_t HAL_MMC_ReadBlocks(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr,
                                uint32_t timeout_ms);
hal_status_t HAL_MMC_WriteBlocks(hal_mmc_handle_t *hmmc, const uint8_t *p_data, uint32_t block_addr,
                                 uint32_t blocks_nbr, uint32_t timeout_ms);
hal_status_t HAL_MMC_ReadBlocks_IT(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr);
hal_status_t HAL_MMC_WriteBlocks_IT(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr);
hal_status_t HAL_MMC_ReadBlocks_DMA(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr);
hal_status_t HAL_MMC_WriteBlocks_DMA(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr);

#if defined (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1)
hal_status_t HAL_MMC_ReadBlocks_LinkedList(hal_mmc_handle_t *hmmc, uint32_t block_addr, uint32_t blocks_nbr,
                                           const hal_q_t *p_q);
hal_status_t HAL_MMC_WriteBlocks_LinkedList(hal_mmc_handle_t *hmmc, uint32_t block_addr, uint32_t blocks_nbr,
                                            const hal_q_t *p_q);
#endif /* USE_HAL_MMC_LINKEDLIST */

hal_status_t HAL_MMC_Abort(hal_mmc_handle_t *hmmc);
hal_status_t HAL_MMC_Abort_IT(hal_mmc_handle_t *hmmc);
/**
  * @}
  */

/** @defgroup MMC_Exported_Functions_Group4 IRQHandler and Callbacks Functions
  * @{
  */
void HAL_MMC_IRQHandler(hal_mmc_handle_t *hmmc);
void HAL_MMC_XferCpltCallback(hal_mmc_handle_t *hmmc, hal_mmc_event_cb_t cb_event);
void HAL_MMC_ErrorCallback(hal_mmc_handle_t *hmmc);
void HAL_MMC_AbortCallback(hal_mmc_handle_t *hmmc);

#if defined (USE_HAL_MMC_REGISTER_CALLBACKS) && (USE_HAL_MMC_REGISTER_CALLBACKS == 1)
hal_status_t HAL_MMC_RegisterXferCpltCallback(hal_mmc_handle_t *hmmc, hal_mmc_xfer_cb_t callback);
hal_status_t HAL_MMC_RegisterErrorCallback(hal_mmc_handle_t *hmmc, hal_mmc_cb_t callback);
hal_status_t HAL_MMC_RegisterAbortCallback(hal_mmc_handle_t *hmmc, hal_mmc_cb_t callback);
#endif /* USE_HAL_MMC_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup MMC_Exported_Functions_Group5 MMC State, Error related functions
  * @{
  */
hal_mmc_state_t HAL_MMC_GetState(const hal_mmc_handle_t *hmmc);

#if defined(USE_HAL_MMC_GET_LAST_ERRORS) && (USE_HAL_MMC_GET_LAST_ERRORS == 1)
uint32_t HAL_MMC_GetLastErrorCodes(const hal_mmc_handle_t *hmmc);
#endif /* USE_HAL_MMC_GET_LAST_ERRORS */
/**
  * @}
  */
/** @defgroup MMC_Exported_Functions_Group6 MMC User data related functions
  * @{
  */
#if defined (USE_HAL_MMC_USER_DATA) && (USE_HAL_MMC_USER_DATA == 1)
void HAL_MMC_SetUserData(hal_mmc_handle_t *hmmc, const void *p_user_data);
const void *HAL_MMC_GetUserData(const hal_mmc_handle_t *hmmc);
#endif /* USE_HAL_MMC_USER_DATA */
/**
  * @}
  */

/** @defgroup MMC_Exported_Functions_Group7 MMC Card related functions
  * @{
  */
hal_mmc_card_state_t HAL_MMC_GetCardState(hal_mmc_handle_t *hmmc);
void                 HAL_MMC_GetCardInfo(const hal_mmc_handle_t *hmmc, hal_mmc_card_info_t *p_card_info);

#if defined (USE_HAL_MMC_GET_CID) && (USE_HAL_MMC_GET_CID == 1)
void HAL_MMC_GetCardCID(const hal_mmc_handle_t *hmmc, hal_mmc_card_cid_t *p_cid);
#endif /* USE_HAL_MMC_GET_CID */

#if defined (USE_HAL_MMC_GET_SPEC_VERSION) && (USE_HAL_MMC_GET_SPEC_VERSION == 1)
hal_mmc_specification_version_t HAL_MMC_GetCardSpecVersion(const hal_mmc_handle_t *hmmc);
#endif /* USE_HAL_MMC_GET_SPEC_VERSION */
/**
  * @}
  */

/** @defgroup MMC_Exported_Functions_Group8 Peripheral Erase management
  * @{
  */
hal_status_t HAL_MMC_EraseSequence(hal_mmc_handle_t *hmmc, hal_mmc_erase_type_t erase_type, uint32_t start_block_addr,
                                   uint32_t end_block_addr);
hal_status_t HAL_MMC_Sanitize(hal_mmc_handle_t *hmmc);
hal_status_t HAL_MMC_SetSecureRemovalType(hal_mmc_handle_t *hmmc, hal_mmc_secure_removal_type_t sec_removal_type);
hal_mmc_secure_removal_type_t HAL_MMC_GetSecureRemovalType(const hal_mmc_handle_t *hmmc);
/**
  * @}
  */

/** @defgroup MMC_Exported_Functions_Group9 Peripheral low power management
  * @{
  */
hal_status_t HAL_MMC_EnterCardSleepMode(hal_mmc_handle_t *hmmc);
hal_status_t HAL_MMC_ExitCardSleepMode(hal_mmc_handle_t *hmmc);
/**
  * @}
  */

/** @defgroup MMC_Exported_Functions_Group10 Linked-List Queue functions
  * @{
  */
#if defined (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1)
/**
  * @brief Get MMC Card Node information.
  * @param next_offset_addr  next node address offset.
  * @param p_addressing_mode node addressing mode.
  */
__STATIC_INLINE void HAL_MMC_GetNodeInfo(uint32_t *next_offset_addr, hal_q_addressing_mode_t *p_addressing_mode)
{
  *next_offset_addr = 0U;
  *p_addressing_mode = HAL_Q_ADDRESSING_BASE_OFFSET;
}

/**
  * @brief Set MMC Card node address.
  * @param head_node_addr   Head node address.
  * @param prev_node_addr   Previous node address.
  * @param next_node_addr   Next node address.
  * @param node_addr_offset Node address offset.
  */
__STATIC_INLINE void HAL_MMC_SetNodeAddress(uint32_t head_node_addr, uint32_t prev_node_addr, uint32_t next_node_addr,
                                            uint32_t node_addr_offset)
{
  STM32_MODIFY_REG((*(uint32_t *)(prev_node_addr + node_addr_offset)), SDMMC_IDMALAR_IDMALA,
                   ((next_node_addr - head_node_addr) & SDMMC_IDMALAR_IDMALA));
}

/**
  * @brief Get MMC Card node address.
  * @param head_node_addr    Head node address.
  * @param current_node_addr Current node address.
  * @param node_addr_offset  Node address offset.
  * @retval SDMMC node address.
  */
__STATIC_INLINE uint32_t HAL_MMC_GetNodeAddress(uint32_t head_node_addr, uint32_t current_node_addr,
                                                uint32_t node_addr_offset)
{
  return (head_node_addr + (*(uint32_t *)(current_node_addr + node_addr_offset) & SDMMC_IDMALAR_IDMALA));
}

hal_status_t HAL_MMC_FillNodeConfig(hal_mmc_node_t *p_node, void *p_buffer, uint32_t size_byte);
void         HAL_MMC_GetNodeConfig(const hal_mmc_node_t *p_node, uint32_t *p_buffer, uint32_t *p_size_byte);
hal_status_t HAL_MMC_SetNodeDataBufferState(const hal_mmc_node_t *p_node, hal_mmc_node_state_t state);
hal_mmc_node_state_t HAL_MMC_GetNodeDataBufferState(const hal_mmc_node_t *p_node);
#endif /* USE_HAL_MMC_LINKEDLIST */
/**
  * @}
  */

/** @defgroup MMC_Exported_Functions_Group11 MMC Delay Block functions
  * @{
  */
hal_status_t HAL_MMC_SetConfigDlybDelay(const hal_mmc_handle_t *hmmc, uint32_t clock_phase_value);
uint32_t HAL_MMC_GetDlybOutputClockPhase(const hal_mmc_handle_t *hmmc);
hal_status_t HAL_MMC_CalculateDlybMaxClockPhase(hal_mmc_handle_t *hmmc, uint32_t *p_max_clock_phase);
hal_status_t HAL_MMC_EnableDlyb(hal_mmc_handle_t *hmmc);
hal_status_t HAL_MMC_DisableDlyb(hal_mmc_handle_t *hmmc);
hal_mmc_dlyb_state_t HAL_MMC_IsEnabledDlyb(hal_mmc_handle_t *hmmc);
/**
  * @}
  */

/** @defgroup MMC_Exported_Functions_Group12 Interrupt And Flag Configuration
  * @{
This section provides functions allowing to initialize and de-initialize the MMC card device :
- Call the function HAL_MMC_EnableIT() to enable the MMC device interrupt.
- Call the function HAL_MMC_DisableIT() to disable the device interrupt.
- Call the function HAL_MMC_IsActiveFlag() to check whether the specified MMC flag is set or not.
- Call the function HAL_MMC_ClearFlag() to clear the MMC device pending flags.
  */
/**
  * @brief Enable the MMC device interrupt.
  * @param hmmc      Pointer to a hal_mmc_handle_t structure.
  * @param interrupt Specifies the SDMMC interrupt sources to be enabled. This parameter can be a combination
                     of @ref SDMMC_CORE_Interrupt_sources group.
  */
__STATIC_INLINE void HAL_MMC_EnableIT(hal_mmc_handle_t *hmmc, uint32_t interrupt)
{
  SDMMC_ENABLE_IT((SDMMC_TypeDef *)((uint32_t)hmmc->instance), interrupt);
}

/**
  * @brief Disable the MMC device interrupt.
  * @param hmmc      Pointer to a hal_mmc_handle_t structure.
  * @param interrupt Specifies the SDMMC interrupt sources to be disable. This parameter can be a combination
                     of @ref SDMMC_CORE_Interrupt_sources group.
  */
__STATIC_INLINE void HAL_MMC_DisableIT(hal_mmc_handle_t *hmmc, uint32_t interrupt)
{
  SDMMC_DISABLE_IT((SDMMC_TypeDef *)((uint32_t)hmmc->instance), interrupt);
}

/**
  * @brief Check whether the specified MMC flag is set or not.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param flag Specifies the flag source to check. This parameter can be a combination of
                @ref SDMMC_CORE_Flags_sources group.
  * @retval The new state of SDMMC_FLAG (SET or RESET).
  */
__STATIC_INLINE uint32_t HAL_MMC_IsActiveFlag(const hal_mmc_handle_t *hmmc, uint32_t flag)
{
  return (uint32_t)SDMMC_IS_ACTIVE_FLAG((SDMMC_TypeDef *)((uint32_t)hmmc->instance), flag);
}

/**
  * @brief Clear the MMC pending flags.
  * @param hmmc Pointer to a hal_mmc_handle_t structure.
  * @param flag Specifies the SDMMC flag sources to clear. This parameter can be a combination of
                @ref SDMMC_CORE_Flags_sources group.
  */
__STATIC_INLINE void HAL_MMC_ClearFlag(hal_mmc_handle_t *hmmc, uint32_t flag)
{
  SDMMC_CLEAR_FLAG((SDMMC_TypeDef *)((uint32_t)hmmc->instance), flag);
}
/**
  * @}
  */
#if defined (USE_HAL_MMC_RPMB_FEATURE) && (USE_HAL_MMC_RPMB_FEATURE == 1)
/** @defgroup MMC_Exported_Functions_Group13 MMC Replay Protected Memory Block management (RPMB)
  * @{
  */
hal_status_t HAL_MMC_SelectPartitionArea(hal_mmc_handle_t *hmmc, hal_mmc_area_partition_t area_partition);
hal_status_t HAL_MMC_ProgramRPMBAuthenticationKey(hal_mmc_handle_t *hmmc, const uint8_t *p_key, uint32_t timeout_ms);
hal_status_t HAL_MMC_GetRPMBWriteCounter(hal_mmc_handle_t *hmmc, uint8_t *p_nonce, uint32_t *p_write_counter,
                                         uint32_t timeout_ms);

hal_status_t HAL_MMC_WriteRPMBBlocks(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr,
                                     uint32_t blocks_nbr, uint8_t *p_mac, uint32_t timeout_ms);
hal_status_t HAL_MMC_ReadRPMBBlocks(hal_mmc_handle_t *hmmc, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr,
                                    uint8_t *p_nonce, uint8_t *p_mac, uint32_t timeout_ms);

uint32_t     HAL_MMC_GetRPMBErrorCodes(const hal_mmc_handle_t *hmmc);
uint32_t     HAL_MMC_GetRPMBSize(const hal_mmc_handle_t *hmmc);
/**
  * @}
  */
#endif /* USE_HAL_MMC_RPMB_FEATURE */
/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
#if defined (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1)
/** @defgroup MMC_Private_Variables MMC Private Variables
  * @{
  */
/*! HAL MMC addressing descriptor operation structure definition */
static const hal_q_desc_ops_t HAL_MMC_DescOps =
{
  HAL_MMC_GetNodeInfo,    /*!< Get MMC Card node information */
  HAL_MMC_SetNodeAddress, /*!< Set MMC Card node address     */
  HAL_MMC_GetNodeAddress, /*!< Get MMC Card node address     */
};
/**
  * @}
  */
#endif /* (USE_HAL_MMC_LINKEDLIST) && (USE_HAL_MMC_LINKEDLIST == 1) */

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

#endif /* STM32H7PXX_HAL_MMC_H */
