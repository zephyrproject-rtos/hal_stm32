/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_sd.h
  * @brief   Header file of SD HAL module.
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
#ifndef STM32H7Pxx_HAL_SD_H
#define STM32H7Pxx_HAL_SD_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#if defined (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1)
/* Include Q module for linked-list management with associated features */
#ifndef USE_HAL_Q_BASE_OFFSET_ADDR_MODE
#define USE_HAL_Q_BASE_OFFSET_ADDR_MODE (1U)
#endif /* USE_HAL_Q_BASE_OFFSET_ADDR_MODE */

#ifndef USE_HAL_Q_CIRCULAR_LINK
#define USE_HAL_Q_CIRCULAR_LINK    (1U)
#endif /* USE_HAL_Q_CIRCULAR_LINK */
#include "stm32h7pxx_hal_q.h"
#endif /* (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1) */

#include "stm32h7pxx_sdmmc_core.h"
#include "stm32h7pxx_dlyb_core.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */
#if defined(SDMMC1)

/** @defgroup SD SD
  * @{
  */
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup SD_Exported_Constants HAL SD Constants
  * @{
  */
/** @defgroup SD_Transfer_Timeout SD Transfer Timeout definition
  * @{
  */
#define HAL_SD_DATA_MAX_TIMEOUT      0xFFFFFFFFU /*!< SD data timeout           */
#define HAL_SD_STOP_XFER_MAX_TIMEOUT 500U        /*!< SD erase timeout 500ms    */
#define HAL_SD_ERASE_MAX_TIMEOUT     63000U      /*!< SD max erase Timeout 63s  */
/**
  * @}
  */

/** @defgroup SD_Error_Status SD Error status definition
  * @{
  */
#define HAL_SD_ERROR_NONE                     SDMMC_ERROR_NONE                   /*!< No error                                                     */
#define HAL_SD_ERROR_CMD_CRC_FAIL             SDMMC_ERROR_CMD_CRC_FAIL           /*!< Command response received (but CRC check failed)             */
#define HAL_SD_ERROR_DATA_CRC_FAIL            SDMMC_ERROR_DATA_CRC_FAIL          /*!< Data block sent/received (CRC check failed)                  */
#define HAL_SD_ERROR_CMD_RSP_TIMEOUT          SDMMC_ERROR_CMD_RSP_TIMEOUT        /*!< Command response timeout                                     */
#define HAL_SD_ERROR_DATA_TIMEOUT             SDMMC_ERROR_DATA_TIMEOUT           /*!< Data timeout                                                 */
#define HAL_SD_ERROR_TX_UNDERRUN              SDMMC_ERROR_TX_UNDERRUN            /*!< Transmit FIFO underrun                                       */
#define HAL_SD_ERROR_RX_OVERRUN               SDMMC_ERROR_RX_OVERRUN             /*!< Receive FIFO overrun                                         */
#define HAL_SD_ERROR_ADDR_MISALIGNED          SDMMC_ERROR_ADDR_MISALIGNED        /*!< Misaligned address                                           */
#define HAL_SD_ERROR_BLOCK_LEN_ERR            SDMMC_ERROR_BLOCK_LEN_ERR          /*!< Transferred block length is not allowed for the card or the
                                              number of transferred bytes does not match the block length  */
#define HAL_SD_ERROR_ERASE_SEQ_ERR            SDMMC_ERROR_ERASE_SEQ_ERR          /*!< An error in the sequence of erase command occurs             */
#define HAL_SD_ERROR_BAD_ERASE_PARAM          SDMMC_ERROR_BAD_ERASE_PARAM        /*!< An invalid selection for erase groups                        */
#define HAL_SD_ERROR_WRITE_PROT_VIOLATION     SDMMC_ERROR_WRITE_PROT_VIOLATION   /*!< Attempt to program a write protect block                     */
#define HAL_SD_ERROR_LOCK_UNLOCK_FAILED       SDMMC_ERROR_LOCK_UNLOCK_FAILED     /*!< Sequence or password error has been detected in unlock
                                              command or if there was an attempt to access a locked card   */
#define HAL_SD_ERROR_COM_CRC_FAILED           SDMMC_ERROR_COM_CRC_FAILED         /*!< CRC check of the previous command failed                     */
#define HAL_SD_ERROR_ILLEGAL_CMD              SDMMC_ERROR_ILLEGAL_CMD            /*!< Command is not legal for the card state                      */
#define HAL_SD_ERROR_CARD_ECC_FAILED          SDMMC_ERROR_CARD_ECC_FAILED        /*!< Card internal ECC was applied but failed to correct the data */
#define HAL_SD_ERROR_CC_ERR                   SDMMC_ERROR_CC_ERR                 /*!< Internal card controller error                               */
#define HAL_SD_ERROR_GENERAL_UNKNOWN_ERR      SDMMC_ERROR_GENERAL_UNKNOWN_ERR    /*!< General or unknown error                                     */
#define HAL_SD_ERROR_STREAM_READ_UNDERRUN     SDMMC_ERROR_STREAM_READ_UNDERRUN   /*!< The card could not sustain data reading in stream mode       */
#define HAL_SD_ERROR_STREAM_WRITE_OVERRUN     SDMMC_ERROR_STREAM_WRITE_OVERRUN   /*!< The card could not sustain data programming in stream mode   */
#define HAL_SD_ERROR_CID_CSD_OVERWRITE        SDMMC_ERROR_CID_CSD_OVERWRITE      /*!< CID/CSD overwrite error                                      */
#define HAL_SD_ERROR_WP_ERASE_SKIP            SDMMC_ERROR_WP_ERASE_SKIP          /*!< Only partial address space was erased                        */
#define HAL_SD_ERROR_CARD_ECC_DISABLED        SDMMC_ERROR_CARD_ECC_DISABLED      /*!< Command has been executed without using internal ECC         */
#define HAL_SD_ERROR_ERASE_RESET              SDMMC_ERROR_ERASE_RESET            /*!< Erase sequence was cleared before executing because an out
                                              of erase sequence command was received                       */
#define HAL_SD_ERROR_AKE_SEQ_ERR              SDMMC_ERROR_AKE_SEQ_ERR            /*!< Error in sequence of authentication                          */
#define HAL_SD_ERROR_INVALID_VOLTRANGE        SDMMC_ERROR_INVALID_VOLTRANGE      /*!< Error in case of invalid voltage range                       */
#define HAL_SD_ERROR_ADDR_OUT_OF_RANGE        SDMMC_ERROR_ADDR_OUT_OF_RANGE      /*!< Error when addressed block is out of range                   */
#define HAL_SD_ERROR_REQUEST_NOT_APPLICABLE   SDMMC_ERROR_REQUEST_NOT_APPLICABLE /*!< Error when command request is not applicable                 */
#define HAL_SD_ERROR_INVALID_PARAM            SDMMC_ERROR_INVALID_PARAMETER      /*!< the used parameter is not valid                              */
#define HAL_SD_ERROR_UNSUPPORTED_FEATURE      SDMMC_ERROR_UNSUPPORTED_FEATURE    /*!< Error when feature is not supported                          */
#define HAL_SD_ERROR_BUSY                     SDMMC_ERROR_BUSY                   /*!< Error when transfer process is busy                          */
#define HAL_SD_ERROR_DMA                      SDMMC_ERROR_DMA                    /*!< Error while DMA transfer                                     */
#define HAL_SD_ERROR_TIMEOUT                  SDMMC_ERROR_TIMEOUT                /*!< Timeout error                                                */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup SD_Exported_Types HAL SD Types
  * @{
  */

/*! SD Card instance */
typedef enum
{
  HAL_SD_CARD_1 = SDMMC1_BASE, /*!< HAL SD card instance 1 */
#if defined (SDMMC2)
  HAL_SD_CARD_2 = SDMMC2_BASE  /*!< HAL SD card instance 2 */
#endif /* SDMMC2 */
} hal_sd_t;

/*! SD Card global state */
typedef enum
{
  HAL_SD_STATE_RESET        = (0U),        /*!< SD not Initialized                */
  HAL_SD_STATE_INIT         = (1U << 31U), /*!< SD initialized but not configured */
  HAL_SD_STATE_CARD_REMOVED = (1U << 30U), /*!< SD card removed                   */
  HAL_SD_STATE_IDLE         = (1U << 29U), /*!< SD ready for use                  */
  HAL_SD_STATE_ACTIVE       = (1U << 28U), /*!< SD operation IO state             */
  HAL_SD_STATE_ABORT        = (1U << 27U)  /*!< SD is aborting current process    */
} hal_sd_state_t;

/*! SD Card internal State */
typedef enum
{
  HAL_SD_CARD_READY          = 0x01U, /*!< Card state is ready                     */
  HAL_SD_CARD_IDENTIFICATION = 0x02U, /*!< Card is in identification state         */
  HAL_SD_CARD_STANDBY        = 0x03U, /*!< Card is in standby state                */
  HAL_SD_CARD_TRANSFER       = 0x04U, /*!< Card is in transfer state               */
  HAL_SD_CARD_SENDING        = 0x05U, /*!< Card is sending an operation            */
  HAL_SD_CARD_RECEIVING      = 0x06U, /*!< Card is receiving operation information */
  HAL_SD_CARD_PROGRAMMING    = 0x07U, /*!< Card is in programming state            */
  HAL_SD_CARD_DISCONNECTED   = 0x08U, /*!< Card is disconnected                    */
  HAL_SD_CARD_ERROR          = 0xFFU  /*!< Card response Error                     */
} hal_sd_card_state_t;

/*! SD Card Clock Edge */
typedef enum
{
  HAL_SD_CLOCK_EDGE_RISING  = SDMMC_CLOCK_EDGE_RISING,  /*!< Clock edge is in rising mode  */
  HAL_SD_CLOCK_EDGE_FALLING = SDMMC_CLOCK_EDGE_FALLING  /*!< Clock edge is in falling mode */
} hal_sd_clock_edge_t;

/*! SD Card Clock Power Saving */
typedef enum
{
  HAL_SD_CLOCK_POWER_SAVE_DISABLE = SDMMC_CLOCK_POWER_SAVE_DISABLE, /*!< Clock is always Disabled                     */
  HAL_SD_CLOCK_POWER_SAVE_ENABLE  = SDMMC_CLOCK_POWER_SAVE_ENABLE   /*!< Clock is only enabled when the bus is active */
} hal_sd_clock_power_save_t;

/*! SD Card Bus Width */
typedef enum
{
  HAL_SD_BUS_WIDE_1BIT = SDMMC_BUS_WIDE_1BIT, /*!< Default 1-bit wide bus mode */
  HAL_SD_BUS_WIDE_4BIT = SDMMC_BUS_WIDE_4BIT  /*!< 4-bit wide bus mode         */
} hal_sd_bus_wide_t;

/*! SD Card Hardware Flow Control */
typedef enum
{
  HAL_SD_HARDWARE_FLOW_CONTROL_DISABLE = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE, /*!< Hardware flow control is disabled */
  HAL_SD_HARDWARE_FLOW_CONTROL_ENABLE  = SDMMC_HARDWARE_FLOW_CONTROL_ENABLE   /*!< Hardware flow control is enabled  */
} hal_sd_hardware_flow_control_t;

/*! SD Card Transceiver Present */
typedef enum
{
  HAL_SD_TRANSCEIVER_NOT_PRESENT = SDMMC_TRANSCEIVER_NOT_PRESENT, /*!< SD Transceiver is not present */
  HAL_SD_TRANSCEIVER_PRESENT     = SDMMC_TRANSCEIVER_PRESENT      /*!< SD Transceiver is present     */
} hal_sd_transceiver_t;

/*! SD Card Transceiver State */
typedef enum
{
  HAL_SD_TRANSCEIVER_DISABLE = SDMMC_TRANSCEIVER_DISABLE, /*!< SD transceiver disable */
  HAL_SD_TRANSCEIVER_ENABLE  = SDMMC_TRANSCEIVER_ENABLE   /*!< SD transceiver enable  */
} hal_sd_transceiver_state_t;

/*! SD Card Speed mode */
typedef enum
{
  HAL_SD_SPEED_MODE_DEFAULT = SDMMC_SPEED_MODE_DEFAULT,      /*!< Default Speed up to 12.5 MB/sec, Freq up to 25MHz 3.3V signaling */
  HAL_SD_SPEED_MODE_HIGH    = SDMMC_SPEED_MODE_HIGH,         /*!< High Speed up to 25 MB/sec, Freq up to 50MHz 3.3V signaling      */
  HAL_SD_SPEED_MODE_DDR50   = SDMMC_SPEED_MODE_DDR,          /*!< DDR50 up to50MB/sec, Freq up to 50MHz 1.8V signaling             */
  HAL_SD_SPEED_MODE_SDR104  = SDMMC_SPEED_MODE_ULTRA_SDR104, /*!< SDR104 up to 104MB/sec, Freq up to 208MHz 1.8V signaling         */
  HAL_SD_SPEED_MODE_SDR50   = SDMMC_SPEED_MODE_ULTRA_SDR50   /*!< SDR50 up to 50MB/sec, Freq up to 100MHz 1.8V signaling           */
} hal_sd_speed_mode_t;

#if defined (USE_HAL_SD_GET_SPEC_VERSION) && (USE_HAL_SD_GET_SPEC_VERSION == 1)
/*! SD Card Specification version */
typedef enum
{
  HAL_SD_SPECIFICATION_VERSION_1_00_OR_1_01 = 0, /*!< SD Card spec version <= 1.01     */
  HAL_SD_SPECIFICATION_VERSION_1_10         = 1, /*!< SD Card spec version 1.10        */
  HAL_SD_SPECIFICATION_VERSION_2_00         = 2, /*!< SD Card spec version 2.00        */
  HAL_SD_SPECIFICATION_VERSION_3_0X         = 3, /*!< SD Card spec version 3.00        */
  HAL_SD_SPECIFICATION_VERSION_4_XX         = 4, /*!< SD Card spec version 4.00        */
  HAL_SD_SPECIFICATION_VERSION_5_XX         = 5, /*!< SD Card spec version 5.00        */
  HAL_SD_SPECIFICATION_VERSION_6_XX         = 6, /*!< SD Card spec version 6.00        */
  HAL_SD_SPECIFICATION_VESION_UNSUPPORTED   = 7  /*!< SD Card spec version unsupported */
} hal_sd_specification_version_t;
#endif /* USE_HAL_SD_GET_SPEC_VERSION */

/*! SD Card Event Callback */
typedef enum
{
  HAL_SD_EVENT_CB_TX_CPLT      = 0x01U, /*!< SD Tx complete callback      */
  HAL_SD_EVENT_CB_RX_CPLT      = 0x02U, /*!< SD Rx complete callback      */
  HAL_SD_EVENT_CB_TX_NODE_CPLT = 0x03U, /*!< SD Tx NODE complete callback */
  HAL_SD_EVENT_CB_RX_NODE_CPLT = 0x04U  /*!< SD Rx NODE complete callback */
} hal_sd_event_cb_t;

#if defined (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1)
/*! SD Card Node State */
typedef enum
{
  HAL_SD_DATA_BUFFER_NOT_READY = 0U, /*!< SD Data Buffer Not Ready */
  HAL_SD_DATA_BUFFER_READY     = 1U  /*!< SD Data Buffer Ready     */
} hal_sd_node_state_t;
#endif /* USE_HAL_SD_LINKEDLIST */

/*! SD Card DLYB State */
typedef enum
{
  HAL_SD_DLYB_DISABLED = DLYB_DISABLED, /*!< SD DLYB disabled */
  HAL_SD_DLYB_ENABLED  = DLYB_ENABLED   /*!< SD DLYB enabled  */
} hal_sd_dlyb_state_t;

/*! SD Card Information */
typedef struct
{
  uint32_t relative_addr;         /*!< Specifies the Relative Card Address           */
  uint32_t blk_nbr;               /*!< Specifies the Card Capacity in blocks         */
  uint32_t blk_size_byte;         /*!< Specifies one block size in bytes             */
  uint32_t logical_blk_nbr;       /*!< Specifies the Card logical Capacity in blocks */
  uint32_t logical_blk_size_byte; /*!< Specifies logical block size in bytes         */
} hal_sd_card_info_t;

#if defined (USE_HAL_SD_GET_CID) && (USE_HAL_SD_GET_CID == 1)
/*! SD Card Identification Data */
typedef struct
{
  uint32_t product_name_part1; /*!< Product Name part1    */
  uint32_t product_serial_nbr; /*!< Product Serial Number */
  uint16_t oem_app_id;         /*!< OEM/Application ID    */
  uint16_t manufacturer_date;  /*!< Manufacturing Date    */
  uint8_t  manufacturer_id;    /*!< Manufacturer ID       */
  uint8_t  product_name_part2; /*!< Product Name part2    */
  uint8_t  product_rev;        /*!< Product Revision      */
  uint8_t  reserved1;          /*!< Reserved              */
  uint8_t  cid_crc;            /*!< CID CRC               */
  uint8_t  reserved2;          /*!< Reserved              */
} hal_sd_card_cid_t;
#endif /* USE_HAL_SD_GET_CID */

/*! SD Card Status */
typedef struct
{
  uint32_t protected_area_size_byte; /*!< Carries information about the capacity of protected area      */
  uint16_t card_type;                /*!< Carries information about card type                           */
  uint16_t erase_size;               /*!< Determines the number of AUs to be erased in one operation    */
  uint8_t  data_bus_width;           /*!< Shows the currently defined data bus width                    */
  uint8_t  secured_mode;             /*!< Card is in secured mode of operation                          */
  uint8_t  speed_class;              /*!< Carries information about the speed class of the card         */
  uint8_t  performance_move;         /*!< Carries information about the card's performance move         */
  uint8_t  allocation_unit_size;     /*!< Carries information about the card's allocation unit size     */
  uint8_t  erase_timeout;            /*!< Determines the timeout for any number of AU erase             */
  uint8_t  erase_offset;             /*!< Carries information about the erase offset                    */
  uint8_t  uhs_speed_grade;          /*!< Carries information about the speed grade of UHS card         */
  uint8_t  uhs_allocation_unit_size; /*!< Carries information about the UHS card's allocation unit size */
  uint8_t  video_speed_class;        /*!< Carries information about the Video Speed Class of UHS card   */
} hal_sd_card_status_t;

/*! SD Card Clock configuration */
typedef struct
{
  hal_sd_clock_edge_t       clk_edge;       /*!< SD clock edge       */
  hal_sd_clock_power_save_t clk_power_save; /*!< SD clock power save */
#if defined (USE_HAL_SD_AUTO_DETECTION_FREQUENCY) && (USE_HAL_SD_AUTO_DETECTION_FREQUENCY == 0)
  uint32_t                clk_hz;         /*!< SD clock frequency  */
#endif /* USE_HAL_SD_AUTO_DETECTION_FREQUENCY */
} hal_sd_clock_config_t;

/*! SD Card globale configuration */
typedef struct
{
  hal_sd_clock_config_t          clk_cfg;                /*!< SD clock configuration                  */
  hal_sd_bus_wide_t              bus_wide;               /*!< SD bus wide                             */
  hal_sd_hardware_flow_control_t hw_flow_ctrl;           /*!< SD hardware flow control                */
  hal_sd_transceiver_t           transceiver;            /*!< SD transceiver                          */
  uint32_t                       data_timeout_cycle;     /*!< SD data timeout                         */
  uint32_t                       stop_xfer_timeout_ms;   /*!< SD stop transfer timeout in millisecond */
  uint32_t                       erase_timeout_ms;       /*!< SD erase timeout in millisecond         */
} hal_sd_config_t;

#if defined (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1)
/*! SD Card Data Control structure */
typedef struct
{
  uint32_t idma_node_offset;      /*!< SD Card DMA linked list configuration register */
  uint32_t idma_buffer_base_addr; /*!< SD Card DMA buffer base address register       */
  uint32_t idma_buffer_size;      /*!< SD Card DMA buffer size register               */
} hal_sd_node_t;
#endif /* USE_HAL_SD_LINKEDLIST */

typedef struct hal_sd_handle_s hal_sd_handle_t; /*!< SD handle Structure type */

#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
typedef void (*hal_sd_cb_t)(hal_sd_handle_t *hsd);                                    /*!< HAL SD Error/ABORT Callback pointer definition */
typedef void (*hal_sd_xfer_cb_t)(hal_sd_handle_t *hsd, hal_sd_event_cb_t cb_event);   /*!< HAL SD Process Callback pointer definition     */

/*! HAL SD Transceiver Callback pointer definition */
typedef void (*hal_sd_transceiver_cb_t)(hal_sd_handle_t *hsd, hal_sd_transceiver_state_t state);
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */

/*! SD handle Structure definition */
struct hal_sd_handle_s
{
  hal_sd_t                       instance;                          /*!< SD registers base address               */
  uint32_t                       *p_xfer_buff;                      /*!< Pointer to SD Xfer Buffer               */
  uint32_t                       xfer_size_byte;                    /*!< SD Xfer size                            */
  volatile uint32_t              context;                           /*!< SD transfer context                     */
  volatile hal_sd_state_t        global_state;                      /*!< SD card Global State                    */
  hal_sd_card_info_t             sd_card;                           /*!< SD Card information                     */
  hal_sd_transceiver_t           sd_transceiver;                    /*!< SD transceiver present                  */
#if defined (USE_HAL_SD_GET_SPEC_VERSION) && (USE_HAL_SD_GET_SPEC_VERSION == 1)
  hal_sd_specification_version_t version;                           /*!< SD card version                         */
#endif /* USE_HAL_SD_GET_SPEC_VERSION */
  uint32_t                       type;                              /*!< SD card Type                            */
  uint32_t                       speed;                             /*!< SD card Speed                           */
  uint32_t                       data_timeout_cycle;                /*!< SD data timeout                         */
  uint32_t                       stop_xfer_timeout_ms;              /*!< SD stop transfer timeout in millisecond */
  uint32_t                       erase_timeout_ms;                  /*!< SD erase timeout in millisecond         */
#if defined (USE_HAL_SD_GET_CID) && (USE_HAL_SD_GET_CID == 1)
  hal_sd_card_cid_t              cid;                               /*!< SD card identification                  */
#endif /* USE_HAL_SD_GET_CID */
#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
  hal_sd_xfer_cb_t               p_xfer_cplt_callback;              /*!< SD Xfer callback function               */
  hal_sd_cb_t                    p_error_callback;                  /*!< SD Error callback function              */
  hal_sd_cb_t                    p_abort_callback;                  /*!< SD Abort callback function              */
  hal_sd_transceiver_cb_t        p_transceiver_1_8V_callback;       /*!< SD Transceiver callback function        */
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */

#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
  volatile uint32_t              last_error_codes;                  /*!< SD last errors codes                   */
#endif /* USE_HAL_SD_GET_LAST_ERRORS */

#if defined (USE_HAL_SD_USER_DATA) && (USE_HAL_SD_USER_DATA == 1)
  const void                     *p_user_data;                      /*!< SD user data                           */
#endif /* USE_HAL_SD_USER_DATA */
};
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup SD_Exported_Functions HAL SD Functions
  * @{
  */

/** @defgroup SD_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_SD_Init(hal_sd_handle_t *hsd, hal_sd_t instance);
void         HAL_SD_DeInit(hal_sd_handle_t *hsd);
/**
  * @}
  */

/** @defgroup SD_Exported_Functions_Group2 Set and Get configurations functions
  * @{
  */
hal_status_t HAL_SD_SetConfig(hal_sd_handle_t *hsd, const hal_sd_config_t *p_config);
void         HAL_SD_GetConfig(const hal_sd_handle_t *hsd, hal_sd_config_t *p_config);
hal_status_t HAL_SD_NotifyCardInsertion(hal_sd_handle_t *hsd, const hal_sd_config_t *p_config);
hal_status_t HAL_SD_NotifyCardRemoval(hal_sd_handle_t *hsd);
hal_status_t HAL_SD_SetDataTimeout(hal_sd_handle_t *hsd, uint32_t data_timeout_cycle);
uint32_t     HAL_SD_GetDataTimeout(const hal_sd_handle_t *hsd);
hal_status_t HAL_SD_SetStopXferTimeout(hal_sd_handle_t *hsd, uint32_t stopxfer_timeout_ms);
uint32_t     HAL_SD_GetStopXferTimeout(const hal_sd_handle_t *hsd);
hal_status_t HAL_SD_SetEraseTimeout(hal_sd_handle_t *hsd, uint32_t erase_timeout_ms);
uint32_t     HAL_SD_GetEraseTimeout(const hal_sd_handle_t *hsd);
/**
  * @}
  */

/** @defgroup SD_Exported_Functions_Group3 Input and Output operation functions
  * @{
  */
hal_status_t HAL_SD_Erase(hal_sd_handle_t *hsd, uint32_t start_block_addr, uint32_t end_block_addr);

/* Blocking mode: Polling */
hal_status_t HAL_SD_ReadBlocks(hal_sd_handle_t *hsd, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr,
                               uint32_t timeout_ms);
hal_status_t HAL_SD_WriteBlocks(hal_sd_handle_t *hsd, const uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr,
                                uint32_t timeout_ms);

/* Non-Blocking mode: IT */
hal_status_t HAL_SD_ReadBlocks_IT(hal_sd_handle_t *hsd, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr);
hal_status_t HAL_SD_WriteBlocks_IT(hal_sd_handle_t *hsd, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr);

/* Non-Blocking mode: DMA in normal mode */
hal_status_t HAL_SD_ReadBlocks_DMA(hal_sd_handle_t *hsd, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr);
hal_status_t HAL_SD_WriteBlocks_DMA(hal_sd_handle_t *hsd, uint8_t *p_data, uint32_t block_addr, uint32_t blocks_nbr);

#if defined (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1)
/* Non-Blocking mode: DMA in linked-list mode */
hal_status_t HAL_SD_ReadBlocks_LinkedList(hal_sd_handle_t *hsd, uint32_t block_addr, uint32_t blocks_nbr,
                                          const hal_q_t *p_q);
hal_status_t HAL_SD_WriteBlocks_LinkedList(hal_sd_handle_t *hsd, uint32_t block_addr, uint32_t blocks_nbr,
                                           const hal_q_t *p_q);
#endif /* USE_HAL_SD_LINKEDLIST */

hal_status_t HAL_SD_Abort(hal_sd_handle_t *hsd);
hal_status_t HAL_SD_Abort_IT(hal_sd_handle_t *hsd);
/**
  * @}
  */

/** @defgroup SD_Exported_Functions_Group4 IRQHandler and Callbacks Functions
  * @{
  */
void HAL_SD_IRQHandler(hal_sd_handle_t *hsd);
void HAL_SD_XferCpltCallback(hal_sd_handle_t *hsd, hal_sd_event_cb_t cb_event);
void HAL_SD_ErrorCallback(hal_sd_handle_t *hsd);
void HAL_SD_AbortCallback(hal_sd_handle_t *hsd);
void HAL_SD_DriveTransceiver_1_8V_Callback(hal_sd_handle_t *hsd, hal_sd_transceiver_state_t state);

#if defined (USE_HAL_SD_REGISTER_CALLBACKS) && (USE_HAL_SD_REGISTER_CALLBACKS == 1)
hal_status_t HAL_SD_RegisterXferCpltCallback(hal_sd_handle_t *hsd, hal_sd_xfer_cb_t callback);
hal_status_t HAL_SD_RegisterErrorCallback(hal_sd_handle_t *hsd, hal_sd_cb_t callback);
hal_status_t HAL_SD_RegisterAbortCallback(hal_sd_handle_t *hsd, hal_sd_cb_t callback);
hal_status_t HAL_SD_RegisterTransceiverCallback(hal_sd_handle_t *hsd, hal_sd_transceiver_cb_t callback);
#endif /* USE_HAL_SD_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup SD_Exported_Functions_Group5 SD card related functions
  * @{
  */
hal_sd_state_t                 HAL_SD_GetState(const hal_sd_handle_t *hsd);
hal_sd_card_state_t            HAL_SD_GetCardState(const hal_sd_handle_t *hsd);
hal_status_t                   HAL_SD_GetCardStatus(hal_sd_handle_t *hsd, hal_sd_card_status_t *p_status);
void                           HAL_SD_GetCardInfo(const hal_sd_handle_t *hsd, hal_sd_card_info_t *p_card_info);
#if defined (USE_HAL_SD_GET_CID) && (USE_HAL_SD_GET_CID == 1)
void HAL_SD_GetCardCID(const hal_sd_handle_t *hsd, hal_sd_card_cid_t *p_cid);
#endif /* USE_HAL_SD_GET_CID */
hal_status_t                   HAL_SD_SwitchSpeedMode(hal_sd_handle_t *hsd, hal_sd_speed_mode_t speed_mode);
#if defined (USE_HAL_SD_GET_SPEC_VERSION) && (USE_HAL_SD_GET_SPEC_VERSION == 1)
hal_sd_specification_version_t HAL_SD_GetCardSpecVersion(const hal_sd_handle_t *hsd);
#endif /* USE_HAL_SD_GET_SPEC_VERSION */

#if defined(USE_HAL_SD_GET_LAST_ERRORS) && (USE_HAL_SD_GET_LAST_ERRORS == 1)
uint32_t                       HAL_SD_GetLastErrorCodes(const hal_sd_handle_t *hsd);
#endif /* USE_HAL_SD_GET_LAST_ERRORS */

#if defined (USE_HAL_SD_USER_DATA) && (USE_HAL_SD_USER_DATA == 1)
void HAL_SD_SetUserData(hal_sd_handle_t *hsd, const void *p_user_data);
const void *HAL_SD_GetUserData(const hal_sd_handle_t *hsd);
#endif /* USE_HAL_SD_USER_DATA */

uint32_t HAL_SD_GetClockFreq(const hal_sd_handle_t *hsd);
/**
  * @}
  */

/** @defgroup SD_Exported_Functions_Group6 Interrupt And Flag Configuration
  * @{
This section provides functions allowing to initialize and de-initialize the SD card device :
- Call the function HAL_SD_EnableIT() to enable the SD device interrupt.
- Call the function HAL_SD_DisableIT() to disable the device interrupt.
- Call the function HAL_SD_IsActiveFlag() to check whether the specified SD flag is set or not.
- Call the function HAL_SD_ClearFlag() to clear the SD device pending flags.
  */
/**
  * @brief  Enable the SD device interrupt.
  * @param  hsd       Pointer to a hal_sd_handle_t structure that contains the configuration information for the SD.
  * @param  interrupt Specifies the SDMMC interrupt sources to be enabled. This parameter can be a combination
                      of @ref SDMMC_CORE_Interrupt_sources group.
  */
__STATIC_INLINE void HAL_SD_EnableIT(hal_sd_handle_t *hsd, uint32_t interrupt)
{
  SDMMC_ENABLE_IT((SDMMC_TypeDef *)((uint32_t)hsd->instance), interrupt);
}

/**
  * @brief  Disable the SD device interrupt.
  * @param  hsd       Pointer to a hal_sd_handle_t structure that contains the configuration information for the SD.
  * @param  interrupt Specifies the SDMMC interrupt sources to be disable. This parameter can be a combination
                      of @ref SDMMC_CORE_Interrupt_sources group.
  */
__STATIC_INLINE void HAL_SD_DisableIT(hal_sd_handle_t *hsd, uint32_t interrupt)
{
  SDMMC_DISABLE_IT((SDMMC_TypeDef *)((uint32_t)hsd->instance), interrupt);
}

/**
  * @brief  Check whether the specified SD flag is set or not.
  * @param  hsd  Pointer to a hal_sd_handle_t structure that contains the configuration information for the SD.
  * @param  flag Specifies the flag source to check. This parameter can be a combination of
                 @ref SDMMC_CORE_Flags_sources group.
  * @retval The new state of SDMMC_FLAG (SET or RESET).
  */
__STATIC_INLINE uint32_t HAL_SD_IsActiveFlag(const hal_sd_handle_t *hsd, uint32_t flag)
{
  return (uint32_t)SDMMC_IS_ACTIVE_FLAG((SDMMC_TypeDef *)((uint32_t)hsd->instance), flag);
}

/**
  * @brief  Clear the SD pending flags.
  * @param  hsd  Pointer to a hal_sd_handle_t structure that contains the configuration information for the SD.
  * @param  flag Specifies the SDMMC flag sources to clear. This parameter can be a combination of
                 @ref SDMMC_CORE_Flags_sources group.
  */
__STATIC_INLINE void HAL_SD_ClearFlag(hal_sd_handle_t *hsd, uint32_t flag)
{
  SDMMC_CLEAR_FLAG((SDMMC_TypeDef *)((uint32_t)hsd->instance), flag);
}
/**
  * @}
  */

/**
  * @defgroup SD_Exported_Functions_Group7 linked-list queue functions
  * @{
  */
#if defined (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1)
/**
  * @brief Get SD Card Node information.
  * @param next_offset_addr  next node address offset.
  * @param p_addressing_mode node addressing mode.
  */
__STATIC_INLINE void HAL_SD_GetNodeInfo(uint32_t *next_offset_addr, hal_q_addressing_mode_t *p_addressing_mode)
{
  *next_offset_addr = 0U;
  *p_addressing_mode = HAL_Q_ADDRESSING_BASE_OFFSET;
}

/**
  * @brief Set SD Card node address.
  * @param head_node_addr   Head node address.
  * @param prev_node_addr   Previous node address.
  * @param next_node_addr   Next node address.
  * @param node_addr_offset Node address offset.
  */
__STATIC_INLINE void HAL_SD_SetNodeAddress(uint32_t head_node_addr, uint32_t prev_node_addr, uint32_t next_node_addr,
                                           uint32_t node_addr_offset)
{
  STM32_MODIFY_REG((*(uint32_t *)(prev_node_addr + node_addr_offset)), SDMMC_IDMALAR_IDMALA,
                   ((next_node_addr - head_node_addr) & SDMMC_IDMALAR_IDMALA));
}

/**
  * @brief Get SD Card node address.
  * @param head_node_addr    Head node address.
  * @param current_node_addr Current node address.
  * @param node_addr_offset  Node address offset.
  * @retval SDMMC node address.
  */
__STATIC_INLINE uint32_t HAL_SD_GetNodeAddress(uint32_t head_node_addr, uint32_t current_node_addr,
                                               uint32_t node_addr_offset)
{
  return (head_node_addr + (*(uint32_t *)(current_node_addr + node_addr_offset) & SDMMC_IDMALAR_IDMALA));
}

hal_status_t HAL_SD_FillNodeConfig(hal_sd_node_t *p_node, void *p_buffer, uint32_t size_byte);
void         HAL_SD_GetNodeConfig(const hal_sd_node_t *p_node, uint32_t *p_buffer, uint32_t *p_size_byte);
hal_status_t HAL_SD_SetNodeDataBufferState(const hal_sd_node_t *p_node, hal_sd_node_state_t state);
hal_sd_node_state_t HAL_SD_GetNodeDataBufferState(const hal_sd_node_t *p_node);
#endif /* (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1) */
/**
  * @}
  */

/** @defgroup SD_Exported_Functions_Group8 SD Delay Block functions
  * @{
  */
hal_status_t HAL_SD_SetConfigDlybDelay(const hal_sd_handle_t *hsd, uint32_t clock_phase_value);
uint32_t     HAL_SD_GetDlybOutputClockPhase(const hal_sd_handle_t *hsd);
hal_status_t HAL_SD_CalculateDlybMaxClockPhase(hal_sd_handle_t *hsd, uint32_t *p_max_clock_phase);
hal_status_t HAL_SD_EnableDlyb(hal_sd_handle_t *hsd);
hal_status_t HAL_SD_DisableDlyb(hal_sd_handle_t *hsd);
hal_sd_dlyb_state_t HAL_SD_IsEnabledDlyb(hal_sd_handle_t *hsd);
/**
  * @}
  */

/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
#if defined (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1)
/** @defgroup SD_Private_Variables SD Private Variables
  * @{
  */
/*! HAL SD addressing descriptor operation structure definition */
static const hal_q_desc_ops_t HAL_SD_DescOps =
{
  HAL_SD_GetNodeInfo,    /*!< Get SD Card node information */
  HAL_SD_SetNodeAddress, /*!< Set SD Card node address     */
  HAL_SD_GetNodeAddress, /*!< Get SD Card node address     */
};
/**
  * @}
  */
#endif /* (USE_HAL_SD_LINKEDLIST) && (USE_HAL_SD_LINKEDLIST == 1) */

/**
  * @}
  */
#endif /* SDMMC1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7Pxx_HAL_SD_H */
