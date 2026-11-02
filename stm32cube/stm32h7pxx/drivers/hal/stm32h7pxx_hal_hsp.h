/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_hsp.h
  * @brief   Header file of HSP HAL module.
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
#ifndef STM32H7Pxx_HAL_HSP_H
#define STM32H7Pxx_HAL_HSP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

#if defined(HSP1)

/** @defgroup HSP HSP
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup HSP_Exported_Constants HSP Exported Constants
  * @{
  */

/** @defgroup HSP_Hardware_definition  HSP Hardware definition
  * @{
  */
#define HAL_HSP_INSTANCE_NBR  HSP_INSTANCE_NBR /*!< Constant defined in CMSIS Device file */

/**
  * @}
  */

/** @defgroup HSP_HAL_Error_Codes  HSP HAL Error Codes
  * @{
  */
#define HAL_HSP_ERROR_NONE                       (0UL)        /*!< No error                                           */
#define HAL_HSP_ERROR_TRGIN_OVR                  (1UL << 10U) /*!< Trigger Input Overrun                              */
#define HAL_HSP_ERROR_BUFFER_UDR_OR_OVR          (1UL << 11U) /*!< STREAM Buffer Overrun or Underrun                  */
#define HAL_HSP_ERROR_CAPTURE_OVR                (1UL << 12U) /*!< TIMESTAMP Capture Overrun                          */
#define HAL_HSP_ERROR_BREAK_IN                   (1UL << 13U) /*!< Break Input Arrival                                */
#define HAL_HSP_ERROR_HDEG_OVR                   (1UL << 14U) /*!< HSP Dedicated Event Generator Overrun              */
#define HAL_HSP_ERROR_SPE_ACCESS                 (1UL << 16U) /*!< Signal Processor Engine Access Error               */
#define HAL_HSP_ERROR_FPU                        (1UL << 17U) /*!< Floating Point Unit Error                          */
#define HAL_HSP_ERROR_FIRMWARE                   (1UL << 18U) /*!< Firmware Error                                     */
#define HAL_HSP_FAULT_ERROR_CRAM_WRITE_PROTECTED (1UL << 26U) /*!< CRAM Write Protected                               */
#define HAL_HSP_FAULT_ERROR_SPE_SCHEDULER        (1UL << 27U) /*!< Signal Processor Engine Scheduler Error            */
#define HAL_HSP_FAULT_ERROR_SPE_OPCODE_INVALID   (1UL << 28U) /*!< Firmware Invalid OpCode                            */
#define HAL_HSP_FAULT_ERROR_SPE_ACCESS           (1UL << 29U) /*!< Critical Signal Processor Engine Access Error      */
#define HAL_HSP_FAULT_ERROR_FW_INIT              (1UL << 30U) /*!< Firmware initialization error                      */
#define HAL_HSP_FAULT_ERROR_BOOT                 (1UL << 31U) /*!< Boot error: code returned in handle                */

/*! HAL HSP Error mask for all Fault Errors */
#define HAL_HSP_FAULT_ERROR_ALL  \
  (HAL_HSP_FAULT_ERROR_SPE_SCHEDULER | HAL_HSP_FAULT_ERROR_SPE_OPCODE_INVALID | HAL_HSP_FAULT_ERROR_SPE_ACCESS  \
   | HAL_HSP_FAULT_ERROR_FW_INIT     | HAL_HSP_FAULT_ERROR_BOOT | HAL_HSP_FAULT_ERROR_CRAM_WRITE_PROTECTED)

/*! HAL HSP Error mask for all Hardware Errors (including Fault Errors) */
#define HAL_HSP_ERROR_HW_ALL  \
  (HAL_HSP_ERROR_TRGIN_OVR   | HAL_HSP_ERROR_BUFFER_UDR_OR_OVR | HAL_HSP_ERROR_CAPTURE_OVR  \
   | HAL_HSP_ERROR_BREAK_IN  | HAL_HSP_ERROR_HDEG_OVR          | HAL_HSP_ERROR_FPU          \
   | HAL_HSP_ERROR_FIRMWARE  | HAL_HSP_FAULT_ERROR_ALL )

/**
  * @}
  */

/** @defgroup HSP_Firmware_Error_Codes  HSP Firmware Error Codes
  * @{
  */
#define HAL_HSP_FW_ERROR_UNDEFINED_PROCLIST    (9U) /*!< Error when trying to execute an undefined processing list */

/**
  * @}
  */

/** @defgroup HSP_Smart_Clocking_Values  HSP Smart Clocking Value
  * @{
  */
#define HAL_HSP_SMARTCLOCKING_CTRL  HSP_CR_CTRLCGDIS /*!< ID for HSP SmartClocking of Controller block             */
#define HAL_HSP_SMARTCLOCKING_SPE   HSP_CR_SPECGDIS  /*!< ID for HSP SmartClocking of Signal Processor Engine      */
#define HAL_HSP_SMARTCLOCKING_MMC   HSP_CR_MMCCGDIS  /*!< ID for HSP SmartClocking of Memory Management Controller */

/*! HAL HSP SmartClocking mask of all blocks */
#define HAL_HSP_SMARTCLOCKING_ALL  \
  (HAL_HSP_SMARTCLOCKING_CTRL | HAL_HSP_SMARTCLOCKING_SPE | HAL_HSP_SMARTCLOCKING_MMC)

/**
  * @}
  */

/** @defgroup HSP_TRGIN_ID  HSP Trigger Input Interface Identifiers
  * @{
  */
#define HAL_HSP_TRGIN_0  HSP_ITFENR_TRGI0EN  /*!< ID of HSP Trigger Input interface 0 */
#define HAL_HSP_TRGIN_1  HSP_ITFENR_TRGI1EN  /*!< ID of HSP Trigger Input interface 1 */
#define HAL_HSP_TRGIN_2  HSP_ITFENR_TRGI2EN  /*!< ID of HSP Trigger Input interface 2 */
#define HAL_HSP_TRGIN_3  HSP_ITFENR_TRGI3EN  /*!< ID of HSP Trigger Input interface 3 */
#define HAL_HSP_TRGIN_4  HSP_ITFENR_TRGI4EN  /*!< ID of HSP Trigger Input interface 4 */
#define HAL_HSP_TRGIN_5  HSP_ITFENR_TRGI5EN  /*!< ID of HSP Trigger Input interface 5 */
#define HAL_HSP_TRGIN_6  HSP_ITFENR_TRGI6EN  /*!< ID of HSP Trigger Input interface 6 */
#define HAL_HSP_TRGIN_7  HSP_ITFENR_TRGI7EN  /*!< ID of HSP Trigger Input interface 7 */
#define HAL_HSP_TRGIN_8  HSP_ITFENR_TRGI8EN  /*!< ID of HSP Trigger Input interface 8 */
#define HAL_HSP_TRGIN_9  HSP_ITFENR_TRGI9EN  /*!< ID of HSP Trigger Input interface 9 */

/*! HAL HSP Trigger Input mask of all interfaces */
#define HAL_HSP_TRGIN_ALL                                                                     \
  (HAL_HSP_TRGIN_0   | HAL_HSP_TRGIN_1 | HAL_HSP_TRGIN_2 | HAL_HSP_TRGIN_3 | HAL_HSP_TRGIN_4  \
   | HAL_HSP_TRGIN_5 | HAL_HSP_TRGIN_6 | HAL_HSP_TRGIN_7 | HAL_HSP_TRGIN_8 | HAL_HSP_TRGIN_9)

/**
  * @}
  */

/** @defgroup HSP_EVENT_Constants HSP Event Constants
  * @{
  */
/*! Bitfield position of "Priority" value in enumerate @ref hal_hsp_event_source_t */
#define HAL_HSP_EVENT_PRIO_POS  (26U)

/*! Bitfield position of "Register Source bitfield position" value in enumerate @ref hal_hsp_event_source_t */
#define HAL_HSP_EVENT_REG_SRC_BITFIELD_POSITION_POS  (21U)

/*! Bitfield position of "Register Event Source" value in enumerate @ref hal_hsp_event_source_t */
#define HAL_HSP_EVENT_SOURCE_POS  (0U)

/**
  * @brief Encode a HAL HSP event source value.
  * @param evt_prio Event priority.
  * @param reg_pos Register source bitfield position.
  * @param src_sel Event source selector value.
  * @retval Encoded @ref hal_hsp_event_source_t value.
  */
#define HAL_HSP_EVENT_SOURCE_ENCODE(evt_prio, reg_pos, src_sel)                           \
  (((uint32_t)(evt_prio) << HAL_HSP_EVENT_PRIO_POS)                                       \
   | ((uint32_t)(reg_pos) << HAL_HSP_EVENT_REG_SRC_BITFIELD_POSITION_POS)                 \
   | ((uint32_t)(src_sel) << HAL_HSP_EVENT_SOURCE_POS))

/*! HSP EVTxSRC selector value: first ADC source slot connected to the event */
#define HAL_HSP_EVENT_SRC_SEL_ADC_A  (0U)
/*! HSP EVTxSRC selector value: second ADC source slot connected to the event */
#define HAL_HSP_EVENT_SRC_SEL_ADC_B  (1U)
/*! HSP EVTxSRC selector value: STREAM source connected to the event */
#define HAL_HSP_EVENT_SRC_SEL_STREAM  (2U)
/*! HSP EVTxSRC selector value: first TRGIN slot connected to the event */
#define HAL_HSP_EVENT_SRC_SEL_TRGIN_0  (3U)
/*! HSP EVTxSRC selector value: second TRGIN slot connected to the event */
#define HAL_HSP_EVENT_SRC_SEL_TRGIN_1  (4U)
/*! HSP EVTxSRC selector value: HSP Shared Event Generator source */
#define HAL_HSP_EVENT_SRC_SEL_HSEG  (5U)
/*! HSP EVTxSRC selector value: CPU Shared Event Generator source */
#define HAL_HSP_EVENT_SRC_SEL_CSEG  (6U)

#define HAL_HSP_EVENT_1   HSP_EVTENR_EVTEN_0   /*!< ID of HSP EVENT 1 */
#define HAL_HSP_EVENT_2   HSP_EVTENR_EVTEN_1   /*!< ID of HSP EVENT 2 */
#define HAL_HSP_EVENT_3   HSP_EVTENR_EVTEN_2   /*!< ID of HSP EVENT 3 */
#define HAL_HSP_EVENT_4   HSP_EVTENR_EVTEN_3   /*!< ID of HSP EVENT 4 */
#define HAL_HSP_EVENT_5   HSP_EVTENR_EVTEN_4   /*!< ID of HSP EVENT 5 */
#define HAL_HSP_EVENT_6   HSP_EVTENR_EVTEN_5   /*!< ID of HSP EVENT 6 */
#define HAL_HSP_EVENT_7   HSP_EVTENR_EVTEN_6   /*!< ID of HSP EVENT 7 */
#define HAL_HSP_EVENT_8   HSP_EVTENR_EVTEN_7   /*!< ID of HSP EVENT 8 */
#define HAL_HSP_EVENT_9   HSP_EVTENR_EVTEN_8   /*!< ID of HSP EVENT 9 */
#define HAL_HSP_EVENT_10  HSP_EVTENR_EVTEN_9   /*!< ID of HSP EVENT 10 */
#define HAL_HSP_EVENT_11  HSP_EVTENR_EVTEN_10  /*!< ID of HSP EVENT 11 */
#define HAL_HSP_EVENT_12  HSP_EVTENR_EVTEN_11  /*!< ID of HSP EVENT 12 */
#define HAL_HSP_EVENT_13  HSP_EVTENR_EVTEN_12  /*!< ID of HSP EVENT 13 */
#define HAL_HSP_EVENT_14  HSP_EVTENR_EVTEN_13  /*!< ID of HSP EVENT 14 */
#define HAL_HSP_EVENT_15  HSP_EVTENR_EVTEN_14  /*!< ID of HSP EVENT 15 */
#define HAL_HSP_EVENT_16  HSP_EVTENR_EVTEN_15  /*!< ID of HSP EVENT 16 */
#define HAL_HSP_EVENT_17  HSP_EVTENR_EVTEN_16  /*!< ID of HSP EVENT 17 */
#define HAL_HSP_EVENT_18  HSP_EVTENR_EVTEN_17  /*!< ID of HSP EVENT 18 */
#define HAL_HSP_EVENT_19  HSP_EVTENR_EVTEN_18  /*!< ID of HSP EVENT 19 */
#define HAL_HSP_EVENT_20  HSP_EVTENR_EVTEN_19  /*!< ID of HSP EVENT 20 */
#define HAL_HSP_EVENT_21  HSP_EVTENR_EVTEN_20  /*!< ID of HSP EVENT 21 */
#define HAL_HSP_EVENT_22  HSP_EVTENR_EVTEN_21  /*!< ID of HSP EVENT 22 */

/*! HAL HSP Mask of all HSP Events */
#define HAL_HSP_EVENT_ALL                                                                         \
  (HAL_HSP_EVENT_1    | HAL_HSP_EVENT_2  | HAL_HSP_EVENT_3  | HAL_HSP_EVENT_4  | HAL_HSP_EVENT_5  \
   | HAL_HSP_EVENT_6  | HAL_HSP_EVENT_7  | HAL_HSP_EVENT_8  | HAL_HSP_EVENT_9  | HAL_HSP_EVENT_10 \
   | HAL_HSP_EVENT_11 | HAL_HSP_EVENT_12 | HAL_HSP_EVENT_13 | HAL_HSP_EVENT_14 | HAL_HSP_EVENT_15 \
   | HAL_HSP_EVENT_16 | HAL_HSP_EVENT_17 | HAL_HSP_EVENT_18 | HAL_HSP_EVENT_19 | HAL_HSP_EVENT_20 \
   | HAL_HSP_EVENT_21 | HAL_HSP_EVENT_22)

/**
  * @}
  */

/** @defgroup HSP_STREAM_BUFFER_Flags HSP STREAM Buffer Flags
  * @{
  */
#define HAL_HSP_FLAG_EVT_STREAM_BUFFER_0     HSP_EVT_ISR_B0EVTF  /*!< STREAM Buffer 0 TX Full / RX Empty flag */
#define HAL_HSP_FLAG_EVT_STREAM_BUFFER_1     HSP_EVT_ISR_B1EVTF  /*!< STREAM Buffer 1 TX Full / RX Empty flag */
#define HAL_HSP_FLAG_EVT_STREAM_BUFFER_2     HSP_EVT_ISR_B2EVTF  /*!< STREAM Buffer 2 TX Full / RX Empty flag */
#define HAL_HSP_FLAG_EVT_STREAM_BUFFER_3     HSP_EVT_ISR_B3EVTF  /*!< STREAM Buffer 3 TX Full / RX Empty flag */
#define HAL_HSP_FLAG_EVT_STREAM_BUFFER_ALL                               \
  (HAL_HSP_FLAG_EVT_STREAM_BUFFER_0  | HAL_HSP_FLAG_EVT_STREAM_BUFFER_1  \
   | HAL_HSP_FLAG_EVT_STREAM_BUFFER_2 | HAL_HSP_FLAG_EVT_STREAM_BUFFER_3)  /*!< All STREAM Buffer Ready flags  */

#define HAL_HSP_FLAG_ERR_STREAM_BUFFER_0     HSP_ERR_ISR_B0ERRF  /*!< STREAM Buffer 0 TX UDR / RX OVR flag */
#define HAL_HSP_FLAG_ERR_STREAM_BUFFER_1     HSP_ERR_ISR_B1ERRF  /*!< STREAM Buffer 1 TX UDR / RX OVR flag */
#define HAL_HSP_FLAG_ERR_STREAM_BUFFER_2     HSP_ERR_ISR_B2ERRF  /*!< STREAM Buffer 2 TX UDR / RX OVR flag */
#define HAL_HSP_FLAG_ERR_STREAM_BUFFER_3     HSP_ERR_ISR_B3ERRF  /*!< STREAM Buffer 3 TX UDR / RX OVR flag */
#define HAL_HSP_FLAG_ERR_STREAM_BUFFER_ALL                               \
  (HAL_HSP_FLAG_ERR_STREAM_BUFFER_0  | HAL_HSP_FLAG_ERR_STREAM_BUFFER_1  \
   | HAL_HSP_FLAG_ERR_STREAM_BUFFER_2 | HAL_HSP_FLAG_ERR_STREAM_BUFFER_3)  /*!< All STREAM TX UDR / RX OVR flags */

/**
  * @}
  */

/** @defgroup HSP_TCU_Flags HSP Task Comparator Unit Flags
  * @{
  */
#define HAL_HSP_FLAG_TCU_CMP_0_TASK_STARTED  HSP_EVT_ISR_SOTECP0F  /*!< Task Comparator Unit 0 Start of Task flag */
#define HAL_HSP_FLAG_TCU_CMP_1_TASK_STARTED  HSP_EVT_ISR_SOTECP1F  /*!< Task Comparator Unit 1 Start of Task flag */
#define HAL_HSP_FLAG_TCU_CMP_2_TASK_STARTED  HSP_EVT_ISR_SOTECP2F  /*!< Task Comparator Unit 2 Start of Task flag */
#define HAL_HSP_FLAG_TCU_CMP_3_TASK_STARTED  HSP_EVT_ISR_SOTECP3F  /*!< Task Comparator Unit 3 Start of Task flag */
#define HAL_HSP_FLAG_TCU_CMP_0_TASK_ENDED    HSP_EVT_ISR_EOTECP0F  /*!< Task Comparator Unit 0 End of Task flag   */
#define HAL_HSP_FLAG_TCU_CMP_1_TASK_ENDED    HSP_EVT_ISR_EOTECP1F  /*!< Task Comparator Unit 1 End of Task flag   */
#define HAL_HSP_FLAG_TCU_CMP_2_TASK_ENDED    HSP_EVT_ISR_EOTECP2F  /*!< Task Comparator Unit 2 End of Task flag   */
#define HAL_HSP_FLAG_TCU_CMP_3_TASK_ENDED    HSP_EVT_ISR_EOTECP3F  /*!< Task Comparator Unit 3 End of Task flag   */
#define HAL_HSP_FLAG_TCU_TASK_OVL        HSP_EVT_ISR_TOVLPF    /*!< Task Comparator Unit Task Overlap flag    */

/*! HAL HSP Mask of all HSP Task Comparator 0 flags */
#define HAL_HSP_FLAG_TCU_CMP_0_ALL  \
  (HAL_HSP_FLAG_TCU_CMP_0_TASK_STARTED | HAL_HSP_FLAG_TCU_CMP_0_TASK_ENDED)

/*! HAL HSP Mask of all HSP Task Comparator 1 flags */
#define HAL_HSP_FLAG_TCU_CMP_1_ALL  \
  (HAL_HSP_FLAG_TCU_CMP_1_TASK_STARTED | HAL_HSP_FLAG_TCU_CMP_1_TASK_ENDED)

/*! HAL HSP Mask of all HSP Task Comparator 2 flags */
#define HAL_HSP_FLAG_TCU_CMP_2_ALL  \
  (HAL_HSP_FLAG_TCU_CMP_2_TASK_STARTED | HAL_HSP_FLAG_TCU_CMP_2_TASK_ENDED)

/*! HAL HSP Mask of all HSP Task Comparator 3 flags */
#define HAL_HSP_FLAG_TCU_CMP_3_ALL  \
  (HAL_HSP_FLAG_TCU_CMP_3_TASK_STARTED | HAL_HSP_FLAG_TCU_CMP_3_TASK_ENDED)

/*! HAL HSP Mask of all HSP Task Comparator Unit flags */
#define HAL_HSP_FLAG_TCU_ALL                          \
  (HAL_HSP_FLAG_TCU_CMP_0_ALL   | HAL_HSP_FLAG_TCU_CMP_1_ALL  \
   | HAL_HSP_FLAG_TCU_CMP_2_ALL | HAL_HSP_FLAG_TCU_CMP_3_ALL  \
   | HAL_HSP_FLAG_TCU_TASK_OVL)

/**
  * @}
  */

/** @defgroup HSP_Interrupts_Constants HSP Interrupts Constants
  * @{
  */
#define HAL_HSP_IT_NONE                    (0UL)  /*!< No interrupts */

/**
  * @}
  */

/** @defgroup HSP_Interrupts_Error_Constants HSP Interrupts Error Constants
  * @{
  */
#define HAL_HSP_TRGIN_ERR_IT_OVR            HSP_ERR_IER_TRGIOVRIE  /*!< Trigger Input Overrun error                 */
#define HAL_HSP_STREAM_ERR_IT_BUFFER_0_OVR  HSP_ERR_IER_B0ERRIE    /*!< Stream 0 Underrun/Overrun error             */
#define HAL_HSP_STREAM_ERR_IT_BUFFER_1_OVR  HSP_ERR_IER_B1ERRIE    /*!< Stream 1 Underrun/Overrun error             */
#define HAL_HSP_STREAM_ERR_IT_BUFFER_2_OVR  HSP_ERR_IER_B2ERRIE    /*!< Stream 2 Underrun/Overrun error             */
#define HAL_HSP_STREAM_ERR_IT_BUFFER_3_OVR  HSP_ERR_IER_B3ERRIE    /*!< Stream 3 Underrun/Overrun error             */
#define HAL_HSP_TSC_ERR_IT_OVR              HSP_ERR_IER_CAPOVRIE   /*!< Timestamp Capture Overrun error             */
#define HAL_HSP_SPE_ERR_IT_FW               HSP_ERR_IER_FWERRIE    /*!< Firmware error                              */
#define HAL_HSP_SPE_ERR_IT_SCHEDULER        HSP_ERR_IER_SCHERRIE   /*!< Scheduler error                             */
#define HAL_HSP_SPE_ERR_IT_HDEG_OVR         HSP_ERR_IER_HDEGOVRIE  /*!< Dedicated Event Generator Overrun error     */
#define HAL_HSP_SPE_ERR_IT_INVALID_OPCODE   HSP_ERR_IER_OPCOERRIE  /*!< Invalid Opcode error                        */
#define HAL_HSP_SPE_ERR_IT_ACCESS           HSP_ERR_IER_ACCERRIE   /*!< Access error                                */
#define HAL_HSP_SPE_ERR_IT_FPU_UDF          HSP_ERR_IER_UDFIE      /*!< Floating Point Unit Underflow error         */
#define HAL_HSP_SPE_ERR_IT_FPU_OVF          HSP_ERR_IER_OVFIE      /*!< Floating Point Unit Overflow error          */
#define HAL_HSP_SPE_ERR_IT_FPU_DBZ          HSP_ERR_IER_DBZIE      /*!< Floating Point Unit Division By Zero error  */
#define HAL_HSP_SPE_ERR_IT_FPU_INVALID      HSP_ERR_IER_INVIE      /*!< Floating Point Unit Invalid Exception error */
#define HAL_HSP_SPE_ERR_IT_FPU_DENORMAL     HSP_ERR_IER_DENORMIE   /*!< Floating Point Unit Denormal error          */
#define HAL_HSP_SPE_ERR_IT_BREAK_INPUT      HSP_ERR_IER_BKINIE     /*!< Break Input                                 */

/*! HAL HSP Mask of all Signal Processor Engine interrupts causing a Fault error*/
#define HAL_HSP_FAULT_ERROR_SPE_ALL  (HAL_HSP_SPE_ERR_SCHEDULER | HAL_HSP_SPE_ERR_INVALID_OPCODE)

/*! HAL HSP Mask of all STREAM Buffer Errors */
#define HAL_HSP_STREAM_ERR_IT_ALL  (HAL_HSP_STREAM_ERR_IT_BUFFER_0_OVR   | HAL_HSP_STREAM_ERR_IT_BUFFER_1_OVR  \
                                    | HAL_HSP_STREAM_ERR_IT_BUFFER_2_OVR | HAL_HSP_STREAM_ERR_IT_BUFFER_3_OVR)

/*! HAL HSP Mask of all Trigger Input Errors */
#define HAL_HSP_TRGIN_ERR_IT_ALL  (HAL_HSP_TRGIN_ERR_IT_OVR)

/*! HAL HSP Mask of all Timestamp Capture Errors */
#define HAL_HSP_TSC_ERR_IT_ALL  (HAL_HSP_TSC_ERR_IT_OVR)

/*! HAL HSP Mask of all Floating Point Unit Errors */
#define HAL_HSP_SPE_ERR_IT_FPU_ALL  (HAL_HSP_SPE_ERR_IT_FPU_UDF   | HAL_HSP_SPE_ERR_IT_FPU_OVF      \
                                     | HAL_HSP_SPE_ERR_IT_FPU_DBZ | HAL_HSP_SPE_ERR_IT_FPU_INVALID  \
                                     | HAL_HSP_SPE_ERR_IT_FPU_DENORMAL)

/*! HAL HSP Mask of all Signal Processor Engine Errors */
#define HAL_HSP_SPE_ERR_IT_ALL  (HAL_HSP_SPE_ERR_IT_FW         | HAL_HSP_SPE_ERR_IT_SCHEDULER       \
                                 | HAL_HSP_SPE_ERR_IT_HDEG_OVR | HAL_HSP_SPE_ERR_IT_INVALID_OPCODE  \
                                 | HAL_HSP_SPE_ERR_IT_ACCESS   | HAL_HSP_SPE_ERR_IT_BREAK_INPUT)


/**
  * @}
  */

/** @defgroup HSP_Error_Information_Constants HSP Errors Information Constants
  * @{
  */
#define HAL_HSP_ERROR_INFO_NONE                 (0UL)  /*!< No error information */
#define HAL_HSP_ERROR_INFO_TRGIN_0_OVR          (HSP_ERRINF_TRGIN_0_OVR)  /*!< Trigger Input 0 overrun occurred   */
#define HAL_HSP_ERROR_INFO_TRGIN_1_OVR          (HSP_ERRINF_TRGIN_1_OVR)  /*!< Trigger Input 1 overrun occurred   */
#define HAL_HSP_ERROR_INFO_TRGIN_2_OVR          (HSP_ERRINF_TRGIN_2_OVR)  /*!< Trigger Input 2 overrun occurred   */
#define HAL_HSP_ERROR_INFO_TRGIN_3_OVR          (HSP_ERRINF_TRGIN_3_OVR)  /*!< Trigger Input 3 overrun occurred   */
#define HAL_HSP_ERROR_INFO_TRGIN_4_OVR          (HSP_ERRINF_TRGIN_4_OVR)  /*!< Trigger Input 4 overrun occurred   */
#define HAL_HSP_ERROR_INFO_TRGIN_5_OVR          (HSP_ERRINF_TRGIN_5_OVR)  /*!< Trigger Input 5 overrun occurred   */
#define HAL_HSP_ERROR_INFO_TRGIN_6_OVR          (HSP_ERRINF_TRGIN_6_OVR)  /*!< Trigger Input 6 overrun occurred   */
#define HAL_HSP_ERROR_INFO_TRGIN_7_OVR          (HSP_ERRINF_TRGIN_7_OVR)  /*!< Trigger Input 7 overrun occurred   */
#define HAL_HSP_ERROR_INFO_TRGIN_8_OVR          (HSP_ERRINF_TRGIN_8_OVR)  /*!< Trigger Input 8 overrun occurred   */
#define HAL_HSP_ERROR_INFO_TRGIN_9_OVR          (HSP_ERRINF_TRGIN_9_OVR)  /*!< Trigger Input 9 overrun occurred   */
#define HAL_HSP_ERROR_INFO_SLAVE_AHB_ACCESS     (HSP_ERRINFR_SAHBERR)  /*!< Signal Processor Engine Slave AHB Access
                                                                            error                                     */
#define HAL_HSP_ERROR_INFO_INTERNAL_AHB_ACCESS  (HSP_ERRINFR_MAHBERR)  /*!< Signal Processor Engine AHB Access error
                                                                            to HSP_CTRL                               */
#define HAL_HSP_ERROR_INFO_DATA_MEM_ACCESS      (HSP_ERRINFR_DMERR)    /*!< Signal Processor Engine Data Memory Access
                                                                            error                                     */
#define HAL_HSP_ERROR_INFO_CODE_MEM_ACCESS      (HSP_ERRINFR_CMERR)    /*!< Signal Processor Engine Code Memory Access
                                                                            error                                     */

#define HAL_HSP_ERROR_INFO_FPU_INEXACT   (HSP_ERRINFR_INEXACT)  /*!< Floating Point Unit Inexact Exception       */
#define HAL_HSP_ERROR_INFO_FPU_UDF       (HSP_ERRINFR_UDFLOW)   /*!< Floating Point Unit Underflow error         */
#define HAL_HSP_ERROR_INFO_FPU_OVF       (HSP_ERRINFR_OVFLOW)   /*!< Floating Point Unit Overflow error          */
#define HAL_HSP_ERROR_INFO_FPU_DIVZERO   (HSP_ERRINFR_DIVZERO)  /*!< Floating Point Unit Division By Zero error  */
#define HAL_HSP_ERROR_INFO_FPU_INVALID   (HSP_ERRINFR_INVALID)  /*!< Floating Point Unit Invalid Exception error */
#define HAL_HSP_ERROR_INFO_FPU_DENORMAL  (HSP_ERRINFR_DENORM)   /*!< Floating Point Unit Denormal error          */

/*! HAL HSP Mask of all HSP Floating Point Unit Errors */
#define HAL_HSP_ERROR_INFO_FPU_ALL  (HAL_HSP_ERROR_INFO_FPU_INEXACT   | HAL_HSP_ERROR_INFO_FPU_UDF      \
                                     | HAL_HSP_ERROR_INFO_FPU_OVF     | HAL_HSP_ERROR_INFO_FPU_DIVZERO  \
                                     | HAL_HSP_ERROR_INFO_FPU_INVALID | HAL_HSP_ERROR_INFO_FPU_DENORMAL)

/*! HAL HSP Mask of all HSP Signal Processor Engine Fault Errors for Memory Management Controller */
#define HAL_HSP_FAULT_ERROR_INFO_MMC_ALL  \
  (HAL_HSP_ERROR_INFO_INTERNAL_AHB_ACCESS | HAL_HSP_ERROR_INFO_CODE_MEM_ACCESS)

/*! HAL HSP Mask of all HSP Signal Processor Engine Errors for Memory Management Controller */
#define HAL_HSP_ERROR_INFO_MMC_ALL                                           \
  (HAL_HSP_ERROR_INFO_SLAVE_AHB_ACCESS | HAL_HSP_ERROR_INFO_DATA_MEM_ACCESS  \
   | HAL_HSP_FAULT_ERROR_INFO_MMC_ALL)

/**
  * @}
  */

/** @defgroup HSP_Interrupts_Constants HSP Interrupts Constants
  * @{
  */
#define HAL_HSP_SPE_IT_ENTER_IN_WFE        HSP_EVT_IER_SOFWFEIE   /*!< HSP engine enters in WFE state          */
#define HAL_HSP_SPE_IT_EXIT_FROM_WFE       HSP_EVT_IER_EOFWFEIE   /*!< HSP engine exits from WFE state         */
#define HAL_HSP_SPE_IT_FPU_SATURATION      HSP_EVT_IER_FPUSATIE   /*!< Floating Point Unit saturation occurred */

#define HAL_HSP_PRC_IT_CDEG_READY          HSP_EVT_IER_CDEGRDYIE  /*!< CPU Dedicated Event Generator is ready  */
#define HAL_HSP_TSC_IT_DATA_READY          HSP_EVT_IER_CAPRDYIE   /*!< TimeStamp Capture Data is available     */
#define HAL_HSP_STREAM_IT_BUFFER_0_READY   HSP_EVT_IER_B0EVTIE    /*!< Stream buffer 0 is empty or full
                                                                       depending on whether the direction is
                                                                       configured for RX or TX                 */
#define HAL_HSP_STREAM_IT_BUFFER_1_READY   HSP_EVT_IER_B1EVTIE    /*!< Stream buffer 1 is empty or full
                                                                       depending on whether the direction is
                                                                       configured for RX or TX                 */
#define HAL_HSP_STREAM_IT_BUFFER_2_READY   HSP_EVT_IER_B2EVTIE    /*!< Stream buffer 2 is empty or full
                                                                       depending on whether the direction is
                                                                       configured for RX or TX                 */
#define HAL_HSP_STREAM_IT_BUFFER_3_READY   HSP_EVT_IER_B3EVTIE    /*!< Stream buffer 3 is empty or full
                                                                       depending on whether the direction is
                                                                       configured for RX or TX                 */
#define HAL_HSP_TCU_IT_CMP_0_TASK_STARTED  HSP_EVT_IER_SOTECP0IE  /*!< Task Comparator Unit 0 triggers this
                                                                       interrupt when the monitored task starts*/
#define HAL_HSP_TCU_IT_CMP_1_TASK_STARTED  HSP_EVT_IER_SOTECP1IE  /*!< Task Comparator Unit 1 triggers this
                                                                       interrupt when the monitored task starts*/
#define HAL_HSP_TCU_IT_CMP_2_TASK_STARTED  HSP_EVT_IER_SOTECP2IE  /*!< Task Comparator Unit 2 triggers this
                                                                       interrupt when the monitored task starts*/
#define HAL_HSP_TCU_IT_CMP_3_TASK_STARTED  HSP_EVT_IER_SOTECP3IE  /*!< Task Comparator Unit 3 triggers this
                                                                       interrupt when the monitored task starts*/
#define HAL_HSP_TCU_IT_CMP_0_TASK_ENDED    HSP_EVT_IER_EOTECP0IE  /*!< Task Comparator Unit 0 triggers this
                                                                       interrupt when the monitored task ends  */
#define HAL_HSP_TCU_IT_CMP_1_TASK_ENDED    HSP_EVT_IER_EOTECP1IE  /*!< Task Comparator Unit 1 triggers this
                                                                       interrupt when the monitored task ends  */
#define HAL_HSP_TCU_IT_CMP_2_TASK_ENDED    HSP_EVT_IER_EOTECP2IE  /*!< Task Comparator Unit 2 triggers this
                                                                       interrupt when the monitored task ends  */
#define HAL_HSP_TCU_IT_CMP_3_TASK_ENDED    HSP_EVT_IER_EOTECP3IE  /*!< Task Comparator Unit 3 triggers this
                                                                       interrupt when the monitored task ends  */
#define HAL_HSP_TCU_IT_TASK_OVL            HSP_EVT_IER_TOVLPIE    /*!< Task Overlap occurred                   */

/*! HAL HSP Mask of all HSP STREAM Buffer Events */
#define HAL_HSP_STREAM_EVT_IT_ALL  (HAL_HSP_STREAM_IT_BUFFER_0_READY   | HAL_HSP_STREAM_IT_BUFFER_1_READY  \
                                    | HAL_HSP_STREAM_IT_BUFFER_2_READY | HAL_HSP_STREAM_IT_BUFFER_3_READY)

/*! HAL HSP Mask of all HSP Task Comparator 0 Events */
#define HAL_HSP_TCU_IT_CMP_0_ALL  \
  (HAL_HSP_TCU_IT_CMP_0_TASK_STARTED | HAL_HSP_TCU_IT_CMP_0_TASK_ENDED)

/*! HAL HSP Mask of all HSP Task Comparator 1 Events */
#define HAL_HSP_TCU_IT_CMP_1_ALL  \
  (HAL_HSP_TCU_IT_CMP_1_TASK_STARTED | HAL_HSP_TCU_IT_CMP_1_TASK_ENDED)

/*! HAL HSP Mask of all HSP Task Comparator 2 Events */
#define HAL_HSP_TCU_IT_CMP_2_ALL  \
  (HAL_HSP_TCU_IT_CMP_2_TASK_STARTED | HAL_HSP_TCU_IT_CMP_2_TASK_ENDED)

/*! HAL HSP Mask of all HSP Task Comparator 3 Events */
#define HAL_HSP_TCU_IT_CMP_3_ALL  \
  (HAL_HSP_TCU_IT_CMP_3_TASK_STARTED | HAL_HSP_TCU_IT_CMP_3_TASK_ENDED)

/*! HAL HSP Mask of all HSP Task Comparator Events */
#define HAL_HSP_TCU_IT_CMP_ALL                                   \
  (HAL_HSP_TCU_IT_CMP_0_ALL   | HAL_HSP_TCU_IT_CMP_1_ALL  \
   | HAL_HSP_TCU_IT_CMP_2_ALL | HAL_HSP_TCU_IT_CMP_3_ALL)

/*! HAL HSP Mask of all HSP TCU Events */
#define HAL_HSP_TCU_IT_ALL  (HAL_HSP_TCU_IT_CMP_0_ALL   | HAL_HSP_TCU_IT_CMP_1_ALL  \
                             | HAL_HSP_TCU_IT_CMP_2_ALL | HAL_HSP_TCU_IT_CMP_3_ALL  \
                             | HAL_HSP_TCU_IT_TASK_OVL)

/*! HAL HSP Mask of all HSP Signal Processor Engine Events */
#define HAL_HSP_SPE_IT_ALL  (HAL_HSP_SPE_IT_ENTER_IN_WFE | HAL_HSP_SPE_IT_EXIT_FROM_WFE  \
                             | HAL_HSP_SPE_IT_FPU_SATURATION)

/**
  * @}
  */

/** @defgroup HSP_Processing_Function_Event_Interrupts_Constants HSP Processing Function Event Interrupts Constants
  * @{
  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_0   HSP_PFCTEVT_IER_PFCTIE_0   /*!< Processing Function Event 0 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_1   HSP_PFCTEVT_IER_PFCTIE_1   /*!< Processing Function Event 1 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_2   HSP_PFCTEVT_IER_PFCTIE_2   /*!< Processing Function Event 2 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_3   HSP_PFCTEVT_IER_PFCTIE_3   /*!< Processing Function Event 3 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_4   HSP_PFCTEVT_IER_PFCTIE_4   /*!< Processing Function Event 4 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_5   HSP_PFCTEVT_IER_PFCTIE_5   /*!< Processing Function Event 5 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_6   HSP_PFCTEVT_IER_PFCTIE_6   /*!< Processing Function Event 6 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_7   HSP_PFCTEVT_IER_PFCTIE_7   /*!< Processing Function Event 7 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_8   HSP_PFCTEVT_IER_PFCTIE_8   /*!< Processing Function Event 8 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_9   HSP_PFCTEVT_IER_PFCTIE_9   /*!< Processing Function Event 9 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_10  HSP_PFCTEVT_IER_PFCTIE_10  /*!< Processing Function Event 10 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_11  HSP_PFCTEVT_IER_PFCTIE_11  /*!< Processing Function Event 11 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_12  HSP_PFCTEVT_IER_PFCTIE_12  /*!< Processing Function Event 12 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_13  HSP_PFCTEVT_IER_PFCTIE_13  /*!< Processing Function Event 13 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_14  HSP_PFCTEVT_IER_PFCTIE_14  /*!< Processing Function Event 14 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_15  HSP_PFCTEVT_IER_PFCTIE_15  /*!< Processing Function Event 15 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_16  HSP_PFCTEVT_IER_PFCTIE_16  /*!< Processing Function Event 16 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_17  HSP_PFCTEVT_IER_PFCTIE_17  /*!< Processing Function Event 17 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_18  HSP_PFCTEVT_IER_PFCTIE_18  /*!< Processing Function Event 18 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_19  HSP_PFCTEVT_IER_PFCTIE_19  /*!< Processing Function Event 19 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_20  HSP_PFCTEVT_IER_PFCTIE_20  /*!< Processing Function Event 20 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_21  HSP_PFCTEVT_IER_PFCTIE_21  /*!< Processing Function Event 21 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_22  HSP_PFCTEVT_IER_PFCTIE_22  /*!< Processing Function Event 22 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_23  HSP_PFCTEVT_IER_PFCTIE_23  /*!< Processing Function Event 23 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_24  HSP_PFCTEVT_IER_PFCTIE_24  /*!< Processing Function Event 24 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_25  HSP_PFCTEVT_IER_PFCTIE_25  /*!< Processing Function Event 25 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_26  HSP_PFCTEVT_IER_PFCTIE_26  /*!< Processing Function Event 26 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_27  HSP_PFCTEVT_IER_PFCTIE_27  /*!< Processing Function Event 27 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_28  HSP_PFCTEVT_IER_PFCTIE_28  /*!< Processing Function Event 28 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_29  HSP_PFCTEVT_IER_PFCTIE_29  /*!< Processing Function Event 29 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_30  HSP_PFCTEVT_IER_PFCTIE_30  /*!< Processing Function Event 30 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_31  HSP_PFCTEVT_IER_PFCTIE_31  /*!< Processing Function Event 31 interrupt */

/*! HAL HSP Mask of all HSP Processing Function interrupts */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_ALL  \
  (HAL_HSP_PROCLIST_IT_PFCTEVT_0    | HAL_HSP_PROCLIST_IT_PFCTEVT_1  | HAL_HSP_PROCLIST_IT_PFCTEVT_2   \
   | HAL_HSP_PROCLIST_IT_PFCTEVT_3  | HAL_HSP_PROCLIST_IT_PFCTEVT_4  | HAL_HSP_PROCLIST_IT_PFCTEVT_5   \
   | HAL_HSP_PROCLIST_IT_PFCTEVT_6  | HAL_HSP_PROCLIST_IT_PFCTEVT_7  | HAL_HSP_PROCLIST_IT_PFCTEVT_8   \
   | HAL_HSP_PROCLIST_IT_PFCTEVT_9  | HAL_HSP_PROCLIST_IT_PFCTEVT_10 | HAL_HSP_PROCLIST_IT_PFCTEVT_11  \
   | HAL_HSP_PROCLIST_IT_PFCTEVT_12 | HAL_HSP_PROCLIST_IT_PFCTEVT_13 | HAL_HSP_PROCLIST_IT_PFCTEVT_14  \
   | HAL_HSP_PROCLIST_IT_PFCTEVT_15 | HAL_HSP_PROCLIST_IT_PFCTEVT_16 | HAL_HSP_PROCLIST_IT_PFCTEVT_17  \
   | HAL_HSP_PROCLIST_IT_PFCTEVT_18 | HAL_HSP_PROCLIST_IT_PFCTEVT_19 | HAL_HSP_PROCLIST_IT_PFCTEVT_20  \
   | HAL_HSP_PROCLIST_IT_PFCTEVT_21 | HAL_HSP_PROCLIST_IT_PFCTEVT_22 | HAL_HSP_PROCLIST_IT_PFCTEVT_23  \
   | HAL_HSP_PROCLIST_IT_PFCTEVT_24 | HAL_HSP_PROCLIST_IT_PFCTEVT_25 | HAL_HSP_PROCLIST_IT_PFCTEVT_26  \
   | HAL_HSP_PROCLIST_IT_PFCTEVT_27 | HAL_HSP_PROCLIST_IT_PFCTEVT_28 | HAL_HSP_PROCLIST_IT_PFCTEVT_29  \
   | HAL_HSP_PROCLIST_IT_PFCTEVT_30 | HAL_HSP_PROCLIST_IT_PFCTEVT_31)

/**
  * @}
  */

/** @defgroup HSP_SPE_Run_State_Constants HSP Signal Processor Engine Run State Constants
  * @{
  */
#define HAL_HSP_SPE_RUN_STATE_WFE     (0U)  /*!< HSP Signal Processor Engine Wait For Event state */
#define HAL_HSP_SPE_RUN_STATE_ACTIVE  (1U)  /*!< HSP Signal Processor Engine Active state         */

/**
  * @}
  */

/** @defgroup HSP_Break_Event_Constants HSP Break Event constants
  * @{
  */
#define HAL_HSP_BREAK_EVENT_SPE_OVR           HSP_BKOCFGR_HDEGOVEN  /*!< HSP Dedicated Event Generator Overrun       */
#define HAL_HSP_BREAK_EVENT_FIRMWARE          HSP_BKOCFGR_FWEREN    /*!< Firmware Error                              */
#define HAL_HSP_BREAK_EVENT_MEMORY_ACCESS     HSP_BKOCFGR_ACCEREN   /*!< Signal Processor Engine Memory Access Error */
#define HAL_HSP_BREAK_EVENT_OPCODE            HSP_BKOCFGR_OPCEREN   /*!< OpCode Error                                */
#define HAL_HSP_BREAK_EVENT_FPU               HSP_BKOCFGR_FPUEREN   /*!< Floating Point Unit Error                   */
#define HAL_HSP_BREAK_EVENT_PFCT_28           HSP_BKOCFGR_PFCT28EN  /*!< Processing Function Event 28                */
#define HAL_HSP_BREAK_EVENT_PFCT_29           HSP_BKOCFGR_PFCT29EN  /*!< Processing Function Event 29                */
#define HAL_HSP_BREAK_EVENT_PFCT_30           HSP_BKOCFGR_PFCT30EN  /*!< Processing Function Event 30                */
#define HAL_HSP_BREAK_EVENT_PFCT_31           HSP_BKOCFGR_PFCT31EN  /*!< Processing Function Event 31                */
#define HAL_HSP_BREAK_EVENT_FPU_SATURATION    HSP_BKICFGR_FSATEN    /*!< Floating Point Unit Saturation Event        */
#define HAL_HSP_BREAK_EVENT_SINGLE_STEP       HSP_BKICFGR_SSEN      /*!< Single Step Event                           */

/*! HAL HSP BREAK Mask of all Processing Function Events */
#define HAL_HSP_BREAK_EVENT_PFCT_ALL  (HAL_HSP_BREAK_EVENT_PFCT_28   | HAL_HSP_BREAK_EVENT_PFCT_29  \
                                       | HAL_HSP_BREAK_EVENT_PFCT_30 | HAL_HSP_BREAK_EVENT_PFCT_31)

/*! HAL HSP BREAK Mask of all Break Output Events */
#define HAL_HSP_BREAK_OUTPUT_EVENT_ALL                                 \
  (HAL_HSP_BREAK_EVENT_SPE_OVR         | HAL_HSP_BREAK_EVENT_FIRMWARE  \
   | HAL_HSP_BREAK_EVENT_MEMORY_ACCESS | HAL_HSP_BREAK_EVENT_OPCODE    \
   | HAL_HSP_BREAK_EVENT_FPU           | HAL_HSP_BREAK_EVENT_PFCT_ALL)

/*! HAL HSP BREAK Mask of all Break Internal Events */
#define HAL_HSP_BREAK_FREEZE_EVENT_ALL  \
  (HAL_HSP_BREAK_OUTPUT_EVENT_ALL | HAL_HSP_BREAK_EVENT_FPU_SATURATION)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup HSP_Exported_Macros  HSP Exported Macros
  * @{
  */
/**
  * @brief Retrieve the HSP RAM Firmware major version.
  * @param  firmware_version  Firmware version value returned by HAL_HSP_GetFirmwareVersion().
  * @return RAM Firmware major version value.
  */
#define HAL_HSP_GET_RAM_FW_MAJOR_VERSION(firmware_version)  \
  (((firmware_version) & HSP_FWVERR_RAMMAJREV) >> HSP_FWVERR_RAMMAJREV_Pos)

/**
  * @brief Retrieve the HSP RAM Firmware minor version.
  * @param  firmware_version  Firmware version value returned by HAL_HSP_GetFirmwareVersion().
  * @return RAM Firmware minor version value.
  */
#define HAL_HSP_GET_RAM_FW_MINOR_VERSION(firmware_version)  \
  (((firmware_version) & HSP_FWVERR_RAMMINREV) >> HSP_FWVERR_RAMMINREV_Pos)

/**
  * @brief Retrieve the HSP ROM Firmware major version.
  * @param  firmware_version  Firmware version value returned by HAL_HSP_GetFirmwareVersion().
  * @return ROM Firmware major version value.
  */
#define HAL_HSP_GET_ROM_FW_MAJOR_VERSION(firmware_version)  \
  (((firmware_version) & HSP_FWVERR_ROMMAJREV) >> HSP_FWVERR_ROMMAJREV_Pos)

/**
  * @brief Retrieve the HSP ROM Firmware minor version.
  * @param  firmware_version  Firmware version value returned by HAL_HSP_GetFirmwareVersion().
  * @return ROM Firmware minor version value.
  */
#define HAL_HSP_GET_ROM_FW_MINOR_VERSION(firmware_version)  \
  (((firmware_version) & HSP_FWVERR_ROMMINREV) >> HSP_FWVERR_ROMMINREV_Pos)

/**
  * @brief Get the HSP Shared Event Generator Event Source Enum value.
  * @param  evt_priority  Event priority.
  * @return HSEG enumerate from hal_hsp_event_source_t.
  */
#define HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_HSEG(evt_priority)  \
  (((evt_priority) == 1U)?HAL_HSP_EVENT_1_HSEG:               \
   ((evt_priority) == 2U)?HAL_HSP_EVENT_2_HSEG:               \
   ((evt_priority) == 3U)?HAL_HSP_EVENT_3_HSEG:               \
   ((evt_priority) == 4U)?HAL_HSP_EVENT_4_HSEG:               \
   ((evt_priority) == 5U)?HAL_HSP_EVENT_5_HSEG:               \
   ((evt_priority) == 6U)?HAL_HSP_EVENT_6_HSEG:               \
   ((evt_priority) == 7U)?HAL_HSP_EVENT_7_HSEG:               \
   ((evt_priority) == 8U)?HAL_HSP_EVENT_8_HSEG:               \
   ((evt_priority) == 9U)?HAL_HSP_EVENT_9_HSEG:               \
   ((evt_priority) == 10U)?HAL_HSP_EVENT_10_HSEG:             \
   ((evt_priority) == 11U)?HAL_HSP_EVENT_11_HSEG:             \
   ((evt_priority) == 12U)?HAL_HSP_EVENT_12_HSEG:             \
   ((evt_priority) == 13U)?HAL_HSP_EVENT_13_HSEG:             \
   ((evt_priority) == 14U)?HAL_HSP_EVENT_14_HSEG:             \
   ((evt_priority) == 15U)?HAL_HSP_EVENT_15_HSEG:             \
   ((evt_priority) == 16U)?HAL_HSP_EVENT_16_HSEG:             \
   ((evt_priority) == 17U)?HAL_HSP_EVENT_17_HSEG:             \
   ((evt_priority) == 18U)?HAL_HSP_EVENT_18_HSEG:             \
   ((evt_priority) == 19U)?HAL_HSP_EVENT_19_HSEG:             \
   ((evt_priority) == 20U)?HAL_HSP_EVENT_20_HSEG:             \
   ((evt_priority) == 21U)?HAL_HSP_EVENT_21_HSEG:             \
   ((evt_priority) == 22U)?HAL_HSP_EVENT_22_HSEG:             \
   HAL_HSP_EVENT_RESERVED)

/**
  * @brief Get the CPU Shared Event Generator Event Source Enum value.
  * @param  evt_priority  Event priority.
  * @retval uint32_t.
  */
#define HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_CSEG(evt_priority)  \
  (((evt_priority) == 1U)?HAL_HSP_EVENT_1_CSEG:               \
   ((evt_priority) == 2U)?HAL_HSP_EVENT_2_CSEG:               \
   ((evt_priority) == 3U)?HAL_HSP_EVENT_3_CSEG:               \
   ((evt_priority) == 4U)?HAL_HSP_EVENT_4_CSEG:               \
   ((evt_priority) == 5U)?HAL_HSP_EVENT_5_CSEG:               \
   ((evt_priority) == 6U)?HAL_HSP_EVENT_6_CSEG:               \
   ((evt_priority) == 7U)?HAL_HSP_EVENT_7_CSEG:               \
   ((evt_priority) == 8U)?HAL_HSP_EVENT_8_CSEG:               \
   ((evt_priority) == 9U)?HAL_HSP_EVENT_9_CSEG:               \
   ((evt_priority) == 10U)?HAL_HSP_EVENT_10_CSEG:             \
   ((evt_priority) == 11U)?HAL_HSP_EVENT_11_CSEG:             \
   ((evt_priority) == 12U)?HAL_HSP_EVENT_12_CSEG:             \
   ((evt_priority) == 13U)?HAL_HSP_EVENT_13_CSEG:             \
   ((evt_priority) == 14U)?HAL_HSP_EVENT_14_CSEG:             \
   ((evt_priority) == 15U)?HAL_HSP_EVENT_15_CSEG:             \
   ((evt_priority) == 16U)?HAL_HSP_EVENT_16_CSEG:             \
   ((evt_priority) == 17U)?HAL_HSP_EVENT_17_CSEG:             \
   ((evt_priority) == 18U)?HAL_HSP_EVENT_18_CSEG:             \
   ((evt_priority) == 19U)?HAL_HSP_EVENT_19_CSEG:             \
   ((evt_priority) == 20U)?HAL_HSP_EVENT_20_CSEG:             \
   ((evt_priority) == 21U)?HAL_HSP_EVENT_21_CSEG:             \
   ((evt_priority) == 22U)?HAL_HSP_EVENT_22_CSEG:             \
   HAL_HSP_EVENT_RESERVED)

/**
  * @brief Get the HSP Event STREAM Buffer Source Enum value.
  * @param  evt_priority  Event priority.
  * @retval uint32_t.
  */
#define HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_STREAM(evt_priority)  \
  (((evt_priority) == 1U)?HAL_HSP_EVENT_1_STREAM0:              \
   ((evt_priority) == 2U)?HAL_HSP_EVENT_2_STREAM1:              \
   ((evt_priority) == 3U)?HAL_HSP_EVENT_3_STREAM2:              \
   ((evt_priority) == 4U)?HAL_HSP_EVENT_4_STREAM3:              \
   ((evt_priority) == 5U)?HAL_HSP_EVENT_5_STREAM0:              \
   ((evt_priority) == 6U)?HAL_HSP_EVENT_6_STREAM1:              \
   ((evt_priority) == 7U)?HAL_HSP_EVENT_7_STREAM2:              \
   ((evt_priority) == 8U)?HAL_HSP_EVENT_8_STREAM3:              \
   ((evt_priority) == 9U)?HAL_HSP_EVENT_9_STREAM0:              \
   ((evt_priority) == 10U)?HAL_HSP_EVENT_10_STREAM1:            \
   ((evt_priority) == 11U)?HAL_HSP_EVENT_11_STREAM2:            \
   ((evt_priority) == 12U)?HAL_HSP_EVENT_12_STREAM3:            \
   ((evt_priority) == 13U)?HAL_HSP_EVENT_13_STREAM0:            \
   ((evt_priority) == 14U)?HAL_HSP_EVENT_14_STREAM1:            \
   ((evt_priority) == 15U)?HAL_HSP_EVENT_15_STREAM2:            \
   ((evt_priority) == 16U)?HAL_HSP_EVENT_16_STREAM3:            \
   ((evt_priority) == 17U)?HAL_HSP_EVENT_17_STREAM0:            \
   ((evt_priority) == 18U)?HAL_HSP_EVENT_18_STREAM1:            \
   ((evt_priority) == 19U)?HAL_HSP_EVENT_19_STREAM2:            \
   ((evt_priority) == 20U)?HAL_HSP_EVENT_20_STREAM3:            \
   ((evt_priority) == 21U)?HAL_HSP_EVENT_21_STREAM0:            \
   ((evt_priority) == 22U)?HAL_HSP_EVENT_22_STREAM1:            \
   HAL_HSP_EVENT_RESERVED)

/**
  * @brief Get the HSP Event Trigger Input Source Enum value.
  * @param  evt_priority  Event priority.
  * @param  trig_itf_id   Trigger Input id.
  * @retval uint32_t.
  */
#define HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_TRIGGER(evt_priority, trig_itf_id)    \
  ((((evt_priority) == 1U)  && ((trig_itf_id) == 3U))?HAL_HSP_EVENT_1_TRGIN3:   \
   (((evt_priority) == 1U)  && ((trig_itf_id) == 8U))?HAL_HSP_EVENT_1_TRGIN8:   \
   (((evt_priority) == 2U)  && ((trig_itf_id) == 4U))?HAL_HSP_EVENT_2_TRGIN4:   \
   (((evt_priority) == 2U)  && ((trig_itf_id) == 9U))?HAL_HSP_EVENT_2_TRGIN9:   \
   (((evt_priority) == 3U)  && ((trig_itf_id) == 0U))?HAL_HSP_EVENT_3_TRGIN0:   \
   (((evt_priority) == 3U)  && ((trig_itf_id) == 5U))?HAL_HSP_EVENT_3_TRGIN5:   \
   (((evt_priority) == 4U)  && ((trig_itf_id) == 1U))?HAL_HSP_EVENT_4_TRGIN1:   \
   (((evt_priority) == 4U)  && ((trig_itf_id) == 6U))?HAL_HSP_EVENT_4_TRGIN6:   \
   (((evt_priority) == 5U)  && ((trig_itf_id) == 2U))?HAL_HSP_EVENT_5_TRGIN2:   \
   (((evt_priority) == 5U)  && ((trig_itf_id) == 7U))?HAL_HSP_EVENT_5_TRGIN7:   \
   (((evt_priority) == 6U)  && ((trig_itf_id) == 3U))?HAL_HSP_EVENT_6_TRGIN3:   \
   (((evt_priority) == 6U)  && ((trig_itf_id) == 8U))?HAL_HSP_EVENT_6_TRGIN8:   \
   (((evt_priority) == 7U)  && ((trig_itf_id) == 4U))?HAL_HSP_EVENT_7_TRGIN4:   \
   (((evt_priority) == 7U)  && ((trig_itf_id) == 9U))?HAL_HSP_EVENT_7_TRGIN9:   \
   (((evt_priority) == 8U)  && ((trig_itf_id) == 0U))?HAL_HSP_EVENT_8_TRGIN0:   \
   (((evt_priority) == 8U)  && ((trig_itf_id) == 5U))?HAL_HSP_EVENT_8_TRGIN5:   \
   (((evt_priority) == 9U)  && ((trig_itf_id) == 1U))?HAL_HSP_EVENT_9_TRGIN1:   \
   (((evt_priority) == 9U)  && ((trig_itf_id) == 6U))?HAL_HSP_EVENT_9_TRGIN6:   \
   (((evt_priority) == 10U) && ((trig_itf_id) == 2U))?HAL_HSP_EVENT_10_TRGIN2:  \
   (((evt_priority) == 10U) && ((trig_itf_id) == 7U))?HAL_HSP_EVENT_10_TRGIN7:  \
   (((evt_priority) == 11U) && ((trig_itf_id) == 3U))?HAL_HSP_EVENT_11_TRGIN3:  \
   (((evt_priority) == 11U) && ((trig_itf_id) == 8U))?HAL_HSP_EVENT_11_TRGIN8:  \
   (((evt_priority) == 12U) && ((trig_itf_id) == 4U))?HAL_HSP_EVENT_12_TRGIN4:  \
   (((evt_priority) == 12U) && ((trig_itf_id) == 9U))?HAL_HSP_EVENT_12_TRGIN9:  \
   (((evt_priority) == 13U) && ((trig_itf_id) == 0U))?HAL_HSP_EVENT_13_TRGIN0:  \
   (((evt_priority) == 13U) && ((trig_itf_id) == 5U))?HAL_HSP_EVENT_13_TRGIN5:  \
   (((evt_priority) == 14U) && ((trig_itf_id) == 1U))?HAL_HSP_EVENT_14_TRGIN1:  \
   (((evt_priority) == 14U) && ((trig_itf_id) == 6U))?HAL_HSP_EVENT_14_TRGIN6:  \
   (((evt_priority) == 15U) && ((trig_itf_id) == 2U))?HAL_HSP_EVENT_15_TRGIN2:  \
   (((evt_priority) == 15U) && ((trig_itf_id) == 7U))?HAL_HSP_EVENT_15_TRGIN7:  \
   (((evt_priority) == 16U) && ((trig_itf_id) == 3U))?HAL_HSP_EVENT_16_TRGIN3:  \
   (((evt_priority) == 16U) && ((trig_itf_id) == 8U))?HAL_HSP_EVENT_16_TRGIN8:  \
   (((evt_priority) == 17U) && ((trig_itf_id) == 4U))?HAL_HSP_EVENT_17_TRGIN4:  \
   (((evt_priority) == 17U) && ((trig_itf_id) == 9U))?HAL_HSP_EVENT_17_TRGIN9:  \
   (((evt_priority) == 18U) && ((trig_itf_id) == 0U))?HAL_HSP_EVENT_18_TRGIN0:  \
   (((evt_priority) == 18U) && ((trig_itf_id) == 5U))?HAL_HSP_EVENT_18_TRGIN5:  \
   (((evt_priority) == 19U) && ((trig_itf_id) == 1U))?HAL_HSP_EVENT_19_TRGIN1:  \
   (((evt_priority) == 19U) && ((trig_itf_id) == 6U))?HAL_HSP_EVENT_19_TRGIN6:  \
   (((evt_priority) == 20U) && ((trig_itf_id) == 2U))?HAL_HSP_EVENT_20_TRGIN2:  \
   (((evt_priority) == 20U) && ((trig_itf_id) == 7U))?HAL_HSP_EVENT_20_TRGIN7:  \
   (((evt_priority) == 21U) && ((trig_itf_id) == 3U))?HAL_HSP_EVENT_21_TRGIN3:  \
   (((evt_priority) == 21U) && ((trig_itf_id) == 8U))?HAL_HSP_EVENT_21_TRGIN8:  \
   (((evt_priority) == 22U) && ((trig_itf_id) == 4U))?HAL_HSP_EVENT_22_TRGIN4:  \
   (((evt_priority) == 22U) && ((trig_itf_id) == 9U))?HAL_HSP_EVENT_22_TRGIN9:  \
   HAL_HSP_EVENT_RESERVED)

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HSP_Exported_Types  HSP Exported Types
  * @{
  */
/** @defgroup HSP_Exported_Types_Group1 HSP Boot Types
  * @{
  */
/*! HAL HSP Performance Monitor state enumeration */
typedef enum
{
  HAL_HSP_PERF_MONITOR_DISABLE = 0U,
  HAL_HSP_PERF_MONITOR_ENABLE  = 1U,
} hal_hsp_perf_monitor_state_t;

/*! HAL HSP Boot configuration structure */
typedef struct
{
  /*! Boot Command ID depends on Firmware ROM */
  uint32_t boot_cmd_id;

  /*! Boot Success Code depends on Firmware ROM */
  uint32_t boot_success_code;

  /*! Enable/Disable the Performance Monitor at Boot step */
  hal_hsp_perf_monitor_state_t perf_monitor_state;

  /** Firmware Error Direct Command ID, to clean the Firmware Error Code,
      depends on Firmware ROM */
  uint32_t fwerr_dcmd_id;
} hal_hsp_boot_config_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group2 HSP Command Enumerations
  * @{
  */
/*! HAL HSP command parameter enumeration */
typedef enum
{
  HAL_HSP_PARAM_0  = 0U,
  HAL_HSP_PARAM_1  = 1U,
  HAL_HSP_PARAM_2  = 2U,
  HAL_HSP_PARAM_3  = 3U,
  HAL_HSP_PARAM_4  = 4U,
  HAL_HSP_PARAM_5  = 5U,
  HAL_HSP_PARAM_6  = 6U,
  HAL_HSP_PARAM_7  = 7U,
  HAL_HSP_PARAM_8  = 8U,
  HAL_HSP_PARAM_9  = 9U,
  HAL_HSP_PARAM_10 = 10U,
  HAL_HSP_PARAM_11 = 11U,
  HAL_HSP_PARAM_12 = 12U,
  HAL_HSP_PARAM_13 = 13U,
  HAL_HSP_PARAM_14 = 14U,
  HAL_HSP_PARAM_15 = 15U,
} hal_hsp_param_t;

/*! HAL HSP DCMD data pointer enumeration */
typedef enum
{
  /*! Direct Command Pointer 0 */
  HAL_HSP_DCMD_DATA_PTR0 = 0U,

  /*! Direct Command Pointer 1 */
  HAL_HSP_DCMD_DATA_PTR1 = 1U,

  /*! Direct Command Pointer 2 */
  HAL_HSP_DCMD_DATA_PTR2 = 2U
} hal_hsp_dcmd_data_ptr_t;

/*! HAL HSP DCMD interface status enumeration */
typedef enum
{
  /*! Direct Command Interface is ready to use */
  HAL_HSP_DCMD_READY = 0U,

  /*! Direct Command Interface is busy */
  HAL_HSP_DCMD_BUSY  = HSP_DCMDSR_DCBSY
} hal_hsp_dcmd_status_t;

/*! HAL HSP MSGBOX semaphore status enumeration */
typedef enum
{
  /*! No message in the mailbox */
  HAL_HSP_MSGBOX_SEMAPHORE_NO_MSG        = 0U,

  /*! A message is available in the mailbox */
  HAL_HSP_MSGBOX_SEMAPHORE_MSG_AVAILABLE = HSP_H2CSEMR_H2CSEM
} hal_hsp_msgbox_semaphore_status_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group3 HSP Task Enumerations
  * @{
  */
/*! HAL HSP task enumeration */
typedef enum
{
  HAL_HSP_TASK_0 = 0U,   /*!< HSP Task 0   */
  HAL_HSP_TASK_1 = 1U,   /*!< HSP Task 1   */
  HAL_HSP_TASK_2 = 2U,   /*!< HSP Task 2   */
  HAL_HSP_TASK_3 = 3U,   /*!< HSP Task 3   */
  HAL_HSP_TASK_4 = 4U,   /*!< HSP Task 4   */
  HAL_HSP_TASK_5 = 5U,   /*!< HSP Task 5   */
  HAL_HSP_TASK_6 = 6U,   /*!< HSP Task 6   */
  HAL_HSP_TASK_7 = 7U,   /*!< HSP Task 7   */
  HAL_HSP_TASK_8 = 8U,   /*!< HSP Task 8   */
  HAL_HSP_TASK_9 = 9U,   /*!< HSP Task 9   */
  HAL_HSP_TASK_10 = 10U, /*!< HSP Task 10  */
  HAL_HSP_TASK_11 = 11U, /*!< HSP Task 11  */
  HAL_HSP_TASK_12 = 12U, /*!< HSP Task 12  */
  HAL_HSP_TASK_13 = 13U, /*!< HSP Task 13  */
  HAL_HSP_TASK_14 = 14U, /*!< HSP Task 14  */
  HAL_HSP_TASK_15 = 15U, /*!< HSP Task 15  */
  HAL_HSP_TASK_16 = 16U, /*!< HSP Task 16  */
  HAL_HSP_TASK_17 = 17U, /*!< HSP Task 17  */
  HAL_HSP_TASK_18 = 18U, /*!< HSP Task 18  */
  HAL_HSP_TASK_19 = 19U, /*!< HSP Task 19  */
  HAL_HSP_TASK_20 = 20U, /*!< HSP Task 20  */
  HAL_HSP_TASK_21 = 21U, /*!< HSP Task 21  */
  HAL_HSP_TASK_22 = 22U, /*!< HSP Task 22  */
  HAL_HSP_TASK_23 = 23U, /*!< HSP Task 23  */
  HAL_HSP_TASK_24 = 24U, /*!< HSP Task 24  */
  HAL_HSP_TASK_25 = 25U, /*!< HSP Task 25  */
  HAL_HSP_TASK_26 = 26U, /*!< HSP Task 26  */
  HAL_HSP_TASK_27 = 27U, /*!< HSP Task 27  */
  HAL_HSP_TASK_28 = 28U, /*!< HSP Task 28  */
  HAL_HSP_TASK_29 = 29U, /*!< HSP Task 29  */
  HAL_HSP_TASK_30 = 30U, /*!< HSP Task 30  */
  HAL_HSP_TASK_31 = 31U, /*!< HSP Task 31  */
  HAL_HSP_TASK_32 = 32U, /*!< HSP Task 32  */
  HAL_HSP_TASK_33 = 33U, /*!< HSP Task 33  */
  HAL_HSP_TASK_34 = 34U, /*!< HSP Task 34  */
  HAL_HSP_TASK_35 = 35U, /*!< HSP Task 35  */
  HAL_HSP_TASK_36 = 36U, /*!< HSP Task 36  */
  HAL_HSP_TASK_SUPERVISOR = 37U  /*!< HSP Task dedicated for Supervisor process */
} hal_hsp_task_t;

/*! HAL HSP task comparator enumeration */
typedef enum
{
  HAL_HSP_TASK_COMPARATOR_0  = 0U,
  HAL_HSP_TASK_COMPARATOR_1  = 1U,
  HAL_HSP_TASK_COMPARATOR_2  = 2U,
  HAL_HSP_TASK_COMPARATOR_3  = 3U
} hal_hsp_task_comparator_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group4 HSP Event Trigger Source Matrix Enumerations
  * @{
  */
/**
  * @brief  HAL HSP event source enumeration.
  *
  *  +------------------+--------------+------------------+--- ... ---+-------------------+
  *  | Priority (6-bit) | Register SRC field pos (5-bit)  |  Reserved | reg value (3-bit) |
  *  +------------------+--------------+------------------+--- ... ---+-------------------+
  */
typedef enum
{
  HAL_HSP_EVENT_RESERVED = 0U,

  /* Event 1 source Matrix ****************************************************/
  HAL_HSP_EVENT_1_STREAM0 = HAL_HSP_EVENT_SOURCE_ENCODE(1U, HSP_EVTSRC0R_EVT1SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_1_TRGIN3  = HAL_HSP_EVENT_SOURCE_ENCODE(1U, HSP_EVTSRC0R_EVT1SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_1_TRGIN8  = HAL_HSP_EVENT_SOURCE_ENCODE(1U, HSP_EVTSRC0R_EVT1SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_1_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(1U, HSP_EVTSRC0R_EVT1SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_1_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(1U, HSP_EVTSRC0R_EVT1SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 2 source Matrix ****************************************************/
  HAL_HSP_EVENT_2_STREAM1 = HAL_HSP_EVENT_SOURCE_ENCODE(2U, HSP_EVTSRC0R_EVT2SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_2_TRGIN4  = HAL_HSP_EVENT_SOURCE_ENCODE(2U, HSP_EVTSRC0R_EVT2SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_2_TRGIN9  = HAL_HSP_EVENT_SOURCE_ENCODE(2U, HSP_EVTSRC0R_EVT2SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_2_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(2U, HSP_EVTSRC0R_EVT2SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_2_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(2U, HSP_EVTSRC0R_EVT2SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 3 source Matrix ****************************************************/
  HAL_HSP_EVENT_3_STREAM2 = HAL_HSP_EVENT_SOURCE_ENCODE(3U, HSP_EVTSRC0R_EVT3SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_3_TRGIN0  = HAL_HSP_EVENT_SOURCE_ENCODE(3U, HSP_EVTSRC0R_EVT3SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_3_TRGIN5  = HAL_HSP_EVENT_SOURCE_ENCODE(3U, HSP_EVTSRC0R_EVT3SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_3_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(3U, HSP_EVTSRC0R_EVT3SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_3_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(3U, HSP_EVTSRC0R_EVT3SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 4 source Matrix ****************************************************/
  HAL_HSP_EVENT_4_STREAM3 = HAL_HSP_EVENT_SOURCE_ENCODE(4U, HSP_EVTSRC0R_EVT4SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_4_TRGIN1  = HAL_HSP_EVENT_SOURCE_ENCODE(4U, HSP_EVTSRC0R_EVT4SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_4_TRGIN6  = HAL_HSP_EVENT_SOURCE_ENCODE(4U, HSP_EVTSRC0R_EVT4SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_4_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(4U, HSP_EVTSRC0R_EVT4SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_4_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(4U, HSP_EVTSRC0R_EVT4SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 5 source Matrix ****************************************************/
  HAL_HSP_EVENT_5_STREAM0 = HAL_HSP_EVENT_SOURCE_ENCODE(5U, HSP_EVTSRC0R_EVT5SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_5_TRGIN2  = HAL_HSP_EVENT_SOURCE_ENCODE(5U, HSP_EVTSRC0R_EVT5SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_5_TRGIN7  = HAL_HSP_EVENT_SOURCE_ENCODE(5U, HSP_EVTSRC0R_EVT5SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_5_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(5U, HSP_EVTSRC0R_EVT5SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_5_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(5U, HSP_EVTSRC0R_EVT5SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 6 source Matrix ****************************************************/
  HAL_HSP_EVENT_6_STREAM1 = HAL_HSP_EVENT_SOURCE_ENCODE(6U, HSP_EVTSRC0R_EVT6SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_6_TRGIN3  = HAL_HSP_EVENT_SOURCE_ENCODE(6U, HSP_EVTSRC0R_EVT6SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_6_TRGIN8  = HAL_HSP_EVENT_SOURCE_ENCODE(6U, HSP_EVTSRC0R_EVT6SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_6_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(6U, HSP_EVTSRC0R_EVT6SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_6_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(6U, HSP_EVTSRC0R_EVT6SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 7 source Matrix ****************************************************/
  HAL_HSP_EVENT_7_STREAM2 = HAL_HSP_EVENT_SOURCE_ENCODE(7U, HSP_EVTSRC0R_EVT7SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_7_TRGIN4  = HAL_HSP_EVENT_SOURCE_ENCODE(7U, HSP_EVTSRC0R_EVT7SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_7_TRGIN9  = HAL_HSP_EVENT_SOURCE_ENCODE(7U, HSP_EVTSRC0R_EVT7SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_7_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(7U, HSP_EVTSRC0R_EVT7SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_7_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(7U, HSP_EVTSRC0R_EVT7SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 8 source Matrix ****************************************************/
  HAL_HSP_EVENT_8_STREAM3 = HAL_HSP_EVENT_SOURCE_ENCODE(8U, HSP_EVTSRC0R_EVT8SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_8_TRGIN0  = HAL_HSP_EVENT_SOURCE_ENCODE(8U, HSP_EVTSRC0R_EVT8SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_8_TRGIN5  = HAL_HSP_EVENT_SOURCE_ENCODE(8U, HSP_EVTSRC0R_EVT8SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_8_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(8U, HSP_EVTSRC0R_EVT8SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_8_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(8U, HSP_EVTSRC0R_EVT8SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 9 source Matrix ****************************************************/
  HAL_HSP_EVENT_9_STREAM0 = HAL_HSP_EVENT_SOURCE_ENCODE(9U, HSP_EVTSRC1R_EVT9SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_9_TRGIN1  = HAL_HSP_EVENT_SOURCE_ENCODE(9U, HSP_EVTSRC1R_EVT9SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_9_TRGIN6  = HAL_HSP_EVENT_SOURCE_ENCODE(9U, HSP_EVTSRC1R_EVT9SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_9_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(9U, HSP_EVTSRC1R_EVT9SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_9_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(9U, HSP_EVTSRC1R_EVT9SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 10 source Matrix ***************************************************/
  HAL_HSP_EVENT_10_STREAM1 = HAL_HSP_EVENT_SOURCE_ENCODE(10U, HSP_EVTSRC1R_EVT10SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_10_TRGIN2  = HAL_HSP_EVENT_SOURCE_ENCODE(10U, HSP_EVTSRC1R_EVT10SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_10_TRGIN7  = HAL_HSP_EVENT_SOURCE_ENCODE(10U, HSP_EVTSRC1R_EVT10SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_10_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(10U, HSP_EVTSRC1R_EVT10SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_10_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(10U, HSP_EVTSRC1R_EVT10SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 11 source Matrix ***************************************************/
  HAL_HSP_EVENT_11_STREAM2 = HAL_HSP_EVENT_SOURCE_ENCODE(11U, HSP_EVTSRC1R_EVT11SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_11_TRGIN3  = HAL_HSP_EVENT_SOURCE_ENCODE(11U, HSP_EVTSRC1R_EVT11SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_11_TRGIN8  = HAL_HSP_EVENT_SOURCE_ENCODE(11U, HSP_EVTSRC1R_EVT11SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_11_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(11U, HSP_EVTSRC1R_EVT11SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_11_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(11U, HSP_EVTSRC1R_EVT11SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 12 source Matrix ***************************************************/
  HAL_HSP_EVENT_12_STREAM3 = HAL_HSP_EVENT_SOURCE_ENCODE(12U, HSP_EVTSRC1R_EVT12SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_12_TRGIN4  = HAL_HSP_EVENT_SOURCE_ENCODE(12U, HSP_EVTSRC1R_EVT12SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_12_TRGIN9  = HAL_HSP_EVENT_SOURCE_ENCODE(12U, HSP_EVTSRC1R_EVT12SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_12_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(12U, HSP_EVTSRC1R_EVT12SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_12_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(12U, HSP_EVTSRC1R_EVT12SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 13 source Matrix ***************************************************/
  HAL_HSP_EVENT_13_STREAM0 = HAL_HSP_EVENT_SOURCE_ENCODE(13U, HSP_EVTSRC1R_EVT13SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_13_TRGIN0  = HAL_HSP_EVENT_SOURCE_ENCODE(13U, HSP_EVTSRC1R_EVT13SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_13_TRGIN5  = HAL_HSP_EVENT_SOURCE_ENCODE(13U, HSP_EVTSRC1R_EVT13SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_13_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(13U, HSP_EVTSRC1R_EVT13SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_13_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(13U, HSP_EVTSRC1R_EVT13SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 14 source Matrix ***************************************************/
  HAL_HSP_EVENT_14_STREAM1 = HAL_HSP_EVENT_SOURCE_ENCODE(14U, HSP_EVTSRC1R_EVT14SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_14_TRGIN1  = HAL_HSP_EVENT_SOURCE_ENCODE(14U, HSP_EVTSRC1R_EVT14SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_14_TRGIN6  = HAL_HSP_EVENT_SOURCE_ENCODE(14U, HSP_EVTSRC1R_EVT14SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_14_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(14U, HSP_EVTSRC1R_EVT14SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_14_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(14U, HSP_EVTSRC1R_EVT14SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 15 source Matrix ***************************************************/
  HAL_HSP_EVENT_15_STREAM2 = HAL_HSP_EVENT_SOURCE_ENCODE(15U, HSP_EVTSRC1R_EVT15SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_15_TRGIN2  = HAL_HSP_EVENT_SOURCE_ENCODE(15U, HSP_EVTSRC1R_EVT15SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_15_TRGIN7  = HAL_HSP_EVENT_SOURCE_ENCODE(15U, HSP_EVTSRC1R_EVT15SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_15_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(15U, HSP_EVTSRC1R_EVT15SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_15_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(15U, HSP_EVTSRC1R_EVT15SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 16 source Matrix ***************************************************/
  HAL_HSP_EVENT_16_STREAM3 = HAL_HSP_EVENT_SOURCE_ENCODE(16U, HSP_EVTSRC1R_EVT16SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_16_TRGIN3  = HAL_HSP_EVENT_SOURCE_ENCODE(16U, HSP_EVTSRC1R_EVT16SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_16_TRGIN8  = HAL_HSP_EVENT_SOURCE_ENCODE(16U, HSP_EVTSRC1R_EVT16SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_16_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(16U, HSP_EVTSRC1R_EVT16SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_16_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(16U, HSP_EVTSRC1R_EVT16SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 17 source Matrix ***************************************************/
  HAL_HSP_EVENT_17_STREAM0 = HAL_HSP_EVENT_SOURCE_ENCODE(17U, HSP_EVTSRC2R_EVT17SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_17_TRGIN4  = HAL_HSP_EVENT_SOURCE_ENCODE(17U, HSP_EVTSRC2R_EVT17SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_17_TRGIN9  = HAL_HSP_EVENT_SOURCE_ENCODE(17U, HSP_EVTSRC2R_EVT17SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_17_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(17U, HSP_EVTSRC2R_EVT17SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_17_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(17U, HSP_EVTSRC2R_EVT17SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 18 source Matrix ***************************************************/
  HAL_HSP_EVENT_18_STREAM1 = HAL_HSP_EVENT_SOURCE_ENCODE(18U, HSP_EVTSRC2R_EVT18SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_18_TRGIN0  = HAL_HSP_EVENT_SOURCE_ENCODE(18U, HSP_EVTSRC2R_EVT18SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_18_TRGIN5  = HAL_HSP_EVENT_SOURCE_ENCODE(18U, HSP_EVTSRC2R_EVT18SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_18_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(18U, HSP_EVTSRC2R_EVT18SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_18_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(18U, HSP_EVTSRC2R_EVT18SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 19 source Matrix ***************************************************/
  HAL_HSP_EVENT_19_STREAM2 = HAL_HSP_EVENT_SOURCE_ENCODE(19U, HSP_EVTSRC2R_EVT19SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_19_TRGIN1  = HAL_HSP_EVENT_SOURCE_ENCODE(19U, HSP_EVTSRC2R_EVT19SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_19_TRGIN6  = HAL_HSP_EVENT_SOURCE_ENCODE(19U, HSP_EVTSRC2R_EVT19SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_19_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(19U, HSP_EVTSRC2R_EVT19SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_19_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(19U, HSP_EVTSRC2R_EVT19SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 20 source Matrix ***************************************************/
  HAL_HSP_EVENT_20_STREAM3 = HAL_HSP_EVENT_SOURCE_ENCODE(20U, HSP_EVTSRC2R_EVT20SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_20_TRGIN2  = HAL_HSP_EVENT_SOURCE_ENCODE(20U, HSP_EVTSRC2R_EVT20SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_20_TRGIN7  = HAL_HSP_EVENT_SOURCE_ENCODE(20U, HSP_EVTSRC2R_EVT20SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_20_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(20U, HSP_EVTSRC2R_EVT20SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_20_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(20U, HSP_EVTSRC2R_EVT20SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 21 source Matrix ***************************************************/
  HAL_HSP_EVENT_21_STREAM0 = HAL_HSP_EVENT_SOURCE_ENCODE(21U, HSP_EVTSRC2R_EVT21SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_21_TRGIN3  = HAL_HSP_EVENT_SOURCE_ENCODE(21U, HSP_EVTSRC2R_EVT21SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_21_TRGIN8  = HAL_HSP_EVENT_SOURCE_ENCODE(21U, HSP_EVTSRC2R_EVT21SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_21_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(21U, HSP_EVTSRC2R_EVT21SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_21_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(21U, HSP_EVTSRC2R_EVT21SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
  /* Event 22 source Matrix ***************************************************/
  HAL_HSP_EVENT_22_STREAM1 = HAL_HSP_EVENT_SOURCE_ENCODE(22U, HSP_EVTSRC2R_EVT22SRC_Pos, HAL_HSP_EVENT_SRC_SEL_STREAM),
  HAL_HSP_EVENT_22_TRGIN4  = HAL_HSP_EVENT_SOURCE_ENCODE(22U, HSP_EVTSRC2R_EVT22SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_0),
  HAL_HSP_EVENT_22_TRGIN9  = HAL_HSP_EVENT_SOURCE_ENCODE(22U, HSP_EVTSRC2R_EVT22SRC_Pos, HAL_HSP_EVENT_SRC_SEL_TRGIN_1),
  HAL_HSP_EVENT_22_HSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(22U, HSP_EVTSRC2R_EVT22SRC_Pos, HAL_HSP_EVENT_SRC_SEL_HSEG),
  HAL_HSP_EVENT_22_CSEG    = HAL_HSP_EVENT_SOURCE_ENCODE(22U, HSP_EVTSRC2R_EVT22SRC_Pos, HAL_HSP_EVENT_SRC_SEL_CSEG),
} hal_hsp_event_source_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group6 HSP Stream Interface Types
  * @{
  */
/*! HAL HSP STREAM buffer identifier enumeration */
typedef enum
{
  HAL_HSP_STREAM_BUFFER_0 = 0U,
  HAL_HSP_STREAM_BUFFER_1 = 1U,
  HAL_HSP_STREAM_BUFFER_2 = 2U,
  HAL_HSP_STREAM_BUFFER_3 = 3U,
} hal_hsp_stream_buffer_t;

/*! HAL HSP STREAM buffer direction enumeration */
typedef enum
{
  /*! STREAM Buffer Direction RX (CPU to HSP) */
  HAL_HSP_STREAM_BUFFER_DIR_RX = 0U,

  /*! STREAM Buffer Direction TX (HSP to CPU) */
  HAL_HSP_STREAM_BUFFER_DIR_TX = 1U,
} hal_hsp_stream_buffer_direction_t;

/*! HAL HSP STREAM buffer synchronization state enumeration */
typedef enum
{
  /*! STREAM Buffer synchronization to disable */
  HAL_HSP_STREAM_BUFFER_SYNC_DISABLE = 0U,

  /*! STREAM Buffer synchronization to enable */
  HAL_HSP_STREAM_BUFFER_SYNC_ENABLE  = 1U,
} hal_hsp_stream_buffer_sync_state_t;

/*! HAL HSP STREAM integer to float status enumeration */
typedef enum
{
  /*! Conversion Integer to Float is disabled */
  HAL_HSP_STREAM_INT_TO_FLOAT_DISABLED = 0U,

  /*! Conversion Integer to float is enabled */
  HAL_HSP_STREAM_INT_TO_FLOAT_ENABLED   = HSP_BUFFCFGR_I2FEN,
} hal_hsp_stream_int_to_float_status_t;

/*! HAL HSP STREAM buffer configuration structure */
typedef struct
{
  /*! STREAM Buffer ID */
  hal_hsp_stream_buffer_t buffer_id;

  /*! STREAM Buffer direction TX or RX */
  hal_hsp_stream_buffer_direction_t direction;

  /*! Synchronize the STREAM Buffer with the STREAM Buffer +1 */
  hal_hsp_stream_buffer_sync_state_t sync_state;
} hal_hsp_stream_buffer_config_t;

/*! HAL HSP STREAM flag status enumeration */
typedef enum
{
  HAL_HSP_STREAM_FLAG_NOT_ACTIVE = 0U,  /*!< Flag not active */
  HAL_HSP_STREAM_FLAG_ACTIVE     = 1U   /*!< Flag active     */
} hal_hsp_stream_flag_status_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group7 HSP Trigger Input Interface Types
  * @{
  */
/*! HAL HSP TRGIN polarity enumeration */
typedef enum
{
  HAL_HSP_TRGIN_POLARITY_RISING  = 0U,
  HAL_HSP_TRGIN_POLARITY_FALLING = 1U,
} hal_hsp_trgin_polarity_t;

/*! HAL HSP hardware trigger input source selector enumeration */
typedef enum
{
  HAL_HSP1_TRGIN_GPDMA_CH15_TC  = 0U,  /*!< GPDMA Channel 15 TC */
  HAL_HSP1_TRGIN_GPDMA_CH14_TC  = 1U,  /*!< GPDMA Channel 14 TC */
  HAL_HSP1_TRGIN_GPDMA_CH13_TC  = 2U,  /*!< GPDMA Channel 13 TC */
  HAL_HSP1_TRGIN_GPDMA_CH12_TC  = 3U,  /*!< GPDMA Channel 12 TC */
  HAL_HSP1_TRGIN_EXTI0          = 4U,  /*!< EXTI0               */
  HAL_HSP1_TRGIN_NPU_HOST_INT_3 = 5U,  /*!< NPU host_int_3      */
  HAL_HSP1_TRGIN_TIM1_TRGO      = 6U,  /*!< tim1_trgo           */
  HAL_HSP1_TRGIN_TIM1_TRGO2     = 7U,  /*!< tim1_trgo2          */
  HAL_HSP1_TRGIN_TIM2_TRGO      = 8U,  /*!< tim2_trgo           */
  HAL_HSP1_TRGIN_TIM3_TRGO      = 9U,  /*!< tim3_trgo           */
  HAL_HSP1_TRGIN_TIM6_TRGO      = 10U, /*!< tim6_trgo           */
  HAL_HSP1_TRGIN_TIM7_TRGO      = 11U, /*!< tim7_trgo           */
  HAL_HSP1_TRGIN_TIM8_TRGO      = 12U, /*!< tim8_trgo           */
  HAL_HSP1_TRGIN_TIM8_TRGO2     = 13U, /*!< tim8_trgo2          */
  HAL_HSP1_TRGIN_TIM15_TRGO     = 14U, /*!< tim15_trgo          */
  HAL_HSP1_TRGIN_HPDMA_CH15_TC  = 15U, /*!< HPDMA Channel 15 TC */
  HAL_HSP1_TRGIN_HPDMA_CH14_TC  = 16U, /*!< HPDMA Channel 14 TC */
  HAL_HSP1_TRGIN_HPDMA_CH13_TC  = 17U, /*!< HPDMA Channel 13 TC */
  HAL_HSP1_TRGIN_HPDMA_CH12_TC  = 18U, /*!< HPDMA Channel 12 TC */
  HAL_HSP1_TRGIN_ADF1_SAD_DET   = 19U, /*!< ADF1_SAD_det        */

} hal_hsp_trgin_source_t;

/*! HAL HSP TRGIN status enumeration */
typedef enum
{
  /*! Trigger Input is disabled */
  HAL_HSP_TRGIN_DISABLED = 0U,

  /*! Trigger Input is enabled */
  HAL_HSP_TRGIN_ENABLED  = 1U,
} hal_hsp_trgin_status_t;

/*! HAL HSP TRGIN configuration structure */
typedef struct
{
  /*! Polarity of the Trigger Input Interface */
  hal_hsp_trgin_polarity_t polarity;

  /*! ID of the source signal selected */
  hal_hsp_trgin_source_t source;
} hal_hsp_trgin_config_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group8 HSP Processing Request Control Types
  * @{
  */
/*! HAL HSP PRC task synchronization source enumeration */
typedef enum
{
  HAL_HSP_PRC_TASK_SYNC_TCU_0 = 0U,
  HAL_HSP_PRC_TASK_SYNC_TCU_1 = 1U,
  HAL_HSP_PRC_TASK_SYNC_TCU_2 = 2U,
  HAL_HSP_PRC_TASK_SYNC_TCU_3 = 3U,
  HAL_HSP_PRC_TASK_SYNC_NONE  = 4U
} hal_hsp_prc_task_sync_source_t;

/*! HAL HSP PRC task configuration structure */
typedef struct
{
  /*! Event source */
  hal_hsp_event_source_t source;

  /*! Synchronize the event with the end of a task execution */
  hal_hsp_prc_task_sync_source_t sync;
} hal_hsp_prc_task_config_t;

/*! HAL HSP PRC lowest priority task status enumeration */
typedef enum
{
  HAL_HSP_PRC_LOWEST_PRIO_TASK_NONE    = 0U,
  HAL_HSP_PRC_LOWEST_PRIO_TASK_ONGOING = 1U
} hal_hsp_prc_lowest_priority_task_status_t;

/*! HAL HSP polling mode enumeration */
typedef enum
{
  /*! Polling is terminated when all selected events occurred */
  HAL_HSP_POLLING_FOR_ALL_EVENT = 0U,

  /*! Polling is terminated when at least one selected event occurred */
  HAL_HSP_POLLING_FOR_ANY_EVENT = 1U,
} hal_hsp_polling_mode_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group9 HSP Trigger Output Types
  * @{
  */
/*! HAL HSP TRGO trigger enumeration */
typedef enum
{
  HAL_HSP_TRGO_TRIGGER_0 = 0U,
  HAL_HSP_TRGO_TRIGGER_1 = 1U,
  HAL_HSP_TRGO_TRIGGER_2 = 2U,
  HAL_HSP_TRGO_TRIGGER_3 = 3U,
} hal_hsp_trgo_trigger_t;

/*! HAL HSP TRGO source enumeration */
typedef enum
{
  HAL_HSP_TRGO_SRC_NONE   = 0U,  /*!< Disabled */
  HAL_HSP_TRGO_SRC_STREAM = HSP_TRGOCFGR_TRGO0SRC_0,  /*!< Trigger from STREAM Interface */
  HAL_HSP_TRGO_SRC_SPE    = HSP_TRGOCFGR_TRGO0SRC_1,  /*!< Trigger from Signal Processor Engine Core */
  HAL_HSP_TRGO_SRC_TIMESTAMPCAPTURE = (HSP_TRGOCFGR_TRGO0SRC_0 | HSP_TRGOCFGR_TRGO0SRC_1),
  /*!< Trigger from TimeStamp Capture */
} hal_hsp_trgo_source_t;

/*! HAL HSP TRGO configuration structure */
typedef struct
{
  /*! TRGO output identifier */
  hal_hsp_trgo_trigger_t trigger_id;

  /*! TRGO source selection */
  hal_hsp_trgo_source_t source;
} hal_hsp_trgo_config_t;

/*! HAL HSP TRGO status enumeration */
typedef enum
{
  HAL_HSP_TRGO_DISABLED = 0U,
  HAL_HSP_TRGO_ENABLED  = HSP_ITFENR_TRGOEN,
} hal_hsp_trgo_status_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group10  HSP TimeStamp Capture Types
  * @{
  */
/*! HAL HSP TSC capture mode enumeration */
typedef enum
{
  HAL_HSP_TSC_CAPTURE_MODE_SPE_BREAKS       = HSP_CAPCR_CAPMOD_0,
  HAL_HSP_TSC_CAPTURE_MODE_TASK_NBR_CHANGES = HSP_CAPCR_CAPMOD_1,
  HAL_HSP_TSC_CAPTURE_MODE_PFCT_NBR_CHANGES = (HSP_CAPCR_CAPMOD_1 | HSP_CAPCR_CAPMOD_0),
} hal_hsp_tsc_capture_mode_t;

/*! HAL HSP TSC prescaler enumeration */
typedef enum
{
  HAL_HSP_TSC_PRESCALER_BYPASSED = 0U,
  HAL_HSP_TSC_PRESCALER_DIV2     = HSP_CAPCR_PRESC_0,
  HAL_HSP_TSC_PRESCALER_DIV4     = HSP_CAPCR_PRESC_1,
  HAL_HSP_TSC_PRESCALER_DIV8     = (HSP_CAPCR_PRESC_1 | HSP_CAPCR_PRESC_0),
  HAL_HSP_TSC_PRESCALER_DIV16    = HSP_CAPCR_PRESC_2,
  HAL_HSP_TSC_PRESCALER_DIV32    = (HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_0),
  HAL_HSP_TSC_PRESCALER_DIV64    = (HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_1),
  HAL_HSP_TSC_PRESCALER_DIV128   = (HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_1 | HSP_CAPCR_PRESC_0),
  HAL_HSP_TSC_PRESCALER_DIV256   = HSP_CAPCR_PRESC_3,
  HAL_HSP_TSC_PRESCALER_DIV512   = (HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_0),
  HAL_HSP_TSC_PRESCALER_DIV1024  = (HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_1),
  HAL_HSP_TSC_PRESCALER_DIV2048  = (HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_1 | HSP_CAPCR_PRESC_0),
  HAL_HSP_TSC_PRESCALER_DIV4096  = (HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_2),
  HAL_HSP_TSC_PRESCALER_DIV8192  = (HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_0),
  HAL_HSP_TSC_PRESCALER_DIV16384 = (HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_1),
  HAL_HSP_TSC_PRESCALER_DIV32768 = (HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_1 | HSP_CAPCR_PRESC_0),
} hal_hsp_tsc_prescaler_t;

/*! HAL HSP TSC free running counter state enumeration */
typedef enum
{
  HAL_HSP_TSC_FREE_COUNTER_DISABLE = 0U,
  HAL_HSP_TSC_FREE_COUNTER_ENABLE  = HSP_CAPCR_FRCNTEN
} hal_hsp_tsc_free_running_counter_state_t;

/*! HAL HSP TSC task filter enumeration */
typedef enum
{
  HAL_HSP_TSC_TASK_FILTER_NONE    = 0U,
  HAL_HSP_TSC_TASK_FILTER_TSKCMP0 = HSP_CAPCR_TSKFLT
} hal_hsp_tsc_task_filter_t;

/*! HAL HSP TSC configuration structure */
typedef struct
{
  /*! Division ratio in order to define the time stamp granularity (For Free Counter mode only) */
  hal_hsp_tsc_prescaler_t prescaler;

  /*! Enable the Free counter mode */
  hal_hsp_tsc_free_running_counter_state_t counter;

  /*! Enable the filtering for a task monitored by the Task Comparator Unit 0 */
  hal_hsp_tsc_task_filter_t filter;
} hal_hsp_tsc_config_t;

/*! HAL HSP TSC capture data status enumeration */
typedef enum
{
  HAL_HSP_TSC_CAPTURE_DATA_NOT_READY = 0U,
  HAL_HSP_TSC_CAPTURE_DATA_READY     = HSP_EVT_ISR_CAPRDYF,
} hal_hsp_tsc_capture_data_status_t;

/** HAL HSP TSC timestamp structure.
  * This type provides the raw 32-bit value read from CAPDR and 2 bitfield views:
  * - free_counter     : layout when HSP_CAPCR_FRCNTEN is set
  * - no_free_counter  : alternate layout when HSP_CAPCR_FRCNTEN is cleared
  */
typedef union hal_hsp_tsc_timestamp_u
{
  /*! Raw 32-bit value read from CAPDR register */
  uint32_t raw;

  /** CAPDR layout when FreeCounter is enabled (HSP_CAPCR_FRCNTEN=1)
      - TSTAMP  : [13:0]
      - IFHIST  : [21:14]
      - IFCNT   : [25:22]
      - TSKNB   : [31:26]
  */
  struct
  {
    uint32_t timestamp   : 14;
    uint32_t if_history  : 8;
    uint32_t if_counter  : 4;
    uint32_t task_number : 6;
  } free_counter;

  /** CAPDR alternate layout when FreeCounter is disabled (HSP_CAPCR_FRCNTEN=0)
      - ALT_IFHIST : [14:0]
      - reserved   : [15]
      - ALT_PFCTNB : [21:16]
      - ALT_IFCNT  : [25:22]
      - ALT_TSKNB  : [31:26]
  */
  struct
  {
    uint32_t if_history  : 15;
    uint32_t reserved0   : 1;
    uint32_t pfct_number : 6;
    uint32_t if_counter  : 4;
    uint32_t task_number : 6;
  } no_free_counter;
} hal_hsp_tsc_timestamp_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group11  HSP Buffer RAM Types
  * @{
  */
/*! HAL HSP BRAM conflict access counter status enumeration */
typedef enum
{
  HAL_HSP_BRAM_CONFLICT_ACC_CTR_DISABLED = 0U,
  HAL_HSP_BRAM_CONFLICT_ACC_CTR_ENABLED  = HSP_CAPCR_CCNTREN
} hal_hsp_bram_conflict_access_counter_status_t;

/*! HAL HSP BRAM bandwidth arbitration latency enumeration */
typedef enum
{
  HAL_HSP_BRAM_LATENCY_16_CYCLES = 0U,
  HAL_HSP_BRAM_LATENCY_8_CYCLES  = HSP_CR_BARB_0,
  HAL_HSP_BRAM_LATENCY_4_CYCLES  = HSP_CR_BARB_1
} hal_hsp_bram_latency_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group12  HSP Monitoring Types
  * @{
  */
/*! HAL HSP SNOOP group A signal enumeration */
typedef enum
{
  /*! No signal */
  HAL_HSP_SNOOP_GRPA_SIGNAL_NONE             = 0U,

  /*! Task Active bits [2:0] */
  HAL_HSP_SNOOP_GRPA_TASK_2_1_0              = HSP_SNPR_SNPSELA_0,

  /*! TRGIN/STREAM Buffer/ADCIN 0 */
  HAL_HSP_SNOOP_GRPA_TRGIN_BUFF_ADC          = (HSP_SNPR_SNPSELA_1 | HSP_SNPR_SNPSELA_0),

  /*! Timestamp Capture Processing function number bits [2:0] */
  HAL_HSP_SNOOP_GRPA_TSC_PFCTNB_2_1_0        = (HSP_SNPR_SNPSELA_2 << HSP_SNPR_SNPSELA_Pos),

  /*! Task Comparator 0 to 2 */
  HAL_HSP_SNOOP_GRPA_TSC_CMP_2_1_0           = (HSP_SNPR_SNPSELA_2 | HSP_SNPR_SNPSELA_0),

  /*! WakeUp, Signal Processor Engine Jump and Signal Processor Engine WFE */
  HAL_HSP_SNOOP_GRPA_EVTCWKUP_SPEJUMP_SPEWFE = (HSP_SNPR_SNPSELA_2 | HSP_SNPR_SNPSELA_1),

  /*! Priority Encoder bits [2:0] */
  HAL_HSP_SNOOP_GRPA_PE_2_1_0                = (HSP_SNPR_SNPSELA_2 | HSP_SNPR_SNPSELA_1 | HSP_SNPR_SNPSELA_0)
} hal_hsp_snoop_grpa_signal_t;

/*! HAL HSP SNOOP group B signal enumeration */
typedef enum
{
  /*! No signal */
  HAL_HSP_SNOOP_GRPB_SIGNAL_NONE              = 0U,

  /*! Task Active bits [5:3] */
  HAL_HSP_SNOOP_GRPB_TASK_5_4_3               = HSP_SNPR_SNPSELB_0,

  /*! Direct Command, CDEG & HSEG */
  HAL_HSP_SNOOP_GRPB_DCMD_CDEG_HDEG           = (HSP_SNPR_SNPSELB_1 | HSP_SNPR_SNPSELB_0),

  /*! Timestamp Capture Processing function number bits [5:3] */
  HAL_HSP_SNOOP_GRPB_TSC_PFCTNB_5_4_3         = HSP_SNPR_SNPSELB_2,

  /*! Task Comparator 3 */
  HAL_HSP_SNOOP_GRPB_TSC_CMP_3                = (HSP_SNPR_SNPSELB_2 | HSP_SNPR_SNPSELB_0),

  /*! Timestamp Capture Pulse on Call, IF and IF True instructions */
  HAL_HSP_SNOOP_GRPB_TSC_PULSE_CALL_IF_IFTRUE = (HSP_SNPR_SNPSELB_2 | HSP_SNPR_SNPSELB_1),

  /*! Priority Encoder bits [5:3] */
  HAL_HSP_SNOOP_GRPB_PE_5_4_3                 = (HSP_SNPR_SNPSELB_2 | HSP_SNPR_SNPSELB_1 | HSP_SNPR_SNPSELB_0)
} hal_hsp_snoop_grpb_signal_t;

/*! HAL_HSP SNOOP configuration structure */
typedef struct
{
  /*! SNOOP group A signal selection */
  hal_hsp_snoop_grpa_signal_t grpa_signal;

  /*! SNOOP group B signal selection */
  hal_hsp_snoop_grpb_signal_t grpb_signal;
} hal_hsp_snoop_config_t;

/*! HAL HSP BREAK output enumeration */
typedef enum
{
  HAL_HSP_BREAK_OUTPUT_0 = 0U,
  HAL_HSP_BREAK_OUTPUT_1 = 1U,
  HAL_HSP_BREAK_OUTPUT_2 = 2U,
  HAL_HSP_BREAK_OUTPUT_3 = 3U
} hal_hsp_break_output_t;

/*! HAL HSP BREAK output configuration structure */
typedef struct
{
  /*! BREAK output identifier */
  hal_hsp_break_output_t output_id;

  /*! Critical events mapped to the BREAK output */
  uint32_t critical_events;
} hal_hsp_break_output_config_t;

/*! HAL HSP BREAK debug single step status enumeration */
typedef enum
{
  HAL_HSP_BREAK_DBG_SINGLE_STEP_DISABLED = 0U,
  HAL_HSP_BREAK_DBG_SINGLE_STEP_ENABLED  = HSP_BKICFGR_SSEN
} hal_hsp_break_dbg_single_step_status_t;

/*! HAL HSP Signal Processor Engine event status enumeration */
typedef enum
{
  HAL_HSP_SPE_EVENT_RESET = 0U,
  HAL_HSP_SPE_EVENT_SET   = 1U
} hal_hsp_spe_event_status_t;

/*! HAL HSP Signal Processor Engine interrupt status enumeration */
typedef enum
{
  HAL_HSP_SPE_IT_DISABLED = 0U,
  HAL_HSP_SPE_IT_ENABLED  = 1U
} hal_hsp_spe_it_status_t;

#if defined(USE_HAL_HSP_PROCLIST_NOTIFICATION_IT) && (USE_HAL_HSP_PROCLIST_NOTIFICATION_IT == 1)
/*! HAL HSP Processing List interrupt status enumeration */
typedef enum
{
  HAL_HSP_PROCLIST_IT_DISABLED = 0U,
  HAL_HSP_PROCLIST_IT_ENABLED  = 1U
} hal_hsp_proclist_it_status_t;
#endif /* USE_HAL_HSP_PROCLIST_NOTIFICATION_IT*/

/*! HAL HSP Hardware error status enumeration */
typedef enum
{
  HAL_HSP_HW_ERROR_NONE  = 0U,
  HAL_HSP_HW_ERROR_MINOR = 1U,
  HAL_HSP_HW_ERROR_FAULT = 2U
} hal_hsp_hw_error_status_t;

/*! HAL HSP SmartClocking status enumeration */
typedef enum
{
  HAL_HSP_SMARTCLOCKING_DISABLED = 0U,
  HAL_HSP_SMARTCLOCKING_ENABLED  = 1U
} hal_hsp_smartclocking_status_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group14  HSP Hardware Capabilities
  * @{
  */
/*! HAL HSP Hardware Capabilities Structure definition */
typedef struct
{
  /*! BRAMAB base address */
  uint32_t bramab_base_address;

  /*! BRAMAB size in bytes */
  uint32_t bramab_size_byte;

  /*! BRAMA base address */
  uint32_t brama_base_address;

  /*! BRAMB base address */
  uint32_t bramb_base_address;

  /*! Direct Command identifier register address */
  __IOM uint32_t *p_dcmd_cmdid;

  /*! Direct Command parameter registers base address */
  __IOM uint32_t *p_dcmd_param;

  /*! Direct Command data pointer registers base address */
  __IOM uint32_t *p_dcmd_data;

  /*! CPU dedicated event generator register address */
  __IOM uint32_t *p_cdeg;
} hal_hsp_hw_info_t;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group15  HSP Handle
  * @{
  */
/*! HAL HSP instance enumeration */
typedef enum
{
  HAL_HSP1 = HSP1_BASE,  /*!< Peripheral instance HSP1 */
} hal_hsp_t;

/*! HAL HSP handle state enumeration */
typedef enum
{
  HAL_HSP_STATE_RESET          = 0UL,           /*!< HSP not yet initialized                                       */
  HAL_HSP_STATE_INIT           = (1UL << 31U),  /*!< HSP initialized but not yet configured                        */
  HAL_HSP_STATE_READY_TO_BOOT  = (1UL << 28U),  /*!< HSP DRAM Firmware loaded, Plugin can be loaded before booting */
  HAL_HSP_STATE_RUNNING        = (1UL << 27U),  /*!< HSP initialized, Firmware & Plugin Loaded and Boot completed  */
  HAL_HSP_STATE_FAULT          = (1UL << 26U)   /*!< HSP encountered an unrecoverable error and a recovery sequence
                                                     is needed */
} hal_hsp_state_t;

/*! HAL HSP Handle type definition */
typedef struct hal_hsp_handle_s hal_hsp_handle_t;

#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
/*! Pointer to a HSP callback function */
typedef void (*hal_hsp_cb_t)(hal_hsp_handle_t *hhsp);

/*! Pointer to a HSP callback function taking 1 parameter in addition to the handle */
typedef void (*hal_hsp_one_param_cb_t)(hal_hsp_handle_t *hhsp, uint32_t value);

/*! Pointer to a HSP callback function taking 1 hal_hsp_tsc_timestamp_t parameter in addition to the handle */
typedef void (*hal_hsp_tsc_cb_t)(hal_hsp_handle_t *hhsp, hal_hsp_tsc_timestamp_t timestamp);

/*! Pointer to a HSP Error callback function */
typedef void (*hal_hsp_error_cb_t)(hal_hsp_handle_t *hhsp,
                                   hal_hsp_hw_error_status_t err_status, uint32_t value1, uint32_t value2);

#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */

/*! HAL HSP handle structure */
struct hal_hsp_handle_s
{
  /*! HAL HSP instance */
  hal_hsp_t instance;

  /*! HSP global state */
  volatile hal_hsp_state_t global_state;

#if defined (USE_HAL_HSP_GET_LAST_ERRORS) && (USE_HAL_HSP_GET_LAST_ERRORS == 1)
  volatile uint32_t last_error_codes;  /*!< Errors limited to the last process
                                        This parameter can be a combination of @ref HSP_HAL_Error_Codes */
#endif /* USE_HAL_HSP_GET_LAST_ERRORS */
#if defined (USE_HAL_HSP_MSGBOX_GET_LAST_ERROR) && (USE_HAL_HSP_MSGBOX_GET_LAST_ERROR == 1)
  volatile uint32_t msgbox_last_error_code; /*!< Message Box last error code */
#endif /* USE_HAL_HSP_MSGBOX_GET_LAST_ERROR */

  /* CRAM/DRAM Memory region -------------------------------------------------*/
  /*! Free CRAM Size in bytes */
  uint32_t cram_free_size_byte;

  /* CNN Safe mode -----------------------------------------------------------*/
  /*! Store the status of Enabled Interface */
  uint32_t backup_enabled_itfs;

  /*! Store the status of Enabled Events */
  uint32_t backup_enabled_events;

  /*! Store the status of Enabled Event Interrupts */
  uint32_t backup_event_its;

  /*! Store the status of Enabled Processing Function Event Interrupts */
  uint32_t backup_pfctevt_its;

  /* Firmware Error Management -----------------------------------------------*/
  /*! Direct Command ID to clean the Firmware Error Code */
  uint32_t fwerr_dcmd_id;

  /* Interrupts callbacks ----------------------------------------------------*/
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
  /*! HSP Signal Processor Engine Run State callback function pointer */
  hal_hsp_one_param_cb_t p_spe_run_state_cb;

  /*! HSP Signal Processor Engine Floating Point Unit Saturation event callback function pointer */
  hal_hsp_cb_t p_spe_fpu_saturation_cb;

  /*! HSP PRC Task Completed callback function pointer */
  hal_hsp_cb_t p_prc_task_cplt_cb;

#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
  /*! HSP Timestamp Capture Data Ready callback function pointer */
  hal_hsp_tsc_cb_t p_tsc_timestamp_ready_cb;
#endif /* USE_HAL_HSP_TSC_IT */

#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  /*! HSP Task Comparator Unit Task Started callback function pointer */
  hal_hsp_one_param_cb_t p_tcu_task_started_cb;

  /*! HSP Task Comparator Unit Task Ended callback function pointer */
  hal_hsp_one_param_cb_t p_tcu_task_ended_cb;

  /*! HSP Task Overlap event callback function pointer */
  hal_hsp_cb_t p_tcu_task_overlap_cb;
#endif /* USE_HAL_HSP_TCU_IT */

#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
  /*! HSP STREAM Buffer Empty callback function pointer */
  hal_hsp_one_param_cb_t p_stream_buffer_empty_cb;

  /*! HSP STREAM Buffer Full callback function pointer */
  hal_hsp_one_param_cb_t p_stream_buffer_full_cb;
#endif /* USE_HAL_HSP_STREAM_IT */

#if defined(USE_HAL_HSP_PROCLIST_NOTIFICATION_IT) && (USE_HAL_HSP_PROCLIST_NOTIFICATION_IT == 1)
  /*! HSP Processing Function Event callback function pointer */
  hal_hsp_one_param_cb_t p_processing_event_cb;
#endif /* USE_HAL_HSP_PROCLIST_NOTIFICATION_IT */

  /*! HSP Error callback function pointer */
  hal_hsp_error_cb_t p_error_cb;
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */

#if defined (USE_HAL_HSP_USER_DATA) && (USE_HAL_HSP_USER_DATA == 1)
  /*! User Data Pointer  */
  const void *p_user_data;
#endif /* USE_HAL_HSP_USER_DATA */
};

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HSP_Exported_Functions HSP Exported Functions
  * @{
  */

/** @defgroup HSP_Exported_Functions_Group1  HSP Initialization and de-initialization functions
  * @{
  */
/* Init/DeInit functions ******************************************************/
hal_status_t HAL_HSP_Init(hal_hsp_handle_t *hhsp, hal_hsp_t instance);
void HAL_HSP_DeInit(hal_hsp_handle_t *hhsp);

/* Firmware/Plugin functions **************************************************/
hal_status_t HAL_HSP_LoadFirmware(hal_hsp_handle_t *hhsp,
                                  const uint8_t *p_cram_bin, uint32_t cram_size_byte,
                                  const uint8_t *p_dram_bin, uint32_t dram_size_byte);
hal_status_t HAL_HSP_LoadPlugin(hal_hsp_handle_t *hhsp, const uint8_t *p_plugin_bin, uint32_t size_byte);

/* Boot functions *************************************************************/
hal_status_t HAL_HSP_Boot(hal_hsp_handle_t *hhsp, const hal_hsp_boot_config_t *p_config, uint32_t *p_boot_error_code);
uint32_t HAL_HSP_GetFirmwareVersion(const hal_hsp_handle_t *hhsp);

void HAL_HSP_GetHWInfo(const hal_hsp_handle_t *hhsp, hal_hsp_hw_info_t *p_hw_info);

hal_hsp_t HAL_HSP_GetInstance(const hal_hsp_handle_t *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group2  HSP Command Management
  * @{
  A set of functions to communicate with the peripheral:
    - with the Direct Command interface for Accelerator Mode
    - with the Message Box interface for Sequencer Mode
    - with common Parameter interface to transmit Command parameters
  */
/* Direct Command interface ***************************************************/
/**
  * @brief  Write a Command into the Direct Command interface.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param  cmd_id  Command Identifier
  * @note  Optimized code function. It must be called when the handle state is set to HAL_HSP_STATE_RUNNING.
  */
__STATIC_FORCEINLINE void HAL_HSP_DCMD_WriteCommand(const hal_hsp_handle_t *hhsp, uint32_t cmd_id)
{
  HSP_TypeDef *p_hspx = (HSP_TypeDef *)(uint32_t)(hhsp->instance);
  STM32_WRITE_REG(p_hspx->DCMDIDR, cmd_id);
}

/**
  * @brief  Write a Data Pointer into the Direct Command interface.
  * @param  hhsp              Pointer to a @ref hal_hsp_handle_t.
  * @param  dcmd_data_ptr_id  Data Pointer Identifier
  * @param  data_address  Data Address
  * @note  Optimized code function. It must be called when the handle state is set to HAL_HSP_STATE_RUNNING.
  */
__STATIC_FORCEINLINE void HAL_HSP_DCMD_WriteDataPointer(const hal_hsp_handle_t *hhsp,
                                                        hal_hsp_dcmd_data_ptr_t dcmd_data_ptr_id, uint32_t data_address)
{
  __IOM uint32_t *p_reg = (uint32_t __IOM *) & (((HSP_TypeDef *)(uint32_t)(hhsp->instance))->DCMDPTR0);
  STM32_WRITE_REG(p_reg[(uint32_t)dcmd_data_ptr_id], data_address);
}

/**
  * @brief Get the status of Direct Command processing.
  * @param hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @return Direct Command processing status
  */
__STATIC_FORCEINLINE hal_hsp_dcmd_status_t HAL_HSP_DCMD_GetStatus(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx = (HSP_TypeDef *)(uint32_t)(hhsp->instance);

  return (hal_hsp_dcmd_status_t)(uint32_t)(STM32_READ_BIT(p_hspx->DCMDSR, HSP_DCMDSR_DCBSY));
}

/* Message Box interface ******************************************************/
hal_status_t HAL_HSP_MSGBOX_SendMessage(const hal_hsp_handle_t *hhsp, uint32_t message);

/**
  * @brief Get the Status of MSGBox Semaphore (CPU side).
  * @param hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @return Message Box Semaphore status
  */
__STATIC_FORCEINLINE hal_hsp_msgbox_semaphore_status_t HAL_HSP_MSGBOX_IsMessageAvailable(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx = (HSP_TypeDef *)(uint32_t)(hhsp->instance);

  return (hal_hsp_msgbox_semaphore_status_t)(uint32_t)(STM32_READ_BIT(p_hspx->H2CSEMR, HSP_H2CSEMR_H2CSEM));
}

/**
  * @brief Get the Message sent by the Signal Processor Engine for the CPU.
  * @param hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @note  Optimized code function. It must be called when the handle state is set to HAL_HSP_STATE_RUNNING.
  * @return  Signal Processor Engine Message value
  */
__STATIC_FORCEINLINE uint32_t HAL_HSP_MSGBOX_GetMessage(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx = (HSP_TypeDef *)(uint32_t)(hhsp->instance);

  return STM32_READ_REG(p_hspx->H2CMSGDR);
}

/**
  * @brief Acknowledge the MSGBOX Semaphore to inform the HSP that the CPU has read the message.
  * @param hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @note  Optimized code function. It must be called when the handle state is set to HAL_HSP_STATE_RUNNING.
  */
__STATIC_FORCEINLINE void HAL_HSP_MSGBOX_AckSemaphore(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx = (HSP_TypeDef *)(uint32_t)(hhsp->instance);

  STM32_SET_BIT(p_hspx->H2CSEMR, HSP_H2CSEMR_H2CSEM);

  /* If ITs are not enabled, the driver must clear the following flags:                       */
  /*  - HSP_EVT_ISR_H2CMRDYF  indicating a message is available for the CPU                   */
  /*  - HSP_EVT_ICR_C2HMFREEF indicating the MSGB is free for CPU to Signal Processor Engine  */
  STM32_WRITE_REG(p_hspx->EVT_ICR, (HSP_EVT_ICR_H2CMRDYC | HSP_EVT_ICR_C2HMFREEC));
}

/* Command Parameter interface ************************************************/
/**
  * @brief  Fill a parameter for any HSP command for DCMD or MSGBox interfaces.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @param  param_id  ID of parameter
  * @param  value     Parameter Value for the current Command ongoing.
  * @note  Optimized code function. It must be called when the handle state is set to HAL_HSP_STATE_RUNNING.
  */
__STATIC_FORCEINLINE void HAL_HSP_WriteParameter(const hal_hsp_handle_t *hhsp,
                                                 hal_hsp_param_t param_id, uint32_t value)
{
  __IOM uint32_t *p_reg = (uint32_t __IOM *) & (((HSP_TypeDef *)(uint32_t)(hhsp->instance))->PARAMR0);

  STM32_WRITE_REG(p_reg[(uint32_t)param_id], value);
}

/**
  * @brief  Return the value of a parameter.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @param  param_id  ID of parameter
  * @note  Optimized code function. It must be called when the handle state is set to HAL_HSP_STATE_RUNNING.
  * @return Value of the parameter.
  */
__STATIC_FORCEINLINE uint32_t HAL_HSP_ReadParameter(const hal_hsp_handle_t *hhsp, hal_hsp_param_t param_id)
{
  const __IOM uint32_t *p_reg = (uint32_t __IOM *) & (((HSP_TypeDef *)(uint32_t)(hhsp->instance))->PARAMR0);

  return STM32_READ_REG(p_reg[(uint32_t)param_id]);
}

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group3_2 HSP STREAM Interface
  * @{
  */
/* STREAM Interface ----------------------------------------------------------*/
hal_status_t HAL_HSP_STREAM_SetMultiConfig(const hal_hsp_handle_t *hhsp,
                                           const hal_hsp_stream_buffer_config_t *p_config_array,
                                           uint32_t config_array_size);
void HAL_HSP_STREAM_GetMultiConfig(const hal_hsp_handle_t *hhsp,
                                   hal_hsp_stream_buffer_config_t *p_config_array, uint32_t config_array_size);

hal_status_t HAL_HSP_STREAM_EnableIntToFloat(const hal_hsp_handle_t *hhsp);
hal_status_t HAL_HSP_STREAM_DisableIntToFloat(const hal_hsp_handle_t *hhsp);
hal_hsp_stream_int_to_float_status_t HAL_HSP_STREAM_IsEnabledIntToFloat(const hal_hsp_handle_t *hhsp);

hal_status_t HAL_HSP_STREAM_Start(const hal_hsp_handle_t *hhsp,
                                  uint32_t evt_interrupts, uint32_t err_interrupts);
hal_status_t HAL_HSP_STREAM_Stop(const hal_hsp_handle_t *hhsp);

/**
  * @brief  Check whether the selected HSP STREAM Buffer flag is set or not.
  * @param  hhsp  Pointer to a hal_hsp_handle_t.
  * @param  flag  specifies the HSP flag to check
  *         This parameter can be one of the following values:
  *            @arg HAL_HSP_FLAG_EVT_STREAM_BUFFER_0: HSP STREAM Buffer 0 Ready flag
  *            @arg HAL_HSP_FLAG_EVT_STREAM_BUFFER_1: HSP STREAM Buffer 1 Ready flag
  *            @arg HAL_HSP_FLAG_EVT_STREAM_BUFFER_2: HSP STREAM Buffer 2 Ready flag
  *            @arg HAL_HSP_FLAG_EVT_STREAM_BUFFER_3: HSP STREAM Buffer 3 Ready flag
  * @return STREAM Buffer flag status.
  */
__STATIC_INLINE hal_hsp_stream_flag_status_t HAL_HSP_STREAM_IsActiveFlag_Event(const hal_hsp_handle_t *hhsp,
                                                                               uint32_t flag)
{
  const HSP_TypeDef *p_hspx = (HSP_TypeDef *)(uint32_t)(hhsp->instance);

  return ((STM32_READ_BIT(p_hspx->EVT_ISR, flag) != 0U) ? HAL_HSP_STREAM_FLAG_ACTIVE : HAL_HSP_STREAM_FLAG_NOT_ACTIVE);
}

/**
  * @brief  Write a data into the STREAM Buffer.
  * @param  hhsp       Pointer to a hal_hsp_handle_t.
  * @param  stream_id  STREAM Buffer id.
  * @param  value  Value to be written.
  */
__STATIC_INLINE void HAL_HSP_STREAM_WriteBufferData(const hal_hsp_handle_t *hhsp,
                                                    hal_hsp_stream_buffer_t stream_id,
                                                    uint32_t value)
{
  HSP_TypeDef *p_hspx = (HSP_TypeDef *)(uint32_t)(hhsp->instance);
  STM32_WRITE_REG(p_hspx->BUFFDR[(uint32_t)stream_id], value);
}

/**
  * @brief  Read the value from the STREAM Buffer.
  * @param  hhsp       Pointer to a hal_hsp_handle_t.
  * @param  stream_id  STREAM Buffer id.
  * @return STREAM Buffer value.
  */
__STATIC_INLINE uint32_t HAL_HSP_STREAM_ReadBufferData(const hal_hsp_handle_t *hhsp,
                                                       hal_hsp_stream_buffer_t stream_id)
{
  const HSP_TypeDef *p_hspx = (HSP_TypeDef *)(uint32_t)(hhsp->instance);
  return STM32_READ_REG(p_hspx->BUFFDR[(uint32_t)stream_id]);
}

/**
  * @brief  Get a STREAM Buffer data register address.
  * @param  hhsp  Pointer to a hal_hsp_handle_t.
  * @param  id    Stream buffer id.
  * @retval STREAM Buffer data register address.
  */
__STATIC_INLINE __IOM uint32_t *HAL_HSP_STREAM_GetDataRegAddress(const hal_hsp_handle_t *hhsp,
                                                                 hal_hsp_stream_buffer_t id)
{
  return &(((HSP_TypeDef *)(uint32_t)(hhsp->instance))->BUFFDR[(uint32_t)id]);
}

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group3_3 HSP Trigger Input Interface
  * @{
  */
/* Trigger Input Interface ---------------------------------------------------*/
hal_status_t HAL_HSP_TRGIN_SetConfigTriggers(const hal_hsp_handle_t *hhsp, uint32_t trgin_ids,
                                             const hal_hsp_trgin_config_t *p_config);
void HAL_HSP_TRGIN_GetConfigTrigger(const hal_hsp_handle_t *hhsp, uint32_t trgin_id, hal_hsp_trgin_config_t *p_config);

hal_status_t HAL_HSP_TRGIN_EnableTriggers(const hal_hsp_handle_t *hhsp, uint32_t trgin_ids);
hal_status_t HAL_HSP_TRGIN_DisableTriggers(const hal_hsp_handle_t *hhsp, uint32_t trgin_ids);
hal_hsp_trgin_status_t HAL_HSP_TRGIN_IsEnabledTrigger(const hal_hsp_handle_t *hhsp, uint32_t trgin_id);

#if defined(USE_HAL_HSP_TRGIN_IT) && (USE_HAL_HSP_TRGIN_IT == 1)
hal_status_t HAL_HSP_TRGIN_EnableIT(const hal_hsp_handle_t *hhsp, uint32_t interrupts);
hal_status_t HAL_HSP_TRGIN_DisableIT(const hal_hsp_handle_t *hhsp, uint32_t interrupts);
#endif /* USE_HAL_HSP_TRGIN_IT */

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group3_4 HSP Processing Request Control
  * @{
  */
hal_status_t HAL_HSP_PRC_SetMultiTaskConfig(const hal_hsp_handle_t *hhsp,
                                            const hal_hsp_prc_task_config_t *p_config_array,
                                            uint32_t config_array_size);
void HAL_HSP_PRC_GetMultiTaskConfig(const hal_hsp_handle_t *hhsp,
                                    hal_hsp_prc_task_config_t *p_config_array, uint32_t config_array_size);

hal_status_t HAL_HSP_PRC_EnableEvents(const hal_hsp_handle_t *hhsp, uint32_t events);
hal_status_t HAL_HSP_PRC_DisableEvents(const hal_hsp_handle_t *hhsp, uint32_t events);
uint32_t HAL_HSP_PRC_GetActiveEvents(const hal_hsp_handle_t *hhsp);

/* API to run the execution of a Processing List with CSEG ********************/
hal_status_t HAL_HSP_PRC_SWRequestTask(const hal_hsp_handle_t *hhsp, uint32_t events);
hal_status_t HAL_HSP_PRC_PollForEvent(const hal_hsp_handle_t *hhsp, hal_hsp_polling_mode_t poll_mode,
                                      uint32_t events, uint32_t timeout_ms,
                                      uint32_t *p_events_status);

hal_status_t HAL_HSP_PRC_SWRequestLowestPriorityTask(const hal_hsp_handle_t *hhsp,
                                                     hal_hsp_task_t task_id, hal_hsp_prc_task_sync_source_t sync,
                                                     uint32_t interrupts);

hal_hsp_prc_lowest_priority_task_status_t HAL_HSP_PRC_GetSWRequestLowestPriorityStatusAndClearFlag(
  const hal_hsp_handle_t *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group4 HSP Power Consumption Control
  * @{
  */
/* Power Consumption Control **************************************************/
hal_status_t HAL_HSP_SMARTCLOCKING_Enable(const hal_hsp_handle_t *hhsp, uint32_t clocks);
hal_status_t HAL_HSP_SMARTCLOCKING_Disable(const hal_hsp_handle_t *hhsp, uint32_t clocks);
hal_hsp_smartclocking_status_t HAL_HSP_SMARTCLOCKING_IsEnabled(const hal_hsp_handle_t *hhsp, uint32_t clock);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group5 HSP Task Comparator management
  * @{
  */
/* Start/End of Task Detector ------------------------------------------------*/
hal_status_t HAL_HSP_TCU_StartComparator(const hal_hsp_handle_t *hhsp,
                                         hal_hsp_task_comparator_t tcu_id, hal_hsp_task_t task_id,
                                         uint32_t interrupts);
hal_status_t HAL_HSP_TCU_StopComparator(const hal_hsp_handle_t *hhsp, hal_hsp_task_comparator_t tcu_id);

/* Task Overlap Detector -----------------------------------------------------*/
hal_status_t HAL_HSP_TCU_StartOverlapDetector(const hal_hsp_handle_t *hhsp,
                                              hal_hsp_task_t lower_task_id,
                                              hal_hsp_task_t higher_task_id,
                                              uint32_t interrupts);
hal_status_t HAL_HSP_TCU_StopOverlapDetector(const hal_hsp_handle_t *hhsp);

/* Events/Interrupts Management ----------------------------------------------*/
hal_status_t HAL_HSP_TCU_PollForEvent(const hal_hsp_handle_t *hhsp,
                                      hal_hsp_polling_mode_t poll_mode, uint32_t flags,
                                      uint32_t timeout_ms, uint32_t *p_flags_status);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group6 HSP Trigger Output management
  * @{
  */
hal_status_t HAL_HSP_TRGO_SetMultiConfig(const hal_hsp_handle_t *hhsp,
                                         const hal_hsp_trgo_config_t *p_config_array, uint32_t config_array_size);
void HAL_HSP_TRGO_GetMultiConfig(const hal_hsp_handle_t *hhsp,
                                 hal_hsp_trgo_config_t *p_config_array, uint32_t config_array_size);
hal_status_t HAL_HSP_TRGO_Enable(const hal_hsp_handle_t *hhsp);
hal_status_t HAL_HSP_TRGO_Disable(const hal_hsp_handle_t *hhsp);
hal_hsp_trgo_status_t HAL_HSP_TRGO_IsEnabled(const hal_hsp_handle_t *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group7 HSP Timestamp Capture
  * @{
  */
hal_status_t HAL_HSP_TSC_SetConfig(const hal_hsp_handle_t *hhsp, const hal_hsp_tsc_config_t *p_config);
void HAL_HSP_TSC_GetConfig(const hal_hsp_handle_t *hhsp, hal_hsp_tsc_config_t *p_config);

hal_status_t HAL_HSP_TSC_Start(const hal_hsp_handle_t *hhsp, hal_hsp_tsc_capture_mode_t cap_mode,
                               uint32_t evt_its, uint32_t err_its);
hal_status_t HAL_HSP_TSC_Stop(const hal_hsp_handle_t *hhsp);

hal_hsp_tsc_capture_data_status_t HAL_HSP_TSC_IsTimeStampReady(const hal_hsp_handle_t *hhsp);
hal_hsp_tsc_timestamp_t HAL_HSP_TSC_GetTimeStamp(const hal_hsp_handle_t *hhsp);

/**
  * @brief  Get the TimeStamp Capture Data register address.
  * @param  hhsp  Pointer to a hal_hsp_handle_t.
  * @note   Reading this register clears automatically the related capture data ready flag.
  * @retval TSC register address.
  */
__STATIC_INLINE __IM uint32_t *HAL_HSP_TSC_GetCaptureDataRegAddress(const hal_hsp_handle_t *hhsp)
{
  return &(((HSP_TypeDef *)(uint32_t)(hhsp->instance))->CAPDR);
}

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group8 HSP Performance
  * @{
  */
/* BRAM Access Control -------------------------------------------------------*/
hal_status_t HAL_HSP_BRAM_EnableConflictAccessCounter(const hal_hsp_handle_t *hhsp);
hal_status_t HAL_HSP_BRAM_DisableConflictAccessCounter(const hal_hsp_handle_t *hhsp);
hal_hsp_bram_conflict_access_counter_status_t HAL_HSP_BRAM_IsEnabledConflictAccessCounter(const hal_hsp_handle_t *hhsp);
uint32_t HAL_HSP_BRAM_GetConflictAccessCounter(const hal_hsp_handle_t *hhsp);
hal_status_t HAL_HSP_BRAM_SetLatency(const hal_hsp_handle_t *hhsp, hal_hsp_bram_latency_t latency);
hal_hsp_bram_latency_t HAL_HSP_BRAM_GetLatency(const hal_hsp_handle_t *hhsp);

/* Signal Processor Engine Interrupts ----------------------------------------*/
hal_status_t HAL_HSP_SPE_EnableEventInterrupts(const hal_hsp_handle_t *hhsp, uint32_t events);
hal_status_t HAL_HSP_SPE_DisableEventInterrupts(const hal_hsp_handle_t *hhsp, uint32_t events);
hal_hsp_spe_it_status_t HAL_HSP_SPE_IsEnabledEventInterrupts(const hal_hsp_handle_t *hhsp, uint32_t event);

hal_hsp_spe_event_status_t HAL_HSP_SPE_GetEventStatusAndClearFlag(const hal_hsp_handle_t *hhsp, uint32_t event);

hal_status_t HAL_HSP_SPE_EnableErrorInterrupts(const hal_hsp_handle_t *hhsp, uint32_t errors);
hal_status_t HAL_HSP_SPE_DisableErrorInterrupts(const hal_hsp_handle_t *hhsp, uint32_t errors);
hal_hsp_spe_it_status_t HAL_HSP_SPE_IsEnabledErrorInterrupts(const hal_hsp_handle_t *hhsp, uint32_t error);

hal_hsp_hw_error_status_t HAL_HSP_ExecErrorHandler(hal_hsp_handle_t *hhsp, uint32_t *p_error_info);
hal_status_t HAL_HSP_CleanFirmwareErrorCode(const hal_hsp_handle_t *hhsp);
uint32_t HAL_HSP_GetFirmwareErrorCode(const hal_hsp_handle_t *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group9 HSP Snoop
  * @{
  */
hal_status_t HAL_HSP_SNOOP_SetSignals(const hal_hsp_handle_t *hhsp, const hal_hsp_snoop_config_t *p_config);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group10 HSP Break Interface
  * @{
  */
hal_status_t HAL_HSP_BREAK_SetMultiConfigOutput(const hal_hsp_handle_t *hhsp,
                                                const hal_hsp_break_output_config_t *p_config_array,
                                                uint32_t config_array_size);
void HAL_HSP_BREAK_GetMultiConfigOutput(const hal_hsp_handle_t *hhsp,
                                        hal_hsp_break_output_config_t *p_config_array, uint32_t config_array_size);

hal_status_t HAL_HSP_BREAK_SetDebugEvents(const hal_hsp_handle_t *hhsp, uint32_t events);
uint32_t HAL_HSP_BREAK_GetDebugEvents(const hal_hsp_handle_t *hhsp);
hal_status_t HAL_HSP_BREAK_EnableDebugSingleStep(const hal_hsp_handle_t *hhsp);
hal_status_t HAL_HSP_BREAK_DisableDebugSingleStep(const hal_hsp_handle_t *hhsp);
hal_hsp_break_dbg_single_step_status_t HAL_HSP_BREAK_IsEnabledDebugSingleStep(const hal_hsp_handle_t *hhsp);
hal_status_t HAL_HSP_BREAK_ResumeDebugEvents(const hal_hsp_handle_t *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group11 HSP Protection
  * @{
  */
hal_status_t HAL_HSP_Lock(const hal_hsp_handle_t *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group12 HSP CNN Safe Mode Execution
  * @{
  */
hal_status_t HAL_HSP_CNN_EnterSafeMode(hal_hsp_handle_t *hhsp);
hal_status_t HAL_HSP_CNN_ExitSafeMode(const hal_hsp_handle_t *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group13 HSP Processing List management
  * @{
  */
/* Processing Function Notification Management */
/* API to manage the 32 flags for Process */
hal_status_t HAL_HSP_PROCLIST_PollForNotification(const hal_hsp_handle_t *hhsp,
                                                  hal_hsp_polling_mode_t poll_mode, uint32_t pfct_events,
                                                  uint32_t timeout_ms, uint32_t *p_pfct_evts_status);
#if defined(USE_HAL_HSP_PROCLIST_NOTIFICATION_IT) && (USE_HAL_HSP_PROCLIST_NOTIFICATION_IT == 1)
hal_status_t HAL_HSP_PROCLIST_EnableIT(const hal_hsp_handle_t *hhsp, uint32_t interrupts);
hal_status_t HAL_HSP_PROCLIST_DisableIT(const hal_hsp_handle_t *hhsp, uint32_t interrupts);
hal_hsp_proclist_it_status_t HAL_HSP_PROCLIST_IsEnabledIT(const hal_hsp_handle_t *hhsp, uint32_t interrupt);
#endif /* USE_HAL_HSP_PROCLIST_NOTIFICATION_IT */

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group14 HSP IRQ Handler and Callbacks functions
  * @{
  */
/* Global IRQ Handler *********************************************************/
void HAL_HSP_IRQHandler(hal_hsp_handle_t *hhsp);

/* Event IRQ Handlers and Callbacks *******************************************/
void HAL_HSP_EVT_IRQHandler(hal_hsp_handle_t *hhsp);

void HAL_HSP_PRC_TaskCpltCallback(hal_hsp_handle_t *hhsp);
void HAL_HSP_SPE_FPUSaturationCallback(hal_hsp_handle_t *hhsp);
void HAL_HSP_SPE_RunStateCallback(hal_hsp_handle_t *hhsp, uint32_t state);
#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
void HAL_HSP_STREAM_BufferEmptyCallback(hal_hsp_handle_t *hhsp, uint32_t buffers_mask);
void HAL_HSP_STREAM_BufferFullCallback(hal_hsp_handle_t *hhsp, uint32_t buffers_mask);
#endif /* USE_HAL_HSP_STREAM_IT */
#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
void HAL_HSP_TCU_TaskStartedCallback(hal_hsp_handle_t *hhsp, uint32_t comparators_mask);
void HAL_HSP_TCU_TaskEndedCallback(hal_hsp_handle_t *hhsp, uint32_t comparators_mask);
void HAL_HSP_TCU_TaskOverlapCallback(hal_hsp_handle_t *hhsp);
#endif /* USE_HAL_HSP_TCU_IT */
#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
void HAL_HSP_TSC_TimestampReadyCallback(hal_hsp_handle_t *hhsp, hal_hsp_tsc_timestamp_t timestamp);
#endif /* USE_HAL_HSP_TSC_IT */

/* Error IRQ Handlers and Callbacks *******************************************/
void HAL_HSP_ERR_IRQHandler(hal_hsp_handle_t *hhsp);
void HAL_HSP_ErrorCallback(hal_hsp_handle_t *hhsp, hal_hsp_hw_error_status_t error_status,
                           uint32_t fw_error_code, uint32_t error_inf_mask);

/* Firmware Event IRQ Handlers and Callbacks **********************************/
#if defined(USE_HAL_HSP_PROCLIST_NOTIFICATION_IT) && (USE_HAL_HSP_PROCLIST_NOTIFICATION_IT == 1)
void HAL_HSP_FWEVT_IRQHandler(hal_hsp_handle_t *hhsp);
void HAL_HSP_ProcessingEventCallback(hal_hsp_handle_t *hhsp, uint32_t events_mask);
#endif /* USE_HAL_HSP_PROCLIST_NOTIFICATION_IT */

#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions ************************************/
hal_status_t HAL_HSP_RegisterPRC_TaskCpltCallback(hal_hsp_handle_t *hhsp,
                                                  hal_hsp_cb_t p_callback);
hal_status_t HAL_HSP_RegisterSPE_FPUSaturationCallback(hal_hsp_handle_t *hhsp,
                                                       hal_hsp_cb_t p_callback);
hal_status_t HAL_HSP_RegisterSPE_RunStateCallback(hal_hsp_handle_t *hhsp,
                                                  hal_hsp_one_param_cb_t p_callback);
#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
hal_status_t HAL_HSP_RegisterSTREAM_BufferEmptyCallback(hal_hsp_handle_t *hhsp,
                                                        hal_hsp_one_param_cb_t p_callback);
hal_status_t HAL_HSP_RegisterSTREAM_BufferFullCallback(hal_hsp_handle_t *hhsp,
                                                       hal_hsp_one_param_cb_t p_callback);
#endif /* USE_HAL_HSP_STREAM_IT */
#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
hal_status_t HAL_HSP_RegisterTCU_TaskOverlapCallback(hal_hsp_handle_t *hhsp,
                                                     hal_hsp_cb_t p_callback);
hal_status_t HAL_HSP_RegisterTCU_TaskStartedCallback(hal_hsp_handle_t *hhsp,
                                                     hal_hsp_one_param_cb_t p_callback);
hal_status_t HAL_HSP_RegisterTCU_TaskEndedCallback(hal_hsp_handle_t *hhsp,
                                                   hal_hsp_one_param_cb_t p_callback);
#endif /* USE_HAL_HSP_TCU_IT */
#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
hal_status_t HAL_HSP_RegisterTSC_TimestampReadyCallback(hal_hsp_handle_t *hhsp,
                                                        hal_hsp_tsc_cb_t p_callback);
#endif /* USE_HAL_HSP_TSC_IT */
hal_status_t HAL_HSP_RegisterErrorCallback(hal_hsp_handle_t *hhsp, hal_hsp_error_cb_t p_callback);
#if defined(USE_HAL_HSP_PROCLIST_NOTIFICATION_IT) && (USE_HAL_HSP_PROCLIST_NOTIFICATION_IT == 1)
hal_status_t HAL_HSP_RegisterProcessingEventCallback(hal_hsp_handle_t *hhsp,
                                                     hal_hsp_one_param_cb_t p_callback);
#endif /* USE_HAL_HSP_PROCLIST_NOTIFICATION_IT */
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group15  Peripheral State and Error functions
  * @{
  */
hal_hsp_state_t HAL_HSP_GetState(const hal_hsp_handle_t *hhsp);
uint32_t HAL_HSP_GetCRAMFreeSizeByte(const hal_hsp_handle_t *hhsp);
#if defined(USE_HAL_HSP_GET_LAST_ERRORS) && (USE_HAL_HSP_GET_LAST_ERRORS == 1)
uint32_t HAL_HSP_GetLastErrorCodes(const hal_hsp_handle_t *hhsp);
#endif /* USE_HAL_HSP_GET_LAST_ERRORS */
#if defined(USE_HAL_HSP_MSGBOX_GET_LAST_ERROR) && (USE_HAL_HSP_MSGBOX_GET_LAST_ERROR == 1)
uint32_t HAL_HSP_GetMsgBoxLastErrorCode(const hal_hsp_handle_t *hhsp);
#endif /* USE_HAL_HSP_MSGBOX_GET_LAST_ERROR */

/**
  * @}
  */

#if defined(USE_HAL_HSP_USER_DATA) && (USE_HAL_HSP_USER_DATA == 1)
/** @defgroup HSP_Exported_Functions_Group16 Set/Get user data
  * @{
  */
void HAL_HSP_SetUserData(hal_hsp_handle_t *hhsp, const void *p_user_data);
const void *HAL_HSP_GetUserData(const hal_hsp_handle_t *hhsp);
/**
  * @}
  */

#endif /* USE_HAL_HSP_USER_DATA */
/**
  * @}
  */

/**
  * @}
  */

#endif /* HSP1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7Pxx_HAL_HSP_H */
