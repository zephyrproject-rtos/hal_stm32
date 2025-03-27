/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_hsem.h
  * @author  MCD Application Team
  * @brief   Header file of HSEM HAL module.
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
#ifndef STM32MP2xx_HAL_HSEM_H
#define STM32MP2xx_HAL_HSEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
   * @{
   */

/** @addtogroup HSEM
   * @{
   */

/* Exported constants --------------------------------------------------------*/

/** @defgroup HSEM_Exported_Constants HSEM Exported Constants
  * @{
  */

/** @defgroup HSEM_CPU_GROUP HSEM CPU and GROUP
  * @{
  */
#define HSEM_GROUP0  0U
#define HSEM_GROUP1  1U
#define HSEM_GROUP2  2U
#define HSEM_GROUP3  3U
#define HSEM_CPU1    4U
#define HSEM_CPU2    5U
#define HSEM_CPU3    6U

/**
  * @}
  */

/** @defgroup HSEM_Semaphore_attributes HSEM semaphore RIF PRIV & SEC protection attributes
  * @{
  */
#define HSEM_SEM_PRIV  (HSEM_SEM_PRIV_SELECT | (1U << HSEM_SEM_PRIV_VAL_Pos))
#define HSEM_SEM_NPRIV (HSEM_SEM_PRIV_SELECT | (0U << HSEM_SEM_PRIV_VAL_Pos))
#define HSEM_SEM_SEC   (HSEM_SEM_SEC_SELECT | (1U << HSEM_SEM_SEC_VAL_Pos))
#define HSEM_SEM_NSEC  (HSEM_SEM_SEC_SELECT | (0U << HSEM_SEM_SEC_VAL_Pos))

/**
  * @}
  */

/** @defgroup HSEM_CPU_attributes HSEM RIF CPU CID protection attributes
  * @{
  */
#define HSEM_CPU_CID_DISABLE   (HSEM_CPU_CID_DISABLE_SELECT)
#define HSEM_CPU_CID_STATIC_0  (HSEM_CPU_CID_STATIC_SELECT | (0U << HSEM_CPU_CID_VAL_Pos))
#define HSEM_CPU_CID_STATIC_1  (HSEM_CPU_CID_STATIC_SELECT | (1U << HSEM_CPU_CID_VAL_Pos))
#define HSEM_CPU_CID_STATIC_2  (HSEM_CPU_CID_STATIC_SELECT | (2U << HSEM_CPU_CID_VAL_Pos))
#define HSEM_CPU_CID_STATIC_3  (HSEM_CPU_CID_STATIC_SELECT | (3U << HSEM_CPU_CID_VAL_Pos))
#define HSEM_CPU_CID_STATIC_4  (HSEM_CPU_CID_STATIC_SELECT | (4U << HSEM_CPU_CID_VAL_Pos))
#define HSEM_CPU_CID_STATIC_5  (HSEM_CPU_CID_STATIC_SELECT | (5U << HSEM_CPU_CID_VAL_Pos))
#define HSEM_CPU_CID_STATIC_6  (HSEM_CPU_CID_STATIC_SELECT | (6U << HSEM_CPU_CID_VAL_Pos))
#define HSEM_CPU_CID_STATIC_7  (HSEM_CPU_CID_STATIC_SELECT | (7U << HSEM_CPU_CID_VAL_Pos))

/**
  * @}
  */

/** @defgroup HSEM_Group_attributes HSEM RIF GROUP CID protection attributes
  * @{
  */
#define HSEM_GROUP_CID_DISABLE   (HSEM_GROUP_CID_DISABLE_SELECT)
#define HSEM_GROUP_CID_STATIC_1  (HSEM_GROUP_CID_STATIC_SELECT | (1U << HSEM_GROUP_CID_CPU1_VAL_Pos))
#define HSEM_GROUP_CID_STATIC_2  (HSEM_GROUP_CID_STATIC_SELECT | (1U << HSEM_GROUP_CID_CPU2_VAL_Pos))
#define HSEM_GROUP_CID_STATIC_3  (HSEM_GROUP_CID_STATIC_SELECT | (1U << HSEM_GROUP_CID_CPU3_VAL_Pos))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup HSEM_Exported_Macros HSEM Exported Macros
  * @{
  */

/**
  * @brief  SemID to mask helper Macro.
  * @param  __SEMID__: semaphore ID from 0 to HSEM_SEMID_MAX
  * @retval Semaphore Mask.
  */
#define __HAL_HSEM_SEMID_TO_MASK(__SEMID__) (1UL << (__SEMID__))

/**
  * @brief  Enables the specified HSEM interrupts.
  * @param  __SEM_MASK__: semaphores Mask
  * @retval None.
  */
#if defined(DUAL_CORE)
#define __HAL_HSEM_ENABLE_IT(__SEM_MASK__) ((((SCB->CPUID & 0x000000F0U) >> 4U )== 0x7U) ? \
                                            (HSEM->C1IER |= (__SEM_MASK__)) : \
                                            (HSEM->C2IER |= (__SEM_MASK__)))
#else
#define __HAL_HSEM_ENABLE_IT(__SEM_MASK__) (HSEM->IER |= (__SEM_MASK__))
#endif /* DUAL_CORE */
/**
  * @brief  Disables the specified HSEM interrupts.
  * @param  __SEM_MASK__: semaphores Mask
  * @retval None.
  */
#if defined(DUAL_CORE)
#define __HAL_HSEM_DISABLE_IT(__SEM_MASK__) ((((SCB->CPUID & 0x000000F0) >> 4 )== 0x7) ? \
                                             (HSEM->C1IER &= ~(__SEM_MASK__)) :       \
                                             (HSEM->C2IER &= ~(__SEM_MASK__)))
#else
#define __HAL_HSEM_DISABLE_IT(__SEM_MASK__) (HSEM->IER &= ~(__SEM_MASK__))
#endif /* DUAL_CORE */

/**
  * @brief  Checks whether interrupt has occurred or not for semaphores specified by a mask.
  * @param  __SEM_MASK__: semaphores Mask
  * @retval semaphores Mask : Semaphores where an interrupt occurred.
  */
#if defined(DUAL_CORE)
#define __HAL_HSEM_GET_IT(__SEM_MASK__) ((((SCB->CPUID & 0x000000F0) >> 4 )== 0x7) ? \
                                         ((__SEM_MASK__) & HSEM->C1MISR) :        \
                                         ((__SEM_MASK__) & HSEM->C2MISR1))
#else
#define __HAL_HSEM_GET_IT(__SEM_MASK__) ((__SEM_MASK__) & HSEM->MISR)
#endif /* DUAL_CORE */

/**
  * @brief  Get the semaphores release status flags.
  * @param  __SEM_MASK__: semaphores Mask
  * @retval semaphores Mask : Semaphores where Release flags rise.
  */
#if defined(DUAL_CORE)
#define __HAL_HSEM_GET_FLAG(__SEM_MASK__) ((((SCB->CPUID & 0x000000F0) >> 4 )== 0x7) ? \
                                           (__SEM_MASK__) & HSEM->C1ISR :           \
                                           (__SEM_MASK__) & HSEM->C2ISR)
#else
#define __HAL_HSEM_GET_FLAG(__SEM_MASK__) ((__SEM_MASK__) & HSEM->ISR)
#endif /* DUAL_CORE */

/**
  * @brief  Clears the HSEM Interrupt flags.
  * @param  __SEM_MASK__: semaphores Mask
  * @retval None.
  */
#if defined(DUAL_CORE)
#define __HAL_HSEM_CLEAR_FLAG(__SEM_MASK__) ((((SCB->CPUID & 0x000000F0) >> 4 )== 0x7) ? \
                                             (HSEM->C1ICR |= (__SEM_MASK__)) :        \
                                             (HSEM->C2ICR |= (__SEM_MASK__)))
#else
#define __HAL_HSEM_CLEAR_FLAG(__SEM_MASK__) (HSEM->ICR |= (__SEM_MASK__))
#endif /* DUAL_CORE */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HSEM_Exported_Functions HSEM Exported Functions
  * @{
  */

/** @addtogroup HSEM_Exported_Functions_Group1 Take and Release functions
  * @brief    HSEM Take and Release functions
  * @{
  */

/* HSEM semaphore take (lock) using 2-Step  method ****************************/
HAL_StatusTypeDef  HAL_HSEM_Take(uint32_t SemID, uint32_t ProcessID);
/* HSEM semaphore fast take (lock) using 1-Step  method ***********************/
HAL_StatusTypeDef  HAL_HSEM_FastTake(uint32_t SemID);
/* HSEM Check semaphore state Taken or not   **********************************/
uint32_t HAL_HSEM_IsSemTaken(uint32_t SemID);
/* HSEM Release  **************************************************************/
void  HAL_HSEM_Release(uint32_t SemID, uint32_t ProcessID);
/* HSEM Release All************************************************************/
void HAL_HSEM_ReleaseAll(uint32_t Key, uint32_t CoreID);

/**
  * @}
  */

/** @addtogroup HSEM_Exported_Functions_Group2 HSEM Set and Get Key functions
  * @brief    HSEM Set and Get Key functions.
  * @{
  */
/* HSEM Set Clear Key *********************************************************/
void  HAL_HSEM_SetClearKey(uint32_t Key);
/* HSEM Get Clear Key *********************************************************/
uint32_t HAL_HSEM_GetClearKey(void);
/**
  * @}
  */

/** @addtogroup HSEM_Exported_Functions_Group3
  * @brief   HSEM Notification functions
  * @{
  */
/* HSEM Activate HSEM Notification (When a semaphore is released) ) *****************/
void HAL_HSEM_ActivateNotification(uint32_t SemMask);
/* HSEM Deactivate HSEM Notification (When a semaphore is released)  ****************/
void HAL_HSEM_DeactivateNotification(uint32_t SemMask);
/* HSEM Free Callback (When a semaphore is released)  *******************************/
void HAL_HSEM_FreeCallback(uint32_t SemMask);
/* HSEM IRQ Handler  **********************************************************/
void HAL_HSEM_IRQHandler(void);

/**
  * @}
  */

/** @addtogroup HSEM_Exported_Functions_Group4 HSEM RIF protection configuration functions
  * @brief      HSEM RIF protection configuration functions.
  * @{
  */
/* HSEM Configure Semaphore Attributes (SEC & PRIV) ***************************/
HAL_StatusTypeDef HAL_HSEM_ConfigSemAttributes(uint32_t SemID, uint32_t SemAttributes);
/* HSEM Get Configuration of Semaphore Attributes (SEC & PRIV) ****************/
HAL_StatusTypeDef HAL_HSEM_GetConfigSemAttributes(uint32_t SemID, uint32_t *pSemAttributes);
/* HSEM Configure CPU and GROUP CID Attributes ********************************/
HAL_StatusTypeDef HAL_HSEM_ConfigAttributes(uint32_t Item, uint32_t Attributes);
/* HSEM Get Configuration of CPU and GROUP CID Attributes *********************/
HAL_StatusTypeDef HAL_HSEM_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes);

/**
  * @}
  */

/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/** @defgroup HSEM_Private_Constants HSEM Private Constants
  * @{
  *    The attrbitues are coded according to the following scheme:
  *    00: Value of Semaphore PRIV   (meaningful if bit 24 is set)
  *    01: Value of Semaphore SEC    (meaningful if bit 25 is set)
  *    02 ... 05: Value of CPU CID   (meaningful if bit 29 is set)
  *    06: Value of GROUP CID CPU1   (meaningful if bit 27 is set)
  *    07: Value of GROUP CID CPU2   (meaningful if bit 27 is set)
  *    08: Value of GROUP CID CPU3   (meaningful if bit 27 is set)
  *    09 ... 23: RFU
  *    24: Makes the value of Semaphore PRIV (bit 00) meaningful
  *    25: Makes the value of Semaphore SEC  (bit 01) meaningful
  *    26: RFU
  *    27: Makes the value of GROUP CID CPUx (bits 06 to 08) meaningful
  *    28: GROUP CID disable
  *    29: Makes the value of CPU CID (bits 02 to 05) meaningful
  *    30: RFU
  *    31: CPU CID disable
  */
#define HSEM_SEM_PRIV_VAL_Pos               0U
#define HSEM_SEM_SEC_VAL_Pos                1U
#define HSEM_CPU_CID_VAL_Pos                2U
#define HSEM_GROUP_CID_CPU1_VAL_Pos         6U
#define HSEM_GROUP_CID_CPU2_VAL_Pos         7U
#define HSEM_GROUP_CID_CPU3_VAL_Pos         8U
#define HSEM_SEM_PRIV_SELECT_Pos            24U
#define HSEM_SEM_SEC_SELECT_Pos             25U
#define HSEM_GROUP_CID_STATIC_SELECT_Pos    27U
#define HSEM_GROUP_CID_DISABLE_SELECT_Pos   28U
#define HSEM_CPU_CID_STATIC_SELECT_Pos      29U
#define HSEM_CPU_CID_DISABLE_SELECT_Pos     31U

#define HSEM_CPU_CID_VAL_Msk                (0x0FU << HSEM_CPU_CID_VAL_Pos)

#define HSEM_SEM_PRIV_SELECT                (1U << HSEM_SEM_PRIV_SELECT_Pos)
#define HSEM_SEM_SEC_SELECT                 (1U << HSEM_SEM_SEC_SELECT_Pos)
#define HSEM_GROUP_CID_STATIC_SELECT        (1U << HSEM_GROUP_CID_STATIC_SELECT_Pos)
#define HSEM_GROUP_CID_DISABLE_SELECT       (1U << HSEM_GROUP_CID_DISABLE_SELECT_Pos)
#define HSEM_CPU_CID_STATIC_SELECT          (1U << HSEM_CPU_CID_STATIC_SELECT_Pos)
#define HSEM_CPU_CID_DISABLE_SELECT         (1U << HSEM_CPU_CID_DISABLE_SELECT_Pos)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup HSEM_Private_Macros HSEM Private Macros
  * @{
  */

#define IS_HSEM_SEMID(__SEMID__) ((__SEMID__) <= HSEM_SEMID_MAX )

#define IS_HSEM_PROCESSID(__PROCESSID__) ((__PROCESSID__) <= HSEM_PROCESSID_MAX )

#define IS_HSEM_KEY(__KEY__) ((__KEY__) <= HSEM_CLEAR_KEY_MAX )

#define IS_HSEM_COREID(__COREID__) (((__COREID__) == HSEM_CPU1_COREID) || \
                                    ((__COREID__) == HSEM_CPU2_COREID) || \
                                    ((__COREID__) == HSEM_CPU3_COREID))

#define IS_HSEM_ITEM_CID(__ITEM__) (((__ITEM__) >= HSEM_GROUP0) && \
                                    ((__ITEM__) <= HSEM_CPU3))

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_HAL_HSEM_H */
