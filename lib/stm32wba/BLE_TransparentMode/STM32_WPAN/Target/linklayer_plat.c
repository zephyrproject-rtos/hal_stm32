/*
 * Copyright (c) 2023 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "scm.h"

#define max(a,b) ((a) > (b) ? a : b)

/* 2.4GHz RADIO ISR callbacks */
typedef void (*radio_isr_cb_t) (void);

/* Radio critical sections */
static uint32_t primask_bit = 0;
volatile int32_t irq_counter;

/* Radio bus clock control variables */
uint8_t AHB5_SwitchedOff;
uint32_t radio_sleep_timer_val;

/**
  * @brief  Configure the necessary clock sources for the radio.
  * @param  None
  * @retval None
  */
void LINKLAYER_PLAT_ClockInit(void)
{
	AHB5_SwitchedOff = 0;
	radio_sleep_timer_val = 0;

	LL_PWR_EnableBkUpAccess();

	/* Select LSE as Sleep CLK */
	__HAL_RCC_RADIOSLPTIM_CONFIG(RCC_RADIOSTCLKSOURCE_LSE);

	LL_PWR_DisableBkUpAccess();

	/* Enable AHB5ENR peripheral clock (bus CLK) */
	__HAL_RCC_RADIO_CLK_ENABLE();
}

/**
  * @brief  Enable/disable the Link Layer active clock (baseband clock).
  * @param  enable: boolean value to enable (1) or disable (0) the clock.
  * @retval None
  */
void LINKLAYER_PLAT_WaitHclkRdy(void)
{
  /* Wait on radio bus clock readiness */
  while(HAL_RCCEx_GetRadioBusClockReadiness() != RCC_RADIO_BUS_CLOCK_READY);
}

/**
  * @brief  Active wait on bus clock readiness.
  * @param  None
  * @retval None
  */
void LINKLAYER_PLAT_AclkCtrl(uint8_t enable)
{
  if(enable){
    /* Enable RADIO baseband clock (active CLK) */
    HAL_RCCEx_EnableRadioBBClock();

    /* Polling on HSE32 activation */
    while ( LL_RCC_HSE_IsReady() == 0);
  }
  else
  {
    /* Disable RADIO baseband clock (active CLK) */
    HAL_RCCEx_DisableRadioBBClock();
  }
}

/**
  * @brief  Enable interrupts.
  * @param  None
  * @retval None
  */
void LINKLAYER_PLAT_EnableIRQ(void)
{
  irq_counter = max(0,irq_counter-1);

  if(irq_counter == 0)
  {
    /* When irq_counter reaches 0, restore primask bit */
    __set_PRIMASK(primask_bit);
  }
}

/**
  * @brief  Disable interrupts.
  * @param  None
  * @retval None
  */
void LINKLAYER_PLAT_DisableIRQ(void)
{
  if(irq_counter == 0)
  {
    /* Save primask bit at first interrupt disablement */
    primask_bit= __get_PRIMASK();
  }
  __disable_irq();
  irq_counter ++;
}

/**
  * @brief  Enable link layer high priority ISR only.
  * @param  None
  * @retval None
  */
void LINKLAYER_PLAT_EnableRadioIT(void)
{
  /* USER CODE BEGIN LINKLAYER_PLAT_EnableRadioIT_1*/

  /* USER CODE END LINKLAYER_PLAT_EnableRadioIT_1*/

  HAL_NVIC_EnableIRQ((IRQn_Type) RADIO_INTR_NUM);

  /* USER CODE BEGIN LINKLAYER_PLAT_EnableRadioIT_2*/

  /* USER CODE END LINKLAYER_PLAT_EnableRadioIT_2*/
}

/**
  * @brief  Disable link layer high priority ISR only.
  * @param  None
  * @retval None
  */
void LINKLAYER_PLAT_DisableRadioIT(void)
{
  /* USER CODE BEGIN LINKLAYER_PLAT_DisableRadioIT_1*/

  /* USER CODE END LINKLAYER_PLAT_DisableRadioIT_1*/

  HAL_NVIC_DisableIRQ((IRQn_Type) RADIO_INTR_NUM);

  /* USER CODE BEGIN LINKLAYER_PLAT_DisableRadioIT_2*/

  /* USER CODE END LINKLAYER_PLAT_DisableRadioIT_2*/
}

/**
  * @brief  Get the ST company ID.
  * @param  None
  * @retval Company ID
  */
uint32_t LINKLAYER_PLAT_GetSTCompanyID(void)
{
  return LL_FLASH_GetSTCompanyID();
}

/**
  * @brief  Get the Unique Device Number (UDN).
  * @param  None
  * @retval UDN
  */
uint32_t LINKLAYER_PLAT_GetUDN(void)
{
  return LL_FLASH_GetUDN();
}

/**
  * @brief  Notify the Link Layer platform layer the system will enter in WFI 
  *         and AHB5 clock may be turned of regarding the 2.4Ghz radio state. 
  * @param  None
  * @retval None
  */
void LINKLAYER_PLAT_NotifyWFIEnter(void)
{
  /* Check if Radio state will allow the AHB5 clock to be cut */
  
  /* AHB5 clock will be cut in the following cases:
   * - 2.4GHz radio is not in ACTIVE mode (in SLEEP or DEEPSLEEP mode).
   * - RADIOSMEN and STRADIOCLKON bits are at 0.
   */
  if((LL_PWR_GetRadioMode() != LL_PWR_RADIO_ACTIVE_MODE) ||
     ((__HAL_RCC_RADIO_IS_CLK_SLEEP_ENABLED() == 0) && (LL_RCC_RADIO_IsEnabledSleepTimerClock() == 0)))
  {
    AHB5_SwitchedOff = 1;
  }
}

/**
  * @brief  Notify the Link Layer platform layer the system exited WFI and AHB5 
  *         clock may be resynchronized as is may have been turned of during
  *         low power mode entry.
  * @param  None
  * @retval None
  */
void LINKLAYER_PLAT_NotifyWFIExit(void)
{
 /* Check if AHB5 clock has been turned of and needs resynchronisation */
  if (AHB5_SwitchedOff)
  {
    /* Read sleep register as earlier as possible */
    radio_sleep_timer_val = ll_intf_cmn_get_slptmr_value();
  }
}
