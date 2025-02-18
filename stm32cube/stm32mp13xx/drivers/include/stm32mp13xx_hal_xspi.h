/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_xspi.h
  * @author  MCD Application Team
  * @brief   Header file of XSPI HAL module for supporting QuadSPI
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP13xx_HAL_XSPI_H
#define STM32MP13xx_HAL_XSPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal_def.h"
#include "stm32mp13xx_hal_mdma.h"

#if defined(QUADSPI) || defined(QUADSPI1) || defined(QUADSPI2)

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @addtogroup XSPI
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup XSPI_Exported_Types XSPI Exported Types
  * @{
  */

/**
  * @brief  XSPI Init structure definition
  */
typedef struct
{
  uint32_t ClockPrescaler;     /* Specifies the prescaler factor for generating clock based on the AHB clock.
                                  This parameter can be a number between 0 and 255 */
  uint32_t FifoThresholdByte;  /* Specifies the threshold number of bytes in the FIFO (used only in indirect mode)
                                  This parameter can be a value between 1 and 32. Earlier
                                  parameter FifoThreshold is renamed to FifoThresholdByte for better
                                  compatibility with ExtMem Manager */
  uint32_t SampleShifting;     /* Specifies the Sample Shift. The data is sampled 1/2 clock cycle delay later to
                                  take in account external signal delays.
                                  (It should be XSPI_SAMPLE_SHIFTING_NONE in DTR mode)
                                  This parameter can be a value of @ref XSPI_SampleShifting */
  uint32_t MemorySize;          /* Specifies the Memory Size. MemorySize+1 is effectively the number of address bits
                                  required to address the flash memory. The flash capacity can be up to 4GB
                                  (addressed using 32 bits) in indirect mode, but the addressable space in
                                  memory-mapped mode is limited to 256MB
                                  This parameter can be a number between 0 and 31. Earlier parameter
                                  FlashSize is renamed to MemorySize for better compatibility
                                  with ExtMem Manager */
  uint32_t ChipSelectHighTimeCycle; /* Specifies the Chip Select High Time. ChipSelectHighTimeCycle+1 defines
                                       the minimum number of clock cycles which the chip select must remain
                                       high between commands. Earlier parameter ChipSelectHighTime is renamed
                                       to FifoThresholdByte for better compatibility with ExtMem Manager
                                       This parameter can be a value of @ref XSPI_ChipSelectHighTimeCycle */
  uint32_t ClockMode;          /* Specifies the Clock Mode. It indicates the level that clock takes between commands.
                                  This parameter can be a value of @ref XSPI_ClockMode */
  uint32_t MemoryMode;         /* Specifies the Memory Mode State
                                  This parameter can be a value of @ref XSPI_DualFlash_Mode
                                  This has been renamed from DualFlash to MemoryMode for better compatibility with
                                  ExtMem Manager */
} XSPI_InitTypeDef;


/**
  * @brief  XSPI Handle Structure definition
  */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
typedef struct __XSPI_HandleTypeDef
#else
typedef struct
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
{
  QUADSPI_TypeDef            *Instance;        /* XSPI registers base address        */
  XSPI_InitTypeDef           Init;             /* XSPI communication parameters      */
  uint8_t                    *pBuffPtr;        /* Pointer to XSPI Tx/Rx transfer Buffer */
  __IO uint32_t              XferSize;         /* XSPI Tx/Rx Transfer size              */
  __IO uint32_t              XferCount;        /* XSPI Tx/Rx Transfer Counter           */
  MDMA_HandleTypeDef          *hmdma;            /* XSPI Rx/Tx MDMA Handle parameters   */
  __IO HAL_LockTypeDef       Lock;             /* Locking object                     */
  __IO uint32_t State;            /* XSPI communication state           */
  __IO uint32_t              ErrorCode;        /* XSPI Error code                    */
  uint32_t                   Timeout;          /* Timeout for the XSPI memory access */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
  void (* ErrorCallback)(struct __XSPI_HandleTypeDef *hxspi);
  void (* AbortCpltCallback)(struct __XSPI_HandleTypeDef *hxspi);
  void (* FifoThresholdCallback)(struct __XSPI_HandleTypeDef *hxspi);
  void (* CmdCpltCallback)(struct __XSPI_HandleTypeDef *hxspi);
  void (* RxCpltCallback)(struct __XSPI_HandleTypeDef *hxspi);
  void (* TxCpltCallback)(struct __XSPI_HandleTypeDef *hxspi);
  void (* RxHalfCpltCallback)(struct __XSPI_HandleTypeDef *hxspi);
  void (* TxHalfCpltCallback)(struct __XSPI_HandleTypeDef *hxspi);
  void (* StatusMatchCallback)(struct __XSPI_HandleTypeDef *hxspi);
  void (* TimeOutCallback)(struct __XSPI_HandleTypeDef *hxspi);

  void (* MspInitCallback)(struct __XSPI_HandleTypeDef *hxspi);
  void (* MspDeInitCallback)(struct __XSPI_HandleTypeDef *hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
} XSPI_HandleTypeDef;

/**
  * @brief  XSPI Command structure definition
  */
typedef struct
{
  uint32_t Instruction;        /* Specifies the Instruction to be sent
                                  This parameter can be a value (8-bit) between 0x00 and 0xFF */
  uint32_t Address;            /* Specifies the Address to be sent (Size from 1 to 4 bytes according AddressWidth)
                                  This parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
  uint32_t AlternateBytes;     /* Specifies the Alternate Bytes to be sent (Size from 1 to 4 bytes
                                  according AlternateBytesWidth)
                                  This parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
  uint32_t AddressWidth;        /* Specifies the Address Width
                                  This parameter can be a value of @ref XSPI_AddressWidth
                                  Renamed from AddressSize to AddressWidth for better compatibility with
                                  ExtMem Manager */
  uint32_t AlternateBytesWidth; /* Specifies the Alternate Bytes Width
                                  This parameter can be a value of @ref XSPI_AlternateBytesWidth
                                  Renamed from AlternateBytesSize to AlternateBytesWidth for better
                                  compatibility with ExtMem Manager*/
  uint32_t DummyCycles;        /* Specifies the Number of Dummy Cycles.
                                  This parameter can be a number between 0 and 31 */
  uint32_t InstructionMode;    /* Specifies the Instruction Mode
                                  This parameter can be a value of @ref XSPI_InstructionMode */
  uint32_t AddressMode;        /* Specifies the Address Mode
                                  This parameter can be a value of @ref XSPI_AddressMode */
  uint32_t AlternateByteMode;  /* Specifies the Alternate Bytes Mode
                                  This parameter can be a value of @ref XSPI_AlternateBytesMode */
  uint32_t DataMode;           /* Specifies the Data Mode (used for dummy cycles and data phases)
                                  This parameter can be a value of @ref XSPI_DataMode */
  uint32_t DataLength;         /* Specifies the length of data to transfer. (This is the number of bytes)
                                  This parameter can be any value between 0 and 0xFFFFFFFF (0 means undefined length
                                  until end of memory)
                                  Renamed from NbData to DataLength for better compatibility with ExtMem Manager */
  uint32_t DTRMode;            /* Specifies the double transfer rate mode for address, alternate byte and data phase
                                  This parameter can be a value of @ref XSPI_DTRMode */
  uint32_t DelayHoldHalfCycle;   /* Specifies if the Delay hold is enabled. When enabled it delays the data
                                  output by one half of system clock in DTR mode. */
  uint32_t SIOOMode;               /* Specifies the send instruction only once mode
                                      This parameter can be a value of @ref XSPI_SIOOMode */
  uint32_t OperationType;          /* Dummy Parameter, used for compatibility only */

  uint32_t IOSelect;               /* Specifies the FlashID which will be used */

  uint32_t InstructionWidth;       /* Dummy Parameter, used for compatibility only */

  uint32_t InstructionDTRMode;     /* Dummy Parameter, used for compatibility only */

  uint32_t AddressDTRMode;         /* Dummy Parameter, used for compatibility only */

  uint32_t AlternateBytesDTRMode;  /* Dummy Parameter, used for compatibility only */

  uint32_t DataDTRMode;            /* Dummy Parameter, used for compatibility only */

  uint32_t DQSMode;                /* Dummy Parameter, used for compatibility only */
} XSPI_RegularCmdTypeDef;

/**
  * @brief  XSPI Auto Polling mode configuration structure definition
  */
typedef struct
{
  uint32_t MatchValue;         /* Specifies the value to be compared with the masked status register to get a match.
                                  This parameter can be any value between 0 and 0xFFFFFFFF */
  uint32_t MatchMask;          /* Specifies the mask to be applied to the status bytes received.
                                  This parameter can be any value between 0 and 0xFFFFFFFF */
  uint32_t IntervalTime;       /* Specifies the number of clock cycles between two read during automatic polling phases.
                                  This parameter can be any value between 0 and 0xFFFF */
  uint32_t MatchMode;          /* Specifies the method used for determining a match.
                                  This parameter can be a value of @ref XSPI_MatchMode */
  uint32_t AutomaticStop;      /* Specifies if automatic polling is stopped after a match.
                                  This parameter can be a value of @ref XSPI_AutomaticStop */
} XSPI_AutoPollingTypeDef;

/**
  * @brief  XSPI Memory Mapped mode configuration structure definition
  */
typedef struct
{
  uint32_t TimeoutPeriodClock; /* Specifies the number of clock to wait when the FIFO is full before to
                                  release the chip select.
                                  This parameter can be any value between 0 and 0xFFFF */
  uint32_t TimeOutActivation;  /* Specifies if the timeout counter is enabled to release the chip select.
                                  This parameter can be a value of @ref XSPI_TimeOutActivation */
} XSPI_MemoryMappedTypeDef;

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
/**
  * @brief  HAL XSPI Callback ID enumeration definition
  */
typedef enum
{
  HAL_XSPI_ERROR_CB_ID          = 0x00U,  /*!< XSPI Error Callback ID            */
  HAL_XSPI_ABORT_CB_ID          = 0x01U,  /*!< XSPI Abort Callback ID            */
  HAL_XSPI_FIFO_THRESHOLD_CB_ID = 0x02U,  /*!< XSPI FIFO Threshold Callback ID   */
  HAL_XSPI_CMD_CPLT_CB_ID       = 0x03U,  /*!< XSPI Command Complete Callback ID */
  HAL_XSPI_RX_CPLT_CB_ID        = 0x04U,  /*!< XSPI Rx Complete Callback ID      */
  HAL_XSPI_TX_CPLT_CB_ID        = 0x05U,  /*!< XSPI Tx Complete Callback ID      */
  HAL_XSPI_RX_HALF_CPLT_CB_ID   = 0x06U,  /*!< XSPI Rx Half Complete Callback ID */
  HAL_XSPI_TX_HALF_CPLT_CB_ID   = 0x07U,  /*!< XSPI Tx Half Complete Callback ID */
  HAL_XSPI_STATUS_MATCH_CB_ID   = 0x08U,  /*!< XSPI Status Match Callback ID     */
  HAL_XSPI_TIMEOUT_CB_ID        = 0x09U,  /*!< XSPI Timeout Callback ID          */

  HAL_XSPI_MSP_INIT_CB_ID       = 0x0AU,  /*!< XSPI MspInit Callback ID          */
  HAL_XSPI_MSP_DEINIT_CB_ID     = 0x0B0   /*!< XSPI MspDeInit Callback ID        */
} HAL_XSPI_CallbackIDTypeDef;

/**
  * @brief  HAL XSPI Callback pointer definition
  */
typedef void (*pXSPI_CallbackTypeDef)(XSPI_HandleTypeDef *hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup XSPI_Exported_Variables XSPI Exported Variables
  * @{
  */
/* ConfigCmd needs to be populated by application code before invoking below APIs -:
1) HAL_XSPI_AutoPolling()
2) HAL_XSPI_AutoPolling_IT()
3) HAL_XSPI_MemoryMapped() */

extern XSPI_RegularCmdTypeDef ConfigCmd;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup XSPI_Exported_Constants XSPI Exported Constants
  * @{
  */

/** @defgroup XSPI_State XSPI State
  * @{
  */
#define HAL_XSPI_STATE_RESET                 (0x00000000U)  /*!< Peripheral not initialized                            */
#define HAL_XSPI_STATE_READY                 (0x00000001U)  /*!< Peripheral initialized and ready for use              */
#define HAL_XSPI_STATE_BUSY                  (0x00000002U)  /*!< Peripheral in indirect mode and busy                  */
#define HAL_XSPI_STATE_BUSY_INDIRECT_TX      (0x00000012U)  /*!< Peripheral in indirect mode with transmission ongoing */
#define HAL_XSPI_STATE_BUSY_INDIRECT_RX      (0x00000022U)  /*!< Peripheral in indirect mode with reception ongoing    */
#define HAL_XSPI_STATE_BUSY_AUTO_POLLING     (0x00000042U)  /*!< Peripheral in auto polling mode ongoing               */
#define HAL_XSPI_STATE_BUSY_MEM_MAPPED       (0x00000082U)  /*!< Peripheral in memory mapped mode ongoing              */
#define HAL_XSPI_STATE_ABORT                 (0x00000008U)  /*!< Peripheral with abort request ongoing                 */
#define HAL_XSPI_STATE_ERROR                 (0x00000004U)  /*!< Peripheral in error                                   */
/**
  * @}
  */

/** @defgroup XSPI_ErrorCode XSPI Error Code
  * @{
  */
#define HAL_XSPI_ERROR_NONE             0x00000000U /*!< No error                 */
#define HAL_XSPI_ERROR_TIMEOUT          0x00000001U /*!< Timeout error            */
#define HAL_XSPI_ERROR_TRANSFER         0x00000002U /*!< Transfer error           */
#define HAL_XSPI_ERROR_DMA              0x00000004U /*!< DMA transfer error       */
#define HAL_XSPI_ERROR_INVALID_PARAM    0x00000008U /*!< Invalid parameters error */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
#define HAL_XSPI_ERROR_INVALID_CALLBACK 0x00000010U /*!< Invalid callback error   */
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
/**
  * @}
  */

/** @defgroup XSPI_SampleShifting XSPI Sample Shifting
  * @{
  */
#define XSPI_SAMPLE_SHIFTING_NONE      0x00000000U                   /*!<No clock cycle shift to sample data*/
#define XSPI_SAMPLE_SHIFTING_HALFCYCLE ((uint32_t)QUADSPI_CR_SSHIFT) /*!<1/2 clock cycle shift to sample data*/
/**
  * @}
  */

/** @defgroup XSPI_ClockMode XSPI Clock Mode
  * @{
  */
#define XSPI_CLOCK_MODE_0              0x00000000U                    /*!<Clk stays low while nCS is released*/
#define XSPI_CLOCK_MODE_3              ((uint32_t)QUADSPI_DCR_CKMODE) /*!<Clk goes high while nCS is released*/
/**
  * @}
  */

/** @defgroup XSPI_Flash_Select XSPI Flash Select
  * @{
  */
#define HAL_XSPI_SELECT_IO_3_0                0x00000000U                    /*!<FLASH 1 selected*/
#define HAL_XSPI_SELECT_IO_7_4                ((uint32_t)QUADSPI_CR_FSEL)    /*!<FLASH 2 selected*/
/**
  * @}
  */

/** @defgroup XSPI_MEMORYMODE_Mode XSPI Memory Mode
  * @{
  */
#define HAL_XSPI_DUAL_MEM          ((uint32_t)QUADSPI_CR_DFM) /*!< Dual mode enabled                */
#define HAL_XSPI_SINGLE_MEM         0x00000000U            /*!< Dual-memory mode disabled        */
/**
  * @}
  */


/** @defgroup XSPI_AddressWidth XSPI Address Size
  * @{
  */
#define XSPI_ADDRESS_8_BITS            0x00000000U                      /*!<8-bit address*/
#define XSPI_ADDRESS_16_BITS           ((uint32_t)QUADSPI_CCR_ADSIZE_0) /*!<16-bit address*/
#define XSPI_ADDRESS_24_BITS           ((uint32_t)QUADSPI_CCR_ADSIZE_1) /*!<24-bit address*/
#define XSPI_ADDRESS_32_BITS           ((uint32_t)QUADSPI_CCR_ADSIZE)   /*!<32-bit address*/
/**
  * @}
  */

/** @defgroup XSPI_AlternateBytesWidth XSPI Alternate Bytes Size
  * @{
  */
#define XSPI_ALT_BYTES_8_BITS    0x00000000U                      /*!<8-bit alternate bytes*/
#define XSPI_ALT_BYTES_16_BITS   ((uint32_t)QUADSPI_CCR_ABSIZE_0) /*!<16-bit alternate bytes*/
#define XSPI_ALT_BYTES_24_BITS   ((uint32_t)QUADSPI_CCR_ABSIZE_1) /*!<24-bit alternate bytes*/
#define XSPI_ALT_BYTES_32_BITS   ((uint32_t)QUADSPI_CCR_ABSIZE)   /*!<32-bit alternate bytes*/
/**
  * @}
  */

/** @defgroup XSPI_InstructionMode XSPI Instruction Mode
  * @{
  */
#define XSPI_INSTRUCTION_NONE          0x00000000U                     /*!<No instruction*/
#define XSPI_INSTRUCTION_1_LINE        ((uint32_t)QUADSPI_CCR_IMODE_0) /*!<Instruction on a single line*/
#define XSPI_INSTRUCTION_2_LINES       ((uint32_t)QUADSPI_CCR_IMODE_1) /*!<Instruction on two lines*/
#define XSPI_INSTRUCTION_4_LINES       ((uint32_t)QUADSPI_CCR_IMODE)   /*!<Instruction on four lines*/
/**
  * @}
  */

/** @defgroup XSPI_AddressMode XSPI Address Mode
  * @{
  */
#define XSPI_ADDRESS_NONE              0x00000000U                      /*!<No address*/
#define XSPI_ADDRESS_1_LINE            ((uint32_t)QUADSPI_CCR_ADMODE_0) /*!<Address on a single line*/
#define XSPI_ADDRESS_2_LINES           ((uint32_t)QUADSPI_CCR_ADMODE_1) /*!<Address on two lines*/
#define XSPI_ADDRESS_4_LINES           ((uint32_t)QUADSPI_CCR_ADMODE)   /*!<Address on four lines*/
/**
  * @}
  */

/** @defgroup XSPI_AlternateBytesMode XSPI Alternate Bytes Mode
  * @{
  */
#define XSPI_ALT_BYTES_NONE      0x00000000U                      /*!<No alternate bytes*/
#define XSPI_ALT_BYTES_1_LINE    ((uint32_t)QUADSPI_CCR_ABMODE_0) /*!<Alternate bytes on a single line*/
#define XSPI_ALT_BYTES_2_LINES   ((uint32_t)QUADSPI_CCR_ABMODE_1) /*!<Alternate bytes on two lines*/
#define XSPI_ALT_BYTES_4_LINES   ((uint32_t)QUADSPI_CCR_ABMODE)   /*!<Alternate bytes on four lines*/
/**
  * @}
  */

/** @defgroup XSPI_DataMode XSPI Data Mode
  * @{
  */
#define XSPI_DATA_NONE                 0x00000000U                     /*!<No data*/
#define XSPI_DATA_1_LINE               ((uint32_t)QUADSPI_CCR_DMODE_0) /*!<Data on a single line*/
#define XSPI_DATA_2_LINES              ((uint32_t)QUADSPI_CCR_DMODE_1) /*!<Data on two lines*/
#define XSPI_DATA_4_LINES              ((uint32_t)QUADSPI_CCR_DMODE)   /*!<Data on four lines*/
/**
  * @}
  */

/** @defgroup XSPI_DTRMode XSPI DTR Mode
  * @{
  */
#define XSPI_DTR_MODE_DISABLE          0x00000000U                  /*!<Double transfer rate mode disabled*/
#define XSPI_DTR_MODE_ENABLE           ((uint32_t)QUADSPI_CCR_DDRM)    /*!<Double transfer rate mode enabled*/
/**
  * @}
  */

/** @defgroup XSPI_DelayHoldHalfCycle XSPI Data Output Delay
  * @{
  */
#define XSPI_DHHC_ANALOG_DELAY      0x00000000U                  /*!<Delay the data output using analog delay in DTR mode*/
#define XSPI_DHHC_HALF_CLK_DELAY    ((uint32_t)QUADSPI_CCR_DHHC) /*!<Delay the data output by one half of system clock in DTR mode*/
/**
  * @}
  */

/** @defgroup XSPI_SIOOMode XSPI Send Instruction Mode
  * @{
  */
#define XSPI_SIOO_INST_EVERY_CMD       0x00000000U                  /*!<Send instruction on every transaction*/
#define XSPI_SIOO_INST_ONLY_FIRST_CMD  ((uint32_t)QUADSPI_CCR_SIOO) /*!<Send instruction only for the first command*/
/**
  * @}
  */

/** @defgroup XSPI_MatchMode XSPI Match Mode
  * @{
  */
#define XSPI_MATCH_MODE_AND            0x00000000U                /*!<AND match mode between unmasked bits*/
#define XSPI_MATCH_MODE_OR             ((uint32_t)QUADSPI_CR_PMM) /*!<OR match mode between unmasked bits*/
/**
  * @}
  */

/** @defgroup XSPI_AutomaticStop XSPI Automatic Stop
  * @{
  */
#define XSPI_AUTOMATIC_STOP_DISABLE    0x00000000U                 /*!<AutoPolling stops only with abort or XSPI disabling*/
#define XSPI_AUTOMATIC_STOP_ENABLE     ((uint32_t)QUADSPI_CR_APMS) /*!<AutoPolling stops as soon as there is a match*/
/**
  * @}
  */

/** @defgroup XSPI_TimeOutActivation XSPI Timeout Activation
  * @{
  */
#define XSPI_TIMEOUT_COUNTER_DISABLE   0x00000000U                 /*!<Timeout counter disabled, nCS remains active*/
#define XSPI_TIMEOUT_COUNTER_ENABLE    ((uint32_t)QUADSPI_CR_TCEN) /*!<Timeout counter enabled, nCS released when timeout expires*/
/**
  * @}
  */

/** @defgroup XSPI_Flags XSPI Flags
  * @{
  */
#define XSPI_FLAG_BUSY                 QUADSPI_SR_BUSY /*!<Busy flag: operation is ongoing*/
#define XSPI_FLAG_TO                   QUADSPI_SR_TOF  /*!<Timeout flag: timeout occurs in memory-mapped mode*/
#define XSPI_FLAG_SM                   QUADSPI_SR_SMF  /*!<Status match flag: received data matches in autopolling mode*/
#define XSPI_FLAG_FT                   QUADSPI_SR_FTF  /*!<Fifo threshold flag: Fifo threshold reached or data left after read from memory is complete*/
#define XSPI_FLAG_TC                   QUADSPI_SR_TCF  /*!<Transfer complete flag: programmed number of data have been transferred or the transfer has been aborted*/
#define XSPI_FLAG_TE                   QUADSPI_SR_TEF  /*!<Transfer error flag: invalid address is being accessed*/
/**
  * @}
  */

/** @defgroup XSPI_Interrupts XSPI Interrupts
  * @{
  */
#define XSPI_IT_TO                     QUADSPI_CR_TOIE /*!<Interrupt on the timeout flag*/
#define XSPI_IT_SM                     QUADSPI_CR_SMIE /*!<Interrupt on the status match flag*/
#define XSPI_IT_FT                     QUADSPI_CR_FTIE /*!<Interrupt on the fifo threshold flag*/
#define XSPI_IT_TC                     QUADSPI_CR_TCIE /*!<Interrupt on the transfer complete flag*/
#define XSPI_IT_TE                     QUADSPI_CR_TEIE /*!<Interrupt on the transfer error flag*/
/**
  * @}
  */

/** @defgroup XSPI_Timeout_definition XSPI Timeout definition
  * @brief XSPI Timeout definition
  * @{
  */
#define HAL_XSPI_TIMEOUT_DEFAULT_VALUE 5000U /* 5 s */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup XSPI_Exported_Macros XSPI Exported Macros
  * @{
  */
/** @brief Reset XSPI handle state.
  * @param  __HANDLE__ XSPI handle.
  * @retval None
  */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
#define HAL_XSPI_RESET_HANDLE_STATE(__HANDLE__)           do {                                              \
                                                                  (__HANDLE__)->State = HAL_XSPI_STATE_RESET; \
                                                                  (__HANDLE__)->MspInitCallback = NULL;       \
                                                                  (__HANDLE__)->MspDeInitCallback = NULL;     \
                                                               } while(0)
#else
#define HAL_XSPI_RESET_HANDLE_STATE(__HANDLE__)           ((__HANDLE__)->State = HAL_XSPI_STATE_RESET)
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */

/** @brief  Enable the XSPI peripheral.
  * @param  __HANDLE__ specifies the XSPI Handle.
  * @retval None
  */
#define HAL_XSPI_ENABLE(__HANDLE__)                       SET_BIT((__HANDLE__)->Instance->CR, QUADSPI_CR_EN)

/** @brief  Disable the XSPI peripheral.
  * @param  __HANDLE__ specifies the XSPI Handle.
  * @retval None
  */
#define HAL_XSPI_DISABLE(__HANDLE__)                      CLEAR_BIT((__HANDLE__)->Instance->CR, QUADSPI_CR_EN)

/** @brief  Enable the specified XSPI interrupt.
  * @param  __HANDLE__ specifies the XSPI Handle.
  * @param  __INTERRUPT__ specifies the XSPI interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg XSPI_IT_TO: XSPI Timeout interrupt
  *            @arg XSPI_IT_SM: XSPI Status match interrupt
  *            @arg XSPI_IT_FT: XSPI FIFO threshold interrupt
  *            @arg XSPI_IT_TC: XSPI Transfer complete interrupt
  *            @arg XSPI_IT_TE: XSPI Transfer error interrupt
  * @retval None
  */
#define HAL_XSPI_ENABLE_IT(__HANDLE__, __INTERRUPT__)     SET_BIT((__HANDLE__)->Instance->CR, (__INTERRUPT__))


/** @brief  Disable the specified XSPI interrupt.
  * @param  __HANDLE__ specifies the XSPI Handle.
  * @param  __INTERRUPT__ specifies the XSPI interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg XSPI_IT_TO: XSPI Timeout interrupt
  *            @arg XSPI_IT_SM: XSPI Status match interrupt
  *            @arg XSPI_IT_FT: XSPI FIFO threshold interrupt
  *            @arg XSPI_IT_TC: XSPI Transfer complete interrupt
  *            @arg XSPI_IT_TE: XSPI Transfer error interrupt
  * @retval None
  */
#define HAL_XSPI_DISABLE_IT(__HANDLE__, __INTERRUPT__)    CLEAR_BIT((__HANDLE__)->Instance->CR, (__INTERRUPT__))

/** @brief  Check whether the specified XSPI interrupt source is enabled or not.
  * @param  __HANDLE__ specifies the XSPI Handle.
  * @param  __INTERRUPT__ specifies the XSPI interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg XSPI_IT_TO: XSPI Timeout interrupt
  *            @arg XSPI_IT_SM: XSPI Status match interrupt
  *            @arg XSPI_IT_FT: XSPI FIFO threshold interrupt
  *            @arg XSPI_IT_TC: XSPI Transfer complete interrupt
  *            @arg XSPI_IT_TE: XSPI Transfer error interrupt
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define HAL_XSPI_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) (READ_BIT((__HANDLE__)->Instance->CR, (__INTERRUPT__))\
                                                           == (__INTERRUPT__))

/**
  * @brief  Check whether the selected XSPI flag is set or not.
  * @param  __HANDLE__ specifies the XSPI Handle.
  * @param  __FLAG__ specifies the XSPI flag to check.
  *          This parameter can be one of the following values:
  *            @arg XSPI_FLAG_BUSY: XSPI Busy flag
  *            @arg XSPI_FLAG_TO:   XSPI Timeout flag
  *            @arg XSPI_FLAG_SM:   XSPI Status match flag
  *            @arg XSPI_FLAG_FT:   XSPI FIFO threshold flag
  *            @arg XSPI_FLAG_TC:   XSPI Transfer complete flag
  *            @arg XSPI_FLAG_TE:   XSPI Transfer error flag
  * @retval None
  */
#define HAL_XSPI_GET_FLAG(__HANDLE__, __FLAG__)           ((READ_BIT((__HANDLE__)->Instance->SR, (__FLAG__)) \
                                                            != 0U) ? SET : RESET)

/** @brief  Clears the specified XSPI's flag status.
  * @param  __HANDLE__ specifies the XSPI Handle.
  * @param  __FLAG__ specifies the XSPI clear register flag that needs to be set
  *          This parameter can be one of the following values:
  *            @arg XSPI_FLAG_TO: XSPI Timeout flag
  *            @arg XSPI_FLAG_SM: XSPI Status match flag
  *            @arg XSPI_FLAG_TC: XSPI Transfer complete flag
  *            @arg XSPI_FLAG_TE: XSPI Transfer error flag
  * @retval None
  */
#define HAL_XSPI_CLEAR_FLAG(__HANDLE__, __FLAG__)         WRITE_REG((__HANDLE__)->Instance->FCR, (__FLAG__))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup XSPI_Exported_Functions
  * @{
  */

/** @addtogroup XSPI_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions  ********************************/
HAL_StatusTypeDef     HAL_XSPI_Init(XSPI_HandleTypeDef *hxspi);
HAL_StatusTypeDef     HAL_XSPI_DeInit(XSPI_HandleTypeDef *hxspi);
void                  HAL_XSPI_MspInit(XSPI_HandleTypeDef *hxspi);
void                  HAL_XSPI_MspDeInit(XSPI_HandleTypeDef *hxspi);
/**
  * @}
  */

/** @addtogroup XSPI_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/
/* XSPI IRQ handler method */
void                  HAL_XSPI_IRQHandler(XSPI_HandleTypeDef *hxspi);

/* XSPI indirect mode */
HAL_StatusTypeDef     HAL_XSPI_Command(XSPI_HandleTypeDef *hxspi, XSPI_RegularCmdTypeDef *cmd, uint32_t Timeout);
HAL_StatusTypeDef     HAL_XSPI_Transmit(XSPI_HandleTypeDef *hxspi, uint8_t *pData, uint32_t Timeout);
HAL_StatusTypeDef     HAL_XSPI_Receive(XSPI_HandleTypeDef *hxspi, uint8_t *pData, uint32_t Timeout);
HAL_StatusTypeDef     HAL_XSPI_Command_IT(XSPI_HandleTypeDef *hxspi, XSPI_RegularCmdTypeDef *cmd);
HAL_StatusTypeDef     HAL_XSPI_Transmit_IT(XSPI_HandleTypeDef *hxspi, uint8_t *pData);
HAL_StatusTypeDef     HAL_XSPI_Receive_IT(XSPI_HandleTypeDef *hxspi, uint8_t *pData);
HAL_StatusTypeDef     HAL_XSPI_Transmit_DMA(XSPI_HandleTypeDef *hxspi, uint8_t *pData);
HAL_StatusTypeDef     HAL_XSPI_Receive_DMA(XSPI_HandleTypeDef *hxspi, uint8_t *pData);

/* XSPI status flag polling mode */
HAL_StatusTypeDef     HAL_XSPI_AutoPolling(XSPI_HandleTypeDef *hxspi, XSPI_AutoPollingTypeDef *cfg, uint32_t Timeout);
HAL_StatusTypeDef     HAL_XSPI_AutoPolling_IT(XSPI_HandleTypeDef *hxspi, XSPI_AutoPollingTypeDef *cfg);

/* XSPI memory-mapped mode */
HAL_StatusTypeDef     HAL_XSPI_MemoryMapped(XSPI_HandleTypeDef *hxspi, XSPI_MemoryMappedTypeDef *cfg);

/* Callback functions in non-blocking modes ***********************************/
void                  HAL_XSPI_ErrorCallback(XSPI_HandleTypeDef *hxspi);
void                  HAL_XSPI_AbortCpltCallback(XSPI_HandleTypeDef *hxspi);
void                  HAL_XSPI_FifoThresholdCallback(XSPI_HandleTypeDef *hxspi);

/* XSPI indirect mode */
void                  HAL_XSPI_CmdCpltCallback(XSPI_HandleTypeDef *hxspi);
void                  HAL_XSPI_RxCpltCallback(XSPI_HandleTypeDef *hxspi);
void                  HAL_XSPI_TxCpltCallback(XSPI_HandleTypeDef *hxspi);
void                  HAL_XSPI_RxHalfCpltCallback(XSPI_HandleTypeDef *hxspi);
void                  HAL_XSPI_TxHalfCpltCallback(XSPI_HandleTypeDef *hxspi);

/* XSPI status flag polling mode */
void                  HAL_XSPI_StatusMatchCallback(XSPI_HandleTypeDef *hxspi);

/* XSPI memory-mapped mode */
void                  HAL_XSPI_TimeOutCallback(XSPI_HandleTypeDef *hxspi);

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
/* XSPI callback registering/unregistering */
HAL_StatusTypeDef     HAL_XSPI_RegisterCallback(XSPI_HandleTypeDef *hxspi, HAL_XSPI_CallbackIDTypeDef CallbackId,
                                                pXSPI_CallbackTypeDef pCallback);
HAL_StatusTypeDef     HAL_XSPI_UnRegisterCallback(XSPI_HandleTypeDef *hxspi, HAL_XSPI_CallbackIDTypeDef CallbackId);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
/**
  * @}
  */

/** @addtogroup XSPI_Exported_Functions_Group3
  * @{
  */
/* Peripheral Control and State functions  ************************************/
uint32_t              HAL_XSPI_GetState(const XSPI_HandleTypeDef *hxspi);
uint32_t              HAL_XSPI_GetError(const XSPI_HandleTypeDef *hxspi);
HAL_StatusTypeDef     HAL_XSPI_Abort(XSPI_HandleTypeDef *hxspi);
HAL_StatusTypeDef     HAL_XSPI_Abort_IT(XSPI_HandleTypeDef *hxspi);
void                  HAL_XSPI_SetTimeout(XSPI_HandleTypeDef *hxspi, uint32_t Timeout);
HAL_StatusTypeDef     HAL_XSPI_SetFifoThreshold(XSPI_HandleTypeDef *hxspi, uint32_t Threshold);
uint32_t              HAL_XSPI_GetFifoThreshold(const XSPI_HandleTypeDef *hxspi);
/**
  * @}
  */

/**
  * @}
  */
/* End of exported functions -------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/** @defgroup XSPI_Private_Macros XSPI Private Macros
  * @{
  */
#define IS_XSPI_CLK_PRESCALER(PRESCALER) ((PRESCALER) <= 0xFFU)

/* Renamed from IS_XSPI_FIFO_THRESHOLD() to IS_XSPI_FIFO_THRESHOLD_BYTE for better compatibility with ExtMem Manager */
#define IS_XSPI_FIFO_THRESHOLD_BYTE(THR)        (((THR) > 0U) && ((THR) <= 32U))

#define IS_XSPI_SAMPLE_SHIFTING(SSHIFT)             (((SSHIFT) == XSPI_SAMPLE_SHIFTING_NONE) || \
                                                     ((SSHIFT) == XSPI_SAMPLE_SHIFTING_HALFCYCLE))

#define IS_XSPI_MEMORY_SIZE(SIZE)          (((SIZE) <= 31U))

#define IS_XSPI_CS_HIGH_TIME_CYCLE(TIME)   (((TIME) >= 1U) && ((TIME) <= 8U))

#define IS_XSPI_CLOCK_MODE(CLKMODE)        (((CLKMODE) == XSPI_CLOCK_MODE_0) || \
                                            ((CLKMODE) == XSPI_CLOCK_MODE_3))

#define IS_XSPI_IO_SELECT(MEMSEL)           (((MEMSEL) == HAL_XSPI_SELECT_IO_3_0) || \
                                             ((MEMSEL) == HAL_XSPI_SELECT_IO_7_4))
#define IS_XSPI_MEMORY_MODE(MODE)      (((MODE) == HAL_XSPI_DUAL_MEM) || \
                                        ((MODE) == HAL_XSPI_SINGLE_MEM))
#define IS_XSPI_INSTRUCTION(INSTRUCTION)   ((INSTRUCTION) <= 0xFFU)

/* Renamed IS_XSPI_ADDRESS_SIZE() to IS_XSPI_ADDRESS_WIDTH() for better compatibility with ExtMem Manager */
#define IS_XSPI_ADDRESS_WIDTH(ADDR_WIDTH)    (((ADDR_WIDTH) == XSPI_ADDRESS_8_BITS)  || \
                                              ((ADDR_WIDTH) == XSPI_ADDRESS_16_BITS) || \
                                              ((ADDR_WIDTH) == XSPI_ADDRESS_24_BITS) || \
                                              ((ADDR_WIDTH) == XSPI_ADDRESS_32_BITS))

/* Renamed IS_XSPI_ALT_BYTES_SIZE() to IS_XSPI_ALT_BYTES_WIDTH() for better compatibility with
ExtMem Manager */
#define IS_XSPI_ALT_BYTES_WIDTH(SIZE) (((SIZE) == XSPI_ALT_BYTES_8_BITS)  || \
                                       ((SIZE) == XSPI_ALT_BYTES_16_BITS) || \
                                       ((SIZE) == XSPI_ALT_BYTES_24_BITS) || \
                                       ((SIZE) == XSPI_ALT_BYTES_32_BITS))

#define IS_XSPI_DUMMY_CYCLES(DCY)          ((DCY) <= 31U)

#define IS_XSPI_INSTRUCTION_MODE(MODE)     (((MODE) == XSPI_INSTRUCTION_NONE)    || \
                                            ((MODE) == XSPI_INSTRUCTION_1_LINE)  || \
                                            ((MODE) == XSPI_INSTRUCTION_2_LINES) || \
                                            ((MODE) == XSPI_INSTRUCTION_4_LINES))

#define IS_XSPI_ADDRESS_MODE(MODE)         (((MODE) == XSPI_ADDRESS_NONE)    || \
                                            ((MODE) == XSPI_ADDRESS_1_LINE)  || \
                                            ((MODE) == XSPI_ADDRESS_2_LINES) || \
                                            ((MODE) == XSPI_ADDRESS_4_LINES))

#define IS_XSPI_ALT_BYTES_MODE(MODE) (((MODE) == XSPI_ALT_BYTES_NONE)    || \
                                      ((MODE) == XSPI_ALT_BYTES_1_LINE)  || \
                                      ((MODE) == XSPI_ALT_BYTES_2_LINES) || \
                                      ((MODE) == XSPI_ALT_BYTES_4_LINES))

#define IS_XSPI_DATA_MODE(MODE)            (((MODE) == XSPI_DATA_NONE)    || \
                                            ((MODE) == XSPI_DATA_1_LINE)  || \
                                            ((MODE) == XSPI_DATA_2_LINES) || \
                                            ((MODE) == XSPI_DATA_4_LINES))

#define IS_XSPI_DTR_MODE(DTR_MODE)         (((DTR_MODE) == XSPI_DTR_MODE_DISABLE) || \
                                            ((DTR_MODE) == XSPI_DTR_MODE_ENABLE))

#define IS_XSPI_DHHC(DHHC)           (((DHHC) == XSPI_DHHC_ANALOG_DELAY) || \
                                      ((DHHC) == XSPI_DHHC_HALF_CLK_DELAY))

#define IS_XSPI_SIOO_MODE(SIOO_MODE)       (((SIOO_MODE) == XSPI_SIOO_INST_EVERY_CMD) || \
                                            ((SIOO_MODE) == XSPI_SIOO_INST_ONLY_FIRST_CMD))

#define IS_XSPI_INTERVAL(INTERVAL)         ((INTERVAL) <= QUADSPI_PIR_INTERVAL)

#define IS_XSPI_STATUS_BYTES_SIZE(SIZE)    (((SIZE) >= 1U) && ((SIZE) <= 4U))

#define IS_XSPI_MATCH_MODE(MODE)           (((MODE) == XSPI_MATCH_MODE_AND) || \
                                            ((MODE) == XSPI_MATCH_MODE_OR))

#define IS_XSPI_AUTOMATIC_STOP(APMS)       (((APMS) == XSPI_AUTOMATIC_STOP_DISABLE) || \
                                            ((APMS) == XSPI_AUTOMATIC_STOP_ENABLE))

#define IS_XSPI_TIMEOUT_ACTIVATION(TCEN)   (((TCEN) == XSPI_TIMEOUT_COUNTER_DISABLE) || \
                                            ((TCEN) == XSPI_TIMEOUT_COUNTER_ENABLE))

#define IS_XSPI_TIMEOUT_PERIOD(PERIOD)     ((PERIOD) <= 0xFFFFU)

/**
  * @}
  */
/* End of private macros -----------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(XSPI) */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP13xx_HAL_XSPI_H */
