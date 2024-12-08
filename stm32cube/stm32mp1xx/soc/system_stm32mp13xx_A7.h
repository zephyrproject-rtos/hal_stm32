/**
  ******************************************************************************
  * @file    system_stm32mp13xx_A7.h
  * @author  MCD Application Team
  * @brief   CMSIS Cortex Device System Source File for STM32MP13xx devices.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32mp13xx_system
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_STM32MP1XX_A7_H
#define __SYSTEM_STM32MP1XX_A7_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "irq_ctrl.h"
/** @addtogroup STM32MP13xx_System_Includes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32MP13xx_System_Exported_types
  * @{
  */

  /* This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
         Note: If you use this function to configure the system clock; then there
               is no need to call the 2 first functions listed above, since SystemCoreClock
               variable is updated automatically.
  */
extern uint32_t SystemCoreClock;          /*!< System Core1 Clock Frequency  */
extern uint32_t SystemCore1Clock;         /*!< System Core1 Clock Frequency  */
extern uint32_t SystemCore2Clock;         /*!< System Core2 Clock Frequency  */

extern IRQHandler_t IRQ_Vector_Table[MAX_IRQ_n];

/**
  \brief Setup the microcontroller system.

   Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);
extern void SystemInit_cpu1 (void);
extern void SystemInit_Interrupts_SoftIRQn_Handler(uint32_t Software_Interrupt_Id, uint8_t cpu_id_request);
extern void SecurePhysicalTimer_IRQHandler(void);

/**
  \brief  Update SystemCoreClock variable.

   Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);

/**
  \brief  Create Translation Table.

   Creates Memory Management Unit Translation Table.
 */
extern void MMU_CreateTranslationTable(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_STM32MP1XX_A7_H */

/**
  * @}
  */

/**
  * @}
  */

