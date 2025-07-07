/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_rcc.c
  * @author  MCD Application Team
  * @version $VERSION$
  * @date    $DATE$
  * @brief   RCC LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_ll_rcc.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if defined(RCC)


/** @addtogroup RCC_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_LL_Private_Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_LL_Exported_Functions
  * @{
  */

/** @addtogroup RCC_LL_EF_Init
  * @{
  */

/**
  * @brief  Reset the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *         - HSI  ON and used as system clock source
  *         - HSE, CSI, PLL1, PLL2, PLL3 and PLL4 OFF
  *         - AHBs and APBs bus pre-scalers set to 1.
  *         - MCO1 and MCO2 OFF
  *         - All interrupts disabled (except Wake-up from CSTOP Interrupt Enable)
  * @note   This function doesn't modify the configuration of the
  *         - Peripheral clocks
  *         - LSI, LSE and RTC clocks
  *         - HSECSS and LSECSS
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RCC registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_RCC_DeInit(void)
{
  uint32_t i;

  /* Set HSION bit */
  LL_RCC_HSI_Enable();

  /* Insure HSIRDY bit is set before writing default MSIRANGE value */
  while (LL_RCC_HSI_IsReady() == 0U)
  {}

  /* Reset MCO1 Configuration Register */
  CLEAR_REG(RCC->MCO1CFGR);

  /* Reset MCO2 Configuration Register */
  CLEAR_REG(RCC->MCO2CFGR);

  /* Reset xbar channels inputs */
  /* Reset FINDIVx, PREDIVx */
  for (i = 0U; i < 64U; i++)
  {
    RCC->XBARxCFGR[i] = LL_RCC_XBAR_CLKSRC_HSI | (1U << 6);
    WRITE_REG(RCC->FINDIVxCFGR[i], 0x00000040U | (1U << 6));
    CLEAR_REG(RCC->PREDIVxCFGR[i]);
  }

  /* Reset PLLs */
  CLEAR_REG(RCC->PLL4CFGR4);
  CLEAR_REG(RCC->PLL5CFGR4);
  CLEAR_REG(RCC->PLL6CFGR4);
  CLEAR_REG(RCC->PLL7CFGR4);
  CLEAR_REG(RCC->PLL8CFGR4);
  WRITE_REG(RCC->PLL4CFGR1, 0x10000001U);
  WRITE_REG(RCC->PLL5CFGR1, 0x10000001U);
  WRITE_REG(RCC->PLL6CFGR1, 0x10000001U);
  WRITE_REG(RCC->PLL7CFGR1, 0x10000001U);
  WRITE_REG(RCC->PLL8CFGR1, 0x10000001U);
  CLEAR_REG(RCC->PLL4CFGR2);
  CLEAR_REG(RCC->PLL5CFGR2);
  CLEAR_REG(RCC->PLL6CFGR2);
  CLEAR_REG(RCC->PLL7CFGR2);
  CLEAR_REG(RCC->PLL8CFGR2);
  WRITE_REG(RCC->PLL4CFGR3, 0x04000000U);
  WRITE_REG(RCC->PLL5CFGR3, 0x04000000U);
  WRITE_REG(RCC->PLL6CFGR3, 0x04000000U);
  WRITE_REG(RCC->PLL7CFGR3, 0x04000000U);
  WRITE_REG(RCC->PLL8CFGR3, 0x04000000U);
  CLEAR_REG(RCC->PLL4CFGR5);
  CLEAR_REG(RCC->PLL5CFGR5);
  CLEAR_REG(RCC->PLL6CFGR5);
  CLEAR_REG(RCC->PLL7CFGR5);
  CLEAR_REG(RCC->PLL8CFGR5);
  CLEAR_REG(RCC->PLL4CFGR6);
  CLEAR_REG(RCC->PLL5CFGR6);
  CLEAR_REG(RCC->PLL6CFGR6);
  CLEAR_REG(RCC->PLL7CFGR6);
  CLEAR_REG(RCC->PLL8CFGR6);
  CLEAR_REG(RCC->PLL4CFGR7);
  CLEAR_REG(RCC->PLL5CFGR7);
  CLEAR_REG(RCC->PLL6CFGR7);
  CLEAR_REG(RCC->PLL7CFGR7);
  CLEAR_REG(RCC->PLL8CFGR7);

  /* Reset GFG */
  CLEAR_REG(RCC->MUXSELCFGR);

  /* Reset APBDIVx */
  CLEAR_REG(RCC->APB1DIVR);
  CLEAR_REG(RCC->APB2DIVR);
  CLEAR_REG(RCC->APB3DIVR);
  CLEAR_REG(RCC->APB4DIVR);
  CLEAR_REG(RCC->APBDBGDIVR);

  /* Reset HSITRIM value */
  CLEAR_REG(RCC->HSICFGR);

  /* Reset MSITRIM value */
  CLEAR_REG(RCC->MSICFGR);

  /* Reset RCC oscillator states except HSI */
  WRITE_REG(RCC->OCENCLRR, 0x7E2U);

  /* Clear all RCC interrupt flags */
#if defined(CORE_CA35)
  CLEAR_REG(RCC->C1CIESETR);
#elif defined(CORE_CM33)
  CLEAR_REG(RCC->C2CIESETR);
#endif /* CORE_CA35 */

  /* Clear all RCC Reset Flags */
  CLEAR_REG(RCC->HWRSTSCLRR);

  return SUCCESS;
}

/**
  * @}
  */

/**
  * @brief  Return the frequencies of different on chip clocks;  MPUSS, AXISS,
  *         MCUSS, ACLK, MLHCLK, APB[5:1] AHB[6:1] and MCU buses clocks.
  * @note   Each time MPUSS, AXISS, MCUSS, ACLK, MLHCLK, APB[5:1] AHB[6:1] and/or
  *         MCU clock changes, this function must be called to update structure
  *         fields. Otherwise, any configuration based on this function will
  *         be incorrect.
  * @param  RCC_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which
  *         will hold the clocks frequencies.
  * @retval None
  */
void LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks)
{
  uint32_t lsmcudiv;
  uint32_t apb_div;

  /*!< AXIM clock frequency */
  RCC_Clocks->AXIM_Frequency = HSI_VALUE;

  /*!< MLAHB clock frequency */
  RCC_Clocks->MLAHB_Frequency = HSI_VALUE;

  /* Read LSMCUDIV */
  lsmcudiv = LL_RCC_Get_LSMCUDIVR() + 1U;

  /*!< AHB1 clock frequency */
  RCC_Clocks->AHB1_Frequency = HSI_VALUE / lsmcudiv;

  /*!< AHB2 clock frequency */
  RCC_Clocks->AHB2_Frequency = HSI_VALUE / lsmcudiv;

  /*!< AHB3 clock frequency */
  RCC_Clocks->AHB3_Frequency = HSI_VALUE / lsmcudiv;

  /*!< AHB4 clock frequency */
  RCC_Clocks->AHB4_Frequency = HSI_VALUE / lsmcudiv;

  /*!< AHB5 clock frequency */
  RCC_Clocks->AHB5_Frequency = HSI_VALUE / lsmcudiv;

  RCC_Clocks->AHB6_Frequency = HSI_VALUE / lsmcudiv;

  /*!< AHBSR clock frequency */
  RCC_Clocks->AHBSR_Frequency = HSI_VALUE / lsmcudiv;

  /*!< APB1 clock frequency */
  apb_div = LL_RCC_GetAPB1Prescaler();
  apb_div = ((uint32_t)(1UL << apb_div) * lsmcudiv);
  RCC_Clocks->APB1_Frequency = HSI_VALUE / apb_div;

  /*!< APB2 clock frequency */
  apb_div = LL_RCC_GetAPB2Prescaler();
  apb_div = ((uint32_t)(1UL << apb_div) * lsmcudiv);
  RCC_Clocks->APB2_Frequency = HSI_VALUE / apb_div;

  /*!< APB3 clock frequency */
  apb_div = LL_RCC_GetAPB3Prescaler();
  apb_div = ((uint32_t)(1UL << apb_div) * lsmcudiv);
  RCC_Clocks->APB3_Frequency = HSI_VALUE / apb_div;

  /*!< APB4 clock frequency */
  apb_div = LL_RCC_GetAPB4Prescaler();
  apb_div = ((uint32_t)(1UL << apb_div) * lsmcudiv);
  RCC_Clocks->APB4_Frequency = HSI_VALUE / apb_div;
#if defined(RCC_APB5DIVR_APB5DIV)
  /*!< APB5 clock frequency */
  apb_div = LL_RCC_GetAPB5Prescaler();
  apb_div = ((uint32_t)(1UL << apb_div) * lsmcudiv);
  RCC_Clocks->APB5_Frequency = HSI_VALUE / apb_div;
#endif /* RCC_APB5DIVR_APB5DIV */
  /*!< APBSR clock frequency */
  RCC_Clocks->APBSR_Frequency = (HSI_VALUE / lsmcudiv);

  /*!< APBDBG clock frequency */
  apb_div = LL_RCC_GetAPBDBGPrescaler();
  apb_div = ((uint32_t)(1UL << apb_div) * lsmcudiv);
  RCC_Clocks->APBDBG_Frequency = HSI_VALUE / apb_div;
}

/**
  * @brief  Return PLL2 clocks frequency
  * @param  PLL_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which
  *         will hold the clocks frequencies.
  * @retval None
  */
void LL_RCC_GetPLL2ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;
  uint32_t frefdiv;
  uint32_t fbdiv;
  uint32_t postdiv1;
  uint32_t postdiv2;
  uint64_t pll_vco;
  uint64_t pll_output;

  pllsource = LL_RCC_PLL2_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL2SOURCE_HSI:
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL2SOURCE_HSE:
      pllinputfreq = HSE_VALUE;
      break;

    case LL_RCC_PLL2SOURCE_MSI:
      pllinputfreq = MSI_VALUE;
      break;

    default:
      pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
      break;
  }

  frefdiv = LL_RCC_PLL2_GetFREFDIV();
  fbdiv = LL_RCC_PLL2_GetFBDIV();
  postdiv1 = (RCC->PLL2CFGR6 & RCC_PLL2CFGR6_POSTDIV1_Msk) >> RCC_PLL2CFGR6_POSTDIV1_Pos;
  postdiv2 = (RCC->PLL2CFGR7 & RCC_PLL2CFGR7_POSTDIV2_Msk) >> RCC_PLL2CFGR7_POSTDIV2_Pos;
  uint32_t config = postdiv1 * postdiv2;
  if (frefdiv != 0U)
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv) / (uint64_t)frefdiv;
  }
  else
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv);
  }
  if (config != 0U)
  {
    pll_output = pll_vco / config;
  }
  else
  {
    pll_output = pll_vco;
  }

  PLL_Clocks->freq = (uint32_t)pll_output;
}
#if defined(RCC_PLL3CFGR1_PLLEN)
/**
  * @brief  Return PLL3 clocks frequency
  * @param  PLL_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which
  *         will hold the clocks frequencies.
  * @retval None
  */
void LL_RCC_GetPLL3ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;
  uint32_t frefdiv;
  uint32_t fbdiv;
  uint32_t postdiv1;
  uint32_t postdiv2;
  uint64_t pll_vco;
  uint64_t pll_output;

  pllsource = LL_RCC_PLL3_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL3SOURCE_HSI:
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL3SOURCE_HSE:
      pllinputfreq = HSE_VALUE;
      break;

    case LL_RCC_PLL3SOURCE_MSI:
      pllinputfreq = MSI_VALUE;
      break;

    default:
      pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
      break;
  }

  frefdiv = LL_RCC_PLL3_GetFREFDIV();
  fbdiv = LL_RCC_PLL3_GetFBDIV();
  postdiv1 = (RCC->PLL3CFGR6 & RCC_PLL3CFGR6_POSTDIV1_Msk) >> RCC_PLL3CFGR6_POSTDIV1_Pos;
  postdiv2 = (RCC->PLL3CFGR7 & RCC_PLL3CFGR7_POSTDIV2_Msk) >> RCC_PLL3CFGR7_POSTDIV2_Pos;
  uint32_t config = postdiv1 * postdiv2;
  if (frefdiv != 0U)
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv) / (uint64_t)frefdiv;
  }
  else
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv);
  }
  if (config != 0U)
  {
    pll_output = pll_vco / config;
  }
  else
  {
    pll_output = pll_vco;
  }

  PLL_Clocks->freq = (uint32_t)pll_output;
}
#endif /* RCC_PLL3CFGR1_PLLEN */

/**
  * @brief  Return PLL4 clocks frequency
  * @param  PLL_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which
  *         will hold the clocks frequencies.
  * @retval None
  */
void LL_RCC_GetPLL4ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;
  uint32_t frefdiv;
  uint32_t fbdiv;
  uint32_t postdiv1;
  uint32_t postdiv2;
  uint64_t pll_vco;
  uint64_t pll_output;

  pllsource = LL_RCC_PLL4_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL4SOURCE_HSI:
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL4SOURCE_HSE:
      pllinputfreq = HSE_VALUE;
      break;

    case LL_RCC_PLL4SOURCE_MSI:
      pllinputfreq = MSI_VALUE;
      break;
#if defined(LL_RCC_PLL4SOURCE_CKIN)
    case LL_RCC_PLL4SOURCE_CKIN:
      pllinputfreq = EXTERNAL_CLOCK_VALUE;
      break;
#endif /* LL_RCC_PLL4SOURCE_CKIN */
    default:
      pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
      break;
  }

  frefdiv = LL_RCC_PLL4_GetFREFDIV();
  fbdiv = LL_RCC_PLL4_GetFBDIV();
  postdiv1 = (RCC->PLL4CFGR6 & RCC_PLL4CFGR6_POSTDIV1_Msk) >> RCC_PLL4CFGR6_POSTDIV1_Pos;
  postdiv2 = (RCC->PLL4CFGR7 & RCC_PLL4CFGR7_POSTDIV2_Msk) >> RCC_PLL4CFGR7_POSTDIV2_Pos;
  uint32_t config = postdiv1 * postdiv2;
  if (frefdiv != 0U)
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv) / (uint64_t)frefdiv;
  }
  else
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv);
  }
  if (config != 0U)
  {
    pll_output = pll_vco / config;
  }
  else
  {
    pll_output = pll_vco;
  }

  PLL_Clocks->freq = (uint32_t)pll_output;
}

/**
  * @brief  Return PLL5 clocks frequency
  * @param  PLL_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which
  *         will hold the clocks frequencies.
  * @retval None
  */
void LL_RCC_GetPLL5ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;
  uint32_t frefdiv;
  uint32_t fbdiv;
  uint32_t postdiv1;
  uint32_t postdiv2;
  uint64_t pll_vco;
  uint64_t pll_output;

  pllsource = LL_RCC_PLL5_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL5SOURCE_HSI:
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL5SOURCE_HSE:
      pllinputfreq = HSE_VALUE;
      break;

    case LL_RCC_PLL5SOURCE_MSI:
      pllinputfreq = MSI_VALUE;
      break;
#if defined(LL_RCC_PLL5SOURCE_CKIN)
    case LL_RCC_PLL5SOURCE_CKIN:
      pllinputfreq = EXTERNAL_CLOCK_VALUE;
      break;
#endif /* LL_RCC_PLL5SOURCE_CKIN */
    default:
      pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
      break;
  }

  frefdiv = LL_RCC_PLL5_GetFREFDIV();
  fbdiv = LL_RCC_PLL5_GetFBDIV();
  postdiv1 = (RCC->PLL5CFGR6 & RCC_PLL5CFGR6_POSTDIV1_Msk) >> RCC_PLL5CFGR6_POSTDIV1_Pos;
  postdiv2 = (RCC->PLL5CFGR7 & RCC_PLL5CFGR7_POSTDIV2_Msk) >> RCC_PLL5CFGR7_POSTDIV2_Pos;
  uint32_t config = postdiv1 * postdiv2;
  if (frefdiv != 0U)
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv) / (uint64_t)frefdiv;
  }
  else
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv);
  }
  if (config != 0U)
  {
    pll_output = pll_vco / config;
  }
  else
  {
    pll_output = pll_vco;
  }

  PLL_Clocks->freq = (uint32_t)pll_output;
}

/**
  * @brief  Return PLL6 clocks frequency
  * @param  PLL_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which
  *         will hold the clocks frequencies.
  * @retval None
  */
void LL_RCC_GetPLL6ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;
  uint32_t frefdiv;
  uint32_t fbdiv;
  uint32_t postdiv1;
  uint32_t postdiv2;
  uint64_t pll_vco;
  uint64_t pll_output;

  pllsource = LL_RCC_PLL6_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL6SOURCE_HSI:
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL6SOURCE_HSE:
      pllinputfreq = HSE_VALUE;
      break;

    case LL_RCC_PLL6SOURCE_MSI:
      pllinputfreq = MSI_VALUE;
      break;
#if defined(LL_RCC_PLL6SOURCE_CKIN)
    case LL_RCC_PLL6SOURCE_CKIN:
      pllinputfreq = EXTERNAL_CLOCK_VALUE;
      break;
#endif /* LL_RCC_PLL6SOURCE_CKIN */
    default:
      pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
      break;
  }

  frefdiv = LL_RCC_PLL6_GetFREFDIV();
  fbdiv = LL_RCC_PLL6_GetFBDIV();
  postdiv1 = (RCC->PLL6CFGR6 & RCC_PLL6CFGR6_POSTDIV1_Msk) >> RCC_PLL6CFGR6_POSTDIV1_Pos;
  postdiv2 = (RCC->PLL6CFGR7 & RCC_PLL6CFGR7_POSTDIV2_Msk) >> RCC_PLL6CFGR7_POSTDIV2_Pos;
  uint32_t config = postdiv1 * postdiv2;
  if (frefdiv != 0U)
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv) / (uint64_t)frefdiv;
  }
  else
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv);
  }
  if (config != 0U)
  {
    pll_output = pll_vco / config;
  }
  else
  {
    pll_output = pll_vco;
  }

  PLL_Clocks->freq = (uint32_t)pll_output;
}

/**
  * @brief  Return PLL7 clocks frequency
  * @param  PLL_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which
  *         will hold the clocks frequencies.
  * @retval None
  */
void LL_RCC_GetPLL7ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;
  uint32_t frefdiv;
  uint32_t fbdiv;
  uint32_t postdiv1;
  uint32_t postdiv2;
  uint64_t pll_vco;
  uint64_t pll_output;

  pllsource = LL_RCC_PLL7_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL7SOURCE_HSI:
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL7SOURCE_HSE:
      pllinputfreq = HSE_VALUE;
      break;

    case LL_RCC_PLL7SOURCE_MSI:
      pllinputfreq = MSI_VALUE;
      break;
#if defined(LL_RCC_PLL7SOURCE_CKIN)
    case LL_RCC_PLL7SOURCE_CKIN:
      pllinputfreq = EXTERNAL_CLOCK_VALUE;
      break;
#endif /* LL_RCC_PLL7SOURCE_CKIN */
    default:
      pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
      break;
  }

  frefdiv = LL_RCC_PLL7_GetFREFDIV();
  fbdiv = LL_RCC_PLL7_GetFBDIV();
  postdiv1 = (RCC->PLL7CFGR6 & RCC_PLL7CFGR6_POSTDIV1_Msk) >> RCC_PLL7CFGR6_POSTDIV1_Pos;
  postdiv2 = (RCC->PLL7CFGR7 & RCC_PLL7CFGR7_POSTDIV2_Msk) >> RCC_PLL7CFGR7_POSTDIV2_Pos;
  uint32_t config = postdiv1 * postdiv2;
  if (frefdiv != 0U)
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv) / (uint64_t)frefdiv;
  }
  else
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv);
  }
  if (config != 0U)
  {
    pll_output = pll_vco / config;
  }
  else
  {
    pll_output = pll_vco;
  }

  PLL_Clocks->freq = (uint32_t)pll_output;
}

/**
  * @brief  Return PLL8 clocks frequency
  * @param  PLL_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which
  *         will hold the clocks frequencies.
  * @retval None
  */
void LL_RCC_GetPLL8ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;
  uint32_t frefdiv;
  uint32_t fbdiv;
  uint32_t postdiv1;
  uint32_t postdiv2;
  uint64_t pll_vco;
  uint64_t pll_output;

  pllsource = LL_RCC_PLL8_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL8SOURCE_HSI:
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL8SOURCE_HSE:
      pllinputfreq = HSE_VALUE;
      break;

    case LL_RCC_PLL8SOURCE_MSI:
      pllinputfreq = MSI_VALUE;
      break;
#if defined(LL_RCC_PLL8SOURCE_CKIN)
    case LL_RCC_PLL8SOURCE_CKIN:
      pllinputfreq = EXTERNAL_CLOCK_VALUE;
      break;
#endif /* LL_RCC_PLL8SOURCE_CKIN */
    default:
      pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
      break;
  }

  frefdiv = LL_RCC_PLL8_GetFREFDIV();
  fbdiv = LL_RCC_PLL8_GetFBDIV();
  postdiv1 = (RCC->PLL8CFGR6 & RCC_PLL8CFGR6_POSTDIV1_Msk) >> RCC_PLL8CFGR6_POSTDIV1_Pos;
  postdiv2 = (RCC->PLL8CFGR7 & RCC_PLL8CFGR7_POSTDIV2_Msk) >> RCC_PLL8CFGR7_POSTDIV2_Pos;
  uint32_t config = postdiv1 * postdiv2;
  if (frefdiv != 0U)
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv) / (uint64_t)frefdiv;
  }
  else
  {
    pll_vco = ((uint64_t)pllinputfreq * (uint64_t)fbdiv);
  }
  if (config != 0U)
  {
    pll_output = pll_vco / config;
  }
  else
  {
    pll_output = pll_vco;
  }

  PLL_Clocks->freq = (uint32_t)pll_output;
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C12_I3C12_CLKSOURCE
  *         @arg @ref LL_RCC_I2C46_CLKSOURCE
  *         @arg @ref LL_RCC_I2C35_I3C3_CLKSOURCE
  *         @arg @ref LL_RCC_I2C7_CLKSOURCE
  * @retval I2C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetI2CClockFreq(uint32_t I2CxSource)
{
  uint32_t i2c_frequency;
  LL_PLL_ClocksTypeDef PLL_Clocks;
  uint32_t i2c_source;
  uint32_t i2c_source_freq;
  uint32_t i2c_prediv;
  uint32_t i2c_findiv;

  /* Add assert */

  switch (I2CxSource)
  {
#if defined(LL_RCC_I2C12_I3C12_CLKSOURCE)
    case LL_RCC_I2C12_I3C12_CLKSOURCE:
      i2c_source = LL_RCC_GetI2C1_2_I3C1_2ClockSource();
      i2c_prediv = LL_RCC_GetI2C1_2_I3C1_2_PREDIV();
      i2c_findiv = LL_RCC_GetI2C1_2_I3C1_2_FINDIV();
      break;
#elif defined(LL_RCC_I2C12_CLKSOURCE)
    case LL_RCC_I2C12_CLKSOURCE:
      i2c_source = LL_RCC_GetI2C1_2ClockSource();
      i2c_prediv = LL_RCC_GetI2C1_2_PREDIV();
      i2c_findiv = LL_RCC_GetI2C1_2_FINDIV();
      break;
#endif /* LL_RCC_I2C12_I3C12_CLKSOURCE */
#if defined(LL_RCC_I2C46_CLKSOURCE)
    case LL_RCC_I2C46_CLKSOURCE:
      i2c_source = LL_RCC_GetI2C4_6ClockSource();
      i2c_prediv = LL_RCC_GetI2C4_6_PREDIV();
      i2c_findiv = LL_RCC_GetI2C4_6_FINDIV();
      break;

    case LL_RCC_I2C35_I3C3_CLKSOURCE:
      i2c_source = LL_RCC_GetI2C3_5_I3C3ClockSource();
      i2c_prediv = LL_RCC_GetI2C3_5_I3C3_PREDIV();
      i2c_findiv = LL_RCC_GetI2C3_5_I3C3_FINDIV();
      break;

    case LL_RCC_I2C7_CLKSOURCE:
      i2c_source = LL_RCC_GetI2C7ClockSource();
      i2c_prediv = LL_RCC_GetI2C7_PREDIV();
      i2c_findiv = LL_RCC_GetI2C7_FINDIV();
      break;
#endif /* LL_RCC_I2C46_CLKSOURCE */

#if defined(LL_RCC_I2C3_CLKSOURCE)
    case LL_RCC_I2C3_CLKSOURCE:
      i2c_source = LL_RCC_GetI2C3ClockSource();
      i2c_prediv = LL_RCC_GetI2C3_PREDIV();
      i2c_findiv = LL_RCC_GetI2C3_FINDIV();
      break;
#endif /* LL_RCC_I2C3_CLKSOURCE */

#if defined(LL_RCC_I2C8_CLKSOURCE)
    case LL_RCC_I2C8_CLKSOURCE:
      i2c_source = LL_RCC_GetI2C8ClockSource();
      i2c_prediv = LL_RCC_GetI2C8_PREDIV();
      i2c_findiv = LL_RCC_GetI2C8_FINDIV();
      break;
#endif /* LL_RCC_I2C8_CLKSOURCE */

#if defined(LL_RCC_I3C4_CLKSOURCE)
    case LL_RCC_I3C4_CLKSOURCE:
      i2c_source = LL_RCC_GetI3C4ClockSource();
      i2c_prediv = LL_RCC_GetI3C4_PREDIV();
      i2c_findiv = LL_RCC_GetI3C4_FINDIV();
      break;

#endif /* LL_RCC_I3C4_CLKSOURCE */
    default:
      i2c_source = 0U;
      i2c_prediv = 0U;
      i2c_findiv = 0U;
      break;
  }

  switch (i2c_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      i2c_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      i2c_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      i2c_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      i2c_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      i2c_source_freq = LSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_SPDIF:
      i2c_source_freq = 0;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      i2c_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      i2c_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      i2c_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      i2c_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      i2c_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      i2c_source_freq = PLL_Clocks.freq;
      break;
    default:
      i2c_source_freq = 0U;
      break;
  }

  i2c_frequency = i2c_source_freq / ((i2c_prediv + 1U) * (i2c_findiv + 1U));

  return i2c_frequency;
}

/**
  * @brief  Return SAIx clock frequency
  * @param  SAIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_MDF1_CLKSOURCE
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE
  *         @arg @ref LL_RCC_SAI34_CLKSOURCE
  * @retval SAI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetSAIClockFreq(uint32_t SAIxSource)
{
  uint32_t sai_frequency;
  LL_PLL_ClocksTypeDef PLL_Clocks;
  uint32_t sai_source;
  uint32_t sai_source_freq;
  uint32_t sai_prediv;
  uint32_t sai_findiv;

  /* Add assert */

  switch (SAIxSource)
  {
#if defined(LL_RCC_SAI1_MDF1_CLKSOURCE)
    case LL_RCC_SAI1_MDF1_CLKSOURCE:
      sai_source = LL_RCC_GetSAI1_MDF1ClockSource();
      sai_prediv = LL_RCC_GetSAI1_MDF1_PREDIV();
      sai_findiv = LL_RCC_GetSAI1_MDF1_FINDIV();
      break;
#elif defined(LL_RCC_SAI1_CLKSOURCE)
    case LL_RCC_SAI1_CLKSOURCE:
      sai_source = LL_RCC_GetSAI1ClockSource();
      sai_prediv = LL_RCC_GetSAI1_PREDIV();
      sai_findiv = LL_RCC_GetSAI1_FINDIV();
      break;
#endif /* LL_RCC_SAI1_MDF1_CLKSOURCE */
    case LL_RCC_SAI2_CLKSOURCE:
      sai_source = LL_RCC_GetSAI2ClockSource();
      sai_prediv = LL_RCC_GetSAI2_PREDIV();
      sai_findiv = LL_RCC_GetSAI2_FINDIV();
      break;
#if defined(LL_RCC_SAI34_CLKSOURCE)
    case LL_RCC_SAI34_CLKSOURCE:
      sai_source = LL_RCC_GetSAI3_4ClockSource();
      sai_prediv = LL_RCC_GetSAI3_4_PREDIV();
      sai_findiv = LL_RCC_GetSAI3_4_PREDIV();
      break;
#else
    case LL_RCC_SAI3_CLKSOURCE:
      sai_source = LL_RCC_GetSAI3ClockSource();
      sai_prediv = LL_RCC_GetSAI3_PREDIV();
      sai_findiv = LL_RCC_GetSAI3_PREDIV();
      break;

    case LL_RCC_SAI4_CLKSOURCE:
      sai_source = LL_RCC_GetSAI4ClockSource();
      sai_prediv = LL_RCC_GetSAI4_PREDIV();
      sai_findiv = LL_RCC_GetSAI4_PREDIV();
      break;
#endif /* LL_RCC_SAI34_CLKSOURCE */
    default:
      sai_source = 0U;
      sai_prediv = 0U;
      sai_findiv = 0U;
      break;
  }

  switch (sai_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      sai_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      sai_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      sai_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      sai_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      sai_source_freq = LSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_SPDIF:
      sai_source_freq = 0;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      sai_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      sai_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      sai_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      sai_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      sai_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      sai_source_freq = PLL_Clocks.freq;
      break;
    default:
      sai_source_freq = 0U;
      break;
  }

  sai_frequency = sai_source_freq / ((sai_prediv + 1U) * (sai_findiv + 1U));

  return sai_frequency;
}

/**
  * @brief  Return SPIx clock frequency
  * @param  SPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE
  *         @arg @ref LL_RCC_SPI67_CLKSOURCE
  *         @arg @ref LL_RCC_SPI8_CLKSOURCE
  * @retval SPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetSPIClockFreq(uint32_t SPIxSource)
{
  uint32_t spi_frequency;
  LL_PLL_ClocksTypeDef PLL_Clocks;
  uint32_t spi_source;
  uint32_t spi_source_freq;
  uint32_t spi_prediv;
  uint32_t spi_findiv;

  /* Add assert */

  switch (SPIxSource)
  {
    case LL_RCC_SPI1_CLKSOURCE:
      spi_source = LL_RCC_GetSPI1ClockSource();
      spi_prediv = LL_RCC_GetSPI1_PREDIV();
      spi_findiv = LL_RCC_GetSPI1_FINDIV();
      break;
#if defined(LL_RCC_SPI23_CLKSOURCE)
    case LL_RCC_SPI23_CLKSOURCE:
      spi_source = LL_RCC_GetSPI2_3ClockSource();
      spi_prediv = LL_RCC_GetSPI2_3_PREDIV();
      spi_findiv = LL_RCC_GetSPI2_3_FINDIV();
      break;
#else
    case LL_RCC_SPI2_CLKSOURCE:
      spi_source = LL_RCC_GetSPI2ClockSource();
      spi_prediv = LL_RCC_GetSPI2_PREDIV();
      spi_findiv = LL_RCC_GetSPI2_FINDIV();
      break;
    case LL_RCC_SPI3_CLKSOURCE:
      spi_source = LL_RCC_GetSPI3ClockSource();
      spi_prediv = LL_RCC_GetSPI3_PREDIV();
      spi_findiv = LL_RCC_GetSPI3_FINDIV();
      break;
#endif /* LL_RCC_SPI23_CLKSOURCE */
    case LL_RCC_SPI45_CLKSOURCE:
      spi_source = LL_RCC_GetSPI4_5ClockSource();
      spi_prediv = LL_RCC_GetSPI4_5_PREDIV();
      spi_findiv = LL_RCC_GetSPI4_5_FINDIV();
      break;
#if defined(LL_RCC_SPI67_CLKSOURCE)
    case LL_RCC_SPI67_CLKSOURCE:
      spi_source = LL_RCC_GetSPI6_7ClockSource();
      spi_prediv = LL_RCC_GetSPI6_7_PREDIV();
      spi_findiv = LL_RCC_GetSPI6_7_FINDIV();
      break;
#elif defined(LL_RCC_SPI6_CLKSOURCE)
    case LL_RCC_SPI6_CLKSOURCE:
      spi_source = LL_RCC_GetSPI6ClockSource();
      spi_prediv = LL_RCC_GetSPI6_PREDIV();
      spi_findiv = LL_RCC_GetSPI6_FINDIV();
      break;
#endif /* LL_RCC_SPI67_CLKSOURCE */
#if defined(RCC_SPI8CFGR_SPI8EN)
    case LL_RCC_SPI8_CLKSOURCE:
      spi_source = LL_RCC_GetSPI8ClockSource();
      spi_prediv = LL_RCC_GetSPI8_PREDIV();
      spi_findiv = LL_RCC_GetSPI8_FINDIV();
      break;
#endif /* RCC_SPI8CFGR_SPI8EN */
    default:
      spi_source = 0U;
      spi_prediv = 0U;
      spi_findiv = 0U;
      break;
  }

  switch (spi_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      spi_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      spi_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      spi_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      spi_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      spi_source_freq = LSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_SPDIF:
      spi_source_freq = 0;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      spi_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      spi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      spi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      spi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      spi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      spi_source_freq = PLL_Clocks.freq;
      break;
    default:
      spi_source_freq = 0U;
      break;
  }

  spi_frequency = spi_source_freq / ((spi_prediv + 1U) * (spi_findiv + 1U));

  return spi_frequency;
}

/**
  * @brief  Return UARTx clock frequency
  * @param  UARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_UART24_CLKSOURCE
  *         @arg @ref LL_RCC_USART35_CLKSOURCE
  *         @arg @ref LL_RCC_USART6_CLKSOURCE
  *         @arg @ref LL_RCC_UART78_CLKSOURCE
  *         @arg @ref LL_RCC_UART9_CLKSOURCE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval UART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetUARTClockFreq(uint32_t UARTxSource)
{
  uint32_t uart_frequency;
  uint32_t uart_source;
  uint32_t uart_prediv;
  uint32_t uart_findiv;
  uint32_t uart_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (UARTxSource)
  {
    case LL_RCC_USART1_CLKSOURCE:
      uart_source = LL_RCC_GetUSART1ClockSource();
      uart_prediv = LL_RCC_GetUSART1_PREDIV();
      uart_findiv = LL_RCC_GetUSART1_FINDIV();
      break;

    case LL_RCC_UART24_CLKSOURCE:
      uart_source = LL_RCC_GetUART2_4ClockSource();
      uart_prediv = LL_RCC_GetUART2_4_PREDIV();
      uart_findiv = LL_RCC_GetUART2_4_FINDIV();
      break;

    case LL_RCC_USART35_CLKSOURCE:
      uart_source = LL_RCC_GetUSART3_5ClockSource();
      uart_prediv = LL_RCC_GetUSART3_5_PREDIV();
      uart_findiv = LL_RCC_GetUSART3_5_FINDIV();
      break;

    case LL_RCC_USART6_CLKSOURCE:
      uart_source = LL_RCC_GetUSART6ClockSource();
      uart_prediv = LL_RCC_GetUSART6_PREDIV();
      uart_findiv = LL_RCC_GetUSART6_FINDIV();
      break;
#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
    case LL_RCC_UART78_CLKSOURCE:
      uart_source = LL_RCC_GetUART7_8ClockSource();
      uart_prediv = LL_RCC_GetUART7_8_PREDIV();
      uart_findiv = LL_RCC_GetUART7_8_FINDIV();
      break;
#else
    case LL_RCC_UART7_CLKSOURCE:
      uart_source = LL_RCC_GetUART7ClockSource();
      uart_prediv = LL_RCC_GetUART7_PREDIV();
      uart_findiv = LL_RCC_GetUART7_FINDIV();
      break;
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
#if defined(LL_RCC_UART9_CLKSOURCE)
    case LL_RCC_UART9_CLKSOURCE:
      uart_source = LL_RCC_GetUART9ClockSource();
      uart_prediv = LL_RCC_GetUART9_PREDIV();
      uart_findiv = LL_RCC_GetUART9_FINDIV();
      break;
#endif /* LL_RCC_UART9_CLKSOURCE */
    case LL_RCC_LPUART1_CLKSOURCE:
      uart_source = LL_RCC_XBAR_CLKSRC_MSI;
      uart_prediv = LL_RCC_GetLPUART1_PREDIV();
      uart_findiv = LL_RCC_GetLPUART1_FINDIV();
      break;
    default:
      uart_source = 0U;
      uart_prediv = 0U;
      uart_findiv = 0U;
      break;
  }

  switch (uart_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      uart_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      uart_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      uart_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      uart_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      uart_source_freq = LSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_SPDIF:
      uart_source_freq = 0;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      uart_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      uart_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      uart_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      uart_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      uart_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      uart_source_freq = PLL_Clocks.freq;
      break;
    default:
      uart_source_freq = 0U;
      break;
  }

  uart_frequency = uart_source_freq / ((uart_prediv + 1U) * (uart_findiv + 1U));

  return uart_frequency;
}

/**
  * @brief  Return SDMMCx clock frequency
  * @param  SDMMCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC1_CLKSOURCE
  *         @arg @ref LL_RCC_SDMMC2_CLKSOURCE
  *         @arg @ref LL_RCC_SDMMC3_CLKSOURCE
  * @retval SDMMC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetSDMMCClockFreq(uint32_t SDMMCxSource)
{
  uint32_t sdmmc_frequency;
  uint32_t sdmmc_source;
  uint32_t sdmmc_prediv;
  uint32_t sdmmc_findiv;
  uint32_t sdmmc_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (SDMMCxSource)
  {
    case LL_RCC_SDMMC1_CLKSOURCE:
      sdmmc_source = LL_RCC_GetSDMMC1ClockSource();
      sdmmc_prediv = LL_RCC_GetSDMMC1_PREDIV();
      sdmmc_findiv = LL_RCC_GetSDMMC1_FINDIV();
      break;

    case LL_RCC_SDMMC2_CLKSOURCE:
      sdmmc_source = LL_RCC_GetSDMMC2ClockSource();
      sdmmc_prediv = LL_RCC_GetSDMMC2_PREDIV();
      sdmmc_findiv = LL_RCC_GetSDMMC2_FINDIV();
      break;

    case LL_RCC_SDMMC3_CLKSOURCE:
      sdmmc_source = LL_RCC_GetSDMMC3ClockSource();
      sdmmc_prediv = LL_RCC_GetSDMMC3_PREDIV();
      sdmmc_findiv = LL_RCC_GetSDMMC3_FINDIV();
      break;

    default:
      sdmmc_source = 0U;
      sdmmc_prediv = 0U;
      sdmmc_findiv = 0U;
      break;
  }

  switch (sdmmc_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      sdmmc_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      sdmmc_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      sdmmc_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      sdmmc_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      sdmmc_source_freq = LSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_SPDIF:
      sdmmc_source_freq = 0;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      sdmmc_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      sdmmc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      sdmmc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      sdmmc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      sdmmc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      sdmmc_source_freq = PLL_Clocks.freq;
      break;
    default:
      sdmmc_source_freq = 0U;
      break;
  }

  sdmmc_frequency = sdmmc_source_freq / ((sdmmc_prediv + 1U) * (sdmmc_findiv + 1U));

  return sdmmc_frequency;
}

/**
  * @brief  Return ETHx clock frequency
  * @param  ETHxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETH1_ETHSW_CLKSOURCE
  *         @arg @ref LL_RCC_ETH2_CLKSOURCE
  *         @arg @ref LL_RCC_ETH1PTP_ETH2PTP_CLKSOURCE
  * @retval ETH clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetETHClockFreq(uint32_t ETHxSource)
{
  uint32_t eth_frequency;
  uint32_t eth_source;
  uint32_t eth_prediv;
  uint32_t eth_findiv;
  uint32_t eth_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (ETHxSource)
  {
#if defined(LL_RCC_ETH1_ETHSW_CLKSOURCE)
    case LL_RCC_ETH1_ETHSW_CLKSOURCE:
#elif defined(LL_RCC_ETH1_CLKSOURCE)
    case LL_RCC_ETH1_CLKSOURCE:
#endif /* LL_RCC_ETH1_ETHSW_CLKSOURCE */
      eth_source = LL_RCC_GetETH1ClockSource();
      eth_prediv = LL_RCC_GetETH1_PREDIV();
      eth_findiv = LL_RCC_GetETH1_FINDIV();
      break;

    case LL_RCC_ETH2_CLKSOURCE:
      eth_source = LL_RCC_GetETH2ClockSource();
      eth_prediv = LL_RCC_GetETH2_PREDIV();
      eth_findiv = LL_RCC_GetETH2_FINDIV();
      break;

    case LL_RCC_ETH1PTP_ETH2PTP_CLKSOURCE:
      eth_source = LL_RCC_GetETH1_2_PTPClockSource();
      eth_prediv = LL_RCC_GetETH1_2_PTP_PREDIV();
      eth_findiv = LL_RCC_GetETH1_2_PTP_FINDIV();
      break;

    default:
      eth_source = 0U;
      eth_prediv = 0U;
      eth_findiv = 0U;
      break;
  }

  switch (eth_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      eth_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      eth_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      eth_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      eth_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      eth_source_freq = LSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_SPDIF:
      eth_source_freq = 0;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      eth_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      eth_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      eth_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      eth_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      eth_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      eth_source_freq = PLL_Clocks.freq;
      break;
    default:
      eth_source_freq = 0U;
      break;
  }

  eth_frequency = eth_source_freq / ((eth_prediv + 1U) * (eth_findiv + 1U));

  return eth_frequency;
}

/**
  * @brief  Return OSPIx clock frequency
  * @param  OSPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OSPI1_CLKSOURCE
  *         @arg @ref LL_RCC_OSPI2_CLKSOURCE
  * @retval OSPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetOSPIClockFreq(uint32_t OSPIxSource)
{
  uint32_t ospi_frequency;
  uint32_t ospi_source;
  uint32_t ospi_prediv;
  uint32_t ospi_findiv;
  uint32_t ospi_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (OSPIxSource)
  {
    case LL_RCC_OSPI1_CLKSOURCE:
      ospi_source = LL_RCC_GetOSPI1ClockSource();
      ospi_prediv = LL_RCC_GetOSPI1_PREDIV();
      ospi_findiv = LL_RCC_GetOSPI1_FINDIV();
      break;
#if defined(LL_RCC_OSPI2_CLKSOURCE)
    case LL_RCC_OSPI2_CLKSOURCE:
      ospi_source = LL_RCC_GetOSPI2ClockSource();
      ospi_prediv = LL_RCC_GetOSPI2_PREDIV();
      ospi_findiv = LL_RCC_GetOSPI2_FINDIV();
      break;
#endif /* LL_RCC_OSPI2_CLKSOURCE */
    default:
      ospi_source = 0U;
      ospi_prediv = 0U;
      ospi_findiv = 0U;
      break;
  }

  switch (ospi_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      ospi_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      ospi_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      ospi_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      ospi_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      ospi_source_freq = LSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_SPDIF:
      ospi_source_freq = 0;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      ospi_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      ospi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      ospi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      ospi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      ospi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      ospi_source_freq = PLL_Clocks.freq;
      break;
    default:
      ospi_source_freq = 0U;
      break;
  }

  ospi_frequency = ospi_source_freq / ((ospi_prediv + 1U) * (ospi_findiv + 1U));

  return ospi_frequency;
}

/**
  * @brief  Return FMCx clock frequency
  * @param  FMCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FMC_CLKSOURCE
  * @retval FMC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetFMCClockFreq(uint32_t FMCxSource)
{
  uint32_t fmc_frequency;
  uint32_t fmc_source;
  uint32_t fmc_prediv;
  uint32_t fmc_findiv;
  uint32_t fmc_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (FMCxSource)
  {
    case LL_RCC_FMC_CLKSOURCE:
      fmc_source = LL_RCC_GetFMCClockSource();
      fmc_prediv = LL_RCC_GetFMC_PREDIV();
      fmc_findiv = LL_RCC_GetFMC_FINDIV();
      break;

    default:
      fmc_source = 0U;
      fmc_prediv = 0U;
      fmc_findiv = 0U;
      break;
  }

  switch (fmc_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      fmc_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      fmc_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      fmc_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      fmc_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      fmc_source_freq = LSE_VALUE;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      fmc_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      fmc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      fmc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      fmc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      fmc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      fmc_source_freq = PLL_Clocks.freq;
      break;
    default:
      fmc_source_freq = 0U;
      break;
  }

  fmc_frequency = fmc_source_freq / ((fmc_prediv + 1U) * (fmc_findiv + 1U));

  return fmc_frequency;
}

#if defined(FDCAN1)
/**
  * @brief  Return FDCANx clock frequency
  * @param  FDCANxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval FDCAN clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetFDCANClockFreq(uint32_t FDCANxSource)
{
  uint32_t fdcan_frequency;
  uint32_t fdcan_source;
  uint32_t fdcan_prediv;
  uint32_t fdcan_findiv;
  uint32_t fdcan_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (FDCANxSource)
  {
    case LL_RCC_FMC_CLKSOURCE:
      fdcan_source = LL_RCC_GetFDCANClockSource();
      fdcan_prediv = LL_RCC_GetFDCAN_PREDIV();
      fdcan_findiv = LL_RCC_GetFDCAN_FINDIV();
      break;

    default:
      fdcan_source = 0U;
      fdcan_prediv = 0U;
      fdcan_findiv = 0U;
      break;
  }

  switch (fdcan_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      fdcan_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      fdcan_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      fdcan_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      fdcan_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      fdcan_source_freq = LSE_VALUE;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      fdcan_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      fdcan_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      fdcan_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      fdcan_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      fdcan_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      fdcan_source_freq = PLL_Clocks.freq;
      break;
    default:
      fdcan_source_freq = 0U;
      break;
  }

  fdcan_frequency = fdcan_source_freq / ((fdcan_prediv + 1U) * (fdcan_findiv + 1U));

  return fdcan_frequency;
}
#endif /*FDCAN1*/

/**
  * @brief  Return SPDIFRXx clock frequency
  * @param  SPDIFRXxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE
  * @retval SPDIFRX clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetSPDIFRXClockFreq(uint32_t SPDIFRXxSource)
{
  uint32_t spdifrx_frequency;
  uint32_t spdifrx_source;
  uint32_t spdifrx_prediv;
  uint32_t spdifrx_findiv;
  uint32_t spdifrx_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (SPDIFRXxSource)
  {
    case LL_RCC_SPDIFRX_CLKSOURCE:
      spdifrx_source = LL_RCC_GetSPDIFRXClockSource();
      spdifrx_prediv = LL_RCC_GetSPDIFRX_PREDIV();
      spdifrx_findiv = LL_RCC_GetSPDIFRX_FINDIV();
      break;

    default:
      spdifrx_source = 0U;
      spdifrx_prediv = 0U;
      spdifrx_findiv = 0U;
      break;
  }

  switch (spdifrx_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      spdifrx_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      spdifrx_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      spdifrx_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      spdifrx_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      spdifrx_source_freq = LSE_VALUE;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      spdifrx_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      spdifrx_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      spdifrx_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      spdifrx_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      spdifrx_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      spdifrx_source_freq = PLL_Clocks.freq;
      break;
    default:
      spdifrx_source_freq = 0U;
      break;
  }

  spdifrx_frequency = spdifrx_source_freq / ((spdifrx_prediv + 1U) * (spdifrx_findiv + 1U));

  return spdifrx_frequency;
}

/**
  * @brief  Return USBPHYx clock frequency
  * @param  USBPHYxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB2PHY1_CLKSOURCE
  *         @arg @ref LL_RCC_USB2PHY2_CLKSOURCE
  *         @arg @ref LL_RCC_USB3PCIEPHY_CLKSOURCE
  * @retval USBPHY clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetUSBPHYClockFreq(uint32_t USBPHYxSource)
{
  uint32_t usbphy_frequency;
  uint32_t usbphy_source;
  uint32_t usbphy_prediv;
  uint32_t usbphy_findiv;
  uint32_t usbphy_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (USBPHYxSource)
  {
    case LL_RCC_USB2PHY1_CLKSOURCE:
      usbphy_source = LL_RCC_GetUSB2PHY1ClockSource();
      usbphy_prediv = LL_RCC_GetUSB2PHY1_PREDIV();
      usbphy_findiv = LL_RCC_GetSPDIFRX_FINDIV();
      break;

    case LL_RCC_USB2PHY2_CLKSOURCE:
      usbphy_source = LL_RCC_GetUSB2PHY2ClockSource();
      usbphy_prediv = LL_RCC_GetUSB2PHY2_PREDIV();
      usbphy_findiv = LL_RCC_GetUSB2PHY2_FINDIV();
      break;
#if defined(LL_RCC_USB3PCIEPHY_CLKSOURCE)
    case LL_RCC_USB3PCIEPHY_CLKSOURCE:
      usbphy_source = LL_RCC_GetUSB3PCIEPHYClockSource();
      usbphy_prediv = LL_RCC_GetUSB3PCIEPHY_PREDIV();
      usbphy_findiv = LL_RCC_GetUSB3PCIEPHY_FINDIV();
      break;
#endif /* LL_RCC_USB3PCIEPHY_CLKSOURCE */
    default:
      usbphy_source = 0U;
      usbphy_prediv = 0U;
      usbphy_findiv = 0U;
      break;
  }

  switch (usbphy_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      usbphy_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      usbphy_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      usbphy_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      usbphy_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      usbphy_source_freq = LSE_VALUE;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      usbphy_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      usbphy_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      usbphy_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      usbphy_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      usbphy_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      usbphy_source_freq = PLL_Clocks.freq;
      break;
    default:
      usbphy_source_freq = 0U;
      break;
  }

  usbphy_frequency = usbphy_source_freq / ((usbphy_prediv + 1U) * (usbphy_findiv + 1U));

  return usbphy_frequency;
}


/**
  * @brief  Return STGENx clock frequency
  * @param  STGENxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_STGEN_CLKSOURCE
  * @retval STGEN clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetSTGENClockFreq(uint32_t STGENxSource)
{
  uint32_t stgen_frequency;
  uint32_t stgen_source;
  uint32_t stgen_prediv;
  uint32_t stgen_findiv;
  uint32_t stgen_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (STGENxSource)
  {
    case LL_RCC_STGEN_CLKSOURCE:
      stgen_source = LL_RCC_GetSTGENClockSource();
      stgen_prediv = LL_RCC_GetSTGEN_PREDIV();
      stgen_findiv = LL_RCC_GetSTGEN_FINDIV();
      break;

    default:
      stgen_source = 0U;
      stgen_prediv = 0U;
      stgen_findiv = 0U;
      break;
  }

  switch (stgen_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      stgen_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      stgen_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      stgen_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      stgen_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      stgen_source_freq = LSE_VALUE;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      stgen_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      stgen_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      stgen_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      stgen_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      stgen_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      stgen_source_freq = PLL_Clocks.freq;
      break;
    default:
      stgen_source_freq = 0U;
      break;
  }

  stgen_frequency = stgen_source_freq / ((stgen_prediv + 1U) * (stgen_findiv + 1U));

  return stgen_frequency;
}

#if defined(DSI)
/**
  * @brief  Return DSIx clock frequency
  * @param  DSIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DSIBLANE_CLKSOURCE
  *         @arg @ref LL_RCC_DSIPHY_CLKSOURCE
  * @retval DSI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetDSIClockFreq(uint32_t DSIxSource)
{
  uint32_t dsi_frequency;
  uint32_t dsi_source;
  uint32_t dsi_prediv;
  uint32_t dsi_findiv;
  uint32_t dsi_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (DSIxSource)
  {
    case LL_RCC_DSIBLANE_CLKSOURCE:
      dsi_source = LL_RCC_GetDSIBLANEClockSource();
      dsi_prediv = LL_RCC_GetDSIBLANE_PREDIV();
      dsi_findiv = LL_RCC_GetDSIBLANE_FINDIV();
      break;

    case LL_RCC_DSIPHY_CLKSOURCE:
      dsi_source = LL_RCC_GetDSIPHYClockSource();
      dsi_prediv = LL_RCC_GetDSIPHY_PREDIV();
      dsi_findiv = LL_RCC_GetDSIPHY_FINDIV();
      break;

    default:
      dsi_source = 0U;
      dsi_prediv = 0U;
      dsi_findiv = 0U;
      break;
  }

  switch (dsi_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      dsi_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      dsi_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      dsi_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      dsi_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      dsi_source_freq = LSE_VALUE;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      dsi_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      dsi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      dsi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      dsi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      dsi_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      dsi_source_freq = PLL_Clocks.freq;
      break;
    default:
      dsi_source_freq = 0U;
      break;
  }

  dsi_frequency = dsi_source_freq / ((dsi_prediv + 1U) * (dsi_findiv + 1U));

  return dsi_frequency;
}
#endif /* DSI */

/**
  * @brief  Return ADCx clock frequency
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC12_CLKSOURCE
  *         @arg @ref LL_RCC_ADC3_CLKSOURCE
  * @retval ADC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetADCClockFreq(uint32_t ADCxSource)
{
  uint32_t adc_frequency;
  uint32_t adc_source;
  uint32_t adc_prediv;
  uint32_t adc_findiv;
  uint32_t adc_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (ADCxSource)
  {
#if defined(LL_RCC_ADC12_CLKSOURCE)
    case LL_RCC_ADC12_CLKSOURCE:
      adc_source = LL_RCC_GetADC12ClockSource();
      adc_prediv = LL_RCC_GetADC12_PREDIV();
      adc_findiv = LL_RCC_GetADC12_FINDIV();
      break;

    case LL_RCC_ADC3_CLKSOURCE:
      adc_source = LL_RCC_GetADC3ClockSource();
      adc_prediv = LL_RCC_GetADC3_PREDIV();
      adc_findiv = LL_RCC_GetADC3_FINDIV();
      break;
#elif defined(LL_RCC_ADC1_CLKSOURCE)
    case LL_RCC_ADC1_CLKSOURCE:
      adc_source = LL_RCC_GetADC1ClockSource();
      adc_prediv = LL_RCC_GetADC1_PREDIV();
      adc_findiv = LL_RCC_GetADC1_FINDIV();
      break;

    case LL_RCC_ADC2_CLKSOURCE:
      adc_source = LL_RCC_GetADC2ClockSource();
      adc_prediv = LL_RCC_GetADC2_PREDIV();
      adc_findiv = LL_RCC_GetADC2_FINDIV();
      break;
#endif /* LL_RCC_ADC1_CLKSOURCE */


    default:
      adc_source = 0U;
      adc_prediv = 0U;
      adc_findiv = 0U;
      break;
  }

  switch (adc_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      adc_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      adc_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      adc_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      adc_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      adc_source_freq = LSE_VALUE;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      adc_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      adc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      adc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      adc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      adc_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      adc_source_freq = PLL_Clocks.freq;
      break;
    default:
      adc_source_freq = 0U;
      break;
  }

  adc_frequency = adc_source_freq / ((adc_prediv + 1U) * (adc_findiv + 1U));

  return adc_frequency;
}

/**
  * @brief  Return LPTIMx clock frequency
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM12_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE
  * @retval LPTIM clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource)
{
  uint32_t lptim_frequency;
  uint32_t lptim_source;
  uint32_t lptim_prediv;
  uint32_t lptim_findiv;
  uint32_t lptim_source_freq;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Add assert */

  switch (LPTIMxSource)
  {
    case LL_RCC_LPTIM12_CLKSOURCE:
      lptim_source = LL_RCC_GetLPTIM1_2ClockSource();
      lptim_prediv = LL_RCC_GetLPTIM1_2_PREDIV();
      lptim_findiv = LL_RCC_GetLPTIM1_2_FINDIV();
      break;

    case LL_RCC_LPTIM3_CLKSOURCE:
      lptim_source = LL_RCC_GetLPTIM3ClockSource();
      lptim_prediv = LL_RCC_GetLPTIM3_PREDIV();
      lptim_findiv = LL_RCC_GetLPTIM3_FINDIV();
      break;
#if defined(LL_RCC_LPTIM45_CLKSOURCE)
    case LL_RCC_LPTIM45_CLKSOURCE:
      lptim_source = LL_RCC_GetLPTIM4_5ClockSource();
      lptim_prediv = LL_RCC_GetLPTIM4_5_PREDIV();
      lptim_findiv = LL_RCC_GetLPTIM4_5_FINDIV();
      break;
#elif defined(LL_RCC_LPTIM4_CLKSOURCE)
    case LL_RCC_LPTIM4_CLKSOURCE:
      lptim_source = LL_RCC_GetLPTIM4ClockSource();
      lptim_prediv = LL_RCC_GetLPTIM4_PREDIV();
      lptim_findiv = LL_RCC_GetLPTIM4_FINDIV();
      break;

    case LL_RCC_LPTIM5_CLKSOURCE:
      lptim_source = LL_RCC_GetLPTIM5ClockSource();
      lptim_prediv = LL_RCC_GetLPTIM5_PREDIV();
      lptim_findiv = LL_RCC_GetLPTIM5_FINDIV();
      break;
#endif /* LL_RCC_LPTIM45_CLKSOURCE */
    default:
      lptim_source = 0U;
      lptim_prediv = 0U;
      lptim_findiv = 0U;
      break;
  }

  switch (lptim_source)
  {
    case LL_RCC_XBAR_CLKSRC_HSI:
    case LL_RCC_XBAR_CLKSRC_HSIKER:
      lptim_source_freq = HSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_HSE:
    case LL_RCC_XBAR_CLKSRC_HSEKER:
      lptim_source_freq = HSE_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_MSI:
    case LL_RCC_XBAR_CLKSRC_MSIKER:
      lptim_source_freq = MSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSI:
      lptim_source_freq = LSI_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_LSE:
      lptim_source_freq = LSE_VALUE;
      break;
#if defined(LL_RCC_XBAR_CLKSRC_I2S)
    case LL_RCC_XBAR_CLKSRC_I2S:
#elif defined(LL_RCC_XBAR_CLKSRC_CK_IN)
    case LL_RCC_XBAR_CLKSRC_CK_IN :
#endif /* LL_RCC_XBAR_CLKSRC_I2S */
      lptim_source_freq = EXTERNAL_CLOCK_VALUE;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV:
      LL_RCC_GetPLL4ClockFreq(&PLL_Clocks);
      lptim_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV:
      LL_RCC_GetPLL5ClockFreq(&PLL_Clocks);
      lptim_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV:
      LL_RCC_GetPLL6ClockFreq(&PLL_Clocks);
      lptim_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV:
      LL_RCC_GetPLL7ClockFreq(&PLL_Clocks);
      lptim_source_freq = PLL_Clocks.freq;
      break;
    case LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV:
      LL_RCC_GetPLL8ClockFreq(&PLL_Clocks);
      lptim_source_freq = PLL_Clocks.freq;
      break;
    default:
      lptim_source_freq = 0U;
      break;
  }

  lptim_frequency = lptim_source_freq / ((lptim_prediv + 1U) * (lptim_findiv + 1U));

  return lptim_frequency;
}


/**
  * @brief  Return RTC clock frequency
  * @retval RTC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetRTCClockFreq(void)
{
  uint32_t rtc_source;
  uint32_t rtc_source_freq;
  uint32_t config;

  /* Add assert */
  rtc_source = LL_RCC_GetRTCClockSource();
  config = LL_RCC_GetRTC_HSEPrescaler();
  switch (rtc_source)
  {
    case LL_RCC_RTC_CLKSOURCE_HSE_DIV:
      (config != 0U) ? (rtc_source_freq = HSE_VALUE / config) : (rtc_source_freq = 0U);
      break;
    case LL_RCC_RTC_CLKSOURCE_LSI:
      rtc_source_freq = LSI_VALUE;
      break;
    case LL_RCC_RTC_CLKSOURCE_LSE:
      rtc_source_freq = LSE_VALUE;
      break;
    default:
      rtc_source_freq = 0U;
      break;
  }

  return rtc_source_freq;
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* RCC */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
