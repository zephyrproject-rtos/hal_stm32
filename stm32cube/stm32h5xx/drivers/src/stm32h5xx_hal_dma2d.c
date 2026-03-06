/**
  ******************************************************************************
  * @file    stm32h5xx_hal_dma2d.c
  * @author  MCD Application Team
  * @brief   DMA2D HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the DMA2D peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
           The DMA2D supports two exclusive operating modes: Direct Mode and Command List Mode.
           You can select the desired mode with the compilation define in the file stm32_hal_conf.h as follows:

           Set USE_DMA2D_COMMAND_LIST_MODE to 1 to enable Command List Mode. In this mode, a series of SIMD instructions
           are prepared in a command list, which, once executed, loads the register values
           and starts the DMA2D operations automatically.
           Set USE_DMA2D_COMMAND_LIST_MODE to 0 to use Direct Mode, which provides direct access
           to the DMA2D registers for immediate operation control.
    [..]
      (#) Program the required configuration through the following parameters:
          the transfer mode, the output color mode the output offset and the alpha position using
          HAL_DMA2D_Init() function.

      (#) Program the required configuration through the following parameters:
          the input color mode, the input color, the input alpha value, the alpha mode,
          the red/blue swap mode, the inverted alpha mode, the input offset and the alpha position using
          HAL_DMA2D_ConfigLayer() function for foreground or/and background layer.

      (#) Program the required configuration by specifying the mirroring/rotation type using the
          HAL_DMA2D_ConfigRotation() for the selected source foreground, background, or blender output

      (#) Program the downscaling parameters by providing the horizontal and vertical scaling ratios,
          pixel dimensions, and phase values through a DMA2D_DownscalingCfgTypeDef structure and
          using the HAL_DMA2D_ConfigDownscaling() function for the selected source foreground,
          background, or blender output.

      (#) Program the stencil buffer configuration by specifying the source, stencil mode,
          buffer address, line offset, and horizontal pre/post pixels
          using a DMA2D_StencilCfgTypeDef structure and using the HAL_DMA2D_ConfigStencil() function
          to configure the stencil buffer settings for the selected source.

     *** Polling mode IO operation ***
     =================================
    [..]
       (#) Configure pdata parameter (explained hereafter), destination and data length
           and enable the transfer using HAL_DMA2D_Start().
       (#) Wait for end of transfer using HAL_DMA2D_PollForTransfer(), at this stage
           user can specify the value of timeout according to his end application.

     *** Interrupt mode IO operation ***
     ===================================
     [..]
       (#) Configure pdata parameter, destination and data length and enable
           the transfer using HAL_DMA2D_Start_IT().
       (#) Use HAL_DMA2D_IRQHandler() called under DMA2D_IRQHandler() interrupt subroutine.
       (#) At the end of data transfer HAL_DMA2D_IRQHandler() function is executed and user can
           add his own function by customization of function pointer XferCpltCallback (member
           of DMA2D handle structure).
       (#) In case of error, the HAL_DMA2D_IRQHandler() function calls the callback
           XferErrorCallback.

         -@-   In Register-to-Memory transfer mode, pdata parameter is the register
               color, in Memory-to-memory or Memory-to-Memory with pixel format
               conversion pdata is the source address.

         -@-   Configure the foreground source address, the background source address,
               the destination and data length then Enable the transfer using
               HAL_DMA2D_BlendingStart() in polling mode and HAL_DMA2D_BlendingStart_IT()
               in interrupt mode.

         -@-   HAL_DMA2D_BlendingStart() and HAL_DMA2D_BlendingStart_IT() functions
               are used if the memory to memory with blending transfer mode is selected.

      (#) Optionally, configure and enable the CLUT using HAL_DMA2D_CLUTLoad() in polling
          mode or HAL_DMA2D_CLUTLoad_IT() in interrupt mode.

      (#) Optionally, configure the line watermark in using the API HAL_DMA2D_ProgramLineEvent().

      (#) Optionally, configure the dead time value in the AHB clock cycle inserted between two
          consecutive accesses on the AHB master port in using the API HAL_DMA2D_ConfigDeadTime()
          and enable/disable the functionality  with the APIs HAL_DMA2D_EnableDeadTime() or
          HAL_DMA2D_DisableDeadTime().

      (#) The transfer can be suspended, resumed and aborted using the following
          functions: HAL_DMA2D_Suspend(), HAL_DMA2D_Resume(), HAL_DMA2D_Abort().

      (#) The CLUT loading can be suspended, resumed and aborted using the following
          functions: HAL_DMA2D_CLUTLoading_Suspend(), HAL_DMA2D_CLUTLoading_Resume(),
          HAL_DMA2D_CLUTLoading_Abort().

      (#) To control the DMA2D state, use the following function: HAL_DMA2D_GetState().

      (#) To read the DMA2D error code, use the following function: HAL_DMA2D_GetError().

     *** DMA2D HAL driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in DMA2D HAL driver :

      (+) __HAL_DMA2D_ENABLE: Enable the DMA2D peripheral.
      (+) __HAL_DMA2D_GET_FLAG: Get the DMA2D pending flags.
      (+) __HAL_DMA2D_CLEAR_FLAG: Clear the DMA2D pending flags.
      (+) __HAL_DMA2D_ENABLE_IT: Enable the specified DMA2D interrupts.
      (+) __HAL_DMA2D_DISABLE_IT: Disable the specified DMA2D interrupts.
      (+) __HAL_DMA2D_GET_IT_SOURCE: Check whether the specified DMA2D interrupt is enabled or not.

     *** Callback registration ***
     ===================================
     [..]
      (#) The compilation define  USE_HAL_DMA2D_REGISTER_CALLBACKS when set to 1
          allows the user to configure dynamically the driver callbacks.
          Use function @ref HAL_DMA2D_RegisterCallback() to register a user callback.

      (#) Function @ref HAL_DMA2D_RegisterCallback() allows to register following callbacks:
            (+) XferCpltCallback : callback for transfer complete.
            (+) XferErrorCallback : callback for transfer error.
            (+) LineEventCallback : callback for line event.
            (+) CLUTLoadingCpltCallback : callback for CLUT loading completion.
            (+) MspInitCallback    : DMA2D MspInit.
            (+) MspDeInitCallback  : DMA2D MspDeInit.
          This function takes as parameters the HAL peripheral handle, the Callback ID
          and a pointer to the user callback function.

      (#) Use function @ref HAL_DMA2D_UnRegisterCallback() to reset a callback to the default
          weak (overridden) function.
          @ref HAL_DMA2D_UnRegisterCallback() takes as parameters the HAL peripheral handle,
          and the Callback ID.
          This function allows to reset following callbacks:
            (+) XferCpltCallback : callback for transfer complete.
            (+) XferErrorCallback : callback for transfer error.
            (+) LineEventCallback : callback for line event.
            (+) CLUTLoadingCpltCallback : callback for CLUT loading completion.
            (+) MspInitCallback    : DMA2D MspInit.
            (+) MspDeInitCallback  : DMA2D MspDeInit.

      (#) By default, after the @ref HAL_DMA2D_Init and if the state is HAL_DMA2D_STATE_RESET
          all callbacks are reset to the corresponding legacy weak (overridden) functions:
          examples @ref HAL_DMA2D_LineEventCallback(), @ref HAL_DMA2D_CLUTLoadingCpltCallback()
          Exception done for MspInit and MspDeInit callbacks that are respectively
          reset to the legacy weak (overridden) functions in the @ref HAL_DMA2D_Init
          and @ref HAL_DMA2D_DeInit only when these callbacks are null (not registered beforehand)
          If not, MspInit or MspDeInit are not null, the @ref HAL_DMA2D_Init and @ref HAL_DMA2D_DeInit
          keep and use the user MspInit/MspDeInit callbacks (registered beforehand).

          Exception as well for Transfer Completion and Transfer Error callbacks that are not defined
          as weak (overridden) functions. They must be defined by the user to be resorted to.

          Callbacks can be registered/unregistered in READY state only.
          Exception done for MspInit/MspDeInit callbacks that can be registered/unregistered
          in READY or RESET state, thus registered (user) MspInit/DeInit callbacks can be used
          during the Init/DeInit.
          In that case first register the MspInit/MspDeInit user callbacks
          using @ref HAL_DMA2D_RegisterCallback before calling @ref HAL_DMA2D_DeInit
          or @ref HAL_DMA2D_Init function.

          When The compilation define USE_HAL_DMA2D_REGISTER_CALLBACKS is set to 0 or
          not defined, the callback registering feature is not available
          and weak (overridden) callbacks are used.

     [...]

        DMA2D Command List Mode enables efficient execution of graphic operations by preparing sequences
        of instructions in memory, organized as linear command lists referenced by a ring buffer.
        The DMA2D hardware processes these instructions, updating internal registers and performing data transfer
        thereby offloading the CPU.

        Ring Buffer
      +----------------+----------------+----------------+
      | Descriptor 1   | Descriptor 2   | Descriptor 3   |  <-- Head Pointer
      +----------------+----------------+----------------+
             |                 |                 |
      Linear Command List  Linear Command List  Linear Command List
      +------------+       +------------+       +------------+
      | Instr 1    |       | Instr 1    |       | Instr 1    |
      | Instr 2    |       | Instr 2    |       | Instr 2    |
      | ...        |       | ...        |       | ...        |
      | END        |       | END        |       | END        |
      +------------+       +------------+       +------------+

      [...] Ring Buffer Configuration

            The ring buffer is a circular memory area in your system RAM that holds descriptors.
            Each descriptor points to a linear command list a series of instructions for the DMA2D hardware.

            To set this up, you first initialize the DMA2D peripheral and configure the ring buffer by calling
            the function HAL_DMA2D_CL_Init() and specifying:
             - The size of the ring buffer (how many descriptors it can hold).
             - The base address of the ring buffer in system memory.
            This configuration ensures the DMA2D hardware knows where to fetch command list descriptors for execution.

      [...] Linear Command Lists Preparation
            Each descriptor in the ring buffer references a linear command list,
            which is essentially a buffer of DMA2D instructions and register values.

            You initialize these command list buffers by HAL_DMA2D_CL_Init_CommandList() to provide:
            - The memory address where the command list instructions will be stored.
            - The size of this buffer.

             Once initialized, you can start building your command lists by adding commands that configure
             the DMA2D Hardware.

      [...] Command List instructions build
                 The driver provides a set of APIs to add commands to your linear command lists:

                 (#) Program the required configuration through the following parameters: transfer mode,
                  output color mode, output offset, and alpha position using the HAL_DMA2D_CL_Init() function.

                 (#) Program Layer required configuration through the following parameters: input color mode,
                 input alpha value, alpha mode, red/blue swap mode, inverted alpha mode, input offset,
                 and alpha position using the HAL_DMA2D_CL_AddConfigLayerCMD() function
                 for the foreground and/or background layer.

                 (#) Program the stencil buffer address, stencil mode, and line offset with pixels to be skipped
                 at the beginning and at the end (HTRAIL, HPRE, VTRAIL, VPRE) using the function
                 HAL_DMA2D_CL_AddConfigStencilCMD() for the foreground layer, background layer, or blender output.

                 (#) Program the mirroring or rotation type using the HAL_DMA2D_CL_AddConfigRotationCMD()
                 function for the foreground layer, background layer, or blender output.

                 (#) Program for downscaling PixelPerLines, NumberOfLines, VStep, HStep, VPhase, and HPhase using
                 the HAL_DMA2D_CL_AddConfigDownscalingCMD() function for the foreground layer, background layer,
                 or blender output.

                (#) Optionally, configure the line watermark in using the function HAL_DMA2D_CL_AddLineEventCMD().

      [...] Command List Copy ans Data Transfers Enable
                 Use the following APIs to enable data transfer for the selected operating mode and to copy
                 the constructed command list to the address pointed to by pCommandList, as chosen by the user.

                 Each API appends the necessary instructions and register values to the command list buffer,
                 building a sequence of operations that the DMA2D hardware will execute.

            (+++)Configure using HAL_DMA2D_CL_AddCopyCMD():
                 -@- Register-to-Memory transfer mode: The pdata parameter(register color),
                     the destination, the data length, and enable the transfer.
                 -@- Memory-to-Memory or Memory-to-Memory with pixel format conversion:
                     The pdata parameter (the source address), the destination, the data length and enable the transfer
                     then copy the instructions to the command list buffer.
            (+++)Configure using HAL_DMA2D_CL_AddBlendingCMD():
                 The foreground source address, the background source address,
                 the destination, data length and enable the transfer then copy the instructions
                 to the command list buffer.

            (+++)Optionally configure using HAL_DMA2D_CL_AddCLUTStartLoadCMD():
                 The CLUT Color Mode, the CLUT size and enable the CLUT loading then copy the instructions
                 to the command list buffer.

      [...] Linear Command Lists Insersion
            (+)Insert Command Lists into the Ring Buffer HAL_DMA2D_CL_InsertCommandList()
               Once your command lists are prepared, you insert them into the ring buffer .

            (+)During insertion, you can also configure General Purpose Flags (GPFLAGs) to control synchronization or
               trigger specific behaviors before and after executing each command list.

      [...]  Command List Execution and Interrupt
            (+) Once you have queued your prepared command lists into the ring buffer,you can initiate their execution
                by the DMA2D hardware HAL_DMA2D_CL_Start(), where the register values will be effectively loaded into
                the DMA2D registers, and the operations will be started sequentially.
                This function enables all relevant DMA2D interrupts, allowing you to monitor the execution progress
                and handle events such as completion or errors seamlessly.

                If you require more control over interrupt management, you can use HAL_DMA2D_CL_StartOpt(), which lets
                you selectively enable or disable specific DMA2D interrupts according to your application needs.

            (+) Use HAL_DMA2D_CL_IRQHandler() called under DMA2D_IRQHandler() interrupt subroutine.
            (+) At each event HAL_DMA2D_CL_IRQHandler() function is executed and the corresponding weak callback
               (member of DMA2D CL handle structure DMA2D_CL_HandleTypeDef) is called:
                  (+)RBXferCpltCallback : callback for Ring Buffer transfer complete.
                  (+)CL_SuspendCallback : callback for Command List Suspend.
                  (+)CL_GeneralPurposeEventCallback : callback for General Purpose Flag Event.
                  (+)XferErrorCallback : callback for transfer error.
                  (+)XferCpltCallback : callback for data transfer complete.
                  (+)LineEventCallback : callback for line event.
                  (+)CLUTLoadingCpltCallback : callback for CLUT loading completion.
                  (+)ErrorCallback : callback for error (Ring Buffer Management and Command List Errors)
                  (+)MspInitCallback : DMA2D MspInit.
                  (+)MspDeInitCallback : DMA2D MspDeInit.
            (+) The above list of most used macros in DMA2D HAL driver can be used

            (+) The Command List execution can be suspended and resumed through
                HAL_DMA2D_CL_Suspend() and HAL_DMA2D_CL_Resume()
                You can Abort command list execution immediately if needed by HAL_DMA2D_CL_Abort()

     [..]
      (@) You can refer to the DMA2D HAL driver header file for more useful macros

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

#ifdef HAL_DMA2D_MODULE_ENABLED
#if defined (DMA2D)

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

/** @defgroup DMA2D  DMA2D
  * @brief DMA2D HAL module driver
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup DMA2D_Private_Constants DMA2D Private Constants
  * @{
  */

/** @defgroup DMA2D_TimeOut DMA2D Time Out
  * @{
  */
#define DMA2D_TIMEOUT_ABORT           (1000U)  /*!<  1s  */
#define DMA2D_TIMEOUT_SUSPEND         (1000U)  /*!<  1s  */
/**
  * @}
  */

#if (USE_DMA2D_COMMAND_LIST_MODE == 1)
/** @defgroup DMA2D_CL_Registers DMA2D Command List Registers
  * @{
  */
#define DMA2D_CL_CR_REG          0U
#define DMA2D_CL_IER_REG         1U
#define DMA2D_CL_IFCR_REG        2U
#define DMA2D_CL_FGMAR_REG       3U
#define DMA2D_CL_FGOR_REG        4U
#define DMA2D_CL_FGMSR_REG       5U
#define DMA2D_CL_FGPFCCR_REG     6U
#define DMA2D_CL_FGCOLR_REG      7U
#define DMA2D_CL_FGCMAR_REG      8U
#define DMA2D_CL_BGMAR_REG       9U
#define DMA2D_CL_BGOR_REG       10U
#define DMA2D_CL_BGMSR_REG      11U
#define DMA2D_CL_BGPFCCR_REG    12U
#define DMA2D_CL_BGCOLR_REG     13U
#define DMA2D_CL_BGCMAR_REG     14U
#define DMA2D_CL_OPFCCR_REG     15U
#define DMA2D_CL_OCOLR_REG      16U
#define DMA2D_CL_OMAR_REG       17U
#define DMA2D_CL_OOR_REG        18U
#define DMA2D_CL_NLR_REG        19U
#define DMA2D_CL_SBCR_REG       20U
#define DMA2D_CL_SBMAR_REG      21U
#define DMA2D_CL_SBOR_REG       22U
#define DMA2D_CL_SBMSR_REG      23U
#define DMA2D_CL_TBCR_REG       24U
#define DMA2D_CL_SCR_REG        25U
#define DMA2D_CL_SNLR_REG       26U
#define DMA2D_CL_SSR_REG        27U
#define DMA2D_CL_SPR_REG        28U
#define HAL_DMA2D_CL_LDM_REG_NUM    29U
const uint32_t LDM_Decoder[HAL_DMA2D_CL_LDM_REG_NUM] =
{
  1 << 30U, /* DMA2D_CL_CR_REG      */
    1 << 29U, /* DMA2D_CL_IER_REG     */
    1 << 28U, /* DMA2D_CL_IFCR_REG    */
    1 << 27U, /* DMA2D_CL_FGMAR_REG   */
    1 << 27U, /* DMA2D_CL_FGOR_REG    */
    1 << 26U, /* DMA2D_CL_FGMSR_REG   */
    1 << 25U, /* DMA2D_CL_FGPFCCR_REG */
    1 << 24U, /* DMA2D_CL_FGCOLR_REG  */
    1 << 23U, /* DMA2D_CL_FGCMAR_REG  */
    1 << 22U, /* DMA2D_CL_BGMAR_REG   */
    1 << 22U, /* DMA2D_CL_BGOR_REG    */
    1 << 21U, /* DMA2D_CL_BGMSR_REG   */
    1 << 20U, /* DMA2D_CL_BGPFCCR_REG */
    1 << 19U, /* DMA2D_CL_BGCOLR_REG  */
    1 << 18U, /* DMA2D_CL_BGCMAR_REG  */
    1 << 17U, /* DMA2D_CL_OPFCR_REG   */
    1 << 16U, /* DMA2D_CL_OCOLR_REG   */
    1 << 15U, /* DMA2D_CL_OMAR_REG    */
    1 << 15U, /* DMA2D_CL_OOR_REG     */
    1 << 14U, /* DMA2D_CL_NLR_REG     */
    1 << 13U, /* DMA2D_CL_SBCR_REG    */
    1 << 12U, /* DMA2D_CL_SBMAR_REG   */
    1 << 12U, /* DMA2D_CL_SBOR_REG    */
    1 << 11U, /* DMA2D_CL_SBMSR_REG   */
    1 << 7U, /* DMA2D_CL_TBCR_REG    */
    1 << 3U, /* DMA2D_CL_SCR_REG     */
    1 << 2U, /* DMA2D_CL_SNLR_REG    */
    1 << 2U, /* DMA2D_CL_SSR_REG     */
    1 << 2U  /* DMA2D_CL_SPR_REG     */
};
#define DMA2D_CL_LDM_MODIFY_REG(HANDLE, REG, MASK, VALUE) \
  ((HANDLE)->LDM_Reg_values[(REG)] = ((HANDLE)->LDM_Reg_values[(REG)] & ~(MASK)) | ((VALUE) & (MASK)), \
   (HANDLE)->LDM_Instruction |= LDM_Decoder[(REG)] )
#define DMA2D_CL_LDM_WRITE_REG(HANDLE, REG, VALUE) \
  ((HANDLE)->LDM_Reg_values[(REG)] = (VALUE), \
   (HANDLE)->LDM_Instruction |= LDM_Decoder[(REG)])
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 1 */
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup DMA2D_Private_Functions DMA2D Private Functions
  * @{
  */
#if (USE_DMA2D_COMMAND_LIST_MODE == 1)
static void DMA2D_CL_SetConfig(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress, uint32_t Width,
                               uint32_t Height);
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 1 */
#if (USE_DMA2D_COMMAND_LIST_MODE == 0)
static void DMA2D_SetConfig(DMA2D_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress, uint32_t Width,
                            uint32_t Height);
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 0 */
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup DMA2D_Exported_Functions DMA2D Exported Functions
  * @{
  */

/** @defgroup DMA2D_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief   Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
                ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the DMA2D
      (+) De-initialize the DMA2D

@endverbatim
  * @{
  */
#if (USE_DMA2D_COMMAND_LIST_MODE == 0)
/**
  * @brief  Initialize the DMA2D according to the specified
  *         parameters in the DMA2D_InitTypeDef and create the associated handle.
  * @param  hdma2d pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_Init(DMA2D_HandleTypeDef *hdma2d)
{
  /* Check the DMA2D peripheral state */
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DMA2D_ALL_INSTANCE(hdma2d->Instance));
  assert_param(IS_DMA2D_MODE(hdma2d->Init.Mode));
  assert_param(IS_DMA2D_CMODE(hdma2d->Init.ColorMode));
  assert_param(IS_DMA2D_OFFSET(hdma2d->Init.OutputOffset));
  assert_param(IS_DMA2D_ALPHA_INVERTED(hdma2d->Init.AlphaInverted));
  assert_param(IS_DMA2D_RB_SWAP(hdma2d->Init.RedBlueSwap));
  assert_param(IS_DMA2D_LOM_MODE(hdma2d->Init.LineOffsetMode));
  assert_param(IS_DMA2D_BYTES_SWAP(hdma2d->Init.BytesSwap));
  assert_param(IS_DMA2D_ALPHA_POSITION(hdma2d->Init.AlphaPosition));

#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
  if (hdma2d->State == HAL_DMA2D_STATE_RESET)
  {
    /* Reset Callback pointers in HAL_DMA2D_STATE_RESET only */
    hdma2d->LineEventCallback       = HAL_DMA2D_LineEventCallback;
    hdma2d->CLUTLoadingCpltCallback = HAL_DMA2D_CLUTLoadingCpltCallback;
    if (hdma2d->MspInitCallback == NULL)
    {
      hdma2d->MspInitCallback = HAL_DMA2D_MspInit;
    }

    /* Init the low level hardware */
    hdma2d->MspInitCallback(hdma2d);
  }
#else
  if (hdma2d->State == HAL_DMA2D_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hdma2d->Lock = HAL_UNLOCKED;
    /* Init the low level hardware */
    HAL_DMA2D_MspInit(hdma2d);
  }
#endif /* (USE_HAL_DMA2D_REGISTER_CALLBACKS) */

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* DMA2D CR register configuration -------------------------------------------*/
  MODIFY_REG(hdma2d->Instance->CR, DMA2D_CR_MODE | DMA2D_CR_LOM, hdma2d->Init.Mode | hdma2d->Init.LineOffsetMode);

  /* DMA2D OPFCCR register configuration ---------------------------------------*/
  MODIFY_REG(hdma2d->Instance->OPFCCR, DMA2D_OPFCCR_CM | DMA2D_OPFCCR_SB,
             hdma2d->Init.ColorMode | hdma2d->Init.BytesSwap);

  /* DMA2D OOR register configuration ------------------------------------------*/
  MODIFY_REG(hdma2d->Instance->OOR, DMA2D_OOR_LO, hdma2d->Init.OutputOffset);
  /* DMA2D OPFCCR AI AP and RBS fields setting (Output Alpha Inversion)*/
  MODIFY_REG(hdma2d->Instance->OPFCCR, (DMA2D_OPFCCR_AI | DMA2D_OPFCCR_RBS | DMA2D_OPFCCR_APOS),
             ((hdma2d->Init.AlphaInverted << DMA2D_OPFCCR_AI_Pos) | \
              (hdma2d->Init.RedBlueSwap << DMA2D_OPFCCR_RBS_Pos) | \
              (hdma2d->Init.AlphaPosition << DMA2D_OPFCCR_APOS_Pos)));


  /* Update error code */
  hdma2d->ErrorCode = HAL_DMA2D_ERROR_NONE;

  /* Initialize the DMA2D state*/
  hdma2d->State  = HAL_DMA2D_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Deinitializes the DMA2D peripheral registers to their default reset
  *         values.
  * @param  hdma2d pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval None
  */

HAL_StatusTypeDef HAL_DMA2D_DeInit(DMA2D_HandleTypeDef *hdma2d)
{

  /* Check the DMA2D peripheral state */
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  /* Before aborting any DMA2D transfer or CLUT loading, check
     first whether or not DMA2D clock is enabled */
  if (__HAL_RCC_DMA2D_IS_CLK_ENABLED() == 1U)
  {
    /* Abort DMA2D transfer if any */
    if ((hdma2d->Instance->CR & DMA2D_CR_START) == DMA2D_CR_START)
    {
      if (HAL_DMA2D_Abort(hdma2d) != HAL_OK)
      {
        /* Issue when aborting DMA2D transfer */
        return HAL_ERROR;
      }
    }
    else
    {
      /* Abort background CLUT loading if any */
      if ((hdma2d->Instance->BGPFCCR & DMA2D_BGPFCCR_START) == DMA2D_BGPFCCR_START)
      {
        if (HAL_DMA2D_CLUTLoading_Abort(hdma2d, 0U) != HAL_OK)
        {
          /* Issue when aborting background CLUT loading */
          return HAL_ERROR;
        }
      }
      else
      {
        /* Abort foreground CLUT loading if any */
        if ((hdma2d->Instance->FGPFCCR & DMA2D_FGPFCCR_START) == DMA2D_FGPFCCR_START)
        {
          if (HAL_DMA2D_CLUTLoading_Abort(hdma2d, 1U) != HAL_OK)
          {
            /* Issue when aborting foreground CLUT loading */
            return HAL_ERROR;
          }
        }
      }
    }
  }

  /* Reset DMA2D control registers*/
  hdma2d->Instance->CR       =    0U;
  hdma2d->Instance->IFCR     = 0x3FU;
  hdma2d->Instance->FGOR     =    0U;
  hdma2d->Instance->BGOR     =    0U;
  hdma2d->Instance->FGPFCCR  =    0U;
  hdma2d->Instance->BGPFCCR  =    0U;
  hdma2d->Instance->OPFCCR   =    0U;

#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)

  if (hdma2d->MspDeInitCallback == NULL)
  {
    hdma2d->MspDeInitCallback = HAL_DMA2D_MspDeInit;
  }

  /* DeInit the low level hardware */
  hdma2d->MspDeInitCallback(hdma2d);

#else
  /* Carry on with de-initialization of low level hardware */
  HAL_DMA2D_MspDeInit(hdma2d);
#endif /* (USE_HAL_DMA2D_REGISTER_CALLBACKS) */

  /* Update error code */
  hdma2d->ErrorCode = HAL_DMA2D_ERROR_NONE;

  /* Initialize the DMA2D state*/
  hdma2d->State  = HAL_DMA2D_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hdma2d);

  return HAL_OK;
}

/**
  * @brief  Initializes the DMA2D MSP.
  * @param  hdma2d pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval None
  */
__weak void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_MspInit can be implemented in the user file.
   */
}

/**
  * @brief  DeInitializes the DMA2D MSP.
  * @param  hdma2d pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval None
  */
__weak void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_MspDeInit can be implemented in the user file.
   */
}

#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User DMA2D Callback
  *         To be used instead of the weak (overridden) predefined callback
  * @param hdma2d DMA2D handle
  * @param CallbackID ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_DMA2D_TRANSFERCOMPLETE_CB_ID DMA2D transfer complete Callback ID
  *          @arg @ref HAL_DMA2D_TRANSFERERROR_CB_ID DMA2D transfer error Callback ID
  *          @arg @ref HAL_DMA2D_LINEEVENT_CB_ID DMA2D line event Callback ID
  *          @arg @ref HAL_DMA2D_CLUTLOADINGCPLT_CB_ID DMA2D CLUT loading completion Callback ID
  *          @arg @ref HAL_DMA2D_MSPINIT_CB_ID DMA2D MspInit callback ID
  *          @arg @ref HAL_DMA2D_MSPDEINIT_CB_ID DMA2D MspDeInit callback ID
  * @param pCallback pointer to the Callback function
  * @note No weak predefined callbacks are defined for HAL_DMA2D_TRANSFERCOMPLETE_CB_ID or HAL_DMA2D_TRANSFERERROR_CB_ID
  * @retval status
  */
HAL_StatusTypeDef HAL_DMA2D_RegisterCallback(DMA2D_HandleTypeDef *hdma2d, HAL_DMA2D_CallbackIDTypeDef CallbackID,
                                             pDMA2D_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }
  /* Process locked */
  __HAL_LOCK(hdma2d);

  if (HAL_DMA2D_STATE_READY == hdma2d->State)
  {
    switch (CallbackID)
    {
      case HAL_DMA2D_TRANSFERCOMPLETE_CB_ID :
        hdma2d->XferCpltCallback = pCallback;
        break;

      case HAL_DMA2D_TRANSFERERROR_CB_ID :
        hdma2d->XferErrorCallback = pCallback;
        break;

      case HAL_DMA2D_LINEEVENT_CB_ID :
        hdma2d->LineEventCallback = pCallback;
        break;

      case HAL_DMA2D_CLUTLOADINGCPLT_CB_ID :
        hdma2d->CLUTLoadingCpltCallback = pCallback;
        break;

      case HAL_DMA2D_MSPINIT_CB_ID :
        hdma2d->MspInitCallback = pCallback;
        break;

      case HAL_DMA2D_MSPDEINIT_CB_ID :
        hdma2d->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_DMA2D_STATE_RESET == hdma2d->State)
  {
    switch (CallbackID)
    {
      case HAL_DMA2D_MSPINIT_CB_ID :
        hdma2d->MspInitCallback = pCallback;
        break;

      case HAL_DMA2D_MSPDEINIT_CB_ID :
        hdma2d->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hdma2d);
  return status;
}

/**
  * @brief  Unregister a DMA2D Callback
  *         DMA2D Callback is redirected to the weak (overridden) predefined callback
  * @param hdma2d DMA2D handle
  * @param CallbackID ID of the callback to be unregistered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_DMA2D_TRANSFERCOMPLETE_CB_ID DMA2D transfer complete Callback ID
  *          @arg @ref HAL_DMA2D_TRANSFERERROR_CB_ID DMA2D transfer error Callback ID
  *          @arg @ref HAL_DMA2D_LINEEVENT_CB_ID DMA2D line event Callback ID
  *          @arg @ref HAL_DMA2D_CLUTLOADINGCPLT_CB_ID DMA2D CLUT loading completion Callback ID
  *          @arg @ref HAL_DMA2D_MSPINIT_CB_ID DMA2D MspInit callback ID
  *          @arg @ref HAL_DMA2D_MSPDEINIT_CB_ID DMA2D MspDeInit callback ID
  * @note No weak predefined callbacks are defined for HAL_DMA2D_TRANSFERCOMPLETE_CB_ID or HAL_DMA2D_TRANSFERERROR_CB_ID
  * @retval status
  */
HAL_StatusTypeDef HAL_DMA2D_UnRegisterCallback(DMA2D_HandleTypeDef *hdma2d, HAL_DMA2D_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hdma2d);

  if (HAL_DMA2D_STATE_READY == hdma2d->State)
  {
    switch (CallbackID)
    {
      case HAL_DMA2D_TRANSFERCOMPLETE_CB_ID :
        hdma2d->XferCpltCallback = NULL;
        break;

      case HAL_DMA2D_TRANSFERERROR_CB_ID :
        hdma2d->XferErrorCallback = NULL;
        break;

      case HAL_DMA2D_LINEEVENT_CB_ID :
        hdma2d->LineEventCallback = HAL_DMA2D_LineEventCallback;
        break;

      case HAL_DMA2D_CLUTLOADINGCPLT_CB_ID :
        hdma2d->CLUTLoadingCpltCallback = HAL_DMA2D_CLUTLoadingCpltCallback;
        break;

      case HAL_DMA2D_MSPINIT_CB_ID :
        hdma2d->MspInitCallback = HAL_DMA2D_MspInit; /* Legacy weak (overridden) Msp Init */
        break;

      case HAL_DMA2D_MSPDEINIT_CB_ID :
        hdma2d->MspDeInitCallback = HAL_DMA2D_MspDeInit; /* Legacy weak (overridden) Msp DeInit */
        break;

      default :
        /* Update the error code */
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_DMA2D_STATE_RESET == hdma2d->State)
  {
    switch (CallbackID)
    {
      case HAL_DMA2D_MSPINIT_CB_ID :
        hdma2d->MspInitCallback = HAL_DMA2D_MspInit;   /* Legacy weak (overridden) Msp Init */
        break;

      case HAL_DMA2D_MSPDEINIT_CB_ID :
        hdma2d->MspDeInitCallback = HAL_DMA2D_MspDeInit;  /* Legacy weak (overridden) Msp DeInit */
        break;

      default :
        /* Update the error code */
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hdma2d);
  return status;
}
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

/**
  * @}
  */


/** @defgroup DMA2D_Exported_Functions_Group2 IO operation functions
  *  @brief   IO operation functions
  *
@verbatim
 ===============================================================================
                      #####  IO operation functions  #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the pdata, destination address and data size then
          start the DMA2D transfer.
      (+) Configure the source for foreground and background, destination address
          and data size then start a MultiBuffer DMA2D transfer.
      (+) Configure the pdata, destination address and data size then
          start the DMA2D transfer with interrupt.
      (+) Configure the source for foreground and background, destination address
          and data size then start a MultiBuffer DMA2D transfer with interrupt.
      (+) Abort DMA2D transfer.
      (+) Suspend DMA2D transfer.
      (+) Resume DMA2D transfer.
      (+) Enable CLUT transfer.
      (+) Configure CLUT loading then start transfer in polling mode.
      (+) Configure CLUT loading then start transfer in interrupt mode.
      (+) Abort DMA2D CLUT loading.
      (+) Suspend DMA2D CLUT loading.
      (+) Resume DMA2D CLUT loading.
      (+) Poll for transfer complete.
      (+) handle DMA2D interrupt request.
      (+) Transfer watermark callback.
      (+) CLUT Transfer Complete callback.


@endverbatim
  * @{
  */

/**
  * @brief  Start the DMA2D Transfer.
  * @param  hdma2d     Pointer to a DMA2D_HandleTypeDef structure that contains
  *                     the configuration information for the DMA2D.
  * @param  pdata      Configure the source memory Buffer address if
  *                     Memory-to-Memory or Memory-to-Memory with pixel format
  *                     conversion mode is selected, or configure
  *                     the color value if Register-to-Memory mode is selected.
  * @param  DstAddress The destination memory Buffer address.
  * @param  Width      The width of data to be transferred from source
  *                    to destination (expressed in number of pixels per line).
  * @param  Height     The height of data to be transferred from source to destination (expressed in number of lines).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_Start(DMA2D_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress, uint32_t Width,
                                  uint32_t Height)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LINE(Height));
  assert_param(IS_DMA2D_PIXEL(Width));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* Configure the source, destination address and the data size */
  DMA2D_SetConfig(hdma2d, pdata, DstAddress, Width, Height);

  /* Enable the Peripheral */
  __HAL_DMA2D_ENABLE(hdma2d);

  return HAL_OK;
}

/**
  * @brief  Start the DMA2D Transfer with interrupt enabled.
  * @param  hdma2d     Pointer to a DMA2D_HandleTypeDef structure that contains
  *                     the configuration information for the DMA2D.
  * @param  pdata      Configure the source memory Buffer address if
  *                     the Memory-to-Memory or Memory-to-Memory with pixel format
  *                     conversion mode is selected, or configure
  *                     the color value if Register-to-Memory mode is selected.
  * @param  DstAddress The destination memory Buffer address.
  * @param  Width      The width of data to be transferred from source
  *                    to destination (expressed in number of pixels per line).
  * @param  Height     The height of data to be transferred from source to destination (expressed in number of lines).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_Start_IT(DMA2D_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress, uint32_t Width,
                                     uint32_t Height)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LINE(Height));
  assert_param(IS_DMA2D_PIXEL(Width));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* Configure the source, destination address and the data size */
  DMA2D_SetConfig(hdma2d, pdata, DstAddress, Width, Height);

  /* Enable the transfer complete, transfer error and configuration error interrupts */
  __HAL_DMA2D_ENABLE_IT(hdma2d, DMA2D_IT_TC | DMA2D_IT_TE | DMA2D_IT_CE);

  /* Enable the Peripheral */
  __HAL_DMA2D_ENABLE(hdma2d);

  return HAL_OK;
}

/**
  * @brief  Start the multi-source DMA2D Transfer.
  * @param  hdma2d      Pointer to a DMA2D_HandleTypeDef structure that contains
  *                      the configuration information for the DMA2D.
  * @param  SrcAddress1 The source memory Buffer address for the foreground layer.
  * @param  SrcAddress2 The source memory Buffer address for the background layer.
  * @param  DstAddress  The destination memory Buffer address.
  * @param  Width       The width of data to be transferred from source
  *                     to destination (expressed in number of pixels per line).
  * @param  Height      The height of data to be transferred from source to destination (expressed in number of lines).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_BlendingStart(DMA2D_HandleTypeDef *hdma2d, uint32_t SrcAddress1, uint32_t  SrcAddress2,
                                          uint32_t DstAddress, uint32_t Width,  uint32_t Height)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LINE(Height));
  assert_param(IS_DMA2D_PIXEL(Width));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  if (hdma2d->Init.Mode == DMA2D_M2M_BLEND_FG)
  {
    /*blending & fixed FG*/
    WRITE_REG(hdma2d->Instance->FGCOLR, SrcAddress1);
    /* Configure the source, destination address and the data size */
    DMA2D_SetConfig(hdma2d, SrcAddress2, DstAddress, Width, Height);
  }
  else if (hdma2d->Init.Mode == DMA2D_M2M_BLEND_BG)
  {
    /*blending & fixed BG*/
    WRITE_REG(hdma2d->Instance->BGCOLR, SrcAddress2);
    /* Configure the source, destination address and the data size */
    DMA2D_SetConfig(hdma2d, SrcAddress1, DstAddress, Width, Height);
  }
  else
  {
    /* Configure DMA2D Stream source2 address */
    WRITE_REG(hdma2d->Instance->BGMAR, SrcAddress2);

    /* Configure the source, destination address and the data size */
    DMA2D_SetConfig(hdma2d, SrcAddress1, DstAddress, Width, Height);
  }

  /* Enable the Peripheral */
  __HAL_DMA2D_ENABLE(hdma2d);

  return HAL_OK;
}

/**
  * @brief  Start the multi-source DMA2D Transfer with interrupt enabled.
  * @param  hdma2d     Pointer to a DMA2D_HandleTypeDef structure that contains
  *                     the configuration information for the DMA2D.
  * @param  SrcAddress1 The source memory Buffer address for the foreground layer.
  * @param  SrcAddress2 The source memory Buffer address for the background layer.
  * @param  DstAddress  The destination memory Buffer address.
  * @param  Width       The width of data to be transferred from source
  *                     to destination (expressed in number of pixels per line).
  * @param  Height      The height of data to be transferred from source to destination (expressed in number of lines).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_BlendingStart_IT(DMA2D_HandleTypeDef *hdma2d, uint32_t SrcAddress1, uint32_t  SrcAddress2,
                                             uint32_t DstAddress, uint32_t Width,  uint32_t Height)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LINE(Height));
  assert_param(IS_DMA2D_PIXEL(Width));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  if (hdma2d->Init.Mode == DMA2D_M2M_BLEND_FG)
  {
    /*blending & fixed FG*/
    WRITE_REG(hdma2d->Instance->FGCOLR, SrcAddress1);
    /* Configure the source, destination address and the data size */
    DMA2D_SetConfig(hdma2d, SrcAddress2, DstAddress, Width, Height);
  }
  else if (hdma2d->Init.Mode == DMA2D_M2M_BLEND_BG)
  {
    /*blending & fixed BG*/
    WRITE_REG(hdma2d->Instance->BGCOLR, SrcAddress2);
    /* Configure the source, destination address and the data size */
    DMA2D_SetConfig(hdma2d, SrcAddress1, DstAddress, Width, Height);
  }
  else
  {
    WRITE_REG(hdma2d->Instance->BGMAR, SrcAddress2);

    /* Configure the source, destination address and the data size */
    DMA2D_SetConfig(hdma2d, SrcAddress1, DstAddress, Width, Height);
  }

  /* Enable the transfer complete, transfer error and configuration error interrupts */
  __HAL_DMA2D_ENABLE_IT(hdma2d, DMA2D_IT_TC | DMA2D_IT_TE | DMA2D_IT_CE);

  /* Enable the Peripheral */
  __HAL_DMA2D_ENABLE(hdma2d);

  return HAL_OK;
}

/**
  * @brief  Abort the DMA2D Transfer.
  * @param  hdma2d  pointer to a DMA2D_HandleTypeDef structure that contains
  *                  the configuration information for the DMA2D.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_Abort(DMA2D_HandleTypeDef *hdma2d)
{
  uint32_t tickstart;

  /* Abort the DMA2D transfer */
  /* START bit is reset to make sure not to set it again, in the event the HW clears it
     between the register read and the register write by the CPU (writing 0 has no
     effect on START bitvalue) */
  MODIFY_REG(hdma2d->Instance->CR, DMA2D_CR_ABORT | DMA2D_CR_START, DMA2D_CR_ABORT);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Check if the DMA2D is effectively disabled */
  while ((hdma2d->Instance->CR & DMA2D_CR_START) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > DMA2D_TIMEOUT_ABORT)
    {
      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TIMEOUT;

      /* Change the DMA2D state */
      hdma2d->State = HAL_DMA2D_STATE_TIMEOUT;

      /* Process Unlocked */
      __HAL_UNLOCK(hdma2d);

      return HAL_TIMEOUT;
    }
  }

  /* Disable the Transfer Complete, Transfer Error and Configuration Error interrupts */
  __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_TC | DMA2D_IT_TE | DMA2D_IT_CE);

  /* Change the DMA2D state*/
  hdma2d->State = HAL_DMA2D_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hdma2d);

  return HAL_OK;
}

/**
  * @brief  Suspend the DMA2D Transfer.
  * @param  hdma2d pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_Suspend(DMA2D_HandleTypeDef *hdma2d)
{
  uint32_t tickstart;

  /* Suspend the DMA2D transfer */
  /* START bit is reset to make sure not to set it again, in the event the HW clears it
     between the register read and the register write by the CPU (writing 0 has no
     effect on START bitvalue). */
  MODIFY_REG(hdma2d->Instance->CR, DMA2D_CR_SUSP | DMA2D_CR_START, DMA2D_CR_SUSP);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Check if the DMA2D is effectively suspended */
  while ((hdma2d->Instance->CR & (DMA2D_CR_SUSP | DMA2D_CR_START)) == DMA2D_CR_START)
  {
    if ((HAL_GetTick() - tickstart) > DMA2D_TIMEOUT_SUSPEND)
    {
      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TIMEOUT;

      /* Change the DMA2D state */
      hdma2d->State = HAL_DMA2D_STATE_TIMEOUT;

      return HAL_TIMEOUT;
    }
  }

  /* Check whether or not a transfer is actually suspended and change the DMA2D state accordingly */
  if ((hdma2d->Instance->CR & DMA2D_CR_START) != 0U)
  {
    hdma2d->State = HAL_DMA2D_STATE_SUSPEND;
  }
  else
  {
    /* Make sure SUSP bit is cleared since it is meaningless
       when no transfer is on-going */
    CLEAR_BIT(hdma2d->Instance->CR, DMA2D_CR_SUSP);
  }

  return HAL_OK;
}

/**
  * @brief  Resume the DMA2D Transfer.
  * @param  hdma2d pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_Resume(DMA2D_HandleTypeDef *hdma2d)
{
  /* Check the SUSP and START bits */
  if ((hdma2d->Instance->CR & (DMA2D_CR_SUSP | DMA2D_CR_START)) == (DMA2D_CR_SUSP | DMA2D_CR_START))
  {
    /* Ongoing transfer is suspended: change the DMA2D state before resuming */
    hdma2d->State = HAL_DMA2D_STATE_BUSY;
  }

  /* Resume the DMA2D transfer */
  /* START bit is reset to make sure not to set it again, in the event the HW clears it
     between the register read and the register write by the CPU (writing 0 has no
     effect on START bitvalue). */
  CLEAR_BIT(hdma2d->Instance->CR, (DMA2D_CR_SUSP | DMA2D_CR_START));

  return HAL_OK;
}


/**
  * @brief  Enable the DMA2D CLUT Transfer.
  * @param  hdma2d   Pointer to a DMA2D_HandleTypeDef structure that contains
  *                   the configuration information for the DMA2D.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_EnableCLUT(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  if (LayerIdx == DMA2D_BACKGROUND_LAYER)
  {
    /* Enable the background CLUT loading */
    SET_BIT(hdma2d->Instance->BGPFCCR, DMA2D_BGPFCCR_START);
  }
  else
  {
    /* Enable the foreground CLUT loading */
    SET_BIT(hdma2d->Instance->FGPFCCR, DMA2D_FGPFCCR_START);
  }

  return HAL_OK;
}

/**
  * @brief  Start DMA2D CLUT Loading.
  * @param  hdma2d   Pointer to a DMA2D_HandleTypeDef structure that contains
  *                   the configuration information for the DMA2D.
  * @param  CLUTCfg  Pointer to a DMA2D_CLUTCfgTypeDef structure that contains
  *                   the configuration information for the color look up table.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CLUTStartLoad(DMA2D_HandleTypeDef *hdma2d, const DMA2D_CLUTCfgTypeDef *CLUTCfg,
                                          uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LAYER(LayerIdx));
  assert_param(IS_DMA2D_CLUT_CM(CLUTCfg->CLUTColorMode));
  assert_param(IS_DMA2D_CLUT_SIZE(CLUTCfg->Size));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* Configure the CLUT of the background DMA2D layer */
  if (LayerIdx == DMA2D_BACKGROUND_LAYER)
  {
    /* Write background CLUT memory address */
    WRITE_REG(hdma2d->Instance->BGCMAR, (uint32_t)CLUTCfg->pCLUT);

    /* Write background CLUT size and CLUT color mode */
    MODIFY_REG(hdma2d->Instance->BGPFCCR, (DMA2D_BGPFCCR_CS | DMA2D_BGPFCCR_CM),
               ((CLUTCfg->Size << DMA2D_BGPFCCR_CS_Pos) | (CLUTCfg->CLUTColorMode << DMA2D_BGPFCCR_CM_Pos)));

    /* Enable the CLUT loading for the background */
    SET_BIT(hdma2d->Instance->BGPFCCR, DMA2D_BGPFCCR_START);
  }
  /* Configure the CLUT of the foreground DMA2D layer */
  else
  {
    /* Write foreground CLUT memory address */
    WRITE_REG(hdma2d->Instance->FGCMAR, (uint32_t)CLUTCfg->pCLUT);

    /* Write foreground CLUT size and CLUT color mode */
    MODIFY_REG(hdma2d->Instance->FGPFCCR, (DMA2D_FGPFCCR_CS | DMA2D_FGPFCCR_CM),
               ((CLUTCfg->Size << DMA2D_FGPFCCR_CS_Pos) | (CLUTCfg->CLUTColorMode << DMA2D_FGPFCCR_CM_Pos)));

    /* Enable the CLUT loading for the foreground */
    SET_BIT(hdma2d->Instance->FGPFCCR, DMA2D_FGPFCCR_START);
  }

  return HAL_OK;
}

/**
  * @brief  Start DMA2D CLUT Loading with interrupt enabled.
  * @param  hdma2d   Pointer to a DMA2D_HandleTypeDef structure that contains
  *                   the configuration information for the DMA2D.
  * @param  CLUTCfg  Pointer to a DMA2D_CLUTCfgTypeDef structure that contains
  *                   the configuration information for the color look up table.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CLUTStartLoad_IT(DMA2D_HandleTypeDef *hdma2d, const DMA2D_CLUTCfgTypeDef *CLUTCfg,
                                             uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LAYER(LayerIdx));
  assert_param(IS_DMA2D_CLUT_CM(CLUTCfg->CLUTColorMode));
  assert_param(IS_DMA2D_CLUT_SIZE(CLUTCfg->Size));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* Configure the CLUT of the background DMA2D layer */
  if (LayerIdx == DMA2D_BACKGROUND_LAYER)
  {
    /* Write background CLUT memory address */
    WRITE_REG(hdma2d->Instance->BGCMAR, (uint32_t)CLUTCfg->pCLUT);

    /* Write background CLUT size and CLUT color mode */
    MODIFY_REG(hdma2d->Instance->BGPFCCR, (DMA2D_BGPFCCR_CS | DMA2D_BGPFCCR_CM),
               ((CLUTCfg->Size << DMA2D_BGPFCCR_CS_Pos) | (CLUTCfg->CLUTColorMode << DMA2D_BGPFCCR_CM_Pos)));

    /* Enable the CLUT Transfer Complete, transfer Error, configuration Error and CLUT Access Error interrupts */
    __HAL_DMA2D_ENABLE_IT(hdma2d, DMA2D_IT_CTC | DMA2D_IT_TE | DMA2D_IT_CE | DMA2D_IT_CAE);

    /* Enable the CLUT loading for the background */
    SET_BIT(hdma2d->Instance->BGPFCCR, DMA2D_BGPFCCR_START);
  }
  /* Configure the CLUT of the foreground DMA2D layer */
  else
  {
    /* Write foreground CLUT memory address */
    WRITE_REG(hdma2d->Instance->FGCMAR, (uint32_t)CLUTCfg->pCLUT);

    /* Write foreground CLUT size and CLUT color mode */
    MODIFY_REG(hdma2d->Instance->FGPFCCR, (DMA2D_FGPFCCR_CS | DMA2D_FGPFCCR_CM),
               ((CLUTCfg->Size << DMA2D_FGPFCCR_CS_Pos) | (CLUTCfg->CLUTColorMode << DMA2D_FGPFCCR_CM_Pos)));

    /* Enable the CLUT Transfer Complete, transfer Error, configuration Error and CLUT Access Error interrupts */
    __HAL_DMA2D_ENABLE_IT(hdma2d, DMA2D_IT_CTC | DMA2D_IT_TE | DMA2D_IT_CE | DMA2D_IT_CAE);

    /* Enable the CLUT loading for the foreground */
    SET_BIT(hdma2d->Instance->FGPFCCR, DMA2D_FGPFCCR_START);
  }

  return HAL_OK;
}

/**
  * @brief  Start DMA2D CLUT Loading.
  * @param  hdma2d   Pointer to a DMA2D_HandleTypeDef structure that contains
  *                   the configuration information for the DMA2D.
  * @param  CLUTCfg  Pointer to a DMA2D_CLUTCfgTypeDef structure that contains
  *                   the configuration information for the color look up table.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @note API obsolete and maintained for compatibility with legacy. User is
  *      invited to resort to HAL_DMA2D_CLUTStartLoad() instead to benefit from
  *      code compactness, code size and improved heap usage.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CLUTLoad(DMA2D_HandleTypeDef *hdma2d, DMA2D_CLUTCfgTypeDef CLUTCfg, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LAYER(LayerIdx));
  assert_param(IS_DMA2D_CLUT_CM(CLUTCfg.CLUTColorMode));
  assert_param(IS_DMA2D_CLUT_SIZE(CLUTCfg.Size));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* Configure the CLUT of the background DMA2D layer */
  if (LayerIdx == DMA2D_BACKGROUND_LAYER)
  {
    /* Write background CLUT memory address */
    WRITE_REG(hdma2d->Instance->BGCMAR, (uint32_t)CLUTCfg.pCLUT);

    /* Write background CLUT size and CLUT color mode */
    MODIFY_REG(hdma2d->Instance->BGPFCCR, (DMA2D_BGPFCCR_CS | DMA2D_BGPFCCR_CM),
               ((CLUTCfg.Size << DMA2D_BGPFCCR_CS_Pos) | (CLUTCfg.CLUTColorMode << DMA2D_BGPFCCR_CM_Pos)));

    /* Enable the CLUT loading for the background */
    SET_BIT(hdma2d->Instance->BGPFCCR, DMA2D_BGPFCCR_START);
  }
  /* Configure the CLUT of the foreground DMA2D layer */
  else
  {
    /* Write foreground CLUT memory address */
    WRITE_REG(hdma2d->Instance->FGCMAR, (uint32_t)CLUTCfg.pCLUT);

    /* Write foreground CLUT size and CLUT color mode */
    MODIFY_REG(hdma2d->Instance->FGPFCCR, (DMA2D_FGPFCCR_CS | DMA2D_FGPFCCR_CM),
               ((CLUTCfg.Size << DMA2D_FGPFCCR_CS_Pos) | (CLUTCfg.CLUTColorMode << DMA2D_FGPFCCR_CM_Pos)));

    /* Enable the CLUT loading for the foreground */
    SET_BIT(hdma2d->Instance->FGPFCCR, DMA2D_FGPFCCR_START);
  }

  return HAL_OK;
}

/**
  * @brief  Start DMA2D CLUT Loading with interrupt enabled.
  * @param  hdma2d   Pointer to a DMA2D_HandleTypeDef structure that contains
  *                   the configuration information for the DMA2D.
  * @param  CLUTCfg  Pointer to a DMA2D_CLUTCfgTypeDef structure that contains
  *                   the configuration information for the color look up table.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @note API obsolete and maintained for compatibility with legacy. User is
  *      invited to resort to HAL_DMA2D_CLUTStartLoad_IT() instead to benefit
  *      from code compactness, code size and improved heap usage.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CLUTLoad_IT(DMA2D_HandleTypeDef *hdma2d, DMA2D_CLUTCfgTypeDef CLUTCfg, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LAYER(LayerIdx));
  assert_param(IS_DMA2D_CLUT_CM(CLUTCfg.CLUTColorMode));
  assert_param(IS_DMA2D_CLUT_SIZE(CLUTCfg.Size));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* Configure the CLUT of the background DMA2D layer */
  if (LayerIdx == DMA2D_BACKGROUND_LAYER)
  {
    /* Write background CLUT memory address */
    WRITE_REG(hdma2d->Instance->BGCMAR, (uint32_t)CLUTCfg.pCLUT);

    /* Write background CLUT size and CLUT color mode */
    MODIFY_REG(hdma2d->Instance->BGPFCCR, (DMA2D_BGPFCCR_CS | DMA2D_BGPFCCR_CM),
               ((CLUTCfg.Size << DMA2D_BGPFCCR_CS_Pos) | (CLUTCfg.CLUTColorMode << DMA2D_BGPFCCR_CM_Pos)));

    /* Enable the CLUT Transfer Complete, transfer Error, configuration Error and CLUT Access Error interrupts */
    __HAL_DMA2D_ENABLE_IT(hdma2d, DMA2D_IT_CTC | DMA2D_IT_TE | DMA2D_IT_CE | DMA2D_IT_CAE);

    /* Enable the CLUT loading for the background */
    SET_BIT(hdma2d->Instance->BGPFCCR, DMA2D_BGPFCCR_START);
  }
  /* Configure the CLUT of the foreground DMA2D layer */
  else
  {
    /* Write foreground CLUT memory address */
    WRITE_REG(hdma2d->Instance->FGCMAR, (uint32_t)CLUTCfg.pCLUT);

    /* Write foreground CLUT size and CLUT color mode */
    MODIFY_REG(hdma2d->Instance->FGPFCCR, (DMA2D_FGPFCCR_CS | DMA2D_FGPFCCR_CM),
               ((CLUTCfg.Size << DMA2D_FGPFCCR_CS_Pos) | (CLUTCfg.CLUTColorMode << DMA2D_FGPFCCR_CM_Pos)));

    /* Enable the CLUT Transfer Complete, transfer Error, configuration Error and CLUT Access Error interrupts */
    __HAL_DMA2D_ENABLE_IT(hdma2d, DMA2D_IT_CTC | DMA2D_IT_TE | DMA2D_IT_CE | DMA2D_IT_CAE);

    /* Enable the CLUT loading for the foreground */
    SET_BIT(hdma2d->Instance->FGPFCCR, DMA2D_FGPFCCR_START);
  }

  return HAL_OK;
}

/**
  * @brief  Abort the DMA2D CLUT loading.
  * @param  hdma2d  Pointer to a DMA2D_HandleTypeDef structure that contains
  *                  the configuration information for the DMA2D.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CLUTLoading_Abort(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx)
{
  uint32_t tickstart;
  const __IO uint32_t *reg =  &(hdma2d->Instance->BGPFCCR);  /* by default, point at background register */

  /* Abort the CLUT loading */
  SET_BIT(hdma2d->Instance->CR, DMA2D_CR_ABORT);

  /* If foreground CLUT loading is considered, update local variables */
  if (LayerIdx == DMA2D_FOREGROUND_LAYER)
  {
    reg  = &(hdma2d->Instance->FGPFCCR);
  }


  /* Get tick */
  tickstart = HAL_GetTick();

  /* Check if the CLUT loading is aborted */
  while ((*reg & DMA2D_BGPFCCR_START) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > DMA2D_TIMEOUT_ABORT)
    {
      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TIMEOUT;

      /* Change the DMA2D state */
      hdma2d->State = HAL_DMA2D_STATE_TIMEOUT;

      /* Process Unlocked */
      __HAL_UNLOCK(hdma2d);

      return HAL_TIMEOUT;
    }
  }

  /* Disable the CLUT Transfer Complete, Transfer Error, Configuration Error and CLUT Access Error interrupts */
  __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_CTC | DMA2D_IT_TE | DMA2D_IT_CE | DMA2D_IT_CAE);

  /* Change the DMA2D state*/
  hdma2d->State = HAL_DMA2D_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hdma2d);

  return HAL_OK;
}

/**
  * @brief  Suspend the DMA2D CLUT loading.
  * @param  hdma2d Pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CLUTLoading_Suspend(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx)
{
  uint32_t tickstart;
  uint32_t loadsuspended;
  const __IO uint32_t *reg =  &(hdma2d->Instance->BGPFCCR);  /* by default, point at background register */

  /* Suspend the CLUT loading */
  SET_BIT(hdma2d->Instance->CR, DMA2D_CR_SUSP);

  /* If foreground CLUT loading is considered, update local variables */
  if (LayerIdx == DMA2D_FOREGROUND_LAYER)
  {
    reg  = &(hdma2d->Instance->FGPFCCR);
  }

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Check if the CLUT loading is suspended */
  /* 1st condition: Suspend Check */
  loadsuspended = ((hdma2d->Instance->CR & DMA2D_CR_SUSP) == DMA2D_CR_SUSP) ? 1UL : 0UL;
  /* 2nd condition: Not Start Check */
  loadsuspended |= ((*reg & DMA2D_BGPFCCR_START) != DMA2D_BGPFCCR_START) ? 1UL : 0UL;
  while (loadsuspended == 0UL)
  {
    if ((HAL_GetTick() - tickstart) > DMA2D_TIMEOUT_SUSPEND)
    {
      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TIMEOUT;

      /* Change the DMA2D state */
      hdma2d->State = HAL_DMA2D_STATE_TIMEOUT;

      return HAL_TIMEOUT;
    }
    /* 1st condition: Suspend Check */
    loadsuspended = ((hdma2d->Instance->CR & DMA2D_CR_SUSP) == DMA2D_CR_SUSP) ? 1UL : 0UL;
    /* 2nd condition: Not Start Check */
    loadsuspended |= ((*reg & DMA2D_BGPFCCR_START) != DMA2D_BGPFCCR_START) ? 1UL : 0UL;
  }

  /* Check whether or not a transfer is actually suspended and change the DMA2D state accordingly */
  if ((*reg & DMA2D_BGPFCCR_START) != 0U)
  {
    hdma2d->State = HAL_DMA2D_STATE_SUSPEND;
  }
  else
  {
    /* Make sure SUSP bit is cleared since it is meaningless
       when no transfer is on-going */
    CLEAR_BIT(hdma2d->Instance->CR, DMA2D_CR_SUSP);
  }

  return HAL_OK;
}

/**
  * @brief  Resume the DMA2D CLUT loading.
  * @param  hdma2d pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CLUTLoading_Resume(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx)
{
  /* Check the SUSP and START bits for background or foreground CLUT loading */
  if (LayerIdx == DMA2D_BACKGROUND_LAYER)
  {
    /* Background CLUT loading suspension check */
    if ((hdma2d->Instance->CR & DMA2D_CR_SUSP) == DMA2D_CR_SUSP)
    {
      if ((hdma2d->Instance->BGPFCCR & DMA2D_BGPFCCR_START) == DMA2D_BGPFCCR_START)
      {
        /* Ongoing CLUT loading is suspended: change the DMA2D state before resuming */
        hdma2d->State = HAL_DMA2D_STATE_BUSY;
      }
    }
  }
  else
  {
    /* Foreground CLUT loading suspension check */
    if ((hdma2d->Instance->CR & DMA2D_CR_SUSP) == DMA2D_CR_SUSP)
    {
      if ((hdma2d->Instance->FGPFCCR & DMA2D_FGPFCCR_START) == DMA2D_FGPFCCR_START)
      {
        /* Ongoing CLUT loading is suspended: change the DMA2D state before resuming */
        hdma2d->State = HAL_DMA2D_STATE_BUSY;
      }
    }
  }

  /* Resume the CLUT loading */
  CLEAR_BIT(hdma2d->Instance->CR, DMA2D_CR_SUSP);

  return HAL_OK;
}


/**

  * @brief  Polling for transfer complete or CLUT loading.
  * @param  hdma2d Pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_PollForTransfer(DMA2D_HandleTypeDef *hdma2d, uint32_t Timeout)
{
  uint32_t tickstart;
  uint32_t layer_start;
  __IO uint32_t isrflags = 0x0U;

  /* Polling for DMA2D transfer */
  if ((hdma2d->Instance->CR & DMA2D_CR_START) != 0U)
  {
    /* Get tick */
    tickstart = HAL_GetTick();

    while (__HAL_DMA2D_GET_FLAG(hdma2d, DMA2D_FLAG_TC) == 0U)
    {
      isrflags = READ_REG(hdma2d->Instance->ISR);
      if ((isrflags & (DMA2D_FLAG_CE | DMA2D_FLAG_TE)) != 0U)
      {
        if ((isrflags & DMA2D_FLAG_CE) != 0U)
        {
          hdma2d->ErrorCode |= HAL_DMA2D_ERROR_CE;
        }
        if ((isrflags & DMA2D_FLAG_TE) != 0U)
        {
          hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TE;
        }
        /* Clear the transfer and configuration error flags */
        __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_CE | DMA2D_FLAG_TE);

        /* Change DMA2D state */
        hdma2d->State = HAL_DMA2D_STATE_ERROR;

        /* Process unlocked */
        __HAL_UNLOCK(hdma2d);

        return HAL_ERROR;
      }
      /* Check for the Timeout */
      if (Timeout != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
        {
          /* Update error code */
          hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TIMEOUT;

          /* Change the DMA2D state */
          hdma2d->State = HAL_DMA2D_STATE_TIMEOUT;

          /* Process unlocked */
          __HAL_UNLOCK(hdma2d);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  /* Polling for CLUT loading (foreground or background) */
  layer_start = hdma2d->Instance->FGPFCCR & DMA2D_FGPFCCR_START;
  layer_start |= hdma2d->Instance->BGPFCCR & DMA2D_BGPFCCR_START;
  if (layer_start != 0U)
  {
    /* Get tick */
    tickstart = HAL_GetTick();

    while (__HAL_DMA2D_GET_FLAG(hdma2d, DMA2D_FLAG_CTC) == 0U)
    {
      isrflags = READ_REG(hdma2d->Instance->ISR);
      if ((isrflags & (DMA2D_FLAG_CAE | DMA2D_FLAG_CE | DMA2D_FLAG_TE)) != 0U)
      {
        if ((isrflags & DMA2D_FLAG_CAE) != 0U)
        {
          hdma2d->ErrorCode |= HAL_DMA2D_ERROR_CAE;
        }
        if ((isrflags & DMA2D_FLAG_CE) != 0U)
        {
          hdma2d->ErrorCode |= HAL_DMA2D_ERROR_CE;
        }
        if ((isrflags & DMA2D_FLAG_TE) != 0U)
        {
          hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TE;
        }
        /* Clear the CLUT Access Error, Configuration Error and Transfer Error flags */
        __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_CAE | DMA2D_FLAG_CE | DMA2D_FLAG_TE);

        /* Change DMA2D state */
        hdma2d->State = HAL_DMA2D_STATE_ERROR;

        /* Process unlocked */
        __HAL_UNLOCK(hdma2d);

        return HAL_ERROR;
      }
      /* Check for the Timeout */
      if (Timeout != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
        {
          /* Update error code */
          hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TIMEOUT;

          /* Change the DMA2D state */
          hdma2d->State = HAL_DMA2D_STATE_TIMEOUT;

          /* Process unlocked */
          __HAL_UNLOCK(hdma2d);

          return HAL_TIMEOUT;
        }
      }
    }
  }

  /* Clear the transfer complete and CLUT loading flags */
  __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_TC | DMA2D_FLAG_CTC);

  /* Change DMA2D state */
  hdma2d->State = HAL_DMA2D_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hdma2d);

  return HAL_OK;
}
/**
  * @brief  Handle DMA2D interrupt request.
  * @param  hdma2d Pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval HAL status
  */
void HAL_DMA2D_IRQHandler(DMA2D_HandleTypeDef *hdma2d)
{
  uint32_t isrflags = READ_REG(hdma2d->Instance->ISR);
  uint32_t ierflags = READ_REG(hdma2d->Instance->IER);

  /* Transfer Error Interrupt management ***************************************/
  if ((isrflags & DMA2D_FLAG_TE) != 0U)
  {
    if ((ierflags & DMA2D_IT_TE) != 0U)
    {
      /* Disable the transfer Error interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_TE);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TE;

      /* Clear the transfer error flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_TE);

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_STATE_ERROR;

      /* Process Unlocked */
      __HAL_UNLOCK(hdma2d);

      if (hdma2d->XferErrorCallback != NULL)
      {
        /* Transfer error Callback */
        hdma2d->XferErrorCallback(hdma2d);
      }
    }
  }
  /* Configuration Error Interrupt management **********************************/
  if ((isrflags & DMA2D_FLAG_CE) != 0U)
  {
    if ((ierflags & DMA2D_IT_CE) != 0U)
    {
      /* Disable the Configuration Error interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_CE);

      /* Clear the Configuration error flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_CE);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_CE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_STATE_ERROR;

      /* Process Unlocked */
      __HAL_UNLOCK(hdma2d);

      if (hdma2d->XferErrorCallback != NULL)
      {
        /* Transfer error Callback */
        hdma2d->XferErrorCallback(hdma2d);
      }
    }
  }
  /* CLUT access Error Interrupt management ***********************************/
  if ((isrflags & DMA2D_FLAG_CAE) != 0U)
  {
    if ((ierflags & DMA2D_IT_CAE) != 0U)
    {
      /* Disable the CLUT access error interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_CAE);

      /* Clear the CLUT access error flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_CAE);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_CAE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_STATE_ERROR;

      /* Process Unlocked */
      __HAL_UNLOCK(hdma2d);

      if (hdma2d->XferErrorCallback != NULL)
      {
        /* Transfer error Callback */
        hdma2d->XferErrorCallback(hdma2d);
      }
    }
  }
  /* Transfer watermark Interrupt management **********************************/
  if ((isrflags & DMA2D_FLAG_TW) != 0U)
  {
    if ((ierflags & DMA2D_IT_TW) != 0U)
    {
      /* Disable the transfer watermark interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_TW);

      /* Clear the transfer watermark flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_TW);

      /* Transfer watermark Callback */
#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      hdma2d->LineEventCallback(hdma2d);
#else
      HAL_DMA2D_LineEventCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

    }
  }
  /* Transfer Complete Interrupt management ************************************/
  if ((isrflags & DMA2D_FLAG_TC) != 0U)
  {
    if ((ierflags & DMA2D_IT_TC) != 0U)
    {
      /* Disable the transfer complete interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_TC);

      /* Clear the transfer complete flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_TC);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_NONE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_STATE_READY;

      /* Process Unlocked */
      __HAL_UNLOCK(hdma2d);

      if (hdma2d->XferCpltCallback != NULL)
      {
        /* Transfer complete Callback */
        hdma2d->XferCpltCallback(hdma2d);
      }
    }
  }
  /* CLUT Transfer Complete Interrupt management ******************************/
  if ((isrflags & DMA2D_FLAG_CTC) != 0U)
  {
    if ((ierflags & DMA2D_IT_CTC) != 0U)
    {
      /* Disable the CLUT transfer complete interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_CTC);

      /* Clear the CLUT transfer complete flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_CTC);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_NONE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_STATE_READY;

      /* Process Unlocked */
      __HAL_UNLOCK(hdma2d);

      /* CLUT Transfer complete Callback */
#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      hdma2d->CLUTLoadingCpltCallback(hdma2d);
#else
      HAL_DMA2D_CLUTLoadingCpltCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
    }
  }

}

/**
  * @brief  Transfer watermark callback.
  * @param  hdma2d pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval None
  */
__weak void HAL_DMA2D_LineEventCallback(DMA2D_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_LineEventCallback can be implemented in the user file.
   */
}

/**
  * @brief  CLUT Transfer Complete callback.
  * @param  hdma2d pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval None
  */
__weak void HAL_DMA2D_CLUTLoadingCpltCallback(DMA2D_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CLUTLoadingCpltCallback can be implemented in the user file.
   */
}

/**
  * @}
  */

/** @defgroup DMA2D_Exported_Functions_Group3 Peripheral Control functions
  *  @brief    Peripheral Control functions
  *
@verbatim
 ===============================================================================
                    ##### Peripheral Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the DMA2D foreground or background layer parameters.
      (+) Configure the DMA2D CLUT transfer.
      (+) Configure the line watermark
      (+) Configure the dead time value.
      (+) Enable or disable the dead time value functionality.


@endverbatim
  * @{
  */

/**
  * @brief  Configure the DMA2D Layer according to the specified
  *         parameters in the DMA2D_HandleTypeDef.
  * @param  hdma2d Pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_ConfigLayer(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx)
{
  const DMA2D_LayerCfgTypeDef *pLayerCfg;
  uint32_t regMask;
  uint32_t regValue;

  /* Check the parameters */
  assert_param(IS_DMA2D_LAYER(LayerIdx));
  assert_param(IS_DMA2D_OFFSET(hdma2d->LayerCfg[LayerIdx].InputOffset));
  if (hdma2d->Init.Mode != DMA2D_R2M)
  {
    assert_param(IS_DMA2D_INPUT_COLOR_MODE(hdma2d->LayerCfg[LayerIdx].InputColorMode));
    if (hdma2d->Init.Mode != DMA2D_M2M)
    {
      assert_param(IS_DMA2D_ALPHA_MODE(hdma2d->LayerCfg[LayerIdx].AlphaMode));
    }
  }
  assert_param(IS_DMA2D_ALPHA_INVERTED(hdma2d->LayerCfg[LayerIdx].AlphaInverted));
  assert_param(IS_DMA2D_RB_SWAP(hdma2d->LayerCfg[LayerIdx].RedBlueSwap));

  if ((LayerIdx == DMA2D_FOREGROUND_LAYER) && (hdma2d->LayerCfg[LayerIdx].InputColorMode == DMA2D_INPUT_YCBCR))
  {
    assert_param(IS_DMA2D_CHROMA_SUB_SAMPLING(hdma2d->LayerCfg[LayerIdx].ChromaSubSampling));
  }

  assert_param(IS_DMA2D_ALPHA_POSITION(hdma2d->LayerCfg[LayerIdx].AlphaPosition));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  pLayerCfg = &hdma2d->LayerCfg[LayerIdx];

  /* Prepare the value to be written to the BGPFCCR or FGPFCCR register */
  regValue = pLayerCfg->InputColorMode | (pLayerCfg->AlphaMode << DMA2D_BGPFCCR_AM_Pos) | \
             (pLayerCfg->AlphaInverted << DMA2D_BGPFCCR_AI_Pos) | (pLayerCfg->RedBlueSwap << DMA2D_BGPFCCR_RBS_Pos) | \
             (pLayerCfg->AlphaPosition << DMA2D_BGPFCCR_APOS_Pos);
  regMask  = (DMA2D_BGPFCCR_CM | DMA2D_BGPFCCR_AM | DMA2D_BGPFCCR_ALPHA | DMA2D_BGPFCCR_AI | DMA2D_BGPFCCR_RBS | \
              DMA2D_BGPFCCR_APOS);


  if ((pLayerCfg->InputColorMode == DMA2D_INPUT_A4) || (pLayerCfg->InputColorMode == DMA2D_INPUT_A8))
  {
    regValue |= (pLayerCfg->InputAlpha & DMA2D_BGPFCCR_ALPHA);
  }
  else
  {
    regValue |= (pLayerCfg->InputAlpha << DMA2D_BGPFCCR_ALPHA_Pos);
  }

  /* Configure the background DMA2D layer */
  if (LayerIdx == DMA2D_BACKGROUND_LAYER)
  {
    /* Write DMA2D BGPFCCR register */
    MODIFY_REG(hdma2d->Instance->BGPFCCR, regMask, regValue);

    /* DMA2D BGOR register configuration -------------------------------------*/
    WRITE_REG(hdma2d->Instance->BGOR, pLayerCfg->InputOffset);

    /* DMA2D BGCOLR register configuration -------------------------------------*/
    if ((pLayerCfg->InputColorMode == DMA2D_INPUT_A4) || (pLayerCfg->InputColorMode == DMA2D_INPUT_A8))
    {
      WRITE_REG(hdma2d->Instance->BGCOLR, pLayerCfg->InputAlpha & (DMA2D_BGCOLR_BLUE | DMA2D_BGCOLR_GREEN | \
                                                                   DMA2D_BGCOLR_RED));
    }
  }
  /* Configure the foreground DMA2D layer */
  else
  {

    if (pLayerCfg->InputColorMode == DMA2D_INPUT_YCBCR)
    {
      regValue |= (pLayerCfg->ChromaSubSampling << DMA2D_FGPFCCR_CSS_Pos);
      regMask  |= DMA2D_FGPFCCR_CSS;
    }

    /* Write DMA2D FGPFCCR register */
    MODIFY_REG(hdma2d->Instance->FGPFCCR, regMask, regValue);

    /* DMA2D FGOR register configuration -------------------------------------*/
    WRITE_REG(hdma2d->Instance->FGOR, pLayerCfg->InputOffset);

    /* DMA2D FGCOLR register configuration -------------------------------------*/
    if ((pLayerCfg->InputColorMode == DMA2D_INPUT_A4) || (pLayerCfg->InputColorMode == DMA2D_INPUT_A8))
    {
      WRITE_REG(hdma2d->Instance->FGCOLR, pLayerCfg->InputAlpha & (DMA2D_FGCOLR_BLUE | DMA2D_FGCOLR_GREEN | \
                                                                   DMA2D_FGCOLR_RED));
    }
  }
  /* Initialize the DMA2D state*/
  hdma2d->State = HAL_DMA2D_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hdma2d);

  return HAL_OK;
}

/**
  * @brief  Configure the DMA2D CLUT Transfer.
  * @param  hdma2d   Pointer to a DMA2D_HandleTypeDef structure that contains
  *                   the configuration information for the DMA2D.
  * @param  CLUTCfg  Pointer to a DMA2D_CLUTCfgTypeDef structure that contains
  *                   the configuration information for the color look up table.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @note API obsolete and maintained for compatibility with legacy. User is invited
  *      to resort to HAL_DMA2D_CLUTStartLoad() instead to benefit from code compactness,
  *      code size and improved heap usage.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_ConfigCLUT(DMA2D_HandleTypeDef *hdma2d, DMA2D_CLUTCfgTypeDef CLUTCfg, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LAYER(LayerIdx));
  assert_param(IS_DMA2D_CLUT_CM(CLUTCfg.CLUTColorMode));
  assert_param(IS_DMA2D_CLUT_SIZE(CLUTCfg.Size));

  /* Process locked */
  __HAL_LOCK(hdma2d);

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* Configure the CLUT of the background DMA2D layer */
  if (LayerIdx == DMA2D_BACKGROUND_LAYER)
  {
    /* Write background CLUT memory address */
    WRITE_REG(hdma2d->Instance->BGCMAR, (uint32_t)CLUTCfg.pCLUT);

    /* Write background CLUT size and CLUT color mode */
    MODIFY_REG(hdma2d->Instance->BGPFCCR, (DMA2D_BGPFCCR_CS | DMA2D_BGPFCCR_CM),
               ((CLUTCfg.Size << DMA2D_BGPFCCR_CS_Pos) | (CLUTCfg.CLUTColorMode << DMA2D_BGPFCCR_CM_Pos)));
  }
  /* Configure the CLUT of the foreground DMA2D layer */
  else
  {
    /* Write foreground CLUT memory address */
    WRITE_REG(hdma2d->Instance->FGCMAR, (uint32_t)CLUTCfg.pCLUT);

    /* Write foreground CLUT size and CLUT color mode */
    MODIFY_REG(hdma2d->Instance->FGPFCCR, (DMA2D_FGPFCCR_CS | DMA2D_FGPFCCR_CM),
               ((CLUTCfg.Size << DMA2D_FGPFCCR_CS_Pos) | (CLUTCfg.CLUTColorMode << DMA2D_FGPFCCR_CM_Pos)));
  }

  /* Set the DMA2D state to Ready*/
  hdma2d->State = HAL_DMA2D_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hdma2d);

  return HAL_OK;
}


/**
  * @brief  Configure the DMA2D rotation/mirroring for the selected source Foreground, Background or Blender output
  * @param  hdma2d    Pointer to a DMA2D_HandleTypeDef structure that contains
  *                   the configuration information for the DMA2D peripheral.
  * @param  Source  Specifies the source of the tile buffer.
  *                        This parameter can be a value from @ref DMA2D_SOURCE
  * @param  Mirroring_Type   Specifies the mirroring and rotation operation.
  *                          This parameter can be a value from @ref DMA2D_MirroringRotation
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_ConfigRotation(DMA2D_HandleTypeDef *hdma2d, uint32_t Source, uint32_t Mirroring_Type)
{
  /* Check parameters */
  assert_param(IS_DMA2D_ROT_SRC(Source));
  assert_param(IS_DMA2D_ROT_TYPE(Mirroring_Type));


  /* Set tile buffer control register */
  WRITE_REG(hdma2d->Instance->TBCR, Source | (Mirroring_Type << DMA2D_TBCR_XMEN_Pos));

  return HAL_OK;
}

/**
  * @brief  Configures the DMA2D Downscaling for the selected source Foreground, Background or Blender output
  * @param  hdma2d           Pointer to DMA2D handle structure.
  * @param Source           Specifies the source of the tile buffer.
  *                         This parameter can be a value from @ref DMA2D_SOURCE
  * @param  pDownscalingCfg  Pointer to DMA2D_DownscalingCfgTypeDef that contains
  *                          the configuration information for downscaling.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_ConfigDownscaling(DMA2D_HandleTypeDef *hdma2d, uint32_t Source,
                                              DMA2D_DownscalingCfgTypeDef *pDownscalingCfg)
{
  /* HSEP and VSTEP  Calculation */
  uint16_t hstep = (4096U / (pDownscalingCfg->HRatio) - 1U);
  uint16_t vstep = (4096U / (pDownscalingCfg->VRatio) - 1U);

  /* Check parameters */
  assert_param(IS_DMA2D_ALL_INSTANCE(hdma2d->Instance));
  assert_param(IS_DMA2D_SCALE_SRC(Source));
  assert_param(IS_DMA2D_SCALE_HSTEP(hstep));
  assert_param(IS_DMA2D_SCALE_VSTEP(vstep));
  assert_param(IS_DMA2D_SCALE_PIXEL_PER_LINE(pDownscalingCfg->PixelPerLines));
  assert_param(IS_DMA2D_SCALE_NUMBER_OF_LINES(pDownscalingCfg->NumberOfLines));
  assert_param(IS_DMA2D_SCALE_HPHASE(pDownscalingCfg->HPhase));
  assert_param(IS_DMA2D_SCALE_VPHASE(pDownscalingCfg->VPhase));

  /* Config scaling source */
  MODIFY_REG(hdma2d->Instance->SCR, DMA2D_SCR_SRC, Source);

  /* Config scaling Height and Width */
  MODIFY_REG(hdma2d->Instance->SNLR, (DMA2D_SNLR_NL | DMA2D_SNLR_PL), (pDownscalingCfg->NumberOfLines |
                                                                       (pDownscalingCfg->PixelPerLines <<
                                                                        DMA2D_SNLR_PL_Pos)));

  /* Config scaling HSEP and VSTEP */
  MODIFY_REG(hdma2d->Instance->SSR, (DMA2D_SSR_HSTEP | DMA2D_SSR_VSTEP), (hstep | (((uint32_t)vstep) <<
                                                                                    DMA2D_SSR_VSTEP_Pos)));

  /* Config scaling HPHASE and VPHASE */
  MODIFY_REG(hdma2d->Instance->SPR, (DMA2D_SPR_HPHASE | DMA2D_SPR_VPHASE),
            (pDownscalingCfg->HPhase | (((uint32_t)pDownscalingCfg->VPhase) << DMA2D_SPR_VPHASE_Pos)));

  return HAL_OK;
}

/**
  * @brief  Configure the DMA2D stencil buffer for the selected source Foreground, Background or Blender output.
  * @param  hdma2d      Pointer to DMA2D handle structure.
  * @param  Source      Stencil source selection.
  *                     This parameter can be a value from @ref DMA2D_SOURCE
  * @param  pStencilCfg pointer to DMA2D_StencilCfgTypeDef that contains Stencil buffer configuration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_ConfigStencil(DMA2D_HandleTypeDef *hdma2d, uint32_t Source,
                                          DMA2D_StencilCfgTypeDef *pStencilCfg)
{

  /* Check parameters */
  assert_param(IS_DMA2D_STENCIL_SRC(Source));
  assert_param(IS_DMA2D_STENCIL_MODE(pStencilCfg->Mode));
  assert_param(IS_DMA2D_STENCIL_LO(pStencilCfg->LineOffset));
  assert_param(IS_DMA2D_STENCIL_HPRE(pStencilCfg->HPre));
  assert_param(IS_DMA2D_STENCIL_HTRAIL(pStencilCfg->HTrail));
  assert_param(IS_DMA2D_STENCIL_ALPHA_INVERTED(pStencilCfg->AlphaInverted));

  /* Configure SBCR: source and mode and Alpha Invert: SRC MODE AI */
  MODIFY_REG(hdma2d->Instance->SBCR, DMA2D_SBCR_SRC | DMA2D_SBCR_MODE | DMA2D_SBCR_AI,
             Source | (pStencilCfg->Mode << DMA2D_SBCR_MODE_Pos) | (pStencilCfg->AlphaInverted << DMA2D_SBCR_AI_Pos));

  /* Set stencil buffer address */
  WRITE_REG(hdma2d->Instance->SBMAR, pStencilCfg->Address);

  /* Set stencil buffer offset */
  MODIFY_REG(hdma2d->Instance->SBOR, DMA2D_SBOR_LO, pStencilCfg->LineOffset);

  /* Set stencil buffer memory skip: Horizontal pre/trail pixels */
  MODIFY_REG(hdma2d->Instance->SBMSR, (DMA2D_SBMSR_HPRE | DMA2D_SBMSR_HTRAIL),
             (pStencilCfg->HPre | (pStencilCfg->HTrail << DMA2D_SBMSR_HTRAIL_Pos)));

  return HAL_OK;
}
/**
  * @brief  Configure the line watermark.
  * @param  hdma2d Pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @param  Line   Line Watermark configuration (maximum 16-bit long value expected).
  * @note   HAL_DMA2D_ProgramLineEvent() API enables the transfer watermark interrupt.
  * @note   The transfer watermark interrupt is disabled once it has occurred.
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_DMA2D_ProgramLineEvent(DMA2D_HandleTypeDef *hdma2d, uint32_t Line)
{
  /* Check the parameters */
  if (Line > DMA2D_LWR_LW)
  {
    return HAL_ERROR;
  }
  else
  {
    /* Process locked */
    __HAL_LOCK(hdma2d);

    /* Change DMA2D peripheral state */
    hdma2d->State = HAL_DMA2D_STATE_BUSY;

    /* Sets the Line watermark configuration */
    WRITE_REG(hdma2d->Instance->LWR, Line);

    /* Enable the Line interrupt */
    __HAL_DMA2D_ENABLE_IT(hdma2d, DMA2D_IT_TW);

    /* Initialize the DMA2D state*/
    hdma2d->State = HAL_DMA2D_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hdma2d);

    return HAL_OK;
  }
}

/**
  * @brief Enable DMA2D dead time feature.
  * @param hdma2d DMA2D handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_EnableDeadTime(DMA2D_HandleTypeDef *hdma2d)
{
  /* Process Locked */
  __HAL_LOCK(hdma2d);

  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* Set DMA2D_AMTCR EN bit */
  SET_BIT(hdma2d->Instance->AMTCR, DMA2D_AMTCR_EN);

  hdma2d->State = HAL_DMA2D_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hdma2d);

  return HAL_OK;
}

/**
  * @brief Disable DMA2D dead time feature.
  * @param hdma2d DMA2D handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_DisableDeadTime(DMA2D_HandleTypeDef *hdma2d)
{
  /* Process Locked */
  __HAL_LOCK(hdma2d);

  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* Clear DMA2D_AMTCR EN bit */
  CLEAR_BIT(hdma2d->Instance->AMTCR, DMA2D_AMTCR_EN);

  hdma2d->State = HAL_DMA2D_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hdma2d);

  return HAL_OK;
}

/**
  * @brief Configure dead time.
  * @note The dead time value represents the guaranteed minimum number of cycles between
  *       two consecutive transactions on the AHB bus.
  * @param hdma2d DMA2D handle.
  * @param DeadTime dead time value.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_ConfigDeadTime(DMA2D_HandleTypeDef *hdma2d, uint8_t DeadTime)
{
  /* Process Locked */
  __HAL_LOCK(hdma2d);

  hdma2d->State = HAL_DMA2D_STATE_BUSY;

  /* Set DMA2D_AMTCR DT field */
  MODIFY_REG(hdma2d->Instance->AMTCR, DMA2D_AMTCR_DT, (((uint32_t) DeadTime) << DMA2D_AMTCR_DT_Pos));

  hdma2d->State = HAL_DMA2D_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hdma2d);

  return HAL_OK;
}

/**
  * @}
  */


/** @defgroup DMA2D_Exported_Functions_Group4 Peripheral State and Error functions
  *  @brief    Peripheral State functions
  *
@verbatim
 ===============================================================================
                  ##### Peripheral State and Errors functions #####
 ===============================================================================
    [..]
    This subsection provides functions allowing to:
      (+) Get the DMA2D state
      (+) Get the DMA2D error code

@endverbatim
  * @{
  */

/**
  * @brief  Return the DMA2D state
  * @param  hdma2d pointer to a DMA2D_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval HAL state
  */
HAL_DMA2D_StateTypeDef HAL_DMA2D_GetState(const DMA2D_HandleTypeDef *hdma2d)
{
  return hdma2d->State;
}

/**
  * @brief  Return the DMA2D error code
  * @param  hdma2d  pointer to a DMA2D_HandleTypeDef structure that contains
  *               the configuration information for DMA2D.
  * @retval DMA2D Error Code
  */
uint32_t HAL_DMA2D_GetError(const DMA2D_HandleTypeDef *hdma2d)
{
  return hdma2d->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup DMA2D_Private_Functions DMA2D Private Functions
  * @{
  */

/**
  * @brief  Set the DMA2D transfer parameters.
  * @param  hdma2d     Pointer to a DMA2D_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA2D.
  * @param  pdata      The source memory Buffer address
  * @param  DstAddress The destination memory Buffer address
  * @param  Width      The width of data to be transferred from source to destination.
  * @param  Height     The height of data to be transferred from source to destination.
  * @retval HAL status
  */
static void DMA2D_SetConfig(DMA2D_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress, uint32_t Width,
                            uint32_t Height)
{
  /* Configure DMA2D data size */
  /* Swap Width and Height when X/Y Swap is enabled */
  if ((hdma2d->Instance->TBCR & DMA2D_TBCR_XYSEN) == DMA2D_TBCR_XYSEN)
  {
    MODIFY_REG(hdma2d->Instance->NLR, (DMA2D_NLR_NL | DMA2D_NLR_PL), (Width | (Height << DMA2D_NLR_PL_Pos)));
  }
  else
  {
    MODIFY_REG(hdma2d->Instance->NLR, (DMA2D_NLR_NL | DMA2D_NLR_PL), (Height | (Width << DMA2D_NLR_PL_Pos)));
  }
  /* Make sure that Layer input color mode is configured */
  assert_param(IS_DMA2D_INPUT_COLOR_MODE(hdma2d->LayerCfg[1].InputColorMode));
  assert_param(IS_DMA2D_INPUT_COLOR_MODE(hdma2d->LayerCfg[0].InputColorMode));
  MODIFY_REG(hdma2d->Instance->FGPFCCR, DMA2D_FGPFCCR_CM, hdma2d->LayerCfg[1].InputColorMode);
  MODIFY_REG(hdma2d->Instance->BGPFCCR, DMA2D_BGPFCCR_CM, hdma2d->LayerCfg[0].InputColorMode);

  /* Configure DMA2D destination address */
  WRITE_REG(hdma2d->Instance->OMAR, DstAddress);

  /* Register to memory DMA2D mode selected */
  if (hdma2d->Init.Mode == DMA2D_R2M)
  {
    /* Write to DMA2D OCOLR register */
    WRITE_REG(hdma2d->Instance->OCOLR, pdata);
  }
  else if (hdma2d->Init.Mode == DMA2D_M2M_BLEND_FG) /*M2M_blending with fixed color FG DMA2D Mode selected*/
  {
    WRITE_REG(hdma2d->Instance->BGMAR, pdata);
  }
  else /* M2M, M2M_PFC,M2M_Blending or M2M_blending with fixed color BG DMA2D Mode */
  {
    /* Configure DMA2D source address */
    WRITE_REG(hdma2d->Instance->FGMAR, pdata);
  }
}
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 0 */
#if (USE_DMA2D_COMMAND_LIST_MODE == 1)
/**
  * @brief  Initialize the DMA2D CL (Command List) Mode
  *         This function configures the DMA2D ring buffer according to RingBuffer parameter of DMA2D_CL_HandleTypeDef
  * @note This function sets up the register values for the configuration along with the specific LDM instruction.
  *       These will be saved in the chosen command list via HAL_DMA2D_CL_InsertCommandList().
  *       When the Command List execution begins, the internal registers will be loaded according to the prepared
  *       register values and the corresponding instruction.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_Init(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Check the DMA2D peripheral state */
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }
  /* Check the parameters */
  assert_param(IS_DMA2D_ALL_INSTANCE(hdma2d->Instance));
  assert_param(IS_DMA2D_MODE(hdma2d->Init.Mode));
  assert_param(IS_DMA2D_CMODE(hdma2d->Init.ColorMode));
  assert_param(IS_DMA2D_OFFSET(hdma2d->Init.OutputOffset));
  assert_param(IS_DMA2D_ALPHA_INVERTED(hdma2d->Init.AlphaInverted));
  assert_param(IS_DMA2D_RB_SWAP(hdma2d->Init.RedBlueSwap));
  assert_param(IS_DMA2D_LOM_MODE(hdma2d->Init.LineOffsetMode));
  assert_param(IS_DMA2D_BYTES_SWAP(hdma2d->Init.BytesSwap));
  assert_param(IS_DMA2D_CL_ADDRESS_RB_VALID((uint32_t) hdma2d->RingBuffer.Address));
  assert_param(IS_DMA2D_CL_RB_SIZE(hdma2d->RingBuffer.Size));

#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
  if (hdma2d->State == HAL_DMA2D_CL_STATE_RESET)
  {
    /* Reset Callback pointers in HAL_DMA2D_CL_STATE_RESET only */
    hdma2d->LineEventCallback              = HAL_DMA2D_CL_LineEventCallback;
    hdma2d->CLUTLoadingCpltCallback        = HAL_DMA2D_CL_CLUTLoadingCpltCallback;
    hdma2d->RBXferCpltCallback             = HAL_DMA2D_CL_RBXferCpltCallback;
    hdma2d->CL_SuspendCallback             = HAL_DMA2D_CL_SuspendCallback;
    hdma2d->CL_GeneralPurposeEventCallback = HAL_DMA2D_CL_GeneralPuposeEventCallback;
    hdma2d->XferErrorCallback              = HAL_DMA2D_CL_XferErrorCallback;
    hdma2d->XferCpltCallback               = HAL_DMA2D_CL_TransferCpltCallback;
    hdma2d->ErrorCallback                  = HAL_DMA2D_CL_ErrorCallback;
    hdma2d->MspDeInitCallback              = HAL_DMA2D_CL_MspDeInit;
    if (hdma2d->MspInitCallback == NULL)
    {
      hdma2d->MspInitCallback = HAL_DMA2D_CL_MspInit;
    }
    /* Init the low level hardware */
    hdma2d->MspInitCallback(hdma2d);
  }
#else
  if (hdma2d->State == HAL_DMA2D_CL_STATE_RESET)
  {
    /* Init the low level hardware */
    HAL_DMA2D_CL_MspInit(hdma2d);
  }
#endif /* (USE_HAL_DMA2D_REGISTER_CALLBACKS) */
  if (hdma2d->State == HAL_DMA2D_CL_STATE_RESET)
  {
    /* Reset Read and write pointers */
    hdma2d->Instance->RBWPR = 0;
    hdma2d->Instance->RBHPR = 0;
    /* Configure the Ring Buffer Size and Base Address */
    WRITE_REG(hdma2d->Instance->RBBAR, (uint32_t)hdma2d->RingBuffer.Address);
    MODIFY_REG(hdma2d->Instance->CLCR, DMA2D_CLCR_RBS, (hdma2d->RingBuffer.Size << DMA2D_CLCR_RBS_Pos));
    hdma2d->LDM_Instruction = 0;
    uint32_t index;
    for (index = 0 ; index < HAL_DMA2D_CL_LDM_REG_NUM; index++)
    {
      hdma2d->LDM_Reg_values[index] = 0x00000000;
    }
    /* Update error code */
    hdma2d->ErrorCode = HAL_DMA2D_ERROR_NONE;
    /* Initialize the DMA2D state*/
    hdma2d->State  = HAL_DMA2D_CL_STATE_READY;
  }
  /* DMA2D CR register configuration -------------------------------------------*/
  DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_CR_REG, DMA2D_CR_MODE | DMA2D_CR_LOM,
                          hdma2d->Init.Mode | hdma2d->Init.LineOffsetMode);
  /* DMA2D OPFCCR register configuration ---------------------------------------*/
  DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_OPFCCR_REG, DMA2D_OPFCCR_CM | DMA2D_OPFCCR_SB,
                          hdma2d->Init.ColorMode | hdma2d->Init.BytesSwap);
  /* DMA2D OOR register configuration ------------------------------------------*/
  DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_OOR_REG, DMA2D_OOR_LO, hdma2d->Init.OutputOffset);
  /* DMA2D OPFCCR AI AP and RBS fields setting (Output Alpha Inversion)*/
  DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_OPFCCR_REG, (DMA2D_OPFCCR_AI | DMA2D_OPFCCR_RBS | DMA2D_OPFCCR_APOS),
                          ((hdma2d->Init.AlphaInverted << DMA2D_OPFCCR_AI_Pos) | \
                           (hdma2d->Init.RedBlueSwap << DMA2D_OPFCCR_RBS_Pos) | \
                           (hdma2d->Init.AlphaPosition << DMA2D_OPFCCR_APOS_Pos)));

  return HAL_OK;
}

/**
  * @brief  Deinitializes the DMA2D peripheral registers to their default reset
  *         values.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval None
  */
HAL_StatusTypeDef HAL_DMA2D_CL_DeInit(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Check the DMA2D peripheral state */
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  /* Abort CMD List */
  hdma2d->Instance->CLCR   = 0x4;

  /* Reset DMA2D control registers */
  hdma2d->Instance->CR       = 0U;
  hdma2d->Instance->IFCR     = 0U;
  hdma2d->Instance->FGOR     = 0U;
  hdma2d->Instance->BGOR     = 0U;
  hdma2d->Instance->FGPFCCR  = 0U;
  hdma2d->Instance->BGPFCCR  = 0U;
  hdma2d->Instance->OPFCCR   = 0U;

  hdma2d->Instance->SBCR  = 0;
  hdma2d->Instance->SBMAR = 0;
  hdma2d->Instance->SBOR  = 0;

  hdma2d->Instance->RBBAR  = 0;
  hdma2d->Instance->RBHPR  = 0;
  hdma2d->Instance->RBWPR  = 0;
  hdma2d->Instance->LBCBAR = 0;
  hdma2d->Instance->LBCSR  = 0;
  hdma2d->Instance->LBCAR  = 0;
  hdma2d->Instance->GPFCR  = 0;

  /* Disable CL and clear LDM , RING BUFFER and cmdlist offset */
#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)

  if (hdma2d->MspDeInitCallback == NULL)
  {
    hdma2d->MspDeInitCallback = HAL_DMA2D_CL_MspDeInit;
  }

  /* DeInit the low level hardware */
  hdma2d->MspDeInitCallback(hdma2d);

#else
  /* Carry on with de-initialization of low level hardware */
  HAL_DMA2D_CL_MspDeInit(hdma2d);
#endif /* (USE_HAL_DMA2D_REGISTER_CALLBACKS) */

  /* Update error code */
  hdma2d->ErrorCode = HAL_DMA2D_ERROR_NONE;

  /* Initialize the DMA2D state*/
  hdma2d->State  = HAL_DMA2D_CL_STATE_RESET;

  return HAL_OK;
}
/**
  * @brief  Add Layer Configuration LDM with the specified parameters.
  * @note This function sets up the register values for the layer configuration along with the specific LDM instruction.
  *       These will be saved in the chosen command list via HAL_DMA2D_CL_InsertCommandList().
  *       When the Command List execution begins, the internal registers will be loaded according to the prepared
  *       register values and the corresponding instruction.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @param  LayerIdx (DMA2D Layer index): it can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @param  pLayerCfg Pointer to a DMA2D_LayerCfgTypeDef structure that contains
  *                   the configuration parameters for the specified layer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_AddConfigLayerCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t LayerIdx,
                                                 DMA2D_LayerCfgTypeDef *pLayerCfg)
{
  uint32_t regMask;
  uint32_t regValue;

  /* Check the parameters */
  assert_param(IS_DMA2D_LAYER(LayerIdx));
  assert_param(IS_DMA2D_OFFSET(pLayerCfg->InputOffset));
  if (hdma2d->Init.Mode != DMA2D_R2M)
  {
    assert_param(IS_DMA2D_INPUT_COLOR_MODE(pLayerCfg->InputColorMode));
    if (hdma2d->Init.Mode != DMA2D_M2M)
    {
      assert_param(IS_DMA2D_ALPHA_MODE(pLayerCfg->AlphaMode));
    }
  }

  assert_param(IS_DMA2D_ALPHA_INVERTED(pLayerCfg->AlphaInverted));
  assert_param(IS_DMA2D_RB_SWAP(pLayerCfg->RedBlueSwap));
  assert_param(IS_DMA2D_ALPHA_POSITION(pLayerCfg->AlphaPosition));
  assert_param(IS_DMA2D_CHROMA_SUB_SAMPLING(pLayerCfg->ChromaSubSampling));

  /* Prepare the value to be written to the BGPFCCR or FGPFCCR register */
  regValue = pLayerCfg->InputColorMode | (pLayerCfg->AlphaMode << DMA2D_BGPFCCR_AM_Pos) | \
             (pLayerCfg->AlphaInverted << DMA2D_BGPFCCR_AI_Pos) | (pLayerCfg->RedBlueSwap << DMA2D_BGPFCCR_RBS_Pos) | \
             (pLayerCfg->AlphaPosition << DMA2D_BGPFCCR_APOS_Pos);
  regMask  = (DMA2D_BGPFCCR_CM | DMA2D_BGPFCCR_AM | DMA2D_BGPFCCR_ALPHA | DMA2D_BGPFCCR_AI | DMA2D_BGPFCCR_RBS | \
              DMA2D_BGPFCCR_APOS);


  if ((pLayerCfg->InputColorMode == DMA2D_INPUT_A8) || (pLayerCfg->InputColorMode == DMA2D_INPUT_A2) || \
      (pLayerCfg->InputColorMode == DMA2D_INPUT_A2) || (pLayerCfg->InputColorMode == DMA2D_INPUT_A1))
  {
    regValue |= (pLayerCfg->InputAlpha & DMA2D_BGPFCCR_ALPHA);
  }
  else
  {
    regValue |= (pLayerCfg->InputAlpha << DMA2D_BGPFCCR_ALPHA_Pos);
  }

  /* Configure the background DMA2D layer */
  if (LayerIdx == DMA2D_BACKGROUND_LAYER)
  {
    DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_BGPFCCR_REG, regMask, regValue);
    DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_BGOR_REG, pLayerCfg->InputOffset);

    /* DMA2D BGCOLR register configuration -------------------------------------*/
    if ((pLayerCfg->InputColorMode == DMA2D_INPUT_A8) || (pLayerCfg->InputColorMode == DMA2D_INPUT_A2) || \
        (pLayerCfg->InputColorMode == DMA2D_INPUT_A2) || (pLayerCfg->InputColorMode == DMA2D_INPUT_A1))
    {
      DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_BGCOLR_REG, pLayerCfg->InputAlpha & (DMA2D_BGCOLR_BLUE | \
                                                                                   DMA2D_BGCOLR_GREEN | \
                                                                                   DMA2D_BGCOLR_RED));
    }

  }
  /* Configure the foreground DMA2D layer */
  else
  {
    if (pLayerCfg->InputColorMode == DMA2D_INPUT_YCBCR)
    {
      regValue |= (pLayerCfg->ChromaSubSampling << DMA2D_FGPFCCR_CSS_Pos);
      regMask  |= DMA2D_FGPFCCR_CSS;
    }

    DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_FGPFCCR_REG, regMask, regValue);
    DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_FGOR_REG, pLayerCfg->InputOffset);

    /* DMA2D FGCOLR register configuration -------------------------------------*/
    if ((pLayerCfg->InputColorMode == DMA2D_INPUT_A8) || (pLayerCfg->InputColorMode == DMA2D_INPUT_A2) || \
        (pLayerCfg->InputColorMode == DMA2D_INPUT_A2) || (pLayerCfg->InputColorMode == DMA2D_INPUT_A1))
    {
      DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_FGCOLR_REG, pLayerCfg->InputAlpha & (DMA2D_FGCOLR_BLUE | \
                                                                                   DMA2D_FGCOLR_GREEN | \
                                                                                   DMA2D_FGCOLR_RED));
    }
  }

  return HAL_OK;
}

/**
  * @brief  Add Rotation Configuration LDM with the specified parameters.
  * @note This function sets up the register values for the rotation configuration along with
  *       the specific LDM instruction.
  *       These will be saved in the chosen command list via HAL_DMA2D_CL_InsertCommandList().
  *       When the Command List execution begins, the internal registers will be loaded according to the prepared
  *       register values and the corresponding instruction.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @param  Source      Specifies the source to configure for the rotation.
  *                     This parameter can be one value of @ref DMA2D_SOURCE
  * @param  Mirror_type Specifies the Mirror type to be configured
  *                     This parameter can be one value of @ref DMA2D_MirroringRotation
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_AddConfigRotationCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t Source,
                                                    uint32_t Mirroring_Type)
{
  /* Check the DMA2D channel handle parameter */
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DMA2D_ROT_SRC(Source));
  assert_param(IS_DMA2D_ROT_TYPE(Mirroring_Type));

  /* Set tile buffer control register */
  DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_TBCR_REG, Source | (Mirroring_Type << DMA2D_TBCR_XMEN_Pos));

  return HAL_OK;
}

/**
  * @brief  Add downscaling Configuration LDM for the specified source.
  * @note This function sets up the register values for the layer configuration along with the specific LDM instruction.
  *       These will be saved in the chosen command list via HAL_DMA2D_CL_InsertCommandList().
  *       When the Command List execution begins, the internal registers will be loaded according to the prepared
  *       register values and the corresponding instruction
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @param  Source      Specifies the source to configure for the downscaling.
  *                     This parameter can be one value of @ref DMA2D_SOURCE
  * @param  pDownscalingCfg Pointer to a DMA2D_DownscalingCfgTypeDef structure that contains
  *                         the downscaling parameters such as pixels per line, number of lines,
  *                         vertical and horizontal step sizes, and phase offsets.
  *  The downscaling configuration is not intended to be updated at runtime.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_AddConfigDownscalingCMD(DMA2D_CL_HandleTypeDef *const hdma2d, uint32_t Source,
                                                       DMA2D_DownscalingCfgTypeDef *pDownscalingCfg)
{
  /* HSET and VSTEP  Calculation */
  uint16_t hstep = (4096 / (pDownscalingCfg->HRatio) - 1);
  uint16_t vstep = (4096 / (pDownscalingCfg->VRatio) - 1);

  /* Check the DMA2D channel handle parameter */
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DMA2D_ALL_INSTANCE(hdma2d->Instance));
  assert_param(IS_DMA2D_SCALE_SRC(Source));
  assert_param(IS_DMA2D_SCALE_HSTEP(hstep));
  assert_param(IS_DMA2D_SCALE_VSTEP(vstep));
  assert_param(IS_DMA2D_SCALE_PIXEL_PER_LINE(pDownscalingCfg->PixelPerLines));
  assert_param(IS_DMA2D_SCALE_NUMBER_OF_LINES(pDownscalingCfg->NumberOfLines));
  assert_param(IS_DMA2D_SCALE_HPHASE(pDownscalingCfg->HPhase));
  assert_param(IS_DMA2D_SCALE_VPHASE(pDownscalingCfg->VPhase));

  /* Config scaling source */
  DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_SCR_REG, Source);

  /* Config scaling Height and Width */
  DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_SNLR_REG, (pDownscalingCfg->NumberOfLines |
                                                     (pDownscalingCfg->PixelPerLines << DMA2D_SNLR_PL_Pos)));

  /* Config scaling HSEP and VSTEP */
  DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_SSR_REG, (hstep | (vstep << DMA2D_SSR_VSTEP_Pos)));

  /* Config scaling HPHASE and VPHASE */
  DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_SPR_REG, (pDownscalingCfg->HPhase |
                                                    (pDownscalingCfg->VPhase << DMA2D_SPR_VPHASE_Pos)));

  return HAL_OK;

}
/**
  * @brief  Add Stencil Configuration LDM for the specified source.
  * @note This function sets up the register values for the layer configuration along with the specific LDM instruction.
  *       These will be saved in the chosen command list via HAL_DMA2D_CL_InsertCommandList().
  *       When the Command List execution begins, the internal registers will be loaded according to the prepared
  *       register values and the corresponding instruction
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @param  Source      Specifies the source to configure for the stenciling.
  *                     This parameter can be one value of @ref DMA2D_SOURCE
  * @param  pStencilCfg Pointer to a DMA2D_StencilCfgTypeDef structure that contains
  *                     the stencil configuration parameters such as vertical and horizontal trail and pre values.
  *  The Stencil configuration is not intended to be updated at runtime.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_AddConfigStencilCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t Source,
                                                   DMA2D_StencilCfgTypeDef *pStencilCfg)
{
  /* Check the DMA2D channel handle parameter */
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_DMA2D_STENCIL_SRC(Source));
  assert_param(IS_DMA2D_STENCIL_MODE(pStencilCfg->Mode));
  assert_param(IS_DMA2D_STENCIL_LO(pStencilCfg->LineOffset));
  assert_param(IS_DMA2D_STENCIL_HPRE(pStencilCfg->HPre));
  assert_param(IS_DMA2D_STENCIL_HTRAIL(pStencilCfg->HTrail));
  assert_param(IS_DMA2D_STENCIL_ALPHA_INVERTED(pStencilCfg->AlphaInverted));

  /* Configure SBCR: source and mode and Alpha Invert: SRC MODE AI */
  DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_SBCR_REG, DMA2D_SBCR_SRC | DMA2D_SBCR_MODE | DMA2D_SBCR_AI,
                          (Source | (pStencilCfg->Mode << DMA2D_SBCR_MODE_Pos) | \
                           (pStencilCfg->AlphaInverted << DMA2D_SBCR_AI_Pos)));

  /* Set stencil buffer address */
  DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_SBMAR_REG, DMA2D_SBMAR_MA, pStencilCfg->Address);

  /* Set stencil buffer offset */
  DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_SBOR_REG, DMA2D_SBOR_LO, pStencilCfg->LineOffset);

  /* Set stencil buffer memory skip: Horizontal pre/trail pixels */
  DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_SBMSR_REG, (DMA2D_SBMSR_HPRE | DMA2D_SBMSR_HTRAIL),
                          (pStencilCfg->HPre | (pStencilCfg->HTrail << DMA2D_SBMSR_HTRAIL_Pos)));

  return HAL_OK;
}

/**
  * @brief  Add a CLUT Loading operation LDM with the specified parameters in DMA2D_CLUTCfgTypeDef
  *         and copy the prepared LDM instructions and register values. to the chosen Command List address.
  * @note This function sets up the register values for this configuration along with the specific LDM instruction.
  *       These will be saved in the chosen command list via HAL_DMA2D_CL_InsertCommandList().
  *       When the Command List execution begins, the internal registers will be loaded according to the prepared
  *       register values and the corresponding instruction
  * @param  hdma2d   Pointer to a DMA2D_HandleTypeDef structure that contains
  *                   the configuration information for the DMA2D.
  * @param  CLUTCfg  Pointer to a DMA2D_CLUTCfgTypeDef structure that contains
  *                   the configuration information for the color look up table.
  * @param  LayerIdx DMA2D Layer index.
  *                   This parameter can be one of the following values:
  *                   DMA2D_BACKGROUND_LAYER(0) / DMA2D_FOREGROUND_LAYER(1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_AddCLUTStartLoadCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t LayerIdx,
                                                   const DMA2D_CLUTCfgTypeDef *CLUTCfg,
                                                   DMA2D_CL_CommandListTypeDef *pCommandList)
{
  uint8_t reg_index;

  /* Check the parameters */
  assert_param(IS_DMA2D_LAYER(LayerIdx));
  assert_param(IS_DMA2D_CLUT_CM(CLUTCfg->CLUTColorMode));
  assert_param(IS_DMA2D_CLUT_SIZE(CLUTCfg->Size));

  /* Change DMA2D peripheral state */
  hdma2d->State = HAL_DMA2D_CL_STATE_BUSY;

  /* Configure the CLUT of the background DMA2D layer */
  if (LayerIdx == DMA2D_BACKGROUND_LAYER)
  {
    /* Write background CLUT memory address */
    DMA2D_CL_LDM_WRITE_REG(hdma2d, hdma2d->Instance->BGCMAR, (uint32_t)CLUTCfg->pCLUT);

    /* Write background CLUT size and CLUT color mode */
    DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_BGPFCCR_REG, (DMA2D_BGPFCCR_CS | DMA2D_BGPFCCR_CM),
                            ((CLUTCfg->Size << DMA2D_BGPFCCR_CS_Pos) |
                             (CLUTCfg->CLUTColorMode << DMA2D_BGPFCCR_CM_Pos)));

    /* Enable the CLUT Transfer Complete, transfer Error, configuration Error and CLUT Access Error interrupts */
    __HAL_DMA2D_ENABLE_IT(hdma2d, DMA2D_IT_CTC | DMA2D_IT_TE | DMA2D_IT_CE | DMA2D_IT_CAE);

    /* Enable the CLUT loading for the background */
    DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_BGPFCCR_REG, DMA2D_BGPFCCR_START,  DMA2D_BGPFCCR_START);
  }
  /* Configure the CLUT of the foreground DMA2D layer */
  else
  {
    /* Write foreground CLUT memory address */
    DMA2D_CL_LDM_WRITE_REG(hdma2d, hdma2d->Instance->FGCMAR, (uint32_t)CLUTCfg->pCLUT);

    /* Write foreground CLUT size and CLUT color mode */
    DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_FGPFCCR_REG, (DMA2D_FGPFCCR_CS | DMA2D_FGPFCCR_CM),
                            ((CLUTCfg->Size << DMA2D_FGPFCCR_CS_Pos) |
                             (CLUTCfg->CLUTColorMode << DMA2D_FGPFCCR_CM_Pos)));

    /* Enable the CLUT Transfer Complete, transfer Error, configuration Error and CLUT Access Error interrupts */
    __HAL_DMA2D_ENABLE_IT(hdma2d, DMA2D_IT_CTC | DMA2D_IT_TE | DMA2D_IT_CE | DMA2D_IT_CAE);

    /* Enable the CLUT loading for the foreground */
    DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_FGPFCCR_REG, DMA2D_FGPFCCR_START, DMA2D_FGPFCCR_START);
  }

  if (pCommandList->Index != pCommandList->Size)
  {
    pCommandList->Address[pCommandList->Index++] = hdma2d->LDM_Instruction;
  }
  else
  {
    return HAL_ERROR;
  }

  for (reg_index = 0; reg_index < HAL_DMA2D_CL_LDM_REG_NUM; reg_index++)
  {
    if (hdma2d->LDM_Instruction & LDM_Decoder[reg_index])
    {
      if (pCommandList->Index != pCommandList->Size)
      {
        pCommandList->Address[pCommandList->Index++] = hdma2d->LDM_Reg_values[reg_index];
      }
      else
      {
        return HAL_ERROR;
      }
    }
  }

  hdma2d->LDM_Instruction = 0;

  return HAL_OK;
}

/**
  * @brief  Add a copy operation LDM from a source buffer to a destination address with the specified width and height
  *         and copy the prepared LDM instructions and register values. to the chosen Command List address.
  * @note This function sets up the register values for the layer configuration along with the specific LDM instruction.
  *       These will be saved in the chosen command list via HAL_DMA2D_CL_InsertCommandList().
  *       When the Command List execution begins, the internal registers will be loaded according to the prepared
  *       register values and the corresponding instruction
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @param  pdata        Source buffer address from which data will be copied.
  * @param  DstAddress   Destination address where data will be copied.
  * @param  Width        Width of the data area to copy, in pixels.
  * @param  Height       Height of the data area to copy, in lines.
  * @param  pCommandList Pointer to a DMA2D_CL_CommandListTypeDef structure that holds
  *                      the command list where the copy command will be appended.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_AddCopyCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress,
                                          uint32_t Width, uint32_t Height, DMA2D_CL_CommandListTypeDef *pCommandList)
{
  uint8_t reg_index;
  uint32_t rb_size;

  /* Check the DMA2D channel handle parameter */
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DMA2D_LINE(Height));
  assert_param(IS_DMA2D_PIXEL(Width));

  rb_size = ((hdma2d->Instance->CLCR & DMA2D_CLCR_RBS) >> DMA2D_CLCR_RBS_Pos);

  if (rb_size > hdma2d->RingBuffer.Size)
  {
    return HAL_ERROR;
  }

  /* Configure the source, destination address and the data size */
  DMA2D_CL_SetConfig(hdma2d, pdata, DstAddress, Width, Height);

  /* Enable the Peripheral */
  DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_CR_REG, DMA2D_CR_START, DMA2D_CR_START);

  if (pCommandList->Index != pCommandList->Size)
  {
    pCommandList->Address[pCommandList->Index++] = hdma2d->LDM_Instruction;
  }
  else
  {
    return HAL_ERROR;
  }

  for (reg_index = 0; reg_index < HAL_DMA2D_CL_LDM_REG_NUM; reg_index++)
  {
    if (hdma2d->LDM_Instruction & LDM_Decoder[reg_index])
    {
      if (pCommandList->Index != pCommandList->Size)
      {
        pCommandList->Address[pCommandList->Index++] = hdma2d->LDM_Reg_values[reg_index];
      }
      else
      {
        return HAL_ERROR;
      }
    }
  }

  hdma2d->LDM_Instruction = 0;

  return HAL_OK;
}

/**
  * @brief  Add a blending operation LDM between two source buffers to a destination address with specified width
  *         and height.
  * @note This function sets up the register values for the layer configuration along with the specific LDM instruction.
  *       These will be saved in the chosen command list via HAL_DMA2D_CL_InsertCommandList().
  *       When the Command List execution begins, the internal registers will be loaded according to the prepared
  *       register values and the corresponding instruction
  *       Copy the prepared LDM instructions and register values to the chosen Command List address.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @param  SrcAddress1  Source address of the first input buffer for blending.
  * @param  SrcAddress2  Source address of the second input buffer for blending.
  * @param  DstAddress   Destination address where the blended result will be stored.
  * @param  Width        Width of the data area to blend, in pixels.
  * @param  Height       Height of the data area to blend, in lines.
  * @param  pCommandList Pointer to a DMA2D_CL_CommandListTypeDef structure that holds
  *                      the command list where the blending command will be appended.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_AddBlendingCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t SrcAddress1,
                                              uint32_t SrcAddress2, uint32_t DstAddress, uint32_t Width,
                                              uint32_t Height, DMA2D_CL_CommandListTypeDef *pCommandList)
{
  uint8_t reg_index;

  /* Check the DMA2D channel handle parameter */
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DMA2D_LINE(Height));
  assert_param(IS_DMA2D_PIXEL(Width));


  if (hdma2d->Init.Mode == DMA2D_M2M_BLEND_FG)
  {
    /*blending & fixed FG*/
    DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_FGCOLR_REG, SrcAddress1);
    DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_FGPFCCR_REG, (DMA2D_FGPFCCR_ALPHA), (SrcAddress1 & 0xFF000000));

    /* Configure the source, destination address and the data size */
    DMA2D_CL_SetConfig(hdma2d, SrcAddress2, DstAddress, Width, Height);
  }
  else if (hdma2d->Init.Mode == DMA2D_M2M_BLEND_BG)
  {
    /*blending & fixed BG*/
    DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_BGCOLR_REG, SrcAddress2);
    DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_BGPFCCR_REG, (DMA2D_BGPFCCR_ALPHA), (SrcAddress2 & 0xFF000000));

    /* Configure the source, destination address and the data size */
    DMA2D_CL_SetConfig(hdma2d, SrcAddress1, DstAddress, Width, Height);
  }
  else
  {
    /* Configure DMA2D Stream source2 address */
    DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_BGMAR_REG, SrcAddress2);

    /* Configure the source, destination address and the data size */
    DMA2D_CL_SetConfig(hdma2d, SrcAddress1, DstAddress, Width, Height);
  }

  /* Enable the Start Transfer Bit */
  DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_CR_REG, (DMA2D_CR_START), DMA2D_CR_START);

  if (pCommandList->Index != pCommandList->Size)
  {
    pCommandList->Address[pCommandList->Index++] = hdma2d->LDM_Instruction;
  }
  else
  {
    return HAL_ERROR;
  }

  for (reg_index = 0; reg_index < HAL_DMA2D_CL_LDM_REG_NUM; reg_index++)
  {
    if (hdma2d->LDM_Instruction & LDM_Decoder[reg_index])
    {
      if (pCommandList->Index != pCommandList->Size)
      {
        pCommandList->Address[pCommandList->Index++] = hdma2d->LDM_Reg_values[reg_index];
      }
      else
      {
        return HAL_ERROR;
      }
    }
  }

  /* Invalidate and reset the LDM handle */
  hdma2d->LDM_Instruction = 0;

  return HAL_OK;
}
/**
  * @brief  Sets up the DMA2D Command List structure by specifying its buffer address and size.
  * @param  Address      Pointer to the memory region allocated for the command list.
  * @param  Size         The command List Size.
  * @param  pCommandList Pointer to the DMA2D_CL_CommandListTypeDef structure to be initialized.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_Init_CommandList(uint32_t *Address, uint32_t Size,
                                                DMA2D_CL_CommandListTypeDef *pCommandList)
{
  pCommandList->Address = Address;
  pCommandList->Size    = Size;
  pCommandList->Index   = 0;

  return HAL_OK;
}

/**
  * @brief  Insert a prepared Command List into the DMA2D ring buffer for execution.
  *         This function writes the command list descriptor into the ring buffer
  *         and configures pre/post-flag operations.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @param  pCommandList    Pointer to a DMA2D_CL_CommandListTypeDef structure containing
  *                         the command list to be inserted.
  * @param  gpflag          General purpose flag controlling command list behavior.
  * @param  post_flag_config Configuration flags to be applied after command list execution.
  *                          Must be a valid pre/post flag operation.
  * @param  pre_flag_config Configuration flags to be applied before command list execution.
  *                         Must be a valid pre/post flag operation.
  * @retval HAL status
  */
#define RBS_TO_RING_BUFFER_SIZE(val)  (1U << ((val) + 6))
HAL_StatusTypeDef HAL_DMA2D_CL_InsertCommandList(DMA2D_CL_HandleTypeDef *hdma2d,
                                                 DMA2D_CL_CommandListTypeDef *pCommandList,
                                                 uint32_t gpflag, uint32_t post_flag_config, uint32_t pre_flag_config)
{
  uint32_t write_ptr;
  uint64_t *descriptor;
  uint32_t *CLaddress = (uint32_t *)pCommandList->Address;

  uint32_t ring_buffer_size = RBS_TO_RING_BUFFER_SIZE(((hdma2d->Instance->CLCR & DMA2D_CLCR_RBS_Msk) >>
                                                        DMA2D_CLCR_RBS_Pos));


  assert_param(IS_DMA2D_CL_GPFLAG(gpflag));
  assert_param(IS_DMA2D_CL_PRE_POST_FLAG_OPERATION(post_flag_config));
  assert_param(IS_DMA2D_CL_PRE_POST_FLAG_OPERATION(pre_flag_config));
  assert_param(IS_DMA2D_CL_ADDRESS_VALID((uint32_t)pCommandList->Address));
  assert_param(IS_DMA2D_CL_SIZE(pCommandList->Size));

  if ((hdma2d == NULL) || (pCommandList == NULL))
  {
    return HAL_ERROR;
  }

  if (pCommandList->Address[pCommandList->Index] != 0xFFFFFFFF)
  {
    if (pCommandList->Address[pCommandList->Index] != pCommandList->Size)
    {
      pCommandList->Address[pCommandList->Index] = 0xFFFFFFFF;
      pCommandList->Index++;
    }

    else
    {
      return HAL_ERROR;
    }
  }

  write_ptr = hdma2d->Instance->RBWPR;

  uint32_t next_write_ptr = write_ptr + 8;
  if (next_write_ptr >= ring_buffer_size)
  {
    return HAL_ERROR;
  }

  /* descriptor in the first free slot */
  descriptor = (uint64_t *)(hdma2d->Instance->RBBAR + write_ptr);

  /* fill the descriptor */
  *descriptor = ((pCommandList->Index - 1) |
                 (post_flag_config << (24 + 2 * gpflag)) |
                 (pre_flag_config  << (16 + 2 * gpflag)));
  *descriptor <<= 32;
  *descriptor &= 0x00000FFF00000000;

  /* Store last index values to be used for next descriptor after writing @to ring buffer */
  *descriptor += (uint64_t)((uint32_t)CLaddress); /* the selected address passed as cmdlist */


  /* Increment the write pointer */
  hdma2d->Instance->RBWPR = next_write_ptr;

  return HAL_OK;
}
/**
  * @brief  Start the DMA2D Command List execution.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval HAL status
  * @note   The function starts CL execution with all relevant DMA2D interrupts.
  */
HAL_StatusTypeDef HAL_DMA2D_CL_Start(DMA2D_CL_HandleTypeDef *hdma2d)
{
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  if (hdma2d->State != HAL_DMA2D_CL_STATE_BUSY)
  {
    /* Change DMA2D peripheral Cl state */
    hdma2d->State = HAL_DMA2D_CL_STATE_BUSY;

    SET_BIT(hdma2d->Instance->CLCR, DMA2D_CLCR_START);
  }

  __HAL_DMA2D_ENABLE_IT(hdma2d, DMA2D_IT_CE | DMA2D_IT_TW | DMA2D_IT_TC | DMA2D_IT_TE | \
                        DMA2D_IT_CLE | DMA2D_IT_CLS | DMA2D_IT_RBE | DMA2D_IT_RBC);

  return HAL_OK;

}

/**
  * @brief  Start the DMA2D Command List execution with optional interrupt configuration.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @param  Interrupts Specifies the DMA2D interrupts to enable during command list execution.
  *                   This parameter can be a value or a combination of
  * @retval HAL status
  * @note   The function starts CL execution with the specified DMA2D interrupts.
  */
HAL_StatusTypeDef HAL_DMA2D_CL_StartOpt(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t Interrupts)
{
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  if (hdma2d->State != HAL_DMA2D_CL_STATE_BUSY)
  {
    /* Change DMA2D peripheral Cl state */
    hdma2d->State = HAL_DMA2D_CL_STATE_BUSY;

    SET_BIT(hdma2d->Instance->CLCR, DMA2D_CLCR_START);
  }

  __HAL_DMA2D_ENABLE_IT(hdma2d, Interrupts);

  return HAL_OK;
}

/**
  * @brief  Suspend the DMA2D Command List execution.
  *          The CL suspend operation is effective only after the current command finishes execution.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_Suspend(DMA2D_CL_HandleTypeDef *hdma2d)
{
  uint32_t tickstart;
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  SET_BIT(hdma2d->Instance->CLCR, DMA2D_CLCR_SUSP);

  /* Should wait until the suspend is effective ,
     the DMA2D continue executing the current linear Command List */
  /* The suspend is effective after the completion of the current command being executed */
  tickstart = HAL_GetTick();
  while ((hdma2d->Instance->CLSR & DMA2D_CLSR_SUSPS) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > DMA2D_TIMEOUT_SUSPEND)
    {
      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TIMEOUT;

      /* Change the DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_TIMEOUT;

      return HAL_TIMEOUT;
    }
  }

  hdma2d->State = HAL_DMA2D_CL_STATE_SUSPEND;

  return HAL_OK;
}

/**
  * @brief  Resume the DMA2D Command List execution
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_Resume(DMA2D_CL_HandleTypeDef *hdma2d)
{
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  CLEAR_BIT(hdma2d->Instance->CLCR, DMA2D_CLCR_SUSP);

  hdma2d->State = HAL_DMA2D_CL_STATE_BUSY;

  return HAL_OK;
}
/**
  * @brief  Abort the DMA2D Command List execution immediately.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_Abort(DMA2D_CL_HandleTypeDef *hdma2d)
{
  if (hdma2d == NULL)
  {
    return HAL_ERROR;
  }

  SET_BIT(hdma2d->Instance->CLCR, DMA2D_CLCR_ABORT);

  hdma2d->State = HAL_DMA2D_CL_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Handle DMA2D Command List interrupt request.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval None
  */
void HAL_DMA2D_CL_IRQHandler(DMA2D_CL_HandleTypeDef *hdma2d)
{
  uint32_t isrflags = READ_REG(hdma2d->Instance->ISR);
  uint32_t ierflags = READ_REG(hdma2d->Instance->IER);
  uint32_t clsrflags = READ_REG(hdma2d->Instance->CLSR);

  /* Transfer Error Interrupt management ***************************************/
  if ((isrflags & DMA2D_FLAG_TE) != 0U)
  {
    if ((ierflags & DMA2D_IT_TE) != 0U)
    {
      /* Disable the transfer Error interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_TE);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_TE;

      /* Clear the transfer error flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_TE);

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_ERROR;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->XferErrorCallback(hdma2d);
#else
      HAL_DMA2D_CL_XferErrorCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
    }
  }
  /* Configuration Error Interrupt management **********************************/
  if ((isrflags & DMA2D_FLAG_CE) != 0U)
  {
    if ((ierflags & DMA2D_IT_CE) != 0U)
    {
      /* Disable the Configuration Error interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_CE);

      /* Clear the Configuration error flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_CE);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_CE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_ERROR;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->XferErrorCallback(hdma2d);
#else
      HAL_DMA2D_CL_XferErrorCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
    }
  }
  /* CLUT access Error Interrupt management ***********************************/
  if ((isrflags & DMA2D_FLAG_CAE) != 0U)
  {
    if ((ierflags & DMA2D_IT_CAE) != 0U)
    {
      /* Disable the CLUT access error interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_CAE);

      /* Clear the CLUT access error flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_CAE);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_CAE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_ERROR;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->XferErrorCallback(hdma2d);
#else
      HAL_DMA2D_CL_XferErrorCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
    }
  }
  /* Transfer watermark Interrupt management **********************************/
  if ((isrflags & DMA2D_FLAG_TW) != 0U)
  {
    if ((ierflags & DMA2D_IT_TW) != 0U)
    {
      /* Disable the transfer watermark interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_TW);

      /* Clear the transfer watermark flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_TW);

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->LineEventCallback(hdma2d);
#else
      HAL_DMA2D_CL_LineEventCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

    }
  }
  /* Transfer Complete Interrupt management ************************************/
  if ((isrflags & DMA2D_FLAG_TC) != 0U)
  {
    if ((ierflags & DMA2D_IT_TC) != 0U)
    {
      /* Disable the transfer complete interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_TC);

      /* Clear the transfer complete flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_TC);

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer complete Callback */
      hdma2d->XferCpltCallback(hdma2d);
#else
      HAL_DMA2D_CL_TransferCpltCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

    }
  }

  /* CLUT Transfer Complete Interrupt management ******************************/
  if ((isrflags & DMA2D_FLAG_CTC) != 0U)
  {
    if ((ierflags & DMA2D_IT_CTC) != 0U)
    {
      /* Disable the CLUT transfer complete interrupt */
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_CTC);

      /* Clear the CLUT transfer complete flag */
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_CTC);

      /* CLUT Transfer complete Callback */
#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      hdma2d->CLUTLoadingCpltCallback(hdma2d);
#else
      HAL_DMA2D_CL_CLUTLoadingCpltCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
    }
  }

  /* Command List Error Interrupt management ******************************/
  if ((isrflags & DMA2D_FLAG_CLE) != 0U)
  {
    if ((ierflags & DMA2D_IT_CLE) != 0U)
    {
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_CLE);

      /* Check the error source */
      if ((clsrflags & DMA2D_CLSR_LCLMSE) != 0U)
      {
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_LCLMSE;
      }
      if ((clsrflags & DMA2D_CLSR_LCLIE) != 0U)
      {
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_LCLIE ;
      }
      if ((clsrflags & DMA2D_CLSR_LCLRE) != 0U)
      {
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_LCLRE;
      }

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_CLE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_ERROR;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->ErrorCallback(hdma2d);
#else
      HAL_DMA2D_CL_ErrorCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

    }
  }

  /* Command List Suspend Interrupt management ******************************/
  if ((isrflags & DMA2D_FLAG_CLS) != 0U)
  {
    if ((ierflags & DMA2D_IT_CLS) != 0U)
    {
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_CLS);
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_CLS);

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_SUSPEND;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->CL_SuspendCallback(hdma2d);
#else
      HAL_DMA2D_CL_SuspendCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

    }
  }

  /* Ring Buffer Error Interrupt management ******************************/
  if ((isrflags & DMA2D_FLAG_RBE) != 0U)
  {
    if ((ierflags & DMA2D_IT_RBE) != 0U)
    {
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_RBE);
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_RBE);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_RBE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_ERROR;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->ErrorCallback(hdma2d);
#else
      HAL_DMA2D_CL_ErrorCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
    }
  }

  /* Ring Buffer Complete Interrupt management ******************************/
  if ((isrflags & DMA2D_FLAG_RBC) != 0U)
  {
    if ((ierflags & DMA2D_IT_RBC) != 0U)
    {
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_RBC);
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_RBC);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_NONE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_READY;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->RBXferCpltCallback(hdma2d);
#else
      HAL_DMA2D_CL_RBXferCpltCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

    }
  }

  /* General Purpose Flag 0 Interrupt management ********************/
  if ((isrflags & DMA2D_FLAG_GPF0I) != 0U)
  {
    if ((ierflags & DMA2D_IT_GPF0) != 0U)
    {
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_GPF0);
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_GPF0I);
      __HAL_DMA2D_CL_CLEAR_GPFLAG(hdma2d, DMA2D_FLAG_GPF0);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_NONE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_READY;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->CL_GeneralPurposeEventCallback(hdma2d, DMA2D_GPFLAG0);
#else
      HAL_DMA2D_CL_GeneralPuposeEventCallback(hdma2d, DMA2D_GPFLAG0);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

    }
  }

  /* General Purpose Flag 1 Interrupt management ********************/
  if ((isrflags & DMA2D_FLAG_GPF1I) != 0U)
  {
    if ((ierflags & DMA2D_IT_GPF1) != 0U)
    {
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_GPF1);
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_GPF1I);
      __HAL_DMA2D_CL_CLEAR_GPFLAG(hdma2d, DMA2D_FLAG_GPF1);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_NONE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_READY;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->CL_GeneralPurposeEventCallback(hdma2d, DMA2D_GPFLAG1);
#else
      HAL_DMA2D_CL_GeneralPuposeEventCallback(hdma2d, DMA2D_GPFLAG1);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

    }
  }

  /* General Purpose Flag 2 Interrupt management ********************/
  if ((isrflags & DMA2D_FLAG_GPF2I) != 0U)
  {
    if ((ierflags & DMA2D_IT_GPF2) != 0U)
    {
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_GPF2);
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_GPF2I);
      __HAL_DMA2D_CL_CLEAR_GPFLAG(hdma2d, DMA2D_FLAG_GPF2);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_NONE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_READY;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->CL_GeneralPurposeEventCallback(hdma2d, DMA2D_GPFLAG2);
#else
      HAL_DMA2D_CL_GeneralPuposeEventCallback(hdma2d, DMA2D_GPFLAG2);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

    }
  }

  /* General Purpose Flag 3 Interrupt management ********************/
  if ((isrflags & DMA2D_FLAG_GPF3I) != 0U)
  {
    if ((ierflags & DMA2D_IT_GPF3) != 0U)
    {
      __HAL_DMA2D_DISABLE_IT(hdma2d, DMA2D_IT_GPF3);
      __HAL_DMA2D_CLEAR_FLAG(hdma2d, DMA2D_FLAG_GPF3I);
      __HAL_DMA2D_CL_CLEAR_GPFLAG(hdma2d, DMA2D_FLAG_GPF3);

      /* Update error code */
      hdma2d->ErrorCode |= HAL_DMA2D_ERROR_NONE;

      /* Change DMA2D state */
      hdma2d->State = HAL_DMA2D_CL_STATE_READY;

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
      /* Transfer error Callback */
      hdma2d->CL_GeneralPurposeEventCallback(hdma2d, DMA2D_GPFLAG3);
#else
      HAL_DMA2D_CL_GeneralPuposeEventCallback(hdma2d, DMA2D_GPFLAG3);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
    }
  }

}

/**
  * @brief Reset the Command List Index
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_ResetIndex(DMA2D_CL_CommandListTypeDef *pCommandList)
{
  pCommandList->Index = 0 ;

  return HAL_OK;
}

/**
  * @brief  Initializes the DMA2D MSP.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval None
  */
__weak void HAL_DMA2D_CL_MspInit(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CL_MspInit can be implemented in the user file.
   */
}

/**
  * @brief  DeInitializes the DMA2D MSP.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains
  *                 the configuration information for the DMA2D.
  * @retval None
  */
__weak void HAL_DMA2D_CL_MspDeInit(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CL_MspDeInit can be implemented in the user file.
   */
}

/**
  * @brief  Ring Buffer Transfer callback.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval None
  */
__weak void HAL_DMA2D_CL_RBXferCpltCallback(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CL_RBXferCpltCallback can be implemented in the user file.
   */
}
/**
  * @brief  Line Event callback.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval None
  */
__weak void HAL_DMA2D_CL_LineEventCallback(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CL_LineEventCallback can be implemented in the user file.
   */
}

/**
  * @brief  CLUT Transfer Complete callback.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval None
  */
__weak void HAL_DMA2D_CL_CLUTLoadingCpltCallback(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CL_CLUTLoadingCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  Suspend Event callback.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval None
  */
__weak void HAL_DMA2D_CL_SuspendCallback(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CL_SuspendCallback can be implemented in the user file.
   */
}

/**
  * @brief  Transfer Complete callback.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval None
  */
__weak void HAL_DMA2D_CL_TransferCpltCallback(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CL_TransferCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  Transfer error callback.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval None
  */
__weak void  HAL_DMA2D_CL_XferErrorCallback(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CL_XferErrorCallback can be implemented in the user file.
   */
}
/**
  * @brief  Error callback.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval None
  */
__weak void HAL_DMA2D_CL_ErrorCallback(DMA2D_CL_HandleTypeDef *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CL_ErrorCallback can be implemented in the user file.
   */
}
/**
  * @brief  General Purpose Flag Event callback.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval None
  */
__weak void HAL_DMA2D_CL_GeneralPuposeEventCallback(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t GeneralPurposeFlag)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hdma2d);
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_DMA2D_CL_GeneralPuposeEventCallback can be implemented in the user file.
   */
}

#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User DMA2D Command List (CL) Callback
  *         To be used instead of the weak (overridden) predefined callback.
  * @param  hdma2d     DMA2D Command List handle.
  * @param  CallbackID ID of the callback to be registered.
  *         This parameter can be one of the following values:
  *           @arg @ref HAL_DMA2D_CL_RBXFERCPLT_CB_ID         DMA2D Ring Buffer transfer complete Callback ID
  *           @arg @ref HAL_DMA2D_CL_SUSPEND_CB_ID            DMA2D Command List Suspend Callback ID
  *           @arg @ref HAL_DMA2D_CL_XFERERROR_CB_ID          DMA2D Transfer Error Callback ID
  *           @arg @ref HAL_DMA2D_CL_XFERCPLT_CB_ID           DMA2D Transfer Complete Callback ID
  *           @arg @ref HAL_DMA2D_CL_LINEEVENT_CB_ID          DMA2D Line Event Callback ID
  *           @arg @ref HAL_DMA2D_CL_CLUTLOADINGCPLT_CB_ID    DMA2D CLUT Loading Completion Callback ID
  *           @arg @ref HAL_DMA2D_CL_ERROR_CB_ID              DMA2D General Error Callback ID
  *           @arg @ref HAL_DMA2D_CL_MSPINIT_CB_ID            DMA2D MspInit Callback ID
  *           @arg @ref HAL_DMA2D_CL_MSPDEINIT_CB_ID          DMA2D MspDeInit Callback ID
  * @param  pCallback  Pointer to the callback function.
  * @retval status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_RegisterCallback(DMA2D_CL_HandleTypeDef *hdma2d,
                                                HAL_DMA2D_CL_CallbackIDTypeDef CallbackID,
                                                pDMA2D_CL_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }

  if (HAL_DMA2D_CL_STATE_READY == hdma2d->State)
  {
    switch (CallbackID)
    {
      case HAL_DMA2D_CL_RINGBUFFERCOMPLETE_CB_ID:
        hdma2d->RBXferCpltCallback = pCallback;
        break;

      case HAL_DMA2D_CL_SUSPEND_CB_ID:
        hdma2d->CL_SuspendCallback = pCallback;
        break;

      case HAL_DMA2D_CL_TRANSFERERROR_CB_ID:
        hdma2d->XferErrorCallback = pCallback;
        break;

      case HAL_DMA2D_CL_TRANSFERCOMPLETE_CB_ID:
        hdma2d->XferCpltCallback = pCallback;
        break;

      case HAL_DMA2D_CL_LINEEVENT_CB_ID:
        hdma2d->LineEventCallback = pCallback;
        break;

      case HAL_DMA2D_CL_CLUTLOADINGCPLT_CB_ID:
        hdma2d->CLUTLoadingCpltCallback = pCallback;
        break;

      case HAL_DMA2D_CL_ERROR_CB_ID:
        hdma2d->ErrorCallback = pCallback;
        break;

      case HAL_DMA2D_CL_MSPINIT_CB_ID:
        hdma2d->MspInitCallback = pCallback;
        break;

      case HAL_DMA2D_CL_MSPDEINIT_CB_ID:
        hdma2d->MspDeInitCallback = pCallback;
        break;

      default:
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
        status = HAL_ERROR;
        break;
    }
  }
  else if (HAL_DMA2D_CL_STATE_RESET == hdma2d->State)
  {
    switch (CallbackID)
    {
      case HAL_DMA2D_CL_MSPINIT_CB_ID:
        hdma2d->MspInitCallback = pCallback;
        break;

      case HAL_DMA2D_CL_MSPDEINIT_CB_ID:
        hdma2d->MspDeInitCallback = pCallback;
        break;

      default:
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
    status = HAL_ERROR;
  }

  return status;
}


/**
  * @brief  Unregister a User DMA2D Command List (CL) Callback
  *         Resets the callback pointer to the default weak function.
  * @param  hdma2d     DMA2D Command List handle.
  * @param  CallbackID ID of the callback to be unregistered.
  *         This parameter can be one of the following values:
  *           @arg @ref HAL_DMA2D_CL_RBXFERCPLT_CB_ID         DMA2D Ring Buffer transfer complete Callback ID
  *           @arg @ref HAL_DMA2D_CL_SUSPEND_CB_ID            DMA2D Command List Suspend Callback ID
  *           @arg @ref HAL_DMA2D_CL_XFERERROR_CB_ID          DMA2D Transfer Error Callback ID
  *           @arg @ref HAL_DMA2D_CL_XFERCPLT_CB_ID           DMA2D Transfer Complete Callback ID
  *           @arg @ref HAL_DMA2D_CL_LINEEVENT_CB_ID          DMA2D Line Event Callback ID
  *           @arg @ref HAL_DMA2D_CL_CLUTLOADINGCPLT_CB_ID    DMA2D CLUT Loading Completion Callback ID
  *           @arg @ref HAL_DMA2D_CL_ERROR_CB_ID              DMA2D General Error Callback ID
  *           @arg @ref HAL_DMA2D_CL_MSPINIT_CB_ID            DMA2D MspInit Callback ID
  *           @arg @ref HAL_DMA2D_CL_MSPDEINIT_CB_ID          DMA2D MspDeInit Callback ID
  * @retval status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_UnRegisterCallback(DMA2D_CL_HandleTypeDef *hdma2d,
                                                  HAL_DMA2D_CL_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (HAL_DMA2D_CL_STATE_READY == hdma2d->State)
  {
    switch (CallbackID)
    {
      case HAL_DMA2D_CL_RINGBUFFERCOMPLETE_CB_ID:
        hdma2d->RBXferCpltCallback = HAL_DMA2D_CL_RBXferCpltCallback;
        break;

      case HAL_DMA2D_CL_SUSPEND_CB_ID:
        hdma2d->CL_SuspendCallback = HAL_DMA2D_CL_SuspendCallback;
        break;

      case HAL_DMA2D_CL_TRANSFERERROR_CB_ID:
        hdma2d->XferErrorCallback = HAL_DMA2D_CL_XferErrorCallback;
        break;

      case HAL_DMA2D_CL_TRANSFERCOMPLETE_CB_ID:
        hdma2d->XferCpltCallback = HAL_DMA2D_CL_TransferCpltCallback;
        break;

      case HAL_DMA2D_CL_LINEEVENT_CB_ID:
        hdma2d->LineEventCallback = HAL_DMA2D_CL_LineEventCallback;
        break;

      case HAL_DMA2D_CL_CLUTLOADINGCPLT_CB_ID:
        hdma2d->CLUTLoadingCpltCallback = HAL_DMA2D_CL_CLUTLoadingCpltCallback;
        break;

      case HAL_DMA2D_CL_ERROR_CB_ID:
        hdma2d->ErrorCallback = HAL_DMA2D_CL_ErrorCallback;
        break;

      case HAL_DMA2D_CL_MSPINIT_CB_ID:
        hdma2d->MspInitCallback = HAL_DMA2D_CL_MspInit;
        break;

      case HAL_DMA2D_CL_MSPDEINIT_CB_ID:
        hdma2d->MspDeInitCallback = HAL_DMA2D_CL_MspDeInit;
        break;

      default:
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
        status = HAL_ERROR;
        break;
    }
  }
  else if (HAL_DMA2D_CL_STATE_RESET == hdma2d->State)
  {
    switch (CallbackID)
    {
      case HAL_DMA2D_CL_MSPINIT_CB_ID:
        hdma2d->MspInitCallback = HAL_DMA2D_CL_MspInit;
        break;

      case HAL_DMA2D_CL_MSPDEINIT_CB_ID:
        hdma2d->MspDeInitCallback = HAL_DMA2D_CL_MspDeInit;
        break;

      default:
        hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
    status = HAL_ERROR;
  }

  return status;
}


/**
  * @brief  Register a User DMA2D Command List (CL) General Purpose Event Callback
  *         To be used instead of the weak (overridden) predefined callback for general purpose events.
  * @param  hdma2d     DMA2D Command List handle.
  * @param  CallbackID ID of the callback to be registered.
  *         This parameter must be HAL_DMA2D_CL_GP_EVENT_CB_ID.
  * @param  pCallback  Pointer to the general purpose event callback function.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_Register_GeneralPurposeEvent_Callback(DMA2D_CL_HandleTypeDef *hdma2d,
                                                                     HAL_DMA2D_CL_CallbackIDTypeDef CallbackID,
                                                                     pDMA2D_CL_GeneralPurposeEventCallbackTypeDef
                                                                     pCallback)
{

  if (pCallback == NULL)
  {
    hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }

  if (HAL_DMA2D_CL_STATE_READY == hdma2d->State)
  {
    if (CallbackID == HAL_DMA2D_CL_GENERALPURPOSEFLAGEVENT_CB_ID)
    {
      hdma2d->CL_GeneralPurposeEventCallback = pCallback;
    }
  }
  else
  {
    hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Unregister the User DMA2D Command List (CL) General Purpose Event Callback
  *         Resets the callback pointer to the default weak function.
  * @param  hdma2d     DMA2D Command List handle.
  * @param  CallbackID ID of the callback to be unregistered.
  *         This parameter must be HAL_DMA2D_CL_GP_EVENT_CB_ID.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA2D_CL_UnRegister_GeneralPurposeEvent_Callback(DMA2D_CL_HandleTypeDef *hdma2d,
                                                                       HAL_DMA2D_CL_CallbackIDTypeDef CallbackID)
{

  if (HAL_DMA2D_CL_STATE_READY == hdma2d->State)
  {
    if (CallbackID == HAL_DMA2D_CL_GENERALPURPOSEFLAGEVENT_CB_ID)
    {
      hdma2d->CL_GeneralPurposeEventCallback = HAL_DMA2D_CL_GeneralPuposeEventCallback;
    }
  }
  else
  {
    hdma2d->ErrorCode |= HAL_DMA2D_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }

  return HAL_OK;
}
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

/** @defgroup DMA2D_Exported_Functions_Group4 Peripheral State and Error functions
  *  @brief    Peripheral State functions
  *
@verbatim
 ===============================================================================
                  ##### Peripheral State and Errors functions #####
 ===============================================================================
    [..]
    This subsection provides functions allowing to:
      (+) Get the DMA2D state
      (+) Get the DMA2D error code

@endverbatim
  * @{
  */
/**
  * @brief  Return the DMA2D state
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval HAL DMA2D state
  */
HAL_DMA2D_CL_StateTypeDef HAL_DMA2D_CL_GetState(const DMA2D_CL_HandleTypeDef *hdma2d)
{
  return hdma2d->State;
}

/**
  * @brief  Return the DMA2D error code
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @retval DMA2D Error Code
  */
uint32_t HAL_DMA2D_CL_GetError(const DMA2D_CL_HandleTypeDef *hdma2d)
{
  return hdma2d->ErrorCode;
}

/** @defgroup DMA2D_Private_Functions DMA2D Private Functions
  * @{
  */
/**
  * @brief  Set the DMA2D transfer parameters.
  * @param  hdma2d pointer to a DMA2D_CL_HandleTypeDef structure that contains the configuration information
  * @param  pdata      The source memory Buffer address
  * @param  DstAddress The destination memory Buffer address
  * @param  Width      The width of data to be transferred from source to destination.
  * @param  Height     The height of data to be transferred from source to destination.
  * @retval None
  */
static void DMA2D_CL_SetConfig(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress, uint32_t Width,
                               uint32_t Height)
{
  /* Configure DMA2D data size */
  /* Swap Width and Height when X/Y Swap is enabled */
  if ((hdma2d->Instance->TBCR & DMA2D_TBCR_XYSEN) == DMA2D_TBCR_XYSEN)
  {
    DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_NLR_REG,
                            (DMA2D_NLR_NL | DMA2D_NLR_PL), (Width | (Height << DMA2D_NLR_PL_Pos)));
  }
  else
  {
    DMA2D_CL_LDM_MODIFY_REG(hdma2d, DMA2D_CL_NLR_REG,
                            (DMA2D_NLR_NL | DMA2D_NLR_PL), (Height | (Width << DMA2D_NLR_PL_Pos)));
  }

  DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_OMAR_REG, DstAddress);
  /* Register to memory DMA2D mode selected */
  if (hdma2d->Init.Mode == DMA2D_R2M)
  {
    /* Write to DMA2D OCOLR register */
    DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_OCOLR_REG, pdata);
  }
  else if (hdma2d->Init.Mode == DMA2D_M2M_BLEND_FG) /*M2M_blending with fixed color FG DMA2D Mode selected*/
  {
    DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_BGMAR_REG, pdata);
  }
  else /* M2M, M2M_PFC,M2M_Blending or M2M_blending with fixed color BG DMA2D Mode */
  {
    DMA2D_CL_LDM_WRITE_REG(hdma2d, DMA2D_CL_FGMAR_REG, pdata);
  }
}
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 1 */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* DMA2D */
#endif /* HAL_DMA2D_MODULE_ENABLED */
