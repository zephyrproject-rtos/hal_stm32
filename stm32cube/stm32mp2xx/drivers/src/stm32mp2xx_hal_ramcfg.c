/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_ramcfg.c
  * @author  MCD Application Team
  * @brief   RAMCFG HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the RAMs configuration controller peripheral:
  *           + RAMCFG Initialization and De-initialization Functions.
  *           + RAMCFG ECC Operation Functions.
  *           + RAMCFG CRC Operation Functions.
  *           + RAMCFG Configure Wait State Functions.
  *           + RAMCFG Write Protection Functions.
  *           + RAMCFG Erase Operation Functions.
  *           + RAMCFG Handle Interrupt and Callbacks Functions.
  *           + RAMCFG State and Error Functions.
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
                    ##### RAMCFG Peripheral features #####
  ==============================================================================
  [..]
    (+) Each SRAM is managed by a RAMCFG instance.
        (++) SYSRAM placed in D2 Domain.
             (+++) Size         = 256 kB.
             (+++) Base Address = 0x20000000.

        (++) SRAM1 placed in D2 Domain.
             (+++) Size         = 128 kB.
             (+++) Base Address = 0x20040000.

        (++) SRAM2 placed in D2 Domain.
             (+++) Size         = 128 kB.
             (+++) Base Address = 0x20060000.

        (++) RETRAM placed in Backup Domain.
             (+++) Size         = 128 kB.
             (+++) Base Address = 0x20080000.

        (++) LPSRAM1 placed in Backup Domain.
             (+++) Size         = 8 kB.
             (+++) Base Address = 0x200C0000.

        (++) LPSRAM2 placed in D3 Domain.
             (+++) Size         = 8 kB.
             (+++) Base Address = 0x200C2000.

        (++) LPSRAM3 placed in D3 Domain.
             (+++) Size         = 16 kB.
             (+++) Base Address = 0x200C4000.

        (++) BKPSRAM placed in Backup Domain.
             (+++) Size         = 8 kB.
             (+++) Base Address = 0x42000000.

        (++) VDERAM placed in Video Domain.
             (+++) Size         = 128 kB.
             (+++) Base Address = 0x200A0000.

    (+) Each SRAM could be erased independently through its RAMCFG instance.

    (+) RETRAM and BKPRAM support ECC correction feature. This mechanism
        adopts the Single Error Correction Double Error Detection (SECDED)
        algorithm. This feature provides the following information:
             (++) Single error address.
             (++) Double error address.

    (+) RETRAM and LPSRAM1 support CRC (Cyclic Redundancy Check) feature.
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) Call HAL_RAMCFG_Init() to initialize the RAMCFG peripheral before using
       any feature. Call HAL_RAMCFG_DeInit() to de-initialize the RAMCFG when
       using this peripheral is no more needed or a hardware issue is occurred.

     *** ECC feature ***
     ===================
    [..]
          (+) Call HAL_RAMCFG_StartECC() and HAL_RAMCFG_StopECC() to enable and
              disable ECC hardware process.

          (+) Call HAL_RAMCFG_EnableNotification() and HAL_RAMCFG_DisableNotification()
              to enable and disable ECC interrupts. Interrupts could be :
                    (++) Single error interrupt.
                    (++) Double error interrupt.
                    (++) Double error interrupt redirected to Non masKable
                          interrupt (NMI).

          (+) Call HAL_RAMCFG_GetSingleErrorAddress() to get the address of the
              last fail RAM word detected (only for single error)  and
              Call HAL_RAMCFG_GetDoubleErrorAddress() to get the address of the
              last fail RAM word detected (only for double error).

          (+) Call HAL_RAMCFG_IsECCErrorDetected() to check if an ECC single/double
              error was detected. This API is used in silent mode (No ECC interrupt
              is enabled).

     *** HW erase feature ***
     ==========================
    [..]
          (+) Call HAL_RAMCFG_HWEraseEnable() to Enable erase operation done after
              a system reset.

          (+) Call HAL_RAMCFG_HWEraseDisable() to Disable erase operation done after
              a system reset.

     *** CRC feature ***
     ================================
    [..]
          (+) Call HAL_RAMCFG_ConfigCRC() to Configure CRC mode and CRC Buffer Size.

          (+) Call HAL_RAMCFG_ComputeCRC() to compute reference CRC or compute and
              check CRC.

     *** Erase feature ***
     =====================
    [..]
          (+) Call HAL_RAMCFG_Erase() to launch a hardware erase for the given
              SRAM.

          (+) The erase value is equal to 0 when launching erase hardware through
              RAMCFG.

          (+) SRAM2 write protected pages are erased when performing an erase
              through RAMCFG.

     *** RAMCFG HAL driver macros list ***
     =====================================
     [..]
       Below the list of used macros in RAMCFG HAL driver.

      (+) __HAL_RAMCFG_ENABLE_IT     : Enable the specified RAMCFG interrupts.
      (+) __HAL_RAMCFG_DISABLE_IT    : Disable the specified RAMCFG interrupts.
      (+) __HAL_RAMCFG_GET_FLAG      : Get the RAMCFG pending flags.
      (+) __HAL_RAMCFG_CLEAR_FLAG    : Clear the RAMCFG pending flags.
      (+) __HAL_RAMCFG_GET_IT_SOURCE : Check whether the specified RAMCFG
                                       interrupt source is enabled or not.
      (+) __HAL_RAMCFG_CRC_GET_FLAG  : Get the RAMCFG CRC pending flags.
      (+) __HAL_RAMCFG_CRC_CLEAR_FLAG: Clear the RAMCFG CRC pending flags.
  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @defgroup RAMCFG RAMCFG
  * @brief RAMCFG HAL module driver
  * @{
  */

#ifdef HAL_RAMCFG_MODULE_ENABLED

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/** @addtogroup FLASH_Private_Constants
  * @{
  */
#define RAMCFG_TIMEOUT_VALUE 50000U
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup RAMCFG_Exported_Functions
  * @{
  */

/** @addtogroup RAMCFG_Exported_Functions_Group1
  *
@verbatim
 ===============================================================================
             ##### Initialization and de-initialization Functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing to initialize and de-initialize the
    RAMCFG instance.
    [..]
    The HAL_RAMCFG_Init() function follows the RAMCFG instance configuration
    procedures as described in the reference manual.
    The HAL_RAMCFG_DeInit() function allows to deinitialize the RAMCFG instance.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the RAMCFG by clearing flags and disabling interrupts.
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG
  *                   instance.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_Init(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the RAMCFG peripheral handle */
  if (hramcfg == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RAMCFG_ALL_INSTANCE(hramcfg->Instance));

  /* Update RAMCFG peripheral state */
  hramcfg->State = HAL_RAMCFG_STATE_BUSY;

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
  /* Check if a valid MSP API was registered */
  if (hramcfg->MspInitCallback != NULL)
  {
    /* Init the low level hardware */
    hramcfg->MspInitCallback(hramcfg);
  }
#else
  HAL_RAMCFG_MspInit(hramcfg);
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */

  /* Unlock the SRAM ECC enable bit and disable the ECC feature */
  WRITE_REG(hramcfg->Instance->ECCKEY, RAMCFG_ECC_KEY1);
  WRITE_REG(hramcfg->Instance->ECCKEY, RAMCFG_ECC_KEY2);
  hramcfg->Instance->CR &= ~(RAMCFG_CR_ECCE | RAMCFG_CR_ALE);

  /* Disable all RAMCFG interrupts */
  __HAL_RAMCFG_DISABLE_IT(hramcfg, RAMCFG_IT_ALL);

  /* Clear RAMCFG monitor flags */
  __HAL_RAMCFG_CLEAR_FLAG(hramcfg, RAMCFG_FLAGS_ALL);

  /* Initialise the RAMCFG error code */
  hramcfg->ErrorCode = HAL_RAMCFG_ERROR_NONE;

  /* Initialize the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the RAMCFG peripheral.
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG
  *                   instance.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_DeInit(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the RAMCFG peripheral handle */
  if (hramcfg == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RAMCFG_ALL_INSTANCE(hramcfg->Instance));

  /* Unlock the SRAM ECC enable bit and disable the ECC feature */
  WRITE_REG(hramcfg->Instance->ECCKEY, RAMCFG_ECC_KEY1);
  WRITE_REG(hramcfg->Instance->ECCKEY, RAMCFG_ECC_KEY2);
  hramcfg->Instance->CR &= ~(RAMCFG_CR_ECCE | RAMCFG_CR_ALE);

  /* Disable all RAMCFG interrupts */
  __HAL_RAMCFG_DISABLE_IT(hramcfg, RAMCFG_IT_ALL);

  /* Clear RAMCFG monitor flags */
  __HAL_RAMCFG_CLEAR_FLAG(hramcfg, RAMCFG_FLAGS_ALL);

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
  /* Check if a valid MSP API was registered */
  if (hramcfg->MspDeInitCallback != NULL)
  {
    /* Init the low level hardware */
    hramcfg->MspDeInitCallback(hramcfg);
  }

  /* Clean callbacks */
  hramcfg->DetectSingleErrorCallback = NULL;
  hramcfg->DetectDoubleErrorCallback = NULL;
#else
  HAL_RAMCFG_MspDeInit(hramcfg);
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */

  /* Reset the RAMCFG error code */
  hramcfg->ErrorCode = HAL_RAMCFG_ERROR_NONE;

  /* Reset the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_RESET;

  return HAL_OK;
}

/**
  * @brief Initialize the RAMCFG MSP.
  * @param hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMCFG.
  * @retval None.
  */
__weak void HAL_RAMCFG_MspInit(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hramcfg);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RAMCFG_MspInit can be implemented in the user file      */
}

/**
  * @brief DeInitialize the RAMCFG MSP.
  * @param hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMCFG.
  * @retval None.
  */
__weak void HAL_RAMCFG_MspDeInit(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hramcfg);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RAMCFG_MspDeInit can be implemented in the user file    */
}
/**
  * @}
  */

/** @addtogroup RAMCFG_Exported_Functions_Group2
  *
@verbatim
 ===============================================================================
                      ##### ECC Operations Functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing to manage ECC feature provided by
    the RAMCFG peripheral.
    [..]
    The HAL_RAMCFG_StartECC() function allows enabling and starting the ECC
    mechanism for the selected RAMCFG instance.
    The HAL_RAMCFG_StopECC() function allows disabling and stopping the ECC
    mechanism for the selected RAMCFG instance.
    The HAL_RAMCFG_EnableNotification() function allows to enabling interrupts
    for single ECC error, double ECC error and NMI error.
    The HAL_RAMCFG_DisableNotification() function allows to disabling interrupts
    for single ECC error, double ECC error. When NMI interrupt is enabled it
    could not be disabled only by a global peripheral reset or by a system reset.
    The HAL_RAMCFG_IsECCErrorDetected() function allows to check if an ECC error
    is occurred.
    The HAL_RAMCFG_GetSingleErrorAddress() function allows to get the address of
    the last single ECC error detected.
    The HAL_RAMCFG_GetDoubleErrorAddress() function allows to get the address of
    the last double ECC error detected.

@endverbatim
  * @{
  */

/**
  * @brief  Start ECC mechanism for the given SRAM.
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG
  *                   instance.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_StartECC(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_ECC_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Check if ECC mechanism is active */
    if ((hramcfg->Instance->CR & RAMCFG_CR_ECCE) != RAMCFG_CR_ECCE)
    {
      /* Start the SRAM ECC mechanism and latching the error address */
      hramcfg->Instance->CR |= (RAMCFG_CR_ECCE | RAMCFG_CR_ALE);
    }
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_BUSY;

    /* Return error status */
    return HAL_ERROR;
  }

  /* Update the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Stop ECC mechanism for the given SRAM.
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG
  *                   instance.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_StopECC(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_ECC_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Check if ECC mechanism is active */
    if ((hramcfg->Instance->CR & RAMCFG_CR_ECCE) == RAMCFG_CR_ECCE)
    {
      /* Unlock the SRAM ECC bit */
      WRITE_REG(hramcfg->Instance->ECCKEY, RAMCFG_ECC_KEY1);
      WRITE_REG(hramcfg->Instance->ECCKEY, RAMCFG_ECC_KEY2);

      /* Start the SRAM ECC mechanism and latching the error address */
      hramcfg->Instance->CR &= ~(RAMCFG_CR_ECCE | RAMCFG_CR_ALE);
    }
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_BUSY;

    /* Return error status */
    return HAL_ERROR;
  }

  /* Update the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Enable the RAMCFG error interrupts.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @param  Notifications : Select the notification to be enabled.
  *                         This parameter could be any value of @ref
  *                         RAMCFG_Interrupt group.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_EnableNotification(RAMCFG_HandleTypeDef *hramcfg, uint32_t Notifications)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_ECC_INSTANCE(hramcfg->Instance));
  assert_param(IS_RAMCFG_INTERRUPT(Notifications));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Enable RAMCFG interrupts */
    __HAL_RAMCFG_ENABLE_IT(hramcfg, Notifications);
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_BUSY;

    /* Return error status */
    return HAL_ERROR;
  }

  /* Update the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Disable the RAMCFG error interrupts.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @param  Notifications : Select the notification to be disabled.
  *                         This parameter could be :
  *                         RAMCFG_IT_SINGLEERR : Single Error Interrupt.
  *                         RAMCFG_IT_DOUBLEERR : Double Error Interrupt.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_DisableNotification(RAMCFG_HandleTypeDef *hramcfg, uint32_t Notifications)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_ECC_INSTANCE(hramcfg->Instance));
  assert_param(IS_RAMCFG_INTERRUPT(Notifications));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Disable RAMCFG interrupts */
    __HAL_RAMCFG_DISABLE_IT(hramcfg, Notifications);
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_BUSY;

    /* Return error status */
    return HAL_ERROR;
  }

  /* Update the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Check if an ECC single error was occurred.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_RAMCFG_IsECCSingleErrorDetected(const RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_ECC_INSTANCE(hramcfg->Instance));

  /* Return the state of SEDC flag */
  return ((READ_BIT(hramcfg->Instance->ISR, RAMCFG_FLAG_SINGLEERR) == (RAMCFG_FLAG_SINGLEERR)) ? 1UL : 0UL);
}

/**
  * @brief  Check if an ECC double error was occurred.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_RAMCFG_IsECCDoubleErrorDetected(const RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_ECC_INSTANCE(hramcfg->Instance));

  /* Return the state of SEDC flag */
  return ((READ_BIT(hramcfg->Instance->ISR, RAMCFG_FLAG_DOUBLEERR) == (RAMCFG_FLAG_DOUBLEERR)) ? 1UL : 0UL);
}

/**
  * @brief  Get the RAMCFG single error address.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval Single error address offset.
  */
uint32_t HAL_RAMCFG_GetSingleErrorAddress(const RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_ECC_INSTANCE(hramcfg->Instance));

  return hramcfg->Instance->SEAR;
}

/**
  * @brief  Get the RAMCFG double error address.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval Double error address offset.
  */
uint32_t HAL_RAMCFG_GetDoubleErrorAddress(const RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_ECC_INSTANCE(hramcfg->Instance));

  return hramcfg->Instance->DEAR;
}
/**
  * @}
  */

/** @addtogroup RAMCFG_Exported_Functions_Group5
  *
@verbatim
 ===============================================================================
                      ##### Erase Operation Functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing a hardware erase for the given SRAM.
    [..]
    The HAL_RAMCFG_Erase() function allows a hardware mass erase for the given
    SRAM. The erase value for all SRAMs is 0.

@endverbatim
  * @{
  */

/**
  * @brief  launch a Mass Erase for the given SRAM.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @param  Timeout       : Maximum SRAM erase operation timeout.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_Erase(RAMCFG_HandleTypeDef *hramcfg)
{
  uint32_t Timeout = RAMCFG_TIMEOUT_VALUE, tickstart = HAL_GetTick();

  /* Check the parameters */
  assert_param(IS_RAMCFG_ALL_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Unlock the RAMCFG erase bit */
    WRITE_REG(hramcfg->Instance->ERKEYR, RAMCFG_ERASE_KEY1);
    WRITE_REG(hramcfg->Instance->ERKEYR, RAMCFG_ERASE_KEY2);

    /* Start the SRAM erase operation */
    hramcfg->Instance->CR |= RAMCFG_CR_SRAMER;

    /*
       Wait for the SRAM hardware erase operation to complete by polling on
       SRAMBUSY flag to be reset.
    */
    while (__HAL_RAMCFG_GET_FLAG(hramcfg, RAMCFG_FLAG_SRAMBUSY) != 0U)
    {
      if (Timeout != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
        {
          /* Update the RAMCFG error code */
          hramcfg->ErrorCode = HAL_RAMCFG_ERROR_TIMEOUT;

          /* Update the RAMCFG state */
          hramcfg->State = HAL_RAMCFG_STATE_ERROR;

          /* Return error status */
          return HAL_ERROR;
        }
      }
    }
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_BUSY;

    /* Return error status */
    return HAL_ERROR;
  }

  /* Update the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_READY;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup RAMCFG_Exported_Functions_Group6
  *
@verbatim
 ===============================================================================
               ##### Handle Interrupt and Callbacks Functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing to handle RAMCFG interrupts and
    Register / UnRegister the different callbacks.
    [..]
    The HAL_RAMCFG_IRQHandler() function allows to handle the active RAMCFG
    interrupt request.
    The HAL_RAMCFG_RegisterCallback() function allows to register the selected
    RAMCFG callbacks.
    The HAL_RAMCFG_UnRegisterCallback() function allows to unregister the
    selected RAMCFG callbacks.
@endverbatim
  * @{
  */

/**
  * @brief  Handles RAMCFG interrupt request.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval None.
  */
void HAL_RAMCFG_IRQHandler(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Single Error Interrupt Management ****************************************/
  if (__HAL_RAMCFG_GET_IT_SOURCE(hramcfg, RAMCFG_IT_SINGLEERR) != 0U)
  {
    if (__HAL_RAMCFG_GET_FLAG(hramcfg, RAMCFG_FLAG_SINGLEERR) != 0U)
    {
      /* Clear active flags */
      __HAL_RAMCFG_CLEAR_FLAG(hramcfg, RAMCFG_FLAG_SINGLEERR);

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
      /* Check if a valid single error callback is registered */
      if (hramcfg->DetectSingleErrorCallback != NULL)
      {
        /* Single error detection callback */
        hramcfg->DetectSingleErrorCallback(hramcfg);
      }
#else
      HAL_RAMCFG_DetectSingleErrorCallback(hramcfg);
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */
    }
  }

  /* Double Error Interrupt Management ****************************************/
  if (__HAL_RAMCFG_GET_IT_SOURCE(hramcfg, RAMCFG_IT_DOUBLEERR) != 0U)
  {
    if (__HAL_RAMCFG_GET_FLAG(hramcfg, RAMCFG_FLAG_DOUBLEERR) != 0U)
    {
      /* Clear active flags */
      __HAL_RAMCFG_CLEAR_FLAG(hramcfg, RAMCFG_FLAG_DOUBLEERR);

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
      /* Check if a valid double error callback is registered */
      if (hramcfg->DetectDoubleErrorCallback != NULL)
      {
        /* Double error detection callback */
        hramcfg->DetectDoubleErrorCallback(hramcfg);
      }
#else
      HAL_RAMCFG_DetectDoubleErrorCallback(hramcfg);
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @brief  RAMCFG single error detection callback.
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG.
  * @retval None.
  */
__weak void HAL_RAMCFG_DetectSingleErrorCallback(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hramcfg);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RAMCFG_DetectSingleErrorCallback could be implemented in
            the user file.                                                    */
}

/**
  * @brief  RAMCFG double error detection callback.
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG.
  * @retval None.
  */
__weak void HAL_RAMCFG_DetectDoubleErrorCallback(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hramcfg);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RAMCFG_DetectDoubleErrorCallback could be implemented in
            the user file.                                                    */
}

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register RAMCFG callbacks.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @param  CallbackID    : User Callback identifier a HAL_MDMA_CallbackIDTypeDef
  *                         ENUM as parameter.
  * @param  pCallback     : Pointer to private callback function.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_RegisterCallback(RAMCFG_HandleTypeDef *hramcfg, HAL_RAMCFG_CallbackIDTypeDef CallbackID,
                                              void (* pCallback)(RAMCFG_HandleTypeDef *_hramcfg))
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hramcfg->ErrorCode |= HAL_RAMCFG_ERROR_INVALID_CALLBACK;

    /* Return error status */
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RAMCFG_ALL_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    switch (CallbackID)
    {
      case  HAL_RAMCFG_SE_DETECT_CB_ID:
        /* Register single error callback */
        hramcfg->DetectSingleErrorCallback = pCallback;
        break;

      case  HAL_RAMCFG_DE_DETECT_CB_ID:
        /* Register single error callback */
        hramcfg->DetectDoubleErrorCallback = pCallback;
        break;

      case HAL_RAMCFG_MSPINIT_CB_ID :
        /* Register msp init callback */
        hramcfg->MspInitCallback = pCallback;
        break;

      case HAL_RAMCFG_MSPDEINIT_CB_ID :
        /* Register msp de-init callback */
        hramcfg->MspDeInitCallback = pCallback;
        break;

      default:
        /* Update the error code */
        hramcfg->ErrorCode |= HAL_RAMCFG_ERROR_INVALID_CALLBACK;

        /* Update return status */
        status = HAL_ERROR;
        break;
    }
  }
  else if (hramcfg->State == HAL_RAMCFG_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_RAMCFG_MSPINIT_CB_ID :
        /* Register msp init callback */
        hramcfg->MspInitCallback = pCallback;
        break;

      case HAL_RAMCFG_MSPDEINIT_CB_ID :
        /* Register msp de-init callback */
        hramcfg->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hramcfg->ErrorCode |= HAL_RAMCFG_ERROR_INVALID_CALLBACK;

        /* Update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_INVALID_CALLBACK;

    /* Update return status */
    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  UnRegister RAMCFG callbacks.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @param  CallbackID    : User Callback identifier a HAL_MDMA_CallbackIDTypeDef
  *                         ENUM as parameter.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_UnRegisterCallback(RAMCFG_HandleTypeDef *hramcfg, HAL_RAMCFG_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_RAMCFG_ALL_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    switch (CallbackID)
    {
      case  HAL_RAMCFG_SE_DETECT_CB_ID:
        /* UnRegister single error callback */
        hramcfg->DetectSingleErrorCallback = NULL;
        break;

      case  HAL_RAMCFG_DE_DETECT_CB_ID:
        /* UnRegister double error callback */
        hramcfg->DetectDoubleErrorCallback = NULL;
        break;

      case HAL_RAMCFG_MSPINIT_CB_ID :
        /* UnRegister msp init callback */
        hramcfg->MspInitCallback = NULL;
        break;

      case HAL_RAMCFG_MSPDEINIT_CB_ID :
        /* UnRegister msp de-init callback */
        hramcfg->MspDeInitCallback = NULL;
        break;

      case  HAL_RAMCFG_ALL_CB_ID:
        /* UnRegister all available callbacks */
        hramcfg->DetectSingleErrorCallback = NULL;
        hramcfg->DetectDoubleErrorCallback = NULL;
        hramcfg->MspDeInitCallback         = NULL;
        hramcfg->MspInitCallback           = NULL;
        break;

      default:
        /* Return error status */
        status = HAL_ERROR;
        break;
    }
  }
  else if (hramcfg->State == HAL_RAMCFG_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_RAMCFG_MSPINIT_CB_ID :
        /* UnRegister msp init callback */
        hramcfg->MspInitCallback = NULL;
        break;

      case HAL_RAMCFG_MSPDEINIT_CB_ID :
        /* UnRegister msp de-init callback */
        hramcfg->MspDeInitCallback = NULL;
        break;

      case  HAL_RAMCFG_ALL_CB_ID:
        /* UnRegister all available callbacks */
        hramcfg->MspDeInitCallback = NULL;
        hramcfg->MspInitCallback   = NULL;
        break;

      default :
        /* Update the error code */
        hramcfg->ErrorCode |= HAL_RAMCFG_ERROR_INVALID_CALLBACK;

        /* Update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_INVALID_CALLBACK;

    /* Update return status */
    status = HAL_ERROR;
  }

  return status;
}
/**
  * @}
  */
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */

/** @addtogroup RAMCFG_Exported_Functions_Group7
  *
@verbatim
 ===============================================================================
                    ##### State and Error Functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing to check and get the RAMCFG state
    and the error code .
    [..]
    The HAL_RAMCFG_GetState() function allows to get the RAMCFG peripheral
    state.
    The HAL_RAMCFG_GetError() function allows to Get the RAMCFG peripheral error
    code.

@endverbatim
  * @{
  */

/**
  * @brief  Get the RAMCFG peripheral state.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval RAMCFG state.
  */
HAL_RAMCFG_StateTypeDef HAL_RAMCFG_GetState(const RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_ALL_INSTANCE(hramcfg->Instance));

  /* Return the RAMCFG state */
  return hramcfg->State;
}

/**
  * @brief  Get the RAMCFG peripheral error code.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval RAMCFG error code.
  */
uint32_t HAL_RAMCFG_GetError(const RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_ALL_INSTANCE(hramcfg->Instance));

  /* Return the RAMCFG error code */
  return hramcfg->ErrorCode;
}
/**
  * @}
  */


/** @addtogroup RAMCFG_Exported_Functions_Group8
  *
@verbatim
 ===============================================================================
                         ##### CRC Functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing to manage the RAMCFG CRC
    (Cyclic Redundancy Check CRC-32)
    [..]
    The HAL_RAMCFG_ActiveCRC() function allows to
    The HAL_RAMCFG_ComputeCRC() function allows to
    The HAL_RAMCFG_CheckCRC() function allows to

@endverbatim
  * @{
  */

/**
  * @brief  Configure CRC mode and CRC Buffer Size
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval RAMCFG error code
  */
HAL_StatusTypeDef HAL_RAMCFG_ConfigCRC(RAMCFG_HandleTypeDef *hramcfg, const HAL_RAMCFG_ConfigCRCTypeDef *crcConfig)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_CRC_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Write 0x0 in CRCC[1:0] bits of the RAMCFG_xCCR1 to deactivate the CRC */
    MODIFY_REG(hramcfg->Instance->CCR1, RAMCFG_CCR1_CRCC, 0U);

    /* Write 1 in SRAMHWERDIS bit of RAMCFG control register to disable hardware erase */
    hramcfg->Instance->CR |= RAMCFG_CR_SRAMHWERDIS;

    /* Select the size of the buffer to take into account during CRC computation */
    MODIFY_REG(hramcfg->Instance->CCR1, RAMCFG_CCR1_CRCBS,     \
               (((uint32_t)(crcConfig->CRCBufferSize) << RAMCFG_CCR1_CRCBS_Pos) & RAMCFG_CCR1_CRCBS_Msk));

    /* Configure the CRC mode */
    MODIFY_REG(hramcfg->Instance->CCR1, RAMCFG_CCR1_CRCC,      \
               (((uint32_t)(crcConfig->CRCMode) << RAMCFG_CCR1_CRCC_Pos) & RAMCFG_CCR1_CRCC_Msk));
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_BUSY;

    /* Return error status */
    return HAL_ERROR;
  }

  /* Update the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Compute CRC
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval RAMCFG state
  */
HAL_StatusTypeDef HAL_RAMCFG_ComputeCRC(RAMCFG_HandleTypeDef *hramcfg)
{
  uint32_t Timeout = RAMCFG_TIMEOUT_VALUE;
  uint32_t tickstart = HAL_GetTick();
  uint32_t mode;

  /* Check the parameters */
  assert_param(IS_RAMCFG_CRC_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Read CRC mode */
    mode = READ_BIT(hramcfg->Instance->CCR1, RAMCFG_CCR1_CRCC);

    switch (mode)
    {
      case 0: /* CRC disable so do nothing */
        break;

      case 1: /* CRC computation */

        /* Start CRC computation */
        hramcfg->Instance->CCR2 |= RAMCFG_CCR2_CRCCS;

        /* Wait computation ending */
        while (READ_BIT(hramcfg->Instance->CSR, RAMCFG_CSR_CRCEOC) != RAMCFG_CSR_CRCEOC)
        {
          if (Timeout != HAL_MAX_DELAY)
          {
            if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
            {
              /* Update the RAMCFG error code */
              hramcfg->ErrorCode = HAL_RAMCFG_ERROR_TIMEOUT;

              /* Update the RAMCFG state */
              hramcfg->State = HAL_RAMCFG_STATE_ERROR;

              /* Return error status */
              return HAL_ERROR;
            }
          }
        }

        /* Save calculated signature in reference signature */
        hramcfg->Instance->CRSR = hramcfg->Instance->CCSR;
        break;

      case 2: /* CRC computation and signature check */

        /* Clear registers */
        hramcfg->Instance->CCR2 |= RAMCFG_CCR2_CRCFC;

        /* Start CRC computation */
        hramcfg->Instance->CCR2 |= RAMCFG_CCR2_CRCCS;

        /* Wait computation ending */
        while (READ_BIT(hramcfg->Instance->CSR, RAMCFG_CSR_CRCEOC) != RAMCFG_CSR_CRCEOC)
        {
          if (Timeout != HAL_MAX_DELAY)
          {
            if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
            {
              /* Update the RAMCFG error code */
              hramcfg->ErrorCode = HAL_RAMCFG_ERROR_TIMEOUT;

              /* Update the RAMCFG state */
              hramcfg->State = HAL_RAMCFG_STATE_ERROR;

              /* Return error status */
              return HAL_ERROR;
            }
          }
        }

        /* Check CRC signature validity */
        if (READ_BIT(hramcfg->Instance->CSR, RAMCFG_CSR_CRCSCS) != RAMCFG_CSR_CRCSCS)
        {
          /* Fault detected in SRAM data */
          hramcfg->ErrorCode = HAL_RAMCFG_ERROR_CRC;

          /* Update the RAMCFG state */
          hramcfg->State = HAL_RAMCFG_STATE_READY;

          /* Return error status */
          return HAL_ERROR;
        }
        break;

      default:
        /* Update the RAMCFG state */
        hramcfg->State = HAL_RAMCFG_STATE_READY;

        /* Return error status */
        return HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_BUSY;

    /* Return error status */
    return HAL_ERROR;
  }

  /* Update the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Enable erase operation done after a system reset
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval RAMCFG error code
  */
HAL_StatusTypeDef HAL_RAMCFG_HWEraseEnable(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_CRC_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    MODIFY_REG(hramcfg->Instance->CR, RAMCFG_CR_SRAMHWERDIS, 0U);
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_BUSY;

    /* Return error status */
    return HAL_ERROR;
  }

  /* Update the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Disable erase operation done after a system reset
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval RAMCFG error code
  */
HAL_StatusTypeDef HAL_RAMCFG_HWEraseDisable(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_CRC_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    MODIFY_REG(hramcfg->Instance->CR, 0U, RAMCFG_CR_SRAMHWERDIS);
  }
  else
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_BUSY;

    /* Return error status */
    return HAL_ERROR;
  }

  /* Update the RAMCFG state */
  hramcfg->State = HAL_RAMCFG_STATE_READY;

  return HAL_OK;
}
/**
  * @}
  */


#endif /* HAL_RAMCFG_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
