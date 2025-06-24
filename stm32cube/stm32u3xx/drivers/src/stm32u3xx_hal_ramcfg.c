/**
  ******************************************************************************
  * @file    stm32u3xx_hal_ramcfg.c
  * @author  MCD Application Team
  * @brief   RAMCFG HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the RAMs configuration controller peripheral:
  *           + RAMCFG Initialization and De-initialization Functions.
  *           + RAMCFG Parity Error Detection Functions.
  *           + RAMCFG Write Protection Functions.
  *           + RAMCFG Erase Operation Functions.
  *           + RAMCFG Handle Interrupt and Callbacks Functions.
  *           + RAMCFG State and Error Functions.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
        with the following feature:

#ifdef SRAM3_BASE
        (++) Parity check on SRAM2 and SRAM3
#else
        (++) Parity check on SRAM2
#endif

        (++) Write protection (1-Kbyte granularity) on SRAM2
        (++) SRAM software erase on all SRAMs

        (++) SRAM1 placed in Core Domain.
             (+++) Size         = 192 kB

        (++) SRAM2 placed in Core Domain.
             (+++) Size         = 64 kB

#ifdef SRAM3_BASE
        (++) SRAM3 placed in Core Domain.
             (+++) Size         = 320 kB

    (+) SRAM2 and SRAM3 support Parity Error Detection (PED) correction feature.
#else
    (+) SRAM2 supports Parity Error Detection (PED) correction feature.
#endif

        When the ALE bit is set in RAMCFG SRAM control register (RAMCFG_MxCR),
        the failing parity SRAM offset word address is stored in the RAMCFG SRAM
        parity error address register RAMCFG_MxPEAR.

    (+) Each SRAMs can be erased independently through its RAMCFG instance.

    (+) SRAM2 is divided into 64 pages with
        1 kB granularity. Each page can be write protected independently through
        its RAMCFG instance.


  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) Call HAL_RAMCFG_Init() to initialize the RAMCFG peripheral before using
       any feature. Call HAL_RAMCFG_DeInit() to de-initialize the RAMCFG when
       using this peripheral is no more needed or a hardware issue has occurred.
       HAL_RAMCFG_Init() and HAL_RAMCFG_DeInit() APIs do not change the activation
       status of Parity error feature. It is managed by HAL_RAMCFG_EnableParityErrorDetection(),
       HAL_RAMCFG_DisableParityErrorDetection() or option bytes (When available on the device).

     *** Parity Error Detection (PED) feature ***
     ============================================
    [..]
#ifdef SRAM3_BASE
          (+) Parity is supported by SRAM2 and SRAM3.
#else
          (+) Parity is supported by SRAM2.
#endif

          (+) Call HAL_RAMCFG_EnableParityErrorDetection() to set PCE bit and enable parity error detection.

          (+) Call HAL_RAMCFG_DisableParityErrorDetection() to clear PCE bit and disable parity error detection.

              The parity error detection can be also enable or disable with the SRAMx_PE user option bit
              in FLASH_OPTR register.

              When enabling SRAM parity, it is advised to initialize by software the whole
              RAM memory at the beginning of the code. This to avoid getting parity errors
              when reading non-initialized addresses.

          (+) Call HAL_RAMCFG_EnableNotification() and HAL_RAMCFG_DisableNotification()
              to enable and disable PED interrupts. Interrupts could be:
                    (++) Parity error detection interrupt.
                    (++) Parity error detection interrupt redirected to Non Maskable
                          interrupt (NMI).

              When a parity error is detected the PED and CPED bits are set in RAMCFG SRAM
              interrupt status register (RAMCFG_MxISR) and RAMCFG SRAM interrupt clear register
              (RAMCFG_MxICR). An interrupt or NMI can be generated if enabled by the PEIE or PENMI
              bits in the RAMCFG SRAM control register (RAMCFG_MxCR).

          (+) Call HAL_RAMCFG_LatchParityErrorAddress() to set ALE bit and track parity error location address

          (+) Call HAL_RAMCFG_GetParityErrorAddress() to get the failing parity SRAM offset word
              address stored in the RAMCFG parity error address register (RAMCFG_MxPEAR) together
              with the failing byte(s) parity error flag and the AHB bus master ID.

              When the PED and CPED bits are already set any subsequent parity failing access SRAM
              offset word address is no longer updated. A new parity error SRAM offset word address will
              only be latched when PED and CPED are cleared.

          (+) Call HAL_RAMCFG_IsParityErrorDetected() to check if an Parity error was detected.
              This API is used in silent mode (No PED interrupt is enabled).

     *** Write protection feature ***
     ================================
    [..]
          (+) Call HAL_RAMCFG_EnableWriteProtection() to enable the write
              protection for the given SRAM2 page(s).

          (+) There is no API to disable write protection as this feature can
              be disabled only by a global peripheral reset or system reset.

          (+) Any write access to a write protected area of SRAM2 causes a
              HardFault interrupt.

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
  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal.h"

/** @addtogroup STM32U3xx_HAL_Driver
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

/** @addtogroup RAMCFG_Private_Constants
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
    This section provides functions to initialize and de-initialize the
    RAMCFG instance.
    [..]
    The HAL_RAMCFG_Init() function follows the RAMCFG instance configuration
    procedures as described in the reference manual.
    The HAL_RAMCFG_DeInit() function allows deinitializing the RAMCFG instance.
    HAL_RAMCFG_Init() and HAL_RAMCFG_DeInit() APIs do not change the activation
    status of Parity error feature. It is managed by HAL_RAMCFG_EnableParityErrorDetection(),
    HAL_RAMCFG_DisableParityErrorDetection() or option bytes (When available on the device).
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

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1U)

  /* Init the low level hardware */
  /* Check if a valid MSP API was registered */
  if (hramcfg->MspInitCallback == NULL)
  {
    /* Legacy callback */
    hramcfg->MspInitCallback = HAL_RAMCFG_MspInit;
  }
  hramcfg->MspInitCallback(hramcfg);
#else
  HAL_RAMCFG_MspInit(hramcfg);
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */

  /* Initialize the RAMCFG error code */
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

  /* Disable latch parity error address */
  hramcfg->Instance->CR &= ~(RAMCFG_CR_ALE);

  /* Disable all RAMCFG interrupts */
  __HAL_RAMCFG_DISABLE_IT(hramcfg, RAMCFG_IT_ALL);

  /* Clear RAMCFG monitor flags */
  __HAL_RAMCFG_CLEAR_FLAG(hramcfg, RAMCFG_FLAG_PARITYERR);

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1U)
  /* Check if a valid MSP API was registered */
  if (hramcfg->MspDeInitCallback != NULL)
  {
    /* Init the low level hardware */
    hramcfg->MspDeInitCallback(hramcfg);
  }

  /* Clean callbacks */
  hramcfg->DetectParityErrorCallback = NULL;
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
          ##### (Parity Error Detection) PED Operations Functions  #####
 ===============================================================================
    [..]
    This section provides functions to manage Parity Error Detection
    (PED) feature provided by the RAMCFG peripheral.
    [..]
    The HAL_RAMCFG_EnableParityErrorDetection() function allows enabling the parity error
    detection for the selected RAMCFG instance.
    The HAL_RAMCFG_DisableParityErrorDetection() function allows disabling the parity error
    detection for the selected RAMCFG instance.
    The HAL_RAMCFG_LatchParityErrorAddress() function allows enabling the parity error
    fail address latch for the selected RAMCFG instance.
    The HAL_RAMCFG_UnlatchParityErrorAddress() function allows disabling the parity error
    fail address latch for the selected RAMCFG instance.
    The HAL_RAMCFG_EnableNotification() function allows enabling interrupts
    for parity error detection and NMI error.
    The HAL_RAMCFG_DisableNotification() function allows disabling interrupts
    for parity error detection. When NMI interrupt is enabled, it can only be
    disabled by a global peripheral reset or by a system reset.
    The HAL_RAMCFG_IsParityErrorDetected() function allows checking if a parity
    error is detected.
    The HAL_RAMCFG_GetParityErrorAddress() function allows getting the address of
    the parity error detected.

@endverbatim
  * @{
  */

/**
  * @brief  Parity error detection enable.
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG
  *                   instance.
#ifdef SRAM3_BASE
  * @note   Parity error detection only available for SRAM2 and SRAM3
#else
  * @note   Parity error detection only available for SRAM2
#endif
    @note   When parity is enabled by SRAMx_PE user option bit, the PCE bit is automatically set (in RAMCFG_MxCR) after
  *         system reset.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_EnableParityErrorDetection(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_PED_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Enable parity error detection */
    SET_BIT(hramcfg->Instance->CR, RAMCFG_CR_PCE);
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
  * @brief  Parity error detection disable.
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG
  *                   instance.
#ifdef SRAM3_BASE
  * @note   Parity error detection only available for SRAM2 and SRAM3
#else
  * @note   Parity error detection only available for SRAM2
#endif
  * @note   When parity is enabled by SRAMx_PE user option bit, the PCE bit is automatically set (in RAMCFG_M2CR) after
  *         system reset.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_DisableParityErrorDetection(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_PED_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Check if PCE is enable */
    if ((READ_BIT(hramcfg->Instance->CR, RAMCFG_CR_PCE) == RAMCFG_CR_PCE))
    {
      /* Unlock the RAMCFG parity write protection key bit */
      WRITE_REG(hramcfg->Instance->PARKEYR, RAMCFG_PARITY_KEY1);
      WRITE_REG(hramcfg->Instance->PARKEYR, RAMCFG_PARITY_KEY2);

      /* Disable parity error detection */
      CLEAR_BIT(hramcfg->Instance->CR, RAMCFG_CR_PCE);

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
  * @brief  Parity error fail address latch enable.
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG
  *                   instance.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_LatchParityErrorAddress(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_PED_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Enable parity error fail address latch */
    SET_BIT(hramcfg->Instance->CR, RAMCFG_CR_ALE);
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
  * @brief  Parity error fail address latch disable
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG
  *                   instance.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_UnlatchParityErrorAddress(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_PED_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Disable parity error fail address latch */
    CLEAR_BIT(hramcfg->Instance->CR, RAMCFG_CR_ALE);
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
  *                         This parameter could be any value of @ref RAMCFG_Interrupt group.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_EnableNotification(RAMCFG_HandleTypeDef *hramcfg, uint32_t Notifications)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_PED_INSTANCE(hramcfg->Instance));
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
  *                         RAMCFG_IT_PARITYERR : Parity Error Detection.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_DisableNotification(RAMCFG_HandleTypeDef *hramcfg, uint32_t Notifications)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_PED_INSTANCE(hramcfg->Instance));
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
  * @brief  Check if a parity error was detected.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_RAMCFG_IsParityErrorDetected(const RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_PED_INSTANCE(hramcfg->Instance));

  /* Return the state of PED flag */
  return ((READ_BIT(hramcfg->Instance->ISR, RAMCFG_FLAG_PARITYERR) == (RAMCFG_FLAG_PARITYERR)) ? 1UL : 0UL);
}

/**
  * @brief  Get the RAMCFG parity error address.
  * @param  hramcfg         Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @retval Parity error address.
  */
uint32_t HAL_RAMCFG_GetParityErrorAddress(const RAMCFG_HandleTypeDef *hramcfg)
{
  /* Check the parameters */
  assert_param(IS_RAMCFG_PED_INSTANCE(hramcfg->Instance));

  return READ_REG(hramcfg->Instance->PEAR);
}

/**
  * @}
  */


/** @addtogroup RAMCFG_Exported_Functions_Group3
  *
@verbatim
 ===============================================================================
                      ##### Write Protection Functions  #####
 ===============================================================================
    [..]
    This section provides functions to enable write protection feature for
    the page(s) of SRAM2.
    [..]
    The HAL_RAMCFG_EnableWriteProtection() function allows enabling the write
    protection for the page(s) of SRAM2.
    Disabling SRAM2 page(s) protection is performed only by a global
    peripheral reset or a by a system reset.

@endverbatim
  * @{
  */

/**
  * @brief  Enable write protection for the given page(s).
  * @note   Write protection feature could be disabled only by system reset.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @param  StartPage     : Select the start page number (from 0 to 63)
  * @param  NbPage        : Number of pages to be protected.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_EnableWriteProtection(RAMCFG_HandleTypeDef *hramcfg, uint32_t StartPage, uint32_t NbPage)
{
  uint32_t page_mask_0 = 0U;
  uint32_t page_mask_1 = 0U;

  /* Check the parameters */
  assert_param(IS_RAMCFG_WP_INSTANCE(hramcfg->Instance));
  assert_param(IS_RAMCFG_WRITEPROTECTION_PAGE(StartPage + NbPage));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Repeat for page number to be protected */
    for (uint32_t count = 0U; count < NbPage; count++)
    {
      if ((StartPage + count) < 32U)
      {
        page_mask_0 |= (1UL << (StartPage + count));
      }
      else
      {
        page_mask_1 |= (1UL << ((StartPage + count) - 32U));
      }
    }

    /* Apply mask to protect pages */
    WRITE_REG(hramcfg->Instance->WPR1, page_mask_0);
    WRITE_REG(hramcfg->Instance->WPR2, page_mask_1);
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

/** @addtogroup RAMCFG_Exported_Functions_Group4
  *
@verbatim
 ===============================================================================
                      ##### Erase Operation Functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing a hardware erase for the given SRAM.
    [..]
    The HAL_RAMCFG_Erase() function allowing a hardware mass erase for the given
    SRAM. The erase value for all SRAMs is 0.

@endverbatim
  * @{
  */

/**
  * @brief  Launches and waits for the mass erase completion of a given SRAM.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.

  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_Erase(RAMCFG_HandleTypeDef *hramcfg)
{
  uint32_t tickstart = HAL_GetTick();

  /* Check the parameters */
  assert_param(IS_RAMCFG_ER_INSTANCE(hramcfg->Instance));

  /* Check RAMCFG state */
  if (hramcfg->State == HAL_RAMCFG_STATE_READY)
  {
    /* Update RAMCFG peripheral state */
    hramcfg->State = HAL_RAMCFG_STATE_BUSY;

    /* Unlock the RAMCFG erase bit */
    WRITE_REG(hramcfg->Instance->ERKEYR, RAMCFG_ERASE_KEY1);
    WRITE_REG(hramcfg->Instance->ERKEYR, RAMCFG_ERASE_KEY2);

    /* Start the SRAM erase operation */
    SET_BIT(hramcfg->Instance->CR, RAMCFG_CR_SRAMER);

    /* Wait for the SRAM hardware erase operation to complete by polling on
       SRAMBUSY flag to be reset. */
    while (__HAL_RAMCFG_GET_FLAG(hramcfg, RAMCFG_FLAG_SRAMBUSY) != 0U)
    {
      if ((HAL_GetTick() - tickstart) > RAMCFG_TIMEOUT_VALUE)
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

/** @addtogroup RAMCFG_Exported_Functions_Group5
  *
@verbatim
 ===============================================================================
               ##### Handle Interrupt and Callbacks Functions  #####
 ===============================================================================
    [..]
    This section provides functions to handle RAMCFG interrupts and
    Register / UnRegister the different callbacks.
    [..]
    The HAL_RAMCFG_IRQHandler() function allows handling the active RAMCFG
    interrupt request.
    The HAL_RAMCFG_RegisterCallback() function allows registering the selected
    RAMCFG callbacks.
    The HAL_RAMCFG_UnRegisterCallback() function allows unregistering the
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
  if (__HAL_RAMCFG_GET_IT_SOURCE(hramcfg, RAMCFG_IT_PARITYERR) != 0U)
  {
    if (__HAL_RAMCFG_GET_FLAG(hramcfg, RAMCFG_FLAG_PARITYERR) != 0U)
    {
      /* Clear active flags */
      __HAL_RAMCFG_CLEAR_FLAG(hramcfg, RAMCFG_FLAG_PARITYERR);

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1U)
      /* Check if a valid single error callback is registered */
      if (hramcfg->DetectParityErrorCallback == NULL)
      {
        /* Legacy callback */
        hramcfg->DetectParityErrorCallback = HAL_RAMCFG_DetectParityErrorCallback;
      }
      hramcfg->DetectParityErrorCallback(hramcfg);
#else
      HAL_RAMCFG_DetectParityErrorCallback(hramcfg);
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @brief  RAMCFG parity error detection callback.
  * @param  hramcfg : Pointer to a RAMCFG_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMCFG.
  * @retval None.
  */
__weak void HAL_RAMCFG_DetectParityErrorCallback(RAMCFG_HandleTypeDef *hramcfg)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hramcfg);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_RAMCFG_DetectParityErrorCallback can be implemented in
            the user file.                                                    */
}

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register RAMCFG callbacks.
  * @param  hramcfg       : Pointer to a RAMCFG_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMCFG instance.
  * @param  CallbackID    : User Callback identifier a HAL_RAMCFG_CallbackIDTypeDef
  *                         ENUM as parameter.
  * @param  pCallback     : Pointer to private callback function.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMCFG_RegisterCallback(RAMCFG_HandleTypeDef *hramcfg,
                                              HAL_RAMCFG_CallbackIDTypeDef CallbackID,
                                              void (* pCallback)(RAMCFG_HandleTypeDef *_hramcfg))
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hramcfg->ErrorCode = HAL_RAMCFG_ERROR_INVALID_CALLBACK;

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
      case  HAL_RAMCFG_PE_DETECT_CB_ID:
        /* Register parity error detection callback */
        hramcfg->DetectParityErrorCallback = pCallback;
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
        hramcfg->ErrorCode = HAL_RAMCFG_ERROR_INVALID_CALLBACK;

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
        hramcfg->ErrorCode = HAL_RAMCFG_ERROR_INVALID_CALLBACK;

        /* Update return status */
        status = HAL_ERROR;
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
  * @param  CallbackID    : User Callback identifier a HAL_RAMCFG_CallbackIDTypeDef
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
      case  HAL_RAMCFG_PE_DETECT_CB_ID:
        /* UnRegister parity error detection callback */
        hramcfg->DetectParityErrorCallback = NULL;
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
        hramcfg->DetectParityErrorCallback = NULL;
        hramcfg->MspDeInitCallback         = NULL;
        hramcfg->MspInitCallback           = NULL;
        break;

      default:
        /* Update the error code */
        hramcfg->ErrorCode = HAL_RAMCFG_ERROR_INVALID_CALLBACK;

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
        hramcfg->ErrorCode = HAL_RAMCFG_ERROR_INVALID_CALLBACK;

        /* Update return status */
        status = HAL_ERROR;
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

/** @addtogroup RAMCFG_Exported_Functions_Group6
  *
@verbatim
 ===============================================================================
                    ##### State and Error Functions  #####
 ===============================================================================
    [..]
    This section provides functions to check and get the RAMCFG state
    and the error code .
    [..]
    The HAL_RAMCFG_GetState() function allows getting the RAMCFG peripheral
    state.
    The HAL_RAMCFG_GetError() function allows getting the RAMCFG peripheral error
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


#endif /* HAL_RAMCFG_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

