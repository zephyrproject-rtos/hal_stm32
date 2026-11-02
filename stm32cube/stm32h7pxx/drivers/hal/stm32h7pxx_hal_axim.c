/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_axim.c
  * @brief   This file provides firmware functions to manage the AXI Interconnect Matrix.
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

/** @addtogroup STM32H7PXX_HAL_Driver
  * @{
  */
#if defined (AXIM)
#if defined (USE_HAL_AXIM_MODULE) && (USE_HAL_AXIM_MODULE == 1)

/** @defgroup AXIM AXIM
  * @{
  */

/** @defgroup AXIM_Introduction AXIM Introduction
  * @{

  The AXIM hardware abstraction layer provides a comprehensive set of APIs to interface with the AXI Interconnect Matrix
  initiators and targets on STM32 microcontrollers. It is intended to manage the outstanding transactions issued by the
  AXIM initiators and targets, allowing the configuration of their quality of service (QoS) and issuing capabilities.

  It simplifies the configuration, initialization, and management of the AXI Interconnect Matrix, enabling developers to
  optimize the performance and behavior of their system's interconnect.

  This abstraction layer guarantees portability and ease of use across different STM32 series.
  */
/**
  * @}
  */

/** @defgroup AXIM_How_To_Use AXIM How To Use
  * @{
# AXIM main features

## The HAL AXIM driver provides the following main features:
1. Initiator management
  - The driver allows to manage initiators by:
    - Enabling configuration of read/write quality of service (QoS) when supported by the initiator.
    - Controlling read/write issuing capability to shape outstanding transactions.

2. Target management
  - The driver allows to configure AXI targets by:
    - Setting read/write bus matrix issuing capability to tune interconnect behavior.

3. Peripheral identification
  - The driver allows to retrieve AXIM peripheral identification data such as revision, JEP-106 information,
    part number, and file size.

4. Component identification
  - The driver allows to retrieve AXIM component metadata such as component class and preamble bits.

# How to use the AXIM HAL module driver

## The AXIM HAL driver can be used as follows :

This driver provides the HAL AXIM driver functions that allow the configuration and management of the
AXI Interconnect Matrix initiators and targets and the retrieval of the AXIM peripheral and component information.

1. How to configure an AXIM initiator

   - Configure an AXIM initiator using HAL_AXIM_INI_SetConfig(), which allows to set:
     - Read/write quality of service if available for a given initiator.
     - Read/write Issuing capability.
     - Packing of beats to match the output data width.
     - Increment override.
   - Configure an AXIM initiator read quality of service by using HAL_AXIM_INI_SetReadQoS() function.
   - Configure an AXIM initiator write quality of service by using HAL_AXIM_INI_SetWriteQoS() function.
   - Configure an AXIM initiator read/write issuing capability by using HAL_AXIM_INI_SetIssuingCapability() function.
   - Configure an AXIM initiator packing by using HAL_AXIM_INI_EnablePacking()
     or HAL_AXIM_INI_DisablePacking() functions.
   - Configure an AXIM initiator increment override by using HAL_AXIM_INI_SetIncrementOverride() function.

2. How to configure an AXIM target

   - Configure an AXIM target globally by using HAL_AXIM_TARG_SetConfig() function, which allows to set:
     - Read/write bus matrix issuing capability.
     - Read/write issuing capability.
     - packing of beats to match the output data width.
     - Long burst generation at the output of the AMIB.
   - Configure an AXIM target read/write bus matrix issuing capability with
     HAL_AXIM_TARG_SetBusMatrixIssuingCapability() function.
   - Configure an AXIM target read/write issuing capability with HAL_AXIM_TARG_SetIssuingCapability() function.
   - Configure an AXIM target packing with HAL_AXIM_TARG_EnablePacking()
     or HAL_AXIM_TARG_DisablePacking() functions.
   - Configure an AXIM target long burst generation with HAL_AXIM_TARG_EnableLongBurst()
     or HAL_AXIM_TARG_DisableLongBurst() functions.

3. How to get the AXIM peripheral information

   - Get AXIM peripheral information such as the revision, JEP-106 information, part number, and file size using
     HAL_AXIM_GetPeripheralInfo() function.

4. How to get the AXIM component information
   - Get AXIM component information such as the component class, and preamble bits using
     HAL_AXIM_GetComponentInfo() function.
  */
/**
  * @}
  */

/** @defgroup AXIM_Configuration_Table AXIM Configuration Table
  * @{
  # Configuration inside the AXIM driver

Config defines                    | Description      | Default value     | Note
--------------------------------- | ---------------- | ----------------- | --------------------------------------
PRODUCT                           | From IDE         | NA                | The selected product.
USE_HAL_AXIM_MODULE               | From hal_conf.h  | 1                 | Enable the HAL AXIM module.
USE_ASSERT_DBG_PARAM              | From IDE         | NA                | Enable the parameters asserts.
USE_HAL_CHECK_PARAM               | From hal_conf.h  | 0                 | Enable the parameters runtime checks.
  */
/**
  * @}
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup AXIM_Private_Constants AXIM Private Constants
  * @{
  */
#define AXIM_PACKING_NOT_AVAILABLE            0xFFUL /*!< Packing not available error value             */
#define AXIM_INCREMENT_OVERRIDE_NOT_AVAILABLE 0xFFUL /*!< Increment override not available error value  */
#define AXIM_LONG_BURST_NOT_AVAILABLE         0xFFUL /*!< Long burst not available error value          */
#define AXIM_PRIORITY_MAX_VALUE               0x0FUL /*!< Maximum read/write priority value             */
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup AXIM_Private_Macros AXIM Private Macros
  * @{
  */

/*! Macro to check initiator */
#define IS_AXIM_INITIATOR(ini) (((ini) == HAL_AXIM_INI_GPDMA    ) \
                                || ((ini) == HAL_AXIM_INI_SDMMC1) \
                                || ((ini) == HAL_AXIM_INI_HPDMA ) \
                                || ((ini) == HAL_AXIM_INI_CORE  ) \
                                || ((ini) == HAL_AXIM_INI_NPU_1 ) \
                                || ((ini) == HAL_AXIM_INI_NPU_2 ))

/*! Macro to check target */
#define IS_AXIM_TARGET(targ) (((targ) == HAL_AXIM_TARG_AHBIC_BRIDGE    ) \
                              || ((targ) == HAL_AXIM_TARG_FMC          ) \
                              || ((targ) == HAL_AXIM_TARG_XSPI1        ) \
                              || ((targ) == HAL_AXIM_TARG_AXISRAM3     ) \
                              || ((targ) == HAL_AXIM_TARG_AXISRAM2     ) \
                              || ((targ) == HAL_AXIM_TARG_AXISRAM1     ) \
                              || ((targ) == HAL_AXIM_TARG_FLASH        ) \
                              || ((targ) == HAL_AXIM_TARG_AXISRAM4     ) \
                              || ((targ) == HAL_AXIM_TARG_AHBS_BRIDGE  ))

/*! Macro to check priority value */
#define IS_AXIM_PRIORITY_VALUE(value) ((value) <= AXIM_PRIORITY_MAX_VALUE)

/*! Macro to check issuing functionality value */
#define IS_AXIM_ISSUING_CAPABILITY(mode) (((mode) == HAL_AXIM_ISSUING_NORMAL           ) \
                                          || ((mode) == HAL_AXIM_ISSUING_OVERRIDE_READ ) \
                                          || ((mode) == HAL_AXIM_ISSUING_OVERRIDE_WRITE) \
                                          || ((mode) == HAL_AXIM_ISSUING_OVERRIDE_BOTH ))

/*! Macro to check initiators support packing feature */
#define IS_AXIM_PACKING_INITIATOR(ini) (((ini) == HAL_AXIM_INI_GPDMA) || ((ini) == HAL_AXIM_INI_SDMMC1))

/*! Macro to check targets support packing feature */
#define IS_AXIM_PACKING_TARGET(targ) (((targ) == HAL_AXIM_TARG_AHBIC_BRIDGE) || ((targ) == HAL_AXIM_TARG_AHBS_BRIDGE))

/*! Macro to check packing */
#define IS_AXIM_PACKING(packing) (((packing) == HAL_AXIM_PACKING_DISABLE) || ((packing) == HAL_AXIM_PACKING_ENABLE))

/*! Macro to check initiators support increment override feature */
#define IS_AXIM_INCREMENT_OVERRIDE_INITIATOR(ini) (((ini) == HAL_AXIM_INI_GPDMA) || ((ini) == HAL_AXIM_INI_SDMMC1))

/*! Macro to check increment override */
#define IS_AXIM_INCREMENT_OVERRIDE(increment_override) (((increment_override) == HAL_AXIM_INCREMENT_NORMAL           ) \
                                                        || ((increment_override) == HAL_AXIM_INCREMENT_OVERRIDE_READ ) \
                                                        || ((increment_override) == HAL_AXIM_INCREMENT_OVERRIDE_WRITE) \
                                                        || ((increment_override) == HAL_AXIM_INCREMENT_OVERRIDE_BOTH ))

/*! Macro to check targets support long burst feature */
#define IS_AXIM_LONG_BURST_TARGET(targ) (((targ) == HAL_AXIM_TARG_AHBIC_BRIDGE) \
                                         || ((targ) == HAL_AXIM_TARG_AHBS_BRIDGE))

/*! Macro to check long burst */
#define IS_AXIM_LONG_BURST(long_burst) (((long_burst) == HAL_AXIM_LONG_BURST_DISABLE) \
                                        || ((long_burst) == HAL_AXIM_LONG_BURST_ENABLE))
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @addtogroup AXIM_Exported_Functions
  * @{
  */

/** @addtogroup AXIM_Exported_Functions_Group1
  * @{
- This subsection provides a set of functions to configure AXIM initiators.
  - Use HAL_AXIM_INI_SetConfig() to set initiator configuration.
  - Use HAL_AXIM_INI_GetConfig() to get initiator configuration.
  - Use HAL_AXIM_INI_SetReadQoS() to set initiator read quality of service.
  - Use HAL_AXIM_INI_GetReadQoS() to get initiator read quality of service.
  - Use HAL_AXIM_INI_SetWriteQoS() to set initiator write quality of service.
  - Use HAL_AXIM_INI_GetWriteQoS() to get initiator write quality of service.
  - Use HAL_AXIM_INI_SetIssuingCapability() to set initiator read/write issuing capability.
  - Use HAL_AXIM_INI_GetIssuingCapability() to get initiator read/write issuing capability.
  - Use HAL_AXIM_INI_EnablePacking() to enable packing of beats to match the output data width.
  - Use HAL_AXIM_INI_DisablePacking() to disable packing of beats to match the output data width.
  - Use HAL_AXIM_INI_IsEnabledPacking() to check if the packing is enabled or disabled.
  - Use HAL_AXIM_INI_SetIncrementOverride() to set initiator read/write increment override configuration.
  - Use HAL_AXIM_INI_GetIncrementOverride() to get initiator read/write increment override configuration.
  */

/**
  * @brief  Set AXIM initiator configuration.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  *         @arg @ref HAL_AXIM_INI_HPDMA (**)
  *         @arg @ref HAL_AXIM_INI_CORE (**)
  *         @arg @ref HAL_AXIM_INI_NPU_1 (**)
  *         @arg @ref HAL_AXIM_INI_NPU_2 (**)
  * @param  p_ini_config Pointer to AXIM initiator configuration structure.
  * @note   For these initiators (**) : The packing and increment override configuration are not available.
  * @retval HAL_INVALID_PARAM if p_ini_config is NULL.
  * @retval HAL_OK if AXIM initiator has been successfully configured.
  */
hal_status_t HAL_AXIM_INI_SetConfig(hal_axim_ini_t ini, const hal_axim_ini_config_t *p_ini_config)
{
  ASSERT_DBG_PARAM(IS_AXIM_INITIATOR(ini));
  ASSERT_DBG_PARAM(p_ini_config != NULL);
  ASSERT_DBG_PARAM(IS_AXIM_PRIORITY_VALUE(p_ini_config->read_qos));
  ASSERT_DBG_PARAM(IS_AXIM_PRIORITY_VALUE(p_ini_config->write_qos));
  ASSERT_DBG_PARAM(IS_AXIM_ISSUING_CAPABILITY(p_ini_config->capability));
  ASSERT_DBG_PARAM(IS_AXIM_PACKING(p_ini_config->packing));
  ASSERT_DBG_PARAM(IS_AXIM_INCREMENT_OVERRIDE(p_ini_config->increment_override));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_ini_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_AXIM_ASIB_SetReadQoS((uint32_t)ini, p_ini_config->read_qos);
  LL_AXIM_ASIB_SetWriteQoS((uint32_t)ini, p_ini_config->write_qos);

  LL_AXIM_ASIB_SetIssuingCapability((uint32_t)ini, (uint32_t)p_ini_config->capability);

  if (IS_AXIM_PACKING_INITIATOR(ini) != 0U)
  {
    if (p_ini_config->packing == HAL_AXIM_PACKING_ENABLE)
    {
      LL_AXIM_ASIB_EnablePacking((uint32_t)ini);
    }
    else
    {
      LL_AXIM_ASIB_DisablePacking((uint32_t)ini);
    }
  }

  if (IS_AXIM_INCREMENT_OVERRIDE_INITIATOR(ini) != 0U)
  {
    LL_AXIM_ASIB_SetIncrementOverride((uint32_t)ini, (uint32_t)p_ini_config->increment_override);
  }

  return HAL_OK;
}

/**
  * @brief  Get AXIM initiator configuration.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  *         @arg @ref HAL_AXIM_INI_HPDMA (**)
  *         @arg @ref HAL_AXIM_INI_CORE (**)
  *         @arg @ref HAL_AXIM_INI_NPU_1 (**)
  *         @arg @ref HAL_AXIM_INI_NPU_2 (**)
  * @param  p_ini_config Pointer to AXIM initiator configuration structure.
  * @note   For these initiators (**) : The packing and increment_override fields are set to
  *         AXIM_PACKING_NOT_AVAILABLE and AXIM_INCREMENT_OVERRIDE_NOT_AVAILABLE.
  */
void HAL_AXIM_INI_GetConfig(hal_axim_ini_t ini, hal_axim_ini_config_t *p_ini_config)
{
  ASSERT_DBG_PARAM(IS_AXIM_INITIATOR(ini));
  ASSERT_DBG_PARAM(p_ini_config != NULL);

  p_ini_config->read_qos   = (uint8_t)LL_AXIM_ASIB_GetReadQoS((uint32_t)ini);
  p_ini_config->write_qos  = (uint8_t)LL_AXIM_ASIB_GetWriteQoS((uint32_t)ini);

  p_ini_config->capability = (hal_axim_issuing_capability_t)LL_AXIM_ASIB_GetIssuingCapability((uint32_t)ini);

  p_ini_config->packing    = (hal_axim_packing_state_t)AXIM_PACKING_NOT_AVAILABLE;

  if (IS_AXIM_PACKING_INITIATOR(ini) != 0U)
  {
    p_ini_config->packing = (hal_axim_packing_state_t)LL_AXIM_ASIB_IsEnabledPacking((uint32_t)ini);
  }

  p_ini_config->increment_override = (hal_axim_increment_override_t)AXIM_INCREMENT_OVERRIDE_NOT_AVAILABLE;

  if (IS_AXIM_INCREMENT_OVERRIDE_INITIATOR(ini) != 0U)
  {
    p_ini_config->increment_override = (hal_axim_increment_override_t)LL_AXIM_ASIB_GetIncrementOverride((uint32_t)ini);
  }
}

/**
  * @brief  Configure AXIM initiator read quality of service.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  *         @arg @ref HAL_AXIM_INI_HPDMA
  *         @arg @ref HAL_AXIM_INI_CORE
  *         @arg @ref HAL_AXIM_INI_NPU_1
  *         @arg @ref HAL_AXIM_INI_NPU_2
  * @param  read_qos read quality of service value can be between 0 and 15.
  * @retval HAL_OK            if the initiator read quality of service has been successfully configured.
  */
hal_status_t HAL_AXIM_INI_SetReadQoS(hal_axim_ini_t ini, uint32_t read_qos)
{
  ASSERT_DBG_PARAM(IS_AXIM_INITIATOR(ini));
  ASSERT_DBG_PARAM(IS_AXIM_PRIORITY_VALUE(read_qos));

  LL_AXIM_ASIB_SetReadQoS((uint32_t)ini, read_qos);

  return HAL_OK;
}

/**
  * @brief  Get AXIM initiator read quality of service.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  *         @arg @ref HAL_AXIM_INI_HPDMA
  *         @arg @ref HAL_AXIM_INI_CORE
  *         @arg @ref HAL_AXIM_INI_NPU_1
  *         @arg @ref HAL_AXIM_INI_NPU_2
  * @retval Read quality of service value can be between 0 and 15.
  */
uint32_t HAL_AXIM_INI_GetReadQoS(hal_axim_ini_t ini)
{
  ASSERT_DBG_PARAM(IS_AXIM_INITIATOR(ini));

  return LL_AXIM_ASIB_GetReadQoS((uint32_t)ini);
}

/**
  * @brief  Configure AXIM initiator write quality of service.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  *         @arg @ref HAL_AXIM_INI_HPDMA
  *         @arg @ref HAL_AXIM_INI_CORE
  *         @arg @ref HAL_AXIM_INI_NPU_1
  *         @arg @ref HAL_AXIM_INI_NPU_2
  * @param  write_qos write quality of service value can be between 0 and 15.
  * @retval HAL_OK            if the initiator write quality of service has been successfully configured.
  */
hal_status_t HAL_AXIM_INI_SetWriteQoS(hal_axim_ini_t ini, uint32_t write_qos)
{
  ASSERT_DBG_PARAM(IS_AXIM_INITIATOR(ini));
  ASSERT_DBG_PARAM(IS_AXIM_PRIORITY_VALUE(write_qos));

  LL_AXIM_ASIB_SetWriteQoS((uint32_t)ini, write_qos);

  return HAL_OK;
}

/**
  * @brief  Get AXIM initiator write quality of service.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  *         @arg @ref HAL_AXIM_INI_HPDMA
  *         @arg @ref HAL_AXIM_INI_CORE
  *         @arg @ref HAL_AXIM_INI_NPU_1
  *         @arg @ref HAL_AXIM_INI_NPU_2
  * @retval Write quality of service value can be between 0 and 15.
  */
uint32_t HAL_AXIM_INI_GetWriteQoS(hal_axim_ini_t ini)
{
  ASSERT_DBG_PARAM(IS_AXIM_INITIATOR(ini));

  return LL_AXIM_ASIB_GetWriteQoS((uint32_t)ini);
}

/**
  * @brief  Set AXIM initiator read/write issuing capability.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  *         @arg @ref HAL_AXIM_INI_HPDMA
  *         @arg @ref HAL_AXIM_INI_CORE
  *         @arg @ref HAL_AXIM_INI_NPU_1
  *         @arg @ref HAL_AXIM_INI_NPU_2
  * @param  capability This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_ISSUING_NORMAL
  *         @arg @ref HAL_AXIM_ISSUING_OVERRIDE_READ
  *         @arg @ref HAL_AXIM_ISSUING_OVERRIDE_WRITE
  *         @arg @ref HAL_AXIM_ISSUING_OVERRIDE_BOTH
  * @retval HAL_OK AXIM initiator read/write issuing capability is successfully configured.
  */
hal_status_t HAL_AXIM_INI_SetIssuingCapability(hal_axim_ini_t ini, hal_axim_issuing_capability_t capability)
{
  ASSERT_DBG_PARAM(IS_AXIM_INITIATOR(ini));
  ASSERT_DBG_PARAM(IS_AXIM_ISSUING_CAPABILITY(capability));

  LL_AXIM_ASIB_SetIssuingCapability((uint32_t)ini, (uint32_t)capability);

  return HAL_OK;
}

/**
  * @brief  Get AXIM initiator read/write issuing capability.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  *         @arg @ref HAL_AXIM_INI_HPDMA
  *         @arg @ref HAL_AXIM_INI_CORE
  *         @arg @ref HAL_AXIM_INI_NPU_1
  *         @arg @ref HAL_AXIM_INI_NPU_2
  * @retval AXIM read/write issuing capability
  */
hal_axim_issuing_capability_t HAL_AXIM_INI_GetIssuingCapability(hal_axim_ini_t ini)
{
  ASSERT_DBG_PARAM(IS_AXIM_INITIATOR(ini));

  return (hal_axim_issuing_capability_t)LL_AXIM_ASIB_GetIssuingCapability((uint32_t)ini);
}

/**
  * @brief  Enable packing for AXIM initiator.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  * @retval HAL_INVALID_PARAM if the initiator does not support packing.
  * @retval HAL_OK            AXIM initiator packing is successfully enabled.
  */
hal_status_t HAL_AXIM_INI_EnablePacking(hal_axim_ini_t ini)
{
  ASSERT_DBG_PARAM(IS_AXIM_PACKING_INITIATOR(ini));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (IS_AXIM_PACKING_INITIATOR(ini) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_AXIM_ASIB_EnablePacking((uint32_t)ini);

  return HAL_OK;
}

/**
  * @brief  Disable packing for AXIM initiator.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  * @retval HAL_INVALID_PARAM if the initiator does not support packing.
  * @retval HAL_OK            AXIM initiator packing is successfully disabled.
  */
hal_status_t HAL_AXIM_INI_DisablePacking(hal_axim_ini_t ini)
{
  ASSERT_DBG_PARAM(IS_AXIM_PACKING_INITIATOR(ini));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (IS_AXIM_PACKING_INITIATOR(ini) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_AXIM_ASIB_DisablePacking((uint32_t)ini);

  return HAL_OK;
}

/**
  * @brief  Check if packing is enabled or disabled for AXIM initiator.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  * @retval AXIM_PACKING_NOT_AVAILABLE if the initiator does not support packing.
  * @retval AXIM initiator packing enable status.
  */
hal_axim_packing_status_t HAL_AXIM_INI_IsEnabledPacking(hal_axim_ini_t ini)
{
  ASSERT_DBG_PARAM(IS_AXIM_PACKING_INITIATOR(ini));

  if (IS_AXIM_PACKING_INITIATOR(ini) == 0U)
  {
    return (hal_axim_packing_status_t)AXIM_PACKING_NOT_AVAILABLE;
  }
  else
  {
    return (hal_axim_packing_status_t)LL_AXIM_ASIB_IsEnabledPacking((uint32_t)ini);
  }
}

/**
  * @brief  Set AXIM initiator increment override configuration.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  * @param  increment_override This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INCREMENT_NORMAL
  *         @arg @ref HAL_AXIM_INCREMENT_OVERRIDE_READ
  *         @arg @ref HAL_AXIM_INCREMENT_OVERRIDE_WRITE
  *         @arg @ref HAL_AXIM_INCREMENT_OVERRIDE_BOTH
  * @retval HAL_INVALID_PARAM if the initiator does not support increment override.
  * @retval HAL_OK            AXIM initiator increment override is successfully configured.
  */
hal_status_t HAL_AXIM_INI_SetIncrementOverride(hal_axim_ini_t ini, hal_axim_increment_override_t increment_override)
{
  ASSERT_DBG_PARAM(IS_AXIM_INCREMENT_OVERRIDE_INITIATOR(ini));
  ASSERT_DBG_PARAM(IS_AXIM_INCREMENT_OVERRIDE(increment_override));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (IS_AXIM_INCREMENT_OVERRIDE_INITIATOR(ini) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_AXIM_ASIB_SetIncrementOverride((uint32_t)ini, (uint32_t)increment_override);

  return HAL_OK;
}

/**
  * @brief  Get AXIM initiator increment override configuration.
  * @param  ini AXIM initiator. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_INI_GPDMA
  *         @arg @ref HAL_AXIM_INI_SDMMC1
  * @retval AXIM_INCREMENT_OVERRIDE_NOT_AVAILABLE if the initiator does not support increment override.
  * @retval AXIM increment override configuration
  */
hal_axim_increment_override_t HAL_AXIM_INI_GetIncrementOverride(hal_axim_ini_t ini)
{
  ASSERT_DBG_PARAM(IS_AXIM_INCREMENT_OVERRIDE_INITIATOR(ini));

  if (IS_AXIM_INCREMENT_OVERRIDE_INITIATOR(ini) == 0U)
  {
    return (hal_axim_increment_override_t)AXIM_INCREMENT_OVERRIDE_NOT_AVAILABLE;
  }
  else
  {
    return (hal_axim_increment_override_t)LL_AXIM_ASIB_GetIncrementOverride((uint32_t)ini);
  }
}

/**
  * @}
  */

/** @addtogroup AXIM_Exported_Functions_Group2
  * @{
- This subsection provides a set of functions to configure AXIM targets.
  - Use HAL_AXIM_TARG_SetConfig() to set target configuration.
  - Use HAL_AXIM_TARG_GetConfig() to get target configuration.
  - Use HAL_AXIM_TARG_SetBusMatrixIssuingCapability() to set target read/write bus matrix issuing capability.
  - Use HAL_AXIM_TARG_GetBusMatrixIssuingCapability() to get target read/write bus matrix issuing capability.
  - Use HAL_AXIM_TARG_SetIssuingCapability() to set target read/write issuing capability.
  - Use HAL_AXIM_TARG_GetIssuingCapability() to get target read/write issuing capability.
  - Use HAL_AXIM_TARG_EnablePacking() to enable packing of beats to match the output data width.
  - Use HAL_AXIM_TARG_DisablePacking() to disable packing of beats to match the output data width.
  - Use HAL_AXIM_TARG_IsEnabledPacking() to check if the packing is enabled or disabled.
  - Use HAL_AXIM_TARG_EnableLongBurst() to enable the long bursts generation at the output of the AMIB.
  - Use HAL_AXIM_TARG_DisableLongBurst() to disable the long bursts generation at the output of the AMIB.
  - Use HAL_AXIM_TARG_IsEnabledLongBurst() to check if the long bursts generation is enabled or disabled.
  */

/**
  * @brief  Set AXIM target configuration.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_FMC (*)
  *         @arg @ref HAL_AXIM_TARG_XSPI1 (*)
  *         @arg @ref HAL_AXIM_TARG_AXISRAM3 (*)
  *         @arg @ref HAL_AXIM_TARG_AXISRAM2 (*)
  *         @arg @ref HAL_AXIM_TARG_AXISRAM1 (*)
  *         @arg @ref HAL_AXIM_TARG_FLASH (*)
  *         @arg @ref HAL_AXIM_TARG_AXISRAM4 (*)
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @param  p_targ_config Pointer to AXIM target configuration structure.
  * @note   For these targets (*) : The packing and long burst generation are not available.
  * @retval HAL_INVALID_PARAM if p_targ_config is NULL.
  * @retval HAL_OK if AXIM target has been successfully configured.
  */
hal_status_t HAL_AXIM_TARG_SetConfig(hal_axim_targ_t targ,
                                     const hal_axim_targ_config_t *p_targ_config)
{
  ASSERT_DBG_PARAM(IS_AXIM_TARGET(targ));
  ASSERT_DBG_PARAM(p_targ_config != NULL);
  ASSERT_DBG_PARAM(IS_AXIM_ISSUING_CAPABILITY(p_targ_config->bus_matrix_capability));
  ASSERT_DBG_PARAM(IS_AXIM_ISSUING_CAPABILITY(p_targ_config->capability));
  ASSERT_DBG_PARAM(IS_AXIM_PACKING(p_targ_config->packing));
  ASSERT_DBG_PARAM(IS_AXIM_LONG_BURST(p_targ_config->long_burst));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_targ_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_AXIM_AMIB_SetBusMatrixIssuingCapability((uint32_t)targ, (uint32_t)p_targ_config->bus_matrix_capability);
  LL_AXIM_AMIB_SetIssuingCapability((uint32_t)targ, (uint32_t)p_targ_config->capability);

  if (IS_AXIM_PACKING_TARGET(targ) != 0U)
  {
    if (p_targ_config->packing == HAL_AXIM_PACKING_ENABLE)
    {
      LL_AXIM_AMIB_EnablePacking((uint32_t)targ);
    }
    else
    {
      LL_AXIM_AMIB_DisablePacking((uint32_t)targ);
    }
  }

  if (IS_AXIM_LONG_BURST_TARGET(targ) != 0U)
  {
    if (p_targ_config->long_burst == HAL_AXIM_LONG_BURST_ENABLE)
    {
      LL_AXIM_AMIB_EnableLongBurst((uint32_t)targ);
    }
    else
    {
      LL_AXIM_AMIB_DisableLongBurst((uint32_t)targ);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Get AXIM target configuration.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_FMC (*)
  *         @arg @ref HAL_AXIM_TARG_XSPI1 (*)
  *         @arg @ref HAL_AXIM_TARG_AXISRAM3 (*)
  *         @arg @ref HAL_AXIM_TARG_AXISRAM2 (*)
  *         @arg @ref HAL_AXIM_TARG_AXISRAM1 (*)
  *         @arg @ref HAL_AXIM_TARG_FLASH (*)
  *         @arg @ref HAL_AXIM_TARG_AXISRAM4 (*)
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @param  p_targ_config Pointer to AXIM target configuration structure.
  * @note   For these targets (*) : The packing and long_burst_gen fields are set to AXIM_PACKING_NOT_AVAILABLE
  *         and AXIM_LONG_BURST_GEN_NOT_AVAILABLE.
  */
void HAL_AXIM_TARG_GetConfig(hal_axim_targ_t targ,
                             hal_axim_targ_config_t *p_targ_config)
{
  ASSERT_DBG_PARAM(IS_AXIM_TARGET(targ));
  ASSERT_DBG_PARAM(p_targ_config != NULL);

  p_targ_config->bus_matrix_capability =
    (hal_axim_issuing_capability_t)LL_AXIM_AMIB_GetBusMatrixIssuingCapability((uint32_t)targ);
  p_targ_config->capability = (hal_axim_issuing_capability_t)LL_AXIM_AMIB_GetIssuingCapability((uint32_t)targ);

  p_targ_config->packing        = (hal_axim_packing_state_t)AXIM_PACKING_NOT_AVAILABLE;

  if (IS_AXIM_PACKING_TARGET(targ) != 0U)
  {
    p_targ_config->packing    = (hal_axim_packing_state_t)LL_AXIM_AMIB_IsEnabledPacking((uint32_t)targ);
  }

  p_targ_config->long_burst = (hal_axim_long_burst_state_t)AXIM_LONG_BURST_NOT_AVAILABLE;

  if (IS_AXIM_LONG_BURST_TARGET(targ) != 0U)
  {
    p_targ_config->long_burst = (hal_axim_long_burst_state_t)LL_AXIM_AMIB_IsEnabledLongBurst((uint32_t)targ);
  }
}

/**
  * @brief  Set AXIM target read/write bus matrix issuing capability.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_FMC
  *         @arg @ref HAL_AXIM_TARG_XSPI1
  *         @arg @ref HAL_AXIM_TARG_AXISRAM3
  *         @arg @ref HAL_AXIM_TARG_AXISRAM2
  *         @arg @ref HAL_AXIM_TARG_AXISRAM1
  *         @arg @ref HAL_AXIM_TARG_FLASH
  *         @arg @ref HAL_AXIM_TARG_AXISRAM4
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @param  bus_matrix_capability This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_ISSUING_NORMAL
  *         @arg @ref HAL_AXIM_ISSUING_OVERRIDE_READ
  *         @arg @ref HAL_AXIM_ISSUING_OVERRIDE_WRITE
  *         @arg @ref HAL_AXIM_ISSUING_OVERRIDE_BOTH
  * @retval HAL_OK AXIM target read/write bus matrix issuing capability is successfully configured.
  */
hal_status_t HAL_AXIM_TARG_SetBusMatrixIssuingCapability(hal_axim_targ_t targ,
                                                         hal_axim_issuing_capability_t bus_matrix_capability)
{
  ASSERT_DBG_PARAM(IS_AXIM_TARGET(targ));
  ASSERT_DBG_PARAM(IS_AXIM_ISSUING_CAPABILITY(bus_matrix_capability));

  LL_AXIM_AMIB_SetBusMatrixIssuingCapability((uint32_t)targ, (uint32_t)bus_matrix_capability);

  return HAL_OK;
}

/**
  * @brief  Get AXIM target read/write bus matrix issuing capability.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_FMC
  *         @arg @ref HAL_AXIM_TARG_XSPI1
  *         @arg @ref HAL_AXIM_TARG_AXISRAM3
  *         @arg @ref HAL_AXIM_TARG_AXISRAM2
  *         @arg @ref HAL_AXIM_TARG_AXISRAM1
  *         @arg @ref HAL_AXIM_TARG_FLASH
  *         @arg @ref HAL_AXIM_TARG_AXISRAM4
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @retval AXIM bus matrix issuing capability
  */
hal_axim_issuing_capability_t HAL_AXIM_TARG_GetBusMatrixIssuingCapability(hal_axim_targ_t targ)
{
  ASSERT_DBG_PARAM(IS_AXIM_TARGET(targ));

  return (hal_axim_issuing_capability_t)LL_AXIM_AMIB_GetBusMatrixIssuingCapability((uint32_t)targ);
}

/**
  * @brief  Set AXIM target read/write issuing capability.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_FMC
  *         @arg @ref HAL_AXIM_TARG_XSPI1
  *         @arg @ref HAL_AXIM_TARG_AXISRAM3
  *         @arg @ref HAL_AXIM_TARG_AXISRAM2
  *         @arg @ref HAL_AXIM_TARG_AXISRAM1
  *         @arg @ref HAL_AXIM_TARG_FLASH
  *         @arg @ref HAL_AXIM_TARG_AXISRAM4
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @param  capability This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_ISSUING_NORMAL
  *         @arg @ref HAL_AXIM_ISSUING_OVERRIDE_READ
  *         @arg @ref HAL_AXIM_ISSUING_OVERRIDE_WRITE
  *         @arg @ref HAL_AXIM_ISSUING_OVERRIDE_BOTH
  * @retval HAL_OK AXIM target read/write issuing capability is successfully configured.
  */
hal_status_t HAL_AXIM_TARG_SetIssuingCapability(hal_axim_targ_t targ, hal_axim_issuing_capability_t capability)
{
  ASSERT_DBG_PARAM(IS_AXIM_TARGET(targ));
  ASSERT_DBG_PARAM(IS_AXIM_ISSUING_CAPABILITY(capability));

  LL_AXIM_AMIB_SetIssuingCapability((uint32_t)targ, (uint32_t)capability);

  return HAL_OK;
}

/**
  * @brief  Get AXIM target read/write issuing capability.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_FMC
  *         @arg @ref HAL_AXIM_TARG_XSPI1
  *         @arg @ref HAL_AXIM_TARG_AXISRAM3
  *         @arg @ref HAL_AXIM_TARG_AXISRAM2
  *         @arg @ref HAL_AXIM_TARG_AXISRAM1
  *         @arg @ref HAL_AXIM_TARG_FLASH
  *         @arg @ref HAL_AXIM_TARG_AXISRAM4
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @retval AXIM issuing capability
  */
hal_axim_issuing_capability_t HAL_AXIM_TARG_GetIssuingCapability(hal_axim_targ_t targ)
{
  ASSERT_DBG_PARAM(IS_AXIM_TARGET(targ));

  return (hal_axim_issuing_capability_t)LL_AXIM_AMIB_GetIssuingCapability((uint32_t)targ);
}

/**
  * @brief  Enable packing for AXIM target.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @retval HAL_INVALID_PARAM if the target does not support packing.
  * @retval HAL_OK            AXIM target packing is successfully enabled.
  */
hal_status_t HAL_AXIM_TARG_EnablePacking(hal_axim_targ_t targ)
{
  ASSERT_DBG_PARAM(IS_AXIM_PACKING_TARGET(targ));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (IS_AXIM_PACKING_TARGET(targ) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_AXIM_AMIB_EnablePacking((uint32_t)targ);

  return HAL_OK;
}

/**
  * @brief  Disable packing for AXIM target.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @retval HAL_INVALID_PARAM if the target does not support packing.
  * @retval HAL_OK AXIM target packing is successfully disabled.
  */
hal_status_t HAL_AXIM_TARG_DisablePacking(hal_axim_targ_t targ)
{
  ASSERT_DBG_PARAM(IS_AXIM_PACKING_TARGET(targ));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (IS_AXIM_PACKING_TARGET(targ) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_AXIM_AMIB_DisablePacking((uint32_t)targ);

  return HAL_OK;
}

/**
  * @brief  Check if the packing is enabled or disabled for AXIM target.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @retval AXIM_PACKING_NOT_AVAILABLE if the target does not support packing.
  * @retval AXIM target packing enable status.
  */
hal_axim_packing_status_t HAL_AXIM_TARG_IsEnabledPacking(hal_axim_targ_t targ)
{
  ASSERT_DBG_PARAM(IS_AXIM_PACKING_TARGET(targ));

  if (IS_AXIM_PACKING_TARGET(targ) == 0U)
  {
    return (hal_axim_packing_status_t)AXIM_PACKING_NOT_AVAILABLE;
  }
  else
  {
    return (hal_axim_packing_status_t)LL_AXIM_AMIB_IsEnabledPacking((uint32_t)targ);
  }
}

/**
  * @brief  Enable long burst for AXIM target.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @retval HAL_INVALID_PARAM if the target does not support long burst.
  * @retval HAL_OK            AXIM target long burst is successfully enabled.
  */
hal_status_t HAL_AXIM_TARG_EnableLongBurst(hal_axim_targ_t targ)
{
  ASSERT_DBG_PARAM(IS_AXIM_LONG_BURST_TARGET(targ));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (IS_AXIM_LONG_BURST_TARGET(targ) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_AXIM_AMIB_EnableLongBurst((uint32_t)targ);

  return HAL_OK;
}

/**
  * @brief  Disable long burst for AXIM target.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @retval HAL_INVALID_PARAM if the target does not support long burst.
  * @retval HAL_OK AXIM target long burst is successfully disabled.
  */
hal_status_t HAL_AXIM_TARG_DisableLongBurst(hal_axim_targ_t targ)
{
  ASSERT_DBG_PARAM(IS_AXIM_LONG_BURST_TARGET(targ));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (IS_AXIM_LONG_BURST_TARGET(targ) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_AXIM_AMIB_DisableLongBurst((uint32_t)targ);

  return HAL_OK;
}

/**
  * @brief  Check if the long burst is enabled or disabled for AXIM target.
  * @param  targ AXIM target. This parameter can be one of the following values:
  *         @arg @ref HAL_AXIM_TARG_AHBIC_BRIDGE
  *         @arg @ref HAL_AXIM_TARG_AHBS_BRIDGE
  * @retval AXIM_LONG_BURST_NOT_AVAILABLE if the target does not support long burst.
  * @retval AXIM target long burst enable status.
  */
hal_axim_long_burst_status_t HAL_AXIM_TARG_IsEnabledLongBurst(hal_axim_targ_t targ)
{
  ASSERT_DBG_PARAM(IS_AXIM_LONG_BURST_TARGET(targ));

  if (IS_AXIM_LONG_BURST_TARGET(targ) == 0U)
  {
    return (hal_axim_long_burst_status_t)AXIM_LONG_BURST_NOT_AVAILABLE;
  }
  else
  {
    return (hal_axim_long_burst_status_t)LL_AXIM_AMIB_IsEnabledLongBurst((uint32_t)targ);
  }
}

/**
  * @}
  */

/** @addtogroup AXIM_Exported_Functions_Group3
  *  @{
- This subsection provides a set of functions to get AXIM peripheral and component information.
  - Use HAL_AXIM_GetPeripheralInfo() to get AXIM peripheral information such as the revision, JEP-106 information,
    part number, and file size.
  - Use HAL_AXIM_GetComponentInfo() to get AXIM component information such as the component class and preamble bits.
  */

/**
  * @brief  Get AXIM Peripheral Information.
  * @param  p_periph_info Pointer to AXIM peripheral information structure.
  */
void HAL_AXIM_GetPeripheralInfo(hal_axim_periph_info_t *p_periph_info)
{
  ASSERT_DBG_PARAM(p_periph_info != (void *)NULL);
  p_periph_info->jep_id.jep_continuation_code = LL_AXIM_GetRevisionContinuationCode();
  p_periph_info->jep_id.jep_identity_code     = LL_AXIM_GetJEPID();
  p_periph_info->jep_id.jep_code_flag         = LL_AXIM_GetJEPCodeFlag();
  p_periph_info->file_size_unit4k             = (uint8_t)LL_AXIM_GetFileSize();
  p_periph_info->part_number                  = (uint16_t)LL_AXIM_GetPartNumber();
  p_periph_info->revision                     = (uint8_t)LL_AXIM_GetRevision();
}

/**
  * @brief  Get AXIM Component Information.
  * @param  p_component_info Pointer to AXIM component information structure.
  */
void HAL_AXIM_GetComponentInfo(hal_axim_component_info_t *p_component_info)
{
  ASSERT_DBG_PARAM(p_component_info != (void *)NULL);
  p_component_info->preamble    = LL_AXIM_GetPreamble();
  p_component_info->comp_class  = (uint8_t)LL_AXIM_GetComponentClass();
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

#endif /* USE_HAL_AXIM_MODULE */
#endif /* AXIM */
/**
  * @}
  */
