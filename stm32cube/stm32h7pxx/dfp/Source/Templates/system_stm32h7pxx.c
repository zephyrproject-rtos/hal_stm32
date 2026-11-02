/**
  ******************************************************************************
  * @file    system_stm32h7pxx.c
  * @brief   CMSIS Cortex-M7 Device Peripheral Access Layer System Source File
  *
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32h7pxxxx.c" file.
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
  *   Then SystemInit() function is called, in "startup_stm32h7pxxxx.c" file, to
  *   configure the system before branching to the main function.
  *
  *   This file configures the system clock as follows:
  *=============================================================================
  *=============================================================================
  *-----------------------------------------------------------------------------
  *        System Clock source                     | HSI
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                              | 64000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                                | 64000000
  *-----------------------------------------------------------------------------

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

/** @addtogroup STM32H7Pxx_system
  * @{
  */

/** @addtogroup STM32H7Pxx_System_Private_Includes
  * @{
  */

#include "stm32h7pxx.h"
#include <math.h>

/**
  * @}
  */

/** @addtogroup STM32H7Pxx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32H7Pxx_System_Private_Defines
  * @{
  */

#define SYSTEM_CLOCK HSI_VALUE /*!< Reset system clock in Hz */

/**
  * @}
  */

/** @addtogroup STM32H7Pxx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32H7Pxx_System_Private_Variables
  * @{
  */
/*!< The VTOR location information is based on information from the linker with a dependency
     on the IDE, the cortex register is updated using the __VECTOR_TABLE variable.
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

const uint8_t  CPUPrescTable[16] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U};
const uint8_t  AHBPrescTable[16] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U};
const uint8_t  APBPrescTable[8] =  {0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U};

/**
  * @}
  */

/** @addtogroup STM32H7Pxx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32H7Pxx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

void SystemInit(void)
{
  /* Configure Power Supply --------------------------------------------------*/
#if defined(USE_SYSTEM_SUPPLY_STARTUP_BYPASS)
  /* Enable both LDO and SMPS, bypass enabled */
  STM32_WRITE_BIT(PWR->CSR2, PWR_CSR2_BYPASS);
#else
  /* Enable both LDO and SMPS, bypass disabled */
  STM32_CLEAR_BIT(PWR->CSR2, PWR_CSR2_BYPASS);
#endif /* USE_SYSTEM_SUPPLY_STARTUP_BYPASS */

  /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB_EnableFPU();
#endif /* (__FPU_PRESENT == 1) && (__FPU_USED == 1) */

  /* Configure the Vector Table location -------------------------------------*/
  SCB_SetVTOR((uint32_t)(&__VECTOR_TABLE[0]));
}

/**
  * @brief  Update SystemCoreClock variable according to RCC registers values.
  *         The SystemCoreClock variable contains the core clock (sys_cpu_ck), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  * @param  None
  * @note   Each time the core clock changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
  *
  *           - If SYSCLK source is CSI, SystemCoreClock will contain the CSI_VALUE(**)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(***)
  *
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSI_VALUE(*)
  *             or CSI_VALUE(**) or HSE_VALUE(***) multiplied/divided by the PLL factors.
  *
  *         (*) HSI_VALUE is a constant defined in stm32h7pxxxx.h file (default value
  *              64 MHz) but the real value can vary depending on the variations
  *              in voltage and temperature.
  *
  *         (**) CSI_VALUE is a constant defined in stm32h7pxxxx.h file (default value
  *             4 MHz) but the real value can vary depending on the variations
  *             in voltage and temperature.
  *
  *         (***) HSE_VALUE is a constant defined in stm32_external_env.h file (default value
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
  uint32_t sysclk;
  uint32_t pllsource;
  uint32_t pllm;
  uint32_t pllp;
  uint32_t core_presc;
  float_t pllfracn;
  float_t pllvco;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case 0x00:  /* HSI used as system clock source (default after reset) */
      sysclk = (HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> RCC_CR_HSIDIV_Pos));
      break;

    case 0x08:  /* CSI used as system clock source */
      sysclk = CSI_VALUE;
      break;

    case 0x10:  /* HSE used as system clock source */
#if defined(HSE_VALUE)
      sysclk = HSE_VALUE;
#else
      while(1); /* Blocked, the user must define HSE_VALUE*/
#endif /* HSE_VALUE */
      break;

    case 0x18:  /* PLL1 used as system clock  source */
      /* PLL1_VCO = (HSE_VALUE or HSI_VALUE or CSI_VALUE/ PLLM) * PLLN
         SYSCLK = PLL1_VCO / PLL1R
         */
      pllsource = (RCC->PLLCKSELR & RCC_PLLCKSELR_PLLSRC);
      pllm = ((RCC->PLLCKSELR & RCC_PLLCKSELR_DIVM1) >> RCC_PLLCKSELR_DIVM1_Pos)  ;
      if ((RCC->PLLCFGR & RCC_PLLCFGR_PLL1FRACEN) != 0U)
      {
        pllfracn = (float_t)(uint32_t)(((RCC->PLL1FRACR & RCC_PLL1FRACR_FRACN) >> RCC_PLL1FRACR_FRACN_Pos));
      }
      else
      {
        pllfracn = (float_t)0U;
      }

      if (pllm != 0U)
      {
        switch (pllsource)
        {
          case 0x02:  /* HSE used as PLL1 clock source */
#if defined(HSE_VALUE)
            pllvco = (float_t)HSE_VALUE / (float_t)pllm;
#else
            while(1); /* Blocked, the user must define HSE_VALUE*/
#endif /* HSE_VALUE */
            break;

          case 0x01:  /* CSI used as PLL1 clock source */
            pllvco = (float_t)CSI_VALUE / (float_t)pllm;
            break;

          case 0x00:  /* HSI used as PLL1 clock source */
          default:
            pllvco = (float_t)(HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> RCC_CR_HSIDIV_Pos)) / (float_t)pllm;

            break;
        }
        pllvco *= ((float_t)(uint32_t)((RCC->PLL1DIVR1 & RCC_PLL1DIVR1_DIVN) + 1U) + (pllfracn / (float_t)0x2000U));
        pllp = (((RCC->PLL1DIVR1 & RCC_PLL1DIVR1_DIVP) >> RCC_PLL1DIVR1_DIVP_Pos) + 1U);
        sysclk = (uint32_t)(float_t)(pllvco / (float_t)pllp);
      }
      else
      {
        sysclk = 0U;
      }
      break;

    default:  /* Unexpected, default to HSI used as system clock source (default after reset) */
      sysclk = (HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> RCC_CR_HSIDIV_Pos));
      break;
  }

  /* system clock frequency : CM7 CPU frequency  */
  core_presc = (RCC->CDCFGR & RCC_CDCFGR_CPRE);
  if (core_presc >= 8U)
  {
    SystemCoreClock = (sysclk >> (core_presc - 7U));
  }
  else
  {
    SystemCoreClock = sysclk;
  }
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
