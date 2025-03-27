/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_rcc.c
  * @author  MCD Application Team
  * @brief   RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Reset and Clock Control (RCC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
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
  @verbatim
  ==============================================================================
                      ##### RCC specific features #####
  ==============================================================================
    [..]
      After reset the device is running from HSI oscillator (64 MHz), D-Cache
      and I-Cache are disabled, and all peripherals are off except internal
      SRAM, and JTAG.

      (+) There is no prescaler on High speed (AHBs) and Low speed (APBs) busses:
          all peripherals mapped on these busses are running at HSI speed.
      (+) The clock for all peripherals is switched off, except the SRAM.
      (+) All GPIOs are in analog mode, except the JTAG pins which
          are assigned to be used for debug purpose.

    [..]
      Once the device started from reset, the user application has to:
      (+) Configure the clock source to be used to drive the System clock
          (if the application needs higher frequency/performance)
      (+) Configure the System clock frequency
      (+) Configure the AHB and APB busses prescalers
      (+) Enable the clock for the peripheral(s) to be used
      (+) Configure the clock source(s) for peripherals which clocks are not
          derived from the System clock

  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @defgroup RCC RCC
  * @brief RCC HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)  || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE)   == \
                                                RCC_OSCILLATORTYPE_HSE)                     || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI)   == \
                                                RCC_OSCILLATORTYPE_HSI)                     || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_MSI)   == \
                                                RCC_OSCILLATORTYPE_MSI)                     || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI)   == \
                                                RCC_OSCILLATORTYPE_LSI)                     || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE)   == \
                                                RCC_OSCILLATORTYPE_LSE))

#define RCC_GET_MCO_GPIO_PIN(__RCC_MCOx__)    ((__RCC_MCOx__) & GPIO_PIN_MASK)
#define RCC_GET_MCO_GPIO_AF(__RCC_MCOx__)     (((__RCC_MCOx__) & RCC_MCO_GPIOAF_MASK) >> RCC_MCO_GPIOAF_POS)
#define RCC_GET_MCO_GPIO_INDEX(__RCC_MCOx__)  (((__RCC_MCOx__) & RCC_MCO_GPIOPORT_MASK) >> RCC_MCO_GPIOPORT_POS)

#if defined(GPIOJ) && defined(GPIOK)
#define RCC_GET_MCO_GPIO_PORT(__RCC_MCOx__)   ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  0U) ? GPIOA : \
                                               ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  1U) ? GPIOB : \
                                                ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  2U) ? GPIOC : \
                                                 ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  3U) ? GPIOD : \
                                                  ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  4U) ? GPIOE : \
                                                   ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  5U) ? GPIOF : \
                                                    ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  6U) ? GPIOG : \
                                                     ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  7U) ? GPIOH : \
                                                      ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  8U) ? GPIOI : \
                                                       ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  9U) ? GPIOJ : \
                                                        ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) == 10U) ? GPIOK : \
                                                         ((RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) == 11U) ? GPIOZ : \
                                                          NULL))))))))))))
#else
#define RCC_GET_MCO_GPIO_PORT(__RCC_MCOx__)   (RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  0U ? GPIOA :       \
                                               (RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  1U ? GPIOB :       \
                                                (RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  2U ? GPIOC :       \
                                                 (RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  3U ? GPIOD :       \
                                                  (RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  4U ? GPIOE :       \
                                                   (RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  5U ? GPIOF :       \
                                                    (RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  6U ? GPIOG :       \
                                                     (RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  7U ? GPIOH :       \
                                                      (RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  8U ? GPIOI :       \
                                                       (RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__)) ==  9U ? GPIOZ : NULL) \
                                                      )))))))))
#endif /* GPIOJ && GPIOK */

/**
  * @}
  */


/* Private define ------------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants
  * @{
  */
#define LSI_TIMEOUT_VALUE          2UL    /* 2 ms (minimum Tick + 1) */
#define LSE_TIMEOUT_VALUE          1000UL
#define PLL_TIMEOUT_VALUE          2UL    /* 2 ms (minimum Tick + 1) */
#define CLOCKSWITCH_TIMEOUT_VALUE  5000UL /* 5 s    */
#define FINDIV_TIMEOUT_VALUE       1UL
#define PREDIV_TIMEOUT_VALUE       1UL
#define LSMCUDIV_TIMEOUT_VALUE     1UL
#define APB1DIV_TIMEOUT_VALUE      1UL
#define APB2DIV_TIMEOUT_VALUE      1UL
#define APB3DIV_TIMEOUT_VALUE      1UL
#define APB4DIV_TIMEOUT_VALUE      1UL
#define APBDBGDIV_TIMEOUT_VALUE    1UL
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC Private Functions
  * @{
  */

void HAL_RCC_HSIMON_IRQHandler(void);
__weak void HAL_RCC_CSSCallback(void);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Returns the state of HSE clock (used or not).
  *
  * @note   The status is recomputed by reading back the settings
  *         in the SoC registers
  * @retval TRUE if HSE is used, False else
  */
static uint32_t RCC_is_hse_in_use(void)
{
  uint32_t gfg;
  uint32_t i;
  uint32_t status = 0;

  /* Check GFG */
  gfg = RCC->MUXSELCFGR;
#if defined(RCC_MUXSELCFGR_MUXSEL7)
  if ((((gfg & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL1_Msk) >> RCC_MUXSELCFGR_MUXSEL1_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL2_Msk) >> RCC_MUXSELCFGR_MUXSEL2_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL3_Msk) >> RCC_MUXSELCFGR_MUXSEL3_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL4_Msk) >> RCC_MUXSELCFGR_MUXSEL4_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL5_Msk) >> RCC_MUXSELCFGR_MUXSEL5_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL6_Msk) >> RCC_MUXSELCFGR_MUXSEL6_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL7_Msk) >> RCC_MUXSELCFGR_MUXSEL7_Pos) == 0x1U))
#else
  if ((((gfg & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL1_Msk) >> RCC_MUXSELCFGR_MUXSEL1_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL2_Msk) >> RCC_MUXSELCFGR_MUXSEL2_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL3_Msk) >> RCC_MUXSELCFGR_MUXSEL3_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL4_Msk) >> RCC_MUXSELCFGR_MUXSEL4_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL5_Msk) >> RCC_MUXSELCFGR_MUXSEL5_Pos) == 0x1U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL6_Msk) >> RCC_MUXSELCFGR_MUXSEL6_Pos) == 0x1U))
#endif
  {
    return 1;
  }

  /* HSE is ON but no pll is client so check xbar */
  for (i = 0U; i < 64U; i++)
  {
    if ((RCC->XBARxCFGR[i] & RCC_XBARxCFGR_XBARxSEL_Msk) == RCC_XBARxCFGR_XBARxSEL_6)
    {
      status = 1;
      break;
    }
  }

  return status;
}

/**
  * @brief  Returns the state of HSI clock (used or not).
  *
  * @note   The status is recomputed by reading back the settings
  *         in the SoC registers
  * @retval TRUE if HSI is used, False else
  */
static uint32_t RCC_is_hsi_in_use(void)
{
  uint32_t gfg;
  uint32_t i;
  uint32_t status = 0;

  /* Check GFG */
  gfg = RCC->MUXSELCFGR;
#if defined(RCC_MUXSELCFGR_MUXSEL7)
  if ((((gfg & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL1_Msk) >> RCC_MUXSELCFGR_MUXSEL1_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL2_Msk) >> RCC_MUXSELCFGR_MUXSEL2_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL3_Msk) >> RCC_MUXSELCFGR_MUXSEL3_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL4_Msk) >> RCC_MUXSELCFGR_MUXSEL4_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL5_Msk) >> RCC_MUXSELCFGR_MUXSEL5_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL6_Msk) >> RCC_MUXSELCFGR_MUXSEL6_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL7_Msk) >> RCC_MUXSELCFGR_MUXSEL7_Pos) == 0x0U))
#else
  if ((((gfg & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL1_Msk) >> RCC_MUXSELCFGR_MUXSEL1_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL2_Msk) >> RCC_MUXSELCFGR_MUXSEL2_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL3_Msk) >> RCC_MUXSELCFGR_MUXSEL3_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL4_Msk) >> RCC_MUXSELCFGR_MUXSEL4_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL5_Msk) >> RCC_MUXSELCFGR_MUXSEL5_Pos) == 0x0U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL6_Msk) >> RCC_MUXSELCFGR_MUXSEL6_Pos) == 0x0U))
#endif
  {
    return 1;
  }

  /* HSI is ON but no pll is client so check xbar */
  for (i = 0U; i < 64U; i++)
  {
    if ((RCC->XBARxCFGR[i] & RCC_XBARxCFGR_XBARxSEL_Msk) == RCC_XBARxCFGR_XBARxSEL_5)
    {
      status = 1;
      break;
    }
  }

  return status;
}

/**
  * @brief  Returns the state of MSI clock (used or not).
  *
  * @note   The status is recomputed by reading back the settings
  *         in the SoC registers
  * @retval TRUE if MSI is used, False else
  */
static uint32_t RCC_is_msi_in_use(void)
{
  uint32_t gfg;
  uint32_t i;
  uint32_t status = 0;

  /* Check GFG */
  gfg = RCC->MUXSELCFGR;
#if defined(RCC_MUXSELCFGR_MUXSEL7)
  if ((((gfg & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL1_Msk) >> RCC_MUXSELCFGR_MUXSEL1_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL2_Msk) >> RCC_MUXSELCFGR_MUXSEL2_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL3_Msk) >> RCC_MUXSELCFGR_MUXSEL3_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL4_Msk) >> RCC_MUXSELCFGR_MUXSEL4_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL5_Msk) >> RCC_MUXSELCFGR_MUXSEL5_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL6_Msk) >> RCC_MUXSELCFGR_MUXSEL6_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL7_Msk) >> RCC_MUXSELCFGR_MUXSEL7_Pos) == 0x2U))
#else
  if ((((gfg & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL1_Msk) >> RCC_MUXSELCFGR_MUXSEL1_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL2_Msk) >> RCC_MUXSELCFGR_MUXSEL2_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL3_Msk) >> RCC_MUXSELCFGR_MUXSEL3_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL4_Msk) >> RCC_MUXSELCFGR_MUXSEL4_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL5_Msk) >> RCC_MUXSELCFGR_MUXSEL5_Pos) == 0x2U) ||
      (((gfg & RCC_MUXSELCFGR_MUXSEL6_Msk) >> RCC_MUXSELCFGR_MUXSEL6_Pos) == 0x2U))
#endif
  {
    return 1;
  }

  /* HSE is ON but no pll is client so check xbar */
  for (i = 0U; i < 64U; i++)
  {
    if ((RCC->XBARxCFGR[i] & RCC_XBARxCFGR_XBARxSEL_Msk) == RCC_XBARxCFGR_XBARxSEL_7)
    {
      status = 1;
      break;
    }
  }

  return status;
}

/**
  * @brief  Returns the state of LSI clock (used or not).
  *
  * @note   The status is recomputed by reading back the settings
  *         in the SoC registers
  * @retval TRUE if LSI is used, False else
  */
static uint32_t RCC_is_lsi_in_use(void)
{
  uint32_t i;
  uint32_t status = 0;

  /* check xbar */
  for (i = 0U; i < 64U; i++)
  {
    if ((RCC->XBARxCFGR[i] & RCC_XBARxCFGR_XBARxSEL_Msk) == RCC_XBARxCFGR_XBARxSEL_D)
    {
      status = 1;
      break;
    }
  }

  return status;
}

/**
  * @brief  Returns the state of LSE clock (used or not).
  *
  * @note   The status is recomputed by reading back the settings
  *         in the SoC registers
  * @retval TRUE if LSE is used, False else
  */
static uint32_t RCC_is_lse_in_use(void)
{
  uint32_t i;
  uint32_t status = 0;

  /* check xbar */
  for (i = 0U; i < 64U; i++)
  {
    if ((RCC->XBARxCFGR[i] & RCC_XBARxCFGR_XBARxSEL_Msk) == RCC_XBARxCFGR_XBARxSEL_E)
    {
      status = 1;
      break;
    }
  }

  return status;
}
/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/

/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
  @verbatim
 ===============================================================================
           ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to configure the internal and external oscillators
      (HSE, HSI, LSE, MSI, LSI, PLL, CSS and MCO) and the System busses clocks (SYSCLK, AHB, APB1
       APB2, APB3 and APB4).

    [..] Internal/external clock and PLL configuration
         (+) HSI (high-speed internal): 64 MHz factory-trimmed RC used directly or through
             the PLL as System clock source.

         (+) MSI (Multiple Speed Internal): Its frequency is software trimmable (4 or 16 MHz).

         (+) LSI (low-speed internal): 32 KHz low consumption RC used as IWDG and/or RTC
             clock source.

         (+) HSE (high-speed external): 4 to 48 MHz crystal oscillator used directly or
             through the PLL as System clock source. Can be used also optionally as RTC clock source.

         (+) LSE (low-speed external): 32.768 KHz oscillator used optionally as RTC clock source.

         (+) PLL2 (clocked by HSI, HSE or MSI). This PLL is outside of the RCC but control registers
             are located inside.

         (+) PLL3 (clocked by HSI, HSE or MSI). This PLL is outside of the RCC but control registers
             are located inside.

         (+) PLL4 (clocked by HSI, HSE or MSI).

         (+) PLL5 (clocked by HSI, HSE or MSI).

         (+) PLL6 (clocked by HSI, HSE or MSI).

         (+) PLL7 (clocked by HSI, HSE or MSI).

         (+) PLL8 (clocked by HSI, HSE or MSI).

         (+) CSS (Clock security system): once enabled, if a HSE clock failure occurs
            (HSE used directly or through PLL as System clock source), the System clock
             is automatically switched to HSI and an interrupt is generated if enabled.

         (+) LSECSS (LSE Clock security system), once enabled and if a LSE clock failure occurs
             (++) The clock provided to the RTC is disabled immediately by the hardware
             (++) A failure event is generated (rcc_lsecss_fail). This event is connected to the TAMP
                  block, allowing to wake up if in low power, and allowing the protection of backup
                  registers and BKPSRAM.

         (+) MCO1 (micro controller clock output), used to output either findiv61 or flexclk_clkobs0
             (through a configurable pre-scaler).

         (+) MCO2 (micro controller clock output), used to output either findiv62 or flexclk_clkobs1
             (through a configurable pre-scaler).

    [..] System, AHB and APB busses clocks configuration
         (+) Several clock sources can be used to drive the System clock (SYSCLK): MSI, HSI,
             HSE and main PLL.
             The AHB clock (HCLK) is derived from System clock through configurable
             prescaler and used to clock the CPU, memory and peripherals mapped
             on AHB bus (DMA, GPIO...). APB1 (PCLK1) and APB2 (PCLK2) clocks are derived
             from AHB clock through configurable prescalers and used to clock
             the peripherals mapped on these busses.

         (+) The clock source frequency should be adapted depending on the device voltage range
             as listed in the Reference Manual "Clock source frequency versus voltage scaling" chapter.

  @endverbatim

  * @{
  */

/**
  * @brief  Reset the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *            - HSI ON and used as system clock source
  *            - HSE, HSI, PLL2, PLL3, PLL4, PLL5, PLL6, PLL7, PLL8 OFF
  *            - AHB, APB1 and APB2 prescaler set to 1
  *            - CSS, MCO1 and MCO2 OFF
  *            - All interrupts disabled
  *            - All interrupt and reset flags cleared
  * @note   This function doesn't modify the configuration of:
  *            - Peripheral clocks
  *            - LSI, LSE and RTC clocks
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_DeInit(void)
{
  uint32_t tickstart;
  uint32_t i;

  /* Set HSION bit to enable HSI oscillator */
  SET_BIT(RCC->OCENSETR, RCC_OCENSETR_HSION);

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till HSI is ready */
  while ((RCC->OCRDYR & RCC_OCRDYR_HSIRDY) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Reset MCO1 Configuration Register */
  CLEAR_REG(RCC->MCO1CFGR);

  /* Reset MCO2 Configuration Register */
  CLEAR_REG(RCC->MCO2CFGR);

  /* Reset xbar channels inputs */
  /* Reset FINDIVx, PREDIVx */
  for (i = 0U; i < 64U; i++)
  {
    RCC->XBARxCFGR[i] = RCC_XBAR_CLKSRC_HSI | (1U << 6);
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

  /* Reset the Oscillator Enable Control registers */

  /* Reset MSITRIM value */
  CLEAR_REG(RCC->MSICFGR);

  /* Reset RCC Clock Source Interrupt Enable Register */
  WRITE_REG(RCC->OCENCLRR, RCC_OCENCLRR_HSIKERON | RCC_OCENCLRR_HSEDIGBYP | RCC_OCENCLRR_HSEON |
            RCC_OCENCLRR_HSEKERON | RCC_OCENCLRR_HSEBYP);

  /* Clear all RCC interrupt flags */
#if defined(CORE_CA35)
  CLEAR_REG(RCC->C1CIESETR);
#elif defined(CORE_CM33)
  CLEAR_REG(RCC->C2CIESETR);
#endif /* CORE_CA35 */

  /* Clear all RCC Reset Flags */
  CLEAR_REG(RCC->HWRSTSCLRR);

  /* Adapt Systick interrupt period */
  return (HAL_InitTick(TICK_INT_PRIORITY));
}

/**
  * @brief  Initialize the RCC Oscillators according to the specified parameters in the
  *         RCC_OscInitTypeDef.
  * @param  pRCC_OscInitStruct  pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC Oscillators.
  * @note   The PLL is not disabled when used as system clock.
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this function. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this function. User should request a transition to HSE Off
  *         first and then HSE On or HSE Bypass.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef  *pRCC_OscInitStruct)
{
  uint32_t tickstart;
  uint32_t backup_domain;
  uint32_t backupdomain_mask;
  uint32_t backupdomain_reg;
  /* Check Null pointer */
  if (pRCC_OscInitStruct == NULL)
  {
    return HAL_ERROR;
  }
#if defined(PWR_BDCR1_DBD3P)
  backupdomain_mask = PWR_BDCR1_DBD3P;
  backupdomain_reg  = PWR->BDCR1;
#else
  backupdomain_mask = PWR_BDCR_DBP;
  backupdomain_reg  = PWR->BDCR;
#endif /* PWR_BDCR1_DBD3P */
  /* Check the parameters */
  assert_param(IS_RCC_OSCILLATORTYPE(pRCC_OscInitStruct->OscillatorType));

  /*------------------------------- HSE Configuration ------------------------*/
  if (((pRCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSE(pRCC_OscInitStruct->HSEState));

    /* When the HSE is used somewhere in the system it will not be disabled */
    if (RCC_is_hse_in_use() != 0U)
    {
      if (pRCC_OscInitStruct->HSEState != (RCC->OCENSETR & RCC_HSE_BYPASS_DIGITAL))
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Turning HSE off is needed before configuring */
      LL_RCC_HSE_Disable();
      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSE is stopped */
      while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == SET)
      {
        if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }

      LL_RCC_HSE_DisableBypass();
      LL_RCC_HSE_DisableDigBypass();

      /* Configure HSE oscillator */
      if (pRCC_OscInitStruct->HSEState == RCC_HSE_BYPASS_DIGITAL)
      {
        LL_RCC_HSE_EnableDigBypass();
      }
      else if (pRCC_OscInitStruct->HSEState == RCC_HSE_BYPASS)
      {
        LL_RCC_HSE_EnableBypass();
      }
      else
      {
        /* do nothing */
      }
      /* Enable oscillator */
      LL_RCC_HSE_Enable();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till HSE is ready */
      while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
      {
        if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  /*----------------------------- HSI Configuration --------------------------*/
  if (((pRCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSI(pRCC_OscInitStruct->HSIState));
    assert_param(IS_RCC_HSICALIBRATION_VALUE(pRCC_OscInitStruct->HSICalibrationValue));

    /* When the HSI is used as system clock it will not disabled */
    if (RCC_is_hsi_in_use() != 0U)
    {
      /* When HSI is used as system clock it will not disabled */
      if (pRCC_OscInitStruct->HSIState != RCC_HSI_ON)
      {
        return HAL_ERROR;
      }
      /* Otherwise, just the calibration is allowed */
      else
      {
        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(pRCC_OscInitStruct->HSICalibrationValue);
      }
    }
    else
    {
      /* Check the HSI State */
      if ((pRCC_OscInitStruct->HSIState) != RCC_HSI_OFF)
      {
        /* Enable the Internal High Speed oscillator (HSI). */
        LL_RCC_HSI_Enable();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSI is ready */
        while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }

        /* Adjusts the Internal High Speed oscillator (HSI) calibration value */
        LL_RCC_HSI_SetCalibTrimming(pRCC_OscInitStruct->HSICalibrationValue);
      }
      else
      {
        /* Disable the Internal High Speed oscillator (HSI) */
        LL_RCC_HSI_Disable();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSI is ready */
        while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != RESET)
        {
          if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }

  /*----------------------------- MSI Configuration --------------------------*/
  if (((pRCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_MSI) == RCC_OSCILLATORTYPE_MSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_MSI(pRCC_OscInitStruct->MSIState));
    assert_param(IS_RCC_MSICALIBRATION_VALUE(pRCC_OscInitStruct->MSICalibrationValue));

    /* When the MSI is used as system clock it will not be disabled */
    if (RCC_is_msi_in_use() != 0U)
    {
      if (pRCC_OscInitStruct->MSIState != RCC_MSI_ON)
      {
        return HAL_ERROR;
      }
      /* Otherwise, just the calibration is allowed */
      else
      {
        /* Adjusts the Internal High Speed oscillator (MSI) calibration value */
        LL_RCC_MSI_SetCalibTrimming(pRCC_OscInitStruct->MSICalibrationValue);
      }
    }
    else
    {
      /* Check the MSI State */
      if ((pRCC_OscInitStruct->MSIState) != RCC_MSI_OFF)
      {
        if (HAL_IS_BIT_CLR(backupdomain_reg, backupdomain_mask))
        {
          backup_domain = 1;

          /* Enable write access to Backup domain */
#if defined(PWR_BDCR1_DBD3P)
          HAL_PWR_EnableBkUpD3Access();
#else
          HAL_PWR_EnableBkUpAccess();
#endif /* PWR_BDCR1_DBD3P */

          /* Wait for Backup domain Write protection disable */
          tickstart = HAL_GetTick();
#if defined(PWR_BDCR1_DBD3P)
          while ((PWR->BDCR1 & backupdomain_mask) == (uint32_t)RESET)
#else
          while ((PWR->BDCR & backupdomain_mask) == (uint32_t)RESET)
#endif /* PWR_BDCR1_DBD3P */
          {
            if ((HAL_GetTick() - tickstart) > DBP_TIMEOUT_VALUE)
            {
              return HAL_TIMEOUT;
            }
          }
        }
        else
        {
          backup_domain = 0;
        }

#if defined(RCC_BDCR_MSIFREQSEL)
        if (pRCC_OscInitStruct->MSIFrequency == RCC_MSI_4MHZ)
        {
          CLEAR_BIT(RCC->BDCR, RCC_BDCR_MSIFREQSEL);
        }
        else
        {
          SET_BIT(RCC->BDCR, RCC_BDCR_MSIFREQSEL);
        }
#endif /* RCC_BDCR_MSIFREQSEL */

        /* Enable the Internal High Speed oscillator (MSI). */
#if defined(RCC_OCENSETR_MSION)
        SET_BIT(RCC->OCENSETR, RCC_OCENSETR_MSION);
#elif defined(RCC_D3DCR_MSION)
        SET_BIT(RCC->D3DCR, RCC_D3DCR_MSION);
#endif /* RCC_OCENSETR_MSION */

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till MSI is ready */
        while (__HAL_RCC_GET_FLAG(RCC_FLAG_MSIRDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > MSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }

        /* Adjusts the Internal High Speed oscillator (MSI) calibration value */
        __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(pRCC_OscInitStruct->MSICalibrationValue);

        /* Enable backup domain write protection */
        if (backup_domain == 1U)
        {
#if defined(PWR_BDCR1_DBD3P)
          HAL_PWR_EnableBkUpD3Access();
#else
          HAL_PWR_EnableBkUpAccess();
#endif /* PWR_BDCR1_DBD3P */
        }
      }
      else
      {
        /* Disable the Internal High Speed oscillator (MSI) */
#if defined(RCC_OCENSETR_MSION)
        CLEAR_BIT(RCC->OCENCLRR, RCC_OCENCLRR_MSION);
#elif defined(RCC_D3DCR_MSION)
        CLEAR_BIT(RCC->D3DCR, RCC_D3DCR_MSION);
#endif /* RCC_OCENSETR_MSION */
      }
    }
  }

  /*------------------------------ LSI Configuration -------------------------*/
  if (((pRCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSI(pRCC_OscInitStruct->LSIState));

    if (RCC_is_lsi_in_use() != 0U)
    {
      if (pRCC_OscInitStruct->LSIState != RCC_LSI_ON)
      {
        return HAL_ERROR;
      }
      /* Otherwise, just the calibration is allowed */
    }

    if (HAL_IS_BIT_CLR(backupdomain_reg, backupdomain_mask))
    {
      backup_domain = 1;

      /* Enable write access to Backup domain */
#if defined(PWR_BDCR1_DBD3P)
      HAL_PWR_EnableBkUpD3Access();
#else
      HAL_PWR_EnableBkUpAccess();
#endif /* PWR_BDCR1_DBD3P */

      /* Wait for Backup domain Write protection disable */
      tickstart = HAL_GetTick();

#if defined(PWR_BDCR1_DBD3P)
      while ((PWR->BDCR1 & backupdomain_mask) == (uint32_t)RESET)
#else
      while ((PWR->BDCR & backupdomain_mask) == (uint32_t)RESET)
#endif /* PWR_BDCR1_DBD3P */
      {
        if ((HAL_GetTick() - tickstart) > DBP_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      backup_domain = 0;
    }

    /* Check the LSI State */
    if (pRCC_OscInitStruct->LSIState == RCC_LSI_ON)
    {
      /* Enable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_ENABLE();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSI is ready */
      while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == RESET)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      if (pRCC_OscInitStruct->LSIState == RCC_LSI_OFF)
      {
        /* Disable the Internal Low Speed oscillator (LSI). */
        __HAL_RCC_LSI_DISABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till LSI is ready */
        while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) != RESET)
        {
          if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }

    if (backup_domain == 1U)
    {
#if defined(PWR_BDCR1_DBD3P)
      HAL_PWR_DisableBkUpD3Access();
#else
      HAL_PWR_DisableBkUpAccess();
#endif /* PWR_BDCR1_DBD3P */

    }
  }

  /*------------------------------ LSE Configuration -------------------------*/
  if (((pRCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSE(pRCC_OscInitStruct->LSEState));

    if (RCC_is_lse_in_use() != 0U)
    {
      if (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) != RESET)
      {
        if (pRCC_OscInitStruct->LSEState != (RCC->BDCR & RCC_LSE_BYPASS_DIGITAL))
        {
          return HAL_ERROR;
        }
      }
      /* Otherwise, just the calibration is allowed */
    }

    if (HAL_IS_BIT_CLR(backupdomain_reg, backupdomain_mask))
    {
      backup_domain = 1;

      /* Enable write access to Backup domain */
#if defined(PWR_BDCR1_DBD3P)
      HAL_PWR_EnableBkUpD3Access();
#else
      HAL_PWR_EnableBkUpAccess();
#endif /* PWR_BDCR1_DBD3P */

      /* Wait for Backup domain Write protection disable */
      tickstart = HAL_GetTick();

#if defined(PWR_BDCR1_DBD3P)
      while ((PWR->BDCR1 & backupdomain_mask) == (uint32_t)RESET)
#else
      while ((PWR->BDCR & backupdomain_mask) == (uint32_t)RESET)
#endif /* PWR_BDCR1_DBD3P */
      {
        if ((HAL_GetTick() - tickstart) > DBP_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      backup_domain = 0;
    }

    /* Turning LSE off is needed before configuring */
    LL_RCC_LSE_Disable();

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    /* Wait till LSE is stopped */
    while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == SET)
    {
      if ((HAL_GetTick() - tickstart) > LSE_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

    LL_RCC_LSE_DisableBypass();
    LL_RCC_LSE_DisableDigBypass();

    if (pRCC_OscInitStruct->LSEState != RCC_LSE_OFF)
    {
      if (pRCC_OscInitStruct->LSEState == RCC_LSE_BYPASS_DIGITAL)
      {
        LL_RCC_LSE_EnableDigBypass();
      }
      else if (pRCC_OscInitStruct->LSEState == RCC_LSE_BYPASS)
      {
        LL_RCC_LSE_EnableBypass();
      }
      else
      {
        /* do nothing */
      }
      /* LSEDrv */
      LL_RCC_LSE_SetDriveCapability(pRCC_OscInitStruct->LSEDriveValue);

      /* Enable oscillator */
      LL_RCC_LSE_Enable();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSE is ready */
      while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
      {
        if ((HAL_GetTick() - tickstart) > LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    if (backup_domain == 1U)
    {
#if defined(PWR_BDCR1_DBD3P)
      HAL_PWR_DisableBkUpD3Access();
#else
      HAL_PWR_DisableBkUpAccess();
#endif /* PWR_BDCR1_DBD3P */
    }
  }

  return HAL_OK;
}

/**
  * @brief  Initialize the CPU, AHB, APB busses and RTC clocks according to the specified
  *         parameters in the pRCC_ClkInitStruct.
  * @param  pRCC_ClkInitStruct  pointer to an RCC_ClkInitTypeDef structure that
  *         contains the configuration information for the RCC peripheral.
  * @param  FLatency  FLASH Latency
  *          This parameter is not used on STM32MP25.
  *
  * @note   The HSI is used by default as system clock source after
  *         startup from Reset, wake-up from STANDBY mode. The HSI frequency is 64 MHz.
  * @note   The HSI can be selected as system clock source after wakeup
  *         from STOP modes or in case of failure of the HSE used directly or indirectly
  *         as system clock (if the Clock Security System CSS is enabled).
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay or PLL locked).
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source is ready.
  * @note   You can use HAL_RCC_GetClockConfig() function to know which clock is
  *         currently used as system clock source.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef   *const pRCC_ClkInitStruct, uint32_t FLatency)
{
  uint32_t tickstart;
  uint32_t backup_domain;
  UNUSED(FLatency);/*unused variable*/
  uint32_t backupdomain_mask;

#if defined(PWR_BDCR1_DBD3P)
  backupdomain_mask = PWR_BDCR1_DBD3P;
#else
  backupdomain_mask = PWR_BDCR_DBP;
#endif /* PWR_BDCR1_DBD3P */

  /* Check Null pointer */
  if (pRCC_ClkInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_RCC_CLOCKTYPE(pRCC_ClkInitStruct->ClockType));

  /* Process LSMCUDIV to avoid potential crash, because ck_icn_ls_mcu exceeds his limit,
     when maximum frequency is applied to ck_icn_hs_mcu."
  */
  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_LS_MCU) == RCC_CLOCKTYPE_ICN_LS_MCU)
  {
    /* Cross bar is inherited from ICN_HS_MCU */

    /* Set LSMCUDIV */
    RCC->LSMCUDIVR = pRCC_ClkInitStruct->ICN_LSMCU_Div;

    /* Wait for divider to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->LSMCUDIVR & RCC_LSMCUDIVR_LSMCUDIVRDY) == (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > LSMCUDIV_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_HS_MCU) == RCC_CLOCKTYPE_ICN_HS_MCU)
  {
    /* Set flexgen dividers */
    /* if divider is < 64, use findiv */
    if (pRCC_ClkInitStruct->ICN_HS_MCU.Div <= 64U)
    {
      RCC->PREDIVxCFGR[0] = 0x0;
      RCC->FINDIVxCFGR[0] = ((pRCC_ClkInitStruct->ICN_HS_MCU.Div) - 1U) | (1U << 6);

      /* Wait for findiv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->FINDIVSR1 & 0x1U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > FINDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_HS_MCU.Div <= 128U)
    {
      RCC->FINDIVxCFGR[0] = ((pRCC_ClkInitStruct->ICN_HS_MCU.Div / 2U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[0] = 0x1;

      /* Wait for prediv & findiv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x1U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_HS_MCU.Div <= 256U)
    {
      RCC->FINDIVxCFGR[0] = ((pRCC_ClkInitStruct->ICN_HS_MCU.Div / 4U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[0] = 0x3;

      /* Wait for prediv & findiv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x1U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      RCC->FINDIVxCFGR[0] = ((pRCC_ClkInitStruct->ICN_HS_MCU.Div / 1024U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[0] = 0x3FF;

      /* Wait for prediv & findiv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x1U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Set cross bar source */
    LL_RCC_SetCrossbarSource(0, pRCC_ClkInitStruct->ICN_HS_MCU.XBAR_ClkSrc);

    /* Wait for xbar to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->XBARxCFGR[0] & 0x80U) != (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > XBAR_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

#if defined(CORE_CM33)
    /* Update SystemCoreClock */
    SystemCoreClockUpdate();
    /* Adapt Systick interrupt period */
    if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK)
    {
      return HAL_ERROR;
    }
#endif /* CORE_CM33 */
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_APB1) == RCC_CLOCKTYPE_ICN_APB1)
  {
    /* Set APB1 divider */
    LL_RCC_SetAPB1Prescaler(pRCC_ClkInitStruct->APB1_Div);

    /* Wait for divider to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->APB1DIVR & RCC_APB1DIVR_APB1DIVRDY) == (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > APB1DIV_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_APB2) == RCC_CLOCKTYPE_ICN_APB2)
  {
    /* Set APB1 divider */
    LL_RCC_SetAPB2Prescaler(pRCC_ClkInitStruct->APB2_Div);

    /* Wait for divider to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->APB2DIVR & RCC_APB2DIVR_APB2DIVRDY) == (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > APB2DIV_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_APB3) == RCC_CLOCKTYPE_ICN_APB3)
  {
    /* Set APB1 divider */
    LL_RCC_SetAPB3Prescaler(pRCC_ClkInitStruct->APB3_Div);

    /* Wait for divider to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->APB3DIVR & RCC_APB3DIVR_APB3DIVRDY) == (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > APB3DIV_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_APB4) == RCC_CLOCKTYPE_ICN_APB4)
  {
    /* Set APB1 divider */
    LL_RCC_SetAPB4Prescaler(pRCC_ClkInitStruct->APB4_Div);

    /* Wait for divider to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->APB4DIVR & RCC_APB4DIVR_APB4DIVRDY) == (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > APB4DIV_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_APBDBG) == RCC_CLOCKTYPE_ICN_APBDBG)
  {
    /* Set APBDBG divider */
    LL_RCC_SetAPBDBGPrescaler(pRCC_ClkInitStruct->APBDBG_Div);

    /* Wait for divider to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->APBDBGDIVR & RCC_APBDBGDIVR_APBDBGDIVRDY) == (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > APBDBGDIV_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_SDMMC) == RCC_CLOCKTYPE_ICN_SDMMC)
  {
    /* Set flexgen dividers */
    /* if divider is < 64, use findiv */
    if (pRCC_ClkInitStruct->ICN_SDMMC.Div <= 64U)
    {
      RCC->PREDIVxCFGR[1] = 0x0;
      RCC->FINDIVxCFGR[1] = ((pRCC_ClkInitStruct->ICN_SDMMC.Div) - 1U) | (1U << 6);

      /* Wait for findiv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->FINDIVSR1 & 0x2U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > FINDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_SDMMC.Div <= 128U)
    {
      RCC->FINDIVxCFGR[1] = ((pRCC_ClkInitStruct->ICN_SDMMC.Div / 2U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[1] = 0x1;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x2U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_SDMMC.Div <= 256U)
    {
      RCC->FINDIVxCFGR[1] = ((pRCC_ClkInitStruct->ICN_SDMMC.Div / 4U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[1] = 0x3;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x2U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      RCC->FINDIVxCFGR[1] = ((pRCC_ClkInitStruct->ICN_SDMMC.Div / 1024U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[1] = 0x3FF;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x2U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Set cross bar source */
    LL_RCC_SetCrossbarSource(1, pRCC_ClkInitStruct->ICN_SDMMC.XBAR_ClkSrc);

    /* Wait for xbar to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->XBARxCFGR[1] & 0x80U) != (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > XBAR_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_DDR) == RCC_CLOCKTYPE_ICN_DDR)
  {
    /* Set flexgen dividers */
    /* if divider is < 64, use findiv */
    if (pRCC_ClkInitStruct->ICN_DDR.Div <= 64U)
    {
      RCC->PREDIVxCFGR[2] = 0x0;
      RCC->FINDIVxCFGR[2] = ((pRCC_ClkInitStruct->ICN_DDR.Div) - 1U) | (1U << 6);

      /* Wait for findiv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->FINDIVSR1 & 0x4U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > FINDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_DDR.Div <= 128U)
    {
      RCC->FINDIVxCFGR[2] = ((pRCC_ClkInitStruct->ICN_DDR.Div / 2U) - 1U) | (1U << 6);;
      RCC->PREDIVxCFGR[2] = 0x1;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x4U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_DDR.Div <= 256U)
    {
      RCC->FINDIVxCFGR[2] = ((pRCC_ClkInitStruct->ICN_DDR.Div / 4U) - 1U) | (1U << 6);;
      RCC->PREDIVxCFGR[2] = 0x3;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x4U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      RCC->FINDIVxCFGR[2] = ((pRCC_ClkInitStruct->ICN_DDR.Div / 1024U) - 1U) | (1U << 6);;
      RCC->PREDIVxCFGR[2] = 0x3FF;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x4U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Set cross bar source */
    LL_RCC_SetCrossbarSource(2, pRCC_ClkInitStruct->ICN_DDR.XBAR_ClkSrc);

    /* Wait for xbar to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->XBARxCFGR[2] & 0x80U) != (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > XBAR_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_DISPLAY) == RCC_CLOCKTYPE_ICN_DISPLAY)
  {
    /* Set flexgen dividers */
    /* if divider is < 64, use findiv */
    if (pRCC_ClkInitStruct->ICN_DISPLAY.Div <= 64U)
    {
      RCC->PREDIVxCFGR[3] = 0x0;
      RCC->FINDIVxCFGR[3] = ((pRCC_ClkInitStruct->ICN_DISPLAY.Div) - 1U) | (1U << 6);

      /* Wait for findiv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->FINDIVSR1 & 0x8U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > FINDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_DISPLAY.Div <= 128U)
    {
      RCC->FINDIVxCFGR[3] = ((pRCC_ClkInitStruct->ICN_DISPLAY.Div / 2U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[3] = 0x1;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x8U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_DISPLAY.Div <= 256U)
    {
      RCC->FINDIVxCFGR[3] = ((pRCC_ClkInitStruct->ICN_DISPLAY.Div / 4U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[3] = 0x3;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x8U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      RCC->FINDIVxCFGR[3] = ((pRCC_ClkInitStruct->ICN_DISPLAY.Div / 1024U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[3] = 0x3FF;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x8U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Set cross bar source */
    LL_RCC_SetCrossbarSource(3, pRCC_ClkInitStruct->ICN_DISPLAY.XBAR_ClkSrc);

    /* Wait for xbar to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->XBARxCFGR[3] & 0x80U) != (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > XBAR_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_HCL) == RCC_CLOCKTYPE_ICN_HCL)
  {
    /* Set flexgen dividers */
    /* if divider is < 64, use findiv */
    if (pRCC_ClkInitStruct->ICN_HCL.Div <= 64U)
    {
      RCC->PREDIVxCFGR[4] = 0x0;
      RCC->FINDIVxCFGR[4] = ((pRCC_ClkInitStruct->ICN_HCL.Div) - 1U) | (1U << 6);

      /* Wait for findiv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->FINDIVSR1 & 0x10U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > FINDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_HCL.Div <= 128U)
    {
      RCC->FINDIVxCFGR[4] = ((pRCC_ClkInitStruct->ICN_HCL.Div / 2U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[4] = 0x1;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x10U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_HCL.Div <= 256U)
    {
      RCC->FINDIVxCFGR[4] = ((pRCC_ClkInitStruct->ICN_HCL.Div / 4U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[4] = 0x3;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x10U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      RCC->FINDIVxCFGR[4] = ((pRCC_ClkInitStruct->ICN_HCL.Div / 1024U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[4] = 0x3FF;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x10U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Set cross bar source */
    LL_RCC_SetCrossbarSource(4, pRCC_ClkInitStruct->ICN_HCL.XBAR_ClkSrc);

    /* Wait for xbar to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->XBARxCFGR[4] & 0x80U) != (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > XBAR_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_NIC) == RCC_CLOCKTYPE_ICN_NIC)
  {
    /* Set flexgen dividers */
    /* if divider is < 64, use findiv */
    if (pRCC_ClkInitStruct->ICN_NIC.Div <= 64U)
    {
      RCC->PREDIVxCFGR[5] = 0x0;
      RCC->FINDIVxCFGR[5] = ((pRCC_ClkInitStruct->ICN_NIC.Div) - 1U) | (1U << 6);

      /* Wait for findiv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->FINDIVSR1 & 0x20U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > FINDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_NIC.Div <= 128U)
    {
      RCC->FINDIVxCFGR[5] = ((pRCC_ClkInitStruct->ICN_NIC.Div / 2U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[5] = 0x1;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x20U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_NIC.Div <= 256U)
    {
      RCC->FINDIVxCFGR[5] = ((pRCC_ClkInitStruct->ICN_NIC.Div / 4U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[5] = 0x3;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x20U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      RCC->FINDIVxCFGR[5] = ((pRCC_ClkInitStruct->ICN_NIC.Div / 1024U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[5] = 0x3FF;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x20U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Set cross bar source */
    LL_RCC_SetCrossbarSource(5, pRCC_ClkInitStruct->ICN_NIC.XBAR_ClkSrc);

    /* Wait for xbar to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->XBARxCFGR[5] & 0x80U) != (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > XBAR_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_ICN_VID) == RCC_CLOCKTYPE_ICN_VID)
  {
    /* Set flexgen dividers */
    /* if divider is < 64, use findiv */
    if (pRCC_ClkInitStruct->ICN_VID.Div <= 64U)
    {
      RCC->PREDIVxCFGR[6] = 0x0;
      RCC->FINDIVxCFGR[6] = ((pRCC_ClkInitStruct->ICN_VID.Div) - 1U) | (1U << 6);

      /* Wait for findiv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->FINDIVSR1 & 0x40U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > FINDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_VID.Div <= 128U)
    {
      RCC->FINDIVxCFGR[6] = ((pRCC_ClkInitStruct->ICN_VID.Div / 2U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[6] = 0x1;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x40U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else if (pRCC_ClkInitStruct->ICN_VID.Div <= 256U)
    {
      RCC->FINDIVxCFGR[6] = ((pRCC_ClkInitStruct->ICN_VID.Div / 4U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[6] = 0x3;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x40U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      RCC->FINDIVxCFGR[6] = ((pRCC_ClkInitStruct->ICN_VID.Div / 1024U) - 1U) | (1U << 6);
      RCC->PREDIVxCFGR[6] = 0x3FF;

      /* Wait for prediv to be ready */
      tickstart = HAL_GetTick();

      while ((RCC->PREDIVSR1 & 0x40U) != (uint32_t)RESET)
      {
        if ((HAL_GetTick() - tickstart) > PREDIV_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Set cross bar source */
    LL_RCC_SetCrossbarSource(6, pRCC_ClkInitStruct->ICN_VID.XBAR_ClkSrc);

    /* Wait for xbar to be ready */
    tickstart = HAL_GetTick();

    while ((RCC->XBARxCFGR[6] & 0x80U) != (uint32_t)RESET)
    {
      if ((HAL_GetTick() - tickstart) > XBAR_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((pRCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_RTC) == RCC_CLOCKTYPE_RTC)
  {
#if defined(PWR_BDCR1_DBD3P)
    if (HAL_IS_BIT_CLR(PWR->BDCR1, PWR_BDCR1_DBD3P))
#else
    if (HAL_IS_BIT_CLR(PWR->BDCR, PWR_BDCR_DBP))
#endif /* PWR_BDCR1_DBD3P */
    {
      backup_domain = 1;

      /* Enable write access to Backup domain */
#if defined(PWR_BDCR1_DBD3P)
      HAL_PWR_EnableBkUpD3Access();
#else
      HAL_PWR_EnableBkUpAccess();
#endif /* PWR_BDCR1_DBD3P */

      /* Wait for Backup domain Write protection disable */
      tickstart = HAL_GetTick();

#if defined(PWR_BDCR1_DBD3P)
      while ((PWR->BDCR1 & backupdomain_mask) == (uint32_t)RESET)
#else
      while ((PWR->BDCR & backupdomain_mask) == (uint32_t)RESET)
#endif /* PWR_BDCR1_DBD3P */
      {
        if ((HAL_GetTick() - tickstart) > DBP_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      backup_domain = 0;
    }

    if (pRCC_ClkInitStruct->RTCState == RCC_RTC_ON)
    {
      LL_RCC_EnableRTC();

      LL_RCC_SetRTC_HSEPrescaler(pRCC_ClkInitStruct->RTC_Div);

      LL_RCC_SetRTCClockSource(pRCC_ClkInitStruct->RTC_Src);

      __HAL_RCC_RTC_CLK_ENABLE();
    }
    else
    {
      __HAL_RCC_RTC_CLK_DISABLE();

      LL_RCC_DisableRTC();
    }

    if (backup_domain == 1U)
    {
#if defined(PWR_BDCR1_DBD3P)
      HAL_PWR_DisableBkUpD3Access();
#else
      HAL_PWR_DisableBkUpAccess();
#endif /* PWR_BDCR1_DBD3P */
    }
  }

  return HAL_OK;
}

#if defined(CORE_CA35)
uint32_t HAL_RCC_GetCA35Freq(void)
{
  uint32_t source_clock;
  uint32_t Frequency;

  /* Check CA35 source (can be EXT2F or PLL1) */
  HAL_RCCEx_CA35SS_GetCA35SSClockSource(&source_clock);

  if (source_clock == 0)
  {
    /* Return PLL1 frequency */
    Frequency = HAL_RCCEx_CA35SS_GetPLL1ClockFreq();
  }
  else
  {
    Frequency = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_CPU1_EXT2F);
    if ((CA35SSC->CHGCLKREQ_RW & CA35SSC_CHGCLKREQ_RW_ARM_DIVSELACK) != CA35SSC_CHGCLKREQ_RW_ARM_DIVSELACK)
    {
      Frequency /= 2;
    }
  }

  return Frequency;
}
#endif /* CORE_CA35 */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group2 Peripheral Control functions
  * @brief   RCC clocks control functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to:

    (+) Output clock to MCO pin.
    (+) Retrieve current clock frequencies.
    (+) Enable the Clock Security System.

@endverbatim
  * @{
  */

/**
  * @brief  Select the clock source to output on MCO pin.
  * @note   PA8 should be configured in alternate function mode.
  * @param  RCC_MCOx specifies the output direction for the clock source.
  *          For STM32MP25 family this parameter can have two values:
  *            @arg @ref RCC_MCO1_PC9  Clock source to output on MCO1 pin(PC9).
  *            @arg @ref RCC_MCO1_PF11 Clock source to output on MCO1 pin(PF11).
  *            @arg @ref RCC_MCO1_PI6  Clock source to output on MCO1 pin(PI6).
  *            @arg @ref RCC_MCO1_PZ5  Clock source to output on MCO1 pin(PZ5).
  *            @arg @ref RCC_MCO2_PF10 Clock source to output on MCO2 pin(PF10).
  *            @arg @ref RCC_MCO2_PZ4  Clock source to output on MCO2 pin(PZ4).
  *            @arg @ref RCC_MCO2_PZ9  Clock source to output on MCO2 pin(PZ9).
  *            @arg @ref RCC_MCO1      Same as RCC_MCO1_PC9 (for other families compatibility).
  *            @arg @ref RCC_MCO2      Same as RCC_MCO2_PF10 (for other families compatibility).
  *            @arg @ref RCC_MCO       Same as RCC_MCO1 (for other families compatibility).
  * @param  RCC_MCOSource  specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK MCO1 is disabled
  *            @arg @ref RCC_MCO1SOURCE_CLKOBS  MCO1 source is Clock Observer 0
  *            @arg @ref RCC_MCO1SOURCE_PLL4    MCO1 source is PLL4 Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_PLL5    MCO1 source is PLL5 Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_PLL6    MCO1 source is PLL6 Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_PLL7    MCO1 source is PLL7 Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_PLL8    MCO1 source is PLL8 Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_HSI     MCO1 source is HSI Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_HSE     MCO1 source is HSE Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_MSI     MCO1 source is MSI Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_HSI_KER MCO1 source is HSI_KER Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_HSE_KER MCO1 source is HSE_KER Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_MSI_KER MCO1 source is MSI_KER Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_SPDIF   MCO1 source is SPDIF Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_I2S     MCO1 source is I2S Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_LSI     MCO1 source is LSI Through Crossbar
  *            @arg @ref RCC_MCO1SOURCE_LSE     MCO1 source is LSE Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_NOCLOCK MCO2 is disabled
  *            @arg @ref RCC_MCO2SOURCE_CLKOBS  MCO2 source is Clock Observer 0
  *            @arg @ref RCC_MCO2SOURCE_PLL4    MCO2 source is PLL4 Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_PLL5    MCO2 source is PLL5 Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_PLL6    MCO2 source is PLL6 Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_PLL7    MCO2 source is PLL7 Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_PLL8    MCO2 source is PLL8 Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_HSI     MCO2 source is HSI Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_HSE     MCO2 source is HSE Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_MSI     MCO2 source is MSI Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_HSI_KER MCO2 source is HSI_KER Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_HSE_KER MCO2 source is HSE_KER Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_MSI_KER MCO2 source is MSI_KER Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_SPDIF   MCO2 source is SPDIF Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_I2S     MCO2 source is I2S Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_LSI     MCO2 source is LSI Through Crossbar
  *            @arg @ref RCC_MCO2SOURCE_LSE     MCO2 source is LSE Through Crossbar
  * @param  RCC_MCODiv specifies the MCO prescaler.
  *          This parameter can be only be used when MCO source is through Crossbar
  *          This parameter can be any value supported by Crossbar which are
  *             1    to 64    all values
  *             66   to 128   only values multiple of 2
  *             130  to 256   only values multiple of 4
  *             1024 to 65536 only values multiple of 1024
  * @retval None
  */
void HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv)
{
  GPIO_InitTypeDef gpio_initstruct;
  uint32_t mcoindex;
  uint32_t mco_gpio_index;
  GPIO_TypeDef *mco_gpio_port;
  RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInit;

  assert_param(IS_RCC_MCO(RCC_MCOx));

  /* Common GPIO init parameters */
  gpio_initstruct.Mode      = GPIO_MODE_AF_PP;
  gpio_initstruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_initstruct.Pull      = GPIO_NOPULL;

  /* Get MCOx selection */
  mcoindex = RCC_MCOx & RCC_MCO_INDEX_MASK;

  /* Get MCOx GPIO Port */
  mco_gpio_port = RCC_GET_MCO_GPIO_PORT(RCC_MCOx);
  assert_param(IS_GPIO_ALL_INSTANCE(mco_gpio_port));

  /* GPIO Clock Enable */
  mco_gpio_index = RCC_GET_MCO_GPIO_INDEX(RCC_MCOx);
  switch (mco_gpio_index)
  {
    case 2 :
      __HAL_RCC_GPIOC_CLK_ENABLE();
      break;
    case 5 :
      __HAL_RCC_GPIOF_CLK_ENABLE();
      break;
    case 8 :
      __HAL_RCC_GPIOI_CLK_ENABLE();
      break;
    case 11 :
      __HAL_RCC_GPIOZ_CLK_ENABLE();
      break;
    default :
      /* No MCO output on other GPIO ports */
      break;
  }

  /* Configure the MCOx pin in alternate function mode */
  gpio_initstruct.Pin = RCC_GET_MCO_GPIO_PIN(RCC_MCOx);
  gpio_initstruct.Alternate = RCC_GET_MCO_GPIO_AF(RCC_MCOx);
  HAL_GPIO_Init(mco_gpio_port, &gpio_initstruct);

  if (mcoindex == RCC_MCO1_INDEX)
  {
    assert_param(IS_RCC_MCODIV(RCC_MCODiv));
    assert_param(IS_RCC_MCO1SOURCE(RCC_MCOSource));

    if (RCC_MCOSource == RCC_MCO1SOURCE_NOCLOCK)
    {
      /* Disable MCO1 */
      __HAL_RCC_MCO1_DISABLE();
    }
    else if (RCC_MCOSource == RCC_MCO1SOURCE_CLKOBS)
    {
      /* Enable MCO1 and set source to Clock Observer 0 */
      __HAL_RCC_MCO1_ENABLE();
      SET_BIT(RCC->MCO1CFGR, RCC_MCO1CFGR_MCO1SEL);
    }
    else
    {
      /* Enable MCO1, set source to Crossbar and configure Crossbar channel source */
      __HAL_RCC_MCO1_ENABLE();
      CLEAR_BIT(RCC->MCO1CFGR, RCC_MCO1CFGR_MCO1SEL);
      RCC_PeriphCLKInit.XBAR_Channel = RCC_PERIPHCLK_MCO1;
      RCC_PeriphCLKInit.XBAR_ClkSrc = RCC_MCOSource & 0xFFUL;
      RCC_PeriphCLKInit.Div = RCC_MCODiv;
      (void)HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInit);
    }
  }
  else if (mcoindex == RCC_MCO2_INDEX)
  {
    assert_param(IS_RCC_MCODIV(RCC_MCODiv));
    assert_param(IS_RCC_MCO2SOURCE(RCC_MCOSource));

    if (RCC_MCOSource == RCC_MCO2SOURCE_NOCLOCK)
    {
      /* Disable MCO2 */
      __HAL_RCC_MCO2_DISABLE();
    }
    else if (RCC_MCOSource == RCC_MCO2SOURCE_CLKOBS)
    {
      /* Enable MCO2 and set source to Clock Observer 0 */
      __HAL_RCC_MCO2_ENABLE();
      SET_BIT(RCC->MCO2CFGR, RCC_MCO2CFGR_MCO2SEL);
    }
    else
    {
      /* Enable MCO2, set source to Crossbar and configure Crossbar channel source */
      __HAL_RCC_MCO2_ENABLE();
      CLEAR_BIT(RCC->MCO2CFGR, RCC_MCO2CFGR_MCO2SEL);
      RCC_PeriphCLKInit.XBAR_Channel = RCC_PERIPHCLK_MCO2;
      RCC_PeriphCLKInit.XBAR_ClkSrc = RCC_MCOSource & 0xFFUL;
      RCC_PeriphCLKInit.Div = RCC_MCODiv;
      (void)HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInit);
    }
  }
  else
  {
    /* nothing to do */
  }
}

/**
  * @brief  Get the pRCC_OscInitStruct according to the internal
  *         RCC configuration registers.
  * @param  pRCC_OscInitStruct  pointer to an RCC_OscInitTypeDef structure that
  *         will be filled with current OSCs config.
  * @retval None
  */
void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *pRCC_OscInitStruct)
{
  uint32_t temp_reg;

  pRCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI |
                                       RCC_OSCILLATORTYPE_MSI | RCC_OSCILLATORTYPE_LSI |
                                       RCC_OSCILLATORTYPE_LSE;

  /* Get HSE Config */
  temp_reg = RCC->OCENSETR;
  if ((temp_reg & RCC_HSE_BYPASS_DIGITAL) == RCC_HSE_BYPASS_DIGITAL)
  {
    pRCC_OscInitStruct->HSEState = RCC_HSE_BYPASS_DIGITAL;
  }
  else if ((temp_reg & RCC_HSE_BYPASS) == RCC_HSE_BYPASS)
  {
    pRCC_OscInitStruct->HSEState = RCC_HSE_BYPASS;
  }
  else if ((temp_reg & RCC_HSE_ON) == RCC_HSE_ON)
  {
    pRCC_OscInitStruct->HSEState = RCC_HSE_ON;
  }
  else
  {
    pRCC_OscInitStruct->HSEState = RCC_HSE_OFF;
  }

  /* Get HSI Config */
  temp_reg = RCC->OCENSETR;
  if ((temp_reg & RCC_HSI_ON) == RCC_HSI_ON)
  {
    pRCC_OscInitStruct->HSIState = RCC_HSI_ON;
  }
  else
  {
    pRCC_OscInitStruct->HSIState = RCC_HSI_OFF;
  }
  pRCC_OscInitStruct->HSICalibrationValue = LL_RCC_HSI_GetCalibration();

  /* Get MSI Config */
#if defined(RCC_D3DCR_MSION)
  temp_reg = RCC->D3DCR;
#else
  temp_reg = RCC->OCENSETR;
#endif /* RCC_D3DCR_MSION */

  if ((temp_reg & RCC_MSI_ON) == RCC_MSI_ON)
  {
    pRCC_OscInitStruct->MSIState = RCC_MSI_ON;
  }
  else
  {
    pRCC_OscInitStruct->MSIState = RCC_MSI_OFF;
  }
  pRCC_OscInitStruct->MSICalibrationValue = LL_RCC_MSI_GetCalibTrimming();
#if defined(RCC_BDCR_MSIFREQSEL)
  if (READ_BIT(RCC->BDCR, RCC_BDCR_MSIFREQSEL) == 0U)
  {
    pRCC_OscInitStruct->MSIFrequency = RCC_MSI_4MHZ;
  }
  else
#endif /* RCC_BDCR_MSIFREQSEL */
  {
    pRCC_OscInitStruct->MSIFrequency = RCC_MSI_16MHZ;
  }

  /* Get LSI Config */
  temp_reg = RCC->BDCR;
  if ((temp_reg & RCC_LSI_ON) == RCC_LSI_ON)
  {
    pRCC_OscInitStruct->LSIState = RCC_LSI_ON;
  }
  else
  {
    pRCC_OscInitStruct->LSIState = RCC_LSI_OFF;
  }

  /* Get LSE Config */
  temp_reg = RCC->BDCR;
  if ((temp_reg & RCC_LSE_BYPASS_DIGITAL) == RCC_LSE_BYPASS_DIGITAL)
  {
    pRCC_OscInitStruct->LSEState = RCC_LSE_BYPASS_DIGITAL;
  }
  else if ((temp_reg & RCC_LSE_BYPASS) == RCC_LSE_BYPASS)
  {
    pRCC_OscInitStruct->LSEState = RCC_LSE_BYPASS;
  }
  else if ((temp_reg & RCC_LSE_ON) == RCC_LSE_ON)
  {
    pRCC_OscInitStruct->LSEState = RCC_LSE_ON;
  }
  else
  {
    pRCC_OscInitStruct->LSEState = RCC_LSE_OFF;
  }
  pRCC_OscInitStruct->LSEDriveValue = LL_RCC_LSE_GetDriveCapability();
}

/**
  * @brief  Get the pRCC_ClkInitStruct according to the internal
  *         RCC configuration registers.
  * @param  pRCC_ClkInitStruct  pointer to an RCC_ClkInitTypeDef structure that
  *         will be filled with current clock configuration.
  * @param  pFLatency  This parameter is not used on STM32MP25.
  * @retval None
  */
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *pRCC_ClkInitStruct, const uint32_t *pFLatency)
{
  pRCC_ClkInitStruct->ClockType = RCC_CLOCKTYPE_ICN_HS_MCU | RCC_CLOCKTYPE_ICN_LS_MCU | RCC_CLOCKTYPE_ICN_SDMMC |
                                  RCC_CLOCKTYPE_ICN_DDR | RCC_CLOCKTYPE_ICN_DISPLAY | RCC_CLOCKTYPE_ICN_HCL |
                                  RCC_CLOCKTYPE_ICN_NIC | RCC_CLOCKTYPE_ICN_VID | RCC_CLOCKTYPE_ICN_APB1 |
                                  RCC_CLOCKTYPE_ICN_APB2 | RCC_CLOCKTYPE_ICN_APB3 | RCC_CLOCKTYPE_ICN_APB4 |
                                  RCC_CLOCKTYPE_ICN_APBDBG | RCC_CLOCKTYPE_RTC;
  uint32_t config;
  /* Get ICN_HS_MCU config */
  UNUSED(pFLatency); /*unused variable*/
  pRCC_ClkInitStruct->ICN_HS_MCU.XBAR_ClkSrc = LL_RCC_GetCrossbarSource(0);
  config = ((RCC->FINDIVxCFGR[0] & RCC_FINDIVxCFGR_FINDIVx_Msk) + 1U);
  pRCC_ClkInitStruct->ICN_HS_MCU.Div = config * ((RCC->PREDIVxCFGR[0] & RCC_PREDIVxCFGR_PREDIVx_Msk) + 1U);

  /* Get ICN_LS_MCU config */
  pRCC_ClkInitStruct->ICN_LSMCU_Div = RCC->LSMCUDIVR & 1U;

  /* Get ICN_SDMMC config */
  pRCC_ClkInitStruct->ICN_SDMMC.XBAR_ClkSrc = LL_RCC_GetCrossbarSource(1);
  config = ((RCC->FINDIVxCFGR[1] & RCC_FINDIVxCFGR_FINDIVx_Msk) + 1U);
  pRCC_ClkInitStruct->ICN_SDMMC.Div = config * ((RCC->PREDIVxCFGR[1] & RCC_PREDIVxCFGR_PREDIVx_Msk) + 1U);

  /* Get ICN_DDR config */
  pRCC_ClkInitStruct->ICN_DDR.XBAR_ClkSrc = LL_RCC_GetCrossbarSource(2);
  config = ((RCC->FINDIVxCFGR[2] & RCC_FINDIVxCFGR_FINDIVx_Msk) + 1U);
  pRCC_ClkInitStruct->ICN_DDR.Div = config * ((RCC->PREDIVxCFGR[2] & RCC_PREDIVxCFGR_PREDIVx_Msk) + 1U);

  /* Get ICN_DISPLAY config */
  pRCC_ClkInitStruct->ICN_DISPLAY.XBAR_ClkSrc = LL_RCC_GetCrossbarSource(3);
  config = ((RCC->FINDIVxCFGR[3] & RCC_FINDIVxCFGR_FINDIVx_Msk) + 1U);
  pRCC_ClkInitStruct->ICN_DISPLAY.Div = config * ((RCC->PREDIVxCFGR[3] & RCC_PREDIVxCFGR_PREDIVx_Msk) + 1U);

  /* Get ICN_HCL config */
  pRCC_ClkInitStruct->ICN_HCL.XBAR_ClkSrc = LL_RCC_GetCrossbarSource(4);
  config = ((RCC->FINDIVxCFGR[4] & RCC_FINDIVxCFGR_FINDIVx_Msk) + 1U);
  pRCC_ClkInitStruct->ICN_HCL.Div = config * ((RCC->PREDIVxCFGR[4] & RCC_PREDIVxCFGR_PREDIVx_Msk) + 1U);

  /* Get ICN_NIC config */
  pRCC_ClkInitStruct->ICN_NIC.XBAR_ClkSrc = LL_RCC_GetCrossbarSource(5);
  config = ((RCC->FINDIVxCFGR[5] & RCC_FINDIVxCFGR_FINDIVx_Msk) + 1U);
  pRCC_ClkInitStruct->ICN_NIC.Div = config * ((RCC->PREDIVxCFGR[5] & RCC_PREDIVxCFGR_PREDIVx_Msk) + 1U);

  /* Get ICN_VID config */
  pRCC_ClkInitStruct->ICN_VID.XBAR_ClkSrc = LL_RCC_GetCrossbarSource(6);
  config = ((RCC->FINDIVxCFGR[6] & RCC_FINDIVxCFGR_FINDIVx_Msk) + 1U);
  pRCC_ClkInitStruct->ICN_VID.Div = config * ((RCC->PREDIVxCFGR[6] & RCC_PREDIVxCFGR_PREDIVx_Msk) + 1U);

  /* Get ICN_APB1 config */
  pRCC_ClkInitStruct->APB1_Div = LL_RCC_GetAPB1Prescaler();

  /* Get ICN_APB2 config */
  pRCC_ClkInitStruct->APB2_Div = LL_RCC_GetAPB2Prescaler();

  /* Get ICN_APB3 config */
  pRCC_ClkInitStruct->APB3_Div = LL_RCC_GetAPB3Prescaler();

  /* Get ICN_APB4 config */
  pRCC_ClkInitStruct->APB4_Div = LL_RCC_GetAPB4Prescaler();

  /* Get ICN_APBDBG config */
  pRCC_ClkInitStruct->APBDBG_Div = LL_RCC_GetAPBDBGPrescaler();

  /* Get RTC settings */
  if (READ_BIT(RCC->BDCR, RCC_BDCR_RTCCKEN) == 0U)
  {
    pRCC_ClkInitStruct->RTCState = RCC_RTC_OFF;
  }
  else
  {
    pRCC_ClkInitStruct->RTCState = RCC_RTC_ON;
  }

  pRCC_ClkInitStruct->RTC_Src = LL_RCC_GetRTCClockSource();

  pRCC_ClkInitStruct->RTC_Div = LL_RCC_GetRTC_HSEPrescaler();
}

/**
  * @brief  Returns the bus clocks frequencies
  *
  * @note   The bus frequencies are recomputed by reading back the settings
  *         in the SoC registers
  * @param  clk  Specifies which output clock frequency should be recomputed.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_CLOCKTYPE_ICN_HS_MCU
  *            @arg @ref RCC_CLOCKTYPE_ICN_LS_MCU
  *            @arg @ref RCC_CLOCKTYPE_ICN_APB1
  *            @arg @ref RCC_CLOCKTYPE_ICN_APB2
  *            @arg @ref RCC_CLOCKTYPE_ICN_APB3
  *            @arg @ref RCC_CLOCKTYPE_ICN_APB4
  *            @arg @ref RCC_CLOCKTYPE_ICN_APBDBG
  *            @arg @ref RCC_CLOCKTYPE_ICN_SDMMC
  *            @arg @ref RCC_CLOCKTYPE_ICN_DDR
  *            @arg @ref RCC_CLOCKTYPE_ICN_DISPLAY
  *            @arg @ref RCC_CLOCKTYPE_ICN_HCL
  *            @arg @ref RCC_CLOCKTYPE_ICN_NIC
  *            @arg @ref RCC_CLOCKTYPE_ICN_VID
  * @retval Bus frequency
  */
uint32_t HAL_RCC_GetFreq(uint32_t clk)
{
  uint32_t freq;
  uint32_t lsmcudiv;
  uint32_t fg_freq;
  uint32_t fgindex;
  uint32_t xbar_source;
  uint32_t xbar_source_freq;
  uint32_t config;
  /* Identify flexgen id based on 'clk' */
  switch (clk)
  {
    case RCC_CLOCKTYPE_ICN_SDMMC:
      fgindex = 1;
      break;
    case RCC_CLOCKTYPE_ICN_DDR:
      fgindex = 2;
      break;
    case RCC_CLOCKTYPE_ICN_DISPLAY:
      fgindex = 3;
      break;
    case RCC_CLOCKTYPE_ICN_HCL:
      fgindex = 4;
      break;
    case RCC_CLOCKTYPE_ICN_NIC:
      fgindex = 5;
      break;
    case RCC_CLOCKTYPE_ICN_VID:
      fgindex = 6;
      break;
    default:
      fgindex = 0;
      break;
  }

  /* Identify xbar source */
  xbar_source = LL_RCC_GetCrossbarSource(fgindex);

  /* Then retrieve the source frequency */
  switch (xbar_source)
  {
    case RCC_XBAR_CLKSRC_PLL4:
      xbar_source_freq = HAL_RCCEx_GetPLL4ClockFreq();
      break;

    case RCC_XBAR_CLKSRC_PLL5:
      xbar_source_freq = HAL_RCCEx_GetPLL5ClockFreq();
      break;

    case RCC_XBAR_CLKSRC_PLL6:
      xbar_source_freq = HAL_RCCEx_GetPLL6ClockFreq();
      break;

    case RCC_XBAR_CLKSRC_PLL7:
      xbar_source_freq = HAL_RCCEx_GetPLL7ClockFreq();
      break;

    case RCC_XBAR_CLKSRC_PLL8:
      xbar_source_freq = HAL_RCCEx_GetPLL8ClockFreq();
      break;

    case RCC_XBAR_CLKSRC_HSI:
      xbar_source_freq = HSI_VALUE;
      break;

    case RCC_XBAR_CLKSRC_HSE:
      xbar_source_freq = HSE_VALUE;
      break;

    case RCC_XBAR_CLKSRC_LSI:
      xbar_source_freq = LSI_VALUE;
      break;

    case RCC_XBAR_CLKSRC_LSE:
      xbar_source_freq = LSE_VALUE;
      break;

    case RCC_XBAR_CLKSRC_MSI:
#if defined(RCC_BDCR_MSIFREQSEL)
      if (READ_BIT(RCC->BDCR, RCC_BDCR_MSIFREQSEL) == 0U)
      {
        xbar_source_freq = RCC_MSI_4MHZ;
      }
      else
#endif /* RCC_BDCR_MSIFREQSEL */
      {
        xbar_source_freq = RCC_MSI_16MHZ;
      }
      break;

    default:
      xbar_source_freq = 0;
      break;
  }
  config = ((RCC->FINDIVxCFGR[fgindex] & RCC_FINDIVxCFGR_FINDIVx_Msk) + 1U);
  fg_freq = xbar_source_freq / (config * ((RCC->PREDIVxCFGR[fgindex] & RCC_PREDIVxCFGR_PREDIVx_Msk) + 1U));

  lsmcudiv = ((uint32_t)(RCC->LSMCUDIVR) & RCC_LSMCUDIVR_LSMCUDIV_Msk) + 1U;

  switch (clk)
  {
    case RCC_CLOCKTYPE_ICN_HS_MCU:
    case RCC_CLOCKTYPE_ICN_SDMMC:
    case RCC_CLOCKTYPE_ICN_DDR:
    case RCC_CLOCKTYPE_ICN_DISPLAY:
    case RCC_CLOCKTYPE_ICN_HCL:
    case RCC_CLOCKTYPE_ICN_NIC:
    case RCC_CLOCKTYPE_ICN_VID:
      return fg_freq;
      break;
    case RCC_CLOCKTYPE_ICN_LS_MCU:
      /* return fg freq divided by LSMCU */
      freq = fg_freq / lsmcudiv;
      break;
    case RCC_CLOCKTYPE_ICN_APB1:
      /* return fg freq divided by LSMCU divided by APB1DIV */
      freq = fg_freq / ((uint32_t)(1UL << READ_BIT(RCC->APB1DIVR, RCC_APB1DIVR_APB1DIV)) * lsmcudiv);
      break;
    case RCC_CLOCKTYPE_ICN_APB2:
      /* return fg freq divided by LSMCU divided by APB2DIV */
      freq = fg_freq / ((uint32_t)(1UL << READ_BIT(RCC->APB2DIVR, RCC_APB2DIVR_APB2DIV)) * lsmcudiv);
      break;
    case RCC_CLOCKTYPE_ICN_APB3:
      /* return fg freq divided by LSMCU divided by APB3DIV */
      freq = fg_freq / ((uint32_t)(1UL << READ_BIT(RCC->APB3DIVR, RCC_APB3DIVR_APB3DIV)) * lsmcudiv);
      break;
    case RCC_CLOCKTYPE_ICN_APB4:
      /* return fg freq divided by LSMCU divided by APB4DIV */
      freq = fg_freq / ((uint32_t)(1UL << READ_BIT(RCC->APB4DIVR, RCC_APB4DIVR_APB4DIV)) * lsmcudiv);
      break;
    case RCC_CLOCKTYPE_ICN_APBDBG:
      /* return fg freq divided by LSMCU divided by APBDBGDIV */
      freq = fg_freq / ((uint32_t)(1UL << READ_BIT(RCC->APBDBGDIVR, RCC_APBDBGDIVR_APBDBGDIV)) * lsmcudiv);
      break;
    default: /* Unknown clock */
      freq = 0xFFFFFFFFU;
      break;
  }

  return freq;
}

/**
  * @brief  Return the clock source of a peripheral
  * @param  clk_id  The parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_LPTIM1_2
  *            @arg @ref RCC_PERIPHCLK_UART2_4
  *            @arg @ref RCC_PERIPHCLK_UART3_5
  *            @arg @ref RCC_PERIPHCLK_SPI2_3
  *            @arg @ref RCC_PERIPHCLK_SPDIFRX
  *            @arg @ref RCC_PERIPHCLK_I2C1_2
  *            @arg @ref RCC_PERIPHCLK_I3C1_2
  *            @arg @ref RCC_PERIPHCLK_I2C3_5
  *            @arg @ref RCC_PERIPHCLK_I3C3
  *            @arg @ref RCC_PERIPHCLK_I2C4_6
  *            @arg @ref RCC_PERIPHCLK_I2C7
  *            @arg @ref RCC_PERIPHCLK_SPI1
  *            @arg @ref RCC_PERIPHCLK_SPI4_5
  *            @arg @ref RCC_PERIPHCLK_SPI6_7
  *            @arg @ref RCC_PERIPHCLK_USART1
  *            @arg @ref RCC_PERIPHCLK_USART6
  *            @arg @ref RCC_PERIPHCLK_UART7_8
  *            @arg @ref RCC_PERIPHCLK_UART9
  *            @arg @ref RCC_PERIPHCLK_SAI1_MDF1
  *            @arg @ref RCC_PERIPHCLK_SAI2
  *            @arg @ref RCC_PERIPHCLK_SAI3_4
  *            @arg @ref RCC_PERIPHCLK_FDCAN
  *            @arg @ref RCC_PERIPHCLK_LTDC
  *            @arg @ref RCC_PERIPHCLK_DSIPHY
  *            @arg @ref RCC_PERIPHCLK_DCMIPP
  *            @arg @ref RCC_PERIPHCLK_CSITXESC
  *            @arg @ref RCC_PERIPHCLK_CSIPHY
  *            @arg @ref RCC_PERIPHCLK_LVDSPHY
  *            @arg @ref RCC_PERIPHCLK_STGEN
  *            @arg @ref RCC_PERIPHCLK_USB3PCIEPHY
  *            @arg @ref RCC_PERIPHCLK_USBTC
  *            @arg @ref RCC_PERIPHCLK_I3C4
  *            @arg @ref RCC_PERIPHCLK_SPI8
  *            @arg @ref RCC_PERIPHCLK_I2C8
  *            @arg @ref RCC_PERIPHCLK_LPUART1
  *            @arg @ref RCC_PERIPHCLK_LPTIM3
  *            @arg @ref RCC_PERIPHCLK_LPTIM4_5
  *            @arg @ref RCC_PERIPHCLK_ADF1
  *            @arg @ref RCC_PERIPHCLK_TSDBG
  *            @arg @ref RCC_PERIPHCLK_TPIU
  *            @arg @ref RCC_PERIPHCLK_ATB
  *            @arg @ref RCC_PERIPHCLK_ADC12
  *            @arg @ref RCC_PERIPHCLK_ADC3
  *            @arg @ref RCC_PERIPHCLK_OSPI1
  *            @arg @ref RCC_PERIPHCLK_OSPI2
  *            @arg @ref RCC_PERIPHCLK_FMC
  *            @arg @ref RCC_PERIPHCLK_SDMMC1
  *            @arg @ref RCC_PERIPHCLK_SDMMC2
  *            @arg @ref RCC_PERIPHCLK_SDMMC3
  *            @arg @ref RCC_PERIPHCLK_ETH1_ETHSW
  *            @arg @ref RCC_PERIPHCLK_ETH2
  *            @arg @ref RCC_PERIPHCLK_ETH1PTP_ETH2PTP
  *            @arg @ref RCC_PERIPHCLK_USB2PHY1
  *            @arg @ref RCC_PERIPHCLK_USB2PHY2
  *            @arg @ref RCC_PERIPHCLK_ICN_M_GPU
  *            @arg @ref RCC_PERIPHCLK_ETHSWREF
  *            @arg @ref RCC_PERIPHCLK_MCO1
  *            @arg @ref RCC_PERIPHCLK_MCO2
  *            @arg @ref RCC_PERIPHCLK_CPU1_EXT2F
  * @retval clock source
  */
uint32_t HAL_RCC_GetSource(uint32_t clk_id)
{
  uint32_t source;
  RCC_PeriphCLKInitTypeDef PeriphCLKConfig = {0};

  PeriphCLKConfig.XBAR_Channel = clk_id;

  HAL_RCCEx_GetPeriphCLKConfig(&PeriphCLKConfig);

  source = PeriphCLKConfig.XBAR_ClkSrc;

  return source;
}

/**
  * @brief  Return the CM33 frequency.
  * @retval CM33 frequency in Hz
  */
uint32_t HAL_RCC_GetCM33Freq(void)
{
  return HAL_RCC_GetFreq(RCC_CLOCKTYPE_ICN_HS_MCU);
}

/**
  * @brief Handle the RCC global interrupt request.
  * @retval None
  */
void HAL_RCC_IRQHandler(void)
{
  uint32_t Flags = 0;

  __HAL_RCC_CLEAR_IT(0xFFFFFFFFU);

  /* RCC interrupt user callback */
  HAL_RCC_Callback(Flags);
}

/**
  * @brief  RCC global interrupt callback
  * @param  Flags: It contains the flags which were set during the RCC_IRQHandler
  *                before cleaning them
  * @retval None
  */
__weak void HAL_RCC_Callback(uint32_t Flags)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RCC_Callback could be implemented in the user file
  */
  UNUSED(Flags); /* unused variable */
}

/**
  * @brief Handle the RCC wakeup interrupt request.
  * @retval None
  */
void HAL_RCC_WAKEUP_IRQHandler(void)
{
  uint32_t Flags = 0;

  /* RCC wakeup interrupt user callback */
  HAL_RCC_WAKEUP_Callback(Flags);
}

/**
  * @brief  RCC wakeup interrupt callback
  * @param  Flags: It contains the flags which were set during the RCC_WAKEUP_IRQHandler
  *                before cleaning them
  * @retval None
  */
__weak void HAL_RCC_WAKEUP_Callback(uint32_t Flags)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RCC_WAKEUP_Callback could be implemented in the user file
  */
  UNUSED(Flags); /* unused variable */
}

/**
  * @brief Handle the RCC HSIMON interrupt request.
  * @retval None
  */
void HAL_RCC_HSIMON_IRQHandler(void)
{
  uint32_t Flags = 0;

  /* RCC HSIMON interrupt user callback */
  HAL_RCC_HSIMON_Callback(Flags);
}

/**
  * @brief  RCC HSIMON interrupt callback
  * @param  Flags: It contains the flags which were set during the RCC_HSIMON_IRQHandler
  *                before cleaning them
  * @retval None
  */
__weak void HAL_RCC_HSIMON_Callback(uint32_t Flags)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RCC_HSIMON_Callback could be implemented in the user file
  */
  UNUSED(Flags); /* unused variable */
}

/**
  * @brief  RCC Clock Security System interrupt callback.
  * @retval none
  */
__weak void HAL_RCC_CSSCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RCC_CSSCallback should be implemented in the user file
   */
}

/* Read a register in same device to be sure that previous write operation */
/* into RCC_RxSEMCR is completed (without breaking processor pipeline).    */
__STATIC_INLINE HAL_StatusTypeDef WAIT_MUTEX_WRITTEN_IN_RCC_RxSEMCR(uint32_t LocalResIndex)
{
  /* Therefore, we take this opportunity to check (by reading register RCC_RxCIDCFGR[i]) */
  /* that a dynamic CID filtering is effectively configured for present local resource. */
  if ((READ_REG(RCC->R[LocalResIndex].CIDCFGR) & RCC_LOCALRES_ATTR_CID_TYPE_MSK) == RCC_LOCALRES_CID_TYPE_DYNAMIC)
  {
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @}
  */
/** @defgroup RCC_Exported_Functions_Group3 Attributes management functions
  *  @brief Attributes management functions.
  *
@verbatim
 ===============================================================================
                       ##### RCC attributes functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/** @defgroup RCC_HAL_RIF_Exported_Functions RCC HAL RIF Exported Functions
  * @{
  */

/** @defgroup RCC_HAL_EF_RIF RCC HAL RIF
  * @brief RCC HAL RIF module driver
  * @{
  */

/* On secure Cortex core only : */
#if defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  Configure Security/Privilege/CID Access Filtering of one RCC Local Resource
  *         Lock this configuration if requested
  * @param  LocalResIndex Value can be 0 - 113 and ref can be found in RCC_LL_EC_RIF_LOCALRES
  * @param  LocalResAttributes Value set by an "OR" operation between :
  *         - one or none Lock configuration argument
  *           @arg RCC_LOCALRES_LOCKED
  *         - one or none Security filtering argument
  *           @arg RCC_LOCALRES_SEC
  *           @arg RCC_LOCALRES_NOSEC
  *         - one or none Privilege filtering argument
  *           @arg RCC_LOCALRES_PRIV
  *           @arg RCC_LOCALRES_NOPRIV
  *         - none or one Static CID filtering argument among
  *           @arg RCC_LOCALRES_CID_STATIC_0
  *           @arg RCC_LOCALRES_CID_STATIC_1
  *           @arg RCC_LOCALRES_CID_STATIC_2
  *           @arg RCC_LOCALRES_CID_STATIC_3
  *           @arg RCC_LOCALRES_CID_STATIC_4
  *           @arg RCC_LOCALRES_CID_STATIC_5
  *           @arg RCC_LOCALRES_CID_STATIC_6
  *           @arg RCC_LOCALRES_CID_STATIC_7
  *           or else a constant Dynamic CID filtering argument among
  *           @arg RCC_LOCALRES_CID_DYNAMIC_NONE
  *           @arg RCC_LOCALRES_CID_DYNAMIC_ALL
  *           or else an "OR" combination of Dynamic CID filtering arguments among
  *           @arg RCC_LOCALRES_CID_DYNAMIC_0
  *           @arg RCC_LOCALRES_CID_DYNAMIC_1
  *           @arg RCC_LOCALRES_CID_DYNAMIC_2
  *           @arg RCC_LOCALRES_CID_DYNAMIC_3
  *           @arg RCC_LOCALRES_CID_DYNAMIC_4
  *           @arg RCC_LOCALRES_CID_DYNAMIC_5
  *           @arg RCC_LOCALRES_CID_DYNAMIC_6
  *           @arg RCC_LOCALRES_CID_DYNAMIC_7
  *
  * @note If Lock configuration argument is not provided,
  *       Security/Privilege/CID filtering configuration is not locked.
  *       If Security filtering configuration argument is not provided,
  *       no security filtering configuration is applied.
  *       If Privilege filtering configuration argument is not provided,
  *       no privilege filtering configuration is applied.
  *       If neither static CID filtering argument,
  *       nor dynamic CID filtering argument is provided,
  *       CID filtering is disabled.
  * @retval HAL Status in {HAL_OK; HAL_ERROR}.
  */
HAL_StatusTypeDef HAL_RCC_ConfigAttributes(uint32_t LocalResIndex, uint32_t LocalResAttributes)
{
  /* Initialize HAL status */
  HAL_StatusTypeDef hal_status = HAL_BUSY;

  /* Split LOCK/PRIV/SEC/CID attributes */
  uint32_t priv_attr = LocalResAttributes & RCC_LOCALRES_ATTR_PRIV_MSK;
  uint32_t lock_attr = LocalResAttributes & RCC_LOCALRES_ATTR_LOCK_MSK;
  uint32_t sec_attr  = LocalResAttributes & RCC_LOCALRES_ATTR_SEC_MSK;
  uint32_t cid_attr  = LocalResAttributes & (RCC_LOCALRES_ATTR_CID_TYPE_MSK |
                                             RCC_LOCALRES_ATTR_STATIC_CID_MSK |
                                             RCC_LOCALRES_ATTR_DYNAMIC_CID_MSK);

  /* Check input parameters : */
  /* - valid range of LocalResIndex */
  assert_param(IS_LOCALRES_INDEX(LocalResIndex));
  /* - valid value of PRIV attribute */
  assert_param(IS_PRIV_ATTRIBUTE(priv_attr));
  /* - valid value of LOCK attribute */
  assert_param(IS_LOCK_ATTRIBUTE(lock_attr));
  /* - valid value of SEC attribute */
  assert_param(IS_SEC_ATTRIBUTE(sec_attr));
  /* - valid values of CID type, Static CID and Dynamic CID attributes */
  assert_param(IS_CID_ATTRIBUTE(cid_attr));

  /* Take into account that TDCID is allowed to set any configuration */
  /* that is to say modifying security and privilege filtering */
  /* even if current CID filtering prevents to do it. */
#if defined(CORE_CA35)
  LL_RCC_SetLocalResSCid(LocalResIndex, RCC_LOCALRES_CID_STATIC_1);
#endif /* CORE_CA35 */
#if defined(CORE_CM33)
  LL_RCC_SetLocalResSCid(LocalResIndex, RCC_LOCALRES_CID_STATIC_2);
#endif /* CORE_CM33 */

  /* Manage PRIV filtering attribute */
  if (priv_attr == RCC_LOCALRES_PRIV)
  {
    LL_RCC_EnableLocalResPrivilege(LocalResIndex);
  }
  else if (priv_attr == RCC_LOCALRES_NOPRIV)
  {
    LL_RCC_DisableLocalResPrivilege(LocalResIndex);
  }

  /* Manage SEC filtering attribute */
  if (sec_attr == RCC_LOCALRES_SEC)
  {
    LL_RCC_EnableLocalResSecure(LocalResIndex);
  }
  else if (sec_attr == RCC_LOCALRES_NOSEC)
  {
    LL_RCC_DisableLocalResSecure(LocalResIndex);
  }
  /* Manage CID filtering attributes */
  switch (cid_attr & RCC_LOCALRES_ATTR_CID_TYPE_MSK)
  {
    case RCC_LOCALRES_CID_TYPE_STATIC:
      LL_RCC_SetLocalResSCid(LocalResIndex, cid_attr);
      break;
    case RCC_LOCALRES_CID_TYPE_DYNAMIC:
      LL_RCC_SetLocalResWLCid(LocalResIndex, cid_attr);
      break;
    case RCC_LOCALRES_CID_TYPE_NONE:
      LL_RCC_SetLocalResNoCid(LocalResIndex);
      break;
    default :
      hal_status = HAL_ERROR;
      break;
  }
  /* Manage LOCK configuration attribute */
  if (lock_attr == RCC_LOCALRES_LOCKED)
  {
    LL_RCC_LockLocalResConfig(LocalResIndex);
  }

  /* return HAL status */
  if (hal_status == HAL_BUSY)
  {
    hal_status = HAL_OK;
  }
  return hal_status;
}
#endif /* defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Get Security/Privilege/CID Access Filtering configuration of one RCC Local Resource
  * @param  LocalResIndex Value can be 0 - 113 and ref can be found in RCC_LL_EC_RIF_LOCALRES
  * @param  pLocalResAttributes Returned value composed of following bitfield :
  *         . bits [31:24] Locked configuration state
  *         . bits [23:16] CID whitelist (dynamic CIDs list)
  *         . bits [15:12] Security filtering state
  *         . bits [11:8]  Privilege filtering state
  *         . bit  7       Reserved
  *         . bits [6:4]   Static CID
  *         . bits [3:2]   Reserved
  *         . bits [1:0]   CID filtering type
  *         to be compared with following reference values
  *         - linked to Lock configuration state
  *           @arg RCC_LOCALRES_LOCKED
  *         - linked to Security filtering state
  *           @arg RCC_LOCALRES_SEC
  *           @arg RCC_LOCALRES_NOSEC
  *         - linked to Privilege filtering state
  *           @arg RCC_LOCALRES_PRIV
  *           @arg RCC_LOCALRES_NOPRIV
  *         - linked to Static CID filtering configuration
  *           @arg RCC_LOCALRES_CID_STATIC_0
  *           @arg RCC_LOCALRES_CID_STATIC_1
  *           @arg RCC_LOCALRES_CID_STATIC_2
  *           @arg RCC_LOCALRES_CID_STATIC_3
  *           @arg RCC_LOCALRES_CID_STATIC_4
  *           @arg RCC_LOCALRES_CID_STATIC_5
  *           @arg RCC_LOCALRES_CID_STATIC_6
  *           @arg RCC_LOCALRES_CID_STATIC_7
  *         - linked to Dynamic CID filtering configuration
  *           @arg RCC_LOCALRES_CID_DYNAMIC_NONE
  *           @arg RCC_LOCALRES_CID_DYNAMIC_ALL
  *           @arg RCC_LOCALRES_CID_DYNAMIC_0
  *           @arg RCC_LOCALRES_CID_DYNAMIC_1
  *           @arg RCC_LOCALRES_CID_DYNAMIC_2
  *           @arg RCC_LOCALRES_CID_DYNAMIC_3
  *           @arg RCC_LOCALRES_CID_DYNAMIC_4
  *           @arg RCC_LOCALRES_CID_DYNAMIC_5
  *           @arg RCC_LOCALRES_CID_DYNAMIC_6
  *           @arg RCC_LOCALRES_CID_DYNAMIC_7
  * @retval HAL Status in {HAL_OK; HAL_ERROR}.
  */
HAL_StatusTypeDef HAL_RCC_GetConfigAttributes(uint32_t LocalResIndex, uint32_t *pLocalResAttributes)
{
  uint32_t local_res_attr;

  /* Initialize HAL status */
  HAL_StatusTypeDef hal_status = HAL_BUSY;

  /* Check input parameters : */
  /* - not-null pointer for pLocalResAttributes */
  if (pLocalResAttributes == NULL)
  {
    return HAL_ERROR;
  }
  /* - valid range of LocalResIndex */
  assert_param(IS_LOCALRES_INDEX(LocalResIndex));

  /* Initialize attributes value to None */
  local_res_attr = RCC_LOCALRES_ATTR_NONE;
  /* and LocalResAttributes value to Invalid */
  *pLocalResAttributes = RCC_LOCALRES_ATTR_INVALID;

  /* Get local resource lock state */
  if (LL_RCC_IsLockedLocalResConfig(LocalResIndex) == 1U)
  {
    /* to set lock configuration attribute accordingly */
    local_res_attr |= RCC_LOCALRES_LOCKED;
  }

  /* Get local resource security filtering state */
  if (LL_RCC_IsEnabledLocalResSecure(LocalResIndex) == 1U)
  {
    /* to set security filtering attribute accordingly */
    local_res_attr |= RCC_LOCALRES_SEC;
  }
  else
  {
    local_res_attr |= RCC_LOCALRES_NOSEC;
  }

  /* Get local resource privilege filtering state */
  if (LL_RCC_IsEnabledLocalResPrivilege(LocalResIndex) == 1U)
  {
    /* to set privilege filtering attribute accordingly */
    local_res_attr |= RCC_LOCALRES_PRIV;
  }
  else
  {
    local_res_attr |= RCC_LOCALRES_NOPRIV;
  }

  /* Get local resource CID filtering settings */
  /* to set None/Static/Dynamic CID filtering attributes accordingly */
  local_res_attr |= LL_RCC_GetLocalResCid(LocalResIndex);

  /* Output LocalResAttributes value */
  *pLocalResAttributes = local_res_attr;

  /* return HAL status */
  if (hal_status == HAL_BUSY)
  {
    hal_status = HAL_OK;
  }
  return hal_status;
}

/**
  * @brief  Take semaphore to access RCC Local Resource.
  *         Check semaphore has been effectively taken.
  * @param  LocalResIndex Value can be 0 - 113 and ref can be found in RCC_LL_EC_RIF_LOCALRES
  * @note   If operation fails, return error status.
  * @retval HAL Status in {HAL_OK; HAL_ERROR}.
  */
HAL_StatusTypeDef HAL_RCC_TakeLocalResSemaphore(uint32_t LocalResIndex)
{
  /* Initialize HAL status */
  HAL_StatusTypeDef hal_status = HAL_BUSY;

  /* Check input parameter : LocalResIndex in valid range */
  assert_param(IS_LOCALRES_INDEX(LocalResIndex));

  /* For local resource : */
  /* - check semaphore initial state */
  /*   and set output status accordingly */
  if ((LL_RCC_GetLocalResSem(LocalResIndex) & RCC_RxSEMCR_SEM_MUTEX) == RCC_RxSEMCR_SEM_MUTEX)
  {
    /*   <=> if already taken, then output error status */
    return HAL_ERROR;
  }
  /* - take semaphore */
  LL_RCC_TakeLocalResSem(LocalResIndex);
  /* - once mutex has been updated in target register, */
  (void)WAIT_MUTEX_WRITTEN_IN_RCC_RxSEMCR(LocalResIndex);
  /*   check semaphore has been taken */
  /*   and set output status accordingly */
  /*   <=> if semaphore has not been taken by : */
  /*       - CID1 in A35 case, */
#if defined(CORE_CA35)
  if (LL_RCC_GetLocalResSem(LocalResIndex) != RCC_LOCALRES_TAKEN_SEMCID1)
#endif /* CORE_CA35 */
    /*       - CID2 in M33 case, */
#if defined(CORE_CM33)
    if (LL_RCC_GetLocalResSem(LocalResIndex) != RCC_LOCALRES_TAKEN_SEMCID2)
#endif /* CORE_CM33 */
    {
      /*       then output error status */
      return HAL_ERROR;
    }
  /* return HAL status */
  if (hal_status == HAL_BUSY)
  {
    hal_status = HAL_OK;
  }
  return hal_status;
}

/**
  * @brief  Release semaphore used to access RCC Local Resource.
  *         Check semaphore has been effectively released.
  * @param  LocalResIndex Value can be 0 - 113 and ref can be found in RCC_LL_EC_RIF_LOCALRES
  * @note   If operation fails, return error status.
  * @retval HAL Status in {HAL_OK; HAL_ERROR}.
  */
HAL_StatusTypeDef HAL_RCC_ReleaseLocalResSemaphore(uint32_t LocalResIndex)
{
  /* Initialize HAL status */
  HAL_StatusTypeDef hal_status = HAL_BUSY;

  /* Check input parameter : LocalResIndex in valid range */
  assert_param(IS_LOCALRES_INDEX(LocalResIndex));

  /* For local resource : */
  /* - check semaphore initial state */
  /*   and set output status accordingly */
  /*   <=> if semaphore has not been taken by : */
  /*       - CID1 in A35 case, */
#if defined(CORE_CA35)
  if (LL_RCC_GetLocalResSem(LocalResIndex) != RCC_LOCALRES_TAKEN_SEMCID1)
#endif /* defined(CORE_CA35) */
    /*       - CID2 in M33 case, */
#if defined(CORE_CM33)
    if (LL_RCC_GetLocalResSem(LocalResIndex) != RCC_LOCALRES_TAKEN_SEMCID2)
#endif /* defined(CORE_CM33) */
    {
      /*       then output error status */
      return HAL_ERROR;
    }
  /* - release semaphore */
  LL_RCC_ReleaseLocalResSem(LocalResIndex);
  /* - once mutex has been updated in target register, */
  (void)WAIT_MUTEX_WRITTEN_IN_RCC_RxSEMCR(LocalResIndex);
  /*   check semaphore has been released */
  /*   and set output status accordingly */
  /*   <=> if semaphore has not been released by : */
  /*       - CID1 in A35 case, */
#if defined(CORE_CA35)
  if (LL_RCC_GetLocalResSem(LocalResIndex) != RCC_LOCALRES_RELEASED_SEMCID1)
#endif /* CORE_CA35 */
    /*       - CID2 in M33 case, */
#if defined(CORE_CM33)
    if (LL_RCC_GetLocalResSem(LocalResIndex) != RCC_LOCALRES_RELEASED_SEMCID2)
#endif /* CORE_CM33 */
    {
      /*       then output error status */
      return HAL_ERROR;
    }
  /* return HAL status */
  if (hal_status == HAL_BUSY)
  {
    hal_status = HAL_OK;
  }
  return hal_status;
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
/**
  * @}
  */
#endif /* HAL_RCC_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

