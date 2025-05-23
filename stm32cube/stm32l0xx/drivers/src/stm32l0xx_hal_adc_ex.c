/**
  ******************************************************************************
  * @file    stm32l0xx_hal_adc_ex.c
  * @author  MCD Application Team
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Peripheral Control functions
  *          Other functions (generic functions) are available in file
  *          "stm32l0xx_hal_adc.c".
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  [..]
  (@) Sections "ADC peripheral features" and "How to use this driver" are
      available in file of generic functions "stm32l0xx_hal_adc.c".
  [..]
  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup ADCEx ADCEx
  * @brief ADC Extended HAL module driver
  * @{
  */

#ifdef HAL_ADC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup ADCEx_Private_Constants ADC Extended Private Constants
  * @{
  */

/* Fixed timeout values for ADC calibration, enable settling time, disable  */
/* settling time.                                                           */
/* Values defined to be higher than worst cases: low clock frequency,       */
/* maximum prescaler.                                                       */
/* Unit: ms                                                                 */
#define ADC_CALIBRATION_TIMEOUT      10U

/* Delay for VREFINT stabilization time. */
/* Internal reference startup time max value is 3ms  (refer to device datasheet, parameter TVREFINT). */
/* Unit: ms */
#define SYSCFG_BUF_VREFINT_ENABLE_TIMEOUT       (3U)

/* Delay for TEMPSENSOR stabilization time. */
/* Temperature sensor startup time max value is 10us  (refer to device datasheet, parameter tSTART). */
/* Unit: ms */
#define SYSCFG_BUF_TEMPSENSOR_ENABLE_TIMEOUT    (1U)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Functions ADC Extended Exported Functions
  * @{
  */

/** @defgroup ADCEx_Exported_Functions_Group1 Extended Input and Output operation functions
  * @brief    Extended IO operation functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Perform the ADC calibration.
@endverbatim
  * @{
  */

/**
  * @brief  Perform an ADC automatic self-calibration
  *         Calibration prerequisite: ADC must be disabled (execute this
  *         function before HAL_ADC_Start() or after HAL_ADC_Stop() ).
  * @note   Calibration factor can be read after calibration, using function
  *         HAL_ADC_GetValue() (value on 7 bits: from DR[6;0]).
  * @param  hadc       ADC handle
  * @param  SingleDiff Selection of single-ended or differential input
  *          This parameter can be only of the following values:
  *            @arg ADC_SINGLE_ENDED: Channel in mode input single ended
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef *hadc, uint32_t SingleDiff)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  uint32_t tickstart = 0U;
  uint32_t backup_setting_adc_dma_transfer = 0U; /* Note: Variable not declared as volatile because register read is already declared as volatile */

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Prevent unused argument(s) compilation warning */
  UNUSED(SingleDiff);

  /* Process locked */
  __HAL_LOCK(hadc);

  /* Calibration prerequisite: ADC must be disabled. */
  if (ADC_IS_ENABLE(hadc) == RESET)
  {
    /* Set ADC state */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_REG_BUSY,
                      HAL_ADC_STATE_BUSY_INTERNAL);

    /* Disable ADC DMA transfer request during calibration */
    /* Note: Specificity of this STM32 series: Calibration factor is           */
    /*       available in data register and also transferred by DMA.           */
    /*       To not insert ADC calibration factor among ADC conversion data   */
    /*       in array variable, DMA transfer must be disabled during          */
    /*       calibration.                                                     */
    backup_setting_adc_dma_transfer = READ_BIT(hadc->Instance->CFGR1, ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG);
    CLEAR_BIT(hadc->Instance->CFGR1, ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG);

    /* Start ADC calibration */
    hadc->Instance->CR |= ADC_CR_ADCAL;

    tickstart = HAL_GetTick();

    /* Wait for calibration completion */
    while (HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADCAL))
    {
      if ((HAL_GetTick() - tickstart) > ADC_CALIBRATION_TIMEOUT)
      {
        /* New check to avoid false timeout detection in case of preemption */
        if (HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADCAL))
        {
          /* Update ADC state machine to error */
          ADC_STATE_CLR_SET(hadc->State,
                            HAL_ADC_STATE_BUSY_INTERNAL,
                            HAL_ADC_STATE_ERROR_INTERNAL);

          /* Process unlocked */
          __HAL_UNLOCK(hadc);

          return HAL_ERROR;
        }
      }
    }

    /* Restore ADC DMA transfer request after calibration */
    SET_BIT(hadc->Instance->CFGR1, backup_setting_adc_dma_transfer);

    /* Set ADC state */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_BUSY_INTERNAL,
                      HAL_ADC_STATE_READY);
  }
  else
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);

    tmp_hal_status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Get the calibration factor.
  * @param  hadc ADC handle.
  * @param  SingleDiff This parameter can be only:
  *           @arg ADC_SINGLE_ENDED: Channel in mode input single ended.
  * @retval Calibration value.
  */
uint32_t HAL_ADCEx_Calibration_GetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_SINGLE_DIFFERENTIAL(SingleDiff));

  /* Prevent unused argument(s) compilation warning */
  UNUSED(SingleDiff);

  /* Return the ADC calibration value */
  return ((hadc->Instance->CALFACT) & 0x0000007FU);
}

/**
  * @brief  Set the calibration factor to overwrite automatic conversion result.
  *         ADC must be enabled and no conversion is ongoing.
  * @param  hadc ADC handle
  * @param  SingleDiff This parameter can be only:
  *           @arg ADC_SINGLE_ENDED: Channel in mode input single ended.
  * @param  CalibrationFactor Calibration factor (coded on 7 bits maximum)
  * @retval HAL state
  */
HAL_StatusTypeDef HAL_ADCEx_Calibration_SetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff, uint32_t CalibrationFactor)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_SINGLE_DIFFERENTIAL(SingleDiff));
  assert_param(IS_ADC_CALFACT(CalibrationFactor));

  /* Prevent unused argument(s) compilation warning */
  UNUSED(SingleDiff);

  /* Process locked */
  __HAL_LOCK(hadc);

  /* Verification of hardware constraints before modifying the calibration    */
  /* factors register: ADC must be enabled, no conversion on going.           */
  if ((ADC_IS_ENABLE(hadc) != RESET)                            &&
      (ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET))
  {
    /* Set the selected ADC calibration value */
    hadc->Instance->CALFACT &= ~ADC_CALFACT_CALFACT;
    hadc->Instance->CALFACT |= CalibrationFactor;
  }
  else
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
    /* Update ADC state machine to error */
    SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);

    /* Update ADC state machine to error */
    tmp_hal_status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);

  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Enables the buffer of Vrefint for the ADC, required when device is in mode low-power (low-power run, low-power sleep or stop mode)
  *         However ADC is not functional in low-power mode, therefore these functions is not targeted for ADC (obsolete)
  *         For more details on procedure and buffer current consumption, refer to device reference manual.
  * @note   This is functional only if the LOCK is not set.
  * @note   This API is obsolete. This equivalent configuration is done in HAL_ADC_ConfigChannel().
            bit fields in ADC_CCR and SYSCFG_CFGR3 control the same signals to VREFINT and TempSensor buffers
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_EnableVREFINT(void)
{
  uint32_t tickstart = 0U;

  /* Enable the Buffer for the ADC by setting ENBUF_SENSOR_ADC bit in the CFGR3 register */
  SET_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_ENBUF_VREFINT_ADC);

  /* Wait for Vrefint buffer effectively enabled */
  /* Get tick count */
  tickstart = HAL_GetTick();

  while (HAL_IS_BIT_CLR(SYSCFG->CFGR3, SYSCFG_CFGR3_VREFINT_RDYF))
  {
    if ((HAL_GetTick() - tickstart) > SYSCFG_BUF_VREFINT_ENABLE_TIMEOUT)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (HAL_IS_BIT_CLR(SYSCFG->CFGR3, SYSCFG_CFGR3_VREFINT_RDYF))
      {
        return HAL_ERROR;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Disables the Buffer Vrefint for the ADC.
  * @note This is functional only if the LOCK is not set.
  * @note This API is obsolete. This equivalent configuration is done in HAL_ADC_ConfigChannel().
          bit fields in ADC_CCR and SYSCFG_CFGR3 control the same signals to VREFINT and TempSensor buffers.
  * @retval None
  */
void HAL_ADCEx_DisableVREFINT(void)
{
  /* Disable the Vrefint by resetting ENBUF_SENSOR_ADC bit in the CFGR3 register */
  CLEAR_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_ENBUF_VREFINT_ADC);
}

/**
  * @brief  Enables the buffer of temperature sensor, when device is in mode low-power (low-power run, low-power sleep or stop mode)
  *         However ADC is not functional in low-power mode, therefore these functions is not targeted for ADC (obsolete)
  *         For more details on procedure and buffer current consumption, refer to device reference manual.
  * @note   This is functional only if the LOCK is not set.
  * @note   This API is obsolete. This equivalent configuration is done in HAL_ADC_ConfigChannel().
            bit fields in ADC_CCR and SYSCFG_CFGR3 control the same signals to VREFINT and TempSensor buffers
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_EnableVREFINTTempSensor(void)
{
  uint32_t tickstart = 0U;

  /* Enable the Buffer for the ADC by setting ENBUF_SENSOR_ADC bit in the CFGR3 register */
  SET_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_ENBUF_SENSOR_ADC);

  /* Wait for Vrefint buffer effectively enabled */
  /* Get tick count */
  tickstart = HAL_GetTick();

  while (HAL_IS_BIT_CLR(SYSCFG->CFGR3, SYSCFG_CFGR3_VREFINT_RDYF))
  {
    if ((HAL_GetTick() - tickstart) > SYSCFG_BUF_TEMPSENSOR_ENABLE_TIMEOUT)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (HAL_IS_BIT_CLR(SYSCFG->CFGR3, SYSCFG_CFGR3_VREFINT_RDYF))
      {
        return HAL_ERROR;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Disables the VREFINT and Sensor for the ADC.
  * @note This is functional only if the LOCK is not set.
  * @note This API is obsolete. This equivalent configuration is done in HAL_ADC_ConfigChannel().
          bit fields in ADC_CCR and SYSCFG_CFGR3 control the same signals to VREFINT and TempSensor buffers.
  * @retval None
  */
void HAL_ADCEx_DisableVREFINTTempSensor(void)
{
  /* Disable the Vrefint by resetting ENBUF_SENSOR_ADC bit in the CFGR3 register */
  CLEAR_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_ENBUF_SENSOR_ADC);
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
#endif /* HAL_ADC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

