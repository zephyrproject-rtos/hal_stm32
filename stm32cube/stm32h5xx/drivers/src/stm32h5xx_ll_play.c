/**
  ******************************************************************************
  * @file    stm32h5xx_ll_play.c
  * @author  MCD Application Team
  * @brief   PLAY LL module driver.
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
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_ll_play.h"
#include "stm32h5xx_ll_bus.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32H5xx_LL_Driver
  * @{
  */

#if defined(PLAY1)

/** @addtogroup PLAY_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PLAY_LL_Exported_Functions
  * @{
  */

/** @addtogroup PLAY_LL_EF_Init
  * @{
  */

/**
  * @brief  De-Initialize PLAY peripheral registers to their default reset values.
  * @param  PLAYx PLAY Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PLAY registers are de-initialized
  *          - ERROR: PLAY registers are not de-initialized
  */
ErrorStatus LL_PLAY_DeInit(PLAY_TypeDef *PLAYx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_PLAY_ALL_INSTANCE(PLAYx));

  if (PLAYx == PLAY1)
  {
    /* Unlock the Configuration Registers */
    LL_PLAY_Unlock(PLAYx);

    /* Reset Configuration Registers which are not reset by  */
    /* Force PLAY reset */
    LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_PLAY1APB);

    /* Release PLAY reset */
    LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_PLAY1APB);

    /* Privilege register set to default reset values */
    LL_PLAY_ConfigPrivilege(PLAYx, LL_PLAY_NPRIV);

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    /* Secure register set to default reset values */
    LL_PLAY_ConfigSecure(PLAYx, LL_PLAY_NSEC);
#endif /* __ARM_FEATURE_CMSE */
  }
  else
  {
    status = ERROR;
  }

  return (status);
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

#endif /* PLAY1 */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
