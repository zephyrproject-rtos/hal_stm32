/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_xspi.c
  * @author  MCD Application Team
  * @brief   XSPI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the XSPI interface (XSPI).
  *           + Initialization and de-initialization functions
  *           + Indirect functional mode management
  *           + Memory-mapped functional mode management
  *           + Auto-polling functional mode management
  *           + Interrupts and flags management
  *           + MDMA channel configuration for indirect functional mode
  *           + Errors management and abort functionality
  *
  *
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
  @verbatim
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
  [..]
    *** Initialization ***
    ======================
    [..]
      (#) As prerequisite, fill in the HAL_XSPI_MspInit() :
        (++) Enable XSPI clock interface with __HAL_RCC_QSPI_CLK_ENABLE().
        (++) Reset XSPI Peripheral with __HAL_RCC_QSPI_FORCE_RESET() and
             __HAL_RCC_QSPI_RELEASE_RESET().
        (++) Enable the clocks for the XSPI GPIOS with __HAL_RCC_GPIOx_CLK_ENABLE().
        (++) Configure these XSPI pins in alternate mode using HAL_GPIO_Init().
        (++) If interrupt mode is used, enable and configure XSPI global
            interrupt with HAL_NVIC_SetPriority() and HAL_NVIC_EnableIRQ().
        (++) If DMA mode is used, enable the clocks for the XSPI MDMA
            with __HAL_RCC_MDMA_CLK_ENABLE(), configure MDMA with HAL_MDMA_Init(),
            link it with XSPI handle using __HAL_LINKDMA(), enable and configure
            MDMA global interrupt with HAL_NVIC_SetPriority() and HAL_NVIC_EnableIRQ().
      (#) Configure the memory size, the clock prescaler, the fifo threshold, the
          clock mode, the sample shifting and the CS high time using the HAL_XSPI_Init() function.

    *** Indirect functional mode ***
    ================================
    [..]
      (#) Configure the command sequence using the HAL_XSPI_Command() or HAL_XSPI_Command_IT()
          functions :
         (++) Instruction phase : the mode used and if present the instruction opcode.
         (++) Address phase : the mode used and if present the size and the address value.
         (++) Alternate-bytes phase : the mode used and if present the size and the alternate
             bytes values.
         (++) Dummy-cycles phase : the number of dummy cycles (mode used is same as data phase).
         (++) Data phase : the mode used and if present the number of bytes.
         (++) Double Transfer Rate (DTR) mode : the activation (or not) of this mode and the delay
             if activated.
         (++) Sending Instruction Only Once (SIOO) mode : the activation (or not) of this mode.
      (#) If no data is required for the command, it is sent directly to the memory :
         (++) In polling mode, the output of the function is done when the transfer is complete.
         (++) In interrupt mode, HAL_XSPI_CmdCpltCallback() will be called when the transfer is complete.
      (#) For the indirect write mode, use HAL_XSPI_Transmit(), HAL_XSPI_Transmit_DMA() or
          HAL_XSPI_Transmit_IT() after the command configuration :
         (++) In polling mode, the output of the function is done when the transfer is complete.
         (++) In interrupt mode, HAL_XSPI_FifoThresholdCallback() will be called when the fifo threshold
             is reached and HAL_XSPI_TxCpltCallback() will be called when the transfer is complete.
         (++) In DMA mode, HAL_XSPI_TxHalfCpltCallback() will be called at the half transfer and
             HAL_XSPI_TxCpltCallback() will be called when the transfer is complete.
      (#) For the indirect read mode, use HAL_XSPI_Receive(), HAL_XSPI_Receive_DMA() or
          HAL_XSPI_Receive_IT() after the command configuration :
         (++) In polling mode, the output of the function is done when the transfer is complete.
         (++) In interrupt mode, HAL_XSPI_FifoThresholdCallback() will be called when the fifo threshold
             is reached and HAL_XSPI_RxCpltCallback() will be called when the transfer is complete.
         (++) In DMA mode, HAL_XSPI_RxHalfCpltCallback() will be called at the half transfer and
             HAL_XSPI_RxCpltCallback() will be called when the transfer is complete.

    *** Auto-polling functional mode ***
    ====================================
    [..]
      (#) XSPI_RegularCmdTypeDef ConfigCmd defined in hal_xspi.h needs to be populated by application for configuring
          the command sequence using the HAL_XSPI_AutoPolling() or HAL_XSPI_AutoPolling_IT() functions :
         (++) Instruction phase : the mode used and if present the instruction opcode.
         (++) Address phase : the mode used and if present the size and the address value.
         (++) Alternate-bytes phase : the mode used and if present the size and the alternate
             bytes values.
         (++) Dummy-cycles phase : the number of dummy cycles (mode used is same as data phase).
         (++) Data phase : the mode used.
         (++) Double Data Rate (DTR) mode : the activation (or not) of this mode and the delay
             if activated.
         (++) Sending Instruction Only Once (SIOO) mode : the activation (or not) of this mode.
         (++) The size of the status bytes, the match value, the mask used, the match mode (OR/AND),
             the polling interval and the automatic stop activation.
      (#) After the configuration :
         (++) In polling mode, the output of the function is done when the status match is reached. The
             automatic stop is activated to avoid an infinite loop.
         (++) In interrupt mode, HAL_XSPI_StatusMatchCallback() will be called each time the status match is reached.

    *** MDMA functional mode ***
    ====================================
    [..]
      (#) Configure the SourceInc and DestinationInc of MDMA parameters in the HAL_XSPI_MspInit() function :
         (++) MDMA settings for write operation :
          (+) The DestinationInc should be MDMA_DEST_INC_DISABLE
          (+) The SourceInc must be a value of MDMA_Source_increment_mode (Except the MDMA_SRC_INC_DOUBLEWORD).
          (+) The SourceDataSize must be a value of MDMA Source data size (Except the MDMA_SRC_DATASIZE_DOUBLEWORD)
              aligned with MDMA_Source_increment_mode .
          (+) The DestDataSize must be a value of MDMA Destination data size (Except the MDMA_DEST_DATASIZE_DOUBLEWORD)
         (++) MDMA settings for read operation :
          (+) The SourceInc should be MDMA_SRC_INC_DISABLE
          (+) The DestinationInc must be a value of MDMA_Destination_increment_mode
              (Except the MDMA_DEST_INC_DOUBLEWORD).
          (+) The SourceDataSize must be a value of MDMA Source data size (Except the MDMA_SRC_DATASIZE_DOUBLEWORD) .
          (+) The DestDataSize must be a value of MDMA Destination data size
              (Except the MDMA_DEST_DATASIZE_DOUBLEWORD)
              aligned with MDMA_Destination_increment_mode.
         (++)The buffer Transfer Length(BufferTransferLength) = number of bytes in the FIFO(FifoThreshold) of the Xspi.
      (#)In case of wrong MDMA setting
        (++) For write operation :
         (+) If the DestinationInc is different to MDMA_DEST_INC_DISABLE,
             it will be disabled by the HAL_XSPI_Transmit_DMA().
        (++) For read operation :
         (+) If the SourceInc is not set to MDMA_SRC_INC_DISABLE , it will be disabled by the HAL_XSPI_Receive_DMA().

    *** Memory-mapped functional mode ***
    =====================================
    [..]
      (#) XSPI_RegularCmdTypeDef ConfigCmd defined in hal_xspi.h needs to be populated by application for configuring
          the command sequence using the HAL_XSPI_MemoryMapped() functions :
         (++) Instruction phase : the mode used and if present the instruction opcode.
         (++) Address phase : the mode used and the size.
         (++) Alternate-bytes phase : the mode used and if present the size and the alternate
             bytes values.
         (++) Dummy-cycles phase : the number of dummy cycles (mode used is same as data phase).
         (++) Data phase : the mode used.
         (++) Double Data Rate (DTR) mode : the activation (or not) of this mode and the delay
             if activated.
         (++) Sending Instruction Only Once (SIOO) mode : the activation (or not) of this mode.
         (++) The timeout activation and the timeout period.
      (#) After the configuration, the XSPI will be used as soon as an access on the AHB is done on
          the address range. HAL_XSPI_TimeOutCallback() will be called when the timeout expires.

    *** Errors management and abort functionality ***
    =================================================
    [..]
      (#) HAL_XSPI_GetError() function gives the error raised during the last operation.
      (#) HAL_XSPI_Abort() and HAL_XSPI_Abort_IT() functions aborts any on-going operation and
          flushes the fifo :
         (++) In polling mode, the output of the function is done when the transfer
              complete bit is set and the busy bit cleared.
         (++) In interrupt mode, HAL_XSPI_AbortCpltCallback() will be called when
              the transfer complete bit is set.

    *** Control functions ***
    =========================
    [..]
      (#) HAL_XSPI_GetState() function gives the current state of the HAL XSPI driver.
      (#) HAL_XSPI_SetTimeout() function configures the timeout value used in the driver.
      (#) HAL_XSPI_SetFifoThreshold() function configures the threshold on the Fifo of the XSPI IP.
      (#) HAL_XSPI_GetFifoThreshold() function gives the current of the Fifo's threshold

    *** Callback registration ***
    =============================================
    [..]
      The compilation define  USE_HAL_XSPI_REGISTER_CALLBACKS when set to 1
      allows the user to configure dynamically the driver callbacks.

      Use Functions HAL_XSPI_RegisterCallback() to register a user callback,
      it allows to register following callbacks:
        (+) ErrorCallback : callback when error occurs.
        (+) AbortCpltCallback : callback when abort is completed.
        (+) FifoThresholdCallback : callback when the fifo threshold is reached.
        (+) CmdCpltCallback : callback when a command without data is completed.
        (+) RxCpltCallback : callback when a reception transfer is completed.
        (+) TxCpltCallback : callback when a transmission transfer is completed.
        (+) RxHalfCpltCallback : callback when half of the reception transfer is completed.
        (+) TxHalfCpltCallback : callback when half of the transmission transfer is completed.
        (+) StatusMatchCallback : callback when a status match occurs.
        (+) TimeOutCallback : callback when the timeout perioed expires.
        (+) MspInitCallback    : XSPI MspInit.
        (+) MspDeInitCallback  : XSPI MspDeInit.
      This function takes as parameters the HAL peripheral handle, the Callback ID
      and a pointer to the user callback function.

      Use function HAL_XSPI_UnRegisterCallback() to reset a callback to the default
      weak (surcharged) function. It allows to reset following callbacks:
        (+) ErrorCallback : callback when error occurs.
        (+) AbortCpltCallback : callback when abort is completed.
        (+) FifoThresholdCallback : callback when the fifo threshold is reached.
        (+) CmdCpltCallback : callback when a command without data is completed.
        (+) RxCpltCallback : callback when a reception transfer is completed.
        (+) TxCpltCallback : callback when a transmission transfer is completed.
        (+) RxHalfCpltCallback : callback when half of the reception transfer is completed.
        (+) TxHalfCpltCallback : callback when half of the transmission transfer is completed.
        (+) StatusMatchCallback : callback when a status match occurs.
        (+) TimeOutCallback : callback when the timeout perioed expires.
        (+) MspInitCallback    : XSPI MspInit.
        (+) MspDeInitCallback  : XSPI MspDeInit.
      This function) takes as parameters the HAL peripheral handle and the Callback ID.

      By default, after the HAL_XSPI_Init and if the state is HAL_XSPI_STATE_RESET
      all callbacks are reset to the corresponding legacy weak (surcharged) functions.
      Exception done for MspInit and MspDeInit callbacks that are respectively
      reset to the legacy weak (surcharged) functions in the HAL_XSPI_Init
      and  HAL_XSPI_DeInit only when these callbacks are null (not registered beforehand).
      If not, MspInit or MspDeInit are not null, the HAL_XSPI_Init and HAL_XSPI_DeInit
      keep and use the user MspInit/MspDeInit callbacks (registered beforehand)

      Callbacks can be registered/unregistered in READY state only.
      Exception done for MspInit/MspDeInit callbacks that can be registered/unregistered
      in READY or RESET state, thus registered (user) MspInit/DeInit callbacks can be used
      during the Init/DeInit.
      In that case first register the MspInit/MspDeInit user callbacks
      using HAL_XSPI_RegisterCallback before calling HAL_XSPI_DeInit
      or HAL_XSPI_Init function.

      When The compilation define USE_HAL_XSPI_REGISTER_CALLBACKS is set to 0 or
      not defined, the callback registering feature is not available
      and weak (surcharged) callbacks are used.

    *** Workarounds linked to Silicon Limitation ***
    ====================================================
    [..]
      (#) Workarounds Implemented inside HAL Driver
         (++) Extra data written in the FIFO at the end of a read transfer

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal.h"

#if defined(QUADSPI) || defined(QUADSPI1) || defined(QUADSPI2)

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @defgroup XSPI XSPI
  * @brief XSPI HAL module driver
  * @{
  */
#ifdef HAL_XSPI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/** @defgroup XSPI_Private_Constants XSPI Private Constants
  * @{
  */
#define XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE 0x00000000U                     /*!<Indirect write mode*/
#define XSPI_FUNCTIONAL_MODE_INDIRECT_READ  ((uint32_t)QUADSPI_CCR_FMODE_0) /*!<Indirect read mode*/
#define XSPI_FUNCTIONAL_MODE_AUTO_POLLING   ((uint32_t)QUADSPI_CCR_FMODE_1) /*!<Automatic polling mode*/
#define XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED  ((uint32_t)QUADSPI_CCR_FMODE)   /*!<Memory-mapped mode*/
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup XSPI_Private_Macros XSPI Private Macros
  * @{
  */
#define IS_XSPI_FUNCTIONAL_MODE(MODE) (((MODE) == XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE) || \
                                       ((MODE) == XSPI_FUNCTIONAL_MODE_INDIRECT_READ)  || \
                                       ((MODE) == XSPI_FUNCTIONAL_MODE_AUTO_POLLING)   || \
                                       ((MODE) == XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED))
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
XSPI_RegularCmdTypeDef ConfigCmd = {0};

/* Private function prototypes -----------------------------------------------*/
static void XSPI_DMARxCplt(MDMA_HandleTypeDef *hmdma);
static void XSPI_DMATxCplt(MDMA_HandleTypeDef *hmdma);
static void XSPI_DMAError(MDMA_HandleTypeDef *hmdma);
static void XSPI_DMAAbortCplt(MDMA_HandleTypeDef *hmdma);
static HAL_StatusTypeDef XSPI_WaitFlagStateUntilTimeout(XSPI_HandleTypeDef *hxspi, uint32_t Flag, FlagStatus State,
                                                        uint32_t Tickstart, uint32_t Timeout);
static void XSPI_Config(XSPI_HandleTypeDef *hxspi, XSPI_RegularCmdTypeDef *cmd, uint32_t FunctionalMode);

/* Exported functions --------------------------------------------------------*/

/** @defgroup XSPI_Exported_Functions XSPI Exported Functions
  * @{
  */

/** @defgroup XSPI_Exported_Functions_Group1 Initialization/de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to :
      (+) Initialize the XSPI.
      (+) De-initialize the XSPI.

@endverbatim
  * @{
  */

/**
  * @brief Initialize the XSPI mode according to the specified parameters
  *        in the XSPI_InitTypeDef and initialize the associated handle.
  * @param hxspi XSPI handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Init(XSPI_HandleTypeDef *hxspi)
{
  HAL_StatusTypeDef status;
  uint32_t tickstart = HAL_GetTick();

  /* Check the XSPI handle allocation */
  if (hxspi == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_QSPI_ALL_INSTANCE(hxspi->Instance));
  assert_param(IS_XSPI_CLK_PRESCALER(hxspi->Init.ClockPrescaler));
  /* Renamed IS_XSPI_FIFO_THRESHOLD(), FifoThreshold to IS_XSPI_FIFO_THRESHOLDBYTE and FifoThresholdByte respectively
  for better compatibility with ExtMem Manager */
  assert_param(IS_XSPI_FIFO_THRESHOLD_BYTE(hxspi->Init.FifoThresholdByte));
  assert_param(IS_XSPI_SAMPLE_SHIFTING(hxspi->Init.SampleShifting));
  /* FlashSize renamed to MemorySize for compatibility with Ext Mem Manager */
  assert_param(IS_XSPI_MEMORY_SIZE(hxspi->Init.MemorySize));
  assert_param(IS_XSPI_CS_HIGH_TIME_CYCLE(hxspi->Init.ChipSelectHighTimeCycle));
  assert_param(IS_XSPI_CLOCK_MODE(hxspi->Init.ClockMode));
  /* Renamed IS_XSPI_DUAL_FLASH_MODE to IS_XSPI_MEMORY_MODE for better compatibility with ExtMem Manager */
  assert_param(IS_XSPI_MEMORY_MODE(hxspi->Init.MemoryMode));

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hxspi->Lock = HAL_UNLOCKED;

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
    /* Reset Callback pointers in HAL_XSPI_STATE_RESET only */
    hxspi->ErrorCallback         = HAL_XSPI_ErrorCallback;
    hxspi->AbortCpltCallback     = HAL_XSPI_AbortCpltCallback;
    hxspi->FifoThresholdCallback = HAL_XSPI_FifoThresholdCallback;
    hxspi->CmdCpltCallback       = HAL_XSPI_CmdCpltCallback;
    hxspi->RxCpltCallback        = HAL_XSPI_RxCpltCallback;
    hxspi->TxCpltCallback        = HAL_XSPI_TxCpltCallback;
    hxspi->RxHalfCpltCallback    = HAL_XSPI_RxHalfCpltCallback;
    hxspi->TxHalfCpltCallback    = HAL_XSPI_TxHalfCpltCallback;
    hxspi->StatusMatchCallback   = HAL_XSPI_StatusMatchCallback;
    hxspi->TimeOutCallback       = HAL_XSPI_TimeOutCallback;

    if (hxspi->MspInitCallback == NULL)
    {
      hxspi->MspInitCallback = HAL_XSPI_MspInit;
    }

    /* Init the low level hardware */
    hxspi->MspInitCallback(hxspi);
#else
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_XSPI_MspInit(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */

    /* Configure the default timeout for the XSPI memory access */
    HAL_XSPI_SetTimeout(hxspi, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);
  }
  /* Renamed FifoThreshold to FifoThresholdByte for better compatibility with ExtMem Manager for future integration */
  /* Configure XSPI FIFO Threshold */
  MODIFY_REG(hxspi->Instance->CR, QUADSPI_CR_FTHRES,
             ((hxspi->Init.FifoThresholdByte - 1U) << QUADSPI_CR_FTHRES_Pos));

  /* Wait till BUSY flag reset */
  status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_BUSY, RESET, tickstart, hxspi->Timeout);

  if (status == HAL_OK)
  {
    /* Configure XSPI Clock Prescaler and Sample Shift */
    MODIFY_REG(hxspi->Instance->CR, (QUADSPI_CR_PRESCALER | QUADSPI_CR_SSHIFT | QUADSPI_CR_FSEL | QUADSPI_CR_DFM),
               ((hxspi->Init.ClockPrescaler << QUADSPI_CR_PRESCALER_Pos) |
                hxspi->Init.SampleShifting  | hxspi->Init.MemoryMode));

    /* Configure XSPI Memory Size, CS High Time and Clock Mode */
    MODIFY_REG(hxspi->Instance->DCR, (QUADSPI_DCR_FSIZE | QUADSPI_DCR_CSHT | QUADSPI_DCR_CKMODE),
               ((hxspi->Init.MemorySize << QUADSPI_DCR_FSIZE_Pos) |
                ((hxspi->Init.ChipSelectHighTimeCycle - 1U) << QUADSPI_DCR_CSHT_Pos) | hxspi->Init.ClockMode));

    /* Enable the XSPI peripheral */
    HAL_XSPI_ENABLE(hxspi);

    /* Set XSPI error code to none */
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    /* Initialize the XSPI state */
    hxspi->State = HAL_XSPI_STATE_READY;
  }

  /* Release Lock */
  __HAL_UNLOCK(hxspi);

  /* Return function status */
  return status;
}

/**
  * @brief De-Initialize the XSPI peripheral.
  * @param hxspi XSPI handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_DeInit(XSPI_HandleTypeDef *hxspi)
{
  /* Check the XSPI handle allocation */
  if (hxspi == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hxspi);

  /* Disable the XSPI Peripheral Clock */
  HAL_XSPI_DISABLE(hxspi);

#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
  if (hxspi->MspDeInitCallback == NULL)
  {
    hxspi->MspDeInitCallback = HAL_XSPI_MspDeInit;
  }

  /* DeInit the low level hardware */
  hxspi->MspDeInitCallback(hxspi);
#else
  /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
  HAL_XSPI_MspDeInit(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */

  /* Set XSPI error code to none */
  hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

  /* Initialize the XSPI state */
  hxspi->State = HAL_XSPI_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hxspi);

  return HAL_OK;
}

/**
  * @brief Initialize the XSPI MSP.
  * @param hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_MspInit(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_XSPI_MspInit can be implemented in the user file
   */
}

/**
  * @brief DeInitialize the XSPI MSP.
  * @param hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_MspDeInit(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_XSPI_MspDeInit can be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup XSPI_Exported_Functions_Group2 Input and Output operation functions
  *  @brief XSPI Transmit/Receive functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to :
      (+) Handle the interrupts.
      (+) Handle the command sequence.
      (+) Transmit data in blocking, interrupt or DMA mode.
      (+) Receive data in blocking, interrupt or DMA mode.
      (+) Manage the auto-polling functional mode.
      (+) Manage the memory-mapped functional mode.

@endverbatim
  * @{
  */

/**
  * @brief Handle XSPI interrupt request.
  * @param hxspi XSPI handle
  * @retval None
  */
void HAL_XSPI_IRQHandler(XSPI_HandleTypeDef *hxspi)
{
  __IO uint32_t *data_reg;
  uint32_t flag = READ_REG(hxspi->Instance->SR);
  uint32_t itsource = READ_REG(hxspi->Instance->CR);

  /* XSPI Fifo Threshold interrupt occurred ----------------------------------*/
  if (((flag & XSPI_FLAG_FT) != 0U) && ((itsource & XSPI_IT_FT) != 0U))
  {
    data_reg = &hxspi->Instance->DR;

    if (hxspi->State == HAL_XSPI_STATE_BUSY_INDIRECT_TX)
    {
      /* Transmission process */
      while (HAL_XSPI_GET_FLAG(hxspi, XSPI_FLAG_FT) != RESET)
      {
        if (hxspi->XferCount > 0U)
        {
          /* Fill the FIFO until the threshold is reached */
          *((__IO uint8_t *)data_reg) = *hxspi->pBuffPtr;
          hxspi->pBuffPtr++;
          hxspi->XferCount--;
        }
        else
        {
          /* No more data available for the transfer */
          /* Disable the XSPI FIFO Threshold Interrupt */
          HAL_XSPI_DISABLE_IT(hxspi, XSPI_IT_FT);
          break;
        }
      }
    }
    else if (hxspi->State == HAL_XSPI_STATE_BUSY_INDIRECT_RX)
    {
      /* Receiving Process */
      while (HAL_XSPI_GET_FLAG(hxspi, XSPI_FLAG_FT) != RESET)
      {
        if (hxspi->XferCount > 0U)
        {
          /* Read the FIFO until the threshold is reached */
          *hxspi->pBuffPtr = *((__IO uint8_t *)data_reg);
          hxspi->pBuffPtr++;
          hxspi->XferCount--;
        }
        else
        {
          /* All data have been received for the transfer */
          /* Disable the XSPI FIFO Threshold Interrupt */
          HAL_XSPI_DISABLE_IT(hxspi, XSPI_IT_FT);
          break;
        }
      }
    }
    else
    {
      /* Nothing to do */
    }

    /* FIFO Threshold callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
    hxspi->FifoThresholdCallback(hxspi);
#else
    HAL_XSPI_FifoThresholdCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
  }

  /* XSPI Transfer Complete interrupt occurred -------------------------------*/
  else if (((flag & XSPI_FLAG_TC) != 0U) && ((itsource & XSPI_IT_TC) != 0U))
  {
    /* Clear interrupt */
    WRITE_REG(hxspi->Instance->FCR, XSPI_FLAG_TC);

    /* Disable the XSPI FIFO Threshold, Transfer Error and Transfer complete Interrupts */
    HAL_XSPI_DISABLE_IT(hxspi, XSPI_IT_TC | XSPI_IT_TE | XSPI_IT_FT);

    /* Transfer complete callback */
    if (hxspi->State == HAL_XSPI_STATE_BUSY_INDIRECT_TX)
    {
      if ((hxspi->Instance->CR & QUADSPI_CR_DMAEN) != 0U)
      {
        /* Disable the DMA transfer by clearing the DMAEN bit in the XSPI CR register */
        CLEAR_BIT(hxspi->Instance->CR, QUADSPI_CR_DMAEN);

        /* Disable the MDMA channel */
        __HAL_MDMA_DISABLE(hxspi->hmdma);
      }


      /* Change state of XSPI */
      hxspi->State = HAL_XSPI_STATE_READY;

      /* TX Complete callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
      hxspi->TxCpltCallback(hxspi);
#else
      HAL_XSPI_TxCpltCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
    }
    else if (hxspi->State == HAL_XSPI_STATE_BUSY_INDIRECT_RX)
    {
      if ((hxspi->Instance->CR & QUADSPI_CR_DMAEN) != 0U)
      {
        /* Disable the DMA transfer by clearing the DMAEN bit in the XSPI CR register */
        CLEAR_BIT(hxspi->Instance->CR, QUADSPI_CR_DMAEN);

        /* Disable the MDMA channel */
        __HAL_MDMA_DISABLE(hxspi->hmdma);
      }
      else
      {
        data_reg = &hxspi->Instance->DR;
        while (READ_BIT(hxspi->Instance->SR, QUADSPI_SR_FLEVEL) != 0U)
        {
          if (hxspi->XferCount > 0U)
          {
            /* Read the last data received in the FIFO until it is empty */
            *hxspi->pBuffPtr = *((__IO uint8_t *)data_reg);
            hxspi->pBuffPtr++;
            hxspi->XferCount--;
          }
          else
          {
            /* All data have been received for the transfer */
            break;
          }
        }
      }


      /* Change state of XSPI */
      hxspi->State = HAL_XSPI_STATE_READY;

      /* RX Complete callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
      hxspi->RxCpltCallback(hxspi);
#else
      HAL_XSPI_RxCpltCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
    }
    else if (hxspi->State == HAL_XSPI_STATE_BUSY)
    {
      /* Change state of XSPI */
      hxspi->State = HAL_XSPI_STATE_READY;

      /* Command Complete callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
      hxspi->CmdCpltCallback(hxspi);
#else
      HAL_XSPI_CmdCpltCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
 */
    }
    else if (hxspi->State == HAL_XSPI_STATE_ABORT)
    {
      /* Reset functional mode configuration to indirect write mode by default */
      CLEAR_BIT(hxspi->Instance->CCR, QUADSPI_CCR_FMODE);

      /* Change state of XSPI */
      hxspi->State = HAL_XSPI_STATE_READY;

      if (hxspi->ErrorCode == HAL_XSPI_ERROR_NONE)
      {
        /* Abort called by the user */

        /* Abort Complete callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
        hxspi->AbortCpltCallback(hxspi);
#else
        HAL_XSPI_AbortCpltCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
      }
      else
      {
        /* Abort due to an error (eg :  MDMA error) */

        /* Error callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
        hxspi->ErrorCallback(hxspi);
#else
        HAL_XSPI_ErrorCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
      }
    }
    else
    {
      /* Nothing to do */
    }
  }

  /* XSPI Status Match interrupt occurred ------------------------------------*/
  else if (((flag & XSPI_FLAG_SM) != 0U) && ((itsource & XSPI_IT_SM) != 0U))
  {
    /* Clear interrupt */
    WRITE_REG(hxspi->Instance->FCR, XSPI_FLAG_SM);

    /* Check if the automatic poll mode stop is activated */
    if (READ_BIT(hxspi->Instance->CR, QUADSPI_CR_APMS) != 0U)
    {
      /* Disable the XSPI Transfer Error and Status Match Interrupts */
      HAL_XSPI_DISABLE_IT(hxspi, (XSPI_IT_SM | XSPI_IT_TE));

      /* Change state of XSPI */
      hxspi->State = HAL_XSPI_STATE_READY;
    }

    /* Status match callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
    hxspi->StatusMatchCallback(hxspi);
#else
    HAL_XSPI_StatusMatchCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
  }

  /* XSPI Transfer Error interrupt occurred ----------------------------------*/
  else if (((flag & XSPI_FLAG_TE) != 0U) && ((itsource & XSPI_IT_TE) != 0U))
  {
    /* Clear interrupt */
    WRITE_REG(hxspi->Instance->FCR, XSPI_FLAG_TE);

    /* Disable all the XSPI Interrupts */
    HAL_XSPI_DISABLE_IT(hxspi, XSPI_IT_SM | XSPI_IT_TC | XSPI_IT_TE | XSPI_IT_FT);

    /* Set error code */
    hxspi->ErrorCode |= HAL_XSPI_ERROR_TRANSFER;

    if ((hxspi->Instance->CR & QUADSPI_CR_DMAEN) != 0U)
    {
      /* Disable the DMA transfer by clearing the DMAEN bit in the XSPI CR register */
      CLEAR_BIT(hxspi->Instance->CR, QUADSPI_CR_DMAEN);

      /* Disable the MDMA channel */
      hxspi->hmdma->XferAbortCallback = XSPI_DMAAbortCplt;
      if (HAL_MDMA_Abort_IT(hxspi->hmdma) != HAL_OK)
      {
        /* Set error code to DMA */
        hxspi->ErrorCode |= HAL_XSPI_ERROR_DMA;

        /* Change state of XSPI */
        hxspi->State = HAL_XSPI_STATE_READY;

        /* Error callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
        hxspi->ErrorCallback(hxspi);
#else
        HAL_XSPI_ErrorCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
      }
    }
    else
    {
      /* Change state of XSPI */
      hxspi->State = HAL_XSPI_STATE_READY;

      /* Error callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
      hxspi->ErrorCallback(hxspi);
#else
      HAL_XSPI_ErrorCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
    }
  }

  /* XSPI Timeout interrupt occurred -----------------------------------------*/
  else if (((flag & XSPI_FLAG_TO) != 0U) && ((itsource & XSPI_IT_TO) != 0U))
  {
    /* Clear interrupt */
    WRITE_REG(hxspi->Instance->FCR, XSPI_FLAG_TO);

    /* Timeout callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
    hxspi->TimeOutCallback(hxspi);
#else
    HAL_XSPI_TimeOutCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
  }

  else
  {
    /* Nothing to do */
  }
}

/**
  * @brief Set the command configuration.
  * @param hxspi XSPI handle
  * @param cmd : structure that contains the command configuration information
  * @param Timeout Timeout duration
  * @note   This function is used only in Indirect Read or Write Modes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Command(XSPI_HandleTypeDef *hxspi, XSPI_RegularCmdTypeDef *cmd, uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  uint32_t tickstart = HAL_GetTick();

  /* Renamed IS_XSPI_DUAL_FLASH_MODE to IS_XSPI_MEMORY_MODE for better compatibility with ExtMem Manager */
  assert_param(IS_XSPI_MEMORY_MODE(hxspi->Init.MemoryMode));

  if (hxspi->Init.MemoryMode != HAL_XSPI_DUAL_MEM)
  {
    assert_param(IS_XSPI_IO_SELECT(cmd->IOSelect));
    MODIFY_REG(hxspi->Instance->CR, QUADSPI_CR_FSEL, cmd->IOSelect);
  }

  /* Check the parameters */
  assert_param(IS_XSPI_INSTRUCTION_MODE(cmd->InstructionMode));
  if (cmd->InstructionMode != XSPI_INSTRUCTION_NONE)
  {
    assert_param(IS_XSPI_INSTRUCTION(cmd->Instruction));
  }

  assert_param(IS_XSPI_ADDRESS_MODE(cmd->AddressMode));
  if (cmd->AddressMode != XSPI_ADDRESS_NONE)
  {
    /* Renamed IS_XSPI_ADDRESS_SIZE() to IS_XSPI_ADDRESS_WIDTH() for better compatibility with ExtMem Manager */
    assert_param(IS_XSPI_ADDRESS_WIDTH(cmd->AddressWidth));
  }

  assert_param(IS_XSPI_ALT_BYTES_MODE(cmd->AlternateByteMode));
  if (cmd->AlternateByteMode != XSPI_ALT_BYTES_NONE)
  {
    /* Renamed IS_XSPI_ALT_BYTES_SIZE() to IS_XSPI_ALT_BYTES_WIDTH() for better compatibility with
    ExtMem Manager */
    assert_param(IS_XSPI_ALT_BYTES_WIDTH(cmd->AlternateBytesWidth));
  }

  assert_param(IS_XSPI_DUMMY_CYCLES(cmd->DummyCycles));
  assert_param(IS_XSPI_DATA_MODE(cmd->DataMode));

  assert_param(IS_XSPI_DTR_MODE(cmd->DTRMode));
  assert_param(IS_XSPI_DHHC(cmd->DelayHoldHalfCycle));
  assert_param(IS_XSPI_SIOO_MODE(cmd->SIOOMode));

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    /* Update XSPI state */
    hxspi->State = HAL_XSPI_STATE_BUSY;

    /* Wait till BUSY flag reset */
    status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_BUSY, RESET, tickstart, Timeout);

    if (status == HAL_OK)
    {
      /* Call the configuration function */
      XSPI_Config(hxspi, cmd, XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE);

      if (cmd->DataMode == XSPI_DATA_NONE)
      {
        /* When there is no data phase, the transfer start as soon as the configuration is done
        so wait until TC flag is set to go back in idle state */
        status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_TC, SET, tickstart, Timeout);

        if (status == HAL_OK)
        {
          HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TC);

          /* Update XSPI state */
          hxspi->State = HAL_XSPI_STATE_READY;
        }
      }
      else
      {
        /* Update XSPI state */
        hxspi->State = HAL_XSPI_STATE_READY;
      }
    }
  }
  else
  {
    status = HAL_BUSY;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hxspi);

  /* Return function status */
  return status;
}

/**
  * @brief Set the command configuration in interrupt mode.
  * @param hxspi XSPI handle
  * @param cmd structure that contains the command configuration information
  * @note   This function is used only in Indirect Read or Write Modes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Command_IT(XSPI_HandleTypeDef *hxspi, XSPI_RegularCmdTypeDef *cmd)
{
  HAL_StatusTypeDef status;
  uint32_t tickstart = HAL_GetTick();

  /* Renamed IS_XSPI_DUAL_FLASH_MODE to IS_XSPI_MEMORY_MODE for better compatibility with ExtMem Manager */
  assert_param(IS_XSPI_MEMORY_MODE(hxspi->Init.MemoryMode));

  if (hxspi->Init.MemoryMode != HAL_XSPI_DUAL_MEM)
  {
    assert_param(IS_XSPI_IO_SELECT(cmd->IOSelect));
    MODIFY_REG(hxspi->Instance->CR, QUADSPI_CR_FSEL, cmd->IOSelect);
  }

  /* Check the parameters */
  assert_param(IS_XSPI_INSTRUCTION_MODE(cmd->InstructionMode));
  if (cmd->InstructionMode != XSPI_INSTRUCTION_NONE)
  {
    assert_param(IS_XSPI_INSTRUCTION(cmd->Instruction));
  }

  assert_param(IS_XSPI_ADDRESS_MODE(cmd->AddressMode));
  if (cmd->AddressMode != XSPI_ADDRESS_NONE)
  {
    /* Renamed IS_XSPI_ADDRESS_SIZE() to IS_XSPI_ADDRESS_WIDTH() for better compatibility with ExtMem Manager */
    assert_param(IS_XSPI_ADDRESS_WIDTH(cmd->AddressWidth));
  }

  assert_param(IS_XSPI_ALT_BYTES_MODE(cmd->AlternateByteMode));
  if (cmd->AlternateByteMode != XSPI_ALT_BYTES_NONE)
  {
    /* Renamed IS_XSPI_ALT_BYTES_SIZE() to IS_XSPI_ALT_BYTES_WIDTH() for better compatibility with
    ExtMem Manager */
    assert_param(IS_XSPI_ALT_BYTES_WIDTH(cmd->AlternateBytesWidth));
  }

  assert_param(IS_XSPI_DUMMY_CYCLES(cmd->DummyCycles));
  assert_param(IS_XSPI_DATA_MODE(cmd->DataMode));

  assert_param(IS_XSPI_DTR_MODE(cmd->DTRMode));
  assert_param(IS_XSPI_DHHC(cmd->DelayHoldHalfCycle));
  assert_param(IS_XSPI_SIOO_MODE(cmd->SIOOMode));

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    /* Update XSPI state */
    hxspi->State = HAL_XSPI_STATE_BUSY;

    /* Wait till BUSY flag reset */
    status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_BUSY, RESET, tickstart, hxspi->Timeout);

    if (status == HAL_OK)
    {
      if (cmd->DataMode == XSPI_DATA_NONE)
      {
        /* Clear interrupt */
        HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TE | XSPI_FLAG_TC);
      }

      /* Call the configuration function */
      XSPI_Config(hxspi, cmd, XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE);

      if (cmd->DataMode == XSPI_DATA_NONE)
      {
        /* When there is no data phase, the transfer start as soon as the configuration is done
        so activate TC and TE interrupts */
        /* Process unlocked */
        __HAL_UNLOCK(hxspi);

        /* Enable the XSPI Transfer Error Interrupt */
        HAL_XSPI_ENABLE_IT(hxspi, XSPI_IT_TE | XSPI_IT_TC);
      }
      else
      {
        /* Update XSPI state */
        hxspi->State = HAL_XSPI_STATE_READY;

        /* Process unlocked */
        __HAL_UNLOCK(hxspi);
      }
    }
    else
    {
      /* Process unlocked */
      __HAL_UNLOCK(hxspi);
    }
  }
  else
  {
    status = HAL_BUSY;

    /* Process unlocked */
    __HAL_UNLOCK(hxspi);
  }

  /* Return function status */
  return status;
}

/**
  * @brief Transmit an amount of data in blocking mode.
  * @param hxspi XSPI handle
  * @param pData pointer to data buffer
  * @param Timeout Timeout duration
  * @note   This function is used only in Indirect Write Mode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Transmit(XSPI_HandleTypeDef *hxspi, uint8_t *pData, uint32_t Timeout)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tickstart = HAL_GetTick();
  __IO uint32_t *data_reg = &hxspi->Instance->DR;

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    if (pData != NULL)
    {
      /* Update state */
      hxspi->State = HAL_XSPI_STATE_BUSY_INDIRECT_TX;

      /* Configure counters and size of the handle */
      hxspi->XferCount = READ_REG(hxspi->Instance->DLR) + 1U;
      hxspi->XferSize = READ_REG(hxspi->Instance->DLR) + 1U;
      hxspi->pBuffPtr = pData;

      /* Configure XSPI: CCR register with functional as indirect write */
      MODIFY_REG(hxspi->Instance->CCR, QUADSPI_CCR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE);

      while (hxspi->XferCount > 0U)
      {
        /* Wait until FT flag is set to send data */
        status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_FT, SET, tickstart, Timeout);

        if (status != HAL_OK)
        {
          break;
        }

        *((__IO uint8_t *)data_reg) = *hxspi->pBuffPtr;
        hxspi->pBuffPtr++;
        hxspi->XferCount--;
      }

      if (status == HAL_OK)
      {
        /* Wait until TC flag is set to go back in idle state */
        status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_TC, SET, tickstart, Timeout);

        if (status == HAL_OK)
        {
          /* Clear Transfer Complete bit */
          HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TC);

        }
      }

      /* Update XSPI state */
      hxspi->State = HAL_XSPI_STATE_READY;
    }
    else
    {
      hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
  }
  else
  {
    status = HAL_BUSY;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hxspi);

  return status;
}


/**
  * @brief Receive an amount of data in blocking mode.
  * @param hxspi XSPI handle
  * @param pData pointer to data buffer
  * @param Timeout Timeout duration
  * @note   This function is used only in Indirect Read Mode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Receive(XSPI_HandleTypeDef *hxspi, uint8_t *pData, uint32_t Timeout)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tickstart = HAL_GetTick();
  uint32_t addr_reg = READ_REG(hxspi->Instance->AR);
  __IO uint32_t *data_reg = &hxspi->Instance->DR;

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    if (pData != NULL)
    {
      /* Update state */
      hxspi->State = HAL_XSPI_STATE_BUSY_INDIRECT_RX;

      /* Configure counters and size of the handle */
      hxspi->XferCount = READ_REG(hxspi->Instance->DLR) + 1U;
      hxspi->XferSize = READ_REG(hxspi->Instance->DLR) + 1U;
      hxspi->pBuffPtr = pData;

      /* Configure XSPI: CCR register with functional as indirect read */
      MODIFY_REG(hxspi->Instance->CCR, QUADSPI_CCR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_READ);

      /* Start the transfer by re-writing the address in AR register */
      WRITE_REG(hxspi->Instance->AR, addr_reg);

      while (hxspi->XferCount > 0U)
      {
        /* Wait until FT or TC flag is set to read received data */
        status = XSPI_WaitFlagStateUntilTimeout(hxspi, (XSPI_FLAG_FT | XSPI_FLAG_TC), SET, tickstart, Timeout);

        if (status != HAL_OK)
        {
          break;
        }

        *hxspi->pBuffPtr = *((__IO uint8_t *)data_reg);
        hxspi->pBuffPtr++;
        hxspi->XferCount--;
      }

      if (status == HAL_OK)
      {
        /* Wait until TC flag is set to go back in idle state */
        status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_TC, SET, tickstart, Timeout);

        if (status == HAL_OK)
        {
          /* Clear Transfer Complete bit */
          HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TC);

        }
      }

      /* Update XSPI state */
      hxspi->State = HAL_XSPI_STATE_READY;
    }
    else
    {
      hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
  }
  else
  {
    status = HAL_BUSY;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hxspi);

  return status;
}

/**
  * @brief  Send an amount of data in non-blocking mode with interrupt.
  * @param  hxspi XSPI handle
  * @param  pData pointer to data buffer
  * @note   This function is used only in Indirect Write Mode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Transmit_IT(XSPI_HandleTypeDef *hxspi, uint8_t *pData)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    if (pData != NULL)
    {
      /* Update state */
      hxspi->State = HAL_XSPI_STATE_BUSY_INDIRECT_TX;

      /* Configure counters and size of the handle */
      hxspi->XferCount = READ_REG(hxspi->Instance->DLR) + 1U;
      hxspi->XferSize = READ_REG(hxspi->Instance->DLR) + 1U;
      hxspi->pBuffPtr = pData;

      /* Clear interrupt */
      HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TE | XSPI_FLAG_TC);

      /* Configure XSPI: CCR register with functional as indirect write */
      MODIFY_REG(hxspi->Instance->CCR, QUADSPI_CCR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE);

      /* Process unlocked */
      __HAL_UNLOCK(hxspi);

      /* Enable the XSPI transfer error, FIFO threshold and transfer complete Interrupts */
      HAL_XSPI_ENABLE_IT(hxspi, XSPI_IT_TE | XSPI_IT_FT | XSPI_IT_TC);
    }
    else
    {
      hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_PARAM;
      status = HAL_ERROR;

      /* Process unlocked */
      __HAL_UNLOCK(hxspi);
    }
  }
  else
  {
    status = HAL_BUSY;

    /* Process unlocked */
    __HAL_UNLOCK(hxspi);
  }

  return status;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with interrupt.
  * @param  hxspi XSPI handle
  * @param  pData pointer to data buffer
  * @note   This function is used only in Indirect Read Mode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Receive_IT(XSPI_HandleTypeDef *hxspi, uint8_t *pData)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t addr_reg = READ_REG(hxspi->Instance->AR);

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    if (pData != NULL)
    {
      /* Update state */
      hxspi->State = HAL_XSPI_STATE_BUSY_INDIRECT_RX;

      /* Configure counters and size of the handle */
      hxspi->XferCount = READ_REG(hxspi->Instance->DLR) + 1U;
      hxspi->XferSize = READ_REG(hxspi->Instance->DLR) + 1U;
      hxspi->pBuffPtr = pData;

      /* Clear interrupt */
      HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TE | XSPI_FLAG_TC);

      /* Configure XSPI: CCR register with functional as indirect read */
      MODIFY_REG(hxspi->Instance->CCR, QUADSPI_CCR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_READ);

      /* Start the transfer by re-writing the address in AR register */
      WRITE_REG(hxspi->Instance->AR, addr_reg);

      /* Process unlocked */
      __HAL_UNLOCK(hxspi);

      /* Enable the XSPI transfer error, FIFO threshold and transfer complete Interrupts */
      HAL_XSPI_ENABLE_IT(hxspi, XSPI_IT_TE | XSPI_IT_FT | XSPI_IT_TC);
    }
    else
    {
      hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_PARAM;
      status = HAL_ERROR;

      /* Process unlocked */
      __HAL_UNLOCK(hxspi);
    }
  }
  else
  {
    status = HAL_BUSY;

    /* Process unlocked */
    __HAL_UNLOCK(hxspi);
  }

  return status;
}

/**
  * @brief  Send an amount of data in non-blocking mode with DMA.
  * @param  hxspi XSPI handle
  * @param  pData pointer to data buffer
  * @note   This function is used only in Indirect Write Mode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Transmit_DMA(XSPI_HandleTypeDef *hxspi, uint8_t *pData)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t data_size = (READ_REG(hxspi->Instance->DLR) + 1U);

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    /* Clear the error code */
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    if (pData != NULL)
    {
      /* Configure counters of the handle */
      hxspi->XferCount = data_size;

      /* Update state */
      hxspi->State = HAL_XSPI_STATE_BUSY_INDIRECT_TX;

      /* Clear interrupt */
      HAL_XSPI_CLEAR_FLAG(hxspi, (XSPI_FLAG_TE | XSPI_FLAG_TC));

      /* Configure size and pointer of the handle */
      hxspi->XferSize = hxspi->XferCount;
      hxspi->pBuffPtr = pData;

      /* Configure XSPI: CCR register with functional mode as indirect write */
      MODIFY_REG(hxspi->Instance->CCR, QUADSPI_CCR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE);

      /* Set the XSPI MDMA transfer complete callback */
      hxspi->hmdma->XferCpltCallback = XSPI_DMATxCplt;

      /* Set the MDMA error callback */
      hxspi->hmdma->XferErrorCallback = XSPI_DMAError;

      /* Clear the MDMA abort callback */
      hxspi->hmdma->XferAbortCallback = NULL;

      /* In Transmit mode , the MDMA destination is the XSPI DR register :
         Force the MDMA Destination Increment to disable */
      MODIFY_REG(hxspi->hmdma->Instance->CTCR, (MDMA_CTCR_DINC | MDMA_CTCR_DINCOS), MDMA_DEST_INC_DISABLE);

      /* Update MDMA configuration with the correct SourceInc field for Write operation */
      if (hxspi->hmdma->Init.SourceDataSize == MDMA_SRC_DATASIZE_BYTE)
      {
        MODIFY_REG(hxspi->hmdma->Instance->CTCR, (MDMA_CTCR_SINC | MDMA_CTCR_SINCOS), MDMA_SRC_INC_BYTE);
      }
      else if (hxspi->hmdma->Init.SourceDataSize == MDMA_SRC_DATASIZE_HALFWORD)
      {
        MODIFY_REG(hxspi->hmdma->Instance->CTCR, (MDMA_CTCR_SINC | MDMA_CTCR_SINCOS), MDMA_SRC_INC_HALFWORD);
      }
      else if (hxspi->hmdma->Init.SourceDataSize == MDMA_SRC_DATASIZE_WORD)
      {
        MODIFY_REG(hxspi->hmdma->Instance->CTCR, (MDMA_CTCR_SINC | MDMA_CTCR_SINCOS), MDMA_SRC_INC_WORD);
      }
      else
      {
        /* in case of incorrect source data size */
        hxspi->ErrorCode |= HAL_XSPI_ERROR_DMA;
        status = HAL_ERROR;
      }

      /* Enable the XSPI transmit MDMA */
      if (HAL_MDMA_Start_IT(hxspi->hmdma, (uint32_t)pData, (uint32_t)&hxspi->Instance->DR, hxspi->XferSize,
                            1) == HAL_OK)
      {
        /* Process unlocked */
        __HAL_UNLOCK(hxspi);

        /* Enable the XSPI transfer error Interrupt */
        HAL_XSPI_ENABLE_IT(hxspi, XSPI_IT_TE);

        /* Enable the MDMA transfer by setting the DMAEN bit not needed for MDMA*/
      }
      else
      {
        status = HAL_ERROR;
        hxspi->ErrorCode |= HAL_XSPI_ERROR_DMA;
        hxspi->State = HAL_XSPI_STATE_READY;

        /* Process unlocked */
        __HAL_UNLOCK(hxspi);
      }
    }
    else
    {
      hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_PARAM;
      status = HAL_ERROR;

      /* Process unlocked */
      __HAL_UNLOCK(hxspi);
    }
  }
  else
  {
    status = HAL_BUSY;

    /* Process unlocked */
    __HAL_UNLOCK(hxspi);
  }

  return status;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with DMA.
  * @param  hxspi XSPI handle
  * @param  pData pointer to data buffer.
  * @note   This function is used only in Indirect Read Mode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Receive_DMA(XSPI_HandleTypeDef *hxspi, uint8_t *pData)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t addr_reg = READ_REG(hxspi->Instance->AR);
  uint32_t data_size = (READ_REG(hxspi->Instance->DLR) + 1U);

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    /* Clear the error code */
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    if (pData != NULL)
    {
      /* Configure counters of the handle */
      hxspi->XferCount = data_size;
      /* Update state */
      hxspi->State = HAL_XSPI_STATE_BUSY_INDIRECT_RX;

      /* Clear interrupt */
      HAL_XSPI_CLEAR_FLAG(hxspi, (XSPI_FLAG_TE | XSPI_FLAG_TC));

      /* Configure size and pointer of the handle */
      hxspi->XferSize = hxspi->XferCount;
      hxspi->pBuffPtr = pData;

      /* Set the XSPI DMA transfer complete callback */
      hxspi->hmdma->XferCpltCallback = XSPI_DMARxCplt;

      /* Set the MDMA error callback */
      hxspi->hmdma->XferErrorCallback = XSPI_DMAError;

      /* Clear the MDMA abort callback */
      hxspi->hmdma->XferAbortCallback = NULL;

      /* In Receive mode , the MDMA source is the XSPI DR register : Force the MDMA Source Increment to disable */
      MODIFY_REG(hxspi->hmdma->Instance->CTCR, (MDMA_CTCR_SINC | MDMA_CTCR_SINCOS), MDMA_SRC_INC_DISABLE);

      /* Update MDMA configuration with the correct DestinationInc field for read operation */
      if (hxspi->hmdma->Init.DestDataSize == MDMA_DEST_DATASIZE_BYTE)
      {
        MODIFY_REG(hxspi->hmdma->Instance->CTCR, (MDMA_CTCR_DINC | MDMA_CTCR_DINCOS), MDMA_DEST_INC_BYTE);
      }
      else if (hxspi->hmdma->Init.DestDataSize == MDMA_DEST_DATASIZE_HALFWORD)
      {
        MODIFY_REG(hxspi->hmdma->Instance->CTCR, (MDMA_CTCR_DINC | MDMA_CTCR_DINCOS), MDMA_DEST_INC_HALFWORD);
      }
      else if (hxspi->hmdma->Init.DestDataSize == MDMA_DEST_DATASIZE_WORD)
      {
        MODIFY_REG(hxspi->hmdma->Instance->CTCR, (MDMA_CTCR_DINC | MDMA_CTCR_DINCOS), MDMA_DEST_INC_WORD);
      }
      else
      {
        /* in case of incorrect destination data size */
        hxspi->ErrorCode |= HAL_XSPI_ERROR_DMA;
        status = HAL_ERROR;
      }

      /* XSPI need to be configured to indirect mode before starting
         the MDMA to avoid premature triggering for the MDMA transfer */
      /* Configure XSPI: CCR register with functional as indirect read */
      MODIFY_REG(hxspi->Instance->CCR, QUADSPI_CCR_FMODE, XSPI_FUNCTIONAL_MODE_INDIRECT_READ);

      /* Start the transfer by re-writing the address in AR register */
      WRITE_REG(hxspi->Instance->AR, addr_reg);

      /* Enable the MDMA */
      if (HAL_MDMA_Start_IT(hxspi->hmdma, (uint32_t)&hxspi->Instance->DR, (uint32_t)pData, hxspi->XferSize, 1)
          == HAL_OK)
      {
        /* Process unlocked */
        __HAL_UNLOCK(hxspi);

        /* Enable the XSPI transfer error Interrupt */
        HAL_XSPI_ENABLE_IT(hxspi, XSPI_IT_TE);

        /* Enable the MDMA transfer by setting the DMAEN bit in the XSPI CR register */
        SET_BIT(hxspi->Instance->CR, QUADSPI_CR_DMAEN);
      }
      else
      {
        status = HAL_ERROR;
        hxspi->ErrorCode |= HAL_XSPI_ERROR_DMA;
        hxspi->State = HAL_XSPI_STATE_READY;

        /* Process unlocked */
        __HAL_UNLOCK(hxspi);
      }
    }
    else
    {
      hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_PARAM;
      status = HAL_ERROR;

      /* Process unlocked */
      __HAL_UNLOCK(hxspi);
    }
  }
  else
  {
    status = HAL_BUSY;

    /* Process unlocked */
    __HAL_UNLOCK(hxspi);
  }

  return status;
}

/**
  * @brief  Configure the XSPI Automatic Polling Mode in blocking mode.
  * @param  hxspi XSPI handle
  * @param  cfg structure that contains the polling configuration information.
  * @param  Timeout Timeout duration
  * @note   This function is used only in Automatic Polling Mode.
            XSPI_RegularCmdTypeDef ConfigCmd defined in hal_xspi.h needs to be populated by application code before
            invoking below APIs HAL_XSPI_AutoPolling()
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_AutoPolling(XSPI_HandleTypeDef *hxspi, XSPI_AutoPollingTypeDef *cfg, uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  uint32_t tickstart = HAL_GetTick();

  /* Renamed IS_XSPI_DUAL_FLASH_MODE to IS_XSPI_MEMORY_MODE for better compatibility with ExtMem Manager */
  assert_param(IS_XSPI_MEMORY_MODE(hxspi->Init.MemoryMode));

  if (hxspi->Init.MemoryMode != HAL_XSPI_DUAL_MEM)
  {
    assert_param(IS_XSPI_IO_SELECT(ConfigCmd.IOSelect));
    MODIFY_REG(hxspi->Instance->CR, QUADSPI_CR_FSEL, ConfigCmd.IOSelect);
  }

  assert_param(IS_XSPI_INSTRUCTION_MODE(ConfigCmd.InstructionMode));
  if (ConfigCmd.InstructionMode != XSPI_INSTRUCTION_NONE)
  {
    assert_param(IS_XSPI_INSTRUCTION(ConfigCmd.Instruction));
  }

  assert_param(IS_XSPI_ADDRESS_MODE(ConfigCmd.AddressMode));
  if (ConfigCmd.AddressMode != XSPI_ADDRESS_NONE)
  {
    /* Renamed IS_XSPI_ADDRESS_SIZE() to IS_XSPI_ADDRESS_WIDTH() for better compatibility with ExtMem Manager */
    assert_param(IS_XSPI_ADDRESS_WIDTH(ConfigCmd.AddressWidth));
  }

  assert_param(IS_XSPI_ALT_BYTES_MODE(ConfigCmd.AlternateByteMode));
  if (ConfigCmd.AlternateByteMode != XSPI_ALT_BYTES_NONE)
  {
    /* Renamed IS_XSPI_ALT_BYTES_SIZE() to IS_XSPI_ALT_BYTES_WIDTH() for better compatibility with
    ExtMem Manager */
    assert_param(IS_XSPI_ALT_BYTES_WIDTH(ConfigCmd.AlternateBytesWidth));
  }

  assert_param(IS_XSPI_DUMMY_CYCLES(ConfigCmd.DummyCycles));
  assert_param(IS_XSPI_DATA_MODE(ConfigCmd.DataMode));

  assert_param(IS_XSPI_DTR_MODE(ConfigCmd.DTRMode));
  assert_param(IS_XSPI_DHHC(ConfigCmd.DelayHoldHalfCycle));
  assert_param(IS_XSPI_SIOO_MODE(ConfigCmd.SIOOMode));

  assert_param(IS_XSPI_INTERVAL(cfg->IntervalTime));
  assert_param(IS_XSPI_MATCH_MODE(cfg->MatchMode));

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    /* Update state */
    hxspi->State = HAL_XSPI_STATE_BUSY_AUTO_POLLING;

    /* Wait till BUSY flag reset */
    status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_BUSY, RESET, tickstart, Timeout);

    if (status == HAL_OK)
    {
      /* Configure XSPI: PSMAR register with the status match value */
      WRITE_REG(hxspi->Instance->PSMAR, cfg->MatchValue);

      /* Configure XSPI: PSMKR register with the status mask value */
      WRITE_REG(hxspi->Instance->PSMKR, cfg->MatchMask);

      /* Configure XSPI: PIR register with the interval value */
      WRITE_REG(hxspi->Instance->PIR, cfg->IntervalTime);

      /* Configure XSPI: CR register with Match mode and Automatic stop enabled
      (otherwise there will be an infinite loop in blocking mode) */
      MODIFY_REG(hxspi->Instance->CR, (QUADSPI_CR_PMM | QUADSPI_CR_APMS),
                 (cfg->MatchMode | XSPI_AUTOMATIC_STOP_ENABLE));

      /* Call the configuration function */
      XSPI_Config(hxspi, &ConfigCmd, XSPI_FUNCTIONAL_MODE_AUTO_POLLING);

      /* Wait until SM flag is set to go back in idle state */
      status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_SM, SET, tickstart, Timeout);

      if (status == HAL_OK)
      {
        HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_SM);

        /* Update state */
        hxspi->State = HAL_XSPI_STATE_READY;
      }
    }
  }
  else
  {
    status = HAL_BUSY;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hxspi);

  /* Return function status */
  return status;
}

/**
  * @brief  Configure the XSPI Automatic Polling Mode in non-blocking mode.
  * @param  hxspi XSPI handle
  * @param  cfg structure that contains the polling configuration information.
  * @note   This function is used only in Automatic Polling Mode.
            XSPI_RegularCmdTypeDef ConfigCmd defined in hal_xspi.h needs to be populated by application code before
            invoking below APIs HAL_XSPI_AutoPolling_IT()
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_AutoPolling_IT(XSPI_HandleTypeDef *hxspi, XSPI_AutoPollingTypeDef *cfg)
{
  HAL_StatusTypeDef status;
  uint32_t tickstart = HAL_GetTick();

  /* Renamed IS_XSPI_DUAL_FLASH_MODE to IS_XSPI_MEMORY_MODE for better compatibility with ExtMem Manager */
  assert_param(IS_XSPI_MEMORY_MODE(hxspi->Init.MemoryMode));

  if (hxspi->Init.MemoryMode != HAL_XSPI_DUAL_MEM)
  {
    assert_param(IS_XSPI_IO_SELECT(ConfigCmd.IOSelect));
    MODIFY_REG(hxspi->Instance->CR, QUADSPI_CR_FSEL, ConfigCmd.IOSelect);
  }

  assert_param(IS_XSPI_INSTRUCTION_MODE(ConfigCmd.InstructionMode));
  if (ConfigCmd.InstructionMode != XSPI_INSTRUCTION_NONE)
  {
    assert_param(IS_XSPI_INSTRUCTION(ConfigCmd.Instruction));
  }

  assert_param(IS_XSPI_ADDRESS_MODE(ConfigCmd.AddressMode));
  if (ConfigCmd.AddressMode != XSPI_ADDRESS_NONE)
  {
    /* Renamed IS_XSPI_ADDRESS_SIZE() to IS_XSPI_ADDRESS_WIDTH() for better compatibility with ExtMem Manager */
    assert_param(IS_XSPI_ADDRESS_WIDTH(ConfigCmd.AddressWidth));
  }

  assert_param(IS_XSPI_ALT_BYTES_MODE(ConfigCmd.AlternateByteMode));
  if (ConfigCmd.AlternateByteMode != XSPI_ALT_BYTES_NONE)
  {
    /* Renamed IS_XSPI_ALT_BYTES_SIZE() to IS_XSPI_ALT_BYTES_WIDTH() for better compatibility with
    ExtMem Manager */
    assert_param(IS_XSPI_ALT_BYTES_WIDTH(ConfigCmd.AlternateBytesWidth));
  }

  assert_param(IS_XSPI_DUMMY_CYCLES(ConfigCmd.DummyCycles));
  assert_param(IS_XSPI_DATA_MODE(ConfigCmd.DataMode));

  assert_param(IS_XSPI_DTR_MODE(ConfigCmd.DTRMode));
  assert_param(IS_XSPI_DHHC(ConfigCmd.DelayHoldHalfCycle));
  assert_param(IS_XSPI_SIOO_MODE(ConfigCmd.SIOOMode));

  assert_param(IS_XSPI_INTERVAL(cfg->IntervalTime));
  assert_param(IS_XSPI_MATCH_MODE(cfg->MatchMode));
  assert_param(IS_XSPI_AUTOMATIC_STOP(cfg->AutomaticStop));

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    /* Update state */
    hxspi->State = HAL_XSPI_STATE_BUSY_AUTO_POLLING;

    /* Wait till BUSY flag reset */
    status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_BUSY, RESET, tickstart, hxspi->Timeout);

    if (status == HAL_OK)
    {
      /* Configure XSPI: PSMAR register with the status match value */
      WRITE_REG(hxspi->Instance->PSMAR, cfg->MatchValue);

      /* Configure XSPI: PSMKR register with the status mask value */
      WRITE_REG(hxspi->Instance->PSMKR, cfg->MatchMask);

      /* Configure XSPI: PIR register with the interval value */
      WRITE_REG(hxspi->Instance->PIR, cfg->IntervalTime);

      /* Configure XSPI: CR register with Match mode and Automatic stop mode */
      MODIFY_REG(hxspi->Instance->CR, (QUADSPI_CR_PMM | QUADSPI_CR_APMS),
                 (cfg->MatchMode | cfg->AutomaticStop));

      /* Clear interrupt */
      HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TE | XSPI_FLAG_SM);

      /* Call the configuration function */
      XSPI_Config(hxspi, &ConfigCmd, XSPI_FUNCTIONAL_MODE_AUTO_POLLING);

      /* Process unlocked */
      __HAL_UNLOCK(hxspi);

      /* Enable the XSPI Transfer Error and status match Interrupt */
      HAL_XSPI_ENABLE_IT(hxspi, (XSPI_IT_SM | XSPI_IT_TE));

    }
    else
    {
      /* Process unlocked */
      __HAL_UNLOCK(hxspi);
    }
  }
  else
  {
    status = HAL_BUSY;

    /* Process unlocked */
    __HAL_UNLOCK(hxspi);
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Configure the Memory Mapped mode.
  * @param  hxspi XSPI handle
  * @param  cfg structure that contains the memory mapped configuration information.
  * @note   This function is used only in Memory mapped Mode.
            XSPI_RegularCmdTypeDef ConfigCmd defined in hal_xspi.h needs to be populated by application code before
            invoking below APIs HAL_XSPI_MemoryMapped()
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_MemoryMapped(XSPI_HandleTypeDef *hxspi, XSPI_MemoryMappedTypeDef *cfg)
{
  HAL_StatusTypeDef status;
  uint32_t tickstart = HAL_GetTick();

  /* Renamed IS_XSPI_DUAL_FLASH_MODE to IS_XSPI_MEMORY_MODE for better compatibility with ExtMem Manager */
  assert_param(IS_XSPI_MEMORY_MODE(hxspi->Init.MemoryMode));

  if (hxspi->Init.MemoryMode != HAL_XSPI_DUAL_MEM)
  {
    assert_param(IS_XSPI_IO_SELECT(ConfigCmd.IOSelect));
    MODIFY_REG(hxspi->Instance->CR, QUADSPI_CR_FSEL, ConfigCmd.IOSelect);
  }

  assert_param(IS_XSPI_INSTRUCTION_MODE(ConfigCmd.InstructionMode));
  if (ConfigCmd.InstructionMode != XSPI_INSTRUCTION_NONE)
  {
    assert_param(IS_XSPI_INSTRUCTION(ConfigCmd.Instruction));
  }

  assert_param(IS_XSPI_ADDRESS_MODE(ConfigCmd.AddressMode));
  if (ConfigCmd.AddressMode != XSPI_ADDRESS_NONE)
  {
    /* Renamed IS_XSPI_ADDRESS_SIZE() to IS_XSPI_ADDRESS_WIDTH() for better compatibility with ExtMem Manager */
    assert_param(IS_XSPI_ADDRESS_WIDTH(ConfigCmd.AddressWidth));
  }

  assert_param(IS_XSPI_ALT_BYTES_MODE(ConfigCmd.AlternateByteMode));
  if (ConfigCmd.AlternateByteMode != XSPI_ALT_BYTES_NONE)
  {
    /* Renamed IS_XSPI_ALT_BYTES_SIZE() to IS_XSPI_ALT_BYTES_WIDTH() for better compatibility with
    ExtMem Manager */
    assert_param(IS_XSPI_ALT_BYTES_WIDTH(ConfigCmd.AlternateBytesWidth));
  }

  assert_param(IS_XSPI_DUMMY_CYCLES(ConfigCmd.DummyCycles));
  assert_param(IS_XSPI_DATA_MODE(ConfigCmd.DataMode));

  assert_param(IS_XSPI_DTR_MODE(ConfigCmd.DTRMode));
  assert_param(IS_XSPI_DHHC(ConfigCmd.DelayHoldHalfCycle));
  assert_param(IS_XSPI_SIOO_MODE(ConfigCmd.SIOOMode));

  assert_param(IS_XSPI_TIMEOUT_ACTIVATION(cfg->TimeOutActivation));

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    hxspi->ErrorCode = HAL_XSPI_ERROR_NONE;

    /* Update state */
    hxspi->State = HAL_XSPI_STATE_BUSY_MEM_MAPPED;

    /* Wait till BUSY flag reset */
    status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_BUSY, RESET, tickstart, hxspi->Timeout);

    if (status == HAL_OK)
    {
      /* Configure XSPI: CR register with timeout counter enable */
      MODIFY_REG(hxspi->Instance->CR, QUADSPI_CR_TCEN, cfg->TimeOutActivation);

      if (cfg->TimeOutActivation == XSPI_TIMEOUT_COUNTER_ENABLE)
      {
        assert_param(IS_XSPI_TIMEOUT_PERIOD(cfg->TimeoutPeriodClock));

        /* Configure XSPI: LPTR register with the low-power timeout value */
        WRITE_REG(hxspi->Instance->LPTR, cfg->TimeoutPeriodClock);

        /* Clear interrupt */
        HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TO);

        /* Enable the XSPI TimeOut Interrupt */
        HAL_XSPI_ENABLE_IT(hxspi, XSPI_IT_TO);
      }

      /* Call the configuration function */
      XSPI_Config(hxspi, &ConfigCmd, XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED);
    }
  }
  else
  {
    status = HAL_BUSY;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hxspi);

  /* Return function status */
  return status;
}

/**
  * @brief  Transfer Error callback.
  * @param  hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_ErrorCallback(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_XSPI_ErrorCallback could be implemented in the user file
   */
}

/**
  * @brief  Abort completed callback.
  * @param  hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_AbortCpltCallback(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_XSPI_AbortCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Command completed callback.
  * @param  hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_CmdCpltCallback(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_XSPI_CmdCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_RxCpltCallback(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_XSPI_RxCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Tx Transfer completed callback.
  * @param  hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_TxCpltCallback(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_XSPI_TxCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Rx Half Transfer completed callback.
  * @param  hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_RxHalfCpltCallback(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_XSPI_RxHalfCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Tx Half Transfer completed callback.
  * @param  hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_TxHalfCpltCallback(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_XSPI_TxHalfCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  FIFO Threshold callback.
  * @param  hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_FifoThresholdCallback(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_XSPI_FIFOThresholdCallback could be implemented in the user file
   */
}

/**
  * @brief  Status Match callback.
  * @param  hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_StatusMatchCallback(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_XSPI_StatusMatchCallback could be implemented in the user file
   */
}

/**
  * @brief  Timeout callback.
  * @param  hxspi XSPI handle
  * @retval None
  */
__weak void HAL_XSPI_TimeOutCallback(XSPI_HandleTypeDef *hxspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hxspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_XSPI_TimeOutCallback could be implemented in the user file
   */
}
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register a User XSPI Callback
  *         To be used instead of the weak (surcharged) predefined callback
  * @param hxspi XSPI handle
  * @param CallbackId ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_XSPI_ERROR_CB_ID          XSPI Error Callback ID
  *          @arg @ref HAL_XSPI_ABORT_CB_ID          XSPI Abort Callback ID
  *          @arg @ref HAL_XSPI_FIFO_THRESHOLD_CB_ID XSPI FIFO Threshold Callback ID
  *          @arg @ref HAL_XSPI_CMD_CPLT_CB_ID       XSPI Command Complete Callback ID
  *          @arg @ref HAL_XSPI_RX_CPLT_CB_ID        XSPI Rx Complete Callback ID
  *          @arg @ref HAL_XSPI_TX_CPLT_CB_ID        XSPI Tx Complete Callback ID
  *          @arg @ref HAL_XSPI_RX_HALF_CPLT_CB_ID   XSPI Rx Half Complete Callback ID
  *          @arg @ref HAL_XSPI_TX_HALF_CPLT_CB_ID   XSPI Tx Half Complete Callback ID
  *          @arg @ref HAL_XSPI_STATUS_MATCH_CB_ID   XSPI Status Match Callback ID
  *          @arg @ref HAL_XSPI_TIMEOUT_CB_ID        XSPI Timeout Callback ID
  *          @arg @ref HAL_XSPI_MSP_INIT_CB_ID       XSPI MspInit callback ID
  *          @arg @ref HAL_XSPI_MSP_DEINIT_CB_ID     XSPI MspDeInit callback ID
  * @param pCallback pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_XSPI_RegisterCallback(XSPI_HandleTypeDef *hxspi, HAL_XSPI_CallbackIDTypeDef CallbackId,
                                            pXSPI_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    switch (CallbackId)
    {
      case  HAL_XSPI_ERROR_CB_ID :
        hxspi->ErrorCallback = pCallback;
        break;
      case HAL_XSPI_ABORT_CB_ID :
        hxspi->AbortCpltCallback = pCallback;
        break;
      case HAL_XSPI_FIFO_THRESHOLD_CB_ID :
        hxspi->FifoThresholdCallback = pCallback;
        break;
      case HAL_XSPI_CMD_CPLT_CB_ID :
        hxspi->CmdCpltCallback = pCallback;
        break;
      case HAL_XSPI_RX_CPLT_CB_ID :
        hxspi->RxCpltCallback = pCallback;
        break;
      case HAL_XSPI_TX_CPLT_CB_ID :
        hxspi->TxCpltCallback = pCallback;
        break;
      case HAL_XSPI_RX_HALF_CPLT_CB_ID :
        hxspi->RxHalfCpltCallback = pCallback;
        break;
      case HAL_XSPI_TX_HALF_CPLT_CB_ID :
        hxspi->TxHalfCpltCallback = pCallback;
        break;
      case HAL_XSPI_STATUS_MATCH_CB_ID :
        hxspi->StatusMatchCallback = pCallback;
        break;
      case HAL_XSPI_TIMEOUT_CB_ID :
        hxspi->TimeOutCallback = pCallback;
        break;
      case HAL_XSPI_MSP_INIT_CB_ID :
        hxspi->MspInitCallback = pCallback;
        break;
      case HAL_XSPI_MSP_DEINIT_CB_ID :
        hxspi->MspDeInitCallback = pCallback;
        break;
      default :
        /* Update the error code */
        hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hxspi->State == HAL_XSPI_STATE_RESET)
  {
    switch (CallbackId)
    {
      case HAL_XSPI_MSP_INIT_CB_ID :
        hxspi->MspInitCallback = pCallback;
        break;
      case HAL_XSPI_MSP_DEINIT_CB_ID :
        hxspi->MspDeInitCallback = pCallback;
        break;
      default :
        /* Update the error code */
        hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_CALLBACK;
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hxspi);
  return status;
}

/**
  * @brief  Unregister a User XSPI Callback
  *         XSPI Callback is redirected to the weak (surcharged) predefined callback
  * @param hxspi XSPI handle
  * @param CallbackId ID of the callback to be unregistered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_XSPI_ERROR_CB_ID          XSPI Error Callback ID
  *          @arg @ref HAL_XSPI_ABORT_CB_ID          XSPI Abort Callback ID
  *          @arg @ref HAL_XSPI_FIFO_THRESHOLD_CB_ID XSPI FIFO Threshold Callback ID
  *          @arg @ref HAL_XSPI_CMD_CPLT_CB_ID       XSPI Command Complete Callback ID
  *          @arg @ref HAL_XSPI_RX_CPLT_CB_ID        XSPI Rx Complete Callback ID
  *          @arg @ref HAL_XSPI_TX_CPLT_CB_ID        XSPI Tx Complete Callback ID
  *          @arg @ref HAL_XSPI_RX_HALF_CPLT_CB_ID   XSPI Rx Half Complete Callback ID
  *          @arg @ref HAL_XSPI_TX_HALF_CPLT_CB_ID   XSPI Tx Half Complete Callback ID
  *          @arg @ref HAL_XSPI_STATUS_MATCH_CB_ID   XSPI Status Match Callback ID
  *          @arg @ref HAL_XSPI_TIMEOUT_CB_ID        XSPI Timeout Callback ID
  *          @arg @ref HAL_XSPI_MSP_INIT_CB_ID       XSPI MspInit callback ID
  *          @arg @ref HAL_XSPI_MSP_DEINIT_CB_ID     XSPI MspDeInit callback ID
  * @retval status
  */
HAL_StatusTypeDef HAL_XSPI_UnRegisterCallback(XSPI_HandleTypeDef *hxspi, HAL_XSPI_CallbackIDTypeDef CallbackId)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    switch (CallbackId)
    {
      case  HAL_XSPI_ERROR_CB_ID :
        hxspi->ErrorCallback = HAL_XSPI_ErrorCallback;
        break;
      case HAL_XSPI_ABORT_CB_ID :
        hxspi->AbortCpltCallback = HAL_XSPI_AbortCpltCallback;
        break;
      case HAL_XSPI_FIFO_THRESHOLD_CB_ID :
        hxspi->FifoThresholdCallback = HAL_XSPI_FifoThresholdCallback;
        break;
      case HAL_XSPI_CMD_CPLT_CB_ID :
        hxspi->CmdCpltCallback = HAL_XSPI_CmdCpltCallback;
        break;
      case HAL_XSPI_RX_CPLT_CB_ID :
        hxspi->RxCpltCallback = HAL_XSPI_RxCpltCallback;
        break;
      case HAL_XSPI_TX_CPLT_CB_ID :
        hxspi->TxCpltCallback = HAL_XSPI_TxCpltCallback;
        break;
      case HAL_XSPI_RX_HALF_CPLT_CB_ID :
        hxspi->RxHalfCpltCallback = HAL_XSPI_RxHalfCpltCallback;
        break;
      case HAL_XSPI_TX_HALF_CPLT_CB_ID :
        hxspi->TxHalfCpltCallback = HAL_XSPI_TxHalfCpltCallback;
        break;
      case HAL_XSPI_STATUS_MATCH_CB_ID :
        hxspi->StatusMatchCallback = HAL_XSPI_StatusMatchCallback;
        break;
      case HAL_XSPI_TIMEOUT_CB_ID :
        hxspi->TimeOutCallback = HAL_XSPI_TimeOutCallback;
        break;
      case HAL_XSPI_MSP_INIT_CB_ID :
        hxspi->MspInitCallback = HAL_XSPI_MspInit;
        break;
      case HAL_XSPI_MSP_DEINIT_CB_ID :
        hxspi->MspDeInitCallback = HAL_XSPI_MspDeInit;
        break;
      default :
        /* Update the error code */
        hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hxspi->State == HAL_XSPI_STATE_RESET)
  {
    switch (CallbackId)
    {
      case HAL_XSPI_MSP_INIT_CB_ID :
        hxspi->MspInitCallback = HAL_XSPI_MspInit;
        break;
      case HAL_XSPI_MSP_DEINIT_CB_ID :
        hxspi->MspDeInitCallback = HAL_XSPI_MspDeInit;
        break;
      default :
        /* Update the error code */
        hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hxspi->ErrorCode |= HAL_XSPI_ERROR_INVALID_CALLBACK;
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hxspi);
  return status;
}
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */

/**
  * @}
  */

/** @defgroup XSPI_Exported_Functions_Group3 Peripheral Control and State functions
  *  @brief   XSPI control and State functions
  *
@verbatim
 ===============================================================================
                  ##### Peripheral Control and State functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to :
      (+) Check in run-time the state of the driver.
      (+) Check the error code set during last operation.
      (+) Abort any operation.


@endverbatim
  * @{
  */

/**
  * @brief  Return the XSPI handle state.
  * @param  hxspi XSPI handle
  * @retval HAL state
  */
uint32_t HAL_XSPI_GetState(const XSPI_HandleTypeDef *hxspi)
{
  /* Return XSPI handle state */
  return hxspi->State;
}

/**
  * @brief  Return the XSPI error code.
  * @param  hxspi XSPI handle
  * @retval XSPI Error Code
  */
uint32_t HAL_XSPI_GetError(const XSPI_HandleTypeDef *hxspi)
{
  return hxspi->ErrorCode;
}

/**
  * @brief  Abort the current transmission.
  * @param  hxspi XSPI handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Abort(XSPI_HandleTypeDef *hxspi)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tickstart = HAL_GetTick();

  /* Check if the state is in one of the busy states */
  if (((uint32_t)hxspi->State & 0x2U) != 0U)
  {
    /* Process unlocked */
    __HAL_UNLOCK(hxspi);

    if ((hxspi->Instance->CR & QUADSPI_CR_DMAEN) != 0U)
    {
      /* Disable the DMA transfer by clearing the DMAEN bit in the XSPI CR register */
      CLEAR_BIT(hxspi->Instance->CR, QUADSPI_CR_DMAEN);

      /* Abort MDMA */
      status = HAL_MDMA_Abort(hxspi->hmdma);
      if (status != HAL_OK)
      {
        hxspi->ErrorCode |= HAL_XSPI_ERROR_DMA;
      }
    }

    if (HAL_XSPI_GET_FLAG(hxspi, XSPI_FLAG_BUSY) != RESET)
    {
      /* Configure XSPI: CR register with Abort request */
      SET_BIT(hxspi->Instance->CR, QUADSPI_CR_ABORT);

      /* Wait until TC flag is set to go back in idle state */
      status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_TC, SET, tickstart, hxspi->Timeout);

      if (status == HAL_OK)
      {
        HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TC);

        /* Wait until BUSY flag is reset */
        status = XSPI_WaitFlagStateUntilTimeout(hxspi, XSPI_FLAG_BUSY, RESET, tickstart, hxspi->Timeout);
      }

      if (status == HAL_OK)
      {
        /* Reset functional mode configuration to indirect write mode by default */
        CLEAR_BIT(hxspi->Instance->CCR, QUADSPI_CCR_FMODE);

        /* Update state */
        hxspi->State = HAL_XSPI_STATE_READY;
      }
    }
    else
    {
      /* Update state */
      hxspi->State = HAL_XSPI_STATE_READY;
    }
  }

  return status;
}

/**
  * @brief  Abort the current transmission (non-blocking function)
  * @param  hxspi XSPI handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_Abort_IT(XSPI_HandleTypeDef *hxspi)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check if the state is in one of the busy states */
  if (((uint32_t)hxspi->State & 0x2U) != 0U)
  {
    /* Process unlocked */
    __HAL_UNLOCK(hxspi);

    /* Update XSPI state */
    hxspi->State = HAL_XSPI_STATE_ABORT;

    /* Disable all interrupts */
    HAL_XSPI_DISABLE_IT(hxspi, (XSPI_IT_TO | XSPI_IT_SM | XSPI_IT_FT | XSPI_IT_TC | XSPI_IT_TE));

    if ((hxspi->Instance->CR & QUADSPI_CR_DMAEN) != 0U)
    {
      /* Disable the DMA transfer by clearing the DMAEN bit in the XSPI CR register */
      CLEAR_BIT(hxspi->Instance->CR, QUADSPI_CR_DMAEN);

      /* Abort MDMA channel */
      hxspi->hmdma->XferAbortCallback = XSPI_DMAAbortCplt;
      if (HAL_MDMA_Abort_IT(hxspi->hmdma) != HAL_OK)
      {
        /* Change state of XSPI */
        hxspi->State = HAL_XSPI_STATE_READY;

        /* Abort Complete callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
        hxspi->AbortCpltCallback(hxspi);
#else
        HAL_XSPI_AbortCpltCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
      }
    }
    else
    {
      if (HAL_XSPI_GET_FLAG(hxspi, XSPI_FLAG_BUSY) != RESET)
      {
        /* Clear interrupt */
        HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TC);

        /* Enable the XSPI Transfer Complete Interrupt */
        HAL_XSPI_ENABLE_IT(hxspi, XSPI_IT_TC);

        /* Configure XSPI: CR register with Abort request */
        SET_BIT(hxspi->Instance->CR, QUADSPI_CR_ABORT);
      }
      else
      {
        /* Change state of XSPI */
        hxspi->State = HAL_XSPI_STATE_READY;
      }
    }
  }
  return status;
}

/** @brief Set XSPI timeout.
  * @param  hxspi XSPI handle.
  * @param  Timeout Timeout for the XSPI memory access.
  * @retval None
  */
void HAL_XSPI_SetTimeout(XSPI_HandleTypeDef *hxspi, uint32_t Timeout)
{
  hxspi->Timeout = Timeout;
}

/** @brief Set XSPI Fifo threshold.
  * @param  hxspi XSPI handle.
  * @param  Threshold Threshold of the Fifo (value between 1 and 16).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_XSPI_SetFifoThreshold(XSPI_HandleTypeDef *hxspi, uint32_t Threshold)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hxspi);

  if (hxspi->State == HAL_XSPI_STATE_READY)
  {
    /* Synchronize init structure with new FIFO threshold value */
    /* Renamed FifoThreshold to FifoThresholdByte for better compatibility with ExtMem Manager for future
    integration */
    hxspi->Init.FifoThresholdByte = Threshold;

    /* Configure XSPI FIFO Threshold */
    MODIFY_REG(hxspi->Instance->CR, QUADSPI_CR_FTHRES,
               ((hxspi->Init.FifoThresholdByte - 1U) << QUADSPI_CR_FTHRES_Pos));
  }
  else
  {
    status = HAL_BUSY;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hxspi);

  /* Return function status */
  return status;
}

/** @brief Get XSPI Fifo threshold.
  * @param  hxspi XSPI handle.
  * @retval Fifo threshold (value between 1 and 16)
  */
uint32_t HAL_XSPI_GetFifoThreshold(const XSPI_HandleTypeDef *hxspi)
{
  return ((READ_BIT(hxspi->Instance->CR, QUADSPI_CR_FTHRES) >> QUADSPI_CR_FTHRES_Pos) + 1U);
}

/**
  * @}
  */

/** @defgroup XSPI_Private_Functions XSPI Private Functions
  * @{
  */

/**
  * @brief  DMA XSPI receive process complete callback.
  * @param  hmdma MDMA handle
  * @retval None
  */
static void XSPI_DMARxCplt(MDMA_HandleTypeDef *hmdma)
{
  XSPI_HandleTypeDef *hxspi = (XSPI_HandleTypeDef *)(hmdma->Parent);
  hxspi->XferCount = 0U;

  /* Enable the XSPI transfer complete Interrupt */
  HAL_XSPI_ENABLE_IT(hxspi, XSPI_IT_TC);
}

/**
  * @brief  DMA XSPI transmit process complete callback.
  * @param  hmdma MDMA handle
  * @retval None
  */
static void XSPI_DMATxCplt(MDMA_HandleTypeDef *hmdma)
{
  XSPI_HandleTypeDef *hxspi = (XSPI_HandleTypeDef *)(hmdma->Parent);
  hxspi->XferCount = 0U;

  /* Enable the XSPI transfer complete Interrupt */
  HAL_XSPI_ENABLE_IT(hxspi, XSPI_IT_TC);
}

/**
  * @brief  DMA XSPI communication error callback.
  * @param  hmdma MDMA handle
  * @retval None
  */
static void XSPI_DMAError(MDMA_HandleTypeDef *hmdma)
{
  XSPI_HandleTypeDef *hxspi = (XSPI_HandleTypeDef *)(hmdma->Parent);

  hxspi->XferCount = 0U;
  hxspi->XferCount = 0U;
  hxspi->ErrorCode   |= HAL_XSPI_ERROR_DMA;

  /* Disable the MDMA transfer by clearing the DMAEN bit in the XSPI CR register */
  CLEAR_BIT(hxspi->Instance->CR, QUADSPI_CR_DMAEN);

  /* Abort the XSPI */
  (void)HAL_XSPI_Abort_IT(hxspi);

}

/**
  * @brief  MDMA XSPI abort complete callback.
  * @param  hmdma MDMA handle
  * @retval None
  */
static void XSPI_DMAAbortCplt(MDMA_HandleTypeDef *hmdma)
{
  XSPI_HandleTypeDef *hxspi = (XSPI_HandleTypeDef *)(hmdma->Parent);

  hxspi->XferCount = 0U;
  hxspi->XferCount = 0U;

  if (hxspi->State == HAL_XSPI_STATE_ABORT)
  {
    /* MDMA Abort called by XSPI abort */
    /* Clear interrupt */
    HAL_XSPI_CLEAR_FLAG(hxspi, XSPI_FLAG_TC);

    /* Enable the XSPI Transfer Complete Interrupt */
    HAL_XSPI_ENABLE_IT(hxspi, XSPI_IT_TC);

    /* Configure XSPI: CR register with Abort request */
    SET_BIT(hxspi->Instance->CR, QUADSPI_CR_ABORT);
  }
  else
  {
    /* MDMA Abort called due to a transfer error interrupt */
    /* Change state of XSPI */
    hxspi->State = HAL_XSPI_STATE_READY;

    /* Error callback */
#if defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U)
    hxspi->ErrorCallback(hxspi);
#else
    HAL_XSPI_ErrorCallback(hxspi);
#endif /* defined (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1U) */
  }
}

/**
  * @brief  Wait for a flag state until timeout.
  * @param  hxspi XSPI handle
  * @param  Flag Flag checked
  * @param  State Value of the flag expected
  * @param  Tickstart Tick start value
  * @param  Timeout Duration of the timeout
  * @retval HAL status
  */
static HAL_StatusTypeDef XSPI_WaitFlagStateUntilTimeout(XSPI_HandleTypeDef *hxspi, uint32_t Flag,
                                                        FlagStatus State, uint32_t Tickstart, uint32_t Timeout)
{
  /* Wait until flag is in expected state */
  while ((HAL_XSPI_GET_FLAG(hxspi, Flag)) != State)
  {
    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
      {
        hxspi->State     = HAL_XSPI_STATE_ERROR;
        hxspi->ErrorCode |= HAL_XSPI_ERROR_TIMEOUT;

        return HAL_ERROR;
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief  Configure the communication registers.
  * @param  hxspi XSPI handle
  * @param  cmd structure that contains the command configuration information
  * @param  FunctionalMode functional mode to configured
  *           This parameter can be one of the following values:
  *            @arg XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE: Indirect write mode
  *            @arg XSPI_FUNCTIONAL_MODE_INDIRECT_READ: Indirect read mode
  *            @arg XSPI_FUNCTIONAL_MODE_AUTO_POLLING: Automatic polling mode
  *            @arg XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED: Memory-mapped mode
  * @retval None
  */
static void XSPI_Config(XSPI_HandleTypeDef *hxspi, XSPI_RegularCmdTypeDef *cmd, uint32_t FunctionalMode)
{
  assert_param(IS_XSPI_FUNCTIONAL_MODE(FunctionalMode));

  if ((cmd->DataMode != XSPI_DATA_NONE) && (FunctionalMode != XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED))
  {
    /* Configure XSPI: DLR register with the number of data to read or write */
    WRITE_REG(hxspi->Instance->DLR, (cmd->DataLength - 1U));
  }

  if (cmd->InstructionMode != XSPI_INSTRUCTION_NONE)
  {
    if (cmd->AlternateByteMode != XSPI_ALT_BYTES_NONE)
    {
      /* Configure XSPI: ABR register with alternate bytes value */
      WRITE_REG(hxspi->Instance->ABR, cmd->AlternateBytes);

      if (cmd->AddressMode != XSPI_ADDRESS_NONE)
      {
        /*---- Command with instruction, address and alternate bytes ----*/
        /* Configure XSPI: CCR register with all communications parameters */
        WRITE_REG(hxspi->Instance->CCR, (cmd->DTRMode | cmd->DelayHoldHalfCycle | cmd->SIOOMode |
                                         cmd->DataMode | (cmd->DummyCycles << QUADSPI_CCR_DCYC_Pos) |
                                         cmd->AlternateBytesWidth | cmd->AlternateByteMode |
                                         cmd->AddressWidth | cmd->AddressMode | cmd->InstructionMode |
                                         cmd->Instruction | FunctionalMode));

        if (FunctionalMode != XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED)
        {
          /* Configure XSPI: AR register with address value */
          WRITE_REG(hxspi->Instance->AR, cmd->Address);
        }
      }
      else
      {
        /*---- Command with instruction and alternate bytes ----*/
        /* Configure XSPI: CCR register with all communications parameters */
        WRITE_REG(hxspi->Instance->CCR, (cmd->DTRMode | cmd->DelayHoldHalfCycle | cmd->SIOOMode |
                                         cmd->DataMode | (cmd->DummyCycles << QUADSPI_CCR_DCYC_Pos) |
                                         cmd->AlternateBytesWidth | cmd->AlternateByteMode |
                                         cmd->AddressMode | cmd->InstructionMode |
                                         cmd->Instruction | FunctionalMode));
      }
    }
    else
    {
      if (cmd->AddressMode != XSPI_ADDRESS_NONE)
      {
        /*---- Command with instruction and address ----*/
        /* Configure XSPI: CCR register with all communications parameters */
        WRITE_REG(hxspi->Instance->CCR, (cmd->DTRMode | cmd->DelayHoldHalfCycle | cmd->SIOOMode |
                                         cmd->DataMode | (cmd->DummyCycles << QUADSPI_CCR_DCYC_Pos) |
                                         cmd->AlternateByteMode | cmd->AddressWidth | cmd->AddressMode |
                                         cmd->InstructionMode | cmd->Instruction | FunctionalMode));

        if (FunctionalMode != XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED)
        {
          /* Configure XSPI: AR register with address value */
          WRITE_REG(hxspi->Instance->AR, cmd->Address);
        }
      }
      else
      {
        /*---- Command with only instruction ----*/
        /* Configure XSPI: CCR register with all communications parameters */
        WRITE_REG(hxspi->Instance->CCR, (cmd->DTRMode | cmd->DelayHoldHalfCycle | cmd->SIOOMode |
                                         cmd->DataMode | (cmd->DummyCycles << QUADSPI_CCR_DCYC_Pos) |
                                         cmd->AlternateByteMode | cmd->AddressMode |
                                         cmd->InstructionMode | cmd->Instruction | FunctionalMode));
      }
    }
  }
  else
  {
    if (cmd->AlternateByteMode != XSPI_ALT_BYTES_NONE)
    {
      /* Configure XSPI: ABR register with alternate bytes value */
      WRITE_REG(hxspi->Instance->ABR, cmd->AlternateBytes);

      if (cmd->AddressMode != XSPI_ADDRESS_NONE)
      {
        /*---- Command with address and alternate bytes ----*/
        /* Configure XSPI: CCR register with all communications parameters */
        WRITE_REG(hxspi->Instance->CCR, (cmd->DTRMode | cmd->DelayHoldHalfCycle | cmd->SIOOMode |
                                         cmd->DataMode | (cmd->DummyCycles << QUADSPI_CCR_DCYC_Pos) |
                                         cmd->AlternateBytesWidth | cmd->AlternateByteMode |
                                         cmd->AddressWidth | cmd->AddressMode |
                                         cmd->InstructionMode | FunctionalMode));

        if (FunctionalMode != XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED)
        {
          /* Configure XSPI: AR register with address value */
          WRITE_REG(hxspi->Instance->AR, cmd->Address);
        }
      }
      else
      {
        /*---- Command with only alternate bytes ----*/
        /* Configure XSPI: CCR register with all communications parameters */
        WRITE_REG(hxspi->Instance->CCR, (cmd->DTRMode | cmd->DelayHoldHalfCycle | cmd->SIOOMode |
                                         cmd->DataMode | (cmd->DummyCycles << QUADSPI_CCR_DCYC_Pos) |
                                         cmd->AlternateBytesWidth | cmd->AlternateByteMode |
                                         cmd->AddressMode | cmd->InstructionMode | FunctionalMode));
      }
    }
    else
    {
      if (cmd->AddressMode != XSPI_ADDRESS_NONE)
      {
        /*---- Command with only address ----*/
        /* Configure XSPI: CCR register with all communications parameters */
        WRITE_REG(hxspi->Instance->CCR, (cmd->DTRMode | cmd->DelayHoldHalfCycle | cmd->SIOOMode |
                                         cmd->DataMode | (cmd->DummyCycles << QUADSPI_CCR_DCYC_Pos) |
                                         cmd->AlternateByteMode | cmd->AddressWidth |
                                         cmd->AddressMode | cmd->InstructionMode | FunctionalMode));

        if (FunctionalMode != XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED)
        {
          /* Configure XSPI: AR register with address value */
          WRITE_REG(hxspi->Instance->AR, cmd->Address);
        }
      }
      else
      {
        /*---- Command with only data phase ----*/
        if (cmd->DataMode != XSPI_DATA_NONE)
        {
          /* Configure XSPI: CCR register with all communications parameters */
          WRITE_REG(hxspi->Instance->CCR, (cmd->DTRMode | cmd->DelayHoldHalfCycle | cmd->SIOOMode |
                                           cmd->DataMode | (cmd->DummyCycles << QUADSPI_CCR_DCYC_Pos) |
                                           cmd->AlternateByteMode | cmd->AddressMode |
                                           cmd->InstructionMode | FunctionalMode));
        }
      }
    }
  }
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_XSPI_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(XSPI) */
