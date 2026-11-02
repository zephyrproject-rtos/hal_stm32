/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_adf.h
  * @brief   Header file of ADF HAL module.
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
#ifndef STM32H7PXX_HAL_ADF_H
#define STM32H7PXX_HAL_ADF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */
#if defined (ADF1)

/** @defgroup ADF ADF
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup ADF_Exported_Constants HAL ADF constants
  * @{
  */

#if defined(USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
/** @defgroup ADF_Error_Codes ADF error codes
  * @{
  */
#define HAL_ADF_ERROR_NONE               (0UL)       /*!< No error */
#define HAL_ADF_ERROR_DFLT_ACQ_OVERFLOW  (1UL << 0U) /*!< Overflow occurs during acquisition */
#define HAL_ADF_ERROR_DFLT_RSF_OVERRUN   (1UL << 1U) /*!< Overrun occurs on reshape filter */
#define HAL_ADF_ERROR_SITF_CLOCK_ABSENCE (1UL << 2U) /*!< Clock absence detection occurs */
#define HAL_ADF_ERROR_DFLT_SATURATION    (1UL << 3U) /*!< Saturation detection occurs */
#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
#define HAL_ADF_ERROR_DMA                (1UL << 4U) /*!< DMA error occurs */
#endif /* USE_HAL_ADF_DMA */
/**
  * @}
  */
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

/** @defgroup ADF_DFLT_Optional_Interrupts ADF DFLT optional interrupts
  * @{
  */
#define HAL_ADF_DFLT_OPT_IT_NONE    (0U)                             /*!< No optional interrupt */
#define HAL_ADF_DFLT_OPT_IT_ACQ_OVR (1UL << 0U)                      /*!< Acquisition overflow interrupt */
#define HAL_ADF_DFLT_OPT_IT_RSF_OVR (1UL << 1U)                      /*!< Reshape filter overrun interrupt */
#define HAL_ADF_DFLT_OPT_IT_SAT     (1UL << 2U)                      /*!< Saturation interrupt */
#define HAL_ADF_DFLT_OPT_IT_DEFAULT (HAL_ADF_DFLT_OPT_IT_ACQ_OVR \
                                     | HAL_ADF_DFLT_OPT_IT_RSF_OVR \
                                     | HAL_ADF_DFLT_OPT_IT_SAT)      /*!< All optional interrupts */
/**
  * @}
  */

/** @defgroup ADF_SAD_Optional_Interrupts ADF SAD optional interrupts
  * @{
  */
#define HAL_ADF_SAD_OPT_IT_NONE        (0U)                           /*!< No optional interrupt */
#define HAL_ADF_SAD_OPT_IT_SOUND_LEVEL (1UL << 0U)                    /*!< SAD sound level interrupt */
#define HAL_ADF_SAD_OPT_IT_DEFAULT     HAL_ADF_SAD_OPT_IT_SOUND_LEVEL /*!< All optional interrupts */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADF_Exported_Types HAL ADF types
  * @{
  */

/** @defgroup ADF_Exported_Types_Group1 Enumerations
  * @{
  */

/**
  * @brief HAL ADF instances definitions.
  */
typedef enum
{
  HAL_ADF1 = ADF1_BASE /*!< Peripheral instance ADF1 */
} hal_adf_t;

/**
  * @brief HAL ADF states definitions.
  */
typedef enum
{
  HAL_ADF_STATE_RESET  = (0U),         /*!< ADF not initialized */
  HAL_ADF_STATE_INIT   = (1UL << 31U), /*!< ADF Initialized but processing clock divider not yet configured */
  HAL_ADF_STATE_IDLE   = (1UL << 30U), /*!< ADF Initialized, at least processing clock divider configured
                                           but clock generator disabled */
  HAL_ADF_STATE_ACTIVE = (1UL << 29U)  /*!< ADF clock generator enabled */
} hal_adf_state_t;

/**
  * @brief HAL ADF output clocks definitions.
  */
typedef enum
{
  HAL_ADF_OUTPUT_CLOCK_NONE =  0U,                  /*!< ADF_CCK0 and ADF_CCK1 are used as input clocks */
  HAL_ADF_OUTPUT_CLOCK_CCK0 =  ADF_CKGCR_CCK0DIR,   /*!< Only ADF_CCK0 is used as output clock */
  HAL_ADF_OUTPUT_CLOCK_CCK1 =  ADF_CKGCR_CCK1DIR,   /*!< Only ADF_CCK1 is used as output clock */
  HAL_ADF_OUTPUT_CLOCK_ALL  = (ADF_CKGCR_CCK0DIR \
                               | ADF_CKGCR_CCK1DIR) /*!< ADF_CCK0 and ADF_CCK1 are used as output clocks */
} hal_adf_output_clock_pins_t;

/**
  * @brief HAL ADF output clocks status definitions.
  */
typedef enum
{
  HAL_ADF_OUTPUT_CLOCK_DISABLED     = 0U, /*!< ADF_CCK0 and ADF_CCK1 output clocks disabled */
  HAL_ADF_OUTPUT_CLOCK_CCK0_ENABLED = 1U, /*!< Only ADF_CCK0 output clock enabled */
  HAL_ADF_OUTPUT_CLOCK_CCK1_ENABLED = 2U, /*!< Only ADF_CCK1 output clock enabled */
  HAL_ADF_OUTPUT_CLOCK_ALL_ENABLED  = 3U  /*!< ADF_CCK0 and ADF_CCK1 output clocks enabled */
} hal_adf_output_clock_status_t;

/**
  * @brief HAL ADF output clock trigger sources definitions.
  */
typedef enum
{
  HAL_ADF_OUT_CLOCK_TRIG_TRGO   =  0U,                /*!< Source is TRGO signal */
  HAL_ADF_OUT_CLOCK_TRIG_EXTI15 =  ADF_CKGCR_TRGSRC_1 /*!< Source is EXTI15 signal */
} hal_adf_output_clock_trigger_source_t;

/**
  * @brief HAL ADF output clock trigger edges definitions.
  */
typedef enum
{
  HAL_ADF_OUT_CLOCK_TRIG_RISING_EDGE  = 0U,               /*!< Rising edge */
  HAL_ADF_OUT_CLOCK_TRIG_FALLING_EDGE = ADF_CKGCR_TRGSENS /*!< Falling edge */
} hal_adf_output_clock_trigger_edge_t;

/**
  * @brief HAL ADF output clock trigger status definitions.
  */
typedef enum
{
  HAL_ADF_OUT_CLOCK_TRIG_DISABLED = 0U, /*!< Output clock trigger disabled */
  HAL_ADF_OUT_CLOCK_TRIG_ENABLED  = 1U  /*!< Output clock trigger enabled */
} hal_adf_output_clock_trigger_status_t;

/**
  * @brief HAL ADF trigger output status definitions.
  */
typedef enum
{
  HAL_ADF_TRIGGER_OUTPUT_DISABLED = 0U, /*!< Trigger output disabled */
  HAL_ADF_TRIGGER_OUTPUT_ENABLED  = 1U  /*!< Trigger output enabled */
} hal_adf_trigger_output_status_t;

/**
  * @brief HAL ADF block indexes definitions.
  */
typedef enum
{
  HAL_ADF_BLOCK_INDEX_0 = 0U  /*!< ADF block 0 */
} hal_adf_block_index_t;

/**
  * @brief HAL ADF serial interface states definitions.
  */
typedef enum
{
  HAL_ADF_SITF_STATE_RESET  = (1UL << 31U), /*!< ADF serial interface not configured */
  HAL_ADF_SITF_STATE_IDLE   = (1UL << 30U), /*!< ADF serial interface configured but not activated */
  HAL_ADF_SITF_STATE_ACTIVE = (1UL << 29U)  /*!< ADF serial interface activated */
} hal_adf_serial_interface_state_t;

/**
  * @brief HAL ADF serial interface modes definitions.
  */
typedef enum
{
  HAL_ADF_SITF_MODE_LF_MASTER_SPI      = 0U,                   /*!< LF master SPI mode */
  HAL_ADF_SITF_MODE_NORMAL_SPI         = ADF_SITFCR_SITFMOD_0, /*!< Normal SPI mode */
  HAL_ADF_SITF_MODE_MANCHESTER_FALLING = ADF_SITFCR_SITFMOD_1, /*!< Manchester falling mode */
  HAL_ADF_SITF_MODE_MANCHESTER_RISING  = ADF_SITFCR_SITFMOD    /*!< Manchester rising mode */
} hal_adf_serial_interface_mode_t;

/**
  * @brief HAL ADF serial interface clock sources definitions.
  */
typedef enum
{
  HAL_ADF_SITF_CLOCK_SOURCE_CCK0 = 0U,                 /*!< Common clock 0 source */
  HAL_ADF_SITF_CLOCK_SOURCE_CCK1 = ADF_SITFCR_SCKSRC_0 /*!< Common clock 1 source */
} hal_adf_serial_interface_clock_source_t;

/**
  * @brief HAL ADF clock absence status definitions.
  */
typedef enum
{
  HAL_ADF_SITF_CKAB_NOT_DETECTED = 0U, /*!< Clock absence not detected */
  HAL_ADF_SITF_CKAB_DETECTED     = 1U  /*!< Clock absence detected */
} hal_adf_sitf_ckab_status_t;

/**
  * @brief HAL ADF bitstream input edges definitions.
  */
typedef enum
{
  HAL_ADF_BSMX_INPUT_RISING  = 0U, /*!< Rising edge */
  HAL_ADF_BSMX_INPUT_FALLING = 1U  /*!< Falling edge */
} hal_adf_bitstream_input_edge_t;

/**
  * @brief HAL ADF digital filter states definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_STATE_RESET  = (1UL << 31U), /*!< ADF digital filter not configured */
  HAL_ADF_DFLT_STATE_IDLE   = (1UL << 30U), /*!< ADF digital filter configured but not activated */
  HAL_ADF_DFLT_STATE_ACTIVE = (1UL << 29U)  /*!< ADF digital filter activated */
} hal_adf_digital_filter_state_t;

/**
  * @brief HAL ADF digital filter data sources definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_DATA_SOURCE_BSMX    = 0U,                    /*!< Bitstream matrix */
  HAL_ADF_DFLT_DATA_SOURCE_ADCITF1 = ADF_DFLTCICR_DATSRC_1, /*!< ADC interface 1 (ADC1) */
  HAL_ADF_DFLT_DATA_SOURCE_ADCITF2 = ADF_DFLTCICR_DATSRC    /*!< ADC interface 2 (ADC2) */
} hal_adf_dflt_data_source_t;

/**
  * @brief HAL ADF digital filter CIC modes definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_CIC_ONE_FILTER_SINC4    =  ADF_DFLTCICR_CICMOD_2,    /*!< One filter in Sinc4 order */
  HAL_ADF_DFLT_CIC_ONE_FILTER_SINC5    = (ADF_DFLTCICR_CICMOD_0 \
                                          | ADF_DFLTCICR_CICMOD_2)  /*!< One filter in Sinc5 order */
} hal_adf_dflt_cic_mode_t;

/**
  * @brief HAL ADF digital filter acquisition modes definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_ACQ_MODE_ASYNC_CONT    =  0U,                     /*!< Asynchronous, continuous */
  HAL_ADF_DFLT_ACQ_MODE_ASYNC_SINGLE  =  ADF_DFLTCR_ACQMOD_0,    /*!< Asynchronous, single-shot */
  HAL_ADF_DFLT_ACQ_MODE_SYNC_CONT     =  ADF_DFLTCR_ACQMOD_1,    /*!< Synchronous, continuous */
  HAL_ADF_DFLT_ACQ_MODE_SYNC_SINGLE   = (ADF_DFLTCR_ACQMOD_0 \
                                         | ADF_DFLTCR_ACQMOD_1), /*!< Synchronous, single-shot */
  HAL_ADF_DFLT_ACQ_MODE_WINDOW_CONT   =  ADF_DFLTCR_ACQMOD_2     /*!< Window, continuous */
} hal_adf_dflt_acquisition_mode_t;

/**
  * @brief HAL ADF digital filter trigger sources definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_TRIG_TRGO   =  0U,                 /*!< Source is TRGO signal */
  HAL_ADF_DFLT_TRIG_EXTI15 =  ADF_DFLTCR_TRGSRC_1 /*!< Source is EXTI15 signal */
} hal_adf_dflt_trigger_source_t;

/**
  * @brief HAL ADF digital filter trigger edges definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_TRIG_RISING_EDGE  = 0U,                /*!< Rising edge */
  HAL_ADF_DFLT_TRIG_FALLING_EDGE = ADF_DFLTCR_TRGSENS /*!< Falling edge */
} hal_adf_dflt_trigger_edge_t;

/**
  * @brief HAL ADF digital filter FIFO thresholds definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_FIFO_THRESHOLD_NOT_EMPTY = 0U,            /*!< Event generated when FIFO is not empty */
  HAL_ADF_DFLT_FIFO_THRESHOLD_HALF_FULL = ADF_DFLTCR_FTH /*!< Event generated when FIFO is half-full */
} hal_adf_dflt_fifo_threshold_t;

/**
  * @brief HAL ADF reshape filter decimation ratios definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_RSF_DR_4 = 0U,                 /*!< Reshape filter decimation ratio is 4 */
  HAL_ADF_DFLT_RSF_DR_1 = ADF_DFLTRSFR_RSFLTD /*!< Reshape filter decimation ratio is 1 */
} hal_adf_dflt_rsf_decimation_ratio_t;

/**
  * @brief HAL ADF reshape filter status definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_RSF_DISABLED = 0U, /*!< Reshape filter disabled */
  HAL_ADF_DFLT_RSF_ENABLED  = 1U  /*!< Reshape filter enabled */
} hal_adf_dflt_rsf_status_t;

/**
  * @brief HAL ADF high-pass filter cut-off frequencies definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_HPF_CUT_OFF_0_000625FPCM = 0U,                  /*!< Cut-off frequency of 0.000625xFpcm */
  HAL_ADF_DFLT_HPF_CUT_OFF_0_00125FPCM  = ADF_DFLTRSFR_HPFC_0, /*!< Cut-off frequency of 0.00125xFpcm */
  HAL_ADF_DFLT_HPF_CUT_OFF_0_0025FPCM   = ADF_DFLTRSFR_HPFC_1, /*!< Cut-off frequency of 0.0025xFpcm */
  HAL_ADF_DFLT_HPF_CUT_OFF_0_0095FPCM   = ADF_DFLTRSFR_HPFC    /*!< Cut-off frequency of 0.0095xFpcm */
} hal_adf_dflt_hpf_cut_off_frequency_t;

/**
  * @brief HAL ADF high-pass filter status definitions.
  */
typedef enum
{
  HAL_ADF_DFLT_HPF_DISABLED = 0U, /*!< High-pass filter disabled */
  HAL_ADF_DFLT_HPF_ENABLED  = 1U  /*!< High-pass filter enabled */
} hal_adf_dflt_hpf_status_t;

#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
/**
  * @brief HAL ADF DMA data resolutions definitions.
  */
typedef enum
{
  HAL_ADF_DMA_DATA_RESOLUTION_FULL     = 0U, /*!< Transfer the full 24 bits of the acquisition data */
  HAL_ADF_DMA_DATA_RESOLUTION_MSB_ONLY = 1U  /*!< Transfer only the 16 MSB of the acquisition data */
} hal_adf_dma_data_resolution_t;
#endif /* USE_HAL_ADF_DMA */

/**
  * @brief HAL ADF sound activity detector states definitions.
  */
typedef enum
{
  HAL_ADF_SAD_STATE_RESET  = (1UL << 31U), /*!< ADF sound activity detector not configured */
  HAL_ADF_SAD_STATE_IDLE   = (1UL << 30U), /*!< ADF sound activity detector configured but not activated */
  HAL_ADF_SAD_STATE_ACTIVE = (1UL << 29U)  /*!< ADF sound activity detector activated */
} hal_adf_sad_state_t;

/**
  * @brief HAL ADF sound activity detector modes definitions.
  */
typedef enum
{
  HAL_ADF_SAD_MODE_VOICE_ACTIVITY = 0U,                 /*!< Voice activity detector */
  HAL_ADF_SAD_MODE_SOUND          = ADF_SADCR_SADMOD_0, /*!< Sound detector */
  HAL_ADF_SAD_MODE_AMBIENT_NOISE  = ADF_SADCR_SADMOD    /*!< Ambient noise detector */
} hal_adf_sad_mode_t;

/**
  * @brief HAL ADF sound activity detector memory transfers definitions.
  */
typedef enum
{
  HAL_ADF_SAD_MEMORY_TRANSFER_NO               = 0U,                 /*!< No memory transfer */
  HAL_ADF_SAD_MEMORY_TRANSFER_DURING_DETECTION = ADF_SADCR_DATCAP_0, /*!< Memory transfer only during detection */
  HAL_ADF_SAD_MEMORY_TRANSFER_ALWAYS           = ADF_SADCR_DATCAP    /*!< Memory transfer always */
} hal_adf_sad_memory_transfer_t;

/**
  * @brief HAL ADF sound activity detector trigger events definitions.
  */
typedef enum
{
  HAL_ADF_SAD_TRIGGER_ENTER_DETECT      = 0U,              /*!< Event when enter in detect state */
  HAL_ADF_SAD_TRIGGER_ENTER_EXIT_DETECT = ADF_SADCR_DETCFG /*!< Event when enter or exit from detect state */
} hal_adf_sad_trigger_event_t;

/**
  * @brief HAL ADF sound activity detector frame sizes definitions.
  */
typedef enum
{
  HAL_ADF_SAD_FRAME_SIZE_8_PCM_SAMPLES   =  0U,                    /*!< Frame size of 8 PCM samples */
  HAL_ADF_SAD_FRAME_SIZE_16_PCM_SAMPLES  =  ADF_SADCR_FRSIZE_0,    /*!< Frame size of 16 PCM samples */
  HAL_ADF_SAD_FRAME_SIZE_32_PCM_SAMPLES  =  ADF_SADCR_FRSIZE_1,    /*!< Frame size of 32 PCM samples */
  HAL_ADF_SAD_FRAME_SIZE_64_PCM_SAMPLES  = (ADF_SADCR_FRSIZE_0 \
                                            | ADF_SADCR_FRSIZE_1), /*!< Frame size of 64 PCM samples */
  HAL_ADF_SAD_FRAME_SIZE_128_PCM_SAMPLES =  ADF_SADCR_FRSIZE_2,    /*!< Frame size of 128 PCM samples */
  HAL_ADF_SAD_FRAME_SIZE_256_PCM_SAMPLES = (ADF_SADCR_FRSIZE_0 \
                                            | ADF_SADCR_FRSIZE_2), /*!< Frame size of 256 PCM samples */
  HAL_ADF_SAD_FRAME_SIZE_512_PCM_SAMPLES =  ADF_SADCR_FRSIZE       /*!< Frame size of 512 PCM samples */
} hal_adf_sad_frame_size_t;

/**
  * @brief HAL ADF sound activity detector learning frames definitions.
  */
typedef enum
{
  HAL_ADF_SAD_LEARNING_FRAMES_2  =  0U,                     /*!< 2 learning frames */
  HAL_ADF_SAD_LEARNING_FRAMES_4  =  ADF_SADCFGR_LFRNB_0,    /*!< 4 learning frames */
  HAL_ADF_SAD_LEARNING_FRAMES_8  =  ADF_SADCFGR_LFRNB_1,    /*!< 8 learning frames */
  HAL_ADF_SAD_LEARNING_FRAMES_16 = (ADF_SADCFGR_LFRNB_0 \
                                    | ADF_SADCFGR_LFRNB_1), /*!< 16 learning frames */
  HAL_ADF_SAD_LEARNING_FRAMES_32 =  ADF_SADCFGR_LFRNB       /*!< 32 learning frames */
} hal_adf_sad_learning_frames_t;

/**
  * @brief HAL ADF sound activity detector signal to noise thresholds definitions.
  */
typedef enum
{
  HAL_ADF_SAD_SIGNAL_TO_NOISE_3_5_DB  =  0U,                     /*!< Signal to noise threshold of 3.5dB */
  HAL_ADF_SAD_SIGNAL_TO_NOISE_6_DB    =  ADF_SADCFGR_SNTHR_0,    /*!< Signal to noise threshold of 6dB */
  HAL_ADF_SAD_SIGNAL_TO_NOISE_9_5_DB  =  ADF_SADCFGR_SNTHR_1,    /*!< Signal to noise threshold of 9.5dB */
  HAL_ADF_SAD_SIGNAL_TO_NOISE_12_DB   = (ADF_SADCFGR_SNTHR_0 \
                                         | ADF_SADCFGR_SNTHR_1), /*!< Signal to noise threshold of 12dB */
  HAL_ADF_SAD_SIGNAL_TO_NOISE_15_6_DB =  ADF_SADCFGR_SNTHR_2,    /*!< Signal to noise threshold of 15.6dB */
  HAL_ADF_SAD_SIGNAL_TO_NOISE_18_DB   = (ADF_SADCFGR_SNTHR_0 \
                                         | ADF_SADCFGR_SNTHR_2), /*!< Signal to noise threshold of 18dB */
  HAL_ADF_SAD_SIGNAL_TO_NOISE_21_6_DB = (ADF_SADCFGR_SNTHR_1 \
                                         | ADF_SADCFGR_SNTHR_2), /*!< Signal to noise threshold of 21.6dB */
  HAL_ADF_SAD_SIGNAL_TO_NOISE_24_1_DB = (ADF_SADCFGR_SNTHR_0 \
                                         | ADF_SADCFGR_SNTHR_1 \
                                         | ADF_SADCFGR_SNTHR_2), /*!< Signal to noise threshold of 24.1dB */
  HAL_ADF_SAD_SIGNAL_TO_NOISE_27_6_DB =  ADF_SADCFGR_SNTHR_3,    /*!< Signal to noise threshold of 27.6dB */
  HAL_ADF_SAD_SIGNAL_TO_NOISE_30_1_DB = (ADF_SADCFGR_SNTHR_0 \
                                         | ADF_SADCFGR_SNTHR_3)  /*!< Signal to noise threshold of 30.1dB */
} hal_adf_sad_signal_to_noise_threshold_t;

/**
  * @brief HAL ADF sound activity detector hangover time windows definitions.
  */
typedef enum
{
  HAL_ADF_SAD_HANGOVER_TIME_4_FRAMES   =  0U,                     /*!< Hangover time window of 4 frames */
  HAL_ADF_SAD_HANGOVER_TIME_8_FRAMES   =  ADF_SADCFGR_HGOVR_0,    /*!< Hangover time window of 8 frames */
  HAL_ADF_SAD_HANGOVER_TIME_16_FRAMES  =  ADF_SADCFGR_HGOVR_1,    /*!< Hangover time window of 16 frames */
  HAL_ADF_SAD_HANGOVER_TIME_32_FRAMES  = (ADF_SADCFGR_HGOVR_0 \
                                          | ADF_SADCFGR_HGOVR_1), /*!< Hangover time window of 32 frames */
  HAL_ADF_SAD_HANGOVER_TIME_64_FRAMES  =  ADF_SADCFGR_HGOVR_2,    /*!< Hangover time window of 64 frames */
  HAL_ADF_SAD_HANGOVER_TIME_128_FRAMES = (ADF_SADCFGR_HGOVR_0 \
                                          | ADF_SADCFGR_HGOVR_2), /*!< Hangover time window of 128 frames */
  HAL_ADF_SAD_HANGOVER_TIME_256_FRAMES = (ADF_SADCFGR_HGOVR_1 \
                                          | ADF_SADCFGR_HGOVR_2), /*!< Hangover time window of 256 frames */
  HAL_ADF_SAD_HANGOVER_TIME_512_FRAMES =  ADF_SADCFGR_HGOVR       /*!< Hangover time window of 512 frames */
} hal_adf_sad_hangover_time_window_t;

/**
  * @brief HAL ADF sound activity detector hysteresis status definitions.
  */
typedef enum
{
  HAL_ADF_SAD_HYSTERESIS_DISABLED = 0U, /*!< Hysteresis disabled */
  HAL_ADF_SAD_HYSTERESIS_ENABLED  = 1U  /*!< Hysteresis enabled */
} hal_adf_sad_hysteresis_status_t;

/**
  * @brief HAL ADF sound activity detector status definitions.
  */
typedef enum
{
  HAL_ADF_SOUND_ACTIVITY_NOT_DETECTED = 0U, /*!< Sound activity not detected */
  HAL_ADF_SOUND_ACTIVITY_DETECTED     = 1U  /*!< Sound activity detected */
} hal_adf_sad_status_t;

/**
  * @}
  */

/** @defgroup ADF_Exported_Types_Group2 ADF handle structure
  * @{
  */

typedef struct hal_adf_handle_s hal_adf_handle_t; /*!< ADF handle type definition */

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
typedef void (*hal_adf_cb_t)(hal_adf_handle_t *, hal_adf_block_index_t); /*!< Pointer to generic callback */
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */

/**
  * @brief HAL ADF handle structure definition.
  */
struct hal_adf_handle_s
{
  /*! Peripheral instance */
  hal_adf_t                                 instance;
  /*! Global state */
  volatile hal_adf_state_t                  global_state;
  /*! Serial interfaces states */
  volatile hal_adf_serial_interface_state_t serial_interface_states[ADF1_BLOCKS_NUMBER];
  /*! Digital filters states */
  volatile hal_adf_digital_filter_state_t   digital_filter_states[ADF1_BLOCKS_NUMBER];
  /*! Sound activity detectors states */
  volatile hal_adf_sad_state_t              sound_activity_detector_states[ADF1_BLOCKS_NUMBER];
#if defined (USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
  /*! Errors limited to the last process. This parameter can be a combination of @ref ADF_Error_Codes */
  volatile uint32_t                         last_error_codes[ADF1_BLOCKS_NUMBER];
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */
#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
  /*! DMA handles */
  hal_dma_handle_t                         *hdma[ADF1_BLOCKS_NUMBER];
#endif /* USE_HAL_ADF_DMA */
#if defined (USE_HAL_ADF_USER_DATA) && (USE_HAL_ADF_USER_DATA == 1)
  /*! User data pointer */
  const void                               *p_user_data;
#endif /* USE_HAL_ADF_USER_DATA */
#if defined (USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
  /*! Acquisition complete callback */
  hal_adf_cb_t                              p_acquisition_cplt_cb;
  /*! Acquisition half complete callback */
  hal_adf_cb_t                              p_acquisition_half_cplt_cb;
  /*! Acquisition stop callback */
  hal_adf_cb_t                              p_acquisition_stop_cb;
  /*! Sound level callback */
  hal_adf_cb_t                              p_sound_level_cb;
  /*! Sound activity callback */
  hal_adf_cb_t                              p_sound_activity_cb;
  /*! Error callback */
  hal_adf_cb_t                              p_error_cb;
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
};

/**
  * @}
  */

/** @defgroup ADF_Exported_Types_Group3 ADF configuration structures
  * @{
  */

/**
  * @brief HAL ADF serial interface configuration structure definition.
  */
typedef struct
{
  hal_adf_serial_interface_mode_t         mode;         /*!< Serial interface mode */
  hal_adf_serial_interface_clock_source_t clock_source; /*!< Serial interface clock source */
  uint32_t                                threshold;    /*!< Threshold for clock absence detection or manchester symbol
                                                             threshold. This parameter must be a number between
                                                             Min_Data = 4 and Max_Data = 31 */
} hal_adf_serial_interface_config_t;

/**
  * @brief HAL ADF digital filter trigger configuration structure definition.
  */
typedef struct
{
  hal_adf_dflt_trigger_source_t source; /*!< Trigger source */
  hal_adf_dflt_trigger_edge_t   edge;   /*!< Trigger edge */
} hal_adf_dflt_trigger_config_t;

/**
  * @brief HAL ADF digital filter configuration structure definition.
  */
typedef struct
{
  hal_adf_dflt_data_source_t      data_source;      /*!< Data source */
  hal_adf_dflt_cic_mode_t         cic_mode;         /*!< CIC mode */
  uint32_t                        decimation_ratio; /*!< Decimation ratio. This parameter must be a number between
                                                         Min_Data = 2 and Max_Data = 512 */
  int32_t                         gain;             /*!< Gain in step of around 3db (from -48db to 72dB).
                                                         This parameter must be a number between Min_Data = -16
                                                         and Max_Data = 24 */
  hal_adf_dflt_acquisition_mode_t acquisition_mode; /*!< Acquisition mode */
  hal_adf_dflt_trigger_config_t   trigger;          /*!< Trigger configuration */
} hal_adf_digital_filter_config_t;

#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
/**
  * @brief HAL ADF DMA configuration structure definition.
  */
typedef struct
{
  uint32_t                      address;          /*!< Destination address */
  uint32_t                      data_length_byte; /*!< Data length in bytes */
  hal_adf_dma_data_resolution_t data_resolution;  /*!< Data resolution */
} hal_adf_dma_config_t;
#endif /* USE_HAL_ADF_DMA */

/**
  * @brief HAL ADF sound activity detector configuration structure definition.
  */
typedef struct
{
  hal_adf_sad_mode_t            mode;                  /*!< mode */
  hal_adf_sad_memory_transfer_t memory_transfer;       /*!< Memory transfer */
  hal_adf_sad_trigger_event_t   trigger_event;         /*!< Trigger event */
  uint32_t                      minimum_ambient_noise; /*!< Minimum ambient noise level.
                                                            This parameter must be a number between Min_Data = 0
                                                            and Max_Data = 8191 */
} hal_adf_sad_config_t;

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup ADF_Exported_Functions HAL ADF functions
  * @{
  */

/** @defgroup ADF_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_ADF_Init(hal_adf_handle_t *hadf, hal_adf_t instance);
void         HAL_ADF_DeInit(hal_adf_handle_t *hadf);
hal_adf_t    HAL_ADF_GetInstance(const hal_adf_handle_t *hadf);
/**
  * @}
  */

/** @defgroup ADF_Exported_Functions_Group2 Common clock generator and features functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_ADF_SetConfig(hal_adf_handle_t *hadf, uint32_t proc_clock_divider);
void         HAL_ADF_GetConfig(const hal_adf_handle_t *hadf, uint32_t *p_proc_clock_divider);

hal_status_t HAL_ADF_SetConfigOutputClock(const hal_adf_handle_t *hadf, hal_adf_output_clock_pins_t pins,
                                          uint32_t output_clock_divider);
void         HAL_ADF_GetConfigOutputClock(const hal_adf_handle_t *hadf, hal_adf_output_clock_pins_t *p_pins,
                                          uint32_t *p_output_clock_divider);

hal_status_t HAL_ADF_SetConfigOutputClockTrigger(const hal_adf_handle_t *hadf,
                                                 hal_adf_output_clock_trigger_source_t source,
                                                 hal_adf_output_clock_trigger_edge_t edge);
void         HAL_ADF_GetConfigOutputClockTrigger(const hal_adf_handle_t *hadf,
                                                 hal_adf_output_clock_trigger_source_t *p_source,
                                                 hal_adf_output_clock_trigger_edge_t *p_edge);

#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
hal_status_t HAL_ADF_SetDMA(hal_adf_handle_t     *hadf,
                            hal_adf_block_index_t block_index,
                            hal_dma_handle_t     *hdma);
#endif /* USE_HAL_ADF_DMA */

uint32_t     HAL_ADF_GetClockFreq(const hal_adf_handle_t *hadf);

#if defined (USE_HAL_ADF_USER_DATA) && (USE_HAL_ADF_USER_DATA == 1)
void        HAL_ADF_SetUserData(hal_adf_handle_t *hadf, const void *p_user_data);
const void *HAL_ADF_GetUserData(const hal_adf_handle_t *hadf);
#endif /* USE_HAL_SAI_USER_DATA */

#if defined(USE_HAL_ADF_GET_LAST_ERRORS) && (USE_HAL_ADF_GET_LAST_ERRORS == 1)
uint32_t     HAL_ADF_GetLastErrorCodes(const hal_adf_handle_t *hadf,
                                       hal_adf_block_index_t   block_index);
#endif /* USE_HAL_ADF_GET_LAST_ERRORS */

/* Control functions */
hal_status_t                          HAL_ADF_EnableOutputClock(const hal_adf_handle_t *hadf,
                                                                hal_adf_output_clock_pins_t pins);
hal_status_t                          HAL_ADF_DisableOutputClock(const hal_adf_handle_t *hadf,
                                                                 hal_adf_output_clock_pins_t pins);
hal_adf_output_clock_status_t         HAL_ADF_IsEnabledOutputClock(const hal_adf_handle_t *hadf);

hal_status_t                          HAL_ADF_EnableOutputClockTrigger(const hal_adf_handle_t *hadf);
hal_status_t                          HAL_ADF_DisableOutputClockTrigger(const hal_adf_handle_t *hadf);
hal_adf_output_clock_trigger_status_t HAL_ADF_IsEnabledOutputClockTrigger(const hal_adf_handle_t *hadf);

hal_status_t                          HAL_ADF_EnableTriggerOutput(const hal_adf_handle_t *hadf);
hal_adf_trigger_output_status_t       HAL_ADF_IsEnabledTriggerOutput(const hal_adf_handle_t *hadf);

/* Process functions */
hal_status_t HAL_ADF_Start(hal_adf_handle_t *hadf);
hal_status_t HAL_ADF_Stop(hal_adf_handle_t *hadf);
/**
  * @}
  */

/** @defgroup ADF_Exported_Functions_Group3 Serial interface functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_ADF_SITF_SetConfig(hal_adf_handle_t *hadf,
                                    hal_adf_block_index_t serial_interface_index,
                                    const hal_adf_serial_interface_config_t *p_config);
void         HAL_ADF_SITF_GetConfig(const hal_adf_handle_t *hadf,
                                    hal_adf_block_index_t serial_interface_index,
                                    hal_adf_serial_interface_config_t *p_config);

/* Process functions */
hal_status_t HAL_ADF_SITF_Start(hal_adf_handle_t *hadf, hal_adf_block_index_t serial_interface_index);
hal_status_t HAL_ADF_SITF_Stop(hal_adf_handle_t *hadf, hal_adf_block_index_t serial_interface_index);

/* Clock absence detection functions */
hal_adf_sitf_ckab_status_t HAL_ADF_SITF_IsClockAbsenceDetected(const hal_adf_handle_t *hadf,
                                                               hal_adf_block_index_t serial_interface_index);

hal_status_t HAL_ADF_SITF_StartClockAbsenceDetect_IT(const hal_adf_handle_t *hadf,
                                                     hal_adf_block_index_t serial_interface_index);
hal_status_t HAL_ADF_SITF_StopClockAbsenceDetect_IT(const hal_adf_handle_t *hadf,
                                                    hal_adf_block_index_t serial_interface_index);
/**
  * @}
  */

/** @defgroup ADF_Exported_Functions_Group4 Bitstream matrix functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_ADF_BSMX_SetConfig(const hal_adf_handle_t *hadf,
                                    hal_adf_block_index_t bitstream_matrix_index,
                                    hal_adf_block_index_t serial_interface_index,
                                    hal_adf_bitstream_input_edge_t edge);
void         HAL_ADF_BSMX_GetConfig(const hal_adf_handle_t *hadf,
                                    hal_adf_block_index_t bitstream_matrix_index,
                                    hal_adf_block_index_t *p_serial_interface_index,
                                    hal_adf_bitstream_input_edge_t *p_edge);
/**
  * @}
  */

/** @defgroup ADF_Exported_Functions_Group5 Digital filter functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_ADF_DFLT_SetConfig(hal_adf_handle_t *hadf,
                                    hal_adf_block_index_t digital_filter_index,
                                    const hal_adf_digital_filter_config_t *p_config);
void         HAL_ADF_DFLT_GetConfig(const hal_adf_handle_t *hadf,
                                    hal_adf_block_index_t digital_filter_index,
                                    hal_adf_digital_filter_config_t *p_config);

hal_status_t HAL_ADF_DFLT_SetSamplesDelay(const hal_adf_handle_t *hadf,
                                          hal_adf_block_index_t digital_filter_index,
                                          uint32_t samples_delay);
uint32_t     HAL_ADF_DFLT_GetSamplesDelay(const hal_adf_handle_t *hadf,
                                          hal_adf_block_index_t digital_filter_index);

hal_status_t HAL_ADF_DFLT_SetGain(const hal_adf_handle_t *hadf,
                                  hal_adf_block_index_t digital_filter_index,
                                  int32_t gain);
int32_t      HAL_ADF_DFLT_GetGain(const hal_adf_handle_t *hadf,
                                  hal_adf_block_index_t digital_filter_index);

hal_status_t                  HAL_ADF_DFLT_SetFifoThreshold(const hal_adf_handle_t *hadf,
                                                            hal_adf_block_index_t digital_filter_index,
                                                            hal_adf_dflt_fifo_threshold_t fifo_threshold);
hal_adf_dflt_fifo_threshold_t HAL_ADF_DFLT_GetFifoThreshold(const hal_adf_handle_t *hadf,
                                                            hal_adf_block_index_t digital_filter_index);

hal_status_t HAL_ADF_DFLT_SetDiscardSamples(const hal_adf_handle_t *hadf,
                                            hal_adf_block_index_t digital_filter_index,
                                            uint32_t discard_samples);
uint32_t     HAL_ADF_DFLT_GetDiscardSamples(const hal_adf_handle_t *hadf,
                                            hal_adf_block_index_t digital_filter_index);

/* Control functions */
hal_status_t HAL_ADF_DFLT_EnableReshapeFilter(const hal_adf_handle_t *hadf,
                                              hal_adf_block_index_t digital_filter_index,
                                              hal_adf_dflt_rsf_decimation_ratio_t decimation_ratio);
hal_status_t HAL_ADF_DFLT_DisableReshapeFilter(const hal_adf_handle_t *hadf,
                                               hal_adf_block_index_t digital_filter_index);
hal_adf_dflt_rsf_status_t HAL_ADF_DFLT_IsEnabledReshapeFilter(const hal_adf_handle_t *hadf,
                                                              hal_adf_block_index_t digital_filter_index);
hal_adf_dflt_rsf_decimation_ratio_t HAL_ADF_DFLT_GetReshapeFilterDecimationRatio(const hal_adf_handle_t *hadf,
    hal_adf_block_index_t digital_filter_index);

hal_status_t HAL_ADF_DFLT_EnableHighPassFilter(const hal_adf_handle_t *hadf,
                                               hal_adf_block_index_t digital_filter_index,
                                               hal_adf_dflt_hpf_cut_off_frequency_t cut_off_frequency);
hal_status_t HAL_ADF_DFLT_DisableHighPassFilter(const hal_adf_handle_t *hadf,
                                                hal_adf_block_index_t digital_filter_index);
hal_adf_dflt_hpf_status_t HAL_ADF_DFLT_IsEnabledHighPassFilter(const hal_adf_handle_t *hadf,
                                                               hal_adf_block_index_t digital_filter_index);
hal_adf_dflt_hpf_cut_off_frequency_t HAL_ADF_DFLT_GetHighPassFilterCutOffFrequency(const hal_adf_handle_t *hadf,
    hal_adf_block_index_t digital_filter_index);

/* Process functions */
hal_status_t HAL_ADF_DFLT_StartAcq(hal_adf_handle_t *hadf,
                                   hal_adf_block_index_t digital_filter_index);
hal_status_t HAL_ADF_DFLT_StopAcq(hal_adf_handle_t *hadf,
                                  hal_adf_block_index_t digital_filter_index);
hal_status_t HAL_ADF_DFLT_PollForAcq(hal_adf_handle_t *hadf,
                                     hal_adf_block_index_t digital_filter_index,
                                     uint32_t timeout_ms);
int32_t      HAL_ADF_DFLT_GetAcqValue(const hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t digital_filter_index);

hal_status_t HAL_ADF_DFLT_StartAcq_IT(hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t digital_filter_index);
hal_status_t HAL_ADF_DFLT_StopAcq_IT(hal_adf_handle_t *hadf,
                                     hal_adf_block_index_t digital_filter_index);
hal_status_t HAL_ADF_DFLT_StartAcq_IT_Opt(hal_adf_handle_t *hadf,
                                          hal_adf_block_index_t digital_filter_index,
                                          uint32_t interruptions);

#if defined (USE_HAL_ADF_DMA) && (USE_HAL_ADF_DMA == 1)
hal_status_t HAL_ADF_DFLT_StartAcq_DMA(hal_adf_handle_t *hadf,
                                       hal_adf_block_index_t digital_filter_index,
                                       const hal_adf_dma_config_t *p_dma_config);
hal_status_t HAL_ADF_DFLT_StopAcq_DMA(hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t digital_filter_index);
hal_status_t HAL_ADF_DFLT_StartAcq_DMA_Opt(hal_adf_handle_t *hadf,
                                           hal_adf_block_index_t digital_filter_index,
                                           const hal_adf_dma_config_t *p_dma_config,
                                           uint32_t interruptions);
#endif /* USE_HAL_ADF_DMA */
/**
  * @}
  */

/** @defgroup ADF_Exported_Functions_Group6 Sound activity detector functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_ADF_SAD_SetConfig(hal_adf_handle_t *hadf,
                                   hal_adf_block_index_t sound_activity_detector_index,
                                   const hal_adf_sad_config_t *p_config);
void         HAL_ADF_SAD_GetConfig(const hal_adf_handle_t *hadf,
                                   hal_adf_block_index_t sound_activity_detector_index,
                                   hal_adf_sad_config_t *p_config);

hal_status_t             HAL_ADF_SAD_SetFrameSize(const hal_adf_handle_t *hadf,
                                                  hal_adf_block_index_t sound_activity_detector_index,
                                                  hal_adf_sad_frame_size_t frame_size);
hal_adf_sad_frame_size_t HAL_ADF_SAD_GetFrameSize(const hal_adf_handle_t *hadf,
                                                  hal_adf_block_index_t sound_activity_detector_index);

hal_status_t                  HAL_ADF_SAD_SetLearningFrames(const hal_adf_handle_t *hadf,
                                                            hal_adf_block_index_t sound_activity_detector_index,
                                                            hal_adf_sad_learning_frames_t learning_frames);
hal_adf_sad_learning_frames_t HAL_ADF_SAD_GetLearningFrames(const hal_adf_handle_t *hadf,
                                                            hal_adf_block_index_t sound_activity_detector_index);

hal_status_t HAL_ADF_SAD_SetSignalToNoiseThreshold(const hal_adf_handle_t *hadf,
                                                   hal_adf_block_index_t sound_activity_detector_index,
                                                   hal_adf_sad_signal_to_noise_threshold_t threshold);
hal_adf_sad_signal_to_noise_threshold_t
HAL_ADF_SAD_GetSignalToNoiseThreshold(const hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t sound_activity_detector_index);

hal_status_t HAL_ADF_SAD_SetAmbientNoiseSlope(const hal_adf_handle_t *hadf,
                                              hal_adf_block_index_t sound_activity_detector_index,
                                              uint32_t ambient_noise_slope);
uint32_t     HAL_ADF_SAD_GetAmbientNoiseSlope(const hal_adf_handle_t *hadf,
                                              hal_adf_block_index_t sound_activity_detector_index);

hal_status_t HAL_ADF_SAD_SetHangoverTimeWindow(const hal_adf_handle_t *hadf,
                                               hal_adf_block_index_t sound_activity_detector_index,
                                               hal_adf_sad_hangover_time_window_t hangover_time_window);
hal_adf_sad_hangover_time_window_t
HAL_ADF_SAD_GetHangoverTimeWindow(const hal_adf_handle_t *hadf,
                                  hal_adf_block_index_t sound_activity_detector_index);

/* Control functions */
hal_status_t                    HAL_ADF_SAD_EnableHysteresis(const hal_adf_handle_t *hadf,
                                                             hal_adf_block_index_t sound_activity_detector_index);
hal_status_t                    HAL_ADF_SAD_DisableHysteresis(const hal_adf_handle_t *hadf,
                                                              hal_adf_block_index_t sound_activity_detector_index);
hal_adf_sad_hysteresis_status_t HAL_ADF_SAD_IsEnabledHysteresis(const hal_adf_handle_t *hadf,
                                                                hal_adf_block_index_t sound_activity_detector_index);

/* Process functions */
hal_status_t         HAL_ADF_SAD_Start(hal_adf_handle_t *hadf,
                                       hal_adf_block_index_t sound_activity_detector_index);
hal_status_t         HAL_ADF_SAD_Stop(hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t sound_activity_detector_index);
hal_adf_sad_status_t HAL_ADF_SAD_IsDetected(const hal_adf_handle_t *hadf,
                                            hal_adf_block_index_t sound_activity_detector_index);
hal_status_t         HAL_ADF_SAD_PollForSoundLevel(const hal_adf_handle_t *hadf,
                                                   hal_adf_block_index_t sound_activity_detector_index,
                                                   uint32_t timeout_ms);
void                 HAL_ADF_SAD_GetSoundAndAmbientNoiseLevels(const hal_adf_handle_t *hadf,
                                                               hal_adf_block_index_t sound_activity_detector_index,
                                                               uint32_t *p_sound_level,
                                                               uint32_t *p_ambient_noise_level);

hal_status_t HAL_ADF_SAD_Start_IT(hal_adf_handle_t *hadf,
                                  hal_adf_block_index_t sound_activity_detector_index);
hal_status_t HAL_ADF_SAD_Stop_IT(hal_adf_handle_t *hadf,
                                 hal_adf_block_index_t sound_activity_detector_index);
hal_status_t HAL_ADF_SAD_Start_IT_Opt(hal_adf_handle_t *hadf,
                                      hal_adf_block_index_t sound_activity_detector_index,
                                      uint32_t interruptions);
/**
  * @}
  */

/** @defgroup ADF_Exported_Functions_Group7 IRQ handler and callback functions
  * @{
  */
void HAL_ADF_IRQHandler(hal_adf_handle_t *hadf, hal_adf_block_index_t block_index);
void HAL_ADF_DFLT_AcqCpltCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t digital_filter_index);
void HAL_ADF_DFLT_AcqHalfCpltCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t digital_filter_index);
void HAL_ADF_DFLT_AcqStopCpltCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t digital_filter_index);
void HAL_ADF_SAD_SoundLevelCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t sound_activity_detector_index);
void HAL_ADF_SAD_SoundActivityCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t sound_activity_detector_index);
void HAL_ADF_ErrorCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t block_index);

#if defined(USE_HAL_ADF_REGISTER_CALLBACKS) && (USE_HAL_ADF_REGISTER_CALLBACKS == 1)
hal_status_t HAL_ADF_DFLT_RegisterAcqCpltCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback);
hal_status_t HAL_ADF_DFLT_RegisterAcqHalfCpltCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback);
hal_status_t HAL_ADF_DFLT_RegisterAcqStopCpltCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback);
hal_status_t HAL_ADF_SAD_RegisterSoundLevelCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback);
hal_status_t HAL_ADF_SAD_RegisterSoundActivityCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback);
hal_status_t HAL_ADF_RegisterErrorCallback(hal_adf_handle_t *hadf, hal_adf_cb_t p_callback);
#endif /* USE_HAL_ADF_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup ADF_Exported_Functions_Group8 State functions
  * @{
  */
hal_adf_state_t HAL_ADF_GetState(const hal_adf_handle_t *hadf);

hal_adf_serial_interface_state_t HAL_ADF_SITF_GetState(const hal_adf_handle_t *hadf,
                                                       hal_adf_block_index_t serial_interface_index);

hal_adf_digital_filter_state_t HAL_ADF_DFLT_GetState(const hal_adf_handle_t *hadf,
                                                     hal_adf_block_index_t digital_filter_index);

hal_adf_sad_state_t HAL_ADF_SAD_GetState(const hal_adf_handle_t *hadf,
                                         hal_adf_block_index_t sound_activity_detector_index);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* ADF1 */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_HAL_ADF_H */
