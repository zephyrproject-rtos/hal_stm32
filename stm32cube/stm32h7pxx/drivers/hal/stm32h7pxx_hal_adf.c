/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_adf.c
  * @brief   ADF HAL module driver.
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

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */
#if defined (ADF1)
#if defined(USE_HAL_ADF_MODULE) && (USE_HAL_ADF_MODULE == 1)

/** @addtogroup ADF
  * @{
  */
/** @defgroup ADF_Introduction ADF Introduction
  * @{

  - The ADF hardware abstraction layer provides a set of APIs to interface with the STM32 ADF
  (Audio Digital Filter) peripheral.

  - The ADF peripheral is a high-performance module dedicated to the connection of external sigma-delta modulators.
  It is mainly used for audio capture signals and metering applications.

  - This abstraction layer simplifies peripheral configuration, initialization and management and supports polling,
  interrupt and DMA modes for data acquisitions.

  - This abstraction layer ensures portability and ease of use across different STM32 series.

  */
/**
  * @}
  */

/** @defgroup ADF_How_To_Use ADF How To Use
  * @{

# How to use the HAL ADF driver

## The HAL ADF driver can be used as follows:

ADFx HW IP is composed of a common clock generator and blocks.
Each block is composed of sub-blocks:
  - a serial interface.
  - a bitstream matrix.
  - a digital filter.
  - a sound activity detector.

Configuration and activation of common clock generator must be first performed.

### Common clock generator usage

1. Declare a hal_adf_handle_t handle structure and initialize the ADFx driver with a ADFx HW instance by calling
   the HAL_ADF_Init().
   The ADFx clock is enabled inside the HAL_ADF_Init() if USE_HAL_ADF_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.

2. Configure the low level hardware (GPIO, CLOCK, NVIC, DMA...):
  - Enable the ADFx clock if USE_HAL_ADF_CLK_ENABLE_MODEL = HAL_CLK_ENABLE_NO.
  - ADFx pins configuration:
    - Enable the clock for the ADFx GPIOs
    - Configure ADFx pins as alternate function pull-up
  - NVIC configuration if you need to use interrupt process
    - Configure the ADFx interrupt priority.
    - Enable the NVIC ADFx IRQ handle.
  - DMA configuration if you need to use DMA process
    - Declare a DMA handle structure.
    - Enable the DMAx clock.
    - Configure the declared DMA handle structure with the required parameters.
    - Associate the initialized DMA handle to the ADF DMA handle using HAL_ADF_SetDMA().
    - Configure the corresponding NVIC line priority and enable it.
  - ADFx kernel source clock has to be activated and selected.

3. Configure the processing clock divider by calling HAL_ADF_SetConfig().

4. Configure and/or enable advanced features.
   All these advanced configurations are optional (not mandatory) and concerns mainly
   output clocks (for instance by calling HAL_ADF_SetConfigOutputClock() and HAL_ADF_EnableOutputClock()).

5. Activate the clock generator by calling HAL_ADF_Start().

### Serial interface usage

1. Configure mode, clock source and threshold of a serial interface by calling HAL_ADF_SITF_SetConfig().

2. Activate a serial interface by calling HAL_ADF_SITF_Start().

3. Clock absence detection feature is available on each serial interface and can be used:
  - By calling HAL_ADF_SITF_IsClockAbsenceDetected in polling mode.
  - By calling HAL_ADF_SITF_StartClockAbsenceDetect_IT in interrupt mode.

### Bitstream matrix usage

Connect one serial interface to a bitstream matrix and select edge by calling HAL_ADF_BSMX_SetConfig().

### Digital filter usage

1. Configure data source, CIC mode, decimation ratio, gain, acquisition mode and trigger parameters
   of a digital filter by calling HAL_ADF_DFLT_SetConfig().

2. Configure and/or enable advanced features.
   All these advanced configurations are optional (not mandatory) and concerns:
  - Samples delay by calling HAL_ADF_DFLT_SetSamplesDelay().
  - FIFO threshold by calling HAL_ADF_DFLT_SetFifoThreshold().
  - Discard samples by calling HAL_ADF_DFLT_SetDiscardSamples().
  - Reshape filter by calling HAL_ADF_DFLT_EnableReshapeFilter().
  - High-pass filter by calling HAL_ADF_DFLT_EnableHighPassFilter().

3. Acquisitions.
  - Polling mode:
    - Start acquisition by calling HAL_ADF_DFLT_StartAcq().
    - Wait for the end of acquisition by calling HAL_ADF_DFLT_PollForAcq().
    - Get acquisition value by calling HAL_ADF_DFLT_GetAcqValue().
    - Stop acquisition by calling HAL_ADF_DFLT_StopAcq().

  - Interrupt mode:
    - Start acquisition by calling HAL_ADF_DFLT_StartAcq_IT() or HAL_ADF_DFLT_StartAcq_IT_Opt().
    - Wait for the end of acquisition (HAL_ADF_DFLT_AcqCpltCallback() occurrence).
    - Get acquisition value by calling HAL_ADF_DFLT_GetAcqValue().
    - Stop acquisition by calling HAL_ADF_DFLT_StopAcq_IT().

  - DMA mode:
    - Start acquisition by calling HAL_ADF_DFLT_StartAcq_DMA() or HAL_ADF_DFLT_StartAcq_DMA_Opt().
    - Wait for acquisitions (HAL_ADF_DFLT_AcqHalfCpltCallback() and HAL_ADF_DFLT_AcqCpltCallback() occurrences).
    - Stop acquisition by calling HAL_ADF_DFLT_StopAcq_DMA().

### Sound activity detector usage

1. Configure mode, memory transfer, trigger event and minimum ambient noise level by calling HAL_ADF_SAD_SetConfig().

2. Configure and/or enable advanced features.
   All these advanced configurations are optional (not mandatory) and concerns:
  - Frame size by calling HAL_ADF_SAD_SetFrameSize().
  - Learning frames by calling HAL_ADF_SAD_SetLearningFrames().
  - Signal to noise threshold by calling HAL_ADF_SAD_SetSignalToNoiseThreshold().
  - Ambient noise slope by calling HAL_ADF_SAD_SetAmbientNoiseSlope().
  - Hangover time window by calling HAL_ADF_SAD_SetHangoverTimeWindow().
  - Hysteresis by calling HAL_ADF_SAD_EnableHysteresis().

3. Activate a sound activity detector::
  - By calling HAL_ADF_SAD_Start() in polling mode.
  - By calling HAL_ADF_SAD_Start_IT() or HAL_ADF_SAD_Start_IT_Opt() in interrupt mode.

### Callbacks definition in interrupt or DMA mode:

  When the compilation define USE_HAL_ADF_REGISTER_CALLBACKS is set to 1, the user can configure dynamically the
  driver callbacks, via its own method:

Callback name               | Default value                       | Callback registration function
----------------------------| ------------------------------------| --------------------------------------------
DFLT_AcqCpltCallback        | HAL_ADF_DFLT_AcqCpltCallback()      | HAL_ADF_DFLT_RegisterAcqCpltCallback()
DFLT_AcqHalfCpltCallback    | HAL_ADF_DFLT_AcqHalfCpltCallback()  | HAL_ADF_DFLT_RegisterAcqHalfCpltCallback()
DFLT_AcqStopCpltCallback    | HAL_ADF_DFLT_AcqStopCpltCallback()  | HAL_ADF_DFLT_RegisterAcqStopCpltCallback()
SAD_SoundLevelCallback      | HAL_ADF_SAD_SoundLevelCallback()    | HAL_ADF_SAD_RegisterSoundLevelCallback()
SAD_SoundActivityCallback   | HAL_ADF_SAD_SoundActivityCallback() | HAL_ADF_SAD_RegisterSoundActivityCallback()
ErrorCallback               | HAL_ADF_ErrorCallback()             | HAL_ADF_RegisterErrorCallback()

  If one needs to unregister a callback, register the default callback via the registration function.

  By default, after the HAL_ADF_Init() and when the state is @ref HAL_ADF_STATE_INIT, all callbacks are set to the
  corresponding default weak functions.

  Callbacks can be registered in all states.

  When the compilation define USE_HAL_ADF_REGISTER_CALLBACKS is set to 0 or not defined, the callback registration
  feature is not available and weak callbacks are used, represented by the default value in the table above.
  */
/**
  * @}
  */

/** @defgroup ADF_Configuration_Table ADF Configuration Table
  * @{

# Configuration inside the HAL ADF driver

Config defines                 | Where            | Default value     | Note
-------------------------------| -----------------| ------------------| -------------------------------------------
USE_HAL_ADF_MODULE             | hal_conf.h       |         1         | Enable the HAL ADF module
USE_HAL_ADF_REGISTER_CALLBACKS | hal_conf.h       |         0         | Allow user to define his own callback
USE_HAL_ADF_CLK_ENABLE_MODEL   | hal_conf.h       | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_ADF_USER_DATA          | hal_conf.h       |         0         | Add an user data inside HAL ADF handle
USE_HAL_ADF_GET_LAST_ERRORS    | hal_conf.h       |         0         | Enable retrieving last processes error codes
USE_HAL_ADF_DMA                | hal_conf.h       |         1         | Enable DMA code inside HAL ADF
USE_HAL_CHECK_PARAM            | hal_conf.h       |         0         | Enable checking of vital parameters at runtime
USE_HAL_CHECK_PROCESS_STATE    | hal_conf.h       |         0         | Enable atomic access to process state check
USE_ASSERT_DBG_PARAM           | PreProcessor env |        NONE       | Enable check parameters for HAL
USE_ASSERT_DBG_STATE           | PreProcessor env |        NONE       | Enable check state for HAL
  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup ADF_Private_Macros ADF Private Macros
  * @{
  */

/**
  * @brief Get ADF instance from the selected HAL ADF handle
  */
#define ADF_GET_INSTANCE(hadf) ((ADF_TypeDef *)((uint32_t)(hadf)->instance))

/**
  * @brief Get ADF block from the selected HAL ADF handle and index
  */
#define ADF_GET_BLOCK(hadf, index) ((ADF_Block_TypeDef *)(((uint32_t)(hadf)->instance) \
                                                          + (ADF1_BLOCK_SIZE * ((uint32_t)(index) + 1U))))

/**
  * @brief Processing clock divider
  */
#define IS_ADF_PROC_CLOCK_DIVIDER(value) ((1U <= (value)) && ((value) <= 128U))

/**
  * @brief Output clock pins
  */
#define IS_ADF_OUTPUT_CLOCK_PINS(pins) (((pins) == HAL_ADF_OUTPUT_CLOCK_NONE) \
                                        || ((pins) == HAL_ADF_OUTPUT_CLOCK_CCK0) \
                                        || ((pins) == HAL_ADF_OUTPUT_CLOCK_CCK1) \
                                        || ((pins) == HAL_ADF_OUTPUT_CLOCK_ALL))

/**
  * @brief Output clock divider
  */
#define IS_ADF_OUTPUT_CLOCK_DIVIDER(value) ((1U <= (value)) && ((value) <= 16U))

/**
  * @brief Output clock trigger source
  */
#define IS_ADF_OUTPUT_CLOCK_TRIGGER_SOURCE(source) (((source) == HAL_ADF_OUT_CLOCK_TRIG_TRGO) \
                                                    || ((source) == HAL_ADF_OUT_CLOCK_TRIG_EXTI15))

/**
  * @brief Output clock trigger edge
  */
#define IS_ADF_OUTPUT_CLOCK_TRIGGER_EDGE(edge) (((edge) == HAL_ADF_OUT_CLOCK_TRIG_RISING_EDGE) \
                                                || ((edge) == HAL_ADF_OUT_CLOCK_TRIG_FALLING_EDGE))

/**
  * @brief Block index
  */
#define IS_ADF_BLOCK_INDEX(value) ((value) <= (ADF1_BLOCKS_NUMBER - 1U))

/**
  * @brief Serial interface mode
  */
#define IS_ADF_SITF_MODE(mode) (((mode) == HAL_ADF_SITF_MODE_LF_MASTER_SPI) \
                                || ((mode) == HAL_ADF_SITF_MODE_NORMAL_SPI) \
                                || ((mode) == HAL_ADF_SITF_MODE_MANCHESTER_FALLING) \
                                || ((mode) == HAL_ADF_SITF_MODE_MANCHESTER_RISING))

/**
  * @brief Serial interface clock source
  */
#define IS_ADF_SITF_CLOCK_SOURCE(source) (((source) == HAL_ADF_SITF_CLOCK_SOURCE_CCK0) \
                                          || ((source) == HAL_ADF_SITF_CLOCK_SOURCE_CCK1))

/**
  * @brief Serial interface threshold
  */
#define IS_ADF_SITF_THRESHOLD(value) ((4U <= (value)) && ((value) <= 31U))

/**
  * @brief Bitstream matrix input edge
  */
#define IS_ADF_BSMX_INPUT_EDGE(edge) (((edge) == HAL_ADF_BSMX_INPUT_RISING) \
                                      || ((edge) == HAL_ADF_BSMX_INPUT_FALLING))

/**
  * @brief Digital filter data source
  */
#define IS_ADF_DFLT_DATA_SOURCE(source) (((source) == HAL_ADF_DFLT_DATA_SOURCE_BSMX) \
                                         || ((source) == HAL_ADF_DFLT_DATA_SOURCE_ADCITF1) \
                                         || ((source) == HAL_ADF_DFLT_DATA_SOURCE_ADCITF2))

/**
  * @brief Digital filter CIC mode
  */
#define IS_ADF_DFLT_CIC_MODE(mode) (((mode) == HAL_ADF_DFLT_CIC_ONE_FILTER_SINC4) \
                                    || ((mode) == HAL_ADF_DFLT_CIC_ONE_FILTER_SINC5))

/**
  * @brief Digital filter decimation ratio
  */
#define IS_ADF_DFLT_DECIMATION_RATIO(value) ((2U <= (value)) && ((value) <= 512U))

/**
  * @brief Digital filter gain
  */
#define IS_ADF_DFLT_GAIN(value) ((-16 <= (value)) && ((value) <= 24))

/**
  * @brief Digital filter acquisition mode
  */
#define IS_ADF_DFLT_ACQUISITION_MODE(mode) (((mode) == HAL_ADF_DFLT_ACQ_MODE_ASYNC_CONT) \
                                            || ((mode) == HAL_ADF_DFLT_ACQ_MODE_ASYNC_SINGLE) \
                                            || ((mode) == HAL_ADF_DFLT_ACQ_MODE_SYNC_CONT) \
                                            || ((mode) == HAL_ADF_DFLT_ACQ_MODE_SYNC_SINGLE) \
                                            || ((mode) == HAL_ADF_DFLT_ACQ_MODE_WINDOW_CONT))

/**
  * @brief Digital filter trigger source
  */
#define IS_ADF_DFLT_TRIGGER_SOURCE(source) (((source) == HAL_ADF_DFLT_TRIG_TRGO) \
                                            || ((source) == HAL_ADF_DFLT_TRIG_EXTI15))

/**
  * @brief Digital filter trigger edge
  */
#define IS_ADF_DFLT_TRIGGER_EDGE(edge) (((edge) == HAL_ADF_DFLT_TRIG_RISING_EDGE) \
                                        || ((edge) == HAL_ADF_DFLT_TRIG_FALLING_EDGE))

/**
  * @brief Digital filter samples delay
  */
#define IS_ADF_DFLT_SAMPLES_DELAY(value) ((value) <= 127U)

/**
  * @brief Digital filter FIFO threshold
  */
#define IS_ADF_DFLT_FIFO_THRESHOLD(value) (((value) == HAL_ADF_DFLT_FIFO_THRESHOLD_NOT_EMPTY) \
                                           || ((value) == HAL_ADF_DFLT_FIFO_THRESHOLD_HALF_FULL))

/**
  * @brief Digital filter discard samples
  */
#define IS_ADF_DFLT_DISCARD_SAMPLES(value) ((value) <= 255U)

/**
  * @brief Digital filter reshape filter decimation ratio
  */
#define IS_ADF_DFLT_RSF_DECIMATION_RATIO(value) (((value) == HAL_ADF_DFLT_RSF_DR_4) \
                                                 || ((value) == HAL_ADF_DFLT_RSF_DR_1))

/**
  * @brief Digital filter high-pass filter cut-off frequency
  */
#define IS_ADF_DFLT_HPF_CUT_OFF_FREQUENCY(value) (((value) == HAL_ADF_DFLT_HPF_CUT_OFF_0_000625FPCM) \
                                                  || ((value) == HAL_ADF_DFLT_HPF_CUT_OFF_0_00125FPCM) \
                                                  || ((value) == HAL_ADF_DFLT_HPF_CUT_OFF_0_0025FPCM) \
                                                  || ((value) == HAL_ADF_DFLT_HPF_CUT_OFF_0_0095FPCM))

/**
  * @brief Digital filter optional interruptions
  */
#define IS_ADF_DFLT_OPTIONAL_IT(value) ((value) <= HAL_ADF_DFLT_OPT_IT_DEFAULT)

#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
/**
  * @brief Digital filter DMA data resolution
  */
#define IS_ADF_DFLT_DMA_DATA_RESOLUTION(value) (((value) == HAL_ADF_DMA_DATA_RESOLUTION_FULL) \
                                                || ((value) == HAL_ADF_DMA_DATA_RESOLUTION_MSB_ONLY))
#endif /* USE_HAL_ADF_DMA */

/**
  * @brief Sound activity detector mode
  */
#define IS_ADF_SAD_MODE(value) (((value) == HAL_ADF_SAD_MODE_VOICE_ACTIVITY) \
                                || ((value) == HAL_ADF_SAD_MODE_SOUND) \
                                || ((value) == HAL_ADF_SAD_MODE_AMBIENT_NOISE))

/**
  * @brief Sound activity detector memory transfer
  */
#define IS_ADF_SAD_MEMORY_TRANSFER(value) (((value) == HAL_ADF_SAD_MEMORY_TRANSFER_NO) \
                                           || ((value) == HAL_ADF_SAD_MEMORY_TRANSFER_DURING_DETECTION) \
                                           || ((value) == HAL_ADF_SAD_MEMORY_TRANSFER_ALWAYS))

/**
  * @brief Sound activity detector trigger event
  */
#define IS_ADF_SAD_TRIGGER_EVENT(value) (((value) == HAL_ADF_SAD_TRIGGER_ENTER_DETECT) \
                                         || ((value) == HAL_ADF_SAD_TRIGGER_ENTER_EXIT_DETECT))

/**
  * @brief Sound activity detector minimum ambient noise
  */
#define IS_ADF_SAD_MINIMUM_AMBIENT_NOISE(value) ((value) <= 8191U)

/**
  * @brief Sound activity detector frame size
  */
#define IS_ADF_SAD_FRAME_SIZE(value) (((value) == HAL_ADF_SAD_FRAME_SIZE_8_PCM_SAMPLES) \
                                      || ((value) == HAL_ADF_SAD_FRAME_SIZE_16_PCM_SAMPLES) \
                                      || ((value) == HAL_ADF_SAD_FRAME_SIZE_32_PCM_SAMPLES) \
                                      || ((value) == HAL_ADF_SAD_FRAME_SIZE_64_PCM_SAMPLES) \
                                      || ((value) == HAL_ADF_SAD_FRAME_SIZE_128_PCM_SAMPLES) \
                                      || ((value) == HAL_ADF_SAD_FRAME_SIZE_256_PCM_SAMPLES) \
                                      || ((value) == HAL_ADF_SAD_FRAME_SIZE_512_PCM_SAMPLES))

/**
  * @brief Sound activity detector learning frames
  */
#define IS_ADF_SAD_LEARNING_FRAMES(value) (((value) == HAL_ADF_SAD_LEARNING_FRAMES_2) \
                                           || ((value) == HAL_ADF_SAD_LEARNING_FRAMES_4) \
                                           || ((value) == HAL_ADF_SAD_LEARNING_FRAMES_8) \
                                           || ((value) == HAL_ADF_SAD_LEARNING_FRAMES_16) \
                                           || ((value) == HAL_ADF_SAD_LEARNING_FRAMES_32))

/**
  * @brief Sound activity detector signal to noise threshold
  */
#define IS_ADF_SAD_SIGNAL_TO_NOISE_THRESHOLD(value) (((value) == HAL_ADF_SAD_SIGNAL_TO_NOISE_3_5_DB) \
                                                     || ((value) == HAL_ADF_SAD_SIGNAL_TO_NOISE_6_DB) \
                                                     || ((value) == HAL_ADF_SAD_SIGNAL_TO_NOISE_9_5_DB) \
                                                     || ((value) == HAL_ADF_SAD_SIGNAL_TO_NOISE_12_DB) \
                                                     || ((value) == HAL_ADF_SAD_SIGNAL_TO_NOISE_15_6_DB) \
                                                     || ((value) == HAL_ADF_SAD_SIGNAL_TO_NOISE_18_DB) \
                                                     || ((value) == HAL_ADF_SAD_SIGNAL_TO_NOISE_21_6_DB) \
                                                     || ((value) == HAL_ADF_SAD_SIGNAL_TO_NOISE_24_1_DB) \
                                                     || ((value) == HAL_ADF_SAD_SIGNAL_TO_NOISE_27_6_DB) \
                                                     || ((value) == HAL_ADF_SAD_SIGNAL_TO_NOISE_30_1_DB))

/**
  * @brief Sound activity detector ambient noise slope
  */
#define IS_ADF_SAD_AMBIENT_NOISE_SLOPE(value) ((value) <= 7U)

/**
  * @brief Sound activity detector hangover time window
  */
#define IS_ADF_SAD_HANGOVER_TIME_WINDOW(value) (((value) == HAL_ADF_SAD_HANGOVER_TIME_4_FRAMES) \
                                                || ((value) == HAL_ADF_SAD_HANGOVER_TIME_8_FRAMES) \
                                                || ((value) == HAL_ADF_SAD_HANGOVER_TIME_16_FRAMES) \
                                                || ((value) == HAL_ADF_SAD_HANGOVER_TIME_32_FRAMES) \
                                                || ((value) == HAL_ADF_SAD_HANGOVER_TIME_64_FRAMES) \
                                                || ((value) == HAL_ADF_SAD_HANGOVER_TIME_128_FRAMES) \
                                                || ((value) == HAL_ADF_SAD_HANGOVER_TIME_256_FRAMES) \
                                                || ((value) == HAL_ADF_SAD_HANGOVER_TIME_512_FRAMES))

/**
  * @brief Sound activity detector optional interruptions
  */
#define IS_ADF_SAD_OPTIONAL_IT(value) ((value) <= HAL_ADF_SAD_OPT_IT_DEFAULT)

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup ADF_Private_Functions ADF Private Functions
  * @{
  */

static uint32_t ADF_AdjustGainToRegisterValue(int32_t gain);
static int32_t  ADF_AdjustGainFromRegisterValue(uint32_t register_gain);

static void ADF_DFLT_EnableInterruptions(ADF_Block_TypeDef *p_adf_block);
static void ADF_DFLT_EnableInterruptions_Opt(ADF_Block_TypeDef *p_adf_block, uint32_t interruptions);

#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
static hal_adf_block_index_t ADF_DFLT_GetBlockIndexFromDmaHandle(const hal_adf_handle_t *hadf,
                                                                 const hal_dma_handle_t *hdma);
static void ADF_DFLT_DMA_Cplt(hal_dma_handle_t *hdma);
static void ADF_DFLT_DMA_HalfCplt(hal_dma_handle_t *hdma);
static void ADF_DFLT_DMA_Error(hal_dma_handle_t *hdma);
static void ADF_DFLT_DMA_Abort(hal_dma_handle_t *hdma);
#endif /* USE_HAL_ADF_DMA */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADF_Exported_Functions
  * @{
  */

/** @addtogroup ADF_Exported_Functions_Group1
  * @{
This section provides a set of functions allowing to initialize and deinitialize the ADF peripheral:
  - Call the function HAL_ADF_Init() to initialize the selected ADF handle.
  - Call the function HAL_ADF_DeInit() to deinitialize the ADF.
  - Call the function HAL_ADF_GetInstance() to retrieve the HAL ADF instance from the handle.
  */

/**
  * @brief  Initialize the ADF according to the associated handle.
  * @param  hadf              Pointer to a hal_adf_handle_t.
  * @param  instance          HAL ADF instance.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to HAL ADF handle is NULL.
  */
hal_status_t HAL_ADF_Init(hal_adf_handle_t *hadf, hal_adf_t instance)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_ALL_INSTANCE((ADF_TypeDef *)(uint32_t)instance));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hadf == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hadf->instance = instance;

#if defined(USE_HAL_ADF_CLK_ENABLE_MODEL) && (USE_HAL_ADF_CLK_ENABLE_MODEL >= HAL_CLK_ENABLE_PERIPH_ONLY)
  HAL_RCC_ADF1_EnableClock();
#endif /* USE_HAL_ADF_CLK_ENABLE_MODEL */

#if defined (USE_HAL_ADF_USER_DATA) && (USE_HAL_ADF_USER_DATA == 1)
  hadf->p_user_data = (void *) NULL;
#endif /* USE_HAL_ADF_USER_DATA */

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
  /* Initialize HAL ADF callbacks */
  hadf->p_acquisition_cplt_cb      = HAL_ADF_DFLT_AcqCpltCallback;
  hadf->p_acquisition_half_cplt_cb = HAL_ADF_DFLT_AcqHalfCpltCallback;
  hadf->p_acquisition_stop_cb      = HAL_ADF_DFLT_AcqStopCpltCallback;
  hadf->p_sound_level_cb           = HAL_ADF_SAD_SoundLevelCallback;
  hadf->p_sound_activity_cb        = HAL_ADF_SAD_SoundActivityCallback;
  hadf->p_error_cb                 = HAL_ADF_ErrorCallback;
#endif  /* USE_HAL_ADF_REGISTER_CALLBACKS */

  for (uint8_t i = 0U; i < ADF1_BLOCKS_NUMBER; i++)
  {
#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
    hadf->hdma[i] = NULL;
#endif /* USE_HAL_ADF_DMA */

#if defined(USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
    hadf->last_error_codes[i] = HAL_ADF_ERROR_NONE;
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

    /* Reset all sub-block states */
    hadf->serial_interface_states[i]        = HAL_ADF_SITF_STATE_RESET;
    hadf->digital_filter_states[i]          = HAL_ADF_DFLT_STATE_RESET;
    hadf->sound_activity_detector_states[i] = HAL_ADF_SAD_STATE_RESET;
  }

  hadf->global_state = HAL_ADF_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief De-initialize the ADF.
  * @param hadf Pointer to a hal_adf_handle_t.
  */
void HAL_ADF_DeInit(hal_adf_handle_t *hadf)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_ALL_INSTANCE((ADF_TypeDef *)(uint32_t)hadf->instance));

  for (uint8_t i = 0U; i < ADF1_BLOCKS_NUMBER; i++)
  {
    p_adf_block = ADF_GET_BLOCK(hadf, i);

#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
    /* Abort potential DMA in progress */
    if ((hadf->digital_filter_states[i] == HAL_ADF_DFLT_STATE_ACTIVE) && (hadf->hdma[i] != NULL))
    {
      (void) HAL_DMA_Abort(hadf->hdma[i]);
    }
#endif /* USE_HAL_ADF_DMA */

    /* Disable all sub-blocks */
    STM32_CLEAR_BIT(p_adf_block->SADCR, ADF_SADCR_SADEN);
    STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);
    STM32_CLEAR_BIT(p_adf_block->SITFCR, ADF_SITFCR_SITFEN);

    /* Disable all block interruptions */
    STM32_CLEAR_REG(p_adf_block->DFLTIER);

    /* Clear block pending flags */
    STM32_WRITE_REG(p_adf_block->DFLTISR, (ADF_DFLTISR_DOVRF | ADF_DFLTISR_SATF | ADF_DFLTISR_CKABF | ADF_DFLTISR_RFOVRF
                                           | ADF_DFLTISR_SDDETF | ADF_DFLTISR_SDLVLF));

    /* Reset all sub-block states */
    hadf->serial_interface_states[i]        = HAL_ADF_SITF_STATE_RESET;
    hadf->digital_filter_states[i]          = HAL_ADF_DFLT_STATE_RESET;
    hadf->sound_activity_detector_states[i] = HAL_ADF_SAD_STATE_RESET;
  }

  /* Disable clock generator */
  STM32_CLEAR_BIT(ADF_GET_INSTANCE(hadf)->CKGCR, ADF_CKGCR_CKGDEN);

  hadf->global_state = HAL_ADF_STATE_RESET;
}

/**
  * @brief  Return the HAL ADF instance from the handle.
  * @param  hadf      Pointer to a hal_adf_handle_t.
  * @return hal_adf_t HAL ADF instance.
  */
hal_adf_t HAL_ADF_GetInstance(const hal_adf_handle_t *hadf)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_ALL_INSTANCE(ADF_GET_INSTANCE(hadf)));

  return hadf->instance;
}

/**
  * @}
  */

/** @addtogroup ADF_Exported_Functions_Group2
  * @{
This section provides a set of functions allowing to configure common clock generator and features:
  - Call the function HAL_ADF_SetConfig() to configure processing clock divider.
  - Call the function HAL_ADF_GetConfig() to get the current processing clock divider.
  - Call the function HAL_ADF_SetConfigOutputClock() to configure output clock pins and divider.
  - Call the function HAL_ADF_GetConfigOutputClock() to get the current output clock pins and divider.
  - Call the function HAL_ADF_SetConfigOutputClockTrigger() to configure output clock trigger and edge.
  - Call the function HAL_ADF_GetConfigOutputClockTrigger() to get the current output clock trigger and edge.
  - Call the function HAL_ADF_SetDMA() to link DMA handle for a specified block to the ADF handle.
  - Call the function HAL_ADF_GetClockFreq() to get the current ADF kernel clock frequency.
  - Call the function HAL_ADF_SetUserData() to set user data in ADF handle.
  - Call the function HAL_ADF_GetUserData() to get user data from ADF handle.
  - Call the function HAL_ADF_GetLastErrorCodes() to get last error codes on a specified block.

This section provides also a set of functions allowing to control common features:
  - Call the function HAL_ADF_EnableOutputClock() to enable output clock pins.
  - Call the function HAL_ADF_DisableOutputClock() to disable output clock pins.
  - Call the function HAL_ADF_IsEnabledOutputClock() to check output clock pins status.
  - Call the function HAL_ADF_EnableOutputClockTrigger() to enable output clock trigger.
  - Call the function HAL_ADF_DisableOutputClockTrigger() to disable output clock trigger.
  - Call the function HAL_ADF_IsEnabledOutputClockTrigger() to check output clock trigger status.
  - Call the function HAL_ADF_EnableTriggerOutput() to enable trigger output.
  - Call the function HAL_ADF_IsEnabledTriggerOutput() to check trigger output status.

This section provides also a set of functions allowing to process common clock generator:
  - Call the function HAL_ADF_Start() to activate clock generator.
  - Call the function HAL_ADF_Stop() to deactivate clock generator.
  */

/* Configuration functions */
/**
  * @brief  Configure processing clock divider.
  * @param  hadf               Pointer to a hal_adf_handle_t.
  * @param  proc_clock_divider Processing clock divider.
  *                            This parameter must be a number between Min_Data = 1 and Max_Data = 128.
  * @retval HAL_OK             Operation completed successfully.
  */
hal_status_t HAL_ADF_SetConfig(hal_adf_handle_t *hadf, uint32_t proc_clock_divider)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_PROC_CLOCK_DIVIDER(proc_clock_divider));

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_INIT | (uint32_t)HAL_ADF_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_INSTANCE(hadf)->CKGCR, ADF_CKGCR_PROCDIV_Msk,
                   (proc_clock_divider - 1U) << ADF_CKGCR_PROCDIV_Pos);

  hadf->global_state = HAL_ADF_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the current processing clock divider.
  * @param hadf                 Pointer to a hal_adf_handle_t.
  * @param p_proc_clock_divider Pointer to processing clock divider.
  */
void HAL_ADF_GetConfig(const hal_adf_handle_t *hadf, uint32_t *p_proc_clock_divider)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_proc_clock_divider != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);

  *p_proc_clock_divider = ((STM32_READ_REG(ADF_GET_INSTANCE(hadf)->CKGCR) & ADF_CKGCR_PROCDIV_Msk)
                           >> ADF_CKGCR_PROCDIV_Pos) + 1U;
}

/**
  * @brief  Configure output clock pins and divider.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  pins                 Output clock pins.
  * @param  output_clock_divider Output clock divider.
  *                              This parameter must be a number between Min_Data = 1 and Max_Data = 16.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_SetConfigOutputClock(const hal_adf_handle_t *hadf, hal_adf_output_clock_pins_t pins,
                                          uint32_t output_clock_divider)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_OUTPUT_CLOCK_PINS(pins));
  ASSERT_DBG_PARAM(IS_ADF_OUTPUT_CLOCK_DIVIDER(output_clock_divider));

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_INSTANCE(hadf)->CKGCR, ADF_CKGCR_CCK0DIR_Msk | ADF_CKGCR_CCK1DIR_Msk | ADF_CKGCR_CCKDIV_Msk,
                   (uint32_t)pins | ((output_clock_divider - 1U) << ADF_CKGCR_CCKDIV_Pos));

  return HAL_OK;
}

/**
  * @brief Get the current output clock pins and divider.
  * @param hadf                   Pointer to a hal_adf_handle_t.
  * @param p_pins                 Pointer to output clock pins.
  * @param p_output_clock_divider Pointer to output clock divider.
  */
void HAL_ADF_GetConfigOutputClock(const hal_adf_handle_t *hadf, hal_adf_output_clock_pins_t *p_pins,
                                  uint32_t *p_output_clock_divider)
{
  uint32_t ckgcr_reg;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_pins != NULL);
  ASSERT_DBG_PARAM(p_output_clock_divider != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);

  ckgcr_reg = STM32_READ_REG(ADF_GET_INSTANCE(hadf)->CKGCR);
  *p_pins = (hal_adf_output_clock_pins_t)(uint32_t)(ckgcr_reg & (ADF_CKGCR_CCK0DIR_Msk | ADF_CKGCR_CCK1DIR_Msk));
  *p_output_clock_divider = ((ckgcr_reg & ADF_CKGCR_CCKDIV_Msk) >> ADF_CKGCR_CCKDIV_Pos) + 1U;
}

/**
  * @brief  Configure output clock trigger and edge.
  * @param  hadf   Pointer to a hal_adf_handle_t.
  * @param  source Output clock trigger source.
  * @param  edge   Output clock trigger edge.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_ADF_SetConfigOutputClockTrigger(const hal_adf_handle_t *hadf,
                                                 hal_adf_output_clock_trigger_source_t source,
                                                 hal_adf_output_clock_trigger_edge_t edge)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_OUTPUT_CLOCK_TRIGGER_SOURCE(source));
  ASSERT_DBG_PARAM(IS_ADF_OUTPUT_CLOCK_TRIGGER_EDGE(edge));

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_INSTANCE(hadf)->CKGCR, ADF_CKGCR_TRGSRC_Msk | ADF_CKGCR_TRGSENS_Msk,
                   (uint32_t)source | (uint32_t)edge);

  return HAL_OK;
}

/**
  * @brief Get the current output clock trigger and edge.
  * @param hadf     Pointer to a hal_adf_handle_t.
  * @param p_source Pointer to output clock trigger source.
  * @param p_edge   Pointer to output clock trigger edge.
  */
void HAL_ADF_GetConfigOutputClockTrigger(const hal_adf_handle_t *hadf,
                                         hal_adf_output_clock_trigger_source_t *p_source,
                                         hal_adf_output_clock_trigger_edge_t *p_edge)
{
  uint32_t ckgcr_reg;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_source != NULL);
  ASSERT_DBG_PARAM(p_edge != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);

  ckgcr_reg = STM32_READ_REG(ADF_GET_INSTANCE(hadf)->CKGCR);
  *p_source = (hal_adf_output_clock_trigger_source_t)(uint32_t)(ckgcr_reg & ADF_CKGCR_TRGSRC_Msk);
  *p_edge = (hal_adf_output_clock_trigger_edge_t)(uint32_t)(ckgcr_reg & ADF_CKGCR_TRGSENS_Msk);
}

#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
/**
  * @brief  Link DMA handle for a specified block to the ADF handle.
  * @param  hadf              Pointer to a hal_adf_handle_t.
  * @param  block_index       Block index.
  * @param  hdma              Pointer to DMA handle.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to DMA handle is NULL.
  */
hal_status_t HAL_ADF_SetDMA(hal_adf_handle_t *hadf,
                            hal_adf_block_index_t block_index,
                            hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)block_index));

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[block_index],
                   (uint32_t)HAL_ADF_DFLT_STATE_RESET | (uint32_t)HAL_ADF_DFLT_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hadf->hdma[block_index] = hdma;
  hdma->p_parent = hadf;

  return HAL_OK;
}
#endif /* USE_HAL_ADF_DMA */

/**
  * @brief  Get the current ADF kernel clock frequency.
  * @param  hadf     Pointer to a hal_adf_handle_t.
  * @return uint32_t ADF kernel clock frequency in Hz.
  * @retval 0        ADF source clock not configured or not ready.
  */
uint32_t HAL_ADF_GetClockFreq(const hal_adf_handle_t *hadf)
{
  ASSERT_DBG_PARAM(hadf != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);

#if (!defined(USE_ASSERT_DBG_STATE) && !defined(USE_ASSERT_DBG_PARAM))
  STM32_UNUSED(hadf);
#endif /* (!defined(USE_ASSERT_DBG_STATE) && !defined(USE_ASSERT_DBG_PARAM)) */

  return HAL_RCC_ADF1_GetKernelClkFreq();
}

#if defined (USE_HAL_ADF_USER_DATA) && (USE_HAL_ADF_USER_DATA == 1)
/**
  * @brief Set user data in ADF handle.
  * @param hadf        Pointer to a hal_adf_handle_t.
  * @param p_user_data Pointer to user data structure.
  */
void HAL_ADF_SetUserData(hal_adf_handle_t *hadf, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hadf != NULL);

  hadf->p_user_data = p_user_data;
}

/**
  * @brief  Get user data from ADF handle.
  * @param  hadf Pointer to a hal_adf_handle_t.
  * @return void Pointer to user data structure.
  */
const void *HAL_ADF_GetUserData(const hal_adf_handle_t *hadf)
{
  ASSERT_DBG_PARAM(hadf != NULL);

  return hadf->p_user_data;
}
#endif /* USE_HAL_ADF_USER_DATA */

#if defined(USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
/**
  * @brief  Get last error codes on a specified block.
  * @param  hadf        Pointer to a hal_adf_handle_t.
  * @param  block_index Block index.
  * @return uint32_t    Last error codes on the specified block.
  *                     This return value can be a combination of the following values:
  *                       @arg @ref HAL_ADF_ERROR_NONE
  *                       @arg @ref HAL_ADF_ERROR_DFLT_ACQ_OVERFLOW
  *                       @arg @ref HAL_ADF_ERROR_DFLT_RSF_OVERRUN
  *                       @arg @ref HAL_ADF_ERROR_SITF_CLOCK_ABSENCE
  *                       @arg @ref HAL_ADF_ERROR_DFLT_SATURATION
  *                       @arg @ref HAL_ADF_ERROR_DMA
  */
uint32_t HAL_ADF_GetLastErrorCodes(const hal_adf_handle_t *hadf,
                                   hal_adf_block_index_t block_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)block_index));

  return hadf->last_error_codes[block_index];
}
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

/* Control functions */
/**
  * @brief  Enable output clock pins.
  * @param  hadf   Pointer to a hal_adf_handle_t.
  * @param  pins   Output clock pins.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_ADF_EnableOutputClock(const hal_adf_handle_t *hadf, hal_adf_output_clock_pins_t pins)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_OUTPUT_CLOCK_PINS(pins));

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);

  STM32_SET_BIT(ADF_GET_INSTANCE(hadf)->CKGCR, (uint32_t)pins >> 4U);

  return HAL_OK;
}

/**
  * @brief  Disable output clock pins.
  * @param  hadf   Pointer to a hal_adf_handle_t.
  * @param  pins   Output clock pins.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_ADF_DisableOutputClock(const hal_adf_handle_t *hadf, hal_adf_output_clock_pins_t pins)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_OUTPUT_CLOCK_PINS(pins));

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);

  STM32_CLEAR_BIT(ADF_GET_INSTANCE(hadf)->CKGCR, (uint32_t)pins >> 4U);

  return HAL_OK;
}

/**
  * @brief  Check output clock pins status.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @return hal_adf_output_clock_status_t Output clock pins status.
  */
hal_adf_output_clock_status_t HAL_ADF_IsEnabledOutputClock(const hal_adf_handle_t *hadf)
{
  ASSERT_DBG_PARAM(hadf != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);

  return (hal_adf_output_clock_status_t)(uint32_t)((STM32_READ_REG(ADF_GET_INSTANCE(hadf)->CKGCR)
                                                    & (ADF_CKGCR_CCK0EN_Msk | ADF_CKGCR_CCK1EN_Msk)) >> 1U);
}

/**
  * @brief  Enable output clock trigger.
  * @param  hadf   Pointer to a hal_adf_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_ADF_EnableOutputClockTrigger(const hal_adf_handle_t *hadf)
{
  ASSERT_DBG_PARAM(hadf != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE);

  STM32_SET_BIT(ADF_GET_INSTANCE(hadf)->CKGCR, ADF_CKGCR_CKGMOD);

  return HAL_OK;
}

/**
  * @brief  Disable output clock trigger.
  * @param  hadf   Pointer to a hal_adf_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_ADF_DisableOutputClockTrigger(const hal_adf_handle_t *hadf)
{
  ASSERT_DBG_PARAM(hadf != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE);

  STM32_CLEAR_BIT(ADF_GET_INSTANCE(hadf)->CKGCR, ADF_CKGCR_CKGMOD);

  return HAL_OK;
}

/**
  * @brief  Check output clock trigger status.
  * @param  hadf                                  Pointer to a hal_adf_handle_t.
  * @return hal_adf_output_clock_trigger_status_t Output clock trigger status.
  */
hal_adf_output_clock_trigger_status_t HAL_ADF_IsEnabledOutputClockTrigger(const hal_adf_handle_t *hadf)
{
  hal_adf_output_clock_trigger_status_t status;

  ASSERT_DBG_PARAM(hadf != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);

  status = (STM32_IS_BIT_SET(ADF_GET_INSTANCE(hadf)->CKGCR, ADF_CKGCR_CKGMOD)) ? HAL_ADF_OUT_CLOCK_TRIG_ENABLED
           : HAL_ADF_OUT_CLOCK_TRIG_DISABLED;

  return status;
}

/**
  * @brief  Enable trigger output.
  * @param  hadf   Pointer to a hal_adf_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_ADF_EnableTriggerOutput(const hal_adf_handle_t *hadf)
{
  ASSERT_DBG_PARAM(hadf != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);

  STM32_SET_BIT(ADF_GET_INSTANCE(hadf)->GCR, ADF_GCR_TRGO);

  return HAL_OK;
}

/**
  * @brief  Check trigger output status.
  * @param  hadf                            Pointer to a hal_adf_handle_t.
  * @return hal_adf_trigger_output_status_t Trigger output status.
  */
hal_adf_trigger_output_status_t HAL_ADF_IsEnabledTriggerOutput(const hal_adf_handle_t *hadf)
{
  hal_adf_trigger_output_status_t status;

  ASSERT_DBG_PARAM(hadf != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE | (uint32_t)HAL_ADF_STATE_ACTIVE);

  status = (STM32_IS_BIT_SET(ADF_GET_INSTANCE(hadf)->GCR, ADF_GCR_TRGO)) ? HAL_ADF_TRIGGER_OUTPUT_ENABLED
           : HAL_ADF_TRIGGER_OUTPUT_DISABLED;

  return status;
}

/* Process functions */
/**
  * @brief  Activate clock generator.
  * @param  hadf     Pointer to a hal_adf_handle_t.
  * @retval HAL_OK   Operation completed successfully.
  * @retval HAL_BUSY The global state is not HAL_ADF_STATE_IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_ADF_Start(hal_adf_handle_t *hadf)
{
  ASSERT_DBG_PARAM(hadf != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hadf, global_state, HAL_ADF_STATE_IDLE, HAL_ADF_STATE_ACTIVE);

  STM32_SET_BIT(ADF_GET_INSTANCE(hadf)->CKGCR, ADF_CKGCR_CKGDEN);

  return HAL_OK;
}

/**
  * @brief  Deactivate clock generator.
  * @param  hadf   Pointer to a hal_adf_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_ADF_Stop(hal_adf_handle_t *hadf)
{
  ASSERT_DBG_PARAM(hadf != NULL);

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_ACTIVE);

  for (uint8_t i = 0U; i < ADF1_BLOCKS_NUMBER; i++)
  {
    ASSERT_DBG_STATE(hadf->serial_interface_states[i], (uint32_t)HAL_ADF_SITF_STATE_RESET
                     | (uint32_t)HAL_ADF_SITF_STATE_IDLE);
    ASSERT_DBG_STATE(hadf->digital_filter_states[i], (uint32_t)HAL_ADF_DFLT_STATE_RESET
                     | (uint32_t)HAL_ADF_DFLT_STATE_IDLE);
    ASSERT_DBG_STATE(hadf->sound_activity_detector_states[i], (uint32_t)HAL_ADF_SAD_STATE_RESET
                     | (uint32_t)HAL_ADF_SAD_STATE_IDLE);
  }

  STM32_CLEAR_BIT(ADF_GET_INSTANCE(hadf)->CKGCR, ADF_CKGCR_CKGDEN);

  hadf->global_state = HAL_ADF_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup ADF_Exported_Functions_Group3
  * @{
This section provides a set of functions allowing to configure and process serial interface:
  - Call the function HAL_ADF_SITF_SetConfig() to configure a specified serial interface.
  - Call the function HAL_ADF_SITF_GetConfig() to get the current configuration of a specified serial interface.
  - Call the function HAL_ADF_SITF_Start() to activate a specified serial interface.
  - Call the function HAL_ADF_SITF_Stop() to deactivate a specified serial interface.

This section provides also a set of functions for clock absence detection feature:
  - Call the function HAL_ADF_SITF_IsClockAbsenceDetected() to check clock absence detection status on a specified
    serial interface.
  - Call the function HAL_ADF_SITF_StartClockAbsenceDetect_IT() to start clock absence detection in interrupt mode
    on a specified serial interface.
  - Call the function HAL_ADF_SITF_StopClockAbsenceDetect_IT() to stop clock absence detection in interrupt mode
    on a specified serial interface.
  */

/* Configuration functions */
/**
  * @brief  Configure a specified serial interface.
  * @param  hadf                   Pointer to a hal_adf_handle_t.
  * @param  serial_interface_index Serial interface index.
  * @param  p_config               Pointer to serial interface configuration structure.
  * @retval HAL_OK                 Operation completed successfully.
  * @retval HAL_INVALID_PARAM      Pointer to serial interface configuration structure is NULL.
  */
hal_status_t HAL_ADF_SITF_SetConfig(hal_adf_handle_t *hadf,
                                    hal_adf_block_index_t serial_interface_index,
                                    const hal_adf_serial_interface_config_t *p_config)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)serial_interface_index));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_ADF_SITF_MODE(p_config->mode));
  ASSERT_DBG_PARAM(IS_ADF_SITF_CLOCK_SOURCE(p_config->clock_source));
  ASSERT_DBG_PARAM(IS_ADF_SITF_THRESHOLD(p_config->threshold));

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->serial_interface_states[serial_interface_index], (uint32_t)HAL_ADF_SITF_STATE_RESET
                   | (uint32_t)HAL_ADF_SITF_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, serial_interface_index)->SITFCR,
                   ADF_SITFCR_SCKSRC_Msk | ADF_SITFCR_SITFMOD_Msk | ADF_SITFCR_STH_Msk,
                   (uint32_t)p_config->clock_source | (uint32_t)p_config->mode
                   | (p_config->threshold << ADF_SITFCR_STH_Pos));

  hadf->serial_interface_states[serial_interface_index] = HAL_ADF_SITF_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the current configuration of a specified serial interface.
  * @param hadf                   Pointer to a hal_adf_handle_t.
  * @param serial_interface_index Serial interface index.
  * @param p_config               Pointer to serial interface configuration structure.
  */
void HAL_ADF_SITF_GetConfig(const hal_adf_handle_t *hadf,
                            hal_adf_block_index_t serial_interface_index,
                            hal_adf_serial_interface_config_t *p_config)
{
  uint32_t sitfcr_reg;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hadf->global_state, (uint32_t)HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->serial_interface_states[serial_interface_index], (uint32_t)HAL_ADF_SITF_STATE_IDLE
                   | (uint32_t)HAL_ADF_SITF_STATE_ACTIVE);

  sitfcr_reg = STM32_READ_REG(ADF_GET_BLOCK(hadf, serial_interface_index)->SITFCR);
  p_config->mode = (hal_adf_serial_interface_mode_t)(uint32_t)(sitfcr_reg & ADF_SITFCR_SITFMOD_Msk);
  p_config->clock_source = (hal_adf_serial_interface_clock_source_t)(uint32_t)(sitfcr_reg & ADF_SITFCR_SCKSRC_Msk);
  p_config->threshold = ((sitfcr_reg & ADF_SITFCR_STH_Msk) >> ADF_SITFCR_STH_Pos);
}

/* Process functions */
/**
  * @brief  Activate a specified serial interface.
  * @param  hadf                   Pointer to a hal_adf_handle_t.
  * @param  serial_interface_index Serial interface index.
  * @retval HAL_OK                 Operation completed successfully.
  * @retval HAL_BUSY               The serial interface state is not HAL_ADF_SITF_STATE_IDLE
  *                                (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_ADF_SITF_Start(hal_adf_handle_t *hadf, hal_adf_block_index_t serial_interface_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->serial_interface_states[serial_interface_index], HAL_ADF_SITF_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hadf, serial_interface_states[serial_interface_index], HAL_ADF_SITF_STATE_IDLE,
                         HAL_ADF_SITF_STATE_ACTIVE);

  STM32_SET_BIT(ADF_GET_BLOCK(hadf, serial_interface_index)->SITFCR, ADF_SITFCR_SITFEN);

  return HAL_OK;
}

/**
  * @brief  Deactivate a specified serial interface.
  * @param  hadf                   Pointer to a hal_adf_handle_t.
  * @param  serial_interface_index Serial interface index.
  * @retval HAL_OK                 Operation completed successfully.
  */
hal_status_t HAL_ADF_SITF_Stop(hal_adf_handle_t *hadf, hal_adf_block_index_t serial_interface_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->serial_interface_states[serial_interface_index], HAL_ADF_SITF_STATE_ACTIVE);

  STM32_CLEAR_BIT(ADF_GET_BLOCK(hadf, serial_interface_index)->SITFCR, ADF_SITFCR_SITFEN);

  hadf->serial_interface_states[serial_interface_index] = HAL_ADF_SITF_STATE_IDLE;

  return HAL_OK;
}

/* Clock absence detection functions */
/**
  * @brief  Check clock absence detection status on a specified serial interface.
  * @param  hadf                       Pointer to a hal_adf_handle_t.
  * @param  serial_interface_index     Serial interface index.
  * @return hal_adf_sitf_ckab_status_t Clock absence detection status.
  */
hal_adf_sitf_ckab_status_t HAL_ADF_SITF_IsClockAbsenceDetected(const hal_adf_handle_t *hadf,
                                                               hal_adf_block_index_t serial_interface_index)
{
  hal_adf_sitf_ckab_status_t status;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->serial_interface_states[serial_interface_index], HAL_ADF_SITF_STATE_ACTIVE);

  status = (STM32_IS_BIT_SET(ADF_GET_BLOCK(hadf, serial_interface_index)->DFLTISR, ADF_DFLTISR_CKABF))
           ? HAL_ADF_SITF_CKAB_DETECTED : HAL_ADF_SITF_CKAB_NOT_DETECTED;

  return status;
}

/**
  * @brief  Start clock absence detection in interrupt mode on a specified serial interface.
  * @param  hadf                   Pointer to a hal_adf_handle_t.
  * @param  serial_interface_index Serial interface index.
  * @retval HAL_OK                 Operation completed successfully.
  */
hal_status_t HAL_ADF_SITF_StartClockAbsenceDetect_IT(const hal_adf_handle_t *hadf,
                                                     hal_adf_block_index_t serial_interface_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->serial_interface_states[serial_interface_index], HAL_ADF_SITF_STATE_ACTIVE);

  STM32_SET_BIT(ADF_GET_BLOCK(hadf, serial_interface_index)->DFLTIER, ADF_DFLTIER_CKABIE);

  return HAL_OK;
}

/**
  * @brief  Stop clock absence detection in interrupt mode on a specified serial interface.
  * @param  hadf                   Pointer to a hal_adf_handle_t.
  * @param  serial_interface_index Serial interface index.
  * @retval HAL_OK                 Operation completed successfully.
  */
hal_status_t HAL_ADF_SITF_StopClockAbsenceDetect_IT(const hal_adf_handle_t *hadf,
                                                    hal_adf_block_index_t serial_interface_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->serial_interface_states[serial_interface_index], HAL_ADF_SITF_STATE_ACTIVE);

  STM32_CLEAR_BIT(ADF_GET_BLOCK(hadf, serial_interface_index)->DFLTIER, ADF_DFLTIER_CKABIE);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup ADF_Exported_Functions_Group4
  * @{
This section provides a set of functions allowing to configure bitstream matrix:
  - Call the function HAL_ADF_BSMX_SetConfig() to configure a specified bitstream matrix.
  - Call the function HAL_ADF_BSMX_GetConfig() to get the current configuration of a specified bitstream matrix.
  */

/* Configuration functions */
/**
  * @brief  Connect a specified bitstream matrix to a specified serial interface and configure input edge.
  * @param  hadf                   Pointer to a hal_adf_handle_t.
  * @param  bitstream_matrix_index Bitstream matrix index.
  * @param  serial_interface_index Serial interface index.
  * @param  edge                   Input edge.
  * @retval HAL_OK                 Operation completed successfully.
  */
hal_status_t HAL_ADF_BSMX_SetConfig(const hal_adf_handle_t *hadf,
                                    hal_adf_block_index_t bitstream_matrix_index,
                                    hal_adf_block_index_t serial_interface_index,
                                    hal_adf_bitstream_input_edge_t edge)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)bitstream_matrix_index));
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)serial_interface_index));
  ASSERT_DBG_PARAM(IS_ADF_BSMX_INPUT_EDGE(edge));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[bitstream_matrix_index], (uint32_t)HAL_ADF_DFLT_STATE_RESET
                   | (uint32_t)HAL_ADF_DFLT_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, bitstream_matrix_index)->BSMXCR, ADF_BSMXCR_BSSEL_Msk,
                   ((uint32_t)serial_interface_index << 1U) | (uint32_t)edge);

  return HAL_OK;
}

/**
  * @brief Get the current serial interface connected to a specified bitstream matrix and current input edge.
  * @param hadf                     Pointer to a hal_adf_handle_t.
  * @param bitstream_matrix_index   Bitstream matrix index.
  * @param p_serial_interface_index Pointer to serial interface index.
  * @param p_edge                   Pointer to input edge.
  */
void HAL_ADF_BSMX_GetConfig(const hal_adf_handle_t *hadf,
                            hal_adf_block_index_t bitstream_matrix_index,
                            hal_adf_block_index_t *p_serial_interface_index,
                            hal_adf_bitstream_input_edge_t *p_edge)
{
  uint32_t bsmxcr_reg;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)bitstream_matrix_index));
  ASSERT_DBG_PARAM(p_serial_interface_index != NULL);
  ASSERT_DBG_PARAM(p_edge != NULL);

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);

  bsmxcr_reg = STM32_READ_REG(ADF_GET_BLOCK(hadf, bitstream_matrix_index)->BSMXCR);
  *p_serial_interface_index = (hal_adf_block_index_t)(uint32_t)((bsmxcr_reg & ADF_BSMXCR_BSSEL_Msk) >> 1U);
  *p_edge = (hal_adf_bitstream_input_edge_t)(uint32_t)(bsmxcr_reg & 1U);
}

/**
  * @}
  */

/** @addtogroup ADF_Exported_Functions_Group5
  * @{
This section provides a set of functions allowing to configure digital filter:
  - Call the function HAL_ADF_DFLT_SetConfig() to configure a specified digital filter.
  - Call the function HAL_ADF_DFLT_GetConfig() to get current configuration of a specified digital filter.
  - Call the function HAL_ADF_DFLT_SetSamplesDelay() to set samples delay on a specified digital filter.
  - Call the function HAL_ADF_DFLT_GetSamplesDelay() to get current samples delay on a specified digital filter.
  - Call the function HAL_ADF_DFLT_SetGain() to set gain on a specified digital filter.
  - Call the function HAL_ADF_DFLT_GetGain() to get current gain on a specified digital filter.
  - Call the function HAL_ADF_DFLT_SetFifoThreshold() to set FIFO threshold on a specified digital filter.
  - Call the function HAL_ADF_DFLT_GetFifoThreshold() to get current FIFO threshold on a specified digital filter.
  - Call the function HAL_ADF_DFLT_SetDiscardSamples() to set discard samples on a specified digital filter.
  - Call the function HAL_ADF_DFLT_GetDiscardSamples() to get current discard samples on a specified digital filter.

This section provides also a set of functions allowing to control digital filter:
  - Call the function HAL_ADF_DFLT_EnableReshapeFilter() to enable reshape filter on a specified digital filter.
  - Call the function HAL_ADF_DFLT_DisableReshapeFilter() to disable reshape filter on a specified digital filter.
  - Call the function HAL_ADF_DFLT_IsEnabledReshapeFilter() to check reshape filter status on a specified
    digital filter.
  - Call the function HAL_ADF_DFLT_GetReshapeFilterDecimationRatio() to get current reshape filter decimation ratio
    on a specified digital filter.
  - Call the function HAL_ADF_DFLT_EnableHighPassFilter() to enable high-pass filter on a specified digital filter.
  - Call the function HAL_ADF_DFLT_DisableHighPassFilter() to disable high-pass filter on a specified digital filter.
  - Call the function HAL_ADF_DFLT_IsEnabledHighPassFilter() to check high-pass filter status on a specified
    digital filter.
  - Call the function HAL_ADF_DFLT_GetHighPassFilterCutOffFrequency() to get current high-pass filter cut-off frequency
    on a specified digital filter.

This section provides also a set of functions allowing to process digital filter:
  - Call the function HAL_ADF_DFLT_StartAcq() to start acquisition on a specified digital filter in polling mode.
  - Call the function HAL_ADF_DFLT_StopAcq() to stop acquisition on a specified digital filter in polling mode.
  - Call the function HAL_ADF_DFLT_PollForAcq() to wait available acquisition on a specified digital filter
    in polling mode.
  - Call the function HAL_ADF_DFLT_GetAcqValue() to get acquisition value on a specified digital filter.
  - Call the function HAL_ADF_DFLT_StartAcq_IT() to start acquisition on a specified digital filter in interrupt mode.
  - Call the function HAL_ADF_DFLT_StopAcq_IT() to stop acquisition on a specified digital filter in interrupt mode.
  - Call the function HAL_ADF_DFLT_StartAcq_IT_Opt() to start acquisition on a specified digital filter
    in interrupt mode with optional interruptions.
  - Call the function HAL_ADF_DFLT_StartAcq_DMA() to start acquisition on a specified digital filter in DMA mode.
  - Call the function HAL_ADF_DFLT_StopAcq_DMA() to stop acquisition on a specified digital filter in DMA mode.
  - Call the function HAL_ADF_DFLT_StartAcq_DMA_Opt() to start acquisition on a specified digital filter
    in DMA mode with optional interruptions.
  */

/* Configuration functions */
/**
  * @brief  Configure a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  p_config             Pointer to digital filter configuration structure.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_INVALID_PARAM    Pointer to digital filter configuration structure is NULL.
  */
hal_status_t HAL_ADF_DFLT_SetConfig(hal_adf_handle_t *hadf,
                                    hal_adf_block_index_t digital_filter_index,
                                    const hal_adf_digital_filter_config_t *p_config)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_ADF_DFLT_DATA_SOURCE(p_config->data_source));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_CIC_MODE(p_config->cic_mode));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_DECIMATION_RATIO(p_config->decimation_ratio));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_GAIN(p_config->gain));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_ACQUISITION_MODE(p_config->acquisition_mode));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_TRIGGER_SOURCE(p_config->trigger.source));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_TRIGGER_EDGE(p_config->trigger.edge));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_RESET
                   | (uint32_t)HAL_ADF_DFLT_STATE_IDLE);

  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);
  STM32_MODIFY_REG(p_adf_block->DFLTCICR, ADF_DFLTCICR_DATSRC_Msk | ADF_DFLTCICR_CICMOD_Msk | ADF_DFLTCICR_MCICD_Msk
                   | ADF_DFLTCICR_SCALE_Msk, (uint32_t)p_config->data_source | (uint32_t)p_config->cic_mode
                   | ((p_config->decimation_ratio - 1U) << ADF_DFLTCICR_MCICD_Pos)
                   | (ADF_AdjustGainToRegisterValue(p_config->gain) << ADF_DFLTCICR_SCALE_Pos));
  STM32_MODIFY_REG(p_adf_block->DFLTCR, ADF_DFLTCR_ACQMOD_Msk | ADF_DFLTCR_TRGSENS_Msk | ADF_DFLTCR_TRGSRC_Msk,
                   (uint32_t)p_config->acquisition_mode | (uint32_t)p_config->trigger.edge
                   | (uint32_t)p_config->trigger.source);

  hadf->digital_filter_states[digital_filter_index] = HAL_ADF_DFLT_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get current configuration of a specified digital filter.
  * @param hadf                 Pointer to a hal_adf_handle_t.
  * @param digital_filter_index Digital filter index.
  * @param p_config             Pointer to digital filter configuration structure.
  */
void HAL_ADF_DFLT_GetConfig(const hal_adf_handle_t *hadf,
                            hal_adf_block_index_t digital_filter_index,
                            hal_adf_digital_filter_config_t *p_config)
{
  const ADF_Block_TypeDef *p_adf_block;
  uint32_t reg;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);
  reg = STM32_READ_REG(p_adf_block->DFLTCICR);
  p_config->data_source = (hal_adf_dflt_data_source_t)(uint32_t)(reg & ADF_DFLTCICR_DATSRC_Msk);
  p_config->cic_mode = (hal_adf_dflt_cic_mode_t)(uint32_t)(reg & ADF_DFLTCICR_CICMOD_Msk);
  p_config->decimation_ratio = ((reg & ADF_DFLTCICR_MCICD_Msk) >> ADF_DFLTCICR_MCICD_Pos) + 1U;
  p_config->gain = ADF_AdjustGainFromRegisterValue((reg & ADF_DFLTCICR_SCALE_Msk) >> ADF_DFLTCICR_SCALE_Pos);
  reg = STM32_READ_REG(p_adf_block->DFLTCR);
  p_config->acquisition_mode = (hal_adf_dflt_acquisition_mode_t)(uint32_t)(reg & ADF_DFLTCR_ACQMOD_Msk);
  p_config->trigger.source = (hal_adf_dflt_trigger_source_t)(uint32_t)(reg & ADF_DFLTCR_TRGSRC_Msk);
  p_config->trigger.edge = (hal_adf_dflt_trigger_edge_t)(uint32_t)(reg & ADF_DFLTCR_TRGSENS_Msk);
}

/**
  * @brief  Set samples delay on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  samples_delay        Samples delay.
  *                              This parameter must be a number between Min_Data = 0 and Max_Data = 127.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_SetSamplesDelay(const hal_adf_handle_t *hadf,
                                          hal_adf_block_index_t digital_filter_index,
                                          uint32_t samples_delay)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_SAMPLES_DELAY(samples_delay));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, digital_filter_index)->DLYCR, ADF_DLYCR_SKPDLY_Msk, samples_delay);

  return HAL_OK;
}

/**
  * @brief  Get current samples delay on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @return uint32_t             Samples delay.
  */
uint32_t HAL_ADF_DFLT_GetSamplesDelay(const hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  return (STM32_READ_BIT(ADF_GET_BLOCK(hadf, digital_filter_index)->DLYCR, ADF_DLYCR_SKPDLY_Msk));
}

/**
  * @brief  Set gain on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  gain                 Gain in step of around 3db (from -48db to 72dB).
  *                              This parameter must be a number between Min_Data = -16 and Max_Data = 24.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_SetGain(const hal_adf_handle_t *hadf,
                                  hal_adf_block_index_t digital_filter_index,
                                  int32_t gain)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_GAIN(gain));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTCICR, ADF_DFLTCICR_SCALE_Msk,
                   (ADF_AdjustGainToRegisterValue(gain) << ADF_DFLTCICR_SCALE_Pos));

  return HAL_OK;
}

/**
  * @brief  Get current gain on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @return int32_t              Gain in step of around 3db (from -48db to 72dB).
  *                              This parameter is a number between Min_Data = -16 and Max_Data = 24.
  */
int32_t HAL_ADF_DFLT_GetGain(const hal_adf_handle_t *hadf,
                             hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  return ADF_AdjustGainFromRegisterValue((STM32_READ_REG(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTCICR)
                                          & ADF_DFLTCICR_SCALE_Msk) >> ADF_DFLTCICR_SCALE_Pos);
}

/**
  * @brief  Set FIFO threshold on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  fifo_threshold       FIFO threshold.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_SetFifoThreshold(const hal_adf_handle_t *hadf,
                                           hal_adf_block_index_t digital_filter_index,
                                           hal_adf_dflt_fifo_threshold_t fifo_threshold)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_FIFO_THRESHOLD(fifo_threshold));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTCR, ADF_DFLTCR_FTH_Msk, (uint32_t)fifo_threshold);

  return HAL_OK;
}

/**
  * @brief  Get current FIFO threshold on a specified digital filter.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index          Digital filter index.
  * @return hal_adf_dflt_fifo_threshold_t FIFO threshold.
  */
hal_adf_dflt_fifo_threshold_t HAL_ADF_DFLT_GetFifoThreshold(const hal_adf_handle_t *hadf,
                                                            hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  return (hal_adf_dflt_fifo_threshold_t)(uint32_t)STM32_READ_BIT(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTCR,
                                                                 ADF_DFLTCR_FTH_Msk);
}

/**
  * @brief  Set discard samples on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  discard_samples      Discard samples.
  *                              This parameter must be a number between Min_Data = 0 and Max_Data = 255.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_SetDiscardSamples(const hal_adf_handle_t *hadf,
                                            hal_adf_block_index_t digital_filter_index,
                                            uint32_t discard_samples)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_DISCARD_SAMPLES(discard_samples));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTCR, ADF_DFLTCR_NBDIS_Msk,
                   discard_samples << ADF_DFLTCR_NBDIS_Pos);

  return HAL_OK;
}

/**
  * @brief  Get current discard samples on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @return uint32_t             Discard samples.
  */
uint32_t HAL_ADF_DFLT_GetDiscardSamples(const hal_adf_handle_t *hadf,
                                        hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  return (STM32_READ_BIT(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTCR,
                         ADF_DFLTCR_NBDIS_Msk) >> ADF_DFLTCR_NBDIS_Pos);
}

/* Control functions */
/**
  * @brief  Enable reshape filter on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  decimation_ratio     Reshape filter decimation ratio.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_EnableReshapeFilter(const hal_adf_handle_t *hadf,
                                              hal_adf_block_index_t digital_filter_index,
                                              hal_adf_dflt_rsf_decimation_ratio_t decimation_ratio)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_RSF_DECIMATION_RATIO(decimation_ratio));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTRSFR,
                   ADF_DFLTRSFR_RSFLTBYP_Msk | ADF_DFLTRSFR_RSFLTD_Msk,
                   (uint32_t)decimation_ratio);

  return HAL_OK;
}

/**
  * @brief  Disable reshape filter on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_DisableReshapeFilter(const hal_adf_handle_t *hadf,
                                               hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  STM32_SET_BIT(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTRSFR, ADF_DFLTRSFR_RSFLTBYP);

  return HAL_OK;
}

/**
  * @brief  Check reshape filter status on a specified digital filter.
  * @param  hadf                      Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index      Digital filter index.
  * @return hal_adf_dflt_rsf_status_t Reshape filter status.
  */
hal_adf_dflt_rsf_status_t HAL_ADF_DFLT_IsEnabledReshapeFilter(const hal_adf_handle_t *hadf,
                                                              hal_adf_block_index_t digital_filter_index)
{
  hal_adf_dflt_rsf_status_t status;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  status = (STM32_IS_BIT_SET(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTRSFR, ADF_DFLTRSFR_RSFLTBYP))
           ? HAL_ADF_DFLT_RSF_DISABLED : HAL_ADF_DFLT_RSF_ENABLED;

  return status;
}

/**
  * @brief  Get current reshape filter decimation ratio on a specified digital filter.
  * @param  hadf                                Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index                Digital filter index.
  * @return hal_adf_dflt_rsf_decimation_ratio_t Reshape filter decimation ratio.
  */
hal_adf_dflt_rsf_decimation_ratio_t HAL_ADF_DFLT_GetReshapeFilterDecimationRatio(const hal_adf_handle_t *hadf,
    hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  return (hal_adf_dflt_rsf_decimation_ratio_t)(uint32_t)STM32_READ_BIT(ADF_GET_BLOCK(hadf,
                                                                       digital_filter_index)->DFLTRSFR,
                                                                       ADF_DFLTRSFR_RSFLTD_Msk);
}

/**
  * @brief  Enable high-pass filter on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  cut_off_frequency    High-pass filter cut-off frequency.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_EnableHighPassFilter(const hal_adf_handle_t *hadf,
                                               hal_adf_block_index_t digital_filter_index,
                                               hal_adf_dflt_hpf_cut_off_frequency_t cut_off_frequency)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_HPF_CUT_OFF_FREQUENCY(cut_off_frequency));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTRSFR, ADF_DFLTRSFR_HPFBYP_Msk | ADF_DFLTRSFR_HPFC_Msk,
                   (uint32_t)cut_off_frequency);

  return HAL_OK;
}

/**
  * @brief  Disable high-pass filter on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_DisableHighPassFilter(const hal_adf_handle_t *hadf,
                                                hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  STM32_SET_BIT(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTRSFR, ADF_DFLTRSFR_HPFBYP);

  return HAL_OK;
}

/**
  * @brief  Check high-pass filter status on a specified digital filter.
  * @param  hadf                      Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index      Digital filter index.
  * @return hal_adf_dflt_hpf_status_t High-pass filter status.
  */
hal_adf_dflt_hpf_status_t HAL_ADF_DFLT_IsEnabledHighPassFilter(const hal_adf_handle_t *hadf,
                                                               hal_adf_block_index_t digital_filter_index)
{
  hal_adf_dflt_hpf_status_t status;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  status = (STM32_IS_BIT_SET(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTRSFR, ADF_DFLTRSFR_HPFBYP))
           ? HAL_ADF_DFLT_HPF_DISABLED : HAL_ADF_DFLT_HPF_ENABLED;

  return status;
}

/**
  * @brief  Get current high-pass filter cut-off frequency on a specified digital filter.
  * @param  hadf                                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index                 Digital filter index.
  * @return hal_adf_dflt_hpf_cut_off_frequency_t High-pass filter cut-off frequency.
  */
hal_adf_dflt_hpf_cut_off_frequency_t HAL_ADF_DFLT_GetHighPassFilterCutOffFrequency(const hal_adf_handle_t *hadf,
    hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  return (hal_adf_dflt_hpf_cut_off_frequency_t)(uint32_t)STM32_READ_BIT(ADF_GET_BLOCK(hadf,
                                                                        digital_filter_index)->DFLTRSFR,
                                                                        ADF_DFLTRSFR_HPFC_Msk);
}

/* Process functions */
/**
  * @brief  Start acquisition on a specified digital filter in polling mode.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_BUSY             The digital filter state is not HAL_ADF_DFLT_STATE_IDLE
  *                              (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_ADF_DFLT_StartAcq(hal_adf_handle_t *hadf,
                                   hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hadf, digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE,
                         HAL_ADF_DFLT_STATE_ACTIVE);

  STM32_SET_BIT(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTCR, ADF_DFLTCR_DFLTEN);

  return HAL_OK;
}

/**
  * @brief  Stop acquisition on a specified digital filter in polling mode.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_StopAcq(hal_adf_handle_t *hadf,
                                  hal_adf_block_index_t digital_filter_index)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_ACTIVE);

  /* Deactivate digital filter and clear potential pending flags */
  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);
  STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);
  STM32_WRITE_REG(p_adf_block->DFLTISR, (ADF_DFLTISR_DOVRF | ADF_DFLTISR_SATF | ADF_DFLTISR_RFOVRF));

  hadf->digital_filter_states[digital_filter_index] = HAL_ADF_DFLT_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Wait available acquisition on a specified digital filter in polling mode.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  timeout_ms           Acquisition timeout value.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_TIMEOUT          Operation exceeds user timeout.
  */
hal_status_t HAL_ADF_DFLT_PollForAcq(hal_adf_handle_t *hadf,
                                     hal_adf_block_index_t digital_filter_index,
                                     uint32_t timeout_ms)
{
  ADF_Block_TypeDef *p_adf_block;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_ACTIVE);

  tickstart = HAL_GetTick();

  /* Check if an acquisition is available */
  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);
  while (STM32_IS_BIT_CLR(p_adf_block->DFLTISR, ADF_DFLTISR_RXNEF))
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        if (STM32_IS_BIT_CLR(p_adf_block->DFLTISR, ADF_DFLTISR_RXNEF))
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  /* If acquisition mode is asynchronous single shot, set digital filter state to idle */
  if (STM32_READ_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_ACQMOD_Msk) == (uint32_t)HAL_ADF_DFLT_ACQ_MODE_ASYNC_SINGLE)
  {
    /* Deactivate digital filter and clear potential pending flags */
    STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);
    STM32_WRITE_REG(p_adf_block->DFLTISR, (ADF_DFLTISR_DOVRF | ADF_DFLTISR_SATF | ADF_DFLTISR_RFOVRF));

    hadf->digital_filter_states[digital_filter_index] = HAL_ADF_DFLT_STATE_IDLE;
  }

  return HAL_OK;
}

/**
  * @brief  Get acquisition value on a specified digital filter.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @return int32_t              Acquisition value.
  */
int32_t HAL_ADF_DFLT_GetAcqValue(const hal_adf_handle_t *hadf,
                                 hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], (uint32_t)HAL_ADF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_ADF_DFLT_STATE_ACTIVE);

  return (int32_t)(uint32_t)STM32_READ_BIT(ADF_GET_BLOCK(hadf, digital_filter_index)->DFLTDR, ADF_DFLTDR_DR_Msk);
}

/**
  * @brief  Start acquisition on a specified digital filter in interrupt mode.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_BUSY             The digital filter state is not HAL_ADF_DFLT_STATE_IDLE
  *                              (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_ADF_DFLT_StartAcq_IT(hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t digital_filter_index)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hadf, digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE,
                         HAL_ADF_DFLT_STATE_ACTIVE);

  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);
  ADF_DFLT_EnableInterruptions(p_adf_block);

  STM32_SET_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);

  return HAL_OK;
}

/**
  * @brief  Stop acquisition on a specified digital filter in interrupt mode.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_StopAcq_IT(hal_adf_handle_t *hadf,
                                     hal_adf_block_index_t digital_filter_index)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_ACTIVE);

  /* Deactivate digital filter */
  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);
  STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);

  /* Disable all acquisition interruptions */
  STM32_CLEAR_BIT(p_adf_block->DFLTIER,
                  ADF_DFLTIER_FTHIE | ADF_DFLTIER_DOVRIE | ADF_DFLTIER_SATIE | ADF_DFLTIER_RFOVRIE);

  /* Clear potential pending flags */
  STM32_WRITE_REG(p_adf_block->DFLTISR, (ADF_DFLTISR_DOVRF | ADF_DFLTISR_SATF | ADF_DFLTISR_RFOVRF));

  hadf->digital_filter_states[digital_filter_index] = HAL_ADF_DFLT_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Start acquisition on a specified digital filter in interrupt mode with optional interruptions.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  interruptions        Optional interruptions.
  *                              This parameter must be a combination of the following values:
  *                                @arg @ref HAL_ADF_DFLT_OPT_IT_NONE
  *                                @arg @ref HAL_ADF_DFLT_OPT_IT_ACQ_OVR
  *                                @arg @ref HAL_ADF_DFLT_OPT_IT_RSF_OVR
  *                                @arg @ref HAL_ADF_DFLT_OPT_IT_SAT
  *                                @arg @ref HAL_ADF_DFLT_OPT_IT_DEFAULT
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_BUSY             The digital filter state is not HAL_ADF_DFLT_STATE_IDLE
  *                              (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_ADF_DFLT_StartAcq_IT_Opt(hal_adf_handle_t *hadf,
                                          hal_adf_block_index_t digital_filter_index,
                                          uint32_t interruptions)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_ADF_DFLT_OPTIONAL_IT(interruptions));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hadf, digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE,
                         HAL_ADF_DFLT_STATE_ACTIVE);

  /* Enable only acquisition complete and specified optional interruptions */
  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);
  ADF_DFLT_EnableInterruptions_Opt(p_adf_block, interruptions);

  /* Activate digital filter */
  STM32_SET_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);

  return HAL_OK;
}

#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
/**
  * @brief  Start acquisition on a specified digital filter in DMA mode.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  p_dma_config         Pointer to DMA configuration structure.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_ERROR            Operation error.
  * @retval HAL_INVALID_PARAM    Pointer to DMA configuration structure is NULL.
  * @retval HAL_BUSY             The digital filter state is not HAL_ADF_DFLT_STATE_IDLE
  *                              (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_ADF_DFLT_StartAcq_DMA(hal_adf_handle_t *hadf,
                                       hal_adf_block_index_t digital_filter_index,
                                       const hal_adf_dma_config_t *p_dma_config)
{
  hal_status_t status = HAL_ERROR;
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(p_dma_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_dma_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(p_dma_config->data_length_byte != 0U);
  ASSERT_DBG_PARAM(IS_ADF_DFLT_DMA_DATA_RESOLUTION(p_dma_config->data_resolution));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hadf, digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE,
                         HAL_ADF_DFLT_STATE_ACTIVE);

  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);
  if (hadf->hdma[digital_filter_index] != NULL)
  {
    uint32_t src_address;

    hadf->hdma[digital_filter_index]->p_xfer_halfcplt_cb = ADF_DFLT_DMA_HalfCplt;
    hadf->hdma[digital_filter_index]->p_xfer_cplt_cb = ADF_DFLT_DMA_Cplt;
    hadf->hdma[digital_filter_index]->p_xfer_error_cb = ADF_DFLT_DMA_Error;

    src_address = (p_dma_config->data_resolution == HAL_ADF_DMA_DATA_RESOLUTION_MSB_ONLY) ?
                  (((uint32_t)&p_adf_block->DFLTDR) + 2U) : (uint32_t)&p_adf_block->DFLTDR;


    status = HAL_DMA_StartPeriphXfer_IT_Opt(hadf->hdma[digital_filter_index], src_address, p_dma_config->address,
                                            p_dma_config->data_length_byte, HAL_DMA_OPT_IT_HT);
  }

  if (status == HAL_OK)
  {
    ADF_DFLT_EnableInterruptions(p_adf_block);

    /* Enable DMA request */
    STM32_SET_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DMAEN);

    /* Activate digital filter */
    STM32_SET_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);
  }
  else
  {
#if defined (USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
    hadf->last_error_codes[digital_filter_index] |= HAL_ADF_ERROR_DMA;
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

    hadf->digital_filter_states[digital_filter_index] = HAL_ADF_DFLT_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Stop acquisition on a specified digital filter in DMA mode.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_ADF_DFLT_StopAcq_DMA(hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_ACTIVE);

  hadf->hdma[digital_filter_index]->p_xfer_abort_cb = ADF_DFLT_DMA_Abort;
  if (HAL_DMA_Abort_IT(hadf->hdma[digital_filter_index]) != HAL_OK)
  {
    ADF_Block_TypeDef *p_adf_block;

    /* Deactivate digital filter */
    p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);
    STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);

    /* Disable all acquisition interruptions */
    STM32_CLEAR_BIT(p_adf_block->DFLTIER,
                    ADF_DFLTIER_FTHIE | ADF_DFLTIER_DOVRIE | ADF_DFLTIER_SATIE | ADF_DFLTIER_RFOVRIE);

    /* Clear potential pending flags */
    STM32_WRITE_REG(p_adf_block->DFLTISR, (ADF_DFLTISR_DOVRF | ADF_DFLTISR_SATF | ADF_DFLTISR_RFOVRF));

    /* Disable DMA request */
    STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DMAEN);

    hadf->digital_filter_states[digital_filter_index] = HAL_ADF_DFLT_STATE_IDLE;

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
    hadf->p_acquisition_stop_cb(hadf, digital_filter_index);
#else
    HAL_ADF_DFLT_AcqStopCpltCallback(hadf, digital_filter_index);
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

/**
  * @brief  Start acquisition on a specified digital filter in DMA mode with optional interruptions.
  * @param  hadf                 Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  p_dma_config         Pointer to DMA configuration structure.
  * @param  interruptions        Optional interruptions.
  *                              This parameter must be a combination of the following values:
  *                                @arg @ref HAL_ADF_DFLT_OPT_IT_NONE
  *                                @arg @ref HAL_ADF_DFLT_OPT_IT_ACQ_OVR
  *                                @arg @ref HAL_ADF_DFLT_OPT_IT_RSF_OVR
  *                                @arg @ref HAL_ADF_DFLT_OPT_IT_SAT
  *                                @arg @ref HAL_ADF_DFLT_OPT_IT_DEFAULT
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_ERROR            Operation error.
  * @retval HAL_INVALID_PARAM    Pointer to DMA configuration structure is NULL.
  * @retval HAL_BUSY             The digital filter state is not HAL_ADF_DFLT_STATE_IDLE
  *                              (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_ADF_DFLT_StartAcq_DMA_Opt(hal_adf_handle_t *hadf,
                                           hal_adf_block_index_t digital_filter_index,
                                           const hal_adf_dma_config_t *p_dma_config,
                                           uint32_t interruptions)
{
  hal_status_t status = HAL_ERROR;
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(p_dma_config != NULL);
  ASSERT_DBG_PARAM(IS_ADF_DFLT_OPTIONAL_IT(interruptions));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_dma_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(p_dma_config->data_length_byte != 0U);
  ASSERT_DBG_PARAM(IS_ADF_DFLT_DMA_DATA_RESOLUTION(p_dma_config->data_resolution));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hadf, digital_filter_states[digital_filter_index], HAL_ADF_DFLT_STATE_IDLE,
                         HAL_ADF_DFLT_STATE_ACTIVE);

  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);
  if (hadf->hdma[digital_filter_index] != NULL)
  {
    uint32_t src_address;

    /* Set DMA callbacks on DMA handle */
    hadf->hdma[digital_filter_index]->p_xfer_halfcplt_cb = ADF_DFLT_DMA_HalfCplt;
    hadf->hdma[digital_filter_index]->p_xfer_cplt_cb = ADF_DFLT_DMA_Cplt;
    hadf->hdma[digital_filter_index]->p_xfer_error_cb = ADF_DFLT_DMA_Error;

    src_address = (p_dma_config->data_resolution == HAL_ADF_DMA_DATA_RESOLUTION_MSB_ONLY) ?
                  (((uint32_t)&p_adf_block->DFLTDR) + 2U) : (uint32_t)&p_adf_block->DFLTDR;


    status = HAL_DMA_StartPeriphXfer_IT_Opt(hadf->hdma[digital_filter_index], src_address, p_dma_config->address,
                                            p_dma_config->data_length_byte, HAL_DMA_OPT_IT_HT);
  }

  if (status == HAL_OK)
  {
    ADF_DFLT_EnableInterruptions_Opt(p_adf_block, interruptions);

    /* Enable DMA request */
    STM32_SET_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DMAEN);

    /* Activate digital filter */
    STM32_SET_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);
  }
  else
  {
#if defined (USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
    hadf->last_error_codes[digital_filter_index] |= HAL_ADF_ERROR_DMA;
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

    hadf->digital_filter_states[digital_filter_index] = HAL_ADF_DFLT_STATE_IDLE;
  }

  return status;
}
#endif /* USE_HAL_ADF_DMA */

/**
  * @}
  */

/** @addtogroup ADF_Exported_Functions_Group6
  * @{
This section provides a set of functions allowing to configure sound activity detector:
  - Call the function HAL_ADF_SAD_SetConfig() to configure a specified sound activity detector.
  - Call the function HAL_ADF_SAD_GetConfig() to get the current configuration of a specified sound activity detector.
  - Call the function HAL_ADF_SAD_SetFrameSize() to set frame size on a specified sound activity detector.
  - Call the function HAL_ADF_SAD_GetFrameSize() to get current frame size on a specified sound activity detector.
  - Call the function HAL_ADF_SAD_SetLearningFrames() to set learning frames on a specified sound activity detector.
  - Call the function HAL_ADF_SAD_GetLearningFrames() to get current learning frames on a specified sound activity
    detector.
  - Call the function HAL_ADF_SAD_SetSignalToNoiseThreshold() to set signal to noise threshold on a specified sound
    activity detector.
  - Call the function HAL_ADF_SAD_GetSignalToNoiseThreshold() to get current signal to noise threshold on a specified
    sound activity detector.
  - Call the function HAL_ADF_SAD_SetAmbientNoiseSlope() to set ambient noise slope on a specified sound activity
    detector.
  - Call the function HAL_ADF_SAD_GetAmbientNoiseSlope() to get current ambient noise slope on a specified sound
    activity detector.
  - Call the function HAL_ADF_SAD_SetHangoverTimeWindow() to set hangover time window on a specified sound activity
    detector.
  - Call the function HAL_ADF_SAD_GetHangoverTimeWindow() to get current hangover time window on a specified sound
    activity detector.

This section provides also a set of functions allowing to control sound activity detector:
  - Call the function HAL_ADF_SAD_EnableHysteresis() to enable hysteresis on a specified sound activity detector.
  - Call the function HAL_ADF_SAD_DisableHysteresis() to disable hysteresis on a specified sound activity detector.
  - Call the function HAL_ADF_SAD_IsEnabledHysteresis() to check hysteresis status on a specified sound activity
    detector.

This section provides also a set of functions allowing to process sound activity detector:
  - Call the function HAL_ADF_SAD_Start() to activate a specified sound activity detector in polling mode.
  - Call the function HAL_ADF_SAD_Stop() to deactivate a specified sound activity detector in polling mode.
  - Call the function HAL_ADF_SAD_IsDetected() to check detection status on a specified sound activity detector in
    polling mode.
  - Call the function HAL_ADF_SAD_PollForSoundLevel() to wait available sound level on a specified sound activity
    detector in polling mode.
  - Call the function HAL_ADF_SAD_GetSoundAndAmbientNoiseLevels() to get current sound level and ambient noise level on
    a specified sound activity detector.
  - Call the function HAL_ADF_SAD_Start_IT() to activate a specified sound activity detector in interrupt mode.
  - Call the function HAL_ADF_SAD_Stop_IT() to deactivate a specified sound activity detector in interrupt mode.
  - Call the function HAL_ADF_SAD_Start_IT_Opt() to activate a specified sound activity detector in interrupt mode with
    optional interruptions.
  */

/* Configuration functions */
/**
  * @brief  Configure a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @param  p_config                      Pointer to sound activity detector configuration structure.
  * @retval HAL_OK                        Operation completed successfully.
  * @retval HAL_INVALID_PARAM             Pointer to sound activity detector configuration structure is NULL.
  */
hal_status_t HAL_ADF_SAD_SetConfig(hal_adf_handle_t *hadf,
                                   hal_adf_block_index_t sound_activity_detector_index,
                                   const hal_adf_sad_config_t *p_config)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_ADF_SAD_MODE(p_config->mode));
  ASSERT_DBG_PARAM(IS_ADF_SAD_MEMORY_TRANSFER(p_config->memory_transfer));
  ASSERT_DBG_PARAM(IS_ADF_SAD_TRIGGER_EVENT(p_config->trigger_event));
  ASSERT_DBG_PARAM(IS_ADF_SAD_MINIMUM_AMBIENT_NOISE(p_config->minimum_ambient_noise));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index],
                   (uint32_t)HAL_ADF_SAD_STATE_RESET | (uint32_t)HAL_ADF_SAD_STATE_IDLE);

  p_adf_block = ADF_GET_BLOCK(hadf, sound_activity_detector_index);
  STM32_MODIFY_REG(p_adf_block->SADCR, ADF_SADCR_DATCAP_Msk | ADF_SADCR_DETCFG_Msk | ADF_SADCR_SADMOD_Msk,
                   (uint32_t)p_config->memory_transfer | (uint32_t)p_config->trigger_event | (uint32_t)p_config->mode);
  STM32_MODIFY_REG(p_adf_block->SADCFGR, ADF_SADCFGR_ANMIN_Msk,
                   p_config->minimum_ambient_noise << ADF_SADCFGR_ANMIN_Pos);

  hadf->sound_activity_detector_states[sound_activity_detector_index] = HAL_ADF_SAD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the current configuration of a specified sound activity detector.
  * @param hadf                          Pointer to a hal_adf_handle_t.
  * @param sound_activity_detector_index Sound activity detector index.
  * @param p_config                      Pointer to sound activity detector configuration structure.
  */
void HAL_ADF_SAD_GetConfig(const hal_adf_handle_t *hadf,
                           hal_adf_block_index_t sound_activity_detector_index,
                           hal_adf_sad_config_t *p_config)
{
  const ADF_Block_TypeDef *p_adf_block;
  uint32_t reg;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index],
                   (uint32_t)HAL_ADF_SAD_STATE_IDLE | (uint32_t)HAL_ADF_SAD_STATE_ACTIVE);

  p_adf_block = ADF_GET_BLOCK(hadf, sound_activity_detector_index);
  reg = STM32_READ_REG(p_adf_block->SADCR);
  p_config->mode = (hal_adf_sad_mode_t)(uint32_t)(reg & ADF_SADCR_SADMOD_Msk);
  p_config->memory_transfer = (hal_adf_sad_memory_transfer_t)(uint32_t)(reg & ADF_SADCR_DATCAP_Msk);
  p_config->trigger_event = (hal_adf_sad_trigger_event_t)(uint32_t)(reg & ADF_SADCR_DETCFG_Msk);
  reg = STM32_READ_REG(p_adf_block->SADCFGR);
  p_config->minimum_ambient_noise = (reg & ADF_SADCFGR_ANMIN_Msk) >> ADF_SADCFGR_ANMIN_Pos;
}

/**
  * @brief  Set frame size on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @param  frame_size                    Frame size.
  * @retval HAL_OK                        Operation completed successfully.
  */
hal_status_t HAL_ADF_SAD_SetFrameSize(const hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t sound_activity_detector_index,
                                      hal_adf_sad_frame_size_t frame_size)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));
  ASSERT_DBG_PARAM(IS_ADF_SAD_FRAME_SIZE(frame_size));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCR,
                   ADF_SADCR_FRSIZE_Msk, (uint32_t)frame_size);

  return HAL_OK;
}

/**
  * @brief  Get current frame size on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @return hal_adf_sad_frame_size_t      Frame size.
  */
hal_adf_sad_frame_size_t HAL_ADF_SAD_GetFrameSize(const hal_adf_handle_t *hadf,
                                                  hal_adf_block_index_t sound_activity_detector_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index],
                   (uint32_t)HAL_ADF_SAD_STATE_IDLE | (uint32_t)HAL_ADF_SAD_STATE_ACTIVE);

  return (hal_adf_sad_frame_size_t)(uint32_t)STM32_READ_BIT(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCR,
                                                            ADF_SADCR_FRSIZE_Msk);
}

/**
  * @brief  Set learning frames on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @param  learning_frames               Learning frames.
  * @retval HAL_OK                        Operation completed successfully.
  */
hal_status_t HAL_ADF_SAD_SetLearningFrames(const hal_adf_handle_t *hadf,
                                           hal_adf_block_index_t sound_activity_detector_index,
                                           hal_adf_sad_learning_frames_t learning_frames)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));
  ASSERT_DBG_PARAM(IS_ADF_SAD_LEARNING_FRAMES(learning_frames));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCFGR, ADF_SADCFGR_LFRNB_Msk,
                   (uint32_t)learning_frames);

  return HAL_OK;
}

/**
  * @brief  Get learning frames on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @return hal_adf_sad_learning_frames_t Learning frames.
  */
hal_adf_sad_learning_frames_t HAL_ADF_SAD_GetLearningFrames(const hal_adf_handle_t *hadf,
                                                            hal_adf_block_index_t sound_activity_detector_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index],
                   (uint32_t)HAL_ADF_SAD_STATE_IDLE | (uint32_t)HAL_ADF_SAD_STATE_ACTIVE);

  return (hal_adf_sad_learning_frames_t)(uint32_t)STM32_READ_BIT(ADF_GET_BLOCK(hadf,
                                                                               sound_activity_detector_index)->SADCFGR,
                                                                 ADF_SADCFGR_LFRNB_Msk);
}

/**
  * @brief  Set signal to noise threshold on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @param  threshold                     Signal to noise threshold.
  * @retval HAL_OK                        Operation completed successfully.
  */
hal_status_t HAL_ADF_SAD_SetSignalToNoiseThreshold(const hal_adf_handle_t *hadf,
                                                   hal_adf_block_index_t sound_activity_detector_index,
                                                   hal_adf_sad_signal_to_noise_threshold_t threshold)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));
  ASSERT_DBG_PARAM(IS_ADF_SAD_SIGNAL_TO_NOISE_THRESHOLD(threshold));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCFGR, ADF_SADCFGR_SNTHR_Msk,
                   (uint32_t)threshold);

  return HAL_OK;
}

/**
  * @brief  Get signal to noise threshold on a specified sound activity detector.
  * @param  hadf                                    Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index           Sound activity detector index.
  * @return hal_adf_sad_signal_to_noise_threshold_t Signal to noise threshold.
  */
hal_adf_sad_signal_to_noise_threshold_t HAL_ADF_SAD_GetSignalToNoiseThreshold(
  const hal_adf_handle_t *hadf,
  hal_adf_block_index_t sound_activity_detector_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index],
                   (uint32_t)HAL_ADF_SAD_STATE_IDLE | (uint32_t)HAL_ADF_SAD_STATE_ACTIVE);

  return (hal_adf_sad_signal_to_noise_threshold_t)(uint32_t)STM32_READ_BIT(
           ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCFGR, ADF_SADCFGR_SNTHR_Msk);
}

/**
  * @brief  Set ambient noise slope on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @param  ambient_noise_slope           Ambient noise slope.
  *                                       This parameter must be a number between Min_Data = 0 and Max_Data = 7.
  * @retval HAL_OK                        Operation completed successfully.
  */
hal_status_t HAL_ADF_SAD_SetAmbientNoiseSlope(const hal_adf_handle_t *hadf,
                                              hal_adf_block_index_t sound_activity_detector_index,
                                              uint32_t ambient_noise_slope)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));
  ASSERT_DBG_PARAM(IS_ADF_SAD_AMBIENT_NOISE_SLOPE(ambient_noise_slope));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCFGR, ADF_SADCFGR_ANSLP_Msk,
                   ambient_noise_slope << ADF_SADCFGR_ANSLP_Pos);

  return HAL_OK;
}

/**
  * @brief  Get ambient noise slope on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @return uint32_t                      Ambient noise slope.
  */
uint32_t HAL_ADF_SAD_GetAmbientNoiseSlope(const hal_adf_handle_t *hadf,
                                          hal_adf_block_index_t sound_activity_detector_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index],
                   (uint32_t)HAL_ADF_SAD_STATE_IDLE | (uint32_t)HAL_ADF_SAD_STATE_ACTIVE);

  return (STM32_READ_BIT(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCFGR, ADF_SADCFGR_ANSLP_Msk)
          >> ADF_SADCFGR_ANSLP_Pos);
}

/**
  * @brief  Set hangover time window on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @param  hangover_time_window          Hangover time window.
  * @retval HAL_OK                        Operation completed successfully.
  */
hal_status_t HAL_ADF_SAD_SetHangoverTimeWindow(const hal_adf_handle_t *hadf,
                                               hal_adf_block_index_t sound_activity_detector_index,
                                               hal_adf_sad_hangover_time_window_t hangover_time_window)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));
  ASSERT_DBG_PARAM(IS_ADF_SAD_HANGOVER_TIME_WINDOW(hangover_time_window));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE);

  STM32_MODIFY_REG(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCFGR, ADF_SADCFGR_HGOVR_Msk,
                   (uint32_t)hangover_time_window);

  return HAL_OK;
}

/**
  * @brief  Get hangover time window on a specified sound activity detector.
  * @param  hadf                               Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index      Sound activity detector index.
  * @return hal_adf_sad_hangover_time_window_t Hangover time window.
  */
hal_adf_sad_hangover_time_window_t HAL_ADF_SAD_GetHangoverTimeWindow(
  const hal_adf_handle_t *hadf,
  hal_adf_block_index_t sound_activity_detector_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index],
                   (uint32_t)HAL_ADF_SAD_STATE_IDLE | (uint32_t)HAL_ADF_SAD_STATE_ACTIVE);

  return (hal_adf_sad_hangover_time_window_t)(uint32_t)STM32_READ_BIT(
           ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCFGR, ADF_SADCFGR_HGOVR_Msk);
}

/* Control functions */
/**
  * @brief  Enable hysteresis on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @retval HAL_OK                        Operation completed successfully.
  */
hal_status_t HAL_ADF_SAD_EnableHysteresis(const hal_adf_handle_t *hadf,
                                          hal_adf_block_index_t sound_activity_detector_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE);

  STM32_SET_BIT(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCR, ADF_SADCR_HYSTEN);

  return HAL_OK;
}

/**
  * @brief  Disable hysteresis on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @retval HAL_OK                        Operation completed successfully.
  */
hal_status_t HAL_ADF_SAD_DisableHysteresis(const hal_adf_handle_t *hadf,
                                           hal_adf_block_index_t sound_activity_detector_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE);

  STM32_CLEAR_BIT(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCR, ADF_SADCR_HYSTEN);

  return HAL_OK;
}

/**
  * @brief  Check hysteresis status on a specified sound activity detector.
  * @param  hadf                            Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index   Sound activity detector index.
  * @return hal_adf_sad_hysteresis_status_t Hysteresis status.
  */
hal_adf_sad_hysteresis_status_t HAL_ADF_SAD_IsEnabledHysteresis(const hal_adf_handle_t *hadf,
                                                                hal_adf_block_index_t sound_activity_detector_index)
{
  hal_adf_sad_hysteresis_status_t status;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index],
                   (uint32_t)HAL_ADF_SAD_STATE_IDLE | (uint32_t)HAL_ADF_SAD_STATE_ACTIVE);

  status = (STM32_IS_BIT_SET(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCR, ADF_SADCR_HYSTEN))
           ? HAL_ADF_SAD_HYSTERESIS_ENABLED : HAL_ADF_SAD_HYSTERESIS_DISABLED;

  return status;
}

/* Process functions */
/**
  * @brief  Activate a specified sound activity detector in polling mode.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @retval HAL_OK                        Operation completed successfully.
  * @retval HAL_BUSY                      The sound activity detector state is not HAL_ADF_SAD_STATE_IDLE
  *                                       (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_ADF_SAD_Start(hal_adf_handle_t *hadf,
                               hal_adf_block_index_t sound_activity_detector_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[sound_activity_detector_index], HAL_ADF_DFLT_STATE_IDLE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hadf, sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE,
                         HAL_ADF_SAD_STATE_ACTIVE);

  STM32_SET_BIT(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->SADCR, ADF_SADCR_SADEN);

  return HAL_OK;
}

/**
  * @brief  Deactivate a specified sound activity detector in polling mode.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @retval HAL_OK                        Operation completed successfully.
  */
hal_status_t HAL_ADF_SAD_Stop(hal_adf_handle_t *hadf,
                              hal_adf_block_index_t sound_activity_detector_index)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_ACTIVE);

  /* Deactivate sound activity detector and clear potential pending flags */
  p_adf_block = ADF_GET_BLOCK(hadf, sound_activity_detector_index);
  STM32_CLEAR_BIT(p_adf_block->SADCR, ADF_SADCR_SADEN);
  STM32_WRITE_REG(p_adf_block->DFLTISR, (ADF_DFLTISR_SDDETF | ADF_DFLTISR_SDLVLF));

  hadf->sound_activity_detector_states[sound_activity_detector_index] = HAL_ADF_SAD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Check detection status on a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @return hal_adf_sad_status_t          Sound activity detection status.
  */
hal_adf_sad_status_t HAL_ADF_SAD_IsDetected(const hal_adf_handle_t *hadf,
                                            hal_adf_block_index_t sound_activity_detector_index)
{
  hal_adf_sad_status_t status;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_ACTIVE);

  status = (STM32_IS_BIT_SET(ADF_GET_BLOCK(hadf, sound_activity_detector_index)->DFLTISR, ADF_DFLTISR_SDDETF))
           ? HAL_ADF_SOUND_ACTIVITY_DETECTED : HAL_ADF_SOUND_ACTIVITY_NOT_DETECTED;

  return status;
}

/**
  * @brief  Wait available sound level on a specified sound activity detector in polling mode.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @param  timeout_ms                    Timeout value.
  * @retval HAL_OK                        Operation completed successfully.
  * @retval HAL_TIMEOUT                   Operation exceeds user timeout.
  */
hal_status_t HAL_ADF_SAD_PollForSoundLevel(const hal_adf_handle_t *hadf,
                                           hal_adf_block_index_t sound_activity_detector_index,
                                           uint32_t timeout_ms)
{
  const ADF_Block_TypeDef *p_adf_block;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_ACTIVE);

  tickstart = HAL_GetTick();

  /* Check if a sound level is available */
  p_adf_block = ADF_GET_BLOCK(hadf, sound_activity_detector_index);
  while (STM32_IS_BIT_CLR(p_adf_block->DFLTISR, ADF_DFLTISR_SDLVLF))
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        if (STM32_IS_BIT_CLR(p_adf_block->DFLTISR, ADF_DFLTISR_SDLVLF))
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Get sound level and ambient noise level on a specified sound activity detector.
  * @param hadf                          Pointer to a hal_adf_handle_t.
  * @param sound_activity_detector_index Sound activity detector index.
  * @param p_sound_level                 Pointer on sound level value.
  * @param p_ambient_noise_level         Pointer on ambient noise level value.
  */
void HAL_ADF_SAD_GetSoundAndAmbientNoiseLevels(const hal_adf_handle_t *hadf,
                                               hal_adf_block_index_t sound_activity_detector_index,
                                               uint32_t *p_sound_level,
                                               uint32_t *p_ambient_noise_level)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));
  ASSERT_DBG_PARAM(p_sound_level != NULL);
  ASSERT_DBG_PARAM(p_ambient_noise_level != NULL);

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index],
                   (uint32_t)HAL_ADF_SAD_STATE_IDLE | (uint32_t)HAL_ADF_SAD_STATE_ACTIVE);

  p_adf_block = ADF_GET_BLOCK(hadf, sound_activity_detector_index);
  *p_sound_level = STM32_READ_BIT(p_adf_block->SADSDLVR, ADF_SADSDLVR_SDLVL_Msk);
  *p_ambient_noise_level = STM32_READ_BIT(p_adf_block->SADANLVR, ADF_SADANLVR_ANLVL_Msk);
  STM32_WRITE_REG(p_adf_block->DFLTISR, ADF_DFLTISR_SDLVLF);
}

/**
  * @brief  Activate a specified sound activity detector in interrupt mode.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @retval HAL_OK                        Operation completed successfully.
  * @retval HAL_BUSY                      The sound activity detector state is not HAL_ADF_SAD_STATE_IDLE
  *                                       (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_ADF_SAD_Start_IT(hal_adf_handle_t *hadf,
                                  hal_adf_block_index_t sound_activity_detector_index)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[sound_activity_detector_index], HAL_ADF_DFLT_STATE_IDLE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hadf, sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE,
                         HAL_ADF_SAD_STATE_ACTIVE);

  /* Enable all sound activity detector interruptions */
  p_adf_block = ADF_GET_BLOCK(hadf, sound_activity_detector_index);
  STM32_SET_BIT(p_adf_block->DFLTIER, ADF_DFLTIER_SDDETIE | ADF_DFLTIER_SDLVLIE);

  /* Activate sound activity detector */
  STM32_SET_BIT(p_adf_block->SADCR, ADF_SADCR_SADEN);

  return HAL_OK;
}

/**
  * @brief  Deactivate a specified sound activity detector in interrupt mode.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @retval HAL_OK                        Operation completed successfully.
  */
hal_status_t HAL_ADF_SAD_Stop_IT(hal_adf_handle_t *hadf,
                                 hal_adf_block_index_t sound_activity_detector_index)
{
  ADF_Block_TypeDef *p_adf_block;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_ACTIVE);

  /* Deactivate sound activity detector */
  p_adf_block = ADF_GET_BLOCK(hadf, sound_activity_detector_index);
  STM32_CLEAR_BIT(p_adf_block->SADCR, ADF_SADCR_SADEN);

  /* Disable all sound activity detector interruptions */
  STM32_CLEAR_BIT(p_adf_block->DFLTIER, ADF_DFLTIER_SDDETIE | ADF_DFLTIER_SDLVLIE);

  /* Clear potential pending flags */
  STM32_WRITE_REG(p_adf_block->DFLTISR, ADF_DFLTISR_SDDETF | ADF_DFLTISR_SDLVLF);

  hadf->sound_activity_detector_states[sound_activity_detector_index] = HAL_ADF_SAD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Activate a specified sound activity detector in interrupt mode with optional interruptions.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @param  interruptions                 Optional interruptions.
  *                                       This parameter must be one of the following values:
  *                                         @arg @ref HAL_ADF_SAD_OPT_IT_NONE
  *                                         @arg @ref HAL_ADF_SAD_OPT_IT_SOUND_LEVEL
  *                                         @arg @ref HAL_ADF_SAD_OPT_IT_DEFAULT
  * @retval HAL_OK                        Operation completed successfully.
  * @retval HAL_BUSY                      The sound activity detector state is not HAL_ADF_SAD_STATE_IDLE
  *                                       (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_ADF_SAD_Start_IT_Opt(hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t sound_activity_detector_index,
                                      uint32_t interruptions)
{
  ADF_Block_TypeDef *p_adf_block;
  uint32_t it_enable;

  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));
  ASSERT_DBG_PARAM(IS_ADF_SAD_OPTIONAL_IT(interruptions));

  ASSERT_DBG_STATE(hadf->global_state, HAL_ADF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hadf->digital_filter_states[sound_activity_detector_index], HAL_ADF_DFLT_STATE_IDLE);
  ASSERT_DBG_STATE(hadf->sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hadf, sound_activity_detector_states[sound_activity_detector_index], HAL_ADF_SAD_STATE_IDLE,
                         HAL_ADF_SAD_STATE_ACTIVE);

  /* Enable sound activity detection and optional interruptions */
  p_adf_block = ADF_GET_BLOCK(hadf, sound_activity_detector_index);
  it_enable = ADF_DFLTIER_SDDETIE;
  if ((interruptions & HAL_ADF_SAD_OPT_IT_SOUND_LEVEL) == HAL_ADF_SAD_OPT_IT_SOUND_LEVEL)
  {
    it_enable |= ADF_DFLTIER_SDLVLIE;
  }
  STM32_SET_BIT(p_adf_block->DFLTIER, it_enable);

  /* Activate sound activity detector */
  STM32_SET_BIT(p_adf_block->SADCR, ADF_SADCR_SADEN);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup ADF_Exported_Functions_Group7
  * @{
This section provides function allowing to handle the ADF interrupt request on blocks, HAL_ADF_IRQHandler().

This section provides also a set of functions allowing to handle callbacks:
  - HAL_ADF_DFLT_AcqCpltCallback() is called when acquisition complete occurs on a specified digital filter.
  - HAL_ADF_DFLT_AcqHalfCpltCallback() is called when acquisition half complete occurs on a specified digital filter.
  - HAL_ADF_DFLT_AcqStopCpltCallback() is called when acquisition stop complete occurs on a specified digital filter.
  - HAL_ADF_SAD_SoundLevelCallback() is called when sound level ready occurs on a specified sound activity detector.
  - HAL_ADF_SAD_SoundActivityCallback() is called when sound detection occurs on a specified sound activity detector.
  - HAL_ADF_ErrorCallback() is called when an error occurs on a specified block.

This section provides also a set of functions allowing to register callbacks:
  - Call the function HAL_ADF_DFLT_RegisterAcqCpltCallback() to register acquisition complete callback.
  - Call the function HAL_ADF_DFLT_RegisterAcqHalfCpltCallback() to register acquisition half complete callback.
  - Call the function HAL_ADF_DFLT_RegisterAcqStopCpltCallback() to register acquisition stop complete callback.
  - Call the function HAL_ADF_SAD_RegisterSoundLevelCallback() to register sound level callback.
  - Call the function HAL_ADF_SAD_RegisterSoundActivityCallback() to register sound activity callback.
  - Call the function HAL_ADF_RegisterErrorCallback() to register error callback.
  */

/**
  * @brief Handle the ADF interrupt request on a specified block.
  * @param hadf        Pointer to a hal_adf_handle_t.
  * @param block_index Block index.
  */
void HAL_ADF_IRQHandler(hal_adf_handle_t *hadf, hal_adf_block_index_t block_index)
{
  ADF_Block_TypeDef *p_adf_block;
  uint32_t interruptions;
  uint32_t flags;
  uint32_t error = 0U;

  p_adf_block = ADF_GET_BLOCK(hadf, block_index);
  interruptions = STM32_READ_REG(p_adf_block->DFLTIER);
  flags = STM32_READ_REG(p_adf_block->DFLTISR);
  interruptions &= flags;

  /* RXFIFO threshold interruption occurrence */
  if (STM32_IS_BIT_SET(interruptions, ADF_DFLTISR_FTHF))
  {
    /* If acquisition mode is asynchronous single shot, set digital filter state to idle */
    if (STM32_READ_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_ACQMOD_Msk) == (uint32_t)HAL_ADF_DFLT_ACQ_MODE_ASYNC_SINGLE)
    {
      /* Deactivate digital filter, disable acquisition interruptions and clear potential pending flags */
      STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);
      STM32_CLEAR_BIT(p_adf_block->DFLTIER,
                      ADF_DFLTIER_FTHIE | ADF_DFLTIER_DOVRIE | ADF_DFLTIER_SATIE | ADF_DFLTIER_RFOVRIE);
      STM32_WRITE_REG(p_adf_block->DFLTISR, ADF_DFLTISR_DOVRF | ADF_DFLTISR_SATF | ADF_DFLTISR_RFOVRF);

      hadf->digital_filter_states[block_index] = HAL_ADF_DFLT_STATE_IDLE;
    }

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
    hadf->p_acquisition_cplt_cb(hadf, block_index);
#else
    HAL_ADF_DFLT_AcqCpltCallback(hadf, block_index);
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
  }

  /* Sound activity detection interruption occurrence */
  if (STM32_IS_BIT_SET(interruptions, ADF_DFLTISR_SDDETF))
  {
    /* Clear sound activity detection flag */
    STM32_SET_BIT(p_adf_block->DFLTISR, ADF_DFLTISR_SDDETF);

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
    hadf->p_sound_activity_cb(hadf, block_index);
#else
    HAL_ADF_SAD_SoundActivityCallback(hadf, block_index);
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
  }

  /* Sound level ready interruption occurrence */
  if (STM32_IS_BIT_SET(interruptions, ADF_DFLTISR_SDLVLF))
  {
    /* Clear sound level ready flag */
    STM32_SET_BIT(p_adf_block->DFLTISR, ADF_DFLTISR_SDLVLF);

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
    hadf->p_sound_level_cb(hadf, block_index);
#else
    HAL_ADF_SAD_SoundLevelCallback(hadf, block_index);
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
  }

  /* Data overflow interruption occurrence */
  if (STM32_IS_BIT_SET(interruptions, ADF_DFLTISR_DOVRF))
  {
#if defined(USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
    hadf->last_error_codes[block_index] |= HAL_ADF_ERROR_DFLT_ACQ_OVERFLOW;
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

    /* Clear data overflow flag */
    STM32_SET_BIT(p_adf_block->DFLTISR, ADF_DFLTISR_DOVRF);

    error = 1U;
  }

  /* Saturation interruption occurrence */
  if (STM32_IS_BIT_SET(interruptions, ADF_DFLTISR_SATF))
  {
#if defined(USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
    hadf->last_error_codes[block_index] |= HAL_ADF_ERROR_DFLT_SATURATION;
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

    /* Clear saturation flag */
    STM32_SET_BIT(p_adf_block->DFLTISR, ADF_DFLTISR_SATF);

    error = 1U;
  }

  /* Reshape filter overrun interruption occurrence */
  if (STM32_IS_BIT_SET(interruptions, ADF_DFLTISR_RFOVRF))
  {
#if defined(USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
    hadf->last_error_codes[block_index] |= HAL_ADF_ERROR_DFLT_RSF_OVERRUN;
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

    /* Clear reshape filter overrun flag */
    STM32_SET_BIT(p_adf_block->DFLTISR, ADF_DFLTISR_RFOVRF);

    error = 1U;
  }

  /* Clock absence detection interruption occurrence */
  if (STM32_IS_BIT_SET(interruptions, ADF_DFLTISR_CKABF))
  {
#if defined(USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
    hadf->last_error_codes[block_index] |= HAL_ADF_ERROR_SITF_CLOCK_ABSENCE;
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

    /* Clear clock absence detection flag */
    STM32_SET_BIT(p_adf_block->DFLTISR, ADF_DFLTISR_CKABF);

    error = 1U;
  }

  if (error != 0U)
  {
#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
    hadf->p_error_cb(hadf, block_index);
#else
    HAL_ADF_ErrorCallback(hadf, block_index);
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
  }
}

/**
  * @brief   Acquisition complete callback.
  * @param   hadf                 Pointer to a hal_adf_handle_t.
  * @param   digital_filter_index Digital filter index.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_ADF_DFLT_AcqCpltCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t digital_filter_index)
{
  STM32_UNUSED(hadf);
  STM32_UNUSED(digital_filter_index);
}

/**
  * @brief   Acquisition half complete callback.
  * @param   hadf                 Pointer to a hal_adf_handle_t.
  * @param   digital_filter_index Digital filter index.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_ADF_DFLT_AcqHalfCpltCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t digital_filter_index)
{
  STM32_UNUSED(hadf);
  STM32_UNUSED(digital_filter_index);
}

/**
  * @brief   Acquisition stop callback.
  * @param   hadf                 Pointer to a hal_adf_handle_t.
  * @param   digital_filter_index Digital filter index.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_ADF_DFLT_AcqStopCpltCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t digital_filter_index)
{
  STM32_UNUSED(hadf);
  STM32_UNUSED(digital_filter_index);
}

/**
  * @brief   Sound level callback.
  * @param   hadf                          Pointer to a hal_adf_handle_t.
  * @param   sound_activity_detector_index Sound activity detector index.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_ADF_SAD_SoundLevelCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t sound_activity_detector_index)
{
  STM32_UNUSED(hadf);
  STM32_UNUSED(sound_activity_detector_index);
}

/**
  * @brief   Sound activity callback.
  * @param   hadf                          Pointer to a hal_adf_handle_t.
  * @param   sound_activity_detector_index Sound activity detector index.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_ADF_SAD_SoundActivityCallback(hal_adf_handle_t *hadf,
                                              hal_adf_block_index_t sound_activity_detector_index)
{
  STM32_UNUSED(hadf);
  STM32_UNUSED(sound_activity_detector_index);
}

/**
  * @brief   Error callback.
  * @param   hadf        Pointer to a hal_adf_handle_t.
  * @param   block_index Block index.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_ADF_ErrorCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t block_index)
{
  STM32_UNUSED(hadf);
  STM32_UNUSED(block_index);
}

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a user acquisition complete callback.
  * @param  hadf              Pointer to a hal_adf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_ADF_DFLT_RegisterAcqCpltCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hadf->p_acquisition_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user acquisition half complete callback.
  * @param  hadf              Pointer to a hal_adf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_ADF_DFLT_RegisterAcqHalfCpltCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hadf->p_acquisition_half_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user acquisition stop callback.
  * @param  hadf              Pointer to a hal_adf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_ADF_DFLT_RegisterAcqStopCpltCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hadf->p_acquisition_stop_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user sound level callback.
  * @param  hadf              Pointer to a hal_adf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_ADF_SAD_RegisterSoundLevelCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hadf->p_sound_level_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user sound activity callback.
  * @param  hadf              Pointer to a hal_adf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_ADF_SAD_RegisterSoundActivityCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hadf->p_sound_activity_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user error callback.
  * @param  hadf              Pointer to a hal_adf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_ADF_RegisterErrorCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hadf->p_error_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup ADF_Exported_Functions_Group8
  * @{
This section provides a set of functions allowing to get all current states:
  - Call the function HAL_ADF_GetState() to get the current global state.
  - Call the function HAL_ADF_SITF_GetState() to get the current state of a specified serial interface.
  - Call the function HAL_ADF_DFLT_GetState() to get the current state of a specified digital filter.
  - Call the function HAL_ADF_SAD_GetState() to get the current state of a specified sound activity detector.
  */

/**
  * @brief  Get the current global state.
  * @param  hadf            Pointer to a hal_adf_handle_t.
  * @return hal_adf_state_t Global state.
  */
hal_adf_state_t HAL_ADF_GetState(const hal_adf_handle_t *hadf)
{
  ASSERT_DBG_PARAM(hadf != NULL);

  return hadf->global_state;
}

/**
  * @brief  Get the current state of a specified serial interface.
  * @param  hadf                             Pointer to a hal_adf_handle_t.
  * @param  serial_interface_index           Serial interface index.
  * @return hal_adf_serial_interface_state_t Serial interface state.
  */
hal_adf_serial_interface_state_t HAL_ADF_SITF_GetState(const hal_adf_handle_t *hadf,
                                                       hal_adf_block_index_t serial_interface_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)serial_interface_index));

  return hadf->serial_interface_states[serial_interface_index];
}

/**
  * @brief  Get the current state of a specified digital filter.
  * @param  hadf                           Pointer to a hal_adf_handle_t.
  * @param  digital_filter_index           Digital filter index.
  * @return hal_adf_digital_filter_state_t Digital filter state.
  */
hal_adf_digital_filter_state_t HAL_ADF_DFLT_GetState(const hal_adf_handle_t *hadf,
                                                     hal_adf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)digital_filter_index));

  return hadf->digital_filter_states[digital_filter_index];
}

/**
  * @brief  Get the current state of a specified sound activity detector.
  * @param  hadf                          Pointer to a hal_adf_handle_t.
  * @param  sound_activity_detector_index Sound activity detector index.
  * @return hal_adf_sad_state_t           Sound activity detector state.
  */
hal_adf_sad_state_t HAL_ADF_SAD_GetState(const hal_adf_handle_t *hadf,
                                         hal_adf_block_index_t sound_activity_detector_index)
{
  ASSERT_DBG_PARAM(hadf != NULL);
  ASSERT_DBG_PARAM(IS_ADF_BLOCK_INDEX((uint32_t)sound_activity_detector_index));

  return hadf->sound_activity_detector_states[sound_activity_detector_index];
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup ADF_Private_Functions
  * @{
  */

/**
  * @brief  Adjust gain to register value.
  * @param  gain    User gain.
  * @return int32_t Register gain value.
  */
static uint32_t ADF_AdjustGainToRegisterValue(int32_t gain)
{
  uint32_t register_gain;

  if (gain < 0)
  {
    int32_t adjust_gain;

    /* adjust gain value to set on register for negative value (offset of -16) */
    adjust_gain = gain - 16;
    register_gain = ((uint32_t)adjust_gain) & (ADF_DFLTCICR_SCALE_Msk >> ADF_DFLTCICR_SCALE_Pos);
  }
  else
  {
    /* for positive value, no offset to apply */
    register_gain = (uint32_t)gain;
  }

  return register_gain;
}

/**
  * @brief  Adjust gain from register value.
  * @param  register_gain Register gain value.
  * @return uint32_t      User gain.
  */
static int32_t ADF_AdjustGainFromRegisterValue(uint32_t register_gain)
{
  int32_t gain;

  if (register_gain > 31U)
  {
    /* adjust gain value to set on register for negative value (offset of +16) */
    gain = (int32_t)(uint32_t)(register_gain | ~(ADF_DFLTCICR_SCALE_Msk >> ADF_DFLTCICR_SCALE_Pos)) + 16;
  }
  else
  {
    /* for positive value, no offset to apply */
    gain = (int32_t) register_gain;
  }

  return gain;
}

/**
  * @brief  Enable all acquisition interruptions for a specified digital filter.
  * @param  p_adf_block Pointer to a specified ADF block.
  */
static void ADF_DFLT_EnableInterruptions(ADF_Block_TypeDef *p_adf_block)
{
  uint32_t it_enable;

  it_enable = ADF_DFLTIER_FTHIE | ADF_DFLTIER_DOVRIE | ADF_DFLTIER_SATIE;
  if (STM32_IS_BIT_CLR(p_adf_block->DFLTRSFR, ADF_DFLTRSFR_RSFLTBYP))
  {
    it_enable |= ADF_DFLTIER_RFOVRIE;
  }
  STM32_MODIFY_REG(p_adf_block->DFLTIER, ADF_DFLTIER_FTHIE_Msk | ADF_DFLTIER_DOVRIE_Msk | ADF_DFLTIER_SATIE_Msk
                   | ADF_DFLTIER_RFOVRIE_Msk, it_enable);
}

/**
  * @brief  Enable only acquisition complete and optional interruptions for a specified digital filter.
  * @param  p_adf_block Pointer to ADF block.
  * @param  interruptions Optional interruptions.
  *                       This parameter must be a combination of the following values:
  *                         @arg @ref HAL_ADF_DFLT_OPT_IT_NONE
  *                         @arg @ref HAL_ADF_DFLT_OPT_IT_ACQ_OVR
  *                         @arg @ref HAL_ADF_DFLT_OPT_IT_RSF_OVR
  *                         @arg @ref HAL_ADF_DFLT_OPT_IT_SAT
  *                         @arg @ref HAL_ADF_DFLT_OPT_IT_DEFAULT
  */
static void ADF_DFLT_EnableInterruptions_Opt(ADF_Block_TypeDef *p_adf_block, uint32_t interruptions)
{
  uint32_t it_enable;

  it_enable = ADF_DFLTIER_FTHIE;
  if ((interruptions & HAL_ADF_DFLT_OPT_IT_ACQ_OVR) == HAL_ADF_DFLT_OPT_IT_ACQ_OVR)
  {
    it_enable |= ADF_DFLTIER_DOVRIE;
  }
  if ((interruptions & HAL_ADF_DFLT_OPT_IT_SAT) == HAL_ADF_DFLT_OPT_IT_SAT)
  {
    it_enable |= ADF_DFLTIER_SATIE;
  }
  if ((interruptions & HAL_ADF_DFLT_OPT_IT_RSF_OVR) == HAL_ADF_DFLT_OPT_IT_RSF_OVR)
  {
    it_enable |= ADF_DFLTIER_RFOVRIE;
  }
  STM32_MODIFY_REG(p_adf_block->DFLTIER, ADF_DFLTIER_FTHIE_Msk | ADF_DFLTIER_DOVRIE_Msk | ADF_DFLTIER_SATIE_Msk
                   | ADF_DFLTIER_RFOVRIE_Msk, it_enable);
}

#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
/**
  * @brief  Get block index corresponding to DMA handle on ADF handle.
  * @param  hadf                  Pointer to a hal_adf_handle_t.
  * @param  hdma                  Pointer to a hal_dma_handle_t.
  * @return hal_adf_block_index_t Digital filter index.
  */
static hal_adf_block_index_t ADF_DFLT_GetBlockIndexFromDmaHandle(const hal_adf_handle_t *hadf,
                                                                 const hal_dma_handle_t *hdma)
{
  uint32_t index = 0U;

#if (ADF1_BLOCKS_NUMBER > 1U)
  while ((hadf->hdma[index] != hdma) && (index < (ADF1_BLOCKS_NUMBER - 1U)))
  {
    index++;
  }
#else
  STM32_UNUSED(hadf);
  STM32_UNUSED(hdma);
#endif /* (ADF1_BLOCKS_NUMBER > 1U) */

  return (hal_adf_block_index_t) index;
}

/**
  * @brief  DMA transfer complete callback.
  * @param  hdma Pointer to a hal_dma_handle_t.
  */
static void ADF_DFLT_DMA_Cplt(hal_dma_handle_t *hdma)
{
  hal_adf_handle_t *hadf = (hal_adf_handle_t *) hdma->p_parent;
  hal_adf_block_index_t digital_filter_index;
  ADF_Block_TypeDef *p_adf_block;

  /* Retrieve digital filter index from DMA handle */
  digital_filter_index = ADF_DFLT_GetBlockIndexFromDmaHandle(hadf, hdma);
  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check if DMA in circular mode*/
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    /* Deactivate digital filter */
    STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);

    /* Disable DMA request */
    STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DMAEN);

    /* Disable all acquisition interruptions */
    STM32_CLEAR_BIT(p_adf_block->DFLTIER,
                    ADF_DFLTIER_FTHIE | ADF_DFLTIER_DOVRIE | ADF_DFLTIER_SATIE | ADF_DFLTIER_RFOVRIE);

    /* Clear potential pending flags */
    STM32_WRITE_REG(p_adf_block->DFLTISR, (ADF_DFLTISR_DOVRF | ADF_DFLTISR_SATF | ADF_DFLTISR_RFOVRF));

    hadf->digital_filter_states[digital_filter_index] = HAL_ADF_DFLT_STATE_IDLE;
  }

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
  hadf->p_acquisition_cplt_cb(hadf, digital_filter_index);
#else
  HAL_ADF_DFLT_AcqCpltCallback(hadf, digital_filter_index);
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA half transfer complete callback.
  * @param  hdma Pointer to a hal_dma_handle_t.
  */
static void ADF_DFLT_DMA_HalfCplt(hal_dma_handle_t *hdma)
{
  hal_adf_handle_t *hadf = (hal_adf_handle_t *) hdma->p_parent;
  hal_adf_block_index_t digital_filter_index;

  /* Retrieve digital filter index from DMA handle */
  digital_filter_index = ADF_DFLT_GetBlockIndexFromDmaHandle(hadf, hdma);

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
  hadf->p_acquisition_half_cplt_cb(hadf, digital_filter_index);
#else
  HAL_ADF_DFLT_AcqHalfCpltCallback(hadf, digital_filter_index);
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA error callback.
  * @param  hdma Pointer to a hal_dma_handle_t.
  */
static void ADF_DFLT_DMA_Error(hal_dma_handle_t *hdma)
{
  hal_adf_handle_t *hadf = (hal_adf_handle_t *) hdma->p_parent;
  hal_adf_block_index_t digital_filter_index;
  ADF_Block_TypeDef *p_adf_block;

  /* Retrieve digital filter index from DMA handle */
  digital_filter_index = ADF_DFLT_GetBlockIndexFromDmaHandle(hadf, hdma);
  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);

#if defined(USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
  hadf->last_error_codes[digital_filter_index] |= HAL_ADF_ERROR_DMA;
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

  /* Deactivate digital filter */
  STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);

  /* Disable DMA request */
  STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DMAEN);

  /* Disable all acquisition interruptions */
  STM32_CLEAR_BIT(p_adf_block->DFLTIER,
                  ADF_DFLTIER_FTHIE | ADF_DFLTIER_DOVRIE | ADF_DFLTIER_SATIE | ADF_DFLTIER_RFOVRIE);

  /* Clear potential pending flags */
  STM32_WRITE_REG(p_adf_block->DFLTISR, (ADF_DFLTISR_DOVRF | ADF_DFLTISR_SATF | ADF_DFLTISR_RFOVRF));

  hadf->digital_filter_states[digital_filter_index] = HAL_ADF_DFLT_STATE_IDLE;

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
  hadf->p_error_cb(hadf, digital_filter_index);
#else
  HAL_ADF_ErrorCallback(hadf, digital_filter_index);
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA abort callback.
  * @param  hdma Pointer to a hal_dma_handle_t.
  */
static void ADF_DFLT_DMA_Abort(hal_dma_handle_t *hdma)
{
  hal_adf_handle_t *hadf = (hal_adf_handle_t *) hdma->p_parent;
  hal_adf_block_index_t digital_filter_index;
  ADF_Block_TypeDef *p_adf_block;

  /* Retrieve digital filter index from DMA handle */
  digital_filter_index = ADF_DFLT_GetBlockIndexFromDmaHandle(hadf, hdma);
  p_adf_block = ADF_GET_BLOCK(hadf, digital_filter_index);

  /* Deactivate digital filter */
  STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DFLTEN);

  /* Disable DMA request */
  STM32_CLEAR_BIT(p_adf_block->DFLTCR, ADF_DFLTCR_DMAEN);

  /* Disable all acquisition interruptions */
  STM32_CLEAR_BIT(p_adf_block->DFLTIER,
                  ADF_DFLTIER_FTHIE | ADF_DFLTIER_DOVRIE | ADF_DFLTIER_SATIE | ADF_DFLTIER_RFOVRIE);

  /* Clear potential pending flags */
  STM32_WRITE_REG(p_adf_block->DFLTISR, (ADF_DFLTISR_DOVRF | ADF_DFLTISR_SATF | ADF_DFLTISR_RFOVRF));

  hadf->digital_filter_states[digital_filter_index] = HAL_ADF_DFLT_STATE_IDLE;

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
  hadf->p_acquisition_stop_cb(hadf, digital_filter_index);
#else
  HAL_ADF_DFLT_AcqStopCpltCallback(hadf, digital_filter_index);
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_ADF_DMA */

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_ADF_MODULE */
#endif /* ADF1 */
/**
  * @}
  */
