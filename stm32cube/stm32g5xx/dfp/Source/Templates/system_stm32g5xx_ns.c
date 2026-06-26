/**
  ******************************************************************************
  * @file    system_stm32g5xx_ns.c
  * @brief   CMSIS Cortex-M33 Device Peripheral Access Layer System Source File
  *          to be used in non-secure application when the system implements
  *          the TrustZone-M security.
  *
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at non-secure startup before
  *                      branch to non-secure main program.
  *                      This call is made inside the "startup_stm32g5xxxx.c" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *   After each device reset the HSI (64 MHz) is used as system clock source.
  *   Then SystemInit() function is called, in "startup_stm32g5xxxx.c" file, to
  *   configure the system clock before to branch to main secure program.
  *   Later, when non-secure SystemInit() function is called, in "startup_stm32g5xxxx.c"
  *   file, the system clock can have been updated from reset value by the main
  *   secure program.
  *
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

/** @addtogroup STM32G5xx_system
  * @{
  */

/** @addtogroup STM32G5xx_System_Private_Includes
  * @{
  */

#include "stm32g5xx.h"


/**
  * @}
  */

/** @addtogroup STM32G5xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32G5xx_System_Private_Defines
  * @{
  */
#define SYSTEM_CLOCK HSI_VALUE /*!< Reset system clock in Hz */

/**
  * @}
  */

/** @addtogroup STM32G5xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32G5xx_System_Private_Variables
  * @{
  */
extern const VECTOR_TABLE_Type __VECTOR_TABLE[];

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
uint32_t SystemCoreClock = SYSTEM_CLOCK;

const uint8_t  AHBPrescTable[16] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U};
const uint8_t  APBPrescTable[8] =  {0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U};
/**
  * @}
  */

/** @addtogroup STM32G5xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32G5xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

void SystemInit(void)
{
  /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB_EnableFPU();
#endif /* (__FPU_PRESENT == 1) && (__FPU_USED == 1) */

  /* Non-secure application main() must call SystemCoreClockUpdate() to update */
  /* the SystemCoreClock variable to ensure non-secure application relies on   */
  /* the initial clock reference set by secure application.                    */
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  * @param  None
  * @note   From the non-secure application, the SystemCoreClock value is
  *         retrieved from the secure domain via a Non-Secure Callable function
  *         since the RCC peripheral can be protected with security attributes
  *         that prevent to compute the SystemCoreClock variable from the RCC
  *         peripheral registers.
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
  *       divided by the HSI divider factor
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
  *
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**)
  *             or HSI_VALUE(*)divided by the HSI divider factor then multiplied/divided by
  *       the PLL factors.
  *
  *         (*) HSI_VALUE is a constant defined in CMSIS device header file (default value
  *              64 MHz) but the real value can vary depending on the variations
  *              in voltage and temperature.
  *
  *         (**) HSE_VALUE is a constant defined in stm32_external_env.h file (default value
  *              24 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function can
  *              have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  /* Get the SystemCoreClock value from the secure domain */
  SystemCoreClock = SECURE_SystemCoreClockUpdate();
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
