/**
  ******************************************************************************
  * @file    stm32g5xx_hal_fmac.c
  * @brief   FMAC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the FMAC peripheral:
  *           + Initialization and de-initialization
  *           + Configuration of internal buffer
  *           + Prelaod X1, X2 and Y function
  *           + IIR and FIR filter function
  *           + Read X1 and Write Y in FIFO mode
  *           + Callbacks
  *           + IRQ handler management
  *           + Peripheral state and error
  *
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
/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

/** @addtogroup FMAC FMAC
  * @{
  */

/** @defgroup FMAC_Introduction FMAC Introduction
  * @{

  - The FMAC hardware abstraction layer provides a set of APIs to interface with the STM32 FMAC
    (Filter Math Accelerator) peripheral.

  - The FMAC HAL driver simplifies the implementation of complex filtering algorithms such as FIR and IIR filters
    by managing peripheral initialization, configuration, and data handling, supporting polling, interrupt and DMA modes
    for data acquisitions.

  - This abstraction layer ensures portability and ease of use across different STM32 series.

  */
/**
  * @}
  */

/** @defgroup FMAC_How_To_Use FMAC How To Use
  * @{

An explanation on the FMAC overall usage:
The FMAC unit performs arithmetic operations on vectors. The unit includes support for circular
buffers on input and output, which allows digital filters to be implemented (Finite/Infinite Impulse Response filters).
The unit allows frequent or lengthy filtering operations to be offloaded from the CPU, freeing up the processor for
other tasks, and it can accelerate such calculations compared to a software implementation.

This file provides firmware functions to managed the following functionalities of the FMAC peripheral:
- Initialization and De-initialization functions
- Configuration functions
- X1 buffer functions for sending the input samples
- X2 buffer functions for preloading the filter coefficients
- Y buffer functions for retrieving output samples
- Filter functions to start and stop the filtering operation
- Callback functions
- IRQ handler management
- Peripheral state and error functions
- Set/Get user data

# How to use the FMAC HAL module driver

## Initialization and de-initialization functions:

- Declare a hal_fmac_handle_t handle structure
- Initialize the FMACx driver with an FMACx HW instance by calling the HAL_FMAC_Init().
  The FMACx clock is enabled inside the HAL_FMAC_Init() if USE_HAL_FMAC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.
- Use HAL_FMAC_DeInit() to de-initialize the FMAC peripheral and restore the default configuration.

## Configuration functions:

- Use HAL_FMAC_SetConfig() to configure the bases inside the FMAC internal 16-bit memory for the three FMAC buffers
  (X1, X2 and Y), and reset all thresholds.
- Use HAL_FMAC_GetConfig() to retrieve the bases inside the FMAC internal 16-bit memory for the three FMAC buffers
  (X1, X2 and Y).

- Configure the FMAC X1 full watermark threshold by calling HAL_FMAC_SetX1FullWatermark(), and retrieve the watermark
  threshold by calling HAL_FMAC_GetX1FullWatermark().
- Configure the FMAC Y empty watermark threshold by calling HAL_FMAC_SetYEmptyWatermark(), and retrieve the watermark
  threshold by calling HAL_FMAC_GetYEmptyWatermark().
- Use HAL_FMAC_SetX2BaseAddress() to Configure the FMAC X2 base address.
- Enable, disable, and Check the FMAC clip status by using the following functions:
  - HAL_FMAC_EnableClip().
  - HAL_FMAC_DisableClip().
  - HAL_FMAC_IsEnabledClip().

- Use HAL_FMAC_GetX1Address() or HAL_FMAC_GetYAddress() to directly write or read the X1 and Y by a periphal
  (Timer, ADC, DAC, etc).

- Link the Write X1 DMA handle to the FMAC handle by calling HAL_FMAC_SetWriteX1DMA().
- Link the Read Y DMA handle to the FMAC handle by calling HAL_FMAC_SetReadYDMA().

## Preload functions:

- Use HAL_FMAC_PreloadX1() and HAL_FMAC_PreloadX1_DMA() to preload the X1 buffer without and with DMA.
- Use HAL_FMAC_PreloadY() and HAL_FMAC_PreloadY_DMA() to preload the Y buffer without and with DMA.
- Use HAL_FMAC_PreloadX2() to preload X2 buffer with Coeff A and/or B.

## Filter functions:

- Use HAL_FMAC_StartFilterFIR() to start a FIR filter process.
- Use HAL_FMAC_StartFilterIIR() to start a IIR filter process.
- Use HAL_FMAC_StopFilter() Stop the filter process, the X1 process and the Y process.

## X1 buffer write functions and Y buffer read functions:

- Write data to X1 in polling mode, interrupt mode, DMA mode, and DMA mode with optional interrupts by calling
  the following functions:
  - HAL_FMAC_WriteX1().
  - HAL_FMAC_WriteX1_IT().
  - HAL_FMAC_WriteX1_DMA().
  - HAL_FMAC_WriteX1_DMA_Opt().

- Read data from Y in polling mode, interrupt mode, DMA mode, and DMA mode with optional interrupts by calling
  the following functions:
  - HAL_FMAC_ReadY().
  - HAL_FMAC_ReadY_IT().
  - HAL_FMAC_ReadY_DMA().
  - HAL_FMAC_ReadY_DMA_Opt().

- Use HAL_FMAC_LockX1WriteAccessForExternPeriph() to start Write data to X1 driven by another peripheral
  (Timer, ADC, DAC etc).
- Use HAL_FMAC_UnockX1WriteAccessForExternPeriph() to stop Write data to X1 driven by another peripheral
  (Timer, ADC, DAC etc).
- Use HAL_FMAC_LockYReadAccessForExternPeriph() to start Read data from Y driven by another peripheral
  (Timer, ADC, DAC etc).
- Use HAL_FMAC_UnlockYReadAccessForExternPeriph() to stop Read data from Y driven by another peripheral
  (Timer, ADC, DAC etc).

## Callbacks functions

- Use HAL_FMAC_RegisterWriteX1CpltCallback() function to register the FMAC Write X1 complete user callback.
- Use HAL_FMAC_RegisterWriteX1HalfCpltCallback() function to register the FMAC Write X1 Half complete user callback.
- Use HAL_FMAC_RegisterReadYCpltCallback() function to register the FMAC Read Y complete user callback.
- Use HAL_FMAC_RegisterReadYHalfCpltCallback() function to register the FMAC Read Y Half complete user callback.
- Use HAL_FMAC_RegisterPreloadCpltCallback() function to register the FMAC Preload complete user callback.
- Use HAL_FMAC_RegisterErrorCallback() function to register the FMAC error user callback.

## IRQ handler management

- Use HAL_FMAC_IRQHandler() function called under FMAC_IRQHandler interrupt subroutine to handle any FMAC interrupt.
- Use HAL_FMAC_ERROR_IRQHandler() function to handle error FMAC interrupts.

## Peripheral State and Error functions

- Use HAL_FMAC_GetState() function to get the FMAC filter process state
- Use HAL_FMAC_GetX1State() function to get the FMAC X1 process state
- Use HAL_FMAC_GetYState() function to get the FMAC Y process state
- Use HAL_FMAC_GetLastErrorCodes() function to get the last error codes

## Set/Get user data

- Use HAL_FMAC_SetUserData() function to set the FMAC user data
- Use HAL_FMAC_GetUserData() function to get the FMAC user data
  */

/**
  * @}
  */

/** @defgroup FMAC_Configuration_Table FMAC Configuration Table
  * @{
# Configuration inside the FMAC driver

Software configuration defined in stm32g5xx_hal_conf.h:
Prepocessor flags                |   Default value   | Comment
-------------------------------- | ----------------- | ------------------------------------------------
USE_HAL_FMAC_MODULE              |         1         | Enable HAL FMAC driver module
USE_HAL_FMAC_REGISTER_CALLBACKS  |         0         | Allow the user to define their own callback
USE_HAL_FMAC_DMA                 |         1         | Enable DMA code inside FMAC
USE_HAL_CHECK_PARAM              |         0         | Enable runtime parameter check
USE_HAL_FMAC_CLK_ENABLE_MODEL    | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_CHECK_PROCESS_STATE      |         0         | Enable atomicity of process state check
USE_HAL_FMAC_USER_DATA           |         0         | Add a user data inside HAL FMAC handle
USE_HAL_FMAC_GET_LAST_ERRORS     |         0         | Enable retrieval of last processes error codes

Software configuration defined in preprocessor environment:
Prepocessor flags                |   Default value   | Comment
-------------------------------- | ----------------- | ------------------------------------------------
USE_ASSERT_DBG_PARAM             |    Not defined    | Enable check param for HAL and LL
USE_ASSERT_DBG_STATE             |    Not defined    | Enable check state for HAL

  */

/**
  * @}
  */

#if defined(FMAC1) || defined(FMAC2)
#if defined(USE_HAL_FMAC_MODULE) && (USE_HAL_FMAC_MODULE == 1)
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @defgroup  FMAC_Private_Constants FMAC Private Constants
  * @{
  */
#define FMAC_TIMEOUT_VALUE       1000U /*!< FMAC polling-based communications time-out value */
#define FMAC_RESET_TIMEOUT_VALUE 500U  /*!< FMAC reset time-out value */
#define FMAC_MEMORY_SIZE_WORD    256U  /*!< Size of the internal 16-bit memory */
#define FMAC_PARAM_P_MAX_IIR      64U  /*!< Maximum value of P parameter with IIR */
#define FMAC_PARAM_P_MAX_FIR     127U  /*!< Maximum value of P parameter with FIR */
#define FMAC_PARAM_P_MIN           2U  /*!< Minimum value of P parameter */
#define FMAC_PARAM_Q_MAX          63U  /*!< Maximum value of Q parameter */
#define FMAC_PARAM_Q_MIN           1U  /*!< Minimum value of Q parameter */
#define FMAC_PARAM_R_MAX           7U  /*!< Maximum value of R parameter */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup  FMAC_Private_Macros FMAC Private Macros
  * @{
  */

/**
  * @brief Retrieve the FMAC HW cmsis instance from the hal handle.
  */
#define FMAC_GET_INSTANCE(handle) \
  ((FMAC_TypeDef *)((uint32_t)((handle)->instance)))

/**
  * @brief  Verify base and offset sum.
  * @param  value Base and offset sum
  * @retval SET   value is valid
  * @retval RESET value is invalid
  */
#define IS_FMAC_BASE_AND_OFFSET(value) ((value) <= FMAC_MEMORY_SIZE_WORD)

/**
  * @brief  Get the threshold matching the watermark.
  * @param  wm Watermark value
  * @retval Value of the threshold in half_word
  */
#define FMAC_GET_THRESHOLD_FROM_WM(wm) (((wm) == LL_FMAC_WM_0_THRESHOLD_1)? 1U: \
                                        ((wm) == LL_FMAC_WM_1_THRESHOLD_2)? 2U: \
                                        ((wm) == LL_FMAC_WM_2_THRESHOLD_4)? 4U:8U)

/**
  * @brief  Verify the FMAC threshold.
  * @param  threshold Value of the threshold
  * @retval SET (threshold is a valid value) or RESET (threshold is invalid)
  */
#define IS_FMAC_THRESHOLD(threshold) (((threshold) == HAL_FMAC_WATERMARK_THRESHOLD_1)    \
                                      || ((threshold) == HAL_FMAC_WATERMARK_THRESHOLD_2) \
                                      || ((threshold) == HAL_FMAC_WATERMARK_THRESHOLD_4) \
                                      || ((threshold) == HAL_FMAC_WATERMARK_THRESHOLD_8))
/**
  * @brief  Verify the FMAC filter parameter P for FIR.
  * @param  p     Value of the filter parameter P
  * @retval SET   p is valid
  * @retval RESET p is invalid

  */
#define IS_FMAC_PARAM_P_FIR(p) (((p) >= FMAC_PARAM_P_MIN) && ((p) <= FMAC_PARAM_P_MAX_FIR))

/**
  * @brief  Verify the FMAC filter parameter P for IIR.
  * @param  p     Value of the filter parameter P
  * @retval SET   p is valid
  * @retval RESET p is invalid
  */
#define IS_FMAC_PARAM_P_IIR(p) (((p) >= FMAC_PARAM_P_MIN) && ((p) <= FMAC_PARAM_P_MAX_IIR))

/**
  * @brief  Verify the FMAC filter parameter Q for IIR.
  * @param  q     Value of the filter parameter Q
  * @retval SET   q is valid
  * @retval RESET q is invalid
  */
#define IS_FMAC_PARAM_Q_IIR(q) (((q) >= FMAC_PARAM_Q_MIN) && ((q) <= FMAC_PARAM_Q_MAX))

/**
  * @brief  Verify the FMAC filter parameter R for FIR or IIR.
  * @param  r     Value of the filter parameter
  * @retval SET   r is valid
  * @retval RESET r is invalid
  */
#define IS_FMAC_PARAM_R_FIR_IIR(r) ((r) <= FMAC_PARAM_R_MAX)

/**
  * @brief  Verify the FMAC clip feature.
  * @param  clip_state Clip state
  * @retval SET        clip_state is valid
  * @retval RESET      clip_state is invalid
  */
#define IS_FMAC_CLIP_STATE(clip_state) (((clip_state) == HAL_FMAC_CLIP_DISABLED) \
                                        || ((clip_state) == HAL_FMAC_CLIP_ENABLED))

/**
  * @brief  Verify filter optional interrupt.
  * @param  it    Interrupt selection
  * @retval SET   it is valid
  * @retval RESET it is invalid
  */
#define IS_FMAC_OPT_IT_FUNCTION(it) (((it) == HAL_FMAC_OPT_IT_FILTER_NONE) \
                                     || ((it) == HAL_FMAC_OPT_IT_FILTER_SATURATION_ERROR))

/**
  * @brief  Verify X1 write DMA optional interrupt.
  * @param  it    Interrupt selection
  * @retval SET   it is valid
  * @retval RESET it is invalid
  */
#define IS_FMAC_OPT_DMA_IT_X1(it) (((it) == HAL_FMAC_OPT_DMA_X1_IT_NONE) \
                                   || ((it) == HAL_FMAC_OPT_DMA_X1_IT_HT))

/**
  * @brief  Verify Y read DAM optional interrupt.
  * @param  it    Interrupt selection
  * @retval SET   it is valid
  * @retval RESET it is invalid
  */
#define IS_FMAC_OPT_DMA_IT_Y(it) (((it) == HAL_FMAC_OPT_DMA_Y_IT_NONE) \
                                  || ((it) == HAL_FMAC_OPT_DMA_Y_IT_HT))
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/** @defgroup  FMAC_Private_Functions FMAC Private Macros
  * @{
  */
static hal_status_t FMAC_PreloadFifo(hal_fmac_handle_t *hfmac, uint32_t func_load, const int16_t *p_data,
                                     uint32_t size_half_word);
#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
static hal_status_t FMAC_PreloadFifo_DMA(hal_fmac_handle_t *hfmac, uint32_t func_load, const int16_t *p_data,
                                         uint32_t size_half_word);
#endif /* USE_HAL_FMAC_DMA */
static hal_status_t FMAC_PreloadWrite(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word);
static hal_status_t FMAC_PreloadWaitStartReset(hal_fmac_handle_t *hfmac);
static void FMAC_WriteDataIncrPtr(hal_fmac_handle_t *hfmac);
static void FMAC_ReadDataIncrPtr(hal_fmac_handle_t *hfmac);
#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
static void FMAC_DMAError(hal_dma_handle_t *hdma);
static void FMAC_DMAWriteX1HalfCpltCallback(hal_dma_handle_t *hdma);
static void FMAC_DMAWriteX1CpltCallback(hal_dma_handle_t *hdma);
static void FMAC_DMAReadYHalfCpltCallback(hal_dma_handle_t *hdma);
static void FMAC_DMAReadYCpltCallback(hal_dma_handle_t *hdma);
static void FMAC_DMAPreloadCpltCallback(hal_dma_handle_t *hdma);
#endif /* USE_HAL_FMAC_DMA */
static hal_status_t FMAC_Abort(hal_fmac_handle_t *hfmac);
/**
  * @}
  */

/* Functions Definition ----------------------------------------------------------------------------------------------*/

/** @defgroup FMAC_Exported_Functions HAL FMAC Functions
  * @{
  */

/** @addtogroup FMAC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
This section provides a set of functions allowing to :
 - Initialize the selected device with the FMAC instance by calling HAL_FMAC_Init().
 - De-Initialize and restore the default configuration of the selected FMACx peripheral by calling HAL_FMAC_DeInit().
 - Retrieve the HAL FMAC instance from the handle by calling HAL_FMAC_GetInstance().
 - Retrieve the CMSIS/LL FMAC instance from the handle by calling HAL_FMAC_GetLLInstance().
  */

/**
  * @brief  Initialize the FMAC according to the associated handle.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  instance          HAL FMAC instance
  * @retval HAL_INVALID_PARAM HAL FMAC instance is NULL
  * @retval HAL_OK            FMAC instance has been correctly initialized.
  */
hal_status_t HAL_FMAC_Init(hal_fmac_handle_t *hfmac, hal_fmac_t instance)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(IS_FMAC_ALL_INSTANCE((FMAC_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hfmac == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hfmac->instance = instance;

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  /* Register the weak functions as default callback functions */
  hfmac->p_write_x1_cplt_cb = HAL_FMAC_WriteX1CpltCallback;
  hfmac->p_read_y_cplt_cb = HAL_FMAC_ReadYCpltCallback;
#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
  hfmac->p_write_x1_half_cplt_cb = HAL_FMAC_WriteX1HalfCpltCallback;
  hfmac->p_read_y_half_cplt_cb = HAL_FMAC_ReadYHalfCpltCallback;
  hfmac->p_preload_cplt_cb = HAL_FMAC_PreloadCpltCallback;
#endif /* USE_HAL_FMAC_DMA */
  hfmac->p_error_cb = HAL_FMAC_ErrorCallback;
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */

#if defined(USE_HAL_FMAC_USER_DATA) && (USE_HAL_FMAC_USER_DATA == 1)
  hfmac->p_user_data = (void *) NULL;
#endif /* USE_HAL_FMAC_USER_DATA */

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
  hfmac->hdma_x1 = NULL;
  hfmac->hdma_y = NULL;
#endif /* USE_HAL_FMAC_DMA */

#if defined(USE_HAL_FMAC_CLK_ENABLE_MODEL) && (USE_HAL_FMAC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  switch (hfmac->instance)
  {
    case HAL_FMAC1:
      HAL_RCC_FMAC1_EnableClock();
      break;
#if defined(FMAC2)
    case HAL_FMAC2:
      HAL_RCC_FMAC2_EnableClock();
      break;
#endif /* FMAC2 */
    default:
      break;
  }
#endif /* USE_HAL_FMAC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO */

#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
  hfmac->last_error_codes = HAL_FMAC_ERROR_NONE;
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */

  hfmac->x1_state = HAL_FMAC_STATE_X1_RESET;
  hfmac->y_state = HAL_FMAC_STATE_Y_RESET;
  hfmac->global_state = HAL_FMAC_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  De-initialize the FMAC peripheral and restore the default configuration.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  */
void HAL_FMAC_DeInit(hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(IS_FMAC_ALL_INSTANCE((FMAC_TypeDef *)((uint32_t)hfmac->instance)));

  (void) FMAC_Abort(hfmac);

  hfmac->x1_state = HAL_FMAC_STATE_X1_RESET;
  hfmac->y_state = HAL_FMAC_STATE_Y_RESET;
  hfmac->global_state = HAL_FMAC_STATE_RESET;
}

/**
  * @brief  Return the HAL FMAC instance from the handle.
  * @param  hfmac      Pointer to a hal_fmac_handle_t.
  * @retval hal_fmac_t HAL FMAC instance.
  */
hal_fmac_t HAL_FMAC_GetInstance(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(IS_FMAC_ALL_INSTANCE(FMAC_GET_INSTANCE(hfmac)));

  return hfmac->instance;
}

/**
  * @brief  Return the CMSIS/LL FMAC instance from the handle.
  * @param  hfmac         Pointer to a hal_fmac_handle_t.
  * @retval FMAC_TypeDef  CMSIS/LL FMAC instance.
  */
FMAC_TypeDef *HAL_FMAC_GetLLInstance(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(IS_FMAC_ALL_INSTANCE((FMAC_TypeDef *)((uint32_t)hfmac->instance)));

  return (FMAC_TypeDef *)((uint32_t)hfmac->instance);
}

/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group2 FMAC configuration functions
  * @{
This section provides a set of functions allowing to:
 - Configure the FMAC memory area in the internal 16-bit memory by calling HAL_FMAC_SetConfig() .
 - Get the FMAC memory area in the internal 16-bit memory configuration by calling HAL_FMAC_GetConfig().
 - Set the FMAC watermark threshold for X1 by calling HAL_FMAC_SetX1FullWatermark().
   Valuable in case of process managed by interrupt.
 - Get the FMAC watermark threshold for X1 by calling HAL_FMAC_GetX1FullWatermark().
 - Set the FMAC watermark threshold for Y by calling HAL_FMAC_SetYEmptyWatermark().
   Valuable in case of process managed by interrupt.
 - Get the FMAC watermark threshold for Y by calling HAL_FMAC_SetYEmptyWatermark()
 - Set the X2 base address by calling HAL_FMAC_SetX2BaseAddress() .
 - Enable the clip mode by calling HAL_FMAC_EnableClip().
 - Disable the clip mode by calling HAL_FMAC_DisableClip().
 - Get X1 write register address by calling HAL_FMAC_GetX1Address() .
   Valuable in case of process managed by another peripheral.
 - Get Y write register address by calling HAL_FMAC_GetYAddress().
   Valuable in case of process managed by another peripheral.
  */

/**
  * @brief  Allocate memory area for X1, X2 and Y in the FMAC internal 16-bit memory. All thresholds are reset.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_config          Pointer to the configuration
  * @retval HAL_INVALID_PARAM p_config is NULL
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_SetConfig(hal_fmac_handle_t *hfmac, const hal_fmac_config_t *p_config)
{
  FMAC_TypeDef *p_fmacx;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_FMAC_BASE_AND_OFFSET(p_config->x1_buf.base_half_word + p_config->x1_buf.size_half_word));
  ASSERT_DBG_PARAM(IS_FMAC_BASE_AND_OFFSET(p_config->x2_buf.base_half_word + p_config->x2_buf.size_half_word));
  ASSERT_DBG_PARAM(IS_FMAC_BASE_AND_OFFSET(p_config->y_buf.base_half_word + p_config->y_buf.size_half_word));
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_INIT | (uint32_t)HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->x1_state, (uint32_t)HAL_FMAC_STATE_X1_RESET | (uint32_t)HAL_FMAC_STATE_X1_IDLE);
  ASSERT_DBG_STATE(hfmac->y_state, (uint32_t)HAL_FMAC_STATE_Y_RESET | (uint32_t)HAL_FMAC_STATE_Y_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_fmacx = FMAC_GET_INSTANCE(hfmac);

  /* Set all bases and sizes and reset all thresholds */
  LL_FMAC_SetX1BaseAndSize(p_fmacx, p_config->x1_buf.base_half_word, p_config->x1_buf.size_half_word);
  LL_FMAC_SetX2BaseAndSize(p_fmacx, p_config->x2_buf.base_half_word, p_config->x2_buf.size_half_word);
  LL_FMAC_SetYBaseAndSize(p_fmacx, p_config->y_buf.base_half_word, p_config->y_buf.size_half_word);

  hfmac->x1_state = HAL_FMAC_STATE_X1_IDLE;
  hfmac->y_state = HAL_FMAC_STATE_Y_IDLE;
  hfmac->global_state = HAL_FMAC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Retrieve the FMAC configuration.
  * @param hfmac    Pointer to a hal_fmac_handle_t
  * @param p_config Pointer to the configuration
  */
void HAL_FMAC_GetConfig(const hal_fmac_handle_t *hfmac, hal_fmac_config_t *p_config)
{
  FMAC_TypeDef *p_fmacx;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t) HAL_FMAC_STATE_IDLE | (uint32_t) HAL_FMAC_STATE_ACTIVE_PRELOAD
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_FILTER);
  p_fmacx = FMAC_GET_INSTANCE(hfmac);

  p_config->x1_buf.base_half_word = LL_FMAC_GetX1Base(p_fmacx);
  p_config->x1_buf.size_half_word = LL_FMAC_GetX1BufferSize(p_fmacx);

  p_config->x2_buf.base_half_word = LL_FMAC_GetX2Base(p_fmacx);
  p_config->x2_buf.size_half_word = LL_FMAC_GetX2BufferSize(p_fmacx);

  p_config->y_buf.base_half_word = LL_FMAC_GetYBase(p_fmacx);
  p_config->y_buf.size_half_word = LL_FMAC_GetYBufferSize(p_fmacx);
}

/**
  * @brief  Configure the FMAC X1 full watermark threshold. Setting a threshold greater than 1 allows several
  *         data to be transferred under one interrupt.
  *         In case of DMA, it must be kept to the default value of @ref HAL_FMAC_WATERMARK_THRESHOLD_1.
  *         In case of Polling, a threshold value of @ref HAL_FMAC_WATERMARK_THRESHOLD_2 avoids waiting for a delay of
  *         3 clock cycles before the X1FULL flag goes high.
  * @param  hfmac     Pointer to a hal_fmac_handle_t
  * @param  threshold Threshold value.
  * @retval HAL_OK    Operation completed successfully
  */
hal_status_t HAL_FMAC_SetX1FullWatermark(hal_fmac_handle_t *hfmac, hal_fmac_watermark_threshold_t threshold)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(IS_FMAC_THRESHOLD(threshold));
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->x1_state, HAL_FMAC_STATE_X1_IDLE);

  LL_FMAC_SetX1FullWatermark(FMAC_GET_INSTANCE(hfmac), (uint32_t) threshold);

  return HAL_OK;
}

/**
  * @brief  Get the FMAC X1 full watermark threshold.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @retval HAL_FMAC_WATERMARK_THRESHOLD_1
  * @retval HAL_FMAC_WATERMARK_THRESHOLD_2
  * @retval HAL_FMAC_WATERMARK_THRESHOLD_4
  * @retval HAL_FMAC_WATERMARK_THRESHOLD_8
  */
hal_fmac_watermark_threshold_t HAL_FMAC_GetX1FullWatermark(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t) HAL_FMAC_STATE_IDLE | (uint32_t) HAL_FMAC_STATE_ACTIVE_PRELOAD
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_FILTER);

  return (hal_fmac_watermark_threshold_t) LL_FMAC_GetX1FullWatermark(FMAC_GET_INSTANCE(hfmac));
}

/**
  * @brief  Configure the FMAC Y empty watermark threshold. Setting a threshold greater than 1 allows several
  *         data to be transferred under one interrupt.
  *         In case of DMA, it must be kept to the default value of @ref HAL_FMAC_WATERMARK_THRESHOLD_1.
  *         In case of Polling, a threshold value of @ref HAL_FMAC_WATERMARK_THRESHOLD_2 avoids waiting for a delay of
  *         3 clock cycles before the YEMPTY flag goes high.
  * @param  hfmac     Pointer to a hal_fmac_handle_t
  * @param  threshold Threshold value
  * @retval HAL_OK    Operation completed successfully
  */
hal_status_t HAL_FMAC_SetYEmptyWatermark(hal_fmac_handle_t *hfmac, hal_fmac_watermark_threshold_t threshold)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(IS_FMAC_THRESHOLD(threshold));
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->y_state, (uint32_t)HAL_FMAC_STATE_Y_IDLE);

  LL_FMAC_SetYEmptyWatermark(FMAC_GET_INSTANCE(hfmac), (uint32_t) threshold);

  return HAL_OK;
}

/**
  * @brief  Get the FMAC Y empty watermark threshold.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @retval HAL_FMAC_WATERMARK_THRESHOLD_1
  * @retval HAL_FMAC_WATERMARK_THRESHOLD_2
  * @retval HAL_FMAC_WATERMARK_THRESHOLD_4
  * @retval HAL_FMAC_WATERMARK_THRESHOLD_8
  */
hal_fmac_watermark_threshold_t HAL_FMAC_GetYEmptyWatermark(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t) HAL_FMAC_STATE_IDLE | (uint32_t) HAL_FMAC_STATE_ACTIVE_PRELOAD
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_FILTER);

  return (hal_fmac_watermark_threshold_t) LL_FMAC_GetYEmptyWatermark(FMAC_GET_INSTANCE(hfmac));
}

/**
  * @brief  Configure the FMAC X2 base address. It can be modified while START=1 for example
  *         to change coefficient values.
  * @param  hfmac          Pointer to a hal_fmac_handle_t
  * @param  base_half_word Base address within the 16-bits internal memory (0x00 to 0xFF)
  * @retval HAL_OK         Operation completed successfully
  */
hal_status_t HAL_FMAC_SetX2BaseAddress(hal_fmac_handle_t *hfmac, uint32_t base_half_word)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(IS_FMAC_BASE_AND_OFFSET(base_half_word));
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t) HAL_FMAC_STATE_IDLE | (uint32_t) HAL_FMAC_STATE_ACTIVE_PRELOAD
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_FILTER);

  LL_FMAC_SetX2Base(FMAC_GET_INSTANCE(hfmac), base_half_word);

  return HAL_OK;
}

/**
  * @brief  Enable Clip. If clipping is enabled, then any value which exceeds the numeric range of the q1.15 output,
            is set to 1 - 2^-15 or -1, according to the sign.
  * @param  hfmac  Pointer to a hal_fmac_handle_t
  * @retval HAL_OK Operation completed successfully
  */
hal_status_t HAL_FMAC_EnableClip(hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_IDLE);

  LL_FMAC_EnableClipping(FMAC_GET_INSTANCE(hfmac));

  return HAL_OK;
}

/**
  * @brief  Disable clip. If clipping is not enabled, the unused accumulator bits after applying
            the gain is simply truncated.
  * @param  hfmac  Pointer to a hal_fmac_handle_t
  * @retval HAL_OK Operation completed successfully
  */
hal_status_t HAL_FMAC_DisableClip(hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_IDLE);

  LL_FMAC_DisableClipping(FMAC_GET_INSTANCE(hfmac));

  return HAL_OK;
}

/**
  * @brief  Check the FMAC clip status.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @retval HAL_FMAC_CLIP_ENABLED  Clip is enabled
  * @retval HAL_FMAC_CLIP_DISABLED Clip is disabled
  */
hal_fmac_clip_status_t HAL_FMAC_IsEnabledClip(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t) HAL_FMAC_STATE_IDLE | (uint32_t) HAL_FMAC_STATE_ACTIVE_PRELOAD
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_FILTER);

  return (hal_fmac_clip_status_t) LL_FMAC_IsEnabledClipping(FMAC_GET_INSTANCE(hfmac));
}

/**
  * @brief  Get the FMAC X1 write register address.
  *         Write data to X1 can be directly driven by a timer or other peripheral such as an ADC.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @retval FMAC X1 write register address
  */
volatile uint32_t *HAL_FMAC_GetX1Address(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t) HAL_FMAC_STATE_IDLE | (uint32_t) HAL_FMAC_STATE_ACTIVE_PRELOAD
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_FILTER);

  return &(FMAC_GET_INSTANCE(hfmac)->WDATA);
}

/**
  * @brief  Get the FMAC Y read register address.
  *         Read data from Y can be directly driven by a timer or other peripheral such as an DAC.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @retval FMAC Y read register address
  */
volatile const uint32_t *HAL_FMAC_GetYAddress(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t) HAL_FMAC_STATE_IDLE | (uint32_t) HAL_FMAC_STATE_ACTIVE_PRELOAD
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_FILTER);

  return &(FMAC_GET_INSTANCE(hfmac)->RDATA);
}

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
/**
  * @brief  Link the Write X1 DMA handle to the FMAC handle.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  hdma              Pointer to a hal_dma_handle_t structure
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_SetWriteX1DMA(hal_fmac_handle_t *hfmac, hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_INIT | (uint32_t)HAL_FMAC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Link the DMA handle to the FMAC handle */
  hfmac->hdma_x1 = hdma;
  /* Link the FMAC handle to the DMA handle */
  hdma->p_parent = hfmac;

  return HAL_OK;
}

/**
  * @brief  Link the Read Y DMA handle to the FMAC handle.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  hdma              Pointer to a hal_dma_handle_t structure
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_SetReadYDMA(hal_fmac_handle_t *hfmac, hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_INIT | (uint32_t)HAL_FMAC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Link the DMA handle to the FMAC handle */
  hfmac->hdma_y = hdma;
  /* Link the FMAC handle to the DMA handle */
  hdma->p_parent = hfmac;

  return HAL_OK;
}
#endif /* USE_HAL_FMAC_DMA */

/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group3 Preload functions
  * @{
This section provides a set of functions allowing to :
 - Preload X1 with sample by calling HAL_FMAC_PreloadX1().
 - Preload Y in case of IIR by calling HAL_FMAC_PreloadY().
 - Preload X2 with coefficients by calling HAL_FMAC_PreloadX2().
 - Preload X1 with sample by calling HAL_FMAC_PreloadX1_DMA().
 - Preload Y in case of IIR by calling HAL_FMAC_PreloadY_DMA().
  */

/**
  * @brief  Preload X1 buffer.
  * @param  hfmac        Pointer to a hal_fmac_handle_t
  * @param  p_data       Pointer to data to preload to X1
  * @param  size_half_word Size in half word, it cannot be bigger than the X1 size in half word
  * @note   This function can be called several times, each call filling partly the buffers.
            In case of overflow (too much data provided through all these calls), an error is returned.
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_PreloadX1(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word <= (uint32_t) LL_FMAC_GetX1BufferSize(FMAC_GET_INSTANCE(hfmac)));
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->x1_state, HAL_FMAC_STATE_X1_IDLE);

  return FMAC_PreloadFifo(hfmac, (LL_FMAC_FUNC_LOAD_X1 | FMAC_PARAM_START), p_data, size_half_word);
}

/**
  * @brief  Preload Y buffer.
  * @param  hfmac        Pointer to a hal_fmac_handle_t
  * @param  p_data       Pointer to data to preload to Y
  * @param  size_half_word Size in half word, it cannot be bigger than the Y size in half word
  * @note   This function can be called several times, each call filling partly the buffers.
            In case of overflow (too much data provided through all these calls), an error is returned.
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_PreloadY(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word <= (uint32_t) LL_FMAC_GetYBufferSize(FMAC_GET_INSTANCE(hfmac)));
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->y_state, HAL_FMAC_STATE_Y_IDLE);

  return FMAC_PreloadFifo(hfmac, (LL_FMAC_FUNC_LOAD_Y | FMAC_PARAM_START), p_data, size_half_word);
}

/**
  * @brief  Preload X2 buffer with Coeff A and/or B.
  *         If no Coeff A, @ref hal_fmac_preload_x2_t::coeff_a_size_half_word must be set to 0.
  *         If no Coeff B, @ref hal_fmac_preload_x2_t::coeff_b_size_half_word must be set to 0.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to data to preload
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_PreloadX2(hal_fmac_handle_t *hfmac, const hal_fmac_preload_x2_t *p_data)
{
  hal_status_t hal_status = HAL_ERROR;
  FMAC_TypeDef *p_fmacx;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM((p_data->coeff_b_size_half_word != 0UL) ?
                   (p_data->p_coeff_b != NULL) : 1);
  ASSERT_DBG_PARAM((p_data->coeff_a_size_half_word != 0UL) ?
                   (p_data->p_coeff_a != NULL) : 1);
  p_fmacx = FMAC_GET_INSTANCE(hfmac);
  ASSERT_DBG_PARAM(((p_data->coeff_a_size_half_word + p_data->coeff_b_size_half_word)
                    <= (uint32_t) LL_FMAC_GetX2BufferSize(p_fmacx)));
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || ((p_data->coeff_b_size_half_word != 0UL) && (p_data->p_coeff_b == NULL))
      || ((p_data->coeff_a_size_half_word != 0UL) && (p_data->p_coeff_a == NULL)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, global_state, HAL_FMAC_STATE_IDLE, HAL_FMAC_STATE_ACTIVE_PRELOAD);

#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
  hfmac->last_error_codes = 0;
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */

  /* Write number of values to be loaded, the data load function and start the operation */
  LL_FMAC_WRITE_REG(p_fmacx, PARAM,
                    (((uint32_t)(p_data->coeff_b_size_half_word) << FMAC_PARAM_P_Pos) |
                     ((uint32_t)(p_data->coeff_a_size_half_word) << FMAC_PARAM_Q_Pos) |
                     LL_FMAC_FUNC_LOAD_X2 | FMAC_PARAM_START));

  /* Load the buffer coeff B into the 16-bits internal memory if coeff_b_size_half_word is not 0 */
  if (FMAC_PreloadWrite(hfmac, p_data->p_coeff_b, p_data->coeff_b_size_half_word) == HAL_OK)
  {
    /* Load the buffer coeff A into the 16-bits internal memory */
    if (FMAC_PreloadWrite(hfmac, p_data->p_coeff_a, p_data->coeff_a_size_half_word) == HAL_OK)
    {
      /* Check if START is reset */
      hal_status = FMAC_PreloadWaitStartReset(hfmac);
    }
  }

  hfmac->global_state = HAL_FMAC_STATE_IDLE;
  return hal_status;
}

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
/**
  * @brief  Preload X1 buffer with DMA.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to data to preload to X1
  * @param  size_half_word    Size in half word, it cannot be bigger than the X1 size in half word
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_PreloadX1_DMA(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word <= (uint32_t) LL_FMAC_GetX1BufferSize(FMAC_GET_INSTANCE(hfmac)));
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->x1_state, HAL_FMAC_STATE_X1_IDLE);

  return FMAC_PreloadFifo_DMA(hfmac, (LL_FMAC_FUNC_LOAD_X1 | FMAC_PARAM_START), p_data, size_half_word);
}

/**
  * @brief  Preload Y buffer with DMA.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to data to preload to Y
  * @param  size_half_word    Size in half word, it cannot be bigger than the Y size in half word
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_PreloadY_DMA(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word <= (uint32_t) LL_FMAC_GetYBufferSize(FMAC_GET_INSTANCE(hfmac)));
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->y_state, HAL_FMAC_STATE_Y_IDLE);

  return FMAC_PreloadFifo_DMA(hfmac, (LL_FMAC_FUNC_LOAD_Y | FMAC_PARAM_START), p_data, size_half_word);
}
#endif /* USE_HAL_FMAC_DMA */

/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group4 Filter functions
  * @{
This section provides a set of functions allowing to :
 - Start a FIR filter process by calling HAL_FMAC_StartFilterFIR().
 - Start a IIR filter process by calling HAL_FMAC_StartFilterIIR().
 - Stop the filter process, the X1 process and the Y process by calling HAL_FMAC_StopFilter() .
  */

/**
  * @brief  Start the FIR filtering.
  * @param  hfmac    Pointer to a hal_fmac_handle_t
  * @param  coeff_nb Number of coefficients (N).  (P in param register)
  * @param  gain     Gain. (R in param register)
  * @param  opt_it   Optional interruption can be one of
  *                  @ref HAL_FMAC_OPT_IT_FILTER_NONE
  *                  @ref HAL_FMAC_OPT_IT_FILTER_SATURATION_ERROR
  * @retval HAL_BUSY Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_OK   Filter started.
  */
hal_status_t HAL_FMAC_StartFilterFIR(hal_fmac_handle_t *hfmac, uint32_t coeff_nb, uint32_t gain, uint32_t opt_it)
{
  FMAC_TypeDef *p_fmacx;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(IS_FMAC_PARAM_P_FIR(coeff_nb));
  ASSERT_DBG_PARAM(IS_FMAC_PARAM_R_FIR_IIR(gain));
  ASSERT_DBG_PARAM(IS_FMAC_OPT_IT_FUNCTION(opt_it));
  p_fmacx = FMAC_GET_INSTANCE(hfmac);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hfmac, global_state, HAL_FMAC_STATE_IDLE, HAL_FMAC_STATE_ACTIVE_FILTER);

  /* Enable the saturation error interruption */
  if (opt_it != HAL_FMAC_OPT_IT_FILTER_NONE)
  {
    LL_FMAC_EnableIT_SAT(p_fmacx);
  }

  LL_FMAC_WRITE_REG(p_fmacx, PARAM, FMAC_PARAM_START | LL_FMAC_FUNC_CONVO_FIR
                    | (coeff_nb << FMAC_PARAM_P_Pos) | (gain << FMAC_PARAM_R_Pos));

  return HAL_OK;
}

/**
  * @brief  Start the IIR filtering.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @param  ff_coeff_nb Number of feed-forward coefficients (N). (P in param register)
  * @param  fb_coeff_nb Number of feed-back coefficients (M). (Q in param register)
  * @param  gain        Gain. (R in param register)
  * @param  opt_it      Optional interruption can be one of
  *                     @ref HAL_FMAC_OPT_IT_FILTER_NONE
  *                     @ref HAL_FMAC_OPT_IT_FILTER_SATURATION_ERROR
  * @retval HAL_BUSY    Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_OK      Filter started.
  */
hal_status_t HAL_FMAC_StartFilterIIR(hal_fmac_handle_t *hfmac, uint32_t ff_coeff_nb, uint32_t fb_coeff_nb,
                                     uint32_t gain, uint32_t opt_it)
{
  FMAC_TypeDef *p_fmacx;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(IS_FMAC_PARAM_P_IIR(ff_coeff_nb));
  ASSERT_DBG_PARAM(IS_FMAC_PARAM_Q_IIR(fb_coeff_nb));
  ASSERT_DBG_PARAM(IS_FMAC_PARAM_R_FIR_IIR(gain));
  ASSERT_DBG_PARAM(IS_FMAC_OPT_IT_FUNCTION(opt_it));
  p_fmacx = FMAC_GET_INSTANCE(hfmac);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hfmac, global_state, HAL_FMAC_STATE_IDLE, HAL_FMAC_STATE_ACTIVE_FILTER);

  if (opt_it != HAL_FMAC_OPT_IT_FILTER_NONE)
  {
    LL_FMAC_EnableIT_SAT(p_fmacx);
  }

  LL_FMAC_WRITE_REG(p_fmacx, PARAM, FMAC_PARAM_START | LL_FMAC_FUNC_IIR_DIRECT_FORM_1
                    | (ff_coeff_nb << FMAC_PARAM_P_Pos) | (fb_coeff_nb << FMAC_PARAM_Q_Pos)
                    | (gain << FMAC_PARAM_R_Pos));

  return HAL_OK;
}

/**
  * @brief  Stop the active filter, the X1 process and the Y process.
  *         Reset the write and read pointers, the internal control logic, the FMAC_SR register and
  *         the FMAC_PARAM register, including the START bit if active.
  *         All interruts are disable. X1, Y and Filter are in IDLE state.
  *         After the stop, user must preload X1 and Y if needed, start a writeX1 process,
  *         start a readY process and start filter.
  * @param  hfmac     Pointer to a hal_fmac_handle_t
  * @retval HAL_ERROR Operation completed with error
  * @retval HAL_OK    Operation completed successfully
  */
hal_status_t HAL_FMAC_StopFilter(hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state,
                   HAL_FMAC_STATE_ACTIVE_FILTER | HAL_FMAC_STATE_ACTIVE_PRELOAD | HAL_FMAC_STATE_IDLE);

  return FMAC_Abort(hfmac);
}

/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group5 Y buffer read functions and X1 buffer write functions
  * @{
This section provides a set of functions allowing to :
  - Write data to X1 in polling mode by calling HAL_FMAC_WriteX1().
  - Write data to X1 in interrupt mode by calling HAL_FMAC_WriteX1_IT().
  - Write data to X1 in DMA mode by calling HAL_FMAC_WriteX1_DMA().
  - Write data to X1 in DMA mode and optional interrupt by calling HAL_FMAC_WriteX1_DMA_Opt().
  - Start Write data to X1 in peripheral mode by calling HAL_FMAC_LockX1WriteAccessForExternPeriph().
  - Stop Write data to X1 in peripheral mode by calling HAL_FMAC_UnlockX1WriteAccessForExternPeriph().
  - Read data from Y in polling mode by calling HAL_FMAC_ReadY().
  - Read data from Y in interrupt mode by calling HAL_FMAC_ReadY_IT().
  - Read data from Y in DMA mode by calling HAL_FMAC_ReadY_DMA().
  - Read data from Y in DMA mode and optional interrupt by calling HAL_FMAC_ReadY_DMA_Opt().
  - Start Read data from Y in peripheral mode by calling HAL_FMAC_LockYReadAccessForExternPeriph().
  - Stop Read data from Y in peripheral mode by calling HAL_FMAC_UnlockYReadAccessForExternPeriph().
  */

/**
  * @brief  Write data to X1 in polling mode.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to input data
  * @param  size_half_word    Size of the input data
  * @param  timeout_ms        Timeout duration in millisecond
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_TIMEOUT       Operation exceeds user timeout
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_WriteX1(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word,
                              uint32_t timeout_ms)
{
  FMAC_TypeDef *p_fmacx;
  uint32_t tick_start;
  const int16_t *p_data_tmp = p_data;
  uint32_t written_size_half_word = 0;
  uint32_t threshold;
  hal_status_t status = HAL_TIMEOUT;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE | HAL_FMAC_STATE_ACTIVE_FILTER);
  ASSERT_DBG_STATE(hfmac->x1_state, HAL_FMAC_STATE_X1_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_half_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, x1_state, HAL_FMAC_STATE_X1_IDLE, HAL_FMAC_STATE_X1_ACTIVE_WRITE);

  p_fmacx = FMAC_GET_INSTANCE(hfmac);
  threshold = FMAC_GET_THRESHOLD_FROM_WM(LL_FMAC_GetX1FullWatermark(p_fmacx));

  /* Init tick_start for timeout management */
  tick_start = HAL_GetTick();

  /* Try to write until timeout or all data are written */
  while (((HAL_GetTick() - tick_start) <= timeout_ms) && (status != HAL_OK))
  {
    /* Check if there is room in FMAC */
    if (LL_FMAC_IsActiveFlag_X1FULL(p_fmacx) == 0U)
    {
      /* Write threshold samples */
      for (uint32_t i = 0; i < threshold; i++)
      {
        LL_FMAC_WriteData(p_fmacx, *p_data_tmp);
        p_data_tmp++;
        written_size_half_word++;
        if (written_size_half_word == size_half_word)
        {
          status = HAL_OK;
          break;
        }
      }
    }
  }

  hfmac->x1_state = HAL_FMAC_STATE_X1_IDLE;

  return status;
}

/**
  * @brief  Read data from Y in polling mode.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to output data
  * @param  size_half_word    Size of the output data
  * @param  timeout_ms        Timeout duration in millisecond
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_TIMEOUT       Operation exceeds user timeout
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_ReadY(hal_fmac_handle_t *hfmac, int16_t *p_data, uint32_t size_half_word, uint32_t timeout_ms)
{
  FMAC_TypeDef *p_fmacx;
  uint32_t tick_start;
  int16_t *p_data_tmp = p_data;
  uint32_t read_size_half_word = 0;
  uint32_t threshold;
  hal_status_t status = HAL_TIMEOUT;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE | HAL_FMAC_STATE_ACTIVE_FILTER);
  ASSERT_DBG_STATE(hfmac->y_state, HAL_FMAC_STATE_Y_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_half_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, y_state, HAL_FMAC_STATE_Y_IDLE, HAL_FMAC_STATE_Y_ACTIVE_READ);

  p_fmacx = FMAC_GET_INSTANCE(hfmac);
  threshold = FMAC_GET_THRESHOLD_FROM_WM(LL_FMAC_GetYEmptyWatermark(p_fmacx));

  /* Init tick_start for timeout management */
  tick_start = HAL_GetTick();

  /* Try to read until timeout or all are read */
  while (((HAL_GetTick() - tick_start) <= timeout_ms) && (status != HAL_OK))
  {
    /* Check if there is data in FMAC */
    if (LL_FMAC_IsActiveFlag_YEMPTY(p_fmacx) == 0U)
    {
      /* Write threshold samples */
      for (uint32_t i = 0; i < threshold; i++)
      {
        *p_data_tmp = LL_FMAC_ReadData(p_fmacx);
        p_data_tmp++;
        read_size_half_word++;
        if (read_size_half_word == size_half_word)
        {
          status = HAL_OK;
          break;
        }
      }
    }
  }

  hfmac->y_state = HAL_FMAC_STATE_Y_IDLE;

  return status;
}

/**
  * @brief  Write data to X1 in interrupt mode.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to input data
  * @param  size_half_word    Size of the input data
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_WriteX1_IT(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE | HAL_FMAC_STATE_ACTIVE_FILTER);
  ASSERT_DBG_STATE(hfmac->x1_state, HAL_FMAC_STATE_X1_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_half_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, x1_state, HAL_FMAC_STATE_X1_IDLE, HAL_FMAC_STATE_X1_ACTIVE_WRITE);

  /* Store input data location */
  hfmac->p_input = p_data;
  hfmac->input_size_half_word = size_half_word;

  LL_FMAC_EnableIT(FMAC_GET_INSTANCE(hfmac), LL_FMAC_IT_W | LL_FMAC_IT_OVFL);

  return status;
}

/**
  * @brief  Read data from Y in interrupt mode.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to output data
  * @param  size_half_word    Size of the output data.
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_ReadY_IT(hal_fmac_handle_t *hfmac, int16_t *p_data, uint32_t size_half_word)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE | HAL_FMAC_STATE_ACTIVE_FILTER);
  ASSERT_DBG_STATE(hfmac->y_state, HAL_FMAC_STATE_Y_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_half_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, y_state, HAL_FMAC_STATE_Y_IDLE, HAL_FMAC_STATE_Y_ACTIVE_READ);

  hfmac->p_output = p_data;
  hfmac->output_size_half_word = size_half_word;

  LL_FMAC_EnableIT(FMAC_GET_INSTANCE(hfmac), LL_FMAC_IT_R | LL_FMAC_IT_UNFL);

  return status;
}

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
/**
  * @brief  Write data to X1 in DMA mode. Global state must be IDLE (START = 0).
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to input data
  * @param  size_half_word    Size of the input data
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_WriteX1_DMA(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word)
{
  hal_status_t status;
  FMAC_TypeDef *p_fmacx;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->x1_state, HAL_FMAC_STATE_X1_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_half_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, x1_state, HAL_FMAC_STATE_X1_IDLE, HAL_FMAC_STATE_X1_ACTIVE_WRITE);

  p_fmacx = FMAC_GET_INSTANCE(hfmac);

  /* Prepare DMA write xfer */
  hfmac->hdma_x1->p_xfer_halfcplt_cb = FMAC_DMAWriteX1HalfCpltCallback;
  hfmac->hdma_x1->p_xfer_cplt_cb = FMAC_DMAWriteX1CpltCallback;
  hfmac->hdma_x1->p_xfer_error_cb = FMAC_DMAError;

  status = HAL_DMA_StartPeriphXfer_IT_Opt(hfmac->hdma_x1, (uint32_t)p_data, (uint32_t)&p_fmacx->WDATA,
                                          (2UL * size_half_word), HAL_DMA_OPT_IT_HT);

  if (status == HAL_OK)
  {
    LL_FMAC_Enable_DMAReq_and_IT(p_fmacx, LL_FMAC_DMA_WRITE, LL_FMAC_IT_OVFL);
  }
  else
  {
    hfmac->x1_state = HAL_FMAC_STATE_X1_IDLE;
  }

  return status;
}

/**
  * @brief  Write data to X1 in DMA mode. Global state must be IDLE (START = 0).
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to input data
  * @param  size_half_word    Size of the input data
  * @param  opt_it            Optional interruption can be a combination of
  *                           @ref HAL_FMAC_OPT_DMA_X1_IT_NONE
  *                           @ref HAL_FMAC_OPT_DMA_X1_IT_HT
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_WriteX1_DMA_Opt(hal_fmac_handle_t *hfmac, const int16_t *p_data, uint32_t size_half_word,
                                      uint32_t opt_it)
{
  hal_status_t status;
  FMAC_TypeDef *p_fmacx;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_PARAM(IS_FMAC_OPT_DMA_IT_X1(opt_it));
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->x1_state, HAL_FMAC_STATE_X1_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_half_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, x1_state, HAL_FMAC_STATE_X1_IDLE, HAL_FMAC_STATE_X1_ACTIVE_WRITE);

  p_fmacx = FMAC_GET_INSTANCE(hfmac);

  /* Prepare DMA write xfer */
  hfmac->hdma_x1->p_xfer_halfcplt_cb = FMAC_DMAWriteX1HalfCpltCallback;
  hfmac->hdma_x1->p_xfer_cplt_cb = FMAC_DMAWriteX1CpltCallback;
  hfmac->hdma_x1->p_xfer_error_cb = FMAC_DMAError;

  status = HAL_DMA_StartPeriphXfer_IT_Opt(hfmac->hdma_x1, (uint32_t)p_data, (uint32_t)&p_fmacx->WDATA,
                                          (2UL * size_half_word), opt_it);

  if (status == HAL_OK)
  {
    LL_FMAC_Enable_DMAReq_and_IT(p_fmacx, LL_FMAC_DMA_WRITE, LL_FMAC_IT_OVFL);
  }
  else
  {
    hfmac->x1_state = HAL_FMAC_STATE_X1_IDLE;
  }

  return status;
}

/**
  * @brief  Read data from Y in DMA mode. Global state must be IDLE (START = 0).
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to output data
  * @param  size_half_word    Size of the output data.
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_ReadY_DMA(hal_fmac_handle_t *hfmac, int16_t *p_data, uint32_t size_half_word)
{
  hal_status_t status;
  FMAC_TypeDef *p_fmacx;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->y_state, HAL_FMAC_STATE_Y_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_half_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, y_state, HAL_FMAC_STATE_Y_IDLE, HAL_FMAC_STATE_Y_ACTIVE_READ);

  p_fmacx = FMAC_GET_INSTANCE(hfmac);

  /* Prepare DMA read xfer */
  hfmac->hdma_y->p_xfer_halfcplt_cb = FMAC_DMAReadYHalfCpltCallback;
  hfmac->hdma_y->p_xfer_cplt_cb = FMAC_DMAReadYCpltCallback;
  hfmac->hdma_y->p_xfer_error_cb = FMAC_DMAError;

  status = HAL_DMA_StartPeriphXfer_IT_Opt(hfmac->hdma_y, (uint32_t)&p_fmacx->RDATA, (uint32_t)p_data,
                                          (2UL * size_half_word), HAL_DMA_OPT_IT_HT);

  if (status == HAL_OK)
  {
    LL_FMAC_Enable_DMAReq_and_IT(p_fmacx, LL_FMAC_DMA_READ, LL_FMAC_IT_UNFL);
  }
  else
  {
    hfmac->y_state = HAL_FMAC_STATE_Y_IDLE;
  }

  return status;
}

/**
  * @brief  Read data from Y in DMA mode. Global state must be IDLE (START = 0).
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_data            Pointer to output data
  * @param  size_half_word    Size of the output data.
  * @param  opt_it            Optional interruption can be a combination of
  *                           @ref HAL_FMAC_OPT_DMA_Y_IT_NONE
  *                           @ref HAL_FMAC_OPT_DMA_Y_IT_HT
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_ReadY_DMA_Opt(hal_fmac_handle_t *hfmac, int16_t *p_data, uint32_t size_half_word,
                                    uint32_t opt_it)
{
  hal_status_t status;
  FMAC_TypeDef *p_fmacx;

  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_half_word != 0UL);
  ASSERT_DBG_PARAM(IS_FMAC_OPT_DMA_IT_Y(opt_it));
  ASSERT_DBG_STATE(hfmac->global_state, HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->y_state, HAL_FMAC_STATE_Y_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_half_word == 0UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, y_state, HAL_FMAC_STATE_Y_IDLE, HAL_FMAC_STATE_Y_ACTIVE_READ);

  p_fmacx = FMAC_GET_INSTANCE(hfmac);

  /* Prepare DMA read xfer */
  hfmac->hdma_y->p_xfer_halfcplt_cb = FMAC_DMAReadYHalfCpltCallback;
  hfmac->hdma_y->p_xfer_cplt_cb = FMAC_DMAReadYCpltCallback;
  hfmac->hdma_y->p_xfer_error_cb = FMAC_DMAError;

  status = HAL_DMA_StartPeriphXfer_IT_Opt(hfmac->hdma_y, (uint32_t)&p_fmacx->RDATA, (uint32_t)p_data,
                                          (2UL * size_half_word), opt_it);

  if (status == HAL_OK)
  {
    LL_FMAC_Enable_DMAReq_and_IT(p_fmacx, LL_FMAC_DMA_READ, LL_FMAC_IT_UNFL);
  }
  else
  {
    hfmac->y_state = HAL_FMAC_STATE_Y_IDLE;
  }

  return status;
}
#endif /* USE_HAL_FMAC_DMA */

/**
  * @brief  Start write data to X1 is directly driven by a timer or other peripheral such as an ADC.
  *         Overflow error interruption is activated
  * @param  hfmac    Pointer to a hal_fmac_handle_t
  * @retval HAL_BUSY Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_OK   Operation completed successfully
  */
hal_status_t HAL_FMAC_LockX1WriteAccessForExternPeriph(hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->x1_state, HAL_FMAC_STATE_X1_IDLE);

  HAL_CHECK_UPDATE_STATE(hfmac, x1_state, HAL_FMAC_STATE_X1_IDLE, HAL_FMAC_STATE_X1_ACTIVE_WRITE);

  LL_FMAC_EnableIT_OVFL(FMAC_GET_INSTANCE(hfmac));

  return HAL_OK;
}

/**
  * @brief  Stop write data to X1 directly driven by a timer or other peripheral such as an ADC.
  * @param  hfmac  Pointer to a hal_fmac_handle_t
  * @retval HAL_OK Operation completed successfully
  */
hal_status_t HAL_FMAC_UnlockX1WriteAccessForExternPeriph(hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->x1_state, HAL_FMAC_STATE_X1_ACTIVE_WRITE);

  LL_FMAC_DisableIT_OVFL(FMAC_GET_INSTANCE(hfmac));

  hfmac->x1_state = HAL_FMAC_STATE_X1_IDLE;

  return HAL_OK;
}

/**
  * @brief  Start read data from Y driven by a timer or other peripheral such as an DAC.
  *         Underflow error interruption is activated
  * @param  hfmac    Pointer to a hal_fmac_handle_t
  * @retval HAL_BUSY Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_OK   Operation completed successfully
  */
hal_status_t HAL_FMAC_LockYReadAccessForExternPeriph(hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->y_state, HAL_FMAC_STATE_Y_IDLE);

  HAL_CHECK_UPDATE_STATE(hfmac, y_state, HAL_FMAC_STATE_Y_IDLE, HAL_FMAC_STATE_Y_ACTIVE_READ);

  LL_FMAC_EnableIT_UNFL(FMAC_GET_INSTANCE(hfmac));

  return HAL_OK;
}

/**
  * @brief  Stop read data from Y driven by a timer or other peripheral such as an DAC.
  * @param  hfmac  Pointer to a hal_fmac_handle_t
  * @retval HAL_OK Operation completed successfully
  */
hal_status_t HAL_FMAC_UnlockYReadAccessForExternPeriph(hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->y_state, HAL_FMAC_STATE_Y_ACTIVE_READ);

  LL_FMAC_DisableIT_UNFL(FMAC_GET_INSTANCE(hfmac));

  hfmac->y_state = HAL_FMAC_STATE_Y_IDLE;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group6 Callback functions
  * @{
This section provides Interruption and DMA callback functions:
 - The HAL_FMAC_WriteX1CpltCallback() function is called when the write of X1 buffer is complete.
 - The HAL_FMAC_WriteX1HalfCpltCallback() function is called when the write ofX1 buffer is half complete (DMA only).
 - The HAL_FMAC_ReadYCpltCallback() function is called when the read of Y buffer is complete.
 - The HAL_FMAC_ReadYHalfCpltCallback() function is called when the read of Y buffer is half complete (DMA only).
 - The HAL_FMAC_ErrorCallback() function is called in case of an error, there are four possible errors :
   - X1 buffer overflow
   - Y buffer underflow
   - Saturation of the accumulator
   - DMA error
 - The HAL_FMAC_PreloadCpltCallback() function is called when the preload is complete.

 - Call HAL_FMAC_RegisterWriteX1CpltCallback() to register the FMAC Write X1 complete callback.
 - Call HAL_FMAC_RegisterReadYCpltCallback() to register the FMAC Read Y complete callback (DMA only).
 - Call HAL_FMAC_RegisterWriteX1HalfCpltCallback() to register the FMAC Write X1 Half complete callback.
 - Call HAL_FMAC_RegisterReadYHalfCpltCallback() to register the FMAC Read Y Half complete callback (DMA only).
 - Call HAL_FMAC_RegisterErrorCallback() to register the FMAC error callback.
 - Call HAL_FMAC_RegisterPreloadCpltCallback() to register the FMAC Preload complete callback.
  */

/**
  * @brief  FMAC error callback : It can be a combination of X1 buffer overflow, Y buffer underflow, Saturation of the
  *         accumulator or DMA error.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @note   Use HAL_FMAC_GetLastErrorCodes() to get the error codes.
  */
__WEAK void HAL_FMAC_ErrorCallback(hal_fmac_handle_t *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfmac);

  /* WARNING : This function must not be modified; when the callback is needed,
               the HAL_FMAC_ErrorCallback can be implemented in the user file.
   */
}

/**
  * @brief  Write X1 buffer complete callback.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  */
__WEAK void HAL_FMAC_WriteX1CpltCallback(hal_fmac_handle_t *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfmac);

  /* WARNING : This function must not be modified; when the callback is needed,
               the HAL_FMAC_WriteX1CpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  Read Y buffer complete callback.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  */
__WEAK void HAL_FMAC_ReadYCpltCallback(hal_fmac_handle_t *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfmac);

  /* WARNING : This function must not be modified; when the callback is needed,
               the HAL_FMAC_ReadYCpltCallback can be implemented in the user file.
   */
}

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
/**
  * @brief  Write X1 buffer half complete callback.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  */
__WEAK void HAL_FMAC_WriteX1HalfCpltCallback(hal_fmac_handle_t *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfmac);

  /* WARNING : This function must not be modified; when the callback is needed,
               the HAL_FMAC_WriteX1HalfCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  Read Y buffer half complete callback.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  */
__WEAK void HAL_FMAC_ReadYHalfCpltCallback(hal_fmac_handle_t *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfmac);

  /* WARNING : This function must not be modified; when the callback is needed,
               the HAL_FMAC_ReadYHalfCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  FMAC preload buffer complete callback.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  */
__WEAK void HAL_FMAC_PreloadCpltCallback(hal_fmac_handle_t *hfmac)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfmac);

  /* WARNING : This function must not be modified; when the callback is needed,
               the HAL_FMAC_PreloadCpltCallback can be implemented in the user file.
   */
}
#endif /* USE_HAL_FMAC_DMA */

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the FMAC Write X1 complete callback.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_callback        User callback
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_RegisterWriteX1CpltCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_INIT | (uint32_t)HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->x1_state, (uint32_t)HAL_FMAC_STATE_X1_RESET | (uint32_t)HAL_FMAC_STATE_X1_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hfmac->p_write_x1_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the FMAC Read Y complete callback.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_callback        User callback
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_RegisterReadYCpltCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_INIT | (uint32_t)HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->y_state, (uint32_t)HAL_FMAC_STATE_Y_RESET | (uint32_t)HAL_FMAC_STATE_Y_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hfmac->p_read_y_cplt_cb = p_callback;

  return HAL_OK;
}

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
/**
  * @brief  Register the FMAC Write X1 Half complete callback callback.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_callback        User callback
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_RegisterWriteX1HalfCpltCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_INIT | (uint32_t)HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->x1_state, (uint32_t)HAL_FMAC_STATE_X1_RESET | (uint32_t)HAL_FMAC_STATE_X1_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hfmac->p_write_x1_half_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the FMAC Read Y Half complete callback.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_callback        User callback
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_RegisterReadYHalfCpltCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_INIT | (uint32_t)HAL_FMAC_STATE_IDLE);
  ASSERT_DBG_STATE(hfmac->y_state, (uint32_t)HAL_FMAC_STATE_Y_RESET | (uint32_t)HAL_FMAC_STATE_Y_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hfmac->p_read_y_half_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the FMAC Preload complete callback.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_callback        User callback
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_RegisterPreloadCpltCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_INIT | (uint32_t)HAL_FMAC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hfmac->p_preload_cplt_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_FMAC_DMA */

/**
  * @brief  Register the FMAC error callback.
  * @param  hfmac             Pointer to a hal_fmac_handle_t
  * @param  p_callback        User callback
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_OK            Operation completed successfully
  */
hal_status_t HAL_FMAC_RegisterErrorCallback(hal_fmac_handle_t *hfmac, hal_fmac_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t)HAL_FMAC_STATE_INIT | (uint32_t)HAL_FMAC_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hfmac->p_error_cb = p_callback;

  return HAL_OK;
}

#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group7 IRQ handler management
  * @{
This section provides:
 - the main FMAC IRQ handler HAL_FMAC_IRQHandler().
 - Smaller FMAC IRQ handler HAL_FMAC_ERROR_IRQHandler() applicable instead of HAL_FMAC_IRQHandler() when neither
   HAL_FMAC_WriteX1_IT nor HAL_FMAC_ReadY_IT processes are used.

Depending on the process function one's use, different callback might be triggered:

| Process API \n \ \n Callbacks   | HAL_FMAC_WriteX1_IT           | HAL_FMAC_ReadY_IT             |
|---------------------------------|:-----------------------------:|:-----------------------------:|
| HAL_FMAC_WriteX1CpltCallback    |               x               |                               |
| HAL_FMAC_ReadYCpltCallback      |                               |              x                |
| HAL_FMAC_ErrorCallback          |               x               |              x                |

| Process API \n \ \n Callbacks      | HAL_FMAC_WriteX1_DMA       | HAL_FMAC_ReadY_DMA            |
|---------------------------------   |:--------------------------:|:-----------------------------:|
| HAL_FMAC_WriteX1CpltCallback       |               x            |                               |
| HAL_FMAC_ReadYCpltCallback         |                            |               x               |
| HAL_FMAC_WriteX1HalfCpltCallback*  |               x            |                               |
| HAL_FMAC_ReadYHalfCpltCallback*    |                            |               x               |
| HAL_FMAC_ErrorCallback**           |               x            |               x               |

| Process API \n \ \n Callbacks      | HAL_FMAC_PreloadX1_DMA        | HAL_FMAC_PreloadY_DMA         |
|---------------------------------   |:-----------------------------:|:-----------------------------:|
| HAL_FMAC_ErrorCallback**           |               x               |               x               |
| HAL_FMAC_PreloadCpltCallback**     |               x               |               x               |

@note * these callbacks might be called following DMA IRQ management, not FMAC IRQ management.
@note ** these callbacks might be called following DMA IRQ management, or FMAC IRQ management.

| Process API \n \ \n Callbacks      | HAL_FMAC_WriteX1_DMA_Opt   | HAL_FMAC_ReadY_DMA_Opt        |
|---------------------------------   |:--------------------------:|:-----------------------------:|
| HAL_FMAC_WriteX1CpltCallback       |               x            |                               |
| HAL_FMAC_ReadYCpltCallback         |                            |               x               |
| HAL_FMAC_WriteX1HalfCpltCallback*  |               x            |                               |
| HAL_FMAC_ReadYHalfCpltCallback*    |                            |               x               |
| HAL_FMAC_ErrorCallback**           |               x            |               x               |

@note * these callbacks might be called following DMA IRQ management, not FMAC IRQ management.
@note ** these callbacks might be called following DMA IRQ management, or FMAC IRQ management.
  */

/**
  * @brief  FMAC interrupt request HANDLER.
  *         All FMAC interrupts are managed.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  */
void HAL_FMAC_IRQHandler(hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);

  const FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);
  uint32_t reg_sr = LL_FMAC_READ_REG(p_fmacx, SR);
  uint32_t reg_cr = LL_FMAC_READ_REG(p_fmacx, CR);

  if (((reg_cr & FMAC_CR_WIEN) != 0U) && ((reg_sr & FMAC_SR_X1FULL) == 0U))
  {
    /* Write interrupt, fill x1_buf with threshold value (1, 2, 4 or 8) */
    FMAC_WriteDataIncrPtr(hfmac);
  }

  if (((reg_cr & FMAC_CR_RIEN) != 0U) && ((reg_sr & FMAC_SR_YEMPTY) == 0U))
  {
    /* Read interrupt, read from Y with threshold value (1, 2, 4 or 8) */
    FMAC_ReadDataIncrPtr(hfmac);
  }

  uint32_t errors = (reg_cr & (reg_sr >> 6)) & LL_FMAC_IT_ERROR_ALL;

  if (errors != 0U)
  {
#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
    hfmac->last_error_codes |= errors;
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */

    (void) FMAC_Abort(hfmac);

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
    hfmac->p_error_cb(hfmac);
#else
    HAL_FMAC_ErrorCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
  }
}

/**
  * @brief FMAC interrupt request HANDLER limited to error management.
  *        Errors FMAC interrupts only are managed.
  *        It is applicable instead of HAL_FMAC_IRQHandler when neither HAL_FMAC_WriteX1_IT nor HAL_FMAC_ReadY_IT
  *        processes are used.
  * @param hfmac Pointer to a hal_fmac_handle_t
  */
void HAL_FMAC_ERROR_IRQHandler(hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);

  const FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);
  uint32_t reg_sr = LL_FMAC_READ_REG(p_fmacx, SR);
  uint32_t reg_cr = LL_FMAC_READ_REG(p_fmacx, CR);

  uint32_t errors = (reg_cr & (reg_sr >> 6)) & LL_FMAC_IT_ERROR_ALL;

  if (errors != 0U)
  {
#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
    hfmac->last_error_codes |= errors;
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */

    (void) FMAC_Abort(hfmac);

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
    hfmac->p_error_cb(hfmac);
#else
    HAL_FMAC_ErrorCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
  }
}

/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group8 Peripheral State and Error functions
  * @{
This section provides a set of functions allowing to :
  - Get the current state of the filter process by calling HAL_FMAC_GetState().
  - Get state of the X1 Write process by calling HAL_FMAC_GetX1State().
  - Get state of the Y Read process by calling HAL_FMAC_GetYState().
  - Get the FMAC last error codes (X1 overflow, Y underflow Saturation and DMA) by calling HAL_FMAC_GetLastErrorCodes().
  */

/**
  * @brief  Return the FMAC filter process state.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @retval hal_fmac_state_t FMAC filter state
  */
hal_fmac_state_t HAL_FMAC_GetState(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);

  return hfmac->global_state;
}

/**
  * @brief  Return the HAL FMAC X1 process state.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @retval hal_fmac_x1_state_t FMAC X1 process state
  */
hal_fmac_x1_state_t HAL_FMAC_GetX1State(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);

  return hfmac->x1_state;
}

/**
  * @brief  Return the HAL FMAC Y process state.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @retval hal_fmac_y_state_t FMAC Y process state
  */
hal_fmac_y_state_t HAL_FMAC_GetYState(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);

  return hfmac->y_state;
}

#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
/**
  * @brief  Return the errors limited to the last process.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @retval uint32_t last error code. It can be HAL_FMAC_ERROR_NONE or a combination of @ref FMAC_Error_Codes
  */
uint32_t HAL_FMAC_GetLastErrorCodes(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t) HAL_FMAC_STATE_INIT | (uint32_t) HAL_FMAC_STATE_IDLE
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_PRELOAD
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_FILTER);

  return hfmac->last_error_codes;
}
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */

/**
  * @}
  */

#if defined(USE_HAL_FMAC_USER_DATA) && (USE_HAL_FMAC_USER_DATA == 1)
/** @addtogroup FMAC_Exported_Functions_Group9 Set/Get user data
  * @{
This section provides a set of functions allowing to manage a user data pointer stored to the FMAC handle:
 - HAL_FMAC_SetUserData() Set the user data into the handle
 - HAL_FMAC_GetUserData() Get the user data from the handle
  */

/**
  * @brief  Set the user data pointer into the handle.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @param  p_user_data Pointer to the user data.
  */
void HAL_FMAC_SetUserData(hal_fmac_handle_t *hfmac, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t) HAL_FMAC_STATE_INIT | (uint32_t) HAL_FMAC_STATE_IDLE
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_PRELOAD
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_FILTER);

  hfmac->p_user_data = p_user_data;
}

/**
  * @brief  Get the user data pointer from the handle.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  * @retval void* Pointer to the user data
  */
const void *HAL_FMAC_GetUserData(const hal_fmac_handle_t *hfmac)
{
  ASSERT_DBG_PARAM(hfmac != NULL);
  ASSERT_DBG_STATE(hfmac->global_state, (uint32_t) HAL_FMAC_STATE_INIT | (uint32_t) HAL_FMAC_STATE_IDLE
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_PRELOAD
                   | (uint32_t) HAL_FMAC_STATE_ACTIVE_FILTER);

  return (hfmac->p_user_data);
}

/**
  * @}
  */
#endif /* USE_HAL_FMAC_USER_DATA */

/**
  * @}
  */

/** @addtogroup FMAC_Private_Functions
  * @{
  */

/**
  * @brief  Write data into FMAC internal memory through WDATA.
  * @param  hfmac          Pointer to a hal_fmac_handle_t
  * @param  p_data         Pointer to the data buffer
  * @param  size_half_word Size of the data buffer
  * @retval HAL_ERROR      Operation completed with error
  * @retval HAL_OK         Operation completed successfully
  */
static hal_status_t FMAC_PreloadWrite(hal_fmac_handle_t *hfmac, const int16_t *p_data,
                                      uint32_t size_half_word)
{
  const int16_t *p_data_tmp = p_data;
  FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);

  /* Load the buffer into the 16-bits internal memory */
  for (uint32_t index = size_half_word; index > 0U; index--)
  {
    LL_FMAC_WriteData(p_fmacx, *p_data_tmp);
    p_data_tmp++;

    if (LL_FMAC_IsActiveFlag_OVFL(p_fmacx) != 0UL)
    {
#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
      hfmac->last_error_codes |= HAL_FMAC_ERROR_OVERFLOW;
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */
      (void) FMAC_Abort(hfmac);

      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Handle FMAC Function wait auto end of function.
  * @param  hfmac     Pointer to a hal_fmac_handle_t
  * @retval HAL_ERROR Operation completed with error
  * @retval HAL_OK    Operation completed successfully
  */
static hal_status_t FMAC_PreloadWaitStartReset(hal_fmac_handle_t *hfmac)
{
  FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);
  hal_status_t status = HAL_OK;

  /* Init tick_start for timeout management */
  uint32_t tick_start = HAL_GetTick();

  /* Wait until START flag changes */
  while (LL_FMAC_IsEnabledStart(p_fmacx) != 0UL)
  {
    if ((HAL_GetTick() - tick_start) > FMAC_TIMEOUT_VALUE)
    {
      if (LL_FMAC_IsEnabledStart(p_fmacx) != 0UL)
      {
#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
        hfmac->last_error_codes |= HAL_FMAC_ERROR_PRELOAD_TIMEOUT;
#else
        STM32_UNUSED(hfmac);
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */
        status = HAL_ERROR;
      }
      break;
    }
  }

  return status;
}

/**
  * @brief  Write available input data in interrupt mode,
  *         the number of data is equal to the threshold value.
  * @param  hfmac Pointer to a hal_fmac_handle_t
  */
static void FMAC_WriteDataIncrPtr(hal_fmac_handle_t *hfmac)
{
  FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);
  uint32_t threshold = FMAC_GET_THRESHOLD_FROM_WM(LL_FMAC_GetX1FullWatermark(p_fmacx));

  for (uint32_t i = 0; i < threshold; i++)
  {
    LL_FMAC_WriteData(p_fmacx, *hfmac->p_input);
    hfmac->p_input++;
    hfmac->input_size_half_word--;
    if (hfmac->input_size_half_word == 0U)
    {
      /* Disable write interrupt */
      LL_FMAC_DisableIT(p_fmacx, LL_FMAC_IT_W | LL_FMAC_IT_OVFL);

      hfmac->x1_state = HAL_FMAC_STATE_X1_IDLE;

      /* Write complete callback */
#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
      hfmac->p_write_x1_cplt_cb(hfmac);
#else
      HAL_FMAC_WriteX1CpltCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
      break;
    }
  }
}

/**
  * @brief  Read available output data in interrupt mode,
  *         the number of data is equal to the threshold value.
  * @param  hfmac Pointer to a hal_fmac_handle_t.
  */
static void FMAC_ReadDataIncrPtr(hal_fmac_handle_t *hfmac)
{
  FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);
  uint32_t threshold = FMAC_GET_THRESHOLD_FROM_WM(LL_FMAC_GetYEmptyWatermark(p_fmacx));

  for (uint32_t i = 0; i < threshold; i++)
  {
    *hfmac->p_output = LL_FMAC_ReadData(p_fmacx);
    hfmac->p_output++;
    hfmac->output_size_half_word--;
    if (hfmac->output_size_half_word == 0U)
    {
      /* Disable read interrupt */
      LL_FMAC_DisableIT(p_fmacx, LL_FMAC_IT_R | LL_FMAC_IT_UNFL);

      hfmac->y_state = HAL_FMAC_STATE_Y_IDLE;

      /* Read complete callback */
#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
      hfmac->p_read_y_cplt_cb(hfmac);
#else
      HAL_FMAC_ReadYCpltCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
      break;
    }
  }
}

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
/**
  * @brief  DMA FMAC communication error callback.
  * @param  hdma Pointer to DMA handle.
  */
static void FMAC_DMAError(hal_dma_handle_t *hdma)
{
  hal_fmac_handle_t *hfmac = (hal_fmac_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
  hfmac->last_error_codes |= HAL_FMAC_ERROR_DMA;
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */

  (void) FMAC_Abort(hfmac);

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->p_error_cb(hfmac);
#else
  HAL_FMAC_ErrorCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA FMAC Input Data process half complete callback.
  * @param  hdma Pointer toDMA handle.
  */
static void FMAC_DMAWriteX1HalfCpltCallback(hal_dma_handle_t *hdma)
{
  hal_fmac_handle_t *hfmac = (hal_fmac_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->p_write_x1_half_cplt_cb(hfmac);
#else
  HAL_FMAC_WriteX1HalfCpltCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA FMAC Input Data process complete callback.
  * @param  hdma Pointer toDMA handle.
  */
static void FMAC_DMAWriteX1CpltCallback(hal_dma_handle_t *hdma)
{
  hal_fmac_handle_t *hfmac = (hal_fmac_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check if DMA in circular mode*/
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
  {
    FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);
    LL_FMAC_Disable_DMAReq_and_IT(p_fmacx, LL_FMAC_DMA_READ, LL_FMAC_IT_UNFL);
  }
#else /* USE_HAL_DMA_LINKEDLIST */
  FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);
  LL_FMAC_Disable_DMAReq_and_IT(p_fmacx, LL_FMAC_DMA_READ, LL_FMAC_IT_UNFL);
  hfmac->x1_state = HAL_FMAC_STATE_X1_IDLE;
#endif /* USE_HAL_DMA_LINKEDLIST */

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->p_write_x1_cplt_cb(hfmac);
#else
  HAL_FMAC_WriteX1CpltCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA FMAC Output Data process half complete callback.
  * @param  hdma Pointer to DMA handle.
  */
static void FMAC_DMAReadYHalfCpltCallback(hal_dma_handle_t *hdma)
{
  hal_fmac_handle_t *hfmac = (hal_fmac_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->p_read_y_half_cplt_cb(hfmac);
#else
  HAL_FMAC_ReadYHalfCpltCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA FMAC Output Data process complete callback.
  * @param  hdma Pointer to DMA handle.
  */
static void FMAC_DMAReadYCpltCallback(hal_dma_handle_t *hdma)
{
  hal_fmac_handle_t *hfmac = (hal_fmac_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check if DMA in circular mode*/
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
  {
    FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);
    LL_FMAC_Disable_DMAReq_and_IT(p_fmacx, LL_FMAC_DMA_READ, LL_FMAC_IT_UNFL);
  }
#else /* USE_HAL_DMA_LINKEDLIST */
  FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);
  LL_FMAC_Disable_DMAReq_and_IT(p_fmacx, LL_FMAC_DMA_READ, LL_FMAC_IT_UNFL);

  hfmac->y_state = HAL_FMAC_STATE_Y_IDLE;
#endif /* USE_HAL_DMA_LINKEDLIST */

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->p_read_y_cplt_cb(hfmac);
#else
  HAL_FMAC_ReadYCpltCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA FMAC Filter Configuration process complete callback.
  * @param  hdma Pointer to DMA handle.
  */
static void FMAC_DMAPreloadCpltCallback(hal_dma_handle_t *hdma)
{
  hal_fmac_handle_t *hfmac = (hal_fmac_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check if DMA in circular mode*/
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);
    LL_FMAC_Disable_DMAReq_and_IT(p_fmacx, LL_FMAC_DMA_WRITE, LL_FMAC_IT_OVFL);
  }

  hfmac->global_state = HAL_FMAC_STATE_IDLE;

#if defined(USE_HAL_FMAC_REGISTER_CALLBACKS) && (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  hfmac->p_preload_cplt_cb(hfmac);
#else
  HAL_FMAC_PreloadCpltCallback(hfmac);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_FMAC_DMA */

/**
  * @brief  Preload fifo buffer X1 or Y.
  * @param  hfmac             Pointer to FMAC HAL instance.
  * @param  func_load         load function bits and start bit : (LL_FMAC_FUNC_LOAD_X1 | FMAC_PARAM_START) or
  *                           (LL_FMAC_FUNC_LOAD_Y | FMAC_PARAM_START)
  * @param  p_data            Pointer to data to preload
  * @param  size_half_word    Size in half word
  * @retval HAL_INVALID_PARAM p_data is NULL
  * @retval HAL_BUSY          Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_ERROR         Operation completed with error
  * @retval HAL_OK            Operation completed successfully
  */
static hal_status_t FMAC_PreloadFifo(hal_fmac_handle_t *hfmac, uint32_t func_load, const int16_t *p_data,
                                     uint32_t size_half_word)
{
  hal_status_t hal_status = HAL_ERROR;
  FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL) /* if size_byte is equals to 0 p_data equals to NULL is allowed */
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, global_state, HAL_FMAC_STATE_IDLE, HAL_FMAC_STATE_ACTIVE_PRELOAD);

#if defined(USE_HAL_FMAC_GET_LAST_ERRORS) && (USE_HAL_FMAC_GET_LAST_ERRORS == 1)
  hfmac->last_error_codes = 0;
#endif /* USE_HAL_FMAC_GET_LAST_ERRORS */

  /* Write number of values to be loaded, the data load function and start the operation */
  LL_FMAC_WRITE_REG(p_fmacx, PARAM, (((uint32_t)size_half_word << FMAC_PARAM_P_Pos) | func_load));

  /* Load the buffer into the 16-bits internal memory */
  if (FMAC_PreloadWrite(hfmac, p_data, size_half_word) == HAL_OK)
  {
    hal_status = FMAC_PreloadWaitStartReset(hfmac);
  }

  hfmac->global_state = HAL_FMAC_STATE_IDLE;

  return hal_status;
}

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
/**
  * @brief  Preload buffer X1 or Y with DMA.
  * @param  hfmac          Pointer to a hal_fmac_handle_t
  * @param  func_load      load function bits and start bit : (LL_FMAC_FUNC_LOAD_X1 | FMAC_PARAM_START) or
  *                        (LL_FMAC_FUNC_LOAD_Y | FMAC_PARAM_START)
  * @param  p_data         Pointer to data to preload
  * @param  size_half_word Size in half word
  * @retval HAL_ERROR      Operation completed with error
  * @retval HAL_BUSY       Concurrent process ongoing. Returned by HAL_CHECK_UPDATE_STATE
  * @retval HAL_OK         Operation completed successfully
  */
static hal_status_t FMAC_PreloadFifo_DMA(hal_fmac_handle_t *hfmac, uint32_t func_load, const int16_t *p_data,
                                         uint32_t size_half_word)
{
  FMAC_TypeDef *p_fmacx;
  hal_status_t hal_status;

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL) /* if size_byte is equals to 0 p_data equals to NULL is allowed */
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hfmac, global_state, HAL_FMAC_STATE_IDLE, HAL_FMAC_STATE_ACTIVE_PRELOAD);

  p_fmacx = FMAC_GET_INSTANCE(hfmac);

  hfmac->hdma_x1->p_xfer_cplt_cb = FMAC_DMAPreloadCpltCallback;
  hfmac->hdma_x1->p_xfer_error_cb = FMAC_DMAError;

  hal_status = HAL_DMA_StartPeriphXfer_IT_Opt(hfmac->hdma_x1, (uint32_t)p_data, (uint32_t)&p_fmacx->WDATA,
                                              (2UL * size_half_word), HAL_DMA_OPT_IT_NONE);

  if (hal_status == HAL_OK)
  {
    LL_FMAC_Enable_DMAReq_and_IT(p_fmacx, LL_FMAC_DMA_WRITE, LL_FMAC_IT_OVFL);

    /* Write number of values to be loaded, the data load function and start the operation */
    LL_FMAC_WRITE_REG(p_fmacx, PARAM, (((uint32_t)size_half_word << FMAC_PARAM_P_Pos) | func_load));
  }
  else
  {
    hfmac->global_state = HAL_FMAC_STATE_IDLE;
  }

  return hal_status;
}
#endif /* USE_HAL_FMAC_DMA */

/**
  * @brief  Reset the write and read pointers, the internal control logic, the FMAC_SR register and
  *         the FMAC_PARAM register, including the START bit if active.
  *         Disable all interrupts.
  *         All DMA are aborted.
  *         X1, Y and Filter are put in IDLE state.
  *         After the stop, user must preload data, start a writeX1 process, start a readY process and start filter.
  * @param  hfmac     Pointer to a hal_fmac_handle_t
  * @retval HAL_ERROR Operation completed with error
  * @retval HAL_OK    Operation completed successfully
  */
static hal_status_t FMAC_Abort(hal_fmac_handle_t *hfmac)
{
  uint32_t timeout = FMAC_RESET_TIMEOUT_VALUE;
  FMAC_TypeDef *p_fmacx = FMAC_GET_INSTANCE(hfmac);

  /* Perform the reset, stop the filter */
  LL_FMAC_EnableReset(p_fmacx);

  /* Wait until flag is reset (2 or 3 AHB cycles max) */
  while (LL_FMAC_IsEnabledReset(p_fmacx) != 0U)
  {
    if (timeout-- == 0U)
    {
      return HAL_ERROR;
    }
  }

  LL_FMAC_DisableIT(p_fmacx, LL_FMAC_IT_ALL);

#if defined(USE_HAL_FMAC_DMA) && (USE_HAL_FMAC_DMA == 1)
  if (LL_FMAC_IsEnabledDMAReq_WRITE(p_fmacx) != 0U)
  {
    LL_FMAC_DisableDMAReq_WRITE(p_fmacx);
    (void)HAL_DMA_Abort(hfmac->hdma_x1);
  }

  if (LL_FMAC_IsEnabledDMAReq_READ(p_fmacx) != 0U)
  {
    LL_FMAC_DisableDMAReq_READ(p_fmacx);
    (void)HAL_DMA_Abort(hfmac->hdma_y);
  }
#endif /* USE_HAL_FMAC_DMA */

  hfmac->x1_state = HAL_FMAC_STATE_X1_IDLE;
  hfmac->y_state = HAL_FMAC_STATE_Y_IDLE;
  hfmac->global_state = HAL_FMAC_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

#endif /* USE_HAL_FMAC_MODULE */
#endif /* FMAC1 || FMAC2 */

/**
  * @}
  */

/**
  * @}
  */
