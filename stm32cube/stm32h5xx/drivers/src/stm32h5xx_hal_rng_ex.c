/**
  ******************************************************************************
  * @file    stm32h5xx_hal_rng_ex.c
  * @author  MCD Application Team
  * @brief   Extended RNG HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Random Number Generator (RNG) peripheral:
  *           + Lock configuration functions
  *           + Reset the RNG
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
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

#if defined(RNG)

/** @addtogroup RNGEx
  * @brief RNG Extended HAL module driver.
  * @{
  */

#ifdef HAL_RNG_MODULE_ENABLED
#if defined(RNG_CR_CONDRST)
/* Private types -------------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup RNGEx_Private_Constants
  * @{
  */
#define RNG_TIMEOUT_VALUE     2U
/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/* Private functions prototypes ----------------------------------------------*/
/* Private functions  --------------------------------------------------------*/
#if (defined(RNG_HTSR0_RPERRX) || defined(RNG_HTSR1_ADERRX))
HAL_StatusTypeDef RNG_ResilientRecoverSeedError(RNG_HandleTypeDef *hrng);
#endif /* RNG_HTSR0_RPERRX || RNG_HTSR1_ADERRX */
/* Exported functions --------------------------------------------------------*/

/** @defgroup RNGEx_Exported_Functions RNGEx Exported Functions
  * @{
  */

/** @defgroup RNGEx_Exported_Functions_Group1 Configuration and lock functions
  *  @brief   Configuration functions
  *
@verbatim
 ===============================================================================
          ##### Configuration and lock functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the RNG with the specified parameters in the RNG_ConfigTypeDef
      (+) Lock RNG configuration Allows user to lock a configuration until next reset.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the RNG with the specified parameters in the
  *         RNG_ConfigTypeDef.
  * @param  hrng pointer to a RNG_HandleTypeDef structure that contains
  *          the configuration information for RNG.
  * @param  pConf pointer to a RNG_ConfigTypeDef structure that contains
  *         the configuration information for RNG module

  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RNGEx_SetConfig(RNG_HandleTypeDef *hrng, const RNG_ConfigTypeDef *pConf)
{
  uint32_t tickstart;
  uint32_t cr_value;
  HAL_StatusTypeDef status ;

  /* Check the RNG handle allocation */
  if ((hrng == NULL) || (pConf == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RNG_ALL_INSTANCE(hrng->Instance));
  assert_param(IS_RNG_CLOCK_DIVIDER(pConf->ClockDivider));
  assert_param(IS_RNG_NIST_COMPLIANCE(pConf->NistCompliance));
  assert_param(IS_RNG_CONFIG1(pConf->Config1));
  assert_param(IS_RNG_CONFIG2(pConf->Config2));
  assert_param(IS_RNG_CONFIG3(pConf->Config3));
  assert_param(IS_RNG_ARDIS(pConf->AutoReset));

  /* Check RNG peripheral state */
  if (hrng->State == HAL_RNG_STATE_READY)
  {
    /* Change RNG peripheral state */
    hrng->State = HAL_RNG_STATE_BUSY;

    /* Disable RNG */
    __HAL_RNG_DISABLE(hrng);

    /* RNG CR register configuration. Set value in CR register for :
        - NIST Compliance setting
        - Clock divider value
        - Automatic reset to clear SECS bit
        - CONFIG 1, CONFIG 2 and CONFIG 3 values */
    cr_value = (uint32_t)(pConf->ClockDivider | pConf->NistCompliance | pConf->AutoReset
                          | (pConf->Config1 << RNG_CR_RNG_CONFIG1_Pos)
                          | (pConf->Config2 << RNG_CR_RNG_CONFIG2_Pos)
                          | (pConf->Config3 << RNG_CR_RNG_CONFIG3_Pos));

    MODIFY_REG(hrng->Instance->CR, RNG_CR_NISTC | RNG_CR_CLKDIV | RNG_CR_RNG_CONFIG1
               | RNG_CR_RNG_CONFIG2 | RNG_CR_RNG_CONFIG3 | RNG_CR_ARDIS,
               (uint32_t)(RNG_CR_CONDRST | cr_value));

    /* RNG health test control in accordance with NIST */
#if defined(RNG_HTCR3_HTCFG)
    WRITE_REG(hrng->Instance->HTCR[0], pConf->HealthTest);
#else
    WRITE_REG(hrng->Instance->HTCR, pConf->HealthTest);
#endif  /* RNG_HTCR0_HTCFG || RNG_HTCR1_HTCFG || RNG_HTCR2_HTCFG || RNG_HTCR3_HTCFG */

    /* Writing bit CONDRST=0*/
    CLEAR_BIT(hrng->Instance->CR, RNG_CR_CONDRST);
    /* Get tick */
    tickstart = HAL_GetTick();

    /* Wait for conditioning reset process to be completed */
    while (HAL_IS_BIT_SET(hrng->Instance->CR, RNG_CR_CONDRST))
    {
      if ((HAL_GetTick() - tickstart) > RNG_TIMEOUT_VALUE)
      {
        /* New check to avoid false timeout detection in case of prememption */
        if (HAL_IS_BIT_SET(hrng->Instance->CR, RNG_CR_CONDRST))
        {
          hrng->State = HAL_RNG_STATE_READY;
          hrng->ErrorCode = HAL_RNG_ERROR_TIMEOUT;
          return HAL_ERROR;
        }
      }
    }

    /* Enable RNG */
    __HAL_RNG_ENABLE(hrng);

    /* Initialize the RNG state */
    hrng->State = HAL_RNG_STATE_READY;

    /*Check if seed error current status (SECS)is set */
    if (__HAL_RNG_GET_FLAG(hrng, RNG_SR_SECS) != RESET)
    {
      /* Update the error code */
      hrng->ErrorCode = HAL_RNG_ERROR_SEED;
      return HAL_ERROR;
    }

    /* function status */
    status = HAL_OK;
  }
  else
  {
    hrng->ErrorCode = HAL_RNG_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Return the function status */
  return status;
}

/**
  * @brief  Get the RNG Configuration and fill parameters in the
  *         RNG_ConfigTypeDef.
  * @param  hrng pointer to a RNG_HandleTypeDef structure that contains
  *          the configuration information for RNG.
  * @param  pConf pointer to a RNG_ConfigTypeDef structure that contains
  *         the configuration information for RNG module

  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RNGEx_GetConfig(RNG_HandleTypeDef *hrng, RNG_ConfigTypeDef *pConf)
{

  HAL_StatusTypeDef status ;

  /* Check the RNG handle allocation */
  if ((hrng == NULL) || (pConf == NULL))
  {
    return HAL_ERROR;
  }

  /* Check RNG peripheral state */
  if (hrng->State == HAL_RNG_STATE_READY)
  {
    /* Change RNG peripheral state */
    hrng->State = HAL_RNG_STATE_BUSY;

    /* Get  RNG parameters  */
    pConf->Config1        = (uint32_t)((hrng->Instance->CR & RNG_CR_RNG_CONFIG1) >> RNG_CR_RNG_CONFIG1_Pos) ;
    pConf->Config2        = (uint32_t)((hrng->Instance->CR & RNG_CR_RNG_CONFIG2) >> RNG_CR_RNG_CONFIG2_Pos);
    pConf->Config3        = (uint32_t)((hrng->Instance->CR & RNG_CR_RNG_CONFIG3) >> RNG_CR_RNG_CONFIG3_Pos);
    pConf->ClockDivider   = (hrng->Instance->CR & RNG_CR_CLKDIV);
    pConf->NistCompliance = (hrng->Instance->CR & RNG_CR_NISTC);
    pConf->AutoReset      = (hrng->Instance->CR & RNG_CR_ARDIS);
#if defined(RNG_HTCR3_HTCFG)
    pConf->HealthTest     = (hrng->Instance->HTCR[0]);
#else
    pConf->HealthTest     = (hrng->Instance->HTCR);
#endif  /* RNG_HTCR0_HTCFG || RNG_HTCR1_HTCFG || RNG_HTCR2_HTCFG || RNG_HTCR3_HTCFG */

    /* Initialize the RNG state */
    hrng->State = HAL_RNG_STATE_READY;

    /* function status */
    status = HAL_OK;
  }
  else
  {
    hrng->ErrorCode |= HAL_RNG_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Return the function status */
  return status;
}

/**
  * @brief  RNG current configuration lock.
  * @note   This function allows to lock RNG peripheral configuration.
  *         Once locked, HW RNG reset has to be performed prior any further
  *         configuration update.
  * @param  hrng pointer to a RNG_HandleTypeDef structure that contains
  *                the configuration information for RNG.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RNGEx_LockConfig(RNG_HandleTypeDef *hrng)
{
  HAL_StatusTypeDef status;

  /* Check the RNG handle allocation */
  if (hrng == NULL)
  {
    return HAL_ERROR;
  }

  /* Check RNG peripheral state */
  if (hrng->State == HAL_RNG_STATE_READY)
  {
    /* Change RNG peripheral state */
    hrng->State = HAL_RNG_STATE_BUSY;

    /* Perform RNG configuration Lock */
    MODIFY_REG(hrng->Instance->CR, RNG_CR_CONFIGLOCK, RNG_CR_CONFIGLOCK);

    /* Change RNG peripheral state */
    hrng->State = HAL_RNG_STATE_READY;

    /* function status */
    status = HAL_OK;
  }
  else
  {
    hrng->ErrorCode = HAL_RNG_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Return the function status */
  return status;
}


/**
  * @}
  */

/** @defgroup RNGEx_Exported_Functions_Group2 Recover from seed error function
  *  @brief   Recover from seed error function
  *
@verbatim
 ===============================================================================
          ##### Recover from seed error function #####
 ===============================================================================
    [..]  This section provide function allowing to:
      (+) Recover from a seed error

@endverbatim
  * @{
  */

/**
  * @brief  RNG sequence to recover from a seed error
  * @param  hrng: pointer to a RNG_HandleTypeDef structure.
  * @warning Recover from seed error will adapt the parameters config1,2,3 to overcome seed error.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RNGEx_RecoverSeedError(RNG_HandleTypeDef *hrng)
{
  HAL_StatusTypeDef status;
  HAL_RNG_StateTypeDef state;

  /* Check the RNG handle allocation */
  if (hrng == NULL)
  {
    return HAL_ERROR;
  }

  state = hrng->State;

  /* Check RNG peripheral state */
  if ((state == HAL_RNG_STATE_READY) || (state == HAL_RNG_STATE_ERROR))
  {
    /* Change RNG peripheral state */
    hrng->State = HAL_RNG_STATE_BUSY;

    /* sequence to fully recover from a seed error */
#if (defined(RNG_HTSR0_RPERRX) || defined(RNG_HTSR1_ADERRX))
    status = RNG_ResilientRecoverSeedError(hrng);
#else
    status = RNG_RecoverSeedError(hrng);
#endif /* RNG_HTSR0_RPERRX || RNG_HTSR1_ADERRX) */
    if (status == HAL_ERROR)
    {
      /* Update the error code */
      hrng->ErrorCode = HAL_RNG_ERROR_RECOVERSEED;
    }
  }
  else
  {
    hrng->ErrorCode = HAL_RNG_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Return the function status */
  return status;
}

#if defined(RNG_HTCR3_HTCFG)
/**
  * @brief  Configure the RNG additional health tests.
  * @param  hrng              hrng pointer to a RNG_HandleTypeDef structure that contains
  *                           the configuration information for RNG.
  * @param  htcr_idx          is a value of the  htcr.
  * @param  htcr_value        Health test value.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_ERROR         configuration fail.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
HAL_StatusTypeDef   HAL_RNGEx_SetHealthFactorConfig(RNG_HandleTypeDef *hrng, uint32_t htcr_idx, uint32_t htcr_value)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint32_t tickstart;

  assert_param(IS_RNG_HTCR_INDEX(htcr_idx));
  assert_param(IS_RNG_HTCR_VALUE(htcr_value));

  /* Check the RNG handle allocation */
  if (hrng == NULL)
  {
    return HAL_ERROR;
  }

  /* Check RNG peripheral state */
  if (hrng->State == HAL_RNG_STATE_READY)
  {
    /* Change RNG peripheral state */
    hrng->State = HAL_RNG_STATE_BUSY;

    if (LL_RNG_IsConfigLocked(hrng->Instance) == 0U)
    {
      LL_RNG_EnableCondReset(hrng->Instance);
      LL_RNG_SetAdditionalHealthTest(hrng->Instance, htcr_idx, htcr_value);
      LL_RNG_DisableCondReset(hrng->Instance);

      /* Get tick */
      tickstart = HAL_GetTick();

      /* Wait for conditioning reset process to be completed */
      while (HAL_IS_BIT_SET(hrng->Instance->CR, RNG_CR_CONDRST))
      {
        if ((HAL_GetTick() - tickstart) > RNG_TIMEOUT_VALUE)
        {
          /* New check to avoid false timeout detection in case of prememption */
          if (HAL_IS_BIT_SET(hrng->Instance->CR, RNG_CR_CONDRST))
          {
            hrng->State = HAL_RNG_STATE_READY;
            hrng->ErrorCode = HAL_RNG_ERROR_TIMEOUT;
            return HAL_ERROR;
          }
        }
      }
    }

    /* Change RNG peripheral state */
    hrng->State = HAL_RNG_STATE_READY;

    /* function status */
    status = HAL_OK;
  }
  else
  {
    hrng->ErrorCode = HAL_RNG_ERROR_BUSY;
    status = HAL_ERROR;
  }

  return status;
}
#endif /* defined(RNG_HTCR0_HTCFG || RNG_HTCR1_HTCFG || RNG_HTCR2_HTCFG) */
/**
  * @}
  */

/**
  * @}
  */

#if (defined(RNG_HTSR0_RPERRX) || defined(RNG_HTSR1_ADERRX))
/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup RNGEx_Private_Functions RNGEx Private Functions
  * @brief    RNGEx Private Functions
  * @{
  */

/**
  * @brief  RNG sequence to resilient recover from a seed error
  * @param  hrng pointer to a RNG_HandleTypeDef structure.
  * @retval HAL status
  */
HAL_StatusTypeDef RNG_ResilientRecoverSeedError(RNG_HandleTypeDef *hrng)
{
  uint32_t timeout;
  uint32_t htsr_temp = 0U;
  uint32_t htsr_previous_temp = 0U;
  uint32_t htsr_count = 0U;
  uint32_t nsmr_temp = 0U;
  uint32_t tickstart1 = 0U;
  uint32_t tickstart2 = 0U;
  uint32_t tickstart3 = 0U;
  uint32_t oscillators_count = 0U;
  uint32_t config_b_fewer_than_6_osc_count = 0U;
  uint8_t count = 0U;

  /* timeout here is an emperic value */
  timeout = (1UL + ((1UL << (READ_BIT(hrng->Instance->CR, RNG_CR_CLKDIV) >> 16UL)) * RNG_TIMEOUT_VALUE / 8UL));
  LL_RNG_Enable(hrng->Instance);

  tickstart1 = HAL_GetTick();

  /* Check if seed error current status indicates no error and auto-reset succeeded */
  if (LL_RNG_IsActiveFlag_SECS(hrng->Instance) == 0U)
  {
    /* Clear SEIS flag when automatic reset is activated */
    LL_RNG_ClearFlag_SEIS(hrng->Instance);
  }

  else  /* Sequence to fully recover from a seed error*/
  {
    if (LL_RNG_IsConfigLocked(hrng->Instance) == 0U)
    {
      do
      {
        if (LL_RNG_IsActiveFlag_SECS(hrng->Instance) == 0U)
        {
          break;
        }
        /* Read oscillator status registers combined */
        htsr_temp = LL_RNG_GetHealthTestStatus(hrng->Instance, 0U);
        htsr_temp |= LL_RNG_GetHealthTestStatus(hrng->Instance, 1U);
        if (htsr_temp > 0U)
        {
          /* If any oscillator status bits overlap with previous status, increment counter */
          if ((htsr_temp & htsr_previous_temp) != 0U)
          {
            htsr_count++;
          }

          if (htsr_count > 3U)
          {
            /* if the same repetitive or adaptative error is detected 3 times */
            nsmr_temp = LL_RNG_GetNoiseSourceMask(hrng->Instance);

            /* deactivate the same osc in each triple oscillator (Mask oscillators with the seed error by
            clearing bits shifted right by 1) */
            nsmr_temp = nsmr_temp & ~(htsr_temp >> 1U);

            /* Count the number of active oscillators in nsmr */
            oscillators_count = 0U;
            for (count = 0U; count < 9U; count++)
            {
              if (((nsmr_temp >> count) & 0x1U) != 0U)
              {
                /* increment count1 for each 1 in nsmr */
                oscillators_count++;
              }
            }

            if (oscillators_count < 6U)
            {
              /* If fewer than 6 oscillators remain active, unmask all oscillators --> Reset masking */
              nsmr_temp = LL_RNG_GetOscNoiseSrc(hrng->Instance, LL_RNG_NOISE_SRC_1 | LL_RNG_NOISE_SRC_2 \
                                                | LL_RNG_NOISE_SRC_3);
              htsr_previous_temp = 0;
              htsr_count = 0U;
              if ((hrng->Instance->CR  & RNG_CR_CLKDIV_Msk) < ((uint32_t)RNG_CAND_NIST_CR_VALUE & RNG_CR_CLKDIV_Msk))
              {
                config_b_fewer_than_6_osc_count++;
              }
            }

            if (config_b_fewer_than_6_osc_count > 2U)
            {
              /* Reset RNG condition */
              WRITE_REG(hrng->Instance->CR, (RNG_CR_CONDRST_Msk | (uint32_t)RNG_CAND_NIST_CR_VALUE));

              /* Update mask register with new oscillator mask */
              LL_RNG_SetNoiseSourceMask(hrng->Instance, nsmr_temp);

              /* Clear condition reset bit to resume operation */
              LL_RNG_DisableCondReset(hrng->Instance);
            }

            else
            {
              /* Reset RNG condition */
              WRITE_REG(hrng->Instance->CR, (hrng->Instance->CR & ~RNG_CR_RNGEN_Msk) | RNG_CR_CONDRST_Msk);

              /* Update mask register with new oscillator mask */
              LL_RNG_SetNoiseSourceMask(hrng->Instance, nsmr_temp);

              /* Clear condition reset bit to resume operation */
              LL_RNG_DisableCondReset(hrng->Instance);
            }
          }

          else
          {
            /* Briefly toggle conditional reset to recover RNG */
            WRITE_REG(hrng->Instance->CR, (hrng->Instance->CR & ~RNG_CR_RNGEN_Msk) | RNG_CR_CONDRST_Msk);

            /* unmask all oscillators to find another working condition */
            LL_RNG_SetNoiseSourceMask(hrng->Instance, LL_RNG_GetOscNoiseSrc(hrng->Instance, LL_RNG_OSC_1\
                                                                            | LL_RNG_OSC_2 | LL_RNG_OSC_3));
            LL_RNG_DisableCondReset(hrng->Instance);
          }

          /* Wait until RNG is not busy */
          tickstart2 = HAL_GetTick();
          do
          {
            if ((HAL_GetTick() - tickstart2) > RNG_TIMEOUT_VALUE)
            {
              /* New check to avoid false timeout detection in case of preemption */
              LL_RNG_Disable(hrng->Instance);
              hrng->State = HAL_RNG_STATE_ERROR;
              __HAL_UNLOCK(hrng);
              return HAL_ERROR;
            }
          } while (HAL_IS_BIT_SET(hrng->Instance->SR, RNG_SR_BUSY));

          /* No timeout --> Enable RNG */
          LL_RNG_Enable(hrng->Instance);
          tickstart3 = HAL_GetTick();
          do
          {
            if (LL_RNG_IsActiveFlag_DRDY(hrng->Instance) != 0UL)
            {
              break;
            }
            if ((HAL_GetTick() - tickstart3) > timeout)
            {
              /* New check to avoid false timeout detection in case of preemption */
              if (LL_RNG_IsActiveFlag_DRDY(hrng->Instance) == 0UL)
              {
                if (LL_RNG_IsActiveFlag_SECS(hrng->Instance) == 0UL)
                {
                  LL_RNG_Disable(hrng->Instance);
                  hrng->State = HAL_RNG_STATE_ERROR;
                  __HAL_UNLOCK(hrng);
                  return HAL_ERROR;
                }
              }
            }
          } while (LL_RNG_IsActiveFlag_SECS(hrng->Instance) == 0UL);

          /* Accumulate seed error status bits */
          htsr_previous_temp = htsr_previous_temp | htsr_temp;
        }
      } while ((HAL_GetTick() - tickstart1) <= timeout);
    }
  }

  /*Check if seed error current status (SECS)is set */
  if (LL_RNG_IsActiveFlag_SECS(hrng->Instance) != 0U)
  {
    hrng->ErrorCode &= HAL_RNG_ERROR_SEED;
    __HAL_UNLOCK(hrng);
    return HAL_ERROR;
  }

  /* Update the error code */
  hrng->ErrorCode &= ~ HAL_RNG_ERROR_SEED;

  /* Return the function status */
  hrng->State = HAL_RNG_STATE_READY;
  __HAL_UNLOCK(hrng);
  return HAL_OK;
}

/**
  * @}
  */
#endif /* RNG_HTSR0_RPERRX || RNG_HTSR1_ADERRX */
#endif /* RNG_CR_CONDRST */
#endif /* HAL_RNG_MODULE_ENABLED */
/**
  * @}
  */

#endif /* RNG */

/**
  * @}
  */
