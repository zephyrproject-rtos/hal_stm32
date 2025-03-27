/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_wrapper_for_a35.h
  * @author  MCD Application Team
  * @version $VERSION$
  * @date    $DATE$
  * @brief   Wrapper of some specific HAL driver functions for Cortex-A35
  *          This file is included by stm32mp2xx_hal_conf.h
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_HAL_WRAPPER_FOR_A35_H
#define STM32MP2xx_HAL_WRAPPER_FOR_A35_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CORE_CA35)
/* Includes ------------------------------------------------------------------*/
/* From CMSIS "Core_A" */
#include "irq_ctrl.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
/* A35 Wrapper of HAL cortex functions for M33 (ARMv8-M) (see hal_cortex.h) */
#define HAL_NVIC_SetPriority(__IRQN__, __PREEMPTPRIORITY__, __SUBPRIORITY__)  \
  (void)IRQ_SetPriority(__IRQN__, __PREEMPTPRIORITY__)
#define HAL_NVIC_EnableIRQ(__IRQN__)                                          (void)IRQ_Enable(__IRQN__)
#define HAL_NVIC_DisableIRQ(__IRQN__)                                         (void)IRQ_Disable(__IRQN__)
#define HAL_NVIC_ClearPendingIRQ(__IRQN__)                                    (void)IRQ_ClearPending(__IRQN__)
#define HAL_NVIC_SetPendingIRQ(__IRQN__)                                      (void)IRQ_SetPending(__IRQN__)
#define HAL_NVIC_GetPendingIRQ(__IRQN__)                                      IRQ_GetPending(__IRQN__)
#define HAL_NVIC_ConfigInterruptSecurity(__IRQN__, __IRQSECURITYSTATE__)      \
  ((__IRQSECURITYSTATE__ == 0x0) ? (void)IRQ_SetMode(__IRQN__, IRQ_MODE_DOMAIN_SECURE) : \
   (void)IRQ_SetMode(__IRQN__, IRQ_MODE_DOMAIN_NONSECURE))

/* Existing not (already) wrapped functions (needed ?) : */
/*void HAL_NVIC_SystemReset(void);*/
/*void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t *pPreemptPriority, uint32_t *pSubPriority);*/
/*void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGrouping);*/
/*uint32_t HAL_NVIC_GetPriorityGrouping(void);*/
/*uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);*/
/*uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);*/
/*void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);*/
#endif /*CORE_CA35*/

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_HAL_WRAPPER_FOR_A35_H */
