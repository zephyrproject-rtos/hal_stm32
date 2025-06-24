/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_ltdc.h
  * @author  MCD Application Team
  * @brief   Header file of LTDC HAL module.
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
#ifndef STM32MP2xx_HAL_LTDC_H
#define STM32MP2xx_HAL_LTDC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

#if defined (LTDC)

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @defgroup LTDC LTDC
  * @brief LTDC HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup LTDC_Exported_Types LTDC Exported Types
  * @{
  */
#define MAX_LAYER  3U

/**
  * @brief  LTDC color structure definition
  */
typedef struct
{
  uint8_t Blue;                    /*!< Configures the blue value.
                                        This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint8_t Green;                   /*!< Configures the green value.
                                        This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint8_t Red;                     /*!< Configures the red value.
                                        This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint8_t Reserved;                /*!< Reserved 0xFF */
} LTDC_ColorTypeDef;


/**
  * @brief  LTDC gamma structure definition
  */
typedef struct
{
  uint8_t Blue;                    /*!< Configures the gamma blue value.
                                        This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint8_t Green;                   /*!< Configures the gamma green value.
                                        This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint8_t Red;                     /*!< Configures the gamma red value.
                                        This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint8_t Address;                 /*!< Address of the R,G,B table */
} LTDC_GammaTypeDef;

/**
  * @brief  LTDC external display structure definition
  */
typedef struct
{
  uint32_t YCbCrOrder;           /*!< Chrominance order */

  uint32_t YCbCrSel;             /*!< Selection of the CCIR hard-wired coefficients . */

  uint32_t YCbCrEn;              /*!< Output conversion to YCbCr 422 */

} LTDC_ExtDispTypeDef;

/**
  * @brief  LTDC rotation structure definition
  */
typedef struct
{
  uint32_t Buffer0Addr;               /*!< Buffer 0 address */

  uint32_t Buffer1Addr;               /*!< Buffer 1 address */

  uint32_t BufferPitch;               /*!< Buffer pitch */

  uint32_t InterFrameRed;             /*!< Red component of the rotation intermediate frame color */

  uint32_t InterFrameGreen;           /*!< Green component of the rotation intermediate frame color */

  uint32_t InterFrameBlue;            /*!< Blue component of the rotation intermediate frame color */

} LTDC_RotationTypeDef;

/**
  * @brief  LTDC Planar structure definition
  */
typedef struct
{
  uint32_t RescaleEnable;               /*!< Rescale enable */

  uint32_t OddPixel;                   /*!< Odd pixel first */

  uint32_t CbFirst;                    /*!< Cb component first */

  uint32_t YFirst;                     /*!< Y component first */

  uint32_t YCbCrConversion;            /*!< YCbCr to RGB conversion enable */
} LTDC_PlanarTypeDef;

/**
  * @brief  LTDC Auxiliary structure definition
  */
typedef struct
{
  uint32_t StartAddressBuffer0;        /*!< start address buffer0 */

  uint32_t StartAddressBuffer1;        /*!< start address buffer1 */

  uint32_t FrameBufferPitch;            /*!< Frame buffer pitch in bytes */

  uint32_t FrameBufferLineLength;      /*!< Frame buffer line length */

  uint32_t BufferLineNumber;            /*!< buffer line number */
} LTDC_AuxiliaryTypeDef;

/**
  * @brief  LTDC Scaler structure definition
  */
typedef struct
{
  uint32_t HorInputSize;         /*!< horizontal input size */

  uint32_t VerInputSize;         /*!< vertical input size */

  uint32_t HorOutputSize;        /*!< horizontal output size */

  uint32_t VerOutputSize;        /*!< vertical output size */

  uint32_t Enable;               /*!< Enabling scaler */
} LTDC_ScalerTypeDef;

/**
  * @brief  LTDC Conversion structure definition
  */
typedef struct
{
  uint32_t CrToGreen;            /*!< Cr to Green */

  uint32_t CbToGreen;            /*!< Cb to Green */

  uint32_t CrToRed;              /*!< CrToRed coefficient */

  uint32_t CbToBlue;             /*!< CbToBlue coefficient */
} LTDC_ConversionTypeDef;


/**
  * @brief  LTDC Init structure definition
  */
typedef struct
{
  uint32_t            HSPolarity;                /*!< configures the horizontal synchronization polarity.
                                                      This parameter can be one value of @ref LTDC_HS_POLARITY */

  uint32_t            VSPolarity;                /*!< configures the vertical synchronization polarity.
                                                      This parameter can be one value of @ref LTDC_VS_POLARITY */

  uint32_t            DEPolarity;                /*!< configures the data enable polarity.
                                                      This parameter can be one of value of @ref LTDC_DE_POLARITY */

  uint32_t            PCPolarity;                /*!< configures the pixel clock polarity.
                                                      This parameter can be one of value of @ref LTDC_PC_POLARITY */

  uint32_t            HorizontalSync;            /*!< configures the number of Horizontal synchronization width.
                                                      This parameter must be a number between Min_Data = 0x000
                            and Max_Data = 0xFFF. */

  uint32_t            VerticalSync;              /*!< configures the number of Vertical synchronization height.
                                                      This parameter must be a number between Min_Data = 0x000
                            and Max_Data = 0x7FF. */

  uint32_t            AccumulatedHBP;            /*!< configures the accumulated horizontal back porch width.
                                                      This parameter must be a number between
                            Min_Data = LTDC_HorizontalSync and Max_Data = 0xFFF. */

  uint32_t            AccumulatedVBP;            /*!< configures the accumulated vertical back porch height.
                                                      This parameter must be a number between
                            Min_Data = LTDC_VerticalSync and Max_Data = 0x7FF. */

  uint32_t            AccumulatedActiveW;        /*!< configures the accumulated active width.
                                                      This parameter must be a number between
                            Min_Data = LTDC_AccumulatedHBP and Max_Data = 0xFFF. */

  uint32_t            AccumulatedActiveH;        /*!< configures the accumulated active height.
                                                      This parameter must be a number between
                            Min_Data = LTDC_AccumulatedVBP and Max_Data = 0x7FF. */

  uint32_t            TotalWidth;                /*!< configures the total width.
                                                      This parameter must be a number between
                            Min_Data = LTDC_AccumulatedActiveW and Max_Data = 0xFFF. */

  uint32_t            TotalHeigh;                /*!< configures the total height.
                                                      This parameter must be a number between
                            Min_Data = LTDC_AccumulatedActiveH and Max_Data = 0x7FF. */

  LTDC_ColorTypeDef   Backcolor;                 /*!< Configures the background color. */

  uint32_t            SFTrig;                    /*!< configures the single frame mode. */

  uint32_t            SFExtTrig;                 /*!< configures the single frame mode. External Trigger */

  uint32_t            RotEn;                     /*!< Rotation Enable. */

  uint32_t            FifoUnderThresh;           /*!< Fifo underrun threshold. */

  LTDC_ExtDispTypeDef   ExtDisp;                 /*!< Configure the external display interface. */

  LTDC_RotationTypeDef  Rotation;                /*!< Configure the rotation. */
} LTDC_InitTypeDef;

/**
  * @brief  LTDC Layer structure definition
  */
typedef struct
{
  uint32_t WindowX0;                   /*!< Configures the Window Horizontal Start Position.
                                            This parameter must be a number between Min_Data = 0x000
                      and Max_Data = 0xFFF. */

  uint32_t WindowX1;                   /*!< Configures the Window Horizontal Stop Position.
                                            This parameter must be a number between Min_Data = 0x000
                      and Max_Data = 0xFFF. */

  uint32_t WindowY0;                   /*!< Configures the Window vertical Start Position.
                                            This parameter must be a number between Min_Data = 0x000
                      and Max_Data = 0x7FF. */

  uint32_t WindowY1;                   /*!< Configures the Window vertical Stop Position.
                                            This parameter must be a number between Min_Data = 0x0000
                      and Max_Data = 0x7FF. */

  uint32_t PixelFormat;                /*!< Specifies the pixel format.
                                            This parameter can be one of value of @ref LTDC_Pixelformat */

  uint32_t Alpha;                      /*!< Specifies the constant alpha used for blending.
                                            This parameter must be a number between Min_Data = 0x00
                      and Max_Data = 0xFF. */

  uint32_t Alpha0;                     /*!< Configures the default alpha value.
                                            This parameter must be a number between Min_Data = 0x00
                      and Max_Data = 0xFF. */

  uint32_t BlendingFactor1;            /*!< Select the blending factor 1.
                                            This parameter can be one of value of @ref LTDC_BlendingFactor1 */

  uint32_t BlendingFactor2;            /*!< Select the blending factor 2.
                                            This parameter can be one of value of @ref LTDC_BlendingFactor2 */

  uint32_t FBStartAdress;              /*!< Configures the color frame buffer address */

  uint32_t ImageWidth;                 /*!< Configures the color frame buffer line length.
                                            This parameter must be a number between Min_Data = 0x0000
                      and Max_Data = 0x1FFF. */

  uint32_t ImageHeight;                /*!< Specifies the number of line in frame buffer.
                                            This parameter must be a number between Min_Data = 0x000
                      and Max_Data = 0x7FF. */

  LTDC_ColorTypeDef   Backcolor;       /*!< Configures the layer background color. */

  uint8_t BlendingOrder;               /*!< Select the blending order.
                                                         This parameter can be one of between
                             Min_Data = 0x00 and Max_Data = 0x0F. */

  uint8_t BurstLength;                   /*!< Select the burst length.
                                                         This parameter must be a number between
                             Min_Data = 0x00 and Max_Data = 0x10. */
  LTDC_PlanarTypeDef   Planar;     /*!< Configures the planar or semiplanar buffer. */

  uint32_t HorMirrorEn;                /*!< Horizontal mirroring Enable. */

  uint32_t VertMirrorEn;               /*!< Vertical mirroring Enable. */

  LTDC_AuxiliaryTypeDef AuxiliaryFB;   /*!< Configures auxiliary frame buffers */

  LTDC_ScalerTypeDef Scaler;           /*!< Configure the scaler. */

  LTDC_ConversionTypeDef Conversion;           /*!< Configure the conversion YCbCr to RGB. */
} LTDC_LayerCfgTypeDef;

/**
  * @brief  HAL LTDC State structures definition
  */
typedef enum
{
  HAL_LTDC_STATE_RESET             = 0x00U,    /*!< LTDC not yet initialized or disabled */
  HAL_LTDC_STATE_READY             = 0x01U,    /*!< LTDC initialized and ready for use   */
  HAL_LTDC_STATE_BUSY              = 0x02U,    /*!< LTDC internal process is ongoing     */
  HAL_LTDC_STATE_TIMEOUT           = 0x03U,    /*!< LTDC Timeout state                   */
  HAL_LTDC_STATE_ERROR             = 0x04U     /*!< LTDC state error                     */
} HAL_LTDC_StateTypeDef;

/**
  * @brief  LTDC handle Structure definition
  */
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
typedef struct __LTDC_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
{
  LTDC_TypeDef                *Instance;                /*!< LTDC Register base address                */

  LTDC_InitTypeDef            Init;                     /*!< LTDC parameters                           */

  LTDC_LayerCfgTypeDef        LayerCfg[MAX_LAYER];      /*!< LTDC Layers parameters                    */

  HAL_LockTypeDef             Lock;                     /*!< LTDC Lock                                 */

  __IO HAL_LTDC_StateTypeDef  State;                    /*!< LTDC state                                */

  __IO uint32_t               ErrorCode;                /*!< LTDC Error code                           */

#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
  void (* LineEventCallback)(struct __LTDC_HandleTypeDef *hltdc);     /*!< LTDC Line Event Callback    */
  void (* ReloadEventCallback)(struct __LTDC_HandleTypeDef *hltdc);   /*!< LTDC Reload Event Callback  */
  void (* ErrorCallback)(struct __LTDC_HandleTypeDef *hltdc);         /*!< LTDC Error Callback         */

  void (* SecureLineEventCallback)(struct __LTDC_HandleTypeDef *hltdc);     /*!< LTDC Line Event Callback    */
  void (* SecureReloadEventCallback)(struct __LTDC_HandleTypeDef *hltdc);   /*!< LTDC Reload Event Callback  */
  void (* SecureErrorCallback)(struct __LTDC_HandleTypeDef *hltdc);         /*!< LTDC Error Callback         */

  void (* MspInitCallback)(struct __LTDC_HandleTypeDef *hltdc);       /*!< LTDC Msp Init callback      */
  void (* MspDeInitCallback)(struct __LTDC_HandleTypeDef *hltdc);     /*!< LTDC Msp DeInit callback    */

#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */


} LTDC_HandleTypeDef;

#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL LTDC Callback ID enumeration definition
  */
typedef enum
{
  HAL_LTDC_MSPINIT_CB_ID              = 0x00U,    /*!< LTDC MspInit callback ID       */
  HAL_LTDC_MSPDEINIT_CB_ID            = 0x01U,    /*!< LTDC MspDeInit callback ID     */

  HAL_LTDC_LINE_EVENT_CB_ID           = 0x02U,    /*!< LTDC Line Event Callback ID    */
  HAL_LTDC_RELOAD_EVENT_CB_ID         = 0x03U,    /*!< LTDC Reload Callback ID        */
  HAL_LTDC_ERROR_CB_ID                = 0x04U,     /*!< LTDC Error Callback ID         */
  HAL_LTDC_SECURE_LINE_EVENT_CB_ID    = 0x05U,    /*!< LTDC Secure Line Event Callback ID    */
  HAL_LTDC_SECURE_RELOAD_EVENT_CB_ID  = 0x06U,    /*!< LTDC Secure Reload Callback ID        */
  HAL_LTDC_SECURE_ERROR_CB_ID         = 0x07U     /*!< LTDC Secure Error Callback ID         */
} HAL_LTDC_CallbackIDTypeDef;

/**
  * @brief  HAL LTDC Callback pointer definition
  */
typedef  void (*pLTDC_CallbackTypeDef)(LTDC_HandleTypeDef *hltdc);  /*!< pointer to an LTDC callback function */

#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup LTDC_Exported_Constants LTDC Exported Constants
  * @{
  */

/** @defgroup LTDC_Error_Code LTDC Error Code
  * @{
  */
#define HAL_LTDC_ERROR_NONE               0x00000000U   /*!< LTDC No error             */
#define HAL_LTDC_ERROR_TE                 0x00000001U   /*!< LTDC Transfer error       */
#define HAL_LTDC_ERROR_FU                 0x00000002U   /*!< LTDC FIFO Underrun        */
#define HAL_LTDC_ERROR_UK                 0x00000003U   /*!< LTDC FIFO underrun killing  */
#define HAL_LTDC_ERROR_CRC                0x00000004U   /*!< LTDC CRC error              */
#define HAL_LTDC_ERROR_FUR                0x00000005U   /*!< LTDC FIFO inderrun rotation */
#define HAL_LTDC_ERROR_TIMEOUT            0x00000020U   /*!< LTDC Timeout error        */
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
#define  HAL_LTDC_ERROR_INVALID_CALLBACK  0x00000040U   /*!< LTDC Invalid Callback error  */
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup LTDC_Layer LTDC Layer
  * @{
  */
#define LTDC_LAYER_1                      0x00000000U   /*!< LTDC Layer 1 */
#define LTDC_LAYER_2                      0x00000001U   /*!< LTDC Layer 2 */

#define LTDC_LAYER_3                      0x00000002U   /*!< LTDC Layer 3 */
/**
  * @}
  */

/** @defgroup LTDC_HS_POLARITY LTDC HS POLARITY
  * @{
  */
#define LTDC_HSPOLARITY_AL                0x00000000U   /*!< Horizontal Synchronization is active low. */
#define LTDC_HSPOLARITY_AH                LTDC_GCR_HSPOL            /*!< Horizontal Synchronization is active high. */
/**
  * @}
  */

/** @defgroup LTDC_VS_POLARITY LTDC VS POLARITY
  * @{
  */
#define LTDC_VSPOLARITY_AL                0x00000000U   /*!< Vertical Synchronization is active low. */
#define LTDC_VSPOLARITY_AH                LTDC_GCR_VSPOL            /*!< Vertical Synchronization is active high. */
/**
  * @}
  */

/** @defgroup LTDC_DE_POLARITY LTDC DE POLARITY
  * @{
  */
#define LTDC_DEPOLARITY_AL                0x00000000U   /*!< Data Enable, is active low. */
#define LTDC_DEPOLARITY_AH                LTDC_GCR_DEPOL            /*!< Data Enable, is active high. */
/**
  * @}
  */

/** @defgroup LTDC_PC_POLARITY LTDC PC POLARITY
  * @{
  */
#define LTDC_PCPOLARITY_IPC               0x00000000U   /*!< input pixel clock. */
#define LTDC_PCPOLARITY_IIPC              LTDC_GCR_PCPOL            /*!< inverted input pixel clock. */
/**
  * @}
  */

/** @defgroup LTDC_SYNC LTDC SYNC
  * @{
  */
#define LTDC_HORIZONTALSYNC               (LTDC_SSCR_HSW >> 16U)    /*!< Horizontal synchronization width. */
#define LTDC_VERTICALSYNC                 LTDC_SSCR_VSH             /*!< Vertical synchronization height. */
/**
  * @}
  */

/** @defgroup LTDC_BACK_COLOR LTDC BACK COLOR
  * @{
  */
#define LTDC_COLOR                        0x000000FFU   /*!< Color mask */
/**
  * @}
  */

/** @defgroup LTDC_BlendingFactor1 LTDC Blending Factor1
  * @{
  */
#define LTDC_BLENDING_FACTOR1_CA          0x00000400U   /*!< Blending factor : Cte Alpha */
#define LTDC_BLENDING_FACTOR1_PAxCA       0x00000600U   /*!< Blending factor : Cte Alpha x Pixel Alpha*/
/**
  * @}
  */

/** @defgroup LTDC_BlendingFactor2 LTDC Blending Factor2
  * @{
  */
#define LTDC_BLENDING_FACTOR2_CA          0x00000005U   /*!< Blending factor : Cte Alpha */
#define LTDC_BLENDING_FACTOR2_PAxCA       0x00000007U   /*!< Blending factor : Cte Alpha x Pixel Alpha*/
/**
  * @}
  */

/** @defgroup LTDC_Pixelformat LTDC Pixel format
  * @{
  */
#define LTDC_PIXEL_FORMAT_ARGB8888        0x00000000U   /*!< ARGB8888 LTDC pixel format             */
#define LTDC_PIXEL_FORMAT_ABGR8888        0x00000001U   /*!< ABGR8888 LTDC pixel format             */
#define LTDC_PIXEL_FORMAT_RGBA8888        0x00000002U   /*!< RGBA8888 LTDC pixel format             */
#define LTDC_PIXEL_FORMAT_BGRA8888        0x00000003U   /*!< BGRA8888 LTDC pixel format             */
#define LTDC_PIXEL_FORMAT_RGB565          0x00000004U   /*!< RGB565 LTDC pixel format               */
#define LTDC_PIXEL_FORMAT_BGR565          0x00000005U   /*!< RGB565 LTDC pixel format               */
#define LTDC_PIXEL_FORMAT_RGB888          0x00000006U   /*!< RGB888 LTDC pixel format               */
#define LTDC_PIXEL_FORMAT_ARGB1555        0x00000007U   /*!< ARGB1555 LTDC pixel format             */
#define LTDC_PIXEL_FORMAT_ARGB4444        0x00000008U   /*!< ARGB4444 LTDC pixel format             */
#define LTDC_PIXEL_FORMAT_L8              0x00000009U   /*!< L8 LTDC pixel format                   */
#define LTDC_PIXEL_FORMAT_AL44            0x0000000AU   /*!< AL44 LTDC pixel format                 */
#define LTDC_PIXEL_FORMAT_AL88            0x0000000BU   /*!< AL88 LTDC pixel format                 */
#define LTDC_PIXEL_FORMAT_UYVY            0x0000000CU   /*!< UYVY Interleave LTDC pixel format      */
#define LTDC_PIXEL_FORMAT_VYUY            0x0000000DU   /*!< VYUY Interleave LTDC pixel format      */
#define LTDC_PIXEL_FORMAT_YUYV            0x0000000EU   /*!< YUYV Interleave LTDC pixel format      */
#define LTDC_PIXEL_FORMAT_YVYU            0x0000000FU   /*!< YVYU Interleave LTDC pixel format      */
#define LTDC_PIXEL_FORMAT_NV12            0x00000010U   /*!< NV12 Semi Planar LTDC pixel format     */
#define LTDC_PIXEL_FORMAT_NV21            0x00000011U   /*!< NV21 Semi Planar LTDC pixel format     */
#define LTDC_PIXEL_FORMAT_YUV420          0x00000012U   /*!< YUV420 Full Planar LTDC pixel format   */
#define LTDC_PIXEL_FORMAT_YVU420          0x00000013U   /*!< YVU420 Full Planar LTDC pixel format   */
/**
  * @}
  */

/** @defgroup LTDC_Alpha LTDC Alpha
  * @{
  */
#define LTDC_ALPHA                        LTDC_LxCACR_CONSTA        /*!< LTDC Constant Alpha mask */
/**
  * @}
  */

/** @defgroup LTDC_LAYER_Config LTDC LAYER Config
  * @{
  */
#define LTDC_STOPPOSITION                 (LTDC_LxWHPCR_WHSPPOS >> 16U) /*!< LTDC Layer stop position  */
#define LTDC_STARTPOSITION                LTDC_LxWHPCR_WHSTPOS          /*!< LTDC Layer start position */

#define LTDC_COLOR_FRAME_BUFFER           LTDC_LxCFBLR_CFBLL            /*!< LTDC Layer Line length    */
#define LTDC_LINE_NUMBER                  LTDC_LxCFBLNR_CFBLNBR         /*!< LTDC Layer Line number    */
/**
  * @}
  */

/** @defgroup LTDC_Interrupts LTDC Interrupts
  * @{
  */
#define LTDC_IT_LI                        LTDC_IER_LIE              /*!< LTDC Line Interrupt            */
#define LTDC_IT_FU                        LTDC_IER_FUWIE            /*!< LTDC FIFO Underrun Interrupt   */
#define LTDC_IT_TE                        LTDC_IER_TERRIE           /*!< LTDC Transfer Error Interrupt  */
#define LTDC_IT_RR                        LTDC_IER_RRIE             /*!< LTDC Register Reload Interrupt */
#define LTDC_IT_UK                        LTDC_IER_FUKIE            /*!< LTDC FIFO Underrun Killing Interrupt */
#define LTDC_IT_CR                        LTDC_IER_CRCIE            /*!< LTDC CRC error Interrupt */
#define LTDC_IT_UR                        LTDC_IER_FURIE            /*!< LTDC FIFIO Underrun at rotation Interrupt */
/**
  * @}
  */

/** @defgroup LTDC_Flags LTDC Flags
  * @{
  */
#define LTDC_FLAG_LI                      LTDC_ISR_LIF              /*!< LTDC Line Interrupt Flag            */
#define LTDC_FLAG_FU                      LTDC_ISR_FUWIF            /*!< LTDC FIFO Underrun interrupt Flag   */
#define LTDC_FLAG_TE                      LTDC_ISR_TERRIF           /*!< LTDC Transfer Error interrupt Flag  */
#define LTDC_FLAG_RR                      LTDC_ISR_RRIF             /*!< LTDC Register Reload interrupt Flag */
#define LTDC_FLAG_UK                      LTDC_ISR_FUKIF            /*!< LTDC FIFO Underrun Killing Interrupt */
#define LTDC_FLAG_CR                      LTDC_ISR_CRCIF            /*!< LTDC CRC error Interrupt */
#define LTDC_FLAG_UR                      LTDC_ISR_FURIF            /*!< LTDC FIFIO Underrun at rotation Interrupt */
/**
  * @}
  */

/** @defgroup LTDC_Reload_Type LTDC Reload Type
  * @{
  */
#define LTDC_RELOAD_IMMEDIATE             LTDC_SRCR_IMR             /*!< Immediate Reload */
#define LTDC_RELOAD_VERTICAL_BLANKING     LTDC_SRCR_VBR             /*!< Vertical Blanking Reload */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LTDC_Exported_Macros LTDC Exported Macros
  * @{
  */

/** @brief Reset LTDC handle state.
  * @param  __HANDLE__  LTDC handle
  * @retval None
  */
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
#define __HAL_LTDC_RESET_HANDLE_STATE(__HANDLE__) do{                                                  \
                                                      (__HANDLE__)->State = HAL_LTDC_STATE_RESET;     \
                                                      (__HANDLE__)->MspInitCallback = NULL;           \
                                                      (__HANDLE__)->MspDeInitCallback = NULL;         \
                                                    } while(0)
#else
#define __HAL_LTDC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_LTDC_STATE_RESET)
#endif /*USE_HAL_LTDC_REGISTER_CALLBACKS */

/**
  * @brief  Enable the LTDC.
  * @param  __HANDLE__  LTDC handle
  * @retval None.
  */
#define __HAL_LTDC_ENABLE(__HANDLE__)    ((__HANDLE__)->Instance->GCR |= LTDC_GCR_LTDCEN)

/**
  * @brief  Disable the LTDC.
  * @param  __HANDLE__  LTDC handle
  * @retval None.
  */
#define __HAL_LTDC_DISABLE(__HANDLE__)   ((__HANDLE__)->Instance->GCR &= ~(LTDC_GCR_LTDCEN))

/**
  * @brief  Enable the LTDC Layer.
  * @param  __HANDLE__  LTDC handle
  * @param  __LAYER__   Specify the layer to be enabled.
  *                     This parameter can be LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1) or LTDC_LAYER_3 (2).
  * @retval None.
  */
#define __HAL_LTDC_LAYER_ENABLE(__HANDLE__, __LAYER__)  ((LTDC_LAYER((__HANDLE__), (__LAYER__)))->CR \
                                                         |= (uint32_t)LTDC_LxCR_LEN)

/**
  * @brief  Disable the LTDC Layer.
  * @param  __HANDLE__  LTDC handle
  * @param  __LAYER__   Specify the layer to be disabled.
  *                     This parameter can be LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1) or LTDC_LAYER_3 (2).
  * @retval None.
  */
#define __HAL_LTDC_LAYER_DISABLE(__HANDLE__, __LAYER__) ((LTDC_LAYER((__HANDLE__), (__LAYER__)))->CR \
                                                         &= ~(uint32_t)LTDC_LxCR_LEN)

/**
  * @brief  Reload immediately all LTDC Layers.
  * @param  __HANDLE__  LTDC handle
  * @retval None.
  */
#define __HAL_LTDC_RELOAD_IMMEDIATE_CONFIG(__HANDLE__)  ((__HANDLE__)->Instance->SRCR |= LTDC_SRCR_IMR)

/**
  * @brief  Reload during vertical blanking period all LTDC Layers.
  * @param  __HANDLE__  LTDC handle
  * @retval None.
  */
#define __HAL_LTDC_VERTICAL_BLANKING_RELOAD_CONFIG(__HANDLE__)  ((__HANDLE__)->Instance->SRCR |= LTDC_SRCR_VBR)

/* Interrupt & Flag management */
/**
  * @brief  Get the LTDC pending flags.
  * @param  __HANDLE__  LTDC handle
  * @param  __FLAG__    Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_FLAG_LI: Line Interrupt flag
  *            @arg LTDC_FLAG_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_FLAG_TE: Transfer Error interrupt flag
  *            @arg LTDC_FLAG_RR: Register Reload Interrupt Flag
  *            @arg LTDC_FLAG_UK: LTDC FIFO Underrun Killing Interrupt flag
  *            @arg LTDC_FLAG_CR: LTDC CRC error Interrupt flag
  *            @arg LTDC_FLAG_UR: LTDC FIFIO Underrun at rotation Interrupt flag
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_LTDC_GET_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ISR & (__FLAG__))

/**
  * @brief  Clears the LTDC pending flags.
  * @param  __HANDLE__  LTDC handle
  * @param  __FLAG__    Specify the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_FLAG_LI: Line Interrupt flag
  *            @arg LTDC_FLAG_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_FLAG_TE: Transfer Error interrupt flag
  *            @arg LTDC_FLAG_RR: Register Reload Interrupt Flag
  *            @arg LTDC_FLAG_UK: LTDC FIFO Underrun Killing Interrupt flag
  *            @arg LTDC_FLAG_CR: LTDC CRC error Interrupt flag
  *            @arg LTDC_FLAG_UR: LTDC FIFIO Underrun at rotation Interrupt flag
  * @retval None
  */
#define __HAL_LTDC_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = (__FLAG__))

/**
  * @brief  Enables the specified LTDC interrupts.
  * @param  __HANDLE__  LTDC handle
  * @param __INTERRUPT__ Specify the LTDC interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_IT_LI: Line Interrupt flag
  *            @arg LTDC_IT_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_IT_TE: Transfer Error interrupt flag
  *            @arg LTDC_IT_RR: Register Reload Interrupt Flag
  *            @arg LTDC_IT_UK: LTDC FIFO Underrun Killing Interrupt flag
  *            @arg LTDC_IT_CR: LTDC CRC error Interrupt flag
  *            @arg LTDC_IT_UR: LTDC FIFIO Underrun at rotation Interrupt flag
  * @retval None
  */
#define __HAL_LTDC_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER |= (__INTERRUPT__))

/**
  * @brief  Disables the specified LTDC interrupts.
  * @param  __HANDLE__  LTDC handle
  * @param __INTERRUPT__ Specify the LTDC interrupt sources to be disabled.
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_IT_LI: Line Interrupt flag
  *            @arg LTDC_IT_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_IT_TE: Transfer Error interrupt flag
  *            @arg LTDC_IT_RR: Register Reload Interrupt Flag
  *            @arg LTDC_IT_UK: LTDC FIFO Underrun Killing Interrupt flag
  *            @arg LTDC_IT_CR: LTDC CRC error Interrupt flag
  *            @arg LTDC_IT_UR: LTDC FIFIO Underrun at rotation Interrupt flag
  * @retval None
  */
#define __HAL_LTDC_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified LTDC interrupt has occurred or not.
  * @param  __HANDLE__  LTDC handle
  * @param __INTERRUPT__ Specify the LTDC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg LTDC_IT_LI: Line Interrupt flag
  *            @arg LTDC_IT_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_IT_TE: Transfer Error interrupt flag
  *            @arg LTDC_IT_RR: Register Reload Interrupt Flag
  * @retval The state of INTERRUPT (SET or RESET).
  */
#define __HAL_LTDC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER & (__INTERRUPT__))

/**
  * @brief  Get the Secure LTDC pending flags.
  * @param  __HANDLE__  LTDC handle
  * @param  __FLAG__    Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_FLAG_LI: Line Interrupt flag
  *            @arg LTDC_FLAG_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_FLAG_TE: Transfer Error interrupt flag
  *            @arg LTDC_FLAG_RR: Register Reload Interrupt Flag
  *            @arg LTDC_FLAG_UK: LTDC FIFO Underrun Killing Interrupt flag
  *            @arg LTDC_FLAG_CR: LTDC CRC error Interrupt flag
  *            @arg LTDC_FLAG_UR: LTDC FIFIO Underrun at rotation Interrupt flag
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_LTDC_GET_SECURE_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ISR2 & (__FLAG__))

/**
  * @brief  Clears the LTDC Secure pending flags.
  * @param  __HANDLE__  LTDC handle
  * @param  __FLAG__    Specify the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_FLAG_LI: Line Interrupt flag
  *            @arg LTDC_FLAG_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_FLAG_TE: Transfer Error interrupt flag
  *            @arg LTDC_FLAG_RR: Register Reload Interrupt Flag
  *            @arg LTDC_FLAG_UK: LTDC FIFO Underrun Killing Interrupt flag
  *            @arg LTDC_FLAG_CR: LTDC CRC error Interrupt flag
  *            @arg LTDC_FLAG_UR: LTDC FIFIO Underrun at rotation Interrupt flag
  * @retval None
  */
#define __HAL_LTDC_CLEAR_SECURE_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR2 = (__FLAG__))

/**
  * @brief  Enables the specified LTDC Secure interrupts.
  * @param  __HANDLE__  LTDC handle
  * @param __INTERRUPT__ Specify the LTDC interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_IT_LI: Line Interrupt flag
  *            @arg LTDC_IT_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_IT_TE: Transfer Error interrupt flag
  *            @arg LTDC_IT_RR: Register Reload Interrupt Flag
  *            @arg LTDC_IT_UK: LTDC FIFO Underrun Killing Interrupt flag
  *            @arg LTDC_IT_CR: LTDC CRC error Interrupt flag
  *            @arg LTDC_IT_UR: LTDC FIFIO Underrun at rotation Interrupt flag
  * @retval None
  */
#define __HAL_LTDC_ENABLE_SECURE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER2 |= (__INTERRUPT__))

/**
  * @brief  Disables the specified LTDC Secure interrupts.
  * @param  __HANDLE__  LTDC handle
  * @param __INTERRUPT__ Specify the LTDC interrupt sources to be disabled.
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_IT_LI: Line Interrupt flag
  *            @arg LTDC_IT_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_IT_TE: Transfer Error interrupt flag
  *            @arg LTDC_IT_RR: Register Reload Interrupt Flag
  *            @arg LTDC_IT_UK: LTDC FIFO Underrun Killing Interrupt flag
  *            @arg LTDC_IT_CR: LTDC CRC error Interrupt flag
  *            @arg LTDC_IT_UR: LTDC FIFIO Underrun at rotation Interrupt flag
  * @retval None
  */
#define __HAL_LTDC_DISABLE_SECURE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER2 &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified LTDC Secure interrupt has occurred or not.
  * @param  __HANDLE__  LTDC handle
  * @param __INTERRUPT__ Specify the LTDC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg LTDC_IT_LI: Line Interrupt flag
  *            @arg LTDC_IT_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_IT_TE: Transfer Error interrupt flag
  *            @arg LTDC_IT_RR: Register Reload Interrupt Flag
  *            @arg LTDC_IT_UK: LTDC FIFO Underrun Killing Interrupt flag
  *            @arg LTDC_IT_CR: LTDC CRC error Interrupt flag
  *            @arg LTDC_IT_UR: LTDC FIFIO Underrun at rotation Interrupt flag
  * @retval The state of INTERRUPT (SET or RESET).
  */
#define __HAL_LTDC_GET_SECURE_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER2 & (__INTERRUPT__))
/**
  * @}
  */

/* Include LTDC HAL Extension module */
#include "stm32mp2xx_hal_ltdc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup LTDC_Exported_Functions
  * @{
  */
/** @addtogroup LTDC_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_LTDC_Init(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_DeInit(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_ErrorCallback(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_ReloadEventCallback(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_ProgramSecureLineEvent(LTDC_HandleTypeDef *hltdc, uint32_t Line);
void HAL_LTDC_Secure_ErrorCallback(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_Secure_LineEventCallback(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_Secure_ReloadEventCallback(LTDC_HandleTypeDef *hltdc);

/* Mirroring functions *****************************/
HAL_StatusTypeDef HAL_LTDC_EnableHMirror(LTDC_HandleTypeDef *hltdc, const LTDC_LayerCfgTypeDef *pLayerCfg,
                                         uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableHMirror(LTDC_HandleTypeDef *hltdc,
                                          const LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_EnableVMirror(LTDC_HandleTypeDef *hltdc, const LTDC_LayerCfgTypeDef *pLayerCfg,
                                         uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableVMirror(LTDC_HandleTypeDef *hltdc, const LTDC_LayerCfgTypeDef *pLayerCfg,
                                          uint32_t LayerIdx);

/* Single frame mode software trigger functions *****************************/
HAL_StatusTypeDef HAL_LTDC_EnableSFSWTrigger(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_DisableSFSWTrigger(LTDC_HandleTypeDef *hltdc);

/* Callbacks Register/UnRegister functions  ***********************************/
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_LTDC_RegisterCallback(LTDC_HandleTypeDef *hltdc, HAL_LTDC_CallbackIDTypeDef CallbackID,
                                            pLTDC_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_LTDC_UnRegisterCallback(LTDC_HandleTypeDef *hltdc, HAL_LTDC_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup LTDC_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/
void  HAL_LTDC_IRQHandler(LTDC_HandleTypeDef *hltdc);
void  HAL_LTDC_Secure_IRQHandler(LTDC_HandleTypeDef *hltdc);
/**
  * @}
  */

/** @addtogroup LTDC_Exported_Functions_Group3
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_LTDC_ConfigLayer(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetWindowSize(LTDC_HandleTypeDef *hltdc, uint32_t XSize, uint32_t YSize, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetWindowPosition(LTDC_HandleTypeDef *hltdc, uint32_t X0, uint32_t Y0, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetPixelFormat(LTDC_HandleTypeDef *hltdc, uint32_t Pixelformat, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetAlpha(LTDC_HandleTypeDef *hltdc, uint32_t Alpha, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetAddress(LTDC_HandleTypeDef *hltdc, uint32_t Address, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetPitch(LTDC_HandleTypeDef *hltdc, uint32_t LinePitchInPixels, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_ConfigColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t RGBValue, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_ConfigCLUT(LTDC_HandleTypeDef *hltdc, const uint32_t *pCLUT, uint32_t CLUTSize,
                                      uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_EnableColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_EnableCLUT(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableCLUT(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_ProgramLineEvent(LTDC_HandleTypeDef *hltdc, uint32_t Line);
HAL_StatusTypeDef HAL_LTDC_EnableDither(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_DisableDither(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_Reload(LTDC_HandleTypeDef *hltdc, uint32_t ReloadType);
HAL_StatusTypeDef HAL_LTDC_Layer_Reload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx, uint32_t ReloadType);
HAL_StatusTypeDef HAL_LTDC_ConfigLayer_NoReload(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg,
                                                uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetWindowSize_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t XSize, uint32_t YSize,
                                                  uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetWindowPosition_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t X0, uint32_t Y0,
                                                      uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetPixelFormat_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Pixelformat, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetAlpha_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Alpha, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetAddress_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Address, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetPitch_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LinePitchInPixels, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_ConfigColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t RGBValue, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_EnableColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_EnableCLUT_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableCLUT_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
uint32_t HAL_LTDC_GetLinePosition(const LTDC_HandleTypeDef *hltdc);
uint32_t HAL_LTDC_GetPixelPosition(const LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_EnableGamma(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_DisableGamma(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_ConfigGamma(LTDC_HandleTypeDef *hltdc, LTDC_GammaTypeDef *pGamma, uint32_t GammaSize);

HAL_StatusTypeDef HAL_LTDC_SetExpectedCRC(LTDC_HandleTypeDef *hltdc, uint32_t ExpectedCrc);
HAL_StatusTypeDef HAL_LTDC_EnableCRC(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_DisableCRC(LTDC_HandleTypeDef *hltdc);
uint32_t HAL_LTDC_GetCRC(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_EnableColorBlending(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableColorBlending(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);

/**
  * @}
  */

/** @addtogroup LTDC_Exported_Functions_Group4
  * @{
  */
/* Peripheral State functions *************************************************/
HAL_LTDC_StateTypeDef HAL_LTDC_GetState(const LTDC_HandleTypeDef *hltdc);
uint32_t              HAL_LTDC_GetError(const LTDC_HandleTypeDef *hltdc);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup LTDC_Private_Macros LTDC Private Macros
  * @{
  */
#define LTDC_LAYER(__HANDLE__, __LAYER__)              ((LTDC_Layer_TypeDef *)((uint32_t)((\
                                                                               (uint32_t)((__HANDLE__)->Instance)) \
                                                                               + 0x100U + (0x100U*(__LAYER__)))))

#define IS_LTDC_LAYER(__LAYER__)                       ((__LAYER__) < MAX_LAYER)
#define IS_LTDC_HSPOL(__HSPOL__)                       (((__HSPOL__) == LTDC_HSPOLARITY_AL) ||\
                                                        ((__HSPOL__) == LTDC_HSPOLARITY_AH))
#define IS_LTDC_VSPOL(__VSPOL__)                       (((__VSPOL__) == LTDC_VSPOLARITY_AL) ||\
                                                        ((__VSPOL__) == LTDC_VSPOLARITY_AH))
#define IS_LTDC_DEPOL(__DEPOL__)                       (((__DEPOL__) == LTDC_DEPOLARITY_AL) ||\
                                                        ((__DEPOL__) ==  LTDC_DEPOLARITY_AH))
#define IS_LTDC_PCPOL(__PCPOL__)                       (((__PCPOL__) == LTDC_PCPOLARITY_IPC) ||\
                                                        ((__PCPOL__) ==  LTDC_PCPOLARITY_IIPC))
#define IS_LTDC_HSYNC(__HSYNC__)                       ((__HSYNC__)  <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_VSYNC(__VSYNC__)                       ((__VSYNC__)  <= LTDC_VERTICALSYNC)
#define IS_LTDC_AHBP(__AHBP__)                         ((__AHBP__)   <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_AVBP(__AVBP__)                         ((__AVBP__)   <= LTDC_VERTICALSYNC)
#define IS_LTDC_AAW(__AAW__)                           ((__AAW__)    <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_AAH(__AAH__)                           ((__AAH__)    <= LTDC_VERTICALSYNC)
#define IS_LTDC_TOTALW(__TOTALW__)                     ((__TOTALW__) <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_TOTALH(__TOTALH__)                     ((__TOTALH__) <= LTDC_VERTICALSYNC)
#define IS_LTDC_BLUEVALUE(__BBLUE__)                   ((__BBLUE__)  <= LTDC_COLOR)
#define IS_LTDC_GREENVALUE(__BGREEN__)                 ((__BGREEN__) <= LTDC_COLOR)
#define IS_LTDC_REDVALUE(__BRED__)                     ((__BRED__)   <= LTDC_COLOR)
#define IS_LTDC_BLENDING_FACTOR1(__BLENDING_FACTOR1__) (((__BLENDING_FACTOR1__) == LTDC_BLENDING_FACTOR1_CA) || \
                                                        ((__BLENDING_FACTOR1__) == LTDC_BLENDING_FACTOR1_PAxCA))
#define IS_LTDC_BLENDING_FACTOR2(__BLENDING_FACTOR1__) (((__BLENDING_FACTOR1__) == LTDC_BLENDING_FACTOR2_CA) || \
                                                        ((__BLENDING_FACTOR1__) == LTDC_BLENDING_FACTOR2_PAxCA))
#define IS_LTDC_PIXEL_FORMAT(__PIXEL_FORMAT__)         (((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_ARGB8888)   || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_ABGR8888)   || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_RGBA8888)   || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_BGRA8888)   || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_RGB565)     || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_BGR565)     || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_RGB888)     || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_ARGB1555)   || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_ARGB4444)   || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_L8)         || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_AL44)       || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_AL88)       || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_UYVY)       || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_VYUY)       || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_YUYV)       || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_YVYU)       || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_NV12)       || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_NV21)       || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_YUV420)     || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_YVU420))
#define IS_LTDC_ALPHA(__ALPHA__)                       ((__ALPHA__) <= LTDC_ALPHA)
#define IS_LTDC_HCONFIGST(__HCONFIGST__)               ((__HCONFIGST__) <= LTDC_STARTPOSITION)
#define IS_LTDC_HCONFIGSP(__HCONFIGSP__)               ((__HCONFIGSP__) <= LTDC_STOPPOSITION)
#define IS_LTDC_VCONFIGST(__VCONFIGST__)               ((__VCONFIGST__) <= LTDC_STARTPOSITION)
#define IS_LTDC_VCONFIGSP(__VCONFIGSP__)               ((__VCONFIGSP__) <= LTDC_STOPPOSITION)
#define IS_LTDC_CFBP(__CFBP__)                         ((__CFBP__) <= LTDC_COLOR_FRAME_BUFFER)
#define IS_LTDC_CFBLL(__CFBLL__)                       ((__CFBLL__) <= LTDC_COLOR_FRAME_BUFFER)
#define IS_LTDC_CFBLNBR(__CFBLNBR__)                   ((__CFBLNBR__) <= LTDC_LINE_NUMBER)
#define IS_LTDC_LIPOS(__LIPOS__)                       ((__LIPOS__) <= 0x7FFU)
#define IS_LTDC_RELOAD(__RELOADTYPE__)                 (((__RELOADTYPE__) == LTDC_RELOAD_IMMEDIATE) ||\
                                                        ((__RELOADTYPE__) == LTDC_RELOAD_VERTICAL_BLANKING))
#define IS_LTDC_EXPCRC(__EXPCRC__)                     ((__EXPCRC__) <= 0xFFU)
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup LTDC_Private_Functions LTDC Private Functions
  * @{
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

#endif /* LTDC */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_HAL_LTDC_H */
