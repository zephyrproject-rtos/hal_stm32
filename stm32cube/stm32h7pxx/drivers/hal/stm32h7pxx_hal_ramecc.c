/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_ramecc.c
  * @brief   This file provides firmware functions to manage the functionalities
  *          of the RAMs configuration controller peripheral
  **********************************************************************************************************************
    * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"
/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

#if defined (RAMECC1) || defined (RAMECC2)
#if defined (USE_HAL_RAMECC_MODULE) && (USE_HAL_RAMECC_MODULE == 1)

/** @addtogroup RAMECC
  * @brief RAMECC HAL module driver
  * @{
  */

/** @defgroup RAMECC_Introduction RAMECC Introduction
  * @{

  The RAMECC hardware abstraction layer provides a set of APIs to interface with the RAMECC peripheral controlling the
  internal SRAMs configuration on STM32 microcontrollers.

  The RAMECC module provides firmware functions to manage the following functionalities :
  - ECC management functions at controller and monitor levels.
  - SRAM information getter functions.

  This abstraction layer guarantees portability and ease of use across different STM32 series.

  */
/**
  * @}
  */

/** @defgroup RAMECC_How_To_Use RAMECC How To Use
  * @{
This module provides a set of APIs to manage each feature supported by the internal SRAMs:

1. ECC feature

  - This feature is supported by all SRAMs. ECC monitoring supports the single error detection and
    correction and double error detection.
  - Each SRAM is associated with a RAMECC monitor, which are grouped together in two separate RAMECC controllers.
  - Interrupts can be enabled either at controller level, i.e. for all monitors of the controller, or at monitor level.

  - Use the HAL_RAMECC_EnableController() or  HAL_RAMECC_EnableMonitor() functions to enable the ECC monitoring
    process in silent mode, i.e. no interrupt will be triggered, nor will a callback be sent upon ECC error.
    User must rely on HAL_RAMECC_GetInfo() function to monitor or/and check for ECC errors if any.

  - Use the HAL_RAMECC_EnableController_IT() or HAL_RAMECC_EnableMonitor_IT() functions to start ECC error
    monitoring process in interrupt mode. This will activate the latching error address and the following interrupts
    will be enabled:
    - Single error interrupt,
    - Double error interrupt,
    - Double error interrupt redirected to Non-Maskable Interrupt(NMI).

    If an interrupt occurs on the RAMECC line, user can call the HAL_RAMECC_IRQHandler() function to manage the
    interrupt for a given instance and receive a dedicated callback to manage the ECC error.

  - Use the HAL_RAMECC_GetInfo() function to get the type, status and address of the last ECC error detected.
    The type can be :
    - No ECC error detected,
    - Single error,
    - Double error.
    - Double Error on Byte Write.

    The status can be :
    - ECC error not corrected,
    - ECC error corrected.

  - Use the HAL_RAMECC_CleanInfo() function to clear all ECC flags for the given monitor so that new ECC errors can be
    caught.

  - Use the HAL_RAMECC_DisableController() or HAL_RAMECC_DisableMonitor() functions to disable the ECC
    monitoring.

2. SRAM information getter
  - Use the HAL_RAMECC_GetLLControllerInstance() function to get the selected RAMECC controller hardware instance.

  - Use the HAL_RAMECC_GetLLMonitorInstance() function to get the selected RAMECC monitor hardware instance.

  - Use the HAL_RAMECC_GetSRAMBaseAddress() function to get the selected RAMECC SRAM base address.

  - Use the HAL_RAMECC_GetSRAMSize() function to get the selected RAMECC SRAM size.
  */
/**
  * @}
  */

/** @defgroup RAMECC_Configuration_Table RAMECC Configuration Table
  * @{
## Configuration inside the RAMECC driver

Config defines                    | Description      | Default value     | Note
--------------------------------- | ---------------- | ----------------- | --------------------------------------
PRODUCT                           | from IDE         | NA                | Ex:STM32H7P62XX.
USE_ASSERT_DBG_PARAM              | from IDE         | None              | Enable the parameters asserts.
USE_HAL_RAMECC_MODULE             | from hal_conf.h  | 1                 | Enable the HAL RAMECC module.

  */
/**
  * @}
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/

/** @defgroup RAMECC_Private_Variables RAMECC Private Variables
  * @{
  */

/*! RAMECC1 monitor instance array */
static const hal_ramecc_monitor_t RAMECC1_MonitorInstanceArray[] =
{
  HAL_RAMECC_AXISRAM1,
  HAL_RAMECC_AXISRAM2,
  HAL_RAMECC_AXISRAM3,
  HAL_RAMECC_AXISRAM4,
  HAL_RAMECC_ITCM,
  HAL_RAMECC_DTCM0,
  HAL_RAMECC_DTCM1
};

/*! RAMECC2 monitor instance array */
static const hal_ramecc_monitor_t RAMECC2_MonitorInstanceArray[] =
{
  HAL_RAMECC_BKPSRAM
};

/**
  * @}
  */

/* Private constants -------------------------------------------------------------------------------------------------*/

/** @defgroup RAMECC_Private_Constants RAMECC Private constants
  * @{
  */

/*! RAMECC1 monitor number */
#define RAMECC1_MONITOR_NB (uint32_t)(sizeof(RAMECC1_MonitorInstanceArray) / sizeof(RAMECC1_MonitorInstanceArray[0]))

/*! RAMECC2 monitor number */
#define RAMECC2_MONITOR_NB (uint32_t)(sizeof(RAMECC2_MonitorInstanceArray) / sizeof(RAMECC2_MonitorInstanceArray[0]))

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_Private_Macros RAMECC Private Macros
  * @{
  */

/*! Macro to get RAMECC instance */
#define RAMECC_GET_INSTANCE(instance) ((RAMECC_TypeDef *)((uint32_t)(instance)))

/*! Macro to get RAMECC monitor instance */
#define RAMECC_GET_MONITOR_INSTANCE(instance) ((RAMECC_Monitor_TypeDef *)((uint32_t)(instance)))

/*! Macro to get RAMECC instance from monitor instance */
#define RAMECC_GET_INSTANCE_FROM_MONITOR(instance) ((RAMECC_TypeDef *)(((uint32_t)(instance)) & 0xFFFFFF00U))

/*! Macro to get number of monitors for a given RAMECC instance */
#define RAMECC_GET_MONITOR_NB(instance) (((instance) == HAL_RAMECC1) ? RAMECC1_MONITOR_NB : RAMECC2_MONITOR_NB)

/*! Macro to get the array of monitor instances for a given RAMECC instance */
#define RAMECC_GET_MONITOR_INSTANCE_ARRAY(instance) (((instance) == HAL_RAMECC1) \
                                                     ? RAMECC1_MonitorInstanceArray \
                                                     : RAMECC2_MonitorInstanceArray)

/*! Macro to check global interrupts */
#define IS_RAMECC_CONTROLLER_INTERRUPT(interrupt) \
  ((((interrupt) & (HAL_RAMECC_CONTROLLER_IT_SINGLE | HAL_RAMECC_CONTROLLER_IT_DOUBLE \
                    | HAL_RAMECC_CONTROLLER_IT_DOUBLE_BYTE_WRITE | HAL_RAMECC_CONTROLLER_IT_ALL)) != 0U) \
   && (((interrupt) & ~(HAL_RAMECC_CONTROLLER_IT_SINGLE | HAL_RAMECC_CONTROLLER_IT_DOUBLE \
                        | HAL_RAMECC_CONTROLLER_IT_DOUBLE_BYTE_WRITE | HAL_RAMECC_CONTROLLER_IT_ALL)) == 0U))

/*! Macro to check monitor interrupts */
#define IS_RAMECC_MONITOR_INTERRUPT(interrupt) ((((interrupt) & (HAL_RAMECC_MONITOR_IT_ALL)) != 0U) \
                                                && (((interrupt) & ~(HAL_RAMECC_MONITOR_IT_ALL)) == 0U))

/*! Macro to get SRAM base address */
#define RAMECC_GET_SRAM_BASE_ADDR(instance) (((instance) == HAL_RAMECC_AXISRAM1) ? SRAM1_AXI_BASE : \
                                             ((instance) == HAL_RAMECC_AXISRAM2) ? SRAM2_AXI_BASE : \
                                             ((instance) == HAL_RAMECC_AXISRAM3) ? SRAM3_AXI_BASE : \
                                             ((instance) == HAL_RAMECC_AXISRAM4) ? SRAM4_AXI_BASE : \
                                             ((instance) == HAL_RAMECC_ITCM) ? ITCM_BASE : \
                                             ((instance) == HAL_RAMECC_DTCM0) ? DTCM_BASE : \
                                             ((instance) == HAL_RAMECC_DTCM1) ? DTCM_BASE : \
                                             ((instance) == HAL_RAMECC_BKPSRAM) ? BKPSRAM_BASE : 0U)

/*! Macro to get SRAM size in bytes */
#define RAMECC_GET_SRAM_SIZE_BYTE(instance) (((instance) == HAL_RAMECC_AXISRAM1) ? SRAM1_AXI_SIZE : \
                                             ((instance) == HAL_RAMECC_AXISRAM2) ? SRAM2_AXI_SIZE : \
                                             ((instance) == HAL_RAMECC_AXISRAM3) ? SRAM3_AXI_SIZE : \
                                             ((instance) == HAL_RAMECC_AXISRAM4) ? SRAM4_AXI_SIZE : \
                                             ((instance) == HAL_RAMECC_ITCM) ? ITCM_SIZE : \
                                             ((instance) == HAL_RAMECC_DTCM0) ? DTCM_SIZE : \
                                             ((instance) == HAL_RAMECC_DTCM1) ? DTCM_SIZE : \
                                             ((instance) == HAL_RAMECC_BKPSRAM) ? BKPSRAM_SIZE : 0U)
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @addtogroup RAMECC_Exported_Functions
  * @{
  */

/** @addtogroup RAMECC_Exported_Functions_Group1
  * @{
This section provides functions allowing to manage ECC feature provided by the RAMECC peripheral at controller level.

- Call the function HAL_RAMECC_EnableController() to enable the ECC error address latching in silent mode for
  each monitor of the specified controller.

- Call the function HAL_RAMECC_EnableController_IT() to enable the ECC error address latching in interrupt mode for
  each monitor of the specified controller. Interrupts (only the ones specified in the dedicated function parameter)
  are enabled at controller level.

- Call the function HAL_RAMECC_DisableController() to disable the ECC error address latching for each monitor of
  the specified controller.
  */

/**
  * @brief  Enable the address latching of all monitors of the given RAMECC controller instance.
  * @param  instance RAMECC controller instance.
  * @retval HAL_OK RAMECC controller has been successfully enabled.
  */
hal_status_t HAL_RAMECC_EnableController(hal_ramecc_controller_t instance)
{
  uint32_t monitor_nb = RAMECC_GET_MONITOR_NB(instance);
  const hal_ramecc_monitor_t *monitor_array = RAMECC_GET_MONITOR_INSTANCE_ARRAY(instance);

  ASSERT_DBG_PARAM(IS_RAMECC_ALL_INSTANCE(RAMECC_GET_INSTANCE(instance)));

  for (uint32_t idx = 0U; idx < monitor_nb; idx++)
  {
    LL_RAMECC_EnableAddressLatch(RAMECC_GET_MONITOR_INSTANCE(monitor_array[idx]));
  }

  return HAL_OK;
}

/**
  * @brief  Enable the given ECC interrupt at controller level and the address latching of all monitors of the given
  *         RAMECC controller instance.
  * @param  instance RAMECC controller instance.
  * @param  interrupt
  *         This parameter can be any combination of the following values:
  *         @arg @ref HAL_RAMECC_CONTROLLER_IT_SINGLE
  *         @arg @ref HAL_RAMECC_CONTROLLER_IT_DOUBLE
  *         @arg @ref HAL_RAMECC_CONTROLLER_IT_DOUBLE_BYTE_WRITE
  *         @arg @ref HAL_RAMECC_CONTROLLER_IT_ALL
  * @retval HAL_OK RAMECC controller interrupt has been successfully enabled.
  */
hal_status_t HAL_RAMECC_EnableController_IT(hal_ramecc_controller_t instance, uint32_t interrupt)
{
  uint32_t monitor_nb = RAMECC_GET_MONITOR_NB(instance);
  const hal_ramecc_monitor_t *monitor_array = RAMECC_GET_MONITOR_INSTANCE_ARRAY(instance);

  ASSERT_DBG_PARAM(IS_RAMECC_ALL_INSTANCE(RAMECC_GET_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_RAMECC_CONTROLLER_INTERRUPT(interrupt));

  for (uint32_t idx = 0U; idx < monitor_nb; idx++)
  {
    LL_RAMECC_ClearFlag(RAMECC_GET_MONITOR_INSTANCE(monitor_array[idx]), LL_RAMECC_FLAG_ALL);
    LL_RAMECC_EnableAddressLatch(RAMECC_GET_MONITOR_INSTANCE(monitor_array[idx]));
  }

  LL_RAMECC_EnableGlobalIT(RAMECC_GET_INSTANCE(instance), interrupt);

  return HAL_OK;
}

/**
  * @brief  Disable all ECC interrupts at controller level and the address latching of all monitors of the given
  *         RAMECC controller instance.
  * @param  instance RAMECC instance.
  * @retval HAL_OK RAMECC controller has been successfully disabled.
  */
hal_status_t HAL_RAMECC_DisableController(hal_ramecc_controller_t instance)
{
  uint32_t monitor_nb = RAMECC_GET_MONITOR_NB(instance);
  const hal_ramecc_monitor_t *monitor_array = RAMECC_GET_MONITOR_INSTANCE_ARRAY(instance);

  ASSERT_DBG_PARAM(IS_RAMECC_ALL_INSTANCE(RAMECC_GET_INSTANCE(instance)));

  for (uint32_t idx = 0U; idx < monitor_nb; idx++)
  {
    LL_RAMECC_DisableAddressLatch(RAMECC_GET_MONITOR_INSTANCE(monitor_array[idx]));
  }

  LL_RAMECC_DisableGlobalIT(RAMECC_GET_INSTANCE(instance), \
                            (HAL_RAMECC_CONTROLLER_IT_SINGLE | HAL_RAMECC_CONTROLLER_IT_DOUBLE \
                             | HAL_RAMECC_CONTROLLER_IT_DOUBLE_BYTE_WRITE | HAL_RAMECC_CONTROLLER_IT_ALL));

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RAMECC_Exported_Functions_Group2
  * @{
This section provides functions allowing to manage ECC feature provided by the RAMECC peripheral at monitor level.
- Call the function HAL_RAMECC_EnableMonitor() to enable the ECC error address latching in silent mode for
  the specified monitor.

- Call the function HAL_RAMECC_EnableMonitor_IT() to enable the ECC error address latching in interrupt mode for
  the specified monitor. Interrupts (only the ones specified in the dedicated function parameter) are enabled at
  monitor level, only for the one specified by the dedicated function parameter.

- Call the function HAL_RAMECC_DisableMonitor() to disable the ECC error address latching of the specified monitor.

- Call the function HAL_RAMECC_GetInfo() to get the ECC information for the specified monitor.

- Call the function HAL_RAMECC_CleanInfo() to clean the ECC information of the specified monitor.
  */

/**
  * @brief  Enable the address latching of the given RAMECC monitor instance.
  * @param  instance RAMECC monitor instance.
  * @retval HAL_OK RAMECC monitor has been successfully enabled.
  */
hal_status_t HAL_RAMECC_EnableMonitor(hal_ramecc_monitor_t instance)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));

  LL_RAMECC_EnableAddressLatch(RAMECC_GET_MONITOR_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Enable the given ECC interrupt and the address latching of the given RAMECC monitor instance.
  * @param  instance RAMECC monitor instance.
  * @param  interrupt
  *         This parameter can be any combination of the following values:
  *         @arg @ref HAL_RAMECC_MONITOR_IT_SINGLE
  *         @arg @ref HAL_RAMECC_MONITOR_IT_DOUBLE
  *         @arg @ref HAL_RAMECC_MONITOR_IT_DOUBLE_BYTE_WRITE
  *         @arg @ref HAL_RAMECC_MONITOR_IT_ALL
  * @retval HAL_OK RAMECC monitor interrupt has been successfully enabled.
  */
hal_status_t HAL_RAMECC_EnableMonitor_IT(hal_ramecc_monitor_t instance, uint32_t interrupt)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_INTERRUPT(interrupt));

  LL_RAMECC_ClearFlag(RAMECC_GET_MONITOR_INSTANCE(instance), LL_RAMECC_FLAG_ALL);
  LL_RAMECC_EnableMonitorIT(RAMECC_GET_MONITOR_INSTANCE(instance), interrupt);
  LL_RAMECC_EnableAddressLatch(RAMECC_GET_MONITOR_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Disable all ECC interrupts and the address latching of the given RAMECC monitor instance.
  * @param  instance RAMECC monitor instance.
  * @retval HAL_OK RAMECC monitor interrupt has been successfully disabled.
  */
hal_status_t HAL_RAMECC_DisableMonitor(hal_ramecc_monitor_t instance)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));

  LL_RAMECC_DisableAddressLatch(RAMECC_GET_MONITOR_INSTANCE(instance));
  LL_RAMECC_DisableMonitorIT(RAMECC_GET_MONITOR_INSTANCE(instance), HAL_RAMECC_MONITOR_IT_ALL);

  return HAL_OK;
}

/**
  * @brief   Get the ECC information.
  * @param   instance RAMECC monitor instance.
  * @param   p_info Pointer to a @ref hal_ramecc_ecc_info_t structure.
  */
void HAL_RAMECC_GetInfo(hal_ramecc_monitor_t instance, hal_ramecc_ecc_info_t *p_info)
{
  uint32_t flags;
  uint32_t offset;
  RAMECC_Monitor_TypeDef *p_monitor = RAMECC_GET_MONITOR_INSTANCE(instance);

  ASSERT_DBG_PARAM(p_info != NULL);
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(p_monitor));

  flags = LL_RAMECC_ReadFlag(p_monitor, LL_RAMECC_FLAG_ALL);

  if (flags == 0U)
  {
    p_info->type = HAL_RAMECC_ECC_NONE;
  }
  else
  {
    offset = LL_RAMECC_GetErrorAddressOffset(p_monitor);
    if (instance == HAL_RAMECC_AXISRAM1)
    {
      offset = (~offset & 0x00002000U) | (offset & 0xFFFFDFFFU); /* Bit 13 value is inverted for AXISRAM1 */
    }

    if (instance == HAL_RAMECC_BKPSRAM)
    {
      p_info->address = (offset << 2U) + BKPSRAM_BASE;
      p_info->data = LL_RAMECC_GetErrorDataBytes(p_monitor);
      p_info->code = LL_RAMECC_GetErrorCode(p_monitor);
    }
    else
    {
      p_info->address = (offset << 3U) + RAMECC_GET_SRAM_BASE_ADDR(instance);
    }

    if ((flags & LL_RAMECC_FLAG_DEBW) != 0U)
    {
      p_info->type = HAL_RAMECC_ECC_DOUBLE_BYTE_WRITE;
      p_info->status = HAL_RAMECC_ECC_NOT_CORRECTED;
    }
    else if ((flags & LL_RAMECC_FLAG_DE) != 0U)
    {
      p_info->type = HAL_RAMECC_ECC_DOUBLE;
      p_info->status = HAL_RAMECC_ECC_NOT_CORRECTED;
    }
    else
    {
      p_info->type = HAL_RAMECC_ECC_SINGLE;
      p_info->status = HAL_RAMECC_ECC_CORRECTED;
    }
  }
}

/**
  * @brief   Clean the ECC information.
  * @param   instance RAMECC monitor instance.
  */
void HAL_RAMECC_CleanInfo(hal_ramecc_monitor_t instance)
{
  RAMECC_Monitor_TypeDef *p_monitor = RAMECC_GET_MONITOR_INSTANCE(instance);

  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(p_monitor));

  LL_RAMECC_ClearFlag(p_monitor, LL_RAMECC_FLAG_ALL);
}

/**
  * @}
  */

/** @addtogroup RAMECC_Exported_Functions_Group3
  * @{

This section provides functions to handle RAMECC interrupts and register different callbacks.
- Call the function HAL_RAMECC_IRQHandler() within RAMECC vector to handle any RAMECC interrupt. This API must
  be executed in IRQ handler mode.
- The function HAL_RAMECC_ErrorCallback() is to be redefined within user application for the error callback.
  */

/**
  * @brief  Handle RAMECC interrupt request.
  * @param  instance RAMECC instance.
  */
void HAL_RAMECC_IRQHandler(hal_ramecc_monitor_t instance)
{
  uint32_t flags;
  uint32_t monitor_its;
  uint32_t global_its;
  RAMECC_Monitor_TypeDef *p_monitor = RAMECC_GET_MONITOR_INSTANCE(instance);

  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(p_monitor));

  flags = LL_RAMECC_ReadFlag(p_monitor, LL_RAMECC_FLAG_ALL);
  monitor_its = LL_RAMECC_GetMonitorIT(p_monitor, LL_RAMECC_MONITOR_IT_ALL);
  global_its  = LL_RAMECC_GetGlobalIT(RAMECC_GET_INSTANCE_FROM_MONITOR(p_monitor), LL_RAMECC_GLOBAL_IT_ALL);

  /* Double Error Interrupt Management */
  if (((flags & LL_RAMECC_FLAG_DE) != 0U) \
      && (((monitor_its & LL_RAMECC_MONITOR_IT_DE) != 0U) \
          || ((global_its & (LL_RAMECC_GLOBAL_IT_DE | LL_RAMECC_GLOBAL_IT_ALL)) != 0U)))
  {
    HAL_RAMECC_ErrorCallback(instance);
    LL_RAMECC_ClearFlag_DE(p_monitor);
  }

  /* Double Error Interrupt Management */
  if (((flags & LL_RAMECC_FLAG_DEBW) != 0U) \
      && (((monitor_its & LL_RAMECC_MONITOR_IT_DEBW) != 0U) \
          || ((global_its & (LL_RAMECC_GLOBAL_IT_DEBW | LL_RAMECC_GLOBAL_IT_ALL)) != 0U)))
  {
    HAL_RAMECC_ErrorCallback(instance);
    LL_RAMECC_ClearFlag_DEBW(p_monitor);
  }

  /* Single Error Interrupt Management */
  if (((flags & LL_RAMECC_FLAG_SE) != 0U) \
      && (((monitor_its & LL_RAMECC_MONITOR_IT_SE) != 0U) \
          || ((global_its & (LL_RAMECC_GLOBAL_IT_SE | LL_RAMECC_GLOBAL_IT_ALL)) != 0U)))
  {
    HAL_RAMECC_ErrorCallback(instance);
    LL_RAMECC_ClearFlag_SE(p_monitor);
  }
}

/**
  * @brief  RAMECC error callback.
  * @param  instance RAMECC monitor instance.
  */
__WEAK void HAL_RAMECC_ErrorCallback(hal_ramecc_monitor_t instance)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(instance);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RAMECC_ErrorCallback can be implemented in
            the user file.                                                    */
}

/**
  * @}
  */

/** @addtogroup RAMECC_Exported_Functions_Group4
  * @{
This section provides functions to get RAMECC instance information.
- Call the function HAL_RAMECC_GetLLControllerInstance() to get the selected RAMECC hardware instance.
- Call the function HAL_RAMECC_GetLLMonitorInstance() to get the selected RAMECC monitor hardware instance.
- Call the function HAL_RAMECC_GetSRAMBaseAddress() to get the selected RAMECC SRAM base address.
- Call the function HAL_RAMECC_GetSRAMSize() to get the selected RAMECC SRAM size.
  */
/**
  * @brief  Get the selected hardware RAMECC instance.
  * @param  instance RAMECC instance.
  * @retval The selected hardware RAMECC instance.
  */
RAMECC_TypeDef *HAL_RAMECC_GetLLControllerInstance(hal_ramecc_controller_t instance)
{
  ASSERT_DBG_PARAM(IS_RAMECC_ALL_INSTANCE(RAMECC_GET_INSTANCE(instance)));

  return ((RAMECC_TypeDef *)((uint32_t)(instance)));
}

/**
  * @brief  Get the selected hardware RAMECC monitor instance.
  * @param  instance RAMECC monitor instance.
  * @retval The selected hardware RAMECC monitor instance.
  */
RAMECC_Monitor_TypeDef *HAL_RAMECC_GetLLMonitorInstance(hal_ramecc_monitor_t instance)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));

  return ((RAMECC_Monitor_TypeDef *)((uint32_t)(instance)));
}

/**
  * @brief  Get the RAMECC SRAM base address.
  * @param  instance RAMECC monitor instance.
  * @retval uint32_t The base address of the given SRAM.
  */
uint32_t HAL_RAMECC_GetSRAMBaseAddress(hal_ramecc_monitor_t instance)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));

  return RAMECC_GET_SRAM_BASE_ADDR(instance);
}

/**
  * @brief  Get the RAMECC SRAM size in bytes.
  * @param  instance RAMECC monitor instance.
  * @retval uint32_t The size of the given SRAM in bytes.
  */
uint32_t HAL_RAMECC_GetSRAMSize(hal_ramecc_monitor_t instance)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));

  return RAMECC_GET_SRAM_SIZE_BYTE(instance);
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

#endif /* USE_HAL_RAMECC_MODULE */
#endif /* RAMECC1 || RAMECC2 */

/**
  * @}
  */
