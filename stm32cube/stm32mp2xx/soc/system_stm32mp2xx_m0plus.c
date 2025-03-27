/**
  ******************************************************************************
  * @file    system_stm32mp2xx_m0plus.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer System Source File
  *
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32mp2xx_m0plus.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock, it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *   After each device reset the HSI (64Mhz) is used as system clock source.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32mp2xx_system
  * @{
  */

/** @addtogroup stm32mp2xx_System_Private_Includes
  * @{
  */

#include "stm32mp2xx.h"

/**
  * @}
  */

/** @addtogroup stm32mp2xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup stm32mp2xx_System_Private_Defines
  * @{
  */

/************************* Miscellaneous Configuration ************************/
/******************************************************************************/
/**
  * @}
  */

/** @addtogroup stm32mp2xx_System_Private_Macros
  * @{
  */

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#if !defined  (HSI_VALUE)
 #if defined (USE_STM32MP257CXX_EMU)
   #define HSI_VALUE             ((uint32_t)200000U)     /*!< Value of the Internal High Speed oscillator in Hz*/
 #elif defined (USE_STM32MP257CXX_FPGA)
   #define HSI_VALUE             ((uint32_t)32000000U)   /*!< Value of the Internal High Speed oscillator in Hz*/
 #else /* USE_STM32MP257CXX_EMU | USE_STM32MP257CXX_FPGA */
   #define HSI_VALUE             ((uint32_t)64000000U)   /*!< Value of the Internal High Speed oscillator in Hz*/
 #endif /* else USE_STM32MP257CXX_EMU | USE_STM32MP257CXX_FPGA */
#endif /* HSI_VALUE */

#define  SYSTEM_CLOCK HSI_VALUE

/**
  * @}
  */

/** @addtogroup stm32mp2xx_System_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @addtogroup stm32mp2xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup stm32mp2xx_System_Private_Functions
  * @{
  */

/*----------------------------------------------------------------------------
  Externals
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYSTEM_CLOCK;

/*----------------------------------------------------------------------------
  System Core Clock update function
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)
{
  SystemCoreClock = SYSTEM_CLOCK;
}

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
  /* default RCC clock configuration is restored after reset ------------*/

  /* No Vector Table relocation since VTOR not present ------------------*/
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
