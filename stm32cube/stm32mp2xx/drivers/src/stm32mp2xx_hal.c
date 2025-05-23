/**
  ******************************************************************************
  * @file    stm32mp2xx_hal.c
  * @author  MCD Application Team
  * @brief   HAL module driver.
  *          This is the common part of the HAL initialization
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The common HAL driver contains a set of generic and common APIs that can be
    used by the PPP peripheral drivers and the user to start using the HAL.
    [..]
    The HAL contains two APIs' categories:
         (+) Common HAL APIs
         (+) Services HAL APIs

  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @defgroup HAL  HAL
  * @brief HAL module driver.
  * @{
  */
#ifdef HAL_MODULE_ENABLED
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup HAL_Private_Defines HAL Private Defines
  * @{
  */
/**
  * @brief STM32MP2xx HAL Driver version number
   */
#define __STM32MP2xx_HAL_VERSION_MAIN   (0x01UL) /*!< [31:24] main version */
#define __STM32MP2xx_HAL_VERSION_SUB1   (0x00UL) /*!< [23:16] sub1 version */
#define __STM32MP2xx_HAL_VERSION_SUB2   (0x00UL) /*!< [15:8]  sub2 version */
#define __STM32MP2xx_HAL_VERSION_RC     (0x00UL) /*!< [7:0]  release candidate */
#define __STM32MP2xx_HAL_VERSION         ((__STM32MP2xx_HAL_VERSION_MAIN << 24)\
                                          |(__STM32MP2xx_HAL_VERSION_SUB1 << 16)\
                                          |(__STM32MP2xx_HAL_VERSION_SUB2 << 8 )\
                                          |(__STM32MP2xx_HAL_VERSION_RC))

#define IDCODE_DEVID_MASK    ((uint32_t)0x00000FFF)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/** @defgroup HAL_Exported_Variables HAL Exported Variables
  * @{
  */
static __IO uint32_t uwTick;
/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
/** @defgroup HAL_Exported_Functions  HAL Exported Functions
  * @{
  */

/** @defgroup HAL_Exported_Functions_Group1 Initialization and de-initialization Functions
  *  @brief    Initialization and de-initialization functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initializes the Flash interface the NVIC allocation and initial clock
          configuration. It initializes the systick also when timeout is needed
          and the backup domain when enabled.
      (+) de-Initializes common part of the HAL
      (+) Configure The time base source to have 1ms time base with a dedicated
          Tick interrupt priority.
        (++) Systick timer is used by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
        (++) Time base configuration function (HAL_InitTick ()) is called automatically
             at the beginning of the program after reset by HAL_Init() or at any time
             when clock is configured, by HAL_RCC_ClockConfig().
        (++) Source of time base is configured  to generate interrupts at regular
             time intervals. Care must be taken if HAL_Delay() is called from a
             peripheral ISR process, the Tick interrupt line must have higher priority
            (numerically lower) than the peripheral interrupt. Otherwise the caller
            ISR process will be blocked.
       (++) functions affecting time base configurations are declared as __weak
             to make  override possible  in case of other  implementations in user file.
@endverbatim
  * @{
  */

/**
  * @brief  This function is used to initialize the HAL Library; it must be the first
  *         instruction to be executed in the main program (before to call any other
  *         HAL function), it performs the following:
  *           Configures the SysTick to generate an interrupt each 1 millisecond,
  *           which is clocked by the HSI (at this stage, the clock is not yet
  *           configured and thus the system is running from the internal HSI at 16 MHz).
  *           Set NVIC Group Priority to 4.
  *           Calls the HAL_MspInit() callback function defined in user file
  *           "stm32mp1xx_hal_msp.c" to do the global low level hardware initialization
  *
  * @note   SysTick is used as time base for the HAL_Delay() function, the application
  *         need to ensure that the SysTick time base is always set to 1 millisecond
  *         to have correct HAL operation.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_Init(void)
{
  /* Configure Flash prefetch, Instruction cache, Data cache */
#if (INSTRUCTION_CACHE_ENABLE != 0)
  /* __HAL_FLASH_INSTRUCTION_CACHE_ENABLE(); */
#endif /* INSTRUCTION_CACHE_ENABLE */

#if (DATA_CACHE_ENABLE != 0)
  /* __HAL_FLASH_DATA_CACHE_ENABLE(); */
#endif /* DATA_CACHE_ENABLE */

#if (PREFETCH_ENABLE != 0)
  /* __HAL_FLASH_PREFETCH_BUFFER_ENABLE(); */
#endif /* PREFETCH_ENABLE */

  /* Set Interrupt Group Priority */
#if defined (CORE_CM33)
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
#endif /* CORE_CM33 */
  /* Use systick as time base source and configure 1ms tick (default clock after Reset is HSI) */
  (void)HAL_InitTick(TICK_INT_PRIORITY);

  /* Init the low level hardware */
  HAL_MspInit();

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  This function de-Initializes common part of the HAL and stops the systick.
  *         This function is optional.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DeInit(void)
{
  /* Reset of all peripherals */


  /* De-Init the low level hardware */
  HAL_MspDeInit();

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the MSP.
  * @retval None
  */
__weak void HAL_MspInit(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitializes the MSP.
  * @retval None
  */
__weak void HAL_MspDeInit(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_MspDeInit could be implemented in the user file
   */
}

/**
  * @brief This function configures the source of the time base.
  *        The time source is configured to have 1ms time base with a dedicated
  *        Tick interrupt priority.
  * @note This function is called  automatically at the beginning of program after
  *       reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig().
  * @note In the default implementation, SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals.
  *       Care must be taken if HAL_Delay() is called from a peripheral ISR process,
  *       The SysTick interrupt must have higher priority (numerically lower)
  *       than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  *       The function is declared as __weak to be overwritten in case of other
  *       implementation in user file.
  * @param TickPriority: SysTick interrupt priority.
  * @retval HAL status
  */
/*
 * !!!!!!!!!!!!!!
 * Modifying this function will not be fully acceptable without additional explanations from arch/design
 * team about M0+/M33 SysTicks source clock setting/selection
 * So implementing a temporary version which is correct enough for current verification work
 * !!!!!!!!!!!!!!
 */
__weak HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  /* Configure the SysTick to have interrupt in 1ms timebase */
#if defined (CORE_CA35)
  /* In Cortex-A35 case, configure Secure/Non-secure Physical Timer */
  /* to be a System Tick generator at 1 ms : */
  /* when A35 is in secure state */
#if !defined(A35_NON_SECURE)
  /* - by starting its source clock aka Secure Timestamp Generator (STGEN)*/
  /*   clocked itself by cl_ker_stgen managed by RCC */
  SystemA35_TZ_STGEN_Start(HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_STGEN));
  /* Note : when A35 is in non-secure state at EL1, */
  /*        EL3 monitor has already started Secure Timestamp Generator */
#endif /* !defined(A35_NON_SECURE) */
  /* - by configuring Secure/Non-secure Physical Timer interrupt accordingly */
  /*   Warning ! TickPriority value shall be compliant with GIC400 Priority */
  /*             Dynamics (see #3.3 in [ARM IHI0048B]). It shall be in range */
  /*             [0;(1<<GIC_PRIO_BITS)-1] and be set according to secure state. */
  SystemA35_SYSTICK_Config(TickPriority);

#elif defined (CORE_CM33)
  /* In Cortex-M33 case, configure SysTick period according to platform frequency */
  /* Should be configured using M33 specifications to set SysTick
   * !!!!!!!!!!!!!!
   * period according to source clock settings
   * !!!!!!!!!!!!!!
   */
#if defined (USE_STM32MP257CXX_EMU)
  HAL_SYSTICK_Config(HSI_VALUE / 1000);
  /* HAL_SYSTICK_Config(HAL_RCC_GetFreq(RCC_CK_ICN_MCU)/1000); when HSI_VALUE will be fixed for UART and other usage */
#else
  /* M33 SysTick "Processor clock" is "ck_cpu2" aka "ck_icn_hs_mcu" */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  (void)HAL_SYSTICK_Config(HAL_RCC_GetFreq(RCC_CLOCKTYPE_ICN_HS_MCU) / 1000U);
#endif /* defined (USE_STM32MP257CXX_EMU) */

  /* Configure the SysTick IRQ priority */
  HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority, 0);
#elif defined(CORE_CM0PLUS)
  /* In Cortex-M0+ case, configure SysTick period according to platform frequency */
  /* !!!!!!!!!!!!!!
   * RCC specifications (RM0457 rev0.2 #22.8.32 pages 1876-1879) cannot be applied
   * because RCC registers are not visible by M0+ core.
   * According to these specifications, source clock for CPU3 SysTick timer clock can be :
   * - "Processor" clock, aka "ck_cpu3h, ck_cpu3s, ck_cpu3d" derived from ck_icn_ls_mcu
   *   with divider set to 2 (when RCC_LSMCUDIV value set to 0x80000001)
   *   at 200 MHz (see page 69) on SoC
   *   with divider set to 1 (when RCC_LSMCUDIV set to its default value 0x80000000)
   *   at  32 / 1 =  32 MHz on FPGA platform
   *   at 300 / 1 = 300 MHz on Emulation platform
   * - "External" clock, LSI (default) or LSE clock according to RCC_BDCR
   *   bit 25 "C3SYSTICKSEL" (see page 1877).
   * !!!!!!!!!!!!!!
   */
  /* Since "Processor" clock is default source clock set by HAL_SYSTICK_Config(),
   * then use HSI frequency value on FPGA/EMU platforms */
#if defined (USE_STM32MP257CXX_EMU) || defined (USE_STM32MP257CXX_FPGA)
  HAL_SYSTICK_Config(HSI_VALUE / 1000);
#else
  HAL_SYSTICK_Config(200000);
#endif /* defined (USE_STM32MP257CXX_EMU) || defined (USE_STM32MP257CXX_FPGA) */
  /* Note that in LSI/LSE "External" clock cases, HAL_SYSTICK_Config parameter
   * value shall be taken from TEN_MS (aka "ONE_MS" on MP2) bit field in M0+
   * system register SYST_CALIB.
   */

  /* Configure the SysTick IRQ priority */
  HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority, 0);
#else
#error "No core selected. Please define either CORE_CA35, CORE_CM33 or CORE_CM0PLUS"
#endif /* defined (CORE_CA35) || defined (CORE_CM33) || defined(CORE_CM0PLUS) */
  /* Return function status */
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group2 HAL Control functions
  *  @brief    HAL Control functions
  *
@verbatim
 ===============================================================================
                      ##### HAL Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Provide a tick value in millisecond
      (+) Provide a blocking delay in millisecond
      (+) Suspend the time base source interrupt
      (+) Resume the time base source interrupt
      (+) Get the HAL API driver version
      (+) Get the device identifier
      (+) Get the device revision identifier

@endverbatim
  * @{
  */

/**
  * @brief This function is called to increment  a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in Systick ISR.
  * @note This function is declared as __weak to be overwritten in case of other
  *      implementations in user file.
  * @retval None
  */
__weak void HAL_IncTick(void)
{
  uwTick++;
}

/**
  * @brief Provides a tick value in millisecond.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
__weak uint32_t HAL_GetTick(void)
{
  return uwTick;
}

/**
  * @brief This function provides accurate delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note ThiS function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay: specifies the delay time length, in milliseconds.
  * @retval None
  */
__weak void HAL_Delay(__IO uint32_t Delay)
{
  const uint32_t tickstart = HAL_GetTick();
  while ((HAL_GetTick() - tickstart) < Delay)
  {
  }
}

/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
  *       is called, the SysTick interrupt will be disabled and so Tick increment
  *       is suspended.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval None
  */
__weak void HAL_SuspendTick(void)
{
#if defined (CORE_CA35)
  /* Disable A35 SysTick Interrupt */
  /* according to its timer source (PPI27, PPI29 or PPI30) */
  SystemA35_ManageTick(A35_SUSPEND_SYSTICK);
#else /* M33 or M0PLUS */
  /* Disable Cortex-M SysTick Interrupt */
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
#endif /* CORE_CA35 */
}

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the the SysTick interrupt will be enabled and so Tick increment
  *       is resumed.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval None
  */
__weak void HAL_ResumeTick(void)
{
#if defined (CORE_CA35)
  /* Enable A35 SysTick Interrupt */
  /* according to its timer source (PPI27, PPI29 or PPI30) */
  SystemA35_ManageTick(A35_RESUME_SYSTICK);
#else /* M33 or M0PLUS */
  /* Enable SysTick Interrupt */
  SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
#endif /* CORE_CA35 */
}

/**
  * @brief  Returns the HAL revision
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t HAL_GetHalVersion(void)
{
  return __STM32MP2xx_HAL_VERSION;
}

#if defined(CORE_CA35) || defined(CORE_CM33)
/**
  * @brief  Returns the device revision identifier.
  * @retval Device revision identifier
  */
uint32_t HAL_GetREVID(void)
{
  return (DEVICE_REVISION());
}

/**
  * @brief  Returns the device identifier.
  * @retval Device identifier
  */
uint32_t HAL_GetDEVID(void)
{
  return (DEVICE_ID());
}

/**
  * @brief  Return the first word of the unique device identifier (UID based on 96 bits)
  * @retval Device identifier
  */
uint32_t HAL_GetUIDw0(void)
{
  return (READ_REG(*((uint32_t *)UID_BASE)));
}

/**
  * @brief  Return the second word of the unique device identifier (UID based on 96 bits)
  * @retval Device identifier
  */
uint32_t HAL_GetUIDw1(void)
{
  return (READ_REG(*((uint32_t *)(UID_BASE + 4U))));
}

/**
  * @brief  Return the third word of the unique device identifier (UID based on 96 bits)
  * @retval Device identifier
  */
uint32_t HAL_GetUIDw2(void)
{
  return (READ_REG(*((uint32_t *)(UID_BASE + 8U))));
}

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group3 DBGMCU Peripheral Control functions
  *
  * @{
  */

/**
  * @brief  If Secure debug is enabled, Freeze IWDG1 only if both CA35 Cores are halted
  * @retval None
  */
void HAL_DBGMCU_EnableWatchdogTimer2CA35Freeze(void)
{
  SET_BIT(DBGMCU->CRA35, DBGMCU_CRA35_WDFZCTL);
}

/**
  * @brief  If Secure debug is enabled, Freeze IWDG1 if either CA35 Cores is halted
  * @retval None
  */
void HAL_DBGMCU_DisableWatchdogTimer2CA35Freeze(void)
{
  CLEAR_BIT(DBGMCU->CRA35, DBGMCU_CRA35_WDFZCTL);
}

/**
  * @brief  Enable the Debug Module during SLEEP mode
  * @retval None
  */
void HAL_DBGMCU_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the Debug Module during SLEEP mode
  * @retval None
  */
void HAL_DBGMCU_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @retval None
  */
void HAL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @retval None
  */
void HAL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during STANDBY mode
  * @retval None
  */
void HAL_DBGMCU_EnableDBGStandbyMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the Debug Module during STANDBY mode
  * @retval None
  */
void HAL_DBGMCU_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group4 HDP Peripheral Control functions
  *
  * @{
  */

/**
  * @brief  Enable the HDP[7:0] output
  * @note   Valid if HDP also enabled in BSEC
  * @retval None
  */
void HAL_HDP_EnableHDP(void)
{
  SET_BIT(HDP->CTRL, HDP_CTRL_EN);
}

/**
  * @brief  Disable the HDP[7:0] output.
  * @retval None
  */
void HAL_HDP_DisableHDP(void)
{
  CLEAR_BIT(HDP->CTRL, HDP_CTRL_EN);
}

/**
  * @brief  Select the output among the 16 available signals for each mux
  * @param  HDP_Mux This value is one of @ref HDP_Mux
  * @param  HDP_Signal This value is one of @ref HDP_Signal
  * @retval None
  */
void HAL_HDP_ConfigHDPMux(uint32_t HDP_Mux, uint32_t HDP_Signal)
{
  MODIFY_REG(HDP->MUX, HDP_Mux, HDP_Signal);
}

/**
  * @brief  Return the output of VAL register
  * @retval Value of VAL register
  */
uint32_t HAL_HDP_ReadVAL(void)
{
  return ((HDP->VAL) & (HDP_VAL_HDPVAL));
}
/**
  * @}
  */


/** @defgroup HAL_Exported_Functions_Group5 SYSCFG Peripheral Control functions
  *
  * @{
  */


/**
  * @brief  Ethernet PHY Interface Selection either MII, RMII or RGMII
  * @param  SYSCFG_ETHInterface: Selects the Ethernet 1 PHY interface
  *   This parameter can be one of the following values:
  *   @arg SYSCFG_ETH_MII : Select the Media Independent Interface
  *   @arg SYSCFG_ETH_RGMII : Select the reduced gigabit media-independent interface
  *   @arg SYSCFG_ETH_RMII: Select the Reduced Media Independent Interface
  * @retval None
  */
void HAL_SYSCFG_ETH1InterfaceSelect(uint32_t SYSCFG_ETHInterface)
{
  assert_param(IS_SYSCFG_ETHERNET_CONFIG(SYSCFG_ETHInterface));

  MODIFY_REG(SYSCFG->ETH1CR, SYSCFG_ETH1CR_ETH1_SEL, (uint32_t)(SYSCFG_ETHInterface));
}

/**
  * @brief  Ethernet PHY Interface Selection either MII, RMII or RGMII
  * @param  SYSCFG_ETHInterface: Selects the Ethernet 2 PHY interface
  *   This parameter can be one of the following values:
  *   @arg SYSCFG_ETH_MII : Select the Media Independent Interface
  *   @arg SYSCFG_ETH_RGMII : Select the reduced gigabit media-independent interface
  *   @arg SYSCFG_ETH_RMII: Select the Reduced Media Independent Interface
  * @retval None
  */
void HAL_SYSCFG_ETH2InterfaceSelect(uint32_t SYSCFG_ETHInterface)
{
  assert_param(IS_SYSCFG_ETHERNET_CONFIG(SYSCFG_ETHInterface));

  MODIFY_REG(SYSCFG->ETH2CR, SYSCFG_ETH2CR_ETH2_SEL, (uint32_t)(SYSCFG_ETHInterface));
}

/**
  * @brief  Ethernet RGMII 125 MHz Clock Selection
  * @param  SYSCFG_ETHClock: Selects the RGMII Ethernet Clock
  *   This parameter can be one of the following values:
  *   @arg SYSCFG_ETH_EXT_CLK : Select the External Clock
  *   @arg SYSCFG_ETH_RCC_CLK : Select the RCC Internal Clock
  * @retval None
  */
void HAL_SYSCFG_ETH1ClockSelect(uint32_t SYSCFG_ETHClock)
{
  assert_param(IS_SYSCFG_ETHERNET_CLOCK_CONFIG(SYSCFG_ETHClock));

  MODIFY_REG(SYSCFG->ETH1CR, SYSCFG_ETH1CR_ETH1_CLK_SEL, (uint32_t)(SYSCFG_ETHClock));
}

/**
  * @brief  Ethernet RGMII 125 MHz Clock Selection
  * @param  SYSCFG_ETHClock: Selects the RGMII Ethernet Clock
  *   This parameter can be one of the following values:
  *   @arg SYSCFG_ETH_EXT_CLK : Select the External Clock
  *   @arg SYSCFG_ETH_RCC_CLK : Select the RCC Internal Clock
  * @retval None
  */
void HAL_SYSCFG_ETH2ClockSelect(uint32_t SYSCFG_ETHClock)
{
  assert_param(IS_SYSCFG_ETHERNET_CLOCK_CONFIG(SYSCFG_ETHClock));

  MODIFY_REG(SYSCFG->ETH2CR, SYSCFG_ETH2CR_ETH2_CLK_SEL, (uint32_t)(SYSCFG_ETHClock));
}


/**
  * @brief  Analog Switch control for analog connections.
  * @param  SYSCFG_AnalogSwitch: Selects the analog pad
  *   This parameter can be one or a combination of the following values:
  *   @arg SYSCFG_SWITCH_PA0 : Select PA0 analog switch
  *   @arg SYSCFG_SWITCH_PA1:  Select PA1 analog switch
  * @param  SYSCFG_SwitchState: Open or Close the analog switch between pads
  *   This parameter can be one or a combination of the following values:
  *   @arg SYSCFG_SWITCH_PA0_OPEN
  *   @arg SYSCFG_SWITCH_PA0_CLOSE
  *   @arg SYSCFG_SWITCH_PA1_OPEN
  *   @arg SYSCFG_SWITCH_PA1_CLOSE
  * @retval None
  */
#if defined(SYSCFG_IOCR_HSLVEN_TRACE)
void HAL_SYSCFG_AnalogSwitchConfig(uint32_t SYSCFG_AnalogSwitch, uint32_t SYSCFG_SwitchState)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_SWITCH_STATE(SYSCFG_SwitchState));
  assert_param(IS_SYSCFG_ANALOG_SWITCH(SYSCFG_AnalogSwitch));
  if ((SYSCFG_AnalogSwitch & SYSCFG_SWITCH_PA0) == SYSCFG_SWITCH_PA0)
  {
    MODIFY_REG(SYSCFG->IOCR, SYSCFG_IOCR_ANA0_SEL, (uint32_t)(SYSCFG_SwitchState));
  }
  if ((SYSCFG_AnalogSwitch & SYSCFG_SWITCH_PA1) == SYSCFG_SWITCH_PA1)
  {
    MODIFY_REG(SYSCFG->IOCR, SYSCFG_IOCR_ANA1_SEL, (uint32_t)(SYSCFG_SwitchState));
  }
}

/**
  * @brief  To Enable optimize the I/O speed when the product voltage is low.
  * @note   This bit is active only if PRODUCT_BELOW_25V user option bit is set. It must be
  *         used only if the product supply voltage is below 2.5 V. Setting this bit when VDD is
  *         higher than 2.5 V might be destructive.
  * @param  SYSCFG_HighSpeedSignal: Signal selection (TRACE, OCTOSPI...)
  *   This parameter can be one or a combination of the following values:
  *   @arg SYSCFG_HIGHSPEED_TRACE_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_LCD_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_OCTOSPIM_P1_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_OCTOSPIM_P2_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_ETH1_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_ETH2_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_ETH3_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SDMMC3_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI1_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI2_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI3_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI4_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI5_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI6_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI7_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI8_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_DCMI_PSSI_DCMIPP_SIGNAL
  * @retval None
  */
void HAL_SYSCFG_EnableIOSpeedOptimize(uint32_t SYSCFG_HighSpeedSignal)
{
  SET_BIT(SYSCFG->IOCR, SYSCFG_HighSpeedSignal) ;
}

/**
  * @brief  To Disable optimize the I/O speed when the product voltage is low.
  * @note   This bit is active only if PRODUCT_BELOW_25V user option bit is set. It must be
  *         used only if the product supply voltage is below 2.5 V. Setting this bit when VDD is
  *         higher than 2.5 V might be destructive.
  * @param  SYSCFG_HighSpeedSignal: Signal selection (TRACE, OCTOSPI...)
  *   This parameter can be one or a combination of the following values:
  *   @arg SYSCFG_HIGHSPEED_TRACE_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_LCD_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_OCTOSPIM_P1_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_OCTOSPIM_P2_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_ETH1_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_ETH2_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_ETH3_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SDMMC3_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI1_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI2_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI3_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI4_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI5_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI6_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI7_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_SPI8_SIGNAL
  *   @arg SYSCFG_HIGHSPEED_DCMI_PSSI_DCMIPP_SIGNAL
  * @retval None
  */
void HAL_SYSCFG_DisableIOSpeedOptimize(uint32_t SYSCFG_HighSpeedSignal)
{
  CLEAR_BIT(SYSCFG->IOCR, SYSCFG_HighSpeedSignal) ;
}
#endif /* SYSCFG_IOCR_HSLVEN_TRACE */

/**
  * @brief  Lock the SYSCFG item(s).
  * @note   Setting lock(s) depends on privilege mode in secure/non-secure code
  *         Lock(s) cleared only at system reset
  * @param  Item Item(s) to set lock on.
  * This parameter can be a combination of @ref SYSCFG_Lock_items
  *   @arg SYSCFG_SAU
  *   @arg SYSCFG_MPU_SEC
  *   @arg SYSCFG_MPU_NSEC
  *   @arg SYSCFG_VTOR_NSEC
  *   @arg SYSCFG_VTOR_AIRCR_SEC
  *   @arg SYSCFG_LOCK_ALL
  * @retval None
  */
void HAL_SYSCFG_Lock(uint32_t Item)
{
  assert_param(IS_SYSCFG_LOCK_SELECT(Item));
  MODIFY_REG(SYSCFG->M33SSCR, SYSCFG_LOCK_ALL, Item);
}

/**
  * @brief  Get the lock state of SYSCFG item.
  * @param  pItem pointer to return locked items
  * the return value can be a combination of @ref SYSCFG_Lock_items
  *   @arg SYSCFG_SAU
  *   @arg SYSCFG_MPU_SEC
  *   @arg SYSCFG_MPU_NSEC
  *   @arg SYSCFG_VTOR_NSEC
  *   @arg SYSCFG_VTOR_AIRCR_SEC
  *   @arg SYSCFG_LOCK_ALL
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SYSCFG_GetLock(uint32_t *pItem)
{
  uint32_t tmp_lock;

  /* Check null pointer */
  if (pItem == NULL)
  {
    return HAL_ERROR;
  }

  /* Get the non-secure lock state */
  tmp_lock = ((READ_REG(SYSCFG->M33SSCR) >> SYSCFG_M33SSCR_LOCKSVTAIRCR_Pos) & 0x3FUL);

  /* Return overall lock status */
  *pItem = tmp_lock;

  return HAL_OK;
}

/**
  * @}
  */

#endif /* CORE_CA35 || CORE_CM33 */

/**
  * @}
  */
#endif /* HAL_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
