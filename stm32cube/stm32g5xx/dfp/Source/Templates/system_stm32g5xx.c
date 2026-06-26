/**
  ******************************************************************************
  * @file    system_stm32g5xx.c
  * @brief   CMSIS Cortex-M33 Device Peripheral Access Layer System Source File
  *
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32g5xxxx.c" file.
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
  *   configure the system clock before to branch to main program.
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

/** @addtogroup STM32G5xx_system
  * @{
  */

/** @addtogroup STM32G5xx_System_Private_Includes
  * @{
  */

#include "stm32g5xx.h"
#include <math.h>

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

#define PLL_FRACN_MODULUS 0x2000U

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

  /* Configure the Vector Table location -------------------------------------*/
  SCB_SetVTOR((uint32_t)(&__VECTOR_TABLE[0]));
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  * @param  None
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
  uint32_t pllp;
  uint32_t pllsource;
  uint32_t pllm;
  uint32_t tmp;
  uint32_t pllfracen;
  float_t fracn1;
  float_t pllvco;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (RCC->CFGR1 & RCC_CFGR1_SYSSW)
  {
    case 0:                 /* HSI used as system clock source */
      SystemCoreClock = HSI_VALUE   >> ((RCC->CR & RCC_CR_HSIDIV) >> RCC_CR_HSIDIV_Pos);
      break;

    case RCC_CFGR1_SYSSW_0: /* HSE used as system clock source */
#if defined (HSE_VALUE)
      SystemCoreClock = HSE_VALUE;
#else
      while (1); /* Block, HSE value to define */
#endif /* HSE_VALUE */
      break;

    case RCC_CFGR1_SYSSW_1:  /* PLL1 used as system clock source */
      pllm = ((RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1M) >> RCC_PLL1CFGR_PLL1M_Pos);
      if (pllm == 0U)
      {
        pllvco = (float_t)0U;
      }
      else
      {
        pllsource = (RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1SRC) >> RCC_PLL1CFGR_PLL1SRC_Pos;
        pllfracen = ((RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1FRACEN) >> RCC_PLL1CFGR_PLL1FRACEN_Pos);
        fracn1 = (float_t)(uint32_t)(pllfracen * ((RCC->PLL1FRACR & RCC_PLL1FRACR_PLL1FRACN) >> \
                                                  RCC_PLL1FRACR_PLL1FRACN_Pos));
        switch (pllsource)
        {
          case 0x01:  /* HSI used as PLL clock source */
            pllvco = ((float_t)(HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> RCC_CR_HSIDIV_Pos)) / (float_t)pllm);
            break;

          case 0x02:  /* HSE used as PLL clock source */
#if defined (HSE_VALUE)
            pllvco = ((float_t)HSE_VALUE / (float_t)pllm);
#else
            while (1); /* Block, HSE value to define */
#endif /* HSE_VALUE */
            break;

          default:    /* No clock sent to PLL*/
            pllvco = (float_t)0U;
            break;
        }

        pllvco *= ((float_t)((uint32_t)(RCC->PLL1DIVR & RCC_PLL1DIVR_PLL1N) + 1) +
                   (fracn1 / (float_t)PLL_FRACN_MODULUS));
      }

      pllp = (((RCC->PLL1DIVR & RCC_PLL1DIVR_PLL1P) >> RCC_PLL1DIVR_PLL1P_Pos) + 1U);
      SystemCoreClock = (uint32_t)((uint32_t)pllvco / pllp);
      break;

    default:
      SystemCoreClock = 0xFFFFFFFFu;
      break;
  }

  /* Compute HCLK clock frequency --------------------------------------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR2 & RCC_CFGR2_HPRE) >> RCC_CFGR2_HPRE_Pos)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
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
