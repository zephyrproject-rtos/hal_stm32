/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_crc.c
  * @author  MCD Application Team
  * @brief   CRC LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_ll_crc.h"
#include "stm32mp2xx_ll_bus.h"

#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if defined (CRC)

/** @addtogroup CRC_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CRC_LL_Exported_Functions
  * @{
  */

/** @addtogroup CRC_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize CRC registers (Registers restored to their default values).
  * @param  CRCx CRC Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: CRC registers are de-initialized
  *          - ERROR: CRC registers are not de-initialized
  */
ErrorStatus LL_CRC_DeInit(const CRC_TypeDef *CRCx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_CRC_ALL_INSTANCE(CRCx));

  if (CRCx == CRC)
  {
    /* Enable CRC reset state */
    LL_RCC_CRC_ForceReset();

    /* Release CRC from reset state */
    LL_RCC_CRC_ReleaseReset();
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

#endif /* defined (CRC) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
