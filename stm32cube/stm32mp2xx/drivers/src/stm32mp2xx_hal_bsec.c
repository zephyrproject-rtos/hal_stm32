/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_bsec.c
  * @author  MCD Application Team
  * @brief   BSEC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of Boot and SECurity (BSEC):
  *           + Initialization and de-initialization functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
    The BSEC HAL driver can be used as follows:



    *** High level operation ***
    =================================


    *** Low level operation ***
    =================================


  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

#if defined(BSEC) && defined(HAL_BSEC_MODULE_ENABLED)

/** @defgroup BSEC BSEC
  * @brief BSEC HAL module driver.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup BSEC_Private_Constants BSEC Private Constants
  * @{
  */
#if  defined(BSEC_HDPLSR_HDPL)
#define BSEC_HDPL_INCREMENT_CODE     0x60B166E7U
#endif /*defined(BSEC_HDPLSR_HDPL)*/

#define BSEC_NB_FUSES                376U
#define BSEC_LIMIT_UPPER_FUSES       256U
#define BSEC_NB_SHADOW_REG           BSEC_NB_FUSES

#if  defined(BSEC_EPOCHSELR_EPSEL)
#define BSEC_NB_EPOCH_COUNTER        2U
#endif /*defined(BSEC_EPOCHSELR_EPSEL)*/

#define BSEC_NB_SCRATCH_REG          4U
#define BSEC_NB_WOSCR_REG            8U
#define BSEC_OTPSR_RELOAD_ERRORS     (BSEC_OTPSR_DISTURBF | BSEC_OTPSR_DEDF | BSEC_OTPSR_AMEF)
#define BSEC_SHADOW_REG_WRITE_LIMIT  9U
#define BSEC_TIMEOUT                 1000U
/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup BSEC_Private_Functions BSEC Private Functions
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup BSEC_Exported_Functions BSEC Exported Functions
  * @{
  */

/** @defgroup BSEC_Exported_Functions_Group1 General configuration functions
  *  @brief   General configuration functions
  *
@verbatim
 ===============================================================================
                ##### General configuration functions #####
 ===============================================================================
    [..]
  This subsection provides a set of functions allowing to perform global
  configuration of BSEC.

      (+) Call the function HAL_BSEC_GetStatus() to get the status of BSEC
    peripheral.

      (+) Call the function HAL_BSEC_GlobalLock() to lock the write to BSEC
    registers.

      (+) Call the function HAL_BSEC_GetGlobalLockStatus() to get the global
    write registers lock status.

      (+) Call the function HAL_BSEC_GetErrorCode() to get the error code
    raised when API return HAL_ERROR.

@endverbatim
  * @{
  */

/**
  * @brief  Get the status of BSEC peripheral.
  *
  * @param  pHbsec   BSEC handle
  * @param  pStatus  Returned value of BSEC status. The returned value is @ref BSEC_Status
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GetStatus(BSEC_HandleTypeDef *const pHbsec, uint32_t *pStatus)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pStatus == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  *pStatus = (pHbsec->Instance->OTPSR & (BSEC_OTPSR_INIT_DONE | BSEC_OTPSR_HIDEUP | BSEC_OTPSR_OTPNVIR));

  return HAL_OK;
}

/**
  * @brief  Lock the write to BSEC registers.
  *
  * @param  pHbsec  BSEC handle
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GlobalLock(BSEC_HandleTypeDef *pHbsec)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Set the value of global lock */
  SET_BIT(pHbsec->Instance->LOCKR, BSEC_LOCKR_GWLOCK);

  return HAL_OK;
}

/**
  * @brief  Get the global write registers lock status.
  *
  * @param  pHbsec  BSEC handle
  * @param  pStatus  Returned value of global lock status. The returned value is @ref BSEC_Global_Lock
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GetGlobalLockStatus(BSEC_HandleTypeDef *const pHbsec, uint32_t *pStatus)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pStatus == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Get the global lock status */
  *pStatus = (pHbsec->Instance->LOCKR & BSEC_LOCKR_GWLOCK);

  return HAL_OK;
}

/**
  * @brief  Get the error code of BSEC driver.
  *
  * @param  pHbsec  BSEC handle
  * @param  pError  Returned value of error code. The returned value is @ref BSEC_Error_Code
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GetErrorCode(BSEC_HandleTypeDef *const pHbsec, uint32_t *pError)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value */
  if (pError == NULL)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  *pError = pHbsec->ErrorCode;

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup BSEC_Exported_Functions_Group2 OTP fuse management functions
  *  @brief   OTP fuse management functions
  *
@verbatim
 ===============================================================================
                  ##### OTP fuse management functions #####
 ===============================================================================
    [..]
  This subsection provides a set of functions allowing to manage the OTP fuses.

      (+) Call the function HAL_BSEC_OTP_Read() to read the value of
    an OTP fuse.

      (+) Call the function HAL_BSEC_OTP_Program() to program an OTP
    fuse with or without permanent lock.

      (+) Call the function HAL_BSEC_OTP_Reload() to reload an OTP
    fuse value.

      (+) Call the function HAL_BSEC_OTP_Lock() to sticky lock
    an OTP fuse programming, writing shadowed register or reload.

      (+) Call the function HAL_BSEC_OTP_GetState() to get the sticky lock
    status (programming, writing shadowed register or reload), the permanent
    lock status, the shadow configuration, the ECC or hidden status of an
    OTP fuse.

@endverbatim
  * @{
  */

/**
  * @brief  Read OTP fuse value.
  *
  * @param  pHbsec     BSEC handle
  * @param  FuseId     Fuse to be read, this parameter value is between 0 and 375
  * @param  pFuseData  Returned value of fuse. The returned value is between 0 and 0xFFFFFFFFU
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_OTP_Read(BSEC_HandleTypeDef *const pHbsec, uint32_t FuseId, uint32_t *pFuseData)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pFuseData == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  if (FuseId < BSEC_NB_FUSES)
  {
    /* Reload the data :
       - Unshadowed fuse are not automatically reload and data no more available after register read
       - Shadowed fuse contains by default the shadow value in the register */
    if ((HAL_BSEC_OTP_Reload(pHbsec, FuseId) == HAL_OK))
    {
      /* Read data from shadow register */
      *pFuseData = pHbsec->Instance->FVRw[FuseId];
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Program an OTP fuse with or without permanent lock.
  *
  * @param  pHbsec    BSEC handle
  * @param  FuseId    Fuse to be written, this parameter value is between 0 and 375
  * @param  FuseData  Data to be written in fuse, this parameter value is between 0 and 0xFFFFFFFFU
  * @param  Lock      Permanent lock value, this parameter is @ref BSEC_Permanent_Lock
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_OTP_Program(BSEC_HandleTypeDef *pHbsec, uint32_t FuseId, uint32_t FuseData, uint32_t Lock)
{
  uint32_t status_reg;
  uint32_t status_bit;
  uint32_t read_data;
  uint32_t tick_start = HAL_GetTick();

  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Check the permanent lock */
  assert_param(IS_BSEC_PERMANENT_LOCK(Lock));

  /* Get the correct register value */
  if (FuseId < BSEC_NB_FUSES)
  {
    status_reg = FuseId / 32U;
    status_bit = (uint32_t)(1UL << (FuseId % 32U));

    if ((pHbsec->Instance->SPLOCKx[status_reg] & status_bit) == 0U)
    {
      /* Write data in register */
      pHbsec->Instance->WDR = FuseData;

      /* Perform a program of the fuse register */
      MODIFY_REG(pHbsec->Instance->OTPCR, (BSEC_OTPCR_PPLOCK | BSEC_OTPCR_PROG | BSEC_OTPCR_ADDR),
                 (FuseId | BSEC_OTPCR_PROG | Lock));

      /* Wait the operation is finished */
      while ((pHbsec->Instance->OTPSR & BSEC_OTPSR_BUSY) != 0U)
      {
        if ((HAL_GetTick() - tick_start) > BSEC_TIMEOUT)
        {
          pHbsec->ErrorCode = HAL_BSEC_TIMEOUT_ERROR;
          return HAL_ERROR;
        }
      }

      /* Check programming errors */
      if ((pHbsec->Instance->OTPSR & BSEC_OTPSR_PROGFAIL) != 0U)
      {
        pHbsec->ErrorCode = HAL_BSEC_PROGFAIL_ERROR;
        return HAL_ERROR;
      }

      /* Read back programmed data */
      if (HAL_BSEC_OTP_Read(pHbsec, FuseId, &read_data) == HAL_OK)
      {
        /* Verify programmed data */
        if (read_data != FuseData)
        {
          pHbsec->ErrorCode = HAL_BSEC_PROGFAIL_ERROR;
          return HAL_ERROR;
        }
      }
      else
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Fuse is sticky programming locked */
      pHbsec->ErrorCode = HAL_BSEC_LOCK_ERROR;
      return HAL_ERROR;
    }
  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Reload a OTP fuse value.
  *
  * @param  pHbsec  BSEC handle
  * @param  FuseId  Fuse to be reload, this parameter value is between 0 and 375
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_OTP_Reload(BSEC_HandleTypeDef *pHbsec, uint32_t FuseId)
{
  uint32_t status_reg;
  uint32_t status_bit;
  uint32_t tick_start = HAL_GetTick();

  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  if (FuseId < BSEC_NB_FUSES)
  {
    status_reg = FuseId / 32U;
    status_bit = (uint32_t)(1UL << (FuseId % 32U));

    if ((pHbsec->Instance->SRLOCKx[status_reg] & status_bit) == 0U)
    {
      /* Perform a reload of the fuse register */
      MODIFY_REG(pHbsec->Instance->OTPCR, (BSEC_OTPCR_PPLOCK | BSEC_OTPCR_PROG | BSEC_OTPCR_ADDR), FuseId);

      /* Wait the operation is finished */
      while ((pHbsec->Instance->OTPSR & BSEC_OTPSR_BUSY) != 0U)
      {
        if ((HAL_GetTick() - tick_start) > BSEC_TIMEOUT)
        {
          pHbsec->ErrorCode = HAL_BSEC_TIMEOUT_ERROR;
          return HAL_ERROR;
        }
      }

      if ((pHbsec->Instance->OTPSR & BSEC_OTPSR_RELOAD_ERRORS) != 0U)
      {
        /* An error occurred during reloading, value can't be relied on */
        pHbsec->ErrorCode = (pHbsec->Instance->OTPSR & BSEC_OTPSR_RELOAD_ERRORS);
        return HAL_ERROR;
      }
    }
    else
    {
      /* Shadow register is sticky reload locked */
      pHbsec->ErrorCode = HAL_BSEC_LOCK_ERROR;
      return HAL_ERROR;
    }
  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Sticky lock an OTP fuse programming, writing shadowed register or reload.
  *
  * @param  pHbsec  BSEC handle
  * @param  FuseId  Fuse to lock, this parameter value is between 0 and 375
  * @param  Lock    Lock status of the fuse, this parameter is a combination of
  *                   @ref HAL_BSEC_FUSE_PROG_LOCKED,
  *                   @ref HAL_BSEC_FUSE_WRITE_LOCKED,
  *                   @ref HAL_BSEC_FUSE_RELOAD_LOCKED
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_OTP_Lock(BSEC_HandleTypeDef *pHbsec, uint32_t FuseId, uint32_t Lock)
{
  uint32_t status_reg;
  uint32_t status_bit;

  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Check the lock configuration */
  assert_param(IS_BSEC_LOCK_CFG(Lock));

  if (FuseId < BSEC_NB_FUSES)
  {
    status_reg = FuseId / 32U;
    status_bit = (uint32_t)(1UL << (FuseId % 32U));

    if ((Lock & HAL_BSEC_FUSE_PROG_LOCKED) != 0U)
    {
      /* Programming lock */
      SET_BIT(pHbsec->Instance->SPLOCKx[status_reg], status_bit);
    }

    if ((Lock & HAL_BSEC_FUSE_WRITE_LOCKED) != 0U)
    {
      /* Write lock */
      SET_BIT(pHbsec->Instance->SWLOCKx[status_reg], status_bit);
    }

    if ((Lock & HAL_BSEC_FUSE_RELOAD_LOCKED) != 0U)
    {
      /* Reload lock */
      SET_BIT(pHbsec->Instance->SRLOCKx[status_reg], status_bit);
    }
  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Get the sticky lock status (programming, writing shadowed register
  *         or reload), the permanent lock status, the shadow configuration,
  *         the ECC or hidden status of an OTP fuse.
  *
  * @param  pHbsec  BSEC handle
  * @param  FuseId  Fuse to get the state, this parameter value is between 0 and 375
  * @param  pState  Returned value of state. The returned value is a combination of @ref BSEC_State
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_OTP_GetState(BSEC_HandleTypeDef *const pHbsec, uint32_t FuseId, uint32_t *pState)
{
  uint32_t status_reg;
  uint32_t status_bit;
  uint32_t otpsr_reg;

  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pState == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  if (FuseId < BSEC_NB_FUSES)
  {
    status_reg = FuseId / 32U;
    status_bit = (uint32_t)(1UL << (FuseId % 32U));

    /* Initialize return value */
    *pState = 0U;

    /* Check sticky programming lock */
    if ((pHbsec->Instance->SPLOCKx[status_reg] & status_bit) != 0U)
    {
      *pState |= HAL_BSEC_FUSE_PROG_LOCKED;
    }

    /* Check sticky write lock */
    if ((pHbsec->Instance->SWLOCKx[status_reg] & status_bit) != 0U)
    {
      *pState |= HAL_BSEC_FUSE_WRITE_LOCKED;
    }

    /* Check sticky reload lock */
    if ((pHbsec->Instance->SRLOCKx[status_reg] & status_bit) != 0U)
    {
      *pState |= HAL_BSEC_FUSE_RELOAD_LOCKED;
    }
    else
    {
      /* Check permanent lock : only in case of reload allowed as OTPSR reflect
         status of most recently read word */
      if (HAL_BSEC_OTP_Reload(pHbsec, FuseId) == HAL_OK)
      {
        otpsr_reg = pHbsec->Instance->OTPSR;

        if ((otpsr_reg & BSEC_OTPSR_PPLF) != 0u)
        {
          /* Permanent programming lock detected */
          *pState |= HAL_BSEC_FUSE_LOCKED;
        }
        else if ((otpsr_reg & BSEC_OTPSR_PPLMF) != 0U)
        {
          /* Permanent programming lock on the two lower fuse values in the array are not identical */
          pHbsec->ErrorCode = HAL_BSEC_PPLM_ERROR;
          return HAL_ERROR;
        }
        else
        {
          /* No permanent programming lock detected */
        }
      }
    }

    /* Check shadow configuration */
    if ((pHbsec->Instance->SFSRx[status_reg] & status_bit) != 0U)
    {
      *pState |= HAL_BSEC_FUSE_SHADOWED;
    }

    /* Check hidden status */
    if (((pHbsec->Instance->OTPSR & BSEC_OTPSR_HIDEUP) != 0U) &&
        (FuseId >= BSEC_LIMIT_UPPER_FUSES))
    {
      *pState |= HAL_BSEC_FUSE_HIDDEN;
    }

    /* Check ECC errors on all OTP fuses */
    *pState |= (pHbsec->Instance->OTPSR & (BSEC_OTPSR_OTPERR | BSEC_OTPSR_OTPSEC));

  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup BSEC_Exported_Functions_Group3 Shadow fuse register management functions
  *  @brief   Shadow fuse register management functions
  *
@verbatim
 ===============================================================================
             ##### Shadow fuse register management functions #####
 ===============================================================================
    [..]
  This subsection provides a set of functions allowing to manage the
  shadow fuse registers.

      (+) Call the function HAL_BSEC_OTP_ReadShadow() to read the value of
    a shadow fuse register.

      (+) Call the function HAL_BSEC_OTP_WriteShadow() to write in a shadow
    fuse register.

      (+) Call the function HAL_BSEC_OTP_GetShadowState() to
    get the validity status of a shadow fuse register.

@endverbatim
  * @{
  */

/**
  * @brief  Read the value of a shadow fuse register.
  *
  * @param  pHbsec    BSEC handle
  * @param  RegId     Shadow register to be read, this parameter value is between 0 and 375
  * @param  pRegData  Returned value of register data. The returned value is between 0 and 0xFFFFFFFFU
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_OTP_ReadShadow(BSEC_HandleTypeDef *const pHbsec, uint32_t RegId, uint32_t *pRegData)
{
  uint32_t status_reg;
  uint32_t status_bit;

  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pRegData == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  if (RegId < BSEC_NB_SHADOW_REG)
  {
    status_reg = RegId / 32U;
    status_bit = (uint32_t)(1UL << (RegId % 32U));

    if ((pHbsec->Instance->SFSRx[status_reg] & status_bit) != 0U)
    {
      /* Read data from shadow register */
      *pRegData = pHbsec->Instance->FVRw[RegId];
    }
    else
    {
      /* Fuse is not shadowed */
      pHbsec->ErrorCode = HAL_BSEC_UNALLOWED_ERROR;
      return HAL_ERROR;
    }
  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Write in a shadow fuse register.
  *
  * @param  pHbsec    BSEC handle
  * @param  RegId     Shadow register to be written, this parameter value is between 0 and 375
  * @param  RegData   Data to be written in shadow register, this parameter value is between 0 and 0xFFFFFFFFU
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_OTP_WriteShadow(BSEC_HandleTypeDef *pHbsec, uint32_t RegId, uint32_t RegData)
{
  uint32_t status_reg;
  uint32_t status_bit;

  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Get the correct register value */
  if ((RegId > BSEC_SHADOW_REG_WRITE_LIMIT) && (RegId < BSEC_NB_SHADOW_REG))
  {
    status_reg = RegId / 32U;
    status_bit = (uint32_t)(1UL << (RegId % 32U));

    if ((pHbsec->Instance->SFSRx[status_reg] & status_bit) != 0U)
    {
      if ((pHbsec->Instance->SWLOCKx[status_reg] & status_bit) == 0U)
      {
        /* Value is written in register */
        pHbsec->Instance->FVRw[RegId] = RegData;
      }
      else
      {
        /* Shadow register is sticky write locked */
        pHbsec->ErrorCode = HAL_BSEC_LOCK_ERROR;
        return HAL_ERROR;
      }
    }
    else
    {
      /* Fuse is not shadowed */
      pHbsec->ErrorCode = HAL_BSEC_UNALLOWED_ERROR;
      return HAL_ERROR;
    }
  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Get the validity status of a shadow register.
  *
  * @param  pHbsec     BSEC handle
  * @param  RegId      Shadow register to be checked, this parameter value is between 0 and 375
  * @param  pValidity  Returned value of validity status. The returned value is @ref BSEC_Reload_Validity
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_OTP_GetShadowState(BSEC_HandleTypeDef *const pHbsec, uint32_t RegId, uint32_t *pValidity)
{
  uint32_t status_reg;
  uint32_t status_bit;

  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pValidity == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  if (RegId < BSEC_NB_SHADOW_REG)
  {
    status_reg = RegId / 32U;
    status_bit = (uint32_t)(1UL << (RegId % 32U));

    if ((pHbsec->Instance->SFSRx[status_reg] & status_bit) != 0U)
    {
      if ((pHbsec->Instance->OTPVLDRx[status_reg] & status_bit) != 0U)
      {
        *pValidity = HAL_BSEC_RELOAD_WITHOUT_ERROR;
      }
      else
      {
        *pValidity = HAL_BSEC_RELOAD_WITH_ERROR;
      }
    }
    else
    {
      /* Fuse is not shadowed */
      pHbsec->ErrorCode = HAL_BSEC_UNALLOWED_ERROR;
      return HAL_ERROR;
    }
  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup BSEC_Exported_Functions_Group4 Device life cycle management functions
  *  @brief   Device life cycle management functions
  *
@verbatim
 ===============================================================================
               ##### Device life cycle management functions #####
 ===============================================================================
    [..]
  This subsection provides a set of functions allowing to manage the
  device life cycle.

      (+) Call the function HAL_BSEC_GetDeviceLifeCycleState() to get the
    BSEC device life cycle state.

      (+) Call the function HAL_BSEC_ReadEpochCounter() to read the value
    of epoch counter.

      (+) Call the function HAL_BSEC_SelectEpochCounter() to select the
    epoch counter used by SAES.

      (+) Call the function HAL_BSEC_GetEpochCounterSelection() to get
    the epoch counter selection for SAES.

@endverbatim
  * @{
  */

/**
  * @brief  Get the BSEC device life cycle state.
  *
  * @param  pHbsec  BSEC handle
  * @param  pState  Returned value of device life cycle state. The returned value is @ref BSEC_State
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GetDeviceLifeCycleState(BSEC_HandleTypeDef *const pHbsec, uint32_t *pState)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pState == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Return the state */
  *pState = (pHbsec->Instance->SR & BSEC_SR_NVSTATE);

  if (IS_BSEC_STATE(*pState))
  {
    return HAL_OK;
  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_UNDEFINED_VALUE_ERROR;
    return HAL_ERROR;
  }
}

#if  defined(BSEC_EPOCHSELR_EPSEL)
/**
  * @brief  Read the value of epoch counter.
  *
  * @param  pHbsec        BSEC handle
  * @param  CounterId     Identifier of the epoch counter to be read, this parameter can be @ref BSEC_Epoch_Select
  * @param  pCounterData  Returned value of epoch counter data. The returned value is between 0 and 0xFFFFFFFFU
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_ReadEpochCounter(BSEC_HandleTypeDef *const pHbsec,
                                            uint32_t CounterId, uint32_t *pCounterData)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pCounterData == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Get the correct register value */
  if (CounterId < BSEC_NB_EPOCH_COUNTER)
  {
    *pCounterData = pHbsec->Instance->EPOCHRx[CounterId];
  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Select the epoch counter used by SAES.
  *
  * @param  pHbsec            BSEC handle
  * @param  SelectedCounter   Epoch selected counter, this parameter can be @ref BSEC_Epoch_Select
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_SelectEpochCounter(BSEC_HandleTypeDef *pHbsec, uint32_t SelectedCounter)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Check the epoch counter selection */
  assert_param(IS_BSEC_EPOCHSEL(SelectedCounter));

  /* Update the selected epoch counter value */
  MODIFY_REG(pHbsec->Instance->EPOCHSELR, BSEC_EPOCHSELR_EPSEL, SelectedCounter);

  return HAL_OK;
}

/**
  * @brief  Get the epoch counter selection for SAES.
  *
  * @param  pHbsec            BSEC handle
  * @param  pSelectedCounter  Returned value of epoch selected counter. The returned value is @ref BSEC_Epoch_Select
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GetEpochCounterSelection(BSEC_HandleTypeDef *const pHbsec, uint32_t *pSelectedCounter)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pSelectedCounter == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Return the debug request */
  *pSelectedCounter = (pHbsec->Instance->EPOCHSELR & BSEC_EPOCHSELR_EPSEL);

  return HAL_OK;
}
#endif /* defined(BSEC_EPOCHSELR_EPSEL) */

/**
  * @}
  */
#if  defined(BSEC_HDPLSR_HDPL)
/** @defgroup BSEC_Exported_Functions_Group5 HDPL management functions
  *  @brief   HDPL management functions
  *
@verbatim
 ===============================================================================
                     ##### HDPL management functions #####
 ===============================================================================
    [..]
  This subsection provides a set of functions allowing to manage the
  HDPL (Hide Protection Level).

      (+) Call the function HAL_BSEC_GetHDPLValue() to get the current HDPL.

      (+) Call the function HAL_BSEC_IncrementHDPLValue() to increment the HDPL.

      (+) Call the function HAL_BSEC_ConfigSAESHDPLIncrementValue() to configure
    the increment of HDPL sent to SAES.

      (+) Call the function HAL_BSEC_GetSAESHDPLIncrementValue() to get the SAES
    increment to HDPL.

@endverbatim
  * @{
  */

/**
  * @brief  Get the current HDPL.
  *
  * @param  pHbsec  BSEC handle
  * @param  pHDPL   Returned value of current HDPL. The returned value is @ref BSEC_HDPL
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GetHDPLValue(BSEC_HandleTypeDef *const pHbsec, uint32_t *pHDPL)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pHDPL == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Return the HDPL */
  *pHDPL = (pHbsec->Instance->HDPLSR & BSEC_HDPLSR_HDPL);

  if (IS_BSEC_HDPL(*pHDPL))
  {
    return HAL_OK;
  }
  else
  {
    pHbsec->ErrorCode = HAL_BSEC_UNDEFINED_VALUE_ERROR;
    return HAL_ERROR;
  }
}

/**
  * @brief  Increment the HDPL.
  *
  * @param  pHbsec  BSEC handle
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_IncrementHDPLValue(BSEC_HandleTypeDef *pHbsec)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Increment HDPL value */
  pHbsec->Instance->HDPLCR = BSEC_HDPL_INCREMENT_CODE;

  return HAL_OK;
}

/**
  * @brief  Configure the increment of HDPL sent to SAES.
  *
  * @param  pHbsec      BSEC handle
  * @param  Increment   Value of HDPL increment, this parameter value can be between 0 and 3
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_ConfigSAESHDPLIncrementValue(BSEC_HandleTypeDef *pHbsec, uint32_t Increment)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Check the debug configuration */
  assert_param(IS_BSEC_NEXTHDPL(Increment));

  /* Write HDPL increment value */
  MODIFY_REG(pHbsec->Instance->NEXTLR, BSEC_NEXTLR_INCR, Increment);

  return HAL_OK;
}

/**
  * @brief  Get the SAES increment to HDPL.
  *
  * @param  pHbsec      BSEC handle
  * @param  pIncrement  Returned value of HDPL increment. The returned value is between 0 and 3
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GetSAESHDPLIncrementValue(BSEC_HandleTypeDef *const pHbsec, uint32_t *pIncrement)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pIncrement == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Return the debug request */
  *pIncrement = (pHbsec->Instance->NEXTLR & BSEC_NEXTLR_INCR);

  return HAL_OK;
}
/**
  * @}
  */
#endif /*defined(BSEC_HDPLSR_HDPL) */
/** @defgroup BSEC_Exported_Functions_Group6 Scratch registers management functions
  *  @brief   Scratch registers management functions
  *
@verbatim
 ===============================================================================
               ##### Scratch registers management functions #####
 ===============================================================================
    [..]
  This subsection provides a set of functions allowing to manage the
  write once scratch and scratch registers.

      (+) Call the function HAL_BSEC_WriteScratchValue() to write a value in
    write once scratch or scratch register.

      (+) Call the function HAL_BSEC_ReadScratchValue() to read a value from
    write once scratch or scratch register.

@endverbatim
  * @{
  */

/**
  * @brief  Write a value in write once scratch or scratch register.
  *
  * @param  pHbsec    BSEC handle
  * @param  pRegAddr  Register to be written
  * @param  Data      Data to be written, this parameter can be a value between 0 and 0xFFFFFFFFU
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_WriteScratchValue(BSEC_HandleTypeDef *pHbsec,
                                             BSEC_ScratchRegTypeDef *const pRegAddr, uint32_t Data)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the register configuration and instance */
  if ((pRegAddr == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Check the debug configuration */
  assert_param(IS_BSEC_REGTYPE(pRegAddr->RegType));

  /* Write data in correct register */
  if (pRegAddr->RegType == HAL_BSEC_SCRATCH_REG)
  {
    if (pRegAddr->RegNumber < BSEC_NB_SCRATCH_REG)
    {
      pHbsec->Instance->SCRATCHRx[pRegAddr->RegNumber] = Data;
    }
    else
    {
      pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
      return HAL_ERROR;
    }
  }
  else
  {
    if (pRegAddr->RegNumber < BSEC_NB_WOSCR_REG)
    {
      pHbsec->Instance->WOSCRx[pRegAddr->RegNumber] = Data;
    }
    else
    {
      pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Read a value from write once scratch or scratch register.
  *
  * @param  pHbsec    BSEC handle
  * @param  pRegAddr  Register to be read
  * @param  pRegData  Returned value of register data. The returned value is between 0 and 0xFFFFFFFFU
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_ReadScratchValue(BSEC_HandleTypeDef *const pHbsec,
                                            BSEC_ScratchRegTypeDef *const pRegAddr, uint32_t *pRegData)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the register configuration, address of returned value and instance */
  if ((pRegAddr == NULL) || (pRegData == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Check the debug configuration */
  assert_param(IS_BSEC_REGTYPE(pRegAddr->RegType));

  /* Get the correct register value */
  if (pRegAddr->RegType == HAL_BSEC_SCRATCH_REG)
  {
    if (pRegAddr->RegNumber < BSEC_NB_SCRATCH_REG)
    {
      *pRegData = pHbsec->Instance->SCRATCHRx[pRegAddr->RegNumber];
    }
    else
    {
      pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
      return HAL_ERROR;
    }
  }
  else
  {
    if (pRegAddr->RegNumber < BSEC_NB_WOSCR_REG)
    {
      *pRegData = pHbsec->Instance->WOSCRx[pRegAddr->RegNumber];
    }
    else
    {
      pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @}
  */
/**
  * @brief  Send data via JTAG.
  *
  * @param  pHbsec  BSEC handle
  * @param  Data    Data to be sent via JTAG, this parameter can be a value between 0 and 0xFFFFFFFFU
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_SendJTAGData(BSEC_HandleTypeDef *pHbsec, uint32_t Data)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Send the data */
  pHbsec->Instance->JTAGOUTR = Data;

  return HAL_OK;
}

/**
  * @brief  Receive data via JTAG.
  *
  * @param  pHbsec  BSEC handle
  * @param  pData   Returned value of received data. The returned value is between 0 and 0xFFFFFFFFU
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_ReceiveJTAGData(BSEC_HandleTypeDef *const pHbsec, uint32_t *pData)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pData == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Return the received data */
  *pData = pHbsec->Instance->JTAGINR;

  return HAL_OK;
}
/** @defgroup BSEC_Exported_Functions_Group8 DHUK management functions
  *  @brief   DHUK management functions
  *
@verbatim
 ===============================================================================
                    ##### DHUK management functions #####
 ===============================================================================
    [..]
  This subsection provides a set of functions allowing to manage the
  DHUK (Derived Hardware Unique Key).

      (+) Call the function HAL_BSEC_GetDHUKValidity() to get the validity
    of DHUK.

      (+) Call the function HAL_BSEC_LockDHUKUse() to lock the DHUK use.

      (+) Call the function HAL_BSEC_GetDHUKLockStatus() to get the DHUK
    lock status.

@endverbatim
  * @{
  */

/**
  * @brief  Get the validity of DHUK.
  *
  * @param  pHbsec     BSEC handle
  * @param  pValidity  Returned value of DHUK validity. The returned value is @ref BSEC_DHUK_Validity
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GetDHUKValidity(BSEC_HandleTypeDef *const pHbsec, uint32_t *pValidity)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pValidity == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Get the DHUK validity */
  *pValidity = (pHbsec->Instance->SR & BSEC_SR_HVALID);

  return HAL_OK;
}

/**
  * @brief  Lock the DHUK use.
  *
  * @param  pHbsec  BSEC handle
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_LockDHUKUse(BSEC_HandleTypeDef *pHbsec)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Set the value of the DHUK lock */
  SET_BIT(pHbsec->Instance->LOCKR, BSEC_LOCKR_HKLOCK);

  return HAL_OK;
}

/**
  * @brief  Get the DHUK lock status.
  *
  * @param  pHbsec   BSEC handle
  * @param  pStatus  Returned value of DHUK lock status. The returned value is @ref BSEC_DHUK_Lock
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GetDHUKLockStatus(BSEC_HandleTypeDef *const pHbsec, uint32_t *pStatus)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pStatus == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Get the DHUK lock status */
  *pStatus = (pHbsec->Instance->LOCKR & BSEC_LOCKR_HKLOCK);

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup BSEC_Exported_Functions_Group9 Reset management functions
  *  @brief   Reset management functions
  *
@verbatim
 ===============================================================================
                    ##### Reset management functions #####
 ===============================================================================
    [..]
  This subsection provides a set of functions allowing to manage the reset.

      (+) Call the function HAL_BSEC_GetNumberResets() to get the number
    of hot or warm resets.

@endverbatim
  * @{
  */

/**
  * @brief  Get the number of hot or warm resets.
  *
  * @param  pHbsec        BSEC handle
  * @param  ResetType     Type of the reset, this parameter can be a value of @ref BSEC_Reset_Type
  * @param  pResetNumber  Returned value of number of reset. The returned value is between 0 and 0xFFFFFFFFU
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_BSEC_GetNumberResets(BSEC_HandleTypeDef *const pHbsec, uint32_t ResetType, uint32_t *pResetNumber)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address of returned value and instance */
  if ((pResetNumber == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }

  /* Check the reset type */
  assert_param(IS_BSEC_RESETTYPE(ResetType));

  /* Get the correct register value */
  if (ResetType == HAL_BSEC_HOT_RESET)
  {
    *pResetNumber = pHbsec->Instance->HRCR;
  }
  else
  {
    *pResetNumber = pHbsec->Instance->WRCR;
  }

  return HAL_OK;
}
/**
  * @}
  */
/** @defgroup BSEC_Exported_Functions_Group10 Debug management functions
  *  @brief   Debug management functions
  *
  * */
/**
  * @brief   This function gets debug signals enabled/disabled status by reading BSEC register 'BSEC_DENR'.
  *
  * @param   pHbsec BSEC handle
  * @param   pDebugSignals pointer to get debug signals.
  *
  * @retval  HAL_StatusTypeDef : Returned value is either
  *
  *          HAL_OK if no error was encountered
  *          or HAL_ERROR in case one or several errors were encountered.
  */
HAL_StatusTypeDef HAL_BSEC_GetDebugSignals(BSEC_HandleTypeDef *const pHbsec, uint32_t *pDebugSignals)
{
  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }
  /* Check the address of returned value and instance */
  if ((pDebugSignals == NULL) || (pHbsec->Instance != BSEC))
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }
  /* return only the part lower 16 bits with debug signals */
  *pDebugSignals = (pHbsec->Instance->DENR & BSEC_DENR_MASK);

  return HAL_OK;
}

/**
  * @brief   This function set debug signals in register 'BSEC_DENR'
  *          This is possible if the HAL_BSEC_DENR register is not currently sticky write locked.
  *          It is checked here.
  *
  * @param   pHbsec BSEC handle
  * @param   [in] debugSignals  : debug signals to apply to HAL_BSEC_DENR' (payload part lower 16 bits).
  *
  * @retval  HAL_StatusTypeDef : Returned value is either :
  *          HAL_OK if no error was encountered
  *          or HAL_ERROR in case one or several errors were encountered.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_SetDebugSignals(BSEC_HandleTypeDef *const pHbsec, uint32_t debugSignals)
{
  uint32_t value;

  /* Check the handle pointer */
  if (pHbsec == NULL)
  {
    return HAL_ERROR;
  }
  /* Check the address of returned value and instance */
  if (pHbsec->Instance != BSEC)
  {
    pHbsec->ErrorCode = HAL_BSEC_PARAM_ERROR;
    return HAL_ERROR;
  }
  /* Is DENABLE sticky write locked in 'BSEC_LOCKR.DENLOCK' */
  if ((pHbsec->Instance->LOCKR & BSEC_LOCKR_DENLOCK) == BSEC_LOCKR_DENLOCK)
  {
    pHbsec->ErrorCode = HAL_BSEC_LOCK_ERROR;
    return HAL_ERROR;
  }
  /* Mask signals part : 16 bits lower from input parameter 'dbgSignals' */
  /* then append write protection key on 16 bits upper part              */
  value = (debugSignals & BSEC_DENR_MASK) | BSEC_DENR_WRITE_KEY;

  /* Update the debug value */
  pHbsec->Instance->DENR = (uint32_t)value;

  return HAL_OK;
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
#endif /* defined(BSEC) && defined(HAL_BSEC_MODULE_ENABLED) */

/**
  * @}
  */

