/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_bsec.c
  * @author  MCD Application Team
  * @brief   BSEC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Cyclic Redundancy Check (BSEC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
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
 ===============================================================================
           ##### How to use this driver #####
 ===============================================================================
  [..]
     (+) Enable BSEC AHB clock using __HAL_RCC_BSEC_CLK_ENABLE();
     (+) Initialize BSEC

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal.h"

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @defgroup BSEC BSEC
  * @brief BSEC HAL module driver.
  * @{
  */

#ifdef HAL_BSEC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
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

/** @defgroup BSEC_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief  Initialization and Configuration functions.
  *
@verbatim
 ===============================================================================
      ##### Initialization and de-initialization functions #####
 ===============================================================================
  [..]  This section provides functions allowing to:
    (+) Initialize the BSEC according to the specified parameters
      in the BSEC_InitTypeDef and create the associated handle
    (+) DeInitialize the BSEC peripheral
    (+) Initialize the BSEC MSP (MCU Specific Package)
    (+) DeInitialize the BSEC MSP

@endverbatim
  * @{
  */

/**
  * @}
  */

/** @defgroup BSEC_Exported_Functions_Group2 Peripheral Control functions
  *  @brief  management functions.
  *
@verbatim
 ===============================================================================
            ##### Peripheral Control functions #####
 ===============================================================================
  [..]  This section provides functions allowing to:
    (+) compute the 7, 8, 16 or 32-bit BSEC value of an 8, 16 or 32-bit data buffer
      using combination of the previous BSEC value and the new one.

     [..]  or

    (+) compute the 7, 8, 16 or 32-bit BSEC value of an 8, 16 or 32-bit data buffer
      independently of the previous BSEC value.

@endverbatim
  * @{
  */

/**
  * @}
  */

/** @defgroup BSEC_Exported_Functions_Group3 Peripheral State functions
  *  @brief  Peripheral State functions.
  *
@verbatim
 ===============================================================================
            ##### Peripheral State functions #####
 ===============================================================================
  [..]
  This subsection permits to get in run-time the status of the peripheral.

@endverbatim
  * @}
  */

/**
  * @}
  */

/** @addtogroup BSEC_Private_Functions
  * @{
  */


/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/

/* Static functions -----------------------------------------------*/


/**
  * @brief   This function utility function reads for a  given register type in @ref BSEC_RegTypeTypeDef
  *      bit 'regBit' value of register index 'regIdx' within the same type 'regType'.
  *
  *      Example : read of bit 23 of register type BSEC_OTP_SRLOCK, register index 2
  *      ie : bit 23 of register BSEC_REG_SRLOCK2 reading
  *      is a call to _BSEC_UtilReadRegisterBit(phBsec, BSEC_REG_TYPE_SRLOCK, 2, 23, &bitValue)
  *
  *      Note : This function is a sub utility function that does not check the SAFMEM readiness,
  *      this is the caller function that should take care of that.
  *
  * @param   hBsec [in]   : BSEC handle
  * @param   regType [in] : BSEC register type : should take value from valid range @ref BSEC_RegTypeTypeDef
  * @param   regIdx [in]  : register index of the same type 'regType' concerned by bit read.
  * @param   regBit [in]  : register bit to read
  * @param   pBitValue [in/out] : Pointer to get register bit read value
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
static HAL_StatusTypeDef BSEC_UtilReadRegisterBit(BSEC_HandleTypeDef *hBsec,
                                                  BSEC_RegTypeTypeDef  regType,
                                                  uint32_t       regIdx,
                                                  uint32_t       regBit,
                                                  uint32_t        *pBitValue)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  __IO uint32_t *ptrReg = (uint32_t *)NULL;

  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pBitValue != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* Check validity of input parameters */
  if ((regIdx <= BSEC_REG_INDEX_MAX) && (regBit < 32U))
  {
    switch (regType)
    {
      case BSEC_REG_TYPE_DISTURBED :
        ptrReg = &(hBsec->Instance->BSEC_OTP_DISTURBED0)  + regIdx;
        break;

      case BSEC_REG_TYPE_ERROR :
        ptrReg = &(hBsec->Instance->BSEC_OTP_ERROR0)  + regIdx;
        break;

      case BSEC_REG_TYPE_WRLOCK :
        ptrReg = &(hBsec->Instance->BSEC_OTP_WRLOCK0)  + regIdx;
        break;

      case BSEC_REG_TYPE_SPLOCK :
        ptrReg = &(hBsec->Instance->BSEC_OTP_SPLOCK0)  + regIdx;
        break;

      case BSEC_REG_TYPE_SWLOCK :
        ptrReg = &(hBsec->Instance->BSEC_OTP_SWLOCK0)  + regIdx;
        break;

      case BSEC_REG_TYPE_SRLOCK :
        ptrReg = &(hBsec->Instance->BSEC_OTP_SRLOCK0)  + regIdx;
        break;

      default :
        /* Should normally never occur if advise for function call is followed by user */
        break;

    } /* of switch(regType) */

    *pBitValue = ((*ptrReg & ((uint32_t)1 << regBit)) >> regBit);

    retVal = HAL_OK;
  }
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;

    *pBitValue = 0;
  }

  return (retVal);
}


/* Exported functions -----------------------------------------------*/



/**
  * @brief   This function initialize BSEC driver handle.
  *
  * @param   hBsec [in] : BSEC handle
  * @retval  None.
  ******************************************************************************
  */
void HAL_BSEC_Init(BSEC_HandleTypeDef *hBsec)
{
  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* Set BSEC peripheral block base address */
  hBsec->Instance = (BSEC_TypeDef *)BSEC_BASE;

  /* Set BSEC driver state to Ready */
  hBsec->State = BSEC_STATE_READY;
}

/**
  * @brief   This function De-initialize the BSEC driver by powering down SAFMEM.
  *
  * @param   hBsec [in] : BSEC handle
  * @retval  None.
  ******************************************************************************
  */
void HAL_BSEC_DeInit(BSEC_HandleTypeDef *hBsec)
{
  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* Call the BSEC_SafMemPwrDown() above for the power down phase */
  HAL_BSEC_SafMemPwrDown(hBsec);

  /* Set BSEC driver state to Idle */
  hBsec->State = BSEC_STATE_IDLE;
}

/**
  * @brief   This function powers up SAFMEM and setting correct frequency in
  *      SAFMEM (FRC).
  * @param   hBsec  [in] : BSEC handle
  * @param   safMemClkFreqRange [in/out] : Range of SAFMEM clock (FRC) should take values
  *           of type @ref BSEC_SafMemClkRangeTypeDef.
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_SafMemPwrUp(BSEC_HandleTypeDef      *hBsec,
                                       BSEC_SafMemClkRangeTypeDef   safMemClkFreqRange)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  uint32_t timeoutDetected = 0;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* Is BSEC driver should be at list in state BSEC_STATE_READY */
  if (hBsec->State >= BSEC_STATE_READY)
  {
    /* Update OTP_CONFIG fields BSEC_OTP_CONFIG.PWRUP=1b1' and BSEC_OTP_CONFIG.FRC[1:0] = FRC */
    /* Note : the PWRUP bit allows to power the SAFMEM : this is required only for   */
    /* operations with the SAFMEM that is read from SAFMEM or programming of OTP words */
    hBsec->Instance->BSEC_OTP_CONFIG |= (((uint32_t)BSEC_SAFMEM_ON << (uint32_t)BSEC_OTP_CONFIG_PWRUP_Pos) |
                                         (((uint32_t)safMemClkFreqRange & (uint32_t)BSEC_OTP_CONFIG_FRC) <<
                                          (uint32_t)BSEC_OTP_CONFIG_FRC_Pos));

    /* Get timer current value at start of loop */
    uint32_t timerValInit = HAL_GetTick();

    /* Poll bit 'BSEC_OTP_STATUS.PWRON' until is set with timeout             */
    /* This insure that SAFMEM is powered up and in stable state, ready for OTP Reading */
    /* from SAFMEM or OTP programming to SAFMEM                     */
    while (((hBsec->Instance->BSEC_OTP_STATUS & BSEC_OTP_STATUS_PWRON) == 0U) &&
           (timeoutDetected == 0U))
    {
      /* Sense timeout occurrence */
      if (((uint32_t)HAL_GetTick() - (uint32_t)timerValInit) >= (uint32_t)BSEC_TIMEOUT_SAFMEM_PWRUP_VAL)
      {
        timeoutDetected = 1;
      }

    } /* of while loop */

    if (timeoutDetected == 0U)
    {
      /* Notify in handle state that the SAFMEM is now powered up */
      hBsec->State = BSEC_STATE_SAFMEM_PWRUP;

      retVal = HAL_OK;
    }
    else
    {
      /* Error BSEC driver showed timeout */
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_TIMEOUT;
    }

  } /* of if(hBsec->State >= BSEC_STATE_READY) */
  else
  {
    /* Error BSEC driver is not in ready state */
    /* Update Error description */
    hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
  }

  return (retVal);
}

/**
  * @brief   This function powers down SAFMEM when it was powered up
  *      and change BSEC state to BSEC_STATE_READY.
  *      No action and no error reported when SAFMEM was not powered up yet.
  *
  * @param   hBsec [in] : BSEC handle
  *
  * @retval  None.
  ******************************************************************************
  */
void HAL_BSEC_SafMemPwrDown(BSEC_HandleTypeDef   *hBsec)
{
  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking) */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* Is SAFMEM already powered up ? */
  if (hBsec->State == BSEC_STATE_SAFMEM_PWRUP)
  {
    /* Write bit BSEC_OTP_CONFIG.PWRUP = 1b0' to power down SAFMEM */
    hBsec->Instance->BSEC_OTP_CONFIG &= ~(BSEC_OTP_CONFIG_PWRUP);

    /* Go down one level to BSEC_STATE_READY : that is all BSEC shadows accessible */
    /* bit no more SAFMEM access possible to program OTP or read OTP from SAFMEM   */
    hBsec->State = BSEC_STATE_READY;
  }
}

/**
  * @brief  This function reads for a given register type in @ref BSEC_RegTypeTypeDef
  *      bit 'regBit' value of otp fuse index 'otpWordIdx' within the same type 'regType'.
  *
  * @param   hBsec [in] : BSEC handle
  * @param   regType [in] : BSEC register type : should take value from valid range @ref BSEC_RegTypeTypeDef
  * @param   otpWordIdx [in] : otp fuse index
  * @param   pBitValue [in/out] : Pointer to get register bit read value
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************/

HAL_StatusTypeDef HAL_BSEC_ReadRegisterBit(BSEC_HandleTypeDef *hBsec,
                                           BSEC_RegTypeTypeDef  regType,
                                           uint32_t       otpWordIdx,
                                           uint32_t        *pBitValue)
{
  HAL_StatusTypeDef retVal;
  uint32_t       regIdx;
  uint32_t       regBit;

  HAL_BSEC_Div(otpWordIdx, 32, &regIdx, &regBit);

  retVal = BSEC_UtilReadRegisterBit(hBsec, regType, regIdx, regBit, pBitValue);

  return retVal;
}
/**
  * @brief   This function reads a given OTP word (32 bits) shadow register of index given in first
  *      parameter 'otpWordIdx'.
  *      The read analyze possible error status such as tampering attempt or
  *      sticky/permanent read locking.
  * @param   hBsec [in] : BSEC handle
  * @param   otpWordIdx [in] : OTP word from which we want to read the shadow register.
  * @param   pOtpShadowVal [in/out] : pointer to get the OTP word shadow value.
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_OtpShadowRead(BSEC_HandleTypeDef *hBsec,
                                         uint32_t       otpWordIdx,
                                         uint32_t        *pOtpShadowVal)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  __IO uint32_t *ptrReg;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pOtpShadowVal != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  if (otpWordIdx <= BSEC_OTP_WORD_INDEX_MAX)
  {
    /* Is BSEC driver in ready state */
    if (hBsec->State >= BSEC_STATE_READY)
    {
      ptrReg = &(hBsec->Instance->BSEC_OTP_DATA[0])  + otpWordIdx;
      *pOtpShadowVal = *ptrReg;

      retVal = HAL_OK;
    }
    else
    {
      /* Error BSEC driver and hardware is not in ready state */
      /* Detail error */
      hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
    }
  }
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;
  }

  return (retVal);
}

/**
  * @brief   This function handles a read OTP word (32 bits) operation from SAFMEM.
  *      The value when correctly read, will be returned in second parameter.
  *      If an issue occurs in the read process (SAFMEM upper OTP sticky read lock,
  *      SAFMEM powered down, tampering attempt, error in ECC or redundancy check while reading...),
  *      the corresponding error status is returned and the read value in * pOtpShadowVal should
  *      not be considered as valid.
  *      In any conditions, the corresponding OTP word shadow register will be updated by the read
  *      process (successful or not).
  *      So careful in case of necessity to hide shadow register, cleanup of the OTP shadow register
  *      is required outside of this function.
  *
  *      @note : special note on Sticky Read Lock feature in BSEC :
  *      Shadow OTP register can be individually read locked by sticky bit during BOOT (this
  *      prevent reloading from SAFMEM). When an OTP word is Sticky Read Locked (until next System Reset)
  *      then an OTP Read operation handled will lead to no update of the corresponding BSEC shadow register.
  *      In other words the only way to read the OTP word value (via BSEC shadow) is not available. The OTP word
  *      cannot be read by any mean, despite the OTP Read operation is possible.
  *
  * @param   hBsec [in] : BSEC handle
  *
  * @param   otpWordIdx [in] : OTP word we want to read from SAFMEM
  *                   (and update accordingly the corresponding OTP shadow register).
  *
  * @param   pOtpShadowVal [in/out] : pointer to get the OTP word value.
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_OtpRead(BSEC_HandleTypeDef *hBsec,
                                   uint32_t       otpWordIdx,
                                   uint32_t        *pOtpShadowVal)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint32_t bitValue = 0;
  uint32_t bitValueDisturbed = 0;
  uint32_t bitValueError = 0;
  uint32_t otpShadowVal = 0;
  uint32_t regVal;
  uint32_t timeoutDetected;
  uint32_t exitReq = 0;

  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pOtpShadowVal != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* Check 'otpWordIdx' parameter validity */
  if (otpWordIdx > BSEC_OTP_WORD_INDEX_MAX)
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error |= (uint32_t)BSEC_ERROR_INVALID_PARAMETER;

    return (status); /* Early exit */
  }

  /* Is BSEC driver BSEC_STATE_SAFMEM_PWRUP state : that is SAFMEM is powered up ? */
  if (hBsec->State == BSEC_STATE_SAFMEM_PWRUP)
  {
    /* Polling until all eventual ongoing BSEC previous operations are finished */
    timeoutDetected = HAL_BSEC_WaitBusyClearWithTimeout(hBsec);
    if (timeoutDetected != 0U)
    {
      hBsec->Error |= (uint32_t)BSEC_ERROR_TIMEOUT;

      return (status); /* Early exit */
    }

    /* If we arrive here, there was no timeout detection ... */

    /* Is OTP Word 'otpWordIdx' Sticky Read Locked ? */
    status = HAL_BSEC_ReadRegisterBit(hBsec, BSEC_REG_TYPE_SRLOCK, otpWordIdx, &bitValue);
    if (status != HAL_OK)
    {
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_SOFT_DRIVER;

      return (HAL_ERROR); /* Early exit */
    }

    /* Prepare an OTP Read operation on OTP word index 'otpWordIdx'        */
    regVal = (BSEC_OTP_CONTROL_PROG_READ_VALUE << BSEC_OTP_CONTROL_PROG_Pos) |
             ((otpWordIdx & BSEC_OTP_CONTROL_ADDR) << BSEC_OTP_CONTROL_ADDR_Pos);

    /* Atomic write to register is required for read execution */
    hBsec->Instance->BSEC_OTP_CONTROL = regVal;

    /* Wait until end of BSEC OTP Read operation ... */
    timeoutDetected = HAL_BSEC_WaitBusyClearWithTimeout(hBsec);
    if (timeoutDetected != 0U)
    {
      hBsec->Error |= (uint32_t)BSEC_ERROR_TIMEOUT;

      return (HAL_ERROR); /* Early exit */
    }

    /* If we arrive here No timeout was detected ... */

    /* Check for eventual disturbed state in 'regBit' of 'regIdx' of */
    /* BSEC registers BSEC_OTP_DISTURBEDx and BSEC_OTP_ERRORx    */
    status = HAL_BSEC_ReadRegisterBit(hBsec, BSEC_REG_TYPE_DISTURBED, otpWordIdx, &bitValueDisturbed);
    if (status != HAL_OK)
    {
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_SOFT_DRIVER;

      return (HAL_ERROR); /* Early exit */
    }

    status = HAL_BSEC_ReadRegisterBit(hBsec, BSEC_REG_TYPE_ERROR, otpWordIdx, &bitValueError);
    if (status != HAL_OK)
    {
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_SOFT_DRIVER;

      return (HAL_ERROR); /* Early exit */
    }

    if (bitValueDisturbed == 1U)
    {
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_DISTURBED;

      /* We will need to stop further processing and exit ... */
      exitReq = 1;
    }

    if (bitValueError == 1U)
    {
      /* Add the error with previous one in error mask if any */
      hBsec->Error |= (uint32_t)BSEC_ERROR_ECC_REDUNDANCY;

      /* We will need to stop further processing and exit ... */
      exitReq = 1;
    }

    /* If exit request from one of the two tests above, early exit */
    if (exitReq != 0U)
    {
      return (HAL_ERROR); /* Early exit */
    }

    /* If we arrive here : the OTP read operation was successful            */

    /* there was no Disturbed detected and no Error detected by BSEC          */
    /* AND the OTP word Index is not Sticky Read Locked, so we can read         */
    /* corresponding BSEC shadow registers that have been updated by OTP Read operation */
    status = HAL_BSEC_OtpShadowRead(hBsec, otpWordIdx, &otpShadowVal);
    if (status != HAL_OK)
    {
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_SOFT_DRIVER;

      return (HAL_ERROR); /* Early exit */
    }

    /* If we arrive here BSEC Shadow Read was successful */
    /* Return read value following the read of shadow register */
    *pOtpShadowVal = otpShadowVal;

  } /* of if(hBsec->State == BSEC_STATE_SAFMEM_PWRUP) */

  else
  {
    /* Error BSEC driver and hardware is not in BSEC_STATE_SAFMEM_PWRUP state */
    /* Update Error description */
    hBsec->Error |= (uint32_t)BSEC_ERROR_SAFMEM_PWRDOWN;

    return (HAL_ERROR); /* Early exit */
  }

  return (HAL_OK);
}

/**
  * @brief   This function gets the security status of the SoC sample
  *      as given by OTP_DATA0[5:0], which is readable from BSEC_OTP_STATUS register.
  * @param   hBsec [in] : BSEC handle
  * @param   pSecStatus [in/out] : pointer to get the SoC sample security status
  *      The returned security status can take values from @ref BSEC_ChipSecurityTypeDef.
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_GetSecurityStatus(BSEC_HandleTypeDef *hBsec, BSEC_ChipSecurityTypeDef *pSecStatus)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  __IO uint32_t otpStatus = 0;
  uint32_t securityMask = (BSEC_OTP_STATUS_INVALID |
                           BSEC_OTP_STATUS_FULLDBG |
                           BSEC_OTP_STATUS_SECURE);

  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pSecStatus != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* The BSEC driver should be at least in ready state */
  if (hBsec->State >= BSEC_STATE_READY)
  {
    /* Read only one time register BSEC_OTP_STATUS, keep security bits only */
    otpStatus = ((hBsec->Instance->BSEC_OTP_STATUS) & securityMask);

    /* BE CAREFUL : test order is very important !! DO NOT MODIFY ! */
    if (((otpStatus & BSEC_OTP_STATUS_INVALID) != 0U) || ((otpStatus & BSEC_OTP_STATUS_FULLDBG) != 0U))
    {
      /* OTP_INVALID bit is set : whatever the value of OTP_FULL_DBG and OTP_SECURED bits */
      /* the security state is OTP_INVALID                         */
      *pSecStatus = BSEC_INVALID_STATE;
    }
    else if ((otpStatus & BSEC_OTP_STATUS_CLOSED) != 0U)
    {
      /* FULL_DBG bit not set, this is a correct OTP_SECURED state */
      *pSecStatus = BSEC_SECURED_CLOSE_STATE;
    }
    else
    {
      /* OTP_INVALID, OTP_SECURE and OTP_FULLDBG bits are not set */
      /* This is an OTP_OPEN1 sample                */
      *pSecStatus = BSEC_SECURED_OPEN_STATE;
    }

    retVal = HAL_OK;

  } /* of if(hBsec->State >= BSEC_STATE_READY) */
  else
  {
    /* Error BSEC driver and hardware is not in ready state */
    /* Update Error description */
    hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
  }

  return (retVal);
}

/**
  * @brief   This function writes the OTP word 'otpWordIdx' with value 'otpVal'.
  *      The write affects one of the shadow registers in the range
  *      BSEC_OTP_DATA[0]..BSEC_OTP_DATA95.
  *      Error status such as OTP word shadow sticky locked write is checked.
  * @param   hBsec [in] : BSEC handle
  * @param   otpWordIdx [in] : OTP word shadow index to be written
  * @param   otpVal [in] : Value to be written in OTP Word shadow register.
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_OtpShadowWrite(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx, uint32_t otpVal)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  HAL_StatusTypeDef status;
  uint32_t bitValue = 0;
  __IO uint32_t *ptrReg;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  if (otpWordIdx <= BSEC_OTP_WORD_INDEX_MAX)
  {
    /* The BSEC driver should be at least in ready state */
    if (hBsec->State >= BSEC_STATE_READY)
    {
      status = HAL_BSEC_ReadRegisterBit(hBsec, BSEC_REG_TYPE_SWLOCK, otpWordIdx, &bitValue);
      if (status == HAL_OK)
      {
        if (bitValue == 0U)
        {
          /* No write locking => proceed to write */
          ptrReg = &(hBsec->Instance->BSEC_OTP_DATA[0])  + otpWordIdx;
          *ptrReg = otpVal;

          retVal = HAL_OK;
        }
        else
        {
          /* otpWordIdx is write locked */
          /* Update Error description */
          hBsec->Error |= (uint32_t)BSEC_ERROR_LOCK_WRITE;
        }
      } /* of if(status == BSEC_STATUS_OK) */
      else
      {
        retVal = status;
      }

    } /* of if(hBsec->State >= BSEC_STATE_READY) */
    else
    {
      /* Error BSEC driver and hardware is not in ready state */
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
    }
  }
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;
  }

  return (retVal);
}

/**
  * @brief   This function tries to program a 32 bits value 'otpWordValReq' in
  *      OTP word 'otpWordIdx' in SAFMEM.
  *      The process is the following and can exit at any step before last step :
  *      1a-  Check if OTP word 'otpWordIdx' is not permanently programming locked, if that is the case return error
  *        BSEC_ERROR_PERM_LOCK_PROG.
  *      1b- Check if OTP word is not sticky programming locked,
  *        in that case return an error BSEC_ERROR_STICKY_LOCK_PROG.
  *      2a- The OTP word 'otpWordIdx' is read from SAFMEM before programming.
  *      2b- If OTP word is sticky read lock, an error BSEC_ERROR_LOCK_READ is returned as it
  *        is not possible to analyze if value requested to be programmed in 'otpWordValReq'
  *        is possible to be written in SAFMEM given the technology of SAFMEM.
  *        Remember : a programming changing
  *        one of the bits from the SAFMEM word or several bits from 1 -> 0 is impossible due to SAFMEM technology.
  *      3a- If step 2b exits without error,
  *        check if 'otpWordValReq' is a value possible to write given SAFMEM technology,
  *        given the current value in OTP word. If not possible return error BSEC_ERROR_PROG_VALUE_NOT_POSSIBLE.
  *      3b- If programming is possible, start programming action. Programming can show timeout if too long.
  *        In that case there is an exit with error BSEC_ERROR_TIMEOUT.
  *        If no timeout occurred, check after programming for an eventual ProgFail error.
  *
  * @param   hBsec [in] : BSEC handle
  * @param   otpWordIdx [in] : OTP word to program in SAFMEM.
  * @param   otpWordValReq [in] : 32 bits value requested to be programmed in SAFMEM.
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_OtpProgram(BSEC_HandleTypeDef    *hBsec,
                                      uint32_t         otpWordIdx,
                                      uint32_t         otpWordValReq)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint32_t permProgLockStatus = (uint32_t)BSEC_NOTLOCKED;
  uint32_t stickyLockStatus = (uint32_t)BSEC_NOTLOCKED;
  uint32_t stickyReadLockBitValue = 0;
  uint32_t otpShadowValBeforeProg = 0;
  uint32_t otpShadowValAfterProg = 0;
  __IO uint32_t otpDiffWord = 0;
  __IO uint32_t bit = 0;
  __IO uint32_t impossibleValDetected = 0;
  __IO uint32_t regVal = 0;
  uint32_t timeoutDetected;

  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),
                         BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* Check 'otpWordIdx' parameter validity */
  if (otpWordIdx > BSEC_OTP_WORD_INDEX_MAX)
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error |= (uint32_t)BSEC_ERROR_INVALID_PARAMETER;

    return (status); /* Early exit */
  }

  /* Is BSEC driver in ready state with SAFMEM powered up ? */
  if (hBsec->State == BSEC_STATE_SAFMEM_PWRUP)
  {
    /* Step 1a- Is the 'otpWordIdx' already permanent programming locked ? */
    /* If that is the case, no need to go further : return error BSEC_ERROR_PERM_LOCK_PROG */
    status = HAL_BSEC_GetOtpPermanentProgLockStatus(hBsec, otpWordIdx, &permProgLockStatus);
    if (status != HAL_OK)
    {
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_SOFT_DRIVER;

      return (HAL_ERROR); /* Early exit */
    }

    /* If 'otpWordIdx' is permanently locked in Programming */
    /* no need to go further : detail error and exit    */
    if (permProgLockStatus == (uint32_t)BSEC_LOCKED)
    {
      /* Update Error description : permanent programming lock of that OTP word */
      hBsec->Error |= (uint32_t)BSEC_ERROR_PERM_LOCK_PROG;

      return (HAL_ERROR); /* Early exit */
    }

    /* If we arrive here, the OTP word 'otpWordIdx' is not permanently Programmed Locked */

    /* Step 1b- get sticky lock status for OTP 'otpWordIdx' */
    status = HAL_BSEC_GetOtpStickyLockStatus(hBsec, otpWordIdx, &stickyLockStatus);
    if (status != HAL_OK)
    {
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_SOFT_DRIVER;

      return (HAL_ERROR); /* Early exit */
    }

    if (((uint32_t)stickyLockStatus & (uint32_t)BSEC_OTP_STICKY_LOCK_PROG_FUSE) != 0U)
    {
      /* Update Error description : sticky programming lock of that otp word */
      hBsec->Error |= (uint32_t)BSEC_ERROR_STICKY_LOCK_PROG;

      return (HAL_ERROR); /* Early exit */
    }

    /* If we arrive here : OTP word 'otpWordIdx' is */
    /* Not permanently programming locked NOR sticky programming locked */

    /* From there two possibilities */
    /* 1- If the OTP Word 'otpWordIdx' is NOT Sticky Read Locked and we can verify if the value  */
    /* we aim to program is possible to program, before actually programming it                  */
    /* 2- If the OTP Word 'otpWordIdx' is Sticky Read Locked we cannot verify the value aimed to */
    /* be programmed is possible we will simply attempt the programming of the target value      */

    /* Is OTP Word 'otpWordIdx' Sticky Read Locked ? */
    status = HAL_BSEC_ReadRegisterBit(hBsec, BSEC_REG_TYPE_SRLOCK, otpWordIdx, &stickyReadLockBitValue);
    if (status != HAL_OK)
    {
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_SOFT_DRIVER;

      return (HAL_ERROR); /* Early exit */
    }

    /* if OTP word 'otpWordIdx' is NOT Sticky Read Locked then we can handle the verification of */
    /* possibility to program 'otpWordValReq' in OTP word 'otpWordIdx' ...             */
    if (stickyReadLockBitValue == 0U)
    {
      /* Case 1- OTP Word 'otpWordIdx' is NOT Sticky Read Locked */

      /* Step 2a/2b- Continue by attempting to read OTP word from SAFMEM to */
      /* know if targeted programming value is possible           */
      status = HAL_BSEC_OtpRead(hBsec, otpWordIdx, (uint32_t *)&otpShadowValBeforeProg);
      if (status != HAL_OK)
      {
        /* Update Error description */
        hBsec->Error |= (uint32_t)BSEC_ERROR_SOFT_DRIVER;

        return (HAL_ERROR); /* Early exit */
      }

      /* Step 3a- Value 'otpWordValReq' possible to write in SAFMEM ? */
      /* otpDiffWord = otpShadowValBeforeProg XOR otpWordValReq */
      /* all bits set to 1b1' in 'otpDiffWord' are the bits that are requested to be changed */
      /* check for number of transitions 1->0 : if any, the value 'otpWordValReq' have no chance */
      /* to be programmed in SAFMEM */
      otpDiffWord = (otpShadowValBeforeProg ^ otpWordValReq);

      for (uint32_t var = bit ; (var < 32U) ; var++)
      {
        /* Look for bits different in 'otpShadowValBeforeProg' and 'otpWordValReq' */

        impossibleValDetected = (((otpDiffWord & ((uint32_t)1 << var)) != 0U) &&
                                 ((otpShadowValBeforeProg & ((uint32_t)1 << var)) != 0U) &&
                                 ((otpWordValReq & ((uint32_t)1 << var)) == 0U)) ? 1U : 0U;

        if (impossibleValDetected == 1U)
        {
          break;
        }
        /* This is a 1 -> 0 transition : impossible with SAFMEM technology ! */
        /* of if((otpDiffWord & (1 << bit) != 0)) */
      } /* of for(bit = 0; ((bit < 32) && (impossibleValDetected == 0)); bit++) */

      if (impossibleValDetected == 1U)
      {
        /* Value is not possible to program in SAFMEM : return error */
        /* Update Error description : not possible to write wanted value in SAFMEM */
        hBsec->Error |= (uint32_t)BSEC_ERROR_PROG_VALUE_NOT_POSSIBLE;

        return (HAL_ERROR); /* Early exit */
      }

      /* If we are still here, the value is possible to be programmed */

    } /* of if(stickyReadLockBitValue == 0) */

    /* In Case 2- OTP Word 'otpWordIdx' is Sticky Read Locked        */
    /* we have not handled the step above and will program in "blind mode" */


    /* Step 3b- Proceed with programming of 'otpWordValReq' */

    /* Polling until all previous ongoing BSEC operations are finished */
    timeoutDetected = HAL_BSEC_WaitBusyClearWithTimeout(hBsec);
    if (timeoutDetected != 0U)
    {
      hBsec->Error |= (uint32_t)BSEC_ERROR_TIMEOUT;

      return (HAL_ERROR); /* Early exit */
    }

    if (stickyReadLockBitValue == 0U)
    {
      /* No timeout detected and all bit transitions are then 0->1 in the differing bits between old  */
      /* value and value requested to be programmed                           */
      /* >> CR#108580 - [bootROM / BSEC driver] : implement workaround to save polyfuse transistor life */

      /* Program register BSEC_OTP_WRDATA with value to program 'otpDiffWord'   */
      /* only modified bits representing a transition 0-> are programmed    */
      /* no reprogramming of a transition 1->1 to save polyfuse transistor life */
      hBsec->Instance->BSEC_OTP_WRDATA = otpDiffWord;

      /* CR#108580 - [bootROM / BSEC driver] : implement workaround to save polyfuse transistor life << */

    } /* of if(stickyReadLockBitValue == 0) */
    else
    {
      /* Due to Sticky Read Lock, We are in "blind mode" ... */
      hBsec->Instance->BSEC_OTP_WRDATA = otpWordValReq;
    }

    /* Prepare Program operation with bit lock reset on OTP bit address corresponding to 'otpWordIdx' */
    regVal = (BSEC_OTP_CONTROL_PROG_PROGRAM_VALUE << BSEC_OTP_CONTROL_PROG_Pos)   |
             (BSEC_OTP_CONTROL_LOCK_NOTLOCKED_VALUE << BSEC_OTP_CONTROL_LOCK_Pos) |
             ((otpWordIdx & BSEC_OTP_CONTROL_ADDR) << BSEC_OTP_CONTROL_ADDR_Pos);

    /* Atomic write of OTP_CONTROL is required */
    hBsec->Instance->BSEC_OTP_CONTROL = regVal;

    /* Wait until end of BSEC programming operation */
    timeoutDetected = HAL_BSEC_WaitBusyClearWithTimeout(hBsec);
    if (timeoutDetected != 0U)
    {
      hBsec->Error |= (uint32_t)BSEC_ERROR_TIMEOUT;

      return (HAL_ERROR); /* Early exit */
    }

    /* No timeout detected ... */
    /* Test programming fail indicator post programming operation */
    if ((hBsec->Instance->BSEC_OTP_STATUS & BSEC_OTP_STATUS_PROGFAIL) != 0U)
    {
      /* PROGFAIL indication : programming was not successful */
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_PROG_FAIL;

      return (HAL_ERROR); /* Early exit */
    }

    /* No PROGFAIL indication : programming was successful                    */
    /* Step 4- Reload shadow register : handle it only if the OTP Word is not */
    /* Sticky Lock Read, because otherwise it has no effect at all ...        */
    if (stickyReadLockBitValue == 0U)
    {
      /* Reload newly programmed OTP value in OTP shadow register request */
      status = HAL_BSEC_OtpRead(hBsec, otpWordIdx, (uint32_t *)&otpShadowValAfterProg);

      return (status);

    } /* of if(stickyReadLockBitValue == 0) */

  } /* of if(hBsec->State == BSEC_STATE_SAFMEM_PWRUP) */

  else
  {
    /* Error BSEC driver and hardware is not in ready state */
    /* Update Error description */
    hBsec->Error |= (uint32_t)BSEC_ERROR_SAFMEM_PWRDOWN;

    return (HAL_ERROR); /* Early exit */
  }

  return (HAL_OK);
}


/**
  * @brief   This function reads the BSEC scratch register word (32 bits).
  * @param   hBsec [in] : BSEC handle
  * @param   pScratchReadVal [in/out] : pointer to read the scratch word.
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_ReadScratch(BSEC_HandleTypeDef *hBsec, uint32_t *pScratchReadVal)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pScratchReadVal != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* The BSEC driver should be at least in ready state */
  if (hBsec->State >= BSEC_STATE_READY)
  {
    /* Read BSEC_SCRATCH */
    *pScratchReadVal = hBsec->Instance->BSEC_SCRATCH;

    retVal = HAL_OK;

  } /* if(hBsec->State >= BSEC_STATE_READY) */
  else
  {
    /* Error BSEC driver and hardware is not in ready state */
    /* Update Error description */
    hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
  }

  return (retVal);
}

/**
  * @brief   This function writes the BSEC scratch register with word (32 bits) given in
  *      parameter. Using register BSEC_SCRATCH register, always accessible (always On power domain),
  *      but reset to its reset value (0x0) by a Power Up Reset.
  * @param   hBsec [in] : BSEC handle
  * @param   scratchWriteVal [in] : word value to write in BSEC_SCRATCH register.
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_WriteScratch(BSEC_HandleTypeDef *hBsec, uint32_t scratchWriteVal)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* The BSEC driver should be at least in ready state */
  if (hBsec->State >= BSEC_STATE_READY)
  {
    /* Write BSEC_SCRATCH */
    hBsec->Instance->BSEC_SCRATCH = scratchWriteVal;

    retVal = HAL_OK;

  } /* if(hBsec->State >= BSEC_STATE_READY) */
  else
  {
    /* Error BSEC driver and hardware is not in ready state */
    /* Update Error description */
    hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
  }

  return (retVal);
}

/**
  * @brief   This function reads a CLTAP word (32 bits) written by JTAG/PC or tester side
  *      MPU-AP SoC Receive direction, using BSEC_JTAGIN register.
  * @param   hBsec [in] : BSEC handle
  * @param   pJtagReadVal [in/out] : pointer to half word (16 bits) read from Jtag.
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_JtagInRead(BSEC_HandleTypeDef *hBsec, uint16_t *pJtagReadVal)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pJtagReadVal != (uint16_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* The BSEC driver should be at least in ready state */
  if (hBsec->State >= BSEC_STATE_READY)
  {
    /* Read BSEC_JTAGIN */
    *pJtagReadVal = (uint16_t)(hBsec->Instance->BSEC_JTAGIN & BSEC_JTAGIN_DATA);

    retVal = HAL_OK;

  } /* if(hBsec->State >= BSEC_STATE_READY) */
  else
  {
    /* Error BSEC driver and hardware is not in ready state */
    /* Update Error description */
    hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
  }

  return (retVal);
}

/**
  * @brief   This function writes a JTAG word (32 bits) toward PC/JTAG :
  *      MPU-AP SoC Transmit direction, using BSEC_JTAGOUT register.
  * @param   hBsec [in] : BSEC handle
  * @param   jtagWriteVal [in] : half word value (16 bits) to write to BSEC_JTAGOUT.
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_JtagOutWrite(BSEC_HandleTypeDef *hBsec, uint16_t jtagWriteVal)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* The BSEC driver should be at least in ready state */
  if (hBsec->State >= BSEC_STATE_READY)
  {
    /* write BSEC_JTAGOUT */
    hBsec->Instance->BSEC_JTAGOUT = (jtagWriteVal & BSEC_JTAGOUT_DATA);

    retVal = HAL_OK;

  } /* if(hBsec->State >= BSEC_STATE_READY) */
  else
  {
    /* Error BSEC driver and hardware is not in ready state */
    /* Update Error description */
    hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
  }

  return (retVal);
}

/**
  * @brief   This function sets sticky locks (ie until next Power On Reset) read or write
  *      depending on function and per functions in the following list :
  *      - OTP Upper OTP Read : shadow sticky load read for upper part OTP words : OTP[32..95] : those
  *      containing ST or OEM secrets.
  *      - Debug Enable Write : for debug (CoreSight) access control (global, for non invasive or invasive access in
  *      either non secure or secure privileged modes) : allows to disable or re-enable a debug access.
  *      - ROMLOCK : allows to unmap the upper 8 kBytes of ROM and sticky lock this unmap : this can be done
  *      by Sw only when the sample is SEC_OPEN.
  *      In all others states of the life cycle (OPEN1/OPEN2/SEC_FINAL/OTP_INVALID),
  *      the unmap of upper 8 kBytes of ROM is handled by Hw and cannot be overridden by Sw.
  *      - PROG_GLOBAL_OTP : Sticky lock programming of all OTPs until next system reset
  * @param   hBsec [in] : BSEC handle
  * @param   setFunctionLockMask [in] : Mask set of functions to lock should be a value
  *         created by ORring one or more of values from @ref BSEC_FuncStickyLockTypeDef.
  *         The @ref BSEC_FuncStickyLockTypeDef are directly mapping the Hw register BSEC_OTP_LOCK.
  *         Note : each bit for which the feature should be locked should have value 1b1', values to 1b0'
  *         have no locking effect (and no clearing of a previous lock also !!).
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_FunctionSetLock(BSEC_HandleTypeDef *hBsec, uint32_t setFunctionLockMask)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  uint32_t maxFuncLockFieldVal = (uint32_t)BSEC_FUNC_STICKY_LOCK_PROG_GLOBAL_OTP |
                                 (uint32_t)BSEC_FUNC_STICKY_LOCK_ROMLOCK     |
                                 (uint32_t)BSEC_FUNC_STICKY_LOCK_DENABLE_WRITE   |
                                 (uint32_t)BSEC_FUNC_STICKY_LOCK_OTP_UPPER_READ;
  uint32_t setFunctionMaskEffective;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),
                         BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* The BSEC driver should be at least in ready state */
  if (hBsec->State >= BSEC_STATE_READY)
  {
    setFunctionMaskEffective = (setFunctionLockMask & maxFuncLockFieldVal);

    /* Write the mask in BSEC_OTP_LOCK */
    hBsec->Instance->BSEC_OTP_LOCK |= setFunctionMaskEffective;

    retVal = HAL_OK;

  } /* of if(hBsec->State >= BSEC_STATE_READY) */
  else
  {
    /* Error BSEC driver and hardware is not in ready state */
    /* Update Error description */
    hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
  }

  return (retVal);
}

/**
  * @brief   This function gets the functionality sticky locks status on functions in the following list :
  *      - OTP Upper OTP Read : shadow sticky load read for upper part OTP words : OTP[32..95] : those
  *      containing ST or OEM secrets.
  *      - Debug Enable Write : for debug (CoreSight) access control (global, for non invasive or invasive access in
  *      either non secure or secure privileged modes) : allows to disable or re-enable a debug access.
  *      - ROMLOCK : allows to unmap the upper 8 kBytes of ROM and sticky lock this unmap : this can be done
  *      by Sw only when the sample is SEC_OPEN.
  *      In all others states of the life cycle (OPEN1/OPEN2/SEC_FINAL/OTP_INVALID),
  *      the unmap of upper 8 kBytes of ROM is handled by Hw and cannot be overridden by Sw.
  *      - PROG_GLOBAL_OTP : Sticky lock programming of all OTPs until next system reset
  * @param   hBsec [in] : BSEC handle
  * @param   pFunctionLockMaskRead [in] : Pointer to get the Mask of functions locked
  *         can be compared with values of @ref BSEC_FuncStickyLockTypeDef to know each function that is locked
  *         currently.
  *         Note : each bit for which the feature is currently locked have value 1b1', values to 1b0'
  *         are the functions not locked.
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_FunctionGetLock(BSEC_HandleTypeDef *hBsec, uint32_t *pFunctionLockMaskRead)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  uint32_t maxFuncLockFieldVal = (uint32_t)BSEC_FUNC_STICKY_LOCK_PROG_GLOBAL_OTP |
                                 (uint32_t)BSEC_FUNC_STICKY_LOCK_ROMLOCK     |
                                 (uint32_t)BSEC_FUNC_STICKY_LOCK_DENABLE_WRITE   |
                                 (uint32_t)BSEC_FUNC_STICKY_LOCK_OTP_UPPER_READ;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pFunctionLockMaskRead != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  /* The BSEC driver should be at least in ready state */
  if (hBsec->State >= BSEC_STATE_READY)
  {
    /* Read the mask from BSEC_OTP_LOCK */
    *pFunctionLockMaskRead = (hBsec->Instance->BSEC_OTP_LOCK & maxFuncLockFieldVal);

    retVal = HAL_OK;

  } /* of if(hBsec->State >= BSEC_STATE_READY) */
  else
  {
    /* Error BSEC driver and hardware is not in ready state */
    /* Update Error description */
    hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
  }

  return (retVal);
}

/**
  * @brief   This function locks permanently the programming of OTP word in SAFMEM
  *      for 'otpWordIdx' given in parameter thanks to operation 'LOCK' (write SAFMEM : ie program )
  *      of register BSEC_OTP_CONTROL. This is a per OTP word operation.
  * @param   hBsec [in] : BSEC handle
  * @param   otpWordIdx [in] : OTP word for which we should forbid programming in SAFMEM permanently.
  *      Such an OTP word in SAFMEM will never be allowed to be reprogrammed in the life of the SoC sample.
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_SetOtpPermanentProgLock(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  HAL_StatusTypeDef status;
  uint32_t lockStatus;
  uint32_t divVal = 0;
  uint32_t modVal = 0;
  uint32_t otpAddr;
  uint32_t otpWrData;
  uint32_t regVal;
  uint32_t timeoutDetected;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  if (otpWordIdx <= BSEC_OTP_WORD_INDEX_MAX)
  {
    /* The BSEC driver should be Initialized with SAFMEM powered up */
    if (hBsec->State == BSEC_STATE_SAFMEM_PWRUP)
    {
      /* Is the 'otpWordIdx' already programming locked ? */
      status = HAL_BSEC_GetOtpPermanentProgLockStatus(hBsec, otpWordIdx, &lockStatus);
      if (status == HAL_OK)
      {
        if (lockStatus == (uint32_t)BSEC_NOTLOCKED)
        {
          /* 'otpWordIdx' is not yet programming locked */
          /* Proceed to operation BSEC_OTP_CONTROL.LOCK = 1b1' for the given 'otpWordIdx' */

          if (otpWordIdx < 32U)
          {
            /* OTP Low part otpWordIdx = (0..31) address and WrData scheme : take into account redundancy bits */
            /* Compute  divVal = otpWordIdx div 8 */
            /* and    modVal = otpWordIdx mod 8 */
            HAL_BSEC_Div(otpWordIdx, 8, &divVal, &modVal);
            otpAddr = divVal;
            otpWrData = ((uint32_t)0x3 << (2U * modVal));
          }
          else
          {
            /* OTP High part otpWordIdx = (32..95) : address and WrData scheme : take into account ECC bits*/
            /* Compute  divVal = (otpWordIdx - 32) div 16 */
            /* and    modVal = (otpWordIdx - 32) mod 16 */
            HAL_BSEC_Div((otpWordIdx - 32U), 16, &divVal, &modVal);
            otpAddr = (divVal + 0x04U);
            otpWrData = ((uint32_t)0x1 << modVal);
          }

          /* Polling until all ongoing BSEC operations are finished */
          timeoutDetected = HAL_BSEC_WaitBusyClearWithTimeout(hBsec);
          if (timeoutDetected != 0U)
          {
            hBsec->Error |= (uint32_t)BSEC_ERROR_TIMEOUT;
          }
          else
          {
            /* Program register BSEC_OTP_WRDATA with correct value depending on 'otpWordIdx' to lock */
            /* see Wildcat BSEC IP TRM rev 1.0.1 or higher for Wildcat and table BSEC_WRLOCK_ADDR_full_table.xlsx */
            hBsec->Instance->BSEC_OTP_WRDATA = otpWrData;

            /* Program operation with bit lock set on OTP bit address corresponding to 'otpWordIdx' */
            /* The ADDR field should be set to a value depending on 'otpWordIdx'          */
            /* see Wildcat BSEC IP TRM rev 1.0.1 or higher for Wildcat and table BSEC_WRLOCK_ADDR_full_table.xlsx */

            regVal = (BSEC_OTP_CONTROL_PROG_PROGRAM_VALUE << BSEC_OTP_CONTROL_PROG_Pos) |
                     BSEC_OTP_CONTROL_LOCK                         |
                     ((otpAddr & BSEC_OTP_CONTROL_ADDR) << BSEC_OTP_CONTROL_ADDR_Pos);

            /* atomic write */
            hBsec->Instance->BSEC_OTP_CONTROL = regVal;

            /* Wait until end of BSEC programming operation */
            timeoutDetected = HAL_BSEC_WaitBusyClearWithTimeout(hBsec);
            if (timeoutDetected != 0U)
            {
              hBsec->Error |= (uint32_t)BSEC_ERROR_TIMEOUT;
            }
            else
            {
              /* no timeout detected */
              /* Test programming fail indicator post programming operation */
              if ((hBsec->Instance->BSEC_OTP_STATUS & BSEC_OTP_STATUS_PROGFAIL) != 0U)
              {
                /* PROGFAIL indication : lock was not successful */
                /* Update Error description */
                hBsec->Error |= (uint32_t)BSEC_ERROR_PROG_FAIL;
              }
              else
              {
                /* No PROGFAIL indication : lock was successful */
                /* Update Error description to no error */
                retVal = HAL_OK;
              }

            } /* of else timeoutDetected */

          } /* of else timeoutDetected */

        } /* of if(lockStatus == BSEC_NOTLOCKED) */
        else
        {
          /* Update Error description */
          hBsec->Error |= (uint32_t)BSEC_ERROR_ALREADY_LOCKED;
        }

      } /* of if(status == HAL_OK) */

    } /* of if(hBsec->State == BSEC_STATE_SAFMEM_PWRUP) */
    else
    {
      /* Error BSEC driver and hardware is not in ready state */
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_SAFMEM_PWRDOWN;
    }
  }
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;
  }

  return (retVal);
}

/**
  * @brief   This function returns in second parameter 'pLockStatus', the information
  *      for a given OTP word index given in first parameter 'otpWordIdx',
  *      whether or not this OTP word is permanently programming locked.
  * @param   hBsec [in] : BSEC handle
  * @param   otpWordIdx [in] : OTP word for which information on permanent programming lock is requested
  * @param   pLockStatus [in/out] : pointer to get permanent programming lock status : value of type
  *                                 @ref BSEC_LockTypeDef
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_GetOtpPermanentProgLockStatus(BSEC_HandleTypeDef *hBsec,
                                                         uint32_t       otpWordIdx,
                                                         uint32_t        *pLockStatus)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  HAL_StatusTypeDef status;
  uint32_t bitValue = 0;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pLockStatus != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  if (otpWordIdx <= BSEC_OTP_WORD_INDEX_MAX)
  {
    /* The BSEC driver should be at least in ready state */
    if (hBsec->State >= BSEC_STATE_READY)
    {
      status = HAL_BSEC_ReadRegisterBit(hBsec, BSEC_REG_TYPE_WRLOCK, otpWordIdx, &bitValue);
      if (status == HAL_OK)
      {
        if (bitValue == 0U)
        {
          /* OTP word 'otpWordIdx' is not permanently write locked */
          *pLockStatus = (uint32_t)BSEC_NOTLOCKED;
        }
        else
        {
          /* OTP word 'otpWordIdx' is permanently write locked */
          *pLockStatus = (uint32_t)BSEC_LOCKED;
        }

        retVal = HAL_OK;
      }
      else
      {
        /* Update Error description */
        hBsec->Error |= (uint32_t)BSEC_ERROR_SOFT_DRIVER;
      }

    } /* of if(hBsec->State >= BSEC_STATE_READY) */
    else
    {
      /* Error BSEC driver and hardware is not in ready state */
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
    }
  }
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;
  }

  return (retVal);
}

/**
  * @brief   This function sticky locks (ie until next system Reset) the OTP word of index
  *      'otpWordIdx' with a lock depending on sticky lock command parameter ('stickyLockCmd')
  *      which can take values in the list (Note : combination of several commands is possible) :
  *      - OTP programming lock command
  *      - OTP shadow register write lock command
  *      - OTP shadow register read lock command
  *      Note1 : this parameter should take values or combination (ORred) of values from @ref BSEC_OtpStickyLockTypeDef.
  *      Note2 : Sticky locking is applied even if already sticky locked for the same function and same bit
  *          No error is returned in that case and sticky lock is re-applied.
  * @param   hBsec [in] : BSEC handle
  * @param   otpWordIdx [in] : OTP word index for which the sticky lock command is processed.
  * @param   stickyLockCmd [in] : Sticky lock command to apply : value of type @ref BSEC_OtpStickyLockTypeDef
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_SetOtpStickyLock(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx, uint32_t stickyLockCmd)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  uint32_t regIdx = 0;
  uint32_t regBit = 0;
  __IO uint32_t *ptrReg;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  if ((otpWordIdx <= BSEC_OTP_WORD_INDEX_MAX) &&
      (stickyLockCmd <= ((uint32_t)BSEC_OTP_STICKY_LOCK_PROG_FUSE |
                         (uint32_t)BSEC_OTP_STICKY_LOCK_WRITE_SHADOW  |
                         (uint32_t)BSEC_OTP_STICKY_LOCK_UPDATE_SHADOW)))
  {
    /* The BSEC driver should be at least in ready state */
    if (hBsec->State >= BSEC_STATE_READY)
    {
      /* Find which register index and which bit position is */
      /* corresponding to 'otpWordIdx'             */
      HAL_BSEC_Div(otpWordIdx, 32, &regIdx, &regBit);

      /* Handle one or several sticky lockings at the same time depending on 'stickyLockCmd' value */
      if ((stickyLockCmd & (uint32_t)BSEC_OTP_STICKY_LOCK_PROG_FUSE) != 0U)
      {
        /* Program to 1b1' bit 'regBit' of register BSEC_OTP_SPLOCK<regIdx> to sticky lock programming */
        /* otpWordIdx word */
        ptrReg = &(hBsec->Instance->BSEC_OTP_SPLOCK0)  + regIdx;
        *ptrReg |= ((uint32_t)1 << regBit);
      }

      if ((stickyLockCmd & (uint32_t)BSEC_OTP_STICKY_LOCK_WRITE_SHADOW) != 0U)
      {
        /* Program to 1b1' bit 'regBit' of register BSEC_OTP_SWLOCK<regIdx> to sticky lock write */
        /* otpWordIdx word shadow register */
        ptrReg = &(hBsec->Instance->BSEC_OTP_SWLOCK0)  + regIdx;
        *ptrReg |= ((uint32_t)1 << regBit);
      }

      if ((stickyLockCmd & (uint32_t)BSEC_OTP_STICKY_LOCK_UPDATE_SHADOW) != 0U)
      {
        /* Program to 1b1' bit 'regBit' of register BSEC_OTP_SRLOCK<regIdx> to sticky lock read */
        /* otpWordIdx word shadow register */
        ptrReg = &(hBsec->Instance->BSEC_OTP_SRLOCK0)  + regIdx;
        *ptrReg |= ((uint32_t)1 << regBit);
      }

      retVal = HAL_OK;

    } /* of if(hBsec->State >= BSEC_STATE_READY) */
    else
    {
      /* Error BSEC driver and hardware is not in ready state */
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
    }
  }
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;
  }

  return (retVal);
}

/**
  * @brief   This function gets OTP sticky lock status for the OTP word of index
  *      'otpWordIdx'.
  *      Each kind of sticky locking is checked for 'otpWordIdx' it can be a combination of items in the list :
  *      - OTP programming lock command
  *      - OTP shadow register write lock command
  *      - OTP shadow register read lock command
  *      Note : this parameter should take values from @ref BSEC_OtpStickyLockTypeDef.
  * @param   hBsec [in] : BSEC handle
  * @param   otpWordIdx [in] : OTP word index for which the sticky lock command is processed.
  * @param   pStickyLockStatus [in] : Composite Sticky lock status : a combination of values from
  *         type @ref BSEC_OtpStickyLockTypeDef
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_GetOtpStickyLockStatus(BSEC_HandleTypeDef *hBsec,
                                                  uint32_t       otpWordIdx,
                                                  uint32_t        *pStickyLockStatus)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  uint32_t regIdx = 0;
  uint32_t regBit = 0;
  __IO uint32_t stickyLockStatus = 0;
  __IO uint32_t splock_flag = 0;
  __IO uint32_t swlock_flag = 0;
  __IO uint32_t srlock_flag = 0;
  __I uint32_t *ptrReg1;
  __I uint32_t *ptrReg2;
  __I uint32_t *ptrReg3;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pStickyLockStatus != (uint32_t*)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  if (otpWordIdx <= BSEC_OTP_WORD_INDEX_MAX)
  {
    /* The BSEC driver should be at least in ready state */
    if (hBsec->State >= BSEC_STATE_READY)
    {
      /* Find which register index and which bit position is */
      /* corresponding to 'otpWordIdx'             */
      HAL_BSEC_Div(otpWordIdx, 32, &regIdx, &regBit);

      /* Be careful : the lines below works because we add pointers uint32_t*    */
      /* So base address of the lock register (P,W,R) is incremented by (regIdx * 4) */
      ptrReg1 = &(hBsec->Instance->BSEC_OTP_SPLOCK0)  + regIdx;
      ptrReg2 = &(hBsec->Instance->BSEC_OTP_SWLOCK0)  + regIdx;
      ptrReg3 = &(hBsec->Instance->BSEC_OTP_SRLOCK0)  + regIdx;

      splock_flag = (* ptrReg1 & ((uint32_t)1 << regBit));
      swlock_flag = (* ptrReg2 & ((uint32_t)1 << regBit));
      srlock_flag = (* ptrReg3 & ((uint32_t)1 << regBit));

      /* Check sticky lock programming status */
      if (splock_flag != 0U)
      {
        stickyLockStatus |= (uint32_t)BSEC_OTP_STICKY_LOCK_PROG_FUSE;
      }

      /* Check sticky lock write shadow status */
      if (swlock_flag != 0U)
      {
        stickyLockStatus |= (uint32_t)BSEC_OTP_STICKY_LOCK_WRITE_SHADOW;
      }

      /* Check sticky lock read shadow status */
      if (srlock_flag != 0U)
      {
        stickyLockStatus |= (uint32_t)BSEC_OTP_STICKY_LOCK_UPDATE_SHADOW;
      }

      *pStickyLockStatus = (uint32_t)stickyLockStatus;

      retVal = HAL_OK;

    } /* of if(hBsec->State >= BSEC_STATE_READY) */
    else
    {
      /* Error BSEC driver and hardware is not in ready state */
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
    }
  }
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;
  }

  return (retVal);
}


/**
  * @brief   This function gets OTP error status for the OTP word of index 'otpWordIdx'.
  * @param   hBsec [in] : BSEC handle
  * @param   otpWordIdx [in] : OTP word index
  * @param   pErrorStatus [in] : error status. 0 means no error, 1 means error
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_GetOtpErrorStatus(BSEC_HandleTypeDef *hBsec,
                                             uint32_t       otpWordIdx,
                                             uint32_t        *pErrorStatus)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pStickyLockStatus != (uint32_t*)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  if (otpWordIdx <= BSEC_OTP_WORD_INDEX_MAX)
  {
    /* The BSEC driver should be at least in ready state */
    if (hBsec->State >= BSEC_STATE_READY)
    {
      /* Find which register index and which bit position is */
      /* corresponding to 'otpWordIdx'             */
      retVal = HAL_BSEC_ReadRegisterBit(hBsec, BSEC_REG_TYPE_ERROR, otpWordIdx, pErrorStatus);
    } /* of if(hBsec->State >= BSEC_STATE_READY) */
    else
    {
      /* Error BSEC driver and hardware is not in ready state */
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
    }
  }
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;
  }

  return (retVal);
}


/**
  * @brief   This function gets OTP disturb status for the OTP word of index 'otpWordIdx'.
  * @param   hBsec [in] : BSEC handle
  * @param   otpWordIdx [in] : OTP word index
  * @param   pDisturbStatus [in] : disturb status
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_GetOtpDisturbStatus(BSEC_HandleTypeDef *hBsec,
                                               uint32_t       otpWordIdx,
                                               uint32_t        *pDisturbStatus)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pStickyLockStatus != (uint32_t*)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  if (otpWordIdx <= BSEC_OTP_WORD_INDEX_MAX)
  {
    /* The BSEC driver should be at least in ready state */
    if (hBsec->State >= BSEC_STATE_READY)
    {
      /* Find which register index and which bit position is */
      /* corresponding to 'otpWordIdx'             */
      retVal = HAL_BSEC_ReadRegisterBit(hBsec, BSEC_REG_TYPE_DISTURBED, otpWordIdx, pDisturbStatus);
    } /* of if(hBsec->State >= BSEC_STATE_READY) */
    else
    {
      /* Error BSEC driver and hardware is not in ready state */
      /* Update Error description */
      hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
    }
  }
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;
  }

  return (retVal);
}


/**
  * @brief   This function returns a mask of feature currently disabled in
  *           EWS stage by SAFMEM OTP_DATA1 word programming.
  * @param   hBsec [in] : BSEC handle
  * @param   pMaskFeatDisabled [in/out] : pointer to get the mask of feature currently disabled by OTP_DATA1.
  *
  *      Careful here a value 1b1' in the bitmask[i] means that the corresponding feature :
  *      (1 << BSEC_OtpFeatureStickyLockTypeDef[i]) is disabled by OTP programming and not accessible to hardware.
  *      But can be potentially re-enabled by programming BSEC_FENABLE[i] = 1b1' on a secure sample
  *      (ie BSEC_OTP_STATUS.OTP_SECURED=1b1').
  *      bitmask[i] = 1b0' means that the feature is not disabled by OTP, hence Hw accessible.
  *
  *      Note : The check of SAFMEM readiness is done by second level function.
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_GetFeatureDisabled(BSEC_HandleTypeDef *hBsec, uint32_t *pMaskFeatDisabled)
{
  HAL_StatusTypeDef status;
  uint32_t featureDisabledValidMask = ((1U << ((uint32_t)BSEC_FEAT_MAX + 1U)) - 1U);
  uint32_t otpShadowReadVal = 0;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pMaskFeatDisabled != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Read feature disabled from BSEC_OTP_DATA1 as always copied from SAFMEM for that word */
  /* BSEC Ready state is checked by second level function BSEC_OtpShadowRead() here     */
  status = HAL_BSEC_OtpShadowRead(hBsec, 1, (uint32_t *)&otpShadowReadVal);
  if (status == HAL_OK)
  {
    /* Mask OTP word read value with only feature disabled mask */
    otpShadowReadVal = (otpShadowReadVal & featureDisabledValidMask);

    *pMaskFeatDisabled = otpShadowReadVal;
  }

  return (status);
}

/**
  * @brief   This function returns the value of bit OTP_DATA1.fdis_tk that gives information of ST Key Provisioning
  *      have already been handled (when value 1b1') or not yet handled (when value is 1b0').
  * @param   hBsec [in] : BSEC handle
  * @param   pFdisTkValue [in/out] : pointer to get value of bit OTP_DATA1.fdis_tk
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_GetFdisTkValue(BSEC_HandleTypeDef *hBsec, uint32_t *pFdisTkValue)
{
  HAL_StatusTypeDef status;
  uint32_t otpShadowReadVal = 0;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pFdisTkValue != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Read feature disabled from BSEC_OTP_DATA1 as always copied from SAFMEM for that word */
  /* BSEC Ready state is checked by second level function BSEC_OtpShadowRead() here     */
  status = HAL_BSEC_OtpShadowRead(hBsec, 1, (uint32_t *)&otpShadowReadVal);
  if (status == HAL_OK)
  {
    *pFdisTkValue = ((otpShadowReadVal & (1U << BSEC_OTP_CFG1_FDIS_TK_BIT_POS)) >> BSEC_OTP_CFG1_FDIS_TK_BIT_POS);
  }

  return (status);
}

/**
  * @brief   This function is used during ST Key Provisioning to read TK from 4 read
  *      in BSEC_SCRATCH register. This is only possible if OTP Mode = OTP_SECURE and
  *      fdis_tk = 0.
  *      The table to get the TK should be allocated externally to a size of 4 uint32_t
  * @param   hBsec [in] : BSEC handle
  * @param   tkValue [in/out] : pointer to get value TK
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_GetTk(BSEC_HandleTypeDef *hBsec, uint32_t *tkValue)
{
  uint32_t idx;
  HAL_StatusTypeDef status = HAL_TIMEOUT ;
  uint32_t *pReadPointer = &(tkValue[3]);  /* Initialize read pointer to
                                              key LSWord start position for the key retrieve */

  /*
   * Important Note :
   * If TK = AES 128 Key is 0x00112233445566778899AABBCCDDEEFF => will be used externally as uint8_t aes_key[16]
   * and called as BSEC_GetTk(hBsec, (uint32_t *) aes_key) : we expect to read :
   * aes_key[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF }
   * First read BSEC_SCRATCH will retrieve LSWord of Key -> 0xCCDDEEFF
   * Second read BSEC_SCRATCH will retrieve        -> 0x8899AABB
   * Third  read BSEC_SCRATCH will retrieve        -> 0x44556677
   * Fourth read BSEC_SCRATCH will retrieve        -> 0x00112233
   * Hence the implementation below :
   */

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (tkValue != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  for (idx = 0; idx < 4U; idx++)
  {
    /* Read BSEC_SCRATCH but do not care about eventual errors */
    status = HAL_BSEC_ReadScratch(hBsec, pReadPointer);

    pReadPointer--; /* decrement pReadPointer */
  }

  return (status);
}

/**
  * @brief   This function gets debug signals enabled/disabled status by reading BSEC register 'BSEC_DENABLE'.
  * @param   hBsec [in] : BSEC handle
  * @param   pDebugMaskEnabled [in/out] : pointer to get the mask of debug signals enabled/disabled.
  *                    Any bit value in mask set to 1b1' means a debug signal that is enabled,
  *                    while 1b0' bit in mask means a debug signal disabled
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_GetDebugEnabled(BSEC_HandleTypeDef *hBsec, uint32_t *pDebugMaskEnabled)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  uint32_t validMask = ((1U << ((uint32_t)BSEC_DEBUG_ENABLE_MAX + 1U)) - 1U);

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pDebugMaskEnabled != (uint32_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* The BSEC driver should be at least in ready state */
  if (hBsec->State >= BSEC_STATE_READY)
  {
    *pDebugMaskEnabled = ((hBsec->Instance->BSEC_DENABLE) & validMask);

    retVal = HAL_OK;
  }
  else
  {
    /* Error BSEC driver and hardware is not in ready state */
    /* Detail error */
    hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
  }

  return (retVal);
}

/**
  * @brief   This function set debug signals enabled/disabled mask by writing to write register 'BSEC_DENABLE'
  *      to an enable/disable mask value in second parameter.
  *      This is possible if the BSEC_DENABLE register is not currently sticky write locked.
  * @param   hBsec [in] : BSEC handle
  * @param   debugMaskEnabled [in/out] : Mask of disable/enable of debug signals.
  *                     Any value set to 1b1' means debug signal is enabled,
  *                     1b0' is a debug signal disabled
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_SetDebugEnabled(BSEC_HandleTypeDef *hBsec, uint32_t debugMaskEnabled)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  uint32_t validMask = ((1U << ((uint32_t)BSEC_DEBUG_ENABLE_MAX + 1U)) - 1U);

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking); */

  if (debugMaskEnabled <= validMask)
  {
    /* The BSEC driver should be at least in ready state */
    if (hBsec->State >= BSEC_STATE_READY)
    {
      /* Is debug enable function locked sticky ?               */
      /* Decision here to use direct register access instead of function call */
      /* BSEC_FunctionGetLock() which would take longer processing time     */
      if ((hBsec->Instance->BSEC_OTP_LOCK & BSEC_OTP_LOCK_DENREG) != 0U)
      {
        /* Yes the debug enable is sticky locked (write)       */
        /* Not possible to write currently the register BSEC_DENABLE */
        /* Update Error description */
        hBsec->Error |= (uint32_t)BSEC_ERROR_LOCK_WRITE;
      }
      else
      {
        /* BSEC_DENABLE is not sticky write locked : proceed to write BSEC_DENABLE */
        hBsec->Instance->BSEC_DENABLE = (debugMaskEnabled & validMask);
        retVal = HAL_OK;
      }
    }
    else
    {
      /* Error BSEC driver and hardware is not in ready state */
      /* Detail error */
      hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
    }
  }
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;
  }

  return (retVal);
}

/**
  * @brief   This function reads in *pPKH the public key HASH (SHA-256) from OTP_DATA[31:24]
  *      This is the hash by SHA-256 of the public key used for authentication of the First Stage Boot Loader (FSBL).
  * @param   hBsec [in] : BSEC handle
  * @param   readMode [in] : read mode should take value from @ref BSEC_ReadModeTypeDef.
  * @param   pkhOtpFirstWordIdx [in] : first OTP word index of PKH
  * @param   pPKH [in/out] : Pointer to read the public key (the memory should have been allocated externally).
  *
  * Note : prior the get an array of 32 bytes should have been allocated externally from this BSEC function, there
  *    is no static or dynamic memory allocation in the current function.
  *
  * @retval  HAL_StatusTypeDef : Returned value.
  ******************************************************************************
  */
HAL_StatusTypeDef HAL_BSEC_GetPKH(BSEC_HandleTypeDef *hBsec,
                                  BSEC_ReadModeTypeDef readMode,
                                  uint32_t       pkhOtpFirstWordIdx,
                                  uint8_t     *pPKH)
{
  HAL_StatusTypeDef retVal = HAL_ERROR;
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t *pPubKeyHashWord;
  uint32_t otpWordIdx;

  /* Verify input parameters validity */
  /* INFASSERTS_REQUIRE(((hBsec != (BSEC_HandleTypeDef *)NULL) && (pPKH != (uint8_t *)NULL)),
                          BSECDRV,AssertBlocking); */

  /* Clean up first Error field in handle (used by previous calls to BSEC driver) */
  hBsec->Error = (uint32_t)BSEC_ERROR_NONE;

  if (pkhOtpFirstWordIdx <= BSEC_OTP_WORD_INDEX_MAX)
  {
    /* Initialize 'pPubKeyHashWord' */
    pPubKeyHashWord = (uint32_t *)pPKH;

    if (readMode == BSEC_READ_FROM_SHADOW)
    {
      /* The BSEC driver should be at least in ready state */
      if (hBsec->State >= BSEC_STATE_READY)
      {
        uint32_t temp = pkhOtpFirstWordIdx + 8U;
        for (otpWordIdx = pkhOtpFirstWordIdx; ((otpWordIdx < (temp)) && (status == HAL_OK)); otpWordIdx++)
        {
          status = HAL_BSEC_OtpShadowRead(hBsec, otpWordIdx, (uint32_t *)pPubKeyHashWord);
          pPubKeyHashWord++;
        }

        /* Return the status : which can be early exit case if issue occurred, in that case the contents */
        /* of *pPKH should not be trusted and used : hBsec->Error will have been updated by HAL_BSEC_OtpRead() or */
        /* BSEC_OtpShadowRead() function */
        retVal = status;
      }
      else
      {
        /* Error BSEC driver and hardware is not in ready state */
        /* Update Error description */
        hBsec->Error |= (uint32_t)BSEC_ERROR_DRIVER_NOT_READY;
      }

    } /* of if(readMode == BSEC_READ_FROM_SHADOW) */
    else
    {
      /* Read from SAFMEM ... */
      /* The BSEC driver should be at least in state SAFMEM Pwr Up */
      if (hBsec->State == BSEC_STATE_SAFMEM_PWRUP)
      {
        /* Force update of shadows from SAFMEM before reading from shadows                    */
        /* This takes longer time and assumes we do not trust at the point we read the OTP shadow registers values */
        uint32_t temp = pkhOtpFirstWordIdx + 8U;
        for (otpWordIdx = pkhOtpFirstWordIdx; ((otpWordIdx < (temp)) && (status == HAL_OK)); otpWordIdx++)
        {
          status = HAL_BSEC_OtpRead(hBsec, otpWordIdx, (uint32_t *)pPubKeyHashWord);
          pPubKeyHashWord++;
        }

        /* Return the status : which can be early exit case if issue occurred, in that case the contents */
        /* of *pPKH should not be trusted and used : hBsec->Error will have been updated by HAL_BSEC_OtpRead() or */
        /* BSEC_OtpShadowRead() function */
        retVal = status;
      }
      else
      {
        /* Error BSEC driver and hardware is not in SAFMEM Pwr Up */
        /* Update Error description */
        hBsec->Error |= (uint32_t)BSEC_ERROR_SAFMEM_PWRDOWN;
      }

    } /* of else Read from SAFMEM */

  } /* of if(pkhOtpFirstWordIdx <= BSEC_OTP_WORD_INDEX_MAX) */
  else
  {
    /* Update Error description to Invalid parameter */
    hBsec->Error = (uint32_t)BSEC_ERROR_INVALID_PARAMETER;
  }

  return (retVal);
}

/**
  * @brief   This static function implements simple integer division
  *      (A div B) and (A mod B) to obtain quotient in *pQ and remainder (modulo) in *pR.
  *
  * @param   A [in] : dividend
  * @param   B [in] : divider
  * @param   pQ [in/out] : integer quotient
  * @param   pR [in/out] : modulo
  * @retval  Void.
  ******************************************************************************
  */
void HAL_BSEC_Div(uint32_t A, uint32_t B, uint32_t *pQ, uint32_t *pR)
{
  uint32_t var1 = A;
  uint32_t var2 = 0;

  /* INFASSERTS_REQUIRE(((pQ != (uint32_t *)NULL) && (pR != (uint32_t *)NULL)),BSECDRV,AssertBlocking); */

  while (var1 >= B)
  {
    var1 = (var1 - B);
    var2++;
  }

  *pR = var1;
  *pQ = var2;
}

/**
  * @brief   This function wait until bit BSEC_OTP_CONTROL.BUSY is 1b0'
  *      before a timeout.
  * @param   hBsec [in] : BSEC handle
  *
  * @retval  timeoutDetected : value 0x1 if timeout was detected while
  *      waiting for bit BUSY to be cleared.
  ******************************************************************************
  */
uint32_t HAL_BSEC_WaitBusyClearWithTimeout(const BSEC_HandleTypeDef *hBsec)
{
  uint32_t timerValInit = HAL_GetTick();
  uint32_t timeoutDetected = 0;

  /* INFASSERTS_REQUIRE((hBsec != (BSEC_HandleTypeDef *)NULL),BSECDRV,AssertBlocking); */

  while (((hBsec->Instance->BSEC_OTP_STATUS & BSEC_OTP_STATUS_BUSY) != 0U) &&
         (timeoutDetected == 0U))
  {
    /* Sense timeout occurrence */
    if (((int32_t)HAL_GetTick() - (int32_t)timerValInit) >= BSEC_TIMEOUT_VAL)
    {
      timeoutDetected = 1;
    }

  } /* of while loop */

  return (timeoutDetected);
}

#endif /* HAL_BSEC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

