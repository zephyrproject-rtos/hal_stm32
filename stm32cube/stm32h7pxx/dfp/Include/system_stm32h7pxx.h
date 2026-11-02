/**
  ******************************************************************************
  * @file    system_stm32h7pxx.h
  * @brief   CMSIS Cortex-M7 Device System Source File for STM32H7Pxx devices.
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32h7pxx_system
  * @{
  */

#ifndef SYSTEM_STM32H7PXX_H
#define SYSTEM_STM32H7PXX_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup STM32H7Pxx_System_Includes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32H7Pxx_System_Exported_Types
  * @{
  */
typedef void(*VECTOR_TABLE_Type)(void);

/**
  * @}
  */

/** @addtogroup STM32H7Pxx_System_Exported_Variables
  * @{
  */
  /* The SystemCoreClock variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by initializing the HAL module through HAL_Init() function
      3) by calling a hal_rcc function to configure the system clock:
          - HAL_RCC_ResetSystemClock()
          - HAL_RCC_SetSysClkSource()
          - HAL_RCC_SetHCLKPrescaler()
          - HAL_RCC_SetBusClockConfig()
          - HAL_RCC_GetHCLKFreq()
         Note: If you use this function to configure the system clock; then there is no need to call
               the 2 first functions listed above, since SystemCoreClock variable is updated automatically.
   */
extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */

extern const uint8_t  CPUPrescTable[16];    /*!< CPU prescalers table values */
extern const uint8_t  AHBPrescTable[16];     /*!< AHB prescalers table values */
extern const uint8_t  APBPrescTable[8];     /*!< APB ranges table values     */

/**
  * @}
  */


/** @addtogroup STM32H7Pxx_System_Exported_Functions
  * @{
  */

/**
  * @brief Setup the microcontroller system.
  *
  * Initialize the System and update the SystemCoreClock variable.
  */
extern void SystemInit (void);


/**
  * @brief  Update SystemCoreClock variable.
  *
  * Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
  */
extern void SystemCoreClockUpdate (void);


/**
  * @brief Update SystemCoreClock variable from secure application and return its value
  *        when security is implemented in the system (Non-secure callable function).
  *
  * Returns the SystemCoreClock value with current core Clock retrieved from cpu registers.
  */
extern uint32_t SECURE_SystemCoreClockUpdate(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_STM32H7PXX_H */

/**
  * @}
  */

/**
  * @}
  */
