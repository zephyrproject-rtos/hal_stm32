/**
  ******************************************************************************
  * @file    stm32n6xx_ll_dlyb.c
  * @author  MCD Application Team
  * @brief   DelayBlock Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the DelayBlock peripheral:
  *           + input clock frequency
  *           + up to 12 oversampling phases
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                       ##### DelayBlock peripheral features #####
  ==============================================================================
    [..] The DelayBlock is used to generate an Output clock which is de-phased from the Input
          clock. The phase of the Output clock is programmed by FW. The Output clock is then used
          to clock the receive data in i.e. a SDMMC, OSPI or QSPI interface.
         The delay is Voltage and Temperature dependent, which may require FW to do re-tuning
          and recenter the Output clock phase to the receive data.

    [..] The DelayBlock features include the following:
         (+) Input clock frequency.
         (+) Up to 12 oversampling phases.

                           ##### How to use this driver #####
  ==============================================================================
    [..]
      This driver is a considered as a driver of service for external devices drivers
      that interfaces with the DELAY peripheral.
      The LL_DLYB_SetDelay() function, configure the Delay value configured on SEL and UNIT.
      The LL_DLYB_GetDelay() function, return the Delay value configured on SEL and UNIT.
      The LL_DLYB_GetClockPeriod()function, get the clock period.


  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"

/** @addtogroup STM32N6xx_LL_Driver
  * @{
  */

/** @defgroup DLYB_LL DLYB
  * @brief DLYB LL module driver.
  * @{
  */

#if defined(HAL_SD_MODULE_ENABLED) || defined(HAL_OSPI_MODULE_ENABLED) || defined(HAL_XSPI_MODULE_ENABLED)
#if defined (DLYB_SDMMC1) || defined (DLYB_SDMMC2) || defined (DLYB_OCTOSPI1) || defined (DLYB_OCTOSPI2)

/**
  @cond 0
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DLYB_TIMEOUT 0xFFU
#define DLYB_LNG_10_0_MASK   0x07FF0000U
#define DLYB_LNG_11_10_MASK  0x0C000000U
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  @endcond
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup DLYB_LL_Exported_Functions
  *  @brief    Configuration and control functions
  *
@verbatim
 ===============================================================================
              ##### Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to
      (+) Control the DLYB.
@endverbatim
  * @{
  */

/** @addtogroup DLYB_Control_Functions DLYB Control functions
  * @{
  */
/**
  * @brief  Set Normal Speed mode for frequencies below 50 MHz.
  * @param  DLYBx: Pointer to a DLYB instance.
  * @param  pdlyb_cfg: Pointer to the DLYB configuration structure.
  * @retval uint32_t: An ErrorStatus enumeration value:
  *          - SUCCESS: Normal speed mode set successfully.
  *          - HAL_TIMEOUT: Failed to establish normal speed mode within timeout.
  */
uint32_t LL_DLYB_SetDelayNormalSpeed(DLYB_TypeDef *DLYBx, const LL_DLYB_CfgTypeDef *pdlyb_cfg)
{
  uint32_t tickstart;

  /* Check the DelayBlock instance */
  assert_param(IS_DLYB_ALL_INSTANCE(DLYBx));

  /* Disable the lock mode */
  CLEAR_BIT(DLYBx->CFG, DLYB_CFGR_SDMMC_DLL_EN);

  /* Wait until the lock is disabled */
  tickstart = HAL_GetTick();
  while ((DLYBx->STATUS & DLYB_STATUS_SDMMC_DLL_LOCK) == DLYB_STATUS_SDMMC_DLL_LOCK)
  {
    if ((HAL_GetTick() - tickstart) >= DLYB_TIMEOUT)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if ((DLYBx->STATUS & DLYB_STATUS_SDMMC_DLL_LOCK) == DLYB_STATUS_SDMMC_DLL_LOCK)
      {
        return (uint32_t) HAL_TIMEOUT;
      }
    }
  }
  /* Enable bypass mode */
  SET_BIT(DLYBx->CFG, DLYB_CFGR_SDMMC_DLL_BYP_EN);

  /* Enable anti-glitch logic */
  SET_BIT(DLYBx->CFG, DLYB_CFGR_SDMMC_DLL_ANTIGLITCH_EN);

  /* Set the value of the taps (a.k.a units) */
  MODIFY_REG(DLYBx->CFG, DLYB_CFGR_SDMMC_DLL_BYP_CMD_Msk, pdlyb_cfg->Units << DLYB_CFGR_SDMMC_DLL_BYP_CMD_Pos);

  /* Program RX delay tap selection (0 to 31) */
  MODIFY_REG(DLYBx->CFG, DLYB_CFGR_SDMMC_RX_TAP_SEL_Msk, pdlyb_cfg->PhaseSel << DLYB_CFGR_SDMMC_RX_TAP_SEL_Pos);

  /* Wait until RX delay line is configured with the delay selected by SDMMC_RX_TAP_SEL[5:0] */
  tickstart = HAL_GetTick();
  while ((DLYBx->STATUS & DLYB_STATUS_SDMMC_RX_TAP_SEL_ACK) != DLYB_STATUS_SDMMC_RX_TAP_SEL_ACK)
  {
    if ((HAL_GetTick() - tickstart) >= DLYB_TIMEOUT)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if ((DLYBx->STATUS & DLYB_STATUS_SDMMC_RX_TAP_SEL_ACK) != DLYB_STATUS_SDMMC_RX_TAP_SEL_ACK)
      {
        return (uint32_t) HAL_TIMEOUT;
      }
    }
  }

  return (uint32_t) SUCCESS;
}

/**
  * @brief  Set High Speed mode for frequencies higher than 50 MHz.
  * @param  DLYBx: Pointer to a DLYB instance.
  * @param  SDMMC_RX_TAP_SEL: RX delay tap selection value (0 to 31).
  * @retval uint32_t: An ErrorStatus enumeration value:
  *          - SUCCESS: High speed mode set successfully.
  *          - HAL_TIMEOUT: Failed to establish high speed mode within timeout.
  */
uint32_t LL_DLYB_SetDelayHighSpeed(DLYB_TypeDef *DLYBx, const uint32_t SDMMC_RX_TAP_SEL)
{
  uint32_t tickstart;

  /* Check the DelayBlock instance */
  assert_param(IS_DLYB_ALL_INSTANCE(DLYBx));

  /* Disable bypass mode */
  CLEAR_BIT(DLYBx->CFG, DLYB_CFGR_SDMMC_DLL_BYP_EN);

  /* Enable anti-glitch logic */
  SET_BIT(DLYBx->CFG, DLYB_CFGR_SDMMC_DLL_ANTIGLITCH_EN);

  /* Start lock sequence again */
  SET_BIT(DLYBx->CFG, DLYB_CFGR_SDMMC_DLL_EN);

  /* Program RX delay tap selection (0 to 31) */
  MODIFY_REG(DLYBx->CFG, DLYB_CFGR_SDMMC_RX_TAP_SEL_Msk, SDMMC_RX_TAP_SEL << DLYB_CFGR_SDMMC_RX_TAP_SEL_Pos);

  /* Wait until RX delay tap selection is acknowledged */
  tickstart = HAL_GetTick();
  while ((DLYBx->STATUS & DLYB_STATUS_SDMMC_RX_TAP_SEL_ACK) == 0U)
  {
    if ((HAL_GetTick() - tickstart) >= DLYB_TIMEOUT)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if ((DLYBx->STATUS & DLYB_STATUS_SDMMC_RX_TAP_SEL_ACK) == 0U)
      {
        return (uint32_t) HAL_TIMEOUT;
      }
    }
  }

  return (uint32_t) SUCCESS;
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
#endif /* DLYB_SDMMC1 || DLYB_SDMMC2 || DLYB_OCTOSPI1 || DLYB_OCTOSPI2 */
#endif /* HAL_SD_MODULE_ENABLED || HAL_OSPI_MODULE_ENABLED || HAL_XSPI_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
