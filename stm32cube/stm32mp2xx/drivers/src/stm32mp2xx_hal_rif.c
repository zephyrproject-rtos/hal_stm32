/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_rif.c
  * @author  MCD Application Team
  * @brief   RIF HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of RIF:
  *           + RISC Initialization and Configuration functions
  *           + IAC Initialization and Configuration functions
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
  ==============================================================================
                  ##### RIF main features #####
  ==============================================================================

  ==============================================================================
                  ##### How to use this driver #####
  ==============================================================================
  [..]
    The RIF HAL driver can be used as follows:

    (#) Configure or get back securable peripherals attributes using
        HAL_RISC_ConfigPeriphAttributes() / HAL_RISC_GetConfigPeriphAttributes()

    (#) Illegal access detection can be configured through IAC sub-block using
        following functions: HAL_IAC_DisableIT() / HAL_IAC_EnableIT()

    (#) Illegal access flags can be retrieved through HAL_IAC_GetFlag() and
        HAL_IAC_ClearFlag() functions

    (#) Illegal access interrupt service routing is served by HAL_RIF_IRQHandler()
        and user can add his own code using HAL_IAC_Callback()

  @endverbatim
  ******************************************************************************
  */
#ifndef STM32MP2xx_HAL_RIF_C
#define STM32MP2xx_HAL_RIF_C

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @defgroup RIF RIF
  * @brief RIF HAL module driver
  * @{
  */

#ifdef HAL_RIF_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup RIF_Exported_Functions RIF Exported Functions
  * @{
  */

/** @defgroup RIF_Exported_Functions_Group1  RISC Configuration functions
  * @brief    RISC Configuration functions
  *
  @verbatim
  ==============================================================================
            ##### RISC Configuration functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to configure RISC
    RISC is Resource isolation Slave Controller
@endverbatim
  * @{
  */
#if defined(CORE_CM33) || defined(CORE_CA35)

#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  Configure RISC on a single peripheral.
  * @param  PeriphAttributes Peripheral attributes, see @ref RIF_Periph_Desc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISC_ConfigPeriphAttributes(RIF_Periph_Desc *PeriphAttributes)
{
  /* Check Periph Attributes */
  if (PeriphAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check Periph Id */
  if (!IS_RIF_PERIPHERAL(PeriphAttributes->PeriphId))
  {
    return HAL_ERROR;
  }

  /* Check Global Lock */
  if (HAL_RIF_IS_RISC_GLOCK())
  {
    return HAL_ERROR;
  }

  /* Check Resource Lock */
  if (HAL_RIF_IS_RISC_RLOCK(PeriphAttributes->PeriphId))
  {
    return HAL_ERROR;
  }

  /* Clear registers before configuration */
  HAL_RIF_CLEAR_RISC_CFEN(PeriphAttributes->PeriphId);
  HAL_RIF_CLEAR_RISC_SEMEN(PeriphAttributes->PeriphId);
  HAL_RIF_CLEAR_RISC_SEC(PeriphAttributes->PeriphId);
  HAL_RIF_CLEAR_RISC_PRIV(PeriphAttributes->PeriphId);

  /* Secure attribute */
  if (PeriphAttributes->SecEnable)
  {
    HAL_RIF_SET_RISC_SEC(PeriphAttributes->PeriphId);
  }
  /* Privilege attribute */
  if (PeriphAttributes->PrivEnable)
  {
    HAL_RIF_SET_RISC_PRIV(PeriphAttributes->PeriphId);
  }

  /* Static CID */
  HAL_RIF_SET_RISC_SCID(PeriphAttributes->PeriphId, PeriphAttributes->Scid);
  /* Semaphore White List */
  HAL_RIF_SET_RISC_SEMWLCX(PeriphAttributes->PeriphId, PeriphAttributes->SemWl);

  /* Compartiment attribute */
  if (PeriphAttributes->CidEnable)
  {
    HAL_RIF_SET_RISC_CFEN(PeriphAttributes->PeriphId);
  }
  /* Semaphore attribute */
  if (PeriphAttributes->SemEnable)
  {
    HAL_RIF_SET_RISC_SEMEN(PeriphAttributes->PeriphId);
  }
  /* Resource Lock attribute */
  if (PeriphAttributes->LockEnable)
  {
    HAL_RIF_SET_RISC_RLOCK(PeriphAttributes->PeriphId);
  }

  return HAL_OK;
}
#endif  /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Get RISC configuration on a single peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref RIF_Peripheral_Identification.
  * @param  PeriphAttributes Peripheral attribute pointer.
  *         This parameter can be a value of @ref RIF_Periph_Desc.
  *         If PeriphId target a single peripheral, pointer on a single element.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISC_GetConfigPeriphAttributes(uint32_t PeriphId, RIF_Periph_Desc *PeriphAttributes)
{
  /* Check Periph Id */
  if (!IS_RIF_PERIPHERAL(PeriphId))
  {
    return HAL_ERROR;
  }

  /* Check Periph Attributes */
  if (PeriphAttributes == NULL)
  {
    return HAL_ERROR;
  }

  PeriphAttributes->PeriphId = PeriphId;
  PeriphAttributes->SecEnable = (uint32_t)HAL_RIF_IS_RISC_SEC(PeriphAttributes->PeriphId);
  PeriphAttributes->PrivEnable = (uint32_t)HAL_RIF_IS_RISC_PRIV(PeriphAttributes->PeriphId);
  PeriphAttributes->CidEnable = (_Bool)HAL_RIF_IS_RISC_CFEN(PeriphAttributes->PeriphId);
  PeriphAttributes->SemEnable = (_Bool)HAL_RIF_IS_RISC_SEMEN(PeriphAttributes->PeriphId);
  PeriphAttributes->Scid = HAL_RIF_READ_RISC_SCID(PeriphAttributes->PeriphId);
  PeriphAttributes->SemWl = HAL_RIF_READ_RISC_SEMWL(PeriphAttributes->PeriphId);
  PeriphAttributes->LockEnable = (uint32_t)HAL_RIF_IS_RISC_RLOCK(PeriphAttributes->PeriphId);

  return HAL_OK;
}

#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  Lock RIF peripheral global configuration.
  * @retval None.
  */
void HAL_RIF_PeriphGLock()
{
  HAL_RIF_SET_RISC_GLOCK();
}
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Get RIF peripheral global lock configuration.
  * @retval Lock State (RIF_PERIPH_GLOCK_OFF or RIF_PERIPH_GLOCK_ON)
  */
uint32_t HAL_RIF_GetPeriphGLock()
{
  return HAL_RIF_IS_RISC_GLOCK();
}

#if defined(RIF_LPSRAM1) && defined(RIF_LPSRAM2) && defined(RIF_LPSRAM3)
/**
  * @}
  */

/** @defgroup RIF_Exported_Functions_Group2 RIF RISAL configuration functions
  * @{
  *
  @verbatim
  ==============================================================================
            ##### RISAL configuration functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to configure RISAL
    RISAL is resource isolation slave unit for address space - Lite version
@endverbatim
  */
#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  RIF RISAL memory configuration.
  * @param  MemAttributes RISAL Memory attribute pointer.
  *         This parameter can be a value of @ref RIF_MemRisal_Desc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISAL_ConfigMemAttributes(RIF_MemRisal_Desc *MemAttributes)
{
  /* Check Mem attributes */
  if (MemAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check RISAL instance */
  if (!IS_RISAL_INSTANCE(MemAttributes->Instance))
  {
    return HAL_ERROR;
  }

  /* Check Global Lock */
  if (HAL_RIF_IS_RISC_GLOCK())
  {
    return HAL_ERROR;
  }

  switch (MemAttributes->Instance)
  {
    case RIF_LPSRAM1:
    {
      if (MemAttributes->SubRegId == RIF_RISAL_MEM_SUBREGA) /* SubRegA */
      {
        /* Clear registers before configuration */
        HAL_RIF_CLEAR_RISAL1_SUBREGA_SREN();
        HAL_RIF_CLEAR_RISAL1_SUBREGA_SEC();
        HAL_RIF_CLEAR_RISAL1_SUBREGA_PRIV();

        if (MemAttributes->SecEnable)
        {
          HAL_RIF_SET_RISAL1_SUBREGA_SEC();
        }
        if (MemAttributes->PrivEnable)
        {
          HAL_RIF_SET_RISAL1_SUBREGA_PRIV();
        }

        HAL_RIF_SET_RISAL1_SUBREGA_SRCID(MemAttributes->Srcid);

        if (MemAttributes->SubRegEnable)
        {
          HAL_RIF_SET_RISAL1_SUBREGA_SREN();
        }
        if (MemAttributes->LockEnable)
        {
          HAL_RIF_SET_RISAL1_SUBREGA_RLOCK();
        }
      }
      else /* SubRegB */
      {
        /* Clear registers before configuration */
        HAL_RIF_CLEAR_RISAL1_SUBREGB_SREN();
        HAL_RIF_CLEAR_RISAL1_SUBREGB_SEC();
        HAL_RIF_CLEAR_RISAL1_SUBREGB_PRIV();

        if (MemAttributes->SecEnable)
        {
          HAL_RIF_SET_RISAL1_SUBREGB_SEC();
        }
        if (MemAttributes->PrivEnable)
        {
          HAL_RIF_SET_RISAL1_SUBREGB_PRIV();
        }

        HAL_RIF_SET_RISAL1_SUBREGB_SRCID(MemAttributes->Srcid);

        if (MemAttributes->SubRegEnable)
        {
          HAL_RIF_SET_RISAL1_SUBREGB_SREN();
        }
        if (MemAttributes->LockEnable)
        {
          HAL_RIF_SET_RISAL1_SUBREGB_RLOCK();
        }
      }
    }
    break;
    case RIF_LPSRAM2:
    {
      if (MemAttributes->SubRegId == RIF_RISAL_MEM_SUBREGA) /* SubRegA */
      {
        /* Clear registers before configuration */
        HAL_RIF_CLEAR_RISAL2_SUBREGA_SREN();
        HAL_RIF_CLEAR_RISAL2_SUBREGA_SEC();
        HAL_RIF_CLEAR_RISAL2_SUBREGA_PRIV();

        if (MemAttributes->SecEnable)
        {
          HAL_RIF_SET_RISAL2_SUBREGA_SEC();
        }
        if (MemAttributes->PrivEnable)
        {
          HAL_RIF_SET_RISAL2_SUBREGA_PRIV();
        }

        HAL_RIF_SET_RISAL2_SUBREGA_SRCID(MemAttributes->Srcid);

        if (MemAttributes->SubRegEnable)
        {
          HAL_RIF_SET_RISAL2_SUBREGA_SREN();
        }
        if (MemAttributes->LockEnable)
        {
          HAL_RIF_SET_RISAL2_SUBREGA_RLOCK();
        }
      }
      else /* SubRegB */
      {
        /* Clear registers before configuration */
        HAL_RIF_CLEAR_RISAL2_SUBREGB_SREN();
        HAL_RIF_CLEAR_RISAL2_SUBREGB_SEC();
        HAL_RIF_CLEAR_RISAL2_SUBREGB_PRIV();

        if (MemAttributes->SecEnable)
        {
          HAL_RIF_SET_RISAL2_SUBREGB_SEC();
        }
        if (MemAttributes->PrivEnable)
        {
          HAL_RIF_SET_RISAL2_SUBREGB_PRIV();
        }

        HAL_RIF_SET_RISAL2_SUBREGB_SRCID(MemAttributes->Srcid);

        if (MemAttributes->SubRegEnable)
        {
          HAL_RIF_SET_RISAL2_SUBREGB_SREN();
        }
        if (MemAttributes->LockEnable)
        {
          HAL_RIF_SET_RISAL2_SUBREGB_RLOCK();
        }
      }
    }
    break;
    case RIF_LPSRAM3:
    {
      if (MemAttributes->SubRegId == RIF_RISAL_MEM_SUBREGA) /* SubRegA */
      {
        /* Clear registers before configuration */
        HAL_RIF_CLEAR_RISAL3_SUBREGA_SREN();
        HAL_RIF_CLEAR_RISAL3_SUBREGA_SEC();
        HAL_RIF_CLEAR_RISAL3_SUBREGA_PRIV();

        if (MemAttributes->SecEnable)
        {
          HAL_RIF_SET_RISAL3_SUBREGA_SEC();
        }
        if (MemAttributes->PrivEnable)
        {
          HAL_RIF_SET_RISAL3_SUBREGA_PRIV();
        }

        HAL_RIF_SET_RISAL3_SUBREGA_SRCID(MemAttributes->Srcid);
        HAL_RIF_SET_RISAL3_SUBREGA_SUBSTART(MemAttributes->SubRegStart / RIF_RISAL_MEM_GRANULARITY);
        HAL_RIF_SET_RISAL3_SUBREGA_SUBLENGTH(MemAttributes->SubRegLength / RIF_RISAL_MEM_GRANULARITY);

        if (MemAttributes->SubRegEnable)
        {
          HAL_RIF_SET_RISAL3_SUBREGA_SREN();
        }
        if (MemAttributes->LockEnable)
        {
          HAL_RIF_SET_RISAL3_SUBREGA_RLOCK();
        }
      }
      else /* SubRegB */
      {
        /* Clear registers before configuration */
        HAL_RIF_CLEAR_RISAL3_SUBREGB_SREN();
        HAL_RIF_CLEAR_RISAL3_SUBREGB_SEC();
        HAL_RIF_CLEAR_RISAL3_SUBREGB_PRIV();

        if (MemAttributes->SecEnable)
        {
          HAL_RIF_SET_RISAL3_SUBREGB_SEC();
        }
        if (MemAttributes->PrivEnable)
        {
          HAL_RIF_SET_RISAL3_SUBREGB_PRIV();
        }

        HAL_RIF_SET_RISAL3_SUBREGB_SRCID(MemAttributes->Srcid);
        HAL_RIF_SET_RISAL3_SUBREGB_SUBSTART(MemAttributes->SubRegStart / RIF_RISAL_MEM_GRANULARITY);
        HAL_RIF_SET_RISAL3_SUBREGB_SUBLENGTH(MemAttributes->SubRegLength / RIF_RISAL_MEM_GRANULARITY);

        if (MemAttributes->SubRegEnable)
        {
          HAL_RIF_SET_RISAL3_SUBREGB_SREN();
        }
        if (MemAttributes->LockEnable)
        {
          HAL_RIF_SET_RISAL3_SUBREGB_RLOCK();
        }
      }
    }
    break;
    default:
    {
      return HAL_ERROR;
    }
    break;
  }
  return HAL_OK;
}
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Get RIF RISAL memory configuration.
  * @param  Instance RISAL Memory instance.
  * @param  SubRegId RISAL Memory sub region id.
  * @param  MemAttributes RISAL Memory attribute pointer.
  *         This parameter can be a value of @ref RIF_MemRisal_Desc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISAL_GetConfigMemAttributes(uint32_t Instance, uint32_t SubRegId, \
                                                   RIF_MemRisal_Desc *MemAttributes)
{
  /* Check RISAL instance */
  if (!IS_RISAL_INSTANCE(Instance))
  {
    return HAL_ERROR;
  }

  /* Check RISAL subreg id */
  if (!IS_RISAL_SUBREG(SubRegId))
  {
    return HAL_ERROR;
  }

  /* Check Mem attributes */
  if (MemAttributes == NULL)
  {
    return HAL_ERROR;
  }

  MemAttributes->Instance = Instance;
  MemAttributes->SubRegId = SubRegId;

  switch (Instance)
  {
    case RIF_LPSRAM1:
      if (SubRegId == RIF_RISAL_MEM_SUBREGA)
      {
        MemAttributes->SecEnable = (uint32_t)HAL_RIF_IS_RISAL1_SUBREGA_SEC();
        MemAttributes->PrivEnable = (uint32_t)HAL_RIF_IS_RISAL1_SUBREGA_PRIV();
        MemAttributes->SubRegEnable = (uint32_t)HAL_RIF_IS_RISAL1_SUBREGA_SREN();
        MemAttributes->LockEnable = (uint32_t)HAL_RIF_IS_RISAL1_SUBREGA_RLOCK();
        MemAttributes->Srcid = HAL_RIF_READ_RISAL1_SUBREGA_SRCID();
        MemAttributes->SubRegStart = 0x0;
        MemAttributes->SubRegLength = 0x0;
      }
      else
      {
        MemAttributes->SecEnable = (uint32_t)HAL_RIF_IS_RISAL1_SUBREGB_SEC();
        MemAttributes->PrivEnable = (uint32_t)HAL_RIF_IS_RISAL1_SUBREGB_PRIV();
        MemAttributes->SubRegEnable = (uint32_t)HAL_RIF_IS_RISAL1_SUBREGB_SREN();
        MemAttributes->LockEnable = (uint32_t)HAL_RIF_IS_RISAL1_SUBREGB_RLOCK();
        MemAttributes->Srcid = HAL_RIF_READ_RISAL1_SUBREGB_SRCID();
        MemAttributes->SubRegStart = 0x0;
        MemAttributes->SubRegLength = 0x0;
      }
      break;
    case RIF_LPSRAM2:
      if (SubRegId == RIF_RISAL_MEM_SUBREGA)
      {
        MemAttributes->SecEnable = (uint32_t)HAL_RIF_IS_RISAL2_SUBREGA_SEC();
        MemAttributes->PrivEnable = (uint32_t)HAL_RIF_IS_RISAL2_SUBREGA_PRIV();
        MemAttributes->SubRegEnable = (uint32_t)HAL_RIF_IS_RISAL2_SUBREGA_SREN();
        MemAttributes->LockEnable = (uint32_t)HAL_RIF_IS_RISAL2_SUBREGA_RLOCK();
        MemAttributes->Srcid = HAL_RIF_READ_RISAL2_SUBREGA_SRCID();
        MemAttributes->SubRegStart = 0x0;
        MemAttributes->SubRegLength = 0x0;
      }
      else
      {
        MemAttributes->SecEnable = (uint32_t)HAL_RIF_IS_RISAL2_SUBREGB_SEC();
        MemAttributes->PrivEnable = (uint32_t)HAL_RIF_IS_RISAL2_SUBREGB_PRIV();
        MemAttributes->SubRegEnable = (uint32_t)HAL_RIF_IS_RISAL2_SUBREGB_SREN();
        MemAttributes->LockEnable = (uint32_t)HAL_RIF_IS_RISAL2_SUBREGB_RLOCK();
        MemAttributes->Srcid = HAL_RIF_READ_RISAL2_SUBREGB_SRCID();
        MemAttributes->SubRegStart = 0x0;
        MemAttributes->SubRegLength = 0x0;
      }
      break;
    case RIF_LPSRAM3:
      if (SubRegId == RIF_RISAL_MEM_SUBREGA)
      {
        MemAttributes->SecEnable = (uint32_t)HAL_RIF_IS_RISAL3_SUBREGA_SEC();
        MemAttributes->PrivEnable = (uint32_t)HAL_RIF_IS_RISAL3_SUBREGA_PRIV();
        MemAttributes->SubRegEnable = (uint32_t)HAL_RIF_IS_RISAL3_SUBREGA_SREN();
        MemAttributes->LockEnable = (uint32_t)HAL_RIF_IS_RISAL3_SUBREGA_RLOCK();
        MemAttributes->Srcid = HAL_RIF_READ_RISAL3_SUBREGA_SRCID();
        MemAttributes->SubRegStart = HAL_RIF_READ_RISAL3_SUBREGA_SUBSTART();
        MemAttributes->SubRegLength = HAL_RIF_READ_RISAL3_SUBREGA_SUBLENGTH();
      }
      else
      {
        MemAttributes->SecEnable = (uint32_t)HAL_RIF_IS_RISAL3_SUBREGB_SEC();
        MemAttributes->PrivEnable = (uint32_t)HAL_RIF_IS_RISAL3_SUBREGB_PRIV();
        MemAttributes->SubRegEnable = (uint32_t)HAL_RIF_IS_RISAL3_SUBREGB_SREN();
        MemAttributes->LockEnable = (uint32_t)HAL_RIF_IS_RISAL3_SUBREGB_RLOCK();
        MemAttributes->Srcid = HAL_RIF_READ_RISAL3_SUBREGB_SRCID();
        MemAttributes->SubRegStart = (RIF_RISAL_MEM_GRANULARITY * HAL_RIF_READ_RISAL3_SUBREGB_SUBSTART());
        MemAttributes->SubRegLength = (RIF_RISAL_MEM_GRANULARITY * HAL_RIF_READ_RISAL3_SUBREGB_SUBLENGTH());
      }
      break;
    default:
      return HAL_ERROR;
      break;
  }
  return HAL_OK;
}
/**
  * @}
  */
#endif /* RISAL1 && RISAL2 && RISAL3 */

/** @defgroup RIF_Exported_Functions_Group3 RIMC functions
  * @{
  *
  @verbatim
  ==============================================================================
            ##### RIMC functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to configure RIMC
    RIMC is resource isolation master controller.
@endverbatim
  */
#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  RIF RIMC trusted attributes configuration.
  * @param  Attributes RIMC Trusted attribute pointer.
  *         This parameter can be a value of @ref RIF_RIMC_TrustedDesc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RIMC_ConfigTrustedAttributes(RIF_RIMC_TrustedDesc *Attributes)
{
  /* Check Attributes */
  if (Attributes == NULL)
  {
    return HAL_ERROR;
  }
  /* Check TD CID */
  if (!IS_RIMC_TDCID(Attributes->TDcid))
  {
    return HAL_ERROR;
  }
  /* Check DAP CID */
  if (!IS_RIMC_DAPCID(Attributes->DAPcid))
  {
    return HAL_ERROR;
  }
  /* Check Global Lock */
  if (HAL_RIF_IS_RIMC_GLOCK())
  {
    return HAL_ERROR;
  }

  /* Configure RIMC Trusted parameters */
  HAL_RIF_SET_RIMC_DAPCID(Attributes->DAPcid);
  HAL_RIF_SET_RIMC_TDCID(Attributes->TDcid);

  return HAL_OK;
}

/**
  * @brief  RIF RIMC master attributes configuration.
  * @param  Attributes RIMC Master attribute pointer.
  *         This parameter can be a value of @ref RIF_RIMC_MasterDesc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RIMC_ConfigMasterAttributes(RIF_RIMC_MasterDesc *Attributes)
{
  /* Check Attributes */
  if (Attributes == NULL)
  {
    return HAL_ERROR;
  }
  /* Check Master ID */
  if (!IS_RIMC_MASTERID(Attributes->MasterId))
  {
    return HAL_ERROR;
  }
  /* Check Master CID */
  if (!IS_RIMC_MASTERCID(Attributes->Mcid))
  {
    return HAL_ERROR;
  }
  /* Check Global Lock */
  if (HAL_RIF_IS_RIMC_GLOCK())
  {
    return HAL_ERROR;
  }

  /* Configure RIMC Master attributes */
  HAL_RIF_SET_RIMC_MCID(Attributes->MasterId, Attributes->Mcid);
  if (Attributes->SecEnable)
  {
    HAL_RIF_SET_RIMC_SEC(Attributes->MasterId);
  }
  if (Attributes->PrivEnable)
  {
    HAL_RIF_SET_RIMC_PRIV(Attributes->MasterId);
  }
  if (Attributes->CidEnable)
  {
    HAL_RIF_SET_RIMC_CIDSEL(Attributes->MasterId);
  }

  return HAL_OK;
}
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Get RIF RIMC trusted attributes configuration.
  * @param  Attributes RIMC Trusted attribute pointer.
  *         This parameter can be a value of @ref RIF_RIMC_TrustedDesc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RIMC_GetConfigTrustedAttributes(RIF_RIMC_TrustedDesc *Attributes)
{
  /* Check Attributes */
  if (Attributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Get RIMC Trusted parameters */
  Attributes->DAPcid = HAL_RIF_READ_RIMC_DAPCID();
  Attributes->TDcid = HAL_RIF_READ_RIMC_TDCID();

  return HAL_OK;
}

/**
  * @brief  Get RIF RIMC master attributes configuration.
  * @param  MasterId RIMC Master Id.
  * @param  Attributes RIMC Master attribute pointer.
  *         This parameter can be a value of @ref RIF_RIMC_MasterDesc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RIMC_GetConfigMasterAttributes(uint32_t MasterId, RIF_RIMC_MasterDesc *Attributes)
{
  /* Check Attributes */
  if (Attributes == NULL)
  {
    return HAL_ERROR;
  }
  /* Check Master ID */
  if (!IS_RIMC_MASTERID(MasterId))
  {
    return HAL_ERROR;
  }

  /* Get RIMC Master attributes */
  Attributes->SecEnable = (uint32_t)HAL_RIF_IS_RIMC_SEC(Attributes->MasterId);
  Attributes->PrivEnable = (uint32_t)HAL_RIF_IS_RIMC_PRIV(Attributes->MasterId);
  Attributes->CidEnable = (_Bool)HAL_RIF_IS_RIMC_CIDSEL(Attributes->MasterId);
  Attributes->Mcid = HAL_RIF_READ_RIMC_MCID(Attributes->MasterId);

  return HAL_OK;
}

#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  Lock RIMC global configuration.
  * @retval None
  */
void HAL_RIMC_GLock()
{
  HAL_RIF_SET_RIMC_GLOCK();
}
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Get RIMC global lock configuration.
  * @retval Lock State (RIF_RIMC_GLOCK_OFF or RIF_RIMC_GLOCK_ON)
  */
uint32_t HAL_RIMC_GetGLock()
{
  return HAL_RIF_IS_RIMC_GLOCK();
}
/**
  * @}
  */

/** @defgroup RIF_Exported_Functions_Group4 RIF RISAB functions
  * @{
  *
  @verbatim
  ==============================================================================
            ##### RISAB functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to configure RISAB
    RISAB is Resource isolation slave unit for address space protection
  (block-based).
@endverbatim
  */
#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  RIF RISAB memory configuration.
  * @param  PageId RISAB Memory Page Id.
  * @param  MemAttributes RISAB Memory attribute pointer.
  *         This parameter can be a value of @ref RIF_MemRisab_Desc.
  *         Same configuration for all pages and blocks by default
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISAB_ConfigMemAttributes(uint32_t PageId, RIF_MemRisab_Desc *MemAttributes)
{
  uint32_t cid;

  /* Check RISAB PageId */
  if (!IS_RISAB_PAGEID(PageId))
  {
    return HAL_ERROR;
  }
  /* Check Mem attributes */
  if (MemAttributes == NULL)
  {
    return HAL_ERROR;
  }
  /* Check RISAB instance */
  if (!IS_RISAB_INSTANCE(MemAttributes->Instance))
  {
    return HAL_ERROR;
  }

  /* Check Global Lock */
  if (HAL_RIF_IS_RISAB_GLOCK(MemAttributes->Instance))
  {
    return HAL_ERROR;
  }
  /* Check Page Lock */
  if (HAL_RIF_IS_RISAB_PG_LOCK(MemAttributes->Instance, PageId))
  {
    return HAL_ERROR;
  }

  /* Get Current CID */
  cid = MemAttributes->Cid;

  /* Reset all registers before configuration */
  HAL_RIF_CLEAR_RISAB_PG_CFEN(MemAttributes->Instance, PageId);
  HAL_RIF_CLEAR_RISAB_PG_DCEN(MemAttributes->Instance, PageId);
  HAL_RIF_CLEAR_RISAB_PG_SEC(MemAttributes->Instance, PageId);
  HAL_RIF_CLEAR_RISAB_PG_PRIV(MemAttributes->Instance, PageId);
#if defined(CORE_CM33)
  HAL_RIF_CLEAR_RISAB_PG_C2_PRIV(MemAttributes->Instance, PageId);
#endif /* defined(CORE_CM33) */
  HAL_RIF_CLEAR_RISAB_PG_CX_PRIV(MemAttributes->Instance, cid, PageId);
  HAL_RIF_CLEAR_RISAB_PG_CX_READ(MemAttributes->Instance, cid, PageId);
  HAL_RIF_CLEAR_RISAB_PG_CX_WRITE(MemAttributes->Instance, cid, PageId);
  HAL_RIF_SET_RISAB_PG_DCCID(MemAttributes->Instance, PageId, 0x0);
  HAL_RIF_CLEAR_RISAB_SRWIAD(MemAttributes->Instance);

  /* Configure RISAB parameters */
  if (MemAttributes->SecAccessEnable)
  {
    HAL_RIF_SET_RISAB_SRWIAD(MemAttributes->Instance);
  }
  if (MemAttributes->PageSecEnable)
  {
    HAL_RIF_SET_RISAB_PG_SEC(MemAttributes->Instance, PageId);
  }
  if (MemAttributes->PagePrivEnable)
  {
    HAL_RIF_SET_RISAB_PG_PRIV(MemAttributes->Instance, PageId);
  }
#if defined(CORE_CM33)
  if (MemAttributes->C2PagePrivEnable)
  {
    HAL_RIF_SET_RISAB_PG_C2_PRIV(MemAttributes->Instance, PageId);
  }
#endif /*defined(CORE_CM33) */
  if (MemAttributes->CidPagePrivEnable)
  {
    HAL_RIF_SET_RISAB_PG_CX_PRIV(MemAttributes->Instance, cid, PageId);
  }
  if (MemAttributes->CidPageReadEnable)
  {
    HAL_RIF_SET_RISAB_PG_CX_READ(MemAttributes->Instance, cid, PageId);
  }
  if (MemAttributes->CidPageWriteEnable)
  {
    HAL_RIF_SET_RISAB_PG_CX_WRITE(MemAttributes->Instance, cid, PageId);
  }
  if (MemAttributes->CidPageEnable)
  {
    HAL_RIF_SET_RISAB_PG_CFEN(MemAttributes->Instance, PageId);
  }
  HAL_RIF_SET_RISAB_PG_DCCID(MemAttributes->Instance, PageId, MemAttributes->Dccid);
  if (MemAttributes->DccidPageEnable)
  {
    HAL_RIF_SET_RISAB_PG_DCEN(MemAttributes->Instance, PageId);
  }
  if (MemAttributes->PageLockEnable)
  {
    HAL_RIF_SET_RISAB_PG_LOCK(MemAttributes->Instance, PageId);
  }

  return HAL_OK;
}
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Get RIF RISAB memory configuration.
  * @param  PageId RISAB Memory Page Id.
  * @param  Cid RISAB Memory Compartiment Id.
  * @param  Instance RISAB Memory instance.
  * @param  MemAttributes RISAB Memory attribute pointer.
  *         This parameter can be a value of @ref RIF_MemRisab_Desc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISAB_GetConfigMemAttributes(uint32_t Instance, uint32_t PageId, \
                                                   uint32_t Cid, RIF_MemRisab_Desc *MemAttributes)
{
  /* Check RISAB instance */
  if (!IS_RISAB_INSTANCE(Instance))
  {
    return HAL_ERROR;
  }
  /* Check RISAB PageId */
  if (!IS_RISAB_PAGEID(PageId))
  {
    return HAL_ERROR;
  }
  /* Check RISAB Cid */
  if (!IS_RISAB_CID(Cid))
  {
    return HAL_ERROR;
  }
  /* Check Mem attributes */
  if (MemAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Reset RISAB parameters */
  MemAttributes->SecAccessEnable = 0;
  MemAttributes->PageSecEnable = 0;
  MemAttributes->PagePrivEnable = 0;
  MemAttributes->CidPageEnable = 0;
  MemAttributes->C2PagePrivEnable = 0;
  MemAttributes->CidPagePrivEnable = 0;
  MemAttributes->CidPageReadEnable = 0;
  MemAttributes->CidPageWriteEnable = 0;
  MemAttributes->DccidPageEnable = 0;
  MemAttributes->Dccid = 0;
  MemAttributes->PageLockEnable = 0;

  /* Get RISAB parameters */
  MemAttributes->Instance = Instance;
  MemAttributes->Cid = Cid;
  MemAttributes->SecAccessEnable = (uint32_t)HAL_RIF_IS_RISAB_SRWIAD(MemAttributes->Instance);
  MemAttributes->CidPagePrivEnable = (_Bool)HAL_RIF_IS_RISAB_PG_CX_PRIV(MemAttributes->Instance, Cid, PageId);
  MemAttributes->CidPageReadEnable = (_Bool)HAL_RIF_IS_RISAB_PG_CX_READ(MemAttributes->Instance, Cid, PageId);
  MemAttributes->CidPageWriteEnable = (_Bool)HAL_RIF_IS_RISAB_PG_CX_WRITE(MemAttributes->Instance, Cid, PageId);
  MemAttributes->CidPageEnable = (_Bool)HAL_RIF_IS_RISAB_PG_CFEN(MemAttributes->Instance, PageId);
  MemAttributes->DccidPageEnable = (_Bool)HAL_RIF_IS_RISAB_PG_DCEN(MemAttributes->Instance, PageId);
  MemAttributes->PageLockEnable = (uint32_t)HAL_RIF_IS_RISAB_PG_LOCK(MemAttributes->Instance, PageId);
  MemAttributes->Dccid = HAL_RIF_READ_RISAB_PG_DCCID(MemAttributes->Instance, PageId);
  if (HAL_RIF_READ_RISAB_PG_SEC(MemAttributes->Instance, PageId) == RISAB_PGSECCFGR_SEC)
  {
    MemAttributes->PageSecEnable = 1;
  }
  if (HAL_RIF_READ_RISAB_PG_PRIV(MemAttributes->Instance, PageId) == RISAB_PGPRIVCFGR_PRIV)
  {
    MemAttributes->PagePrivEnable = 1;
  }
  if (HAL_RIF_READ_RISAB_PG_C2_PRIV(MemAttributes->Instance, PageId) == RISAB_PGC2PRIVCFGR_PRIV)
  {
    MemAttributes->C2PagePrivEnable = 1;
  }

  return HAL_OK;
}

#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  Lock RISAB memory global configuration.
  * @param  Instance RISAB Memory instance.
  * @retval none.
  */
void HAL_RISAB_MemGLock(uint32_t Instance)
{
  /* Check RISAB instance */
  if (IS_RISAB_INSTANCE(Instance))
  {
    HAL_RIF_SET_RISAB_GLOCK(Instance);
  }
}
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Get RISAB memory global lock configuration.
  * @param  Instance RISAB Memory instance.
  * @retval Lock State (RIF_RISAB_LOCK_OFF or RIF_RISAB_LOCK_ON)
  */
uint32_t HAL_RISAB_GetMemGLock(uint32_t Instance)
{
  /* Check RISAB instance */
  if (IS_RISAB_INSTANCE(Instance))
  {
    return HAL_RIF_IS_RISAB_GLOCK(Instance);
  }
  return (RIF_HAL_ERROR);
}
/**
  * @}
  */
/** @defgroup RIF_Exported_Functions_Group5 RIF RISAF functions
  * @{
  *
  @verbatim
  ==============================================================================
            ##### RISAF functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to configure RISAF
    RISAF is Resource isolation slave unit for address space protection
    (full version).
@endverbatim
  */

#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  RIF RISAF memory region configuration.
  * @param  RegionId RISAF Memory Region Id.
  * @param  MemAttributes RISAF Memory attribute pointer.
  *         This parameter can be a value of @ref RIF_MemRisafReg_Desc.
  *         Same configuration for all pages and blocks by default
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISAF_ConfigMemRegionAttributes(uint32_t RegionId, RIF_MemRisafReg_Desc *MemAttributes)
{
  /* Check RISAF RegionId */
  if (!IS_RISAF_REGIONID(RegionId))
  {
    return HAL_ERROR;
  }
  /* Check Mem attributes */
  if (MemAttributes == NULL)
  {
    return HAL_ERROR;
  }
  /* Check RISAF instance */
  if (!IS_RISAF_INSTANCE(MemAttributes->Instance))
  {
    return HAL_ERROR;
  }
  /* Check Global Lock */
  if (HAL_RIF_IS_RISAF_GLOCK(MemAttributes->Instance))
  {
    return HAL_ERROR;
  }
  /* Check CID PRIV */
  if (!IS_RISAF_CIDPRIV(MemAttributes->CidRegPriv))
  {
    return HAL_ERROR;
  }
  /* Check CID READ */
  if (!IS_RISAF_CIDREAD(MemAttributes->CidRegRead))
  {
    return HAL_ERROR;
  }
  /* Check CID WRITE */
  if (!IS_RISAF_CIDWRITE(MemAttributes->CidRegWrite))
  {
    return HAL_ERROR;
  }

  /* Reset all registers before configuration */
  HAL_RIF_CLEAR_RISAF_REG_BREN(MemAttributes->Instance, RegionId);
  HAL_RIF_CLEAR_RISAF_REG_SEC(MemAttributes->Instance, RegionId);
  HAL_RIF_CLEAR_RISAF_REG_ENC(MemAttributes->Instance, RegionId);
  HAL_RIF_CLEAR_RISAF_REG_CIDPRIV(MemAttributes->Instance, RegionId, RISAF_REGCFGR_PRIV);
  HAL_RIF_CLEAR_RISAF_REG_CIDREAD(MemAttributes->Instance, RegionId, RISAF_REGCIDCFGR_RDEN);
  HAL_RIF_CLEAR_RISAF_REG_CIDWRITE(MemAttributes->Instance, RegionId, RISAF_REGCIDCFGR_WREN);

  /* Configure RISAF REGION parameters */
  if (MemAttributes->RegSecEnable)
  {
    HAL_RIF_SET_RISAF_REG_SEC(MemAttributes->Instance, RegionId);
  }
  if (MemAttributes->RegEncEnable)
  {
    HAL_RIF_SET_RISAF_REG_ENC(MemAttributes->Instance, RegionId);
  }
  HAL_RIF_SET_RISAF_REG_CIDPRIV(MemAttributes->Instance, RegionId, MemAttributes->CidRegPriv);
  HAL_RIF_SET_RISAF_REG_CIDREAD(MemAttributes->Instance, RegionId, MemAttributes->CidRegRead);
  HAL_RIF_SET_RISAF_REG_CIDWRITE(MemAttributes->Instance, RegionId, MemAttributes->CidRegWrite);
  if (MemAttributes->Instance == RIF_DDR)
  {
    /* Use absolute base address */
    HAL_RIF_SET_RISAF_REG_STARTR(MemAttributes->Instance, RegionId, MemAttributes->RegAddress);
    HAL_RIF_SET_RISAF_REG_ENDR(MemAttributes->Instance, RegionId\
                               , MemAttributes->RegAddress + MemAttributes->RegSize - 1);
  }
  else
  {
    /* Use offset base address */
    HAL_RIF_SET_RISAF_REG_STARTR(MemAttributes->Instance, RegionId, 0x0);
    HAL_RIF_SET_RISAF_REG_ENDR(MemAttributes->Instance, RegionId, MemAttributes->RegSize - 1);
  }
  if (MemAttributes->RegEnable)
  {
    HAL_RIF_SET_RISAF_REG_BREN(MemAttributes->Instance, RegionId);
  }

  return HAL_OK;
}

/**
  * @brief  RIF RISAF memory subregion configuration.
  * @param  RegionId RISAF Memory Region Id.
  * @param  MemAttributes RISAF Memory attribute pointer.
  *         This parameter can be a value of @ref RIF_MemRisafSubReg_Desc.
  *         Same configuration for all pages and blocks by default
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISAF_ConfigMemSubRegionAttributes(uint32_t RegionId, RIF_MemRisafSubReg_Desc *MemAttributes)
{
  /* Check RISAF RegionId */
  if (!IS_RISAF_REGIONID(RegionId))
  {
    return HAL_ERROR;
  }
  /* Check Mem attributes */
  if (MemAttributes == NULL)
  {
    return HAL_ERROR;
  }
  /* Check RISAF instance */
  if (!IS_RISAF_INSTANCE(MemAttributes->Instance))
  {
    return HAL_ERROR;
  }
  /* Check Global Lock */
  if (HAL_RIF_IS_RISAF_GLOCK(MemAttributes->Instance))
  {
    return HAL_ERROR;
  }
  /* Check RISAF SubRegionId */
  if (!IS_RISAF_SUBREGID(MemAttributes->SubRegId))
  {
    return HAL_ERROR;
  }
  /* Check DCCID */
  if (!IS_RISAF_DCCID(MemAttributes->SubRegDccid))
  {
    return HAL_ERROR;
  }
  /* Check SRCID */
  if (!IS_RISAF_SRCID(MemAttributes->SubRegSrcid))
  {
    return HAL_ERROR;
  }

  if (MemAttributes->SubRegId == RIF_RISAF_MEM_SUBREGA)
  {
    /* Check SubReg Resource Lock */
    if (HAL_RIF_IS_RISAF_SUBREGA_RLOCK(MemAttributes->Instance, RegionId))
    {
      return HAL_ERROR;
    }

    /* Reset all registers before configuration */
    HAL_RIF_CLEAR_RISAF_SUBREGA_SREN(MemAttributes->Instance, RegionId);
    HAL_RIF_CLEAR_RISAF_SUBREGA_SEC(MemAttributes->Instance, RegionId);
    HAL_RIF_CLEAR_RISAF_SUBREGA_PRIV(MemAttributes->Instance, RegionId);
    HAL_RIF_CLEAR_RISAF_SUBREGA_RDEN(MemAttributes->Instance, RegionId);
    HAL_RIF_CLEAR_RISAF_SUBREGA_WREN(MemAttributes->Instance, RegionId);
    HAL_RIF_CLEAR_RISAF_SUBREGA_DCEN(MemAttributes->Instance, RegionId);
    HAL_RIF_SET_RISAF_SUBREGA_DCCID(MemAttributes->Instance, RegionId, 0x0);
    HAL_RIF_SET_RISAF_SUBREGA_SRCID(MemAttributes->Instance, RegionId, 0x0);

    /* Configure RISAF SUBREGION parameters */
    if (MemAttributes->SubRegSecEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGA_SEC(MemAttributes->Instance, RegionId);
    }
    if (MemAttributes->SubRegPrivEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGA_PRIV(MemAttributes->Instance, RegionId);
    }
    if (MemAttributes->SubRegReadEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGA_RDEN(MemAttributes->Instance, RegionId);
    }
    if (MemAttributes->SubRegWriteEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGA_WREN(MemAttributes->Instance, RegionId);
    }
    if (MemAttributes->SubRegDCidEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGA_DCEN(MemAttributes->Instance, RegionId);
    }
    HAL_RIF_SET_RISAF_SUBREGA_DCCID(MemAttributes->Instance, RegionId, MemAttributes->SubRegDccid);
    HAL_RIF_SET_RISAF_SUBREGA_SRCID(MemAttributes->Instance, RegionId, MemAttributes->SubRegSrcid);
    if (MemAttributes->Instance == RIF_DDR)
    {
      /* Use absolute base address */
      HAL_RIF_SET_RISAF_SUBREGA_STARTR(MemAttributes->Instance, RegionId, MemAttributes->SubRegAddress);
      HAL_RIF_SET_RISAF_SUBREGA_ENDR(MemAttributes->Instance, RegionId, \
                                     MemAttributes->SubRegAddress + MemAttributes->SubRegSize - 1);
    }
    else
    {
      /* Use offset base address */
      HAL_RIF_SET_RISAF_SUBREGA_STARTR(MemAttributes->Instance, RegionId, MemAttributes->SubRegAddress);
      HAL_RIF_SET_RISAF_SUBREGA_ENDR(MemAttributes->Instance, RegionId, MemAttributes->SubRegSize - 1);
    }
    if (MemAttributes->SubRegEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGA_SREN(MemAttributes->Instance, RegionId);
    }
    if (MemAttributes->SubRegLockEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGA_RLOCK(MemAttributes->Instance, RegionId);
    }
  }
  else
  {
    /* Check SubReg Resource Lock */
    if (HAL_RIF_IS_RISAF_SUBREGB_RLOCK(MemAttributes->Instance, RegionId))
    {
      return HAL_ERROR;
    }

    /* Reset all registers before configuration */
    HAL_RIF_CLEAR_RISAF_SUBREGB_SREN(MemAttributes->Instance, RegionId);
    HAL_RIF_CLEAR_RISAF_SUBREGB_SEC(MemAttributes->Instance, RegionId);
    HAL_RIF_CLEAR_RISAF_SUBREGB_PRIV(MemAttributes->Instance, RegionId);
    HAL_RIF_CLEAR_RISAF_SUBREGB_RDEN(MemAttributes->Instance, RegionId);
    HAL_RIF_CLEAR_RISAF_SUBREGB_WREN(MemAttributes->Instance, RegionId);
    HAL_RIF_CLEAR_RISAF_SUBREGB_DCEN(MemAttributes->Instance, RegionId);
    HAL_RIF_SET_RISAF_SUBREGB_DCCID(MemAttributes->Instance, RegionId, 0x0);
    HAL_RIF_SET_RISAF_SUBREGB_SRCID(MemAttributes->Instance, RegionId, 0x0);

    /* Configure RISAF SUBREGION parameters */
    if (MemAttributes->SubRegSecEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGB_SEC(MemAttributes->Instance, RegionId);
    }
    if (MemAttributes->SubRegPrivEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGB_PRIV(MemAttributes->Instance, RegionId);
    }
    if (MemAttributes->SubRegReadEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGB_RDEN(MemAttributes->Instance, RegionId);
    }
    if (MemAttributes->SubRegWriteEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGB_WREN(MemAttributes->Instance, RegionId);
    }
    if (MemAttributes->SubRegDCidEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGB_DCEN(MemAttributes->Instance, RegionId);
    }
    HAL_RIF_SET_RISAF_SUBREGB_DCCID(MemAttributes->Instance, RegionId, MemAttributes->SubRegDccid);
    HAL_RIF_SET_RISAF_SUBREGB_SRCID(MemAttributes->Instance, RegionId, MemAttributes->SubRegSrcid);
    if (MemAttributes->Instance == RIF_DDR)
    {
      /* Use absolute base address */
      HAL_RIF_SET_RISAF_SUBREGB_STARTR(MemAttributes->Instance, RegionId, MemAttributes->SubRegAddress);
      HAL_RIF_SET_RISAF_SUBREGB_ENDR(MemAttributes->Instance, RegionId, \
                                     MemAttributes->SubRegAddress + MemAttributes->SubRegSize - 1);
    }
    else
    {
      /* Use offset base address */
      HAL_RIF_SET_RISAF_SUBREGB_STARTR(MemAttributes->Instance, RegionId, MemAttributes->SubRegAddress);
      HAL_RIF_SET_RISAF_SUBREGB_ENDR(MemAttributes->Instance, RegionId, MemAttributes->SubRegSize - 1);
    }
    if (MemAttributes->SubRegEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGB_SREN(MemAttributes->Instance, RegionId);
    }
    if (MemAttributes->SubRegLockEnable)
    {
      HAL_RIF_SET_RISAF_SUBREGB_RLOCK(MemAttributes->Instance, RegionId);
    }
  }

  return HAL_OK;
}

/**
  * @brief  RIF RISAF memory encrypt configuration.
  * @param  MemAttributes RISAF Memory attribute pointer.
  *         This parameter can be a value of @ref RIF_MemRisafEncKey_Desc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISAF_ConfigMemEncryptAttributes(RIF_MemRisafEncKey_Desc *MemAttributes)
{
  /* Check Mem attributes */
  if (MemAttributes == NULL)
  {
    return HAL_ERROR;
  }
  /* Check RISAF instance */
  if (!IS_RISAF_INSTANCE(MemAttributes->Instance))
  {
    return HAL_ERROR;
  }
  /* Check Global Lock */
  if (HAL_RIF_IS_RISAF_GLOCK(MemAttributes->Instance))
  {
    return HAL_ERROR;
  }

  /* Configure RISAF Encryption Key parameters */
  HAL_RIF_SET_RISAF_KEYR(MemAttributes->Instance, 0, MemAttributes->Key0);
  HAL_RIF_SET_RISAF_KEYR(MemAttributes->Instance, 1, MemAttributes->Key1);
  HAL_RIF_SET_RISAF_KEYR(MemAttributes->Instance, 2, MemAttributes->Key2);
  HAL_RIF_SET_RISAF_KEYR(MemAttributes->Instance, 3, MemAttributes->Key3);

  /* Check Key is valid */
  if (!HAL_RIF_IS_RISAF_KEYVALID(MemAttributes->Instance))
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Get RIF RISAF memory configuration.
  * @param  Instance RISAF Memory instance.
  * @param  RegionId RISAF Memory Region Id.
  * @param  MemAttributes RISAF Memory attribute pointer.
  *         This parameter can be a value of @ref RIF_MemRisafReg_Desc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISAF_GetConfigMemRegionAttributes(uint32_t Instance, uint32_t RegionId, \
                                                         RIF_MemRisafReg_Desc *MemAttributes)
{
  /* Check RISAF instance */
  if (!IS_RISAF_INSTANCE(Instance))
  {
    return HAL_ERROR;
  }

  /* Check RISAF RegionId */
  if (!IS_RISAF_REGIONID(RegionId))
  {
    return HAL_ERROR;
  }

  /* Check Mem attributes */
  if (MemAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Get RISAF parameters */
  MemAttributes->Instance = Instance;
  MemAttributes->RegEnable = (uint32_t)HAL_RIF_IS_RISAF_REG_BREN(MemAttributes->Instance, RegionId);
  MemAttributes->RegSecEnable = (uint32_t)HAL_RIF_IS_RISAF_REG_SEC(MemAttributes->Instance, RegionId);
  MemAttributes->RegEncEnable = (uint32_t)HAL_RIF_IS_RISAF_REG_ENC(MemAttributes->Instance, RegionId);
  MemAttributes->CidRegPriv = HAL_RIF_READ_RISAF_REG_CIDPRIV(MemAttributes->Instance, RegionId);
  MemAttributes->CidRegRead = HAL_RIF_READ_RISAF_REG_CIDREAD(MemAttributes->Instance, RegionId);
  MemAttributes->CidRegWrite = HAL_RIF_READ_RISAF_REG_CIDWRITE(MemAttributes->Instance, RegionId);
  MemAttributes->RegAddress = HAL_RIF_READ_RISAF_STARTR(MemAttributes->Instance, RegionId);
  MemAttributes->RegSize = HAL_RIF_READ_RISAF_ENDR(MemAttributes->Instance, RegionId) + 1U;

  return HAL_OK;
}

/**
  * @brief  Get RIF RISAF memory subregion configuration.
  * @param  Instance RISAF Memory instance.
  * @param  RegionId RISAF Memory Region Id.
  * @param  SubRegionId RISAF Memory SubRegion Id.
  * @param  MemAttributes RISAF Memory attribute pointer.
  *         This parameter can be a value of @ref RIF_MemRisafSubReg_Desc.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RISAF_GetConfigMemSubRegionAttributes(uint32_t Instance, uint32_t RegionId, \
                                                            uint32_t SubRegionId, \
                                                            RIF_MemRisafSubReg_Desc *MemAttributes)
{
  /* Check RISAF instance */
  if (!IS_RISAF_INSTANCE(Instance))
  {
    return HAL_ERROR;
  }

  /* Check RISAF RegionId */
  if (!IS_RISAF_REGIONID(RegionId))
  {
    return HAL_ERROR;
  }

  /* Check RISAF SubRegionId */
  if (!IS_RISAF_SUBREGID(SubRegionId))
  {
    return HAL_ERROR;
  }

  /* Check Mem attributes */
  if (MemAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Get RISAF parameters */
  MemAttributes->Instance = Instance;
  MemAttributes->SubRegId = SubRegionId;

  if (MemAttributes->SubRegId == RIF_RISAF_MEM_SUBREGA)
  {
    MemAttributes->SubRegEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGA_SREN(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegSecEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGA_SEC(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegPrivEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGA_PRIV(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegReadEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGA_RDEN(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegWriteEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGA_WREN(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegDCidEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGA_DCEN(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegDccid = HAL_RIF_READ_RISAF_SUBREGA_DCCID(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegSrcid = HAL_RIF_READ_RISAF_SUBREGA_SRCID(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegAddress = HAL_RIF_READ_RISAF_ASTARTR(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegSize = HAL_RIF_READ_RISAF_AENDR(MemAttributes->Instance, RegionId) + 1U;
    MemAttributes->SubRegLockEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGA_RLOCK(MemAttributes->Instance, RegionId);;
  }
  else
  {
    MemAttributes->SubRegEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGB_SREN(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegSecEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGB_SEC(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegPrivEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGB_PRIV(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegReadEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGB_RDEN(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegWriteEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGB_WREN(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegDCidEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGB_DCEN(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegDccid = HAL_RIF_READ_RISAF_SUBREGB_DCCID(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegSrcid = HAL_RIF_READ_RISAF_SUBREGB_SRCID(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegAddress = HAL_RIF_READ_RISAF_BSTARTR(MemAttributes->Instance, RegionId);
    MemAttributes->SubRegSize = HAL_RIF_READ_RISAF_BENDR(MemAttributes->Instance, RegionId) + 1U;
    MemAttributes->SubRegLockEnable = (uint32_t)HAL_RIF_IS_RISAF_SUBREGB_RLOCK(MemAttributes->Instance, RegionId);;
  }

  return HAL_OK;
}

#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  Lock RISAF memory global configuration.
  * @param  Instance RISAF Memory instance.
  * @retval none.
  */
void HAL_RISAF_MemGLock(uint32_t Instance)
{
  /* Check RISAF instance */
  if (IS_RISAF_INSTANCE(Instance))
  {
    HAL_RIF_SET_RISAF_GLOCK(Instance);
  }
}
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Get RISAF memory global lock configuration.
  * @param  Instance RISAF Memory instance.
  * @retval Lock State (RIF_RISAF_LOCK_OFF or RIF_RISAF_LOCK_ON)
  */
uint32_t HAL_RISAF_GetMemGLock(uint32_t Instance)
{
  /* Check RISAF instance */
  if (IS_RISAF_INSTANCE(Instance))
  {
    return HAL_RIF_IS_RISAF_GLOCK(Instance);
  }
  return (RIF_HAL_ERROR);
}

/**
  * @}
  */

/** @defgroup RIF_Exported_Functions_Group6 IAC Configuration and Control functions
  * @brief    IAC Configuration and Controlfunctions
  *
  @verbatim
  ==============================================================================
            ##### IAC Configuration and Control functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to configure and control IAC
    IAC is Illegal Access Controller
@endverbatim
  * @{
  */

/**
  * @brief  Disable the interrupt associated to a single IAC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref RIF_Peripheral_Identification.
  *         Use RIF_PERIPH_ALLIP_Msk to select all peripherals.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_IAC_DisableIT(uint32_t PeriphId)
{
  uint32_t reg_index;

  /* check entry parameters */
  assert_param(IS_RIF_PERIPHERAL(PeriphId));

  if ((PeriphId & RIF_PERIPH_ALLIP_Msk) != 0U)
  {
    /* same configuration is applied to all peripherals */
    for (reg_index = 0; reg_index < RIF_PERIPH_REG_MAX; reg_index++)
    {
      CLEAR_REG(IAC->IER[reg_index]);
    }
  }
  else
  {
    /* common case where only one peripheral is configured */
    CLEAR_BIT(IAC->IER[RIF_GET_REG_INDEX(PeriphId) % (sizeof(IAC->IER) / sizeof(IAC->IER[0]))]\
              , 1U << RIF_GET_PERIPH_POS(PeriphId));
  }

  return HAL_OK;
}

/**
  * @brief  Enable the interrupt associated to a single IAC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref RIF_Peripheral_Identification.
  *         Use RIF_PERIPH_ALLIP_Msk to select all peripherals.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_IAC_EnableIT(uint32_t PeriphId)
{
  uint32_t reg_index;

  /* check entry parameters */
  assert_param(IS_RIF_PERIPHERAL(PeriphId));

  if ((PeriphId & RIF_PERIPH_ALLIP_Msk) != 0U)
  {
    /* same configuration is applied to all peripherals */
    for (reg_index = 0; reg_index < RIF_PERIPH_REG_MAX; reg_index++)
    {
      /* WRITE_REG(IAC->IER[reg_index], RISC_PERIPH_REG_ALL[reg_index]) */
    }
  }
  else
  {
    /* common case where only one peripheral is configured */
    SET_BIT(IAC->IER[RIF_GET_REG_INDEX(PeriphId)\
                     % (sizeof(IAC->IER) / sizeof(IAC->IER[0]))], 1UL << RIF_GET_PERIPH_POS(PeriphId));
  }

  return HAL_OK;
}

/**
  * @brief  Get IAC flag on a single IAC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref RIF_Peripheral_Identification.
  *         To select all peripherals, other usable bits have to be set to 0.
  * @param  Flag Pointer to the flags.
  *         If PeriphId target a single peripheral, pointer on a single element.
  *         If all peripherals selected (RIF_PERIPH_ALLIP_Msk) IAC_PERIPH_NUMBER-size
  *         array elements is to be provided.
  *         Element content is either IAC_NO_ILA_EVENT
  *         or IAC_ILA_EVENT_PENDING
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IAC_GetFlag(uint32_t PeriphId, uint32_t *Flag)
{
  uint32_t i;
  uint32_t reg_index;
  uint32_t reg_value;

  /* check entry parameters */
  assert_param(IS_RIF_PERIPHERAL(PeriphId));

  if (Flag == NULL)
  {
    return HAL_ERROR;
  }

  if ((PeriphId & RIF_PERIPH_ALLIP_Msk) != 0U)
  {
    /* special case where it is applied to all peripherals */
    for (reg_index = 0; reg_index < RIF_PERIPH_REG_MAX; reg_index++)
    {
      reg_value = READ_REG(IAC->ISR[reg_index]);
      for (i = 0U; i < 32U; i++)
      {
        Flag[(reg_index * 32U) + i] = (reg_value & (1UL << i)) >> i;
      }
    }
  }
  else
  {
    /* common case where only one peripheral is concerned */
    Flag[RIF_GET_ARRAY_INDEX(PeriphId)] = READ_BIT(IAC->ISR[RIF_GET_REG_INDEX(PeriphId)\
                                                            % (sizeof(IAC->ISR) / sizeof(IAC->ISR[0]))]\
                                                   , 1UL << RIF_GET_PERIPH_POS(PeriphId));
  }

  return HAL_OK;
}

/**
  * @brief  Clear IAC flag on a single IAC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref RIF_Peripheral_Identification.
  *         Use RIF_PERIPH_ALLIP_Msk to select all peripherals.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_IAC_ClearFlag(uint32_t PeriphId)
{
  uint32_t reg_index;

  /* check entry parameters */
  assert_param(IS_RIF_PERIPHERAL(PeriphId));

  if ((PeriphId & RIF_PERIPH_ALLIP_Msk) != 0U)
  {
    /* same configuration is applied to all peripherals */
    for (reg_index = 0; reg_index < RIF_PERIPH_REG_MAX; reg_index++)
    {
      /*      WRITE_REG(IAC->ICR[reg_index], RISC_PERIPH_REG_ALL[reg_index]) */
    }
  }
  else
  {
    /* common case where only one peripheral is configured */
    SET_BIT((IAC->ICR[RIF_GET_REG_INDEX(PeriphId) % (sizeof(IAC->ICR) / sizeof(IAC->ICR[0]))])\
            , (1UL << (RIF_GET_PERIPH_POS(PeriphId))));
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup RIF_Exported_Functions_Group7 IRQ related functions
  * @brief    IRQ related functions
  *
  @verbatim
  ==============================================================================
            ##### IRQ related functions #####
  ==============================================================================
  [..]
    This section provides RIF IRQ handling and Callback related function
@endverbatim
  * @{
  */

/**
  * @brief  This function handles RIF interrupt request.
  * @retval None.
  */
void HAL_RIF_IRQHandler(void)
{
  /* Get current IT Flags and IT sources value */
  uint32_t reg_index;
  uint32_t flag;
  uint32_t position;

  for (reg_index = 0; reg_index < RIF_PERIPH_REG_MAX; reg_index++)
  {
    /* Get Mask interrupt and then clear them */
    flag = READ_REG(IAC->ISR[reg_index]);
    WRITE_REG(IAC->ICR[reg_index], flag);

    /* Loop on flag to check, which ones have been raised */
    position = 0;
    while ((position < 32U) && ((flag >> position) != 0x00u))
    {
      if ((flag & (1UL << position)) != 0x00u)
      {
        /* Callback with periph_id (add reg pos to find periph id) */
        HAL_IAC_Callback(position | (reg_index << RIF_PERIPH_REG_Pos));
      }

      /* Position bit to be updated */
      position++;
    }
  }
}

/**
  * @brief  RIF IAC sub-block interrupt callback.
  * @retval None.
  */
__weak void HAL_IAC_Callback(uint32_t PeriphId)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(PeriphId);

  /* NOTE: This function should not be modified. When the callback is needed,
   * the HAL_IAC_Callback is to be implemented in the user file
   */
}
#endif /* defined(CORE_CM33) || defined(CORE_CA35) */

/**
  * @}
  */

/**
  * @}
  */

#endif /*HAL_RIF_MODULE_ENABLED*/

/**
  * @}
  */

/**
  * @}
  */

#endif /* STM32MP2xx_HAL_RIF_C */
