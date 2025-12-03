/* radio_plat.c - radio platform adaptation layer */

/*
 * Copyright (c) 2026 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "linklayer_plat.h"
#include "stm32wbaxx_ll_rcc.h"
#include "hw.h"

/*
 * @brief  Configure the necessary clock sources for the radio
 */
 void RADIO_PLAT_ClockInit(void)
{
  LINKLAYER_PLAT_ClockInit();
}

/*
 * @brief  Disable the clock sources used for the radio
 */
void RADIO_PLAT_ClockDeinit(void)
{
  HW_RNG_DisableClock(0);

  LINKLAYER_PLAT_AclkCtrl(0);

  __HAL_RCC_RADIO_CLK_DISABLE();

  __HAL_RCC_RADIO_CLK_SLEEP_DISABLE();
}
