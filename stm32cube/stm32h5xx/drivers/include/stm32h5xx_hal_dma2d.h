/**
  ******************************************************************************
  * @file    stm32h5xx_hal_dma2d.h
  * @author  MCD Application Team
  * @brief   Header file of DMA2D HAL module.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H5xx_HAL_DMA2D_H
#define STM32H5xx_HAL_DMA2D_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal_def.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

#if defined (DMA2D)

/** @addtogroup DMA2D DMA2D
  * @brief DMA2D HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup DMA2D_Exported_Types DMA2D Exported Types
  * @{
  */
#define MAX_DMA2D_LAYER  2U  /*!< DMA2D maximum number of layers */
/**
  * @brief DMA2D Ring Buffer Structure definition
  */
typedef struct
{
  uint32_t  Size;         /*!< The Ring Buffer Size can be value from @ref DMA2D_RB_Size */
  uint32_t *Address;      /*!< The Ring Buffer Base Address */
} DMA2D_CL_RingBufferTypeDef;

/**
  * @brief DMA2D Command List Structure definition
  */
typedef struct
{
  uint32_t Size;           /*!< The Command List Size            */
  uint32_t *Address;       /*!< The Command List Base Address    */
  uint32_t Index;          /*!< The Current Command List Address */
} DMA2D_CL_CommandListTypeDef;
/**
  * @brief DMA2D Stencil Configuration Structure definition
  */
typedef struct
{
  uint32_t Mode;     /*!< The Stencil buffer mode                                      */
  uint32_t AlphaInverted;    /*!< The alpha value                                      */
  uint32_t Address;         /*!< The address of the stencil buffer                     */
  uint32_t LineOffset;      /*!< The stencil offset                                    */
  uint32_t HPre;            /*!< The number of skipped pixel at the beginning of a line */
  uint32_t HTrail;          /*!< The number of skipped pixel at the end of a line       */
} DMA2D_StencilCfgTypeDef;

/**
  * @brief DMA2D Downscaling Configuration Structure definition
  */
typedef struct
{
  uint32_t PixelPerLines;   /*!< The number of pixel per lines of the Scaler                       */
  uint32_t NumberOfLines;   /*!< The number of lines of the Scaler                                 */
  uint16_t VRatio;          /*!< The Vertical scaling Ratio                                        */
  uint16_t HRatio;          /*!< Horizontal scaling Ratio                                          */
  uint32_t VPhase;          /*!< Vertical Phase (This allows partial redrawing of scaled images)   */
  uint32_t HPhase;          /*!< Horizontal Phase (This allows partial redrawing of scaled images) */
} DMA2D_DownscalingCfgTypeDef;

/**
  * @brief DMA2D CLUT Structure definition
  */
typedef struct
{
  uint32_t *pCLUT;                  /*!< Configures the DMA2D CLUT memory address.*/

  uint32_t CLUTColorMode;           /*!< Configures the DMA2D CLUT color mode.
                                         This parameter can be one value of @ref DMA2D_Input_Color_Mode. */

  uint32_t Size;                    /*!< Configures the DMA2D CLUT size.
                                         This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.*/
} DMA2D_CLUTCfgTypeDef;

/**
  * @brief DMA2D Init structure definition
  */
typedef struct
{
  uint32_t             Mode;               /*!< Configures the DMA2D transfer mode.
                                                This parameter can be one value of @ref DMA2D_Mode. */

  uint32_t             ColorMode;          /*!< Configures the color format of the output image.
                                                This parameter can be one value of @ref DMA2D_Output_Color_Mode. */

  uint32_t             OutputOffset;       /*!< Specifies the Offset value.
                                                This parameter must be a number between
                                                Min_Data = 0x0000 and Max_Data = 0x3FFF. */
  uint32_t             AlphaInverted;     /*!< Select regular or inverted alpha value for the output pixel format converter.
                                               This parameter can be one value of @ref DMA2D_Alpha_Inverted. */

  uint32_t             RedBlueSwap;       /*!< Select regular mode (RGB or ARGB) or swap mode (BGR or ABGR)
                                               for the output pixel format converter.
                                               This parameter can be one value of @ref DMA2D_RB_Swap. */

  uint32_t             AlphaPosition;      /*!< Select Alpha position (ARGB or ABGR) or (RGBA or BGRA)
                                               for the output pixel format converter.
                                               This parameter can be one value of @ref DMA2D_Alpha_Position. */

  uint32_t             BytesSwap;         /*!< Select byte regular mode or bytes swap mode (two by two).
                                               This parameter can be one value of @ref DMA2D_Bytes_Swap. */

  uint32_t             LineOffsetMode;    /*!< Configures how is expressed the line offset for the foreground, background and output.
                                               This parameter can be one value of @ref DMA2D_Line_Offset_Mode. */

} DMA2D_InitTypeDef;


/**
  * @brief DMA2D Layer structure definition
  */
typedef struct
{
  uint32_t             InputOffset;       /*!< Configures the DMA2D foreground or background offset.
                                               This parameter must be a number between
                                               Min_Data = 0x0000 and Max_Data = 0x3FFF. */

  uint32_t             InputColorMode;    /*!< Configures the DMA2D foreground or background color mode.
                                               This parameter can be one value of @ref DMA2D_Input_Color_Mode. */

  uint32_t             AlphaMode;         /*!< Configures the DMA2D foreground or background alpha mode.
                                               This parameter can be one value of @ref DMA2D_Alpha_Mode. */

  uint32_t             InputAlpha;        /*!< Specifies the DMA2D foreground or background alpha value and color value
                                               in case of A8 or A4 color mode.
                                               This parameter must be a number between Min_Data = 0x00
                                               and Max_Data = 0xFF except for the color modes detailed below.
                                               @note In case of A8 or A4 color mode (ARGB),
                                               this parameter must be a number between
                                               Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF where
                                               - InputAlpha[24:31] is the alpha value ALPHA[0:7]
                                               - InputAlpha[16:23] is the red value RED[0:7]
                                               - InputAlpha[8:15] is the green value GREEN[0:7]
                                               - InputAlpha[0:7] is the blue value BLUE[0:7]. */
  uint32_t             AlphaPosition;     /*!< Select Alpha position (ARGB or ABGR) or (RGBA or BGRA)
                                               for the output pixel format converter.
                                               This parameter can be one value of @ref DMA2D_Alpha_Position. */
  uint32_t             AlphaInverted;     /*!< Select regular or inverted alpha value.
                                               This parameter can be one value of @ref DMA2D_Alpha_Inverted. */

  uint32_t             RedBlueSwap;       /*!< Select regular mode (RGB or ARGB) or swap mode (BGR or ABGR).
                                               This parameter can be one value of @ref DMA2D_RB_Swap. */

  uint32_t             ChromaSubSampling; /*!< Configure the chroma sub-sampling mode for the YCbCr color mode
                                               This parameter can be one value of @ref DMA2D_Chroma_Sub_Sampling */

} DMA2D_LayerCfgTypeDef;
#if (USE_DMA2D_COMMAND_LIST_MODE == 0)
/**
  * @brief  HAL DMA2D State structures definition
  */
typedef enum
{
  HAL_DMA2D_STATE_RESET             = 0x00U,    /*!< DMA2D not yet initialized or disabled       */
  HAL_DMA2D_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_DMA2D_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_DMA2D_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_DMA2D_STATE_ERROR             = 0x04U,    /*!< DMA2D state error                           */
  HAL_DMA2D_STATE_SUSPEND           = 0x05U     /*!< DMA2D process is suspended                  */
} HAL_DMA2D_StateTypeDef;

/**
  * @brief  DMA2D handle Structure definition
  */
typedef struct __DMA2D_HandleTypeDef
{
  DMA2D_TypeDef               *Instance;                                  /*!< DMA2D register base address.           */

  DMA2D_InitTypeDef           Init;                                       /*!< DMA2D communication parameters.        */

  void (* XferCpltCallback)(struct __DMA2D_HandleTypeDef *hdma2d);        /*!< DMA2D transfer complete callback.      */

  void (* XferErrorCallback)(struct __DMA2D_HandleTypeDef *hdma2d);       /*!< DMA2D transfer error callback.         */

#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
  void (* LineEventCallback)(struct __DMA2D_HandleTypeDef *hdma2d);       /*!< DMA2D line event callback.             */

  void (* CLUTLoadingCpltCallback)(struct __DMA2D_HandleTypeDef *hdma2d); /*!< DMA2D CLUT loading completion callback */

  void (* MspInitCallback)(struct __DMA2D_HandleTypeDef *hdma2d);         /*!< DMA2D Msp Init callback.               */

  void (* MspDeInitCallback)(struct __DMA2D_HandleTypeDef *hdma2d);       /*!< DMA2D Msp DeInit callback.             */

#endif /* (USE_HAL_DMA2D_REGISTER_CALLBACKS) */

  DMA2D_LayerCfgTypeDef       LayerCfg[MAX_DMA2D_LAYER];                  /*!< DMA2D Layers parameters                */

  HAL_LockTypeDef             Lock;                                       /*!< DMA2D lock.                            */

  __IO HAL_DMA2D_StateTypeDef State;                                      /*!< DMA2D transfer state.                  */

  __IO uint32_t               ErrorCode;                                  /*!< DMA2D error code.                      */
} DMA2D_HandleTypeDef;
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 0 */
#if (USE_DMA2D_COMMAND_LIST_MODE == 1)
/**
  * @brief  HAL DMA2D Command List State structures definition
  */
typedef enum
{
  HAL_DMA2D_CL_STATE_RESET             = 0x00U,    /*!< DMA2D not yet initialized or disabled       */
  HAL_DMA2D_CL_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_DMA2D_CL_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_DMA2D_CL_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_DMA2D_CL_STATE_ERROR             = 0x04U,    /*!< DMA2D state error                           */
  HAL_DMA2D_CL_STATE_SUSPEND           = 0x05U     /*!< DMA2D CL process is suspended                  */
} HAL_DMA2D_CL_StateTypeDef;

/**
  * @brief  DMA2D Command List handle Structure definition
  */
typedef struct __DMA2D_CL_HandleTypeDef
{
  DMA2D_TypeDef                  *Instance;                               /*!< DMA2D register base address.        */

  DMA2D_InitTypeDef              Init;                                    /*!< DMA2D communication parameters.     */

  DMA2D_CL_RingBufferTypeDef     RingBuffer;                              /*!< DMA2D Ring Buffer parameters.       */

  uint32_t                       LDM_Instruction;                         /*!< DMA2D CL LDM Instruction            */

  uint32_t                       LDM_Reg_values[29];                      /*!< DMA2D CL LDM Register Values        */

#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)

  void (* RBXferCpltCallback)(struct __DMA2D_CL_HandleTypeDef *hdma2d);   /*!< DMA2D Ring Buffer transfer complete
                                                                               callback. */

  void (* CL_SuspendCallback)(struct __DMA2D_CL_HandleTypeDef *hdma2d);   /*!< DMA2D Command List Suspend callback.   */

  void (* CL_GeneralPurposeEventCallback)(struct __DMA2D_CL_HandleTypeDef *hdma2d, uint32_t gen_pur_flag); /*!< DMA2D
                                                                               General Purpose Flag Event callback.   */

  void (* XferErrorCallback)(struct __DMA2D_CL_HandleTypeDef *hdma2d);       /*!< DMA2D transfer error callback.      */

  void (* XferCpltCallback)(struct __DMA2D_CL_HandleTypeDef *hdma2d);        /*!< DMA2D transfer complete callback.   */

  void (* LineEventCallback)(struct __DMA2D_CL_HandleTypeDef *hdma2d);       /*!< DMA2D line event callback.          */

  void (* CLUTLoadingCpltCallback)(struct __DMA2D_CL_HandleTypeDef *hdma2d); /*!< DMA2D CLUT loading completion
                                                                                  callback */
  void (* ErrorCallback)(struct __DMA2D_CL_HandleTypeDef *hdma2d);           /*!< DMA2D Error callback.               */
  void (* MspInitCallback)(struct __DMA2D_CL_HandleTypeDef *hdma2d);         /*!< DMA2D Msp Init callback.            */

  void (* MspDeInitCallback)(struct __DMA2D_CL_HandleTypeDef *hdma2d);       /*!< DMA2D Msp DeInit callback.          */

#endif /* (USE_HAL_DMA2D_REGISTER_CALLBACKS) */

  __IO HAL_DMA2D_CL_StateTypeDef State;                                   /*!< DMA2D CL transfer state.            */

  __IO uint32_t                  ErrorCode;                                  /*!< DMA2D CL error code.                */

} DMA2D_CL_HandleTypeDef;
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 1 */
#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL DMA2D Callback pointer definition
  */
#if (USE_DMA2D_COMMAND_LIST_MODE == 0)
typedef void (*pDMA2D_CallbackTypeDef)(DMA2D_HandleTypeDef *hdma2d); /*!< Pointer to a DMA2D common callback function */
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 0 */
#if (USE_DMA2D_COMMAND_LIST_MODE == 1)
typedef void (*pDMA2D_CL_CallbackTypeDef)(DMA2D_CL_HandleTypeDef *hdma2d); /*!< Pointer to a DMA2D_CL common callback function */
typedef void (*pDMA2D_CL_GeneralPurposeEventCallbackTypeDef)(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t gen_pur_flag); /*!< Pointer to a DMA2D_CL GEN_PURP_flags common callback function */
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 1 */
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DMA2D_Exported_Constants DMA2D Exported Constants
  * @{
  */

/** @defgroup DMA2D_Error_Code DMA2D Error Code
  * @{
  */
#define HAL_DMA2D_ERROR_NONE        0x00000000U  /*!< No error             */
#define HAL_DMA2D_ERROR_TE          0x00000001U  /*!< Transfer error       */
#define HAL_DMA2D_ERROR_CE          0x00000002U  /*!< Configuration error  */
#define HAL_DMA2D_ERROR_CAE         0x00000004U  /*!< CLUT access error    */
#define HAL_DMA2D_ERROR_TIMEOUT     0x00000020U  /*!< Timeout error        */
#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
#define HAL_DMA2D_ERROR_INVALID_CALLBACK 0x00000040U  /*!< Invalid callback error  */
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
#define HAL_DMA2D_ERROR_CLE         0x00000080U  /*!<* Command List Error  */
#define HAL_DMA2D_ERROR_RBE         0x00000100U  /*!<* Ring Buffer Error   */
#define HAL_DMA2D_ERROR_LCLMSE      0x00000200U  /*!<* Linear command list multiple start error */
#define HAL_DMA2D_ERROR_LCLIE       0x00000400U  /*!<* Linear command list instruction error    */
#define HAL_DMA2D_ERROR_LCLRE       0x00000800U  /*!<* Linear command list read error           */

/**
  * @}
  */

/** @defgroup DMA2D_Mode DMA2D Mode
  * @{
  */
#define DMA2D_M2M                   0x00000000U                         /*!< DMA2D memory to memory transfer mode */
#define DMA2D_M2M_PFC               DMA2D_CR_MODE_0                     /*!< DMA2D memory to memory with pixel format conversion transfer mode */
#define DMA2D_M2M_BLEND             DMA2D_CR_MODE_1                     /*!< DMA2D memory to memory with blending transfer mode */
#define DMA2D_R2M                   (DMA2D_CR_MODE_1 | DMA2D_CR_MODE_0) /*!< DMA2D register to memory transfer mode */
#define DMA2D_M2M_BLEND_FG          DMA2D_CR_MODE_2                     /*!< DMA2D memory to memory with blending transfer mode and fixed color FG */
#define DMA2D_M2M_BLEND_BG          (DMA2D_CR_MODE_2 | DMA2D_CR_MODE_0) /*!< DMA2D memory to memory with blending transfer mode and fixed color BG */
/**
  * @}
  */

/** @defgroup DMA2D_Output_Color_Mode DMA2D Output Color Mode
  * @{
  */
#define DMA2D_OUTPUT_ARGB8888       0x00000000U                           /*!< ARGB8888 DMA2D color mode */
#define DMA2D_OUTPUT_RGB888         DMA2D_OPFCCR_CM_0                     /*!< RGB888 DMA2D color mode   */
#define DMA2D_OUTPUT_RGB565         DMA2D_OPFCCR_CM_1                     /*!< RGB565 DMA2D color mode   */
#define DMA2D_OUTPUT_ARGB1555       (DMA2D_OPFCCR_CM_0|DMA2D_OPFCCR_CM_1) /*!< ARGB1555 DMA2D color mode */
#define DMA2D_OUTPUT_ARGB4444       DMA2D_OPFCCR_CM_2                     /*!< ARGB4444 DMA2D color mode */
#define DMA2D_OUTPUT_ARGB2222       (DMA2D_OPFCCR_CM_1 | DMA2D_OPFCCR_CM_2 | DMA2D_OPFCCR_CM_3)
                                                                          /*!< ARGB2222 DMA2D color mode */
/**
  * @}
  */

/** @defgroup DMA2D_Input_Color_Mode DMA2D Input Color Mode
  * @{
  */
#define DMA2D_INPUT_ARGB8888        0x00000000U  /*!< ARGB8888 color mode */
#define DMA2D_INPUT_RGB888          0x00000001U  /*!< RGB888 color mode   */
#define DMA2D_INPUT_RGB565          0x00000002U  /*!< RGB565 color mode   */
#define DMA2D_INPUT_ARGB1555        0x00000003U  /*!< ARGB1555 color mode */
#define DMA2D_INPUT_ARGB4444        0x00000004U  /*!< ARGB4444 color mode */
#define DMA2D_INPUT_L8              0x00000005U  /*!< L8 color mode       */
#define DMA2D_INPUT_AL44            0x00000006U  /*!< AL44 color mode     */
#define DMA2D_INPUT_AL88            0x00000007U  /*!< AL88 color mode     */
#define DMA2D_INPUT_L4              0x00000008U  /*!< L4 color mode       */
#define DMA2D_INPUT_A8              0x00000009U  /*!< A8 color mode       */
#define DMA2D_INPUT_A4              0x0000000AU  /*!< A4 color mode       */
#define DMA2D_INPUT_YCBCR           0x0000000BU  /*!< YCbCr color mode */
#define DMA2D_INPUT_A2              0x0000000CU  /*!< A2 color mode       */
#define DMA2D_INPUT_A1              0x0000000DU  /*!< A1 color mode       */
#define DMA2D_INPUT_ARGB2222        0x0000000EU  /*!< ARGB2222 color mode */
/**
  * @}
  */

/** @defgroup DMA2D_Input_Color_Mode DMA2D Input Color Mode
  * @{
  */
#define DMA2D_CCM_ARGB8888        0x00000000U  /*!< ARGB8888 CLUT color mode */
#define DMA2D_CCM_RGB888          0x00000001U  /*!< RGB888 CLUT color mode   */
#define DMA2D_CCM_RGB565          0x00000002U  /*!< RGB565 CLUT color mode   */
#define DMA2D_CCM_ARGB1555        0x00000003U  /*!< ARGB1555 CLUT color mode */
#define DMA2D_CCM_ARGB4444        0x00000004U  /*!< ARGB4444 CLUT color mode */
#define DMA2D_CCM_ARGB2222        0x0000000EU  /*!< ARGB2222 CLUT color mode */
/**
  * @}
  */

/** @defgroup DMA2D_Alpha_Mode DMA2D Alpha Mode
  * @{
  */
#define DMA2D_NO_MODIF_ALPHA        0x00000000U  /*!< No modification of the alpha channel value                     */
#define DMA2D_REPLACE_ALPHA         0x00000001U  /*!< Replace original alpha channel value by programmed alpha value */
#define DMA2D_COMBINE_ALPHA         0x00000002U  /*!< Replace original alpha channel value by programmed alpha value
                                                      with original alpha channel value                              */
/**
  * @}
  */

/** @defgroup DMA2D_Alpha_Position DMA2D Alpha Position
  * @{
  */
#define DMA2D_REGULAR_ALPHA_POS            0x00000000U  /*!< Select regular mode (ARGB or ABGR) */
#define DMA2D_SWAP_ALPHA_POS               0x00000001U  /*!< Select swap mode (RGBA or BGRA) */
/**
  * @}
  */

/** @defgroup DMA2D_Alpha_Inverted DMA2D Alpha Inversion
  * @{
  */
#define DMA2D_REGULAR_ALPHA         0x00000000U  /*!< No modification of the alpha channel value */
#define DMA2D_INVERTED_ALPHA        0x00000001U  /*!< Invert the alpha channel value */
/**
  * @}
  */

/** @defgroup DMA2D_RB_Swap DMA2D Red and Blue Swap
  * @{
  */
#define DMA2D_RB_REGULAR            0x00000000U  /*!< Select regular mode (RGB or ARGB) */
#define DMA2D_RB_SWAP               0x00000001U  /*!< Select swap mode (BGR or ABGR) */
/**
  * @}
  */



/** @defgroup DMA2D_Line_Offset_Mode DMA2D Line Offset Mode
  * @{
  */
#define DMA2D_LOM_PIXELS            0x00000000U   /*!< Line offsets expressed in pixels */
#define DMA2D_LOM_BYTES             DMA2D_CR_LOM  /*!< Line offsets expressed in bytes */
/**
  * @}
  */

/** @defgroup DMA2D_Bytes_Swap DMA2D Bytes Swap
  * @{
  */
#define DMA2D_BYTES_REGULAR         0x00000000U      /*!< Bytes in regular order in output FIFO */
#define DMA2D_BYTES_SWAP            DMA2D_OPFCCR_SB  /*!< Bytes are swapped two by two in output FIFO */
/**
  * @}
  */

/** @defgroup DMA2D_Chroma_Sub_Sampling DMA2D Chroma Sub Sampling
  * @{
  */
#define DMA2D_NO_CSS               0x00000000U  /*!< No chroma sub-sampling 4:4:4 */
#define DMA2D_CSS_422              0x00000001U  /*!< chroma sub-sampling 4:2:2 */
#define DMA2D_CSS_420              0x00000002U  /*!< chroma sub-sampling 4:2:0 */
/**
  * @}
  */

/** @defgroup DMA2D_SOURCE DMA2D Source
  * @{
  */
#define DMA2D_SOURCE_NONE                   0x00000000U  /*!< No Source (Disabled)    */
#define DMA2D_SOURCE_FOREGROUND             0x00000001U  /*!< Foreground plane Source */
#define DMA2D_SOURCE_BACKGROUND             0x00000002U  /*!< Background plane        */
#define DMA2D_SOURCE_BLENDER_OUTPUT         0x00000003U  /*!< Blender output          */
/**
  * @}
  */
/** @defgroup DMA2D_COLOR_MODE DMA2D Color Mode
  * @{
  */
#define DMA2D_STENCIL_MODE_A1         0x00000000U  /*!<  */
#define DMA2D_STENCIL_MODE_A2         0x00000001U  /*!< */
#define DMA2D_STENCIL_MODE_A4         0x00000002U  /*!< */
#define DMA2D_STENCIL_MODE_A8         0x00000003U  /*!< */
/**
  * @}
  */
/** @defgroup DMA2D_MirroringRotation DMA2D Mirroring Rotation
  * @{
  */
#define DMA2D_NO_ROTATION      0    /*!< No X, Y Swap , no mirroring                 */
#define DMA2D_NO_ROTATION_FLIP 0x01 /*!< Horizontal mirroring (X-axis flip)          */
#define DMA2D_ROTATE_90        0x05 /*!< 90 degree rotation                          */
#define DMA2D_ROTATE_90_FLIP   0x04 /*!< -90 degree rotation with vertical mirroring */
#define DMA2D_ROTATE_180       0x03 /*!< Both X and Y mirrored (Rotation 180)        */
#define DMA2D_ROTATE_180_FLIP  0x02 /*!< Vertical mirroring (Y-axis flip)            */
#define DMA2D_ROTATE_270       0x06 /*!< -90 degree rotation (X/Y swapped)           */
#define DMA2D_ROTATE_270_FLIP  0x07 /*!< 90 degree rotation with full mirroring      */
/**
  * @}
  */
/** @defgroup DMA2D_RB_Size DMA2D Ring Buffer Size
  * @{
  */
#define DMA2D_RB_SIZE_64B    0x0  /*!< Ring buffer size 64 bytes (2^(0+6))   */
#define DMA2D_RB_SIZE_128B   0x1  /*!< Ring buffer size 128 bytes (2^(1+6))  */
#define DMA2D_RB_SIZE_256B   0x2  /*!< Ring buffer size 256 bytes (2^(2+6))  */
#define DMA2D_RB_SIZE_512B   0x3  /*!< Ring buffer size 512 bytes (2^(3+6))  */
#define DMA2D_RB_SIZE_1KB    0x4  /*!< Ring buffer size 1024 bytes (2^(4+6)) */
#define DMA2D_RB_SIZE_2KB    0x5  /*!< Ring buffer size 2048 bytes (2^(5+6)) */
#define DMA2D_RB_SIZE_4KB    0x6  /*!< Ring buffer size 4096 bytes (2^(6+6)) */
#define DMA2D_RB_SIZE_8KB    0x7  /*!< Ring buffer size 8192 bytes (2^(7+6)) */

/**
  * @}
  */

/** @defgroup DMA2D_GENERAL_PURPOSE_FLAGS DMA2D General Purpose Flags
  * @{
  */
#define DMA2D_GPFLAG0     0  /*!< General Purpose Flag 0 */
#define DMA2D_GPFLAG1     1  /*!< General Purpose Flag 1 */
#define DMA2D_GPFLAG2     2  /*!< General Purpose Flag 2 */
#define DMA2D_GPFLAG3     3  /*!< General Purpose Flag 3 */
/**
  * @}
  */

/** @defgroup DMA2D_GENERAL_PURPOSE_FLAG_OPERATION DMA2D General Purpose Flag Operation
  * @{
  */
#define DMA2D_GPFLAG_NOP     0  /*!< No Operation to be done on General Purpose Flag  */
#define DMA2D_GPFLAG_SET     1  /*!< Set Operation to be done on General Purpose Flag */
#define DMA2D_GPFLAG_RESET   2  /*!< Reset operation to be done on General Purpose Flag  */
#define DMA2D_GPFLAG_TOGGLE  4  /*!< Toggle operation to be done on General Purpose Flag */
/**
  * @}
  */

/** @defgroup DMA2D_GENERAL_PURPOSE_INTERRUPT_MODE DMA2D General Purpose Interrupt Mode
  * @{
  */
#define DMA2D_GPFLAG_NONE            0  /*!< General purpose flag interrupt is never set */
#define DMA2D_GPFLAG_RISING          1  /*!< General purpose flag interrupt is set on a rising edge of the GPF */
#define DMA2D_GPFLAG_FALLING         2  /*!< General purpose flag interrupt is set on a falling edge of the GPF */
#define DMA2D_GPFLAG_RISING_FALLING  3  /*!< General purpose flag interrupt is set on a rising or a falling edge
                                             of the GPF */
/**
  * @}
  */
/** @defgroup DMA2D_Interrupts DMA2D Interrupts
  * @{
  */
#define DMA2D_IT_CE                 DMA2D_IER_CEIE            /*!< Configuration Error Interrupt */
#define DMA2D_IT_CTC                DMA2D_IER_CTCIE           /*!< CLUT Transfer Complete Interrupt */
#define DMA2D_IT_CAE                DMA2D_IER_CAEIE           /*!< CLUT Access Error Interrupt */
#define DMA2D_IT_TW                 DMA2D_IER_TWIE            /*!< Transfer Watermark Interrupt */
#define DMA2D_IT_TC                 DMA2D_IER_TCIE            /*!< Transfer Complete Interrupt */
#define DMA2D_IT_TE                 DMA2D_IER_TEIE            /*!< Transfer Error Interrupt */
#define DMA2D_IT_GPF3               DMA2D_IER_GPF3IE           /*!< General Purpose Flag 3 Interrupt */
#define DMA2D_IT_GPF2               DMA2D_IER_GPF2IE           /*!< General Purpose Flag 2 Interrupt */
#define DMA2D_IT_GPF1               DMA2D_IER_GPF1IE           /*!< General Purpose Flag 1 Interrupt */
#define DMA2D_IT_GPF0               DMA2D_IER_GPF0IE           /*!< General Purpose Flag 0 Interrupt */
#define DMA2D_IT_CLE                DMA2D_IER_CLEIE           /*!< Command List Error Interrupt */
#define DMA2D_IT_CLS                DMA2D_IER_CLSIE           /*!< Command List Suspended Interrupt */
#define DMA2D_IT_RBE                DMA2D_IER_RBEIE           /*!< Ring Buffer Error Interrupt */
#define DMA2D_IT_RBC                DMA2D_IER_RBCIE           /*!< Ring Buffer Completed Interrupt */
#define DMA2D_IT_ALL              (DMA2D_IT_CE  | DMA2D_IT_CTC | DMA2D_IT_CAE| DMA2D_IT_TW|  DMA2D_IT_TC|\
                                   DMA2D_IT_TE |DMA2D_IT_GPF3 | DMA2D_IT_GPF2 | DMA2D_IT_GPF1| DMA2D_IT_GPF0|\
                                   DMA2D_IT_CLE |DMA2D_IT_CLS | DMA2D_IT_RBE | DMA2D_IT_RBC) /*!< All Interrupt */
#define DMA2D_IT_NONE               0x0U                     /*!< DMA2D Interrupt None             */
/**
  * @}
  */

/** @defgroup DMA2D_Flags DMA2D Flags
  * @{
  */
#define DMA2D_FLAG_CE               DMA2D_ISR_CEIF           /*!< Configuration Error Interrupt Flag */
#define DMA2D_FLAG_CTC              DMA2D_ISR_CTCIF          /*!< CLUT Transfer Complete Interrupt Flag */
#define DMA2D_FLAG_CAE              DMA2D_ISR_CAEIF          /*!< CLUT Access Error Interrupt Flag */
#define DMA2D_FLAG_TW               DMA2D_ISR_TWIF           /*!< Transfer Watermark Interrupt Flag */
#define DMA2D_FLAG_TC               DMA2D_ISR_TCIF           /*!< Transfer Complete Interrupt Flag */
#define DMA2D_FLAG_TE               DMA2D_ISR_TEIF           /*!< Transfer Error Interrupt Flag */
#define DMA2D_FLAG_GPF3I            DMA2D_ISR_GPF3IF         /*!< General Purpose Flag 3 Interrupt Flag */
#define DMA2D_FLAG_GPF2I            DMA2D_ISR_GPF2IF         /*!< General Purpose Flag 2 Interrupt Flag */
#define DMA2D_FLAG_GPF1I            DMA2D_ISR_GPF1IF         /*!< General Purpose Flag 1 Interrupt Flag */
#define DMA2D_FLAG_GPF0I            DMA2D_ISR_GPF0IF         /*!< General Purpose Flag 0 Interrupt Flag */
#define DMA2D_FLAG_CLE              DMA2D_ISR_CLEIF          /*!< Command List Error Interrupt Flag */
#define DMA2D_FLAG_CLS              DMA2D_ISR_CLSIF          /*!< Command List suspended Interrupt Flag */
#define DMA2D_FLAG_RBE              DMA2D_ISR_RBEIF          /*!< Ring Buffer Error Interrupt Flag */
#define DMA2D_FLAG_RBC              DMA2D_ISR_RBCIF          /*!< Ring Buffer Completed Interrupt Flag */
#define DMA2D_FLAG_LCLMSE           DMA2D_CLSR_LCLMSE        /*!< Linear command list multi start error Interrupt Flag */
#define DMA2D_FLAG_LCLIE            DMA2D_CLSR_LCLIE         /*!< Linear command list instruction error Interrupt Flag */
#define DMA2D_FLAG_LCLRE            DMA2D_CLSR_LCLRE         /*!< Linear command list read error Interrupt Flag*/
#define DMA2D_FLAG_GPF3S            DMA2D_CLSR_GPF3S         /*!< The command list is suspended by GPFLAG 3 Interrupt Flag */
#define DMA2D_FLAG_GPF2S            DMA2D_CLSR_GPF2S         /*!< The command list is suspended by GPFLAG 2 Interrupt Flag */
#define DMA2D_FLAG_GPF1S            DMA2D_CLSR_GPF1S         /*!< The command list is suspended by GPFLAG 1 Interrupt Flag */
#define DMA2D_FLAG_GPF0S            DMA2D_CLSR_GPF0S         /*!< The command list is suspended by GPFLAG 0 Interrupt Flag */
#define DMA2D_FLAG_SUSPS            DMA2D_CLSR_SUSPS         /*!< The command list is suspended by the SUSP bit Interrupt Flag */
#define DMA2D_FLAG_GPF3             DMA2D_GPFR_GPF3          /*!< General Purpose Flag 3 Flag */
#define DMA2D_FLAG_GPF2             DMA2D_GPFR_GPF2          /*!< General Purpose Flag 2 Flag */
#define DMA2D_FLAG_GPF1             DMA2D_GPFR_GPF1          /*!< General Purpose Flag 1 Flag */
#define DMA2D_FLAG_GPF0             DMA2D_GPFR_GPF0          /*!< General Purpose Flag 0 Flag */
/**
  * @}
  */

#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL DMA2D common Callback ID enumeration definition
  */
typedef enum
{
  HAL_DMA2D_MSPINIT_CB_ID           = 0x00U,    /*!< DMA2D MspInit callback ID                 */
  HAL_DMA2D_MSPDEINIT_CB_ID         = 0x01U,    /*!< DMA2D MspDeInit callback ID               */
  HAL_DMA2D_TRANSFERCOMPLETE_CB_ID  = 0x02U,    /*!< DMA2D transfer complete callback ID       */
  HAL_DMA2D_TRANSFERERROR_CB_ID     = 0x03U,    /*!< DMA2D transfer error callback ID          */
  HAL_DMA2D_LINEEVENT_CB_ID         = 0x04U,    /*!< DMA2D line event callback ID              */
  HAL_DMA2D_CLUTLOADINGCPLT_CB_ID   = 0x05U,    /*!< DMA2D CLUT loading completion callback ID */
} HAL_DMA2D_CallbackIDTypeDef;
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL DMA2D common CL Callback ID enumeration definition
  */
typedef enum
{
  HAL_DMA2D_CL_MSPINIT_CB_ID                     = 0x00U,    /*!< DMA2D MspInit callback ID                 */
  HAL_DMA2D_CL_MSPDEINIT_CB_ID                   = 0x01U,    /*!< DMA2D MspDeInit callback ID               */
  HAL_DMA2D_CL_TRANSFERCOMPLETE_CB_ID            = 0x02U,    /*!< DMA2D transfer complete callback ID       */
  HAL_DMA2D_CL_TRANSFERERROR_CB_ID               = 0x03U,    /*!< DMA2D transfer error callback ID          */
  HAL_DMA2D_CL_LINEEVENT_CB_ID                   = 0x04U,    /*!< DMA2D line event callback ID              */
  HAL_DMA2D_CL_CLUTLOADINGCPLT_CB_ID             = 0x05U,    /*!< DMA2D CLUT loading completion callback ID */
  HAL_DMA2D_CL_SUSPEND_CB_ID                     = 0x06U,    /*!< DMA2D transfer error callback ID          */
  HAL_DMA2D_CL_RINGBUFFERCOMPLETE_CB_ID          = 0x07U,    /*!< DMA2D transfer error callback ID       */
  HAL_DMA2D_CL_GENERALPURPOSEFLAGEVENT_CB_ID     = 0x08U,    /*!< DMA2D transfer error callback ID       */
  HAL_DMA2D_CL_ERROR_CB_ID                       = 0x09U,    /*!< DMA2D transfer error callback ID          */
} HAL_DMA2D_CL_CallbackIDTypeDef;
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

/**
  * @}
  */
/* Exported macros ------------------------------------------------------------*/
/** @defgroup DMA2D_Exported_Macros DMA2D Exported Macros
  * @{
  */

/** @brief Reset DMA2D handle state
  * @param  __HANDLE__ specifies the DMA2D handle.
  * @retval None
  */
#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
#define __HAL_DMA2D_RESET_HANDLE_STATE(__HANDLE__) do{                                             \
                                                       (__HANDLE__)->State = HAL_DMA2D_STATE_RESET;\
                                                       (__HANDLE__)->MspInitCallback = NULL;       \
                                                       (__HANDLE__)->MspDeInitCallback = NULL;     \
                                                     }while(0)
#else
#define __HAL_DMA2D_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DMA2D_STATE_RESET)
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */


/**
  * @brief  Enable the DMA2D.
  * @param  __HANDLE__ DMA2D handle
  * @retval None.
  */
#define __HAL_DMA2D_ENABLE(__HANDLE__)        ((__HANDLE__)->Instance->CR |= DMA2D_CR_START)


/* Interrupt & Flag management */
/**
  * @brief  Get the DMA2D pending flags.
  * @param  __HANDLE__ DMA2D handle
  * @param  __FLAG__ flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg DMA2D_FLAG_CE:  Configuration error flag
  *            @arg DMA2D_FLAG_CTC: CLUT transfer complete flag
  *            @arg DMA2D_FLAG_CAE: CLUT access error flag
  *            @arg DMA2D_FLAG_TW:  Transfer Watermark flag
  *            @arg DMA2D_FLAG_TC:  Transfer complete flag
  *            @arg DMA2D_FLAG_TE:  Transfer error flag
  *            @arg DMA2D_FLAG_GPF3I: General Purpose Flag 3 Interrupt Flag
  *            @arg DMA2D_FLAG_GPF2I: General Purpose Flag 2 Interrupt Flag
  *            @arg DMA2D_FLAG_GPF1I: General Purpose Flag 1 Interrupt Flag
  *            @arg DMA2D_FLAG_GPF0I: General Purpose Flag 0 Interrupt Flag
  *            @arg DMA2D_FLAG_CLE : Command List Error Interrupt Flag
  *            @arg DMA2D_FLAG_CLS : Command List suspended Interrupt Flag
  *            @arg DMA2D_FLAG_RBE : Ring Buffer Error Interrupt Flag
  *            @arg DMA2D_FLAG_RBC : Ring Buffer Completed Interrupt Flag
  * @retval The state of FLAG.
  */
#define __HAL_DMA2D_GET_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ISR & (__FLAG__))

/**
  * @brief  Clear the DMA2D pending flags.
  * @param  __HANDLE__ DMA2D handle
  * @param  __FLAG__ specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA2D_FLAG_CE:  Configuration error flag
  *            @arg DMA2D_FLAG_CTC: CLUT transfer complete flag
  *            @arg DMA2D_FLAG_CAE: CLUT access error flag
  *            @arg DMA2D_FLAG_TW:  Transfer Watermark flag
  *            @arg DMA2D_FLAG_TC:  Transfer complete flag
  *            @arg DMA2D_FLAG_TE:  Transfer error flag
  *            @arg DMA2D_FLAG_GPF3I:  General Purpose Flag 3 Interrupt Flag
  *            @arg DMA2D_FLAG_GPF2I:  General Purpose Flag 2 Interrupt Flag
  *            @arg DMA2D_FLAG_GPF1I:  General Purpose Flag 1 Interrupt Flag
  *            @arg DMA2D_FLAG_GPF0I:  General Purpose Flag 0 Interrupt Flag
  *            @arg DMA2D_FLAG_CLE :  Command List Error Interrupt Flag
  *            @arg DMA2D_FLAG_CLS :  Command List suspended Interrupt Flag
  *            @arg DMA2D_FLAG_RBE :  Ring Buffer Error Interrupt Flag
  *            @arg DMA2D_FLAG_RBC :  Ring Buffer Completed Interrupt Flag
  * @retval None
  */
#define __HAL_DMA2D_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->IFCR = (__FLAG__))

/**
  * @brief  Clear the DMA2D pending GeneralPurpose flags.
  * @param  __HANDLE__ DMA2D handle
  * @param  __FLAG__ specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA2D_FLAG_GPF3:  General Purpose Flag 3
  *            @arg DMA2D_FLAG_GPF2:  General Purpose Flag 2
  *            @arg DMA2D_FLAG_GPF1:  General Purpose Flag 1
  *            @arg DMA2D_FLAG_GPF0:  General Purpose Flag 0
  * @retval None
  */
#define __HAL_DMA2D_CL_CLEAR_GPFLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->GPFRR = (__FLAG__))
/**
  * @brief  Clear the DMA2D pending flags.
  * @param  __HANDLE__ DMA2D handle
  * @param  __FLAG__ specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA2D_FLAG_LCLMSE:  Linear command list multi start error Interrupt Flag
  *            @arg DMA2D_FLAG_LCLIE :  Linear command list instruction error Interrupt Flag
  *            @arg DMA2D_FLAG_LCLRE :  Linear command list read error Interrupt Flag
  *            @arg DMA2D_FLAG_GPF3S :  The command list is suspended by GPFLAG 3 Interrupt Flag
  *            @arg DMA2D_FLAG_GPF2S :  The command list is suspended by GPFLAG 2 Interrupt Flag
  *            @arg DMA2D_FLAG_GPF1S :  The command list is suspended by GPFLAG 1 Interrupt Flag
  *            @arg DMA2D_FLAG_GPF0S :  The command list is suspended by GPFLAG 0 Interrupt Flag
  *            @arg DMA2D_FLAG_SUSPS :  The command list is suspended by the SUSP bit Interrupt Flag
  * @retval None
  */
#define __HAL_DMA2D_CL_GET_GPFLAG_SUSPEND(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->CLSR & (__FLAG__))

/**
  * @brief  Enable the specified DMA2D interrupts.
  * @param  __HANDLE__ DMA2D handle
  * @param __INTERRUPT__ specifies the DMA2D interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA2D_IT_CE:  Configuration error interrupt mask
  *            @arg DMA2D_IT_CTC: CLUT transfer complete interrupt mask
  *            @arg DMA2D_IT_CAE: CLUT access error interrupt mask
  *            @arg DMA2D_IT_TW:  Transfer Watermark interrupt mask
  *            @arg DMA2D_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA2D_IT_TE:  Transfer error interrupt mask
  *            @arg DMA2D_IT_GPF3: General Purpose Flag 3 interrupt mask
  *            @arg DMA2D_IT_GPF2: General Purpose Flag 2 interrupt mask
  *            @arg DMA2D_IT_GPF1: General Purpose Flag 1 interrupt mask
  *            @arg DMA2D_IT_GPF0: General Purpose Flag 0 interrupt mask
  *            @arg DMA2D_IT_CLE : Command List Error interrupt mask
  *            @arg DMA2D_IT_CLS : Command List Suspended interrupt mask
  *            @arg DMA2D_IT_RBE : Ring Buffer Error interrupt mask
  *            @arg DMA2D_IT_RBC : Ring Buffer Completed interrupt mask
  * @retval None
  */
#define __HAL_DMA2D_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER |= (__INTERRUPT__))

/**
  * @brief  Disable the specified DMA2D interrupts.
  * @param  __HANDLE__ DMA2D handle
  * @param __INTERRUPT__ specifies the DMA2D interrupt sources to be disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA2D_IT_CE:  Configuration error interrupt mask
  *            @arg DMA2D_IT_CTC: CLUT transfer complete interrupt mask
  *            @arg DMA2D_IT_CAE: CLUT access error interrupt mask
  *            @arg DMA2D_IT_TW:  Transfer Watermark interrupt mask
  *            @arg DMA2D_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA2D_IT_TE:  Transfer error interrupt mask
  *            @arg DMA2D_IT_GPF3: General Purpose Flag 3 interrupt mask
  *            @arg DMA2D_IT_GPF2: General Purpose Flag 2 interrupt mask
  *            @arg DMA2D_IT_GPF1: General Purpose Flag 1 interrupt mask
  *            @arg DMA2D_IT_GPF0: General Purpose Flag 0 interrupt mask
  *            @arg DMA2D_IT_CLE : Command List Error interrupt mask
  *            @arg DMA2D_IT_CLS : Command List Suspended interrupt mask
  *            @arg DMA2D_IT_RBE : Ring Buffer Error interrupt mask
  *            @arg DMA2D_IT_RBC : Ring Buffer Completed interrupt mask
  * @retval None
  */
#define __HAL_DMA2D_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified DMA2D interrupt source is enabled or not.
  * @param  __HANDLE__ DMA2D handle
  * @param  __INTERRUPT__ specifies the DMA2D interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg DMA2D_IT_CE:  Configuration error interrupt mask
  *            @arg DMA2D_IT_CTC: CLUT transfer complete interrupt mask
  *            @arg DMA2D_IT_CAE: CLUT access error interrupt mask
  *            @arg DMA2D_IT_TW:  Transfer Watermark interrupt mask
  *            @arg DMA2D_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA2D_IT_TE:  Transfer error interrupt mask
  *            @arg DMA2D_IT_GPF3: General Purpose Flag 3 interrupt mask
  *            @arg DMA2D_IT_GPF2: General Purpose Flag 2 interrupt mask
  *            @arg DMA2D_IT_GPF1: General Purpose Flag 1 interrupt mask
  *            @arg DMA2D_IT_GPF0: General Purpose Flag 0 interrupt mask
  *            @arg DMA2D_IT_CLE : Command List Error interrupt mask
  *            @arg DMA2D_IT_CLS : Command List Suspended interrupt mask
  *            @arg DMA2D_IT_RBE : Ring Buffer Error interrupt mask
  *            @arg DMA2D_IT_RBC : Ring Buffer Completed interrupt mask
  * @retval The state of INTERRUPT source.
  */
#define __HAL_DMA2D_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER & (__INTERRUPT__))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DMA2D_Exported_Functions DMA2D Exported Functions
  * @{
  */
#if (USE_DMA2D_COMMAND_LIST_MODE == 0)
/** @addtogroup DMA2D_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

/* Initialization and de-initialization functions *******************************/
HAL_StatusTypeDef HAL_DMA2D_Init(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_DeInit(DMA2D_HandleTypeDef *hdma2d);
void              HAL_DMA2D_MspInit(DMA2D_HandleTypeDef *hdma2d);
void              HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef *hdma2d);
/* Callbacks Register/UnRegister functions  ***********************************/
#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_DMA2D_RegisterCallback(DMA2D_HandleTypeDef *hdma2d, HAL_DMA2D_CallbackIDTypeDef CallbackID,
                                             pDMA2D_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_DMA2D_UnRegisterCallback(DMA2D_HandleTypeDef *hdma2d, HAL_DMA2D_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

/**
  * @}
  */


/** @addtogroup DMA2D_Exported_Functions_Group2 IO operation functions
  * @{
  */

/* IO operation functions *******************************************************/
HAL_StatusTypeDef HAL_DMA2D_Start(DMA2D_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress, uint32_t Width,
                                  uint32_t Height);
HAL_StatusTypeDef HAL_DMA2D_BlendingStart(DMA2D_HandleTypeDef *hdma2d, uint32_t SrcAddress1, uint32_t SrcAddress2,
                                          uint32_t DstAddress, uint32_t Width,  uint32_t Height);
HAL_StatusTypeDef HAL_DMA2D_Start_IT(DMA2D_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress, uint32_t Width,
                                     uint32_t Height);
HAL_StatusTypeDef HAL_DMA2D_BlendingStart_IT(DMA2D_HandleTypeDef *hdma2d, uint32_t SrcAddress1, uint32_t SrcAddress2,
                                             uint32_t DstAddress, uint32_t Width, uint32_t Height);
HAL_StatusTypeDef HAL_DMA2D_Suspend(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_Resume(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_Abort(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_EnableCLUT(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTStartLoad(DMA2D_HandleTypeDef *hdma2d, const DMA2D_CLUTCfgTypeDef *CLUTCfg,
                                          uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTStartLoad_IT(DMA2D_HandleTypeDef *hdma2d, const DMA2D_CLUTCfgTypeDef *CLUTCfg,
                                             uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTLoad(DMA2D_HandleTypeDef *hdma2d, DMA2D_CLUTCfgTypeDef CLUTCfg, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTLoad_IT(DMA2D_HandleTypeDef *hdma2d, DMA2D_CLUTCfgTypeDef CLUTCfg, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTLoading_Abort(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTLoading_Suspend(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTLoading_Resume(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_PollForTransfer(DMA2D_HandleTypeDef *hdma2d, uint32_t Timeout);
void              HAL_DMA2D_IRQHandler(DMA2D_HandleTypeDef *hdma2d);
void              HAL_DMA2D_LineEventCallback(DMA2D_HandleTypeDef *hdma2d);
void              HAL_DMA2D_CLUTLoadingCpltCallback(DMA2D_HandleTypeDef *hdma2d);

/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */

/* Peripheral Control functions *************************************************/
HAL_StatusTypeDef HAL_DMA2D_ConfigLayer(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_ConfigCLUT(DMA2D_HandleTypeDef *hdma2d, DMA2D_CLUTCfgTypeDef CLUTCfg, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_ConfigRotation(DMA2D_HandleTypeDef *hdma2d, uint32_t Source, uint32_t Mirroring_Type);
HAL_StatusTypeDef HAL_DMA2D_ConfigStencil(DMA2D_HandleTypeDef *hdma2d, uint32_t source,
                                          DMA2D_StencilCfgTypeDef *pStencilCfg);
HAL_StatusTypeDef HAL_DMA2D_ConfigDownscaling(DMA2D_HandleTypeDef *hdma2d, uint32_t source,
                                              DMA2D_DownscalingCfgTypeDef *pDownscalingCfg);
HAL_StatusTypeDef HAL_DMA2D_ProgramLineEvent(DMA2D_HandleTypeDef *hdma2d, uint32_t Line);
HAL_StatusTypeDef HAL_DMA2D_EnableDeadTime(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_DisableDeadTime(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_ConfigDeadTime(DMA2D_HandleTypeDef *hdma2d, uint8_t DeadTime);

/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group4 Peripheral State and Error functions
  * @{
  */

/* Peripheral State functions ***************************************************/
HAL_DMA2D_StateTypeDef HAL_DMA2D_GetState(const DMA2D_HandleTypeDef *hdma2d);
uint32_t               HAL_DMA2D_GetError(const DMA2D_HandleTypeDef *hdma2d);
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 0 */
#if (USE_DMA2D_COMMAND_LIST_MODE == 1)
/** @addtogroup DMA2D_Exported_Functions_Group5 IO operation functions
  * @{
  */
HAL_StatusTypeDef HAL_DMA2D_CL_Init(DMA2D_CL_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_CL_DeInit(DMA2D_CL_HandleTypeDef *hdma2d);

void              HAL_DMA2D_CL_MspInit(DMA2D_CL_HandleTypeDef *hdma2d);
void              HAL_DMA2D_CL_MspDeInit(DMA2D_CL_HandleTypeDef *hdma2d);
/* Callbacks Register/UnRegister functions  ***********************************/
#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_DMA2D_CL_RegisterCallback(DMA2D_CL_HandleTypeDef *hdma2d,
                                                HAL_DMA2D_CL_CallbackIDTypeDef CallbackID,
                                                pDMA2D_CL_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_DMA2D_CL_UnRegisterCallback(DMA2D_CL_HandleTypeDef *hdma2d,
                                                  HAL_DMA2D_CL_CallbackIDTypeDef CallbackID);
HAL_StatusTypeDef HAL_DMA2D_CL_Register_GeneralPurposeEvent_Callback(DMA2D_CL_HandleTypeDef *hdma2d, HAL_DMA2D_CL_CallbackIDTypeDef CallbackID,
                                                                   pDMA2D_CL_GeneralPurposeEventCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_DMA2D_CL_UnRegister_GeneralPurposeEvent_Callback(DMA2D_CL_HandleTypeDef *hdma2d, HAL_DMA2D_CL_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */


void HAL_DMA2D_CL_IRQHandler(DMA2D_CL_HandleTypeDef *hdma2d);

void  HAL_DMA2D_CL_LineEventCallback(DMA2D_CL_HandleTypeDef *hdma2d);
void  HAL_DMA2D_CL_CLUTLoadingCpltCallback(DMA2D_CL_HandleTypeDef *hdma2d);
void  HAL_DMA2D_CL_RBXferCpltCallback(DMA2D_CL_HandleTypeDef *hdma2d);
void  HAL_DMA2D_CL_SuspendCallback(DMA2D_CL_HandleTypeDef *hdma2d);
void  HAL_DMA2D_CL_TransferCpltCallback(DMA2D_CL_HandleTypeDef *hdma2d);
void  HAL_DMA2D_CL_XferErrorCallback(DMA2D_CL_HandleTypeDef *hdma2d);
void  HAL_DMA2D_CL_ErrorCallback(DMA2D_CL_HandleTypeDef *hdma2d);
void  HAL_DMA2D_CL_GeneralPuposeEventCallback(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t GeneralPurposeFlag);

HAL_StatusTypeDef HAL_DMA2D_CL_AddConfigLayerCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t LayerIdx,
                                                 DMA2D_LayerCfgTypeDef *pLayerCfg);
HAL_StatusTypeDef HAL_DMA2D_CL_AddConfigRotationCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t Source,
                                                    uint32_t Mirroring_Type);
HAL_StatusTypeDef HAL_DMA2D_CL_AddConfigStencilCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t Source,
                                                 DMA2D_StencilCfgTypeDef *pStencilCfg);
HAL_StatusTypeDef HAL_DMA2D_CL_AddConfigDownscalingCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t Source,
                                                       DMA2D_DownscalingCfgTypeDef *pDownscalingCfg);
HAL_StatusTypeDef HAL_DMA2D_CL_AddProgramLineEventCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t Line);
HAL_StatusTypeDef HAL_DMA2D_CL_AddCLUTStartLoadCMD(DMA2D_CL_HandleTypeDef *hdma2d,uint32_t LayerIdx,
                                              const DMA2D_CLUTCfgTypeDef *CLUTCfg,
                                              DMA2D_CL_CommandListTypeDef *pCommandList);
HAL_StatusTypeDef HAL_DMA2D_CL_AddCopyCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress,
                                            uint32_t Width, uint32_t Height, DMA2D_CL_CommandListTypeDef *pCommandList);
HAL_StatusTypeDef HAL_DMA2D_CL_AddBlendingCMD(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t SrcAddress1,
                                              uint32_t SrcAddress2, uint32_t DstAddress, uint32_t Width,
                                              uint32_t Height,DMA2D_CL_CommandListTypeDef *pCommandList);
HAL_StatusTypeDef HAL_DMA2D_CL_Init_CommandList(uint32_t *Address, uint32_t Size,
                                                DMA2D_CL_CommandListTypeDef *pCommandList);
HAL_StatusTypeDef HAL_DMA2D_CL_ResetIndex(DMA2D_CL_CommandListTypeDef *pCommandList);
HAL_StatusTypeDef HAL_DMA2D_CL_InsertCommandList(DMA2D_CL_HandleTypeDef *hdma2d,
                                                 DMA2D_CL_CommandListTypeDef *pCommandList, uint32_t gpflag,
                                                 uint32_t post_flag_config, uint32_t pre_flag_config);
HAL_StatusTypeDef HAL_DMA2D_CL_Start(DMA2D_CL_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_CL_StartOpt(DMA2D_CL_HandleTypeDef *hdma2d, uint32_t Interrupts);

HAL_StatusTypeDef HAL_DMA2D_CL_Suspend(DMA2D_CL_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_CL_Resume(DMA2D_CL_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_CL_Abort(DMA2D_CL_HandleTypeDef *hdma2d);


HAL_DMA2D_CL_StateTypeDef HAL_DMA2D_CL_GetState(const DMA2D_CL_HandleTypeDef *hdma2d);
uint32_t               HAL_DMA2D_CL_GetError(const DMA2D_CL_HandleTypeDef *hdma2d);
#endif /* USE_DMA2D_COMMAND_LIST_MODE == 1 */
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/

/** @addtogroup DMA2D_Private_Constants DMA2D Private Constants
  * @{
  */

/** @defgroup DMA2D_Maximum_Line_WaterMark DMA2D Maximum Line Watermark
  * @{
  */
#define DMA2D_LINE_WATERMARK_MAX            DMA2D_LWR_LW       /*!< DMA2D maximum line watermark */
/**
  * @}
  */

/** @defgroup DMA2D_Color_Value DMA2D Color Value
  * @{
  */
#define DMA2D_COLOR_VALUE                 0x000000FFU  /*!< Color value mask */
/**
  * @}
  */

/** @defgroup DMA2D_Max_Layer DMA2D Maximum Number of Layers
  * @{
  */
#define DMA2D_MAX_LAYER         2U         /*!< DMA2D maximum number of layers */
/**
  * @}
  */

/** @defgroup DMA2D_Layers DMA2D Layers
  * @{
  */
#define DMA2D_BACKGROUND_LAYER             0x00000000U   /*!< DMA2D Background Layer (layer 0) */
#define DMA2D_FOREGROUND_LAYER             0x00000001U   /*!< DMA2D Foreground Layer (layer 1) */
/**
  * @}
  */

/** @defgroup DMA2D_Offset DMA2D Offset
  * @{
  */
#define DMA2D_OFFSET                DMA2D_FGOR_LO            /*!< maximum Line Offset */
/**
  * @}
  */

/** @defgroup DMA2D_Size DMA2D Size
  * @{
  */
#define DMA2D_PIXEL                 (DMA2D_NLR_PL >> 16U)    /*!< DMA2D maximum number of pixels per line */
#define DMA2D_LINE                  DMA2D_NLR_NL             /*!< DMA2D maximum number of lines           */
/**
  * @}
  */

/** @defgroup DMA2D_CLUT_Size DMA2D CLUT Size
  * @{
  */
#define DMA2D_CLUT_SIZE             (DMA2D_FGPFCCR_CS >> 8U)  /*!< DMA2D maximum CLUT size */
/**
  * @}
  */

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup DMA2D_Private_Macros DMA2D Private Macros
  * @{
  */
#define IS_DMA2D_LAYER(LAYER)                 (((LAYER) == DMA2D_BACKGROUND_LAYER)\
                                               || ((LAYER) == DMA2D_FOREGROUND_LAYER))

#define IS_DMA2D_MODE(MODE)                   (((MODE) == DMA2D_M2M)          || ((MODE) == DMA2D_M2M_PFC) || \
                                               ((MODE) == DMA2D_M2M_BLEND)    || ((MODE) == DMA2D_R2M)     || \
                                               ((MODE) == DMA2D_M2M_BLEND_FG) || ((MODE) == DMA2D_M2M_BLEND_BG))

#define IS_DMA2D_CMODE(MODE_ARGB)             (((MODE_ARGB) == DMA2D_OUTPUT_ARGB8888) || \
                                               ((MODE_ARGB) == DMA2D_OUTPUT_RGB888)   || \
                                               ((MODE_ARGB) == DMA2D_OUTPUT_RGB565)   || \
                                               ((MODE_ARGB) == DMA2D_OUTPUT_ARGB1555) || \
                                               ((MODE_ARGB) == DMA2D_OUTPUT_ARGB4444))

#define IS_DMA2D_COLOR(COLOR)                 ((COLOR) <= DMA2D_COLOR_VALUE)
#define IS_DMA2D_LINE(LINE)                   ((LINE) <= DMA2D_LINE)
#define IS_DMA2D_PIXEL(PIXEL)                 ((PIXEL) <= DMA2D_PIXEL)
#define IS_DMA2D_OFFSET(OOFFSET)              ((OOFFSET) <= DMA2D_OFFSET)

#define IS_DMA2D_INPUT_COLOR_MODE(INPUT_CM)   (((INPUT_CM) == DMA2D_INPUT_ARGB8888) || \
                                               ((INPUT_CM) == DMA2D_INPUT_RGB888)   || \
                                               ((INPUT_CM) == DMA2D_INPUT_RGB565)   || \
                                               ((INPUT_CM) == DMA2D_INPUT_ARGB1555) || \
                                               ((INPUT_CM) == DMA2D_INPUT_ARGB4444) || \
                                               ((INPUT_CM) == DMA2D_INPUT_L8)       || \
                                               ((INPUT_CM) == DMA2D_INPUT_AL44)     || \
                                               ((INPUT_CM) == DMA2D_INPUT_AL88)     || \
                                               ((INPUT_CM) == DMA2D_INPUT_L4)       || \
                                               ((INPUT_CM) == DMA2D_INPUT_A8)       || \
                                               ((INPUT_CM) == DMA2D_INPUT_A4)       || \
                                               ((INPUT_CM) == DMA2D_INPUT_YCBCR)    || \
                                               ((INPUT_CM) == DMA2D_INPUT_A2)       || \
                                               ((INPUT_CM) == DMA2D_INPUT_A1)       || \
                                               ((INPUT_CM) == DMA2D_INPUT_ARGB2222))

#define IS_DMA2D_ALPHA_MODE(AlphaMode)        (((AlphaMode) == DMA2D_NO_MODIF_ALPHA) || \
                                               ((AlphaMode) == DMA2D_REPLACE_ALPHA)  || \
                                               ((AlphaMode) == DMA2D_COMBINE_ALPHA))

#define IS_DMA2D_ALPHA_INVERTED(Alpha_Inverted) (((Alpha_Inverted) == DMA2D_REGULAR_ALPHA) || \
                                                 ((Alpha_Inverted) == DMA2D_INVERTED_ALPHA))

#define IS_DMA2D_RB_SWAP(RB_Swap) (((RB_Swap) == DMA2D_RB_REGULAR) || \
                                   ((RB_Swap) == DMA2D_RB_SWAP))

#define IS_DMA2D_LOM_MODE(LOM)          (((LOM) == DMA2D_LOM_PIXELS) || \
                                         ((LOM) == DMA2D_LOM_BYTES))

#define IS_DMA2D_BYTES_SWAP(BYTES_SWAP) (((BYTES_SWAP) == DMA2D_BYTES_REGULAR) || \
                                         ((BYTES_SWAP) == DMA2D_BYTES_SWAP))

#define IS_DMA2D_CHROMA_SUB_SAMPLING(CSS) (((CSS) == DMA2D_NO_CSS)  || \
                                           ((CSS) == DMA2D_CSS_422) || \
                                           ((CSS) == DMA2D_CSS_420))
#define IS_DMA2D_ALPHA_POSITION(AlphaPosition) (((AlphaPosition) == DMA2D_REGULAR_ALPHA_POS) || \
                                                ((AlphaPosition) == DMA2D_SWAP_ALPHA_POS))

#define IS_DMA2D_ROT_SRC(ROT_SRC) (((ROT_SRC) == DMA2D_SOURCE_NONE)  || \
                                   ((ROT_SRC) == DMA2D_SOURCE_FOREGROUND)  || \
                                   ((ROT_SRC) == DMA2D_SOURCE_BACKGROUND)  || \
                                   ((ROT_SRC) == DMA2D_SOURCE_BLENDER_OUTPUT))
#define IS_DMA2D_ROT_TYPE(ROT_TYPE) (((ROT_TYPE) == DMA2D_NO_ROTATION)   || \
                                     ((ROT_TYPE) == DMA2D_NO_ROTATION_FLIP)                || \
                                     ((ROT_TYPE) == DMA2D_ROTATE_90)                || \
                                     ((ROT_TYPE) == DMA2D_ROTATE_90_FLIP)              || \
                                     ((ROT_TYPE) == DMA2D_ROTATE_180)              || \
                                     ((ROT_TYPE) == DMA2D_ROTATE_180_FLIP)               || \
                                     ((ROT_TYPE) == DMA2D_ROTATE_270)|| \
                                     ((ROT_TYPE) == DMA2D_ROTATE_270_FLIP))

#define IS_DMA2D_SKIP_PIXEL_VALUE(value) ((value) <= 0xFU)
#define IS_DMA2D_STENCIL_MODE(mode) (((mode) == DMA2D_STENCIL_MODE_A1) || \
                                     ((mode) == DMA2D_STENCIL_MODE_A2) || \
                                     ((mode) == DMA2D_STENCIL_MODE_A4) || \
                                     ((mode) == DMA2D_STENCIL_MODE_A8))
#define IS_DMA2D_STENCIL_LO(LO) ((LO) <= 0xFFFFU)
#define IS_DMA2D_STENCIL_HPRE(HPRE) ((HPRE) <= 0xFU)
#define IS_DMA2D_STENCIL_HTRAIL(HTAIL) ((HTAIL) <= 0xFU)
#define IS_DMA2D_STENCIL_ALPHA_INVERTED(ALPHA_INV) (((ALPHA_INV) == DMA2D_REGULAR_ALPHA) || \
                                                    ((ALPHA_INV) == DMA2D_INVERTED_ALPHA))
#define IS_DMA2D_SCALE_SRC(SCALE_SRC) (((SCALE_SRC) == DMA2D_SOURCE_NONE)  || \
                                       ((SCALE_SRC) == DMA2D_SOURCE_FOREGROUND)  || \
                                       ((SCALE_SRC) == DMA2D_SOURCE_BACKGROUND)  || \
                                       ((SCALE_SRC) == DMA2D_SOURCE_BLENDER_OUTPUT))

#define IS_DMA2D_SCALE_VSTEP(VSTEP) ((VSTEP) <= 0xFFFU)
#define IS_DMA2D_SCALE_HSTEP(HSTEP) ((HSTEP) <= 0xFFFU)
#define IS_DMA2D_SCALE_NUMBER_OF_LINES(NL) ((NL) <= 0xFFFFU)
#define IS_DMA2D_SCALE_PIXEL_PER_LINE(PL) ((PL) <= 0x3FFFU)
#define IS_DMA2D_SCALE_HPHASE(HPHASE) ((HPHASE) <= 0xFFFU)
#define IS_DMA2D_SCALE_VPHASE(VPHASE) ((VPHASE) <= 0xFFFU)

#define IS_DMA2D_STENCIL_SRC(STENCIL_SRC) (((STENCIL_SRC) == DMA2D_SOURCE_NONE)  || \
                                           ((STENCIL_SRC) == DMA2D_SOURCE_FOREGROUND)  || \
                                           ((STENCIL_SRC) == DMA2D_SOURCE_BACKGROUND)  || \
                                           ((STENCIL_SRC) == DMA2D_SOURCE_BLENDER_OUTPUT))
#define IS_DMA2D_CLUT_CM(CLUT_CM)        (((CLUT_CM) ==  DMA2D_CCM_ARGB8888)|| ((CLUT_CM) == DMA2D_CCM_RGB888) ||\
                                          ((CLUT_CM) ==  DMA2D_CCM_RGB565) || ((CLUT_CM) ==  DMA2D_CCM_ARGB1555)||\
                                          ((CLUT_CM) ==  DMA2D_CCM_ARGB4444) || ((CLUT_CM) ==  DMA2D_CCM_ARGB2222))
#define IS_DMA2D_CLUT_SIZE(CLUT_SIZE)         ((CLUT_SIZE) <= DMA2D_CLUT_SIZE)
#define IS_DMA2D_LINEWATERMARK(LineWatermark) ((LineWatermark) <= DMA2D_LINE_WATERMARK_MAX)
#define IS_DMA2D_IT(IT)                       (((IT) == DMA2D_IT_CE)    || ((IT) == DMA2D_IT_CTC)  || \
                                               ((IT) == DMA2D_IT_CAE)   || ((IT) == DMA2D_IT_TW)   || \
                                               ((IT) == DMA2D_IT_TC)    || ((IT) == DMA2D_IT_TE)   || \
                                               ((IT) == DMA2D_IT_GPF3)  || ((IT) == DMA2D_IT_GPF2) || \
                                               ((IT) == DMA2D_IT_GPF1)  || ((IT) == DMA2D_IT_GPF0) || \
                                               ((IT) == DMA2D_IT_CLE)   || ((IT) == DMA2D_IT_CLS)  || \
                                               ((IT) == DMA2D_IT_RBE)   || ((IT) == DMA2D_IT_RBC)  || \
                                               ((IT) == DMA2D_IT_ALL))

#define IS_DMA2D_GET_FLAG(FLAG)               (((FLAG) == DMA2D_FLAG_CE)     || ((FLAG) == DMA2D_FLAG_CTC)    || \
                                               ((FLAG) == DMA2D_FLAG_CAE)    || ((FLAG) == DMA2D_FLAG_TW)     || \
                                               ((FLAG) == DMA2D_FLAG_TC)     || ((FLAG) == DMA2D_FLAG_TE)     || \
                                               ((FLAG) == DMA2D_FLAG_GPF3I)  || ((FLAG) == DMA2D_FLAG_GPF2I)  || \
                                               ((FLAG) == DMA2D_FLAG_GPF1I)  || ((FLAG) == DMA2D_FLAG_GPF0I)  || \
                                               ((FLAG) == DMA2D_FLAG_CLE)    || ((FLAG) == DMA2D_FLAG_CLS)    || \
                                               ((FLAG) == DMA2D_FLAG_RBE)    || ((FLAG) == DMA2D_FLAG_RBC)    || \
                                               ((FLAG) == DMA2D_FLAG_LCLMSE) || ((FLAG) == DMA2D_FLAG_LCLIE)  || \
                                               ((FLAG) == DMA2D_FLAG_LCLRE)  || ((FLAG) == DMA2D_FLAG_GPF3S)  || \
                                               ((FLAG) == DMA2D_FLAG_GPF2S)  || ((FLAG) == DMA2D_FLAG_GPF1S)  || \
                                               ((FLAG) == DMA2D_FLAG_GPF0S)  || ((FLAG) == DMA2D_FLAG_SUSPS))
#define IS_DMA2D_CL_RB_SIZE(SIZE) (((SIZE) == DMA2D_RB_SIZE_64B)   || \
                                   ((SIZE) == DMA2D_RB_SIZE_128B)  || \
                                   ((SIZE) == DMA2D_RB_SIZE_256B)  || \
                                   ((SIZE) == DMA2D_RB_SIZE_512B)  || \
                                   ((SIZE) == DMA2D_RB_SIZE_1KB) || \
                                   ((SIZE) == DMA2D_RB_SIZE_2KB) || \
                                   ((SIZE) == DMA2D_RB_SIZE_4KB) || \
                                   ((SIZE) == DMA2D_RB_SIZE_8KB))
#define IS_DMA2D_CL_ADDRESS_RB_VALID(Address) (((Address) != 0x0U) && (((Address) & 0x7) == 0x0U))
#define IS_DMA2D_CL_ADDRESS_VALID(Address) (((Address) != 0x0U) && (((Address) & 0x7) == 0x0U))
#define IS_DMA2D_CL_SIZE(Size) ((Size) <= 4096)

#define IS_DMA2D_CL_PRE_POST_FLAG_OPERATION(flag_operation) ((flag_operation == DMA2D_GPFLAG_NOP)   ||\
                                                             (flag_operation == DMA2D_GPFLAG_SET)   ||\
                                                             (flag_operation == DMA2D_GPFLAG_RESET) ||\
                                                             (flag_operation == DMA2D_GPFLAG_TOGGLE))
#define IS_DMA2D_CL_GPFLAG(GPFLAG) ((GPFLAG == DMA2D_GPFLAG0) ||\
                                    (GPFLAG == DMA2D_GPFLAG1) ||\
                                    (GPFLAG == DMA2D_GPFLAG2) ||\
                                    (GPFLAG == DMA2D_GPFLAG3))
#define IS_DMA2D_CL_GPFLAG_INTERRUPT_MODE(mode) (((mode) == DMA2D_GPFLAG_NONE)    || \
                                                 ((mode) == DMA2D_GPFLAG_RISING)  || \
                                                 ((mode) == DMA2D_GPFLAG_FALLING) || \
                                                 ((mode) == DMA2D_GPFLAG_RISING_FALLING))
#define IS_DMA2D_CL_IT(IT) (((IT) == DMA2D_IT_CE)  || ((IT) == DMA2D_IT_CTC) || \
                            ((IT) == DMA2D_IT_CAE) || ((IT) == DMA2D_IT_TW)  || \
                            ((IT) == DMA2D_IT_TC)  || ((IT) == DMA2D_IT_TE)  || \
                            ((IT) == DMA2D_IT_GPF3) || ((IT) == DMA2D_IT_GPF2) || \
                            ((IT) == DMA2D_IT_GPF1) || ((IT) == DMA2D_IT_GPF0) || \
                            ((IT) == DMA2D_IT_CLE) || ((IT) == DMA2D_IT_CLS) || \
                            ((IT) == DMA2D_IT_RBE) || ((IT) == DMA2D_IT_RBC) || ((IT) == DMA2D_IT_ALL))
/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (DMA2D) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H5xx_HAL_DMA2D_H */
