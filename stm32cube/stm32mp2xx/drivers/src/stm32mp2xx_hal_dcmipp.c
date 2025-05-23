/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_dcmipp.c
  * @author  MCD Application Team
  * @brief   DCMIPP HAL module driver
  *          This file provides firmware functions to manage the following
  *          functionalities of the DCMIPP (Digital Camera Interface Pixel Pipeline)  peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Error functions
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
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
     The sequence below describes how to use this driver to capture image
     from a camera module connected to the DCMI or CSI Interface.
     This sequence does not take into account the configuration of the
     camera module, which should be made before to configure and enable
     the DCMI to capture images.

     (#) Program the required configuration for DCMI through the following parameters:
         the Format, the VSPolarity,the HSPolarity, the PCKPolarity, the ExtendedDataMode
         the SynchroMode, the SynchroCodes of the frame delimite, the SwapBits and the SwapCycles
     using HAL_DCMIPP_Init() and HAL_DCMIPP_SetParallelConfig.
   (#) Program the required configuration for CSI through the following parameters:
     DataTypeMode, DataTypeIDA, DataTypeIDB using HAL_DCMIPP_CSI_PIPE_SetConfig.
     Assign virtual channel to pipe using HAL_DCMIPP_PIPE_CSI_SetVirtualChannelID and
     HAL_DCMIPP_Init().
     (#) Program the required configuration through the following parameters:
         the FrameRate using HAL_DCMIPP_PIPE_Config function.

  *** Interrupt mode IO operation ***
  ===================================
     (#) Configure Pipe parameter, destination and Capture Mode (Snapshot or Continuous) and enable
         the capture request using HAL_DCMIPP_PIPE_Start().
     For CSI use HAL_DCMIPP_CSI_PIPE_Start(), additionally configuring the virtual channel.
     (#) Use HAL_DCMIPP_IRQHandler() called under DCMIPP_IRQHandler() interrupt subroutine. For CSI use
       HAL_DCMIPP_CSI_IRQHandler() called under CSI_IRQHandler() interrupt subroutine.
     (#) At the end of frame capture request HAL_DCMIPP_IRQHandler() function is executed and user can
         add his own function by customization of function pointer PipeFrameEventCallback (member
         of DCMIPP handle structure).
     (#) In case of common error, the HAL_DCMIPP_IRQHandler() function calls the callback
         ErrorCallback otherwise in case of Pipe error
         the HAL_DCMIPP_IRQHandler() function calls the callbackPipeErrorCallback.

    (#) The Pipe capture can be suspended and resumed using the following functions
        HAL_DCMIPP_PIPE_Suspend() and HAL_DCMIPP_PIPE_Resume().

    (#) For Snapshot Mode the capture can be re-enabled using the HAL_DCMIPP_PIPE_EnableCapture();

    (#) Optionally, Program the required configuration through the following parameters:
        Client, MemoryPageSize, Traffic, MaxOutstandingTransactions, DPREGStart, DPREGEnd
        and WLRURatio using HAL_DCMIPP_SetIPPlugConfig().

    (#) Optionally, configure and Enable the CROP feature to select a rectangular
        window from the received image using HAL_DCMIPP_PIPE_SetCropConfig()
        and HAL_DCMIPP_PIPE_EnableCrop() functions.

    (#) Optionally, configure and Enable the line and bytes decimation features
        using the following functions HAL_DCMIPP_PIPE_SetLinesDecimationConfig and
        HAL_DCMIPP_PIPE_SetBytesDecimationConfig.

    (#) Optionally, configure and enable the line event using the function HAL_DCMIPP_PIPE_EnableLineEvent().

    (#) Optionally, configure and enable the Limit event using the function HAL_DCMIPP_PIPE_EnableLimitEvent().

    (#) If needed, reconfigure and change the input pixel format value, the frame rate
        value, the capture Mode , the destination memory address , the syncunmask values,
        Multiline value and Limit value using respectively
        the following functions: HAL_DCMIPP_PIPE_SetPixelPackerFormat(), HAL_DCMIPP_PIPE_SetFrameRate(),
        HAL_DCMIPP_PIPE_SetCaptureMode(), HAL_DCMIPP_PIPE_SetMemoryAddress(), HAL_DCMIPP_SetSyncUnmask(),
        HAL_DCMIPP_PIPE_EnableLineEvent() and HAL_DCMIPP_PIPE_EnableLimitEvent().

    (#) To read the transferred data counter , use the HAL_DCMIPP_PIPE_GetDataCounter()

    (#) To read and reset the Frame counter of the pipe, use the following functions:
        HAL_DCMIPP_PIPE_ReadFrameCounter() and HAL_DCMIPP_PIPE_ResetFrameCounter().

    (#) The Pipe capture can be Stopped using HAL_DCMIPP_PIPE_Stop() function.


    (#) To control the DCMIPP state, use the following function: HAL_DCMIPP_GetState().

    (#) To control the DCMIPP Pipe state, use the following function: HAL_DCMIPP_PIPE_GetState().

    (#) To read the DCMIPP error code, use the following function: HAL_DCMIPP_GetError().

  *** DCMIPP HAL driver macros list ***
  =============================================
  [..]
     Below the list of most used macros in DCMIPP HAL driver :

     (+) __HAL_DCMIPP_GET_FLAG: Get the DCMIPP pending flags.
     (+) __HAL_DCMIPP_CLEAR_FLAG: Clear the DCMIPP pending flags.
     (+) __HAL_DCMIPP_ENABLE_IT: Enable the specified DCMIPP interrupts.
     (+) __HAL_DCMIPP_DISABLE_IT: Disable the specified DCMIPP interrupts.
     (+) __HAL_DCMIPP_GET_IT_SOURCE: Check whether the specified DCMIPP interrupt is enabled or not.

  *** Callback registration ***
  ===================================
  [..]
     (#) The compilation define  USE_HAL_DCMIPP_REGISTER_CALLBACKS when set to 1
          allows the user to configure dynamically the driver callbacks.
          Use function @ref HAL_DCMIPP_RegisterCallback() to register a user callback.
          Use function @ref HAL_DCMIPP_PIPE_RegisterCallback() to register a user pipe callback.

     (#) Function @ref HAL_DCMIPP_RegisterCallback() allows to register following callbacks:
         (+) ErrorCallback          : callback for Error
         (+) MspInitCallback        : DCMIPP MspInit.
         (+) MspDeInitCallback      : DCMIPP MspDeInit.
          This function takes as parameters the HAL peripheral handle, the Callback ID
          and a pointer to the user callback function.
     (#) Function @ref HAL_DCMIPP_PIPE_RegisterCallback() allows to register following callbacks:
         (+) PipeFrameEventCallback : callback for Pipe Frame Event.
         (+) PipeVsyncEventCallback : callback for Pipe Vsync Event.
         (+) PipeLineEventCallback  : callback for Pipe Line Event.
         (+) PipeLimitEventCallback : callback for Pipe Limit Event.
         (+) PipeErrorCallback      : callback for Pipe Error
          This function takes as parameters the HAL peripheral handle, the Callback ID
          and a pointer to the user callback function.

     (#) Use function @ref HAL_DCMIPP_UnRegisterCallback() to reset a callback to the default
         weak (surcharged) function.
         @ref HAL_DCMIPP_UnRegisterCallback() takes as parameters the HAL peripheral handle,
         and the Callback ID.
         This function allows to reset following callbacks:
         (+) ErrorCallback          : callback for Error
         (+) MspInitCallback        : DCMIPP MspInit.
         (+) MspDeInitCallback      : DCMIPP MspDeInit.
     (#) Use function @ref HAL_DCMIPP_PIPE_UnRegisterCallback() to reset a pipe callback to the default
         weak (surcharged) function.
         @ref HAL_DCMIPP_PIPE_UnRegisterCallback() takes as parameters the HAL peripheral handle,
         and the Callback ID.
         This function allows to reset following callbacks:
         (+) PipeFrameEventCallback : callback for Pipe Frame Event.
         (+) PipeVsyncEventCallback : callback for Pipe Vsync Event.
         (+) PipeLineEventCallback  : callback for Pipe Line Event.
         (+) PipeLimitEventCallback : callback for Pipe Limit Event.
         (+) PipeErrorCallback      : callback for Pipe Error
     (#) For CSI, Following are __weak callbacks which cannot be dynamically configured:
         (+) StartOfFrameEventCallback         : callback for Start of Frame  Event.
         (+) EndOfFrameEventCallback           : callback for End of Frame Event.
         (+) TimerCounterEventCallback         : callback for Timer reached Event.
         (+) LineByteEventCallback             : callback for Line/Byte Interrupt Event.
         (+) LineErrorCallback                 : callback for Line Error Callback
         (+) ClockChangerFifoFullEventCallback : callback for clock changer fifi full event
         (+) ShortPacketDetectionEventCallback : callback for short Packet detection event
     (#) By default, after the @ref HAL_DCMIPP_Init and if the state is HAL_DCMIPP_STATE_RESET
         all callbacks are reset to the corresponding legacy weak (surcharged) functions:
         examples @ref PipeFrameEventCallback(), @ref PipeVsyncEventCallback()
         Exception done for MspInit and MspDeInit callbacks that are respectively
         reset to the legacy weak (surcharged) functions in the @ref HAL_DCMIPP_Init
         and @ref HAL_DCMIPP_DeInit only when these callbacks are null (not registered beforehand)
         If not, MspInit or MspDeInit are not null, the @ref HAL_DCMIPP_Init and @ref HAL_DCMIPP_DeInit
         keep and use the user MspInit/MspDeInit callbacks (registered beforehand).

         Callbacks can be registered/unregistered in READY state only.
         Exception done for MspInit/MspDeInit callbacks that can be registered/unregistered
         in READY or RESET state, thus registered (user) MspInit/DeInit callbacks can be used
         during the Init/DeInit.
         In that case first register the MspInit/MspDeInit user callbacks
         using @ref HAL_DCMIPP_RegisterCallback before calling @ref HAL_DCMIPP_DeInit
         or @ref HAL_DCMIPP_Init function.

         When The compilation define USE_HAL_DCMIPP_REGISTER_CALLBACKS is set to 0 or
         not defined, the callback registering feature is not available
         and weak (surcharged) callbacks are used.

     [..]
      (@) You can refer to the DCMIPP HAL driver header file for more useful macros
  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

#ifdef HAL_DCMIPP_MODULE_ENABLED
#if defined (DCMIPP)

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */
/** @defgroup DCMIPP DCMIPP
  * @brief DCMIPP HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define READ_FIELD(REG, MASK)  ((REG) & (MASK))

#define CHECK_SIGNED10(FIELD) ((FIELD) & (0x200U))
#define CHECK_SIGNED11(FIELD) ((FIELD) & (0x400U))
#define DCMIPP_TIMEOUT 1000U  /*!<  1s  */
/*
 * Table of hsfreqrange & osc_freq_target for the Synopsis D-PHY
 */
typedef struct
{
  uint32_t hsfreqrange;
  uint32_t osc_freq_target;
} SNPS_FreqsTypeDef;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup DCMIPP_Private_Functions DCMIPP Private Functions
  * @{
  */
static void Pipe_Config(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, const DCMIPP_PipeConfTypeDef *pPipeConfig);
static void DCMIPP_SetConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t DstAddress, uint32_t CaptureMode);
static void DCMIPP_EnableCapture(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
static HAL_StatusTypeDef DCMIPP_Stop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
static void DCMIPP_CSI_WritePHYReg(CSI_TypeDef *hcsi, uint32_t reg_msb, uint32_t reg_lsb, uint32_t val);
static HAL_StatusTypeDef DCMIPP_CSI_SetVCConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t VirtualChannel);
static HAL_StatusTypeDef DCMIPP_CSI_VCStop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t VirtualChannel);
/**
  * @}
  */
/* Private functions ---------------------------------------------------------*/
/** @defgroup DCMIPP_Private_Functions DCMIPP Private Functions
  * @{
  */
/**
  * @brief  Configure the selected Pipe
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Pipe        Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pPipeConfig pointer to the DCMIPP_PipeConfTypeDef structure that contains
  *                     the configuration information for the pipe.
  * @retval None
  */
static void Pipe_Config(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, const DCMIPP_PipeConfTypeDef *pPipeConfig)
{
  if (Pipe == DCMIPP_PIPE0)
  {
    /* Configure Pipe0 */
    /* Configure Frame Rate */
    MODIFY_REG(hdcmipp->Instance->P0FCTCR, DCMIPP_P0FCTCR_FRATE, pPipeConfig->FrameRate);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    /* Configure Pipe1 */
    /* Configure Frame Rate */
    MODIFY_REG(hdcmipp->Instance->P1FCTCR, DCMIPP_P1FCTCR_FRATE, pPipeConfig->FrameRate);

    /* Configure the pixel packer */
    MODIFY_REG(hdcmipp->Instance->P1PPCR, DCMIPP_P1PPCR_FORMAT, pPipeConfig->PixelPackerFormat);

    /* Configure Pixel Pipe Pitch */
    MODIFY_REG(hdcmipp->Instance->P1PPM0PR, DCMIPP_P1PPM0PR_PITCH,
               pPipeConfig->PixelPipePitch << DCMIPP_P1PPM0PR_PITCH_Pos);

    if ((pPipeConfig->PixelPackerFormat == DCMIPP_PIXEL_PACKER_FORMAT_YUV422_2) ||
        (pPipeConfig->PixelPackerFormat == DCMIPP_PIXEL_PACKER_FORMAT_YUV420_2))
    {
      /* Configure Pixel Pipe Pitch */
      MODIFY_REG(hdcmipp->Instance->P1PPM1PR, DCMIPP_P1PPM1PR_PITCH,
                 pPipeConfig->PixelPipePitch << DCMIPP_P1PPM1PR_PITCH_Pos);
    }
    else if (pPipeConfig->PixelPackerFormat == DCMIPP_PIXEL_PACKER_FORMAT_YUV420_3)
    {
      /* Configure Pixel Pipe Pitch */
      MODIFY_REG(hdcmipp->Instance->P1PPM1PR, DCMIPP_P1PPM1PR_PITCH,
                 ((pPipeConfig->PixelPipePitch) / 2U) << DCMIPP_P1PPM1PR_PITCH_Pos);
    }
    else
    {
      /* Do nothing */
    }
  }
  else
  {
    /* Configure Pipe2 */
    /* Configure Frame Rate */
    MODIFY_REG(hdcmipp->Instance->P2FCTCR, DCMIPP_P2FCTCR_FRATE, pPipeConfig->FrameRate);

    /* Configure the pixel packer */
    MODIFY_REG(hdcmipp->Instance->P2PPCR, DCMIPP_P2PPCR_FORMAT, pPipeConfig->PixelPackerFormat);

    /* Configure Pixel Pipe Pitch */
    MODIFY_REG(hdcmipp->Instance->P2PPM0PR, DCMIPP_P2PPM0PR_PITCH,
               pPipeConfig->PixelPipePitch << DCMIPP_P2PPM0PR_PITCH_Pos);
  }
}
/**
  * @brief  Write register into the D-PHY via the Test registers
  * @param  hcsi pointer to a CSI_TypeDef structure that contains
  *               the CSI registers.
  * @param  reg_msb 8 bit Test-interface data in MSB.
  * @param  reg_lsb 8 bit Test-interface data in LSB.
  * @param  val 8-bit word corresponding to the page offset in testdin.
  * @retval None
  */
static void DCMIPP_CSI_WritePHYReg(CSI_TypeDef *hcsi, uint32_t reg_msb, uint32_t reg_lsb, uint32_t val)
{
  /* For writing the 4-bit testcode MSBs */
  /* Set testen to high */
  SET_BIT(hcsi->PTCR1, CSI_PTCR1_TWM);

  /* Set testclk to high */
  SET_BIT(hcsi->PTCR0, CSI_PTCR0_TCKEN);

  /* Place 0x00 in testdin */
  SET_BIT(hcsi->PTCR1, CSI_PTCR1_TWM);

  /* Set testclk to low (with the falling edge on testclk, the testdin signal content is latched internally) */
  CLEAR_REG(hcsi->PTCR0);

  /* Set testen to low */
  CLEAR_REG(hcsi->PTCR1);

  /* Place the 8-bit word corresponding to the testcode MSBs in testdin */
  SET_BIT(hcsi->PTCR1, reg_msb & 0xffU);

  /* Set testclk to high */
  SET_BIT(hcsi->PTCR0, CSI_PTCR0_TCKEN);

  /* For writing the 8-bit testcode LSBs */
  /* Set testclk to low */
  CLEAR_REG(hcsi->PTCR0);

  /* Set testen to high */
  SET_BIT(hcsi->PTCR1, CSI_PTCR1_TWM);

  /* Set testclk to high */
  SET_BIT(hcsi->PTCR0, CSI_PTCR0_TCKEN);

  /* Place the 8-bit word test data in testdin */
  SET_BIT(hcsi->PTCR1, CSI_PTCR1_TWM | (reg_lsb & 0xffU));

  /* Set testclk to low (with the falling edge on testclk, the testdin signal content is latched internally) */
  CLEAR_REG(hcsi->PTCR0);

  /* Set testen to low */
  CLEAR_REG(hcsi->PTCR1);

  /* For writing the data */
  /* Place the 8-bit word corresponding to the page offset in testdin */
  SET_BIT(hcsi->PTCR1, val & 0xffU);

  /* Set testclk to high (test data is programmed internally */
  SET_BIT(hcsi->PTCR0, CSI_PTCR0_TCKEN);

  /* Finish by setting testclk to low */
  CLEAR_REG(hcsi->PTCR0);
}

/**
  * @brief  Configure the destination address and capture mode for the selected pipe
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Pipe        Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  DstAddress  Specifies the destination memory address for the captured data.
  * @param  CaptureMode Specifies the capture mode to be set for the pipe.
  * @retval None
  */
static void DCMIPP_SetConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t DstAddress, uint32_t CaptureMode)
{
  if (Pipe == DCMIPP_PIPE0)
  {
    /* Update the DCMIPP pipe State */
    hdcmipp->PipeState[Pipe] = HAL_DCMIPP_PIPE_STATE_BUSY;

    /* Set the capture mode */
    hdcmipp->Instance->P0FCTCR |= CaptureMode;

    /* Set the destination address */
    WRITE_REG(hdcmipp->Instance->P0PPM0AR1, DstAddress);

    /* Enable all required interrupts lines for the PIPE0 */
    __HAL_DCMIPP_ENABLE_IT(hdcmipp, DCMIPP_IT_PIPE0_FRAME | DCMIPP_IT_PIPE0_VSYNC | DCMIPP_IT_PIPE0_OVR |
                           DCMIPP_IT_AXI_TRANSFER_ERROR);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    /* Update the DCMIPP pipe State */
    hdcmipp->PipeState[Pipe] = HAL_DCMIPP_PIPE_STATE_BUSY;

    /* Set the capture mode */
    hdcmipp->Instance->P1FCTCR |= CaptureMode;

    /* Set the destination address */
    WRITE_REG(hdcmipp->Instance->P1PPM0AR1, DstAddress);

    /* Enable all required interrupts lines for the PIPE1 */
    __HAL_DCMIPP_ENABLE_IT(hdcmipp, DCMIPP_IT_PIPE1_FRAME  | DCMIPP_IT_PIPE1_OVR | DCMIPP_IT_PIPE1_VSYNC |
                           DCMIPP_IT_AXI_TRANSFER_ERROR);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    /* Update the DCMIPP pipe State */
    hdcmipp->PipeState[Pipe] = HAL_DCMIPP_PIPE_STATE_BUSY;

    /* Set the capture mode */
    hdcmipp->Instance->P2FCTCR |= CaptureMode;

    /* Set the destination address */
    WRITE_REG(hdcmipp->Instance->P2PPM0AR1, DstAddress);

    /* Enable all required interrupts lines for the PIPE2 */
    __HAL_DCMIPP_ENABLE_IT(hdcmipp, DCMIPP_IT_PIPE2_FRAME | DCMIPP_IT_PIPE2_OVR | DCMIPP_IT_PIPE2_VSYNC |
                           DCMIPP_IT_AXI_TRANSFER_ERROR);
  }
  else
  {
    /* Do nothing */
  }
}
/**
  * @brief  Enable the capture for the specified DCMIPP pipe.
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Pipe        Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval None
  */
static void DCMIPP_EnableCapture(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  if (Pipe == DCMIPP_PIPE0)
  {
    /* Activate the Pipe */
    SET_BIT(hdcmipp->Instance->P0FSCR, DCMIPP_P0FSCR_PIPEN);

    /* Start the capture */
    SET_BIT(hdcmipp->Instance->P0FCTCR, DCMIPP_P0FCTCR_CPTREQ);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    /* Activate the Pipe */
    SET_BIT(hdcmipp->Instance->P1FSCR, DCMIPP_P1FSCR_PIPEN);

    /* Start the capture */
    SET_BIT(hdcmipp->Instance->P1FCTCR, DCMIPP_P1FCTCR_CPTREQ);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    /* Activate the Pipe */
    SET_BIT(hdcmipp->Instance->P2FSCR, DCMIPP_P2FSCR_PIPEN);

    /* Start the capture */
    SET_BIT(hdcmipp->Instance->P2FCTCR, DCMIPP_P2FCTCR_CPTREQ);
  }
  else
  {
    /* Do nothing */
  }
}
/**
  * @brief  Stop the capture for the specified DCMIPP pipe.
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Pipe        Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
static HAL_StatusTypeDef DCMIPP_Stop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  uint32_t tickstart;

  if (Pipe == DCMIPP_PIPE0)
  {
    /* Stop the capture */
    CLEAR_BIT(hdcmipp->Instance->P0FCTCR, DCMIPP_P0FCTCR_CPTREQ);


    /* Poll CPTACT status till No capture currently active */
    tickstart = HAL_GetTick();
    do
    {
      if ((HAL_GetTick() - tickstart) > DCMIPP_TIMEOUT)
      {
        return HAL_ERROR;
      }
    } while ((hdcmipp->Instance->CMSR1 & DCMIPP_CMSR1_P0CPTACT) != 0U);

    /* Disable the pipe */
    CLEAR_BIT(hdcmipp->Instance->P0FSCR, DCMIPP_P0FSCR_PIPEN);

    /* Disable all interrupts for this pipe */
    __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE0_FRAME | DCMIPP_IT_PIPE0_VSYNC | DCMIPP_IT_PIPE0_LINE | \
                            DCMIPP_IT_PIPE0_LIMIT | DCMIPP_IT_PIPE0_OVR);
  }

  else if (Pipe == DCMIPP_PIPE1)
  {
    /* Stop the capture */
    CLEAR_BIT(hdcmipp->Instance->P1FCTCR, DCMIPP_P1FCTCR_CPTREQ);


    /* Poll CPTACT status till No capture currently active */
    tickstart = HAL_GetTick();
    do
    {
      if ((HAL_GetTick() - tickstart) > DCMIPP_TIMEOUT)
      {
        return HAL_ERROR;
      }
    } while ((hdcmipp->Instance->CMSR1 & DCMIPP_CMSR1_P1CPTACT) != 0U);

    /* Disable the pipe */
    CLEAR_BIT(hdcmipp->Instance->P1FSCR, DCMIPP_P1FSCR_PIPEN);

    /* Disable all interrupts for this pipe */
    __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE1_FRAME | DCMIPP_IT_PIPE1_VSYNC | DCMIPP_IT_PIPE1_LINE | \
                            DCMIPP_IT_PIPE1_OVR);
  }

  else if (Pipe == DCMIPP_PIPE2)
  {
    /* Stop the capture */
    CLEAR_BIT(hdcmipp->Instance->P2FCTCR, DCMIPP_P2FCTCR_CPTREQ);


    /* Poll CPTACT status till No capture currently active */
    tickstart = HAL_GetTick();
    do
    {
      if ((HAL_GetTick() - tickstart) > DCMIPP_TIMEOUT)
      {
        return HAL_ERROR;
      }
    } while ((hdcmipp->Instance->CMSR1 & DCMIPP_CMSR1_P2CPTACT) != 0U);

    /* Disable the pipe */
    CLEAR_BIT(hdcmipp->Instance->P2FSCR, DCMIPP_P2FSCR_PIPEN);

    /* Disable all interrupts for this pipe */
    __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE2_FRAME | DCMIPP_IT_PIPE2_VSYNC | DCMIPP_IT_PIPE2_LINE | \
                            DCMIPP_IT_PIPE2_OVR);
  }
  else
  {
    /* Do nothing */
  }

  return HAL_OK;
}
/**
  * @brief  Configure and enable the specified CSI virtual channel for a DCMIPP pipe.
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  Pipe            Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  VirtualChannel  Specifies the virtual channel, can be a value from @ref DCMIPP_Virtual_Channel
  */
static HAL_StatusTypeDef DCMIPP_CSI_SetVCConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t VirtualChannel)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;
  uint32_t tickstart;

  /* Set Virtual Channel ID for the selected Pipe */
  if (Pipe == DCMIPP_PIPE0)
  {
    MODIFY_REG(hdcmipp->Instance->P0FSCR, DCMIPP_P0FSCR_VC, VirtualChannel);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    MODIFY_REG(hdcmipp->Instance->P1FSCR, DCMIPP_P1FSCR_VC, VirtualChannel);
  }
  else
  {
    /* Those bit fields are meaningful when PIPEDIFF = 1 */
    if ((hdcmipp->Instance->P1FSCR & DCMIPP_P1FSCR_PIPEDIFF) == 0U)
    {
      /* There are no shared functions with Pipe1, Pipe2 is fully independent */
      SET_BIT(hdcmipp->Instance->P1FSCR, DCMIPP_P1FSCR_PIPEDIFF);
    }

    /* Set Virtual Channel ID and DTIDA for Pipe2 */
    MODIFY_REG(hdcmipp->Instance->P2FSCR, DCMIPP_P2FSCR_VC, VirtualChannel);
  }

  /* Enable the selected virtual channel */
  switch (VirtualChannel)
  {
    case DCMIPP_VIRTUAL_CHANNEL1:
      SET_BIT(csi_instance->CR, CSI_CR_VC1START);
      break;
    case DCMIPP_VIRTUAL_CHANNEL2:
      SET_BIT(csi_instance->CR, CSI_CR_VC2START);
      break;
    case DCMIPP_VIRTUAL_CHANNEL3:
      SET_BIT(csi_instance->CR, CSI_CR_VC3START);
      break;
    default:
      /* DCMIPP_VIRTUAL_CHANNEL0: */
      SET_BIT(csi_instance->CR, CSI_CR_VC0START);
      break;
  }

  /* wait for the selected virtual channel active state */
  tickstart = HAL_GetTick();
  do
  {
    if ((HAL_GetTick() - tickstart) > DCMIPP_TIMEOUT)
    {
      return HAL_ERROR;
    }
  } while ((csi_instance->SR0 & ((uint32_t)CSI_SR0_VC0STATEF << VirtualChannel)) \
           != ((uint32_t)CSI_SR0_VC0STATEF << VirtualChannel));

  /* Enable the SOF and EOF interrupts for the selected virtual channel */
  __HAL_DCMIPP_CSI_ENABLE_IT(csi_instance, ((uint32_t)DCMIPP_CSI_IT_EOF0 << VirtualChannel) | \
                             ((uint32_t)DCMIPP_CSI_IT_SOF0 << VirtualChannel));
  return HAL_OK;
}

/**
  * @brief  Stop the specified CSI virtual channel.
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  VirtualChannel  Specifies the virtual channel, can be a value from @ref DCMIPP_Virtual_Channel
  */
static HAL_StatusTypeDef DCMIPP_CSI_VCStop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t VirtualChannel)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;
  uint32_t tickstart;

  UNUSED(hdcmipp);
  /* Enable the selected virtual channel */
  switch (VirtualChannel)
  {
    case DCMIPP_VIRTUAL_CHANNEL1:
      SET_BIT(csi_instance->CR, CSI_CR_VC1STOP);
      break;
    case DCMIPP_VIRTUAL_CHANNEL2:
      SET_BIT(csi_instance->CR, CSI_CR_VC2STOP);
      break;
    case DCMIPP_VIRTUAL_CHANNEL3:
      SET_BIT(csi_instance->CR, CSI_CR_VC3STOP);
      break;
    default:
      /* DCMIPP_VIRTUAL_CHANNEL0: */
      SET_BIT(csi_instance->CR, CSI_CR_VC0STOP);
      break;
  }

  /* wait for the selected virtual channel active state */
  tickstart = HAL_GetTick();
  do
  {
    if ((HAL_GetTick() - tickstart) > DCMIPP_TIMEOUT)
    {
      return HAL_ERROR;
    }
  } while ((csi_instance->SR0 & ((uint32_t)CSI_SR0_VC0STATEF << VirtualChannel)) \
           == ((uint32_t)CSI_SR0_VC0STATEF << VirtualChannel));


  /* Enable the SOF and EOF interrupts for the selected virtual channel */
  __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, (DCMIPP_CSI_IT_EOF0 << VirtualChannel) | \
                              (DCMIPP_CSI_IT_SOF0 << VirtualChannel));
  return HAL_OK;
}
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup DCMIPP_Exported_Functions DCMIPP Exported Functions
  * @{
  */

/** @addtogroup DCMIPP_Initialization_De-Initialization_Functions DCMIPP Initialization De-Initialization Functions
  *  @brief     Initialization and De-Initialization Functions
@verbatim
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          deinitialize the DCMIPP peripheral:

      (+) User must Implement HAL_DCMIPP_MspInit() function in which he configures
          all related peripherals resources (CLOCK, GPIO and NVIC ).

      (+) Call the function HAL_DCMIPP_Init() to reconfigure the pipe states and DCMIPP
          state.
      (+) Call the function HAL_DCMIPP_DeInit() to restore the default configuration
          of the selected DCMIPP peripheral.
@endverbatim
  * @{
  */

/**
  * @brief  Initialize the selected HAL DCMIPP handle and associate a DCMIPP peripheral instance.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_Init(DCMIPP_HandleTypeDef *hdcmipp)
{
  uint32_t pipe_index;

  /* Check pointer validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check function parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));

  if (hdcmipp->State == HAL_DCMIPP_STATE_RESET)
  {
    /* Init the DCMIPP Callback settings */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
    /* Reset callback pointers to the weak predefined callbacks */
    hdcmipp->PIPE_FrameEventCallback = HAL_DCMIPP_PIPE_FrameEventCallback;
    hdcmipp->PIPE_VsyncEventCallback = HAL_DCMIPP_PIPE_VsyncEventCallback;
    hdcmipp->PIPE_LineEventCallback  = HAL_DCMIPP_PIPE_LineEventCallback;
    hdcmipp->PIPE_LimitEventCallback = HAL_DCMIPP_PIPE_LimitEventCallback;
#if defined(DCMIPPP_P1HISTOGRAM_AVAILABLE)
    hdcmipp->PIPE_HistogramEventCallback = HAL_DCMIPP_PIPE_HistogramEventCallback;
    hdcmipp->PIPE_HistogramErrorCallback = HAL_DCMIPP_PIPE_HistogramErrorCallback;
#endif /* DCMIPPP_P1HISTOGRAM_AVAILABLE */
    hdcmipp->PIPE_ErrorCallback      = HAL_DCMIPP_PIPE_ErrorCallback;
    hdcmipp->ErrorCallback           = HAL_DCMIPP_ErrorCallback;
    hdcmipp->LineErrorCallback         = HAL_DCMIPP_CSI_LineErrorCallback;
    hdcmipp->EndOfFrameEventCallback   = HAL_DCMIPP_CSI_EndOfFrameEventCallback;
    hdcmipp->TimerCounterEventCallback = HAL_DCMIPP_CSI_TimerCounterEventCallback;
    hdcmipp->StartOfFrameEventCallback = HAL_DCMIPP_CSI_StartOfFrameEventCallback;
    hdcmipp->LineByteEventCallback     = HAL_DCMIPP_CSI_LineByteEventCallback;
    hdcmipp->ClockChangerFifoFullEventCallback = HAL_DCMIPP_CSI_ClockChangerFifoFullEventCallback;
    hdcmipp->ShortPacketDetectionEventCallback = HAL_DCMIPP_CSI_ShortPacketDetectionEventCallback;
    if (hdcmipp->MspInitCallback == NULL)
    {
      /* Legacy weak MspInit Callback        */
      hdcmipp->MspInitCallback = HAL_DCMIPP_MspInit;
    }
    /* Initialize the low level hardware (MSP) */
    hdcmipp->MspInitCallback(hdcmipp);
#else
    /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
    HAL_DCMIPP_MspInit(hdcmipp);
#endif /* (USE_HAL_DCMIPP_REGISTER_CALLBACKS) */
  }

  /* Change the DCMIPP state */
  hdcmipp->State = HAL_DCMIPP_STATE_BUSY;

  /* Reset DCMIPP Pipe state */
  for (pipe_index = 0U; pipe_index < DCMIPP_NUM_OF_PIPES; pipe_index++)
  {
    hdcmipp->PipeState[pipe_index] = HAL_DCMIPP_PIPE_STATE_RESET;
  }

  /* Update error code */
  hdcmipp->ErrorCode = HAL_DCMIPP_ERROR_NONE;

  /* Update the DCMIPP state*/
  hdcmipp->State = HAL_DCMIPP_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  De-initializes the DCMIPP peripheral registers to their default reset values.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_DeInit(DCMIPP_HandleTypeDef *hdcmipp)
{
  uint32_t pipe_index;
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;

  /* Check pointer validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Disable the parallel Interface */
  if ((hdcmipp->Instance->PRCR & DCMIPP_PRCR_ENABLE) == DCMIPP_PARALLEL_MODE)
  {
    hdcmipp->Instance->PRCR &= ~DCMIPP_PRCR_ENABLE;
  }
  else
  {
    hdcmipp->Instance->CMCR &= ~DCMIPP_CMCR_INSEL;
  }

  /* Reset flow selection configuration register for all the available pipes */
  hdcmipp->Instance->P0FSCR = 0;
  hdcmipp->Instance->P1FSCR = 0;
  hdcmipp->Instance->P2FSCR = 0;
  /* PowerDown the D-PHY_RX lane(s) etc */
  CLEAR_REG(csi_instance->PCR);

  /* Disable the CSI */
  CLEAR_BIT(csi_instance->CR, CSI_CR_CSIEN);
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
  if (hdcmipp->MspDeInitCallback == NULL)
  {
    hdcmipp->MspDeInitCallback = HAL_DCMIPP_MspDeInit;
  }

  /* DeInit the low level hardware */
  hdcmipp->MspDeInitCallback(hdcmipp);
#else
  /* DeInit the low level hardware */
  HAL_DCMIPP_MspDeInit(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */

  /* Update error code */
  hdcmipp->ErrorCode = HAL_DCMIPP_ERROR_NONE;

  /* Initialize the DCMIPP state*/
  hdcmipp->State = HAL_DCMIPP_STATE_RESET;

  /* Reset DCMIPP Pipe state */
  for (pipe_index = 0U; pipe_index < DCMIPP_NUM_OF_PIPES; pipe_index++)
  {
    hdcmipp->PipeState[pipe_index] = HAL_DCMIPP_PIPE_STATE_RESET;
  }

  return HAL_OK;
}

/**
  * @brief  Initializes the DCMIPP MSP.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval None
  */
__weak void HAL_DCMIPP_MspInit(DCMIPP_HandleTypeDef *hdcmipp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdcmipp);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_MspInit could be implemented in the user file
   */
}

/**
  * @brief  De-Initializes the DCMIPP MSP.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval None
  */
__weak void HAL_DCMIPP_MspDeInit(DCMIPP_HandleTypeDef *hdcmipp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdcmipp);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_MspDeInit could be implemented in the user file
   */
}
/**
  * @}
  */

/** @defgroup DCMIPP_Configuration_Functions DCMIPP Configuration Functions
  * @brief    Configuration Functions
@verbatim
===============================================================================
            ##### Configuration Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing to configure DCMIPP
   (+) HAL_DCMIPP_PARALLEL_SetConfig                   : Set parallel interface config.
   (+) HAL_DCMIPP_CSI_PIPE_SetConfig                   : Set CSI config for pipe
   (+) HAL_DCMIPP_CSI_SetConfig                        : Set CSI config.
   (+) HAL_DCMIPP_CSI_SetVCFilteringConfig             : Set VC filtering
   (+) HAL_DCMIPP_CSI_SetVCConfig                      : Set VC config
   (+) HAL_DCMIPP_PIPE_SetConfig                       : Set pipe configuration
   (+) HAL_DCMIPP_SetIPPlugConfig                      : Set IPPlug Configuration.
@endverbatim
  * @{
  */
/**
  * @brief  Configure the DCMIPP Parallel Interface according to the user parameters.
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  pParallelConfig pointer to DCMIPP_ParallelConfTypeDef that contains
  *                         the parallel Interface configuration information for DCMIPP.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PARALLEL_SetConfig(DCMIPP_HandleTypeDef *hdcmipp,
                                                const DCMIPP_ParallelConfTypeDef *pParallelConfig)
{
  uint32_t prcr_reg;
  uint32_t prescr_reg;

  /* Check parameters */
  if ((hdcmipp == NULL) || (pParallelConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check function parameters */
  assert_param(IS_DCMIPP_FORMAT(pParallelConfig->Format));
  assert_param(IS_DCMIPP_VSPOLARITY(pParallelConfig->VSPolarity));
  assert_param(IS_DCMIPP_HSPOLARITY(pParallelConfig->HSPolarity));
  assert_param(IS_DCMIPP_PCKPOLARITY(pParallelConfig->PCKPolarity));
  assert_param(IS_DCMIPP_EXTENDED_DATA_MODE(pParallelConfig->ExtendedDataMode));
  assert_param(IS_DCMIPP_SYNC_MODE(pParallelConfig->SynchroMode));
  assert_param(IS_DCMIPP_SWAP_BITS(pParallelConfig->SwapBits));
  assert_param(IS_DCMIPP_SWAP_CYCLES(pParallelConfig->SwapCycles));

  /* Check DCMIPP state */
  if (hdcmipp->State != HAL_DCMIPP_STATE_INIT)
  {
    return HAL_ERROR;
  }
  else
  {
    /* Configures the Format, VS, HS, PCK polarity, ExtendedDataMode, SynchronisationMode, Swap Cycles and bits */
    prcr_reg  = ((pParallelConfig->Format)           | \
                 (pParallelConfig->VSPolarity)       | \
                 (pParallelConfig->HSPolarity)       | \
                 (pParallelConfig->PCKPolarity)      | \
                 (pParallelConfig->ExtendedDataMode) | \
                 (pParallelConfig->SynchroMode)      | \
                 (pParallelConfig->SwapCycles)       | \
                 (pParallelConfig->SwapBits));

    WRITE_REG(hdcmipp->Instance->PRCR, prcr_reg);

    if (pParallelConfig->SynchroMode == DCMIPP_SYNCHRO_EMBEDDED)
    {
      /* Set Embedded Sync codes */
      prescr_reg = (((uint32_t)pParallelConfig->SynchroCodes.FrameEndCode << DCMIPP_PRESCR_FEC_Pos)   | \
                    ((uint32_t)pParallelConfig->SynchroCodes.LineEndCode << DCMIPP_PRESCR_LEC_Pos)    | \
                    ((uint32_t)pParallelConfig->SynchroCodes.FrameStartCode << DCMIPP_PRESCR_FSC_Pos) | \
                    ((uint32_t)pParallelConfig->SynchroCodes.LineStartCode << DCMIPP_PRESCR_LSC_Pos));

      WRITE_REG(hdcmipp->Instance->PRESCR, prescr_reg);

      /* Set Embedded Sync Unmask codes : All codes are unmasked */
      WRITE_REG(hdcmipp->Instance->PRESUR, 0xFFFFFFFFU);
    }

    /* Enable the Synchronization error interrupt on parallel interface */
    __HAL_DCMIPP_ENABLE_IT(hdcmipp, DCMIPP_IT_PARALLEL_SYNC_ERROR);

    /* Enable Parallel interface */
    SET_BIT(hdcmipp->Instance->PRCR, DCMIPP_PRCR_ENABLE);

    /* Set Parallel Input Selection */
    CLEAR_BIT(hdcmipp->Instance->CMCR, DCMIPP_CMCR_INSEL);
  }

  /* Update the DCMIPP state */
  hdcmipp->State = HAL_DCMIPP_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Configure the DCMIPP Serial Interface according to the user parameters.
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  pCSI_Config pointer to DCMIPP_CSI_ConfTypeDef that contains the Serial Interface
  *                     configuration information for DCMIPP.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_SetConfig(DCMIPP_HandleTypeDef *hdcmipp, const DCMIPP_CSI_ConfTypeDef *pCSI_Config)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;

  const SNPS_FreqsTypeDef SNPS_Freqs[63] =
  {
    { 0x00U, 460U },  /* HAL_CSI_BT_80 */
    { 0x10U, 460U },  /* HAL_CSI_BT_90 */
    { 0x20U, 460U },  /* HAL_CSI_BT_100 */
    { 0x30U, 460U },  /* HAL_CSI_BT_110 */
    { 0x01U, 460U },  /* HAL_CSI_BT_120 */
    { 0x11U, 460U },  /* HAL_CSI_BT_130 */
    { 0x21U, 460U },  /* HAL_CSI_BT_140 */
    { 0x31U, 460U },  /* HAL_CSI_BT_150 */
    { 0x02U, 460U },  /* HAL_CSI_BT_160 */
    { 0x12U, 460U },  /* HAL_CSI_BT_170 */
    { 0x22U, 460U },  /* HAL_CSI_BT_180 */
    { 0x32U, 460U },  /* HAL_CSI_BT_190 */
    { 0x03U, 460U },  /* HAL_CSI_BT_205 */
    { 0x13U, 460U },  /* HAL_CSI_BT_220 */
    { 0x23U, 460U },  /* HAL_CSI_BT_235 */
    { 0x33U, 460U },  /* HAL_CSI_BT_250 */
    { 0x04U, 460U },  /* HAL_CSI_BT_275 */
    { 0x14U, 460U },  /* HAL_CSI_BT_300 */
    { 0x25U, 460U },  /* HAL_CSI_BT_325 */
    { 0x35U, 460U },  /* HAL_CSI_BT_350 */
    { 0x05U, 460U },  /* HAL_CSI_BT_400 */
    { 0x16U, 460U },  /* HAL_CSI_BT_450 */
    { 0x26U, 460U },  /* HAL_CSI_BT_500 */
    { 0x37U, 460U },  /* HAL_CSI_BT_550 */
    { 0x07U, 460U },  /* HAL_CSI_BT_600 */
    { 0x18U, 460U },  /* HAL_CSI_BT_650 */
    { 0x28U, 460U },  /* HAL_CSI_BT_700 */
    { 0x39U, 460U },  /* HAL_CSI_BT_750 */
    { 0x09U, 460U },  /* HAL_CSI_BT_800 */
    { 0x19U, 460U },  /* HAL_CSI_BT_850 */
    { 0x29U, 460U },  /* HAL_CSI_BT_900 */
    { 0x3AU, 460U },  /* HAL_CSI_BT_950 */
    { 0x0AU, 460U },  /* HAL_CSI_BT_1000 */
    { 0x1AU, 460U },  /* HAL_CSI_BT_1050 */
    { 0x2AU, 460U },  /* HAL_CSI_BT_1100 */
    { 0x3BU, 460U },  /* HAL_CSI_BT_1150 */
    { 0x0BU, 460U },  /* HAL_CSI_BT_1200 */
    { 0x1BU, 460U },  /* HAL_CSI_BT_1250 */
    { 0x2BU, 460U },  /* HAL_CSI_BT_1300 */
    { 0x3CU, 460U },  /* HAL_CSI_BT_1350 */
    { 0x0CU, 460U },  /* HAL_CSI_BT_1400 */
    { 0x1CU, 460U },  /* HAL_CSI_BT_1450 */
    { 0x2CU, 460U },  /* HAL_CSI_BT_1500 */
    { 0x3DU, 285U },  /* HAL_CSI_BT_1550 */
    { 0x0DU, 295U },  /* HAL_CSI_BT_1600 */
    { 0x1DU, 304U },  /* HAL_CSI_BT_1650 */
    { 0x2EU, 313U },  /* HAL_CSI_BT_1700 */
    { 0x3EU, 322U },  /* HAL_CSI_BT_1750 */
    { 0x0EU, 331U },  /* HAL_CSI_BT_1800 */
    { 0x1EU, 341U },  /* HAL_CSI_BT_1850 */
    { 0x2FU, 350U },  /* HAL_CSI_BT_1900 */
    { 0x3FU, 359U },  /* HAL_CSI_BT_1950 */
    { 0x0FU, 368U },  /* HAL_CSI_BT_2000 */
    { 0x40U, 377U },  /* HAL_CSI_BT_2050 */
    { 0x41U, 387U },  /* HAL_CSI_BT_2100 */
    { 0x42U, 396U },  /* HAL_CSI_BT_2150 */
    { 0x43U, 405U },  /* HAL_CSI_BT_2200 */
    { 0x44U, 414U },  /* HAL_CSI_BT_2250 */
    { 0x45U, 423U },  /* HAL_CSI_BT_2300 */
    { 0x46U, 432U },  /* HAL_CSI_BT_2350 */
    { 0x47U, 442U },  /* HAL_CSI_BT_2400 */
    { 0x48U, 451U },  /* HAL_CSI_BT_2450 */
    { 0x49U, 460U },  /* HAL_CSI_BT_2500 */
  };
  /* Check parameters */
  if ((hdcmipp == NULL) || (pCSI_Config == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_NUMBER_OF_LANES(pCSI_Config->NumberOfLanes));
  assert_param(IS_DCMIPP_CSI_DATA_LANE_MAPPING(pCSI_Config->DataLaneMapping));
  assert_param(IS_DCMIPP_CSI_DATA_PHY_BITRATE(pCSI_Config->PHYBitrate));

  /* Ensure the CSI is disabled */
  CLEAR_BIT(csi_instance->CR, CSI_CR_CSIEN);

  /* Configure the Lane Merger */
  if (pCSI_Config->DataLaneMapping == DCMIPP_CSI_PHYSICAL_DATA_LANES)
  {
    WRITE_REG(csi_instance->LMCFGR, pCSI_Config->NumberOfLanes | (DCMIPP_CSI_DATA_LANE0 << CSI_LMCFGR_DL0MAP_Pos) | \
              (DCMIPP_CSI_DATA_LANE1 << CSI_LMCFGR_DL1MAP_Pos));
  }
  else if (pCSI_Config->DataLaneMapping == DCMIPP_CSI_INVERTED_DATA_LANES)
  {
    WRITE_REG(csi_instance->LMCFGR, pCSI_Config->NumberOfLanes | (DCMIPP_CSI_DATA_LANE1 << CSI_LMCFGR_DL0MAP_Pos) | \
              (DCMIPP_CSI_DATA_LANE0 << CSI_LMCFGR_DL1MAP_Pos));
  }
  else
  {
    return HAL_ERROR;
  }

  /* Enable the CSI */
  SET_BIT(csi_instance->CR, CSI_CR_CSIEN);

  /* Enable some interrupts, not related to virtual channels - all error cases */
  __HAL_DCMIPP_CSI_ENABLE_IT(csi_instance, DCMIPP_CSI_IT_CCFIFO |  DCMIPP_CSI_IT_SYNCERR | \
                             DCMIPP_CSI_IT_SPKTERR | DCMIPP_CSI_IT_IDERR | \
                             DCMIPP_CSI_IT_SPKT);

  /* Enable D-PHY Interrupts */
  if (pCSI_Config->NumberOfLanes == DCMIPP_CSI_ONE_DATA_LANE)
  {
    if (pCSI_Config->DataLaneMapping == DCMIPP_CSI_PHYSICAL_DATA_LANES)
    {
      __HAL_DCMIPP_CSI_DPHY_ENABLE_IT(csi_instance, DCMIPP_CSI_IT_ESOTDL0 | DCMIPP_CSI_IT_ESOTSYNCDL0 |
                                      DCMIPP_CSI_IT_EESCDL0 | DCMIPP_CSI_IT_ESYNCESCDL0 |
                                      DCMIPP_CSI_IT_ECTRLDL0);
    }
    else
    {
      __HAL_DCMIPP_CSI_DPHY_ENABLE_IT(csi_instance, DCMIPP_CSI_IT_ESOTDL1 | DCMIPP_CSI_IT_ESOTSYNCDL1 |
                                      DCMIPP_CSI_IT_EESCDL1 | DCMIPP_CSI_IT_ESYNCESCDL1 |
                                      DCMIPP_CSI_IT_ECTRLDL1);
    }

  }
  else
  {
    __HAL_DCMIPP_CSI_DPHY_ENABLE_IT(csi_instance, DCMIPP_CSI_IT_ESOTDL1 | DCMIPP_CSI_IT_ESOTSYNCDL1 |
                                    DCMIPP_CSI_IT_EESCDL1 | DCMIPP_CSI_IT_ESYNCESCDL1 |
                                    DCMIPP_CSI_IT_ECTRLDL1 |
                                    DCMIPP_CSI_IT_ESOTDL0 | DCMIPP_CSI_IT_ESOTSYNCDL0 |
                                    DCMIPP_CSI_IT_EESCDL0 | DCMIPP_CSI_IT_ESYNCESCDL0 |
                                    DCMIPP_CSI_IT_ECTRLDL0);
  }

  /* Start D-PHY Configuration */
  /* Stop the D-PHY */
  CLEAR_BIT(csi_instance->PRCR, CSI_PRCR_PEN);

  /* Get the D-PHY enabledb but with all lanes disabled */
  CLEAR_REG(csi_instance-> PCR);

  /* Set the testclk (clock enable) on during 15ns */
  SET_BIT(csi_instance->PTCR0, CSI_PTCR0_TCKEN);

  HAL_Delay(1);

  CLEAR_REG(csi_instance->PTCR0);

  /* Set hsfreqrange */
  MODIFY_REG(csi_instance->PFCR, CSI_PFCR_HSFR, (0x28U << CSI_PFCR_CCFR_Pos) |
             (SNPS_Freqs[pCSI_Config->PHYBitrate].hsfreqrange << CSI_PFCR_HSFR_Pos));

  /* set reg @08 deskew_polarity_rw 1'b1 */
  DCMIPP_CSI_WritePHYReg(csi_instance, 0x00, 0x08, 0x38);

  /* set reg @0xE4 counter_for_des_en_config_if_rx 0x10 + DLL prog EN */
  /* This is because 13<= cfgclkfreqrange[5:0]<=38 */
  DCMIPP_CSI_WritePHYReg(csi_instance, 0x00, 0xe4, 0x11);

  /* set reg @0xe3 & reg @0xe2 value DLL target oscilation freq */
  /* Based on the table page 77, osc_freq_target */
  DCMIPP_CSI_WritePHYReg(csi_instance, 0x00, 0xe3, SNPS_Freqs[pCSI_Config->PHYBitrate].osc_freq_target >> 8);
  DCMIPP_CSI_WritePHYReg(csi_instance, 0x00, 0xe3, SNPS_Freqs[pCSI_Config->PHYBitrate].osc_freq_target & 0xFFU);

  /* set basedir_0 to RX DLD 0 RX, 1 TX. Synopsys 1 RX 0 TX  + freq range */
  WRITE_REG(csi_instance-> PFCR, (0x28U << CSI_PFCR_CCFR_Pos) |
            (SNPS_Freqs[pCSI_Config->PHYBitrate].hsfreqrange << CSI_PFCR_HSFR_Pos) | CSI_PFCR_DLD);

  /* Enable the D-PHY_RX lane(s) etc */
  if (pCSI_Config->NumberOfLanes == DCMIPP_CSI_ONE_DATA_LANE)
  {
    WRITE_REG(csi_instance->PCR, CSI_PCR_DL0EN | CSI_PCR_CLEN | CSI_PCR_PWRDOWN);
  }
  else
  {
    WRITE_REG(csi_instance->PCR, CSI_PCR_DL0EN | CSI_PCR_DL1EN | CSI_PCR_CLEN | CSI_PCR_PWRDOWN);
  }


  /* Enable PHY, out of reset */
  SET_BIT(csi_instance->PRCR, CSI_PRCR_PEN);

  /* Remove the force */
  CLEAR_REG(csi_instance->PMCR);

  return HAL_OK;

}
/**
  * @brief  Configure the DCMIPP Pipe according to the user parameters.
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  Pipe            Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pCSI_PipeConfig pointer to DCMIPP_CSI_PIPE_ConfTypeDef that contains
  *                         the CSI Pipe configuration information for DCMIPP.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_PIPE_SetConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                const DCMIPP_CSI_PIPE_ConfTypeDef *pCSI_PipeConfig)
{
  uint32_t pxfscr_reg = 0;
  HAL_DCMIPP_StateTypeDef tmp;
  /* Check the DCMIPP peripheral handle parameter and pCSI_Config parameter */
  if ((hdcmipp == NULL) || (pCSI_PipeConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_DATA_TYPE_MODE(pCSI_PipeConfig->DataTypeMode));

  if (Pipe != DCMIPP_PIPE2)
  {
    assert_param(IS_DCMIPP_DATA_TYPE_MODE(pCSI_PipeConfig->DataTypeMode));

    if ((pCSI_PipeConfig->DataTypeMode == DCMIPP_DTMODE_DTIDA_OR_DTIDB)
        || (pCSI_PipeConfig->DataTypeMode == DCMIPP_DTMODE_ALL_EXCEPT_DTIA_DTIB))
    {
      assert_param(IS_DCMIPP_DATA_TYPE(pCSI_PipeConfig->DataTypeIDB));
    }
  }

  if (pCSI_PipeConfig->DataTypeMode != DCMIPP_DTMODE_ALL)
  {
    assert_param(IS_DCMIPP_DATA_TYPE(pCSI_PipeConfig->DataTypeIDA));
  }

  tmp = hdcmipp->State;
  if ((tmp == HAL_DCMIPP_STATE_INIT) || (tmp == HAL_DCMIPP_STATE_READY))
  {
    if (((pCSI_PipeConfig->DataTypeMode == DCMIPP_DTMODE_ALL) || \
         (pCSI_PipeConfig->DataTypeMode == DCMIPP_DTMODE_ALL_EXCEPT_DTIA_DTIB)) && (Pipe != DCMIPP_PIPE0))
    {
      return HAL_ERROR;
    }

    /* Add Data Type Mode for the selected Pipe except Pipe2 */
    if (Pipe != DCMIPP_PIPE2)
    {
      pxfscr_reg |= (uint32_t)(pCSI_PipeConfig->DataTypeMode);
    }

    if (pCSI_PipeConfig->DataTypeMode != DCMIPP_DTMODE_ALL)
    {
      /* Add Data Type IDA for the selected Pipe */
      pxfscr_reg |= (uint32_t)(pCSI_PipeConfig->DataTypeIDA << DCMIPP_P0FSCR_DTIDA_Pos);
    }

    if ((pCSI_PipeConfig->DataTypeMode == DCMIPP_DTMODE_DTIDA_OR_DTIDB)
        || (pCSI_PipeConfig->DataTypeMode == DCMIPP_DTMODE_ALL_EXCEPT_DTIA_DTIB))
    {
      if (Pipe != DCMIPP_PIPE2)
      {
        /* Add Data Type IDB for the selected Pipe except Pipe2 */
        pxfscr_reg |= (uint32_t)(pCSI_PipeConfig->DataTypeIDB << DCMIPP_P0FSCR_DTIDB_Pos);
      }
    }

    if (Pipe == DCMIPP_PIPE0)
    {
      MODIFY_REG(hdcmipp->Instance->P0FSCR,
                 DCMIPP_P0FSCR_VC | DCMIPP_P0FSCR_DTMODE | DCMIPP_P0FSCR_DTIDA | DCMIPP_P0FSCR_DTIDB, pxfscr_reg);
    }
    else if (Pipe == DCMIPP_PIPE1)
    {
      MODIFY_REG(hdcmipp->Instance->P1FSCR,
                 (DCMIPP_P1FSCR_DTIDA | DCMIPP_P1FSCR_DTIDB | DCMIPP_P1FSCR_DTMODE | DCMIPP_P1FSCR_VC), pxfscr_reg);
    }
    else
    {
      MODIFY_REG(hdcmipp->Instance->P2FSCR, (DCMIPP_P2FSCR_DTIDA | DCMIPP_P2FSCR_VC), pxfscr_reg);
    }

    /* Disable Parallel interface */
    CLEAR_BIT(hdcmipp->Instance->PRCR, DCMIPP_PRCR_ENABLE);

    /* Set CSI Input Selection  */
    SET_BIT(hdcmipp->Instance->CMCR, DCMIPP_CMCR_INSEL);
  }

  /* Update the DCMIPP state */
  hdcmipp->State = HAL_DCMIPP_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Configure the DCMIPP Virtual Channel according to the user parameters.
  * @param  hdcmipp            Pointer to DCMIPP handle
  * @param  VirtualChannel     Specifies the virtual channel, can be a value @ref DCMIPP_Virtual_Channel
  * @param  pVCFilteringConfig pointer to DCMIPP_CSI_VCFilteringConfTypeDef that contains
  *                            the Virtual Channel Filtering configuration information.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_SetVCFilteringConfig(DCMIPP_HandleTypeDef *hdcmipp,
                                                      uint32_t VirtualChannel,
                                                      DCMIPP_CSI_VCFilteringConfTypeDef
                                                      *pVCFilteringConfig)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;
  uint32_t cfgr1 = 0;
  uint32_t cfgr2 = 0;
  uint32_t cfgr3 = 0;
  uint32_t cfgr4 = 0;
  uint32_t i;
  struct dt_cfg
  {
    uint32_t *reg;
    uint32_t offset;
  } DTCFG[MAX_DATATYPE_NB] =
  {
    { &cfgr1, 16 }, /* DT0 */
    { &cfgr2, 0 },  /* DT1 */
    { &cfgr2, 16 }, /* DT2 */
    { &cfgr3, 0 },  /* DT3 */
    { &cfgr3, 16 }, /* DT4 */
    { &cfgr4, 0 },  /* DT5 */
    { &cfgr4, 16 }, /* DT6 */
  };

  /* Check pointer and input values validity */
  if ((hdcmipp == NULL) || (pVCFilteringConfig == NULL))
  {
    return HAL_ERROR;
  }

  assert_param(IS_DCMIPP_CSI_DATA_TYPE_NB(pVCFilteringConfig->DataTypeNB));

  for (i = 0; i < pVCFilteringConfig->DataTypeNB; i++)
  {
    assert_param(IS_DCMIPP_CSI_DATA_TYPE_FORMAT(pVCFilteringConfig->DataTypeFormat[i]));
    assert_param(IS_DCMIPP_CSI_DATA_CLASS(pVCFilteringConfig->DataTypeClass[i]));

    *(DTCFG[i].reg) |= ((pVCFilteringConfig->DataTypeClass[i]) << (DTCFG[i].offset)) | \
                       (pVCFilteringConfig->DataTypeFormat[i] << (DTCFG[i].offset + 8U));
    cfgr1 |= ((uint32_t)1U << (CSI_VC0CFGR1_DT0EN_Pos + i));
  }

  switch (VirtualChannel)
  {
    case DCMIPP_VIRTUAL_CHANNEL0:
      WRITE_REG(csi_instance->VC0CFGR1, cfgr1);
      WRITE_REG(csi_instance->VC0CFGR2, cfgr2);
      WRITE_REG(csi_instance->VC0CFGR3, cfgr3);
      WRITE_REG(csi_instance->VC0CFGR4, cfgr4);
      break;
    case DCMIPP_VIRTUAL_CHANNEL1:
      WRITE_REG(csi_instance->VC1CFGR1, cfgr1);
      WRITE_REG(csi_instance->VC1CFGR2, cfgr2);
      WRITE_REG(csi_instance->VC1CFGR3, cfgr3);
      WRITE_REG(csi_instance->VC1CFGR4, cfgr4);
      break;
    case DCMIPP_VIRTUAL_CHANNEL2:
      WRITE_REG(csi_instance->VC2CFGR1, cfgr1);
      WRITE_REG(csi_instance->VC2CFGR2, cfgr2);
      WRITE_REG(csi_instance->VC2CFGR3, cfgr3);
      WRITE_REG(csi_instance->VC2CFGR4, cfgr4);
      break;
    case DCMIPP_VIRTUAL_CHANNEL3:
      WRITE_REG(csi_instance->VC3CFGR1, cfgr1);
      WRITE_REG(csi_instance->VC3CFGR2, cfgr2);
      WRITE_REG(csi_instance->VC3CFGR3, cfgr3);
      WRITE_REG(csi_instance->VC3CFGR4, cfgr4);
      break;
    default:
      break;
  }

  return HAL_OK;
}

/**
  * @brief  Configure the DCMIPP Virtual Channel with the selected Data Type format.
  * @param  hdcmipp        Pointer to DCMIPP handle
  * @param  VirtualChannel Specifies the virtual channel, can be a value from @ref DCMIPP_Virtual_Channel
  * @param  DataTypeFormat Specifies the Data Type Format, can be a value from @ref DCMIPP_CSI_DataTypeFormat.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_SetVCConfig(DCMIPP_HandleTypeDef *hdcmipp,
                                             uint32_t VirtualChannel,
                                             uint32_t DataTypeFormat)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;

  assert_param(IS_DCMIPP_VCID(VirtualChannel));
  assert_param(IS_DCMIPP_CSI_DATA_TYPE_FORMAT(DataTypeFormat));

  /* Check pointer and input values validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Set the common format for all data type for the selected virtual channel */
  switch (VirtualChannel)
  {
    case DCMIPP_VIRTUAL_CHANNEL0:
      WRITE_REG(csi_instance->VC0CFGR1, (DataTypeFormat << CSI_VC0CFGR1_CDTFT_Pos) | CSI_VC0CFGR1_ALLDT);
      break;
    case DCMIPP_VIRTUAL_CHANNEL1:
      WRITE_REG(csi_instance->VC1CFGR1, (DataTypeFormat << CSI_VC1CFGR1_CDTFT_Pos) | CSI_VC1CFGR1_ALLDT);
      break;
    case DCMIPP_VIRTUAL_CHANNEL2:
      WRITE_REG(csi_instance->VC2CFGR1, (DataTypeFormat << CSI_VC2CFGR1_CDTFT_Pos) | CSI_VC2CFGR1_ALLDT);
      break;
    case DCMIPP_VIRTUAL_CHANNEL3:
      WRITE_REG(csi_instance->VC3CFGR1, (DataTypeFormat << CSI_VC3CFGR1_CDTFT_Pos) | CSI_VC3CFGR1_ALLDT);
      break;
    default:
      break;
  }

  return HAL_OK;
}

/**
  * @brief  Configure the pipe according to the user parameters.
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Pipe        Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pPipeConfig pointer to pipe configuration structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                            const DCMIPP_PipeConfTypeDef *pPipeConfig)
{
  HAL_DCMIPP_PipeStateTypeDef pipe_state;

  /* Check the DCMIPP peripheral handle parameter and pPipeConfig parameter */
  if ((hdcmipp == NULL) || (pPipeConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_FRAME_RATE(pPipeConfig->FrameRate));
  if (Pipe != DCMIPP_PIPE0)
  {
    assert_param(IS_DCMIPP_PIXEL_PACKER_FORMAT(pPipeConfig->PixelPackerFormat));
    assert_param(IS_DCMIPP_PIXEL_PIPE_PITCH(pPipeConfig->PixelPipePitch));
  }
  /* Get Pipe State */
  pipe_state = hdcmipp->PipeState[Pipe];

  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    if ((pipe_state == HAL_DCMIPP_PIPE_STATE_RESET) || (pipe_state == HAL_DCMIPP_PIPE_STATE_ERROR))
    {
      /* Update the DCMIPP PIPE state */
      hdcmipp->PipeState[Pipe] = HAL_DCMIPP_PIPE_STATE_BUSY;

      /* Initialize the DCMIPP Pipe registers */
      Pipe_Config(hdcmipp, Pipe, pPipeConfig);

      /* Update the DCMIPP pipe state */
      hdcmipp->PipeState[Pipe] = HAL_DCMIPP_PIPE_STATE_READY;
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Configure the DCMIPP AXI master memory IP-Plug.
  * @param  hdcmipp       Pointer to DCMIPP handle
  * @param  pIPPlugConfig pointer to IPPLUG configuration structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_SetIPPlugConfig(DCMIPP_HandleTypeDef *hdcmipp,
                                             const DCMIPP_IPPlugConfTypeDef *pIPPlugConfig)
{
  uint32_t tickstart;

  /* Check handle validity */
  if ((hdcmipp == NULL) || (pIPPlugConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DCMIPP_CLIENT(pIPPlugConfig->Client));
  assert_param(IS_DCMIPP_DPREG_END(pIPPlugConfig->DPREGEnd));
  assert_param(IS_DCMIPP_DPREG_START(pIPPlugConfig->DPREGStart));
  assert_param(IS_DCMIPP_MAX_OUTSTANDING_TRANSACTIONS(pIPPlugConfig->MaxOutstandingTransactions));
  assert_param(IS_DCMIPP_MEMORY_PAGE_SIZE(pIPPlugConfig->MemoryPageSize));
  assert_param(IS_DCMIPP_TRAFFIC(pIPPlugConfig->Traffic));
  assert_param(IS_DCMIPP_WLRU_RATIO(pIPPlugConfig->WLRURatio));


  if (hdcmipp->State != HAL_DCMIPP_STATE_RESET)
  {
    /* Request to lock the IP-Plug, to allow reconfiguration */
    SET_BIT(hdcmipp->Instance->IPGR2, DCMIPP_IPGR2_PSTART);

    tickstart = HAL_GetTick();
    do
    {
      if ((HAL_GetTick() - tickstart) > DCMIPP_TIMEOUT)
      {
        return HAL_ERROR;
      }
    } while ((hdcmipp->Instance->IPGR3 & DCMIPP_IPGR3_IDLE) != DCMIPP_IPGR3_IDLE);
  }
  else
  {
    return HAL_ERROR;
  }

  /* IP-Plug is currently locked and can be reconfigured */

  /* Set Memory page size */
  hdcmipp->Instance->IPGR1 = (pIPPlugConfig->MemoryPageSize);

  /* IP-PLUG Client1 configuration */
  switch (pIPPlugConfig->Client)
  {
    case DCMIPP_CLIENT1:
    {
      /* Set Traffic : Burst size and Maximum Outstanding transactions */
      hdcmipp->Instance->IPC1R1 = (pIPPlugConfig->Traffic |
                                   (pIPPlugConfig->MaxOutstandingTransactions << DCMIPP_IPC1R1_OTR_Pos));

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC1R2 = (pIPPlugConfig->WLRURatio << DCMIPP_IPC1R2_WLRU_Pos);

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC1R3 = ((pIPPlugConfig->DPREGStart << DCMIPP_IPC1R3_DPREGSTART_Pos) |
                                   (pIPPlugConfig->DPREGEnd << DCMIPP_IPC1R3_DPREGEND_Pos));
      break;
    }
    case DCMIPP_CLIENT2:
    {
      /* Set Traffic : Burst size and Maximum Outstanding transactions */
      hdcmipp->Instance->IPC2R1 = (pIPPlugConfig->Traffic |
                                   (pIPPlugConfig->MaxOutstandingTransactions << DCMIPP_IPC2R1_OTR_Pos));

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC2R2 = (pIPPlugConfig->WLRURatio << DCMIPP_IPC2R2_WLRU_Pos);

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC2R3 = ((pIPPlugConfig->DPREGStart << DCMIPP_IPC2R3_DPREGSTART_Pos) |
                                   (pIPPlugConfig->DPREGEnd << DCMIPP_IPC2R3_DPREGEND_Pos));
      break;
    }
    case DCMIPP_CLIENT3:
    {
      /* Set Traffic : Burst size and Maximum Outstanding transactions */
      hdcmipp->Instance->IPC3R1 = (pIPPlugConfig->Traffic |
                                   (pIPPlugConfig->MaxOutstandingTransactions << DCMIPP_IPC3R1_OTR_Pos));

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC3R2 = (pIPPlugConfig->WLRURatio << DCMIPP_IPC3R2_WLRU_Pos);

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC3R3 = ((pIPPlugConfig->DPREGStart << DCMIPP_IPC3R3_DPREGSTART_Pos) |
                                   (pIPPlugConfig->DPREGEnd << DCMIPP_IPC3R3_DPREGEND_Pos));
      break;
    }
    case DCMIPP_CLIENT4:
    {
      /* Set Traffic : Burst size and Maximum Outstanding transactions */
      hdcmipp->Instance->IPC4R1 = (pIPPlugConfig->Traffic |
                                   (pIPPlugConfig->MaxOutstandingTransactions << DCMIPP_IPC4R1_OTR_Pos));

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC4R2 = (pIPPlugConfig->WLRURatio << DCMIPP_IPC4R2_WLRU_Pos);

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC4R3 = ((pIPPlugConfig->DPREGStart << DCMIPP_IPC4R3_DPREGSTART_Pos) |
                                   (pIPPlugConfig->DPREGEnd << DCMIPP_IPC4R3_DPREGEND_Pos));
      break;
    }
    case DCMIPP_CLIENT5:
    {
      /* Set Traffic : Burst size and Maximum Outstanding transactions */
      hdcmipp->Instance->IPC5R1 = (pIPPlugConfig->Traffic |
                                   (pIPPlugConfig->MaxOutstandingTransactions << DCMIPP_IPC5R1_OTR_Pos));

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC5R2 = (pIPPlugConfig->WLRURatio << DCMIPP_IPC5R2_WLRU_Pos);

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC5R3 = ((pIPPlugConfig->DPREGStart << DCMIPP_IPC5R3_DPREGSTART_Pos) |
                                   (pIPPlugConfig->DPREGEnd << DCMIPP_IPC5R3_DPREGEND_Pos));
      break;
    }
#if defined(DCMIPPP_P1HISTOGRAM_AVAILABLE)
    case DCMIPP_CLIENT6:
    {
      /* Set Traffic : Burst size and Maximum Outstanding transactions */
      hdcmipp->Instance->IPC6R1 = (pIPPlugConfig->Traffic |
                                   (pIPPlugConfig->MaxOutstandingTransactions << DCMIPP_IPC6R1_OTR_Pos));

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC6R2 = (pIPPlugConfig->WLRURatio << DCMIPP_IPC6R2_WLRU_Pos);

      /* Set End word and Start Word of the FIFO of the Clientx */
      hdcmipp->Instance->IPC6R3 = ((pIPPlugConfig->DPREGStart << DCMIPP_IPC6R3_DPREGSTART_Pos) |
                                   (pIPPlugConfig->DPREGEnd << DCMIPP_IPC6R3_DPREGEND_Pos));
      break;
    }
#endif /* DCMIPPP_P1HISTOGRAM_AVAILABLE */
    default:
      break;
  }

  /* No lock requested, IP-Plug runs on demand by background HW */
  CLEAR_BIT(hdcmipp->Instance->IPGR2, DCMIPP_IPGR2_PSTART);

  /* Enable DCMIPP_IT_AXI_TRANSFER_ERR */
  __HAL_DCMIPP_ENABLE_IT(hdcmipp, DCMIPP_IT_AXI_TRANSFER_ERROR);

  return HAL_OK;
}

/**
  * @}
  */
/** @defgroup DCMIPP_TPG_Configuration_Functions DCMIPP TPG Configuration Functions
  * @brief    TPG Configuration Functions
@verbatim
===============================================================================
            ##### TPG Configuration Functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to control the Test
          pattern generator.
@endverbatim
  * @{
  */

/**
  * @brief  Configure TPG
  * @param  hdcmipp Pointer to DCMIPP handle
  * @param  pTPGConfig  pointer to TPG configuration structure
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_DCMIPP_TPG_SetConfig(DCMIPP_HandleTypeDef *hdcmipp, const DCMIPP_TPGConfTypeDef *pTPGConfig)
{
  HAL_DCMIPP_StateTypeDef tmp;

  assert_param(IS_DCMIPP_TPG_WIDTH(pTPGConfig->Width));
  assert_param(IS_DCMIPP_TPG_HEIGHT(pTPGConfig->Height));
  assert_param(IS_DCMIPP_TPG_VBL(pTPGConfig->VBL));
  assert_param(IS_DCMIPP_TPG_FORMAT(pTPGConfig->Format));
  assert_param(IS_DCMIPP_TPG_PATTERN(pTPGConfig->Pattern));
  assert_param(IS_DCMIPP_TPG_GREY_SCALE(pTPGConfig->GreyScale));
  assert_param(IS_DCMIPP_TPG_LIFELINE(pTPGConfig->Lifeline));

  if ((hdcmipp == NULL) || (pTPGConfig == NULL))
  {
    return HAL_ERROR;
  }

  tmp = hdcmipp->State;

  if ((tmp == HAL_DCMIPP_STATE_INIT) || (tmp == HAL_DCMIPP_STATE_READY))
  {
    if (READ_FIELD(hdcmipp->Instance->CMTPGCR2, DCMIPP_CMTPGCR2_TPGEN) == 0U)
    {
      /* Set the width and height */
      WRITE_REG(hdcmipp->Instance->CMTPGCR1, (pTPGConfig->Height << DCMIPP_CMTPGCR1_HEIGHT_Pos) | \
                (pTPGConfig->Width << DCMIPP_CMTPGCR1_WIDTH_Pos));

      WRITE_REG(hdcmipp->Instance->CMTPGCR2, (pTPGConfig->VBL << DCMIPP_CMTPGCR2_VBL_Pos) | \
                pTPGConfig->Format |       \
                pTPGConfig->Pattern |      \
                pTPGConfig->GreyScale |    \
                pTPGConfig->Lifeline);

      if ((pTPGConfig->Format == DCMIPP_TPG_FORMAT_RAW8) || (pTPGConfig->Format == DCMIPP_TPG_FORMAT_RAW10) ||
          (pTPGConfig->Format == DCMIPP_TPG_FORMAT_RAW12) || (pTPGConfig->Format == DCMIPP_TPG_FORMAT_RAW14))
      {
        assert_param(IS_DCMIPP_TPG_RAW_TYPE(pTPGConfig->RawBayerType));
        hdcmipp->Instance->CMTPGCR2 |= pTPGConfig->RawBayerType;
      }
      else if (pTPGConfig->Format == DCMIPP_TPG_FORMAT_YUV422)
      {
        assert_param(IS_DCMIPP_TPG_YUV_TYPE(pTPGConfig->YUVType));
        hdcmipp->Instance->CMTPGCR2 |= pTPGConfig->YUVType;
      }
      else
      {
        /* Do Nothing */
      }

      /* Update the DCMIPP state */
      hdcmipp->State = HAL_DCMIPP_STATE_READY;
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Enable TPG
  * @param  hdcmipp Pointer to DCMIPP handle
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_DCMIPP_TPG_Enable(DCMIPP_HandleTypeDef *hdcmipp)
{
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  SET_BIT(hdcmipp->Instance->CMTPGCR2, DCMIPP_CMTPGCR2_TPGEN);

  return HAL_OK;
}

/**
  * @brief  Disable TPG
  * @param  hdcmipp Pointer to DCMIPP handle
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_DCMIPP_TPG_Disable(DCMIPP_HandleTypeDef *hdcmipp)
{
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  CLEAR_BIT(hdcmipp->Instance->CMTPGCR2, DCMIPP_CMTPGCR2_TPGEN);

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup DCMIPP_IO_operation_Functions DCMIPP IO operation Functions
  *  @brief     IO operation functions
  * @{
  */
/**
  * @brief  Start the DCMIPP capture on the specified pipe
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Pipe        Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  DstAddress  the destination address
  * @param  CaptureMode DCMIPP capture mode for the pipe can be a value from @ref DCMIPP_Capture_Mode.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_Start(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t DstAddress,
                                        uint32_t CaptureMode)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_CAPTURE_MODE(CaptureMode));

  /* Check pointer validity */
  if ((hdcmipp == NULL) || ((DstAddress & 0xFU) != 0U))
  {
    return HAL_ERROR;
  }

  /* Check DCMIPP pipe state */
  if (hdcmipp->PipeState[Pipe]  != HAL_DCMIPP_PIPE_STATE_READY)
  {
    return HAL_ERROR;
  }

  /* Set Capture Mode and Destination address for the selected pipe */
  DCMIPP_SetConfig(hdcmipp, Pipe, DstAddress, CaptureMode);

  /* Enable Capture for the selected Pipe */
  DCMIPP_EnableCapture(hdcmipp, Pipe);

  return HAL_OK;
}

/**
  * @brief  Stop DCMIPP capture on the specified pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_Stop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  HAL_DCMIPP_PipeStateTypeDef pipe_state;

  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check pointer validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Get Pipe State */
  pipe_state = hdcmipp->PipeState[Pipe];

  /* Check DCMIPP Pipe state */
  if (pipe_state != HAL_DCMIPP_PIPE_STATE_RESET)
  {
    if (DCMIPP_Stop(hdcmipp, Pipe) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Update the DCMIPP pipe State */
    hdcmipp->PipeState[Pipe] = HAL_DCMIPP_PIPE_STATE_READY;
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Start the DCMIPP capture on the specified pipe for semi-planar
  * @param  hdcmipp               Pointer to DCMIPP handle
  * @param  Pipe                  Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pSemiPlanarDstAddress Pointer to the destination addresses
  * @param  CaptureMode DCMIPP capture mode for the pipe can be a value from @ref DCMIPP_Capture_Mode.
  * @note   Only DCMIPP_PIPE1 allows semi-planar buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SemiPlanarStart(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                  DCMIPP_SemiPlanarDstAddressTypeDef *pSemiPlanarDstAddress,
                                                  uint32_t CaptureMode)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_CAPTURE_MODE(CaptureMode));

  /* Check pointer validity */
  if ((hdcmipp == NULL) || ((pSemiPlanarDstAddress->UVAddress & 0xFU) != 0U) || \
      ((pSemiPlanarDstAddress->YAddress & 0xFU) != 0U))
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE1)
  {
    /* Check DCMIPP pipe state */
    if (hdcmipp->PipeState[Pipe]  != HAL_DCMIPP_PIPE_STATE_READY)
    {
      return HAL_ERROR;
    }
    /* Set Capture Mode and Destination address for the selected pipe */
    DCMIPP_SetConfig(hdcmipp, Pipe, pSemiPlanarDstAddress->YAddress, CaptureMode);

    /* Set Auxiliary Destination addresses */
    /* Set the destination address */
    WRITE_REG(hdcmipp->Instance->P1PPM1AR1, pSemiPlanarDstAddress->UVAddress);

    /* Enable Capture for the selected Pipe */
    DCMIPP_EnableCapture(hdcmipp, Pipe);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Start the DCMIPP capture on the specified pipe for semi-planar
  * @param  hdcmipp               Pointer to DCMIPP handle
  * @param  Pipe                  Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pFullPlanarDstAddress Pointer to the destination addresses
  * @param  CaptureMode DCMIPP capture mode for the pipe can be a value from @ref DCMIPP_Capture_Mode.
  * @note   Only DCMIPP_PIPE1 allows Full-planar buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_FullPlanarStart(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                  DCMIPP_FullPlanarDstAddressTypeDef *pFullPlanarDstAddress,
                                                  uint32_t CaptureMode)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_CAPTURE_MODE(CaptureMode));

  /* Check pointer validity */
  if ((hdcmipp == NULL) || ((pFullPlanarDstAddress->YAddress & 0xFU) != 0U) ||
      ((pFullPlanarDstAddress->UAddress & 0xFU) != 0U) ||
      ((pFullPlanarDstAddress->VAddress & 0xFU) != 0U))
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE1)
  {
    /* Check DCMIPP pipe state */
    if (hdcmipp->PipeState[Pipe]  != HAL_DCMIPP_PIPE_STATE_READY)
    {
      return HAL_ERROR;
    }

    /* Set Capture Mode and Destination address for the selected pipe */
    DCMIPP_SetConfig(hdcmipp, Pipe, pFullPlanarDstAddress->YAddress, CaptureMode);

    /* Set Auxiliary Destination addresses */
    /* Set the destination address */
    WRITE_REG(hdcmipp->Instance->P1PPM1AR1, pFullPlanarDstAddress->UAddress);

    WRITE_REG(hdcmipp->Instance->P1PPM2AR1, pFullPlanarDstAddress->VAddress);

    /* Enable Capture for the selected Pipe */
    DCMIPP_EnableCapture(hdcmipp, Pipe);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Start DCMIPP capture on the specified pipe and the specified Virtual Channel in Serial Mode
  * @param  hdcmipp        Pointer to DCMIPP handle
  * @param  Pipe           Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  VirtualChannel Virtual Channel to be started can be a value from @ref DCMIPP_Virtual_Channel
  * @param  DstAddress     the destination address
  * @param  CaptureMode    DCMIPP capture mode for the pipe can be a value from @ref DCMIPP_Capture_Mode.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_PIPE_Start(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t VirtualChannel,
                                            uint32_t DstAddress, uint32_t CaptureMode)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_VCID(VirtualChannel));
  assert_param(IS_DCMIPP_CAPTURE_MODE(CaptureMode));

  /* Check pointer validity */
  if ((hdcmipp == NULL) || ((DstAddress & 0xFU) != 0U))
  {
    return HAL_ERROR;
  }

  /* Check DCMIPP pipe state */
  if (hdcmipp->PipeState[Pipe]  != HAL_DCMIPP_PIPE_STATE_READY)
  {
    return HAL_ERROR;
  }

  /* Set Virtual Channel for the selected Pipe */
  if (DCMIPP_CSI_SetVCConfig(hdcmipp, Pipe, VirtualChannel) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Set Capture Mode and Destination address for the selected pipe */
  DCMIPP_SetConfig(hdcmipp, Pipe, DstAddress, CaptureMode);

  /* Enable Capture for the selected Pipe */
  DCMIPP_EnableCapture(hdcmipp, Pipe);

  return HAL_OK;
}
/**
  * @brief  Stop DCMIPP capture on the specified pipe and the specified Virtual Channel
  * @param  hdcmipp        Pointer to DCMIPP handle
  * @param  Pipe           Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  VirtualChannel Virtual Channel to be stopped can be a value from @ref DCMIPP_Virtual_Channel
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_PIPE_Stop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t VirtualChannel)
{
  HAL_DCMIPP_PipeStateTypeDef pipe_state;
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_VCID(VirtualChannel));

  /* Check pointer validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Get Pipe State */
  pipe_state = hdcmipp->PipeState[Pipe];

  /* Check DCMIPP Pipe state */
  if (pipe_state != HAL_DCMIPP_PIPE_STATE_RESET)
  {
    if (DCMIPP_Stop(hdcmipp, Pipe) != HAL_OK)
    {
      return HAL_ERROR;
    }

    if (DCMIPP_CSI_VCStop(hdcmipp, VirtualChannel) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Update the DCMIPP pipe State */
    hdcmipp->PipeState[Pipe] = HAL_DCMIPP_PIPE_STATE_READY;
  }
  else
  {
    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Start the DCMIPP capture on the specified pipe for semi-planar in Serial Mode
  * @param  hdcmipp               Pointer to DCMIPP handle
  * @param  Pipe                  Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  VirtualChannel        Virtual Channel to be started can be a value from @ref DCMIPP_Virtual_Channel
  * @param  pSemiPlanarDstAddress Pointer to the destination addresses
  * @param  CaptureMode DCMIPP capture mode for the pipe can be a value from @ref DCMIPP_Capture_Mode.
  * @note   Only DCMIPP_PIPE1 allows semi-planar buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_PIPE_SemiPlanarStart(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                      uint32_t VirtualChannel,
                                                      DCMIPP_SemiPlanarDstAddressTypeDef *pSemiPlanarDstAddress,
                                                      uint32_t CaptureMode)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_VCID(VirtualChannel));
  assert_param(IS_DCMIPP_CAPTURE_MODE(CaptureMode));

  /* Check pointer validity */
  if ((hdcmipp == NULL) || ((pSemiPlanarDstAddress->UVAddress & 0xFU) != 0U) || \
      ((pSemiPlanarDstAddress->YAddress & 0xFU) != 0U))
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE1)
  {
    /* Check DCMIPP pipe state */
    if (hdcmipp->PipeState[Pipe] != HAL_DCMIPP_PIPE_STATE_READY)
    {
      return HAL_ERROR;
    }

    /* Set Virtual Channel for the selected Pipe */
    if (DCMIPP_CSI_SetVCConfig(hdcmipp, Pipe, VirtualChannel) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Set Capture Mode and Destination address for the selected pipe */
    DCMIPP_SetConfig(hdcmipp, Pipe, pSemiPlanarDstAddress->YAddress, CaptureMode);

    /* Set Auxiliary Destination addresses */
    /* Set the destination address */
    WRITE_REG(hdcmipp->Instance->P1PPM1AR1, pSemiPlanarDstAddress->UVAddress);

    /* Enable Capture for the selected Pipe */
    DCMIPP_EnableCapture(hdcmipp, Pipe);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Start the DCMIPP capture on the specified pipe for semi-planar in Serial Mode
  * @param  hdcmipp               Pointer to DCMIPP handle
  * @param  Pipe                  Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  VirtualChannel        Virtual Channel to be started can be a value from @ref DCMIPP_Virtual_Channel
  * @param  pFullPlanarDstAddress Pointer to the destination addresses
  * @param  CaptureMode DCMIPP    capture mode for the pipe can be a value from @ref DCMIPP_Capture_Mode.
  * @note   Only DCMIPP_PIPE1 allows Full-planar buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_PIPE_FullPlanarStart(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                      uint32_t VirtualChannel,
                                                      DCMIPP_FullPlanarDstAddressTypeDef *pFullPlanarDstAddress,
                                                      uint32_t CaptureMode)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_VCID(VirtualChannel));
  assert_param(IS_DCMIPP_CAPTURE_MODE(CaptureMode));

  /* Check pointer validity */
  if ((hdcmipp == NULL) || ((pFullPlanarDstAddress->YAddress & 0xFU) != 0U) ||
      ((pFullPlanarDstAddress->UAddress & 0xFU) != 0U) ||
      ((pFullPlanarDstAddress->VAddress & 0xFU) != 0U))
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE1)
  {
    /* Check DCMIPP pipe state */
    if (hdcmipp->PipeState[Pipe]  != HAL_DCMIPP_PIPE_STATE_READY)
    {
      return HAL_ERROR;
    }

    /* Set Virtual Channel for the selected Pipe */
    if (DCMIPP_CSI_SetVCConfig(hdcmipp, Pipe, VirtualChannel) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Set Capture Mode and Destination address for the selected pipe */
    DCMIPP_SetConfig(hdcmipp, Pipe, pFullPlanarDstAddress->YAddress, CaptureMode);

    /* Set Auxiliary Destination addresses */
    /* Set the destination address */
    WRITE_REG(hdcmipp->Instance->P1PPM1AR1, pFullPlanarDstAddress->UAddress);

    WRITE_REG(hdcmipp->Instance->P1PPM2AR1, pFullPlanarDstAddress->VAddress);

    /* Enable Capture for the selected Pipe */
    DCMIPP_EnableCapture(hdcmipp, Pipe);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Suspend DCMIPP capture on the specified pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_Suspend(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  HAL_DCMIPP_PipeStateTypeDef pipe_state;
  uint32_t tickstart;

  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (hdcmipp == NULL)
  {
    /* Return Function Status */
    return HAL_ERROR;
  }

  pipe_state = hdcmipp->PipeState[Pipe];

  if (Pipe == DCMIPP_PIPE0)
  {
    /* Check Pipe0 State */
    if (pipe_state == HAL_DCMIPP_PIPE_STATE_BUSY)
    {
      /* Disable Capture Request */
      CLEAR_BIT(hdcmipp->Instance->P0FCTCR, DCMIPP_P0FCTCR_CPTREQ);

      /* Change Pipe State */
      hdcmipp->PipeState[0] = HAL_DCMIPP_PIPE_STATE_SUSPEND;

      /* Poll CPTACT status till No capture currently active */
      tickstart = HAL_GetTick();
      do
      {
        if ((HAL_GetTick() - tickstart) > DCMIPP_TIMEOUT)
        {
          /* Change Pipe State */
          hdcmipp->PipeState[Pipe] = HAL_DCMIPP_PIPE_STATE_ERROR;

          return HAL_ERROR;
        }
      } while ((hdcmipp->Instance->CMSR1 & DCMIPP_CMSR1_P0CPTACT) != 0U);

    }
    else
    {
      /* Return Function Status */
      return HAL_ERROR;
    }
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    if (pipe_state == HAL_DCMIPP_PIPE_STATE_BUSY)
    {
      /* Disable Capture Request */
      CLEAR_BIT(hdcmipp->Instance->P1FCTCR, DCMIPP_P1FCTCR_CPTREQ);
      /* Change Pipe State */
      hdcmipp->PipeState[1] = HAL_DCMIPP_PIPE_STATE_SUSPEND;

      /* Poll CPTACT status till No capture currently active */
      tickstart = HAL_GetTick();
      do
      {
        if ((HAL_GetTick() - tickstart) > DCMIPP_TIMEOUT)
        {
          /* Change Pipe State */
          hdcmipp->PipeState[Pipe] = HAL_DCMIPP_PIPE_STATE_ERROR;

          return HAL_ERROR;
        }
      } while ((hdcmipp->Instance->CMSR1 & DCMIPP_CMSR1_P1CPTACT) != 0U);

    }
    else
    {
      /* Return Function Status */
      return HAL_ERROR;
    }

  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    if (pipe_state == HAL_DCMIPP_PIPE_STATE_BUSY)
    {
      /* Disable Capture Request */
      CLEAR_BIT(hdcmipp->Instance->P2FCTCR, DCMIPP_P2FCTCR_CPTREQ);
      /* Change Pipe State */
      hdcmipp->PipeState[2] = HAL_DCMIPP_PIPE_STATE_SUSPEND;

      /* Poll CPTACT status till No capture currently active */
      tickstart = HAL_GetTick();
      do
      {
        if ((HAL_GetTick() - tickstart) > DCMIPP_TIMEOUT)
        {
          /* Change Pipe State */
          hdcmipp->PipeState[Pipe] = HAL_DCMIPP_PIPE_STATE_ERROR;

          return HAL_ERROR;
        }
      } while ((hdcmipp->Instance->CMSR1 & DCMIPP_CMSR1_P2CPTACT) != 0U);
    }
    else
    {
      /* Return Function Status */
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  /* Return Function Status */
  return HAL_OK;
}

/**
  * @brief  Resume DCMIPP capture on the specified pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_Resume(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  HAL_DCMIPP_PipeStateTypeDef pipe_state ;

  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  pipe_state = hdcmipp->PipeState[Pipe];

  if (Pipe == DCMIPP_PIPE0)
  {
    /* Check Pipe0 State */
    if (pipe_state == HAL_DCMIPP_PIPE_STATE_SUSPEND)
    {
      /* Enable Capture Request */
      SET_BIT(hdcmipp->Instance->P0FCTCR, DCMIPP_P0FCTCR_CPTREQ);

      /* Change Pipe State */
      hdcmipp->PipeState[0] = HAL_DCMIPP_PIPE_STATE_BUSY;
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    if (pipe_state == HAL_DCMIPP_PIPE_STATE_SUSPEND)
    {
      /* Enable Capture Request */
      SET_BIT(hdcmipp->Instance->P1FCTCR, DCMIPP_P1FCTCR_CPTREQ);
      /* Change Pipe State */
      hdcmipp->PipeState[1] = HAL_DCMIPP_PIPE_STATE_BUSY;
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    if (pipe_state == HAL_DCMIPP_PIPE_STATE_SUSPEND)
    {
      /* Enable Capture Request */
      SET_BIT(hdcmipp->Instance->P2FCTCR, DCMIPP_P2FCTCR_CPTREQ);
      /* Change Pipe State */
      hdcmipp->PipeState[2] = HAL_DCMIPP_PIPE_STATE_BUSY;
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup DCMIPP_IRQ_and_Callbacks_Functions DCMIPP IRQ and Callbacks Functions
  * @brief      IRQ and Callbacks functions
  * @{
  */

/** @addtogroup DCMIPP_IRQHandler_Function IRQHandler Function
  * @{
  */
/**
  * @brief  Handles DCMIPP interrupt request.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval None
  */
void HAL_DCMIPP_IRQHandler(DCMIPP_HandleTypeDef *hdcmipp)
{
  uint32_t cmsr2flags = READ_REG(hdcmipp->Instance->CMSR2);
  uint32_t cmierflags = READ_REG(hdcmipp->Instance->CMIER);

  /* ========================= PIPE0 INTERRUPTS ==================== */
  /* Limit error on the PIPE0 ********************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE0_LIMIT) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE0_LIMIT) != 0U)
    {
      /* Disable Limit error Interrupt for pipe0 */
      __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE0_LIMIT);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_PIPE0_LIMIT;

      /* Clear the Limit error flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE0_LIMIT);

      /* LIMIT Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_LimitEventCallback(hdcmipp, DCMIPP_PIPE0);
#else
      HAL_DCMIPP_PIPE_LimitEventCallback(hdcmipp, DCMIPP_PIPE0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* VSYNC interrupt management **********************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE0_VSYNC) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE0_VSYNC) != 0U)
    {
      /* Clear the VSYNC flag for pipe0 */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE0_VSYNC);

      /* VSYNC Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_VsyncEventCallback(hdcmipp, DCMIPP_PIPE0);
#else
      HAL_DCMIPP_PIPE_VsyncEventCallback(hdcmipp, DCMIPP_PIPE0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* FRAME interrupt management ****************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE0_FRAME) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE0_FRAME) != 0U)
    {
      /* When snapshot mode, disable Vsync, Error and Overrun interrupts */
      if ((hdcmipp->Instance->P0FCTCR & DCMIPP_P0FCTCR_CPTMODE) == DCMIPP_MODE_SNAPSHOT)
      {
        __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE0_FRAME | DCMIPP_IT_PIPE0_VSYNC | DCMIPP_IT_PIPE0_OVR);

        /* Update Pipe State */
        hdcmipp->PipeState[0] = HAL_DCMIPP_PIPE_STATE_READY;
      }

      /* Clear the End of Frame flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE0_FRAME);

      /* Frame Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_FrameEventCallback(hdcmipp, DCMIPP_PIPE0);
#else
      HAL_DCMIPP_PIPE_FrameEventCallback(hdcmipp, DCMIPP_PIPE0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* LINE interrupt management **********************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE0_LINE) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE0_LINE) != 0U)
    {
      /* Clear the LINE flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE0_LINE);

      /* LINE Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_LineEventCallback(hdcmipp, DCMIPP_PIPE0);
#else
      HAL_DCMIPP_PIPE_LineEventCallback(hdcmipp, DCMIPP_PIPE0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Overrun error interrupt for Pipe0 ***************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE0_OVR) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE0_OVR) != 0U)
    {
      /* Disable Overrun Error Interrupt for pipe0 */
      __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE0_OVR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_PIPE0_OVR;

      /* Clear the overrun error flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE0_OVR);

      /* Change DCMIPP Pipe state */
      hdcmipp->PipeState[0] = HAL_DCMIPP_PIPE_STATE_ERROR;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_ErrorCallback(hdcmipp, DCMIPP_PIPE0);
#else
      HAL_DCMIPP_PIPE_ErrorCallback(hdcmipp, DCMIPP_PIPE0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* ========================= PIPE1 INTERRUPTS ==================== */
  if ((cmsr2flags & DCMIPP_FLAG_PIPE1_LINE) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE1_LINE) != 0U)
    {
      /* Clear the End of Frame flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE1_LINE);

      /* Frame Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_LineEventCallback(hdcmipp, DCMIPP_PIPE1);
#else
      HAL_DCMIPP_PIPE_LineEventCallback(hdcmipp, DCMIPP_PIPE1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* VSYNC interrupt management **********************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE1_VSYNC) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE1_VSYNC) != 0U)
    {
      /* Clear the VSYNC flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE1_VSYNC);

      /* VSYNC Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_VsyncEventCallback(hdcmipp, DCMIPP_PIPE1);
#else
      HAL_DCMIPP_PIPE_VsyncEventCallback(hdcmipp, DCMIPP_PIPE1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((cmsr2flags & DCMIPP_FLAG_PIPE1_FRAME) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE1_FRAME) != 0U)
    {
      /* When snapshot mode, disable Vsync, Error and Overrun interrupts */
      if ((hdcmipp->Instance->P1FCTCR & DCMIPP_P1FCTCR_CPTMODE) == DCMIPP_MODE_SNAPSHOT)
      {
        __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE1_FRAME | DCMIPP_IT_PIPE1_VSYNC | DCMIPP_IT_PIPE1_OVR);

        /* Update Pipe State */
        hdcmipp->PipeState[1] = HAL_DCMIPP_PIPE_STATE_READY;
      }

      /* Clear the End of Frame flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE1_FRAME);

      /* Frame Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_FrameEventCallback(hdcmipp, DCMIPP_PIPE1);
#else
      HAL_DCMIPP_PIPE_FrameEventCallback(hdcmipp, DCMIPP_PIPE1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Overrun error on the PIPE1 **************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE1_OVR) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE1_OVR) != 0U)
    {
      /* Disable Overrun Error Interrupt for pipe1 */
      __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE1_OVR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_PIPE1_OVR;

      /* Clear the overrun error flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE1_OVR);

      /* Change DCMIPP state */
      hdcmipp->PipeState[1] = HAL_DCMIPP_PIPE_STATE_ERROR;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_ErrorCallback(hdcmipp, DCMIPP_PIPE1);
#else
      HAL_DCMIPP_PIPE_ErrorCallback(hdcmipp, DCMIPP_PIPE1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }
#if defined(DCMIPPP_P1HISTOGRAM_AVAILABLE)
  /* ========================= PIPE1 Histogram INTERRUPTS ==================== */
  /* Histogram Capture Complete on the PIPE1 ********************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE1_STATS) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE1_STATS) != 0U)
    {
      /* Clear the Limit error flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE1_STATS);

#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_HistogramEventCallback(hdcmipp, DCMIPP_PIPE1);
#else
      HAL_DCMIPP_PIPE_HistogramEventCallback(hdcmipp, DCMIPP_PIPE1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }
  /* Histogram Capture Overrun on the PIPE1 ********************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE1_STATS_OVR) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE1_STATS_OVR) != 0U)
    {
      /* Disable Overrun Error Interrupt for pipe1 */
      __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE1_STATS_OVR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_PIPE1_HISTO_OVR;

      /* Stop histogram Capture */
      CLEAR_BIT(hdcmipp->Instance->P1HSCR, DCMIPP_P1HSCR_EN);

      /* Clear the Limit error flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE1_STATS_OVR);

#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_HistogramErrorCallback(hdcmipp, DCMIPP_PIPE1, HAL_DCMIPP_ERROR_PIPE1_HISTO_OVR);
#else
      HAL_DCMIPP_PIPE_HistogramErrorCallback(hdcmipp, DCMIPP_PIPE1, HAL_DCMIPP_ERROR_PIPE1_HISTO_OVR);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }
  /* Histogram Capture Bad Configuration on the PIPE1 ********************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE1_STATS_BAD_CFG) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE1_STATS_BAD_CFG) != 0U)
    {
      /* Disable Overrun Error Interrupt for pipe1 */
      __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE1_STATS_BAD_CFG);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_PIPE1_HISTO_BADCFG;

      /* Stop histogram Capture */
      CLEAR_BIT(hdcmipp->Instance->P1HSCR, DCMIPP_P1HSCR_EN);

      /* Clear the Limit error flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE1_STATS_BAD_CFG);

#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_HistogramErrorCallback(hdcmipp, DCMIPP_PIPE1, HAL_DCMIPP_ERROR_PIPE1_HISTO_BADCFG);
#else
      HAL_DCMIPP_PIPE_HistogramErrorCallback(hdcmipp, DCMIPP_PIPE1, HAL_DCMIPP_ERROR_PIPE1_HISTO_BADCFG);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }
#endif /* DCMIPPP_P1HISTOGRAM_AVAILABLE */
  /* ========================= PIPE2 INTERRUPTS ==================== */
  if ((cmsr2flags & DCMIPP_FLAG_PIPE2_LINE) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE2_LINE) != 0U)
    {
      /* Clear the End of Line flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE2_LINE);

      /* Frame Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_LineEventCallback(hdcmipp, DCMIPP_PIPE2);
#else
      HAL_DCMIPP_PIPE_LineEventCallback(hdcmipp, DCMIPP_PIPE2);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* VSYNC interrupt management **********************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE2_VSYNC) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE2_VSYNC) != 0U)
    {
      /* Clear the VSYNC flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE2_VSYNC);

      /* VSYNC Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_VsyncEventCallback(hdcmipp, DCMIPP_PIPE2);
#else
      HAL_DCMIPP_PIPE_VsyncEventCallback(hdcmipp, DCMIPP_PIPE2);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((cmsr2flags & DCMIPP_FLAG_PIPE2_FRAME) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE2_FRAME) != 0U)
    {
      /* When snapshot mode, disable Vsync, Error and Overrun interrupts */
      if ((hdcmipp->Instance->P2FCTCR & DCMIPP_P2FCTCR_CPTMODE) == DCMIPP_MODE_SNAPSHOT)
      {
        __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE2_FRAME | DCMIPP_IT_PIPE2_VSYNC | DCMIPP_IT_PIPE2_OVR);

        /* Update Pipe State */
        hdcmipp->PipeState[2] = HAL_DCMIPP_PIPE_STATE_READY;
      }

      /* Clear the End of Frame flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE2_FRAME);

      /* Frame Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_FrameEventCallback(hdcmipp, DCMIPP_PIPE2);
#else
      HAL_DCMIPP_PIPE_FrameEventCallback(hdcmipp, DCMIPP_PIPE2);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }
  /* Overrun error on the PIPE2 **************************************/
  if ((cmsr2flags & DCMIPP_FLAG_PIPE2_OVR) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PIPE2_OVR) != 0U)
    {
      /* Disable Overrun Error Interrupt for pipe1 */
      __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE2_OVR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_PIPE2_OVR;

      /* Clear the overrun error flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PIPE2_OVR);

      /* Change DCMIPP state */
      hdcmipp->PipeState[2] = HAL_DCMIPP_PIPE_STATE_ERROR;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->PIPE_ErrorCallback(hdcmipp, DCMIPP_PIPE2);
#else
      HAL_DCMIPP_PIPE_ErrorCallback(hdcmipp, DCMIPP_PIPE2);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Synchronization Error Interrupt on the parallel interface  **************/
  if ((cmsr2flags & DCMIPP_FLAG_PARALLEL_SYNC_ERROR) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_PARALLEL_SYNC_ERROR) != 0U)
    {
      /* Disable Synchronization error interrupt on parallel interface */
      __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PARALLEL_SYNC_ERROR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_PARALLEL_SYNC;

      /* Clear the synchronization error flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_PARALLEL_SYNC_ERROR);

      /* Change DCMIPP state */
      hdcmipp->State = HAL_DCMIPP_STATE_ERROR;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ErrorCallback(hdcmipp);
#else
      HAL_DCMIPP_ErrorCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* IPPLUG AXI transfer Error Interrupt     *********************************/
  if ((cmsr2flags & DCMIPP_FLAG_AXI_TRANSFER_ERROR) != 0U)
  {
    if ((cmierflags & DCMIPP_IT_AXI_TRANSFER_ERROR) != 0U)
    {
      /* Disable IPPLUG AXI transfer Error Interrupt */
      __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_AXI_TRANSFER_ERROR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_AXI_TRANSFER;

      /* Clear the AXI transfer error flag */
      __HAL_DCMIPP_CLEAR_FLAG(hdcmipp, DCMIPP_FLAG_AXI_TRANSFER_ERROR);

      /* Change DCMIPP state */
      hdcmipp->State = HAL_DCMIPP_STATE_ERROR;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ErrorCallback(hdcmipp);
#else
      HAL_DCMIPP_ErrorCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }
}
/**
  * @}
  */
/** @addtogroup DCMIPP_CSI_IRQHandler_Function CSI IRQHandler Function
  * @{
  */
/**
  * @brief  Handles DCMIPP CSI interrupt request.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval None
  */
void HAL_DCMIPP_CSI_IRQHandler(DCMIPP_HandleTypeDef *hdcmipp)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;

  /* Read the SR0 register once */
  uint32_t sr0flags = READ_REG(csi_instance->SR0);
  uint32_t sr1flags = READ_REG(csi_instance->SR1);

  uint32_t ier0_flags = READ_REG(csi_instance->IER0);
  uint32_t ier1_flags = READ_REG(csi_instance->IER1);

  /* Clock changer FIFO full event */
  if ((sr0flags & DCMIPP_CSI_FLAG_CCFIFO) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_CCFIFO) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_CCFIFO);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_CCFIFO);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ClockChangerFifoFullEventCallback(hdcmipp);
#else
      HAL_DCMIPP_CSI_ClockChangerFifoFullEventCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_SPKT) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_SPKT) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_SPKT);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_SPKT);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ShortPacketDetectionEventCallback(hdcmipp);
#else
      HAL_DCMIPP_CSI_ShortPacketDetectionEventCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /*###############################
            End Of Frame
    ##############################*/
  if ((sr0flags & DCMIPP_CSI_FLAG_EOF3) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_EOF3) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_EOF3);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_EOF3);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->EndOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL3);
#else
      HAL_DCMIPP_CSI_EndOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL3);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_EOF2) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_EOF2) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_EOF2);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_EOF2);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->EndOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL2);
#else
      HAL_DCMIPP_CSI_EndOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL2);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_EOF1) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_EOF1) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_EOF1);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_EOF1);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->EndOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL1);
#else
      HAL_DCMIPP_CSI_EndOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_EOF0) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_EOF0) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_EOF0);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_EOF0);

      /* Error Callback */
#if (USE_HAL_DCMIPP_CSIREGISTER_CALLBACKS == 1)
      hdcmipp->EndOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL1);
#else
      HAL_DCMIPP_CSI_EndOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /*###############################
           Start Of Frame
  ##############################*/
  if ((sr0flags & DCMIPP_CSI_FLAG_SOF3) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_SOF3) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_SOF3);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_SOF3);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->StartOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL3);
#else
      HAL_DCMIPP_CSI_StartOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL3);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_SOF2) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_SOF2) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_SOF2);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_SOF2);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->StartOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL2);
#else
      HAL_DCMIPP_CSI_StartOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL2);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_SOF1) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_SOF1) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_SOF1);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_SOF1);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->StartOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL1);
#else
      HAL_DCMIPP_CSI_StartOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_SOF0) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_SOF0) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_SOF0);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_SOF0);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->StartOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL0);
#else
      HAL_DCMIPP_CSI_StartOfFrameEventCallback(hdcmipp, DCMIPP_VIRTUAL_CHANNEL0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /*###############################
           Timer Interrupt
  ##############################*/
  if ((sr0flags & DCMIPP_CSI_FLAG_TIM3) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_TIM3) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_TIM3);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_TIM3);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->TimerCounterEventCallback(hdcmipp, DCMIPP_CSI_TIMER3);
#else
      HAL_DCMIPP_CSI_TimerCounterEventCallback(hdcmipp, DCMIPP_CSI_TIMER3);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_TIM2) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_TIM2) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_TIM2);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_TIM2);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->TimerCounterEventCallback(hdcmipp, DCMIPP_CSI_TIMER2);
#else
      HAL_DCMIPP_CSI_TimerCounterEventCallback(hdcmipp, DCMIPP_CSI_TIMER2);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_TIM1) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_TIM1) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_TIM1);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_TIM1);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->TimerCounterEventCallback(hdcmipp, DCMIPP_CSI_TIMER1);
#else
      HAL_DCMIPP_CSI_TimerCounterEventCallback(hdcmipp, DCMIPP_CSI_TIMER1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_TIM0) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_TIM0) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_TIM0);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_TIM0);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->TimerCounterEventCallback(hdcmipp, DCMIPP_CSI_TIMER0);
#else
      HAL_DCMIPP_CSI_TimerCounterEventCallback(hdcmipp, DCMIPP_CSI_TIMER0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /*###############################
     Byte/Line Counter Interrupt
  ##############################*/
  if ((sr0flags & DCMIPP_CSI_FLAG_LB3) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_LB3) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_LB3);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_LB3);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineByteEventCallback(hdcmipp, DCMIPP_CSI_COUNTER3);
#else
      HAL_DCMIPP_CSI_LineByteEventCallback(hdcmipp, DCMIPP_CSI_COUNTER3);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_LB2) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_LB2) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_LB2);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_LB2);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineByteEventCallback(hdcmipp, DCMIPP_CSI_COUNTER2);
#else
      HAL_DCMIPP_CSI_LineByteEventCallback(hdcmipp, DCMIPP_CSI_COUNTER2);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_LB1) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_LB1) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_LB1);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_LB1);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineByteEventCallback(hdcmipp, DCMIPP_CSI_COUNTER1);
#else
      HAL_DCMIPP_CSI_LineByteEventCallback(hdcmipp, DCMIPP_CSI_COUNTER1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_LB0) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_LB0) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_LB0);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_LB0);

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineByteEventCallback(hdcmipp, DCMIPP_CSI_COUNTER0);
#else
      HAL_DCMIPP_CSI_LineByteEventCallback(hdcmipp, DCMIPP_CSI_COUNTER0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Synchronization error  */
  if ((sr0flags & DCMIPP_CSI_FLAG_SYNCERR) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_SYNCERR) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_SYNCERR);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_SYNCERR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_SYNC;

      /* Change CSI state */
      hdcmipp->State = HAL_DCMIPP_STATE_ERROR;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ErrorCallback(hdcmipp);
#else
      HAL_DCMIPP_ErrorCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_WDERR) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_WDERR) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_WDERR);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_WDERR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_WDG;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ErrorCallback(hdcmipp);
#else
      HAL_DCMIPP_ErrorCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_SPKTERR) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_SPKTERR) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_SPKTERR);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_SPKTERR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_SPKT;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ErrorCallback(hdcmipp);
#else
      HAL_DCMIPP_ErrorCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_IDERR) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_IDERR) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_IDERR);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_IDERR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_DATA_ID;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ErrorCallback(hdcmipp);
#else
      HAL_DCMIPP_ErrorCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_CECCERR) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_CECCERR) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_CECCERR);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_CECCERR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_CECC;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ErrorCallback(hdcmipp);
#else
      HAL_DCMIPP_ErrorCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_ECCERR) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_ECCERR) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_ECCERR);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_ECCERR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_ECC;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ErrorCallback(hdcmipp);
#else
      HAL_DCMIPP_ErrorCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  if ((sr0flags & DCMIPP_CSI_FLAG_CRCERR) != 0U)
  {
    if ((ier0_flags & DCMIPP_CSI_IT_CRCERR) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_CRCERR);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_FLAG(csi_instance, DCMIPP_CSI_FLAG_CRCERR);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_CRC;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->ErrorCallback(hdcmipp);
#else
      HAL_DCMIPP_ErrorCallback(hdcmipp);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Lane 0 Errors */
  /* Start Of Transmission error  */
  if ((sr1flags & DCMIPP_CSI_FLAG_ESOTDL0) != 0U)
  {
    if ((ier1_flags & DCMIPP_CSI_IT_ESOTDL0) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_ESOTDL0);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_DPHY_FLAG(csi_instance, DCMIPP_CSI_FLAG_ESOTDL0);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_SOT;

      /* Change CSI state */
      hdcmipp->State = HAL_DCMIPP_STATE_ERROR;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE0);
#else
      HAL_DCMIPP_CSI_LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Start Of Transmission Synchronisation error   */
  if ((sr1flags & DCMIPP_CSI_FLAG_ESOTSYNCDL0) != 0U)
  {
    if ((ier1_flags & DCMIPP_CSI_IT_ESOTSYNCDL0) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_ESOTSYNCDL0);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_DPHY_FLAG(csi_instance, DCMIPP_CSI_FLAG_ESOTSYNCDL0);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_SOT_SYNC;

      /* Change CSI state */
      hdcmipp->State = HAL_DCMIPP_STATE_ERROR;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE0);
#else
      HAL_DCMIPP_CSI_LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Escape entry error   */
  if ((sr1flags & DCMIPP_CSI_FLAG_EESCDL0) != 0U)
  {
    if ((ier1_flags & DCMIPP_CSI_IT_EESCDL0) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_EESCDL0);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_DPHY_FLAG(csi_instance, DCMIPP_CSI_FLAG_EESCDL0);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_DPHY_ESCAPE;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE0);
#else
      HAL_DCMIPP_CSI_LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Low power data transmission synchronization error  */
  if ((sr1flags & DCMIPP_CSI_FLAG_ESYNCESCDL0) != 0U)
  {
    if ((ier1_flags & DCMIPP_CSI_IT_ESYNCESCDL0) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_ESYNCESCDL0);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_DPHY_FLAG(csi_instance, DCMIPP_CSI_FLAG_ESYNCESCDL0);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_DPHY_LP_SYNC;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE0);
#else
      HAL_DCMIPP_CSI_LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Error control on data line */
  if ((sr1flags & DCMIPP_CSI_FLAG_ECTRLDL0) != 0U)
  {
    if ((ier1_flags & DCMIPP_CSI_IT_ECTRLDL0) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_ECTRLDL0);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_DPHY_FLAG(csi_instance, DCMIPP_CSI_FLAG_ECTRLDL0);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_DPHY_CTRL;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE0);
#else
      HAL_DCMIPP_CSI_LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE0);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Lane 1 Errors */
  /* Start Of Transmission error  */
  if ((sr1flags & DCMIPP_CSI_FLAG_ESOTDL1) != 0U)
  {
    if ((ier1_flags & DCMIPP_CSI_IT_ESOTDL1) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_ESOTDL1);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_DPHY_FLAG(csi_instance, DCMIPP_CSI_FLAG_ESOTDL1);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_SOT;

      /* Change CSI state */
      hdcmipp->State = HAL_DCMIPP_STATE_ERROR;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE1);
#else
      HAL_DCMIPP_CSI_LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Start Of Transmission Synchronisation error   */
  if ((sr1flags & DCMIPP_CSI_FLAG_ESOTSYNCDL1) != 0U)
  {
    if ((ier1_flags & DCMIPP_CSI_IT_ESOTSYNCDL1) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_ESOTSYNCDL1);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_DPHY_FLAG(csi_instance, DCMIPP_CSI_FLAG_ESOTSYNCDL1);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_SOT_SYNC;

      /* Change CSI state */
      hdcmipp->State = HAL_DCMIPP_STATE_ERROR;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE1);
#else
      HAL_DCMIPP_CSI_LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Escape entry error   */
  if ((sr1flags & DCMIPP_CSI_FLAG_EESCDL1) != 0U)
  {
    if ((ier1_flags & DCMIPP_CSI_IT_EESCDL1) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_EESCDL1);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_DPHY_FLAG(csi_instance, DCMIPP_CSI_FLAG_EESCDL1);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_DPHY_ESCAPE;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE1);
#else
      HAL_DCMIPP_CSI_LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Low power data transmission synchronization error  */
  if ((sr1flags & DCMIPP_CSI_FLAG_ESYNCESCDL1) != 0U)
  {
    if ((ier1_flags & DCMIPP_CSI_IT_ESYNCESCDL1) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_ESYNCESCDL1);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_DPHY_FLAG(csi_instance, DCMIPP_CSI_FLAG_ESYNCESCDL1);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_DPHY_LP_SYNC;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE1);
#else
      HAL_DCMIPP_CSI_LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

  /* Error control on data line */
  if ((sr1flags & DCMIPP_CSI_IT_ECTRLDL1) != 0U)
  {
    if ((ier1_flags & DCMIPP_CSI_IT_ECTRLDL1) != 0U)
    {
      /* Disable IT */
      __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_ECTRLDL1);

      /* Clear Flag */
      __HAL_DCMIPP_CSI_CLEAR_DPHY_FLAG(csi_instance, DCMIPP_CSI_IT_ECTRLDL1);

      /* Update error code */
      hdcmipp->ErrorCode |= HAL_DCMIPP_CSI_ERROR_DPHY_CTRL;

      /* Error Callback */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
      hdcmipp->LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE1);
#else
      HAL_DCMIPP_CSI_LineErrorCallback(hdcmipp, DCMIPP_CSI_DATA_LANE1);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
    }
  }

}
/**
  * @}
  */

/** @addtogroup DCMIPP_Callback_Functions Callback Functions
  * @{
  */
/**
  * @brief  Frame Event callback on the pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval None
  */
__weak void HAL_DCMIPP_PIPE_FrameEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_FrameEventDumpPipeCallback could be implemented in the user file
   */
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Pipe);
  UNUSED(hdcmipp);
}

/**
  * @brief  Vsync Event callback on pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval None
  */
__weak void HAL_DCMIPP_PIPE_VsyncEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_VsyncEventDumpPipeCallback could be implemented in the user file
   */
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Pipe);
  UNUSED(hdcmipp);
}


/**
  * @brief  Line Event callback on the pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval None
  */
__weak void HAL_DCMIPP_PIPE_LineEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_LineEventMainPipeCallback could be implemented in the user file
   */
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Pipe);
  UNUSED(hdcmipp);
}

/**
  * @brief  Limit callback on the Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval None
  */
__weak void HAL_DCMIPP_PIPE_LimitEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_LimitEventDumpPipeCallback could be implemented in the user file
   */
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Pipe);
  UNUSED(hdcmipp);
}

#if defined(DCMIPPP_P1HISTOGRAM_AVAILABLE)
/**
  * @brief  Histogram Capture Complete callback on the Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval None
  */
__weak void HAL_DCMIPP_PIPE_HistogramEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_PIPE_HistogramEventCallback could be implemented in the user file
   */
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Pipe);
  UNUSED(hdcmipp);
}

/**
  * @brief  Histogram Event callback on the Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  Error    Specifies the DCMIPP Pipe Histogram Error.
  * @retval None
  */
__weak void HAL_DCMIPP_PIPE_HistogramErrorCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t Error)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_PIPE_HistogramErrorCallback could be implemented in the user file
   */
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Pipe);
  UNUSED(hdcmipp);
  UNUSED(Error);
}
#endif /* DCMIPPP_P1HISTOGRAM_AVAILABLE */
/**
  * @brief  Error callback on the pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval None
  */
__weak void HAL_DCMIPP_PIPE_ErrorCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_SyncErrorEventCallback could be implemented in the user file
   */
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Pipe);
  UNUSED(hdcmipp);
}


/**
  * @brief  Error callback on DCMIPP
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval None
  */
__weak void HAL_DCMIPP_ErrorCallback(DCMIPP_HandleTypeDef *hdcmipp)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_ErrorCallback could be implemented in the user file
   */
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdcmipp);
}
/**
  * @}
  */
/** @defgroup DCMIPP_CSI_Callback_Functions  CSI Callback Functions
  *  @brief   Callback (event / error) functions
  *
@verbatim
 ===============================================================================
                ##### Callback functions #####
 ===============================================================================
    [..]  This section provides function called upon:
      (+) events triggered by the CSI
      (+) errors triggered by the CSI
@endverbatim
  * @{
  */
/**
  * @brief  Line Error callback on the Data Lane
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  DataLane
  * @retval None
  */
__weak void HAL_DCMIPP_CSI_LineErrorCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t DataLane)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_CSI_LineErrorCallback could be implemented in the user file
   */
  UNUSED(hdcmipp);
  UNUSED(DataLane);
}
/**
  * @brief  Clock Changer Fifo Full Event Callback
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval None
  */
__weak void HAL_DCMIPP_CSI_ClockChangerFifoFullEventCallback(DCMIPP_HandleTypeDef *hdcmipp)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_CSI_ClockChangerFifoFullEventCallback could be implemented in the user file
   */
  UNUSED(hdcmipp);
}
/**
  * @brief  Short Packet Detection Event Callback
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval None
  */
__weak void HAL_DCMIPP_CSI_ShortPacketDetectionEventCallback(DCMIPP_HandleTypeDef *hdcmipp)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_CSI_ShortPacketDetectionEventCallback could be implemented in the user file
   */
  UNUSED(hdcmipp);
}
/**
  * @brief  End Of Frame Event Callback
  * @param  hdcmipp             Pointer to DCMIPP handle
  * @param  VirtualChannel      Virtual Channel
  * @retval None
  */
__weak void HAL_DCMIPP_CSI_EndOfFrameEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t VirtualChannel)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_CSI_EndOfFrameEventCallback could be implemented in the user file
   */
  UNUSED(hdcmipp);
  UNUSED(VirtualChannel);
}
/**
  * @brief  Start Of Frame Event Callback
  * @param  hdcmipp              Pointer to DCMIPP handle
  * @param  VirtualChannel       Virtual Channel
  * @retval None
  */
__weak void HAL_DCMIPP_CSI_StartOfFrameEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t VirtualChannel)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_CSI_StartOfFrameEventCallback could be implemented in the user file
   */
  UNUSED(hdcmipp);
  UNUSED(VirtualChannel);
}
/**
  * @brief  Timer Counter Event Callback
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Timer
  * @retval None
  */
__weak void HAL_DCMIPP_CSI_TimerCounterEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Timer)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMIPP_CSI_TimerCounterEventCallback could be implemented in the user file
   */
  UNUSED(hdcmipp);
  UNUSED(Timer);
}
/**
  * @brief  Line Byte Event Callback
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Counter
  * @retval None
  */
__weak void HAL_DCMIPP_CSI_LineByteEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Counter)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
          the HAL_DCMIPP_CSI_LineByteEventCallback could be implemented in the user file
  */
  UNUSED(hdcmipp);
  UNUSED(Counter);
}
/**
  * @}
  */

/** @defgroup DCMIPP_RegisterCallback_Functions Register Callback Functions
  * @{
  */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User DCMIPP Callback
  *         To be used instead of the weak (surcharged) predefined callback
  * @param  hdcmipp    Pointer to DCMIPP handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *          @arg @ref  HAL_DCMIPP_ERROR_CB_ID DCMIPP Error callback ID
  *          @arg @ref  HAL_DCMIPP_MSPINIT_CB_ID DCMIPP MspInit callback ID
  *          @arg @ref  HAL_DCMIPP_MSPDEINIT_CB_ID DCMIPP MspDeInit callback ID
  * @param pCallback pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_DCMIPP_RegisterCallback(DCMIPP_HandleTypeDef *hdcmipp, HAL_DCMIPP_CallbackIDTypeDef CallbackID,
                                              pDCMIPP_CallbackTypeDef pCallback)
{

  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }

  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_DCMIPP_MSPINIT_CB_ID :
        hdcmipp->MspInitCallback = pCallback;
        break;

      case HAL_DCMIPP_MSPDEINIT_CB_ID :
        hdcmipp->MspDeInitCallback = pCallback;
        break;

      case HAL_DCMIPP_ERROR_CB_ID :
        hdcmipp->ErrorCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hdcmipp->State == HAL_DCMIPP_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_DCMIPP_MSPINIT_CB_ID :
        hdcmipp->MspInitCallback = pCallback;
        break;

      case HAL_DCMIPP_MSPDEINIT_CB_ID :
        hdcmipp->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
    /* update return status */
    status =  HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Unregister a User DCMIPP Callback
  *         DCMIPP Callback is redirected to the weak (surcharged) predefined callback
  * @param  hdcmipp    Pointer to DCMIPP handle
  * @param  CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref  HAL_DCMIPP_ERROR_CB_ID DCMIPP Error callback ID
  *          @arg @ref  HAL_DCMIPP_MSPINIT_CB_ID DCMIPP MspInit callback ID
  *          @arg @ref  HAL_DCMIPP_MSPDEINIT_CB_ID DCMIPP MspDeInit callback ID
  * @retval status
  */
HAL_StatusTypeDef HAL_DCMIPP_UnRegisterCallback(DCMIPP_HandleTypeDef *hdcmipp, HAL_DCMIPP_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_DCMIPP_MSPINIT_CB_ID :
        hdcmipp->MspInitCallback = HAL_DCMIPP_MspInit; /* Legacy weak (surcharged) Msp Init */
        break;

      case HAL_DCMIPP_MSPDEINIT_CB_ID :
        hdcmipp->MspDeInitCallback = HAL_DCMIPP_MspDeInit; /* Legacy weak (surcharged) Msp DeInit */
        break;

      default :
        /* Update the error code */
        hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hdcmipp->State == HAL_DCMIPP_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_DCMIPP_MSPINIT_CB_ID :
        hdcmipp->MspInitCallback = HAL_DCMIPP_MspInit;   /* Legacy weak (surcharged) Msp Init */
        break;

      case HAL_DCMIPP_MSPDEINIT_CB_ID :
        hdcmipp->MspDeInitCallback = HAL_DCMIPP_MspDeInit;  /* Legacy weak (surcharged) Msp DeInit */
        break;

      default :
        /* Update the error code */
        hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
    /* update return status */
    status =  HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Register a User DCMIPP Pipe Callback
  *         To be used instead of the weak (surcharged) predefined callback
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *          @arg @ref  HAL_DCMIPP_PIPE_FRAME_EVENT_CB_ID DCMIPP Pipe Frame event callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_VSYNC_EVENT_CB_ID DCMIPP Pipe Vsync event callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_LINE_EVENT_CB_ID DCMIPP Pipe Line event callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_LIMIT_EVENT_CB_ID DCMIPP Pipe Limit event callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_ERROR_CB_ID DCMIPP Pipe Error callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_HISTOGRAM_CB_ID DCMIPP Pipe1 Histogram Event callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_HISTOGRAM_ERROR_CB_ID DCMIPP Pipe1 Histogram Error callback ID
  * @param pCallback pointer to the Pipe Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_RegisterCallback(DCMIPP_HandleTypeDef *hdcmipp,
                                                   HAL_DCMIPP_PIPE_CallbackIDTypeDef CallbackID,
                                                   pDCMIPP_PIPE_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }

  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_DCMIPP_PIPE_FRAME_EVENT_CB_ID :
        hdcmipp->PIPE_FrameEventCallback = pCallback;
        break;

      case HAL_DCMIPP_PIPE_VSYNC_EVENT_CB_ID :
        hdcmipp->PIPE_VsyncEventCallback = pCallback;
        break;

      case HAL_DCMIPP_PIPE_LINE_EVENT_CB_ID :
        hdcmipp->PIPE_LineEventCallback = pCallback;
        break;

      case HAL_DCMIPP_PIPE_LIMIT_EVENT_CB_ID :
        hdcmipp->PIPE_LimitEventCallback = pCallback;
        break;

      case HAL_DCMIPP_PIPE_ERROR_CB_ID :
        hdcmipp->PIPE_ErrorCallback = pCallback;
        break;
#if defined(DCMIPPP_P1HISTOGRAM_AVAILABLE)
      case HAL_DCMIPP_PIPE_HISTOGRAM_CB_ID:
        hdcmipp->PIPE_HistogramEventCallback = pCallback;
        break;
      case HAL_DCMIPP_PIPE_HISTOGRAM_ERROR_CB_ID:
        hdcmipp->PIPE_HistogramErrorCallback = pCallback;
        break;
#endif /* DCMIPPP_P1HISTOGRAM_AVAILABLE */

      default :
        /* Update the error code */
        hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
    /* update return status */
    status =  HAL_ERROR;
  }

  return status;
}

/**
  * @brief  UnRegister a User DCMIPP Pipe Callback
  *         DCMIPP Callback is redirected to the weak (surcharged) predefined callback
  * @param  hdcmipp   Pointer to DCMIPP handle
  * @param  CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref  HAL_DCMIPP_PIPE_FRAME_EVENT_CB_ID DCMIPP Pipe Frame event callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_VSYNC_EVENT_CB_ID DCMIPP Pipe Vsync event callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_LINE_EVENT_CB_ID DCMIPP Pipe Line event callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_LIMIT_EVENT_CB_ID DCMIPP Pipe Limit event callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_ERROR_CB_ID DCMIPP Pipe Error callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_HISTOGRAM_CB_ID DCMIPP Pipe1 Histogram Event callback ID
  *          @arg @ref  HAL_DCMIPP_PIPE_HISTOGRAM_ERROR_CB_ID DCMIPP Pipe1 Histogram Error callback ID
  * @retval status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_UnRegisterCallback(DCMIPP_HandleTypeDef *hdcmipp,
                                                     HAL_DCMIPP_PIPE_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_DCMIPP_PIPE_FRAME_EVENT_CB_ID :
        hdcmipp->PIPE_FrameEventCallback = HAL_DCMIPP_PIPE_FrameEventCallback;
        break;

      case HAL_DCMIPP_PIPE_VSYNC_EVENT_CB_ID :
        hdcmipp->PIPE_VsyncEventCallback = HAL_DCMIPP_PIPE_VsyncEventCallback;
        break;

      case HAL_DCMIPP_PIPE_LINE_EVENT_CB_ID :
        hdcmipp->PIPE_LineEventCallback = HAL_DCMIPP_PIPE_LineEventCallback;
        break;

      case HAL_DCMIPP_PIPE_LIMIT_EVENT_CB_ID :
        hdcmipp->PIPE_LimitEventCallback = HAL_DCMIPP_PIPE_LimitEventCallback;
        break;

      case HAL_DCMIPP_PIPE_ERROR_CB_ID :
        hdcmipp->PIPE_ErrorCallback = HAL_DCMIPP_PIPE_ErrorCallback;
        break;
#if defined(DCMIPPP_P1HISTOGRAM_AVAILABLE)
      case HAL_DCMIPP_PIPE_HISTOGRAM_CB_ID:
        hdcmipp->PIPE_HistogramEventCallback = HAL_DCMIPP_PIPE_HistogramEventCallback;
        break;
      case HAL_DCMIPP_PIPE_HISTOGRAM_ERROR_CB_ID:
        hdcmipp->PIPE_HistogramErrorCallback = HAL_DCMIPP_PIPE_HistogramErrorCallback;
        break;
#endif /* DCMIPPP_P1HISTOGRAM_AVAILABLE */

      default :
        /* Update the error code */
        hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hdcmipp->ErrorCode |= HAL_DCMIPP_ERROR_INVALID_CALLBACK;
    /* update return status */
    status =  HAL_ERROR;
  }

  return status;
}
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
/**
  * @}
  */
/**
  * @}
  */
/** @defgroup DCMIPP_Crop_Functions DCMIPP Crop Functions
@verbatim
===============================================================================
            ##### Crop Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing
   (+) HAL_DCMIPP_PIPE_SetCropConfig : Set Crop configurations
   (+) HAL_DCMIPP_PIPE_EnableCrop    : Enable Crop
   (+) HAL_DCMIPP_PIPE_DisableCrop   : Disable Crop
@endverbatim
  * @{
  */
/**
  * @brief  Configures cropping for the specified DCMIPP pipe according to the user parameters
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Pipe        Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pCropConfig pointer to DCMIPP_CropConfTypeDef structure that contains
  *                     the configuration information for Crop.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetCropConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                const DCMIPP_CropConfTypeDef *pCropConfig)
{
  uint32_t tmp;

  /* Check handle validity */
  if ((hdcmipp == NULL) || (pCropConfig == NULL))
  {
    return HAL_ERROR;
  }

  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_PIPE_CROP_AREA(pCropConfig->PipeArea));
  assert_param(IS_DCMIPP_PIPE_CROP_HSTART(pCropConfig->HStart));
  assert_param(IS_DCMIPP_PIPE_CROP_HSIZE(pCropConfig->HSize));
  assert_param(IS_DCMIPP_PIPE_CROP_VSIZE(pCropConfig->VSize));
  assert_param(IS_DCMIPP_PIPE_CROP_VSTART(pCropConfig->VStart));

  /* Check the DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {

    if (Pipe == DCMIPP_PIPE0)
    {
      tmp = READ_REG(hdcmipp->Instance->PRCR);

      /* Verify for parallel mode with jpeg format , no Line Crop enable  */
      if (((tmp & DCMIPP_PRCR_ENABLE) == DCMIPP_PRCR_ENABLE) && ((tmp & DCMIPP_PRCR_FORMAT) == DCMIPP_FORMAT_BYTE))
      {
        return HAL_ERROR;
      }
      else
      {
        /* Set Cropping horizontal and vertical start for Pipe0 */
        MODIFY_REG(hdcmipp->Instance->P0SCSTR, DCMIPP_P0SCSTR_HSTART | DCMIPP_P0SCSTR_VSTART,
                   (pCropConfig->HStart << DCMIPP_P0SCSTR_HSTART_Pos) |
                   (pCropConfig->VStart << DCMIPP_P0SCSTR_VSTART_Pos));

        /* Set Cropping horizontal and vertical width for Pipe0 */
        /* Set crop Area (Inner or outer) for Pipe0 */
        MODIFY_REG(hdcmipp->Instance->P0SCSZR, DCMIPP_P0SCSZR_HSIZE | DCMIPP_P0SCSZR_VSIZE | DCMIPP_P0SCSZR_POSNEG,
                   (pCropConfig->HSize << DCMIPP_P0SCSZR_HSIZE_Pos) | (pCropConfig->VSize << DCMIPP_P0SCSZR_VSIZE_Pos) |
                   (pCropConfig->PipeArea));
      }
    }
    else if (Pipe == DCMIPP_PIPE1)
    {
      /* Set Cropping horizontal and vertical start for Pipe1 */
      MODIFY_REG(hdcmipp->Instance->P1CRSTR, DCMIPP_P1CRSTR_HSTART | DCMIPP_P1CRSTR_VSTART,
                 (pCropConfig->HStart << DCMIPP_P1CRSTR_HSTART_Pos) | \
                 (pCropConfig->VStart << DCMIPP_P1CRSTR_VSTART_Pos));

      /* Set Cropping horizontal and vertical width for Pipe1 */
      MODIFY_REG(hdcmipp->Instance->P1CRSZR, DCMIPP_P1CRSZR_HSIZE | DCMIPP_P1CRSZR_VSIZE,
                 (pCropConfig->HSize << DCMIPP_P1CRSZR_HSIZE_Pos) | (pCropConfig->VSize << DCMIPP_P1CRSZR_VSIZE_Pos));
    }
    else if (Pipe == DCMIPP_PIPE2)
    {
      /* Set Cropping horizontal and vertical start for Pipe2 */
      MODIFY_REG(hdcmipp->Instance->P2CRSTR, DCMIPP_P2CRSTR_HSTART | DCMIPP_P2CRSTR_VSTART,
                 (pCropConfig->HStart << DCMIPP_P2CRSTR_HSTART_Pos) | \
                 (pCropConfig->VStart << DCMIPP_P2CRSTR_VSTART_Pos));

      /* Set Cropping horizontal and vertical width for Pipe2 */
      MODIFY_REG(hdcmipp->Instance->P2CRSZR, DCMIPP_P2CRSZR_HSIZE | DCMIPP_P2CRSZR_VSIZE,
                 (pCropConfig->HSize << DCMIPP_P2CRSZR_HSIZE_Pos) | (pCropConfig->VSize << DCMIPP_P2CRSZR_VSIZE_Pos));
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Enables the cropping for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @note   Cropping cannot be enabled in parallel mode with JPEG Format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableCrop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  uint32_t tmp;

  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    if (Pipe == DCMIPP_PIPE0)
    {
      /* This bit must be kept cleared if the input format is JPEG */
      /* Verify for parallel mode with jpeg format , no Line Crop enable  */

      tmp = READ_REG(hdcmipp->Instance->PRCR);

      if (((tmp & DCMIPP_PRCR_ENABLE) == DCMIPP_PRCR_ENABLE) && ((tmp & DCMIPP_PRCR_FORMAT) == DCMIPP_FORMAT_BYTE))
      {
        return HAL_ERROR;
      }
      else
      {
        SET_BIT(hdcmipp->Instance->P0SCSZR, DCMIPP_P0SCSZR_ENABLE);
      }
    }
    else if (Pipe == DCMIPP_PIPE1)
    {
      /* Verify Crop line is disabled */
      if (hdcmipp->Instance->P1SRCR != DCMIPP_P1SRCR_CROPEN)
      {
        SET_BIT(hdcmipp->Instance->P1CRSZR, DCMIPP_P1CRSZR_ENABLE);
      }
      else
      {
        return HAL_ERROR;
      }
    }
    else if (Pipe == DCMIPP_PIPE2)
    {
      SET_BIT(hdcmipp->Instance->P2CRSZR, DCMIPP_P2CRSZR_ENABLE);
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the cropping for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableCrop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE0)
  {
    CLEAR_BIT(hdcmipp->Instance->P0SCSZR, DCMIPP_P0SCSZR_ENABLE);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1CRSZR, DCMIPP_P1CRSZR_ENABLE);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    CLEAR_BIT(hdcmipp->Instance->P2CRSZR, DCMIPP_P2CRSZR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @defgroup DCMIPP_Decimation_Functions DCMIPP Decimation Functions
@verbatim
===============================================================================
            ##### Decimation Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing
   (+) HAL_DCMIPP_PIPE_SetBytesDecimationConfig : Set Bytes Decimation configurations.
   (+) HAL_DCMIPP_PIPE_SetLinesDecimationConfig : Set Line Decimation configurations.
   (+) HAL_DCMIPP_PIPE_SetISPDecimationConfig   : Set ISP Decimation configurations.
   (+) HAL_DCMIPP_PIPE_EnableISPDecimation      : Enable ISP Decimation.
   (+) HAL_DCMIPP_PIPE_DisableISPDecimation     : Disable ISP Decimation.
   (+) HAL_DCMIPP_PIPE_SetDecimationConfig      : Set Decimation configurations.
   (+) HAL_DCMIPP_PIPE_EnableDecimation         : Enable Decimation.
   (+) HAL_DCMIPP_PIPE_DisableDecimation        : Disable Decimation.
@endverbatim
  * @{
  */
/**
  * @brief  Configure the Bytes decimation for the selected Pipe.
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Pipe        Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  SelectStart can a be value from @ref DCMIPP_Byte_Start_Mode
  * @param  SelectMode  can be a value from @ref DCMIPP_Byte_Select_Mode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetBytesDecimationConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                           uint32_t SelectStart, uint32_t SelectMode)
{
  uint32_t tmp;

  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_BYTE_SELECT_START(SelectStart));
  assert_param(IS_DCMIPP_BYTE_SELECT_MODE(SelectMode));

  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE0)
  {
    /* OEBS : This bit works in conjunction with BSM field (BSM != 00) */
    /* Modes 10 and 11 work only with EDM [2:0] = 000 into the DCMIPP_PRCR */
    tmp = (hdcmipp->Instance->PRCR & DCMIPP_PRCR_EDM);

    if (((SelectStart == DCMIPP_OEBS_EVEN) && (SelectMode == DCMIPP_BSM_ALL)) ||
        ((SelectStart == DCMIPP_OEBS_ODD) && (SelectMode == DCMIPP_BSM_ALL)) ||
        ((SelectMode > DCMIPP_BSM_DATA_OUT_2) && (tmp != DCMIPP_INTERFACE_8BITS)))
    {
      return HAL_ERROR;
    }
    else
    {
      /* Set Bytes select Start and Bytes select Mode */
      MODIFY_REG(hdcmipp->Instance->P0PPCR, DCMIPP_P0PPCR_BSM | DCMIPP_P0PPCR_OEBS, (SelectStart | SelectMode));
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Configure the Lines decimation for the selected Pipe.
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Pipe        Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  SelectStart can a be value from @ref DCMIPP_Line_Start_Mode
  * @param  SelectMode  can be a value from @ref DCMIPP_Line_Select_Mode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetLinesDecimationConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                           uint32_t SelectStart, uint32_t SelectMode)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_LINE_SELECT_MODE(SelectMode));
  assert_param(IS_DCMIPP_LINE_SELECT_START(SelectStart));

  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE0)
  {
    /* This bit works in conjunction with LSM field (LSM = 1) */
    if ((SelectStart == DCMIPP_OELS_EVEN) && (SelectMode == DCMIPP_LSM_ALTERNATE_2))
    {
      return HAL_ERROR;
    }
    else
    {
      /* Set Lines select Start and Bytes select Mode */
      MODIFY_REG(hdcmipp->Instance->P0PPCR, DCMIPP_P0PPCR_LSM | DCMIPP_P0PPCR_OELS, (SelectStart | SelectMode));
    }
  }
  else
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}
/**
  * @}
  */

/** @defgroup DCMIPP_LimitEvent_Functions DCMIPP Limit Event Functions
@verbatim
===============================================================================
            ##### Limit Event Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing
   (+) HAL_DCMIPP_PIPE_EnableLimitEvent : Enable Limit Event
   (+) HAL_DCMIPP_PIPE_DisableLimitEvent : Disable Limit Event
@endverbatim
  * @{
  */
/**
  * @brief  Define the Data dump limit for the selected Pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  Limit    Data dump Limit.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableLimitEvent(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t Limit)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_DATA_LIMIT(Limit));

  /* Check Parameters */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE0)
  {
    /* Set and enable data limit on Pipe 0 */
    WRITE_REG(hdcmipp->Instance->P0DCLMTR, (Limit << DCMIPP_P0DCLMTR_LIMIT_Pos) | DCMIPP_P0DCLMTR_ENABLE);

    /* Enable Limit Interrupt for pipe0 */
    __HAL_DCMIPP_ENABLE_IT(hdcmipp, DCMIPP_IT_PIPE0_LIMIT);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the the Limit interrupt.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableLimitEvent(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check Parameters */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE0)
  {
    /* Disable data limit on Pipe 0 */
    CLEAR_BIT(hdcmipp->Instance->P0DCLMTR, DCMIPP_P0DCLMTR_ENABLE);

    /* Disable Limit Interrupt for pipe0 */
    __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE0_LIMIT);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/**
  * @brief  Configures the ISP decimation for the specified pipe according to the used parameters.
  * @param  hdcmipp    Pointer to DCMIPP handle
  * @param  Pipe       Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pDecConfig pointer to DCMIPP_DecimationConfTypeDef structure that contains the decimation information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetISPDecimationConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                         const DCMIPP_DecimationConfTypeDef *pDecConfig)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_VRATIO(pDecConfig->VRatio));
  assert_param(IS_DCMIPP_HRATIO(pDecConfig->HRatio));

  /* Check handle validity */
  if ((hdcmipp == NULL) || (pDecConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Set Decimation Type , Vertical and Horizontal Ratio */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    if (Pipe == DCMIPP_PIPE1)
    {
      MODIFY_REG(hdcmipp->Instance->P1DECR, DCMIPP_P1DECR_VDEC | DCMIPP_P1DECR_HDEC,
                 (pDecConfig->VRatio | pDecConfig->HRatio));
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }


  return HAL_OK;
}

/**
  * @brief  Enable the ISP decimation for the specified pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableISPDecimation(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Enable decimation */
  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1DECR, DCMIPP_P1DECR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the ISP decimation for the specified pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableISPDecimation(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Enable decimation */
  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1DECR, DCMIPP_P1DECR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Configures the decimation for the specified pipe according to the used parameters.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pDecConfig pointer to DCMIPP_DecimationConfTypeDef structure that contains the decimation information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetDecimationConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                      const DCMIPP_DecimationConfTypeDef *pDecConfig)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_VRATIO(pDecConfig->VRatio));
  assert_param(IS_DCMIPP_HRATIO(pDecConfig->HRatio));

  /* Check DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    /* Set Decimation Type , Vertical and Horizontal Ratio */
    if (Pipe == DCMIPP_PIPE1)
    {
      MODIFY_REG(hdcmipp->Instance->P1DCCR, DCMIPP_P1DCCR_VDEC | DCMIPP_P1DCCR_HDEC,
                 (pDecConfig->VRatio | pDecConfig->HRatio));
    }
    else if (Pipe == DCMIPP_PIPE2)
    {
      MODIFY_REG(hdcmipp->Instance->P2DCCR, DCMIPP_P2DCCR_VDEC | DCMIPP_P2DCCR_HDEC,
                 (pDecConfig->VRatio | pDecConfig->HRatio));
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Enable the DCMIPP Decimation for the specified pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableDecimation(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Enable decimation */
  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1DCCR, DCMIPP_P1DCCR_ENABLE);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    SET_BIT(hdcmipp->Instance->P2DCCR, DCMIPP_P2DCCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the DCMIPP Decimation for the specified pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableDecimation(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Enable decimation */
  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1DCCR, DCMIPP_P1DCCR_ENABLE);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    CLEAR_BIT(hdcmipp->Instance->P2DCCR, DCMIPP_P2DCCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/** @defgroup DCMIPP_Down_Size_Functions DCMIPP Down Size Functions
@verbatim
===============================================================================
            ##### Down Size Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing
   (+) HAL_DCMIPP_PIPE_SetDownsizeConfig : Set Down Size configuration.
   (+) HAL_DCMIPP_PIPE_DisableDownsize   : Disable Down Size.
   (+) HAL_DCMIPP_PIPE_EnableDownsize    : Enable Down Size.
@endverbatim
  * @{
  */
/**
  * @brief  Configures Downsize for the specified DCMIPP pipe according to the user parameters
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pDownsizeConfig pointer to the DCMIPP_DownsizeTypeDef structure that contains Downsize information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetDownsizeConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                    const DCMIPP_DownsizeTypeDef *pDownsizeConfig)
{
  /* Check handle validity */
  if ((hdcmipp == NULL) || (pDownsizeConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_DOWSIZE_DIV_FACTOR(pDownsizeConfig->HDivFactor));
  assert_param(IS_DCMIPP_DOWSIZE_DIV_FACTOR(pDownsizeConfig->VDivFactor));
  assert_param(IS_DCMIPP_DOWSIZE_RATIO(pDownsizeConfig->HRatio));
  assert_param(IS_DCMIPP_DOWSIZE_RATIO(pDownsizeConfig->VRatio));
  assert_param(IS_DCMIPP_DOWSIZE_SIZE(pDownsizeConfig->HSize));
  assert_param(IS_DCMIPP_DOWSIZE_SIZE(pDownsizeConfig->VSize));

  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    if (Pipe == DCMIPP_PIPE1)
    {
      /* Set Vertical and Horizontal division */
      MODIFY_REG(hdcmipp->Instance->P1DSCR, (DCMIPP_P1DSCR_HDIV | DCMIPP_P1DSCR_VDIV),
                 ((pDownsizeConfig->HDivFactor << DCMIPP_P1DSCR_HDIV_Pos) | \
                  (pDownsizeConfig->VDivFactor << DCMIPP_P1DSCR_VDIV_Pos)));

      /* Set Vertical and Horizontal Ratio */
      MODIFY_REG(hdcmipp->Instance->P1DSRTIOR, DCMIPP_P1DSRTIOR_HRATIO | DCMIPP_P1DSRTIOR_VRATIO,
                 (pDownsizeConfig->HRatio << DCMIPP_P1DSRTIOR_HRATIO_Pos) | \
                 (pDownsizeConfig->VRatio << DCMIPP_P1DSRTIOR_VRATIO_Pos));

      /* Set Downsize Destination size */
      MODIFY_REG(hdcmipp->Instance->P1DSSZR, DCMIPP_P1DSSZR_HSIZE | DCMIPP_P1DSSZR_VSIZE,
                 (pDownsizeConfig->HSize << DCMIPP_P1DSSZR_HSIZE_Pos) | \
                 (pDownsizeConfig->VSize << DCMIPP_P1DSSZR_VSIZE_Pos));
    }
    else if (Pipe == DCMIPP_PIPE2)
    {
      /* Set Vertical and Horizontal division */
      MODIFY_REG(hdcmipp->Instance->P2DSCR, DCMIPP_P2DSCR_HDIV | DCMIPP_P2DSCR_VDIV,
                 (pDownsizeConfig->HDivFactor << DCMIPP_P2DSCR_HDIV_Pos) | \
                 (pDownsizeConfig->VDivFactor << DCMIPP_P2DSCR_VDIV_Pos));

      /* Set Vertical and Horizontal Ratio */
      MODIFY_REG(hdcmipp->Instance->P2DSRTIOR, DCMIPP_P2DSRTIOR_HRATIO | DCMIPP_P2DSRTIOR_VRATIO,
                 (pDownsizeConfig->HRatio << DCMIPP_P2DSRTIOR_HRATIO_Pos) | \
                 (pDownsizeConfig->VRatio << DCMIPP_P2DSRTIOR_VRATIO_Pos));

      /* Set Downsize Destination size */
      MODIFY_REG(hdcmipp->Instance->P2DSSZR, DCMIPP_P2DSSZR_HSIZE | DCMIPP_P2DSSZR_VSIZE,
                 (pDownsizeConfig->HSize << DCMIPP_P2DSSZR_HSIZE_Pos) | \
                 (pDownsizeConfig->VSize << DCMIPP_P2DSSZR_VSIZE_Pos));
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Enable the Downsize for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableDownsize(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check Parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1DSCR, DCMIPP_P1DSCR_ENABLE);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    SET_BIT(hdcmipp->Instance->P2DSCR, DCMIPP_P2DSCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the Downsize for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableDownsize(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check Parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1DSCR, DCMIPP_P1DSCR_ENABLE);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    CLEAR_BIT(hdcmipp->Instance->P2DSCR, DCMIPP_P2DSCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup DCMIPP_Black_Enable_Gamma_Conversion_Functions DCMIPP Enable Gamma Conversion Functions
@verbatim
===============================================================================
            ##### Gamma Conversion Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing
(+) HAL_DCMIPP_PIPE_EnableGammaConversion    : Enable Gamma Conversion.
(+) HAL_DCMIPP_PIPE_DisableGammaConversion   : Disable Gamma Conversion.
(+) HAL_DCMIPP_PIPE_IsEnabledGammaConversion : check if Gamma Conversion enabled.
@endverbatim
  * @{
  */
/**
  * @brief  Enable the Gamma Conversion for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableGammaConversion(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handles validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check Parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1GMCR, DCMIPP_P1GMCR_ENABLE);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    SET_BIT(hdcmipp->Instance->P2GMCR, DCMIPP_P2GMCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the Gamma Conversion for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableGammaConversion(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handles validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check Parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1GMCR, DCMIPP_P1GMCR_ENABLE);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    CLEAR_BIT(hdcmipp->Instance->P2GMCR, DCMIPP_P2GMCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Check if Gamma Conversion is enabled.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledGammaConversion(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    return ((READ_BIT(hdcmipp->Instance->P1GMCR, DCMIPP_P1GMCR_ENABLE) == DCMIPP_P1GMCR_ENABLE) ? 1U : 0U);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    return ((READ_BIT(hdcmipp->Instance->P2GMCR, DCMIPP_P2GMCR_ENABLE) == DCMIPP_P2GMCR_ENABLE) ? 1U : 0U);
  }
  else
  {
    /* State Disabled */
    return 0;
  }
}
/**
  * @}
  */
/** @defgroup DCMIPP_RAW_2_RGB_Functions DCMIPP RAW 2 RGB Functions
@verbatim
===============================================================================
            ##### RAW 2 RGB Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing
(+) HAL_DCMIPP_PIPE_SetISPRawBayer2RGBConfig : Set Raw Bayer to RGB configuration.
(+) HAL_DCMIPP_PIPE_DisableISPRawBayer2RGB   : Disable RAW to RGB.
(+) HAL_DCMIPP_PIPE_EnableISPRawBayer2RGB    : Enable RAW to RGB.
@endverbatim
  * @{
  */
/**
  * @brief  Configures the ISP Raw Bayer to RGB for the specified DCMIPP pipe according to the user parameters
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pRawBayer2RGBConfig pointer to DCMIPP_RawBayer2RGBConfTypeDef structure that contains the Raw Bayer to RGB
  *         information.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetISPRawBayer2RGBConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                           const DCMIPP_RawBayer2RGBConfTypeDef *pRawBayer2RGBConfig)
{
  uint32_t p1dmcr_reg;

  /* Check handles validity */
  if ((hdcmipp == NULL) || (pRawBayer2RGBConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check Parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_RAWBAYER2RGB_RAW_TYPE(pRawBayer2RGBConfig->RawBayerType));
  assert_param(IS_DCMIPP_RAWBAYER2RGB_STRENGTH(pRawBayer2RGBConfig->PeakStrength));
  assert_param(IS_DCMIPP_RAWBAYER2RGB_STRENGTH(pRawBayer2RGBConfig->VLineStrength));
  assert_param(IS_DCMIPP_RAWBAYER2RGB_STRENGTH(pRawBayer2RGBConfig->HLineStrength));
  assert_param(IS_DCMIPP_RAWBAYER2RGB_STRENGTH(pRawBayer2RGBConfig->EdgeStrength));

  if (Pipe == DCMIPP_PIPE1)
  {

    p1dmcr_reg = ((pRawBayer2RGBConfig->RawBayerType)                               | \
                  (pRawBayer2RGBConfig->PeakStrength << DCMIPP_P1DMCR_PEAK_Pos)     | \
                  (pRawBayer2RGBConfig->EdgeStrength << DCMIPP_P1DMCR_EDGE_Pos)     | \
                  (pRawBayer2RGBConfig->VLineStrength << DCMIPP_P1DMCR_LINEV_Pos)   | \
                  (pRawBayer2RGBConfig->HLineStrength << DCMIPP_P1DMCR_LINEH_Pos));


    MODIFY_REG(hdcmipp->Instance->P1DMCR, DCMIPP_P1DMCR_TYPE | DCMIPP_P1DMCR_PEAK | DCMIPP_P1DMCR_LINEV | \
               DCMIPP_P1DMCR_LINEH | DCMIPP_P1DMCR_EDGE, p1dmcr_reg);

  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Enable the ISP Raw Bayer to RGB for the specified DCMIPP pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableISPRawBayer2RGB(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handles validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1DMCR, DCMIPP_P1DMCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the ISP Raw Bayer to RGB for the specified DCMIPP pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableISPRawBayer2RGB(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handles validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1DMCR, DCMIPP_P1DMCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup DCMIPP_Statistic_Removal_Functions DCMIPP Statistic Removal Functions
@verbatim
===============================================================================
            ##### Statistic Removal Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing
   (+) HAL_DCMIPP_PIPE_SetISPRemovalStatisticConfig : Set Statistic Removal Config.
   (+) HAL_DCMIPP_PIPE_EnableISPRemovalStatistic    : Enable Statistic Removal
   (+) HAL_DCMIPP_PIPE_DisableISPRemovalStatistic   : Disable Statistic Removal
@endverbatim
  * @{
  */
/**
  * @brief  Configures the ISP Statistic Removal for the specified DCMIPP pipe.
  * @param  hdcmipp      Pointer to DCMIPP handle
  * @param  Pipe         Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  NbFirstLines number of lines to skip at the top of the image
  * @param  NbLastLines  number of valid image line to keep after the skipped first lines
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetISPRemovalStatisticConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                               uint32_t NbFirstLines, uint32_t NbLastLines)
{
  uint32_t p1srcr_reg;

  /* Check handles validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_NB_FIRST_LINES(NbFirstLines));
  assert_param(IS_DCMIPP_NB_LAST_LINES(NbLastLines));

  if (Pipe == DCMIPP_PIPE1)
  {
    p1srcr_reg = ((NbFirstLines << DCMIPP_P1SRCR_FIRSTLINEDEL_Pos) | (NbLastLines << DCMIPP_P1SRCR_LASTLINE_Pos));

    MODIFY_REG(hdcmipp->Instance->P1SRCR, (DCMIPP_P1SRCR_FIRSTLINEDEL | DCMIPP_P1SRCR_LASTLINE), p1srcr_reg);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Enable the ISP Statisic Removal for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableISPRemovalStatistic(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handles validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1SRCR, DCMIPP_P1SRCR_CROPEN);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the ISP Statisic Removal for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableISPRemovalStatistic(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handles validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1SRCR, DCMIPP_P1SRCR_CROPEN);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup DCMIPP_Bad_Pixel_Removal_Functions DCMIPP Bad Pixel Removal Functions
@verbatim
===============================================================================
            ##### Bad Pixel Removal Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing
   (+) HAL_DCMIPP_PIPE_SetISPBadPixelRemovalConfig : Set Bad Pixel Removal Config.
   (+) HAL_DCMIPP_PIPE_DisableISPBadPixelRemoval   : Disable Bad Pixel Removal
   (+) HAL_DCMIPP_PIPE_EnableISPBadPixelRemoval    : Enable Bad Pixel Removal
@endverbatim
  * @{
  */
/**
  * @brief  Configure the ISP Bad Pixel Removal for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  Strength Specifies the removal strength, can be a value from @ref DCMIPP_Bad_Pixel_Removal_Strength
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetISPBadPixelRemovalConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                              uint32_t Strength)
{
  /* Check handles validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_BAD_PXL_REMOVAL_STRENGTH(Strength));

  if (Pipe == DCMIPP_PIPE1)
  {
    MODIFY_REG(hdcmipp->Instance->P1BPRCR, DCMIPP_P1BPRCR_STRENGTH, Strength << DCMIPP_P1BPRCR_STRENGTH_Pos);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Enable the ISP Bad Pixel Removal for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableISPBadPixelRemoval(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handles validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1BPRCR, DCMIPP_P1BPRCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the ISP Bad Pixel Removal for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableISPBadPixelRemoval(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handles validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1BPRCR, DCMIPP_P1BPRCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup DCMIPP_Color_Conversion_Functions DCMIPP Color Conversion Functions
@verbatim
===============================================================================
            ##### Color Conversion Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing
   (+) HAL_DCMIPP_PIPE_SetISPColorConversionConfig : Set Color conversion config
   (+) HAL_DCMIPP_PIPE_EnableISPColorConversion    : Enable Color Conversion
   (+) HAL_DCMIPP_PIPE_DisableISPColorConversion   : Disable Color Conversion
@endverbatim
  * @{
  */
/**
  * @brief  Configure the ISP Color conversion for the selected DCMIPP Pipe according to the user parameters.
  * @param  hdcmipp                Pointer to DCMIPP handle
  * @param  Pipe                   Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pColorConversionConfig pointer to DCMIPP_ColorConversionConfTypeDef structure that contains
  *                                color conversion information.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetISPColorConversionConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                              const DCMIPP_ColorConversionConfTypeDef
                                                              *pColorConversionConfig)
{
  uint32_t p1cccr_reg;
  uint16_t tmp1;
  uint16_t tmp2;
  int16_t tmp4;
  uint16_t tmp3;

  /* Check handles validity */
  if ((hdcmipp == NULL) || (pColorConversionConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_CLAMP_OUTPUT_SAMPLES(pColorConversionConfig->ClampOutputSamples));
  assert_param(IS_DCMIPP_OUTPUT_SAMPLES_TYPES(pColorConversionConfig->OutputSamplesType));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->RR));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->RG));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->RB));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->RA));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->GR));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->GG));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->GB));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->GA));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->BR));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->BG));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->BB));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->BA));

  if (Pipe == DCMIPP_PIPE1)
  {
    /* Set Clamp and Type */
    p1cccr_reg = ((uint32_t)pColorConversionConfig->ClampOutputSamples << DCMIPP_P1CCCR_CLAMP_Pos) | \
                 ((uint32_t)pColorConversionConfig->OutputSamplesType);

    MODIFY_REG(hdcmipp->Instance->P1CCCR, DCMIPP_P1CCCR_CLAMP | DCMIPP_P1CCCR_TYPE, p1cccr_reg);

    /* Set Coefficient row 1 columns 1 2 3 and the added column of the matrix */
    MODIFY_REG(hdcmipp->Instance->P1CCRR1, DCMIPP_P1CCRR1_RR | DCMIPP_P1CCRR1_RG,
               (((uint32_t)pColorConversionConfig->RR) << DCMIPP_P1CCRR1_RR_Pos) | \
               (((uint32_t)pColorConversionConfig->RG) << DCMIPP_P1CCRR1_RG_Pos));

    if (pColorConversionConfig->RB < 0)
    {
      tmp3 = ((uint16_t)pColorConversionConfig->RB ^ 0x7FFU) + 1U;
      tmp4 = (-1 * (int16_t)tmp3);
      tmp1 = (uint16_t)tmp4;

    }
    else
    {
      tmp1 = (uint16_t)pColorConversionConfig->RB;
    }

    if (pColorConversionConfig->RA < 0)
    {
      tmp3 = ((uint16_t)pColorConversionConfig->RA ^ 0x3FFU) + 1U;
      tmp4 = (-1 * (int16_t)tmp3);
      tmp2 = (uint16_t)tmp4;
    }
    else
    {
      tmp2 = (uint16_t)pColorConversionConfig->RA;
    }

    MODIFY_REG(hdcmipp->Instance->P1CCRR2, DCMIPP_P1CCRR2_RB | DCMIPP_P1CCRR2_RA,
               ((uint32_t)tmp1 << DCMIPP_P1CCRR2_RB_Pos) | ((uint32_t)tmp2 << DCMIPP_P1CCRR2_RA_Pos));


    if (pColorConversionConfig->GG < 0)
    {
      tmp3 = ((uint16_t)pColorConversionConfig->GG ^ 0x7FFU) + 1U;
      tmp4 = (-1 * (int16_t)tmp3);
      tmp1 = (uint16_t)tmp4;
    }
    else
    {
      tmp1 = (uint16_t)pColorConversionConfig->GG;
    }

    if (pColorConversionConfig->GR < 0)
    {
      tmp3 = ((uint16_t)pColorConversionConfig->GR ^ 0x7FFU) + 1U;
      tmp4 = (-1 * (int16_t)tmp3);
      tmp2 = (uint16_t)tmp4;
    }
    else
    {
      tmp2 = (uint16_t)pColorConversionConfig->GR;
    }

    /* Set Coefficient row 2 columns 1 2 3 and the added column of the matrix  */
    MODIFY_REG(hdcmipp->Instance->P1CCGR1, DCMIPP_P1CCGR1_GR | DCMIPP_P1CCGR1_GG,
               ((uint32_t)tmp1 << DCMIPP_P1CCGR1_GG_Pos) | ((uint32_t)tmp2 << DCMIPP_P1CCGR1_GR_Pos));

    if (pColorConversionConfig->GB < 0)
    {
      tmp3 = ((uint16_t)pColorConversionConfig->GB ^ 0x7FFU) + 1U;
      tmp4 = (-1 * (int16_t)tmp3);
      tmp1 = (uint16_t)tmp4;
    }
    else
    {
      tmp1 = (uint16_t)pColorConversionConfig->GB;
    }

    if (pColorConversionConfig->GA < 0)
    {
      tmp3 = ((uint16_t)pColorConversionConfig->GA ^ 0x3FFU) + 1U;
      tmp4 = (-1 * (int16_t)tmp3);
      tmp2 = (uint16_t)tmp4;
    }
    else
    {
      tmp2 = (uint16_t)pColorConversionConfig->GA;
    }

    MODIFY_REG(hdcmipp->Instance->P1CCGR2, DCMIPP_P1CCGR2_GB | DCMIPP_P1CCGR2_GA,
               ((uint32_t)tmp1 << DCMIPP_P1CCGR2_GB_Pos) | ((uint32_t)tmp2 << DCMIPP_P1CCGR2_GA_Pos));

    if (pColorConversionConfig->BR < 0)
    {
      tmp3 = ((uint16_t)pColorConversionConfig->BR ^ 0x7FFU) + 1U;
      tmp4 = (-1 * (int16_t)tmp3);
      tmp1 = (uint16_t)tmp4;
    }
    else
    {
      tmp1 = (uint16_t)pColorConversionConfig->BR;
    }

    if (pColorConversionConfig->BG < 0)
    {
      tmp3 = ((uint16_t)pColorConversionConfig->BG ^ 0x7FFU) + 1U;
      tmp4 = (-1 * (int16_t)tmp3);
      tmp2 = (uint16_t)tmp4;
    }
    else
    {
      tmp2 = (uint16_t)pColorConversionConfig->BG;
    }


    /* Set Coefficient row 3 columns 1 2 3 and the added column of the matrix  */
    MODIFY_REG(hdcmipp->Instance->P1CCBR1, DCMIPP_P1CCBR1_BR | DCMIPP_P1CCBR1_BG,
               ((uint32_t)tmp1 << DCMIPP_P1CCBR1_BR_Pos) | ((uint32_t)tmp2 << DCMIPP_P1CCBR1_BG_Pos));

    if (pColorConversionConfig->BB < 0)
    {
      tmp3 = ((uint16_t)pColorConversionConfig->BB ^ 0x7FFU) + 1U;
      tmp4 = (-1 * (int16_t)tmp3);
      tmp1 = (uint16_t)tmp4;
    }
    else
    {
      tmp1 = (uint16_t)pColorConversionConfig->BB;
    }

    if (pColorConversionConfig->BA < 0)
    {
      tmp3 = ((uint16_t)pColorConversionConfig->BA ^ 0x3FFU) + 1U;
      tmp4 = (-1 * (int16_t)tmp3);
      tmp2 = (uint16_t)tmp4;
    }
    else
    {
      tmp2 = (uint16_t)pColorConversionConfig->BA;
    }

    MODIFY_REG(hdcmipp->Instance->P1CCBR2, DCMIPP_P1CCBR2_BB | DCMIPP_P1CCBR2_BA,
               (((uint32_t)tmp1) << DCMIPP_P1CCBR2_BB_Pos) | (((uint32_t)tmp2) << DCMIPP_P1CCBR2_BA_Pos));
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Enable the ISP Color conversion for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableISPColorConversion(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1CCCR, DCMIPP_P1CCCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Disable the ISP Color conversion for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableISPColorConversion(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1CCCR, DCMIPP_P1CCCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup DCMIPP_YUV_Conversion_Functions DCMIPP YUV Conversion Functions
@verbatim
===============================================================================
            ##### YUV Conversion Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing
   (+) HAL_DCMIPP_PIPE_SetYUVConversionConfig : Set YUV conversion config
   (+) HAL_DCMIPP_PIPE_DisableYUVConversion   : Disable YUV conversion
   (+) HAL_DCMIPP_PIPE_EnableYUVConversion    : Enable YUV conversion
@endverbatim
  * @{
  */
/**
  * @brief  Configure the YUV conversion for the selected DCMIPP Pipe according to the user parameters.
  * @param  hdcmipp                Pointer to DCMIPP handle
  * @param  Pipe                   Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pColorConversionConfig pointer to DCMIPP_ColorConversionConfTypeDef structure that contains
  *                                color conversion information.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetYUVConversionConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                         const DCMIPP_ColorConversionConfTypeDef
                                                         *pColorConversionConfig)
{
  uint32_t p1yuvcr_reg;

  /* Check handles validity */
  if ((hdcmipp == NULL) || (pColorConversionConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_CLAMP_OUTPUT_SAMPLES(pColorConversionConfig->ClampOutputSamples));
  assert_param(IS_DCMIPP_OUTPUT_SAMPLES_TYPES(pColorConversionConfig->OutputSamplesType));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->RR));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->RG));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->RB));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->RA));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->GR));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->GG));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->GB));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->GA));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->BR));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->BG));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->BB));
  assert_param(IS_DCMIPP_COLOR_CONVERSION_COEF(pColorConversionConfig->BA));

  if (Pipe == DCMIPP_PIPE1)
  {
    /* Set Clamp and Type */
    p1yuvcr_reg = (((uint32_t)pColorConversionConfig->OutputSamplesType) | \
                   ((uint32_t)pColorConversionConfig->ClampOutputSamples << DCMIPP_P1YUVCR_CLAMP_Pos));

    MODIFY_REG(hdcmipp->Instance->P1YUVCR, DCMIPP_P1YUVCR_CLAMP | DCMIPP_P1YUVCR_TYPE, p1yuvcr_reg);


    /* Set Coefficient row 1 columns 1 2 3 and the added column of the matrix */
    MODIFY_REG(hdcmipp->Instance->P1YUVRR1, DCMIPP_P1YUVRR1_RR | DCMIPP_P1YUVRR1_RG,
               ((uint32_t)pColorConversionConfig->RR << DCMIPP_P1YUVRR1_RR_Pos) | \
               ((uint32_t)pColorConversionConfig->RG << DCMIPP_P1YUVRR1_RG_Pos));

    MODIFY_REG(hdcmipp->Instance->P1YUVRR2, DCMIPP_P1YUVRR2_RB | DCMIPP_P1YUVRR2_RA,
               ((uint32_t)pColorConversionConfig->RB << DCMIPP_P1YUVRR2_RB_Pos) | \
               ((uint32_t)pColorConversionConfig->RA << DCMIPP_P1YUVRR2_RA_Pos));

    /* Set Coefficient row 2 columns 1 2 3 and the added column of the matrix  */
    MODIFY_REG(hdcmipp->Instance->P1YUVGR1, DCMIPP_P1YUVGR1_GR | DCMIPP_P1YUVGR1_GG,
               ((uint32_t)pColorConversionConfig->GR << DCMIPP_P1YUVGR1_GR_Pos) | \
               ((uint32_t)pColorConversionConfig->GG << DCMIPP_P1YUVGR1_GG_Pos));

    MODIFY_REG(hdcmipp->Instance->P1YUVGR2, DCMIPP_P1YUVGR2_GB | DCMIPP_P1YUVGR2_GA,
               ((uint32_t)pColorConversionConfig->GB << DCMIPP_P1YUVGR2_GB_Pos) |
               ((uint32_t)pColorConversionConfig->GA << DCMIPP_P1YUVGR2_GA_Pos));

    /* Set Coefficient row 3 columns 1 2 3 and the added column of the matrix  */
    MODIFY_REG(hdcmipp->Instance->P1YUVBR1, DCMIPP_P1YUVBR1_BR | DCMIPP_P1YUVBR1_BG,
               ((uint32_t)pColorConversionConfig->BR << DCMIPP_P1YUVBR1_BR_Pos) |
               ((uint32_t)pColorConversionConfig->BG << DCMIPP_P1YUVBR1_BG_Pos));

    MODIFY_REG(hdcmipp->Instance->P1YUVBR2, DCMIPP_P1YUVBR2_BB | DCMIPP_P1YUVBR2_BA,
               ((uint32_t)pColorConversionConfig->BB << DCMIPP_P1YUVBR2_BB_Pos) |
               ((uint32_t)pColorConversionConfig->BA << DCMIPP_P1YUVBR2_BA_Pos));
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Enable the YUV conversion for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableYUVConversion(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1YUVCR, DCMIPP_P1YUVCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Disable the YUV conversion for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableYUVConversion(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1YUVCR, DCMIPP_P1YUVCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @defgroup DCMIPP_Black_Level_Calibration_Functions DCMIPP Black Level Calibration Functions
@verbatim
===============================================================================
            ##### Black level Calibration Functions #####
 ===============================================================================
   [..]  This subsection provides a set of functions allowing
   (+) HAL_DCMIPP_PIPE_SetISPBlackLevelCalibrationConfig : Set Black level Calibration Configuration
   (+) HAL_DCMIPP_PIPE_DisableISPBlackLevelCalibration   : Disable Black level Calibration
   (+) HAL_DCMIPP_PIPE_EnableISPBlackLevelCalibration    : Enable Black level Calibration
@endverbatim
  * @{
  */
/**
  * @brief  Configure the ISP Black Level Calibration for the selected DCMIPP Pipe according to the user parameters.
  * @param  hdcmipp           Pointer to DCMIPP handle
  * @param  Pipe              Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pBlackLevelConfig pointer to DCMIPP_BlackLevelConfTypeDef structure that contains black level
  *                           calibration information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetISPBlackLevelCalibrationConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                                    const DCMIPP_BlackLevelConfTypeDef
                                                                    *pBlackLevelConfig)
{
  /* Check handles validity */
  if ((hdcmipp == NULL) || (pBlackLevelConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    MODIFY_REG(hdcmipp->Instance->P1BLCCR, DCMIPP_P1BLCCR_BLCR | DCMIPP_P1BLCCR_BLCG | DCMIPP_P1BLCCR_BLCB,
               (((uint32_t)pBlackLevelConfig->RedCompBlackLevel << DCMIPP_P1BLCCR_BLCR_Pos) | \
                ((uint32_t)pBlackLevelConfig->GreenCompBlackLevel << DCMIPP_P1BLCCR_BLCG_Pos) | \
                ((uint32_t)pBlackLevelConfig->BlueCompBlackLevel << DCMIPP_P1BLCCR_BLCB_Pos)));
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Enable the ISP Black Level Calibration for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableISPBlackLevelCalibration(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1BLCCR, DCMIPP_P1BLCCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Disable the ISP Black Level Calibration for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableISPBlackLevelCalibration(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1BLCCR, DCMIPP_P1BLCCR_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup DCMIPP_Statistic_Functions DCMIPP Statistic Functions
@verbatim
===============================================================================
            ##### Statistic Extraction Control Functions #####
 ===============================================================================
   [..]  This subsection provides a set of functions allowing
   (+) HAL_DCMIPP_PIPE_SetISPControlStatisticExtractionConfig : Set Statistic Extraction Config.
   (+) HAL_DCMIPP_PIPE_SetISPAreaStatisticExtractionConfig    : Set Statistic Extraction Area Config.
   (+) HAL_DCMIPP_PIPE_EnableISPStatisticExtractionModule     : Enable Statistic Extraction.
   (+) HAL_DCMIPP_PIPE_DisableISPStatisticExtractionModule    : Disable Statistic Extraction Config.
   (+) HAL_DCMIPP_PIPE_EnableISPAreaStatisticExtraction       : Enable  Statistic Extraction Area Config.
   (+) HAL_DCMIPP_PIPE_DisableISPAreaStatisticExtraction      : Disable Statistic Extraction Area Config.
@endverbatim
  * @{
  */
/**
  * @brief  Configure the ISP statistic extraction module for the selected DCMIPP Pipe according to the user parameters.
  * @param  hdcmipp                           Pointer to DCMIPP handle
  * @param  Pipe                              Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  ModuleID                          Specifies the Module ID, can be a value from
  *                                           DCMIPP_Statistics_Extraction_Module_ID.
  * @param  pStatisticExtractionControlConfig Pointer to DCMIPP_StatisticExtractionControlConfTypeDef structure
                                              that contains statistic extraction information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetISPControlStatisticExtractionConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                                         uint8_t ModuleID, const
                                                                         DCMIPP_StatisticExtractionControlConfTypeDef
                                                                         *pStatisticExtractionControlConfig)
{
  uint32_t p1stxcr_reg;

  /* Check handle validity */
  if ((hdcmipp == NULL) || (pStatisticExtractionControlConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_STAT_EXTRACTION_MODULE(ModuleID));
  assert_param(IS_DCMIPP_STAT_EXTRACTION_BINS(pStatisticExtractionControlConfig->Bins));
  assert_param(IS_DCMIPP_STAT_EXTRACTION_SOURCE(pStatisticExtractionControlConfig->Source));
  assert_param(IS_DCMIPP_STAT_EXTRACTION_MODE(pStatisticExtractionControlConfig->Mode));

  if (Pipe == DCMIPP_PIPE1)
  {
    p1stxcr_reg = (pStatisticExtractionControlConfig->Mode) | (pStatisticExtractionControlConfig->Source) | \
                  (pStatisticExtractionControlConfig->Bins);

    switch (ModuleID)
    {
      case DCMIPP_STATEXT_MODULE1:
        MODIFY_REG(hdcmipp->Instance->P1ST1CR, DCMIPP_P1ST1CR_BINS | DCMIPP_P1ST1CR_SRC | \
                   DCMIPP_P1ST1CR_MODE, p1stxcr_reg);
        break;
      case DCMIPP_STATEXT_MODULE2:
        MODIFY_REG(hdcmipp->Instance->P1ST2CR, DCMIPP_P1ST2CR_BINS | DCMIPP_P1ST2CR_SRC | \
                   DCMIPP_P1ST2CR_MODE, p1stxcr_reg);
        break;
      default:
        /* DCMIPP_STATEXT_MODULE3 */
        MODIFY_REG(hdcmipp->Instance->P1ST3CR, DCMIPP_P1ST3CR_BINS | DCMIPP_P1ST3CR_SRC | \
                   DCMIPP_P1ST3CR_MODE, p1stxcr_reg);
        break;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Configures the area for statistics extraction for the selected DCMIPP Pipe according to the user parameters.
  * @param  hdcmipp                        Pointer to DCMIPP handle
  * @param  Pipe                           Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pStatisticExtractionAreaConfig Pointer to DCMIPP_StatisticExtractionAreaConfTypeDef structure
                                           that contains statistic extraction Area information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetISPAreaStatisticExtractionConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                                      const DCMIPP_StatisticExtractionAreaConfTypeDef
                                                                      *pStatisticExtractionAreaConfig)
{
  /* Check handle validity */
  if ((hdcmipp == NULL) || (pStatisticExtractionAreaConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_PIPE_STAT_EXTRACTION_START(pStatisticExtractionAreaConfig->HStart));
  assert_param(IS_DCMIPP_PIPE_STAT_EXTRACTION_START(pStatisticExtractionAreaConfig->VStart));
  assert_param(IS_DCMIPP_PIPE_STAT_EXTRACTION_SIZE(pStatisticExtractionAreaConfig->HSize));
  assert_param(IS_DCMIPP_PIPE_STAT_EXTRACTION_SIZE(pStatisticExtractionAreaConfig->VSize));

  if (Pipe == DCMIPP_PIPE1)
  {
    MODIFY_REG(hdcmipp->Instance->P1STSTR, DCMIPP_P1STSTR_HSTART | DCMIPP_P1STSTR_VSTART,
               (pStatisticExtractionAreaConfig->HStart << DCMIPP_P1STSTR_HSTART_Pos) | \
               (pStatisticExtractionAreaConfig->VStart << DCMIPP_P1STSTR_VSTART_Pos));

    MODIFY_REG(hdcmipp->Instance->P1STSZR, DCMIPP_P1STSZR_HSIZE | DCMIPP_P1STSZR_VSIZE,
               (pStatisticExtractionAreaConfig->HSize << DCMIPP_P1STSZR_HSIZE_Pos) | \
               (pStatisticExtractionAreaConfig->VSize << DCMIPP_P1STSZR_VSIZE_Pos));
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Enable the selected statistic extraction module for the selected DCMIPP Pipe
  * @param  hdcmipp   Pointer to DCMIPP handle
  * @param  Pipe      Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  ModuleID  Specifies the Module ID, can be a value from @ref DCMIPP_Statistics_Extraction_Module_ID.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableISPStatisticExtractionModule(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                                     uint8_t ModuleID)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_STAT_EXTRACTION_MODULE(ModuleID));

  if (Pipe == DCMIPP_PIPE1)
  {
    switch (ModuleID)
    {
      case DCMIPP_STATEXT_MODULE1:
        SET_BIT(hdcmipp->Instance->P1ST1CR, DCMIPP_P1ST1CR_ENABLE);
        break;
      case DCMIPP_STATEXT_MODULE2:
        SET_BIT(hdcmipp->Instance->P1ST2CR, DCMIPP_P1ST2CR_ENABLE);
        break;
      default:
        /* DCMIPP_STATEXT_MODULE3 */
        SET_BIT(hdcmipp->Instance->P1ST3CR, DCMIPP_P1ST3CR_ENABLE);
        break;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the selected statistic extraction module for the selected DCMIPP Pipe
  * @param  hdcmipp   Pointer to DCMIPP handle
  * @param  Pipe      Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  ModuleID  Specifies the Module ID, can be a value from @ref DCMIPP_Statistics_Extraction_Module_ID.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableISPStatisticExtractionModule(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                                      uint8_t ModuleID)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_STAT_EXTRACTION_MODULE(ModuleID));

  if (Pipe == DCMIPP_PIPE1)
  {
    switch (ModuleID)
    {
      case DCMIPP_STATEXT_MODULE1:
        CLEAR_BIT(hdcmipp->Instance->P1ST1CR, DCMIPP_P1ST1CR_ENABLE);
        break;
      case DCMIPP_STATEXT_MODULE2:
        CLEAR_BIT(hdcmipp->Instance->P1ST2CR, DCMIPP_P1ST2CR_ENABLE);
        break;
      case DCMIPP_STATEXT_MODULE3:
        CLEAR_BIT(hdcmipp->Instance->P1ST3CR, DCMIPP_P1ST3CR_ENABLE);
        break;
      default:
        break;
    }

  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Enable the ISP statistic extraction for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableISPAreaStatisticExtraction(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    /* Crop line enable */
    SET_BIT(hdcmipp->Instance->P1STSZR, DCMIPP_P1STSZR_CROPEN);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Disable the ISP statistic extraction for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableISPAreaStatisticExtraction(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1STSZR, DCMIPP_P1STSZR_CROPEN);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @defgroup DCMIPP_Exposure_Control_Functions DCMIPP Exposure Control Functions
@verbatim
===============================================================================
            ##### Exposure Control Functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing
      (+) HAL_DCMIPP_PIPE_SetISPExposureConfig      : Set Exposure configuration.
      (+) HAL_DCMIPP_PIPE_EnableISPExposure         : Enable Exposure configuration.
      (+) HAL_DCMIPP_PIPE_DisableISPExposure        : Disable Exposure configuration.
@endverbatim
  * @{
  */
/**
  * @brief  Configure the ISP Exposure for the selected DCMIPP Pipe according to the user parameters
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  Pipe            Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pExposureConfig pointer to the DCMIPP_ExposureConfTypeDef structure that contains the exposure information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetISPExposureConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                       const DCMIPP_ExposureConfTypeDef *pExposureConfig)
{

  /* Check handle validity */
  if ((hdcmipp == NULL) || (pExposureConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_EXPOSURE_SHF(pExposureConfig->ShiftRed));
  assert_param(IS_DCMIPP_EXPOSURE_SHF(pExposureConfig->ShiftGreen));
  assert_param(IS_DCMIPP_EXPOSURE_SHF(pExposureConfig->ShiftBlue));

  if (Pipe == DCMIPP_PIPE1)
  {
    MODIFY_REG(hdcmipp->Instance->P1EXCR1, DCMIPP_P1EXCR1_SHFR | DCMIPP_P1EXCR1_MULTR,
               (((uint32_t)pExposureConfig->ShiftRed << DCMIPP_P1EXCR1_SHFR_Pos) | \
                ((uint32_t)pExposureConfig->MultiplierRed << DCMIPP_P1EXCR1_MULTR_Pos)));

    WRITE_REG(hdcmipp->Instance->P1EXCR2, (((uint32_t)pExposureConfig->ShiftGreen << DCMIPP_P1EXCR2_SHFG_Pos) | \
                                           ((uint32_t)pExposureConfig->MultiplierGreen << DCMIPP_P1EXCR2_MULTG_Pos) | \
                                           ((uint32_t)pExposureConfig->ShiftBlue << DCMIPP_P1EXCR2_SHFB_Pos) | \
                                           ((uint32_t)pExposureConfig->MultiplierBlue << DCMIPP_P1EXCR2_MULTB_Pos)));
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Enable the ISP Exposure for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableISPExposure(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1EXCR1, DCMIPP_P1EXCR1_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Disable the ISP Exposure for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableISPExposure(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1EXCR1, DCMIPP_P1EXCR1_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup DCMIPP_Contrast_Control_Functions DCMIPP Contrast Control Functions
@verbatim
===============================================================================
            ##### Contrast Control Functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing
      (+) HAL_DCMIPP_PIPE_SetISPCtrlContrastConfig      : Set Contrast configuration.
      (+) HAL_DCMIPP_PIPE_EnableISPCtrlContrast         : Enable Contrast configuration.
      (+) HAL_DCMIPP_PIPE_DisableISPCtrlContrast        : Disable Contrast configuration.
@endverbatim
  * @{
  */
/**
  * @brief  Configure the ISP Contrast for the selected DCMIPP Pipe according to the user parameters
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  Pipe            Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pContrastConfig pointer to the DCMIPP_ContrastConfTypeDef structure that contains contrast information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetISPCtrlContrastConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                           const DCMIPP_ContrastConfTypeDef *pContrastConfig)
{
  /* Check handle validity */
  if ((hdcmipp == NULL) || (pContrastConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_LUMINANCE(pContrastConfig->LUM_0));
  assert_param(IS_DCMIPP_LUMINANCE(pContrastConfig->LUM_32));
  assert_param(IS_DCMIPP_LUMINANCE(pContrastConfig->LUM_64));
  assert_param(IS_DCMIPP_LUMINANCE(pContrastConfig->LUM_96));
  assert_param(IS_DCMIPP_LUMINANCE(pContrastConfig->LUM_128));
  assert_param(IS_DCMIPP_LUMINANCE(pContrastConfig->LUM_160));
  assert_param(IS_DCMIPP_LUMINANCE(pContrastConfig->LUM_192));
  assert_param(IS_DCMIPP_LUMINANCE(pContrastConfig->LUM_224));
  assert_param(IS_DCMIPP_LUMINANCE(pContrastConfig->LUM_256));

  if (Pipe == DCMIPP_PIPE1)
  {

    MODIFY_REG(hdcmipp->Instance->P1CTCR1, DCMIPP_P1CTCR1_LUM0,
               (uint32_t)pContrastConfig->LUM_0 << DCMIPP_P1CTCR1_LUM0_Pos);

    WRITE_REG(hdcmipp->Instance->P1CTCR2, (((uint32_t)pContrastConfig->LUM_32 << DCMIPP_P1CTCR2_LUM1_Pos) |
                                           ((uint32_t)pContrastConfig->LUM_64 << DCMIPP_P1CTCR2_LUM2_Pos) |
                                           ((uint32_t)pContrastConfig->LUM_96 << DCMIPP_P1CTCR2_LUM3_Pos) |
                                           ((uint32_t)pContrastConfig->LUM_128 << DCMIPP_P1CTCR2_LUM4_Pos)));

    WRITE_REG(hdcmipp->Instance->P1CTCR3, (((uint32_t)pContrastConfig->LUM_160 << DCMIPP_P1CTCR3_LUM5_Pos) |
                                           ((uint32_t)pContrastConfig->LUM_192 << DCMIPP_P1CTCR3_LUM6_Pos) |
                                           ((uint32_t)pContrastConfig->LUM_224 << DCMIPP_P1CTCR3_LUM7_Pos) |
                                           ((uint32_t)pContrastConfig->LUM_256 << DCMIPP_P1CTCR3_LUM8_Pos)));
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Enable the ISP Contrast for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableISPCtrlContrast(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1CTCR1, DCMIPP_P1CTCR1_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Disable the ISP Contrast for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableISPCtrlContrast(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check handle validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1CTCR1, DCMIPP_P1CTCR1_ENABLE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup DCMIPP_PeripheralControl_Functions DCMIPP Peripheral Control Functions
@verbatim
===============================================================================
            ##### Peripheral Control Functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing
      (+) HAL_DCMIPP_PIPE_SetFrameRate                     : Set the frame rate.
      (+) HAL_DCMIPP_PIPE_SetCaptureMode                   : Set the capture mode.
      (+) HAL_DCMIPP_PIPE_EnableCapture                    : Enable the capture.
      (+) HAL_DCMIPP_PIPE_SetMemoryAddress                 : Set the destination memory address.
      (+) HAL_DCMIPP_PIPE_PARALLEL_SetInputPixelFormat     : Set input format in parallel mode.
      (+) HAL_DCMIPP_PIPE_SetPitch                         : Set the pitch.
      (+) HAL_DCMIPP_PIPE_SetPixelPackerFormat             : Set Pixel Packer format.
      (+) HAL_DCMIPP_PIPE_CSI_EnableShare                  : Enable sharing between pipes.
      (+) HAL_DCMIPP_PIPE_CSI_DisableShare                 : Disable share.
      (+) HAL_DCMIPP_PIPE_CSI_ForceDataTypeFormat          : Force data type format on CSI.
      (+) HAL_DCMIPP_PIPE_CSI_SetDTMode                    : Set data type mode.
      (+) HAL_DCMIPP_PIPE_CSI_SetDTSelection               : Set data type selection.
      (+) HAL_DCMIPP_PIPE_CSI_EnableHeader                 : Enable Header in CSI.
      (+) HAL_DCMIPP_PIPE_CSI_DisableHeader                : Disable Header in CSI.
      (+)  HAL_DCMIPP_PIPE_CSI_SetVirtualChannelID         : Set virtual channel id.
      (+) HAL_DCMIPP_PARALLEL_SetSyncUnmask                : Set Sync Unmask in Parallel interface.
      (+) HAL_DCMIPP_CSI_SetLineByteCounterConfig          : Set line byte counter Config in CSI.
        (+) HAL_DCMIPP_CSI_EnableLineByteCounter             : Enable line byte counter.
        (+) HAL_DCMIPP_CSI_DisableLineByteCounter            : Disable line byte counter.
      (+) HAL_DCMIPP_CSI_SetTimerConfig                    : Set Timer Config.
        (+) HAL_DCMIPP_CSI_EnableTimer                       : Enable Timer.
        (+) HAL_DCMIPP_CSI_DisableTimer                      : Disable timer
      (+) HAL_DCMIPP_CSI_SetWatchdogCounterConfig          : Set Watch dog counter Config.
      (+) HAL_DCMIPP_PIPE_EnablePAD                        : Enable Padding
      (+) HAL_DCMIPP_PIPE_DisablePAD                       : Disable Padding
      (+) HAL_DCMIPP_PIPE_PARALLEL_EnableComponentsSwap    : Enable component Swap in Parallel Interface
      (+) HAL_DCMIPP_PIPE_PARALLEL_DisableComponentsSwap   : Disable component Swap in Parallel Interface
      (+) HAL_DCMIPP_PIPE_DisableRedBlueSwap               : Disable RED BLUE swap
      (+) HAL_DCMIPP_PIPE_EnableRedBlueSwap                : Enable RED BLUE swap
      (+) HAL_DCMIPP_PIPE_DisableYUVSwap                   : Disable YUV swap
      (+) HAL_DCMIPP_PIPE_EnableYUVSwap                    : Enable YUV swap
      (+) HAL_DCMIPP_PIPE_SetHistogramConfig               : Configure Histogram
      (+) HAL_DCMIPP_PIPE_HistogramEnable                  : Histogram Enable
      (+) HAL_DCMIPP_PIPE_HistogramDisable                 : Histogram Disable
@endverbatim
  * @{
  */
/**
  * @brief  Reconfigure the Frame Rate for the selected pipe
  * @param  hdcmipp    Pointer to DCMIPP handle
  * @param  Pipe       Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  FrameRate  the new Frame Rate, can be a value from @ref DCMIPP_Frame_Rates
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetFrameRate(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t FrameRate)
{
  /* Check Parameters */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_FRAME_RATE(FrameRate));

  /* Set Frame Rate for the Pipe */
  if (Pipe == DCMIPP_PIPE0)
  {
    MODIFY_REG(hdcmipp->Instance->P0FCTCR, DCMIPP_P0FCTCR_FRATE, FrameRate);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    MODIFY_REG(hdcmipp->Instance->P1FCTCR, DCMIPP_P1FCTCR_FRATE, FrameRate);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    MODIFY_REG(hdcmipp->Instance->P2FCTCR, DCMIPP_P2FCTCR_FRATE, FrameRate);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Reconfigure the Pitch for the selected pipe
  * @param  hdcmipp    Pointer to DCMIPP handle
  * @param  Pipe       Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  LinePitch  the new Pitch value.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetPitch(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t LinePitch)
{
  /* Check Parameters */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_PIXEL_PIPE_PITCH(LinePitch));

  /* Set Pixel Pipe Pitch for the Pipe */
  if (Pipe == DCMIPP_PIPE1)
  {
    MODIFY_REG(hdcmipp->Instance->P1PPM0PR, DCMIPP_P1PPM0PR_PITCH, LinePitch << DCMIPP_P1PPM0PR_PITCH_Pos);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    MODIFY_REG(hdcmipp->Instance->P2PPM0PR, DCMIPP_P2PPM0PR_PITCH, LinePitch << DCMIPP_P2PPM0PR_PITCH_Pos);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Reconfigure the PixelPackerFormat for the selected pipe
  * @param  hdcmipp           Pointer to DCMIPP handle
  * @param  Pipe              Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  PixelPackerFormat the new Pixel Packer Format value.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetPixelPackerFormat(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                       uint32_t PixelPackerFormat)
{
  /* Check Parameters */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_PIXEL_PACKER_FORMAT(PixelPackerFormat));

  /* Set Pixel Pipe Pitch for the Pipe */
  if (Pipe == DCMIPP_PIPE1)
  {
    /* Configure the pixel packer */
    MODIFY_REG(hdcmipp->Instance->P1PPCR, DCMIPP_P1PPCR_FORMAT, PixelPackerFormat);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    MODIFY_REG(hdcmipp->Instance->P2PPCR, DCMIPP_P2PPCR_FORMAT, PixelPackerFormat);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Reconfigure Capture Mode for the selected pipe
  * @param  hdcmipp      Pointer to DCMIPP handle
  * @param  Pipe         Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  CaptureMode  the new Capture Mode, can be a value from @ref DCMIPP_Capture_Mode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetCaptureMode(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t CaptureMode)
{
  /* Check Parameters */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_CAPTURE_MODE(CaptureMode));


  /* Set Capture Mode */
  if (Pipe == DCMIPP_PIPE0)
  {
    MODIFY_REG(hdcmipp->Instance->P0FCTCR, DCMIPP_P0FCTCR_CPTMODE, CaptureMode);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    MODIFY_REG(hdcmipp->Instance->P1FCTCR, DCMIPP_P1FCTCR_CPTMODE, CaptureMode);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    MODIFY_REG(hdcmipp->Instance->P2FCTCR, DCMIPP_P2FCTCR_CPTMODE, CaptureMode);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Re-Enable Capture for the selected pipe
  * @param  hdcmipp   Pointer to DCMIPP handle
  * @param  Pipe      Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableCapture(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check Parameters */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Request Capture for the chosen Pipe */

  if (Pipe == DCMIPP_PIPE0)
  {
    SET_BIT(hdcmipp->Instance->P0FCTCR, DCMIPP_P0FCTCR_CPTREQ);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1FCTCR, DCMIPP_P1FCTCR_CPTREQ);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    SET_BIT(hdcmipp->Instance->P2FCTCR, DCMIPP_P2FCTCR_CPTREQ);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Reconfigure the destination memory address for the selected pipe
  * @param  hdcmipp    Pointer to DCMIPP handle
  * @param  Pipe       Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  Memory     the destination address to be changed can be value from @ref DCMIPP_Memory.
  * @param  DstAddress the new destination address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetMemoryAddress(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t Memory,
                                                   uint32_t DstAddress)
{
  /* Check Parameters */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_MEMORY_ADDRESS(Memory));

  /* Request Capture for the chosen Pipe */

  if (Pipe == DCMIPP_PIPE0)
  {
    /* Set Memory0 destination addresses for pipe0 */
    WRITE_REG(hdcmipp->Instance->P0PPM0AR1, DstAddress);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    /* Set Memory0 destination addresses for pipe1 */
    WRITE_REG(hdcmipp->Instance->P1PPM0AR1, DstAddress);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    /* Set Memory0 destination addresses for pipe2 */
    WRITE_REG(hdcmipp->Instance->P2PPM0AR1, DstAddress);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;

}
/**
  * @brief  Reconfigure the input pixel format for the selected pipe
  * @param  hdcmipp           Pointer to DCMIPP handle
  * @param  Pipe              Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  InputPixelFormat  new pixel format, can be a value from @ref DCMIPP_Format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_PARALLEL_SetInputPixelFormat(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                               uint32_t InputPixelFormat)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_FORMAT(InputPixelFormat));

  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE0)
  {
    /* Set Frame Rate */
    MODIFY_REG(hdcmipp->Instance->PRCR, DCMIPP_PRCR_FORMAT, InputPixelFormat);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Set embedded synchronization delimiters unmasks.
  * @param  hdcmipp    Pointer to DCMIPP handle
  * @param  SyncUnmask Pointer to a DCMIPP_EmbeddedSyncUnmaskTypeDef structure that contains
  *                    the embedded synchronization delimiters unmasks.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PARALLEL_SetSyncUnmask(DCMIPP_HandleTypeDef *hdcmipp,
                                                    const DCMIPP_EmbeddedSyncUnmaskTypeDef *SyncUnmask)
{
  uint32_t presur_reg;
  uint32_t prcr_reg;

  /* Check pointer validity */
  if ((hdcmipp == NULL) || (SyncUnmask == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    prcr_reg = hdcmipp->Instance->PRCR;
    /* Check that parallel and Embedded synchronisation modes are configured */
    if (((prcr_reg & DCMIPP_PRCR_ESS) == DCMIPP_SYNCHRO_EMBEDDED) && \
        ((prcr_reg & DCMIPP_PRCR_ENABLE) == DCMIPP_PRCR_ENABLE))
    {
      /* Configure DCMIPP embedded synchronization unmask register */
      presur_reg = (((uint32_t)SyncUnmask->FrameStartUnmask << DCMIPP_PRESUR_FSU_Pos) | \
                    ((uint32_t)SyncUnmask->LineStartUnmask << DCMIPP_PRESUR_LSU_Pos)  | \
                    ((uint32_t)SyncUnmask->LineEndUnmask << DCMIPP_PRESUR_LEU_Pos)    | \
                    ((uint32_t)SyncUnmask->FrameEndUnmask << DCMIPP_PRESUR_FEU_Pos));

      WRITE_REG(hdcmipp->Instance->PRESUR, presur_reg);
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Enable PAD
  * @param  hdcmipp pointer to a DCMIPP_HandleTypeDef structure
  * @param  Pipe pipe where PAD is to be enabled
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnablePAD(DCMIPP_HandleTypeDef *hdcmipp,  uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Verify DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    if (Pipe == DCMIPP_PIPE0)
    {
      SET_BIT(hdcmipp->Instance->P0PPCR, DCMIPP_P0PPCR_PAD);
    }
    else
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Disable PAD
  * @param  hdcmipp pointer to a DCMIPP_HandleTypeDef structure.
  * @param  Pipe pipe where PAD is to be disabled.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisablePAD(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Verify DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    if (Pipe == DCMIPP_PIPE0)
    {
      CLEAR_BIT(hdcmipp->Instance->P0PPCR, DCMIPP_P0PPCR_PAD);
    }
    else
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}


HAL_StatusTypeDef HAL_DCMIPP_PIPE_PARALLEL_EnableComponentsSwap(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if ((Pipe == DCMIPP_PIPE1) || (Pipe == DCMIPP_PIPE2))
  {
    /* Verify DCMIPP State */
    if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
    {
      SET_BIT(hdcmipp->Instance->CMCR, DCMIPP_CMCR_SWAPRB);
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_DCMIPP_PIPE_PARALLEL_DisableComponentsSwap(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if ((Pipe == DCMIPP_PIPE1) || (Pipe == DCMIPP_PIPE2))
  {
    /* Verify DCMIPP State */
    if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
    {
      CLEAR_BIT(hdcmipp->Instance->CMCR, DCMIPP_CMCR_SWAPRB);
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Enable the swapping of red and blue color components for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableRedBlueSwap(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Verify DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    if (Pipe == DCMIPP_PIPE1)
    {
      SET_BIT(hdcmipp->Instance->P1PPCR, DCMIPP_P1PPCR_SWAPRB);
    }
    else if (Pipe == DCMIPP_PIPE2)
    {
      SET_BIT(hdcmipp->Instance->P2PPCR, DCMIPP_P2PPCR_SWAPRB);
    }
    else
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}
/**
  * @brief  Disable the swapping of red and blue color components for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableRedBlueSwap(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Verify DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    if (Pipe == DCMIPP_PIPE1)
    {
      CLEAR_BIT(hdcmipp->Instance->P1PPCR, DCMIPP_P1PPCR_SWAPRB);
    }
    else if (Pipe == DCMIPP_PIPE2)
    {
      CLEAR_BIT(hdcmipp->Instance->P2PPCR, DCMIPP_P2PPCR_SWAPRB);
    }
    else
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}
/**
  * @brief  Enable the swapping of YUV color components for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableYUVSwap(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Verify DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    if (Pipe == DCMIPP_PIPE0)
    {
      SET_BIT(hdcmipp->Instance->P0PPCR, DCMIPP_P0PPCR_SWAPYUV);
    }
    else
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}
/**
  * @brief  Disable the swapping of YUV color components for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableYUVSwap(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Verify DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    if (Pipe == DCMIPP_PIPE0)
    {
      CLEAR_BIT(hdcmipp->Instance->P0PPCR, DCMIPP_P0PPCR_SWAPYUV);
    }
    else
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}
#if defined(DCMIPPP_P1HISTOGRAM_AVAILABLE)
/**
  * @brief  Configure Histogram for the specified DCMIPP pipe.
  * @param  hdcmipp       Pointer to DCMIPP handle
  * @param  Pipe          Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pHistoConfig  Pointer to Histogram Config
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetHistogramConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                     DCMIPP_Histogram_ConfigTypeDef *pHistoConfig)
{
  if ((hdcmipp == NULL) || (pHistoConfig == NULL))
  {
    return HAL_ERROR;
  }

  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_HISTO_BINS(pHistoConfig->Bin));
  assert_param(IS_DCMIPP_HISTO_COMP(pHistoConfig->Components));
  assert_param(IS_DCMIPP_HISTO_HDEC(pHistoConfig->HDec));
  assert_param(IS_DCMIPP_HISTO_VDEC(pHistoConfig->VDec));
  assert_param(IS_DCMIPP_HISTO_PXL_DYN(pHistoConfig->PixelDynamic));
  assert_param(IS_DCMIPP_HISTO_VREG(pHistoConfig->VReg));
  assert_param(IS_DCMIPP_HISTO_HREG(pHistoConfig->HReg));
  assert_param(IS_DCMIPP_HISTO_SRC(pHistoConfig->Source));
  assert_param(IS_DCMIPP_HISTO_VSTART(pHistoConfig->VStart));
  assert_param(IS_DCMIPP_HISTO_HSTART(pHistoConfig->HStart));
  assert_param(IS_DCMIPP_HISTO_VSIZE(pHistoConfig->VSize));
  assert_param(IS_DCMIPP_HISTO_HSIZE(pHistoConfig->HSize));

  if (((pHistoConfig->MemoryAddress) & 0xFU) != 0U)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE1)
  {
    WRITE_REG(hdcmipp->Instance->P1HSCR, (pHistoConfig->Bin << DCMIPP_P1HSCR_BIN_Pos) | \
              (pHistoConfig->PixelDynamic << DCMIPP_P1HSCR_DYN_Pos) | \
              (pHistoConfig->Components << DCMIPP_P1HSCR_COMP_Pos) | (pHistoConfig->VDec << DCMIPP_P1HSCR_VDEC_Pos) | \
              (pHistoConfig->HDec << DCMIPP_P1HSCR_HDEC_Pos) | \
              (pHistoConfig->VReg << DCMIPP_P1HSCR_VREG_Pos) | (pHistoConfig->HReg << DCMIPP_P1HSCR_HREG_Pos) | \
              (pHistoConfig->Source << DCMIPP_P1HSCR_SRC_Pos));

    WRITE_REG(hdcmipp->Instance->P1HSSTR, (pHistoConfig->VStart << DCMIPP_P1HSSTR_VSTART_Pos) | \
              (pHistoConfig->HStart << DCMIPP_P1HSSTR_HSTART_Pos));

    WRITE_REG(hdcmipp->Instance->P1HSSZR, (pHistoConfig->VSize << DCMIPP_P1HSSZR_VSIZE_Pos) | \
              (pHistoConfig->HSize << DCMIPP_P1HSSZR_HSIZE_Pos));

    WRITE_REG(hdcmipp->Instance->P1HSMAR1, pHistoConfig->MemoryAddress);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Enable Histogram for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status.
  */
HAL_StatusTypeDef  HAL_DCMIPP_PIPE_HistogramEnable(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE1)
  {
    SET_BIT(hdcmipp->Instance->P1HSCR, DCMIPP_P1HSCR_EN);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Disable Histogram for the specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status.
  */
HAL_StatusTypeDef  HAL_DCMIPP_PIPE_HistogramDisable(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  if (Pipe == DCMIPP_PIPE1)
  {
    CLEAR_BIT(hdcmipp->Instance->P1HSCR, DCMIPP_P1HSCR_EN);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
#endif /* DCMIPPP_P1HISTOGRAM_AVAILABLE */
/**
  * @}
  */
/** @defgroup DCMIPP_Line_Event_Functions DCMIPP Line Event Functions
@verbatim
===============================================================================
            ##### Line Event Functions #####
===============================================================================
   [..]  This subsection provides a set of functions allowing to configure Line Event
   (+) HAL_DCMIPP_PIPE_EnableLineEvent  : Enable Line event.
   (+) HAL_DCMIPP_PIPE_DisableLineEvent : Disable Line event
@endverbatim
  * @{
  */
/**
  * @brief  Configures the position of the line interrupt.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  Line     Line Interrupt Position.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableLineEvent(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t Line)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_PIPE_MULTILINE(Line));

  if (Pipe == DCMIPP_PIPE0)
  {
    /* Set MultiLine configuration */
    MODIFY_REG(hdcmipp->Instance->P0PPCR, DCMIPP_P0PPCR_LINEMULT, Line);

    /* Enable Multiline Interrupt */
    __HAL_DCMIPP_ENABLE_IT(hdcmipp, DCMIPP_IT_PIPE0_LINE);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    /* Set MultiLine configuration */
    MODIFY_REG(hdcmipp->Instance->P1PPCR, DCMIPP_P1PPCR_LINEMULT, Line);

    /* Enable Multiline Interrupt */
    __HAL_DCMIPP_ENABLE_IT(hdcmipp, DCMIPP_IT_PIPE1_LINE);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    /* Set MultiLine configuration */
    MODIFY_REG(hdcmipp->Instance->P2PPCR, DCMIPP_P2PPCR_LINEMULT, Line);

    /* Enable Multiline Interrupt */
    __HAL_DCMIPP_ENABLE_IT(hdcmipp, DCMIPP_IT_PIPE2_LINE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Disable the the line event interrupt.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableLineEvent(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Disable Multiline Interrupt */
  if (Pipe == DCMIPP_PIPE0)
  {
    __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE0_LINE);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE1_LINE);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    __HAL_DCMIPP_DISABLE_IT(hdcmipp, DCMIPP_IT_PIPE2_LINE);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup DCMIPP_PeripheralControl_Functions DCMIPP Peripheral Control Functions
  * @{
  */
/**
  * @brief  Enable Share between DCMIPP_PIPE1 and DCMIPP_PIPE2
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_CSI_EnableShare(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE2)
  {
    /* Pipe2 receives the same data as Pipe1 */
    CLEAR_BIT(hdcmipp->Instance->P1FSCR, DCMIPP_P1FSCR_PIPEDIFF);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Disable Share between DCMIPP_PIPE1 and DCMIPP_PIPE2
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_CSI_DisableShare(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE2)
  {
    /* Differentiates Pipe2 from pipe1 */
    SET_BIT(hdcmipp->Instance->P1FSCR, DCMIPP_P1FSCR_PIPEDIFF);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Force Data Type Format for the selected Pipe
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  Pipe            Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  DataTypeFormat  Specifies the Data Type Format, can be a value from @ref DCMIPP_DataType
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_CSI_ForceDataTypeFormat(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                          uint32_t DataTypeFormat)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_DATA_TYPE(DataTypeFormat));

  if (Pipe == DCMIPP_PIPE1)
  {
    /* Force data type format */
    MODIFY_REG(hdcmipp->Instance->P1FSCR, DCMIPP_P1FSCR_FDTF,  DataTypeFormat << DCMIPP_P1FSCR_FDTF_Pos);

    /* Force data type format enable */
    SET_BIT(hdcmipp->Instance->P1FSCR, DCMIPP_P1FSCR_FDTFEN);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    /* Check that PIPEDIFF is enabled */
    if ((hdcmipp->Instance->P2FSCR & DCMIPP_P1FSCR_PIPEDIFF) == DCMIPP_P1FSCR_PIPEDIFF)
    {
      /* Force data type format */
      MODIFY_REG(hdcmipp->Instance->P2FSCR, DCMIPP_P1FSCR_FDTF,  DataTypeFormat << DCMIPP_P1FSCR_FDTF_Pos);

      /* Force data type format enable */
      SET_BIT(hdcmipp->Instance->P2FSCR, DCMIPP_P1FSCR_FDTFEN);
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Reconfigure the Data Type Mode
  * @param  hdcmipp       Pointer to DCMIPP handle
  * @param  Pipe          Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  DataTypeMode  Specifies the Data Type Mode, can be a value from @ref DCMIPP_DataTypeMode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_CSI_SetDTMode(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t DataTypeMode)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_DATA_TYPE_MODE(DataTypeMode));

  if (Pipe == DCMIPP_PIPE0)
  {
    MODIFY_REG(hdcmipp->Instance->P0FSCR, DCMIPP_P0FSCR_DTMODE,  DataTypeMode << DCMIPP_P0FSCR_DTMODE_Pos);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    MODIFY_REG(hdcmipp->Instance->P1FSCR, DCMIPP_P1FSCR_DTMODE,  DataTypeMode << DCMIPP_P1FSCR_DTMODE_Pos);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Reconfigure the Data Type Selection
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Pipe        Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  DataTypeID  Specifies the Data Type ID, can be a value from @ref DCMIPP_DataTypeSelection
  * @param  DataType    Specifies the Data Type Format, can be a value from @ref DCMIPP_DataType
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_CSI_SetDTSelection(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t DataTypeID,
                                                     uint32_t DataType)
{
  uint32_t pxfscr_dtid_Msk;

  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_DATA_TYPE(DataType));

  if (DataTypeID == DCMIPP_DTSELECT_IDA)
  {
    pxfscr_dtid_Msk = DCMIPP_P0FSCR_DTIDA_Msk;
  }
  else /* DATA_TYPE_SELECTION_IDB */
  {
    pxfscr_dtid_Msk = DCMIPP_P0FSCR_DTIDB_Pos;
  }

  if (Pipe == DCMIPP_PIPE0)
  {
    MODIFY_REG(hdcmipp->Instance->P0FSCR, pxfscr_dtid_Msk,  DataType << DataTypeID);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    MODIFY_REG(hdcmipp->Instance->P1FSCR, pxfscr_dtid_Msk,  DataType << DataTypeID);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    if (DataTypeID == DCMIPP_DTSELECT_IDA)
    {
      MODIFY_REG(hdcmipp->Instance->P2FSCR, pxfscr_dtid_Msk,  DataType << DataTypeID);
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Enable CSI Header dump for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_CSI_EnableHeader(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE0)
  {
    SET_BIT(hdcmipp->Instance->P0PPCR, DCMIPP_P0PPCR_HEADEREN);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Disable CSI Header dump for the selected DCMIPP Pipe
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_CSI_DisableHeader(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE0)
  {
    CLEAR_BIT(hdcmipp->Instance->P0PPCR, DCMIPP_P0PPCR_HEADEREN);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Set Virtual ChannelID of the pipe
  * @param  hdcmipp              Pointer to DCMIPP handle
  * @param  Pipe                 Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  VirtualChannelID     Virtual channel ID
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_DCMIPP_PIPE_CSI_SetVirtualChannelID(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                           uint32_t VirtualChannelID)
{
  if (Pipe == DCMIPP_PIPE0)
  {
    /* Virtual channel ID of the CSI flow for pipe0 */
    MODIFY_REG(hdcmipp->Instance->P0FSCR, DCMIPP_P0FSCR_VC, VirtualChannelID << DCMIPP_P0FSCR_VC_Pos);
  }
  else if (Pipe == DCMIPP_PIPE1)
  {
    /* Virtual channel ID of the CSI flow for pipe1 */
    MODIFY_REG(hdcmipp->Instance->P1FSCR, DCMIPP_P1FSCR_VC, VirtualChannelID << DCMIPP_P1FSCR_VC_Pos);
  }
  else if (Pipe == DCMIPP_PIPE2)
  {
    /* Virtual channel ID of the CSI flow for pipe2 */
    MODIFY_REG(hdcmipp->Instance->P2FSCR, DCMIPP_P2FSCR_VC, VirtualChannelID << DCMIPP_P2FSCR_VC_Pos);
  }
  else
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup DCMIPP_Frame_Counter_Functions DCMIPP Frame Counter Functions
@verbatim
===============================================================================
            ##### Frame Counter Functions #####
===============================================================================
    [..]  This subsection provides a set of functions allowing
    (+) HAL_DCMIPP_PIPE_SetFrameCounterConfig : Set Frame counter configuration
    (+) HAL_DCMIPP_PIPE_ResetFrameCounter     : Reset Frame Counter
    (+) HAL_DCMIPP_PIPE_ReadFrameCounter      : Read Frame Counter
@endverbatim
  * @{
  */
/**
  * @brief  Associate the frame counter to the selected DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetFrameCounterConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check pointer validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check the DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    /* Configure Pipe Selection for the frame counter */
    MODIFY_REG(hdcmipp->Instance->CMCR, DCMIPP_CMCR_PSFC, Pipe << DCMIPP_CMCR_PSFC_Pos);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Reset the DCMIPP Pipe frame counter
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_ResetFrameCounter(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{

  /* Check pointer validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check the DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    /* Clear Frame counter */
    SET_BIT(hdcmipp->Instance->CMCR, DCMIPP_CMCR_CFC);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Read the DCMIPP frame counter
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pCounter pointer to store the value of the frame counter
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_ReadFrameCounter(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                   uint32_t *pCounter)
{

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check pointer validity */
  if ((hdcmipp == NULL) || (pCounter == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    /* Read frame counter */
    *pCounter = READ_REG(hdcmipp->Instance->CMFRCR);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @defgroup DCMIPP_Data_Counter_Functions DCMIPP Data Counter Functions
  * @{
  */
/**
  * @brief  Read Number of data dumped during the frame.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pCounter pointer to amount of word transferred
  * @note   Data Counter is available only on DCMIPP_PIPE0. The counter saturates at 0x3FFFFFF.
  * @note   Granularity is 32-bit for all the formats except for the
  *         byte stream formats (e.g. JPEG) having byte granularity
  * @retval Status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_GetDataCounter(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                 uint32_t *pCounter)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check pointer validity */
  if ((hdcmipp == NULL) || (pCounter == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    /* Read  Pipe0 dump counter register */
    *pCounter = READ_REG(hdcmipp->Instance->P0DCCNTR);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Get the number of the corrected Bad Pixel in the last frame
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pCounter pointer receiving the number of corrected bad pixels
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_GetISPRemovedBadPixelCounter(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                               uint32_t *pCounter)
{
  /* Check handles validity */
  if ((hdcmipp == NULL) || (pCounter == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check the DCMIPP State */
  if (hdcmipp->State == HAL_DCMIPP_STATE_READY)
  {
    *pCounter = READ_REG(hdcmipp->Instance->P1BPRSR & DCMIPP_P1BPRSR_BADCNT);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Get the Statistic accumulated value for the selected module
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  ModuleID Specifies the Module ID, can be a value from @ref DCMIPP_Statistics_Extraction_Module_ID.
  * @param  pCounter pointer to receive the accumulated value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_GetISPAccumulatedStatisticsCounter(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                                     uint8_t ModuleID, uint32_t *pCounter)
{

  /* Check handle validity */
  if ((hdcmipp == NULL) || (pCounter == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));
  assert_param(IS_DCMIPP_STAT_EXTRACTION_MODULE(ModuleID));

  if (Pipe == DCMIPP_PIPE1)
  {
    switch (ModuleID)
    {
      case DCMIPP_STATEXT_MODULE1:
        *pCounter = (READ_REG(hdcmipp->Instance->P1ST1SR & DCMIPP_P1ST1SR_ACCU));
        break;
      case DCMIPP_STATEXT_MODULE2:
        *pCounter = (READ_REG(hdcmipp->Instance->P1ST2SR & DCMIPP_P1ST2SR_ACCU));
        break;
      case DCMIPP_STATEXT_MODULE3:
        *pCounter = (READ_REG(hdcmipp->Instance->P1ST3SR & DCMIPP_P1ST3SR_ACCU));
        break;
      default:
        break;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @brief  Get the current operating mode of the DCMIPP
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval Returns  the current operating mode of the DCMIPP can be a value from @ref DCMIPP_modes.
  */
uint32_t HAL_DCMIPP_GetMode(const DCMIPP_HandleTypeDef *hdcmipp)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));

  /* Read the configured Mode */
  return READ_BIT(hdcmipp->Instance->CMCR, DCMIPP_CMCR_INSEL) ;
}
/**
  * @}
  */
/** @defgroup DCMIPP_Exported_Functions_Group6 DCMIPP Get Config functions
@verbatim
===============================================================================
            ##### Get Config Functions #####
===============================================================================
  [..]  This subsection provides a set of functions allowing to Get the configuration.
@endverbatim
  * @{
  */
/**
  * @brief  Retrieve the ISP decimation configuration for a specified DCMIPP pipe.
  * @param  hdcmipp      Pointer to DCMIPP handle
  * @param  Pipe         Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pDecConfig   Pointer to a DCMIPP_DecimationConfTypeDef structure that will be
  *                      filled with the decimation configuration of the specified pipe.
  * @retval None
  */
void HAL_DCMIPP_PIPE_GetISPDecimationConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                            DCMIPP_DecimationConfTypeDef *pDecConfig)
{
  uint32_t p1decr;
  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    p1decr = READ_REG(hdcmipp->Instance->P1DECR);
    pDecConfig->HRatio = (p1decr & DCMIPP_P1DECR_HDEC);
    pDecConfig->VRatio = (p1decr & DCMIPP_P1DECR_VDEC);
  }
}

/**
  * @brief  Retrieve the ISP black level calibration configuration for a specified DCMIPP pipe.
  * @param  hdcmipp            Pointer to DCMIPP handle
  * @param  Pipe               Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pBlackLevelConfig  Pointer to a DCMIPP_BlackLevelConfTypeDef structure that will be
  *                            filled with the black level calibration configuration of the specified pipe.
  * @retval None
  */
void HAL_DCMIPP_PIPE_GetISPBlackLevelCalibrationConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                       DCMIPP_BlackLevelConfTypeDef *pBlackLevelConfig)
{
  uint32_t p1blccr_reg;
  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    p1blccr_reg = READ_REG(hdcmipp->Instance->P1BLCCR);
    pBlackLevelConfig->BlueCompBlackLevel = (uint8_t)((p1blccr_reg & DCMIPP_P1BLCCR_BLCB) >> DCMIPP_P1BLCCR_BLCB_Pos);
    pBlackLevelConfig->GreenCompBlackLevel = (uint8_t)((p1blccr_reg & DCMIPP_P1BLCCR_BLCG) >> DCMIPP_P1BLCCR_BLCG_Pos);
    pBlackLevelConfig->RedCompBlackLevel = (uint8_t)((p1blccr_reg & DCMIPP_P1BLCCR_BLCR) >> DCMIPP_P1BLCCR_BLCR_Pos);
  }
}
/**
  * @brief  Retrieve the ISP bad pixel removal strength configuration for a specified DCMIPP pipe.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval  The strength of the bad pixel removal process.
  */
uint32_t HAL_DCMIPP_PIPE_GetISPBadPixelRemovalConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  return (((READ_REG(hdcmipp->Instance->P1BPRCR)) & DCMIPP_P1BPRCR_STRENGTH) >> DCMIPP_P1BPRCR_STRENGTH_Pos);
}
/**
  * @brief  Retrieve the ISP control statistic extraction configuration for a specified DCMIPP pipe and module.
  * @param  hdcmipp                             Pointer to DCMIPP handle
  * @param  Pipe                                Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  ModuleID                            Specifies the Module ID, can be a value from
  *                                             DCMIPP_Statistics_Extraction_Module_ID.
  * @param  pStatisticExtractionControlConfig   Pointer to a DCMIPP_StatisticExtractionConfTypeDef structure
  *                                             that will be filled with the statistic extraction configuration
  *                                             of the specified module.
  * @retval None
  */
void HAL_DCMIPP_PIPE_GetISPControlStatisticExtractionConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                            uint8_t ModuleID,
                                                            DCMIPP_StatisticExtractionControlConfTypeDef
                                                            *pStatisticExtractionControlConfig)
{
  uint32_t tmp;
  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    switch (ModuleID)
    {
      case DCMIPP_STATEXT_MODULE1:
        tmp = READ_REG(hdcmipp->Instance->P1ST1CR);
        break;
      case DCMIPP_STATEXT_MODULE2:
        tmp = READ_REG(hdcmipp->Instance->P1ST2CR);
        break;
      default:
        /* DCMIPP_STATEXT_MODULE3 */
        tmp = READ_REG(hdcmipp->Instance->P1ST3CR);
        break;
    }

    pStatisticExtractionControlConfig->Bins   = ((tmp & DCMIPP_P1ST1CR_BINS));
    pStatisticExtractionControlConfig->Mode   = ((tmp & DCMIPP_P1ST1CR_MODE));
    pStatisticExtractionControlConfig->Source = ((tmp & DCMIPP_P1ST1CR_SRC));
  }
}
/**
  * @brief  Retrieve the ISP area statistic extraction configuration for a specified DCMIPP pipe.
  * @param  hdcmipp                          Pointer to DCMIPP handle
  * @param  Pipe                             Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes.
  * @param  pStatisticExtractionAreaConfig   Pointer to a DCMIPP_StatisticExtractionAreaConfTypeDef structure
  *                                          that will be filled with the area statistic extraction configuration
  *                                          of the specified pipe.
  * @retval None
  */
void HAL_DCMIPP_PIPE_GetISPAreaStatisticExtractionConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                         DCMIPP_StatisticExtractionAreaConfTypeDef
                                                         *pStatisticExtractionAreaConfig)
{
  uint32_t tmp;
  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    tmp = READ_REG(hdcmipp->Instance->P1STSTR);
    pStatisticExtractionAreaConfig->HStart = ((tmp & DCMIPP_P1STSTR_HSTART) >> DCMIPP_P1STSTR_HSTART_Pos);
    pStatisticExtractionAreaConfig->VStart = ((tmp & DCMIPP_P1STSTR_VSTART) >> DCMIPP_P1STSTR_VSTART_Pos);

    tmp = READ_REG(hdcmipp->Instance->P1STSZR);
    pStatisticExtractionAreaConfig->VSize  = ((tmp & DCMIPP_P1STSZR_VSIZE) >> DCMIPP_P1STSZR_VSIZE_Pos);
    pStatisticExtractionAreaConfig->HSize  = ((tmp & DCMIPP_P1STSZR_HSIZE) >> DCMIPP_P1STSZR_HSIZE_Pos);
  }
}
/**
  * @brief  Retrieve the ISP control contrast configuration for a specified DCMIPP pipe.
  * @param  hdcmipp          Pointer to DCMIPP handle
  * @param  Pipe             Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pContrastConfig  Pointer to a DCMIPP_ContrastConfTypeDef structure that will be
  *                          filled with the contrast configuration of the specified pipe.
  * @retval None
  */
void HAL_DCMIPP_PIPE_GetISPCtrlContrastConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                              DCMIPP_ContrastConfTypeDef *pContrastConfig)
{
  uint32_t tmp;

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    tmp = READ_REG(hdcmipp->Instance->P1CTCR1);

    pContrastConfig->LUM_0    = (uint8_t)((tmp & DCMIPP_P1CTCR1_LUM0) >> DCMIPP_P1CTCR1_LUM0_Pos);

    tmp = READ_REG(hdcmipp->Instance->P1CTCR2);
    pContrastConfig->LUM_32   = (uint8_t)((tmp & DCMIPP_P1CTCR2_LUM1) >> DCMIPP_P1CTCR2_LUM1_Pos);
    pContrastConfig->LUM_64   = (uint8_t)((tmp & DCMIPP_P1CTCR2_LUM2) >> DCMIPP_P1CTCR2_LUM2_Pos);
    pContrastConfig->LUM_96   = (uint8_t)((tmp & DCMIPP_P1CTCR2_LUM3) >> DCMIPP_P1CTCR2_LUM3_Pos);
    pContrastConfig->LUM_128  = (uint8_t)((tmp & DCMIPP_P1CTCR2_LUM4) >> DCMIPP_P1CTCR2_LUM4_Pos);

    tmp = READ_REG(hdcmipp->Instance->P1CTCR3);
    pContrastConfig->LUM_160  = (uint8_t)((tmp & DCMIPP_P1CTCR3_LUM5) >> DCMIPP_P1CTCR3_LUM5_Pos);
    pContrastConfig->LUM_192  = (uint8_t)((tmp & DCMIPP_P1CTCR3_LUM6) >> DCMIPP_P1CTCR3_LUM6_Pos);
    pContrastConfig->LUM_224  = (uint8_t)((tmp & DCMIPP_P1CTCR3_LUM7) >> DCMIPP_P1CTCR3_LUM7_Pos);
    pContrastConfig->LUM_256  = (uint8_t)((tmp & DCMIPP_P1CTCR3_LUM8) >> DCMIPP_P1CTCR3_LUM8_Pos);
  }
}
/**
  * @brief  Retrieve the ISP exposure configuration for a specified DCMIPP pipe.
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  Pipe            Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pExposureConfig Pointer to a DCMIPP_ExposureConfTypeDef structure that will be
  *                         filled with the exposure configuration of the specified pipe.
  * @retval None
  */
void HAL_DCMIPP_PIPE_GetISPExposureConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                          DCMIPP_ExposureConfTypeDef *pExposureConfig)
{
  uint32_t tmp;

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    tmp = READ_REG(hdcmipp->Instance->P1EXCR2);

    pExposureConfig->MultiplierBlue  = (uint8_t)((tmp & DCMIPP_P1EXCR2_MULTB) >> DCMIPP_P1EXCR2_MULTB_Pos);
    pExposureConfig->ShiftBlue       = (uint8_t)((tmp & DCMIPP_P1EXCR2_SHFB) >> DCMIPP_P1EXCR2_SHFB_Pos);
    pExposureConfig->ShiftGreen      = (uint8_t)((tmp & DCMIPP_P1EXCR2_SHFG) >> DCMIPP_P1EXCR2_SHFG_Pos);
    pExposureConfig->MultiplierGreen = (uint8_t)((tmp & DCMIPP_P1EXCR2_MULTG) >> DCMIPP_P1EXCR2_MULTG_Pos);

    tmp = READ_REG(hdcmipp->Instance->P1EXCR1);

    pExposureConfig->MultiplierRed   = (uint8_t)((tmp & DCMIPP_P1EXCR1_MULTR) >> DCMIPP_P1EXCR1_MULTR_Pos);
    pExposureConfig->ShiftRed        = (uint8_t)((tmp & DCMIPP_P1EXCR1_SHFR) >> DCMIPP_P1EXCR1_SHFR_Pos);
  }
}
/**
  * @brief  Retrieve the ISP Raw Bayer to RGB conversion configuration for a specified DCMIPP pipe.
  * @param  hdcmipp             Pointer to DCMIPP handle
  * @param  Pipe                Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pRawBayer2RGBConfig Pointer to a DCMIPP_RawBayer2RGBConfTypeDef structure that will be
  *                             filled with the Raw Bayer to RGB conversion configuration of the specified pipe.
  * @retval None
  */
void HAL_DCMIPP_PIPE_GetISPRawBayer2RGBConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                              DCMIPP_RawBayer2RGBConfTypeDef *pRawBayer2RGBConfig)
{
  uint32_t p1dmcr_reg;
  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    p1dmcr_reg = READ_REG(hdcmipp->Instance->P1DMCR);

    pRawBayer2RGBConfig->EdgeStrength  = ((p1dmcr_reg & DCMIPP_P1DMCR_EDGE) >> DCMIPP_P1DMCR_EDGE_Pos);
    pRawBayer2RGBConfig->HLineStrength = ((p1dmcr_reg & DCMIPP_P1DMCR_LINEH) >> DCMIPP_P1DMCR_LINEH_Pos);
    pRawBayer2RGBConfig->PeakStrength  = ((p1dmcr_reg & DCMIPP_P1DMCR_PEAK) >> DCMIPP_P1DMCR_PEAK_Pos);
    pRawBayer2RGBConfig->RawBayerType  = (p1dmcr_reg & DCMIPP_P1DMCR_TYPE);
    pRawBayer2RGBConfig->VLineStrength = ((p1dmcr_reg & DCMIPP_P1DMCR_LINEV) >> DCMIPP_P1DMCR_LINEV_Pos);
  }
}
/**
  * @brief  Retrieve the ISP color conversion configuration for a specified DCMIPP pipe.
  * @param  hdcmipp                 Pointer to DCMIPP handle
  * @param  Pipe                    Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  pColorConversionConfig  Pointer to a DCMIPP_ColorConversionConfTypeDef structure that will be
  *                                 filled with the color conversion configuration of the specified pipe.
  * @retval None
  */
void HAL_DCMIPP_PIPE_GetISPColorConversionConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                 DCMIPP_ColorConversionConfTypeDef *pColorConversionConfig)
{
  uint16_t tmp;
  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    tmp = (uint16_t)READ_REG(hdcmipp->Instance->P1CCCR);

    UNUSED(tmp);

    pColorConversionConfig->ClampOutputSamples = (uint8_t)((tmp & DCMIPP_P1CCCR_CLAMP) >> DCMIPP_P1YUVCR_CLAMP_Pos);
    pColorConversionConfig->OutputSamplesType  = (uint8_t)((tmp & DCMIPP_P1CCCR_TYPE) >> DCMIPP_P1YUVCR_TYPE_Pos);

    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCRR1, DCMIPP_P1CCRR1_RG) >> DCMIPP_P1CCRR1_RG_Pos);

    if (CHECK_SIGNED11(tmp) == 0x400U)
    {
      pColorConversionConfig->RG = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x7FFU)) ;
    }
    else
    {
      pColorConversionConfig->RG = (int16_t)(uint16_t)tmp;
    }

    /* Get Coefficient row 1 columns 1 2 3 and the added column of the matrix */
    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCRR1, DCMIPP_P1CCRR1_RR) >> DCMIPP_P1CCRR1_RR_Pos);

    if (CHECK_SIGNED11(tmp) == 0x400U)
    {
      pColorConversionConfig->RR = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x7FFU));
    }
    else
    {
      pColorConversionConfig->RR = (int16_t)(uint16_t)tmp;
    }

    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCRR2, DCMIPP_P1CCRR2_RA) >> DCMIPP_P1CCRR2_RA_Pos);

    if (CHECK_SIGNED10(tmp) == 0x200U)
    {
      pColorConversionConfig->RA = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x3FFU));
    }
    else
    {
      pColorConversionConfig->RA = (int16_t)(uint16_t)tmp;
    }

    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCRR2, DCMIPP_P1CCRR2_RB) >> DCMIPP_P1CCRR2_RB_Pos);

    if (CHECK_SIGNED11(tmp) == 0x400U)
    {
      pColorConversionConfig->RB = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x7FFU));
    }
    else
    {
      pColorConversionConfig->RB = (int16_t)(uint16_t)tmp;
    }

    /* Get Coefficient row 2 columns 1 2 3 and the added column of the matrix  */
    if (CHECK_SIGNED11(tmp) == 0x400U)
    {
      pColorConversionConfig->RB = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x7FFU));
    }
    else
    {
      pColorConversionConfig->RB = (int16_t)(uint16_t)tmp;
    }

    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCGR1, DCMIPP_P1CCGR1_GG) >> DCMIPP_P1CCGR1_GG_Pos);
    if (CHECK_SIGNED11(tmp) == 0x400U)
    {
      pColorConversionConfig->GG = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x7FFU));
    }
    else
    {
      pColorConversionConfig->GG = (int16_t)(uint16_t)tmp;
    }

    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCGR1, DCMIPP_P1CCGR1_GR) >> DCMIPP_P1CCGR1_GR_Pos);
    if (CHECK_SIGNED11(tmp) == 0x400U)
    {
      pColorConversionConfig->GR = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x7FFU));
    }
    else
    {
      pColorConversionConfig->GR = (int16_t)(uint16_t)tmp;
    }

    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCGR2, DCMIPP_P1CCGR2_GA) >> DCMIPP_P1CCGR2_GA_Pos);
    if (CHECK_SIGNED10(tmp) == 0x200U)
    {
      pColorConversionConfig->GA = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x3FFU));
    }
    else
    {
      pColorConversionConfig->GA = (int16_t)(uint16_t)tmp;
    }

    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCGR2, DCMIPP_P1CCGR2_GB) >> DCMIPP_P1CCGR2_GB_Pos);
    if (CHECK_SIGNED11(tmp) == 0x400U)
    {
      pColorConversionConfig->GB = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x7FFU));
    }
    else
    {
      pColorConversionConfig->GB = (int16_t)(uint16_t)tmp;
    }

    /* Get Coefficient row 3 columns 1 2 3 and the added column of the matrix  */
    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCBR2, DCMIPP_P1CCBR2_BA) >> DCMIPP_P1CCBR2_BA_Pos);
    if (CHECK_SIGNED10(tmp) == 0x200U)
    {
      pColorConversionConfig->BA = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x3FFU));
    }
    else
    {
      pColorConversionConfig->BA = (int16_t)(uint16_t)tmp;
    }

    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCBR2, DCMIPP_P1CCBR2_BB) >> DCMIPP_P1CCBR2_BB_Pos);
    if (CHECK_SIGNED11(tmp) == 0x400U)
    {
      pColorConversionConfig->BB = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x7FFU));
    }
    else
    {
      pColorConversionConfig->BB = (int16_t)(uint16_t)tmp;
    }

    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCBR1, DCMIPP_P1CCBR1_BG) >> DCMIPP_P1CCBR1_BG_Pos);
    if (CHECK_SIGNED11(tmp) == 0x400U)
    {
      pColorConversionConfig->BG = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x7FFU));
    }
    else
    {
      pColorConversionConfig->BG = (int16_t)(uint16_t)tmp;
    }

    tmp = (uint16_t)(READ_FIELD(hdcmipp->Instance->P1CCBR1, DCMIPP_P1CCBR1_BR) >> DCMIPP_P1CCBR1_BR_Pos);
    if (CHECK_SIGNED11(tmp) == 0x400U)
    {
      pColorConversionConfig->BR = (-(int16_t)(uint16_t)((tmp - 1U) ^ 0x7FFU));
    }
    else
    {
      pColorConversionConfig->BR = (int16_t)(uint16_t)tmp;
    }
  }
}
/**
  * @brief  Retrieve the ISP Statistic Removal configuration for a specified DCMIPP pipe.
  * @param  hdcmipp       Pointer to DCMIPP handle
  * @param  Pipe          Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @param  NbFirstLines  Pointer to a uint32_t variable that will be filled with the number
  *                       of first lines to be removed from the statistics computation.
  * @param  NbLastLines   Pointer to a uint32_t variable that will be filled with the number
  *                       of last lines to be removed from the statistics computation.
  * @retval None
  */
void HAL_DCMIPP_PIPE_GetISPRemovalStatisticConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                  uint32_t *NbFirstLines, uint32_t *NbLastLines)
{
  uint32_t tmp;

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    tmp = READ_REG(hdcmipp->Instance->P1SRCR);

    *NbFirstLines  = ((tmp & DCMIPP_P1SRCR_FIRSTLINEDEL) >> DCMIPP_P1SRCR_FIRSTLINEDEL_Pos);

    *NbLastLines = (tmp & DCMIPP_P1SRCR_LASTLINE);
  }
}
#if defined(DCMIPPP_P1HISTOGRAM_AVAILABLE)
void HAL_DCMIPP_PIPE_GetHistogramConfig(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                        DCMIPP_Histogram_ConfigTypeDef *pHistogramConfig)
{
  uint32_t tmp;

  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    tmp = READ_REG(hdcmipp->Instance->P1CHSCR);
    pHistogramConfig->HDec = ((tmp & DCMIPP_P1CHSCR_HDEC) >> DCMIPP_P1CHSCR_HDEC_Pos);
    pHistogramConfig->VDec = ((tmp & DCMIPP_P1CHSCR_VDEC) >> DCMIPP_P1CHSCR_VDEC_Pos);
    pHistogramConfig->Components = ((tmp & DCMIPP_P1CHSCR_COMP) >> DCMIPP_P1CHSCR_COMP_Pos);
    pHistogramConfig->VReg = ((tmp & DCMIPP_P1CHSCR_VREG) >> DCMIPP_P1CHSCR_VREG_Pos);
    pHistogramConfig->HReg = ((tmp & DCMIPP_P1CHSCR_HREG) >> DCMIPP_P1CHSCR_HREG_Pos);
    pHistogramConfig->Source  = ((tmp & DCMIPP_P1CHSCR_SRC) >> DCMIPP_P1CHSCR_SRC_Pos);
    pHistogramConfig->Bin = ((tmp & DCMIPP_P1CHSCR_BIN) >> DCMIPP_P1CHSCR_BIN_Pos);
    pHistogramConfig->PixelDynamic  = ((tmp & DCMIPP_P1CHSCR_DYN) >> DCMIPP_P1CHSCR_DYN_Pos);

    tmp = READ_REG(hdcmipp->Instance->P1CHSSTR);
    pHistogramConfig->VStart  = ((tmp & DCMIPP_P1CHSSTR_VSTART) >> DCMIPP_P1CHSSTR_VSTART_Pos);
    pHistogramConfig->HStart  = ((tmp & DCMIPP_P1CHSSTR_HSTART) >> DCMIPP_P1CHSSTR_HSTART_Pos);

    tmp = READ_REG(hdcmipp->Instance->P1CHSSZR);
    pHistogramConfig->VSize = ((tmp & DCMIPP_P1CHSSZR_VSIZE) >> DCMIPP_P1CHSSZR_VSIZE_Pos);
    pHistogramConfig->HSize = ((tmp & DCMIPP_P1CHSSZR_HSIZE) >> DCMIPP_P1CHSSZR_HSIZE_Pos);

    tmp = READ_REG(hdcmipp->Instance->P1CHSMAR1);
    pHistogramConfig->MemoryAddress = ((tmp & DCMIPP_P1CHSMAR1_MA) >> DCMIPP_P1CHSMAR1_MA_Pos);
  }
}

void HAL_DCMIPP_PIPE_GetLastHistogramAddress(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                             uint32_t *pAddress)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  /* Check handle validity */
  if ((hdcmipp == NULL) || (pAddress == NULL))
  {
    return;
  }

  if (Pipe == DCMIPP_PIPE1)
  {
    *pAddress =  hdcmipp->Instance->P1HSSMAR;
  }
}
#endif /* DCMIPPP_P1HISTOGRAM_AVAILABLE */
/**
  * @brief  Check if the ISP Statistic Removal is enabled or not
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledISPRemovalStatistic(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  return ((READ_BIT(hdcmipp->Instance->P1SRCR, DCMIPP_P1SRCR_CROPEN) == DCMIPP_P1SRCR_CROPEN) ? 1U : 0U);
}
/**
  * @brief  Check if ISP Bad Pixel Removal is enabled or not
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledISPBadPixelRemoval(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    return ((READ_BIT(hdcmipp->Instance->P1BPRCR, DCMIPP_P1BPRCR_ENABLE) == DCMIPP_P1BPRCR_ENABLE) ? 1U : 0U);
  }
  else
  {
    /* State Disabled */
    return 0;
  }
}
/**
  * @brief  Check if ISP Decimation is enabled or not
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledISPDecimation(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    return ((READ_BIT(hdcmipp->Instance->P1DECR, DCMIPP_P1DECR_ENABLE) == DCMIPP_P1DECR_ENABLE) ? 1U : 0U);
  }
  else
  {
    /* State Disabled */
    return 0;
  }
}
/**
  * @brief  Check if ISP Black Level Calibration is enabled or not
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledISPBlackLevelCalibration(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    return ((READ_BIT(hdcmipp->Instance->P1BLCCR, DCMIPP_P1BLCCR_ENABLE) == DCMIPP_P1BLCCR_ENABLE) ? 1U : 0U);
  }
  else
  {
    /* State Disabled */
    return 0;
  }
}
/**
  * @brief  Check if ISP Exposure is enabled or not
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledISPExposure(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    return ((READ_BIT(hdcmipp->Instance->P1EXCR1, DCMIPP_P1EXCR1_ENABLE) == DCMIPP_P1EXCR1_ENABLE) ? 1U : 0U);
  }
  else
  {
    /* State Disabled */
    return 0;
  }
}
/**
  * @brief  Check if ISP RawBayer to RGB is enabled or not
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledISPRawBayer2RGB(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    return ((READ_BIT(hdcmipp->Instance->P1DMCR, DCMIPP_P1DMCR_ENABLE) == DCMIPP_P1DMCR_ENABLE) ? 1U : 0U);
  }
  else
  {
    /* State Disabled */
    return 0;
  }
}
/**
  * @brief  Check if ISP color conversion is enabled
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Pipe to be checked
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledISPColorConversion(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    return ((READ_BIT(hdcmipp->Instance->P1CCCR, DCMIPP_P1CCCR_ENABLE) == DCMIPP_P1CCCR_ENABLE) ? 1U : 0U);
  }
  else
  {
    /* State Disabled */
    return 0;
  }
}
/**
  * @brief  Check if ISP contrast is enabled or not
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledISPCtrlContrast(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    return ((READ_BIT(hdcmipp->Instance->P1CTCR1, DCMIPP_P1CTCR1_ENABLE) == DCMIPP_P1CTCR1_ENABLE) ? 1U : 0U);
  }
  else
  {
    /* State Disabled */
    return 0;
  }
}

/**
  * @brief  Get state of ISP Statistic Extraction Module
  * @param  hdcmipp   pointer to a DCMIPP_HandleTypeDfef structure
  * @param  Pipe      Pipe to be checked
  * @param  ModuleID  Module ID of Statistics extraction module.
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledISPStatisticExtractionModule(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                               uint8_t ModuleID)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    switch (ModuleID)
    {
      case DCMIPP_STATEXT_MODULE2:
        return ((READ_BIT(hdcmipp->Instance->P1ST2CR, DCMIPP_P1ST2CR_ENABLE) == DCMIPP_P1ST2CR_ENABLE) ? 1U : 0U);
        break;
      case DCMIPP_STATEXT_MODULE3:
        return ((READ_BIT(hdcmipp->Instance->P1ST3CR, DCMIPP_P1ST3CR_ENABLE) == DCMIPP_P1ST3CR_ENABLE) ? 1U : 0U);
        break;
      default:
        /* DCMIPP_STATEXT_MODULE1 */
        return ((READ_BIT(hdcmipp->Instance->P1ST1CR, DCMIPP_P1ST1CR_ENABLE) == DCMIPP_P1ST1CR_ENABLE) ? 1U : 0U);
        break;
    }
  }
  else
  {
    /* State Disabled */
    return 0;
  }
}
/**
  * @brief  Check if ISP Area Statistic Extraction is enabled or not
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_DCMIPP_PIPE_IsEnabledISPAreaStatisticExtraction(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check parameters */
  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_PIPE(Pipe));

  if (Pipe == DCMIPP_PIPE1)
  {
    return ((READ_BIT(hdcmipp->Instance->P1STSZR, DCMIPP_P1STSZR_CROPEN) == DCMIPP_P1STSZR_CROPEN) ? 1UL : 0UL);

  }
  else
  {
    /* State Disabled */
    return 0;
  }
}
/**
  * @}
  */
/** @defgroup DCMIPP_PeripheralControl_Functions DCMIPP Peripheral Control Functions
  * @{
  */
/**
  * @brief  Configure the DCMIPP CSI Line/Byte Counter for the selected counter according to the user parameters.
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  Counter         Specifies the counter, can be a value from @ref DCMIPP_CSI_Counter
  * @param  pLineByteConfig Pointer to DCMIPP_CSI_LineByteCounterConfTypeDef that contains the Line/Byte Counter
  *                         configuration information for CSI.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_SetLineByteCounterConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Counter,
                                                          DCMIPP_CSI_LineByteCounterConfTypeDef *pLineByteConfig)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;
  uint32_t prgitr_lbxvc_msk = ((uint32_t)CSI_PRGITR_LB0VC << (Counter * 4U));
  uint32_t prgitr_lbxvc_pos = CSI_PRGITR_LB0VC_Pos + (Counter * 4U);

  /* Check pointer validity */
  if ((hdcmipp == NULL) || (pLineByteConfig == NULL))
  {
    return HAL_ERROR;
  }

  assert_param(IS_DCMIPP_ALL_INSTANCE(hdcmipp->Instance));
  assert_param(IS_DCMIPP_CSI_COUNTER(Counter));
  assert_param(IS_DCMIPP_CSI_LINE_COUNTER(pLineByteConfig->LineCounter));
  assert_param(IS_DCMIPP_CSI_BYTE_COUNTER(pLineByteConfig->ByteCounter));
  assert_param(IS_DCMIPP_VCID(pLineByteConfig->VirtualChannel));

  switch (Counter)
  {
    case DCMIPP_CSI_COUNTER0:
      WRITE_REG(csi_instance->LB0CFGR, (pLineByteConfig->LineCounter << CSI_LB0CFGR_LINECNT_Pos) | \
                pLineByteConfig->ByteCounter);
      break;
    case DCMIPP_CSI_COUNTER1:
      WRITE_REG(csi_instance->LB1CFGR, (pLineByteConfig->LineCounter << CSI_LB1CFGR_LINECNT_Pos) | \
                pLineByteConfig->ByteCounter);
      break;
    case DCMIPP_CSI_COUNTER2:
      WRITE_REG(csi_instance->LB2CFGR, (pLineByteConfig->LineCounter << CSI_LB2CFGR_LINECNT_Pos) | \
                pLineByteConfig->ByteCounter);
      break;
    case DCMIPP_CSI_COUNTER3:
      WRITE_REG(csi_instance->LB3CFGR, (pLineByteConfig->LineCounter << CSI_LB3CFGR_LINECNT_Pos) | \
                pLineByteConfig->ByteCounter);
      break;
    default:
      break;
  }

  /* Link the Line/Byte Counter to the selected virtual channel */
  MODIFY_REG(csi_instance->PRGITR, prgitr_lbxvc_msk, pLineByteConfig->VirtualChannel << prgitr_lbxvc_pos);

  return HAL_OK;
}
/**
  * @brief  Enable the selected DCMIPP CSI Line/Byte Counter.
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  Counter         Specifies the counter, can be a value from @ref DCMIPP_CSI_Counter
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_EnableLineByteCounter(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Counter)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;

  assert_param(IS_DCMIPP_CSI_COUNTER(Counter));

  /* Check pointer validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Enable the Line/Byte Counter IT */
  __HAL_DCMIPP_CSI_ENABLE_IT(csi_instance, ((uint32_t)DCMIPP_CSI_IT_LB0 << Counter));

  /* Enable the selected counter */
  SET_BIT(csi_instance->PRGITR, ((uint32_t)CSI_PRGITR_LB0EN << (Counter * 4U)));

  return HAL_OK;
}
/**
  * @brief  Disable the selected DCMIPP CSI Line/Byte Counter.
  * @param  hdcmipp         Pointer to DCMIPP handle
  * @param  Counter         Specifies the counter, can be a value from @ref DCMIPP_CSI_Counter
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_DisableLineByteCounter(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Counter)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;

  assert_param(IS_DCMIPP_CSI_COUNTER(Counter));

  /* Check pointer validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Enable the Line/Byte Counter IT */
  __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_LB0 << Counter);

  /* Enable the selected counter */
  CLEAR_BIT(csi_instance->PRGITR, CSI_PRGITR_LB0EN << (Counter * 4U));

  return HAL_OK;
}
/**
  * @brief  Configure the DCMIPP CSI Timer for the selected timer according to the user parameters.
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Timer       Specifies the Timer, can be a value from @ref DCMIPP_CSI_Timer
  * @param  TimerConfig Pointer to DCMIPP_CSI_TimerConfTypeDef that contains the timer
  *                     configuration information for CSI.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_SetTimerConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Timer,
                                                DCMIPP_CSI_TimerConfTypeDef *TimerConfig)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;

  uint32_t prgitr_lbx_index = CSI_PRGITR_TIM0VC_Pos + (Timer * 4U);
  uint32_t prgitr_lbxvc_msk = ((uint32_t)CSI_PRGITR_TIM0VC << (Timer * 4U));
  uint32_t startpoint_pos = CSI_PRGITR_TIM0EOF_Pos + (Timer * 4U);

  /* Check pointer validity */
  if ((hdcmipp == NULL) || (TimerConfig == NULL))
  {
    return HAL_ERROR;
  }

  assert_param(IS_DCMIPP_VCID(TimerConfig->VirtualChannel));
  assert_param(IS_DCMIPP_CSI_TIMER(Timer));
  assert_param(IS_DCMIPP_CSI_TIMER_START(TimerConfig->StartPoint));

  /* Set counter value and the start point for the selected timer */
  switch (Timer)
  {
    case DCMIPP_CSI_TIMER0:
      WRITE_REG(csi_instance->TIM0CFGR, TimerConfig->Count);
      break;
    case DCMIPP_CSI_TIMER1:
      WRITE_REG(csi_instance->TIM1CFGR, TimerConfig->Count);
      break;
    case DCMIPP_CSI_TIMER2:
      WRITE_REG(csi_instance->TIM2CFGR, TimerConfig->Count);
      break;
    case DCMIPP_CSI_TIMER3:
      WRITE_REG(csi_instance->TIM3CFGR, TimerConfig->Count);
      break;
    default:
      break;
  }

  SET_BIT(csi_instance->PRGITR, TimerConfig->StartPoint << startpoint_pos);

  /* Link the timer to the selected virtual channel */
  MODIFY_REG(csi_instance->PRGITR, prgitr_lbxvc_msk, (TimerConfig->VirtualChannel) << prgitr_lbx_index);

  return HAL_OK;

}
/**
  * @brief  Enable the selected DCMIPP CSI Timer.
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Timer       Specifies the Timer, can be a value from @ref DCMIPP_CSI_Timer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_EnableTimer(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Timer)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;

  assert_param(IS_DCMIPP_CSI_TIMER(Timer));

  /* Check pointer validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Enable the Timer x IT */
  __HAL_DCMIPP_CSI_ENABLE_IT(csi_instance, ((uint32_t)DCMIPP_CSI_IT_TIM0 << Timer));

  /* Enable the selected timer */
  SET_BIT(csi_instance->PRGITR, ((uint32_t)CSI_PRGITR_TIM0EN << (Timer * 4U)));

  return HAL_OK;
}
/**
  * @brief  Disable the selected DCMIPP CSI Timer.
  * @param  hdcmipp     Pointer to DCMIPP handle
  * @param  Timer       Specifies the Timer, can be a value from @ref DCMIPP_CSI_Timer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_DisableTimer(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Timer)
{
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;

  assert_param(IS_DCMIPP_CSI_TIMER(Timer));

  /* Check pointer validity */
  if (hdcmipp == NULL)
  {
    return HAL_ERROR;
  }

  /* Enable the Line/Byte Counter IT */
  __HAL_DCMIPP_CSI_DISABLE_IT(csi_instance, DCMIPP_CSI_IT_TIM0 << Timer);

  /* Enable the selected counter */
  CLEAR_BIT(csi_instance->PRGITR, CSI_PRGITR_TIM0EN << (Timer * 4U));

  return HAL_OK;
}
/**
  * @brief  Configure the DCMIPP CSI Watchdog counter.
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Counter  Specifies the watchdog counter value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMIPP_CSI_SetWatchdogCounterConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Counter)
{
  UNUSED(hdcmipp);
  CSI_TypeDef *csi_instance;
  csi_instance = CSI;

  /* Configure the watchdog counter */
  WRITE_REG(csi_instance->WDR, Counter);

  /* Enable the watchdog */
  __HAL_DCMIPP_CSI_ENABLE_IT(csi_instance, DCMIPP_CSI_IT_WDERR);

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup DCMIPP_State_and_Error_Functions DCMIPP State and Error Functions
@verbatim
===============================================================================
            ##### State and Error Functions #####
===============================================================================
    [..]  This subsection provides a set of functions allowing
    (+) HAL_DCMIPP_GetState      : Get DCMIPP State.
    (+) HAL_DCMIPP_PIPE_GetState : Get PIPE State.
    (+) HAL_DCMIPP_GetError      : Get DCMIPP Error.
@endverbatim
  * @{
  */

/**
  * @brief  Return the DCMIPP state
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval HAL state
  */
HAL_DCMIPP_StateTypeDef HAL_DCMIPP_GetState(const DCMIPP_HandleTypeDef *hdcmipp)
{
  return hdcmipp->State;
}
/**
  * @brief  Return the DCMIPP error code
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @retval DCMIPP Error Code
  */
uint32_t HAL_DCMIPP_GetError(const DCMIPP_HandleTypeDef *hdcmipp)
{
  return hdcmipp->ErrorCode;
}
/**
  * @brief  Return the DCMIPP state
  * @param  hdcmipp  Pointer to DCMIPP handle
  * @param  Pipe     Specifies the DCMIPP pipe, can be a value from @ref DCMIPP_Pipes
  * @retval HAL state
  */
HAL_DCMIPP_PipeStateTypeDef HAL_DCMIPP_PIPE_GetState(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe)
{
  /* Check Parameters */
  assert_param(IS_DCMIPP_PIPE(Pipe));

  return hdcmipp->PipeState[Pipe];
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

/**
  * @}
  */
#endif /* DCMIPP */
#endif /* HAL_DCMIPP_MODULE_ENABLED */

