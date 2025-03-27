/**************************************************************************//**
 * @file     system_stm32mp2xx_m33_ns.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM33 Device Series
 * @version  V5.00
 * @date     02. November 2016
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stm32mp2xx.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#if !defined  (HSI_VALUE)
 #if defined (USE_STM32MP257CXX_EMU)
   #define HSI_VALUE             ((uint32_t)200000U)     /*!< Value of the Internal High Speed oscillator in Hz*/
 #elif defined (USE_STM32MP257CXX_FPGA) || defined (USE_STM32MP215FXX_FPGA)
   #define HSI_VALUE             ((uint32_t)32000000U)   /*!< Value of the Internal High Speed oscillator in Hz*/
 #else /* USE_STM32MP257CXX_EMU | USE_STM32MP257CXX_FPGA */
   #define HSI_VALUE             ((uint32_t)64000000U)   /*!< Value of the Internal High Speed oscillator in Hz*/
 #endif /* else USE_STM32MP257CXX_EMU | USE_STM32MP257CXX_FPGA | USE_STM32MP215FXX_FPGA*/
#endif /* HSI_VALUE */

#if !defined  (HSE_VALUE)
 #if defined (USE_STM32MP257CXX_EMU)
   #define HSE_VALUE             ((uint32_t)48000000U)   /*!< Value of the External High Speed oscillator in Hz*/
 #elif defined (USE_STM32MP257CXX_FPGA) || defined (USE_STM32MP215FXX_FPGA)
   #define HSE_VALUE             ((uint32_t)32000000U)   /*!< Value of the External High Speed oscillator in Hz*/
 #else /* USE_STM32MP257CXX_EMU | USE_STM32MP257CXX_FPGA */
   #define HSE_VALUE             ((uint32_t)40000000U)   /*!< Value of the External High Speed oscillator in Hz*/
 #endif /* else USE_STM32MP257CXX_EMU | USE_STM32MP257CXX_FPGA | USE_STM32MP215FXX_FPGA*/
#endif /* HSE_VALUE */

#if !defined  (LSI_VALUE)
  #define LSI_VALUE             ((uint32_t)32000U)   /*!< Value of the Internal Low Speed oscillator in Hz*/
#endif /* LSI_VALUE */

#if !defined  (LSE_VALUE)
  #define LSE_VALUE             ((uint32_t)32768U)   /*!< Value of the External Low Speed oscillator in Hz*/
#endif /* LSE_VALUE */

#if !defined  (MSI_VALUE)
  #define MSI_VALUE             ((uint32_t)4000000U)   /*!< Value of the Internal oscillator in Hz*/
#endif /* MSI_VALUE */

#define  SYSTEM_CLOCK HSI_VALUE

/*----------------------------------------------------------------------------
  Externals
 *----------------------------------------------------------------------------*/
#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
  extern uint32_t __Vectors;
#endif

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
/* The SystemCoreClock variable is updated in two ways:
    1) by calling CMSIS function SystemCoreClockUpdate()
    2) each time HAL_RCC_ClockConfig() is called to configure the
         system clock frequency
       Note: If you use this function to configure the system clock frequency
             then there is no need to call SystemCoreClockUpdate(), since
             SystemCoreClock variable is updated automatically.
*/
uint32_t SystemCoreClock = SYSTEM_CLOCK;

typedef struct
{
  uint32_t PLLSource;   /*!< The new source of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Clock_Source                */
  uint8_t  PLLState;    /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_State                       */
  uint8_t  FREFDIV;
  uint16_t FBDIV;
  uint32_t FRACIN;
  uint32_t POSTDIV1;
  uint32_t POSTDIV2;
  uint32_t SSM_Mode;     /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Spread_Spectrum_Mode        */

  uint32_t SSM_SPREAD;
  uint32_t SSM_DIVVAL;
} PLLInitTypeDef;

static void GetPLLxConfig(PLLInitTypeDef  *pll_config, uint32_t PLL_num)
{
  switch (PLL_num)
  {
    case 4:
      pll_config->PLLState = (uint8_t)(((RCC->PLL4CFGR1 & RCC_PLL4CFGR1_PLLEN) == RCC_PLL4CFGR1_PLLEN) ? 1 : 0);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos;
      pll_config->FREFDIV = (uint8_t)((RCC->PLL4CFGR2 & RCC_PLL4CFGR2_FREFDIV_Msk) >> RCC_PLL4CFGR2_FREFDIV_Pos);
      pll_config->FBDIV = (uint16_t)((RCC->PLL4CFGR2 & RCC_PLL4CFGR2_FBDIV_Msk) >> RCC_PLL4CFGR2_FBDIV_Pos);
      pll_config->FRACIN = (RCC->PLL4CFGR3 & RCC_PLL4CFGR3_FRACIN_Msk) >> RCC_PLL4CFGR3_FRACIN_Pos;
      pll_config->POSTDIV1 = (RCC->PLL4CFGR6 & RCC_PLL4CFGR6_POSTDIV1_Msk) >> RCC_PLL4CFGR6_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (RCC->PLL4CFGR7 & RCC_PLL4CFGR7_POSTDIV2_Msk) >> RCC_PLL4CFGR7_POSTDIV2_Pos;
      break;
    case 5:
      pll_config->PLLState = (uint8_t)(((RCC->PLL5CFGR1 & RCC_PLL5CFGR1_PLLEN) == RCC_PLL5CFGR1_PLLEN) ? 1 : 0);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos;
      pll_config->FREFDIV = (uint8_t)((RCC->PLL5CFGR2 & RCC_PLL5CFGR2_FREFDIV_Msk) >> RCC_PLL5CFGR2_FREFDIV_Pos);
      pll_config->FBDIV = (uint16_t)((RCC->PLL5CFGR2 & RCC_PLL5CFGR2_FBDIV_Msk) >> RCC_PLL5CFGR2_FBDIV_Pos);
      pll_config->FRACIN = (RCC->PLL5CFGR3 & RCC_PLL5CFGR3_FRACIN_Msk) >> RCC_PLL5CFGR3_FRACIN_Pos;
      pll_config->POSTDIV1 = (RCC->PLL5CFGR6 & RCC_PLL5CFGR6_POSTDIV1_Msk) >> RCC_PLL5CFGR6_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (RCC->PLL5CFGR7 & RCC_PLL5CFGR7_POSTDIV2_Msk) >> RCC_PLL5CFGR7_POSTDIV2_Pos;
      break;
    case 6:
      pll_config->PLLState = (uint8_t)(((RCC->PLL6CFGR1 & RCC_PLL6CFGR1_PLLEN) == RCC_PLL6CFGR1_PLLEN) ? 1 : 0);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos;
      pll_config->FREFDIV = (uint8_t)((RCC->PLL6CFGR2 & RCC_PLL6CFGR2_FREFDIV_Msk) >> RCC_PLL6CFGR2_FREFDIV_Pos);
      pll_config->FBDIV = (uint16_t)((RCC->PLL6CFGR2 & RCC_PLL6CFGR2_FBDIV_Msk) >> RCC_PLL6CFGR2_FBDIV_Pos);
      pll_config->FRACIN = (RCC->PLL6CFGR3 & RCC_PLL6CFGR3_FRACIN_Msk) >> RCC_PLL6CFGR3_FRACIN_Pos;
      pll_config->POSTDIV1 = (RCC->PLL6CFGR6 & RCC_PLL6CFGR6_POSTDIV1_Msk) >> RCC_PLL6CFGR6_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (RCC->PLL6CFGR7 & RCC_PLL6CFGR7_POSTDIV2_Msk) >> RCC_PLL6CFGR7_POSTDIV2_Pos;
      break;
    case 7:
      pll_config->PLLState = (uint8_t)(((RCC->PLL7CFGR1 & RCC_PLL7CFGR1_PLLEN) == RCC_PLL7CFGR1_PLLEN) ? 1 : 0);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos;
      pll_config->FREFDIV = (uint8_t)((RCC->PLL7CFGR2 & RCC_PLL7CFGR2_FREFDIV_Msk) >> RCC_PLL7CFGR2_FREFDIV_Pos);
      pll_config->FBDIV = (uint16_t)((RCC->PLL7CFGR2 & RCC_PLL7CFGR2_FBDIV_Msk) >> RCC_PLL7CFGR2_FBDIV_Pos);
      pll_config->FRACIN = (RCC->PLL7CFGR3 & RCC_PLL7CFGR3_FRACIN_Msk) >> RCC_PLL7CFGR3_FRACIN_Pos;
      pll_config->POSTDIV1 = (RCC->PLL7CFGR6 & RCC_PLL7CFGR6_POSTDIV1_Msk) >> RCC_PLL7CFGR6_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (RCC->PLL7CFGR7 & RCC_PLL7CFGR7_POSTDIV2_Msk) >> RCC_PLL7CFGR7_POSTDIV2_Pos;
      break;
    case 8:
      pll_config->PLLState = (uint8_t)(((RCC->PLL8CFGR1 & RCC_PLL8CFGR1_PLLEN) == RCC_PLL8CFGR1_PLLEN) ? 1 : 0);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos;
      pll_config->FREFDIV = (uint8_t)((RCC->PLL8CFGR2 & RCC_PLL8CFGR2_FREFDIV_Msk) >> RCC_PLL8CFGR2_FREFDIV_Pos);
      pll_config->FBDIV = (uint16_t)((RCC->PLL8CFGR2 & RCC_PLL8CFGR2_FBDIV_Msk) >> RCC_PLL8CFGR2_FBDIV_Pos);
      pll_config->FRACIN = (RCC->PLL8CFGR3 & RCC_PLL8CFGR3_FRACIN_Msk) >> RCC_PLL8CFGR3_FRACIN_Pos;
      pll_config->POSTDIV1 = (RCC->PLL8CFGR6 & RCC_PLL8CFGR6_POSTDIV1_Msk) >> RCC_PLL8CFGR6_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (RCC->PLL8CFGR7 & RCC_PLL8CFGR7_POSTDIV2_Msk) >> RCC_PLL8CFGR7_POSTDIV2_Pos;
      break;
    default:
      pll_config->PLLState = 0;
      pll_config->PLLSource = 0;
      pll_config->FREFDIV = 0;
      pll_config->FBDIV = 0;
      pll_config->FRACIN = 0;
      pll_config->POSTDIV1 = 0;
      pll_config->POSTDIV2 = 0;
      break;
  }
}

static uint32_t ComputePLLClockFreq(const PLLInitTypeDef *pll)
{
  uint32_t source_freq;
  uint64_t pll_output;

#if defined(USE_STM32MP257CXX_FPGA) || defined (USE_STM32MP215FXX_FPGA)
  source_freq = 32000000UL;
#else /* USE_STM32MP257CXX_FPGA */
  switch (pll->PLLSource)
  {
    case 0 : /* HSI */
      source_freq = HSI_VALUE;
      break;
    case 1 : /* HSE */
      source_freq = HSE_VALUE;
      break;
    case 2 : /* MSI */
      source_freq = MSI_VALUE;
      break;
    default:
      source_freq = 0;
      break;
  }
#endif /* else USE_STM32MP257CXX_FPGA | USE_STM32MP215FXX_FPGA*/

  /* Compute PLL frequency from PLL parameters according to fractional mode selection */
  /* Note : keep maximum computing precision by doubling integer resolution */
  /*        and process numerator before applying dividers */
  if (0U == pll->FRACIN)
  {
    pll_output = (uint64_t)source_freq * (uint64_t)pll->FBDIV;
  }
  else
  {
    pll_output = (uint64_t) source_freq * ( ((1U << 24) * (uint64_t)(pll->FBDIV)) + (uint64_t)(pll->FRACIN) );
    pll_output /= (1U << 24);
  }
  pll_output /= (uint64_t)((uint64_t)pll->FREFDIV * (uint64_t)pll->POSTDIV1 * (uint64_t)pll->POSTDIV2);

  return (uint32_t)pll_output;
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the Cortex-M33 clock
  *         (ck_icn_hs_mcu).
  *         ck_icn_hs_mcu is mapped on flexgen 0 and can have different
  *         Clock source.
  *         SystemCoreClock variable can be used by the user application
  *         to setup the SysTick timer or configure other parameters.
  *
  * @note   Each time the Cortex-M33 clock changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise,
  *         any configuration based on this variable will be incorrect.
  *
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
  uint32_t        xbar_source;
  uint32_t        xbar_source_freq;
  uint32_t 	      tmp;
  PLLInitTypeDef  pll_config;

  /* Identify xbar source for ck_cpu1_ext2f flexgen channel (channel 0) */
  xbar_source = (uint32_t)(READ_BIT(RCC->XBARxCFGR[0], RCC_XBARxCFGR_XBARxSEL_Msk));

  /* Then retrieve the source frequency */
  switch (xbar_source)
  {
    case 0: /* PLL4 */
      GetPLLxConfig(&pll_config, 4);
      xbar_source_freq = ComputePLLClockFreq(&pll_config);
      break;

    case 1 : /* PLL5 */
      GetPLLxConfig(&pll_config, 5);
      xbar_source_freq = ComputePLLClockFreq(&pll_config);
      break;

    case 2 :/* PLL6 */
      GetPLLxConfig(&pll_config, 6);
      xbar_source_freq = ComputePLLClockFreq(&pll_config);
      break;

    case 3 : /* PLL7 */
      GetPLLxConfig(&pll_config, 7);
      xbar_source_freq = ComputePLLClockFreq(&pll_config);
      break;

    case 4 : /* PLL8 */
      GetPLLxConfig(&pll_config, 8);
      xbar_source_freq = ComputePLLClockFreq(&pll_config);
      break;

    case 5 : /* HSI */
      xbar_source_freq = HSI_VALUE;
      break;

    case 6 : /* HSE */
      xbar_source_freq = HSE_VALUE;
      break;

    case 13 : /* LSI */
      xbar_source_freq = LSI_VALUE;
      break;

    case 14 : /* LSE */
      xbar_source_freq = LSE_VALUE;
      break;

    default:
      xbar_source_freq = 0;
      break;
  }

  tmp = ((RCC->FINDIVxCFGR[0] & RCC_FINDIVxCFGR_FINDIVx_Msk) + 1U);

  SystemCoreClock = xbar_source_freq / (tmp * ((RCC->PREDIVxCFGR[0] & RCC_PREDIVxCFGR_PREDIVx_Msk) + 1U));
}

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/
void SystemInit (void)
{

#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
  SCB->VTOR = (uint32_t) &__Vectors;
#endif

#ifdef UNALIGNED_SUPPORT_DISABLE
  SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif

  SystemCoreClock = SYSTEM_CLOCK;
}
