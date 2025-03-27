/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_hsem.h
  * @author  MCD Application Team
  * @brief   Header file of HSEM LL module.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_LL_HSEM_H
#define STM32MP2xx_LL_HSEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx.h"

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if defined(HSEM)

/** @defgroup HSEM_LL HSEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup HSEM_LL_Exported_Constants HSEM Exported Constants
  * @{
  */

/** @defgroup HSEM_LL_EC_COREID COREID Defines
  * @{
  */
#define LL_HSEM_COREID_NONE             0U
#define LL_HSEM_COREID_CPU1             HSEM_COREID_CPU1
#define LL_HSEM_COREID_CPU2             HSEM_COREID_CPU2
#define LL_HSEM_COREID_CPU3             HSEM_COREID_CPU3
#define LL_HSEM_COREID                  HSEM_CR_COREID_CURRENT

/**
  * @}
  */

/** @defgroup HSEM_LL_EC_ATTRIBUTES Attributes Defines
  * @brief HSEM Privilege/NPrivilege and Secure/NSecure Attributes
  * @{
  */
#define LL_HSEM_NSEC_PRIV    HSEM_R_PRIV                 /*!< NSecure and Privileged attribute  */
#define LL_HSEM_NSEC_NPRIV   0x0U                        /*!< NSecure and NPrivileged attribute */
#define LL_HSEM_SEC_PRIV     (HSEM_R_SEC  | HSEM_R_PRIV) /*!< Secure and Privileged attribute   */
#define LL_HSEM_SEC_NPRIV    HSEM_R_SEC                  /*!< Secure and NPrivileged attribute  */

/**
  * @}
  */

/** @defgroup HSEM_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_HSEM_ReadReg function
  * @{
  */
#define LL_HSEM_SEMAPHORE_0                HSEM_C1IER_ISE0
#define LL_HSEM_SEMAPHORE_1                HSEM_C1IER_ISE1
#define LL_HSEM_SEMAPHORE_2                HSEM_C1IER_ISE2
#define LL_HSEM_SEMAPHORE_3                HSEM_C1IER_ISE3
#define LL_HSEM_SEMAPHORE_4                HSEM_C1IER_ISE4
#define LL_HSEM_SEMAPHORE_5                HSEM_C1IER_ISE5
#define LL_HSEM_SEMAPHORE_6                HSEM_C1IER_ISE6
#define LL_HSEM_SEMAPHORE_7                HSEM_C1IER_ISE7
#define LL_HSEM_SEMAPHORE_8                HSEM_C1IER_ISE8
#define LL_HSEM_SEMAPHORE_9                HSEM_C1IER_ISE9
#define LL_HSEM_SEMAPHORE_10               HSEM_C1IER_ISE10
#define LL_HSEM_SEMAPHORE_11               HSEM_C1IER_ISE11
#define LL_HSEM_SEMAPHORE_12               HSEM_C1IER_ISE12
#define LL_HSEM_SEMAPHORE_13               HSEM_C1IER_ISE13
#define LL_HSEM_SEMAPHORE_14               HSEM_C1IER_ISE14
#define LL_HSEM_SEMAPHORE_15               HSEM_C1IER_ISE15
#define LL_HSEM_SEMAPHORE_ALL              0x0000FFFFU
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup HSEM_LL_Exported_Macros HSEM Exported Macros
  * @{
  */

/** @defgroup HSEM_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in HSEM register
  * @param  __INSTANCE__ HSEM Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_HSEM_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in HSEM register
  * @param  __INSTANCE__ HSEM Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_HSEM_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HSEM_LL_Exported_Functions HSEM Exported Functions
  * @{
  */

/** @defgroup HSEM_LL_EF_Data_Management Data_Management
  * @{
  */


/**
  * @brief  Return 1 if the semaphore is locked, else return 0.
  * @rmtoll R            LOCK          LL_HSEM_IsSemaphoreLocked
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsSemaphoreLocked(HSEM_TypeDef *HSEMx, uint32_t Semaphore)
{
  return ((READ_BIT(HSEMx->R[Semaphore], HSEM_R_LOCK) == (HSEM_R_LOCK_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Get core id.
  * @rmtoll R            COREID        LL_HSEM_GetCoreId
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_HSEM_COREID_NONE
  *         @arg @ref LL_HSEM_COREID_CPU1
  *         @arg @ref LL_HSEM_COREID_CPU2
  */
__STATIC_INLINE uint32_t LL_HSEM_GetCoreId(HSEM_TypeDef *HSEMx, uint32_t Semaphore)
{
  return (uint32_t)(READ_BIT(HSEMx->R[Semaphore], HSEM_R_LOCKID_Msk));
}

/**
  * @brief  Get process id.
  * @rmtoll R            PROCID        LL_HSEM_GetProcessId
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @retval Process number. Value between Min_Data=0 and Max_Data=255
  */
__STATIC_INLINE uint32_t LL_HSEM_GetProcessId(HSEM_TypeDef *HSEMx, uint32_t Semaphore)
{
  return (uint32_t)(READ_BIT(HSEMx->R[Semaphore], HSEM_R_PROCID_Msk));
}

/**
  * @brief  Get Secure Status of compartment.
  * @rmtoll R            SEC        LL_HSEM_GetSecurePrivStatus
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  */
__STATIC_INLINE uint32_t LL_HSEM_GetSecurePrivStatus(HSEM_TypeDef *HSEMx, uint32_t Semaphore)
{
  return (uint32_t)(READ_BIT(HSEMx->R[Semaphore], (LL_HSEM_SEC_PRIV)));
}

/**
  * @brief  Get Compartment Filter Status of the semaphore.
  * @rmtoll R            PRIV        LL_HSEM_GetCompartmentFilterStatus
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @retval Returned value can be one of the following values:
  *         @arg LL_HSEM_CID_NOT_FILTERED  : 0
  *         @arg LL_HSEM_CID_FILTERED      : 1
  */
__STATIC_INLINE uint32_t LL_HSEM_GetCompartmentFilterStatus(HSEM_TypeDef *HSEMx, uint32_t Semaphore)
{
  return (uint32_t)(READ_BIT(HSEMx->R[Semaphore], HSEM_R_CFEN_Msk));
}

/**
  * @brief  Config Secure bit for compartment of semaphore.
  * @rmtoll R            SEC        LL_HSEM_SetSecure
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @param  attribute This parameter can be one of the following values:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_ConfigSecurePriv(HSEM_TypeDef *HSEMx, uint32_t Semaphore, uint32_t attribute)
{
  MODIFY_REG(HSEMx->R[Semaphore], LL_HSEM_SEC_PRIV, attribute);
}

/**
  * @brief  Get the lock by writing in R register.
  * @note The R register has to be read to determined if the lock is taken.
  * @rmtoll R            LOCK          LL_HSEM_SetLock
  * @rmtoll R            COREID        LL_HSEM_SetLock
  * @rmtoll R            PROCID        LL_HSEM_SetLock
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @param  process Process id. Value between Min_Data=0 and Max_Data=255
  * @param  attribute Security and privilege attributes. Value can be one of the following:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_SetLock(HSEM_TypeDef *HSEMx, uint32_t Semaphore, uint32_t process, uint32_t attribute)
{
  WRITE_REG(HSEMx->R[Semaphore], (HSEM_R_LOCK | LL_HSEM_COREID | process | attribute));
}

/**
  * @brief  Get the lock with 2-step lock.
  * @rmtoll R            LOCK          LL_HSEM_2StepLock
  * @rmtoll R            COREID        LL_HSEM_2StepLock
  * @rmtoll R            PROCID        LL_HSEM_2StepLock
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @param  process Process id. Value between Min_Data=0 and Max_Data=255
  * @param  attribute Security and privilege attributes. Value can be one of the following:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  * @retval 1 lock fail, 0 lock successful or already locked by same process and core
  */
__STATIC_INLINE uint32_t LL_HSEM_2StepLock(HSEM_TypeDef *HSEMx, uint32_t Semaphore, uint32_t process,
                                           uint32_t attribute)
{
  WRITE_REG(HSEMx->R[Semaphore], (HSEM_R_LOCK | LL_HSEM_COREID | process | attribute));
  return (((HSEMx->R[Semaphore] & ~HSEM_R_CFEN) != (HSEM_R_LOCK | LL_HSEM_COREID | process | attribute)) ? 1U : 0U);
}

/**
  * @brief  Get the lock with 1-step lock.
  * @rmtoll RLR          LOCK          LL_HSEM_1StepLock
  * @rmtoll RLR          CFEN          LL_HSEM_1StepLock
  * @rmtoll RLR          PRIV          LL_HSEM_1StepLock
  * @rmtoll RLR          SEC           LL_HSEM_1StepLock
  * @rmtoll RLR          COREID        LL_HSEM_1StepLock
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @param  attribute Security and privilege attributes. Value can be one of the following:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  * @retval 1 lock fail, 0 lock successful or already locked by same core
  */
__STATIC_INLINE uint32_t LL_HSEM_1StepLock(HSEM_TypeDef *HSEMx, uint32_t Semaphore, uint32_t attribute)
{
  return (((HSEMx->RLR[Semaphore] & ~HSEM_R_CFEN) != (HSEM_RLR_LOCK | LL_HSEM_COREID | attribute)) ? 1U : 0U);
}

/**
  * @brief  Release the lock of the semaphore.
  * @note In case of LL_HSEM_1StepLock usage to lock a semaphore, the process is 0.
  * @rmtoll R            LOCK          LL_HSEM_ReleaseLock
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @param  process Process number. Value between Min_Data=0 and Max_Data=255
  * @param  attribute Security and privilege attributes. Value can be one of the following:
  *         @arg @ref LL_HSEM_NSEC_PRIV
  *         @arg @ref LL_HSEM_NSEC_NPRIV
  *         @arg @ref LL_HSEM_SEC_PRIV
  *         @arg @ref LL_HSEM_SEC_NPRIV
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_ReleaseLock(HSEM_TypeDef *HSEMx, uint32_t Semaphore, uint32_t process, uint32_t attribute)
{
  WRITE_REG(HSEMx->R[Semaphore], (LL_HSEM_COREID | process | attribute));
}

/**
  * @brief  Get the lock status of the semaphore.
  * @rmtoll R            LOCK          LL_HSEM_GetStatus
  * @param  HSEMx HSEM Instance.
  * @param  Semaphore Semaphore number. Value between Min_Data=0 and Max_Data=15
  * @retval 0 semaphore is free, 1 semaphore is locked  */
__STATIC_INLINE uint32_t LL_HSEM_GetStatus(HSEM_TypeDef *HSEMx, uint32_t Semaphore)
{
  return (((HSEMx->R[Semaphore] & HSEM_R_LOCK) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Set the key.
  * @rmtoll KEYR         KEY           LL_HSEM_SetKey
  * @param  HSEMx HSEM Instance.
  * @param  key Key value.
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_SetKey(HSEM_TypeDef *HSEMx, uint32_t key)
{
  WRITE_REG(HSEMx->KEYR, key << HSEM_KEYR_KEY_Pos);
}

/**
  * @brief  Get the key.
  * @rmtoll KEYR         KEY           LL_HSEM_GetKey
  * @param  HSEMx HSEM Instance.
  * @retval key to unlock all semaphore from the same core
  */
__STATIC_INLINE uint32_t LL_HSEM_GetKey(HSEM_TypeDef *HSEMx)
{
  return (uint32_t)(READ_BIT(HSEMx->KEYR, HSEM_KEYR_KEY) >> HSEM_KEYR_KEY_Pos);
}

/**
  * @brief  Release all semaphore with the same core id.
  * @rmtoll CR           KEY           LL_HSEM_ResetAllLock
  * @param  HSEMx HSEM Instance.
  * @param  key Key value.
  * @param  core This parameter can be one of the following values:
  *         @arg @ref LL_HSEM_COREID_CPU1
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_ResetAllLock(HSEM_TypeDef *HSEMx, uint32_t key, uint32_t core)
{
  WRITE_REG(HSEMx->CR, ((key << HSEM_CR_KEY_Pos) | ((core << HSEM_CR_LOCKID_Pos) & HSEM_CR_LOCKID_Msk)));
  WRITE_REG(HSEMx->CR, (((key << HSEM_CR_KEY_Pos) | ((core << HSEM_CR_LOCKID_Pos) & HSEM_CR_LOCKID_Msk))
                        | HSEM_CR_PRIV));
  WRITE_REG(HSEMx->CR, (((key << HSEM_CR_KEY_Pos) | ((core << HSEM_CR_LOCKID_Pos) & HSEM_CR_LOCKID_Msk))
                        | HSEM_CR_SEC));
  WRITE_REG(HSEMx->CR, (((key << HSEM_CR_KEY_Pos) | ((core << HSEM_CR_LOCKID_Pos) & HSEM_CR_LOCKID_Msk))
                        | HSEM_CR_PRIV | HSEM_CR_SEC));
  WRITE_REG(HSEMx->CR, (((key << HSEM_CR_KEY_Pos) | ((core << HSEM_CR_LOCKID_Pos) & HSEM_CR_LOCKID_Msk))
                        | HSEM_CR_CFEN));
  WRITE_REG(HSEMx->CR, (((key << HSEM_CR_KEY_Pos) | ((core << HSEM_CR_LOCKID_Pos) & HSEM_CR_LOCKID_Msk))
                        | HSEM_CR_PRIV | HSEM_CR_CFEN));
  WRITE_REG(HSEMx->CR, (((key << HSEM_CR_KEY_Pos) | ((core << HSEM_CR_LOCKID_Pos) & HSEM_CR_LOCKID_Msk))
                        | HSEM_CR_SEC | HSEM_CR_CFEN));
  WRITE_REG(HSEMx->CR, (((key << HSEM_CR_KEY_Pos) | ((core << HSEM_CR_LOCKID_Pos) & HSEM_CR_LOCKID_Msk))
                        | HSEM_CR_PRIV | HSEM_CR_SEC | HSEM_CR_CFEN));
}

/**
  * @}
  */

/** @defgroup HSEM_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable interrupt.
  * @rmtoll C1IER         ISEM          LL_HSEM_EnableIT_C1IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_EnableIT_C1IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(HSEMx->SC1IER, SemaphoreMask);
#else
  SET_BIT(HSEMx->C1IER, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Disable interrupt.
  * @rmtoll C1IER          ISEM          LL_HSEM_DisableIT_C1IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_DisableIT_C1IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(HSEMx->SC1IER, SemaphoreMask);
#else
  CLEAR_BIT(HSEMx->C1IER, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Check if interrupt is enabled.
  * @rmtoll C1IER          ISEM          LL_HSEM_IsEnabledIT_C1IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsEnabledIT_C1IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SC1IER, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->C1IER, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}


/**
  * @}
  */

/** @defgroup HSEM_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Clear interrupt status.
  * @rmtoll C1ICR         ISEM          LL_HSEM_ClearFlag_C1ICR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_ClearFlag_C1ICR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  WRITE_REG(HSEMx->SC1ICR, SemaphoreMask);
#else
  WRITE_REG(HSEMx->C1ICR, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Get interrupt status from ISR register.
  * @rmtoll C1ISR         ISEM          LL_HSEM_IsActiveFlag_C1ISR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsActiveFlag_C1ISR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SC1ISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->C1ISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Get interrupt status from MISR register.
  * @rmtoll C1MISR        ISEM          LL_HSEM_IsActiveFlag_C1MISR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsActiveFlag_C1MISR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SC1MISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->C1MISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Enable interrupt.
  * @rmtoll C2IER         ISEM          LL_HSEM_EnableIT_C2IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_EnableIT_C2IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(HSEMx->SC2IER, SemaphoreMask);
#else
  SET_BIT(HSEMx->C2IER, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Disable interrupt.
  * @rmtoll C2IER          ISEM          LL_HSEM_DisableIT_C2IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_DisableIT_C2IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(HSEMx->SC2IER, SemaphoreMask);
#else
  CLEAR_BIT(HSEMx->C2IER, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Check if interrupt is enabled.
  * @rmtoll C2IER          ISEM          LL_HSEM_IsEnabledIT_C2IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsEnabledIT_C2IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SC2IER, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->C2IER, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}


/**
  * @}
  */

/** @defgroup HSEM_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Clear interrupt status.
  * @rmtoll C2ICR         ISEM          LL_HSEM_ClearFlag_C2ICR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_ClearFlag_C2ICR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  WRITE_REG(HSEMx->SC2ICR, SemaphoreMask);
#else
  WRITE_REG(HSEMx->C2ICR, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Get interrupt status from ISR register.
  * @rmtoll C2ISR         ISEM          LL_HSEM_IsActiveFlag_C2ISR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsActiveFlag_C2ISR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SC2ISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->C2ISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Get interrupt status from MISR register.
  * @rmtoll C2MISR        ISEM          LL_HSEM_IsActiveFlag_C2MISR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsActiveFlag_C2MISR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SC2MISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->C2MISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Enable interrupt.
  * @rmtoll C3IER         ISEM          LL_HSEM_EnableIT_C3IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_EnableIT_C3IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SET_BIT(HSEMx->SC3IER, SemaphoreMask);
#else
  SET_BIT(HSEMx->C3IER, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Disable interrupt.
  * @rmtoll C3IER          ISEM          LL_HSEM_DisableIT_C3IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_DisableIT_C3IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  CLEAR_BIT(HSEMx->SC3IER, SemaphoreMask);
#else
  CLEAR_BIT(HSEMx->C3IER, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Check if interrupt is enabled.
  * @rmtoll C3IER          ISEM          LL_HSEM_IsEnabledIT_C3IER
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsEnabledIT_C3IER(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SC3IER, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->C3IER, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}


/**
  * @}
  */

/** @defgroup HSEM_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Clear interrupt status.
  * @rmtoll C3ICR         ISEM          LL_HSEM_ClearFlag_C3ICR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_ClearFlag_C3ICR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  WRITE_REG(HSEMx->SC3ICR, SemaphoreMask);
#else
  WRITE_REG(HSEMx->C3ICR, SemaphoreMask);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Get interrupt status from ISR register.
  * @rmtoll C3ISR         ISEM          LL_HSEM_IsActiveFlag_C3ISR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsActiveFlag_C3ISR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SC3ISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->C3ISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Get interrupt status from MISR register.
  * @rmtoll C3MISR        ISEM          LL_HSEM_IsActiveFlag_C3MISR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsActiveFlag_C3MISR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  return ((READ_BIT(HSEMx->SC3MISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#else
  return ((READ_BIT(HSEMx->C3MISR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
}

/**
  * @brief  Enable Security Configuration.
  * @rmtoll SECCFGR         ISEM          LL_HSEM_Enable_SECCFGR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_Enable_SECCFGR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
  SET_BIT(HSEMx->SECCFGR, SemaphoreMask);
}

/**
  * @brief  Disable Security Configuration.
  * @rmtoll SECCFGR          ISEM          LL_HSEM_Disable_SECCFGR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_Disable_SECCFGR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
  CLEAR_BIT(HSEMx->SECCFGR, SemaphoreMask);
}

/**
  * @brief  Check if Security Configuration is enabled.
  * @rmtoll SECCFGR          ISEM          LL_HSEM_IsEnabled_SECCFGR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsEnabled_SECCFGR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
  return ((READ_BIT(HSEMx->SECCFGR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Privilege Configuration.
  * @rmtoll PRIVCFGR         ISEM          LL_HSEM_Enable_PRIVCFGR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_Enable_PRIVCFGR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
  SET_BIT(HSEMx->PRIVCFGR, SemaphoreMask);
}

/**
  * @brief  Disable Privilege Configuration.
  * @rmtoll PRIVCFGR          ISEM          LL_HSEM_Disable_PRIVCFGR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_Disable_PRIVCFGR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
  CLEAR_BIT(HSEMx->PRIVCFGR, SemaphoreMask);
}

/**
  * @brief  Check if Privilege Configuration is enabled.
  * @rmtoll PRIVCFGR          ISEM          LL_HSEM_IsEnabled_PRIVCFGR
  * @param  HSEMx HSEM Instance.
  * @param  SemaphoreMask This parameter can be a combination of the following values:
  *         @arg @ref LL_HSEM_SEMAPHORE_0
  *         @arg @ref LL_HSEM_SEMAPHORE_1
  *         @arg @ref LL_HSEM_SEMAPHORE_2
  *         @arg @ref LL_HSEM_SEMAPHORE_3
  *         @arg @ref LL_HSEM_SEMAPHORE_4
  *         @arg @ref LL_HSEM_SEMAPHORE_5
  *         @arg @ref LL_HSEM_SEMAPHORE_6
  *         @arg @ref LL_HSEM_SEMAPHORE_7
  *         @arg @ref LL_HSEM_SEMAPHORE_8
  *         @arg @ref LL_HSEM_SEMAPHORE_9
  *         @arg @ref LL_HSEM_SEMAPHORE_10
  *         @arg @ref LL_HSEM_SEMAPHORE_11
  *         @arg @ref LL_HSEM_SEMAPHORE_12
  *         @arg @ref LL_HSEM_SEMAPHORE_13
  *         @arg @ref LL_HSEM_SEMAPHORE_14
  *         @arg @ref LL_HSEM_SEMAPHORE_15
  *         @arg @ref LL_HSEM_SEMAPHORE_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HSEM_IsEnabled_PRIVCFGR(HSEM_TypeDef *HSEMx, uint32_t SemaphoreMask)
{
  return ((READ_BIT(HSEMx->PRIVCFGR, SemaphoreMask) == (SemaphoreMask)) ? 1UL : 0UL);
}

/**
  * @brief  Disable Group CID filtering.
  * @rmtoll G0CIDCFGR         ISEM          LL_HSEM_Disable_Group_CID_Filtering
  * @param  HSEMx HSEM Instance.
  * @param  GroupId This parameter can be a combination of the following values:
  *         @arg Group  : 0
  *         @arg Group  : 1
  *         @arg Group  : 2
  *         @arg Group  : 3
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_Disable_Group_CID_Filtering(HSEM_TypeDef *HSEMx, uint32_t GroupId)
{
  __IO uint32_t *regaddr = ((uint32_t *)(&HSEMx->G0CIDCFGR)) + GroupId;
  CLEAR_BIT(*regaddr, HSEM_G0CIDCFGR_CFEN);
}

/**
  * @brief  Configure Group CID filtering.
  * @rmtoll G0CIDCFGR         ISEM          LL_HSEM_Config_Group_CID_Filtering
  * @param  HSEMx HSEM Instance.
  * @param  GroupId This parameter can be a combination of the following values:
  *         @arg Group  : 0
  *         @arg Group  : 1
  *         @arg Group  : 2
  *         @arg Group  : 3
  * @param  wlist This parameter can be a combination of the following values:
  *         @arg HSEM_COREID_CPU1 whitelist         : 1
  *         @arg HSEM_COREID_CPU2 whitelist         : 2
  *         @arg HSEM_COREID_CPU3 whitelist         : 4
  *         @arg HSEM_COREID_CPU1 & CPU2 whitelist  : 3
  *         @arg HSEM_COREID_CPU1 & CPU3 whitelist  : 5
  *         @arg HSEM_COREID_CPU2 & CPU3 whitelist  : 6
  *         @arg HSEM_CORE All whitelist            : 7
  *         @arg HSEM_CORE All blacklist            : 0
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_Config_Group_CID_Filtering(HSEM_TypeDef *HSEMx, uint32_t GroupId, uint32_t wlist)
{
  __IO uint32_t *regaddr = ((uint32_t *)(&HSEMx->G0CIDCFGR)) + GroupId;
  WRITE_REG(*regaddr, ((wlist << HSEM_G0CIDCFGR_SEM_WLIST_C_Pos) | (HSEM_G0CIDCFGR_CFEN)));
}

/**
  * @brief  Disable Processor CID filtering.
  * @rmtoll C1CIDCFGR         ISEM          LL_HSEM_Disable_Processor_CID_Filtering
  * @param  HSEMx HSEM Instance.
  * @param  ProcessorCID This parameter can be a combination of the following values:
  *         @arg ProcessorCID  : 1
  *         @arg ProcessorCID  : 2
  *         @arg ProcessorCID  : 3
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_Disable_Processor_CID_Filtering(HSEM_TypeDef *HSEMx, uint32_t ProcessorCID)
{
  __IO uint32_t *regaddr = ((uint32_t *)(&HSEMx->C1CIDCFGR)) + (ProcessorCID - 1U);
  CLEAR_BIT(*regaddr, HSEM_C1CIDCFGR_CFEN);
}

/**
  * @brief  Configure Group CID filtering.
  * @rmtoll C1CIDCFGR         ISEM          LL_HSEM_Config_Processor_CID_Filtering
  * @param  HSEMx HSEM Instance.
  * @param  CID This parameter can be a combination of the following values:
  *         @arg CID  : 1
  *         @arg CID  : 2
  *         @arg CID  : 3
  * @param  CIDDomainId Value between Min_Data=0 and Max_Data=7
  * @retval None
  */
__STATIC_INLINE void LL_HSEM_Config_Processor_CID_Filtering(HSEM_TypeDef *HSEMx, uint32_t CID, uint32_t CIDDomainId)
{
  __IO uint32_t *regaddr = ((uint32_t *)(&HSEMx->C1CIDCFGR)) + (CID - 1U);
  WRITE_REG(*regaddr, ((CIDDomainId << HSEM_C1CIDCFGR_CID_Pos) | (HSEM_C1CIDCFGR_CFEN)));
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

#endif /* defined(HSEM) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP2xx_LL_HSEM_H */
