/**
  ******************************************************************************
  * @file    stm32g5xx_hal_fmac.h
  * @brief   Header for stm32g5xx_hal_fmac.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G5XX_HAL_FMAC_H
#define STM32G5XX_HAL_FMAC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_fmac.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

#if defined(FMAC1) || defined(FMAC2)
/** @defgroup FMAC FMAC
  * @{
  */

/** @defgroup FMAC_Exported_Constants HAL FMAC Constants
  * @{
  */

/** @defgroup FMAC_Error_Codes FMAC Error code
  * @{
  */
#define HAL_FMAC_ERROR_NONE            0U              /*!< No error            */
#define HAL_FMAC_ERROR_SATURATION      FMAC_CR_SATIEN  /*!< Saturation error    */
#define HAL_FMAC_ERROR_UNDERFLOW       FMAC_CR_UNFLIEN /*!< Underflow error     */
#define HAL_FMAC_ERROR_OVERFLOW        FMAC_CR_OVFLIEN /*!< Overflow error      */
#define HAL_FMAC_ERROR_DMA             (1UL << 30U)    /*!< DMA error           */
#define HAL_FMAC_ERROR_PRELOAD_TIMEOUT (1UL << 31U)    /*!< FIFO preload timout */
/**
  * @}
  */

/** @defgroup FMAC_Filter_Optional_Interruption FMAC filter optional interrupt
  * @{
  */
#define HAL_FMAC_OPT_IT_FILTER_NONE             0UL        /*!< All optional IT are disabled                  */
#define HAL_FMAC_OPT_IT_FILTER_SATURATION_ERROR (1UL << 0) /*!< Enable optional IT saturation error detection */
/**
  * @}
  */

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
/** @defgroup FMAC_X1_DMA_Optional_Interrupt FMAC X1 DMA optional interrupt
  * @{
  */
#define HAL_FMAC_OPT_DMA_X1_IT_NONE HAL_DMA_OPT_IT_NONE /*!< All optional IT are disabled     */
#define HAL_FMAC_OPT_DMA_X1_IT_HT   HAL_DMA_OPT_IT_HT   /*!< Enable optional IT half complete */
/**
  * @}
  */

/** @defgroup FMAC_Y_DMA_Optional_Interrupt FMAC Y DMA optional interrupt
  * @{
  */
#define HAL_FMAC_OPT_DMA_Y_IT_NONE HAL_DMA_OPT_IT_NONE /*!< All optional IT are disabled     */
#define HAL_FMAC_OPT_DMA_Y_IT_HT   HAL_DMA_OPT_IT_HT   /*!< Enable optional IT half complete */
/**
  * @}
  */
#endif  /* USE_HAL_FMAC_DMA */

/**
  * @}
  */

/** @defgroup FMAC_Exported_Types HAL FMAC Types
  * @{
  */

/**
  * @brief HAL FMAC instance
  */
typedef enum
{
  HAL_FMAC1 = FMAC1_BASE, /*!< HAL FMAC1 Peripheral instance */
#if defined(FMAC2)
  HAL_FMAC2 = FMAC2_BASE, /*!< HAL FMAC2 Peripheral instance */
#endif /* FMAC2 */
}
hal_fmac_t;

/**
  * @brief HAL State structure definition
  */
typedef enum
{
  HAL_FMAC_STATE_RESET          = (0UL),       /*!< Not yet Initialized                     */
  HAL_FMAC_STATE_INIT           = (1UL << 31), /*!< Initialized but not yet configured      */
  HAL_FMAC_STATE_IDLE           = (1UL << 30), /*!< Initialized and a global config applied */
  HAL_FMAC_STATE_ACTIVE_PRELOAD = (1UL << 27), /*!< Preload is ongoing                      */
  HAL_FMAC_STATE_ACTIVE_FILTER  = (1UL << 26)  /*!< Filter is ongoing                       */
} hal_fmac_state_t;

/**
  * @brief HAL X1 state structure definition
  */
typedef enum
{
  HAL_FMAC_STATE_X1_RESET        = (1UL << 31), /*!< Not yet Initialized                     */
  HAL_FMAC_STATE_X1_IDLE         = (1UL << 30), /*!< Initialized and a global config applied */
  HAL_FMAC_STATE_X1_ACTIVE_WRITE = (1UL << 29)  /*!< Writing in X1                           */
} hal_fmac_x1_state_t;

/**
  * @brief HAL Y state structure definition
  */
typedef enum
{
  HAL_FMAC_STATE_Y_RESET       = (1UL << 31), /*!< Not yet Initialized                     */
  HAL_FMAC_STATE_Y_IDLE        = (1UL << 30), /*!< Initialized and a global config applied */
  HAL_FMAC_STATE_Y_ACTIVE_READ = (1UL << 29)  /*!< Reading from Y                          */
} hal_fmac_y_state_t;

/**
  * @brief FMAC Clip status definition
  */
typedef enum
{
  HAL_FMAC_CLIP_DISABLED = 0U, /*!< Clipping is disabled */
  HAL_FMAC_CLIP_ENABLED  = 1U  /*!< Clipping is enabled */
} hal_fmac_clip_status_t;

/**
  * @brief Watermark threshold for X1 buffer full flag or Y buffer empty flag
  */
typedef enum
{
  HAL_FMAC_WATERMARK_THRESHOLD_1 = LL_FMAC_WM_0_THRESHOLD_1, /*!< Threshold value is 1 half word */
  HAL_FMAC_WATERMARK_THRESHOLD_2 = LL_FMAC_WM_1_THRESHOLD_2, /*!< Threshold value is 2 half word */
  HAL_FMAC_WATERMARK_THRESHOLD_4 = LL_FMAC_WM_2_THRESHOLD_4, /*!< Threshold value is 4 half word */
  HAL_FMAC_WATERMARK_THRESHOLD_8 = LL_FMAC_WM_3_THRESHOLD_8  /*!< Threshold value is 8 half word */
} hal_fmac_watermark_threshold_t;

/**
  * @brief  FMAC buffer X1 of buffer Y Configuration Structure definition
  *         Note: the buffers can overlap or even coincide exactly.
  */
typedef struct
{
  uint8_t  base_half_word; /*!< Base address within the FMAC internal 16-bit memory (0x00 to 0xFF)       */
  uint8_t  size_half_word; /*!< Size of the 16-bit buffer including the optional headroom (0x00 to 0xFF) */
} hal_fmac_buffer_t;

/**
  * @brief  FMAC Filter Configuration Structure definition
  *         Note: the buffers can overlap or even coincide exactly.
  */
typedef struct
{
  hal_fmac_buffer_t x1_buf; /*!< X1 buffer : Sample input        */
  hal_fmac_buffer_t x2_buf; /*!< X2 buffer : Coefficient B and A */
  hal_fmac_buffer_t y_buf;  /*!< Y buffer : Sample Output        */
} hal_fmac_config_t;

/**
  * @brief  FMAC Preload x2_buf coefficient A and/or B preload value
  */
typedef struct
{
  int16_t *p_coeff_b;             /*!< Initialization of the coefficient vector B                        */
  int16_t *p_coeff_a;             /*!< [IIR only] Initialization of the coefficient vector A             */
  uint8_t coeff_b_size_half_word; /*!< Size of the coefficient vector B. It must be set to 0 if not used */
  uint8_t coeff_a_size_half_word; /*!< Size of the coefficient vector A. It must be set to 0 if not used */
} hal_fmac_preload_x2_t;

typedef struct hal_fmac_handle_s hal_fmac_handle_t; /*!< FMAC handle structure type */

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
typedef  void (*hal_fmac_cb_t)(hal_fmac_handle_t *hfmac); /*!< pointer to an FMAC callback function */
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */

/**
  * @brief FMAC handle structure definition
  */
struct hal_fmac_handle_s
{
  hal_fmac_t    instance;                 /*!< Peripheral instance                                  */
  const int16_t *p_input;                 /*!< Pointer to user input buffer used to send data to X1 */
  uint32_t      input_size_half_word;     /*!< Number of input elements remaining to write to X1    */
  int16_t       *p_output;                /*!< Pointer to user output buffer                        */
  uint32_t      output_size_half_word;    /*!< Number of output elements remaining to read from Y   */

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
  hal_dma_handle_t *hdma_x1;              /*!< X1 write or Preload write DMA handle parameters (exclusive) */
  hal_dma_handle_t *hdma_y;               /*!< Y read DMA handle parameters                                */
#endif /* USE_HAL_FMAC_DMA */

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hal_fmac_cb_t p_write_x1_cplt_cb;       /*!< Write X1 complete callback      */
  hal_fmac_cb_t p_read_y_cplt_cb;         /*!< Read Y complete callback        */
#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
  hal_fmac_cb_t p_write_x1_half_cplt_cb;  /*!< Write X1 half complete callback */
  hal_fmac_cb_t p_read_y_half_cplt_cb;    /*!< Read Y half complete callback   */
  hal_fmac_cb_t p_preload_cplt_cb;        /*!< Preload complete callback       */
#endif /* USE_HAL_FMAC_DMA */
  hal_fmac_cb_t p_error_cb;               /*!< Error callback                  */
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */

  volatile hal_fmac_state_t global_state; /*!< State related to filter handle management */
  volatile hal_fmac_x1_state_t x1_state;  /*!< State related to write operations into X1 */
  volatile hal_fmac_y_state_t y_state;    /*!< State related to read operations from Y   */

#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
  volatile uint32_t last_error_codes;     /*!< Errors limited to the last process
                                               This parameter can be a combination of @ref FMAC_Error_Codes */
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */

#if defined(USE_HAL_FMAC_USER_DATA) && (USE_HAL_FMAC_USER_DATA == 1)
  const void *p_user_data;                /*!< User data pointer */
#endif /* USE_HAL_FMAC_USER_DATA */
};

/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions HAL FMAC Functions
  * @{
  */

/** @defgroup FMAC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_FMAC_Init(hal_fmac_handle_t *hfmac, hal_fmac_t instance);
void HAL_FMAC_DeInit(hal_fmac_handle_t *hfmac);
hal_fmac_t HAL_FMAC_GetInstance(const hal_fmac_handle_t *hfmac);
FMAC_TypeDef *HAL_FMAC_GetLLInstance(const hal_fmac_handle_t *hfmac);
/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group2 FMAC configuration functions
  * @{
  */
/* Buffer global configuration */
hal_status_t HAL_FMAC_SetConfig(hal_fmac_handle_t *hfmac, const hal_fmac_config_t *p_config);
void HAL_FMAC_GetConfig(const hal_fmac_handle_t *hfmac, hal_fmac_config_t *p_config);

/* Threshold input buffer X1 and output buffer Y  */
hal_status_t HAL_FMAC_SetX1FullWatermark(hal_fmac_handle_t *hfmac, hal_fmac_watermark_threshold_t threshold);
hal_fmac_watermark_threshold_t HAL_FMAC_GetX1FullWatermark(const hal_fmac_handle_t *hfmac);
hal_status_t HAL_FMAC_SetYEmptyWatermark(hal_fmac_handle_t *hfmac, hal_fmac_watermark_threshold_t threshold);
hal_fmac_watermark_threshold_t HAL_FMAC_GetYEmptyWatermark(const hal_fmac_handle_t *hfmac);

/* X2 base address */
hal_status_t HAL_FMAC_SetX2BaseAddress(hal_fmac_handle_t *hfmac, uint32_t base_half_word);

/* Clip management */
hal_status_t HAL_FMAC_EnableClip(hal_fmac_handle_t *hfmac);
hal_status_t HAL_FMAC_DisableClip(hal_fmac_handle_t *hfmac);
hal_fmac_clip_status_t HAL_FMAC_IsEnabledClip(const hal_fmac_handle_t *hfmac);

/* X1 and Y can be directly written or read by a periphal (ADC, DAC, etc.).
   Get the read and write register address */
volatile uint32_t *HAL_FMAC_GetX1Address(const hal_fmac_handle_t *hfmac);
volatile const uint32_t *HAL_FMAC_GetYAddress(const hal_fmac_handle_t *hfmac);

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
hal_status_t HAL_FMAC_SetWriteX1DMA(hal_fmac_handle_t *hfmac, hal_dma_handle_t *hdma);
hal_status_t HAL_FMAC_SetReadYDMA(hal_fmac_handle_t *hfmac, hal_dma_handle_t *hdma);
#endif /* USE_HAL_FMAC_DMA */
/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group3 Preload functions
  * @{
  */
hal_status_t HAL_FMAC_PreloadX1(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word);
hal_status_t HAL_FMAC_PreloadY(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word);
hal_status_t HAL_FMAC_PreloadX2(hal_fmac_handle_t *hfmac, const hal_fmac_preload_x2_t *p_data);

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
hal_status_t HAL_FMAC_PreloadX1_DMA(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word);
hal_status_t HAL_FMAC_PreloadY_DMA(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word);
#endif  /* USE_HAL_FMAC_DMA */
/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group4 Filter functions
  * @{
  */
hal_status_t HAL_FMAC_StartFilterFIR(hal_fmac_handle_t *hfmac, uint32_t coeff_nb, uint32_t gain, uint32_t opt_it);
hal_status_t HAL_FMAC_StartFilterIIR(hal_fmac_handle_t *hfmac, uint32_t ff_coeff_nb, uint32_t fb_coeff_nb,
                                     uint32_t gain, uint32_t opt_it);
hal_status_t HAL_FMAC_StopFilter(hal_fmac_handle_t *hfmac);
/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group5 Y buffer read functions and X1 buffer write functions
  * @{
  */

/* Polling */
hal_status_t HAL_FMAC_WriteX1(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word,
                              uint32_t timeout_ms);
hal_status_t HAL_FMAC_ReadY(hal_fmac_handle_t *hfmac, int16_t *p_data, uint32_t size_half_word, uint32_t timeout_ms);

/* Interrupt */
hal_status_t HAL_FMAC_WriteX1_IT(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word);
hal_status_t HAL_FMAC_ReadY_IT(hal_fmac_handle_t *hfmac, int16_t *p_data, uint32_t size_half_word);

/* DMA */
#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
hal_status_t HAL_FMAC_WriteX1_DMA(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word);
hal_status_t HAL_FMAC_WriteX1_DMA_Opt(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word,
                                      uint32_t opt_it);
hal_status_t HAL_FMAC_ReadY_DMA(hal_fmac_handle_t *hfmac, int16_t *p_data, uint32_t size_half_word);
hal_status_t HAL_FMAC_ReadY_DMA_Opt(hal_fmac_handle_t *hfmac, int16_t *p_data, uint32_t size_half_word,
                                    uint32_t opt_it);
#endif /* USE_HAL_FMAC_DMA */

/* X1 and Y can be directly written or read by a peripheral (ADC, DAC, etc.) The following API only update
   the state machine */
hal_status_t HAL_FMAC_LockX1WriteAccessForExternPeriph(hal_fmac_handle_t *hfmac);
hal_status_t HAL_FMAC_UnlockX1WriteAccessForExternPeriph(hal_fmac_handle_t *hfmac);
hal_status_t HAL_FMAC_LockYReadAccessForExternPeriph(hal_fmac_handle_t *hfmac);
hal_status_t HAL_FMAC_UnlockYReadAccessForExternPeriph(hal_fmac_handle_t *hfmac);
/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group6 Callback functions
  * @{
  */
void HAL_FMAC_WriteX1CpltCallback(hal_fmac_handle_t *hfmac);
void HAL_FMAC_ReadYCpltCallback(hal_fmac_handle_t *hfmac);
#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
void HAL_FMAC_WriteX1HalfCpltCallback(hal_fmac_handle_t *hfmac);
void HAL_FMAC_ReadYHalfCpltCallback(hal_fmac_handle_t *hfmac);
void HAL_FMAC_PreloadCpltCallback(hal_fmac_handle_t *hfmac);
#endif  /* USE_HAL_FMAC_DMA */
void HAL_FMAC_ErrorCallback(hal_fmac_handle_t *hfmac);

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
/* Register callbacks */
hal_status_t HAL_FMAC_RegisterWriteX1CpltCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback);
hal_status_t HAL_FMAC_RegisterReadYCpltCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback);
#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
hal_status_t HAL_FMAC_RegisterWriteX1HalfCpltCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback);
hal_status_t HAL_FMAC_RegisterReadYHalfCpltCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback);
hal_status_t HAL_FMAC_RegisterPreloadCpltCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback);
#endif  /* USE_HAL_FMAC_DMA */
hal_status_t HAL_FMAC_RegisterErrorCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group7 IRQ handler management
  * @{
  */
void HAL_FMAC_IRQHandler(hal_fmac_handle_t *hfmac);
void HAL_FMAC_ERROR_IRQHandler(hal_fmac_handle_t *hfmac);
/**
  * @}
  */

/** @defgroup FMAC_Exported_Functions_Group8 Peripheral State and Error functions
  * @{
  */
hal_fmac_state_t HAL_FMAC_GetState(const hal_fmac_handle_t *hfmac);
hal_fmac_x1_state_t HAL_FMAC_GetX1State(const hal_fmac_handle_t *hfmac);
hal_fmac_y_state_t HAL_FMAC_GetYState(const hal_fmac_handle_t *hfmac);

#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
uint32_t HAL_FMAC_GetLastErrorCodes(const hal_fmac_handle_t *hfmac);
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */
/**
  * @}
  */

#if defined(USE_HAL_FMAC_USER_DATA) && (USE_HAL_FMAC_USER_DATA == 1)
/** @defgroup FMAC_Exported_Functions_Group9 Set/Get user data
  * @{
  */
void HAL_FMAC_SetUserData(hal_fmac_handle_t *hfmac, const void *p_user_data);
const void *HAL_FMAC_GetUserData(const hal_fmac_handle_t *hfmac);
/**
  * @}
  */
#endif /* USE_HAL_FMAC_USER_DATA */

/**
  * @}
  */

/**
  * @}
  */
#endif /* FMAC1 || FMAC2 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_HAL_FMAC_H */
