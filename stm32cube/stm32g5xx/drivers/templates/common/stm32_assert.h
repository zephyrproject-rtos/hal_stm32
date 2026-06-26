/**
  ******************************************************************************
  * @file    stm32_assert.h
  * @brief   STM32 assert template file.
  *          This file must be copied to the application folder and renamed
  *          to stm32_assert.h.
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
#ifndef STM32_ASSERT_H
#define STM32_ASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#if defined(USE_ASSERT_DBG_PARAM)
/**
  * @brief  The ASSERT_DBG_PARAM macro is used for function parameter checks.
  * @param  expr If expr is false, it calls the ASSERT_DBG_PARAM function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define ASSERT_DBG_PARAM(expr) ((expr) ? (void)0U : assert_dbg_param_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_dbg_param_failed(uint8_t *file, uint32_t line);
#else
#define ASSERT_DBG_PARAM(expr) ((void)0U)
#endif /* USE_ASSERT_DBG_PARAM */

#if defined(USE_ASSERT_DBG_STATE)
/**
  * @brief  The ASSERT_DBG_STATE macro is used for function state checks.
  * @param  __STATE__ the state field within the PPP handle
  * @param  __VAL__ the authorized state value(s) to be checked
  *                 can be a combination of states
  * @note   If __STATE__ & __VAL__ is zero (unauthorized state), then
  *         the assert_dbg_state_failed function is called which reports
  *         the name of the source file and the source line number of the call that failed.
  *         If __STATE__ & __VAL__ is zero (unauthorized state), then the ASSERT_DBG_STATE macro returns no value.
  */
#define ASSERT_DBG_STATE(__STATE__,__VAL__) (((((uint32_t)(__STATE__)) &  ((uint32_t)(__VAL__))) != 0U) ?  \
                                             (void)0U :                                                    \
                                             assert_dbg_state_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_dbg_state_failed(uint8_t *file, uint32_t line);
#else
#define ASSERT_DBG_STATE(__STATE__,__VAL__) ((void)0U)
#endif /* USE_ASSERT_DBG_STATE  */

#ifdef __cplusplus
}
#endif

#endif /* STM32_ASSERT_H */
