/**
 ******************************************************************************
 * @file    stm32_adv_trace.h
 * @author  MCD Application Team
 * @brief   Header for stm32_adv_trace.c
******************************************************************************
  * @attention
  *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADV_TRACE_H
#define __ADV_TRACE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "utilities_conf.h"

/** @defgroup ADV_TRACE advanced tracer
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADV_TRACE_exported_TypeDef ADV_TRACE exported Typedef
 *  @{
 */

/**
 *  @brief prototype of the time stamp function.
 */
typedef void cb_timestamp(uint8_t *pData, uint16_t *Size);

/**
 *  @brief prototype of the overrun function.
 */
typedef void cb_overrun(uint8_t **pData, uint16_t *size);
/**
 *  @brief  List the Advanced trace function status.
 *  list of the returned status value, any negative value is corresponding to an error.
 */
typedef enum{
  UTIL_ADV_TRACE_OK              =  0,     /*!< Operation terminated successfully.*/
  UTIL_ADV_TRACE_INVALID_PARAM   = -1,     /*!< Invalid Parameter.                */
  UTIL_ADV_TRACE_HW_ERROR        = -2,     /*!< Hardware Error.                   */
  UTIL_ADV_TRACE_MEM_FULL        = -3,     /*!< Memory fifo full.                 */
  UTIL_ADV_TRACE_UNKNOWN_ERROR   = -4,     /*!< Unknown Error.                    */
#if defined(UTIL_ADV_TRACE_CONDITIONNAL)
  UTIL_ADV_TRACE_GIVEUP          = -5,     /*!< trace give up                     */
  UTIL_ADV_TRACE_REGIONMASKED    = -6      /*!< trace region masked               */
#endif
} UTIL_ADV_TRACE_Status_t;

/**
 * @brief Advanced trace driver definition
 */
typedef struct {
  UTIL_ADV_TRACE_Status_t  (* Init)(void (*cb)(void *ptr));                                       /*!< Media initialization.      */
  UTIL_ADV_TRACE_Status_t  (* DeInit)(void);                                                      /*!< Media Un-initialization.   */
  UTIL_ADV_TRACE_Status_t  (* StartRx)(void (*cb)(uint8_t *pdata, uint16_t size, uint8_t error)); /*!< Media to start RX process. */
  UTIL_ADV_TRACE_Status_t  (* Send)(uint8_t *pdata, uint16_t size);                               /*!< Media to send data.        */
}UTIL_ADV_TRACE_Driver_s;

/**
 *  @}
 */

/* External variables --------------------------------------------------------*/
/** @defgroup ADV_TRACE_exported_variables ADV_TRACE exported variables
 *
 *  @{
 */
/**
 *  @brief This structure is the linked with the IF layer implementation.
 */
extern const UTIL_ADV_TRACE_Driver_s UTIL_TraceDriver;

/**
 *  @}
 */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/** @defgroup ADV_TRACE_exported_function ADV_TRACE exported function
 *  @{
 */

/**
 * @brief TraceInit Initializes Logging feature
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_Init(void);

/**
 * @brief TraceDeInit module DeInitializes.
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_DeInit(void);

/**
 * @brief this function check if the buffer is empty.
 * @retval 1 if the buffer is empty else 0
 */
uint8_t UTIL_ADV_TRACE_IsBufferEmpty(void);

/**
 * @brief start the RX process.
 * @param UserCallback ptr function used to get the RX data
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_StartRxProcess(void (*UserCallback)(uint8_t *PData, uint16_t Size, uint8_t Error));

/**
 * @brief TraceSend decode the strFormat and post it to the circular queue for printing
 * @param strFormat Trace message and format
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_FSend(const char *strFormat, ...);

/**
 * @brief post data to the circular queue
 * @param *pdata pointer to Data
 * @param length length of data buffer to be sent
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_Send(const uint8_t *pdata, uint16_t length);

/**
 * @brief ZCSend_Allocation allocate the memory and return information to write the data
 * @param Length trase size
 * @param pData  pointer on the fifo
 * @param FifoSize size of the fifo
 * @param WritePos write position of the fifo
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_ZCSend_Allocation(uint16_t Length, uint8_t **pData, uint16_t *FifoSize, uint16_t *WritePos);

/**
 * @brief ZCSend finalize the data transfer
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_ZCSend_Finalize(void);
/**
 * @brief  Trace send started hook
 * @retval None
 */

/**
 * @brief  Trace send pre hook function
 */
void UTIL_ADV_TRACE_PreSendHook(void);

/**
 * @brief  Trace send post hook function
 */
void UTIL_ADV_TRACE_PostSendHook(void);

#if defined(UTIL_ADV_TRACE_OVERRUN)
/**
 * @brief Register a function used to add overrun info inside the trace
 * @param cb pointer of function to return overrun information
 */
void UTIL_ADV_TRACE_RegisterOverRunFunction(cb_overrun *cb);
#endif

#if defined(UTIL_ADV_TRACE_CONDITIONNAL)

/**
 * @brief conditional FSend decode the strFormat and post it to the circular queue for printing
 * @param VerboseLevel verbose level of the trace
 * @param Region region of the trace
 * @param TimeStampState 0 no time stamp insertion, 1 time stamp inserted inside the trace data
 * @param strFormat formatted string
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_COND_FSend(uint32_t VerboseLevel, uint32_t Region,uint32_t TimeStampState, const char *strFormat, ...);

/**
 * @brief conditional ZCSend Write user formatted data directly in the FIFO (Z-Cpy)
 * @param VerboseLevel verbose level of the trace
 * @param Region region of the trace
 * @param TimeStampState 0 no time stamp insertion, 1 time stamp inserted inside the trace data
 * @param length  data length
 * @param pData  pointer on the fifo
 * @param FifoSize size of the fifo
 * @param WritePos write position of the fifo
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_COND_ZCSend_Allocation(uint32_t VerboseLevel, uint32_t Region, uint32_t TimeStampState, uint16_t length,uint8_t **pData, uint16_t *FifoSize, uint16_t *WritePos);

/**
 * @brief conditional ZCSend finalize the data transfer
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_COND_ZCSend_Finalize(void);

/**
 * @brief confitionnal Send post data to the circular queue
 * @param VerboseLevel verbose level of the trace
 * @param Region region of the trace
 * @param TimeStampState 0 no time stamp insertion, 1 time stamp inserted inside the trace data
 * @param *pdata pointer to Data
 * @param length length of data buffer ro be sent
 * @retval Status based on @ref UTIL_ADV_TRACE_Status_t
 */
UTIL_ADV_TRACE_Status_t UTIL_ADV_TRACE_COND_Send(uint32_t VerboseLevel, uint32_t Region, uint32_t TimeStampState, const uint8_t *pdata, uint16_t length);

/**
 * @brief Register a function used to add timestamp inside the trace
 * @param cb pointer of function to return timestamp information
 */
void UTIL_ADV_TRACE_RegisterTimeStampFunction(cb_timestamp *cb);

/**
 * @brief  Set the verbose level
 * @param  Level (0 to 255)
 * @retval None
 */
void UTIL_ADV_TRACE_SetVerboseLevel(uint8_t Level);

/**
 * @brief  Get the verbose level
 * @retval verbose level
 */
uint8_t UTIL_ADV_TRACE_GetVerboseLevel(void);

/**
 * @brief  add to the mask a bit field region.
 * @param  Region bit field of region to enable
 * @retval None
 */
void UTIL_ADV_TRACE_SetRegion(uint32_t Region);

/**
 * @brief  add to the mask a bit field region.
 * @retval None
 */
uint32_t UTIL_ADV_TRACE_GetRegion(void);

/**
 * @brief  remove from the mask a bit field region.
 * @param  Region Region bit field of region to disable
 * @retval None
 */
void UTIL_ADV_TRACE_ResetRegion(uint32_t Region);

#endif

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__ADV_TRACE_H */
