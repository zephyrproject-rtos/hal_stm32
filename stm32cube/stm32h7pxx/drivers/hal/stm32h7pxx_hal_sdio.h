/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_sdio.h
  * @brief   Header file of SDIO HAL module.
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
#ifndef STM32H7PXX_HAL_SDIO_H
#define STM32H7PXX_HAL_SDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_sdmmc_core.h"
#include "stm32h7pxx_dlyb_core.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */
#if defined(SDMMC1)

/** @defgroup SDIO SDIO
  * @brief SDIO HAL module driver
  * @{
  */
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Exported_Constants HAL SDIO Constants
  * @{
  */

/** @defgroup SDIO_Error_Status SDIO Error status definition
  * @{
  */
#define HAL_SDIO_ERROR_NONE          SDMMC_ERROR_NONE          /*!< No error                                    */
#define HAL_SDIO_ERROR_DATA_CRC_FAIL SDMMC_ERROR_DATA_CRC_FAIL /*!< Data block sent/received (CRC check failed) */
#define HAL_SDIO_ERROR_DATA_TIMEOUT  SDMMC_ERROR_DATA_TIMEOUT  /*!< Data timeout                                */
#define HAL_SDIO_ERROR_TX_UNDERRUN   SDMMC_ERROR_TX_UNDERRUN   /*!< Transmit FIFO underrun                      */
#define HAL_SDIO_ERROR_RX_OVERRUN    SDMMC_ERROR_RX_OVERRUN    /*!< Receive FIFO overrun                        */
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Timeout SDIO Transfer Timeout definition
  * @{
  */
#define HAL_SDIO_DATA_MAX_TIMEOUT  0xFFFFFFFFU /*!< SDIO data timeout */
/**
  * @}
  */

/** @defgroup SDIO_MAX_IO_FUNCTION_NUMBER SDIO maximum IO number
  * @{
  */
#define HAL_SDIO_MAX_IO_NUMBER 7U /*!< SDIO support maximum IO number */
/**
  * @}
  */

/**
  * @}
  */
/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Exported_Types HAL SDIO Types
  * @{
  */

/*! SDIO Card instance */
typedef enum
{
  HAL_SDIO_CARD_1 = SDMMC1_BASE, /*!< HAL SDIO card instance 1 */
#if defined (SDMMC2)
  HAL_SDIO_CARD_2 = SDMMC2_BASE  /*!< HAL SDIO card instance 2 */
#endif /* SDMMC2 */
} hal_sdio_t;

/*! SDIO Card global state */
typedef enum
{
  HAL_SDIO_STATE_RESET        = (0U),         /*!< SDIO card not Initialized                */
  HAL_SDIO_STATE_INIT         = (1UL << 31U), /*!< SDIO card initialized but not configured */
  HAL_SDIO_STATE_CARD_REMOVED = (1UL << 30U), /*!< SDIO card removed                        */
  HAL_SDIO_STATE_IDLE         = (1UL << 29U), /*!< SDIO card ready for use                  */
  HAL_SDIO_STATE_ACTIVE       = (1UL << 28U)  /*!< SDIO card operation IO state             */
} hal_sdio_state_t;

/*! SDIO Card speed mode */
typedef enum
{
  HAL_SDIO_SPEED_MODE_SDR12  = SDMMC_SDIO_BUS_SPEED_SDR12,  /*!< SDIO speed mode SDR12  */
  HAL_SDIO_SPEED_MODE_SDR25  = SDMMC_SDIO_BUS_SPEED_SDR25,  /*!< SDIO speed mode SDR25  */
  HAL_SDIO_SPEED_MODE_SDR50  = SDMMC_SDIO_BUS_SPEED_SDR50,  /*!< SDIO speed mode SDR50  */
  HAL_SDIO_SPEED_MODE_DDR50  = SDMMC_SDIO_BUS_SPEED_SDR104, /*!< SDIO speed mode DDR50  */
  HAL_SDIO_SPEED_MODE_SDR104 = SDMMC_SDIO_BUS_SPEED_DDR50   /*!< SDIO speed mode SDR104 */
} hal_sdio_speed_mode_t;

/*! SDIO Functions number definition */
typedef enum
{
  HAL_SDIO_FUNCTION_0 = 0U, /*!< SDIO function 0 */
  HAL_SDIO_FUNCTION_1 = 1U, /*!< SDIO function 1 */
  HAL_SDIO_FUNCTION_2 = 2U, /*!< SDIO function 2 */
  HAL_SDIO_FUNCTION_3 = 3U, /*!< SDIO function 3 */
  HAL_SDIO_FUNCTION_4 = 4U, /*!< SDIO function 4 */
  HAL_SDIO_FUNCTION_5 = 5U, /*!< SDIO function 5 */
  HAL_SDIO_FUNCTION_6 = 6U, /*!< SDIO function 6 */
  HAL_SDIO_FUNCTION_7 = 7U  /*!< SDIO function 7 */
} hal_sdio_function_t;

/*! SDIO Card block size */
typedef enum
{
  HAL_SDIO_BLOCK_SIZE_1BYTE    = SDMMC_SDIO_BLOCK_SIZE_1BYTE,    /*!< SDIO block size 1 byte    */
  HAL_SDIO_BLOCK_SIZE_2BYTE    = SDMMC_SDIO_BLOCK_SIZE_2BYTE,    /*!< SDIO block size 2 byte    */
  HAL_SDIO_BLOCK_SIZE_4BYTE    = SDMMC_SDIO_BLOCK_SIZE_4BYTE,    /*!< SDIO block size 4 byte    */
  HAL_SDIO_BLOCK_SIZE_8BYTE    = SDMMC_SDIO_BLOCK_SIZE_8BYTE,    /*!< SDIO block size 8 byte    */
  HAL_SDIO_BLOCK_SIZE_16BYTE   = SDMMC_SDIO_BLOCK_SIZE_16BYTE,   /*!< SDIO block size 16 byte   */
  HAL_SDIO_BLOCK_SIZE_32BYTE   = SDMMC_SDIO_BLOCK_SIZE_32BYTE,   /*!< SDIO block size 32 byte   */
  HAL_SDIO_BLOCK_SIZE_64BYTE   = SDMMC_SDIO_BLOCK_SIZE_64BYTE,   /*!< SDIO block size 64 byte   */
  HAL_SDIO_BLOCK_SIZE_128BYTE  = SDMMC_SDIO_BLOCK_SIZE_128BYTE,  /*!< SDIO block size 128 byte  */
  HAL_SDIO_BLOCK_SIZE_256BYTE  = SDMMC_SDIO_BLOCK_SIZE_256BYTE,  /*!< SDIO block size 256 byte  */
  HAL_SDIO_BLOCK_SIZE_512BYTE  = SDMMC_SDIO_BLOCK_SIZE_512BYTE,  /*!< SDIO block size 512 byte  */
  HAL_SDIO_BLOCK_SIZE_1024BYTE = SDMMC_SDIO_BLOCK_SIZE_1024BYTE, /*!< SDIO block size 1024 byte */
  HAL_SDIO_BLOCK_SIZE_2048BYTE = SDMMC_SDIO_BLOCK_SIZE_2048BYTE, /*!< SDIO block size 2048 byte */
} hal_sdio_block_size_t;

/*! SDIO bus width */
typedef enum
{
  HAL_SDIO_BUS_WIDTH_8BIT_NOT_SUPPORTED = 0U, /*!< SDIO bus width 8 bit is not supported */
  HAL_SDIO_BUS_WIDTH_8BIT_SUPPORTED     = 1U  /*!< SDIO bus width 8 bit is supported     */
} hal_sdio_bus_width_8bit_t;

/*! SDIO Card clock edge */
typedef enum
{
  HAL_SDIO_CLOCK_EDGE_RISING  = SDMMC_CLOCK_EDGE_RISING,  /*!< Clock edge is in rising mode  */
  HAL_SDIO_CLOCK_EDGE_FALLING = SDMMC_CLOCK_EDGE_FALLING  /*!< Clock edge is in falling mode */
} hal_sdio_clock_edge_t;

/*! SDIO Card clock power saving */
typedef enum
{
  HAL_SDIO_CLOCK_POWER_SAVE_DISABLE = SDMMC_CLOCK_POWER_SAVE_DISABLE, /*!< Clock is always Disabled  */
  HAL_SDIO_CLOCK_POWER_SAVE_ENABLE  = SDMMC_CLOCK_POWER_SAVE_ENABLE   /*!< Clock is only enabled when
                                                                           the bus is active         */
} hal_sdio_clock_power_save_t;

/*! SDIO Card bus width */
typedef enum
{
  HAL_SDIO_BUS_WIDE_1BIT = SDMMC_BUS_WIDE_1BIT, /*!< Default 1-bit wide bus mode */
  HAL_SDIO_BUS_WIDE_4BIT = SDMMC_BUS_WIDE_4BIT, /*!< 4-bit wide bus mode         */
  HAL_SDIO_BUS_WIDE_8BIT = SDMMC_BUS_WIDE_8BIT  /*!< 8-bit wide bus mode         */
} hal_sdio_bus_wide_t;

/*! SDIO Card hardware flow control */
typedef enum
{
  HAL_SDIO_HARDWARE_FLOW_CONTROL_DISABLE = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE, /*!< Hardware flow control is disabled */
  HAL_SDIO_HARDWARE_FLOW_CONTROL_ENABLE  = SDMMC_HARDWARE_FLOW_CONTROL_ENABLE   /*!< Hardware flow control is enabled  */
} hal_sdio_hardware_flow_control_t;

/*! SDIO Card transceiver present */
typedef enum
{
  HAL_SDIO_TRANSCEIVER_NOT_PRESENT = SDMMC_TRANSCEIVER_NOT_PRESENT, /*!< SDIO Transceiver is not present */
  HAL_SDIO_TRANSCEIVER_PRESENT     = SDMMC_TRANSCEIVER_PRESENT      /*!< SDIO Transceiver is present     */
} hal_sdio_transceiver_t;

/*! SDIO Card transceiver state */
typedef enum
{
  HAL_SDIO_TRANSCEIVER_DISABLE = SDMMC_TRANSCEIVER_DISABLE, /*!< SDIO transceiver disable */
  HAL_SDIO_TRANSCEIVER_ENABLE  = SDMMC_TRANSCEIVER_ENABLE   /*!< SDIO transceiver enable  */
} hal_sdio_transceiver_state_t;

/*! SDIO block mode */
typedef enum
{
  HAL_SDIO_BLOCK_MODE_BYTE  = SDMMC_SDIO_MODE_BYTE,  /*!< SDIO block mode byte  */
  HAL_SDIO_BLOCK_MODE_BLOCK = SDMMC_SDIO_MODE_BLOCK  /*!< SDIO block mode block */
} hal_sdio_block_mode_t;

/*! SDIO operation code */
typedef enum
{
  HAL_SDIO_OP_CODE_INC_NO   = SDMMC_SDIO_NO_INC,  /*!< SDIO operation code no increment   */
  HAL_SDIO_OP_CODE_INC_AUTO = SDMMC_SDIO_AUTO_INC /*!< SDIO operation code auto increment */
} hal_sdio_operation_code_inc_t;

/*! SDIO read after write(RAW) */
typedef enum
{
  HAL_SDIO_WRITE_ONLY       = SDMMC_SDIO_WO, /*!< SDIO Write only       */
  HAL_SDIO_READ_AFTER_WRITE = SDMMC_SDIO_RAW /*!< SDIO Read after write */
} hal_sdio_raw_t;

/*! SDIO event callback */
typedef enum
{
  HAL_SDIO_EVENT_CB_TX_CPLT = 0x01U, /*!< SDIO Tx complete callback */
  HAL_SDIO_EVENT_CB_RX_CPLT = 0x02U, /*!< SDIO Rx complete callback */
} hal_sdio_event_cb_t;

/*! SDIO Card DLYB state */
typedef enum
{
  HAL_SDIO_DLYB_DISABLED = DLYB_DISABLED, /*!< SDIO DLYB disabled */
  HAL_SDIO_DLYB_ENABLED  = DLYB_ENABLED   /*!< SDIO DLYB enabled  */
} hal_sdio_dlyb_state_t;

/*! SDIO Card Common Control Register structure definition */
typedef struct
{
  uint32_t                   card_capability;    /*!< SDIO card capability         */
  uint32_t                   common_cis_pointer; /*!< Point to common CIS          */
  uint8_t                    sdio_revision;      /*!< SDIO revision                */
  uint8_t                    cccr_revision;      /*!< CCCR revision                */
  uint8_t                    sd_spec_revision;   /*!< SD revision                  */
  hal_sdio_bus_width_8bit_t bus_width_8Bit;      /*!< SDIO bus width 8 bit support */
} hal_sdio_cccr_t;

/*! sdio card FBR register(Function Basic Register) */
typedef struct
{
  uint32_t io_pointer_to_cis;   /*!< SDIO current IO pointer to CIS         */
  uint32_t io_pointer_to_csa;   /*!< SDIO current IO pointer to CSA         */
  uint8_t flags;                /*!< SDIO current IO flags                  */
  uint8_t io_std_function_code; /*!< SDIO current IO standard function code */
  uint8_t io_ext_function_code; /*!< SDIO current IO extended function code */
} hal_sdio_fbr_t;

/*! SDIO CMD52 structure definition */
typedef struct
{
  hal_sdio_raw_t read_after_write; /*!< This is the read after write flag, it is used for write access only     */

  uint32_t       reg_addr;         /*!< This is the address of the byte of data inside of the selected function
                                        to read or write                                                        */

  hal_sdio_function_t   io_function_nbr;  /*!< The number of the function within the IO card you wish to read or write */
} hal_sdio_direct_cmd_t;

/*! SDIO CMD53 structure definition */
typedef struct
{
  hal_sdio_operation_code_inc_t operation_code;  /*!< Read/Write operation mode                            */

  hal_sdio_block_mode_t         block_mode;      /*!< Bytes or Blocks mode                                 */

  uint32_t                      reg_addr;        /*!< This is the address of the byte of data inside of the
                                                      selected function to read or write                   */

  hal_sdio_function_t           io_function_nbr; /*!< The number of the function within the IO card you
                                                      wish to read or write                                */
} hal_sdio_extended_cmd_t;

/*! SDIO Card clock configuration */
typedef struct
{
  hal_sdio_clock_edge_t       clk_edge;       /*!< SDIO clock edge       */
  hal_sdio_clock_power_save_t clk_power_save; /*!< SDIO clock power save */
  uint32_t                    clk_hz;         /*!< SDIO clock frequency  */
} hal_sdio_clock_config_t;

/*! SDIO globale configuration */
typedef struct
{
  hal_sdio_clock_config_t          clk_cfg;            /*!< SDIO clock configuration   */
  hal_sdio_bus_wide_t              bus_wide;           /*!< SDIO bus wide              */
  hal_sdio_hardware_flow_control_t hw_flow_ctrl;       /*!< SDIO hardware flow control */
  hal_sdio_transceiver_t           transceiver;        /*!< SDIO transceiver           */
  uint32_t                         data_timeout_cycle; /*!< SDIO data timeout          */
} hal_sdio_config_t;

typedef struct hal_sdio_handle_s hal_sdio_handle_t; /*!< SDIO handle Structure type */

#if defined (USE_HAL_SDIO_REGISTER_CALLBACKS) && (USE_HAL_SDIO_REGISTER_CALLBACKS == 1)
typedef void (*hal_sdio_cb_t)(hal_sdio_handle_t *hsdio); /*!< HAL SDIO Process callback pointer definition     */

typedef void (*hal_sdio_xfer_cb_t)(hal_sdio_handle_t *hsdio, hal_sdio_event_cb_t cb_event);
/*!< HAL SDIO Process Callback pointer definition     */
typedef void (*hal_sdio_transceiver_cb_t)(hal_sdio_handle_t *hsdio, hal_sdio_transceiver_state_t state);
/*!< HAL SDIO Transceiver callback pointer definition */
#endif /* USE_HAL_SDIO_REGISTER_CALLBACKS */

typedef hal_status_t (*hal_sdio_identify_card_t)(hal_sdio_handle_t *hsdio);
/*!< HAL SDIO Enumeration card pointer definition */

typedef void (*hal_sdio_io_function_cb_t)(hal_sdio_handle_t *hsdio, uint32_t func);
/*!< HAL SDIO IO Function callback pointer definition */

/*! SDIO handle structure definition */
struct hal_sdio_handle_s
{
  hal_sdio_t                 instance;                 /*!< SDIO registers base address                            */

  volatile hal_sdio_state_t  global_state;             /*!< SDIO card State                                        */

  uint32_t                   xfer_size_byte;           /*!< SDIO Xfer size                                         */

  uint32_t                   remaining_data;           /*!< Remaining data to transfer                             */

  uint32_t                   next_data_addr;           /*!< SDIO Next data address                                 */

  uint32_t                   next_reg_addr;            /*!< SDIO Next register address                             */

  volatile uint32_t          context;                  /*!< SDIO transfer context                                  */

  uint32_t                   data_timeout_cycle;       /*!< SDIO data timeout                                      */

  hal_sdio_block_size_t      block_size;               /*!< SDIO Block size                                        */

  uint8_t                   *p_xfer_buff;              /*!< Pointer to SDIO Xfer Buffer                            */

  uint8_t                    io_function_enabled_mask; /*!< SDIO used to record current enabled io interrupt       */

  volatile uint8_t           io_interrupt_nbr;         /*!< SDIO used to record total enabled io interrupt numbers */

  hal_sdio_transceiver_t     sdio_transceiver;         /*!< SDIO transceiver present                               */

#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
  volatile uint32_t          last_error_codes;         /*!< SDIO last errors codes                                 */
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

#if defined (USE_HAL_SDIO_USER_DATA) && (USE_HAL_SDIO_USER_DATA == 1)
  const void                 *p_user_data;             /*!< SDIO user data                                         */
#endif /* USE_HAL_SDIO_USER_DATA */

#if defined (USE_HAL_SDIO_REGISTER_CALLBACKS) && (USE_HAL_SDIO_REGISTER_CALLBACKS == 1)
  hal_sdio_xfer_cb_t         p_xfer_cplt_callback;        /*!< SDIO Xfer callback function        */
  hal_sdio_cb_t              p_error_callback;            /*!< SDIO Error callback function       */
  hal_sdio_transceiver_cb_t  p_transceiver_1_8V_callback; /*!< SDIO Transceiver callback function */
#endif /* USE_HAL_SDIO_REGISTER_CALLBACKS */

  hal_sdio_identify_card_t   p_sdio_card_identification_callback; /*!< SDIO enumeration sequence callback function */

  hal_sdio_io_function_cb_t  p_io_function_cplt_callback[HAL_SDIO_MAX_IO_NUMBER]; /*!< SDIO IO callback function */
};
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Exported_Functions HAL SDIO Functions
  * @{
  */
/** @defgroup SDIO_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_SDIO_Init(hal_sdio_handle_t *hsdio, hal_sdio_t instance);
void         HAL_SDIO_DeInit(hal_sdio_handle_t *hsdio);
/**
  * @}
  */

/** @defgroup SDIO_Exported_Functions_Group2 Set and Get configurations functions
  * @{
  */
hal_status_t HAL_SDIO_SetConfig(hal_sdio_handle_t *hsdio, const hal_sdio_config_t *p_config,
                                hal_sdio_identify_card_t sdio_identify_card);
void HAL_SDIO_GetConfig(const hal_sdio_handle_t *hsdio, hal_sdio_config_t *p_config);

hal_status_t HAL_SDIO_NotifyCardInsertion(hal_sdio_handle_t *hsdio, const hal_sdio_config_t *p_config);
hal_status_t HAL_SDIO_NotifyCardRemoval(hal_sdio_handle_t *hsdio);

hal_status_t HAL_SDIO_SetDataBusWidth(hal_sdio_handle_t *hsdio, hal_sdio_bus_wide_t bus_wide);
hal_sdio_bus_wide_t HAL_SDIO_GetDataBusWidth(const hal_sdio_handle_t *hsdio);

hal_status_t HAL_SDIO_SetTransferClockFreq(const hal_sdio_handle_t *hsdio, const uint32_t transfer_clock_freq_hz);
uint32_t     HAL_SDIO_GetTransferClockFreq(const hal_sdio_handle_t *hsdio);

hal_status_t HAL_SDIO_SetBlockSize(hal_sdio_handle_t *hsdio, hal_sdio_function_t function_nbr,
                                   hal_sdio_block_size_t block_size);
hal_status_t HAL_SDIO_SetSpeedMode(hal_sdio_handle_t *hsdio, const hal_sdio_speed_mode_t speed_mode);
hal_status_t HAL_SDIO_ResetCard(hal_sdio_handle_t *hsdio);
hal_status_t HAL_SDIO_SetDataTimeout(hal_sdio_handle_t *hsdio, uint32_t data_timeout_cycle);
uint32_t     HAL_SDIO_GetDataTimeout(const hal_sdio_handle_t *hsdio);
uint32_t     HAL_SDIO_GetClockFreq(const hal_sdio_handle_t *hsdio);
/**
  * @}
  */

/** @defgroup SDIO_Exported_Functions_Group3 Process functions
  * @{
  */
hal_status_t HAL_SDIO_ReadDirect(hal_sdio_handle_t *hsdio, const hal_sdio_direct_cmd_t *p_argument, uint8_t *p_data);
hal_status_t HAL_SDIO_WriteDirect(hal_sdio_handle_t *hsdio, const hal_sdio_direct_cmd_t *p_argument, uint8_t data);

hal_status_t HAL_SDIO_ReadExtended(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument, uint8_t *p_data,
                                   uint32_t size_byte, uint32_t timeout_ms);

hal_status_t HAL_SDIO_WriteExtended(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                    const uint8_t *p_data, uint32_t size_byte, uint32_t timeout_ms);

hal_status_t HAL_SDIO_ReadExtended_DMA(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                       uint8_t *p_data, uint32_t size_byte);

hal_status_t HAL_SDIO_WriteExtended_DMA(hal_sdio_handle_t *hsdio, const hal_sdio_extended_cmd_t *p_argument,
                                        uint8_t *p_data, uint32_t size_byte);
/**
  * @}
  */

/** @defgroup SDIO_Exported_Functions_Group4 IRQHandler and Callbacks Functions
  * @{
  */
void HAL_SDIO_IRQHandler(hal_sdio_handle_t *hsdio);
void HAL_SDIO_XferCpltCallback(hal_sdio_handle_t *hsdio, hal_sdio_event_cb_t cb_event);
void HAL_SDIO_ErrorCallback(hal_sdio_handle_t *hsdio);
void HAL_SDIO_IOFunctionCallback(hal_sdio_handle_t *hsdio, uint32_t func);
void HAL_SDIO_DriveTransceiver_1_8V_Callback(hal_sdio_handle_t *hsdio, hal_sdio_transceiver_state_t state);

#if defined (USE_HAL_SDIO_REGISTER_CALLBACKS) && (USE_HAL_SDIO_REGISTER_CALLBACKS == 1U)
hal_status_t HAL_SDIO_RegisterXferCpltCallback(hal_sdio_handle_t *hsdio, hal_sdio_xfer_cb_t callback);
hal_status_t HAL_SDIO_RegisterErrorCallback(hal_sdio_handle_t *hsdio, hal_sdio_cb_t callback);
hal_status_t HAL_SDIO_RegisterTransceiverCallback(hal_sdio_handle_t *hsdio, hal_sdio_transceiver_cb_t callback);
#endif /* USE_HAL_SDIO_REGISTER_CALLBACKS */
hal_status_t HAL_SDIO_RegisterIOFunctionCallback(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function,
                                                 hal_sdio_io_function_cb_t callback);
/**
  * @}
  */

/** @defgroup SDIO_Exported_Functions_Group5 SDIO card related functions
  * @{
  */
hal_sdio_state_t HAL_SDIO_GetState(const hal_sdio_handle_t *hsdio);

hal_status_t HAL_SDIO_GetCardCommonControlRegister(hal_sdio_handle_t *hsdio, hal_sdio_cccr_t *p_cccr);
hal_status_t HAL_SDIO_GetCardFunctionBasicRegister(hal_sdio_handle_t *hsdio, hal_sdio_fbr_t *p_fbr);

#if defined(USE_HAL_SDIO_GET_LAST_ERRORS) && (USE_HAL_SDIO_GET_LAST_ERRORS == 1)
uint32_t HAL_SDIO_GetLastErrorCodes(const hal_sdio_handle_t *hsdio);
#endif /* USE_HAL_SDIO_GET_LAST_ERRORS */

#if defined (USE_HAL_SDIO_USER_DATA) && (USE_HAL_SDIO_USER_DATA == 1)
void HAL_SDIO_SetUserData(hal_sdio_handle_t *hsdio, const void *p_user_data);
const void *HAL_SDIO_GetUserData(const hal_sdio_handle_t *hsdio);
#endif /* USE_HAL_SDIO_USER_DATA */
/**
  * @}
  */

/** @defgroup SDIO_Exported_Functions_Group6 Peripheral IO interrupt
  * @{
  */
hal_status_t HAL_SDIO_EnableIOFunctionInterrupt(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function);
hal_status_t HAL_SDIO_DisableIOFunctionInterrupt(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function);
hal_status_t HAL_SDIO_EnableIOFunction(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function);
hal_status_t HAL_SDIO_DisableIOFunction(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function);
hal_status_t HAL_SDIO_SelectIOFunction(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function);
hal_status_t HAL_SDIO_AbortIOFunction(hal_sdio_handle_t *hsdio, hal_sdio_function_t io_function);
hal_status_t HAL_SDIO_EnableIOAsynInterrupt(hal_sdio_handle_t *hsdio);
hal_status_t HAL_SDIO_DisableIOAsynInterrupt(hal_sdio_handle_t *hsdio);
/**
  * @}
  */

/** @defgroup SDIO_Exported_Functions_Group7 SDIO Delay Block functions
  * @{
  */
hal_status_t HAL_SDIO_SetConfigDlybDelay(const hal_sdio_handle_t *hsdio, uint32_t clock_phase_value);
uint32_t     HAL_SDIO_GetDlybOutputClockPhase(const hal_sdio_handle_t *hsdio);
hal_status_t HAL_SDIO_CalculateDlybMaxClockPhase(hal_sdio_handle_t *hsdio, uint32_t *p_max_clock_phase);
hal_status_t HAL_SDIO_EnableDlyb(hal_sdio_handle_t *hsdio);
hal_status_t HAL_SDIO_DisableDlyb(hal_sdio_handle_t *hsdio);
hal_sdio_dlyb_state_t HAL_SDIO_IsEnabledDlyb(const hal_sdio_handle_t *hsdio);
/**
  * @}
  */

/** @defgroup SDIO_Exported_Functions_Group8 Interrupt And Flag Configuration
  * @{
This section provides functions allowing to initialize and de-initialize the SDIO card device :
- Call the function HAL_SDIO_EnableIT() to enable the SDIO device interrupt.
- Call the function HAL_SDIO_DisableIT() to disable the device interrupt.
- Call the function HAL_SDIO_IsEnabledIT() to check whether or not the specified SDIO interrupt is set.
- Call the function HAL_SDIO_IsActiveFlag() to check whether the specified SDIO flag is set or not.
- Call the function HAL_SDIO_ClearFlag() to clear the SDIO device pending flags.
  */
/**
  * @brief Enable the SDIO device interrupt.
  * @param hsdio     Pointer to a hal_sdio_handle_t structure that contains the configuration information for the SDIO.
  * @param interrupt Specifies the SDMMC interrupt sources to be enabled. This parameter can be a combination
                     of @ref SDMMC_CORE_Interrupt_sources group.
  */
__STATIC_INLINE void HAL_SDIO_EnableIT(hal_sdio_handle_t *hsdio, uint32_t interrupt)
{
  SDMMC_ENABLE_IT((SDMMC_TypeDef *)((uint32_t)hsdio->instance), interrupt);
}

/**
  * @brief Disable the SDIO device interrupt.
  * @param hsdio     Pointer to a hal_sdio_handle_t structure that contains the configuration information for the SDIO.
  * @param interrupt Specifies the SDMMC interrupt sources to be disable. This parameter can be a combination
                     of @ref SDMMC_CORE_Interrupt_sources group.
  */
__STATIC_INLINE void HAL_SDIO_DisableIT(hal_sdio_handle_t *hsdio, uint32_t interrupt)
{
  SDMMC_DISABLE_IT((SDMMC_TypeDef *)((uint32_t)hsdio->instance), interrupt);
}

/**
  * @brief Check whether or not the specified SDIO interrupt is set.
  * @param hsdio     Pointer to a hal_sdio_handle_t structure that contains the configuration information for the SDIO.
  * @param interrupt Specifies the SDMMC interrupt source to check.
  * @retval The state of SDIO interrupt (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_SDIO_IsEnabledIT(const hal_sdio_handle_t *hsdio, uint32_t interrupt)
{
  return ((uint32_t)((STM32_READ_BIT(((SDMMC_TypeDef *)(uint32_t)(hsdio->instance))->MASKR, interrupt) == interrupt)));
}

/**
  * @brief Check whether the specified SDIO flag is set or not.
  * @param hsdio Pointer to a hal_sdio_handle_t structure that contains the configuration information for the SDIO.
  * @param flag  Specifies the flag source to check.
  * @retval The new state of SDMMC_FLAG (SET or RESET).
  */
__STATIC_INLINE uint32_t HAL_SDIO_IsActiveFlag(const hal_sdio_handle_t *hsdio, uint32_t flag)
{
  return (uint32_t)SDMMC_IS_ACTIVE_FLAG((SDMMC_TypeDef *)((uint32_t)hsdio->instance), flag);
}

/**
  * @brief Clear the SDIO pending flags.
  * @param hsdio Pointer to a hal_sdio_handle_t structure that contains the configuration information for the SDIO.
  * @param flag  Specifies the SDMMC flag sources to clear. This parameter can be a combination of
                 @ref SDMMC_CORE_Flags_sources group.
  */
__STATIC_INLINE void HAL_SDIO_ClearFlag(hal_sdio_handle_t *hsdio, uint32_t flag)
{
  SDMMC_CLEAR_FLAG((SDMMC_TypeDef *)((uint32_t)hsdio->instance), flag);
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

#endif /* STM32H7Pxx_HAL_SDIO_H */
