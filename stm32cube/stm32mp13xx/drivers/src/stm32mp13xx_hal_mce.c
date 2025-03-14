/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_mce.c
  * @author  MCD Application Team
  * @brief   MCE HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Memory Cipher Engine (MCE) Peripheral.
  *           +
  *           +
  *           +
  *
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
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal.h"

#include <stdbool.h>
#include <string.h>

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @defgroup MCE MCE
  * @brief HAL MCE module driver
  * @{
  */
#ifdef HAL_MCE_MODULE_ENABLED
#if defined (MCE)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup MCE_Private_Constants MCE Private Constants
  * @{
  */
#define DDR_BASE_ADDR                        0xC0000000U
#define DDR_MAX_SIZE                         0x40000000U

#define MCE_GRANULARITY                      0x10000U
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup MCE_Exported_Functions MCE Exported Functions
  * @{
  */

/**
  * @brief  MCE initialization, including
  *         - clock management,
  *         - master key filling with validity verification,
  *         - master key lock.
  * @retval None.
  */
void HAL_MCE_Init(void)
{
  SET_BIT(RCC->MP_AHB6ENSETR, RCC_MP_AHB6ENSETR_MCEEN);

  if ((MCE->CR & MCE_CR_MKLOCK) != MCE_CR_MKLOCK)
  {
    MCE->MKEYR0 = 0x78214125U;
    MCE->MKEYR1 = 0x442A472DU;
    MCE->MKEYR2 = 0x4B615064U;
    MCE->MKEYR3 = 0x5367566BU;

    while ((MCE->SR & MCE_SR_MKVALID) == 0U)
    {
      ;
    }

    MCE->CR |= MCE_CR_MKLOCK;
  }
}

/**
  * @brief  Enable MCE region.
  * @param  address Region start address.
  * @param  size Region size.
  * @param  type Region type (normal or encrypted).
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_MCE_Enable_Region(uint32_t address, uint32_t size,
                                        HAL_MCE_RegionTypeDef type)
{
  if ((address < DDR_BASE_ADDR)
      || (size == 0U)
      || ((address - DDR_BASE_ADDR + size) > DDR_MAX_SIZE))
  {
    return HAL_ERROR;
  }

  if (((address % MCE_GRANULARITY)  != 0U)
      || ((size % MCE_GRANULARITY)  != 0U))
  {
    return HAL_ERROR;
  }

  if (type > HAL_MCE_ENCRYPTED_REGION)
  {
    return HAL_ERROR;
  }

  if ((MCE->REGCR & MCE_REGCR_BREN) == MCE_REGCR_BREN)
  {
    MCE->REGCR &= ~MCE_REGCR_BREN;
  }

  MCE->SADDR = (address & MCE_SADDR_BADDSTART);
  MCE->EADDR = ((address + size - 1U) & MCE_EADDR_BADDEND);
  if (type == HAL_MCE_ENCRYPTED_REGION)
  {
    MCE->REGCR |= MCE_REGCR_ENC | MCE_REGCR_BREN;
    if ((MCE->SR & MCE_SR_ENCDIS) != 0U)
    {
      return HAL_ERROR;
    }
  }
  else
  {
    MCE->REGCR &= ~MCE_REGCR_ENC;
    MCE->REGCR |= MCE_REGCR_BREN;
  }

  return HAL_OK;
}

void HAL_MCE_IRQHandler(void)
{
  if ((MCE->IASR & MCE_IASR_CAEF) == MCE_IASR_CAEF)
  {
    MCE->IACR |= MCE_IACR_CAEF;
  }
}

/**
  * @}
  */
#endif /* MCE */
#endif /* HAL_MCE_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
