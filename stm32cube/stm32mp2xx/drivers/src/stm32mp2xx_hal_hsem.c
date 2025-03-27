/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_hsem.c
  * @author  MCD Application Team
  * @brief   HSEM HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the semaphore peripheral:
  *           + Semaphore Take function (2-Step Procedure) , non blocking
  *           + Semaphore FastTake function (1-Step Procedure) , non blocking
  *           + Semaphore Status check
  *           + Semaphore Clear Key Set and Get
  *           + Release and release all functions
  *           + Semaphore notification enabling and disabling and callback functions
  *           + IRQ handler management
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
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
  [..]
      (#)Take a semaphore In 2-Step mode Using function HAL_HSEM_Take. This function takes as parameters :
           (++) the semaphore ID from 0 to HSEM_SEMID_MAX
           (++) the process ID from 0 to HSEM_PROCESSID_MAX
      (#) Fast Take semaphore In 1-Step mode Using function HAL_HSEM_FastTake. This function takes as parameter :
           (++) the semaphore ID from 0_ID to HSEM_SEMID_MAX. Note that the process ID value is implicitly assumed
                as zero
      (#) Check if a semaphore is Taken using function HAL_HSEM_IsSemTaken. This function takes as parameter :
          (++) the semaphore ID from 0_ID to HSEM_SEMID_MAX
          (++) It returns 1 if the given semaphore is taken otherwise (Free) zero
      (#)Release a semaphore using function with HAL_HSEM_Release. This function takes as parameters :
           (++) the semaphore ID from 0 to HSEM_SEMID_MAX
           (++) the process ID from 0 to HSEM_PROCESSID_MAX:
           (++) Note: If ProcessID and MasterID match, semaphore is freed, and an interrupt
         may be generated when enabled (notification activated). If ProcessID or MasterID does not match,
         semaphore remains taken (locked)

      (#)Release all semaphores at once taken by a given Master using function HAL_HSEM_Release_All
          This function takes as parameters :
           (++) the Release Key (value from 0 to HSEM_CLEAR_KEY_MAX) can be Set or Get respectively by
              HAL_HSEM_SetClearKey() or HAL_HSEM_GetClearKey functions
           (++) the Master ID:
           (++) Note: If the Key and MasterID match, all semaphores taken by the given CPU that corresponds
           to MasterID  will be freed, and an interrupt may be generated when enabled (notification activated). If the
           Key or the MasterID doesn't match, semaphores remains taken (locked)

      (#)Semaphores Release all key functions:
         (++)  HAL_HSEM_SetClearKey() to set semaphore release all Key
         (++)  HAL_HSEM_GetClearKey() to get release all Key
      (#)Semaphores notification functions :
         (++)  HAL_HSEM_ActivateNotification to activate a notification callback on
               a given semaphores Mask (bitfield). When one or more semaphores defined by the mask are released
               the callback HAL_HSEM_FreeCallback will be asserted giving as parameters a mask of the released
               semaphores (bitfield).

         (++)  HAL_HSEM_DeactivateNotification to deactivate the notification of a given semaphores Mask (bitfield).
         (++) See the description of the macro __HAL_HSEM_SEMID_TO_MASK to check how to calculate a semaphore mask
                Used by the notification functions
     *** HSEM HAL driver macros list ***
     =============================================
     [..] Below the list of most used macros in HSEM HAL driver.

      (+) __HAL_HSEM_SEMID_TO_MASK: Helper macro to convert a Semaphore ID to a Mask.
      [..] Example of use :
      [..] mask = __HAL_HSEM_SEMID_TO_MASK(8)  |  __HAL_HSEM_SEMID_TO_MASK(21) | __HAL_HSEM_SEMID_TO_MASK(25).
      [..] All next macros take as parameter a semaphore Mask (bitfiled) that can be constructed using
           __HAL_HSEM_SEMID_TO_MASK as the above example.
      (+) __HAL_HSEM_ENABLE_IT: Enable the specified semaphores Mask interrupts.
      (+) __HAL_HSEM_DISABLE_IT: Disable the specified semaphores Mask interrupts.
      (+) __HAL_HSEM_GET_IT: Checks whether the specified semaphore interrupt has occurred or not.
      (+) __HAL_HSEM_GET_FLAG: Get the semaphores status release flags.
      (+) __HAL_HSEM_CLEAR_FLAG: Clear the semaphores status release flags.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @defgroup HSEM HSEM
  * @brief HSEM HAL module driver
  * @{
  */

#ifdef HAL_HSEM_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#if defined(DUAL_CORE)
#ifndef HSEM_R_MASTERID
#define HSEM_R_MASTERID HSEM_R_COREID
#endif  /* HSEM_R_MASTERID */

#ifndef HSEM_RLR_MASTERID
#define HSEM_RLR_MASTERID HSEM_RLR_COREID
#endif  /* HSEM_RLR_MASTERID */

#ifndef HSEM_CR_MASTERID
#define HSEM_CR_MASTERID HSEM_CR_COREID
#endif  /* HSEM_CR_MASTERID */
#endif /* DUAL_CORE */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup HSEM_Private_Functions HSEM Private Functions
  * @{
  */
uint32_t HSEM_Is_Running_Secure(void);
uint32_t HSEM_Is_Running_Privilege(void);
/**
  * @}
  */
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup HSEM_Exported_Functions  HSEM Exported Functions
  * @{
  */

/** @defgroup HSEM_Exported_Functions_Group1 Take and Release functions
  *  @brief    HSEM Take and Release functions
  *
@verbatim
 ==============================================================================
              ##### HSEM Take and Release functions #####
 ==============================================================================
[..] This section provides functions allowing to:
      (+) Take a semaphore with 2 Step method
      (+) Fast Take a semaphore with 1 Step method
      (+) Check semaphore state Taken or not
      (+) Release a semaphore
      (+) Release all semaphore at once

@endverbatim
  * @{
  */


/**
  * @brief  Take a semaphore in 2 Step mode.
  * @param  SemID: semaphore ID from 0 to HSEM_SEMID_MAX
  * @param  ProcessID: Process ID from 0 to HSEM_PROCESSID_MAX
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HSEM_Take(uint32_t SemID, uint32_t ProcessID)
{
  /* Check the parameters */
  assert_param(IS_HSEM_SEMID(SemID));
  assert_param(IS_HSEM_PROCESSID(ProcessID));

  uint32_t reg;

  reg = (ProcessID | HSEM_CR_COREID_CURRENT | HSEM_R_LOCK);

  if (HSEM_Is_Running_Secure() != 0U)
  {
    reg |= HSEM_R_SEC;
  }

  if (HSEM_Is_Running_Privilege() != 0U)
  {
    reg |= HSEM_R_PRIV;
  }

  HSEM->R[SemID] = reg;
  if ((HSEM->R[SemID] & ~HSEM_R_CFEN) == reg)
  {
    return HAL_OK;
  }

  /* Semaphore take fails*/
  return HAL_ERROR;
}

/**
  * @brief  Fast Take a semaphore with 1 Step mode.
  * @param  SemID: semaphore ID from 0 to HSEM_SEMID_MAX
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HSEM_FastTake(uint32_t SemID)
{
  /* Check the parameters */
  assert_param(IS_HSEM_SEMID(SemID));

  uint32_t reg;

  reg = (HSEM_CR_COREID_CURRENT | HSEM_RLR_LOCK);

  if (HSEM_Is_Running_Secure() != 0U)
  {
    reg |= HSEM_RLR_SEC;
  }

  if (HSEM_Is_Running_Privilege() != 0U)
  {
    reg |= HSEM_RLR_PRIV;
  }

  /* Read the RLR register to take the semaphore */
  if ((HSEM->RLR[SemID] & ~HSEM_RLR_CFEN) == reg)
  {
    /*take success when MasterID match and take bit set*/
    return HAL_OK;
  }

  /* Semaphore take fails */
  return HAL_ERROR;
}
/**
  * @brief  Check semaphore state Taken or not.
  * @param  SemID: semaphore ID from 0 to HSEM_SEMID_MAX
  * @retval HAL HSEM state (1: semaphore is taken  -  0: semaphore is free)
  */
uint32_t HAL_HSEM_IsSemTaken(uint32_t SemID)
{
  return (((HSEM->R[SemID] & HSEM_R_LOCK) != 0U) ? 1UL : 0UL);
}


/**
  * @brief  Release a semaphore.
  * @param  SemID: semaphore ID from 0 to HSEM_SEMID_MAX
  * @param  ProcessID: Process ID from 0 to HSEM_PROCESSID_MAX
  * @retval None
  */
void HAL_HSEM_Release(uint32_t SemID, uint32_t ProcessID)
{
  /* Check the parameters */
  assert_param(IS_HSEM_SEMID(SemID));
  assert_param(IS_HSEM_PROCESSID(ProcessID));

  uint32_t reg;

  reg = (ProcessID | HSEM_CR_COREID_CURRENT);

  if (HSEM_Is_Running_Secure() != 0U)
  {
    reg |= HSEM_R_SEC;
  }

  if (HSEM_Is_Running_Privilege() != 0U)
  {
    reg |= HSEM_R_PRIV;
  }

  HSEM->R[SemID] = reg;

}

/**
  * @brief  Release all semaphores used by a given Master .
  * @param  Key: Semaphore Key , value from 0 to HSEM_CLEAR_KEY_MAX
  * @param  CoreID: CoreID of the CPU that is using semaphores to be released
  * @retval None
  */
void HAL_HSEM_ReleaseAll(uint32_t Key, uint32_t CoreID)
{
  assert_param(IS_HSEM_KEY(Key));
  assert_param(IS_HSEM_COREID(CoreID));

  uint32_t reg;

  reg = ((Key << HSEM_CR_KEY_Pos) | (CoreID << HSEM_CR_COREID_Pos));

  /* Clear config1: NoPriv + NoSec */
  HSEM->CR = reg;

  /* Clear config2: Priv + NoSec */
  HSEM->CR = (reg | HSEM_CR_PRIV);

  /* Clear config3: NoPriv + Sec */
  HSEM->CR = (reg | HSEM_CR_SEC);

  /* Clear config4: Priv + Sec */
  HSEM->CR = (reg | HSEM_CR_PRIV | HSEM_CR_SEC);

  /* Clear config5: NoPriv + NoSec + CFEN */
  HSEM->CR = (reg | HSEM_CR_CFEN);

  /* Clear config6: Priv + NoSec + CFEN */
  HSEM->CR = (reg | HSEM_CR_PRIV | HSEM_CR_CFEN);

  /* Clear config7: NoPriv + Sec + CFEN */
  HSEM->CR = (reg | HSEM_CR_SEC | HSEM_CR_CFEN);

  /* Clear config8: Priv + Sec + CFEN */
  HSEM->CR = (reg | HSEM_CR_PRIV | HSEM_CR_SEC | HSEM_CR_CFEN);
}

/**
  * @}
  */

/** @defgroup HSEM_Exported_Functions_Group2 HSEM Set and Get Key functions
  *  @brief    HSEM Set and Get Key functions.
  *
@verbatim
  ==============================================================================
              ##### HSEM Set and Get Key functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Set semaphore Key
      (+) Get semaphore Key
@endverbatim

  * @{
  */

/**
  * @brief  Set semaphore Key .
  * @param  Key: Semaphore Key , value from 0 to HSEM_CLEAR_KEY_MAX
  * @retval None
  */
void HAL_HSEM_SetClearKey(uint32_t Key)
{
  assert_param(IS_HSEM_KEY(Key));

  MODIFY_REG(HSEM->KEYR, HSEM_KEYR_KEY, (Key << HSEM_KEYR_KEY_Pos));

}

/**
  * @brief  Get semaphore Key .
  * @retval Semaphore Key , value from 0 to HSEM_CLEAR_KEY_MAX
  */
uint32_t HAL_HSEM_GetClearKey(void)
{
  return (HSEM->KEYR >> HSEM_KEYR_KEY_Pos);
}

/**
  * @}
  */

/** @defgroup HSEM_Exported_Functions_Group3 HSEM IRQ handler management
  *  @brief    HSEM Notification functions.
  *
@verbatim
  ==============================================================================
      ##### HSEM IRQ handler management and Notification functions #####
  ==============================================================================
[..]  This section provides HSEM IRQ handler and Notification function.

@endverbatim
  * @{
  */

/**
  * @brief  Activate Semaphore release Notification for a given Semaphores Mask .
  * @param  SemMask: Mask of Released semaphores
  * @retval None
  */
void HAL_HSEM_ActivateNotification(uint32_t SemMask)
{
  HSEM_COMMON->IER |= SemMask;
}

/**
  * @brief  Deactivate Semaphore release Notification for a given Semaphores Mask .
  * @param  SemMask: Mask of Released semaphores
  * @retval None
  */
void HAL_HSEM_DeactivateNotification(uint32_t SemMask)
{
  HSEM_COMMON->IER &= ~SemMask;
}

/**
  * @brief  This function handles HSEM interrupt request
  * @retval None
  */
void HAL_HSEM_IRQHandler(void)
{
  uint32_t statusreg;
  /* Get the list of masked freed semaphores*/
  statusreg = HSEM_COMMON->MISR;

  /*Disable Interrupts*/
  HSEM_COMMON->IER &= ~((uint32_t)statusreg);

  /*Clear Flags*/
  HSEM_COMMON->ICR = ((uint32_t)statusreg);

  /* Call FreeCallback */
  HAL_HSEM_FreeCallback(statusreg);
}

/**
  * @brief Semaphore Released Callback.
  * @param SemMask: Mask of Released semaphores
  * @retval None
  */
__weak void HAL_HSEM_FreeCallback(uint32_t SemMask)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(SemMask);

  /* NOTE : This function should not be modified, when the callback is needed,
  the HAL_HSEM_FreeCallback can be implemented in the user file
    */
}

/**
  * @}
  */

/** @defgroup HSEM_Exported_Functions_Group4 HSEM RIF protection configuration functions
  *  @brief   HSEM RIF protection configuration functions.
  *
@verbatim
  ==============================================================================
      ##### HSEM RIF protection configuration functions #####
  ==============================================================================
[..]  This section allows to get/set the RIF protection configuration made of
      security, privilege, and cid (compartment id) attributes.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the RIF security and privilege protections of a semaphore
  * @param  SemID: semaphore ID from 0 to HSEM_SEMID_MAX
  * @param  SemAttributes RIF security and privilege protections attributes.
  *           Combination (logical OR) of
  *             @arg HSEM_SEM_PRIV | HSEM_SEM_NPRIV
  *           with
  *             @arg HSEM_SEM_SEC  | HSEM_SEM_NSEC
  * @retval HAL_OK if the configuration is successfully set, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_HSEM_ConfigSemAttributes(uint32_t SemID, uint32_t SemAttributes)
{
  /* Check the parameters */
  assert_param(IS_HSEM_SEMID(SemID));

  /* Configure privilege attribute */
  if ((SemAttributes & HSEM_SEM_PRIV_SELECT) != 0U)
  {
    if ((SemAttributes & HSEM_SEM_PRIV) == HSEM_SEM_PRIV)
    {
      HSEM->PRIVCFGR |= __HAL_HSEM_SEMID_TO_MASK(SemID);
    }
    else
    {
      HSEM->PRIVCFGR &= ~__HAL_HSEM_SEMID_TO_MASK(SemID);
    }
  }

  /* Configure secure attribute */
  if ((SemAttributes & HSEM_SEM_SEC_SELECT) != 0U)
  {
    if ((SemAttributes & HSEM_SEM_SEC) == HSEM_SEM_SEC)
    {
      HSEM->SECCFGR |= __HAL_HSEM_SEMID_TO_MASK(SemID);
    }
    else
    {
      HSEM->SECCFGR &= ~__HAL_HSEM_SEMID_TO_MASK(SemID);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Get the configuration of the RIF security and privilege protections of a semaphore
  * @param  SemID: semaphore ID from 0 to HSEM_SEMID_MAX
  * @param  pSemAttributes pointer to the output RIF security and privilege protections attributes.
  *           Combination (logical OR) of
  *             @arg HSEM_SEM_PRIV | HSEM_SEM_NPRIV
  *           with
  *             @arg HSEM_SEM_SEC  | HSEM_SEM_NSEC
  * @retval HAL_OK if the configuration is successfully read, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_HSEM_GetConfigSemAttributes(uint32_t SemID, uint32_t *pSemAttributes)
{
  HAL_StatusTypeDef err;

  if (pSemAttributes != NULL)
  {
    /* Check the parameters */
    assert_param(IS_HSEM_SEMID(SemID));
    *pSemAttributes = 0U;

    /* Privilege attribute */
    if ((HSEM->PRIVCFGR & __HAL_HSEM_SEMID_TO_MASK(SemID)) != 0U)
    {
      *pSemAttributes |= HSEM_SEM_PRIV;
    }
    else
    {
      *pSemAttributes |= HSEM_SEM_NPRIV;
    }

    /* Secure attribute */
    if ((HSEM->SECCFGR & __HAL_HSEM_SEMID_TO_MASK(SemID)) != 0U)
    {
      *pSemAttributes |= HSEM_SEM_SEC;
    }
    else
    {
      *pSemAttributes |= HSEM_SEM_NSEC;
    }
    err = HAL_OK;
  }
  else
  {
    err = HAL_ERROR;
  }

  return err;
}

/**
  * @brief  Configure the RIF CPU and GROUP CID protection
  * @param  Item CPU or GROUP
  *           @arg HSEM_CPU1
  *           @arg HSEM_CPU2
  *           @arg HSEM_CPU3
  *           @arg HSEM_GROUP0 (CID filtering for Semaphores 0 to 3)
  *           @arg HSEM_GROUP1 (CID filtering for Semaphores 4 to 7)
  *           @arg HSEM_GROUP2 (CID filtering for Semaphores 8 to 11)
  *           @arg HSEM_GROUP3 (CID filtering for Semaphores 12 to 15)
  * @param  Attributes RIF CPU or GROUP CID protection attribute
  *           If Item is set to HSEM_CPUn, then the Attributes values can be:
  *             @arg HSEM_CPU_CID_DISABLE
  *             @arg HSEM_CPU_CID_STATIC_0
  *             ...
  *             @arg HSEM_CPU_CID_STATIC_7
  *           If Item is set to HSEM_GROUPn, then the Attributes values can be:
  *             @arg HSEM_GROUP_CID_DISABLE
  *             or any combination (logical OR) of
  *             @arg HSEM_GROUP_CID_STATIC_1
  *               with
  *             @arg HSEM_GROUP_CID_STATIC_2
  *               with
  *             @arg HSEM_GROUP_CID_STATIC_3
  * @retval HAL_OK if the configuration is successfully set, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_HSEM_ConfigAttributes(uint32_t Item, uint32_t Attributes)
{
  __IO uint32_t *regaddr;
  uint32_t cid;
  uint32_t sem_wlist = 0;

  /* Check the parameters */
  assert_param(IS_HSEM_ITEM_CID(Item));

  if ((Item >= HSEM_GROUP0) && (Item <= HSEM_GROUP3))
  {
    /* Configure GROUP CID attribute */
    regaddr = &HSEM->G0CIDCFGR + (Item - HSEM_GROUP0);

    if ((Attributes & HSEM_GROUP_CID_DISABLE_SELECT) != 0U)
    {
      /* Disable */
      *regaddr &= ~HSEM_G0CIDCFGR_CFEN;
    }
    else if ((Attributes & HSEM_GROUP_CID_STATIC_SELECT) != 0U)
    {
      /* Enable with white list value */
      if ((Attributes & (1U << HSEM_GROUP_CID_CPU1_VAL_Pos)) != 0U)
      {
        sem_wlist |= 1U << 0U;
      }
      if ((Attributes & (1U << HSEM_GROUP_CID_CPU2_VAL_Pos)) != 0U)
      {
        sem_wlist |= 1U << 1U;
      }
      if ((Attributes & (1U << HSEM_GROUP_CID_CPU3_VAL_Pos)) != 0U)
      {
        sem_wlist |= 1U << 2U;
      }

      *regaddr = HSEM_G0CIDCFGR_CFEN  | (sem_wlist << HSEM_G0CIDCFGR_SEM_WLIST_C_Pos);
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Configure CPU CID attribute */
    regaddr = &HSEM->C1CIDCFGR + (Item - HSEM_CPU1);

    if ((Attributes & HSEM_CPU_CID_DISABLE_SELECT) != 0U)
    {
      /* Disable */
      *regaddr &= ~HSEM_C1CIDCFGR_CFEN;
    }
    else if ((Attributes & HSEM_CPU_CID_STATIC_SELECT) != 0U)
    {
      /* Enable */
      cid = (Attributes & HSEM_CPU_CID_VAL_Msk) >> HSEM_CPU_CID_VAL_Pos;
      *regaddr = HSEM_C1CIDCFGR_CFEN | (cid << HSEM_C1CIDCFGR_CID_Pos);
    }
    else
    {
      /* Nothing to do */
    }
  }

  return HAL_OK;
}

/**
  * @brief  Get the configuration of the RIF CPU and GROUP CID protection
  * @param  Item CPU or GROUP
  *           @arg HSEM_CPU1
  *           @arg HSEM_CPU2
  *           @arg HSEM_CPU3
  *           @arg HSEM_GROUP0 (CID filtering for Semaphores 0 to 3)
  *           @arg HSEM_GROUP1 (CID filtering for Semaphores 4 to 7)
  *           @arg HSEM_GROUP2 (CID filtering for Semaphores 8 to 11)
  *           @arg HSEM_GROUP3 (CID filtering for Semaphores 12 to 15)
  * @param  pAttributes pointer to the output RIF CPU and GROUP CID protections attributes.
  *           If Item is set to HSEM_CPUn, then the *pAttributes values can be:
  *             @arg HSEM_CPU_CID_DISABLE
  *             @arg HSEM_CPU_CID_STATIC_0
  *             ...
  *             @arg HSEM_CPU_CID_STATIC_7
  *           If Item is set to HSEM_GROUPn, then the *pAttributes values can be:
  *             @arg HSEM_GROUP_CID_DISABLE
  *             or any combination (logical OR) of
  *             @arg HSEM_GROUP_CID_STATIC_1
  *               with
  *             @arg HSEM_GROUP_CID_STATIC_2
  *               with
  *             @arg HSEM_GROUP_CID_STATIC_3
  * @retval HAL_OK if the configuration is successfully read, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_HSEM_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes)
{
  __I uint32_t *regaddr;
  HAL_StatusTypeDef err;
  uint32_t cid;
  uint32_t sem_wlist;

  if (pAttributes != NULL)
  {
    /* Check the parameters */
    assert_param(IS_HSEM_ITEM_CID(Item));
    *pAttributes = 0;

    if ((Item >= HSEM_GROUP0) && (Item <= HSEM_GROUP3))
    {
      /* Read GROUP CID attribute */
      regaddr = &HSEM->G0CIDCFGR + (Item - HSEM_GROUP0);

      if ((*regaddr & HSEM_G0CIDCFGR_CFEN) == 0U)
      {
        *pAttributes = HSEM_GROUP_CID_DISABLE;
      }
      else
      {
        sem_wlist = (*regaddr & HSEM_G0CIDCFGR_SEM_WLIST_C_Msk) >> HSEM_G0CIDCFGR_SEM_WLIST_C_Pos;
        if ((sem_wlist & (1U << 0U)) != 0U)
        {
          *pAttributes |= HSEM_GROUP_CID_STATIC_1;
        }
        if ((sem_wlist & (1U << 1U)) != 0U)
        {
          *pAttributes |= HSEM_GROUP_CID_STATIC_2;
        }
        if ((sem_wlist & (1U << 2U)) != 0U)
        {
          *pAttributes |= HSEM_GROUP_CID_STATIC_3;
        }
      }
    }
    else
    {
      /* Read CPU CID attribute */
      regaddr = &HSEM->C1CIDCFGR + (Item - HSEM_CPU1);

      if ((*regaddr & HSEM_C1CIDCFGR_CFEN) == 0U)
      {
        *pAttributes = HSEM_CPU_CID_DISABLE;
      }
      else
      {
        cid = (*regaddr & HSEM_C1CIDCFGR_CID_Msk) >> HSEM_C1CIDCFGR_CID_Pos;
        *pAttributes = HSEM_CPU_CID_STATIC_SELECT | (cid << HSEM_CPU_CID_VAL_Pos);
      }
    }
    err = HAL_OK;
  }
  else
  {
    err = HAL_ERROR;
  }

  return err;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup HSEM_Private_Functions
  * @{
  */

/**
  * @brief  Return whether the CPU operates in Secure mode
  * @retval 1: Secure mode  -  0: Non-Secure mode
  */
uint32_t HSEM_Is_Running_Secure(void)
{
#ifdef CORTEX_IN_SECURE_STATE
  return 1UL;
#else
  return 0UL;
#endif /* CORTEX_IN_SECURE_STATE */
}

/**
  * @brief  Return whether the CPU operates in Privilege mode
  * @retval 1: Privilege mode  -  0: Non-Privilege mode
  */
uint32_t HSEM_Is_Running_Privilege(void)
{
#if defined(CORE_CM33) || defined(CORE_CM0PLUS)
  if ((__get_CONTROL() & 0x1U) == 1U)
  {
    return 0UL;
  }
  else
  {
    return 1UL;
  }
#elif defined(CORE_CA35)
  if (__get_mode() == CPSR_M_USR)
  {
    return 0UL;
  }
  else
  {
    return 1UL;
  }
#else /* CORE_xxx */
#error "Unknown cortex"
#endif /* CORE_xxx */
}

/**
  * @}
  */

#endif /* HAL_HSEM_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
