/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_ipcc.c
  * @author  MCD Application Team
  * @brief   IPCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Inter-Processor communication controller
  *          peripherals (IPCC).
  *           + Initialization and de-initialization functions
  *           + Configuration, notification and interrupts handling
  *           + Peripheral State and Error functions
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
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
      The IPCC HAL driver can be used as follows:

      (#) Declare a IPCC_HandleTypeDef handle structure, for example: IPCC_HandleTypeDef hipcc;
      (#) Initialize the IPCC low level resources by implementing the HAL_IPCC_MspInit() API:
        (##) Enable the IPCC interface clock
        (##) NVIC configuration if you need to use interrupt process
            (+++) Configure the IPCC interrupt priority
            (+++) Enable the NVIC IPCC IRQ

      (#) Initialize the IPCC registers by calling the HAL_IPCC_Init() API which trig
          HAL_IPCC_MspInit().

      (#) Implement the interrupt callbacks for transmission and reception to use the driver in interrupt mode

      (#) Associate those callback to the corresponding channel and direction using HAL_IPCC_ConfigChannel().
          This is the interrupt mode.
          If no callback are configured for a given channel and direction, it is up to the user to poll the
          status of the communication (polling mode).

      (#) Notify the other MCU when a message is available in a chosen channel
          or when a message has been retrieved from a chosen channel by calling
          the HAL_IPCC_NotifyCPU() API.

@endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

#if defined(IPCC) || defined(IPCC1) || defined(IPCC2)
/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup IPCC
  * @{
  */

#ifdef HAL_IPCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup IPCC_Private_Constants IPCC Private Constants
  * @{
  */
#define CHANNEL_INDEX_MSK 0x0000000FU /*!< Mask the channel index to avoid overflow */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
#define IPCC_ALL_RX_BUF (((1UL << hipcc->channelNumber) - 1U) << IPCC_C1MR_CH1OM_Pos)
#define IPCC_ALL_TX_BUF (((1UL << hipcc->channelNumber) - 1U) << IPCC_C1MR_CH1FM_Pos)
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup IPCC_Private_Functions IPCC Private Functions
  * @{
  */
void IPCC_MaskInterrupt(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir);
void IPCC_UnmaskInterrupt(const IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir);
void IPCC_SetDefaultCallbacks(IPCC_HandleTypeDef *hipcc);
void IPCC_Reset_Register(IPCC_HandleTypeDef *hipcc);
IPCC_CommonTypeDef *IPCC_GetCurrentInstance(const IPCC_HandleTypeDef *hipcc);
IPCC_CommonTypeDef *IPCC_GetOtherInstance(const IPCC_HandleTypeDef *hipcc);
/**
  * @}
  */

/** @addtogroup IPCC_Exported_Functions
  * @{
  */

/** @addtogroup IPCC_Exported_Functions_Group1
  *  @brief    Initialization and de-initialization functions
  *
@verbatim
 ===============================================================================
             ##### Initialization and de-initialization functions  #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          deinitialize the IPCC peripheral:

      (+) User must Implement HAL_IPCC_MspInit() function in which he configures
          all related peripherals resources (CLOCK and NVIC ).

      (+) Call the function HAL_IPCC_Init() to configure the IPCC register.

      (+) Call the function HAL_PKA_DeInit() to restore the default configuration
          of the selected IPCC peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the IPCC peripheral.
  * @param  hipcc IPCC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IPCC_Init(IPCC_HandleTypeDef *hipcc)
{
  HAL_StatusTypeDef err = HAL_OK;

  /* Check the IPCC handle allocation */
  if (hipcc != NULL)
  {
    /* Check the parameters */
    assert_param(IS_IPCC_ALL_INSTANCE(hipcc->Instance));
    IPCC_CommonTypeDef *currentInstance = IPCC_GetCurrentInstance(hipcc);

    if (hipcc->State == HAL_IPCC_STATE_RESET)
    {
      /* Init the low level hardware : CLOCK, NVIC */
      HAL_IPCC_MspInit(hipcc);
    }

    /* Set the number of available channels */
    hipcc->channelNumber = (hipcc->Instance->HWCFGR & IPCC_HWCFGR_CHANNELS) >> IPCC_HWCFGR_CHANNELS_Pos;

    /* Reset all registers of the current cpu to default state */
    IPCC_Reset_Register(hipcc);

    /* Activate the interrupts */
    currentInstance->CR |= (IPCC_CR_RXOIE | IPCC_CR_TXFIE);

    /* Clear callback pointers */
    IPCC_SetDefaultCallbacks(hipcc);

    /* Reset all callback notification request */
    hipcc->callbackRequest = 0;

    hipcc->State = HAL_IPCC_STATE_READY;
  }
  else
  {
    err = HAL_ERROR;
  }

  return err;
}

/**
  * @brief  DeInitialize the IPCC peripheral.
  * @param  hipcc IPCC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IPCC_DeInit(IPCC_HandleTypeDef *hipcc)
{
  HAL_StatusTypeDef err = HAL_OK;

  /* Check the IPCC handle allocation */
  if (hipcc != NULL)
  {
    assert_param(IS_IPCC_ALL_INSTANCE(hipcc->Instance));

    /* Set the state to busy */
    hipcc->State = HAL_IPCC_STATE_BUSY;

    /* Reset all registers of the current cpu to default state */
    IPCC_Reset_Register(hipcc);

    /* Clear callback pointers */
    IPCC_SetDefaultCallbacks(hipcc);

    /* Reset all callback notification request */
    hipcc->callbackRequest = 0;

    /* Reset the number of available channels */
    hipcc->channelNumber = 0;

    /* DeInit the low level hardware : CLOCK, NVIC */
    HAL_IPCC_MspDeInit(hipcc);

    hipcc->State = HAL_IPCC_STATE_RESET;
  }
  else
  {
    err = HAL_ERROR;
  }

  return err;
}

/**
  * @brief Initialize the IPCC MSP.
  * @param  hipcc IPCC handle
  * @retval None
  */
__weak void HAL_IPCC_MspInit(IPCC_HandleTypeDef *hipcc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hipcc);

  /* NOTE : This function should not be modified. When the callback is needed
            the HAL_IPCC_MspInit should be implemented in the user file
   */
}

/**
  * @brief IPCC MSP DeInit
  * @param  hipcc IPCC handle
  * @retval None
  */
__weak void HAL_IPCC_MspDeInit(IPCC_HandleTypeDef *hipcc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hipcc);

  /* NOTE : This function should not be modified. When the callback is needed
            the HAL_IPCC_MspDeInit should be implemented in the user file
   */
}

/**
  * @}
  */


/** @addtogroup IPCC_Exported_Functions_Group2
  *  @brief    Configuration, notification and Irq handling functions.
  *
@verbatim
 ===============================================================================
              ##### IO operation functions #####
 ===============================================================================
    [..]  This section provides functions to allow two MCU to communicate.

    (#) For a given channel (IPCC_CHANNEL_NUMBER_nn), for a given direction
        IPCC_CHANNEL_DIR_TX or IPCC_CHANNEL_DIR_RX, you can choose to communicate
        in polling mode or in interrupt mode using IPCC.
        By default, the IPCC HAL driver handle the communication in polling mode.
        By setting a callback for a channel/direction, this communication use
        the interrupt mode.

    (#) Polling mode:
       (++) To transmit information, use HAL_IPCC_NotifyCPU() with
            IPCC_CHANNEL_DIR_TX. To know when the other processor has handled
            the notification, poll the communication using HAL_IPCC_NotifyCPU
            with IPCC_CHANNEL_DIR_TX.

       (++) To receive information, poll the status of the communication with
            HAL_IPCC_GetChannelStatus with IPCC_CHANNEL_DIR_RX. To notify the other
            processor that the information has been received, use HAL_IPCC_NotifyCPU
            with IPCC_CHANNEL_DIR_RX.

    (#) Interrupt mode:
       (++) Configure a callback for the channel and the direction using HAL_IPCC_ConfigChannel().
            This callback will be triggered under interrupt.

       (++) To transmit information, use HAL_IPCC_NotifyCPU() with
            IPCC_CHANNEL_DIR_TX. The callback configured with HAL_IPCC_ConfigChannel() and
            IPCC_CHANNEL_DIR_TX will be triggered once the communication has been handled by the
            other processor.

       (++) To receive information, the callback configured with HAL_IPCC_ConfigChannel() and
            IPCC_CHANNEL_DIR_RX will be triggered on reception of a communication.To notify the other
            processor that the information has been received, use HAL_IPCC_NotifyCPU
            with IPCC_CHANNEL_DIR_RX.

       (++) HAL_IPCC_TX_IRQHandler must be added to the IPCC TX IRQHandler

       (++) HAL_IPCC_RX_IRQHandler must be added to the IPCC RX IRQHandler
@endverbatim
  * @{
  */

/**
  * @brief  Activate the callback notification on receive/transmit interrupt
  * @param  hipcc IPCC handle
  * @param  ChannelIndex Channel number
  *          This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  * @param  ChannelDir Channel direction
  * @param  cb Interrupt callback
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IPCC_ActivateNotification(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex,
                                                IPCC_CHANNELDirTypeDef ChannelDir, ChannelCb cb)
{
  HAL_StatusTypeDef err = HAL_OK;

  /* Check the IPCC handle allocation and the ChannelIndex */
  if ((hipcc != NULL) && (ChannelIndex < hipcc->channelNumber))
  {
    /* Check the parameters */
    assert_param(IS_IPCC_ALL_INSTANCE(hipcc->Instance));

    /* Check IPCC state */
    if (hipcc->State == HAL_IPCC_STATE_READY)
    {
      /* Set callback and register masking information */
      if (ChannelDir == IPCC_CHANNEL_DIR_TX)
      {
        hipcc->ChannelCallbackTx[ChannelIndex] = cb;
        hipcc->callbackRequest |= ((uint32_t)IPCC_MR_CH1FM_Msk << (ChannelIndex & CHANNEL_INDEX_MSK));
      }
      else
      {
        hipcc->ChannelCallbackRx[ChannelIndex] = cb;
        hipcc->callbackRequest |= ((uint32_t)IPCC_MR_CH1OM_Msk << (ChannelIndex & CHANNEL_INDEX_MSK));
      }

      /* Unmask only the channels in reception (Transmission channel mask/unmask is done in HAL_IPCC_NotifyCPU) */
      if (ChannelDir == IPCC_CHANNEL_DIR_RX)
      {
        IPCC_UnmaskInterrupt(hipcc, ChannelIndex, ChannelDir);
      }
    }
    else
    {
      err = HAL_ERROR;
    }
  }
  else
  {
    err = HAL_ERROR;
  }
  return err;
}

/**
  * @brief  Remove the callback notification on receive/transmit interrupt
  * @param  hipcc IPCC handle
  * @param  ChannelIndex Channel number
  *          This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  * @param  ChannelDir Channel direction
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IPCC_DeActivateNotification(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex,
                                                  IPCC_CHANNELDirTypeDef ChannelDir)
{
  HAL_StatusTypeDef err = HAL_OK;

  /* Check the IPCC handle allocation and the ChannelIndex */
  if ((hipcc != NULL) && (ChannelIndex < hipcc->channelNumber))
  {
    /* Check the parameters */
    assert_param(IS_IPCC_ALL_INSTANCE(hipcc->Instance));

    /* Check IPCC state */
    if (hipcc->State == HAL_IPCC_STATE_READY)
    {
      /* Set default callback and register masking information */
      if (ChannelDir == IPCC_CHANNEL_DIR_TX)
      {
        hipcc->ChannelCallbackTx[ChannelIndex] = HAL_IPCC_TxCallback;
        hipcc->callbackRequest &= ~(IPCC_MR_CH1FM_Msk << (ChannelIndex & CHANNEL_INDEX_MSK));
      }
      else
      {
        hipcc->ChannelCallbackRx[ChannelIndex] = HAL_IPCC_RxCallback;
        hipcc->callbackRequest &= ~(IPCC_MR_CH1OM_Msk << (ChannelIndex & CHANNEL_INDEX_MSK));
      }

      /* Mask the interrupt */
      IPCC_MaskInterrupt(hipcc, ChannelIndex, ChannelDir);
    }
    else
    {
      err = HAL_ERROR;
    }
  }
  else
  {
    err = HAL_ERROR;
  }
  return err;
}

/**
  * @brief  Get state of IPCC channel
  * @param  hipcc IPCC handle
  * @param  ChannelIndex Channel number
  *          This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  * @param  ChannelDir Channel direction
  * @retval Channel status
  */
IPCC_CHANNELStatusTypeDef HAL_IPCC_GetChannelStatus(IPCC_HandleTypeDef const *const hipcc, uint32_t ChannelIndex,
                                                    IPCC_CHANNELDirTypeDef ChannelDir)
{
  uint32_t channel_state;
  IPCC_CHANNELStatusTypeDef status;

  /* Check the IPCC handle allocation and the ChannelIndex */
  if ((hipcc != NULL) && (ChannelIndex < hipcc->channelNumber))
  {
    /* Check the parameters */
    assert_param(IS_IPCC_ALL_INSTANCE(hipcc->Instance));
    __I IPCC_CommonTypeDef *currentInstance = IPCC_GetCurrentInstance(hipcc);
    __I IPCC_CommonTypeDef *otherInstance = IPCC_GetOtherInstance(hipcc);

    /* Read corresponding channel depending of the MCU and the direction */
    if (ChannelDir == IPCC_CHANNEL_DIR_TX)
    {
      channel_state = (currentInstance->SR) & ((uint32_t)IPCC_SR_CH1F_Msk << (ChannelIndex & CHANNEL_INDEX_MSK));
    }
    else
    {
      channel_state = (otherInstance->SR) & ((uint32_t)IPCC_SR_CH1F_Msk << (ChannelIndex & CHANNEL_INDEX_MSK));
    }
    status = (channel_state == 0UL) ? IPCC_CHANNEL_STATUS_FREE : IPCC_CHANNEL_STATUS_OCCUPIED;
  }
  else
  {
    status = IPCC_CHANNEL_STATUS_ERROR;
  }

  return status;
}

/**
  * @brief  Notify remote processor
  * @param  hipcc IPCC handle
  * @param  ChannelIndex Channel number
  *          This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  * @param  ChannelDir Channel direction
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IPCC_NotifyCPU(IPCC_HandleTypeDef const *const hipcc, uint32_t ChannelIndex,
                                     IPCC_CHANNELDirTypeDef ChannelDir)
{
  HAL_StatusTypeDef err = HAL_OK;
  uint32_t mask;

  /* Check the parameters */
  assert_param(IS_IPCC_ALL_INSTANCE(hipcc->Instance));
  IPCC_CommonTypeDef *currentInstance = IPCC_GetCurrentInstance(hipcc);

  /* Check if IPCC is initialised and the if ChannelIndex is valid */
  if ((hipcc->State == HAL_IPCC_STATE_READY) && (ChannelIndex < hipcc->channelNumber))
  {
    /* For IPCC_CHANNEL_DIR_TX, set the status. For IPCC_CHANNEL_DIR_RX, clear the status */
    currentInstance->SCR |= ((ChannelDir == IPCC_CHANNEL_DIR_TX) ? (uint32_t)IPCC_SCR_CH1S : \
                             (uint32_t)IPCC_SCR_CH1C) << (ChannelIndex & CHANNEL_INDEX_MSK) ;

    /* Unmask interrupt if the callback is requested */
    mask = ((ChannelDir == IPCC_CHANNEL_DIR_TX) ? (uint32_t)IPCC_MR_CH1FM_Msk : \
            (uint32_t)IPCC_MR_CH1OM_Msk) << (ChannelIndex & CHANNEL_INDEX_MSK) ;
    if ((hipcc->callbackRequest & mask) == mask)
    {
      IPCC_UnmaskInterrupt(hipcc, ChannelIndex, ChannelDir);
    }
  }
  else
  {
    err = HAL_ERROR;
  }

  return err;
}

/**
  * @}
  */

/** @addtogroup IPCC_IRQ_Handler_and_Callbacks
  * @{
  */

/**
  * @brief  This function handles IPCC Tx Free interrupt request.
  * @param  hipcc IPCC handle
  * @retval None
  */
void HAL_IPCC_TX_IRQHandler(IPCC_HandleTypeDef *const hipcc)
{
  uint32_t irqmask;
  uint32_t bit_pos;
  uint32_t ch_count = 0U;
  IPCC_CommonTypeDef *currentInstance = IPCC_GetCurrentInstance(hipcc);

  /* check the Tx free channels which are not masked */
  irqmask = ~(currentInstance->MR) & IPCC_ALL_TX_BUF;
  irqmask = irqmask & ~(currentInstance->SR << IPCC_MR_CH1FM_Pos);

  while (irqmask != 0UL)  /* if several bits are set, it loops to serve all of them */
  {
    bit_pos = 1UL << (IPCC_MR_CH1FM_Pos + (ch_count & CHANNEL_INDEX_MSK));

    if ((irqmask & bit_pos) != 0U)
    {
      /* mask the channel Free interrupt  */
      currentInstance->MR |= bit_pos;
      if (hipcc->ChannelCallbackTx[ch_count] != NULL)
      {
        hipcc->ChannelCallbackTx[ch_count](hipcc, ch_count, IPCC_CHANNEL_DIR_TX);
      }
      irqmask =  irqmask & ~(bit_pos);
    }
    ch_count++;
  }
}

/**
  * @brief  This function handles IPCC Rx Occupied interrupt request.
  * @param  hipcc : IPCC handle
  * @retval None
  */
void HAL_IPCC_RX_IRQHandler(IPCC_HandleTypeDef *const hipcc)
{
  uint32_t irqmask;
  uint32_t bit_pos;
  uint32_t ch_count = 0U;
  IPCC_CommonTypeDef *currentInstance = IPCC_GetCurrentInstance(hipcc);
  __I IPCC_CommonTypeDef *otherInstance = IPCC_GetOtherInstance(hipcc);

  /* check the Rx occupied channels which are not masked */
  irqmask = ~(currentInstance->MR) & IPCC_ALL_RX_BUF;
  irqmask = irqmask & otherInstance->SR;

  while (irqmask != 0UL)  /* if several bits are set, it loops to serve all of them */
  {
    bit_pos = 1UL << (ch_count & CHANNEL_INDEX_MSK);

    if ((irqmask & bit_pos) != 0U)
    {
      /* mask the channel occupied interrupt */
      currentInstance->MR |= bit_pos;
      if (hipcc->ChannelCallbackRx[ch_count] != NULL)
      {
        hipcc->ChannelCallbackRx[ch_count](hipcc, ch_count, IPCC_CHANNEL_DIR_RX);
      }
      irqmask = irqmask & ~(bit_pos);
    }
    ch_count++;
  }
}

/**
  * @brief Rx occupied callback
  * @param hipcc IPCC handle
  * @param ChannelIndex Channel number
  *          This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  * @param ChannelDir Channel direction
  */
__weak void HAL_IPCC_RxCallback(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hipcc);
  UNUSED(ChannelIndex);
  UNUSED(ChannelDir);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_IPCC_RxCallback can be implemented in the user file
   */
}

/**
  * @brief Tx free callback
  * @param hipcc IPCC handle
  * @param ChannelIndex Channel number
  *          This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  * @param ChannelDir Channel direction
  */
__weak void HAL_IPCC_TxCallback(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hipcc);
  UNUSED(ChannelIndex);
  UNUSED(ChannelDir);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_IPCC_TxCallback can be implemented in the user file
   */
}

/**
  * @}
  */

/** @addtogroup IPCC_Exported_Functions_Group3
  *  @brief   IPCC Peripheral State and Error functions
  *
@verbatim
  ==============================================================================
            ##### Peripheral State and Error functions #####
  ==============================================================================
    [..]
    This subsection permit to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief Return the IPCC handle state.
  * @param  hipcc IPCC handle
  * @retval IPCC handle state
  */
HAL_IPCC_StateTypeDef HAL_IPCC_GetState(IPCC_HandleTypeDef const *const hipcc)
{
  return hipcc->State;
}

/**
  * @brief  Get number of IPCC channels
  * @param  hipcc IPCC handle
  * @retval number of IPCC channels, 0 if IPCC is not initialized
  */
uint32_t HAL_IPCC_GetChannelNumber(const IPCC_HandleTypeDef *hipcc)
{
  uint32_t channelNumber = 0;

  if (hipcc != NULL)
  {
    channelNumber = hipcc->channelNumber;
  }
  return channelNumber;
}

/**
  * @}
  */

/** @addtogroup IPCC_Exported_Functions_Group4
  *  @brief   RIF protection configuration functions
  *
@verbatim
  ==============================================================================
            ##### RIF protection configuration functions #####
  ==============================================================================
    [..]
    This subsection allows to get/set the RIF protection configuration made of
    security, privilege, and cid (compartment id) attributes.

@endverbatim
  * @{
  */

/**
  * @brief Configure the RIF security and privilege protections of an IPCC channel
  * @param hipcc IPCC handle
  * @param LocalProcessorId local processor endpoint
  *          @arg IPCC_CPU1
  *          @arg IPCC_CPU2
  * @param ChannelIndex Channel number
  *          This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  * @param ChannelAttributes RIF security and privilege protections attributes.
  *          Combination (logical OR) of
  *            @arg IPCC_CHANNEL_PRIV | IPCC_CHANNEL_NPRIV
  *          with
  *            @arg IPCC_CHANNEL_SEC  | IPCC_CHANNEL_NSEC
  * @retval HAL_OK if the configuration is successfully set, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_IPCC_ConfigChannelAttributes(const IPCC_HandleTypeDef *hipcc, uint32_t LocalProcessorId,
                                                   uint32_t ChannelIndex, uint32_t ChannelAttributes)
{
  HAL_StatusTypeDef err;
  __IO uint32_t *regaddr;

  if (hipcc != NULL)
  {
    assert_param(IS_IPCC_ALL_INSTANCE(hipcc->Instance));

    /* Configure privilege attribute */
    if ((ChannelAttributes & IPCC_CHANNEL_PRIV_SELECT) != 0UL)
    {
      regaddr = (LocalProcessorId == IPCC_CPU1) ? &hipcc->Instance->C1PRIVCFGR : &hipcc->Instance->C2PRIVCFGR;

      if ((ChannelAttributes & IPCC_CHANNEL_PRIV) == IPCC_CHANNEL_PRIV)
      {
        *regaddr |= 1UL << ChannelIndex;
      }
      else
      {
        *regaddr &= ~(1U << ChannelIndex);
      }
    }

    /* Configure secure attribute */
    if ((ChannelAttributes & IPCC_CHANNEL_SEC_SELECT) != 0UL)
    {
      regaddr = (LocalProcessorId == IPCC_CPU1) ? &hipcc->Instance->C1SECCFGR : &hipcc->Instance->C2SECCFGR;

      if ((ChannelAttributes & IPCC_CHANNEL_SEC) == IPCC_CHANNEL_SEC)
      {
        *regaddr |= 1UL << ChannelIndex;
      }
      else
      {
        *regaddr &= ~(1UL << ChannelIndex);
      }
    }
    err = HAL_OK;
  }
  else
  {
    err = HAL_ERROR;
  }

  return err;
}

/**
  * @brief Get the configuration of the RIF security and privilege protections of an IPCC channel
  * @param hipcc IPCC handle
  * @param LocalProcessorId local processor endpoint
  *          @arg IPCC_CPU1
  *          @arg IPCC_CPU2
  * @param ChannelIndex Channel number
  *          This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  * @param pChannelAttributes pointer to the output RIF security and privilege protections attributes.
  *          Combination (logical OR) of
  *            @arg IPCC_CHANNEL_PRIV | IPCC_CHANNEL_NPRIV
  *          with
  *            @arg IPCC_CHANNEL_SEC  | IPCC_CHANNEL_NSEC
  * @retval HAL_OK if the configuration is successfully read, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_IPCC_GetConfigChannelAttributes(const IPCC_HandleTypeDef *hipcc, uint32_t LocalProcessorId,
                                                      uint32_t ChannelIndex, uint32_t *pChannelAttributes)
{
  HAL_StatusTypeDef err;
  __I uint32_t *regaddr;

  if ((hipcc != NULL) && (pChannelAttributes != NULL))
  {
    assert_param(IS_IPCC_ALL_INSTANCE(hipcc->Instance));
    *pChannelAttributes = 0;

    /* Privilege attribute */
    regaddr = (LocalProcessorId == IPCC_CPU1) ? &hipcc->Instance->C1PRIVCFGR : &hipcc->Instance->C2PRIVCFGR;
    if ((*regaddr & (1UL << ChannelIndex)) != 0UL)
    {
      *pChannelAttributes |= IPCC_CHANNEL_PRIV;
    }
    else
    {
      *pChannelAttributes |= IPCC_CHANNEL_NPRIV;
    }

    /* Secure attribute */
    regaddr = (LocalProcessorId == IPCC_CPU1) ? &hipcc->Instance->C1SECCFGR : &hipcc->Instance->C2SECCFGR;
    if ((*regaddr & (1UL << ChannelIndex)) != 0UL)
    {
      *pChannelAttributes |= IPCC_CHANNEL_SEC;
    }
    else
    {
      *pChannelAttributes |= IPCC_CHANNEL_NSEC;
    }
    err = HAL_OK;
  }
  else
  {
    err = HAL_ERROR;
  }

  return err;
}

/**
  * @brief Configure the RIF CID protection
  * @param hipcc IPCC handle
  * @param Item local processor endpoint
  *          @arg IPCC_CPU1
  *          @arg IPCC_CPU2
  * @param Attributes RIF CID protection attribute
  *          @arg IPCC_CPU_CID_DISABLE
  *          @arg IPCC_CPU_CID_STATIC_0
  *          ...
  *          @arg IPCC_CPU_CID_STATIC_7
  * @retval HAL_OK if the configuration is successfully set, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_IPCC_ConfigAttributes(const IPCC_HandleTypeDef *hipcc, uint32_t Item, uint32_t Attributes)
{
  HAL_StatusTypeDef err;
  __IO uint32_t *regaddr;
  uint32_t cid;

  if (hipcc != NULL)
  {
    assert_param(IS_IPCC_ALL_INSTANCE(hipcc->Instance));

    /* Configure CID attribute */
    regaddr = (Item == IPCC_CPU1) ? &hipcc->Instance->C1CIDCFGR : &hipcc->Instance->C2CIDCFGR;

    if ((Attributes & IPCC_CPU_CID_DISABLE_SELECT) != 0U)
    {
      *regaddr &= ~IPCC_C1CIDCFGR_CFEN;
    }
    else if ((Attributes & IPCC_CPU_CID_STATIC_SELECT) != 0U)
    {
      cid = (Attributes & IPCC_CPU_CID_VAL_Msk) >> IPCC_CPU_CID_VAL_Pos;
      *regaddr = IPCC_C1CIDCFGR_CFEN | (cid << IPCC_C1CIDCFGR_CID_Pos);
    }
    else
    {
      /* Nothing to do */
    }
    err = HAL_OK;
  }
  else
  {
    err = HAL_ERROR;
  }

  return err;
}

/**
  * @brief Get the configuration of the RIF CID protection
  * @param hipcc IPCC handle
  * @param Item local processor endpoint
  *          @arg IPCC_CPU1
  *          @arg IPCC_CPU2
  * @param pAttributes pointer to the output RIF CID protection attribute
  *          @arg IPCC_CPU_CID_DISABLE
  *          @arg IPCC_CPU_CID_STATIC_0
  *          ...
  *          @arg IPCC_CPU_CID_STATIC_7
  * @retval HAL_OK if the configuration is successfully read, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_IPCC_GetConfigAttributes(const IPCC_HandleTypeDef *hipcc, uint32_t Item, uint32_t *pAttributes)
{
  HAL_StatusTypeDef err;
  __I uint32_t *regaddr;
  uint32_t cid;

  if ((hipcc != NULL) && (pAttributes != NULL))
  {
    assert_param(IS_IPCC_ALL_INSTANCE(hipcc->Instance));

    /* CID attribute */
    regaddr = (Item == IPCC_CPU1) ? &hipcc->Instance->C1CIDCFGR : &hipcc->Instance->C2CIDCFGR;
    if ((*regaddr & IPCC_C1CIDCFGR_CFEN) == 0U)
    {
      *pAttributes = IPCC_CPU_CID_DISABLE;
    }
    else
    {
      cid = (*regaddr & IPCC_C1CIDCFGR_CID_Msk) >> IPCC_C1CIDCFGR_CID_Pos;
      *pAttributes = IPCC_CPU_CID_STATIC_SELECT | (cid << IPCC_CPU_CID_VAL_Pos);
    }
    err = HAL_OK;
  }
  else
  {
    err = HAL_ERROR;
  }

  return err;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup IPCC_Private_Functions
  * @{
  */

/**
  * @brief  Mask IPCC interrupts.
  * @param  hipcc IPCC handle
  * @param  ChannelIndex Channel number
  *          This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  * @param  ChannelDir Channel direction
  */
void IPCC_MaskInterrupt(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir)
{
  IPCC_CommonTypeDef *currentInstance = IPCC_GetCurrentInstance(hipcc);

  if (ChannelDir == IPCC_CHANNEL_DIR_TX)
  {
    /* Mask interrupt */
    currentInstance->MR |= ((uint32_t)IPCC_MR_CH1FM_Msk << (ChannelIndex & CHANNEL_INDEX_MSK));
  }
  else
  {
    /* Mask interrupt */
    currentInstance->MR |= ((uint32_t)IPCC_MR_CH1OM_Msk << (ChannelIndex & CHANNEL_INDEX_MSK));
  }
}
/**
  * @brief  Unmask IPCC interrupts.
  * @param  hipcc IPCC handle
  * @param  ChannelIndex Channel number
  *          This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  * @param  ChannelDir Channel direction
  */
void IPCC_UnmaskInterrupt(const IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir)
{
  IPCC_CommonTypeDef *currentInstance = IPCC_GetCurrentInstance(hipcc);

  if (ChannelDir == IPCC_CHANNEL_DIR_TX)
  {
    /* Unmask interrupt */
    currentInstance->MR &= ~(IPCC_MR_CH1FM_Msk << (ChannelIndex & CHANNEL_INDEX_MSK));
  }
  else
  {
    /* Unmask interrupt */
    currentInstance->MR &= ~(IPCC_MR_CH1OM_Msk << (ChannelIndex & CHANNEL_INDEX_MSK));
  }
}

/**
  * @brief Reset all callbacks of the handle to NULL.
  * @param  hipcc IPCC handle
  */
void IPCC_SetDefaultCallbacks(IPCC_HandleTypeDef *hipcc)
{
  uint32_t i;
  /* Set all callbacks to default */
  for (i = 0; i < IPCC_CHANNEL_NUMBER; i++)
  {
    hipcc->ChannelCallbackRx[i] = HAL_IPCC_RxCallback;
    hipcc->ChannelCallbackTx[i] = HAL_IPCC_TxCallback;
  }
}

/**
  * @brief Reset IPCC register to default value for the concerned instance.
  * @param  hipcc IPCC handle
  */
void IPCC_Reset_Register(IPCC_HandleTypeDef *hipcc)
{
  IPCC_CommonTypeDef *Instance = IPCC_GetCurrentInstance(hipcc);

  /* Disable RX and TX interrupts */
  Instance->CR  = 0x00000000U;

  /* Mask RX and TX interrupts */
  Instance->MR  = (IPCC_ALL_TX_BUF | IPCC_ALL_RX_BUF);

  /* Clear RX status */
  Instance->SCR = IPCC_ALL_RX_BUF;
}

/**
  * @brief Return the current core endpoint of the current IPCC instance
  * @param  hipcc IPCC handle
  */
IPCC_CommonTypeDef *IPCC_GetCurrentInstance(const IPCC_HandleTypeDef *hipcc)
{

#if defined(IPCC1)
  if (hipcc->Instance == IPCC1)
  {
#if defined(CORE_CM33)
    return IPCC1_C2;
#else   /* CORE_CM33 */
    return IPCC1_C1;
#endif  /* CORE_CM33 */
  }
#endif /* IPCC1 */

#if  defined(IPCC2)
  if (hipcc->Instance == IPCC2)
  {
#if defined (CORE_CA35) || defined(CORE_CM33)
    return IPCC2_C2;
#else   /* (CORE_CA35) || (CORE_CM33) */
    return IPCC2_C1;
#endif  /* (CORE_CA35) || (CORE_CM33) */
  }
#endif /* IPCC2 */

  return NULL;
}

/**
  * @brief Return the other core endpoint of the current IPCC instance
  * @param  hipcc IPCC handle
  */
IPCC_CommonTypeDef *IPCC_GetOtherInstance(const IPCC_HandleTypeDef *hipcc)
{
  const IPCC_CommonTypeDef *currentInstance = IPCC_GetCurrentInstance(hipcc);

#if defined (IPCC1)
  if (currentInstance == IPCC1_C1)
  {
    return  IPCC1_C2;
  }
  else
  {
    return IPCC1_C1;
  }
#endif /* IPCC1 */

#if defined (IPCC2)
  if (currentInstance == IPCC2_C1)
  {
    return IPCC2_C2;
  }
  else
  {
    return IPCC2_C1;
  }
#endif /* IPCC2 */

  return NULL;
}

/**
  * @}
  */

#endif /* HAL_IPCC_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
#endif /* IPCC || IPCC1 || IPCC2 */
