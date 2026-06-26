/**
  ******************************************************************************
  * @file    stm32g5xx_hal_vrefbuf.c
  * @brief   VREFBUF HAL module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

#if defined (VREFBUF)
#if defined (USE_HAL_VREFBUF_MODULE) && (USE_HAL_VREFBUF_MODULE == 1)

/** @addtogroup VREFBUF
  * @{
  */

/** @defgroup VREFBUF_Introduction VREFBUF Introduction
  * @{
  - The VREFBUF (voltage reference buffer) hardware abstraction layer provides a set of APIs to interface with the
    STM32 voltage reference buffer peripheral.
  - It simplifies the configuration, initialization, and management of the internal reference voltage.
  - This abstraction layer ensures portability and ease of use across different STM32 series.

  The HAL VREFBUF driver includes the following features:
  - Selectable output voltage levels
  - Provides a stable voltage reference for on-chip peripherals (ADC, DAC) and can be used as an external reference
    via the VREF+ pin

  */

/**
  * @}
  */

/** @defgroup VREFBUF_How_To_Use VREFBUF How To Use
  * @{

VREFBUF : module in STM32 microcontrollers that provides a reference voltage to both the internal
analog peripherals and external pins used in applications.

# Main features
  VREFBUF is a programmable gain operational amplifier that is composed of:
  - Input  VREFBUF : VREFINT (internal reference voltage in STM32 created from a diode-based circuit).
  - Output VREFBUF : Voltage reference buffer which can be used as voltage reference for internal peripherals
(ADCs, DACs) and for external components.
  - Power supply: VDDA (pin connected to an external power source) and VSSA (pin connected to ground).


# How to use the HAL VREFBUF
Before enabling VREFBUF, several key settings must be configured.

- HAL_RCC_VREFBUF_EnableClock(): The user must first enable the RCC Clock to access VREFBUF registers.
- HAL_VREFBUF_SetConfig(): The user must configure the VREFBUF by setting the voltage scale and
  functional mode of the VREFBUF.


If the user wants to change the VREFBUF's parameters during application runtime,
two distinct functions are available for this purpose :

- HAL_VREFBUF_SetVoltageScale() to modify the voltage scale of VREFBUF.
- HAL_VREFBUF_SetMode() to modify the functional mode of VREFBUF.

VREFBUF can be configured in various modes based on the configuration of each of the voltage reference
buffer mode and the high impedance mode.


- HAL_VREFBUF_SetTrimming() : It provides the user with the option to modify the trimming value of VREFBUF
 (for more detailed information, refer to the function description).
  */

/**
  * @}
  */

/** @defgroup VREFBUF_Configuration_Table VREFBUF Configuration Table
  * @{

# Configuration inside the VREFBUF:

  Config defines                | Description           | Default value | Note                                     |
--------------------------------| ----------------------| ------------- | ------------------------------------------
USE_HAL_VREFBUF_MODULE          | from hal_conf.h       | 1 | When set, HAL VREFBUF module is enabled
USE_HAL_CHECK_PARAM             | from hal_conf.h       | 0  | Parameters (pointers or sizes) are checked in runtime
USE_ASSERT_DBG_PARAM            | from PreProcessor env | None | When defined, enable the params assert
  */

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup VREFBUF_Private_Constants VREFBUF Private Constants
  * @{
  */

/*! Timeout value of VREFBUF output voltage reaching expected value (unit: ms). Refer to datasheet parameter tSTART */
#define VREFBUF_TIMEOUT_VALUE          (1U)

/**
  * @}
  */

/* Private macros -------------------------------------------------------------*/
/** @defgroup VREFBUF_Private_Macros VREFBUF Private Macros
  * @{
  */

/**
  * @brief Macro to check VREFBUF voltage scale validity.
  */
#define IS_VREFBUF_VOLTAGE_SCALE(voltagescale) (((voltagescale) == HAL_VREFBUF_VOLTAGE_2_9V)      \
                                                || ((voltagescale) == HAL_VREFBUF_VOLTAGE_2_5V)   \
                                                || ((voltagescale) == HAL_VREFBUF_VOLTAGE_2_048V) \
                                                || ((voltagescale) == HAL_VREFBUF_VOLTAGE_1_8V))

/**
  * @brief Macro to check VREFBUF mode validity.
  */
#define IS_VREFBUF_MODE(mode)  (((mode) == HAL_VREFBUF_MODE_PULL_DOWN)         \
                                ||((mode) == HAL_VREFBUF_MODE_EXT_VOLTAGE_REF) \
                                ||((mode) == HAL_VREFBUF_MODE_INT_VOLTAGE_REF) \
                                ||((mode) == HAL_VREFBUF_MODE_HOLD))

/**
  * @brief Macro to check VREFBUF trimming value.
  */
#define IS_VREFBUF_TRIMMING(trimmingvalue)  ((trimmingvalue) <= 63U)

/**
  * @brief Macro to get the instance.
  */
#define VREFBUF_GET_INSTANCE(instance)  ((VREFBUF_TypeDef *)((uint32_t)(instance)))

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Return the HAL VREFBUF instance.
  * @param  instance VREFBUF instance.
  * @retval hal_vrefbuf_t HAL VREFBUF instance.
  */
hal_vrefbuf_t HAL_VREFBUF_GetInstance(hal_vrefbuf_t instance)
{
  ASSERT_DBG_PARAM(IS_VREFBUF_ALL_INSTANCE(VREFBUF_GET_INSTANCE(instance)));

  return instance;
}

/**
  * @brief  Return the CMSIS/LL VREFBUF instance.
  * @param  instance VREFBUF instance.
  * @retval VREFBUF_TypeDef CMSIS/LL VREFBUF instance.
  */
VREFBUF_TypeDef *HAL_VREFBUF_GetLLInstance(hal_vrefbuf_t instance)
{
  ASSERT_DBG_PARAM(IS_VREFBUF_ALL_INSTANCE(VREFBUF_GET_INSTANCE(instance)));

  return VREFBUF_GET_INSTANCE(instance);
}

/** @addtogroup VREFBUF_Exported_Functions
  * @{
  */
/** @addtogroup VREFBUF_Exported_Functions_Group1
  * @{
  This subsection provides a set of functions allowing to configure and start the VREFBUF peripheral:
  - Call the function HAL_VREFBUF_SetConfig() to set the different fields needed before starting the VREFBUF.
  - Call the function HAL_VREFBUF_GetConfig() to retrieve the configuration.
  - Call the function HAL_VREFBUF_SetMode() to set the functional mode of VREFBUF.
  - Call the function HAL_VREFBUF_GetMode() to retrieve the functional mode of VREFBUF.
  - Call the function HAL_VREFBUF_SetVoltageScale() to set the voltage scale of VREFBUF.
  - Call the function HAL_VREFBUF_GetVoltageScale() to retrieve the voltage scale of VREFBUF.
  */

/**
  * @brief  Configure the VREFBUF (mode and voltage scale).
  * @param  instance VREFBUF instance.
  * @param  p_config Pointer to a @ref hal_vrefbuf_config_t structure that contains the VREFBUF configuration.
  * @retval HAL_OK VREFBUF instance has been correctly configured.
  * @retval HAL_INVALID_PARAM When the p_config pointer is NULL.
  * @retval HAL_ERROR HAL operation completed with error.
  */
hal_status_t HAL_VREFBUF_SetConfig(hal_vrefbuf_t instance, const hal_vrefbuf_config_t *p_config)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(p_config != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_VREFBUF_ALL_INSTANCE(VREFBUF_GET_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_VREFBUF_MODE(p_config->mode));

#if defined(USE_ASSERT_DBG_PARAM)
  if (p_config->mode == HAL_VREFBUF_MODE_INT_VOLTAGE_REF)
  {
    ASSERT_DBG_PARAM(IS_VREFBUF_VOLTAGE_SCALE(p_config->voltage_scale));
  }
#endif /* USE_ASSERT_DBG_PARAM */

  /* Configure VREFBUF */
  if (p_config->mode == HAL_VREFBUF_MODE_INT_VOLTAGE_REF)
  {
    LL_VREFBUF_SetVoltageScale(VREFBUF_GET_INSTANCE(instance), (uint32_t)p_config->voltage_scale);
  }

  LL_VREFBUF_SetMode(VREFBUF_GET_INSTANCE(instance), (uint32_t)p_config->mode);

  tickstart = HAL_GetTick();

  /* VRR detection is only possible when VREFBUF mode is set to the INTERNAL VOLTAGE REFERENCE */
  if (p_config->mode == HAL_VREFBUF_MODE_INT_VOLTAGE_REF)
  {
    /* Wait for VRR bit */
    while (LL_VREFBUF_IsVREFReady(VREFBUF_GET_INSTANCE(instance)) == 0UL)
    {
      if ((HAL_GetTick() - tickstart) > VREFBUF_TIMEOUT_VALUE)
      {
        if (LL_VREFBUF_IsVREFReady(VREFBUF_GET_INSTANCE(instance)) == 0UL)
        {
          return HAL_ERROR;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Get the configuration of VREFBUF (functional mode and voltage scale).
  * @param  instance VREFBUF instance.
  * @param  p_config Pointer to a @ref hal_vrefbuf_config_t structure that contains the VREFBUF configuration.
  */
void  HAL_VREFBUF_GetConfig(hal_vrefbuf_t instance, hal_vrefbuf_config_t *p_config)
{
  ASSERT_DBG_PARAM(IS_VREFBUF_ALL_INSTANCE(VREFBUF_GET_INSTANCE(instance)));
  ASSERT_DBG_PARAM(p_config != NULL);

  p_config->voltage_scale = (hal_vrefbuf_voltage_scale_t)LL_VREFBUF_GetVoltageScale(VREFBUF_GET_INSTANCE(instance));
  p_config->mode  = (hal_vrefbuf_mode_t)LL_VREFBUF_GetMode(VREFBUF_GET_INSTANCE(instance));
}

/**
  * @brief  Set the functional mode of VREFBUF.
  * @param  instance VREFBUF instance.
  * @param  mode This parameter indicates the mode of VREFBUF @ref hal_vrefbuf_mode_t enumeration.
  * @retval HAL_OK VREFBUF mode has been correctly configured.
  * @retval HAL_ERROR HAL operation completed with error.
  */
hal_status_t  HAL_VREFBUF_SetMode(hal_vrefbuf_t instance, hal_vrefbuf_mode_t mode)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(IS_VREFBUF_ALL_INSTANCE(VREFBUF_GET_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_VREFBUF_MODE(mode));

  LL_VREFBUF_SetMode(VREFBUF_GET_INSTANCE(instance), (uint32_t)mode);

  tickstart = HAL_GetTick();

  /* VRR detection is only possible when VREFBUF mode is set to the INTERNAL VOLTAGE REFERENCE */
  if (mode == HAL_VREFBUF_MODE_INT_VOLTAGE_REF)
  {
    /* Wait for VRR bit */
    while (LL_VREFBUF_IsVREFReady(VREFBUF_GET_INSTANCE(instance)) == 0UL)
    {
      if ((HAL_GetTick() - tickstart) > VREFBUF_TIMEOUT_VALUE)
      {
        if (LL_VREFBUF_IsVREFReady(VREFBUF_GET_INSTANCE(instance)) == 0UL)
        {
          return HAL_ERROR;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Get the functional mode of VREFBUF.
  * @param  instance VREFBUF instance.
  * @retval Value of type @ref hal_vrefbuf_mode_t.
  */
hal_vrefbuf_mode_t  HAL_VREFBUF_GetMode(hal_vrefbuf_t instance)
{
  ASSERT_DBG_PARAM(IS_VREFBUF_ALL_INSTANCE(VREFBUF_GET_INSTANCE(instance)));

  return (hal_vrefbuf_mode_t) LL_VREFBUF_GetMode(VREFBUF_GET_INSTANCE(instance));
}

/**
  * @brief  Set the voltage scale of VREFBUF.
  * @param  instance VREFBUF instance.
  * @param  voltage_scale This parameter indicates the voltage scale of VREFBUF @ref hal_vrefbuf_voltage_scale_t
  *         enumeration.
  * @retval HAL_OK VREFBUF voltage scale has been correctly configured.
  * @retval HAL_ERROR HAL operation completed with error.
  */
hal_status_t  HAL_VREFBUF_SetVoltageScale(hal_vrefbuf_t instance, hal_vrefbuf_voltage_scale_t voltage_scale)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(IS_VREFBUF_ALL_INSTANCE(VREFBUF_GET_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_VREFBUF_VOLTAGE_SCALE(voltage_scale));

  LL_VREFBUF_SetVoltageScale(VREFBUF_GET_INSTANCE(instance), (uint32_t)voltage_scale);

  tickstart = HAL_GetTick();

  /* VRR detection is only possible when VREFBUF mode is set to the INTERNAL VOLTAGE REFERENCE */
  if (LL_VREFBUF_GetMode(VREFBUF_GET_INSTANCE(instance)) == LL_VREFBUF_MODE_INT_VOLTAGE_REF)
  {
    /* Wait for VRR bit */
    while (LL_VREFBUF_IsVREFReady(VREFBUF_GET_INSTANCE(instance)) == 0UL)
    {
      if ((HAL_GetTick() - tickstart) > VREFBUF_TIMEOUT_VALUE)
      {
        if (LL_VREFBUF_IsVREFReady(VREFBUF_GET_INSTANCE(instance)) == 0UL)
        {
          return HAL_ERROR;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Get the voltage scale of VREFBUF.
  * @param  instance VREFBUF instance.
  * @retval Value of type @ref hal_vrefbuf_voltage_scale_t.
  */
hal_vrefbuf_voltage_scale_t  HAL_VREFBUF_GetVoltageScale(hal_vrefbuf_t instance)
{
  ASSERT_DBG_PARAM(IS_VREFBUF_ALL_INSTANCE(VREFBUF_GET_INSTANCE(instance)));

  return (hal_vrefbuf_voltage_scale_t) LL_VREFBUF_GetVoltageScale(VREFBUF_GET_INSTANCE(instance));
}

/**
  * @}
  */

/** @addtogroup VREFBUF_Exported_Functions_Group2
  * @{
  This subsection provides a set of functions that allow the user to configure advanced functions in VREFBUF,
  giving the user greater control over the operation of the driver.
  - Call the function HAL_VREFBUF_SetTrimming() to set the trimming value.
  - Call the function HAL_VREFBUF_GetTrimming() to retrieve the trimming value.
  */

/**
  * @brief  Set the trimming value of VREFBUF.
  * @param  instance VREFBUF instance.
  * @param  trimming_value Trimming value (between 0 and 63).
  * @note The trimming value is automatically initialized with the trimming value (according to the voltage
    scale selected) stored in the flash memory during the production test (factory trimming).
  * @note The user can modify the trimming value with an arbitrary value for fine-tuning of VREFBUF output voltage
    (factory trimming value can be set back by device reset or data backup implemented at application level).
    In this case, any change of voltage scale is discarded.
  * @retval HAL_OK trimming_value has been correctly configured.
  */
hal_status_t  HAL_VREFBUF_SetTrimming(hal_vrefbuf_t instance, uint32_t trimming_value)
{
  ASSERT_DBG_PARAM(IS_VREFBUF_ALL_INSTANCE(VREFBUF_GET_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_VREFBUF_TRIMMING(trimming_value));

  LL_VREFBUF_SetTrimming(VREFBUF_GET_INSTANCE(instance), trimming_value);

  return HAL_OK;
}

/**
  * @brief  Get the trimming value of VREFBUF.
  * @param  instance VREFBUF instance.
  * @retval uint32_t Trimming value (between 0 and 63).
  */
uint32_t  HAL_VREFBUF_GetTrimming(hal_vrefbuf_t instance)
{
  ASSERT_DBG_PARAM(IS_VREFBUF_ALL_INSTANCE(VREFBUF_GET_INSTANCE(instance)));

  return LL_VREFBUF_GetTrimming(VREFBUF_GET_INSTANCE(instance));
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

#endif /* USE_HAL_VREFBUF_MODULE */
#endif /* VREFBUF */
/**
  * @}
  */
