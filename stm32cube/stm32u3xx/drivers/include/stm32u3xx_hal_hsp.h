/**
  ******************************************************************************
  * @file    stm32u3xx_hal_hsp.h
  * @author  MCD Application Team
  * @brief   Header file of HSP HAL module.
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
#ifndef STM32U3xx_HAL_HSP_H
#define STM32U3xx_HAL_HSP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal_def.h"

/** @addtogroup STM32U3xx_HAL_Driver
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

/** HSP1 register address for PARAMR0 */
#define HAL_HSP1_PARAMR0_ADDRESS   ((volatile uint32_t *)(HSP1_PARAMR0_BASE))
/** HSP1 register address for PARAMR1 */
#define HAL_HSP1_PARAMR1_ADDRESS   ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000004UL))
/** HSP1 register address for PARAMR2 */
#define HAL_HSP1_PARAMR2_ADDRESS   ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000008UL))
/** HSP1 register address for PARAMR3 */
#define HAL_HSP1_PARAMR3_ADDRESS   ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x000000000CUL))
/** HSP1 register address for PARAMR4 */
#define HAL_HSP1_PARAMR4_ADDRESS   ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000010UL))
/** HSP1 register address for PARAMR5 */
#define HAL_HSP1_PARAMR5_ADDRESS   ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000014UL))
/** HSP1 register address for PARAMR6 */
#define HAL_HSP1_PARAMR6_ADDRESS   ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000018UL))
/** HSP1 register address for PARAMR7 */
#define HAL_HSP1_PARAMR7_ADDRESS   ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x000000001CUL))
/** HSP1 register address for PARAMR8 */
#define HAL_HSP1_PARAMR8_ADDRESS   ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000020UL))
/** HSP1 register address for PARAMR9 */
#define HAL_HSP1_PARAMR9_ADDRESS   ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000024UL))
/** HSP1 register address for PARAMR10 */
#define HAL_HSP1_PARAMR10_ADDRESS  ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000028UL))
/** HSP1 register address for PARAMR11 */
#define HAL_HSP1_PARAMR11_ADDRESS  ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x000000002CUL))
/** HSP1 register address for PARAMR12 */
#define HAL_HSP1_PARAMR12_ADDRESS  ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000030UL))
/** HSP1 register address for PARAMR13 */
#define HAL_HSP1_PARAMR13_ADDRESS  ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000034UL))
/** HSP1 register address for PARAMR14 */
#define HAL_HSP1_PARAMR14_ADDRESS  ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x0000000038UL))
/** HSP1 register address for PARAMR15 */
#define HAL_HSP1_PARAMR15_ADDRESS  ((volatile uint32_t *)(HSP1_PARAMR0_BASE + 0x000000003CUL))

/** HSP1 register address for DCMDPTR0 */
#define HAL_HSP1_DCMDPTR0_ADDRESS  ((volatile uint32_t *)(HSP1_DCMDPTR0_BASE))
/** HSP1 register address for DCMDPTR1 */
#define HAL_HSP1_DCMDPTR1_ADDRESS  ((volatile uint32_t *)(HSP1_DCMDPTR0_BASE + 0x0000000004UL))
/** HSP1 register address for DCMDPTR2 */
#define HAL_HSP1_DCMDPTR2_ADDRESS  ((volatile uint32_t *)(HSP1_DCMDPTR0_BASE + 0x0000000008UL))
/** HSP1 register address for DCMDIDR */
#define HAL_HSP1_DCMDIDR_ADDRESS   ((volatile uint32_t *)(HSP1_DCMDIDR_BASE))

/**
  * @}
  */

/** @defgroup HSP_HAL_Error_Codes  HSP HAL Error Codes
  * @{
  */
#define HAL_HSP_ERROR_NONE              (0UL)         /*!< No error                              */
#define HAL_HSP_ERROR_INVALID_PARAM     (1UL << 1U)   /*!< Invalid parameter                     */
#define HAL_HSP_ERROR_INVALID_CALLBACK  (1UL << 2U)   /*!< Invalid Callback ID                   */
#define HAL_HSP_ERROR_BOOT              (1UL << 3U)   /*!< Boot error: code returned in handle   */
#define HAL_HSP_ERROR_FIRMWARE          (1UL << 4U)   /*!< Firmware Error: see @ref HSP_Firmware_Error_Codes */

#define HAL_HSP_ERROR_TRGIN_OVR         (1UL << 10U)  /*!< TRGIN Overrun */
#define HAL_HSP_ERROR_BUFFER_UDR_OR_OVR (1UL << 11U)  /*!< STREAM Buffer Overrun or Underrun */
#define HAL_HSP_ERROR_CAPTURE_OVR       (1UL << 12U)  /*!< TIMESTAMP Capture Overrun         */
#define HAL_HSP_ERROR_SCHEDULER         (1UL << 13U)  /*!< SPE Scheduler Error               */
#define HAL_HSP_ERROR_BREAK_IN          (1UL << 14U)  /*!< Break Input Arrival               */
#define HAL_HSP_ERROR_HDEG_OVR          (1UL << 15U)  /*!< HDEG Overrun                      */
#define HAL_HSP_ERROR_OPCODE_INVALID    (1UL << 16U)  /*!< Firmware Invalid OpCode           */
#define HAL_HSP_ERROR_SPE_ACCESS        (1UL << 17U)  /*!< SPE Access Error                  */
#define HAL_HSP_ERROR_FPU               (1UL << 18U)  /*!< FPU Error                         */

/** HAL HSP All Hardware Errors constant */
#define HAL_HSP_ERROR_HW_ALL  \
  (HAL_HSP_ERROR_TRGIN_OVR   | HAL_HSP_ERROR_BUFFER_UDR_OR_OVR | HAL_HSP_ERROR_CAPTURE_OVR  \
   | HAL_HSP_ERROR_SCHEDULER | HAL_HSP_ERROR_BREAK_IN          | HAL_HSP_ERROR_HDEG_OVR     \
   | HAL_HSP_ERROR_OPCODE_INVALID | HAL_HSP_ERROR_SPE_ACCESS   | HAL_HSP_ERROR_FPU)

/**
  * @}
  */

/** @defgroup HSP_Firmware_Error_Codes  HSP Firmware Error Codes
  * @{
  */
#define HAL_HSP_FW_ERROR_PL_EMPTY      (5U << HSP_CR_BSTAT_Pos) /*!< Firmware tries to run an empty Processing list */
#define HAL_HSP_FW_ERROR_SUPERVISOR    (6U << HSP_CR_BSTAT_Pos) /*!< Bad Supervisor Command */
#define HAL_HSP_FW_ERROR_CROM_VERSION  (9U << HSP_CR_BSTAT_Pos) /*!< CROM ID Error: not in line with CRAM code */

/**
  * @}
  */

/** @defgroup HSP_Smart_Clocking_Values  HSP Smart Clocking Value
  * @{
  */
#define HAL_HSP_SMARTCLOCKING_CTRL  HSP_CR_CTRLCGDIS /*!< ID for HSP SmartClocking of CTRL block */
#define HAL_HSP_SMARTCLOCKING_SPE   HSP_CR_SPECGDIS  /*!< ID for HSP SmartClocking of SPE block  */
#define HAL_HSP_SMARTCLOCKING_MMC   HSP_CR_MMCCGDIS  /*!< ID for HSP SmartClocking of MMC block  */

/** HAL HSP SmartClocking mask of all blocks */
#define HAL_HSP_SMARTCLOCKING_ALL  (HAL_HSP_SMARTCLOCKING_CTRL | HAL_HSP_SMARTCLOCKING_SPE | HAL_HSP_SMARTCLOCKING_MMC)

/**
  * @}
  */

/** @defgroup HSP_TRGIN_ID  HSP Trigger Input Identifiers
  * @{
  */
#define HAL_HSP_TRGIN_0  HSP_ITFENR_TRGI0EN  /*!< ID of HSP TRGIN interface 0 */
#define HAL_HSP_TRGIN_1  HSP_ITFENR_TRGI1EN  /*!< ID of HSP TRGIN interface 1 */
#define HAL_HSP_TRGIN_2  HSP_ITFENR_TRGI2EN  /*!< ID of HSP TRGIN interface 2 */
#define HAL_HSP_TRGIN_3  HSP_ITFENR_TRGI3EN  /*!< ID of HSP TRGIN interface 3 */
#define HAL_HSP_TRGIN_4  HSP_ITFENR_TRGI4EN  /*!< ID of HSP TRGIN interface 4 */
#define HAL_HSP_TRGIN_5  HSP_ITFENR_TRGI5EN  /*!< ID of HSP TRGIN interface 5 */
#define HAL_HSP_TRGIN_6  HSP_ITFENR_TRGI6EN  /*!< ID of HSP TRGIN interface 6 */
#define HAL_HSP_TRGIN_7  HSP_ITFENR_TRGI7EN  /*!< ID of HSP TRGIN interface 7 */
#define HAL_HSP_TRGIN_8  HSP_ITFENR_TRGI8EN  /*!< ID of HSP TRGIN interface 8 */
#define HAL_HSP_TRGIN_9  HSP_ITFENR_TRGI9EN  /*!< ID of HSP TRGIN interface 9 */

/** HAL HSP TRGIN mask of all interfaces */
#define HAL_HSP_TRGIN_ALL                                                                     \
  (HAL_HSP_TRGIN_0   | HAL_HSP_TRGIN_1 | HAL_HSP_TRGIN_2 | HAL_HSP_TRGIN_3 | HAL_HSP_TRGIN_4  \
   | HAL_HSP_TRGIN_5 | HAL_HSP_TRGIN_6 | HAL_HSP_TRGIN_7 | HAL_HSP_TRGIN_8 | HAL_HSP_TRGIN_9)

/**
  * @}
  */

/** @defgroup HSP_EVENT_Constants HSP Event Constants
  * @{
  */
/** Event Priority bitfield position in enumerate @ref HAL_HSP_EVENT_SourceTypeDef */
#define HAL_HSP_EVENT_PRIO_POS    (26U)

/** Event Priority bitfield mask in enumerate @ref HAL_HSP_EVENT_SourceTypeDef */
#define HAL_HSP_EVENT_PRIO_MSK    (0x1FU << HAL_HSP_EVENT_PRIO_POS)

/** Event Source bitfield position in enumerate @ref HAL_HSP_EVENT_SourceTypeDef */
#define HAL_HSP_EVENT_SOURCE_POS  (0U)

/** Event Source bitfield mask in enumerate @ref HAL_HSP_EVENT_SourceTypeDef */
#define HAL_HSP_EVENT_SOURCE_MSK  (0x7U << HAL_HSP_EVENT_SOURCE_POS)

#define HAL_HSP_EVENT_1   HSP_EVTENR_EVTEN_0  /*!< ID of HSP EVENT 1 */
#define HAL_HSP_EVENT_2   HSP_EVTENR_EVTEN_1  /*!< ID of HSP EVENT 2 */
#define HAL_HSP_EVENT_3   HSP_EVTENR_EVTEN_2  /*!< ID of HSP EVENT 3 */
#define HAL_HSP_EVENT_4   HSP_EVTENR_EVTEN_3  /*!< ID of HSP EVENT 4 */
#define HAL_HSP_EVENT_5   HSP_EVTENR_EVTEN_4  /*!< ID of HSP EVENT 5 */
#define HAL_HSP_EVENT_6   HSP_EVTENR_EVTEN_5  /*!< ID of HSP EVENT 6 */
#define HAL_HSP_EVENT_7   HSP_EVTENR_EVTEN_6  /*!< ID of HSP EVENT 7 */
#define HAL_HSP_EVENT_8   HSP_EVTENR_EVTEN_7  /*!< ID of HSP EVENT 8 */
#define HAL_HSP_EVENT_9   HSP_EVTENR_EVTEN_8  /*!< ID of HSP EVENT 9 */
#define HAL_HSP_EVENT_10  HSP_EVTENR_EVTEN_9  /*!< ID of HSP EVENT 10 */
#define HAL_HSP_EVENT_11  HSP_EVTENR_EVTEN_10 /*!< ID of HSP EVENT 11 */
#define HAL_HSP_EVENT_12  HSP_EVTENR_EVTEN_11 /*!< ID of HSP EVENT 12 */
#define HAL_HSP_EVENT_13  HSP_EVTENR_EVTEN_12 /*!< ID of HSP EVENT 13 */
#define HAL_HSP_EVENT_14  HSP_EVTENR_EVTEN_13 /*!< ID of HSP EVENT 14 */
#define HAL_HSP_EVENT_15  HSP_EVTENR_EVTEN_14 /*!< ID of HSP EVENT 15 */
#define HAL_HSP_EVENT_16  HSP_EVTENR_EVTEN_15 /*!< ID of HSP EVENT 16 */
#define HAL_HSP_EVENT_17  HSP_EVTENR_EVTEN_16 /*!< ID of HSP EVENT 17 */
#define HAL_HSP_EVENT_18  HSP_EVTENR_EVTEN_17 /*!< ID of HSP EVENT 18 */
#define HAL_HSP_EVENT_19  HSP_EVTENR_EVTEN_18 /*!< ID of HSP EVENT 19 */
#define HAL_HSP_EVENT_20  HSP_EVTENR_EVTEN_19 /*!< ID of HSP EVENT 20 */
#define HAL_HSP_EVENT_21  HSP_EVTENR_EVTEN_20 /*!< ID of HSP EVENT 21 */
#define HAL_HSP_EVENT_22  HSP_EVTENR_EVTEN_21 /*!< ID of HSP EVENT 22 */

/** HAL HSP Mask of all HSP Events */
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

/** @defgroup HSP_TRGIN_Flags HSP TRGIN Flags
  * @{
  */
#define HAL_HSP_FLAG_ERR_TRGIN_OVR     HSP_ERR_ISR_TRGIOVRF  /*!< TRGIN Error Overrun flag */

/**
  * @}
  */

/** @defgroup HSP_Task_Comparator_Flags HSP Task Comparator Flags
  * @{
  */
#define HAL_HSP_FLAG_EVT_TCU_OVERLAP              (HSP_EVT_ISR_TOVLPF)   /*!< Task Overlap flag          */
#define HAL_HSP_FLAG_EVT_TCU_COMP0_START_OF_TASK  (HSP_EVT_ISR_SOTECP0F) /*!< Task Started flag of TCU 0 */
#define HAL_HSP_FLAG_EVT_TCU_COMP1_START_OF_TASK  (HSP_EVT_ISR_SOTECP1F) /*!< Task Started flag of TCU 1 */
#define HAL_HSP_FLAG_EVT_TCU_COMP2_START_OF_TASK  (HSP_EVT_ISR_SOTECP2F) /*!< Task Started flag of TCU 2 */
#define HAL_HSP_FLAG_EVT_TCU_COMP3_START_OF_TASK  (HSP_EVT_ISR_SOTECP3F) /*!< Task Started flag of TCU 3 */
#define HAL_HSP_FLAG_EVT_TCU_COMP0_END_OF_TASK    (HSP_EVT_ISR_SOTECP0F) /*!< Task Ended flag of TCU 0   */
#define HAL_HSP_FLAG_EVT_TCU_COMP1_END_OF_TASK    (HSP_EVT_ISR_SOTECP1F) /*!< Task Ended flag of TCU 1   */
#define HAL_HSP_FLAG_EVT_TCU_COMP2_END_OF_TASK    (HSP_EVT_ISR_SOTECP2F) /*!< Task Ended flag of TCU 2   */
#define HAL_HSP_FLAG_EVT_TCU_COMP3_END_OF_TASK    (HSP_EVT_ISR_SOTECP3F) /*!< Task Ended flag of TCU 3   */

/** All TCU flags */
#define HAL_HSP_FLAG_EVT_TCU_ALL                                                        \
  (HAL_HSP_FLAG_EVT_TCU_OVERLAP                                                         \
   | HAL_HSP_FLAG_EVT_TCU_COMP0_START_OF_TASK | HAL_HSP_FLAG_EVT_TCU_COMP0_END_OF_TASK  \
   | HAL_HSP_FLAG_EVT_TCU_COMP1_START_OF_TASK | HAL_HSP_FLAG_EVT_TCU_COMP1_END_OF_TASK  \
   | HAL_HSP_FLAG_EVT_TCU_COMP2_START_OF_TASK | HAL_HSP_FLAG_EVT_TCU_COMP2_END_OF_TASK  \
   | HAL_HSP_FLAG_EVT_TCU_COMP3_START_OF_TASK | HAL_HSP_FLAG_EVT_TCU_COMP3_END_OF_TASK)

/**
  * @}
  */

/** @defgroup HSP_SPE_Flags HSP SPE Flags
  * @{
  */
#define HAL_HSP_FLAG_EVT_SPE_ENTER_IN_WFE   (HSP_EVT_ISR_SOFWFEF)  /*!< Enter In WFE flag    */
#define HAL_HSP_FLAG_EVT_SPE_EXIT_FROM_WFE  (HSP_EVT_ISR_EOFWFEF)  /*!< Exit  From WFE flag  */

/**
  * @}
  */

/** @defgroup HSP_Interrupts_Constants HSP Interrupts Constants
  * @{
  */
#define HAL_HSP_IT_NONE                    (0UL)                  /*!< No interrupts */

/**
  * @}
  */

/** @defgroup HSP_Interrupts_Error_Constants HSP Interrupts Error Constants
  * @{
  */
#define HAL_HSP_IT_ERR_TRGIN_OVR           HSP_ERR_IER_TRGIOVRIE  /*!< Trigger Input Overrun error interrupt */
#define HAL_HSP_IT_ERR_STREAM0_OVR         HSP_ERR_IER_B0ERRIE    /*!< Stream 0 Underrun/Overrun error interrupt */
#define HAL_HSP_IT_ERR_STREAM1_OVR         HSP_ERR_IER_B1ERRIE    /*!< Stream 1 Underrun/Overrun error interrupt */
#define HAL_HSP_IT_ERR_STREAM2_OVR         HSP_ERR_IER_B2ERRIE    /*!< Stream 2 Underrun/Overrun error interrupt */
#define HAL_HSP_IT_ERR_STREAM3_OVR         HSP_ERR_IER_B3ERRIE    /*!< Stream 3 Underrun/Overrun error interrupt */
#define HAL_HSP_IT_ERR_TSC_OVR             HSP_ERR_IER_CAPOVRIE   /*!< Timestamp Capture Overrun error interrupt */
#define HAL_HSP_IT_ERR_SPE_FW              HSP_ERR_IER_FWERRIE    /*!< SPE Firmware error interrupt */
#define HAL_HSP_IT_ERR_SPE_SCHEDULER       HSP_ERR_IER_SCHERRIE   /*!< SPE Scheduler error interrupt */
#define HAL_HSP_IT_ERR_SPE_BREAK           HSP_ERR_IER_BKINIE     /*!< SPE Break interrupt */
#define HAL_HSP_IT_ERR_SPE_HDEG_OVR        HSP_ERR_IER_HDEGOVRIE  /*!< SPE HDEG Overrun error interrupt */
#define HAL_HSP_IT_ERR_SPE_INVALID_OPCODE  HSP_ERR_IER_OPCOERRIE  /*!< SPE Invalid Opcode error interrupt */
#define HAL_HSP_IT_ERR_SPE_ACCESS          HSP_ERR_IER_ACCERRIE   /*!< SPE Access error interrupt */
#define HAL_HSP_IT_ERR_SPE_FPU_UDF         HSP_ERR_IER_UDFIE      /*!< SPE FPU Underflow error interrupt */
#define HAL_HSP_IT_ERR_SPE_FPU_OVF         HSP_ERR_IER_OVFIE      /*!< SPE FPU Overflow error interrupt */
#define HAL_HSP_IT_ERR_SPE_FPU_DBZ         HSP_ERR_IER_DBZIE      /*!< SPE FPU Division By Zero error interrupt */
#define HAL_HSP_IT_ERR_SPE_FPU_INVALID     HSP_ERR_IER_INVIE      /*!< SPE FPU Invalid Exception error interrupt */
#define HAL_HSP_IT_ERR_SPE_FPU_DENORMAL    HSP_ERR_IER_DENORMIE   /*!< SPE FPU Denormal error interrupt */

/** HAL HSP Mask of all STREAM Buffer Errors */
#define HAL_HSP_IT_ERR_STREAM_ALL  (HAL_HSP_IT_ERR_STREAM0_OVR   | HAL_HSP_IT_ERR_STREAM1_OVR  \
                                    | HAL_HSP_IT_ERR_STREAM2_OVR | HAL_HSP_IT_ERR_STREAM3_OVR)

/** HAL HSP Mask of all TRGIN Errors */
#define HAL_HSP_IT_ERR_TRGIN_ALL  (HAL_HSP_IT_ERR_TRGIN_OVR)

/** HAL HSP Mask of all Timestamp Capture Errors */
#define HAL_HSP_IT_ERR_TSC_ALL  (HAL_HSP_IT_ERR_TSC_OVR)

/** HAL HSP Mask of all FPU Errors */
#define HAL_HSP_IT_ERR_SPE_FPU_ALL  (HAL_HSP_IT_ERR_SPE_FPU_OVF       | HAL_HSP_IT_ERR_SPE_FPU_DBZ        \
                                     | HAL_HSP_IT_ERR_SPE_FPU_INVALID | HAL_HSP_IT_ERR_SPE_FPU_DENORMAL)

/** HAL HSP Mask of all SPE Errors */
#define HAL_HSP_IT_ERR_SPE_ALL  (HAL_HSP_IT_ERR_SPE_FW            | HAL_HSP_IT_ERR_SPE_SCHEDULER       \
                                 | HAL_HSP_IT_ERR_SPE_HDEG_OVR    | HAL_HSP_IT_ERR_SPE_INVALID_OPCODE  \
                                 | HAL_HSP_IT_ERR_SPE_ACCESS      | HAL_HSP_IT_ERR_SPE_FPU_UDF         \
                                 | HAL_HSP_IT_ERR_SPE_FPU_OVF     | HAL_HSP_IT_ERR_SPE_FPU_DBZ         \
                                 | HAL_HSP_IT_ERR_SPE_FPU_INVALID | HAL_HSP_IT_ERR_SPE_FPU_DENORMAL    \
                                 | HAL_HSP_IT_ERR_SPE_BREAK)


/** HAL HSP Mask of all HSP Errors */
#define HAL_HSP_IT_ERR_ALL (HAL_HSP_IT_ERR_STREAM_ALL | HAL_HSP_IT_ERR_TRGIN_ALL  \
                            | HAL_HSP_IT_ERR_TSC_ALL  | HAL_HSP_IT_ERR_SPE_ALL)

#define HAL_HSP_FLAG_ERR_SPE_FPU              (HSP_ERR_ISR_FPUERRF)   /*!< Task Overlap flag          */

/**
  * @}
  */

/** @defgroup HSP_Error_Information_Constants HSP Errors Information Constants
  * @{
  */
#define HAL_HSP_ERRINF_SPE_SLAVE_AHB_ACCESS     HSP_ERRINFR_SAHBERR    /*!< SPE Slave AHB Access error    */
#define HAL_HSP_ERRINF_SPE_INTERNAL_AHB_ACCESS  HSP_ERRINFR_MAHBERR    /*!< SPE Internal AHB Access error */
#define HAL_HSP_ERRINF_SPE_DATA_MEM_ACCESS      HSP_ERRINFR_DMERR      /*!< SPE Data Memory Access error  */
#define HAL_HSP_ERRINF_SPE_CODE_MEM_ACCESS      HSP_ERRINFR_CMERR      /*!< SPE Code Memory Access error  */

/** HAL HSP Mask of all HSP SPE Access Errors */
#define HAL_HSP_ERRINF_SPE_ALL  (HAL_HSP_ERRINF_SPE_SLAVE_AHB_ACCESS   | HAL_HSP_ERRINF_SPE_INTERNAL_AHB_ACCESS  \
                                 | HAL_HSP_ERRINF_SPE_DATA_MEM_ACCESS  | HAL_HSP_ERRINF_SPE_CODE_MEM_ACCESS)

#define HAL_HSP_ERRINF_FPU_INEXACT              HSP_ERRINFR_INEXACT    /*!< FPU Inexact Exception         */
#define HAL_HSP_ERRINF_FPU_UDF                  HSP_ERRINFR_UDFLOW     /*!< FPU Underflow error           */
#define HAL_HSP_ERRINF_FPU_OVF                  HSP_ERRINFR_OVFLOW     /*!< FPU Overflow error            */
#define HAL_HSP_ERRINF_FPU_DIVZERO              HSP_ERRINFR_DIVZERO    /*!< FPU Division By Zero error    */
#define HAL_HSP_ERRINF_FPU_INVALID              HSP_ERRINFR_INVALID    /*!< FPU Invalid Exception error   */
#define HAL_HSP_ERRINF_FPU_DENORMAL             HSP_ERRINFR_DENORM     /*!< FPU Denormal error            */

/** HAL HSP Mask of all HSP FPU Errors */
#define HAL_HSP_ERRINF_FPU_ALL  (HAL_HSP_ERRINF_FPU_INEXACT   | HAL_HSP_ERRINF_FPU_UDF      \
                                 | HAL_HSP_ERRINF_FPU_OVF     | HAL_HSP_ERRINF_FPU_DIVZERO  \
                                 | HAL_HSP_ERRINF_FPU_INVALID | HAL_HSP_ERRINF_FPU_DENORMAL)

/**
  * @}
  */

/** @defgroup HSP_Event_Interrupts_Constants HSP Event Interrupts Constants
  * @{
  */
#define HAL_HSP_IT_EVT_CMD_DIRECT_COMMAND_DONE HSP_EVT_IER_DCDONEIE   /*!< Direct Command Done event interrupt */
#define HAL_HSP_IT_EVT_CMD_CDEG_READY          HSP_EVT_IER_CDEGRDYIE  /*!< CDEG Ready event interrupt */
#define HAL_HSP_IT_EVT_TSC_DATA_READY          HSP_EVT_IER_CAPRDYIE   /*!< TimeStamp Capture Data Ready event interrupt */
#define HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE        HSP_EVT_IER_SOFWFEIE   /*!< SPE Enter In WFE mode event interrupt */
#define HAL_HSP_IT_EVT_SPE_EXIT_FROM_WFE       HSP_EVT_IER_EOFWFEIE   /*!< SPE Exit From WFE mode event interrupt */
#define HAL_HSP_IT_EVT_SPE_FPU_SATURATION      HSP_EVT_IER_FPUSATIE   /*!< SPE FPU Saturation event interrupt */
#define HAL_HSP_IT_EVT_STREAM0_READY           HSP_EVT_IER_B0EVTIE    /*!< Stream buffer 0 is empty or filled (depend of STREAM direction) */
#define HAL_HSP_IT_EVT_STREAM1_READY           HSP_EVT_IER_B1EVTIE    /*!< Stream buffer 1 is empty or filled (depend of STREAM direction) */
#define HAL_HSP_IT_EVT_STREAM2_READY           HSP_EVT_IER_B2EVTIE    /*!< Stream buffer 2 is empty or filled (depend of STREAM direction) */
#define HAL_HSP_IT_EVT_STREAM3_READY           HSP_EVT_IER_B3EVTIE    /*!< Stream buffer 3 is empty or filled (depend of STREAM direction) */
#define HAL_HSP_IT_EVT_TCU0_TASK_STARTED       HSP_EVT_IER_SOTECP0IE  /*!< Task Comparator Unit 0 Start of Task event interrupt */
#define HAL_HSP_IT_EVT_TCU1_TASK_STARTED       HSP_EVT_IER_SOTECP1IE  /*!< Task Comparator Unit 1 Start of Task event interrupt */
#define HAL_HSP_IT_EVT_TCU2_TASK_STARTED       HSP_EVT_IER_SOTECP2IE  /*!< Task Comparator Unit 2 Start of Task event interrupt */
#define HAL_HSP_IT_EVT_TCU3_TASK_STARTED       HSP_EVT_IER_SOTECP3IE  /*!< Task Comparator Unit 3 Start of Task event interrupt */
#define HAL_HSP_IT_EVT_TCU0_TASK_ENDED         HSP_EVT_IER_EOTECP0IE  /*!< Task Comparator Unit 0 End of Task event interrupt */
#define HAL_HSP_IT_EVT_TCU1_TASK_ENDED         HSP_EVT_IER_EOTECP1IE  /*!< Task Comparator Unit 1 End of Task event interrupt */
#define HAL_HSP_IT_EVT_TCU2_TASK_ENDED         HSP_EVT_IER_EOTECP2IE  /*!< Task Comparator Unit 2 End of Task event interrupt */
#define HAL_HSP_IT_EVT_TCU3_TASK_ENDED         HSP_EVT_IER_EOTECP3IE  /*!< Task Comparator Unit 3 End of Task event interrupt */
#define HAL_HSP_IT_EVT_TCU_TASK_OVL            HSP_EVT_IER_TOVLPIE    /*!< Task Comparator Unit Task Overlap event interrupt */

/** HAL HSP Mask of all HSP STREAM Buffer Events */
#define HAL_HSP_IT_EVT_STREAM_ALL  (HAL_HSP_IT_EVT_STREAM0_READY   | HAL_HSP_IT_EVT_STREAM1_READY   \
                                    | HAL_HSP_IT_EVT_STREAM2_READY | HAL_HSP_IT_EVT_STREAM3_READY)

/** HAL HSP Mask of all HSP TCU Events */
#define HAL_HSP_IT_EVT_TCU0_ALL  (HAL_HSP_IT_EVT_TCU0_TASK_STARTED | HAL_HSP_IT_EVT_TCU0_TASK_ENDED)
#define HAL_HSP_IT_EVT_TCU1_ALL  (HAL_HSP_IT_EVT_TCU1_TASK_STARTED | HAL_HSP_IT_EVT_TCU1_TASK_ENDED)
#define HAL_HSP_IT_EVT_TCU2_ALL  (HAL_HSP_IT_EVT_TCU2_TASK_STARTED | HAL_HSP_IT_EVT_TCU2_TASK_ENDED)
#define HAL_HSP_IT_EVT_TCU3_ALL  (HAL_HSP_IT_EVT_TCU3_TASK_STARTED | HAL_HSP_IT_EVT_TCU3_TASK_ENDED)

#define HAL_HSP_IT_EVT_TCU_ALL  (HAL_HSP_IT_EVT_TCU0_ALL   | HAL_HSP_IT_EVT_TCU1_ALL  \
                                 | HAL_HSP_IT_EVT_TCU2_ALL | HAL_HSP_IT_EVT_TCU3_ALL  \
                                 | HAL_HSP_IT_EVT_TCU_TASK_OVL)

/** HAL HSP Mask of all HSP SPE Events */
#define HAL_HSP_IT_EVT_SPE_ALL  (HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE | HAL_HSP_IT_EVT_SPE_EXIT_FROM_WFE  \
                                 | HAL_HSP_IT_EVT_SPE_FPU_SATURATION)

/**
  * @}
  */

/** @defgroup HSP_Processing_Function_Event_Constants HSP Processing Function Event Constants
  * @{
  */
#define HAL_HSP_PROCLIST_EVT_0  HSP_PFCTEVT_ISR_PFCTF_0   /*!< Processing Function Event 0  flag */
#define HAL_HSP_PROCLIST_EVT_1  HSP_PFCTEVT_ISR_PFCTF_1   /*!< Processing Function Event 1  flag */
#define HAL_HSP_PROCLIST_EVT_2  HSP_PFCTEVT_ISR_PFCTF_2   /*!< Processing Function Event 2  flag */
#define HAL_HSP_PROCLIST_EVT_3  HSP_PFCTEVT_ISR_PFCTF_3   /*!< Processing Function Event 3  flag */
#define HAL_HSP_PROCLIST_EVT_4  HSP_PFCTEVT_ISR_PFCTF_4   /*!< Processing Function Event 4  flag */
#define HAL_HSP_PROCLIST_EVT_5  HSP_PFCTEVT_ISR_PFCTF_5   /*!< Processing Function Event 5  flag */
#define HAL_HSP_PROCLIST_EVT_6  HSP_PFCTEVT_ISR_PFCTF_6   /*!< Processing Function Event 6  flag */
#define HAL_HSP_PROCLIST_EVT_7  HSP_PFCTEVT_ISR_PFCTF_7   /*!< Processing Function Event 7  flag */
#define HAL_HSP_PROCLIST_EVT_8  HSP_PFCTEVT_ISR_PFCTF_8   /*!< Processing Function Event 8  flag */
#define HAL_HSP_PROCLIST_EVT_9  HSP_PFCTEVT_ISR_PFCTF_9   /*!< Processing Function Event 9  flag */
#define HAL_HSP_PROCLIST_EVT_10 HSP_PFCTEVT_ISR_PFCTF_10  /*!< Processing Function Event 10 flag */
#define HAL_HSP_PROCLIST_EVT_11 HSP_PFCTEVT_ISR_PFCTF_11  /*!< Processing Function Event 11 flag */
#define HAL_HSP_PROCLIST_EVT_12 HSP_PFCTEVT_ISR_PFCTF_12  /*!< Processing Function Event 12 flag */
#define HAL_HSP_PROCLIST_EVT_13 HSP_PFCTEVT_ISR_PFCTF_13  /*!< Processing Function Event 13 flag */
#define HAL_HSP_PROCLIST_EVT_14 HSP_PFCTEVT_ISR_PFCTF_14  /*!< Processing Function Event 14 flag */
#define HAL_HSP_PROCLIST_EVT_15 HSP_PFCTEVT_ISR_PFCTF_15  /*!< Processing Function Event 15 flag */
#define HAL_HSP_PROCLIST_EVT_16 HSP_PFCTEVT_ISR_PFCTF_16  /*!< Processing Function Event 16 flag */
#define HAL_HSP_PROCLIST_EVT_17 HSP_PFCTEVT_ISR_PFCTF_17  /*!< Processing Function Event 17 flag */
#define HAL_HSP_PROCLIST_EVT_18 HSP_PFCTEVT_ISR_PFCTF_18  /*!< Processing Function Event 18 flag */
#define HAL_HSP_PROCLIST_EVT_19 HSP_PFCTEVT_ISR_PFCTF_19  /*!< Processing Function Event 19 flag */
#define HAL_HSP_PROCLIST_EVT_20 HSP_PFCTEVT_ISR_PFCTF_20  /*!< Processing Function Event 20 flag */
#define HAL_HSP_PROCLIST_EVT_21 HSP_PFCTEVT_ISR_PFCTF_21  /*!< Processing Function Event 21 flag */
#define HAL_HSP_PROCLIST_EVT_22 HSP_PFCTEVT_ISR_PFCTF_22  /*!< Processing Function Event 22 flag */
#define HAL_HSP_PROCLIST_EVT_23 HSP_PFCTEVT_ISR_PFCTF_23  /*!< Processing Function Event 23 flag */
#define HAL_HSP_PROCLIST_EVT_24 HSP_PFCTEVT_ISR_PFCTF_24  /*!< Processing Function Event 24 flag */
#define HAL_HSP_PROCLIST_EVT_25 HSP_PFCTEVT_ISR_PFCTF_25  /*!< Processing Function Event 25 flag */
#define HAL_HSP_PROCLIST_EVT_26 HSP_PFCTEVT_ISR_PFCTF_26  /*!< Processing Function Event 26 flag */
#define HAL_HSP_PROCLIST_EVT_27 HSP_PFCTEVT_ISR_PFCTF_27  /*!< Processing Function Event 27 flag */
#define HAL_HSP_PROCLIST_EVT_28 HSP_PFCTEVT_ISR_PFCTF_28  /*!< Processing Function Event 28 flag */
#define HAL_HSP_PROCLIST_EVT_29 HSP_PFCTEVT_ISR_PFCTF_29  /*!< Processing Function Event 29 flag */
#define HAL_HSP_PROCLIST_EVT_30 HSP_PFCTEVT_ISR_PFCTF_30  /*!< Processing Function Event 30 flag */
#define HAL_HSP_PROCLIST_EVT_31 HSP_PFCTEVT_ISR_PFCTF_31  /*!< Processing Function Event 31 flag */

/** HAL HSP Mask of all HSP Processing Function Events */
#define HAL_HSP_PROCLIST_EVT_ALL  \
  (HAL_HSP_PROCLIST_EVT_0    | HAL_HSP_PROCLIST_EVT_1  | HAL_HSP_PROCLIST_EVT_2  | HAL_HSP_PROCLIST_EVT_3   \
   | HAL_HSP_PROCLIST_EVT_4  | HAL_HSP_PROCLIST_EVT_5  | HAL_HSP_PROCLIST_EVT_6  | HAL_HSP_PROCLIST_EVT_7   \
   | HAL_HSP_PROCLIST_EVT_8  | HAL_HSP_PROCLIST_EVT_9  | HAL_HSP_PROCLIST_EVT_10 | HAL_HSP_PROCLIST_EVT_11  \
   | HAL_HSP_PROCLIST_EVT_12 | HAL_HSP_PROCLIST_EVT_13 | HAL_HSP_PROCLIST_EVT_14 | HAL_HSP_PROCLIST_EVT_15  \
   | HAL_HSP_PROCLIST_EVT_16 | HAL_HSP_PROCLIST_EVT_17 | HAL_HSP_PROCLIST_EVT_18 | HAL_HSP_PROCLIST_EVT_19  \
   | HAL_HSP_PROCLIST_EVT_20 | HAL_HSP_PROCLIST_EVT_21 | HAL_HSP_PROCLIST_EVT_22 | HAL_HSP_PROCLIST_EVT_23  \
   | HAL_HSP_PROCLIST_EVT_24 | HAL_HSP_PROCLIST_EVT_25 | HAL_HSP_PROCLIST_EVT_26 | HAL_HSP_PROCLIST_EVT_27  \
   | HAL_HSP_PROCLIST_EVT_28 | HAL_HSP_PROCLIST_EVT_29 | HAL_HSP_PROCLIST_EVT_30 | HAL_HSP_PROCLIST_EVT_31)

/**
  * @}
  */

/** @defgroup HSP_Processing_Function_Event_Interrupts_Constants HSP Processing Function Event Interrupts Constants
  * @{
  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_0  HSP_PFCTEVT_IER_PFCTIE_0   /*!< Processing Function Event 0 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_1  HSP_PFCTEVT_IER_PFCTIE_1   /*!< Processing Function Event 1 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_2  HSP_PFCTEVT_IER_PFCTIE_2   /*!< Processing Function Event 2 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_3  HSP_PFCTEVT_IER_PFCTIE_3   /*!< Processing Function Event 3 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_4  HSP_PFCTEVT_IER_PFCTIE_4   /*!< Processing Function Event 4 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_5  HSP_PFCTEVT_IER_PFCTIE_5   /*!< Processing Function Event 5 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_6  HSP_PFCTEVT_IER_PFCTIE_6   /*!< Processing Function Event 6 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_7  HSP_PFCTEVT_IER_PFCTIE_7   /*!< Processing Function Event 7 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_8  HSP_PFCTEVT_IER_PFCTIE_8   /*!< Processing Function Event 8 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_9  HSP_PFCTEVT_IER_PFCTIE_9   /*!< Processing Function Event 9 interrupt  */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_10 HSP_PFCTEVT_IER_PFCTIE_10  /*!< Processing Function Event 10 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_11 HSP_PFCTEVT_IER_PFCTIE_11  /*!< Processing Function Event 11 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_12 HSP_PFCTEVT_IER_PFCTIE_12  /*!< Processing Function Event 12 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_13 HSP_PFCTEVT_IER_PFCTIE_13  /*!< Processing Function Event 13 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_14 HSP_PFCTEVT_IER_PFCTIE_14  /*!< Processing Function Event 14 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_15 HSP_PFCTEVT_IER_PFCTIE_15  /*!< Processing Function Event 15 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_16 HSP_PFCTEVT_IER_PFCTIE_16  /*!< Processing Function Event 16 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_17 HSP_PFCTEVT_IER_PFCTIE_17  /*!< Processing Function Event 17 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_18 HSP_PFCTEVT_IER_PFCTIE_18  /*!< Processing Function Event 18 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_19 HSP_PFCTEVT_IER_PFCTIE_19  /*!< Processing Function Event 19 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_20 HSP_PFCTEVT_IER_PFCTIE_20  /*!< Processing Function Event 20 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_21 HSP_PFCTEVT_IER_PFCTIE_21  /*!< Processing Function Event 21 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_22 HSP_PFCTEVT_IER_PFCTIE_22  /*!< Processing Function Event 22 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_23 HSP_PFCTEVT_IER_PFCTIE_23  /*!< Processing Function Event 23 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_24 HSP_PFCTEVT_IER_PFCTIE_24  /*!< Processing Function Event 24 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_25 HSP_PFCTEVT_IER_PFCTIE_25  /*!< Processing Function Event 25 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_26 HSP_PFCTEVT_IER_PFCTIE_26  /*!< Processing Function Event 26 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_27 HSP_PFCTEVT_IER_PFCTIE_27  /*!< Processing Function Event 27 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_28 HSP_PFCTEVT_IER_PFCTIE_28  /*!< Processing Function Event 28 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_29 HSP_PFCTEVT_IER_PFCTIE_29  /*!< Processing Function Event 29 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_30 HSP_PFCTEVT_IER_PFCTIE_30  /*!< Processing Function Event 30 interrupt */
#define HAL_HSP_PROCLIST_IT_PFCTEVT_31 HSP_PFCTEVT_IER_PFCTIE_31  /*!< Processing Function Event 31 interrupt */

/** HAL HSP Mask of all HSP Processing Function interrupts */
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

/** @defgroup HSP_SPE_Run_State_Constants HSP SPE Run State Constants
  * @{
  */
#define HAL_HSP_SPE_RUN_STATE_WFE     0U  /*!< HSP SPE Wait For Event state */
#define HAL_HSP_SPE_RUN_STATE_ACTIVE  1U  /*!< HSP SPE Active state         */

/**
  * @}
  */

/** @defgroup HSP_SNOOP_Constants HSP SNOOP Constants
  * @{
  */
/** HAL HSP SNOOP Group Definition */
#define HAL_HSP_SNOOP_GROUP_A    HSP_SNPR_SNPSELA
#define HAL_HSP_SNOOP_GROUP_B    HSP_SNPR_SNPSELB
#define HAL_HSP_SNOOP_GROUP_ALL  (HAL_HSP_SNOOP_GROUP_A | HAL_HSP_SNOOP_GROUP_B)

/** HAL HSP SNOOP Signal Definition */
#define HAL_HSP_SNOOP_GRPA_TASK_2_1_0               (HSP_SNPR_SNPSELA_0 << HSP_SNPR_SNPSELA_Pos)
#define HAL_HSP_SNOOP_GRPA_DMA_CH_2_1_0_IT          (HSP_SNPR_SNPSELA_1 << HSP_SNPR_SNPSELA_Pos)
#define HAL_HSP_SNOOP_GRPA_TRGIN_BUFF_ADC           ((HSP_SNPR_SNPSELA_1 | HSP_SNPR_SNPSELA_0) << HSP_SNPR_SNPSELA_Pos)
#define HAL_HSP_SNOOP_GRPA_TSC_PFCTNB_2_1_0         (HSP_SNPR_SNPSELA_2 << HSP_SNPR_SNPSELA_Pos)
#define HAL_HSP_SNOOP_GRPA_TSC_CMP_2_1_0            ((HSP_SNPR_SNPSELA_2 | HSP_SNPR_SNPSELA_0) << HSP_SNPR_SNPSELA_Pos)
#define HAL_HSP_SNOOP_GRPA_EVTCWKUP_SPEJUMP_SPEWFE  ((HSP_SNPR_SNPSELA_2 | HSP_SNPR_SNPSELA_1) << HSP_SNPR_SNPSELA_Pos)
#define HAL_HSP_SNOOP_GRPA_PE_2_1_0  ((HSP_SNPR_SNPSELA_2 |\
                                       HSP_SNPR_SNPSELA_1 | HSP_SNPR_SNPSELA_0) << HSP_SNPR_SNPSELA_Pos)
#define HAL_HSP_SNOOP_GRPB_TASK_5_4_3               (HSP_SNPR_SNPSELB_0 << HSP_SNPR_SNPSELB_Pos)
#define HAL_HSP_SNOOP_GRPB_PRC_25_24_23             (HSP_SNPR_SNPSELB_1 << HSP_SNPR_SNPSELB_Pos)
#define HAL_HSP_SNOOP_GRPB_DCMD_CDEG_HDEG           ((HSP_SNPR_SNPSELB_1 | HSP_SNPR_SNPSELB_0) << HSP_SNPR_SNPSELB_Pos)
#define HAL_HSP_SNOOP_GRPB_TSC_PFCTNB_5_4_3         (HSP_SNPR_SNPSELB_2 << HSP_SNPR_SNPSELB_Pos)
#define HAL_HSP_SNOOP_GRPB_TSC_CMP_3                ((HSP_SNPR_SNPSELB_2 | HSP_SNPR_SNPSELB_0) << HSP_SNPR_SNPSELB_Pos)
#define HAL_HSP_SNOOP_GRPB_TSC_PULSE_CALL_IF_IFTRUE ((HSP_SNPR_SNPSELB_2 | HSP_SNPR_SNPSELB_1) << HSP_SNPR_SNPSELB_Pos)
#define HAL_HSP_SNOOP_GRPB_PE_5_4_3  ((HSP_SNPR_SNPSELB_2 |\
                                       HSP_SNPR_SNPSELB_1 | HSP_SNPR_SNPSELB_0) << HSP_SNPR_SNPSELB_Pos)

/**
  * @}
  */

/** @defgroup HSP_Break_Event_Constants HSP Break Event constants
  * @{
  */
#define HAL_HSP_BREAK_CRITICAL_EVENT_MEMORY_ACCESS  HSP_BKOCFGR_ACCEREN   /*!< SPE Memory Access Error      */
#define HAL_HSP_BREAK_CRITICAL_EVENT_FPU            HSP_BKOCFGR_FPUEREN   /*!< FPU Error (Div By Zero...)   */
#define HAL_HSP_BREAK_CRITICAL_EVENT_OPCODE         HSP_BKOCFGR_OPCEREN   /*!< OpCode Error                 */
#define HAL_HSP_BREAK_CRITICAL_EVENT_PFCT28         HSP_BKOCFGR_PFCT28EN  /*!< Processing Function Event 28 */
#define HAL_HSP_BREAK_CRITICAL_EVENT_PFCT29         HSP_BKOCFGR_PFCT29EN  /*!< Processing Function Event 29 */
#define HAL_HSP_BREAK_CRITICAL_EVENT_PFCT30         HSP_BKOCFGR_PFCT30EN  /*!< Processing Function Event 30 */
#define HAL_HSP_BREAK_CRITICAL_EVENT_PFCT31         HSP_BKOCFGR_PFCT31EN  /*!< Processing Function Event 31 */
#define HAL_HSP_BREAK_CRITICAL_EVENT_FIRMWARE       HSP_BKOCFGR_FWEREN    /*!< Firmware Error               */
#define HAL_HSP_BREAK_CRITICAL_EVENT_SPE_OVR        HSP_BKOCFGR_HDEGOVEN  /*!< HDEG Overrun                 */

/** HAL HSP BREAK Mask of all Critical Events */
#define HAL_HSP_BREAK_CRITICAL_EVENT_ALL                                               \
  (HAL_HSP_BREAK_CRITICAL_EVENT_MEMORY_ACCESS | HAL_HSP_BREAK_CRITICAL_EVENT_FPU       \
   | HAL_HSP_BREAK_CRITICAL_EVENT_OPCODE      | HAL_HSP_BREAK_CRITICAL_EVENT_PFCT28    \
   | HAL_HSP_BREAK_CRITICAL_EVENT_PFCT29      | HAL_HSP_BREAK_CRITICAL_EVENT_PFCT30    \
   | HAL_HSP_BREAK_CRITICAL_EVENT_PFCT31      | HAL_HSP_BREAK_CRITICAL_EVENT_FIRMWARE  \
   | HAL_HSP_BREAK_CRITICAL_EVENT_SPE_OVR     | HAL_HSP_BREAK_CRITICAL_EVENT_SPE_OVR)

#define HAL_HSP_BREAK_FREEZE_EVENT_MEMORY_ACCESS   HSP_BKICFGR_ACCEREN   /*!< SPE Memory Access Error      */
#define HAL_HSP_BREAK_FREEZE_EVENT_FPU             HSP_BKICFGR_FPUEREN   /*!< FPU Error (Div By Zero...)   */
#define HAL_HSP_BREAK_FREEZE_EVENT_OPCODE          HSP_BKICFGR_OPCEREN   /*!< OpCode Error                 */
#define HAL_HSP_BREAK_FREEZE_EVENT_PFCT28          HSP_BKICFGR_PFCT28EN  /*!< Processing Function Event 28 */
#define HAL_HSP_BREAK_FREEZE_EVENT_PFCT29          HSP_BKICFGR_PFCT29EN  /*!< Processing Function Event 29 */
#define HAL_HSP_BREAK_FREEZE_EVENT_PFCT30          HSP_BKICFGR_PFCT30EN  /*!< Processing Function Event 30 */
#define HAL_HSP_BREAK_FREEZE_EVENT_PFCT31          HSP_BKICFGR_PFCT31EN  /*!< Processing Function Event 31 */
#define HAL_HSP_BREAK_FREEZE_EVENT_FIRMWARE        HSP_BKICFGR_FWEREN    /*!< Firmware Error               */
#define HAL_HSP_BREAK_FREEZE_EVENT_SPE_OVR         HSP_BKICFGR_HDEGOVEN  /*!< HDEG Overrun                 */
#define HAL_HSP_BREAK_FREEZE_EVENT_FPU_SATURATION  HSP_BKICFGR_FSATEN    /*!< FPU Saturation Event         */

/** HAL HSP BREAK Mask of all Freeze Events */
#define HAL_HSP_BREAK_FREEZE_EVENT_ALL                                                    \
  (HAL_HSP_BREAK_FREEZE_EVENT_MEMORY_ACCESS    | HAL_HSP_BREAK_FREEZE_EVENT_FPU           \
   | HAL_HSP_BREAK_FREEZE_EVENT_OPCODE         | HAL_HSP_BREAK_FREEZE_EVENT_PFCT28        \
   | HAL_HSP_BREAK_FREEZE_EVENT_PFCT29         | HAL_HSP_BREAK_FREEZE_EVENT_PFCT30        \
   | HAL_HSP_BREAK_FREEZE_EVENT_PFCT31         | HAL_HSP_BREAK_FREEZE_EVENT_FIRMWARE      \
   | HAL_HSP_BREAK_FREEZE_EVENT_SPE_OVR        | HAL_HSP_BREAK_FREEZE_EVENT_FPU_SATURATION)

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
#define STM32_READ_BIT      READ_BIT
#define STM32_SET_BIT       SET_BIT
#define STM32_CLEAR_BIT     CLEAR_BIT
#define STM32_IS_BIT_SET    HAL_IS_BIT_SET
#define STM32_READ_REG      READ_REG
#define STM32_WRITE_REG     WRITE_REG
#define STM32_MODIFY_REG    MODIFY_REG
#define STM32_POSITION_VAL  POSITION_VAL

#define HAL_HSP_GET_INSTANCE(hsp_id)  (((hsp_id) == 0U)?HSP1:NULL)
#define HAL_HSP_GET_INSTANCE_ID(instance)  (((instance) == (uint32_t)HSP1)?0U:HAL_HSP_INSTANCE_UNKNOWN)

/**
  * @ Brief Macros to retrieve HSP Interface definitions
  */
#define HAL_HSP_ADC_INTERFACE_NBR(instance)  0U
#define HAL_HSP_STREAM_INTERFACE_NBR(instance)  HSP_STREAM_INTERFACE_NBR((instance))
#define HAL_HSP_TRIGGER_INTERFACE_NBR(instance)  HSP_TRIGGER_INTERFACE_NBR((instance))
#define HAL_HSP_TASK_COMPARATOR_UNIT_NBR(instance)  HSP_TASK_COMPARATOR_UNIT_NBR((instance))

/**
  * @ Brief Macros to retrieve HSP Interface definitions
  */
/**
  * @brief Get the HSP Event HSEG Source Enum value.
  * @param  evt_priority  Event priority.
  * @retval uint32_t.
  */
#define HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_HSEG(evt_priority)  \
  ((evt_priority == 1U)?HAL_HSP_EVENT_1_HSEG:                 \
   (evt_priority == 2U)?HAL_HSP_EVENT_2_HSEG:                 \
   (evt_priority == 3U)?HAL_HSP_EVENT_3_HSEG:                 \
   (evt_priority == 4U)?HAL_HSP_EVENT_4_HSEG:                 \
   (evt_priority == 5U)?HAL_HSP_EVENT_5_HSEG:                 \
   (evt_priority == 6U)?HAL_HSP_EVENT_6_HSEG:                 \
   (evt_priority == 7U)?HAL_HSP_EVENT_7_HSEG:                 \
   (evt_priority == 8U)?HAL_HSP_EVENT_8_HSEG:                 \
   (evt_priority == 9U)?HAL_HSP_EVENT_9_HSEG:                 \
   (evt_priority == 10U)?HAL_HSP_EVENT_10_HSEG:               \
   (evt_priority == 11U)?HAL_HSP_EVENT_11_HSEG:               \
   (evt_priority == 12U)?HAL_HSP_EVENT_12_HSEG:               \
   (evt_priority == 13U)?HAL_HSP_EVENT_13_HSEG:               \
   (evt_priority == 14U)?HAL_HSP_EVENT_14_HSEG:               \
   (evt_priority == 15U)?HAL_HSP_EVENT_15_HSEG:               \
   (evt_priority == 16U)?HAL_HSP_EVENT_16_HSEG:               \
   (evt_priority == 17U)?HAL_HSP_EVENT_17_HSEG:               \
   (evt_priority == 18U)?HAL_HSP_EVENT_18_HSEG:               \
   (evt_priority == 19U)?HAL_HSP_EVENT_19_HSEG:               \
   (evt_priority == 20U)?HAL_HSP_EVENT_20_HSEG:               \
   (evt_priority == 21U)?HAL_HSP_EVENT_21_HSEG:               \
   (evt_priority == 22U)?HAL_HSP_EVENT_22_HSEG:               \
   HAL_HSP_EVENT_RESERVED)

/**
  * @brief Get the HSP Event CSEG Source Enum value.
  * @param  evt_priority  Event priority.
  * @retval uint32_t.
  */
#define HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_CSEG(evt_priority)  \
  ((evt_priority == 1U)?HAL_HSP_EVENT_1_CSEG:                 \
   (evt_priority == 2U)?HAL_HSP_EVENT_2_CSEG:                 \
   (evt_priority == 3U)?HAL_HSP_EVENT_3_CSEG:                 \
   (evt_priority == 4U)?HAL_HSP_EVENT_4_CSEG:                 \
   (evt_priority == 5U)?HAL_HSP_EVENT_5_CSEG:                 \
   (evt_priority == 6U)?HAL_HSP_EVENT_6_CSEG:                 \
   (evt_priority == 7U)?HAL_HSP_EVENT_7_CSEG:                 \
   (evt_priority == 8U)?HAL_HSP_EVENT_8_CSEG:                 \
   (evt_priority == 9U)?HAL_HSP_EVENT_9_CSEG:                 \
   (evt_priority == 10U)?HAL_HSP_EVENT_10_CSEG:               \
   (evt_priority == 11U)?HAL_HSP_EVENT_11_CSEG:               \
   (evt_priority == 12U)?HAL_HSP_EVENT_12_CSEG:               \
   (evt_priority == 13U)?HAL_HSP_EVENT_13_CSEG:               \
   (evt_priority == 14U)?HAL_HSP_EVENT_14_CSEG:               \
   (evt_priority == 15U)?HAL_HSP_EVENT_15_CSEG:               \
   (evt_priority == 16U)?HAL_HSP_EVENT_16_CSEG:               \
   (evt_priority == 17U)?HAL_HSP_EVENT_17_CSEG:               \
   (evt_priority == 18U)?HAL_HSP_EVENT_18_CSEG:               \
   (evt_priority == 19U)?HAL_HSP_EVENT_19_CSEG:               \
   (evt_priority == 20U)?HAL_HSP_EVENT_20_CSEG:               \
   (evt_priority == 21U)?HAL_HSP_EVENT_21_CSEG:               \
   (evt_priority == 22U)?HAL_HSP_EVENT_22_CSEG:               \
   HAL_HSP_EVENT_RESERVED)

/**
  * @brief Get the HSP Event STREAM Buffer Source Enum value.
  * @param  evt_priority  Event priority.
  * @retval uint32_t.
  */
#define HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_STREAM(evt_priority)  \
  ((evt_priority == 1U)?HAL_HSP_EVENT_1_STREAM0:                \
   (evt_priority == 2U)?HAL_HSP_EVENT_2_STREAM1:                \
   (evt_priority == 3U)?HAL_HSP_EVENT_3_STREAM2:                \
   (evt_priority == 4U)?HAL_HSP_EVENT_4_STREAM3:                \
   (evt_priority == 5U)?HAL_HSP_EVENT_5_STREAM0:                \
   (evt_priority == 6U)?HAL_HSP_EVENT_6_STREAM1:                \
   (evt_priority == 7U)?HAL_HSP_EVENT_7_STREAM2:                \
   (evt_priority == 8U)?HAL_HSP_EVENT_8_STREAM3:                \
   (evt_priority == 9U)?HAL_HSP_EVENT_9_STREAM0:                \
   (evt_priority == 10U)?HAL_HSP_EVENT_10_STREAM1:              \
   (evt_priority == 11U)?HAL_HSP_EVENT_11_STREAM2:              \
   (evt_priority == 12U)?HAL_HSP_EVENT_12_STREAM3:              \
   (evt_priority == 13U)?HAL_HSP_EVENT_13_STREAM0:              \
   (evt_priority == 14U)?HAL_HSP_EVENT_14_STREAM1:              \
   (evt_priority == 15U)?HAL_HSP_EVENT_15_STREAM2:              \
   (evt_priority == 16U)?HAL_HSP_EVENT_16_STREAM3:              \
   (evt_priority == 17U)?HAL_HSP_EVENT_17_STREAM0:              \
   (evt_priority == 18U)?HAL_HSP_EVENT_18_STREAM1:              \
   (evt_priority == 19U)?HAL_HSP_EVENT_19_STREAM2:              \
   (evt_priority == 20U)?HAL_HSP_EVENT_20_STREAM3:              \
   (evt_priority == 21U)?HAL_HSP_EVENT_21_STREAM0:              \
   (evt_priority == 22U)?HAL_HSP_EVENT_22_STREAM1:              \
   HAL_HSP_EVENT_RESERVED)

/**
  * @brief Get the HSP Event TRGIN Source Enum value.
  * @param  evt_priority  Event priority.
  * @param  trig_itf_id   TRGIN id.
  * @retval uint32_t.
  */
#define HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_TRIGGER(evt_priority, trig_itf_id)  \
  (((evt_priority == 1U)  && (trig_itf_id == 3U))?HAL_HSP_EVENT_1_TRGIN3:     \
   ((evt_priority == 1U)  && (trig_itf_id == 8U))?HAL_HSP_EVENT_1_TRGIN8:     \
   ((evt_priority == 2U)  && (trig_itf_id == 4U))?HAL_HSP_EVENT_2_TRGIN4:     \
   ((evt_priority == 2U)  && (trig_itf_id == 9U))?HAL_HSP_EVENT_2_TRGIN9:     \
   ((evt_priority == 3U)  && (trig_itf_id == 0U))?HAL_HSP_EVENT_3_TRGIN0:     \
   ((evt_priority == 3U)  && (trig_itf_id == 5U))?HAL_HSP_EVENT_3_TRGIN5:     \
   ((evt_priority == 4U)  && (trig_itf_id == 1U))?HAL_HSP_EVENT_4_TRGIN1:     \
   ((evt_priority == 4U)  && (trig_itf_id == 6U))?HAL_HSP_EVENT_4_TRGIN6:     \
   ((evt_priority == 5U)  && (trig_itf_id == 2U))?HAL_HSP_EVENT_5_TRGIN2:     \
   ((evt_priority == 5U)  && (trig_itf_id == 7U))?HAL_HSP_EVENT_5_TRGIN7:     \
   ((evt_priority == 6U)  && (trig_itf_id == 3U))?HAL_HSP_EVENT_6_TRGIN3:     \
   ((evt_priority == 6U)  && (trig_itf_id == 8U))?HAL_HSP_EVENT_6_TRGIN8:     \
   ((evt_priority == 7U)  && (trig_itf_id == 4U))?HAL_HSP_EVENT_7_TRGIN4:     \
   ((evt_priority == 7U)  && (trig_itf_id == 9U))?HAL_HSP_EVENT_7_TRGIN9:     \
   ((evt_priority == 8U)  && (trig_itf_id == 0U))?HAL_HSP_EVENT_8_TRGIN0:     \
   ((evt_priority == 8U)  && (trig_itf_id == 5U))?HAL_HSP_EVENT_8_TRGIN5:     \
   ((evt_priority == 9U)  && (trig_itf_id == 1U))?HAL_HSP_EVENT_9_TRGIN1:     \
   ((evt_priority == 9U)  && (trig_itf_id == 6U))?HAL_HSP_EVENT_9_TRGIN6:     \
   ((evt_priority == 10U) && (trig_itf_id == 2U))?HAL_HSP_EVENT_10_TRGIN2:    \
   ((evt_priority == 10U) && (trig_itf_id == 7U))?HAL_HSP_EVENT_10_TRGIN7:    \
   ((evt_priority == 11U) && (trig_itf_id == 3U))?HAL_HSP_EVENT_11_TRGIN3:    \
   ((evt_priority == 11U) && (trig_itf_id == 8U))?HAL_HSP_EVENT_11_TRGIN8:    \
   ((evt_priority == 12U) && (trig_itf_id == 4U))?HAL_HSP_EVENT_12_TRGIN4:    \
   ((evt_priority == 12U) && (trig_itf_id == 9U))?HAL_HSP_EVENT_12_TRGIN9:    \
   ((evt_priority == 13U) && (trig_itf_id == 0U))?HAL_HSP_EVENT_13_TRGIN0:    \
   ((evt_priority == 13U) && (trig_itf_id == 5U))?HAL_HSP_EVENT_13_TRGIN5:    \
   ((evt_priority == 14U) && (trig_itf_id == 1U))?HAL_HSP_EVENT_14_TRGIN1:    \
   ((evt_priority == 14U) && (trig_itf_id == 6U))?HAL_HSP_EVENT_14_TRGIN6:    \
   ((evt_priority == 15U) && (trig_itf_id == 2U))?HAL_HSP_EVENT_15_TRGIN2:    \
   ((evt_priority == 15U) && (trig_itf_id == 7U))?HAL_HSP_EVENT_15_TRGIN7:    \
   ((evt_priority == 16U) && (trig_itf_id == 3U))?HAL_HSP_EVENT_16_TRGIN3:    \
   ((evt_priority == 16U) && (trig_itf_id == 8U))?HAL_HSP_EVENT_16_TRGIN8:    \
   ((evt_priority == 17U) && (trig_itf_id == 4U))?HAL_HSP_EVENT_17_TRGIN4:    \
   ((evt_priority == 17U) && (trig_itf_id == 9U))?HAL_HSP_EVENT_17_TRGIN9:    \
   ((evt_priority == 18U) && (trig_itf_id == 0U))?HAL_HSP_EVENT_18_TRGIN0:    \
   ((evt_priority == 18U) && (trig_itf_id == 5U))?HAL_HSP_EVENT_18_TRGIN5:    \
   ((evt_priority == 19U) && (trig_itf_id == 1U))?HAL_HSP_EVENT_19_TRGIN1:    \
   ((evt_priority == 19U) && (trig_itf_id == 6U))?HAL_HSP_EVENT_19_TRGIN6:    \
   ((evt_priority == 20U) && (trig_itf_id == 2U))?HAL_HSP_EVENT_20_TRGIN2:    \
   ((evt_priority == 20U) && (trig_itf_id == 7U))?HAL_HSP_EVENT_20_TRGIN7:    \
   ((evt_priority == 21U) && (trig_itf_id == 3U))?HAL_HSP_EVENT_21_TRGIN3:    \
   ((evt_priority == 21U) && (trig_itf_id == 8U))?HAL_HSP_EVENT_21_TRGIN8:    \
   ((evt_priority == 22U) && (trig_itf_id == 4U))?HAL_HSP_EVENT_22_TRGIN4:    \
   ((evt_priority == 22U) && (trig_itf_id == 9U))?HAL_HSP_EVENT_22_TRGIN9:    \
   HAL_HSP_EVENT_RESERVED)

/** @brief Reset HSP handle state.
  * @param  __HANDLE__  specifies the HSP Handle.
  * @retval None
  */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
#define __HAL_HSP_RESET_HANDLE_STATE(__HANDLE__)             \
  do {                                                       \
    (__HANDLE__)->global_state = HAL_HSP_STATE_RESET;        \
    (__HANDLE__)->MspInitCallback = NULL;                    \
    (__HANDLE__)->MspDeInitCallback = NULL;                  \
    (__HANDLE__)->EVT_SPE_RunStateCallback = NULL;           \
    (__HANDLE__)->EVT_SPE_TaskCpltCallback = NULL;    \
    (__HANDLE__)->EVT_SPE_DirectCommandCpltCallback = NULL;  \
    (__HANDLE__)->EVT_SPE_FPUSaturationCallback = NULL;      \
    (__HANDLE__)->EVT_TSC_TimestampReadyCallback = NULL;     \
    (__HANDLE__)->EVT_TCU_TaskStartedCallback = NULL;        \
    (__HANDLE__)->EVT_TCU_TaskEndedCallback = NULL;          \
    (__HANDLE__)->EVT_TCU_TaskOverlapCallback = NULL;        \
    (__HANDLE__)->EVT_STREAM_BufferEmptyCallback = NULL;     \
    (__HANDLE__)->EVT_STREAM_BufferFullCallback = NULL;      \
    (__HANDLE__)->FWEVT_ProcessingEventCallback = NULL;      \
    (__HANDLE__)->ErrorCallback = NULL;                      \
  } while (0U)
#else
#define __HAL_HSP_RESET_HANDLE_STATE(__HANDLE__)  ((__HANDLE__)->global_state = HAL_HSP_STATE_RESET)
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */

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
/** HAL HSP Performance Monitor State Definition  */
typedef enum
{
  HAL_HSP_PERF_MONITOR_DISABLE = 0U,
  HAL_HSP_PERF_MONITOR_ENABLE  = 1U,
} HAL_HSP_PERF_MONITOR_StateTypeDef;

/** HAL HSP Boot Configuration structure */
typedef struct
{
  /** Boot Command ID depends on Firmware ROM */
  uint32_t boot_cmd_id;

  /** Boot Success Code depends on Firmware ROM */
  uint32_t boot_success_code;

  /** Enable/Disable the Performance Monitor at Boot step */
  HAL_HSP_PERF_MONITOR_StateTypeDef perf_mon;

  /** Offset of Performance Counter in DRAM */
  uint32_t perf_counter_offset;
} HAL_HSP_Boot_ConfigTypeDef;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group2 HSP Command Enumerations
  * @{
  */
/** HAL HSP Direct Command Parameter ID Definition */
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
} HAL_HSP_PARAMTypeDef;

/** Enumerate for Direct Command Data Pointer */
typedef enum
{
  /** Direct Command Pointer 0 */
  HAL_HSP_DIRECT_CMD_PTR0 = 0U,

  /** Direct Command Pointer 1 */
  HAL_HSP_DIRECT_CMD_PTR1 = 1U,

  /** Direct Command Pointer 2 */
  HAL_HSP_DIRECT_CMD_PTR2 = 2U
} HAL_HSP_DIRECT_CMD_Data_PtrTypeDef;

/** Enumerate for Direct Command Status */
typedef enum
{
  /** Direct Command Interface is ready to used */
  HAL_HSP_DIRECT_CMD_READY = 0U,

  /** Direct Command Interface is busy */
  HAL_HSP_DIRECT_CMD_BUSY  = HSP_DCMDSR_DCBSY
} HAL_HSP_DIRECT_CMD_StatusTypeDef;

/** Enumerate for MSGBOX Status */
typedef enum
{
  /** No message in the mailbox */
  HAL_HSP_MSGBOX_SEMAPHORE_NO_MSG        = 0U,

  /** A message is available in the mailbox */
  HAL_HSP_MSGBOX_SEMAPHORE_MSG_AVAILABLE = HSP_H2CSEMR_H2CSEM
} HAL_HSP_MSGBOX_Semaphore_StatusTypeDef;

/** HAL HSP Task ID Definition */
typedef enum
{
  HAL_HSP_TASK_0 = 0U,
  HAL_HSP_TASK_1 = 1U,
  HAL_HSP_TASK_2 = 2U,
  HAL_HSP_TASK_3 = 3U,
  HAL_HSP_TASK_4 = 4U,
  HAL_HSP_TASK_5 = 5U,
  HAL_HSP_TASK_6 = 6U,
  HAL_HSP_TASK_7 = 7U,
  HAL_HSP_TASK_8 = 8U,
  HAL_HSP_TASK_9 = 9U,
  HAL_HSP_TASK_10 = 10U,
  HAL_HSP_TASK_11 = 11U,
  HAL_HSP_TASK_12 = 12U,
  HAL_HSP_TASK_13 = 13U,
  HAL_HSP_TASK_14 = 14U,
  HAL_HSP_TASK_15 = 15U,
  HAL_HSP_TASK_16 = 16U,
  HAL_HSP_TASK_17 = 17U,
  HAL_HSP_TASK_18 = 18U,
  HAL_HSP_TASK_19 = 19U,
  HAL_HSP_TASK_20 = 20U,
  HAL_HSP_TASK_21 = 21U,
  HAL_HSP_TASK_22 = 22U,
  HAL_HSP_TASK_23 = 23U,
  HAL_HSP_TASK_24 = 24U,
  HAL_HSP_TASK_25 = 25U,
  HAL_HSP_TASK_26 = 26U,
  HAL_HSP_TASK_27 = 27U,
  HAL_HSP_TASK_28 = 28U,
  HAL_HSP_TASK_29 = 29U,
  HAL_HSP_TASK_30 = 30U,
  HAL_HSP_TASK_31 = 31U,
  HAL_HSP_TASK_32 = 32U,
  HAL_HSP_TASK_33 = 33U,
  HAL_HSP_TASK_34 = 34U,
  HAL_HSP_TASK_35 = 35U,
  HAL_HSP_TASK_36 = 36U,
  HAL_HSP_TASK_SUPERVISOR = 37U  /*!< Supervisor > */
} HAL_HSP_TaskTypeDef;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group3 HSP Task Comparator Enumerations
  * @{
  */
/** HAL HSP Task Comparator Unit Definition */
typedef enum
{
  HAL_HSP_TASK_COMPARATOR_0    = 0U,
  HAL_HSP_TASK_COMPARATOR_1    = 1U,
  HAL_HSP_TASK_COMPARATOR_2    = 2U,
  HAL_HSP_TASK_COMPARATOR_3    = 3U
} HAL_HSP_TASK_ComparatorTypeDef;

/** HAL HSP Task Overlap status */
typedef enum
{
  /** Task Overlapping is disabled */
  HAL_HSP_TCU_TASK_OVERLAP_DISABLED = 0U,

  /** Task Overlapping is enabled */
  HAL_HSP_TCU_TASK_OVERLAP_ENABLED  = 1U,
} HAL_HSP_TCU_Task_Overlap_StatusTypeDef;

/** HAL HSP Task Comparator Unit status */
typedef enum
{
  /** Task Comparator Unit is disabled */
  HAL_HSP_TCU_COMPARATOR_DISABLED = 0U,

  /** Task Comparator Unit is enabled */
  HAL_HSP_TCU_COMPARATOR_ENABLED  = 1U,
} HAL_HSP_TCU_Comparator_StatusTypeDef;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group4 HSP Event Trigger Source Matrix Enumerations
  * @{
  */
/**
  * @brief  HAL HSP Event Source Definition
  *
  *  +------------------+--------------+------------------+--- ... ---+-------------------+
  *  | Priority (6-bit) | Type (4-bit) |  Idx ITF (5-bit) |  Reserved | reg value (3-bit) |
  *  +------------------+--------------+------------------+--- ... ---+-------------------+
  */
typedef enum
{
  HAL_HSP_EVENT_RESERVED = 0U,

  /* Event 1 source Matrix ****************************************************/
  HAL_HSP_EVENT_1_STREAM0  = ((1U << HAL_HSP_EVENT_PRIO_POS)
                              | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_1_TRGIN3   = ((1U << HAL_HSP_EVENT_PRIO_POS)
                              | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_1_TRGIN8   = ((1U << HAL_HSP_EVENT_PRIO_POS)
                              | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_1_HSEG     = ((1U << HAL_HSP_EVENT_PRIO_POS)
                              | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_1_CSEG     = ((1U << HAL_HSP_EVENT_PRIO_POS)
                              | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 2 source Matrix ****************************************************/
  HAL_HSP_EVENT_2_STREAM1  = ((2U << HAL_HSP_EVENT_PRIO_POS)
                              | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_2_TRGIN4   = ((2U << HAL_HSP_EVENT_PRIO_POS)
                              | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_2_TRGIN9   = ((2U << HAL_HSP_EVENT_PRIO_POS)
                              | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_2_HSEG     = ((2U << HAL_HSP_EVENT_PRIO_POS)
                              | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_2_CSEG     = ((2U << HAL_HSP_EVENT_PRIO_POS)
                              | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 3 source Matrix ****************************************************/
  HAL_HSP_EVENT_3_STREAM2  = ((3U << HAL_HSP_EVENT_PRIO_POS)
                              | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_3_TRGIN0   = ((3U << HAL_HSP_EVENT_PRIO_POS)
                              | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_3_TRGIN5   = ((3U << HAL_HSP_EVENT_PRIO_POS)
                              | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_3_HSEG     = ((3U << HAL_HSP_EVENT_PRIO_POS)
                              | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_3_CSEG     = ((3U << HAL_HSP_EVENT_PRIO_POS)
                              | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 4 source Matrix ****************************************************/
  HAL_HSP_EVENT_4_STREAM3  = ((4U << HAL_HSP_EVENT_PRIO_POS)
                              | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_4_TRGIN1   = ((4U << HAL_HSP_EVENT_PRIO_POS)
                              | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_4_TRGIN6   = ((4U << HAL_HSP_EVENT_PRIO_POS)
                              | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_4_HSEG     = ((4U << HAL_HSP_EVENT_PRIO_POS)
                              | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_4_CSEG     = ((4U << HAL_HSP_EVENT_PRIO_POS)
                              | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 5 source Matrix ****************************************************/
  HAL_HSP_EVENT_5_STREAM0  = ((5U << HAL_HSP_EVENT_PRIO_POS)
                              | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_5_TRGIN2   = ((5U << HAL_HSP_EVENT_PRIO_POS)
                              | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_5_TRGIN7   = ((5U << HAL_HSP_EVENT_PRIO_POS)
                              | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_5_HSEG     = ((5U << HAL_HSP_EVENT_PRIO_POS)
                              | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_5_CSEG     = ((5U << HAL_HSP_EVENT_PRIO_POS)
                              | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 6 source Matrix ****************************************************/
  HAL_HSP_EVENT_6_STREAM1  = ((6U << HAL_HSP_EVENT_PRIO_POS)
                              | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_6_TRGIN3   = ((6U << HAL_HSP_EVENT_PRIO_POS)
                              | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_6_TRGIN8   = ((6U << HAL_HSP_EVENT_PRIO_POS)
                              | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_6_HSEG     = ((6U << HAL_HSP_EVENT_PRIO_POS)
                              | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_6_CSEG     = ((6U << HAL_HSP_EVENT_PRIO_POS)
                              | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 7 source Matrix ****************************************************/
  HAL_HSP_EVENT_7_STREAM2  = ((7U << HAL_HSP_EVENT_PRIO_POS)
                              | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_7_TRGIN4   = ((7U << HAL_HSP_EVENT_PRIO_POS)
                              | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_7_TRGIN9   = ((7U << HAL_HSP_EVENT_PRIO_POS)
                              | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_7_HSEG     = ((7U << HAL_HSP_EVENT_PRIO_POS)
                              | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_7_CSEG     = ((7U << HAL_HSP_EVENT_PRIO_POS)
                              | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 8 source Matrix ****************************************************/
  HAL_HSP_EVENT_8_STREAM3  = ((8U << HAL_HSP_EVENT_PRIO_POS)
                              | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_8_TRGIN0   = ((8U << HAL_HSP_EVENT_PRIO_POS)
                              | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_8_TRGIN5   = ((8U << HAL_HSP_EVENT_PRIO_POS)
                              | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_8_HSEG     = ((8U << HAL_HSP_EVENT_PRIO_POS)
                              | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_8_CSEG     = ((8U << HAL_HSP_EVENT_PRIO_POS)
                              | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 9 source Matrix ****************************************************/
  HAL_HSP_EVENT_9_STREAM0  = ((9U << HAL_HSP_EVENT_PRIO_POS)
                              | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_9_TRGIN1   = ((9U << HAL_HSP_EVENT_PRIO_POS)
                              | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_9_TRGIN6   = ((9U << HAL_HSP_EVENT_PRIO_POS)
                              | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_9_HSEG     = ((9U << HAL_HSP_EVENT_PRIO_POS)
                              | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_9_CSEG     = ((9U << HAL_HSP_EVENT_PRIO_POS)
                              | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 10 source Matrix ***************************************************/
  HAL_HSP_EVENT_10_STREAM1  = ((10U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_10_TRGIN2   = ((10U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_10_TRGIN7   = ((10U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_10_HSEG     = ((10U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_10_CSEG     = ((10U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 11 source Matrix ***************************************************/
  HAL_HSP_EVENT_11_STREAM2  = ((11U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_11_TRGIN3   = ((11U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_11_TRGIN8   = ((11U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_11_HSEG     = ((11U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_11_CSEG     = ((11U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 12 source Matrix ***************************************************/
  HAL_HSP_EVENT_12_STREAM3  = ((12U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_12_TRGIN4   = ((12U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_12_TRGIN9   = ((12U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_12_HSEG     = ((12U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_12_CSEG     = ((12U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 13 source Matrix ***************************************************/
  HAL_HSP_EVENT_13_STREAM0  = ((13U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_13_TRGIN0   = ((13U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_13_TRGIN5   = ((13U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_13_HSEG     = ((13U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_13_CSEG     = ((13U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 14 source Matrix ***************************************************/
  HAL_HSP_EVENT_14_STREAM1  = ((14U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_14_TRGIN1   = ((14U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_14_TRGIN6   = ((14U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_14_HSEG     = ((14U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_14_CSEG     = ((14U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 15 source Matrix ***************************************************/
  HAL_HSP_EVENT_15_STREAM2  = ((15U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_15_TRGIN2   = ((15U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_15_TRGIN7   = ((15U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_15_HSEG     = ((15U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_15_CSEG     = ((15U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 16 source Matrix ***************************************************/
  HAL_HSP_EVENT_16_STREAM3  = ((16U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_16_TRGIN3   = ((16U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_16_TRGIN8   = ((16U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_16_HSEG     = ((16U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_16_CSEG     = ((16U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 17 source Matrix ***************************************************/
  HAL_HSP_EVENT_17_STREAM0  = ((17U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_17_TRGIN4   = ((17U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_17_TRGIN9   = ((17U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_17_HSEG     = ((17U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_17_CSEG     = ((17U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 18 source Matrix ***************************************************/
  HAL_HSP_EVENT_18_STREAM1  = ((18U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_18_TRGIN0   = ((18U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_18_TRGIN5   = ((18U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_18_HSEG     = ((18U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_18_CSEG     = ((18U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 19 source Matrix ***************************************************/
  HAL_HSP_EVENT_19_STREAM2  = ((19U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_19_TRGIN1   = ((19U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_19_TRGIN6   = ((19U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_19_HSEG     = ((19U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_19_CSEG     = ((19U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 20 source Matrix ***************************************************/
  HAL_HSP_EVENT_20_STREAM3  = ((20U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_20_TRGIN2   = ((20U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_20_TRGIN7   = ((20U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_20_HSEG     = ((20U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_20_CSEG     = ((20U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 21 source Matrix ***************************************************/
  HAL_HSP_EVENT_21_STREAM0  = ((21U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_21_TRGIN3   = ((21U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_21_TRGIN8   = ((21U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_21_HSEG     = ((21U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_21_CSEG     = ((21U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
  /* Event 22 source Matrix ***************************************************/
  HAL_HSP_EVENT_22_STREAM1  = ((22U << HAL_HSP_EVENT_PRIO_POS)
                               | (2U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_22_TRGIN4   = ((22U << HAL_HSP_EVENT_PRIO_POS)
                               | (3U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_22_TRGIN9   = ((22U << HAL_HSP_EVENT_PRIO_POS)
                               | (4U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_22_HSEG     = ((22U << HAL_HSP_EVENT_PRIO_POS)
                               | (5U << HAL_HSP_EVENT_SOURCE_POS)),
  HAL_HSP_EVENT_22_CSEG     = ((22U << HAL_HSP_EVENT_PRIO_POS)
                               | (6U << HAL_HSP_EVENT_SOURCE_POS)),
} HAL_HSP_EVENT_SourceTypeDef;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group5 HSP Stream Interface Types
  * @{
  */
/** Enumerate to define the ID of STREAM Interface */
typedef enum
{
  HAL_HSP_STREAM_BUFFER_0 = 0UL,
  HAL_HSP_STREAM_BUFFER_1 = 1UL,
  HAL_HSP_STREAM_BUFFER_2 = 2UL,
  HAL_HSP_STREAM_BUFFER_3 = 3UL,
} HAL_HSP_STREAM_BufferTypeDef;

/** Enumerate to define the STREAM Buffer direction */
typedef enum
{
  HAL_HSP_STREAM_BUFFER_DIRECTION_RX,
  HAL_HSP_STREAM_BUFFER_DIRECTION_TX,
} HAL_HSP_STREAM_Buffer_DirectionTypeDef;

/** Enumerate to define the state of Integer to Float conversion feature */
typedef enum
{
  HAL_HSP_STREAM_BUFFER_SYNC_DISABLE,
  HAL_HSP_STREAM_BUFFER_SYNC_ENABLE,
} HAL_HSP_STREAM_Buffer_Sync_StateTypeDef;

/** Enumerate to define the state of Integer to Float conversion feature */
typedef enum
{
  /** Conversion Integer to Float is disabled */
  HAL_HSP_STREAM_INT_TO_FLOAT_DISABLED,

  /** Conversion Integer to float is enabled */
  HAL_HSP_STREAM_INT_TO_FLOAT_ENABLED,
} HAL_HSP_STREAM_IntToFloat_StatusTypeDef;

/** STREAM configuration structure */
typedef struct
{
  /** STREAM Buffer direction TX or RX */
  HAL_HSP_STREAM_Buffer_DirectionTypeDef direction;

  /** Synchronize the STREAM Buffer with the STREAM Buffer +1 */
  HAL_HSP_STREAM_Buffer_Sync_StateTypeDef sync_state;
} HAL_HSP_STREAM_Buffer_ConfigTypeDef;

/** Enumerate to define the flag status of STREAM Event */
typedef enum
{
  HAL_HSP_STREAM_FLAG_NOT_ACTIVE = 0U,  /*!< Flag not active */
  HAL_HSP_STREAM_FLAG_ACTIVE     = 1U   /*!< Flag active     */
} HAL_HSP_STREAM_FLAG_StatusTypeDef;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group6 HSP Trigger Interface Types
  * @{
  */
/** Enumerate to define the Trigger polarity */
typedef enum
{
  HAL_HSP_TRGIN_POLARITY_RISING  = 0U,
  HAL_HSP_TRGIN_POLARITY_FALLING = 1U,
} HAL_HSP_TRGIN_PolarityTypeDef;

/** Enumerate to define the Trigger Interconnect Matrix */
typedef enum
{
  HAL_HSP_TRGIN_DMA1_CH1_TC,
  HAL_HSP_TRGIN_DMA1_CH2_TC,
  HAL_HSP_TRGIN_DMA1_CH3_TC,
  HAL_HSP_TRGIN_DMA1_CH4_TC,
  HAL_HSP_TRGIN_EXTI0,
  HAL_HSP_TRGIN_EXTI1,
  HAL_HSP_TRGIN_TIM1_TRGO,
  HAL_HSP_TRGIN_TIM1_TRGO2,
  HAL_HSP_TRGIN_TIM2_TRGO,
  HAL_HSP_TRGIN_TIM3_TRGO,
  HAL_HSP_TRGIN_TIM6_TRGO,
  HAL_HSP_TRGIN_TIM7_TRGO,
  HAL_HSP_TRGIN_TIM8_TRGO,
  HAL_HSP_TRGIN_TIM8_TRGO2,
  HAL_HSP_TRGIN_TIM15_TRGO,
  HAL_HSP_TRGIN_LPTIM1_CH1,
  HAL_HSP_TRGIN_LPTIM1_CH2,
  HAL_HSP_TRGIN_LPTIM2_CH1,
  HAL_HSP_TRGIN_LPTIM2_CH2,
  HAL_HSP_TRGIN_ADF1_SAD_DET
} HAL_HSP_TRGIN_SourceTypeDef;

/** Enumerate to define the enabling status of TRGIN instance */
typedef enum
{
  /** TRGIN is disabled */
  HAL_HSP_TRGIN_DISABLED = 0U,

  /** TRGIN is enabled */
  HAL_HSP_TRGIN_ENABLED  = 1U,
} HAL_HSP_TRGIN_StatusTypeDef;

/** TRIGGER configuration structure */
typedef struct
{
  /** Polarity of the TRGIN Interface */
  HAL_HSP_TRGIN_PolarityTypeDef polarity;

  /** ID of the source signal selected */
  HAL_HSP_TRGIN_SourceTypeDef source;
} HAL_HSP_TRGIN_ConfigTypeDef;

/** Enumerate to define the flag status of TRGIN Event or Error */
typedef enum
{
  HAL_HSP_TRGIN_FLAG_NOT_ACTIVE = 0U,  /*!< Flag not active */
  HAL_HSP_TRGIN_FLAG_ACTIVE     = 1U   /*!< Flag active     */
} HAL_HSP_TRGIN_FLAG_StatusTypeDef;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group7 HSP Event Types
  * @{
  */

/** Enumerate to define the Event Synchronization State */
typedef enum
{
  /** Event Synchronization must be disabled */
  HAL_HSP_EVENT_SYNC_DISABLE = 0U,

  /** Event Synchronization must be enabled */
  HAL_HSP_EVENT_SYNC_ENABLE  = 1U
} HAL_HSP_EVENT_Sync_StateTypeDef;

/** Event Synchronization structure */
typedef struct
{
  /** Task Comparator Unit used to monitor the end of task */
  HAL_HSP_TASK_ComparatorTypeDef tcu;

  /** Action to enable or disable the synchronization */
  HAL_HSP_EVENT_Sync_StateTypeDef state;
} HAL_HSP_EVENT_SyncTypeDef;

/** Event configuration structure */
typedef struct
{
  /** Event source */
  HAL_HSP_EVENT_SourceTypeDef source;

  /** Synchronize the event with the end of a task execution */
  HAL_HSP_EVENT_SyncTypeDef sync;
} HAL_HSP_EVENT_ConfigTypeDef;

/** HSP Polling Mode on End Of Event Status */
typedef enum
{
  /** Polling is termintated when all selected events occurred */
  HAL_HSP_POLLING_FOR_ALL_EVENT,

  /** Polling is terinated when almost one selected event occurred */
  HAL_HSP_POLLING_FOR_ANY_EVENT,
} HAL_HSP_POLLING_ModeTypeDef;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group8 HSP Trigger Output Types
  * @{
  */
/** HAL HSP Trigger Output Enumerate */
typedef enum
{
  HAL_HSP_OUTPUT_TRIGGER_0,
  HAL_HSP_OUTPUT_TRIGGER_1,
  HAL_HSP_OUTPUT_TRIGGER_2,
  HAL_HSP_OUTPUT_TRIGGER_3,
} HAL_HSP_OUTPUT_TriggerTypeDef;

/** HAL HSP Trigger Output Source */
typedef enum
{
  HAL_HSP_OUTPUT_TRIGGER_NONE  = 0U,  /*!< Disabled */
  HAL_HSP_OUTPUT_TRIGGER_STREAM = HSP_TRGOCFGR_TRGO0SRC_0, /*!< Trigger from STREAM Interface */
  HAL_HSP_OUTPUT_TRIGGER_CORE = HSP_TRGOCFGR_TRGO0SRC_1,   /*!< Trigger from SPE Core */
  HAL_HSP_OUTPUT_TRIGGER_TIMESTAMPCAPTURE = (HSP_TRGOCFGR_TRGO0SRC_0 | HSP_TRGOCFGR_TRGO0SRC_1),
  /*!< Trigger from TimeStamp Capture */
} HAL_HSP_OUTPUT_TRIGGER_SourceTypeDef;

/** HAL HSP Output status */
typedef enum
{
  HAL_HSP_OUTPUT_DISABLED = 0U,
  HAL_HSP_OUTPUT_ENABLED  = 1U,
} HAL_HSP_OUTPUT_StatusTypeDef;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group9  HSP TimeStamp Capture Types
  * @{
  */
/** HAL HSP TimeStamp Capture Prescaler */
typedef enum
{
  HAL_HSP_TSC_CAPTURE_MODE_SPE_BREAKS       = HSP_CAPCR_CAPMOD_0,
  HAL_HSP_TSC_CAPTURE_MODE_TASK_NBR_CHANGES = HSP_CAPCR_CAPMOD_1,
  HAL_HSP_TSC_CAPTURE_MODE_PFCT_NBR_CHANGES = (HSP_CAPCR_CAPMOD_1 | HSP_CAPCR_CAPMOD_0),
} HAL_HSP_TSC_Capture_ModeTypeDef;

/** HAL HSP TimeStamp Capture Prescaler */
typedef enum
{
  HAL_HSP_TSC_PRESCALER_BYPASSED = 0U,
  HAL_HSP_TSC_PRESCALER_DIV2     = HSP_CAPCR_PRESC_0,
  HAL_HSP_TSC_PRESCALER_DIV4     = HSP_CAPCR_PRESC_1,
  HAL_HSP_TSC_PRESCALER_DIV8     = HSP_CAPCR_PRESC_1 | HSP_CAPCR_PRESC_0,
  HAL_HSP_TSC_PRESCALER_DIV16    = HSP_CAPCR_PRESC_2,
  HAL_HSP_TSC_PRESCALER_DIV32    = HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_0,
  HAL_HSP_TSC_PRESCALER_DIV64    = HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_1,
  HAL_HSP_TSC_PRESCALER_DIV128   = HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_1 | HSP_CAPCR_PRESC_0,
  HAL_HSP_TSC_PRESCALER_DIV256   = HSP_CAPCR_PRESC_3,
  HAL_HSP_TSC_PRESCALER_DIV512   = HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_0,
  HAL_HSP_TSC_PRESCALER_DIV1024  = HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_1,
  HAL_HSP_TSC_PRESCALER_DIV2048  = HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_1 | HSP_CAPCR_PRESC_0,
  HAL_HSP_TSC_PRESCALER_DIV4096  = HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_2,
  HAL_HSP_TSC_PRESCALER_DIV8192  = HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_0,
  HAL_HSP_TSC_PRESCALER_DIV16384 = HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_1,
  HAL_HSP_TSC_PRESCALER_DIV32768 = HSP_CAPCR_PRESC_3 | HSP_CAPCR_PRESC_2 | HSP_CAPCR_PRESC_1 | HSP_CAPCR_PRESC_0,
} HAL_HSP_TSC_PrescalerTypeDef;

/** HAL HSP TimeStamp Capture Free Running Counter status */
typedef enum
{
  HAL_HSP_TSC_FREE_COUNTER_DISABLE = 0U,
  HAL_HSP_TSC_FREE_COUNTER_ENABLE  = HSP_CAPCR_FRCNTEN
} HAL_HSP_TSC_FreeRunningCounterStateTypeDef;

/** HAL HSP TimeStamp Capture Task Filter mode */
typedef enum
{
  HAL_HSP_TSC_TASK_FILTER_NONE    = 0U,
  HAL_HSP_TSC_TASK_FILTER_TSKCMP0 = HSP_CAPCR_TSKFLT
} HAL_HSP_TSC_TaskFilterTypeDef;

/** HAL HSP TimeStamp Capture configuration structure */
typedef struct
{
  /** Division ratio in order to define the time stamp granularity (For Free Counter mode only) */
  HAL_HSP_TSC_PrescalerTypeDef prescaler;

  /** Enable the Free counter mode */
  HAL_HSP_TSC_FreeRunningCounterStateTypeDef counter;

  /** Enable the filtering for a task monitored by the Task Comparator Unit 0 */
  HAL_HSP_TSC_TaskFilterTypeDef filter;
} HAL_HSP_TSC_ConfigTypeDef;

/** HAL HSP TimeStamp Capture status */
typedef enum
{
  HAL_HSP_TSC_DISABLED = 0U,
  HAL_HSP_TSC_ENABLED  = 1U,
} HAL_HSP_TSC_StatusTypeDef;

/** HAL HSP TimeStamp Data structure */
typedef struct
{
  /** Last captured task number */
  uint32_t task_number;

  /** IF instruction counter */
  uint32_t if_counter;

  /** IF condition history */
  uint32_t if_history;

  /** Time-stamp value */
  uint32_t timestamp;

  /** Last captured processing function number */
  uint32_t pfct_number;
} HAL_HSP_TSC_TimeStampTypeDef;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group10  HSP BRAM Types
  * @{
  */
/** HAL HSP BRAM Bandwidth Arbitration enumerate */
typedef enum
{
  HAL_HSP_BRAM_ARBITRATION_LATENCY_16_CYCLES = 0UL,
  HAL_HSP_BRAM_ARBITRATION_LATENCY_8_CYCLES  = HSP_CR_BARB_0,
  HAL_HSP_BRAM_ARBITRATION_LATENCY_4_CYCLES  = HSP_CR_BARB_1
} HAL_HSP_BRAM_ArbitrationTypeDef;

/**
  * @}
  */

/** @defgroup HSP_Exported_Types_Group12  HSP Debug Types
  * @{
  */
/** HAL HSP BREAK Output Definition */
typedef enum
{
  HAL_HSP_BREAK_OUTPUT_0 = 0U,
  HAL_HSP_BREAK_OUTPUT_1 = 1U,
  HAL_HSP_BREAK_OUTPUT_2 = 2U,
  HAL_HSP_BREAK_OUTPUT_3 = 3U
} HAL_HSP_BREAK_OutputTypeDef;

/** HAL HSP BREAK Critical Event status */
typedef enum
{
  HAL_HSP_BREAK_CRITICAL_EVENT_DISABLED = 0U,
  HAL_HSP_BREAK_CRITICAL_EVENT_ENABLED  = 1U
} HAL_HSP_BREAK_Critical_Event_StatusTypeDef;

/** HAL HSP BREAK Freeze Event status */
typedef enum
{
  HAL_HSP_BREAK_FREEZE_EVENT_DISABLED = 0U,
  HAL_HSP_BREAK_FREEZE_EVENT_ENABLED  = 1U
} HAL_HSP_BREAK_Freeze_Event_StatusTypeDef;

/** HAL HSP BREAK Freeze Event status */
typedef enum
{
  HAL_HSP_SPE_IT_DISABLED = 0U,
  HAL_HSP_SPE_IT_ENABLED  = 1U
} HAL_HSP_SPE_IT_StatusTypeDef;

/**
  * @}
  */
/** @defgroup HSP_Exported_Types_Group14  HSP Handle
  * @{
  */
/** HSP HAL Handle State enumeration */
typedef enum
{
  HAL_HSP_STATE_RESET          = 0UL,           /*!< HSP not yet initialized                                 */
  HAL_HSP_STATE_INIT           = (1UL << 31U),  /*!< HSP initialized but not yet configured                  */
  HAL_HSP_STATE_READY_TO_BOOT  = (1UL << 28U),  /*!< HSP DRAM FW loaded, Plugin can be loaded before to Boot */
  HAL_HSP_STATE_RUNNING        = (1UL << 27U),  /*!< HSP initialized, FW & Plugin Loaded and Boot completed  */
  HAL_HSP_STATE_FAULT          = (1UL << 0U)    /*!< HSP Boot uncoverable failure. A HW reset is required    */
} HAL_HSP_StateTypeDef;

/** HAL HSP Handle type definition */
typedef struct hal_hsp_handle_s HSP_HandleTypeDef;

#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
/** Pointer to a HSP callback function */
typedef void (*pHSP_CallbackTypeDef)(HSP_HandleTypeDef *hhsp);

/** Pointer to a HSP callback function taking 1 parameter in addition to the handle */
typedef void (*pHSP_OneParamCallbackTypeDef)(HSP_HandleTypeDef *hhsp, uint32_t value);

/** Pointer to a HSP callback function taking 2 parameters in addition to the handle */
typedef void (*pHSP_TwoParamsCallbackTypeDef)(HSP_HandleTypeDef *hhsp, uint32_t value1, uint32_t value2);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */

/** HAL HSP Handle Structure definition */
struct hal_hsp_handle_s
{
  /** HAL HSP instance */
  HSP_TypeDef *Instance;

  /** HSP global state */
  __IO HAL_HSP_StateTypeDef global_state;

  __IO uint32_t last_error_codes;  /*!< Errors limited to the last process
                                        This parameter can be a combination of @ref HSP_HAL_Error_Codes */
  __IO uint32_t boot_error_code;   /*!< Boot Error code
                                        This parameter can be a value of @ref HSP_Firmware_Error_Codes  */
  __IO uint32_t last_msgbox_error_code; /*!< MsgBox error code */

  /* CRAM/DRAM Memory region -------------------------------------------------*/
  /** Free CRAM Size in word */
  uint32_t cram_free_size_in_word;

  /** Free DRAM Size in word */
  uint32_t dram_free_size_in_word;

  /** CRAM Address to load the next plugin */
  uint32_t cram_address_for_plugin;

  /** Address of HSP Performance Counter */
  uint32_t *p_perf_counter;

  /* CNN Safe mode -----------------------------------------------------------*/
  /** Store the status of Enabled Interface */
  uint32_t backup_enabled_itfs;

  /** Store the status of Enabled Events */
  uint32_t backup_enabled_events;

  /** Store the status of Enabled Event Interrupts */
  uint32_t backup_event_its;

  /** Store the status of Enabled Processing Function Event Interrupts */
  uint32_t backup_pfctevt_its;

  /* Sub-Routine for IRQ Handlers --------------------------------------------*/
  /** HSP subroutine to process STREAM buffer Events */
  void(*stream_handler)(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr);

  /** HSP subroutine to process Task Comparator Unit Events */
  void(*tcu_handler)(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr);

  /** HSP subroutine to process SPE Events */
  void(*spe_handler)(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr);

  /** HSP subroutine to process Timestamp Capture Events */
  void(*tsc_handler)(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr);

  /** HSP subroutine to process Command Events */
  void(*cmd_handler)(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr);

  /** HSP subroutine to process STREAM buffer Errors */
  void(*stream_err_handler)(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors);

  /** HSP subroutine to process TRGIN Errors */
  void(*trgin_err_handler)(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors);

  /** HSP subroutine to process Timestamp Capture Errors */
  void(*tsc_err_handler)(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors);

  /** HSP subroutine to process SPE Errors */
  void(*spe_err_handler)(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors);

  /** HSP subroutine to process Processing Function Events */
  void(*fwevt_handler)(HSP_HandleTypeDef *hhsp, uint32_t reg_fwevt_misr);

  /* Interrupts callbacks ----------------------------------------------------*/
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
  /** HSP SPE Run State callback function pointer */
  void (* EVT_SPE_RunStateCallback)(HSP_HandleTypeDef *hhsp, uint32_t state);

  /** HSP SPE Task Completed callback function pointer */
  void (* EVT_SPE_TaskCpltCallback)(HSP_HandleTypeDef *hhsp);

  /** HSP SPE Direct Command Completed callback function pointer */
  void (* EVT_SPE_DirectCommandCpltCallback)(HSP_HandleTypeDef *hhsp);

  /** HSP SPE FPU Saturation event callback function pointer */
  void (* EVT_SPE_FPUSaturationCallback)(HSP_HandleTypeDef *hhsp);

  /** HSP Timestamp Capture Data Ready callback function pointer */
  void (* EVT_TSC_TimestampReadyCallback)(HSP_HandleTypeDef *hhsp, uint32_t timestamp);

  /** HSP Task Comparator Unit Task Started callback function pointer */
  void (* EVT_TCU_TaskStartedCallback)(HSP_HandleTypeDef *hhsp, uint32_t comparators_mask);

  /** HSP Task Comparator Unit Task Ended callback function pointer */
  void (* EVT_TCU_TaskEndedCallback)(HSP_HandleTypeDef *hhsp, uint32_t comparators_mask);

  /** HSP Task Overlap event callback function pointer */
  void (* EVT_TCU_TaskOverlapCallback)(HSP_HandleTypeDef *hhsp);

  /** HSP STREAM Buffer Empty callback function pointer */
  void (* EVT_STREAM_BufferEmptyCallback)(HSP_HandleTypeDef *hhsp, uint32_t buffers_mask);

  /** HSP STREAM Buffer Full callback function pointer */
  void (* EVT_STREAM_BufferFullCallback)(HSP_HandleTypeDef *hhsp, uint32_t buffers_mask);

  /** HSP Processing Function Event callback function pointer */
  void (* FWEVT_ProcessingEventCallback)(HSP_HandleTypeDef *hhsp, uint32_t events_mask);

  /** HSP Error callback function pointer */
  void (* ErrorCallback)(HSP_HandleTypeDef *hhsp, uint32_t fw_error_code, uint32_t spe_error_inf);

  /** HSP MSP Init callback function pointer */
  void (* MspInitCallback)(HSP_HandleTypeDef *hhsp);

  /** HSP MSP DeInit callback function pointer */
  void (* MspDeInitCallback)(HSP_HandleTypeDef *hhsp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
};

/** HAL HSP Capabilities Structure definition */
typedef struct
{
  uint32_t bramab_base_address;
  uint32_t bramab_size_byte;
  uint32_t brama_base_address;
  uint32_t bramb_base_address;

} HAL_HSP_CapabilitiesTypeDef;

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
HAL_StatusTypeDef HAL_HSP_Init(HSP_HandleTypeDef *hhsp);
HAL_StatusTypeDef HAL_HSP_DeInit(HSP_HandleTypeDef *hhsp);
void HAL_HSP_MspInit(HSP_HandleTypeDef *hhsp);
void HAL_HSP_MspDeInit(HSP_HandleTypeDef *hhsp);

/* Firmware/Plugin functions **************************************************/
HAL_StatusTypeDef HAL_HSP_LoadFirmware(HSP_HandleTypeDef *hhsp,
                                       const uint8_t *p_cram_bin, uint32_t cram_size_bytes,
                                       const uint8_t *p_dram_bin, uint32_t dram_size_bytes);
HAL_StatusTypeDef HAL_HSP_LoadPlugin(HSP_HandleTypeDef *hhsp, const uint8_t *p_plugin_bin, uint32_t size_bytes);

/* Boot functions *************************************************************/
HAL_StatusTypeDef HAL_HSP_Boot(HSP_HandleTypeDef *hhsp, const HAL_HSP_Boot_ConfigTypeDef *p_config,
                               uint32_t timeout_ms);
uint32_t HAL_HSP_GetFirmwareVersion(const HSP_HandleTypeDef *hhsp);

HAL_StatusTypeDef HAL_HSP_GetCapabilities(HSP_HandleTypeDef *hhsp, HAL_HSP_CapabilitiesTypeDef *p_capabilities);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group2  HSP Command Management
  * @{
  */
/**
  * @brief  Write a Command into the Direct Command interface.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  cmd_id  Command ID
  */
__STATIC_FORCEINLINE void HAL_HSP_DIRECT_WriteCommand(const HSP_HandleTypeDef *hhsp, uint32_t cmd_id)
{
  HSP_TypeDef *p_hspx = hhsp->Instance;
  STM32_WRITE_REG(p_hspx->DCMDIDR, cmd_id);
}

/**
  * @brief  Write a Data Pointer into the Direct Command interface.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  ptr_id  Data Pointer ID
  * @param  data_address  Data Address
  */
__STATIC_FORCEINLINE void HAL_HSP_DIRECT_WriteDataPointer(const HSP_HandleTypeDef *hhsp,
                                                          HAL_HSP_DIRECT_CMD_Data_PtrTypeDef ptr_id,
                                                          uint32_t data_address)
{
  __IO uint32_t *reg_ptr0 = (uint32_t __IO *) & (((HSP_TypeDef *)(uint32_t)(hhsp->Instance))->DCMDPTR0);
  STM32_WRITE_REG(reg_ptr0[(uint32_t)ptr_id], data_address);
}

/**
  * @brief  Fill a parameter for any HSP command for DCMD or MSGBox interfaces.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  param_id  ID of parameter
  * @param  value     value.
  */
__STATIC_FORCEINLINE void HAL_HSP_WriteParameter(const HSP_HandleTypeDef *hhsp,
                                                 HAL_HSP_PARAMTypeDef param_id, uint32_t value)
{
  __IO uint32_t *reg_param0 = (uint32_t __IO *) & (((HSP_TypeDef *)(uint32_t)(hhsp->Instance))->PARAMR0);

  STM32_WRITE_REG(reg_param0[(uint32_t)param_id], value);
}

/**
  * @brief  Return the value of a parameter.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  param_id  ID of parameter
  * @return  Value.
  */
__STATIC_FORCEINLINE uint32_t HAL_HSP_ReadParameter(const HSP_HandleTypeDef *hhsp, HAL_HSP_PARAMTypeDef param_id)
{
  const __IO uint32_t *reg_param0 = (uint32_t volatile *) & (hhsp->Instance->PARAMR0);

  return STM32_READ_REG(reg_param0[(uint32_t)param_id]);
}

HAL_StatusTypeDef HAL_HSP_DIRECT_WaitEndOfCommand(const HSP_HandleTypeDef *hhsp, uint32_t timeout_ms);

/**
  * @brief Get the status of Direct Command processing.
  * @param hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_HSP_DIRECT_CMD_BUSY   Direct Command is in progress.
  * @retval HAL_HSP_DIRECT_CMD_READY  Direct Command Interface is readay for a new process.
  */
__STATIC_FORCEINLINE HAL_HSP_DIRECT_CMD_StatusTypeDef HAL_HSP_DIRECT_IsCommandReady(const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx = hhsp->Instance;

  return ((STM32_READ_BIT(p_hspx->DCMDSR, HSP_DCMDSR_DCBSY) != 0U) ? HAL_HSP_DIRECT_CMD_BUSY :
          HAL_HSP_DIRECT_CMD_READY);
}

HAL_StatusTypeDef HAL_HSP_MSGBOX_SendCommand(HSP_HandleTypeDef *hhsp, uint32_t cmd_id, uint32_t timeout_ms);

/**
  * @brief Get the Status of MSGBox Semaphore (CPU side).
  * @param hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_HSP_MSGBOX_SEMAPHORE_NO_MSG         No Message.
  * @retval HAL_HSP_MSGBOX_SEMAPHORE_MSG_AVAILABLE  A Message is ready to be read.
  */
__STATIC_FORCEINLINE HAL_HSP_MSGBOX_Semaphore_StatusTypeDef HAL_HSP_MSGBOX_IsMsgAvailable(
  const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx = hhsp->Instance;

  return ((STM32_READ_BIT(p_hspx->H2CSEMR, HSP_H2CSEMR_H2CSEM) != 0U) ? HAL_HSP_MSGBOX_SEMAPHORE_MSG_AVAILABLE :
          HAL_HSP_MSGBOX_SEMAPHORE_NO_MSG);
}

/**
  * @brief Release the MSGBOX Semaphore to signal the CPU has read the HSP message.
  * @param hhsp  Pointer to a @ref HSP_HandleTypeDef.
  */
__STATIC_FORCEINLINE void HAL_HSP_MSGBOX_ReleaseSemaphore(const HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx = hhsp->Instance;

  STM32_SET_BIT(p_hspx->H2CSEMR, HSP_H2CSEMR_H2CSEM);
}

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group3_2 HSP STREAM Interface
  * @{
  */
/* STREAM Interface ----------------------------------------------------------*/
HAL_StatusTypeDef HAL_HSP_STREAM_SetConfig(HSP_HandleTypeDef *hhsp, HAL_HSP_STREAM_BufferTypeDef stream_id,
                                           const HAL_HSP_STREAM_Buffer_ConfigTypeDef *p_config);
HAL_StatusTypeDef HAL_HSP_STREAM_GetConfig(HSP_HandleTypeDef *hhsp, HAL_HSP_STREAM_BufferTypeDef stream_id,
                                           HAL_HSP_STREAM_Buffer_ConfigTypeDef *p_config);

HAL_StatusTypeDef HAL_HSP_STREAM_Start(HSP_HandleTypeDef *hhsp,
                                       uint32_t interrupt_evt_mask, uint32_t interrupt_err_mask);
HAL_StatusTypeDef HAL_HSP_STREAM_Stop(HSP_HandleTypeDef *hhsp);

HAL_StatusTypeDef HAL_HSP_STREAM_EnableIntToFloat(const HSP_HandleTypeDef *hhsp);
HAL_StatusTypeDef HAL_HSP_STREAM_DisableIntToFloat(const HSP_HandleTypeDef *hhsp);
HAL_HSP_STREAM_IntToFloat_StatusTypeDef HAL_HSP_STREAM_IsEnabledIntToFloat(const HSP_HandleTypeDef *hhsp);

/**
  * @brief  Write a data into the STREAM Buffer.
  * @param  hhsp       Pointer to a HSP_HandleTypeDef.
  * @param  stream_id  STREAM Buffer id.
  * @param  value      Value to be written.
  */
__STATIC_INLINE void HAL_HSP_STREAM_WriteBufferData(HSP_HandleTypeDef *hhsp,
                                                    HAL_HSP_STREAM_BufferTypeDef stream_id,
                                                    uint32_t value)
{
  HSP_TypeDef *p_hspx = hhsp->Instance;

  STM32_WRITE_REG(p_hspx->BUFFDR[(uint32_t)stream_id], value);
}

/**
  * @brief  Read the value from the STREAM Buffer.
  * @param  hhsp       Pointer to a HSP_HandleTypeDef.
  * @param  stream_id  STREAM Buffer id.
  * @return Return the value from the STREAM Buffer Operation completed successfully.
  */
__STATIC_INLINE uint32_t HAL_HSP_STREAM_ReadBufferData(const HSP_HandleTypeDef *hhsp,
                                                       HAL_HSP_STREAM_BufferTypeDef stream_id)
{
  const HSP_TypeDef *p_hspx = hhsp->Instance;

  return STM32_READ_REG(p_hspx->BUFFDR[(uint32_t)stream_id]);
}

/**
  * @brief  Check whether the selected HSP STREAM Buffer flag is set or not.
  * @param  hhsp  Pointer to a HSP_HandleTypeDef.
  * @param  flag  specifies the HSP flag to check
  *         This parameter can be one of the following values:
  *            @arg HAL_HSP_FLAG_EVT_STREAM_BUFFER_0: HSP STREAM Buffer 0 Ready flag
  *            @arg HAL_HSP_FLAG_EVT_STREAM_BUFFER_1: HSP STREAM Buffer 1 Ready flag
  *            @arg HAL_HSP_FLAG_EVT_STREAM_BUFFER_2: HSP STREAM Buffer 2 Ready flag
  *            @arg HAL_HSP_FLAG_EVT_STREAM_BUFFER_3: HSP STREAM Buffer 3 Ready flag
  * @return retrieve the status of the selected HSP flag.
  */
__STATIC_INLINE HAL_HSP_STREAM_FLAG_StatusTypeDef HAL_HSP_STREAM_IsActiveFlag_Event(const HSP_HandleTypeDef *hhsp,
    uint32_t flag)
{
  const HSP_TypeDef *p_hspx = hhsp->Instance;

  return ((STM32_READ_BIT(p_hspx->EVT_ISR, flag) != 0U) ? HAL_HSP_STREAM_FLAG_ACTIVE : HAL_HSP_STREAM_FLAG_NOT_ACTIVE);
}

/**
  * @brief  Check whether the selected HSP STREAM Buffer Error flag is set or not.
  * @param  hhsp  Pointer to a HSP_HandleTypeDef.
  * @param  flag  specifies the HSP flag to check
  *         This parameter can be one of the following values:
  *            @arg HAL_HSP_FLAG_ERR_STREAM_BUFFER_0: HSP STREAM Buffer 0 TX UDR / RX OVR flag
  *            @arg HAL_HSP_FLAG_ERR_STREAM_BUFFER_1: HSP STREAM Buffer 1 TX UDR / RX OVR flag
  *            @arg HAL_HSP_FLAG_ERR_STREAM_BUFFER_2: HSP STREAM Buffer 2 TX UDR / RX OVR flag
  *            @arg HAL_HSP_FLAG_ERR_STREAM_BUFFER_3: HSP STREAM Buffer 3 TX UDR / RX OVR flag
  * @return retrieve the status of the selected HSP flag.
  */
__STATIC_INLINE HAL_HSP_STREAM_FLAG_StatusTypeDef HAL_HSP_STREAM_IsActiveFlag_Error(const HSP_HandleTypeDef *hhsp,
    uint32_t flag)
{
  const HSP_TypeDef *p_hspx = hhsp->Instance;

  return ((STM32_READ_BIT(p_hspx->ERR_ISR, flag) != 0U) ? HAL_HSP_STREAM_FLAG_ACTIVE : HAL_HSP_STREAM_FLAG_NOT_ACTIVE);
}

/** @brief  Clears the specified HSP STREAM Buffer Error flag.
  * @param  hhsp  Pointer to a HSP_HandleTypeDef.
  * @param  flags specifies the HSP clear register flag that needs to be set
  *         This parameter can be any combination of the following values:
  *            @arg HAL_HSP_FLAG_ERR_STREAM_BUFFER_0: HSP STREAM Buffer 0 TX UDR / RX OVR flag
  *            @arg HAL_HSP_FLAG_ERR_STREAM_BUFFER_1: HSP STREAM Buffer 1 TX UDR / RX OVR flag
  *            @arg HAL_HSP_FLAG_ERR_STREAM_BUFFER_2: HSP STREAM Buffer 2 TX UDR / RX OVR flag
  *            @arg HAL_HSP_FLAG_ERR_STREAM_BUFFER_3: HSP STREAM Buffer 3 TX UDR / RX OVR flag
  *            @arg HAL_HSP_FLAG_ERR_STREAM_BUFFER_ALL:  All HSP STREAM Buffer Error flags
  */
__STATIC_INLINE void HAL_HSP_STREAM_ClearFlag_Error(const HSP_HandleTypeDef *hhsp, uint32_t flags)
{
  HSP_TypeDef *p_hspx = hhsp->Instance;

  STM32_WRITE_REG(p_hspx->ERR_ICR, flags);
}

volatile uint32_t *HAL_HSP_STREAM_GetBufferAddress(const HSP_HandleTypeDef *hhsp,
                                                   HAL_HSP_STREAM_BufferTypeDef stream_id);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group3_3 HSP TRGIN Interface
  * @{
  */
/* TRGIN Interface -----------------------------------------------------------*/
HAL_StatusTypeDef HAL_HSP_TRGIN_SetConfig(HSP_HandleTypeDef *hhsp, uint32_t trgin_ids,
                                          const HAL_HSP_TRGIN_ConfigTypeDef *p_config);
HAL_StatusTypeDef HAL_HSP_TRGIN_GetConfig(HSP_HandleTypeDef *hhsp, uint32_t trgin_id,
                                          HAL_HSP_TRGIN_ConfigTypeDef *p_config);

HAL_StatusTypeDef HAL_HSP_TRGIN_Enable(HSP_HandleTypeDef *hhsp, uint32_t trgin_ids);
HAL_StatusTypeDef HAL_HSP_TRGIN_Disable(HSP_HandleTypeDef *hhsp, uint32_t trgin_ids);
HAL_HSP_TRGIN_StatusTypeDef HAL_HSP_TRGIN_IsEnabled(const HSP_HandleTypeDef *hhsp, uint32_t trgin_id);

HAL_StatusTypeDef HAL_HSP_TRGIN_EnableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts);
HAL_StatusTypeDef HAL_HSP_TRGIN_DisableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts);
uint32_t HAL_HSP_TRGIN_IsEnabledIT(const HSP_HandleTypeDef *hhsp, uint32_t interrupts);

/**
  * @brief  Check whether the HSP TRGIN Overrun Error flag is set or not.
  * @param  hhsp specifies the HSP Handle.
  * @return retrieve the status of the selected HSP flag.
  */
__STATIC_INLINE HAL_HSP_TRGIN_FLAG_StatusTypeDef HAL_HSP_TRGIN_IsActiveFlag_Overrun(const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx = hhsp->Instance;

  return ((STM32_READ_BIT(p_hspx->ERR_ISR, HAL_HSP_FLAG_ERR_TRGIN_OVR) != 0U) ? HAL_HSP_TRGIN_FLAG_ACTIVE :
          HAL_HSP_TRGIN_FLAG_NOT_ACTIVE);
}

/** @brief  Clear the specified HSP TRGIN Overrun Error flag status.
  * @param  hhsp specifies the HSP Handle.
  */
__STATIC_INLINE void HAL_HSP_TRGIN_ClearFlag_Overrun(const HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx = hhsp->Instance;

  STM32_WRITE_REG(p_hspx->ERR_ICR, HAL_HSP_FLAG_ERR_TRGIN_OVR);
}

uint32_t HAL_HSP_TRGIN_GetOverrun(const HSP_HandleTypeDef *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group3_4 HSP Event Common management
  * @{
  */
/* Event Management ----------------------------------------------------------*/
HAL_StatusTypeDef HAL_HSP_EVENT_SetConfig(HSP_HandleTypeDef *hhsp,
                                          const HAL_HSP_EVENT_ConfigTypeDef *p_config);
HAL_StatusTypeDef HAL_HSP_EVENT_GetConfig(HSP_HandleTypeDef *hhsp, uint32_t event_id,
                                          HAL_HSP_EVENT_ConfigTypeDef *p_config);
HAL_StatusTypeDef HAL_HSP_EVENT_Enable(HSP_HandleTypeDef *hhsp, uint32_t events);
HAL_StatusTypeDef HAL_HSP_EVENT_Disable(HSP_HandleTypeDef *hhsp, uint32_t events);
uint32_t HAL_HSP_EVENT_GetStatus(const HSP_HandleTypeDef *hhsp);

/* API to run the execution of a Processing List with CSEG ********************/
HAL_StatusTypeDef HAL_HSP_EVENT_RequestSWTrigger(HSP_HandleTypeDef *hhsp, uint32_t events);

HAL_StatusTypeDef HAL_HSP_EVENT_PollForPending(HSP_HandleTypeDef *hhsp, HAL_HSP_POLLING_ModeTypeDef poll_mode,
                                               uint32_t events, uint32_t timeout_ms,
                                               uint32_t *p_events_status);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group4 HSP Power Consumption Control
  * @{
  */
/* Power Consumption Control **************************************************/
HAL_StatusTypeDef HAL_HSP_SMARTCLOCKING_Enable(HSP_HandleTypeDef *hhsp, uint32_t clocks);
HAL_StatusTypeDef HAL_HSP_SMARTCLOCKING_Disable(HSP_HandleTypeDef *hhsp, uint32_t clocks);
uint32_t HAL_HSP_SMARTCLOCKING_IsEnabled(const HSP_HandleTypeDef *hhsp, uint32_t clock);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group5 HSP Task Comparator management
  * @{
  */
/* Start/End of Task Detector ------------------------------------------------*/
HAL_StatusTypeDef HAL_HSP_TCU_StartComparator(HSP_HandleTypeDef *hhsp,
                                              HAL_HSP_TASK_ComparatorTypeDef tcu_id, HAL_HSP_TaskTypeDef task_id,
                                              uint32_t interrupts);
HAL_StatusTypeDef HAL_HSP_TCU_StopComparator(HSP_HandleTypeDef *hhsp, HAL_HSP_TASK_ComparatorTypeDef tcu_id);

/* Task Overlap Detector -----------------------------------------------------*/
HAL_StatusTypeDef HAL_HSP_TCU_StartOverlapDetector(HSP_HandleTypeDef *hhsp,
                                                   HAL_HSP_TaskTypeDef lower_task_id,
                                                   HAL_HSP_TaskTypeDef higher_task_id,
                                                   uint32_t interrupts);
HAL_StatusTypeDef HAL_HSP_TCU_StopOverlapDetector(HSP_HandleTypeDef *hhsp);

/* Events/Interrupts Management ----------------------------------------------*/
HAL_StatusTypeDef HAL_HSP_TCU_PollForEvent(HSP_HandleTypeDef *hhsp,
                                           HAL_HSP_POLLING_ModeTypeDef poll_mode, uint32_t flags,
                                           uint32_t timeout_ms, uint32_t *p_flags_status);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group6 HSP Trigger Output management
  * @{
  */
HAL_StatusTypeDef HAL_HSP_OUTPUT_SetConfigTrigger(HSP_HandleTypeDef *hhsp,
                                                  HAL_HSP_OUTPUT_TriggerTypeDef id,
                                                  HAL_HSP_OUTPUT_TRIGGER_SourceTypeDef source);
HAL_HSP_OUTPUT_TRIGGER_SourceTypeDef HAL_HSP_OUTPUT_GetConfigTrigger(const HSP_HandleTypeDef *hhsp,
                                                                     HAL_HSP_OUTPUT_TriggerTypeDef id);
HAL_StatusTypeDef HAL_HSP_OUTPUT_Enable(HSP_HandleTypeDef *hhsp);
HAL_StatusTypeDef HAL_HSP_OUTPUT_Disable(HSP_HandleTypeDef *hhsp);
HAL_HSP_OUTPUT_StatusTypeDef HAL_HSP_OUTPUT_IsEnabled(const HSP_HandleTypeDef *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group7 HSP Timestamp Capture
  * @{
  */
HAL_StatusTypeDef HAL_HSP_TSC_SetConfig(HSP_HandleTypeDef *hhsp, const HAL_HSP_TSC_ConfigTypeDef *p_config);
HAL_StatusTypeDef HAL_HSP_TSC_GetConfig(HSP_HandleTypeDef *hhsp, HAL_HSP_TSC_ConfigTypeDef *p_config);

/* Polling */
HAL_StatusTypeDef HAL_HSP_TSC_Enable(HSP_HandleTypeDef *hhsp, HAL_HSP_TSC_Capture_ModeTypeDef cap_mode);
HAL_StatusTypeDef HAL_HSP_TSC_Disable(HSP_HandleTypeDef *hhsp);

uint32_t HAL_HSP_TSC_IsActiveFlag(const HSP_HandleTypeDef *hhsp);
HAL_StatusTypeDef HAL_HSP_TSC_GetTimeStamp(HSP_HandleTypeDef *hhsp, HAL_HSP_TSC_TimeStampTypeDef *p_timestamp);

/* IT */
HAL_StatusTypeDef HAL_HSP_TSC_Enable_IT(HSP_HandleTypeDef *hhsp, HAL_HSP_TSC_Capture_ModeTypeDef cap_mode);
HAL_StatusTypeDef HAL_HSP_TSC_Disable_IT(HSP_HandleTypeDef *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group8 HSP Performance
  * @{
  */
/* BRAM Access Control -------------------------------------------------------*/
HAL_StatusTypeDef HAL_HSP_BRAM_EnableConflictAccessCounter(const HSP_HandleTypeDef *hhsp);
HAL_StatusTypeDef HAL_HSP_BRAM_DisableConflictAccessCounter(const HSP_HandleTypeDef *hhsp);
uint32_t HAL_HSP_BRAM_IsEnabledConflictAccessCounter(const HSP_HandleTypeDef *hhsp);
uint32_t HAL_HSP_BRAM_GetConflictAccessCounter(const HSP_HandleTypeDef *hhsp);
HAL_StatusTypeDef HAL_HSP_BRAM_SetBandwidthArbitration(const HSP_HandleTypeDef *hhsp,
                                                       HAL_HSP_BRAM_ArbitrationTypeDef mode);
HAL_HSP_BRAM_ArbitrationTypeDef HAL_HSP_BRAM_GetBandwidthArbitration(const HSP_HandleTypeDef *hhsp);

/* SPE Performance Monitoring ------------------------------------------------*/
uint32_t HAL_HSP_GetPerformanceCycleCount(const HSP_HandleTypeDef *hhsp);

/**
  * @brief  Get the Firmware Error interrupt status.
  * @param  hhsp  Pointer to a HSP_HandleTypeDef.
  * @return The state of flag: 1 or 0.
  */
__STATIC_INLINE uint8_t HAL_HSP_IsActiveFlag_FirmwareError(const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx = hhsp->Instance;

  return (uint8_t)((STM32_READ_BIT(p_hspx->ERR_ISR, HSP_ERR_ISR_FWERRF) != 0U) ? 1U : 0U);
}

/**
  * @brief  Clear Firmware Error Flag.
  * @param  hhsp  Pointer to a HSP_HandleTypeDef.
  */
__STATIC_INLINE void HAL_HSP_ClearFlag_FirmwareError(const HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx = hhsp->Instance;

  STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_FWERRC);
}

uint32_t HAL_HSP_GetFirmwareError(const HSP_HandleTypeDef *hhsp);

/* SPE Interrupts ------------------------------------------------------------*/
HAL_StatusTypeDef HAL_HSP_SPE_EVENT_EnableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts);
HAL_StatusTypeDef HAL_HSP_SPE_EVENT_DisableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts);
HAL_HSP_SPE_IT_StatusTypeDef HAL_HSP_SPE_EVENT_IsEnabledIT(const HSP_HandleTypeDef *hhsp, uint32_t interrupt);

HAL_StatusTypeDef HAL_HSP_SPE_ERROR_EnableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts);
HAL_StatusTypeDef HAL_HSP_SPE_ERROR_DisableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts);
HAL_HSP_SPE_IT_StatusTypeDef HAL_HSP_SPE_ERROR_IsEnabledIT(const HSP_HandleTypeDef *hhsp, uint32_t interrupt);

/** @brief  Clears the specified HSP SPE flag.
  * @param  hhsp  Pointer to a HSP_HandleTypeDef.
  * @param  flags specifies the HSP clear register flag that needs to be set
  *         This parameter can be any combination of the following values:
  *            @arg HAL_HSP_FLAG_EVT_SPE_ENTER_IN_WFE: HSP SPE Enter In WFE mode flag
  *            @arg HAL_HSP_FLAG_EVT_SPE_EXIT_FROM_WFE: HSP SPE Exit From WFE mode flag
  */
__STATIC_INLINE void HAL_HSP_SPE_ClearFlag_Event(const HSP_HandleTypeDef *hhsp, uint32_t flags)
{
  HSP_TypeDef *p_hspx = hhsp->Instance;

  STM32_WRITE_REG(p_hspx->EVT_ICR, flags);
}

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group9 HSP Snoop
  * @{
  */
HAL_StatusTypeDef HAL_HSP_SNOOP_Enable(const HSP_HandleTypeDef *hhsp, uint32_t signals);
HAL_StatusTypeDef HAL_HSP_SNOOP_Disable(const HSP_HandleTypeDef *hhsp, uint32_t group_id);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group10 HSP Break Interface
  * @{
  */
HAL_StatusTypeDef HAL_HSP_BREAK_EnableCriticalEvent(const HSP_HandleTypeDef *hhsp,
                                                    HAL_HSP_BREAK_OutputTypeDef output_id, uint32_t events);
HAL_StatusTypeDef HAL_HSP_BREAK_DisableCriticalEvent(const HSP_HandleTypeDef *hhsp,
                                                     HAL_HSP_BREAK_OutputTypeDef output_id, uint32_t events);
HAL_HSP_BREAK_Critical_Event_StatusTypeDef HAL_HSP_BREAK_IsEnabledCriticalEvent(const HSP_HandleTypeDef *hhsp,
                                                                                HAL_HSP_BREAK_OutputTypeDef output_id,
                                                                                uint32_t event);

HAL_StatusTypeDef HAL_HSP_BREAK_EnableFreezeEvent(const HSP_HandleTypeDef *hhsp, uint32_t events);
HAL_StatusTypeDef HAL_HSP_BREAK_DisableFreezeEvent(const HSP_HandleTypeDef *hhsp, uint32_t events);
HAL_HSP_BREAK_Freeze_Event_StatusTypeDef HAL_HSP_BREAK_IsEnabledFreezeEvent(const HSP_HandleTypeDef *hhsp,
                                                                            uint32_t event);
/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group11 HSP Protection
  * @{
  */
HAL_StatusTypeDef HAL_HSP_Lock(const HSP_HandleTypeDef *hhsp);

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group12 HSP Processing List management
  * @{
  */
HAL_StatusTypeDef HAL_HSP_TASK_Run(const HSP_HandleTypeDef *hhsp, HAL_HSP_TaskTypeDef task_id, uint32_t timeout_ms);
HAL_StatusTypeDef HAL_HSP_TASK_Run_IT(HSP_HandleTypeDef *hhsp, HAL_HSP_TaskTypeDef task_id);

/* Processing Function Notification Management */
/* API to manage the 32 flags for Process */
HAL_StatusTypeDef HAL_HSP_PROCLIST_PollForNotification(HSP_HandleTypeDef *hhsp,
                                                       HAL_HSP_POLLING_ModeTypeDef poll_mode, uint32_t pfct_events,
                                                       uint32_t timeout_ms, uint32_t *p_pfct_events_status);
HAL_StatusTypeDef HAL_HSP_PROCLIST_EnableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts);
HAL_StatusTypeDef HAL_HSP_PROCLIST_DisableIT(const HSP_HandleTypeDef *hhsp, uint32_t interrupts);
uint32_t HAL_HSP_PROCLIST_IsEnabledIT(const HSP_HandleTypeDef *hhsp, uint32_t interrupts);
/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group11_1 HSP CNN Safe Mode Execution
  * @{
  */
HAL_StatusTypeDef HAL_HSP_CNN_EnterSafeMode(HSP_HandleTypeDef *hhsp);
HAL_StatusTypeDef HAL_HSP_CNN_ExitSafeMode(const HSP_HandleTypeDef *hhsp);

/**
  * @brief Send a CNN command.
  * @param hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param cnn_cmd_id  CNN command id.
  * @note  This function is dedicated for CNN function usage.
  */
__STATIC_FORCEINLINE void HAL_HSP_CNN_Run(const HSP_HandleTypeDef *hhsp, uint32_t cnn_cmd_id)
{
  HSP_TypeDef *p_hspx = hhsp->Instance;

  STM32_WRITE_REG(p_hspx->CDEGR, cnn_cmd_id);
}

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group13 HSP IRQ Handler and Callbacks functions
  * @{
  */
/* Global IRQ Handler *********************************************************/
void HAL_HSP_IRQHandler(HSP_HandleTypeDef *hhsp);

/* Event IRQ Handlers and Callbacks *******************************************/
void HAL_HSP_EVT_IRQHandler(HSP_HandleTypeDef *hhsp);

void HAL_HSP_EVT_SPE_DirectCommandCpltCallback(HSP_HandleTypeDef *hhsp);
void HAL_HSP_EVT_SPE_TaskCpltCallback(HSP_HandleTypeDef *hhsp);
void HAL_HSP_EVT_SPE_FPUSaturationCallback(HSP_HandleTypeDef *hhsp);
void HAL_HSP_EVT_SPE_RunStateCallback(HSP_HandleTypeDef *hhsp, uint32_t state);
void HAL_HSP_EVT_STREAM_BufferEmptyCallback(HSP_HandleTypeDef *hhsp, uint32_t buffers_mask);
void HAL_HSP_EVT_STREAM_BufferFullCallback(HSP_HandleTypeDef *hhsp, uint32_t buffers_mask);
void HAL_HSP_EVT_TCU_TaskStartedCallback(HSP_HandleTypeDef *hhsp, uint32_t comparators_mask);
void HAL_HSP_EVT_TCU_TaskEndedCallback(HSP_HandleTypeDef *hhsp, uint32_t comparators_mask);
void HAL_HSP_EVT_TCU_TaskOverlapCallback(HSP_HandleTypeDef *hhsp);
void HAL_HSP_EVT_TSC_TimestampReadyCallback(HSP_HandleTypeDef *hhsp, uint32_t timestamp);

/* Error IRQ Handlers and Callbacks *******************************************/
void HAL_HSP_ERR_IRQHandler(HSP_HandleTypeDef *hhsp);
void HAL_HSP_ErrorCallback(HSP_HandleTypeDef *hhsp, uint32_t fw_error_code, uint32_t error_inf_mask);

/* Firmware Event IRQ Handlers and Callbacks **********************************/
void HAL_HSP_FWEVT_IRQHandler(HSP_HandleTypeDef *hhsp);
void HAL_HSP_FWEVT_ProcessingEventCallback(HSP_HandleTypeDef *hhsp, uint32_t events_mask);

#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions ************************************/
HAL_StatusTypeDef HAL_HSP_RegisterMspInitCallback(HSP_HandleTypeDef *hhsp, pHSP_CallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterMspDeInitCallback(HSP_HandleTypeDef *hhsp, pHSP_CallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterSPE_DirectCommandCpltCallback(HSP_HandleTypeDef *hhsp,
                                                                pHSP_CallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterSPE_TaskCpltCallback(HSP_HandleTypeDef *hhsp,
                                                       pHSP_CallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterSPE_FPUSaturationCallback(HSP_HandleTypeDef *hhsp,
                                                            pHSP_CallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterSPE_RunStateCallback(HSP_HandleTypeDef *hhsp,
                                                       pHSP_OneParamCallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterSTREAM_BufferEmptyCallback(HSP_HandleTypeDef *hhsp,
                                                             pHSP_OneParamCallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterSTREAM_BufferFullCallback(HSP_HandleTypeDef *hhsp,
                                                            pHSP_OneParamCallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterTCU_TaskOverlapCallback(HSP_HandleTypeDef *hhsp,
                                                          pHSP_CallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterTCU_TaskStartedCallback(HSP_HandleTypeDef *hhsp,
                                                          pHSP_OneParamCallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterTCU_TaskEndedCallback(HSP_HandleTypeDef *hhsp,
                                                        pHSP_OneParamCallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterTSC_TimestampReadyCallback(HSP_HandleTypeDef *hhsp,
                                                             pHSP_OneParamCallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterErrorCallback(HSP_HandleTypeDef *hhsp, pHSP_TwoParamsCallbackTypeDef p_callback);
HAL_StatusTypeDef HAL_HSP_RegisterFWEVT_ProcessingEventCallback(HSP_HandleTypeDef *hhsp,
                                                                pHSP_OneParamCallbackTypeDef p_callback);

#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup HSP_Exported_Functions_Group14  Peripheral State and Error functions
  * @{
  */
HAL_HSP_StateTypeDef HAL_HSP_GetState(const HSP_HandleTypeDef *hhsp);
uint32_t HAL_HSP_GetError(const HSP_HandleTypeDef *hhsp);
uint32_t HAL_HSP_GetBootErrorCode(const HSP_HandleTypeDef *hhsp);
uint32_t HAL_HSP_GetMsgBoxErrorCode(const HSP_HandleTypeDef *hhsp);

/**
  * @}
  */

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

#endif /* STM32U3xx_HAL_HSP_H */
