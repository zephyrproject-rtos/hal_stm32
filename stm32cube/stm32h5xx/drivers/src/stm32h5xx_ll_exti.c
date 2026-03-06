/**
  ******************************************************************************
  * @file    stm32h5xx_ll_exti.c
  * @author  MCD Application Team
  * @brief   EXTI LL module driver.
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
#include "stm32h5xx_ll_exti.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32H5xx_LL_Driver
  * @{
  */

#if defined (EXTI)

/** @defgroup EXTI_LL EXTI
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup EXTI_LL_Private_Macros
  * @{
  */

#define IS_LL_EXTI_LINE_0_31(__VALUE__)              (((__VALUE__) & ~LL_EXTI_LINE_ALL_0_31) == 0x00000000U)
#define IS_LL_EXTI_LINE_32_63(__VALUE__)             (((__VALUE__) & ~LL_EXTI_LINE_ALL_32_63) == 0x00000000U)

#if defined(EXTI_IMR3_IM)
#define IS_LL_EXTI_LINE_64_95(__VALUE__)             (((__VALUE__) & ~LL_EXTI_LINE_ALL_64_95) == 0x00000000U)
#endif /* EXTI_IMR3_IM */

#define IS_LL_EXTI_MODE(__VALUE__)                   (((__VALUE__) == LL_EXTI_MODE_IT)            \
                                                      || ((__VALUE__) == LL_EXTI_MODE_EVENT)         \
                                                      || ((__VALUE__) == LL_EXTI_MODE_IT_EVENT))


#define IS_LL_EXTI_TRIGGER(__VALUE__)                (((__VALUE__) == LL_EXTI_TRIGGER_NONE)       \
                                                      || ((__VALUE__) == LL_EXTI_TRIGGER_RISING)     \
                                                      || ((__VALUE__) == LL_EXTI_TRIGGER_FALLING)    \
                                                      || ((__VALUE__) == LL_EXTI_TRIGGER_RISING_FALLING))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup EXTI_LL_Exported_Functions
  * @{
  */

/** @addtogroup EXTI_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the EXTI registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: EXTI registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_EXTI_DeInit(void)
{
  /* Interrupt mask register set to default reset values */
  LL_EXTI_WriteReg(IMR1,   0xFFFE0000U);
#if defined(STM32H533xx) || defined(STM32H523xx)
  LL_EXTI_WriteReg(IMR2,   0x07DBFFFFU);
#elif defined(STM32H503xx)
  LL_EXTI_WriteReg(IMR2,   0x001BFFFFU);
#elif defined(STM32H5F5xx) || defined(STM32H5F4xx) || defined(STM32H5E5xx) ||defined(STM32H5E4xx)
  LL_EXTI_WriteReg(IMR2,   0xF3D9BFFFU);
#else
  LL_EXTI_WriteReg(IMR2,   0x03DBBFFFU);
#endif /* defined(STM32H533xx) || defined(STM32H523xx) */
#if defined(EXTI_IMR3_IM)
  LL_EXTI_WriteReg(IMR3,   0x00000002U);
#endif /* EXTI_IMR3_IM */

  /* Event mask register set to default reset values */
  LL_EXTI_WriteReg(EMR1,   0x00000000U);
  LL_EXTI_WriteReg(EMR2,   0x00000000U);
#if defined(EXTI_EMR3_EM)
  LL_EXTI_WriteReg(EMR3,   0x00000000U);
#endif /* EXTI_EMR3_EM */

  /* Rising Trigger selection register set to default reset values */
  LL_EXTI_WriteReg(RTSR1,  0x00000000U);
  LL_EXTI_WriteReg(RTSR2,  0x00000000U);
#if defined(EXTI_RTSR3_RT64)
  LL_EXTI_WriteReg(RTSR3,  0x00000000U);
#endif /* EXTI_RTSR3_RT64 */

  /* Falling Trigger selection register set to default reset values */
  LL_EXTI_WriteReg(FTSR1,  0x00000000U);
  LL_EXTI_WriteReg(FTSR2,  0x00000000U);
#if defined(EXTI_FTSR3_FT64)
  LL_EXTI_WriteReg(FTSR3,  0x00000000U);
#endif /* EXTI_FTSR3_FT64 */

  /* Software interrupt event register set to default reset values */
  LL_EXTI_WriteReg(SWIER1, 0x00000000U);
  LL_EXTI_WriteReg(SWIER2, 0x00000000U);
#if defined(EXTI_SWIER3_SWIER64)
  LL_EXTI_WriteReg(SWIER3, 0x00000000U);
#endif /* EXTI_SWIER3_SWIER64 */

  /* Pending register set to default reset values */
  LL_EXTI_WriteReg(RPR1,   0xFFFFFFFFU);
  LL_EXTI_WriteReg(FPR1,   0xFFFFFFFFU);
  LL_EXTI_WriteReg(RPR2,   0xFFFFFFFFU);
  LL_EXTI_WriteReg(FPR2,   0xFFFFFFFFU);
#if defined(EXTI_RPR3_RPIF)
  LL_EXTI_WriteReg(RPR3,   0x00000005U);
#endif /* EXTI_RPR3_RPIF */
#if defined(EXTI_FPR3_FPIF)
  LL_EXTI_WriteReg(FPR3,   0x00000005U);
#endif /* EXTI_FPR3_FPIF */

  /* Privilege register set to default reset values */
  LL_EXTI_WriteReg(PRIVCFGR1,  0x00000000U);
  LL_EXTI_WriteReg(PRIVCFGR2,  0x00000000U);
#if defined(EXTI_PRIVENR3_PRIV64)
  LL_EXTI_WriteReg(PRIVCFGR3,  0x00000000U);
#endif /* EXTI_PRIVENR3_PRIV64 */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Secure register set to default reset values */
  LL_EXTI_WriteReg(SECCFGR1,  0x00000000U);
  LL_EXTI_WriteReg(SECCFGR2,  0x00000000U);
#if defined(EXTI_SECENR3_SEC64)
  LL_EXTI_WriteReg(SECCFGR3,  0x00000000U);
#endif /* EXTI_SECENR3_SEC64 */
#endif /* __ARM_FEATURE_CMSE */
  return SUCCESS;
}

/**
  * @brief  Initialize the EXTI registers according to the specified parameters in EXTI_InitStruct.
  * @param  EXTI_InitStruct pointer to a @ref LL_EXTI_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: EXTI registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_EXTI_Init(LL_EXTI_InitTypeDef *EXTI_InitStruct)
{
  ErrorStatus status = SUCCESS;
  /* Check the parameters */
  assert_param(IS_LL_EXTI_LINE_0_31(EXTI_InitStruct->Line_0_31));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTI_InitStruct->Line_32_63));
#if defined(EXTI_IMR3_IM64)
  assert_param(IS_LL_EXTI_LINE_64_95(EXTI_InitStruct->Line_64_95));
#endif /* EXTI_IMR3_IM64 */
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->LineCommand));
  assert_param(IS_LL_EXTI_MODE(EXTI_InitStruct->Mode));

  /* ENABLE LineCommand */
  if (EXTI_InitStruct->LineCommand != DISABLE)
  {
    assert_param(IS_LL_EXTI_TRIGGER(EXTI_InitStruct->Trigger));

    /* Configure EXTI Lines in range from 0 to 31 */
    if (EXTI_InitStruct->Line_0_31 != LL_EXTI_LINE_NONE)
    {
      switch (EXTI_InitStruct->Mode)
      {
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          LL_EXTI_DisableEvent_0_31(EXTI_InitStruct->Line_0_31);
          /* Then Enable IT on provided Lines */
          LL_EXTI_EnableIT_0_31(EXTI_InitStruct->Line_0_31);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          LL_EXTI_DisableIT_0_31(EXTI_InitStruct->Line_0_31);
          /* Then Enable Event on provided Lines */
          LL_EXTI_EnableEvent_0_31(EXTI_InitStruct->Line_0_31);
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_EXTI_EnableIT_0_31(EXTI_InitStruct->Line_0_31);
          LL_EXTI_EnableEvent_0_31(EXTI_InitStruct->Line_0_31);
          break;
        default:
          status = ERROR;
          break;
      }
      if (EXTI_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        switch (EXTI_InitStruct->Trigger)
        {
          case LL_EXTI_TRIGGER_RISING:
            /* First Disable Falling Trigger on provided Lines */
            LL_EXTI_DisableFallingTrig_0_31(EXTI_InitStruct->Line_0_31);
            /* Then Enable Rising Trigger on provided Lines */
            LL_EXTI_EnableRisingTrig_0_31(EXTI_InitStruct->Line_0_31);
            break;
          case LL_EXTI_TRIGGER_FALLING:
            /* First Disable Rising Trigger on provided Lines */
            LL_EXTI_DisableRisingTrig_0_31(EXTI_InitStruct->Line_0_31);
            /* Then Enable Falling Trigger on provided Lines */
            LL_EXTI_EnableFallingTrig_0_31(EXTI_InitStruct->Line_0_31);
            break;
          case LL_EXTI_TRIGGER_RISING_FALLING:
            LL_EXTI_EnableRisingTrig_0_31(EXTI_InitStruct->Line_0_31);
            LL_EXTI_EnableFallingTrig_0_31(EXTI_InitStruct->Line_0_31);
            break;
          default:
            status = ERROR;
            break;
        }
      }
    }

    /* Configure EXTI Lines in range from 32 to 63 */
    if (EXTI_InitStruct->Line_32_63 != LL_EXTI_LINE_NONE)
    {
      switch (EXTI_InitStruct->Mode)
      {
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          LL_EXTI_DisableEvent_32_63(EXTI_InitStruct->Line_32_63);
          /* Then Enable IT on provided Lines */
          LL_EXTI_EnableIT_32_63(EXTI_InitStruct->Line_32_63);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          LL_EXTI_DisableIT_32_63(EXTI_InitStruct->Line_32_63);
          /* Then Enable Event on provided Lines */
          LL_EXTI_EnableEvent_32_63(EXTI_InitStruct->Line_32_63);
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_EXTI_EnableIT_32_63(EXTI_InitStruct->Line_32_63);
          LL_EXTI_EnableEvent_32_63(EXTI_InitStruct->Line_32_63);
          break;
        default:
          status = ERROR;
          break;
      }
      if (EXTI_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        switch (EXTI_InitStruct->Trigger)
        {
          case LL_EXTI_TRIGGER_RISING:
            /* First Disable Falling Trigger on provided Lines */
            LL_EXTI_DisableFallingTrig_32_63(EXTI_InitStruct->Line_32_63);
            /* Then Enable Rising Trigger on provided Lines */
            LL_EXTI_EnableRisingTrig_32_63(EXTI_InitStruct->Line_32_63);
            break;
          case LL_EXTI_TRIGGER_FALLING:
            /* First Disable Rising Trigger on provided Lines */
            LL_EXTI_DisableRisingTrig_32_63(EXTI_InitStruct->Line_32_63);
            /* Then Enable Falling Trigger on provided Lines */
            LL_EXTI_EnableFallingTrig_32_63(EXTI_InitStruct->Line_32_63);
            break;
          case LL_EXTI_TRIGGER_RISING_FALLING:
            LL_EXTI_EnableRisingTrig_32_63(EXTI_InitStruct->Line_32_63);
            LL_EXTI_EnableFallingTrig_32_63(EXTI_InitStruct->Line_32_63);
            break;
          default:
            status = ERROR;
            break;
        }
      }
    }
#if defined(EXTI_IMR3_IM64)
    /* Configure EXTI Lines in range from 64 to 95 */
    if (EXTI_InitStruct->Line_64_95 != LL_EXTI_LINE_NONE)
    {
      switch (EXTI_InitStruct->Mode)
      {
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          LL_EXTI_DisableEvent_64_95(EXTI_InitStruct->Line_64_95);
          /* Then Enable IT on provided Lines */
          LL_EXTI_EnableIT_64_95(EXTI_InitStruct->Line_64_95);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          LL_EXTI_DisableIT_64_95(EXTI_InitStruct->Line_64_95);
          /* Then Enable Event on provided Lines */
          LL_EXTI_EnableEvent_64_95(EXTI_InitStruct->Line_64_95);
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_EXTI_EnableIT_64_95(EXTI_InitStruct->Line_64_95);
          LL_EXTI_EnableEvent_64_95(EXTI_InitStruct->Line_64_95);
          break;
        default:
          status = ERROR;
          break;
      }
      if (EXTI_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        switch (EXTI_InitStruct->Trigger)
        {
          case LL_EXTI_TRIGGER_RISING:
            /* First Disable Falling Trigger on provided Lines */
            LL_EXTI_DisableFallingTrig_64_95(EXTI_InitStruct->Line_64_95);
            /* Then Enable Rising Trigger on provided Lines */
            LL_EXTI_EnableRisingTrig_64_95(EXTI_InitStruct->Line_64_95);
            break;
          case LL_EXTI_TRIGGER_FALLING:
            /* First Disable Rising Trigger on provided Lines */
            LL_EXTI_DisableRisingTrig_64_95(EXTI_InitStruct->Line_64_95);
            /* Then Enable Falling Trigger on provided Lines */
            LL_EXTI_EnableFallingTrig_64_95(EXTI_InitStruct->Line_64_95);
            break;
          case LL_EXTI_TRIGGER_RISING_FALLING:
            LL_EXTI_EnableRisingTrig_64_95(EXTI_InitStruct->Line_64_95);
            LL_EXTI_EnableFallingTrig_64_95(EXTI_InitStruct->Line_64_95);
            break;
          default:
            status = ERROR;
            break;
        }
      }
    }
#endif /* EXTI_IMR3_IM64 */
  }
  /* DISABLE LineCommand */
  else
  {
    /* De-configure EXTI Lines in range from 0 to 31 */
    LL_EXTI_DisableIT_0_31(EXTI_InitStruct->Line_0_31);
    LL_EXTI_DisableEvent_0_31(EXTI_InitStruct->Line_0_31);

    /* De-configure EXTI Lines in range from 32 to 63 */
    LL_EXTI_DisableIT_32_63(EXTI_InitStruct->Line_32_63);
    LL_EXTI_DisableEvent_32_63(EXTI_InitStruct->Line_32_63);

#if defined(EXTI_IMR3_IM64)
    /* De-configure EXTI Lines in range from 64 to 95 */
    LL_EXTI_DisableIT_64_95(EXTI_InitStruct->Line_64_95);
    LL_EXTI_DisableEvent_64_95(EXTI_InitStruct->Line_64_95);
#endif /* EXTI_IMR3_IM64 */

  }
  return status;
}

/**
  * @brief  Set each @ref LL_EXTI_InitTypeDef field to default value.
  * @param  EXTI_InitStruct Pointer to a @ref LL_EXTI_InitTypeDef structure.
  * @retval None
  */
void LL_EXTI_StructInit(LL_EXTI_InitTypeDef *EXTI_InitStruct)
{
  EXTI_InitStruct->Line_0_31      = LL_EXTI_LINE_NONE;
  EXTI_InitStruct->Line_32_63     = LL_EXTI_LINE_NONE;
#if defined(EXTI_IMR3_IM64)
  EXTI_InitStruct->Line_64_95     = LL_EXTI_LINE_NONE;
#endif /* EXTI_IMR3_IM64 */
  EXTI_InitStruct->LineCommand    = DISABLE;
  EXTI_InitStruct->Mode           = LL_EXTI_MODE_IT;
  EXTI_InitStruct->Trigger        = LL_EXTI_TRIGGER_FALLING;
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

#endif /* defined (EXTI) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
