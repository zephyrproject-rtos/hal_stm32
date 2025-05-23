/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_pwr.c
  * @author  MCD Application Team
  * @brief   PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
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
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver

  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup PWR_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup PWR_PVD_Mode_Mask PWR PVD Mode Mask
  * @{
  */


#define PWR_FLAG_SETTING_DELAY_US  1000U
/**
  * @}
  */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup PWR_Private_Macros PWR Private Macros
  * @brief    PWR Private Macros
  * @{
  */

#define WIO_CID_CFG_ADD_OFFSET 0x02u
#define R_CID_CFG_ADD_OFFSET   0x01u
#define WKUPCR_ADD_OFFSET      0x01u

/**
  * @}
  */

/* Private variable -------------------------------------------------------------*/
/** @addtogroup PWR_Private_Variables PWR Private Variables
  * @{
  */
#if !defined(CORE_CM0PLUS)
static uint32_t extiImr2WakeUp[] =
{
  __HAL_WKUP_LINE0_EXTI_MSK,
  __HAL_WKUP_LINE1_EXTI_MSK,
  __HAL_WKUP_LINE2_EXTI_MSK,
  __HAL_WKUP_LINE3_EXTI_MSK,
  __HAL_WKUP_LINE4_EXTI_MSK,
  __HAL_WKUP_LINE5_EXTI_MSK
};
#endif /* CORE_CM0PLUS */
/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Private_Functions PWR Private Functions
  * @{
  */
static void GateCortexSubsystemClockOnSleepEntry(void);
static void KeepCortexSubsystemClockOnSleepEntry(void);
static void ClearStandbyRequest();
#if !defined(CORE_CM0PLUS)
static void SetStandbyRequest(uint8_t STANDBYType);
#endif /* CORE_CM0PLUS */
static void SetRegulatorStopModeIndicator(uint32_t Regulator);
static void ClearRegulatorStopModeIndicator(void);
HAL_StatusTypeDef HAL_PWR_ConfigWioResourceAttributes(uint16_t Resource, uint32_t ResourceAttributes);
HAL_StatusTypeDef HAL_PWR_GetConfigWioResourceAttributes(uint16_t Resource, uint32_t *pResourceAttributes);
HAL_StatusTypeDef HAL_PWR_ConfigNonShareableResourceAttributes(uint16_t Resource, uint32_t ResourceAttributes);
HAL_StatusTypeDef HAL_PWR_GetConfigNonShareableResourceAttributes(uint16_t Resource, uint32_t *pResourceAttributes);

/** @defgroup PWR_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and de-initialization functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]
      After reset, the backup domain (RTC registers, RTC backup data
      registers and backup SRAM) is protected against possible unwanted
      write accesses.
      To enable access to the RTC Domain and RTC registers, proceed as follows:
        (+) Enable access to RTC domain using the HAL_PWR_EnableBkUpD3Access() function.

@endverbatim
  * @{
  */

#if !defined(CORE_CM0PLUS)
#if defined(PWR_BDCR1_DBD3P)
/**
  * @brief  Enables WRITE access to the backup and D3 domain
  *         In reset state, the RCC_BDCR, PWR_CR2, RTC, and backup registers are
  *         protected against parasitic write access. DBP bit must be set to enable
  *         write access to these.
  *         access write : Secure privilege needed + CID filtering
  * @retval None
  */
void HAL_PWR_EnableBkUpD3Access(void)
{
  SET_BIT(PWR->BDCR1, PWR_BDCR1_DBD3P);
}

/**
  * @brief  Disables WRITE access to the backup and D3 domain
  *         backup data registers and backup SRAM) and D3 domain .
  * @retval None
  */
void HAL_PWR_DisableBkUpD3Access(void)
{
  CLEAR_BIT(PWR->BDCR1, PWR_BDCR1_DBD3P);
}

#endif /* defined(PWR_BDCR1_DBD3P) */

#if defined(PWR_BDCR_DBP)
/**
  * @brief  Enables WRITE access to the backup domain
  *         access write : Secure privilege needed + CID filtering
  * @retval None
  */
void HAL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->BDCR, PWR_BDCR_DBP);
}
/**
  * @brief  Disables WRITE access to the backup domain
  *         access write : Secure privilege needed + CID filtering
  * @retval None
  */
void HAL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->BDCR, PWR_BDCR_DBP);
}
#endif /* defined(PWR_BDCR_DBP) */
#else
/**
  * @brief  Enables WRITE access to the backup domain
  *         Even if  D3 domain and backup domain are often open together (see HAL_PWR_EnableBkUpD3Access)
  *         In some very few cases, D3 can be on but backup off
  *         write access only by M0+
  * @retval None
  */
void HAL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->BDCR2, PWR_BDCR2_DBP);
}
/**
  * @brief  Disables WRITE access to the backup domain
  *         Write access only by M0+
  * @retval None
  */
void HAL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->BDCR2, PWR_BDCR2_DBP);
}

#endif /*!defined(CORE_CM0PLUS)*/
/**
  * @}
  */

/** @defgroup PWR_Group2 Peripheral Control functions
  *  @brief Low Power modes configuration functions
  *
@verbatim

 ===============================================================================
                 ##### Peripheral Control functions #####
 ===============================================================================

    *** PVD configuration ***
    =========================
    [..]
      (+) The PVD is used to monitor the VDD power supply by comparing it to a
          threshold selected by the PVD Level (PLS[2:0] bits in the PWR_CR).
      (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower
          than the PVD threshold. This event is internally connected to the EXTI
          line16 and can generate an interrupt if enabled. This is done through
          __HAL_PVD_EXTI_ENABLE_IT() macro.
      (+) The PVD is stopped in Standby mode.

    *** WakeUp pin configuration ***
    ================================
    [..]
      (+) WakeUp pin is used to wake up the system from Standby mode. This pin is
          forced in input pull-down configuration and is active on rising edges.
      (+) There is only one WakeUp pin: WakeUp Pin 1 on PA.00.

    *** Low Power modes configuration ***
    =====================================
    [..]
      The devices feature 3 low-power modes:
      (+) Sleep mode: Cortex core stopped, peripherals kept running.
      (+) Stop mode: all clocks are stopped, regulator running, regulator
          in low power mode
      (+) Standby mode:  all regulators are switched off.

   *** Sleep mode ***
   ==================
    [..]
      (+) Entry:
        The Sleep mode is entered by using the HAL_PWR_EnterSLEEPMode()


      -@@- The Regulator parameter is not used for the STM32MP1/STM32MP2 family
              and is kept as parameter just to maintain compatibility with the
              lower power families (STM32L).
              (on MPx families regulator param are output only on CSTOP not on CSLEEP)
      (+) Exit:
        Any peripheral interrupt acknowledged by the nested vectored interrupt
              controller (NVIC) can wake up the device from Sleep mode.

   *** Stop mode ***
   =================
    [..]
      In Stop mode, all clocks sharing same power domain than CPU are stopped, the PLL, the HSI,
      and the HSE RC oscillators are disabled. Internal SRAM and register contents
      are preserved.
      The voltage regulator can be configured either in normal or low-power mode.


      (+) Entry:
         The Stop mode is entered using the HAL_PWR_EnterSTOPMode()

      (+) Exit:
        Any EXTI Line (Internal or External) configured in Interrupt/Event mode.

   *** Standby mode ***
   ====================
    [..]
    (+)
      The Standby mode allows to achieve the lowest power consumption.

      The voltage regulator is OFF.

      (++) Entry:
        (+++) The Standby mode is entered using the HAL_PWR_EnterSTANDBYMode() function.
      (++) Exit:
        (+++) WKUP pin rising edge, RTC alarm (Alarm A and Alarm B), RTC wakeup,
             tamper event, time-stamp event, external reset in NRST pin, IWDG reset.

   *** Auto-wakeup (AWU) from low-power mode ***
   =============================================
    [..]

     (+) The MCU can be woken up from low-power mode by an RTC Alarm event, an RTC
      Wakeup event, a tamper event or a time-stamp event, without depending on
      an external interrupt (Auto-wakeup mode).

      (+) RTC auto-wakeup (AWU) from the Stop and Standby modes

        (++) To wake up from the Stop mode with an RTC alarm event, it is necessary to
              configure the RTC to generate the RTC alarm using the HAL_RTC_SetAlarm_IT() function.

        (++) To wake up from the Stop mode with an RTC Tamper or time stamp event, it
             is necessary to configure the RTC to detect the tamper or time stamp event using the
                HAL_RTCEx_SetTimeStamp_IT() or HAL_RTCEx_SetTamper_IT() functions.

        (++) To wake up from the Stop mode with an RTC WakeUp event, it is necessary to
              configure the RTC to generate the RTC WakeUp event using the HAL_RTCEx_SetWakeUpTimer_IT() function.

@endverbatim
  * @{
  */

#if defined(CORE_CM33)||defined(CORE_CA35)
/**
  * @brief  Configures EXTI for  Power Voltage Detector(PVD).
  * @param  sConfigPVD: pointer to an PWR_PVDTypeDef structure that contains the configuration
  *         information for the PVD.
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @retval None
  */
void HAL_PWR_ConfigPVD(const PWR_PVDTypeDef *sConfigPVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));

  /* Clear any previous config. Keep it clear if no IT mode is selected */
  __HAL_PWR_PVD_EXTI_DISABLE_IT();
  __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE();

  /* Configure interrupt mode */
  if (IS_AN_INTERRUPT_PWR_PVD_MODE(sConfigPVD->Mode))
  {
    __HAL_PWR_PVD_EXTI_ENABLE_IT();
  }

  /* Configure the edge */
  if ((sConfigPVD->Mode) == PWR_PVD_MODE_IT_RISING)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();
  }

  if ((sConfigPVD->Mode) == PWR_PVD_MODE_IT_FALLING)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();
  }

  if ((sConfigPVD->Mode) == PWR_PVD_MODE_IT_RISING_FALLING)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE();
  }
}

/**
  * @brief Enables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_EnablePVD(void)
{
  /* Enable the power voltage detector */
  SET_BIT(PWR->CR3, PWR_CR3_PVDEN);
}

/**
  * @brief Disables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_DisablePVD(void)
{
  /* Disable the power voltage detector */
  CLEAR_BIT(PWR->CR3, PWR_CR3_PVDEN);
}

/**
  * @brief  Indicate whether the VDD voltage level is between, above or below the threshold.
  * @retval VDD level which can be PWR_NO_VDD_MEASUREMENT_AVAILABLE / PWR_VDD_BELOW_THRESHOLD /
  *         PWR_VDD_ABOVE_OR_EQUAL_THRESHOLD
  */
uint32_t HAL_PWR_GetPVDRange(void)
{
  uint32_t regValue = PWR->CR3;

  /* check VDDcore monitoring is ON */
  if ((regValue & PWR_CR3_PVDEN) != PWR_CR3_PVDEN)
  {
    return PWR_NO_VDD_MEASUREMENT_AVAILABLE;
  }

  /* check VDDcore level */
  if ((regValue & PWR_CR3_PVDO) == PWR_CR3_PVDO)
  {
    return PWR_VDD_BELOW_THRESHOLD;
  }
  else
  {
    return PWR_VDD_ABOVE_OR_EQUAL_THRESHOLD;
  }
}

/**
  * @brief  This function handles the PWR PVD interrupt request.
  * @note   This API should be called under the PVD_IRQHandler().
  * @retval None
  */
void HAL_PWR_PVD_IRQHandler(void)
{
  if (HAL_PWR_GetPVDRange() == PWR_VDD_BELOW_THRESHOLD)
  {
    HAL_PWR_PVD_LowerCallback();
  }
  else
  {
    HAL_PWR_PVD_EqualHigherCallback();
  }

  /* Clear PWR PVD EXTI pending bit */
  __HAL_PWR_PVD_EXTI_CLEAR_FLAG();
}

/**
  * @brief  PWR PVD interrupt callback
  * @retval None
  */
__weak void HAL_PWR_PVD_EqualHigherCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWR_PVD_EqualHigherCallback could be implemented in the user file
   */
}
__weak void HAL_PWR_PVD_LowerCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWR_PVD_LowerCallback could be implemented in the user file
   */
}
#endif /* defined(CORE_CM33)||defined(CORE_CA35) */

#if defined(PWR_D3WKUPENR_TAMP_WKUPEN_D3)
#if !defined(CORE_CM0PLUS)
/*Below all fct to manage D3 wake-up from VBAT mode (ePOS) thru non secure TAMPERs, only M33/A35 can access
  PWR register for this configuration*/

/**
  * @brief Enable D3 wake-up from TAMPERs event when system is in VBAT mode, mandatory if ePOS mode targeted
  * @arg    None
  * @retval None
  */
void HAL_PWR_EnableD3WakeUpTamper(void)
{
  /*setting at PWR IP level */
  SET_BIT(PWR->D3WKUPENR, PWR_D3WKUPENR_TAMP_WKUPEN_D3);
}

/**
  * @brief Disable D3 wake-up from TAMPERs event when system is in VBAT mode
  * @arg    None
  * @retval None
  */
void HAL_PWR_DisableD3WakeUpTamper(void)
{
  /* disable at PWR IP level, D3 wake-up thru tamper event*/
  CLEAR_BIT(PWR->D3WKUPENR, PWR_D3WKUPENR_TAMP_WKUPEN_D3);
}

/**
  * @brief return true if D3 can be wakeup from VBat mode thru  TAMPERs event
  * @retval None
  */
uint32_t HAL_PWR_IsTamperD3WakeUpCapable(void)
{
  return ((PWR->D3WKUPENR & PWR_D3WKUPENR_TAMP_WKUPEN_D3) == PWR_D3WKUPENR_TAMP_WKUPEN_D3) ? 1U : 0U;
}

#endif /*if !defined(CORE_CM0PLUS)*/
#endif /* defined(PWR_D3WKUPENR_TAMP_WKUPEN_D3) */
/* end of fct to manage D3 wake-up from Vbat mode thru non-secure TAMPERs*/


#if !defined(CORE_CM0PLUS)
/*Below all fct to manage POWER WK-UP line */

/**
  * @brief Enable the WakeUp PINx functionality
  * @note Enable wake up from standby mechanism with CPU#i_WAKEUP_PIN_IRQn generation
  * @note wakeup pin from stand-by are one of the 6 wakeup line of PWR IP
  *
  * @note Note that handling of interruption (nvic/gic enable, priority setting callback) is out of scope of this
  * @note function and is under caller responsibility BUT as this interruption may wake-up from standby,
  * @note user shall take care that event is not lost
  * @note when GIC/NVIC is powered again (GIC/NVIC  shall be level sensitive ). For same standby exit purpose,
  * @note this function does not clear PWR WAKEUP line status, otherwise no wakeup event detected at
  * @note CPU level on standby exit.
  * @param WakeUpPinPolarity: Specifies on which edge  of Wake-Up pin detection is done
  *                           @arg PWR_WAKEUP_HIGH
  *                           @arg PWR_WAKEUP_LOW
  *                           @arg Specifies which pull configuration to set on  Wake-Up pin
  *                                 This parameter can be no pull edge   or  pull up or  pull down :
  *                           @arg  PWR_WAKEUP_NOPULL
  *                           @arg  PWR_WAKEUP_PULLUP
  *                           @arg  PWR_WAKEUP_PULLDOWN
  *                           @arg  Specifies the Power Wake-Up pin.This parameter can be one of the following values:
  *                           @arg PWR_WAKEUP_PIN_ID1
  *                           @arg PWR_WAKEUP_PIN_ID2
  *                           @arg PWR_WAKEUP_PIN_ID3
  *                           @arg PWR_WAKEUP_PIN_ID4
  *                           @arg PWR_WAKEUP_PIN_ID5
  *                           @arg PWR_WAKEUP_PIN_ID6
  * to keep compatibility with legacy API, this 3 parameters are gathered into one uint32_t polarity param
  * @retval None
  */
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinPolarity)
{
  __IO uint32_t *regaddr;
  uint32_t WakeUpPinEdge = ((WakeUpPinPolarity & PWR_WAKEUP_EDGE_MASK) >> PWR_WAKEUP_EDGE_POS);
  uint32_t WakeUpPinConfiguration = ((WakeUpPinPolarity & PWR_WAKEUP_PULL_MASK) >> PWR_WAKEUP_PULL_POS);
  uint32_t WakeUpPinx = ((WakeUpPinPolarity & PWR_WAKEUP_PIN_ID_MASK) >> PWR_WAKEUP_PIN_ID_POS);

  assert_param(IS_PWR_WAKEUP_PIN_ID(WakeUpPinx));
  assert_param(IS_PWR_WAKEUP_PIN_CONFIG(WakeUpPinConfiguration));
  assert_param(IS_PWR_WAKEUP_PIN_EDGE(WakeUpPinEdge));

  /*setting at PWR IP level */
  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET * WakeUpPinx); /* Selected register corresponding to input wakeup line*/
  CLEAR_BIT(*regaddr, PWR_CPU_TO_WAKE_UP);                    /* Disable WKUP pinx interruption on current CPU */
  /* Set edge  configuration for wake-up pin*/
  MODIFY_REG(*regaddr, PWR_WKUPCR1_WKUPP, WakeUpPinEdge << PWR_WKUPCR1_WKUPP_Pos);
  /* Set pull  configuration for wake-up pin*/
  MODIFY_REG(*regaddr, PWR_WKUPCR1_WKUPPUPD, WakeUpPinConfiguration << PWR_WKUPCR1_WKUPPUPD_Pos);

  SET_BIT(*regaddr, PWR_CPU_TO_WAKE_UP); /* Enable  WKUP pinx interruption on current CPU */
}
#endif /*!defined(CORE_CM0PLUS)*/


#if !defined(CORE_CM0PLUS)
/**
  * @brief Disables the WakeUp PINx functionality.*
  * @note wakeup pin from stand-by are one of the 6 wakeup line of PWR IP
  * @param WakeUpPinx: Specifies the Power Wake-Up pin.
  *         This parameter can be one of the following values:
  *           @arg PWR_WAKEUP_PIN_ID1
  *           @arg PWR_WAKEUP_PIN_ID2
  *           @arg PWR_WAKEUP_PIN_ID3
  *           @arg PWR_WAKEUP_PIN_ID4
  *           @arg PWR_WAKEUP_PIN_ID5
  *           @arg PWR_WAKEUP_PIN_ID6
  * @retval None
  */
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  assert_param(IS_PWR_WAKEUP_PIN_ID(WakeUpPinx));
  /*Disable  at EXTI IP level */
  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET * WakeUpPinx); /*selected register corresponding to input wakeup line*/
  CLEAR_BIT(*regaddr, PWR_CPU_TO_WAKE_UP);
}
#endif /*!defined(CORE_CM0PLUS)*/


#if !defined(CORE_CM0PLUS)
/**
  * @brief return wakeup capability status of a wakeup event
  * @note wakeup pin from stand-by are one of the 6 wakeup line of PWR IP
  * @param WakeUpPinx: Specifies the Power Wake-Up pin.
  *         This parameter can be one of the following values:
  *           @arg PWR_WAKEUP_PIN_ID1
  *           @arg PWR_WAKEUP_PIN_ID2
  *           @arg PWR_WAKEUP_PIN_ID3
  *           @arg PWR_WAKEUP_PIN_ID4
  *           @arg PWR_WAKEUP_PIN_ID5
  *           @arg PWR_WAKEUP_PIN_ID6
  * @retval None
  */
uint32_t HAL_PWR_IsWakeUpCapable(uint32_t WakeUpPinx)
{
  const __IO uint32_t *regaddr;

  assert_param(IS_PWR_WAKEUP_PIN_ID(WakeUpPinx));
  /*selected register corresponding to input wakeup line*/
  regaddr = (__IO uint32_t *)(&PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET * WakeUpPinx));
  return ((*regaddr & PWR_CPU_TO_WAKE_UP) == PWR_CPU_TO_WAKE_UP) ? 1U : 0U;
}
#endif /*!defined(CORE_CM0PLUS)*/


#if !defined(CORE_CM0PLUS)
/**
  * @brief unmask at EXTI level and for current CPU, EXTI_IRQn interruption associated to  wakeup pin  input parameter.
  *
  * @note Note that handling of interruption (nvic/gic enable, priority setting callback) is out of scope
  * @note of this function and is under caller responsibility
  * @note connected to EXTI2 in direct event type B
  * @note when current CPU is A35 or M33 , wakeup event are one of 6 wakeup-line of PWR IP
  * @note connected to EXTI1 in direct event type B
  * @param WakeUpPinx: Specifies the Power Wake-Up pin.
  *         This parameter can be one of the following values:
  *           @arg PWR_WAKEUP_PIN_ID1
  *           @arg PWR_WAKEUP_PIN_ID2
  *           @arg PWR_WAKEUP_PIN_ID3
  *           @arg PWR_WAKEUP_PIN_ID4
  *           @arg PWR_WAKEUP_PIN_ID5
  *           @arg PWR_WAKEUP_PIN_ID6
  * @retval None
  */
void HAL_PWR_EnableWakeUpExtiIT(uint32_t WakeUpPinx)
{
  assert_param(IS_PWR_WAKEUP_PIN_ID(WakeUpPinx));

  /*wake-up line connected on EXTI1, line 52 to 57*/
  __HAL_WKUP_EXTI_ENABLE_IT(extiImr2WakeUp[WakeUpPinx]);
}
#endif /*!defined(CORE_CM0PLUS)*/


#if !defined(CORE_CM0PLUS)
/**
  * @brief mask WakeUp PINx Interrupt at EXTI level for current CPU.
  * @param WakeUpPinx: Specifies the Power Wake-Up pin.
  *         This parameter can be one of the following values:
  *           @arg PWR_WAKEUP_PIN_ID1
  *           @arg PWR_WAKEUP_PIN_ID2
  *           @arg PWR_WAKEUP_PIN_ID3
  *           @arg PWR_WAKEUP_PIN_ID4
  *           @arg PWR_WAKEUP_PIN_ID5
  *           @arg PWR_WAKEUP_PIN_ID6
  */
void HAL_PWR_DisableWakeUpExtiIT(uint32_t WakeUpPinx)
{
  /*wake-up line connected on EXTI1, line 52 to 57*/
  assert_param(IS_PWR_WAKEUP_PIN_ID(WakeUpPinx));
  __HAL_WKUP_EXTI_DISABLE_IT(extiImr2WakeUp[WakeUpPinx]);
}
#endif /*!defined(CORE_CM0PLUS)*/


#if !defined(CORE_CM0PLUS)
/**
  * @brief Return  WakeUp PINx capability at EXTI level for current CPU.
  * @param WakeUpPinx: Specifies the Power Wake-Up pin.
  *         This parameter can be one of the following values:
  *           @arg PWR_WAKEUP_PIN_ID1
  *           @arg PWR_WAKEUP_PIN_ID2
  *           @arg PWR_WAKEUP_PIN_ID3
  *           @arg PWR_WAKEUP_PIN_ID4
  *           @arg PWR_WAKEUP_PIN_ID5
  *           @arg PWR_WAKEUP_PIN_ID6
  * @retval None
  */
uint32_t HAL_PWR_IsWakeUpExtiCapable(uint32_t WakeUpPinx)
{
  /*wake-up line connected on EXTI1, line 52 to 57*/
  assert_param(IS_PWR_WAKEUP_PIN_ID(WakeUpPinx));
  return (__HAL_WKUP_EXTI_BIT_IT(extiImr2WakeUp[WakeUpPinx]));
}
#endif /*!defined(CORE_CM0PLUS)*/


/**
  * @brief Return PWR state of a CPU
  * @retval return PWR_CPU_CRESET,PWR_CPU_CRUN,PWR_CPU_CSLEEP,PWR_CPU_CSTOP
  */
uint32_t HAL_PWR_CPU1State(void)
{
  return ((PWR->CPU1D1SR & PWR_CPU1D1SR_CSTATE_Msk) >> PWR_CPU1D1SR_CSTATE_Pos);
}
uint32_t HAL_PWR_CPU2State(void)
{
  return ((PWR->CPU2D2SR & PWR_CPU2D2SR_CSTATE_Msk) >> PWR_CPU2D2SR_CSTATE_Pos);
}
#if defined(PWR_CPU3D3SR_CSTATE)
uint32_t HAL_PWR_CPU3State(void)
{
  return ((PWR->CPU3D3SR & PWR_CPU3D3SR_CSTATE_Msk) >> PWR_CPU3D3SR_CSTATE_Pos);
}
#endif /* defined(PWR_CPU3D3SR_CSTATE) */
/**
  * @brief Return PWR state of a power D1 domain
  * @retval return PWR_D1_DRUN, PWR_D1_DSTOP1, PWR_D1_DSTOP2, PWR_D1_DSTOP3, PWR_D1_DSTANDBY
  */
uint32_t HAL_PWR_D1State(void)
{
  return ((PWR->CPU1D1SR & PWR_CPU1D1SR_DSTATE_Msk) >> PWR_CPU1D1SR_DSTATE_Pos);
}

/**
  * @brief Return PWR state of a power D2 domain
  * @retval return PWR_D2_RUN, PWR_D2_STOP, PWR_D2_LP_STOP, PWR_D2_LPLVSTOP2, PWR_D2_STANDBY, PWR_D2_VBAT
  */
uint32_t HAL_PWR_D2State(void)
{
  return ((PWR->CPU2D2SR & PWR_CPU2D2SR_DSTATE_Msk) >> PWR_CPU2D2SR_DSTATE_Pos);
}

#if defined(PWR_CPU3D3SR_DSTATE)
/**
  * @brief Return PWR state of a power D3 domain
  * @retval return PWR_D3_SRUN1, PWR_D3_SRUN2, PWR_D3_SRUN3, PWR_D3_SSTOP1, PWR_D3_SSTOP2, PWR_D3_SSTANDBY
  */
uint32_t HAL_PWR_D3State(void)
{
  return ((PWR->CPU3D3SR & PWR_CPU3D3SR_DSTATE_Msk) >> PWR_CPU3D3SR_DSTATE_Pos);
}
#endif /* defined(PWR_CPU3D3SR_DSTATE) */

/**
  * @brief Return true if D#i domain has been in idle mode since last reset
  * @retval return 0 if answer is false, not 0 if answer is true
  */
uint32_t HAL_PWR_HasD1BeenInStandby(void)
{
  return (__HAL_PWR_GET_FLAG(PWR_FLAG_SB_D1)) ? 1U : 0U;
}

uint32_t HAL_PWR_HasD2BeenInStandby(void)
{
  return (__HAL_PWR_GET_FLAG(PWR_FLAG_SB_D2)) ? 1U : 0U;
}

uint32_t HAL_PWR_HasD3BeenInStandby(void)
{
  return (__HAL_PWR_GET_FLAG(PWR_FLAG_SB_D3)) ? 1U : 0U;
}

/**
  * @brief Return true if system wakes-up from standby (a reset occurs for system wake-up)
  * @retval return 0 if answer is false, not 0 if answer is true
  */
uint32_t HAL_PWR_HasSystemBeenInStandby(void)
{
#if defined(CORE_CA35) || defined(CORE_CM33)
  return (__HAL_PWR_GET_FLAG(PWR_FLAG_SB)) ? 1U : 0U;
#else
  return (__HAL_PWR_GET_FLAG(PWR_FLAG_SB_D3));
#endif /* defined(CORE_CA35) || defined(CORE_CM33) */
}


/**
  * @brief Return true if system  was in VBAT mode
  * @retval return 0 if answer is false, not 0 if answer is true
  */
uint32_t HAL_PWR_HasSystemBeenInVBAT(void)
{
  return (__HAL_PWR_GET_FLAG(PWR_FLAG_VB)) ? 1U : 0U;
}


#if defined(CORE_CM33)||defined(CORE_CA35)
/**
  * @brief Return true if system wakes-up from cstop
  * @retval return 0 if answer is false, not 0 if answer is true
  */
uint32_t HAL_PWR_HasSystemBeenInStop(void)
{
  return (__HAL_PWR_GET_FLAG(PWR_FLAG_STOP)) ? 1U : 0U;
}
#endif /* defined(CORE_CM33)||defined(CORE_CA35) */


/**
  * @brief Enters Sleep mode.
  *
  * @note In Sleep mode, all I/O pins keep the same state as in Run mode.
  *
  * @note In Sleep mode, STM32MP2 PWR module does not allow any update of voltage regulator value:
  * @note Regulators are ON without any low power neither low voltage feature.
  * @note However, for compatibility reason, there is still a regulator argument
  *
  * @note In Sleep mode, the systick can be  stopped to avoid exit from this mode with
  *       systick interrupt when used as time base for Timeout

  * @param Regulator : unused variable but to keep compatibility with legacy API
  * @param SLEEPEntry: Specifies if SLEEP mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg PWR_SLEEPENTRY_WFI: enter SLEEP mode with WFI instruction
  *            @arg PWR_SLEEPENTRY_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void HAL_PWR_EnterSLEEPMode(__attribute__((unused))uint32_t Regulator, uint8_t SLEEPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_SLEEP_ENTRY(SLEEPEntry));

  /* Ensure core do not enter to CSTOP mode (on sleep, only core clock is gated, do not gate subsystem core clock) */
  KeepCortexSubsystemClockOnSleepEntry();

  /*check  request to system standby not set*/
  ClearStandbyRequest();

  /* Select SLEEP mode entry -------------------------------------------------*/
  if (SLEEPEntry == PWR_SLEEPENTRY_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }
}


/**
  * @brief Enters CSTOP/STOP mode.
  * @note In Stop mode, all I/O pins keep the same state as in Run mode.
  * @note When exiting Stop mode by issuing an interrupt or a wake up event,
  * @note the HSI oscillator is selected as system clock.
  * @note When the voltage regulator operates in low power mode, an additional
  * @note startup delay is incurred when waking up from Stop mode.
  * @note By keeping the internal regulator ON during Stop mode, the consumption
  * @note is higher although the startup time is reduced.
  * @param Regulator: Specifies which power state regulator supplying current CPU domain can reach
  *            This parameter can be one of the following values:
  *            @arg PWR_REGULATOR_LP_OFF i.e. full power
  *            @arg PWR_REGULATOR_LP_ON_LV_OFF i.e. can be low power but nominal voltage
  *            @arg PWR_REGULATOR_LP_ON_LV_ON  i.e. can be low power and  low voltage
  * @param STOPEntry: Specifies if Stop mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg PWR_STOPENTRY_WFI: Enter Stop mode with WFI instruction
  *            @arg PWR_STOPENTRY_WFE: Enter Stop mode with WFE instruction
  * @retval None
  */
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_STOP_MODE_REGULATOR(Regulator));
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

  /*indicate  which power saving  can be done when cpu is in stop mode*/
  SetRegulatorStopModeIndicator(Regulator);

  /*check  request to system standby not set*/
  ClearStandbyRequest();

  /* Ensure core enters in  CSTOP mode on sleep (core and core-subsystem  clock are gated) */
  GateCortexSubsystemClockOnSleepEntry();

  /* Select Stop mode entry --------------------------------------------------*/
  if ((STOPEntry == PWR_STOPENTRY_WFI))
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else if (STOPEntry == PWR_STOPENTRY_WFE)
  {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* do nothing */
  }
  /*remove any low power indication for regulator when CPU is in stop mode
    not mandatory as low power PWR output signal are not active when system is in RUN mode,
    but cleaner  to clear these bit inside PWR register*/
  ClearRegulatorStopModeIndicator();

  /* remove 'clock gating on sleep entry' request  */
  KeepCortexSubsystemClockOnSleepEntry();
}

#if defined(CORE_CM33)||defined(CORE_CA35)
/**
  * @brief Enters MPU CStandby / MCU CSTOP allowing system Standby mode.
  * @param STANDBYType: Specifies standby mode that can be reached
  *            This parameter can be one of the following values:
  *            @arg PWR_STANDBY_1 i.e. D3 still open (but D1 and D2 OFF)
  *            @arg PWR_STANDBY_2 i.e. D3 and D2 and D1 OFF
  * @retval None
  */
void HAL_PWR_EnterSTANDBYMode(uint8_t STANDBYType)
{
  /* Check the parameters */
  assert_param(IS_PWR_STANDBY_TYPE(STANDBYType));

  /*Indicate to regulator which power saving  can be done when cpu is in stop mode and allow clock gating*/
  /*useful in case standby is not granted but instead  cstop */
  SetRegulatorStopModeIndicator(PWR_REGULATOR_LP_ON_LV_ON);
  GateCortexSubsystemClockOnSleepEntry();

  /*set request to allow system standby*/
  SetStandbyRequest(STANDBYType);


  /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM)
  __force_stores();
#endif /* __CC_ARM */
  /* Request Wait For Interrupt */
  __WFI();

  /*
  code below is never reached in case STD-BY is granted by PWR but
  only in case of wake-up from sleep/stop (case STD-BY not granted due to other cores activities
  */

  /*remove CPU regulator from power saving state*/
  /*not mandatory as low power PWR output signal are not active when system is in RUN mode,
    but cleaner  to clear these bit inside PWR register*/
  ClearRegulatorStopModeIndicator();

  /* remove 'clock gating on sleep entry' request  */
  KeepCortexSubsystemClockOnSleepEntry();

  /*clear request to allow system standby*/
  ClearStandbyRequest();

}
#endif /*defined(CORE_CM33)||defined(CORE_CA35)*/


/**
  * @brief Indicates Sleep-On-Exit when returning from Handler mode to Thread mode.
  * @note Set SLEEPONEXIT bit of SCR register. When this bit is set, the processor
  *       re-enters IDLE/WFI mode when an interruption handling is over (cortex M)
  *       Setting this bit is useful when the processor is expected to run only on
  *       interruptions handling.
  * @retval None
  */
#if defined(CORE_CM33)||defined(CORE_CM0PLUS)
void HAL_PWR_EnableSleepOnExit(void)
{
  /* Set SLEEPONEXIT bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
  /* Ensure cortexM do not enter to CSTOP mode (do not gate core-subsystem clock when cpu enters sleep mode) */
  KeepCortexSubsystemClockOnSleepEntry();
  /*insure standby request not set*/
  ClearStandbyRequest();
}
#endif /* defined(CORE_CM33)||defined(CORE_CM0PLUS) */

/**
  * @brief Disables Sleep-On-Exit feature when returning from Handler mode to Thread mode.
  * @note Clears SLEEPONEXIT bit of SCR register.
  * @retval None
  */
#if defined(CORE_CM33)||defined(CORE_CM0PLUS)
void HAL_PWR_DisableSleepOnExit(void)
{
  /* Clear SLEEPONEXIT bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}
#endif /* defined(CORE_CM33)||defined(CORE_CM0PLUS) */

/**
  * @brief Indicates Stop-On-Exit when returning from Handler mode to Thread mode.
  * @note Set SLEEPONEXIT bit of SCR register. When this bit is set, the processor
  *       re-enters IDLE/WFA mode when an interruption handling is over (cortex M)
  *       Setting this bit is useful when the processor is expected to run only on
  *       interruptions handling.
  * @retval None
  */
#if defined(CORE_CM33)||defined(CORE_CM0PLUS)
void HAL_PWR_EnableStopOnExit(uint32_t Regulator)
{
  /*Indicate to regulator which power saving  can be done when cpu is in stop mode*/
  SetRegulatorStopModeIndicator(Regulator);
  /* Set SLEEPONEXIT bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
  /* Ensure cortexM subsystem  clock is  gated when cpu enters sleep mode) */
  GateCortexSubsystemClockOnSleepEntry();
  /*insure standby request not set*/
  ClearStandbyRequest();
}
#endif /* defined(CORE_CM33)||defined(CORE_CM0PLUS) */

/**
  * @brief Disables stop-On-Exit feature when returning from Handler mode to Thread mode.
  * @note Clears SLEEPONEXIT bit of SCR register.
  * @retval None
  */
#if defined(CORE_CM33)||defined(CORE_CM0PLUS)
void HAL_PWR_DisableStopOnExit(void)
{
  /* Clear SLEEPONEXIT bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
  /* clear automatic cortex subsystem clock gating on sleep entry*/
  KeepCortexSubsystemClockOnSleepEntry();
  /*remove any low power indication for regulator when CPU is in stop mode*/
  /*not mandatory as low power PWR output signal are not active when system is in RUN mode,
    but cleaner  to clear these bit inside PWR register*/
  ClearRegulatorStopModeIndicator();
}
#endif /*(CORE_CM33)||defined(CORE_CM0PLUS)*/


/**
  * @brief set CPU regulator constraint when cpu is in stop mode
  * @note not relevant if cpu is M0+
  * @retval None
  */
void SetRegulatorStopModeIndicator(uint32_t Regulator)
{
#if defined(CORE_CM0PLUS)
  UNUSED(Regulator);
#else /* CORE_CM0PLUS */
#ifdef CORE_CA35
#define LP_LV_SET_MSK (PWR_CPU1CR_LPDS_D1_Msk|PWR_CPU1CR_LVDS_D1_Msk)
#define REGU_SHIFT_SET PWR_CPU1CR_LPDS_D1_Pos
  __IO uint32_t *regaddr = &PWR->CPU1CR;
#endif /*CORE_CA35*/
#ifdef CORE_CM33
#define LP_LV_SET_MSK (PWR_CPU2CR_LPDS_D2_Msk|PWR_CPU2CR_LVDS_D2_Msk)
#define REGU_SHIFT_SET PWR_CPU2CR_LPDS_D2_Pos
  __IO uint32_t *regaddr = &PWR->CPU2CR;
#endif /*CORE_CM33*/

  /* Check  parameter */
  assert_param(IS_PWR_STOP_MODE_REGULATOR(Regulator));
  *regaddr = ((*regaddr & (~LP_LV_SET_MSK)) | (Regulator << REGU_SHIFT_SET));
#endif /* CORE_CM0PLUS */
}


/**
  * @brief clear CPU regulator constraint when cpu is in stop mode
  * @note thru this API CPU removes any  low power assertion on its domain regulator
  * @retval None
  */
void ClearRegulatorStopModeIndicator()
{
#ifdef CORE_CA35
#define LP_LV_CLR_MSK (PWR_CPU1CR_LPDS_D1_Msk|PWR_CPU1CR_LVDS_D1_Msk)
#define REGU_SHIFT_CLR PWR_CPU1CR_LPDS_D1_Pos
  MODIFY_REG(PWR->CPU1CR, LP_LV_CLR_MSK, PWR_REGULATOR_LP_OFF << REGU_SHIFT_CLR);
#endif /*  CORE_CA35 */
#ifdef CORE_CM33
#define LP_LV_CLR_MSK (PWR_CPU2CR_LPDS_D2_Msk|PWR_CPU2CR_LVDS_D2_Msk)
#define REGU_SHIFT_CLR PWR_CPU2CR_LPDS_D2_Pos
  MODIFY_REG(PWR->CPU2CR, LP_LV_CLR_MSK, PWR_REGULATOR_LP_OFF << REGU_SHIFT_CLR);
#endif /* CORE_CM33 */
}


/**
  * @brief request to gate cortex subsystem clock (e.g. GIC/NVIC, cache, ..) when CPU enters sleep mode
  * @retval None
  */
void GateCortexSubsystemClockOnSleepEntry(void)
{
#if defined(CORE_CM33)||defined(CORE_CM0PLUS)
  /* Set DEEP SLEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);
#else
  __HAL_RCC_ALLOW_CSTOP();
#endif /* defined(CORE_CM33)||defined(CORE_CM0PLUS) */
}


/**
  * @brief forbid  gating of cortex subsystem clock (e.g. GIC/NVIC, cache, ..) when CPU enters sleep mode
  * @retval None
  */
void KeepCortexSubsystemClockOnSleepEntry(void)
{
#if defined(CORE_CM33)||defined(CORE_CM0PLUS)
  /* clear DEEP SLEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);
#else
  __HAL_RCC_PREVENT_CSTOP();
#endif /* defined(CORE_CM33)||defined(CORE_CM0PLUS) */
}

/**
  * @brief forbid  system to go in any standby mode
  * @retval None
  */
void ClearStandbyRequest(void)
{
#ifdef CORE_CA35
  CLEAR_BIT(PWR->CPU1CR, SYSTEM_STANDBY_REQUEST);
  CLEAR_BIT(PWR->CPU1CR, DOMAIN2_STANDBY_REQUEST);
#if defined(PWR_D3CR_PDDS_D3)
  CLEAR_BIT(PWR->D3CR, PWR_D3CR_PDDS_D3);
#endif /* defined(PWR_D3CR_PDDS_D3) */
#endif /* CORE_CA35 */
#ifdef CORE_CM33
  CLEAR_BIT(PWR->CPU2CR, SYSTEM_STANDBY_REQUEST);
#if defined(PWR_D3CR_PDDS_D3)
  CLEAR_BIT(PWR->D3CR, PWR_D3CR_PDDS_D3);
#endif /* defined(PWR_D3CR_PDDS_D3) */
#endif /* CORE_CM33 */
}


#if defined(CORE_CM33)||defined(CORE_CA35)
/**
  * @brief request   system to go in any standby mode
  * @note Beware request may not be granted by PWR (case activity on others CPUs)
  * @retval None
  */
void SetStandbyRequest(uint8_t STANDBYType)
{
  /*clear all standby flag, mandatory otherwise  standby flags are not relevant  at reset (except if reset is pon !)*/
  __HAL_PWR_CLEAR_FLAG();

  /* set CPU system standby authorization*/
#ifdef CORE_CA35
  SET_BIT(PWR->CPU1CR, SYSTEM_STANDBY_REQUEST);
  SET_BIT(PWR->CPU1CR, DOMAIN2_STANDBY_REQUEST);   /*MPU power constraint on D2 domain*/
#endif /* CORE_CA35 */
#ifdef CORE_CM33
  SET_BIT(PWR->CPU2CR, SYSTEM_STANDBY_REQUEST);
#endif /* CORE_CM33 */
#if defined(PWR_D3CR_PDDS_D3)
  if (STANDBYType == PWR_STANDBY_2)
    /*if standby2 is requested, CPU shall set D3 domain standby authorization*/
  {
    SET_BIT(PWR->D3CR, PWR_D3CR_PDDS_D3);
  }
#endif /* defined(PWR_D3CR_PDDS_D3) */
}
#endif /*defined(CORE_CM33)||defined(CORE_CA35)*/

/**
  * @brief Enables CORTEX SEVONPEND bit.
  * @note Sets SEVONPEND bit of SCR register. When this bit is set, pending
  * interruptions (even if interruption disable) can wakeup processor (cortexM) from WFE
  * @retval None
  */
#if defined(CORE_CM33)||defined(CORE_CM0PLUS)
void HAL_PWR_EnableSEVOnPend(void)
{
  /* Set SEVONPEND bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}
#endif /* defined(CORE_CM33)||defined(CORE_CM0PLUS) */

/**
  * @brief Disables CORTEX SEVONPEND bit.
  * @note Clears SEVONPEND bit of SCR register. When this bit is clear, pending
  * interruptions (even if interruption disable) cannot wakeup processor (cortexM) from WFE
  * @retval None
  */
#if defined(CORE_CM33)||defined(CORE_CM0PLUS)
void HAL_PWR_DisableSEVOnPend(void)
{
  /* Clear SEVONPEND bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}
#endif /* defined(CORE_CM33)||defined(CORE_CM0PLUS) */

/**
  * @brief  Configure RIF attribute of a WIO pin bitmap.
  *         Available RIF attributes are CID, security and privilege protection.
  *         RIF attribute is applied on all pins of input param bitmap.
  * @note   If no CID attribute provide, CID filtering is disabled.
  * @param  Resource : wake-up io pin bitmap.
  * @param  ResourceAttributes: RIF (CID/secure/privilege) attributes.

  * @retval HAL Status.

  */
HAL_StatusTypeDef HAL_PWR_ConfigWioResourceAttributes(uint16_t Resource, uint32_t ResourceAttributes)
{
  uint32_t position = 0x00;
  uint32_t iocurrent;
  __IO uint32_t *regaddr;

  /* Check the parameters */
  assert_param(IS_WIO_RESOURCE(Resource));
  assert_param(IS_WIO_PIN_ATTRIBUTES(ResourceAttributes));

  /* Configure WIO pin(s) */
  while (((Resource >> WIO_RESOURCE_POS) >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = ((uint32_t)Resource >> WIO_RESOURCE_POS) & (1UL << position);
    if (iocurrent != 0U)
    {
#if defined (CORTEX_IN_SECURE_STATE)
      if ((ResourceAttributes & WIO_PIN_ATTR_SEC_SELECT) == WIO_PIN_ATTR_SEC_SELECT)
      {
        /* Configure secure/non-secure attribute */
        if ((ResourceAttributes & WIO_PIN_SEC) == WIO_PIN_SEC)
        {
          PWR->WIOSECCFGR |= iocurrent;
        }
        else
        {
          PWR->WIOSECCFGR &= (~iocurrent);
        }
      }
#endif /* CORTEX_IN_SECURE_STATE */
      if ((ResourceAttributes & WIO_PIN_ATTR_PRIV_SELECT) == WIO_PIN_ATTR_PRIV_SELECT)
      {
        /* Configure privilege/non-privilege attribute */
        if ((ResourceAttributes & WIO_PIN_PRIV) == WIO_PIN_PRIV)
        {
          PWR->WIOPRIVCFGR |= iocurrent;
        }
        else
        {
          PWR->WIOPRIVCFGR &= (~iocurrent);
        }
      }
      /* selected register corresponding to current WIO resource */
      regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET * position);

      *regaddr = 0;  /* remove any CID filtering on selected pin */
      if ((ResourceAttributes & (WIO_PIN_CID_DISABLE | WIO_PIN_ATTR_CID_STATIC_SELECT)) == \
          WIO_PIN_ATTR_CID_STATIC_SELECT)
        /* static CID field value used ONLY is CID filtering not disable */
      {
        /* Write static CID configuration */
        *regaddr = ((ResourceAttributes & PWR_WIO1CIDCFGR_SCID_Msk) | PWR_WIO1CIDCFGR_CFEN);
      }
      if ((ResourceAttributes & (WIO_PIN_CID_DISABLE | WIO_PIN_ATTR_CID_SHARED_SELECT)) == \
          WIO_PIN_ATTR_CID_SHARED_SELECT)
        /*shared CID field value used ONLY is CID filtering not disable */
      {
        /* Write shared CID configuration */
        *regaddr = ((ResourceAttributes & WIO_PIN_ATTR_CID_SHARED_MASK) | PWR_WIO1CIDCFGR_SEM_EN | \
                    PWR_WIO1CIDCFGR_CFEN);
      }
    }
    position++;
  }
  return HAL_OK;
}

/**
  * @brief  Get a RIF attributes a single WIO pin.
  * @note   In case input bitmap selects several pins, RIF attributes of first low rank pin is returned
  * @param  Resource : wake-up io pin bitmap, should select only ONE pin
  * @param  pResourceAttributes : pointer of  RIF attributes.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWR_GetConfigWioResourceAttributes(uint16_t Resource, uint32_t *pResourceAttributes)
{
  uint32_t position = 0x00;
  uint32_t iocurrent;
  __IO uint32_t *regaddr;

  /* Check null pointer */
  if (pResourceAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_WIO_RESOURCE(Resource));
  *pResourceAttributes = 0;

  /* Get rif attribute of the WIO pin */
  while (((Resource >> WIO_RESOURCE_POS) >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = ((uint32_t)Resource >> WIO_RESOURCE_POS) & (1UL << position);

    if (iocurrent != 0U)
    {
#if defined (CORTEX_IN_SECURE_STATE)
      *pResourceAttributes |= ((PWR->WIOSECCFGR & iocurrent) == 0U) ? WIO_PIN_NSEC : WIO_PIN_SEC;
#endif /* CORTEX_IN_SECURE_STATE */
      *pResourceAttributes |= ((PWR->WIOPRIVCFGR & iocurrent) == 0U) ? WIO_PIN_NPRIV : WIO_PIN_PRIV;

      regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET * position);
      if ((*regaddr & PWR_WIO1CIDCFGR_CFEN_Msk) == PWR_WIO1CIDCFGR_CFEN)
      {
        if ((*regaddr & PWR_WIO1CIDCFGR_SEM_EN_Msk) == PWR_WIO1CIDCFGR_SEM_EN)
        {
          /* Get CIDs value from Semaphore white list */
          *pResourceAttributes |= ((WIO_PIN_ATTR_CID_SHARED_SELECT) |
                                   (((*regaddr)) & (WIO_PIN_ATTR_CID_SHARED_MASK)));
        }
        else
        {
          /* Get CIDs value from Static CID field */
          *pResourceAttributes |= (WIO_PIN_ATTR_CID_STATIC_SELECT | ((*regaddr) & PWR_WIO1CIDCFGR_SCID_Msk));
        }
      }
      else
      {
        *pResourceAttributes |= WIO_PIN_CID_DISABLE;
      }
      break;
    }
    position++;
  }

  return HAL_OK;
}

/**
  * @brief  Configure RIF attribute of a non shareable resource bitmap.
  *         Available RIF attributes are CID, security and privilege protection.
  *         RIF attribute is applied on all pins of input param bitmap.
  * @note   If no CID attribute provide, CID filtering is disabled.
  * @param  Resource : non shareable resource bitmap.
  * @param  ResourceAttributes: RIF (CID/secure/privilege) attributes.

  * @retval HAL Status.

  */
HAL_StatusTypeDef HAL_PWR_ConfigNonShareableResourceAttributes(uint16_t Resource, uint32_t ResourceAttributes)
{
  uint32_t position = 0x00;
  uint32_t iocurrent;
  __IO uint32_t *regaddr;

  /* Check the parameters */
  assert_param(IS_NS_RESOURCE(Resource));
  assert_param(IS_NS_RESOURCE_ATTRIBUTES(ResourceAttributes));

  /* Configure non shareable resource(s) */
  while (((Resource >> NS_RESOURCE_POS) >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = ((uint32_t)Resource >> NS_RESOURCE_POS) & (1UL << position);
    if (iocurrent != 0U)
    {
#if defined (CORTEX_IN_SECURE_STATE)
      if ((ResourceAttributes & NS_RESOURCE_ATTR_SEC_SELECT) == NS_RESOURCE_ATTR_SEC_SELECT)
      {
        /* Configure secure/non-secure attribute */
        if ((ResourceAttributes & NS_RESOURCE_SEC) == NS_RESOURCE_SEC)
        {
          PWR->RSECCFGR |= iocurrent;
        }
        else
        {
          PWR->RSECCFGR &= (~iocurrent);
        }
      }
#endif /* CORTEX_IN_SECURE_STATE */
      if ((ResourceAttributes & NS_RESOURCE_ATTR_PRIV_SELECT) == NS_RESOURCE_ATTR_PRIV_SELECT)
      {
        /* Configure privilege/non-privilege attribute */
        if ((ResourceAttributes & NS_RESOURCE_PRIV) == NS_RESOURCE_PRIV)
        {
          PWR->RPRIVCFGR |= iocurrent;
        }
        else
        {
          PWR->RPRIVCFGR &= (~iocurrent);
        }
      }
      /* select register corresponding to current non-shareable resource */
      regaddr = &PWR->RxCIDCFGR[0] + (R_CID_CFG_ADD_OFFSET * position);
      *regaddr = 0;  /*remove any CID filtering on selected pin*/
      if ((ResourceAttributes & (NS_RESOURCE_CID_DISABLE | NS_RESOURCE_ATTR_CID_STATIC_SELECT)) ==
          NS_RESOURCE_ATTR_CID_STATIC_SELECT)
        /*static CID field value used ONLY is CID filtering not disable */
      {
        /* Write static CID configuration */
        *regaddr = ((ResourceAttributes & PWR_R0CIDCFGR_SCID_Msk) | PWR_R0CIDCFGR_CFEN);
      }
    }
    position++;
  }
  return HAL_OK;
}


/**
  * @brief  Get a RIF attributes a single non shareable resource.
  * @note   In case input bitmap selects several resource, RIF attributes of first low rank resource is returned
  * @param  Resource : non shareable resource bitmap, should select only ONE resource
  * @param  pResourceAttributes : pointer of  RIF attributes.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWR_GetConfigNonShareableResourceAttributes(uint16_t Resource, uint32_t *pResourceAttributes)
{
  uint32_t position = 0x00;
  uint32_t iocurrent;
  __IO uint32_t *regaddr;

  /* Check null pointer */
  if (pResourceAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_NS_RESOURCE(Resource));
  *pResourceAttributes = 0;

  /* Get rif attribute of the non-shareable resource */
  while (((Resource >> NS_RESOURCE_POS) >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = ((uint32_t)Resource >> NS_RESOURCE_POS) & (1UL << position);

    if (iocurrent != 0U)
    {
#if defined (CORTEX_IN_SECURE_STATE)
      *pResourceAttributes |= ((PWR->RSECCFGR & iocurrent) == 0U) ? NS_RESOURCE_NSEC : NS_RESOURCE_SEC;
#endif /* CORTEX_IN_SECURE_STATE */
      *pResourceAttributes |= ((PWR->RPRIVCFGR & iocurrent) == 0U) ? NS_RESOURCE_NPRIV : NS_RESOURCE_PRIV;
      /* select register corresponding to current non-shareable resource */
      regaddr = &PWR->RxCIDCFGR[0] + (R_CID_CFG_ADD_OFFSET * position);
      if ((*regaddr & PWR_R0CIDCFGR_CFEN_Msk) == PWR_R0CIDCFGR_CFEN)
      {
        /* Get CIDs value from Static CID field */
        *pResourceAttributes |= (NS_RESOURCE_ATTR_CID_STATIC_SELECT | ((*regaddr) & PWR_R0CIDCFGR_SCID_Msk));
      }
      else
      {
        *pResourceAttributes |= NS_RESOURCE_CID_DISABLE;
      }
      break;
    }
    position++;
  }

  return HAL_OK;
}

/**
  * @brief  Attempt to acquire semaphore(s) of  WIO pin bitmap.
  * @note   In case of semaphore acquisition failure, returned status is HAL_KO and
            semaphore acquisition is abandoned  for all bitmap
  * @param  Item : wake-up io pin bitmap
  * @retval HAL Status, HAL_OK if semaphore acquisition for all pins of WIO_Pin is successful
  */
HAL_StatusTypeDef HAL_PWR_TakeResourceSemaphore(uint16_t Item)
{
  uint32_t position = 0x00;
  uint32_t iocurrent;
  uint32_t msk = 0x00;
  __IO uint32_t *regaddr;

  /* Check the parameters */
  assert_param(IS_WIO_RESOURCE(Item));

  /* Get secure attribute of the port pin */
  while (((Item >> WIO_RESOURCE_POS) >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = ((uint32_t)Item >> WIO_RESOURCE_POS) & (1UL << position);
    if (iocurrent != 0U)
    {
      /* Take Semaphore*/
      regaddr = &PWR->WIO1SEMCR + (WIO_CID_CFG_ADD_OFFSET * position);
      *regaddr = PWR_WIO1SEMCR_SEM_MUTEX;
      if (((*regaddr) & PWR_WIO1SEMCR_SEMCID_Msk) != (PWR_WIO1SEMCR_SEMCID_CURRENT))
      {
        /* Mutex not taken with current CID - it means that other authorized CID has control,
           all previous acquired semaphores (if any) shall be released and status error is returned*/
        if ((((uint32_t)Item >> WIO_RESOURCE_POS) & msk) != 0U)
        {
          (void)HAL_PWR_ReleaseResourceSemaphore((Item >> WIO_RESOURCE_POS) & (uint16_t)msk);
        }
        return HAL_ERROR;
      }
    }
    msk += (1UL << position);
    position++;
  }
  return HAL_OK;
}


/**
  * @brief  Release semaphore(s) of  WIO pin bitmap.
  * @param  Item : wake-up io pin bitmap
  * @retval HAL Status, HAL_OK
  */
HAL_StatusTypeDef HAL_PWR_ReleaseResourceSemaphore(uint16_t Item)
{
  uint32_t position = 0x00;
  uint32_t iocurrent;
  __IO uint32_t *regaddr;

  /* Check the parameters */
  assert_param(IS_WIO_RESOURCE(Item));

  /* Get secure attribute of the port pin */
  while (((Item >> WIO_RESOURCE_POS) >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = ((uint32_t)Item >> WIO_RESOURCE_POS) & (1UL << position);
    if (iocurrent != 0U)
    {
      /* Release Semaphore*/
      regaddr = &PWR->WIO1SEMCR + (WIO_CID_CFG_ADD_OFFSET * position);
      *regaddr = ~PWR_WIO1SEMCR_SEM_MUTEX;
    }
    position++;
  }
  return HAL_OK;
}


/**
  * @brief  Configure RIF attribute of a PWR resource (bitmap).
  *         Available RIF attributes are CID, security and privilege protection.
  *         RIF attribute is applied on all PWR resource of input param bitmap.
  *         PWR resource is either a wake-up resource (WIO) or a Non Shareable resource (NS)
  * @note   If no CID attribute provide, CID filtering is disabled.
  * @param  Item : PWR resource bitmap.
  * @param  Attributes: RIF (CID/secure/privilege) attributes.

  * @retval void
  */
void HAL_PWR_ConfigResourceAttributes(uint16_t Item, uint32_t Attributes)
{
  /* Check the parameters */
  assert_param(IS_PWR_ITEMS(Item));

  if (IS_WIO_RESOURCE(Item))
  {
    (void)HAL_PWR_ConfigWioResourceAttributes(Item, Attributes);
  }
  if (IS_NS_RESOURCE(Item))
  {
    (void)HAL_PWR_ConfigNonShareableResourceAttributes(Item, Attributes);
  }
}

/**
  * @brief  Get a RIF attributes a single PWR resource.
  *         PWR resource is either a wake-up resource (WIO) or a Non Shareable resource (NS)
  * @note   In case input bitmap selects several resource, RIF attributes of first low rank resource is returned
  * @param  Item : PWR resource bitmap, should select only ONE resource
  * @param  pAttributes : pointer of  RIF attributes.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWR_GetConfigResourceAttributes(uint16_t Item, uint32_t *pAttributes)
{
  /* Check the parameters */
  assert_param(IS_PWR_ITEMS(Item));

  if (IS_WIO_RESOURCE(Item))
  {
    return (HAL_PWR_GetConfigWioResourceAttributes(Item, pAttributes));
  }
  if (IS_NS_RESOURCE(Item))
  {
    return (HAL_PWR_GetConfigNonShareableResourceAttributes(Item, pAttributes));
  }
  return HAL_OK;
}


/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_PWR_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
